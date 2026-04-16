/**
 * @file advanced.cpp
 * @brief Advanced features implementation
 * @details Implementation of advanced features including Bookmark, Range,
 *          DocumentBuilder, TableOperations, and DocumentSearch.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/advanced.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/footnote.h>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <unordered_map>

namespace cdocx {

// ============================================================================
// Utility Functions
// ============================================================================

namespace utils {

bool starts_with_ci(const std::string& str, const std::string& prefix) {
    if (prefix.size() > str.size()) {
        return false;
    }
    return std::equal(prefix.begin(), prefix.end(), str.begin(),
                      [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

bool contains_ci(const std::string& str, const std::string& substr) {
    if (substr.empty()) {
        return true;
    }
    if (substr.size() > str.size()) {
        return false;
    }
    
    auto it = std::search(str.begin(), str.end(), substr.begin(), substr.end(),
                          [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    return it != str.end();
}

std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

} // namespace utils

// ============================================================================
// Bookmark Implementation
// ============================================================================

Bookmark::Bookmark() = default;

Bookmark::Bookmark(Document* doc, const std::string& name,
                   pugi::xml_node start, pugi::xml_node end)
    : doc_(doc), name_(name), start_node_(start), end_node_(end) {}

std::string Bookmark::get_name() const {
    return name_;
}

void Bookmark::set_name(const std::string& name) {
    name_ = name;
    // Update XML attributes
    if (start_node_) {
        start_node_.attribute("w:name").set_value(name.c_str());
    }
    if (end_node_) {
        end_node_.attribute("w:name").set_value(name.c_str());
    }
}

std::string Bookmark::get_text() const {
    if (!is_valid()) {
        return "";
    }
    
    std::string result;
    
    // Find paragraphs between bookmark start and end
    pugi::xml_node current = start_node_.parent();
    pugi::xml_node end = end_node_.parent();
    
    // Simple case: same paragraph
    if (current == end) {
        for (pugi::xml_node run = current.child("w:r"); run; run = run.next_sibling("w:r")) {
            // Check if run is between bookmarks
            pugi::xml_node t = run.child("w:t");
            if (t) {
                result += t.text().get();
            }
        }
    }
    // TODO: Handle cross-paragraph bookmarks
    
    return result;
}

bool Bookmark::set_text(const std::string& text) {
    if (!is_valid()) {
        return false;
    }
    
    pugi::xml_node current = start_node_.parent();
    
    // Clear existing runs
    pugi::xml_node run = current.child("w:r");
    while (run) {
        pugi::xml_node next = run.next_sibling("w:r");
        current.remove_child(run);
        run = next;
    }
    
    // Create new run with text
    pugi::xml_node new_run = current.append_child("w:r");
    pugi::xml_node t = new_run.append_child("w:t");
    t.text().set(text.c_str());
    
    return true;
}

bool Bookmark::is_valid() const {
    return start_node_ && end_node_;
}

bool Bookmark::remove() {
    if (!is_valid()) {
        return false;
    }
    
    // Remove bookmark markers but keep content
    start_node_.parent().remove_child(start_node_);
    end_node_.parent().remove_child(end_node_);
    
    return true;
}

bool Bookmark::remove_with_content() {
    if (!is_valid()) {
        return false;
    }
    
    // TODO: Remove content between bookmarks
    // This is complex as it may span multiple paragraphs
    
    return remove();
}

// ============================================================================
// Enhanced Format-Preserving Methods (v0.3.0)
// ============================================================================

BookmarkFormat Bookmark::get_format() const {
    BookmarkFormat fmt;
    
    if (!is_valid()) {
        return fmt;
    }
    
    // Get the paragraph containing the bookmark
    pugi::xml_node para = start_node_.parent();
    
    // ========== Extract Paragraph Format (w:pPr) ==========
    pugi::xml_node pPr = para.child("w:pPr");
    if (pPr) {
        // Alignment (w:jc)
        pugi::xml_node jc = pPr.child("w:jc");
        if (jc) {
            fmt.alignment = jc.attribute("w:val").value();
        }
        
        // Spacing (w:spacing)
        pugi::xml_node spacing = pPr.child("w:spacing");
        if (spacing) {
            fmt.line_spacing = spacing.attribute("w:line").as_int();
            fmt.line_rule = spacing.attribute("w:lineRule").value();
            fmt.space_before = spacing.attribute("w:before").as_int();
            fmt.space_after = spacing.attribute("w:after").as_int();
        }
        
        // Indentation (w:ind)
        pugi::xml_node ind = pPr.child("w:ind");
        if (ind) {
            fmt.first_line_indent = ind.attribute("w:firstLine").as_int();
            if (fmt.first_line_indent == 0) {
                // Check for hanging indent (negative first line)
                fmt.first_line_indent = -ind.attribute("w:hanging").as_int();
            }
            fmt.left_indent = ind.attribute("w:left").as_int();
            fmt.right_indent = ind.attribute("w:right").as_int();
        }
        
        // Keep with next (w:keepNext)
        fmt.keep_next = pPr.child("w:keepNext") != nullptr;
        
        // Keep lines together (w:keepLines)
        fmt.keep_lines = pPr.child("w:keepLines") != nullptr;
        
        // Page break before (w:pageBreakBefore)
        fmt.page_break_before = pPr.child("w:pageBreakBefore") != nullptr;
    }
    
    // ========== Extract Character Format (w:rPr) ==========
    pugi::xml_node run = para.child("w:r");
    
    // Find first run that is between bookmark markers
    while (run) {
        pugi::xml_node rPr = run.child("w:rPr");
        if (rPr) {
            // Extract fonts
            pugi::xml_node rFonts = rPr.child("w:rFonts");
            if (rFonts) {
                fmt.font_ascii = rFonts.attribute("w:ascii").value();
                fmt.font_far_east = rFonts.attribute("w:eastAsia").value();
                fmt.font_hansi = rFonts.attribute("w:hAnsi").value();
                fmt.font_hint = rFonts.attribute("w:hint").value();
            }
            
            // Extract font size
            pugi::xml_node sz = rPr.child("w:sz");
            if (sz) {
                fmt.font_size = sz.attribute("w:val").as_int();
            }
            
            // Extract color
            pugi::xml_node color = rPr.child("w:color");
            if (color) {
                fmt.color = color.attribute("w:val").value();
            }
            
            // Extract bold
            pugi::xml_node b = rPr.child("w:b");
            fmt.bold = b != nullptr;
            
            // Extract italic
            pugi::xml_node i = rPr.child("w:i");
            fmt.italic = i != nullptr;
            
            // Extract underline
            pugi::xml_node u = rPr.child("w:u");
            fmt.underline = u != nullptr;
            
            // Extract strikethrough
            pugi::xml_node strike = rPr.child("w:strike");
            fmt.strikethrough = strike != nullptr;
            
            // Format found, return it
            return fmt;
        }
        run = run.next_sibling("w:r");
    }
    
    return fmt;
}

bool Bookmark::set_text_keep_format(const std::string& text) {
    if (!is_valid()) {
        return false;
    }
    
    // Extract existing format
    BookmarkFormat fmt = get_format();
    
    // Use formatted text setting
    return set_text_formatted(text, fmt);
}

bool Bookmark::set_text_formatted(const std::string& text, const BookmarkFormat& format) {
    if (!is_valid()) {
        return false;
    }
    
    pugi::xml_node para = start_node_.parent();
    
    // ========== Apply Paragraph Format (w:pPr) ==========
    pugi::xml_node pPr = para.child("w:pPr");
    if (!pPr) {
        pPr = para.prepend_child("w:pPr");
    }
    
    // Alignment (w:jc)
    if (!format.alignment.empty()) {
        pugi::xml_node jc = pPr.child("w:jc");
        if (!jc) {
            jc = pPr.append_child("w:jc");
        }
        jc.append_attribute("w:val").set_value(format.alignment.c_str());
    }
    
    // Spacing (w:spacing)
    if (format.line_spacing > 0 || format.space_before > 0 || format.space_after > 0 || 
        !format.line_rule.empty()) {
        pugi::xml_node spacing = pPr.child("w:spacing");
        if (!spacing) {
            spacing = pPr.append_child("w:spacing");
        }
        if (format.line_spacing > 0) {
            spacing.append_attribute("w:line").set_value(format.line_spacing);
        }
        if (!format.line_rule.empty()) {
            spacing.append_attribute("w:lineRule").set_value(format.line_rule.c_str());
        }
        if (format.space_before > 0) {
            spacing.append_attribute("w:before").set_value(format.space_before);
        }
        if (format.space_after > 0) {
            spacing.append_attribute("w:after").set_value(format.space_after);
        }
    }
    
    // Indentation (w:ind)
    if (format.first_line_indent != 0 || format.left_indent > 0 || format.right_indent > 0) {
        pugi::xml_node ind = pPr.child("w:ind");
        if (!ind) {
            ind = pPr.append_child("w:ind");
        }
        if (format.first_line_indent > 0) {
            ind.append_attribute("w:firstLine").set_value(format.first_line_indent);
        } else if (format.first_line_indent < 0) {
            ind.append_attribute("w:hanging").set_value(-format.first_line_indent);
        }
        if (format.left_indent > 0) {
            ind.append_attribute("w:left").set_value(format.left_indent);
        }
        if (format.right_indent > 0) {
            ind.append_attribute("w:right").set_value(format.right_indent);
        }
    }
    
    // Keep with next (w:keepNext)
    if (format.keep_next) {
        if (!pPr.child("w:keepNext")) {
            pPr.append_child("w:keepNext");
        }
    }
    
    // Keep lines together (w:keepLines)
    if (format.keep_lines) {
        if (!pPr.child("w:keepLines")) {
            pPr.append_child("w:keepLines");
        }
    }
    
    // Page break before (w:pageBreakBefore)
    if (format.page_break_before) {
        if (!pPr.child("w:pageBreakBefore")) {
            pPr.append_child("w:pageBreakBefore");
        }
    }
    
    // ========== Handle Run Content ==========
    // Find and remove all runs between bookmark start and end
    pugi::xml_node current = start_node_.next_sibling();
    while (current && current != end_node_) {
        pugi::xml_node next = current.next_sibling();
        if (std::string(current.name()) == "w:r") {
            para.remove_child(current);
        }
        current = next;
    }
    
    // Create new run with character format
    pugi::xml_node new_run = para.insert_child_before("w:r", end_node_);
    
    // Apply character formatting if specified
    if (format.is_valid() || format.bold || format.italic || format.underline || format.strikethrough) {
        pugi::xml_node rPr = new_run.append_child("w:rPr");
        
        // Font settings
        if (!format.font_ascii.empty() || !format.font_far_east.empty() || 
            !format.font_hansi.empty() || !format.font_hint.empty()) {
            pugi::xml_node rFonts = rPr.append_child("w:rFonts");
            if (!format.font_ascii.empty())
                rFonts.append_attribute("w:ascii").set_value(format.font_ascii.c_str());
            if (!format.font_far_east.empty())
                rFonts.append_attribute("w:eastAsia").set_value(format.font_far_east.c_str());
            if (!format.font_hansi.empty())
                rFonts.append_attribute("w:hAnsi").set_value(format.font_hansi.c_str());
            if (!format.font_hint.empty())
                rFonts.append_attribute("w:hint").set_value(format.font_hint.c_str());
        }
        
        // Font size
        if (format.font_size > 0) {
            pugi::xml_node sz = rPr.append_child("w:sz");
            sz.append_attribute("w:val").set_value(format.font_size);
            pugi::xml_node szCs = rPr.append_child("w:szCs");
            szCs.append_attribute("w:val").set_value(format.font_size);
        }
        
        // Color
        if (!format.color.empty()) {
            pugi::xml_node color = rPr.append_child("w:color");
            color.append_attribute("w:val").set_value(format.color.c_str());
        }
        
        // Bold
        if (format.bold) {
            rPr.append_child("w:b");
        }
        
        // Italic
        if (format.italic) {
            rPr.append_child("w:i");
        }
        
        // Underline
        if (format.underline) {
            pugi::xml_node u = rPr.append_child("w:u");
            u.append_attribute("w:val").set_value("single");
        }
        
        // Strikethrough
        if (format.strikethrough) {
            rPr.append_child("w:strike");
        }
    }
    
    // Add text content
    pugi::xml_node t = new_run.append_child("w:t");
    t.text().set(text.c_str());
    
    return true;
}

bool Bookmark::is_cross_paragraph() const {
    if (!is_valid()) {
        return false;
    }
    
    return start_node_.parent() != end_node_.parent();
}

std::vector<pugi::xml_node> Bookmark::get_covered_paragraphs() const {
    std::vector<pugi::xml_node> paragraphs;
    
    if (!is_valid()) {
        return paragraphs;
    }
    
    pugi::xml_node start_para = start_node_.parent();
    pugi::xml_node end_para = end_node_.parent();
    
    // Same paragraph
    if (start_para == end_para) {
        paragraphs.push_back(start_para);
        return paragraphs;
    }
    
    // Cross-paragraph: collect all paragraphs
    paragraphs.push_back(start_para);
    
    pugi::xml_node current = start_para.next_sibling("w:p");
    while (current && current != end_para) {
        paragraphs.push_back(current);
        current = current.next_sibling("w:p");
    }
    
    if (end_para) {
        paragraphs.push_back(end_para);
    }
    
    return paragraphs;
}

bool Bookmark::set_text_cross_paragraph(const std::string& text) {
    if (!is_valid()) {
        return false;
    }
    
    auto paragraphs = get_covered_paragraphs();
    if (paragraphs.empty()) {
        return false;
    }
    
    // Single paragraph - use normal method
    if (paragraphs.size() == 1) {
        return set_text_keep_format(text);
    }
    
    // Multi-paragraph handling:
    // 1. Extract format from first paragraph
    BookmarkFormat fmt;
    pugi::xml_node first_run = paragraphs[0].child("w:r");
    if (first_run) {
        pugi::xml_node rPr = first_run.child("w:rPr");
        if (rPr) {
            pugi::xml_node rFonts = rPr.child("w:rFonts");
            if (rFonts) {
                fmt.font_ascii = rFonts.attribute("w:ascii").value();
                fmt.font_far_east = rFonts.attribute("w:eastAsia").value();
            }
            pugi::xml_node sz = rPr.child("w:sz");
            if (sz) {
                fmt.font_size = sz.attribute("w:val").as_int();
            }
        }
    }
    
    // 2. Remove intermediate paragraphs
    for (size_t i = 1; i < paragraphs.size() - 1; ++i) {
        paragraphs[i].parent().remove_child(paragraphs[i]);
    }
    
    // 3. Move bookmarkEnd to first paragraph
    pugi::xml_node last_para = paragraphs.back();
    std::string bookmark_id = start_node_.attribute("w:id").value();
    
    for (pugi::xml_node node = last_para.first_child(); node; node = node.next_sibling()) {
        if (std::string(node.name()) == "w:bookmarkEnd") {
            if (node.attribute("w:id").value() == bookmark_id) {
                // Move to first paragraph
                paragraphs[0].append_copy(node);
                last_para.remove_child(node);
                break;
            }
        }
    }
    
    // 4. Remove last paragraph
    if (paragraphs.size() > 1) {
        last_para.parent().remove_child(last_para);
    }
    
    // 5. Update end_node_ reference
    end_node_ = paragraphs[0].last_child();
    
    // 6. Set text with preserved format
    return set_text_formatted(text, fmt);
}

// ============================================================================
// BookmarkCollection Implementation
// ============================================================================

BookmarkCollection::BookmarkCollection(Document* doc) : doc_(doc) {}

void BookmarkCollection::collect_bookmarks() const {
    if (collected_) {
        return;
    }

    bookmarks_.clear();

    // Scan document.xml for bookmarks
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        collected_ = true;
        return;
    }

    // Find all bookmarkStart and bookmarkEnd elements recursively
    // Use ID-based matching for accurate pairing
    std::map<std::string, pugi::xml_node> starts;  // id -> node
    std::map<std::string, std::string> id_to_name; // id -> name
    std::map<std::string, pugi::xml_node> ends;    // id -> node

    auto collect_from_node = [&](auto& self, pugi::xml_node node) -> void {
        for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
            std::string name = child.name();
            if (name == "w:bookmarkStart") {
                std::string id = child.attribute("w:id").value();
                std::string bm_name = child.attribute("w:name").value();
                if (!id.empty()) {
                    starts[id] = child;
                    id_to_name[id] = bm_name;
                }
            } else if (name == "w:bookmarkEnd") {
                std::string id = child.attribute("w:id").value();
                if (!id.empty()) {
                    ends[id] = child;
                }
            }
            self(self, child);
        }
    };

    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    collect_from_node(collect_from_node, body);

    // Create Bookmark objects by matching IDs
    for (const auto& pair : starts) {
        const std::string& id = pair.first;
        const pugi::xml_node& start_node = pair.second;

        // Find corresponding end by ID
        auto end_it = ends.find(id);
        if (end_it != ends.end()) {
            // Valid bookmark with matching start and end
            bookmarks_.emplace_back(doc_, id_to_name[id], start_node, end_it->second);
        }
        // Else: orphaned bookmark start (no matching end), skip it
    }

    // Note: orphaned bookmark ends (no matching start) are ignored

    collected_ = true;
}

size_t BookmarkCollection::count() const {
    collect_bookmarks();
    return bookmarks_.size();
}

Bookmark BookmarkCollection::get(size_t index) const {
    collect_bookmarks();
    if (index < bookmarks_.size()) {
        return bookmarks_[index];
    }
    return Bookmark();
}

std::optional<Bookmark> BookmarkCollection::get(const std::string& name) const {
    collect_bookmarks();
    
    for (const auto& bm : bookmarks_) {
        if (utils::to_lower(bm.get_name()) == utils::to_lower(name)) {
            return bm;
        }
    }
    
    return std::nullopt;
}

bool BookmarkCollection::contains(const std::string& name) const {
    return get(name).has_value();
}

bool BookmarkCollection::remove(const std::string& name) {
    collect_bookmarks();
    
    for (auto it = bookmarks_.begin(); it != bookmarks_.end(); ++it) {
        if (utils::to_lower(it->get_name()) == utils::to_lower(name)) {
            it->remove();
            bookmarks_.erase(it);
            return true;
        }
    }
    
    return false;
}

bool BookmarkCollection::remove_at(size_t index) {
    collect_bookmarks();
    
    if (index < bookmarks_.size()) {
        bookmarks_[index].remove();
        bookmarks_.erase(bookmarks_.begin() + index);
        return true;
    }
    
    return false;
}

void BookmarkCollection::clear() {
    collect_bookmarks();
    for (auto& bm : bookmarks_) {
        bm.remove();
    }
    bookmarks_.clear();
}

Bookmark BookmarkCollection::add(const std::string& name, Paragraph& para) {
    if (!doc_ || name.empty()) {
        return Bookmark();
    }

    // If bookmark already exists, return it
    auto existing = get(name);
    if (existing) {
        return *existing;
    }

    int id = doc_->generate_unique_bookmark_id();

    auto start = std::make_shared<BookmarkStart>(name, id);
    auto end = std::make_shared<BookmarkEnd>(id);

    para.append_child(start);
    para.append_child(end);

    // Sync to physical so collect_bookmarks() can find the new nodes
    doc_->sync_to_physical_tree();

    // Invalidate cache so next access picks up the new bookmark
    collected_ = false;

    auto result = get(name);
    if (result) {
        return *result;
    }
    return Bookmark();
}

std::vector<Bookmark>::iterator BookmarkCollection::begin() {
    collect_bookmarks();
    return bookmarks_.begin();
}

std::vector<Bookmark>::iterator BookmarkCollection::end() {
    collect_bookmarks();
    return bookmarks_.end();
}

std::vector<Bookmark>::const_iterator BookmarkCollection::begin() const {
    collect_bookmarks();
    return bookmarks_.begin();
}

std::vector<Bookmark>::const_iterator BookmarkCollection::end() const {
    collect_bookmarks();
    return bookmarks_.end();
}

std::vector<std::string> BookmarkCollection::get_names() const {
    collect_bookmarks();
    std::vector<std::string> names;
    names.reserve(bookmarks_.size());
    for (const auto& bm : bookmarks_) {
        names.push_back(bm.get_name());
    }
    return names;
}

// ============================================================================
// Range Implementation
// ============================================================================

Range::Range() = default;

Range::Range(Document* doc, pugi::xml_node start, pugi::xml_node end)
    : doc_(doc), start_para_(start), end_para_(end) {}

std::string Range::get_text() const {
    std::string result;
    
    pugi::xml_node current = start_para_;
    while (current) {
        // Get text from paragraph
        for (pugi::xml_node run = current.child("w:r"); run; run = run.next_sibling("w:r")) {
            pugi::xml_node t = run.child("w:t");
            if (t) {
                result += t.text().get();
            }
        }
        
        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    
    return result;
}

bool Range::replace(const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return false;
    }

    // Fallback for DOM paragraphs without XML node binding
    if (!is_valid() && doc_) {
        auto paragraphs = doc_->get_paragraphs();
        for (auto& para : paragraphs) {
            if (!para) continue;
            std::string para_text = para->get_text();
            size_t pos = para_text.find(old_text);
            if (pos != std::string::npos) {
                para_text.replace(pos, old_text.size(), new_text);
                para->set_text(para_text);
                return true;
            }
        }
        return false;
    }

    pugi::xml_node current = start_para_;
    while (current) {
        // Collect text from all runs in this paragraph
        std::string para_text;
        for (pugi::xml_node run = current.child("w:r"); run; run = run.next_sibling("w:r")) {
            pugi::xml_node t = run.child("w:t");
            if (t) {
                para_text += t.text().get();
            }
        }

        size_t pos = para_text.find(old_text);
        if (pos != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);

            // Clear all runs and set first run to new text
            pugi::xml_node first_run;
            pugi::xml_node run = current.child("w:r");
            while (run) {
                pugi::xml_node next = run.next_sibling("w:r");
                if (!first_run) {
                    first_run = run;
                    // Clear existing text nodes
                    for (pugi::xml_node t = run.child("w:t"); t; t = t.next_sibling("w:t")) {
                        run.remove_child(t);
                    }
                    pugi::xml_node new_t = run.append_child("w:t");
                    if (!para_text.empty() && (std::isspace(para_text.front()) || std::isspace(para_text.back()))) {
                        new_t.append_attribute("xml:space").set_value("preserve");
                    }
                    new_t.text().set(para_text.c_str());
                } else {
                    current.remove_child(run);
                }
                run = next;
            }

            // If no run existed, create one
            if (!first_run) {
                pugi::xml_node new_run = current.append_child("w:r");
                pugi::xml_node new_t = new_run.append_child("w:t");
                if (!para_text.empty() && (std::isspace(para_text.front()) || std::isspace(para_text.back()))) {
                    new_t.append_attribute("xml:space").set_value("preserve");
                }
                new_t.text().set(para_text.c_str());
            }

            return true;
        }

        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    return false;
}

int Range::replace_all(const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return 0;
    }

    // Fallback for DOM paragraphs without XML node binding
    if (!is_valid() && doc_) {
        int total = 0;
        auto paragraphs = doc_->get_paragraphs();
        for (auto& para : paragraphs) {
            if (!para) continue;
            std::string para_text = para->get_text();
            int count = 0;
            size_t pos = 0;
            while ((pos = para_text.find(old_text, pos)) != std::string::npos) {
                para_text.replace(pos, old_text.size(), new_text);
                pos += new_text.size();
                ++count;
            }
            if (count > 0) {
                para->set_text(para_text);
                total += count;
            }
        }
        return total;
    }

    int total = 0;
    pugi::xml_node current = start_para_;
    while (current) {
        // Collect text from all runs in this paragraph
        std::string para_text;
        for (pugi::xml_node run = current.child("w:r"); run; run = run.next_sibling("w:r")) {
            pugi::xml_node t = run.child("w:t");
            if (t) {
                para_text += t.text().get();
            }
        }

        int count = 0;
        size_t pos = 0;
        while ((pos = para_text.find(old_text, pos)) != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);
            pos += new_text.size();
            ++count;
        }

        if (count > 0) {
            ++total;
            // Clear all runs and set first run to new text
            pugi::xml_node first_run;
            pugi::xml_node run = current.child("w:r");
            while (run) {
                pugi::xml_node next = run.next_sibling("w:r");
                if (!first_run) {
                    first_run = run;
                    for (pugi::xml_node t = run.child("w:t"); t; t = t.next_sibling("w:t")) {
                        run.remove_child(t);
                    }
                    pugi::xml_node new_t = run.append_child("w:t");
                    if (!para_text.empty() && (std::isspace(para_text.front()) || std::isspace(para_text.back()))) {
                        new_t.append_attribute("xml:space").set_value("preserve");
                    }
                    new_t.text().set(para_text.c_str());
                } else {
                    current.remove_child(run);
                }
                run = next;
            }

            if (!first_run) {
                pugi::xml_node new_run = current.append_child("w:r");
                pugi::xml_node new_t = new_run.append_child("w:t");
                if (!para_text.empty() && (std::isspace(para_text.front()) || std::isspace(para_text.back()))) {
                    new_t.append_attribute("xml:space").set_value("preserve");
                }
                new_t.text().set(para_text.c_str());
            }
        }

        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    return total;
}

bool Range::delete_content() {
    if (!is_valid()) {
        return false;
    }

    pugi::xml_node current = start_para_;
    while (current) {
        // Remove all run elements
        pugi::xml_node run = current.child("w:r");
        while (run) {
            pugi::xml_node next = run.next_sibling("w:r");
            current.remove_child(run);
            run = next;
        }

        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    return true;
}

bool Range::is_valid() const {
    return start_para_ && end_para_;
}

void Range::collapse(bool to_start) {
    if (to_start) {
        end_para_ = start_para_;
    } else {
        start_para_ = end_para_;
    }
}

// ============================================================================
// TableOperations Implementation
// ============================================================================

bool TableOperations::insert_row(Table& table, size_t index) {
    return table.insert_row(static_cast<int>(index)) != nullptr;
}

bool TableOperations::append_row(Table& table) {
    return table.append_row() != nullptr;
}

bool TableOperations::delete_row(Table& table, size_t index) {
    table.remove_row(static_cast<int>(index));
    return true;
}

bool TableOperations::insert_cell(Row& row, size_t index) {
    return row.insert_cell(static_cast<int>(index)) != nullptr;
}

bool TableOperations::delete_cell(Row& row, size_t index) {
    auto cell = row.get_cell(static_cast<int>(index));
    if (cell) {
        row.remove_child(cell);
        return true;
    }
    return false;
}

size_t TableOperations::get_row_count(const Table& table) {
    return static_cast<size_t>(table.get_row_count());
}

size_t TableOperations::get_column_count(const Table& table) {
    return static_cast<size_t>(table.get_column_count());
}

bool TableOperations::merge_cells_horizontal(Row& row, size_t start, size_t end) {
    auto table = row.get_parent_table();
    if (!table) return false;
    int row_index = row.get_row_index();
    if (row_index < 0) return false;
    auto result = table->merge_cells(row_index, static_cast<int>(start),
                                     row_index, static_cast<int>(end));
    return result != nullptr;
}

bool TableOperations::set_cell_text(Cell& cell, const std::string& text) {
    cell.set_text(text);
    return true;
}

std::string TableOperations::get_cell_text(const Cell& cell) {
    return cell.get_text();
}

// ============================================================================
// DocumentBuilder Implementation
// ============================================================================

DocumentBuilder::DocumentBuilder(Document* doc) : doc_(doc) {
    target_xml_doc_ = doc ? doc->get_document_xml() : nullptr;
}

DocumentBuilder::DocumentBuilder(std::shared_ptr<Document> doc)
    : doc_sptr(doc), doc_(doc.get()) {
    target_xml_doc_ = doc_ ? doc_->get_document_xml() : nullptr;
}

DocumentBuilder::~DocumentBuilder() = default;

void DocumentBuilder::ensure_paragraph() {
    if (!current_paragraph_ || std::strcmp(current_paragraph_.name(), "w:p") != 0) {
        pugi::xml_node body = get_body();
        pugi::xml_node sectPr = body.child("w:sectPr");
        if (sectPr) {
            current_paragraph_ = body.insert_child_before("w:p", sectPr);
        } else {
            current_paragraph_ = body.append_child("w:p");
        }
        current_node_ = current_paragraph_;
        if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
}

pugi::xml_node DocumentBuilder::get_body() {
    pugi::xml_document* doc_xml = target_xml_doc_ ? target_xml_doc_ : doc_->get_document_xml();
    if (!doc_xml) {
        return pugi::xml_node();
    }
    pugi::xml_node root = doc_xml->first_child();
    if (!root) return pugi::xml_node();
    // document.xml has w:document -> w:body, header/footer XML has w:hdr/w:ftr directly
    if (std::strcmp(root.name(), "w:document") == 0) {
        return root.child("w:body");
    }
    if (std::strcmp(root.name(), "w:hdr") == 0 || std::strcmp(root.name(), "w:ftr") == 0) {
        return root;
    }
    return pugi::xml_node();
}

void DocumentBuilder::apply_formatting(pugi::xml_node run) {
    if (!run) {
        return;
    }
    
    pugi::xml_node rPr = run.child("w:rPr");
    if (!rPr) {
        rPr = run.prepend_child("w:rPr");
    }
    
    // Apply formatting flags
    if (format_.bold) {
        if (!rPr.child("w:b")) {
            rPr.append_child("w:b");
        }
    }
    if (format_.italic) {
        if (!rPr.child("w:i")) {
            rPr.append_child("w:i");
        }
    }
    if (format_.underline) {
        pugi::xml_node u = rPr.child("w:u");
        if (!u) {
            u = rPr.append_child("w:u");
        }
        u.append_attribute("w:val").set_value("single");
    }
    if (format_.strikethrough) {
        if (!rPr.child("w:strike")) {
            rPr.append_child("w:strike");
        }
    }
    if (!format_.font_name.empty()) {
        pugi::xml_node rFonts = rPr.child("w:rFonts");
        if (!rFonts) {
            rFonts = rPr.append_child("w:rFonts");
        }
        rFonts.append_attribute("w:ascii").set_value(format_.font_name.c_str());
        rFonts.append_attribute("w:hAnsi").set_value(format_.font_name.c_str());
    }
    if (format_.font_size > 0) {
        pugi::xml_node sz = rPr.child("w:sz");
        if (!sz) {
            sz = rPr.append_child("w:sz");
        }
        sz.append_attribute("w:val").set_value(format_.font_size * 2);
    }
    if (!format_.color.empty()) {
        pugi::xml_node color = rPr.child("w:color");
        if (!color) {
            color = rPr.append_child("w:color");
        }
        color.append_attribute("w:val").set_value(format_.color.c_str());
    }
}

// Navigation
DocumentBuilder& DocumentBuilder::move_to_document_start() {
    pugi::xml_node body = get_body();
    current_paragraph_ = body.child("w:p");
    current_node_ = current_paragraph_;
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_document_end() {
    pugi::xml_node body = get_body();
    // Find the last w:p node, not just any last child
    pugi::xml_node last_para;
    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        last_para = para;
    }
    current_paragraph_ = last_para;
    current_node_ = current_paragraph_;
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_paragraph(size_t index) {
    move_to_paragraph(index, 0);
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_paragraph(size_t paragraph_index, size_t character_index) {
    pugi::xml_node body = get_body();
    size_t count = 0;

    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (count == paragraph_index) {
            current_paragraph_ = para;
            // Find run containing the character index
            size_t char_count = 0;
            for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
                pugi::xml_node t = run.child("w:t");
                if (t) {
                    size_t text_len = std::strlen(t.text().get());
                    if (char_count + text_len >= character_index) {
                        current_node_ = run;
                        return *this;
                    }
                    char_count += text_len;
                }
            }
            current_node_ = para;
            return *this;
        }
        count++;
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_section(size_t index) {
    auto sections = doc_->get_sections();
    if (index >= sections.get_count()) return *this;

    auto body = sections[index]->get_body();
    if (!body) return *this;

    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) return *this;

    pugi::xml_node xml_body = doc_xml->child("w:document").child("w:body");
    size_t sect_count = 0;
    for (pugi::xml_node para = xml_body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (sect_count == index) {
            current_paragraph_ = para;
            current_node_ = para;
            target_xml_doc_ = doc_xml;
            return *this;
        }
        // Check if this paragraph ends a section
        if (para.child("w:sectPr")) {
            sect_count++;
            if (sect_count == index) {
                pugi::xml_node next = para.next_sibling();
                if (next && std::strcmp(next.name(), "w:p") == 0) {
                    current_paragraph_ = next;
                    current_node_ = next;
                } else {
                    current_paragraph_ = para;
                    current_node_ = para;
                }
                target_xml_doc_ = doc_xml;
                return *this;
            }
        }
    }
    // If no section breaks found, just move to first paragraph
    if (index == 0) {
        current_paragraph_ = xml_body.child("w:p");
        current_node_ = current_paragraph_;
        target_xml_doc_ = doc_xml;
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_bookmark(const std::string& name) {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) return *this;

    for (pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
         para; para = para.next_sibling("w:p")) {
        for (pugi::xml_node bm = para.child("w:bookmarkStart"); bm;
             bm = bm.next_sibling("w:bookmarkStart")) {
            pugi::xml_attribute name_attr = bm.attribute("w:name");
            if (name_attr && name_attr.value() == name) {
                target_xml_doc_ = doc_xml;
                current_paragraph_ = para;
                current_node_ = bm;
                return *this;
            }
        }
        // Also search inside runs
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            for (pugi::xml_node bm = run.child("w:bookmarkStart"); bm;
                 bm = bm.next_sibling("w:bookmarkStart")) {
                pugi::xml_attribute name_attr = bm.attribute("w:name");
                if (name_attr && name_attr.value() == name) {
                    target_xml_doc_ = doc_xml;
                    current_paragraph_ = para;
                    current_node_ = run;
                    return *this;
                }
            }
        }
    }
    return *this;
}

bool DocumentBuilder::move_to_merge_field(const std::string& field_name) {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) return false;

    std::string target_code = "MERGEFIELD " + field_name;

    for (pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
         para; para = para.next_sibling("w:p")) {
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            pugi::xml_node fldChar = run.child("w:fldChar");
            if (fldChar && std::strcmp(fldChar.attribute("w:fldCharType").value(), "begin") == 0) {
                // Found start of a field, look for instrText in following runs
                for (pugi::xml_node instr_run = run.next_sibling("w:r"); instr_run;
                     instr_run = instr_run.next_sibling("w:r")) {
                    pugi::xml_node instrText = instr_run.child("w:instrText");
                    if (instrText) {
                        std::string code = instrText.text().get();
                        // Trim leading space if present
                        size_t start = 0;
                        while (start < code.size() && std::isspace(code[start])) start++;
                        std::string trimmed = code.substr(start);
                        if (trimmed.find(target_code) == 0) {
                            target_xml_doc_ = doc_xml;
                            current_paragraph_ = para;
                            current_node_ = run;
                            return true;
                        }
                    }
                    pugi::xml_node end_fldChar = instr_run.child("w:fldChar");
                    if (end_fldChar && std::strcmp(end_fldChar.attribute("w:fldCharType").value(), "separate") == 0) {
                        break;
                    }
                }
            }
        }
    }
    return false;
}

DocumentBuilder& DocumentBuilder::move_to_cell(size_t table_index, size_t row_index, size_t cell_index) {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) return *this;

    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    size_t t_idx = 0;
    for (pugi::xml_node tbl = body.child("w:tbl"); tbl; tbl = tbl.next_sibling("w:tbl")) {
        if (t_idx == table_index) {
            size_t r_idx = 0;
            for (pugi::xml_node tr = tbl.child("w:tr"); tr; tr = tr.next_sibling("w:tr")) {
                if (r_idx == row_index) {
                    size_t c_idx = 0;
                    for (pugi::xml_node tc = tr.child("w:tc"); tc; tc = tc.next_sibling("w:tc")) {
                        if (c_idx == cell_index) {
                            target_xml_doc_ = doc_xml;
                            current_table_ = tbl;
                            current_row_ = tr;
                            current_cell_ = tc;
                            current_paragraph_ = tc.child("w:p");
                            if (!current_paragraph_) {
                                current_paragraph_ = tc.append_child("w:p");
                            }
                            current_node_ = current_paragraph_;
                            in_table_ = true;
                            return *this;
                        }
                        ++c_idx;
                    }
                }
                ++r_idx;
            }
        }
        ++t_idx;
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_header_footer(HeaderFooterType type) {
    auto sect = doc_->get_first_section();
    if (!sect) return *this;

    std::shared_ptr<HeaderFooter> hf;
    if (sect->has_header(type)) {
        hf = sect->get_header(type);
    } else {
        hf = sect->add_header(type);
    }
    if (!hf) return *this;

    // Find the header XML document via relationship
    auto header_names = doc_->get_header_names();
    for (size_t i = 0; i < header_names.size(); ++i) {
        // This is a simplified match; in practice we'd match by relationship
        pugi::xml_document* header_doc = doc_->get_header(static_cast<int>(i));
        if (header_doc) {
            target_xml_doc_ = header_doc;
            pugi::xml_node hdr = header_doc->child("w:hdr");
            current_paragraph_ = hdr.child("w:p");
            if (!current_paragraph_) {
                current_paragraph_ = hdr.append_child("w:p");
            }
            current_node_ = current_paragraph_;
            current_table_ = pugi::xml_node();
            current_row_ = pugi::xml_node();
            current_cell_ = pugi::xml_node();
            in_table_ = false;
            return *this;
        }
    }
    return *this;
}

// Text Insertion
DocumentBuilder& DocumentBuilder::write(const std::string& text) {
    ensure_paragraph();

    pugi::xml_node run = current_paragraph_.append_child("w:r");
    apply_formatting(run);

    pugi::xml_node t = run.append_child("w:t");
    t.text().set(text.c_str());

    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return *this;
}

DocumentBuilder& DocumentBuilder::writeln(const std::string& text) {
    write(text);
    insert_break(BreakType::ParagraphBreak);
    return *this;
}

DocumentBuilder& DocumentBuilder::writeln() {
    insert_break(BreakType::ParagraphBreak);
    return *this;
}

Paragraph* DocumentBuilder::insert_paragraph() {
    pugi::xml_node body = get_body();
    pugi::xml_node sectPr = body.child("w:sectPr");
    if (sectPr) {
        current_paragraph_ = body.insert_child_before("w:p", sectPr);
    } else {
        current_paragraph_ = body.append_child("w:p");
    }
    current_node_ = current_paragraph_;

    // Return pointer to a new Paragraph object
    // Note: This creates a memory management issue - needs proper handling
    static Paragraph* para = nullptr;
    if (para) delete para;
    para = new Paragraph();
    para->set_current(current_paragraph_);
    return para;
}

DocumentBuilder& DocumentBuilder::insert_break() {
    insert_break(BreakType::PageBreak);
    return *this;
}

DocumentBuilder& DocumentBuilder::insert_break(BreakType break_type) {
    switch (break_type) {
        case BreakType::ParagraphBreak: {
            pugi::xml_node body = get_body();
            pugi::xml_node sectPr = body.child("w:sectPr");
            if (sectPr) {
                current_paragraph_ = body.insert_child_before("w:p", sectPr);
            } else {
                current_paragraph_ = body.append_child("w:p");
            }
            current_node_ = current_paragraph_;
            break;
        }
        case BreakType::PageBreak:
        case BreakType::ColumnBreak:
        case BreakType::SectionBreakNextPage:
        case BreakType::SectionBreakContinuous:
        case BreakType::SectionBreakEvenPage:
        case BreakType::SectionBreakOddPage: {
            ensure_paragraph();
            pugi::xml_node run = current_paragraph_.append_child("w:r");
            pugi::xml_node br = run.append_child("w:br");
            if (break_type == BreakType::PageBreak) {
                br.append_attribute("w:type").set_value("page");
            } else if (break_type == BreakType::ColumnBreak) {
                br.append_attribute("w:type").set_value("column");
            } else {
                const char* type_val = nullptr;
                switch (break_type) {
                    case BreakType::SectionBreakNextPage:     type_val = "nextPage"; break;
                    case BreakType::SectionBreakContinuous:   type_val = "continuous"; break;
                    case BreakType::SectionBreakEvenPage:     type_val = "evenPage"; break;
                    case BreakType::SectionBreakOddPage:      type_val = "oddPage"; break;
                    default: break;
                }
                if (type_val) {
                    br.append_attribute("w:type").set_value(type_val);
                }
            }
            break;
        }
        case BreakType::LineBreak: {
            ensure_paragraph();
            pugi::xml_node run = current_paragraph_.append_child("w:r");
            run.append_child("w:br");
            break;
        }
    }
    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return *this;
}

std::shared_ptr<Footnote> DocumentBuilder::insert_footnote(FootnoteType type, const std::string& text) {
    return insert_footnote(type, text, "");
}

std::shared_ptr<Footnote> DocumentBuilder::insert_footnote(FootnoteType type, const std::string& text,
                                                               const std::string& reference_mark) {
    ensure_paragraph();

    int id = doc_->get_next_comment_id();  // Reuse comment ID counter for footnotes

    auto footnote = std::make_shared<Footnote>(doc_, type);
    footnote->set_id(id);
    if (!reference_mark.empty()) {
        footnote->set_reference_mark(reference_mark);
    }
    if (!text.empty()) {
        footnote->set_text(text);
    }

    // Insert footnote reference in current paragraph
    pugi::xml_node run = current_paragraph_.append_child("w:r");
    pugi::xml_node ref = run.append_child("w:footnoteReference");
    ref.append_attribute("w:id").set_value(id);
    if (!reference_mark.empty()) {
        ref.append_attribute("w:customMarkFollows").set_value("1");
        pugi::xml_node mark_run = current_paragraph_.append_child("w:r");
        pugi::xml_node mark_t = mark_run.append_child("w:t");
        mark_t.text().set(reference_mark.c_str());
    }

    // Ensure footnotes/endnotes XML exists
    const char* xml_path = (type == FootnoteType::Endnote) ? "word/endnotes.xml" : "word/footnotes.xml";
    const char* rel_type = (type == FootnoteType::Endnote)
        ? "http://schemas.openxmlformats.org/officeDocument/2006/relationships/endnotes"
        : "http://schemas.openxmlformats.org/officeDocument/2006/relationships/footnotes";
    const char* content_type = (type == FootnoteType::Endnote)
        ? "application/vnd.openxmlformats-officedocument.wordprocessingml.endnotes+xml"
        : "application/vnd.openxmlformats-officedocument.wordprocessingml.footnotes+xml";

    pugi::xml_document* notes_xml = doc_->get_xml_part(xml_path);
    if (!notes_xml) {
        notes_xml = &doc_->create_xml_part(xml_path);
        auto root = notes_xml->prepend_child(type == FootnoteType::Endnote ? "w:endnotes" : "w:footnotes");
        root.append_attribute("xmlns:w")
            .set_value("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r")
            .set_value("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    }

    // Add separator notes if not present
    auto root = notes_xml->child(type == FootnoteType::Endnote ? "w:endnotes" : "w:footnotes");
    if (root) {
        // Check if separator exists
        bool has_sep = false;
        for (auto child = root.child(type == FootnoteType::Endnote ? "w:endnote" : "w:footnote");
             child; child = child.next_sibling(type == FootnoteType::Endnote ? "w:endnote" : "w:footnote")) {
            int note_id = child.attribute("w:id").as_int();
            if (note_id == -1) {
                has_sep = true;
                break;
            }
        }
        if (!has_sep) {
            auto sep = root.prepend_child(type == FootnoteType::Endnote ? "w:endnote" : "w:footnote");
            sep.append_attribute("w:id").set_value(-1);
            sep.append_attribute("w:type").set_value("separator");
            auto sep_para = sep.append_child("w:p");
            auto sep_run = sep_para.append_child("w:r");
            sep_run.append_child("w:separator");

            auto cont_sep = root.prepend_child(type == FootnoteType::Endnote ? "w:endnote" : "w:footnote");
            cont_sep.append_attribute("w:id").set_value(0);
            cont_sep.append_attribute("w:type").set_value("continuationSeparator");
            auto cont_para = cont_sep.append_child("w:p");
            auto cont_run = cont_para.append_child("w:r");
            cont_run.append_child("w:continuationSeparator");
        }
    }

    // Add the footnote content
    auto note_xml = root.append_child(type == FootnoteType::Endnote ? "w:endnote" : "w:footnote");
    note_xml.append_attribute("w:id").set_value(id);
    if (!reference_mark.empty()) {
        note_xml.append_attribute("w:customMarkFollows").set_value("1");
    }

    for (const auto& child : footnote->get_children()) {
        if (child->node_type() == NodeType::Paragraph) {
            auto para_xml = note_xml.append_child("w:p");
            auto* para = dynamic_cast<Paragraph*>(child.get());
            if (para) {
                for (const auto& run_child : para->get_children()) {
                    if (run_child->node_type() == NodeType::Run) {
                        auto run_xml = para_xml.append_child("w:r");
                        auto* run = dynamic_cast<Run*>(run_child.get());
                        if (run) {
                            auto t = run_xml.append_child("w:t");
                            t.text().set(run->get_text().c_str());
                        }
                    }
                }
            }
        }
    }

    doc_->add_relationship("word/_rels/document.xml.rels", rel_type,
                            type == FootnoteType::Endnote ? "endnotes.xml" : "footnotes.xml");
    doc_->add_content_type_override(std::string("/") + xml_path, content_type);
    doc_->mark_modified(xml_path);
    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);

    return footnote;
}

namespace {

std::string field_type_to_code(FieldType type) {
    switch (type) {
        case FieldType::Page:       return "PAGE";
        case FieldType::NumPages:   return "NUMPAGES";
        case FieldType::Date:       return "DATE";
        case FieldType::Time:       return "TIME";
        case FieldType::CreateDate: return "CREATEDATE";
        case FieldType::SaveDate:   return "SAVEDATE";
        case FieldType::Author:     return "AUTHOR";
        case FieldType::Title:      return "TITLE";
        case FieldType::Subject:    return "SUBJECT";
        case FieldType::Keywords:   return "KEYWORDS";
        case FieldType::FileName:   return "FILENAME";
        case FieldType::FileSize:   return "FILESIZE";
        case FieldType::NumWords:   return "NUMWORDS";
        case FieldType::NumChars:   return "NUMCHARS";
        case FieldType::Ref:        return "REF";
        case FieldType::PageRef:    return "PAGEREF";
        case FieldType::Formula:    return "=";
        default:                    return "";
    }
}

std::string field_type_to_result(FieldType type) {
    switch (type) {
        case FieldType::Page:       return "1";
        case FieldType::NumPages:   return "1";
        case FieldType::Date:       return "";
        case FieldType::Time:       return "";
        case FieldType::CreateDate: return "";
        case FieldType::SaveDate:   return "";
        case FieldType::Author:     return "";
        case FieldType::Title:      return "";
        case FieldType::Subject:    return "";
        case FieldType::Keywords:   return "";
        case FieldType::FileName:   return "";
        case FieldType::FileSize:   return "0";
        case FieldType::NumWords:   return "0";
        case FieldType::NumChars:   return "0";
        default:                    return "";
    }
}

} // anonymous namespace

std::shared_ptr<Field> DocumentBuilder::insert_field(FieldType field_type, bool /*update_field*/) {
    std::string code = field_type_to_code(field_type);
    if (code.empty()) {
        code = "PAGE";
    }
    return insert_field(code, field_type_to_result(field_type));
}

