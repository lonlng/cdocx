/**
 * @file template.cpp
 * @brief Template class implementation
 * @details Implementation of placeholder replacement using FSM-based processing
 *          to handle placeholders split across multiple text runs.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/template.h>
#include <cdocx/document.h>

namespace cdocx {

// ============================================================================
// Constructor
// ============================================================================

Template::Template(Document* document) : doc_(document) {}

Template::Template(Document* document, const std::string& prefix, const std::string& suffix)
    : doc_(document), pattern_prefix_(prefix), pattern_suffix_(suffix) {}

// ============================================================================
// Placeholder Management
// ============================================================================

void Template::set(const std::string& key, const std::string& value) {
    placeholders_[key] = value;
}

void Template::set(const std::string& key, const char* value) {
    placeholders_[key] = std::string(value);
}

void Template::set_image(const std::string& key, const std::string& image_path) {
    image_placeholders_[key] = image_path;
}

void Template::set_pattern(const std::string& prefix, const std::string& suffix) {
    pattern_prefix_ = prefix;
    pattern_suffix_ = suffix;
}

void Template::clear() {
    placeholders_.clear();
    image_placeholders_.clear();
}

size_t Template::size() const {
    return placeholders_.size() + image_placeholders_.size();
}

// ============================================================================
// String Replacement
// ============================================================================

/**
 * @internal
 * @brief Replace all occurrences in a string using the placeholder map
 * @param[in,out] text String to modify
 * @return true if any replacement was made
 */
bool Template::replace_in_string(std::string& text) const {
    bool replaced = false;
    
    for (const auto& pair : placeholders_) {
        std::string placeholder = pattern_prefix_ + pair.first + pattern_suffix_;
        size_t pos = 0;
        
        while ((pos = text.find(placeholder, pos)) != std::string::npos) {
            text.replace(pos, placeholder.length(), pair.second);
            pos += pair.second.length();
            replaced = true;
        }
    }
    
    return replaced;
}

/**
 * @internal
 * @brief Try to replace placeholder in a single run
 * @param[in,out] r Run to process
 * @return true if replacement was successful
 * 
 * This handles the simple case where the entire placeholder is in one run.
 */
bool Template::try_replace_single_run(Run& r) const {
    std::string text = r.get_text();
    if (text.empty()) {
        return false;
    }
    
    std::string original = text;
    if (replace_in_string(text)) {
        r.set_text(text);
        return true;
    }
    
    return false;
}

// ============================================================================
// FSM-Based Multi-Run Placeholder Processing
// ============================================================================

/**
 * @internal
 * @brief Transition to collecting state in the FSM
 * @param[in,out] ctx Placeholder context
 * @param[in,out] r Current run
 * @param[in] text Current text
 * @param[in] prefix_pos Position in prefix pattern where match started
 */
void Template::transition_to_collecting_state(PlaceholderContext& ctx, Run& r, 
                                               const std::string& text, size_t prefix_pos) {
    ctx.first_run = &r;
    ctx.prefix_pos = prefix_pos;
    ctx.collected_text = text.substr(prefix_pos);
    ctx.runs_to_delete.clear();
}

/**
 * @internal
 * @brief Try to replace a collected placeholder
 * @param[in] ctx Placeholder context with collected information
 * @param[in,out] p Current paragraph
 * @return true if replacement was successful
 */
bool Template::try_replace_placeholder(const PlaceholderContext& ctx, Paragraph& p) {
    // Find suffix in collected text
    size_t suffix_pos = ctx.collected_text.find(pattern_suffix_);
    if (suffix_pos == std::string::npos) {
        return false;
    }
    
    // Extract placeholder key
    size_t prefix_len = pattern_prefix_.length();
    size_t key_start = ctx.prefix_pos > 0 ? 0 : prefix_len;
    size_t key_end = suffix_pos;
    std::string key = ctx.collected_text.substr(key_start, key_end - key_start);
    
    // Look up replacement
    auto it = placeholders_.find(key);
    if (it == placeholders_.end()) {
        return false;
    }
    
    // Replace in first run
    if (ctx.first_run) {
        std::string first_text = ctx.first_run->get_text();
        std::string before_placeholder = first_text.substr(0, ctx.prefix_pos);
        ctx.first_run->set_text(before_placeholder + it->second);
    }
    
    return true;
}

/**
 * @internal
 * @brief Delete runs that were collected during placeholder detection
 * @param[in] ctx Placeholder context
 * @param[in,out] p Current paragraph
 */
void Template::delete_collected_runs(const PlaceholderContext& ctx, Paragraph& p) {
    for (Run* run : ctx.runs_to_delete) {
        p.remove_run(*run);
    }
}

/**
 * @internal
 * @brief Process a single paragraph for placeholders
 * @param[in,out] p Paragraph to process
 * 
 * Uses a Finite State Machine (FSM) approach to handle placeholders
 * that span multiple text runs.
 */
void Template::process_paragraph(Paragraph& p) {
    PlaceholderContext ctx;
    bool collecting = false;
    
    for (auto r = p.runs(); r.has_next(); r.next()) {
        std::string text = r.get_text();
        if (text.empty()) {
            continue;
        }
        
        if (!collecting) {
            // Look for prefix pattern start
            size_t prefix_pos = text.find(pattern_prefix_);
            if (prefix_pos != std::string::npos) {
                // Check if complete placeholder is in this run
                size_t suffix_pos = text.find(pattern_suffix_, prefix_pos);
                if (suffix_pos != std::string::npos) {
                    // Complete placeholder in single run - process directly
                    try_replace_single_run(r);
                } else {
                    // Start collecting across runs
                    transition_to_collecting_state(ctx, r, text, prefix_pos);
                    collecting = true;
                }
            }
        } else {
            // Currently collecting - append text
            ctx.collected_text += text;
            ctx.runs_to_delete.push_back(&r);
            
            // Check for suffix
            size_t suffix_pos = ctx.collected_text.find(pattern_suffix_);
            if (suffix_pos != std::string::npos) {
                // Complete placeholder found
                if (try_replace_placeholder(ctx, p)) {
                    delete_collected_runs(ctx, p);
                }
                ctx.clear();
                collecting = false;
            }
        }
    }
}

// ============================================================================
// Main Replacement Functions
// ============================================================================

void Template::replace_in_paragraphs() {
    for (auto p = doc_->paragraphs(); p.has_next(); p.next()) {
        // First try simple single-run replacement
        for (auto r = p.runs(); r.has_next(); r.next()) {
            try_replace_single_run(r);
        }
        
        // Then process multi-run placeholders with FSM
        process_paragraph(p);
    }
}

void Template::replace_in_tables() {
    for (auto t = doc_->tables(); t.has_next(); t.next()) {
        for (auto row = t.rows(); row.has_next(); row.next()) {
            for (auto cell = row.cells(); cell.has_next(); cell.next()) {
                for (auto p = cell.paragraphs(); p.has_next(); p.next()) {
                    for (auto r = p.runs(); r.has_next(); r.next()) {
                        try_replace_single_run(r);
                    }
                    process_paragraph(p);
                }
            }
        }
    }
}

void Template::replace_all() {
    if (!doc_ || !doc_->is_open()) {
        return;
    }
    
    replace_in_paragraphs();
    replace_in_tables();
    
    // TODO: Handle image placeholders
}

} // namespace cdocx
