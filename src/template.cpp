/**
 * @file template.cpp
 * @brief Template class implementation
 * @details Implementation of placeholder replacement
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/template.h>
#include <cdocx/document.h>
#include <cdocx/table.h>
#include <cdocx/paragraph.h>

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

// ============================================================================
// Text Replacement
// ============================================================================

bool Template::try_replace_in_text(std::string& text) {
    bool replaced = false;
    
    for (const auto& [key, value] : placeholders_) {
        std::string pattern = pattern_prefix_ + key + pattern_suffix_;
        size_t pos = 0;
        while ((pos = text.find(pattern, pos)) != std::string::npos) {
            text.replace(pos, pattern.length(), value);
            pos += value.length();
            replaced = true;
        }
    }
    
    return replaced;
}

// ============================================================================
// Main Replacement Functions
// ============================================================================

void Template::replace_in_paragraphs() {
    if (!doc_) return;
    
    auto paragraphs = doc_->get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        
        // Get runs in this paragraph
        for (auto& child : para->get_children()) {
            if (auto run = std::dynamic_pointer_cast<Run>(child)) {
                std::string text = run->get_text();
                if (try_replace_in_text(text)) {
                    run->set_text(text);
                }
            }
        }
    }
}

void Template::replace_in_tables() {
    if (!doc_) return;
    
    auto tables = doc_->get_tables();
    for (auto& table : tables) {
        if (!table) continue;
        
        // Process all cells in the table
        for (auto& row_child : table->get_children()) {
            if (auto row = std::dynamic_pointer_cast<Row>(row_child)) {
                for (auto& cell_child : row->get_children()) {
                    if (auto cell = std::dynamic_pointer_cast<Cell>(cell_child)) {
                        // Process paragraphs in this cell
                        for (auto& para_child : cell->get_children()) {
                            if (auto para = std::dynamic_pointer_cast<Paragraph>(para_child)) {
                                for (auto& run_child : para->get_children()) {
                                    if (auto run = std::dynamic_pointer_cast<Run>(run_child)) {
                                        std::string text = run->get_text();
                                        if (try_replace_in_text(text)) {
                                            run->set_text(text);
                                        }
                                    }
                                }
                            }
                        }
                    }
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
}

void Template::replace_in_headers_footers() {
    // TODO: Implement header/footer placeholder replacement
}

bool Template::has_placeholders() const {
    return !placeholders_.empty() || !image_placeholders_.empty();
}

size_t Template::get_placeholder_count() const {
    return placeholders_.size() + image_placeholders_.size();
}

} // namespace cdocx