std::shared_ptr<Field> DocumentBuilder::insert_field(const std::string& field_code) {
    return insert_field(field_code, "");
}

std::shared_ptr<Field> DocumentBuilder::insert_field(const std::string& field_code,
                                                      const std::string& field_value) {
    ensure_paragraph();

    auto field = std::make_shared<Field>(doc_, FieldType::Unknown);
    field->set_field_code(field_code);
    field->set_result(field_value);

    pugi::xml_node run_start = current_paragraph_.append_child("w:r");
    pugi::xml_node fldChar_start = run_start.append_child("w:fldChar");
    fldChar_start.append_attribute("w:fldCharType").set_value("begin");

    if (!field_code.empty()) {
        pugi::xml_node run_instr = current_paragraph_.append_child("w:r");
        pugi::xml_node instrText = run_instr.append_child("w:instrText");
        instrText.append_attribute("xml:space").set_value("preserve");
        instrText.text().set((" " + field_code + " \\* MERGEFORMAT").c_str());
    }

    pugi::xml_node run_sep = current_paragraph_.append_child("w:r");
    pugi::xml_node fldChar_sep = run_sep.append_child("w:fldChar");
    fldChar_sep.append_attribute("w:fldCharType").set_value("separate");

    if (!field_value.empty()) {
        pugi::xml_node run_result = current_paragraph_.append_child("w:r");
        pugi::xml_node t = run_result.append_child("w:t");
        t.text().set(field_value.c_str());
    }

    pugi::xml_node run_end = current_paragraph_.append_child("w:r");
    pugi::xml_node fldChar_end = run_end.append_child("w:fldChar");
    fldChar_end.append_attribute("w:fldCharType").set_value("end");

    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return field;
}

std::shared_ptr<Field> DocumentBuilder::insert_page_number() {
    return insert_field(FieldType::Page);
}

std::shared_ptr<Field> DocumentBuilder::insert_num_pages() {
    return insert_field(FieldType::NumPages);
}

std::shared_ptr<Field> DocumentBuilder::insert_date() {
    return insert_field(FieldType::Date);
}

std::shared_ptr<Field> DocumentBuilder::insert_time() {
    return insert_field(FieldType::Time);
}

std::shared_ptr<Field> DocumentBuilder::insert_merge_field(const std::string& field_name) {
    return insert_field("MERGEFIELD " + field_name);
}

std::shared_ptr<Field> DocumentBuilder::insert_table_of_contents(const std::string& switches) {
    ensure_paragraph();

    std::string toc_code = "TOC";
    if (!switches.empty()) {
        toc_code += " " + switches;
    }

    auto field = std::make_shared<Field>(doc_, FieldType::Unknown);
    field->set_field_code(toc_code);
    field->set_result("\nClick here to update table of contents.\n");

    pugi::xml_node run_start = current_paragraph_.append_child("w:r");
    pugi::xml_node fldChar_start = run_start.append_child("w:fldChar");
    fldChar_start.append_attribute("w:fldCharType").set_value("begin");

    pugi::xml_node run_instr = current_paragraph_.append_child("w:r");
    pugi::xml_node instrText = run_instr.append_child("w:instrText");
    instrText.append_attribute("xml:space").set_value("preserve");
    instrText.text().set((" " + toc_code + " \\h").c_str());

    pugi::xml_node run_sep = current_paragraph_.append_child("w:r");
    pugi::xml_node fldChar_sep = run_sep.append_child("w:fldChar");
    fldChar_sep.append_attribute("w:fldCharType").set_value("separate");

    pugi::xml_node run_result = current_paragraph_.append_child("w:r");
    pugi::xml_node t = run_result.append_child("w:t");
    t.text().set(field->get_result().c_str());

    pugi::xml_node run_end = current_paragraph_.append_child("w:r");
    pugi::xml_node fldChar_end = run_end.append_child("w:fldChar");
    fldChar_end.append_attribute("w:fldCharType").set_value("end");

    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return field;
}

// Formatting
DocumentBuilder& DocumentBuilder::set_bold(bool value) { format_.bold = value; return *this; }
DocumentBuilder& DocumentBuilder::set_italic(bool value) { format_.italic = value; return *this; }
DocumentBuilder& DocumentBuilder::set_underline(bool value) { format_.underline = value; return *this; }
DocumentBuilder& DocumentBuilder::set_strikethrough(bool value) { format_.strikethrough = value; return *this; }
DocumentBuilder& DocumentBuilder::set_font_name(const std::string& name) { format_.font_name = name; return *this; }
DocumentBuilder& DocumentBuilder::set_font_size(int size) { format_.font_size = size; return *this; }
DocumentBuilder& DocumentBuilder::set_color(const std::string& color_hex) { format_.color = color_hex; return *this; }
DocumentBuilder& DocumentBuilder::set_alignment(const std::string& alignment) { format_.alignment = alignment; return *this; }

DocumentBuilder& DocumentBuilder::clear_formatting() {
    format_ = FormattingState();
    return *this;
}

// Table Building
DocumentBuilder& DocumentBuilder::start_table() {
    pugi::xml_node body = get_body();
    pugi::xml_node sectPr = body.child("w:sectPr");
    if (sectPr) {
        current_table_ = body.insert_child_before("w:tbl", sectPr);
    } else {
        current_table_ = body.append_child("w:tbl");
    }
    in_table_ = true;

    // Add table properties
    pugi::xml_node tblPr = current_table_.append_child("w:tblPr");
    pugi::xml_node tblW = tblPr.append_child("w:tblW");
    tblW.append_attribute("w:w").set_value("5000");
    tblW.append_attribute("w:type").set_value("pct");
    return *this;
}

DocumentBuilder& DocumentBuilder::end_table() {
    in_table_ = false;
    current_table_ = pugi::xml_node();
    current_row_ = pugi::xml_node();
    current_cell_ = pugi::xml_node();
    return *this;
}

DocumentBuilder& DocumentBuilder::insert_row() {
    if (!in_table_) {
        return *this;
    }
    current_row_ = current_table_.append_child("w:tr");
    return *this;
}

DocumentBuilder& DocumentBuilder::insert_cell() {
    if (!in_table_ || !current_row_) {
        return *this;
    }
    current_cell_ = current_row_.append_child("w:tc");

    // Add cell properties
    pugi::xml_node tcPr = current_cell_.append_child("w:tcPr");
    pugi::xml_node tcW = tcPr.append_child("w:tcW");
    tcW.append_attribute("w:w").set_value("0");
    tcW.append_attribute("w:type").set_value("auto");

    // Add empty paragraph
    current_paragraph_ = current_cell_.append_child("w:p");
    return *this;
}

DocumentBuilder& DocumentBuilder::end_row() {
    current_row_ = pugi::xml_node();
    current_cell_ = pugi::xml_node();
    return *this;
}

// Hyperlink
DocumentBuilder& DocumentBuilder::insert_hyperlink(const std::string& text, const std::string& url) {
    ensure_paragraph();

    if (!doc_ || url.empty()) {
        write(text);
        return *this;
    }

    // Create relationship for the hyperlink
    std::string rel_id = doc_->find_relationship_id(
        "word/_rels/document.xml.rels", url);
    if (rel_id.empty()) {
        rel_id = doc_->add_relationship(
            "word/_rels/document.xml.rels",
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink",
            url,
            "External");
    }

    // Create hyperlink element
    pugi::xml_node hyperlink = current_paragraph_.append_child("w:hyperlink");
    hyperlink.append_attribute("r:id").set_value(rel_id.c_str());

    // Create run with text and apply current formatting
    pugi::xml_node run = hyperlink.append_child("w:r");
    apply_formatting(run);

    pugi::xml_node t = run.append_child("w:t");
    t.text().set(text.c_str());
    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return *this;
}

// Bookmark
DocumentBuilder& DocumentBuilder::start_bookmark(const std::string& name) {
    if (!doc_) {
        return *this;
    }

    ensure_paragraph();

    // Generate unique bookmark ID
    int bookmark_id = doc_->generate_unique_bookmark_id();

    // Store bookmark ID for later matching with end_bookmark
    bookmark_stack_[name] = bookmark_id;

    // Create bookmarkStart element
    pugi::xml_node bookmark_start = current_paragraph_.append_child("w:bookmarkStart");
    bookmark_start.append_attribute("w:id").set_value(bookmark_id);
    bookmark_start.append_attribute("w:name").set_value(name.c_str());
    return *this;
}

DocumentBuilder& DocumentBuilder::end_bookmark(const std::string& name) {
    if (!doc_) {
        return *this;
    }

    ensure_paragraph();

    // Find the bookmark ID from the stack
    auto it = bookmark_stack_.find(name);
    if (it == bookmark_stack_.end()) {
        // No matching start_bookmark called
        return *this;
    }

    int bookmark_id = it->second;
    bookmark_stack_.erase(it);

    // Create bookmarkEnd element
    pugi::xml_node bookmark_end = current_paragraph_.append_child("w:bookmarkEnd");
    bookmark_end.append_attribute("w:id").set_value(bookmark_id);
    return *this;
}

// Image
bool DocumentBuilder::insert_image(const std::string& image_path, double width, double height) {
    if (!doc_) {
        return false;
    }

    namespace fs = std::filesystem;
    if (!fs::exists(image_path)) {
        return false;
    }

    // Detect image size if not provided
    ImageSize size;
    if (width <= 0 || height <= 0) {
        if (!detect_image_size(image_path, size)) {
            return false;
        }
    } else {
        size = ImageSize(width, height);
    }

    // Add media and get relationship
    std::string rel_id = doc_->add_media_with_rel(image_path, nullptr);
    if (rel_id.empty()) {
        return false;
    }

    ensure_paragraph();

    // Create run with drawing
    pugi::xml_node run = current_paragraph_.append_child("w:r");
    pugi::xml_node drawing = run.append_child("w:drawing");

    // Use inline image (simple, in-line with text)
    pugi::xml_node inline_node = drawing.append_child("wp:inline");
    inline_node.append_attribute("distT").set_value(0);
    inline_node.append_attribute("distB").set_value(0);
    inline_node.append_attribute("distL").set_value(0);
    inline_node.append_attribute("distR").set_value(0);

    pugi::xml_node extent = inline_node.append_child("wp:extent");
    extent.append_attribute("cx").set_value(size.width_emu());
    extent.append_attribute("cy").set_value(size.height_emu());

    pugi::xml_node docPr = inline_node.append_child("wp:docPr");
    static int image_id_counter = 1;
    docPr.append_attribute("id").set_value(image_id_counter++);
    docPr.append_attribute("name").set_value("Picture");

    pugi::xml_node graphic = inline_node.append_child("a:graphic");
    graphic.append_attribute("xmlns:a").set_value(
        "http://schemas.openxmlformats.org/drawingml/2006/main");

    pugi::xml_node graphic_data = graphic.append_child("a:graphicData");
    graphic_data.append_attribute("uri").set_value(
        "http://schemas.openxmlformats.org/drawingml/2006/picture");

    pugi::xml_node pic = graphic_data.append_child("pic:pic");
    pic.append_attribute("xmlns:pic").set_value(
        "http://schemas.openxmlformats.org/drawingml/2006/picture");

    pugi::xml_node nvPicPr = pic.append_child("pic:nvPicPr");
    pugi::xml_node cnvPr = nvPicPr.append_child("pic:cNvPr");
    cnvPr.append_attribute("id").set_value(0);
    cnvPr.append_attribute("name").set_value(image_path.c_str());
    pugi::xml_node cnvPicPr = nvPicPr.append_child("pic:cNvPicPr");

    pugi::xml_node blipFill = pic.append_child("pic:blipFill");
    pugi::xml_node blip = blipFill.append_child("a:blip");
    blip.append_attribute("r:embed").set_value(rel_id.c_str());
    pugi::xml_node stretch = blipFill.append_child("a:stretch");
    stretch.append_child("a:fillRect");

    pugi::xml_node spPr = pic.append_child("pic:spPr");
    pugi::xml_node xfrm = spPr.append_child("a:xfrm");
    pugi::xml_node ext = xfrm.append_child("a:ext");
    ext.append_attribute("cx").set_value(size.width_emu());
    ext.append_attribute("cy").set_value(size.height_emu());
    pugi::xml_node prstGeom = spPr.append_child("a:prstGeom");
    prstGeom.append_attribute("prst").set_value("rect");
    prstGeom.append_child("a:avLst");

    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return true;
}

// Form Fields
static const char* text_form_field_type_to_string(TextFormFieldType type) {
    switch (type) {
        case TextFormFieldType::Number:       return "number";
        case TextFormFieldType::Date:         return "date";
        case TextFormFieldType::CurrentDate:  return "currentDate";
        case TextFormFieldType::CurrentTime:  return "currentTime";
        case TextFormFieldType::Calculated:   return "calculated";
        default:                              return "regular";
    }
}

static void append_ffdata_text_input(pugi::xml_node fld_char,
                                      const FormField& field) {
    auto ff_data = fld_char.append_child("w:ffData");
    if (!field.get_name().empty()) {
        ff_data.append_child("w:name").append_attribute("w:val").set_value(
            field.get_name().c_str());
    }
    ff_data.append_child("w:enabled").append_attribute("w:val").set_value(
        field.get_enabled() ? "1" : "0");
    ff_data.append_child("w:calcOnExit").append_attribute("w:val").set_value(
        field.get_calculate_on_exit() ? "1" : "0");

    if (!field.get_status_text().empty()) {
        ff_data.append_child("w:statusText").append_attribute("w:val").set_value(
            field.get_status_text().c_str());
    }
    if (!field.get_help_text().empty()) {
        ff_data.append_child("w:helpText").append_attribute("w:val").set_value(
            field.get_help_text().c_str());
    }
    if (!field.get_entry_macro().empty()) {
        ff_data.append_child("w:entryMacro").append_attribute("w:val").set_value(
            field.get_entry_macro().c_str());
    }
    if (!field.get_exit_macro().empty()) {
        ff_data.append_child("w:exitMacro").append_attribute("w:val").set_value(
            field.get_exit_macro().c_str());
    }

    auto text_input = ff_data.append_child("w:textInput");
    text_input.append_child("w:type").append_attribute("w:val").set_value(
        text_form_field_type_to_string(field.get_text_input_type()));
    if (!field.get_text_input_default().empty()) {
        text_input.append_child("w:default").append_attribute("w:val").set_value(
            field.get_text_input_default().c_str());
    }
    if (field.get_max_length() > 0) {
        text_input.append_child("w:maxLength").append_attribute("w:val").set_value(
            field.get_max_length());
    }
    if (!field.get_text_input_format().empty()) {
        text_input.append_child("w:format").append_attribute("w:val").set_value(
            field.get_text_input_format().c_str());
    }
}

static void append_ffdata_check_box(pugi::xml_node fld_char,
                                     const FormField& field) {
    auto ff_data = fld_char.append_child("w:ffData");
    if (!field.get_name().empty()) {
        ff_data.append_child("w:name").append_attribute("w:val").set_value(
            field.get_name().c_str());
    }
    ff_data.append_child("w:enabled").append_attribute("w:val").set_value(
        field.get_enabled() ? "1" : "0");
    ff_data.append_child("w:calcOnExit").append_attribute("w:val").set_value(
        field.get_calculate_on_exit() ? "1" : "0");

    auto check_box = ff_data.append_child("w:checkBox");
    if (field.get_is_check_box_exact_size() && field.get_check_box_size() > 0) {
        auto size = check_box.append_child("w:size");
        size.append_attribute("w:val").set_value(
            static_cast<int>(field.get_check_box_size() * 2)); // half-points
    } else {
        check_box.append_child("w:sizeAuto");
    }
    check_box.append_child("w:default").append_attribute("w:val").set_value(
        field.get_default_value() ? "1" : "0");
    check_box.append_child("w:checked").append_attribute("w:val").set_value(
        field.get_checked() ? "1" : "0");
}

static void append_ffdata_drop_down(pugi::xml_node fld_char,
                                     const FormField& field) {
    auto ff_data = fld_char.append_child("w:ffData");
    if (!field.get_name().empty()) {
        ff_data.append_child("w:name").append_attribute("w:val").set_value(
            field.get_name().c_str());
    }
    ff_data.append_child("w:enabled").append_attribute("w:val").set_value(
        field.get_enabled() ? "1" : "0");
    ff_data.append_child("w:calcOnExit").append_attribute("w:val").set_value(
        field.get_calculate_on_exit() ? "1" : "0");

    auto dd_list = ff_data.append_child("w:ddList");
    for (const auto& item : field.get_drop_down_items()) {
        dd_list.append_child("w:listEntry").append_attribute("w:val").set_value(
            item.c_str());
    }
    if (field.get_drop_down_selected_index() >= 0) {
        dd_list.append_child("w:default").append_attribute("w:val").set_value(
            field.get_drop_down_selected_index());
    }
}

std::shared_ptr<FormField> DocumentBuilder::insert_form_field_impl(
    const std::shared_ptr<FormField>& field) {
    if (!doc_) return field;

    ensure_paragraph();
    pugi::xml_node para = current_paragraph_;

    int bookmark_id = 0;
    if (!field->get_name().empty()) {
        bookmark_id = doc_->generate_unique_bookmark_id();
        // Create bookmark start
        pugi::xml_node bm_start = para.append_child("w:bookmarkStart");
        bm_start.append_attribute("w:id").set_value(bookmark_id);
        bm_start.append_attribute("w:name").set_value(field->get_name().c_str());
    }

    // Begin fldChar with ffData
    pugi::xml_node begin_run = para.append_child("w:r");
    pugi::xml_node fld_char = begin_run.append_child("w:fldChar");
    fld_char.append_attribute("w:fldCharType").set_value("begin");

    switch (field->get_form_field_type()) {
        case FormFieldType::TextInput:
            append_ffdata_text_input(fld_char, *field);
            break;
        case FormFieldType::CheckBox:
            append_ffdata_check_box(fld_char, *field);
            break;
        case FormFieldType::ComboBox:
            append_ffdata_drop_down(fld_char, *field);
            break;
    }

    // Instruction text
    pugi::xml_node instr_run = para.append_child("w:r");
    pugi::xml_node instr_text = instr_run.append_child("w:instrText");
    const char* instr = "FORMTEXT";
    if (field->get_form_field_type() == FormFieldType::CheckBox) {
        instr = "FORMCHECKBOX";
    } else if (field->get_form_field_type() == FormFieldType::ComboBox) {
        instr = "FORMDROPDOWN";
    }
    instr_text.text().set(instr);

    // Separate
    pugi::xml_node sep_run = para.append_child("w:r");
    sep_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("separate");

    // Result
    std::string result = field->get_result();
    if (result.empty()) {
        if (field->get_form_field_type() == FormFieldType::CheckBox) {
            result = field->get_checked() ? "\u2611" : "\u2610"; // ballot box symbols
        } else if (field->get_form_field_type() == FormFieldType::ComboBox) {
            const auto& items = field->get_drop_down_items();
            int idx = field->get_drop_down_selected_index();
            if (idx >= 0 && idx < static_cast<int>(items.size())) {
                result = items[idx];
            }
        }
    }
    if (!result.empty()) {
        pugi::xml_node res_run = para.append_child("w:r");
        pugi::xml_node text_node = res_run.append_child("w:t");
        text_node.text().set(result.c_str());
    }

    // End
    pugi::xml_node end_run = para.append_child("w:r");
    end_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("end");

    if (bookmark_id != 0) {
        pugi::xml_node bm_end = para.append_child("w:bookmarkEnd");
        bm_end.append_attribute("w:id").set_value(bookmark_id);
    }

    if (doc_) doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return field;
}

std::shared_ptr<FormField> DocumentBuilder::insert_text_input(
    const std::string& name,
    TextFormFieldType type,
    const std::string& format,
    const std::string& field_value,
    int max_length) {
    auto field = std::make_shared<FormField>(doc_, FormFieldType::TextInput);
    field->set_name(name);
    field->set_text_input_type(type);
    field->set_text_input_format(format);
    field->set_result(field_value);
    field->set_text_input_default(field_value);
    field->set_max_length(max_length);
    return insert_form_field_impl(field);
}

std::shared_ptr<FormField> DocumentBuilder::insert_check_box(
    const std::string& name,
    bool checked_value,
    int size) {
    return insert_check_box(name, checked_value, checked_value, size);
}

std::shared_ptr<FormField> DocumentBuilder::insert_check_box(
    const std::string& name,
    bool default_value,
    bool checked_value,
    int size) {
    auto field = std::make_shared<FormField>(doc_, FormFieldType::CheckBox);
    field->set_name(name);
    field->set_default_value(default_value);
    field->set_checked(checked_value);
    field->set_result(checked_value ? "\u2611" : "\u2610");
    if (size > 0) {
        field->set_is_check_box_exact_size(true);
        field->set_check_box_size(size);
    }
    return insert_form_field_impl(field);
}

std::shared_ptr<FormField> DocumentBuilder::insert_combo_box(
    const std::string& name,
    const std::vector<std::string>& items,
    int selected_index) {
    auto field = std::make_shared<FormField>(doc_, FormFieldType::ComboBox);
    field->set_name(name);
    field->set_drop_down_items(items);
    field->set_drop_down_selected_index(selected_index);
    if (selected_index >= 0 && selected_index < static_cast<int>(items.size())) {
        field->set_result(items[selected_index]);
    }
    return insert_form_field_impl(field);
}

// ============================================================================
// DocumentSearch Implementation
// ============================================================================

static int count_occurrences(const std::string& text, const std::string& pattern) {
    if (pattern.empty() || text.empty() || pattern.size() > text.size()) {
        return 0;
    }
    int count = 0;
    size_t pos = 0;
    while ((pos = text.find(pattern, pos)) != std::string::npos) {
        ++count;
        pos += pattern.size();
    }
    return count;
}

static std::string replace_all_in_string(std::string text, const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return text;
    }
    size_t pos = 0;
    while ((pos = text.find(old_text, pos)) != std::string::npos) {
        text.replace(pos, old_text.size(), new_text);
        pos += new_text.size();
    }
    return text;
}

std::optional<Range> DocumentSearch::find(Document& doc, const std::string& text) {
    if (text.empty()) {
        return std::nullopt;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        std::string para_text = para->get_text();
        if (para_text.find(text) != std::string::npos) {
            return Range(&doc, para->get_current_node(), para->get_current_node());
        }
    }
    return std::nullopt;
}

std::vector<Range> DocumentSearch::find_all(Document& doc, const std::string& text) {
    std::vector<Range> results;
    if (text.empty()) {
        return results;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        std::string para_text = para->get_text();
        if (para_text.find(text) != std::string::npos) {
            results.emplace_back(&doc, para->get_current_node(), para->get_current_node());
        }
    }
    return results;
}

bool DocumentSearch::replace(Document& doc, const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return false;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        std::string para_text = para->get_text();
        size_t pos = para_text.find(old_text);
        if (pos != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);
            para->set_text(para_text);
            return true;
        }
    }
    return false;
}

int DocumentSearch::replace_all(Document& doc, const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return 0;
    }

    int total = 0;
    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        std::string para_text = para->get_text();
        int count = count_occurrences(para_text, old_text);
        if (count > 0) {
            para->set_text(replace_all_in_string(para_text, old_text, new_text));
            total += count;
        }
    }
    return total;
}

bool DocumentSearch::replace_with_formatting(Document& doc, const std::string& old_text,
                                             const std::string& new_text, formatting_flag flag) {
    if (old_text.empty()) {
        return false;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        std::string para_text = para->get_text();
        size_t pos = para_text.find(old_text);
        if (pos != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);
            para->set_text(para_text);
            if (auto run = para->get_first_run()) {
                if (flag & bold) run->set_bold(true);
                if (flag & italic) run->set_italic(true);
                if (flag & underline) run->set_underline(UnderlineType::Single);
            }
            return true;
        }
    }
    return false;
}

int DocumentSearch::find_and_process(Document& doc, const std::string& pattern, const SearchCallback& callback) {
    if (pattern.empty() || !callback) {
        return 0;
    }

    int count = 0;
    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) continue;
        std::string para_text = para->get_text();
        if (para_text.find(pattern) != std::string::npos) {
            Range range(&doc, para->get_current_node(), para->get_current_node());
            ++count;
            if (!callback(para_text, range)) {
                break;
            }
        }
    }
    return count;
}

// ============================================================================
// Image Utility Functions (P1 Enhancement)
// ============================================================================

namespace {

// PNG signature
bool IsPng(const std::vector<uint8_t>& data) {
    return data.size() >= 8 &&
           data[0] == 0x89 && data[1] == 0x50 &&
           data[2] == 0x4E && data[3] == 0x47 &&
           data[4] == 0x0D && data[5] == 0x0A &&
           data[6] == 0x1A && data[7] == 0x0A;
}

// JPEG signature
bool IsJpeg(const std::vector<uint8_t>& data) {
    return data.size() >= 3 && data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF;
}

// GIF signature
bool IsGif(const std::vector<uint8_t>& data) {
    return data.size() >= 6 &&
           data[0] == 'G' && data[1] == 'I' && data[2] == 'F' &&
           data[3] == '8' && (data[4] == '7' || data[4] == '9') && data[5] == 'a';
}

// BMP signature
bool IsBmp(const std::vector<uint8_t>& data) {
    return data.size() >= 2 && data[0] == 'B' && data[1] == 'M';
}

// Read PNG dimensions from data
bool ReadPngDimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    if (data.size() < 24) return false;
    // IHDR chunk: width at offset 16, height at offset 20 (big-endian)
    width = (data[16] << 24) | (data[17] << 16) | (data[18] << 8) | data[19];
    height = (data[20] << 24) | (data[21] << 16) | (data[22] << 8) | data[23];
    return width > 0 && height > 0 && width < 100000 && height < 100000;
}

// Read JPEG dimensions from data
bool ReadJpegDimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    size_t pos = 2;  // Skip SOI marker
    while (pos < data.size()) {
        if (data[pos] != 0xFF) { pos++; continue; }
        while (pos < data.size() && data[pos] == 0xFF) pos++;
        if (pos >= data.size()) break;
        uint8_t marker = data[pos++];
        if (marker == 0xC0 || marker == 0xC2) {  // SOF0 or SOF2
            if (pos + 9 >= data.size()) return false;
            height = (data[pos + 3] << 8) | data[pos + 4];
            width = (data[pos + 5] << 8) | data[pos + 6];
            return width > 0 && height > 0 && width < 100000 && height < 100000;
        }
        if (marker == 0xD9) break;  // EOI
        if (pos + 2 > data.size()) break;
        uint16_t len = (data[pos] << 8) | data[pos + 1];
        pos += len;
    }
    return false;
}

// Read GIF dimensions from data
bool ReadGifDimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    if (data.size() < 10) return false;
    width = data[6] | (data[7] << 8);
    height = data[8] | (data[9] << 8);
    return width > 0 && height > 0 && width < 100000 && height < 100000;
}

// Read BMP dimensions from data
bool ReadBmpDimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    if (data.size() < 26) return false;
    uint32_t dib_size = *reinterpret_cast<const uint32_t*>(&data[14]);
    if (dib_size == 12) {  // BITMAPCOREHEADER
        if (data.size() < 22) return false;
        width = *reinterpret_cast<const uint16_t*>(&data[18]);
        height = *reinterpret_cast<const uint16_t*>(&data[20]);
    } else {  // BITMAPINFOHEADER or later
        width = *reinterpret_cast<const int32_t*>(&data[18]);
        height = std::abs(*reinterpret_cast<const int32_t*>(&data[22]));
    }
    return width > 0 && height > 0 && width < 100000 && height < 100000;
}

} // anonymous namespace

bool detect_image_size(const std::string& image_path, ImageSize& size) {
    std::ifstream file(image_path, std::ios::binary);
    if (!file) return false;

    // Read file header
    std::vector<uint8_t> data(65536);  // Read up to 64KB
    file.read(reinterpret_cast<char*>(data.data()), data.size());
    size_t bytes_read = file.gcount();
    data.resize(bytes_read);

    return detect_image_size_from_memory(data, size);
}

bool detect_image_size_from_memory(const std::vector<uint8_t>& data, ImageSize& size) {
    if (data.size() < 8) return false;

    int width = 0, height = 0;
    bool success = false;

    if (IsPng(data)) {
        success = ReadPngDimensions(data, width, height);
    } else if (IsJpeg(data)) {
        success = ReadJpegDimensions(data, width, height);
    } else if (IsGif(data)) {
        success = ReadGifDimensions(data, width, height);
    } else if (IsBmp(data)) {
        success = ReadBmpDimensions(data, width, height);
    }

    if (success) {
        // Convert pixels to points (assuming 96 DPI)
        size = ImageSize(width * 72.0 / 96.0, height * 72.0 / 96.0);
    }

    return success;
}

ImageFormatInfo validate_image_format_detailed(const std::string& image_path) {
    ImageFormatInfo info;
    std::ifstream file(image_path, std::ios::binary);

    if (!file) {
        info.error_message = "File not found or cannot be opened";
        return info;
    }

    // Check file size
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0);

    if (file_size > 50 * 1024 * 1024) {
        info.error_message = "File too large (max 50MB)";
        return info;
    }

    // Read header
    std::vector<uint8_t> data(65536);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
    data.resize(file.gcount());

    // Detect format
    if (IsPng(data)) {
        info.format = "PNG";
        info.mime_type = "image/png";
    } else if (IsJpeg(data)) {
        info.format = "JPEG";
        info.mime_type = "image/jpeg";
    } else if (IsGif(data)) {
        info.format = "GIF";
        info.mime_type = "image/gif";
    } else if (IsBmp(data)) {
        info.format = "BMP";
        info.mime_type = "image/bmp";
    } else {
        info.error_message = "Unknown or unsupported image format";
        return info;
    }

    // Try to read dimensions
    ImageSize size;
    if (detect_image_size_from_memory(data, size)) {
        info.width = static_cast<int>(size.width_pt * 96.0 / 72.0);
        info.height = static_cast<int>(size.height_pt * 96.0 / 72.0);
        info.is_valid = true;
    } else {
        info.error_message = "Cannot read image dimensions, file may be corrupted";
    }

    return info;
}

ImageFormatInfo validate_image_format_from_memory(const std::vector<uint8_t>& data) {
    ImageFormatInfo info;

    if (data.size() < 8) {
        info.error_message = "Data too small to be a valid image";
        return info;
    }

    // Detect format
    if (IsPng(data)) {
        info.format = "PNG";
        info.mime_type = "image/png";
    } else if (IsJpeg(data)) {
        info.format = "JPEG";
        info.mime_type = "image/jpeg";
    } else if (IsGif(data)) {
        info.format = "GIF";
        info.mime_type = "image/gif";
    } else if (IsBmp(data)) {
        info.format = "BMP";
        info.mime_type = "image/bmp";
    } else {
        info.error_message = "Unknown or unsupported image format";
        return info;
    }

    // Try to read dimensions
    ImageSize size;
    if (detect_image_size_from_memory(data, size)) {
        info.width = static_cast<int>(size.width_pt * 96.0 / 72.0);
        info.height = static_cast<int>(size.height_pt * 96.0 / 72.0);
        info.is_valid = true;
    } else {
        info.error_message = "Cannot read image dimensions, data may be corrupted";
    }

    return info;
}

} // namespace cdocx

