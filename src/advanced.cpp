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
#include <algorithm>
#include <cctype>
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
    
    // Find all bookmarkStart and bookmarkEnd elements
    // Use ID-based matching for accurate pairing
    std::map<std::string, pugi::xml_node> starts;  // id -> node
    std::map<std::string, std::string> id_to_name; // id -> name
    std::map<std::string, pugi::xml_node> ends;    // id -> node
    
    for (pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
         para; para = para.next_sibling("w:p")) {
        for (pugi::xml_node child = para.first_child(); child; child = child.next_sibling()) {
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
        }
    }
    
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
    // TODO: Implement bookmark creation
    // Insert bookmarkStart and bookmarkEnd at paragraph
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
    // TODO: Implement range text replacement
    return false;
}

int Range::replace_all(const std::string& old_text, const std::string& new_text) {
    // TODO: Implement range text replacement
    return 0;
}

bool Range::delete_content() {
    // TODO: Implement range content deletion
    return false;
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
    // TODO: Implement row insertion
    return false;
}

bool TableOperations::append_row(Table& table) {
    // TODO: Implement row append
    return false;
}

bool TableOperations::delete_row(Table& table, size_t index) {
    // TODO: Implement row deletion
    return false;
}

bool TableOperations::insert_cell(TableRow& row, size_t index) {
    // TODO: Implement cell insertion
    return false;
}

bool TableOperations::delete_cell(TableRow& row, size_t index) {
    // TODO: Implement cell deletion
    return false;
}

size_t TableOperations::get_row_count(const Table& table) {
    // TODO: Implement row counting
    return 0;
}

size_t TableOperations::get_column_count(const Table& table) {
    // TODO: Implement column counting
    return 0;
}

bool TableOperations::merge_cells_horizontal(TableRow& row, size_t start, size_t end) {
    // TODO: Implement cell merging
    return false;
}

bool TableOperations::set_cell_text(TableCell& cell, const std::string& text) {
    // TODO: Implement cell text setting
    return false;
}

std::string TableOperations::get_cell_text(const TableCell& cell) {
    // TODO: Implement cell text getting
    return "";
}

// ============================================================================
// DocumentBuilder Implementation
// ============================================================================

DocumentBuilder::DocumentBuilder(Document* doc) : doc_(doc) {}

void DocumentBuilder::ensure_paragraph() {
    if (!current_paragraph_) {
        pugi::xml_node body = get_body();
        current_paragraph_ = body.append_child("w:p");
    }
}

pugi::xml_node DocumentBuilder::get_body() {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        return pugi::xml_node();
    }
    return doc_xml->child("w:document").child("w:body");
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
void DocumentBuilder::move_to_document_start() {
    pugi::xml_node body = get_body();
    current_paragraph_ = body.child("w:p");
    current_node_ = current_paragraph_;
}

void DocumentBuilder::move_to_document_end() {
    pugi::xml_node body = get_body();
    current_paragraph_ = body.last_child();
    current_node_ = current_paragraph_;
}

void DocumentBuilder::move_to_paragraph(size_t index) {
    pugi::xml_node body = get_body();
    size_t count = 0;
    
    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (count == index) {
            current_paragraph_ = para;
            current_node_ = para;
            return;
        }
        count++;
    }
}

void DocumentBuilder::move_to_bookmark(const std::string& name) {
    // TODO: Implement bookmark navigation
}

void DocumentBuilder::move_to_cell(size_t table_index, size_t row_index, size_t cell_index) {
    // TODO: Implement cell navigation
}

// Text Insertion
void DocumentBuilder::write(const std::string& text) {
    ensure_paragraph();
    
    pugi::xml_node run = current_paragraph_.append_child("w:r");
    apply_formatting(run);
    
    pugi::xml_node t = run.append_child("w:t");
    t.text().set(text.c_str());
}

void DocumentBuilder::writeln(const std::string& text) {
    write(text);
    insert_break();
}

void DocumentBuilder::writeln() {
    insert_break();
}

Paragraph* DocumentBuilder::insert_paragraph() {
    pugi::xml_node body = get_body();
    current_paragraph_ = body.append_child("w:p");
    current_node_ = current_paragraph_;
    
    // Return pointer to a new Paragraph object
    // Note: This creates a memory management issue - needs proper handling
    static Paragraph* para = nullptr;
    if (para) delete para;
    para = new Paragraph();
    para->set_current(current_paragraph_);
    return para;
}

void DocumentBuilder::insert_break() {
    pugi::xml_node body = get_body();
    current_paragraph_ = body.append_child("w:p");
    current_node_ = current_paragraph_;
}

// Formatting
void DocumentBuilder::set_bold(bool value) { format_.bold = value; }
void DocumentBuilder::set_italic(bool value) { format_.italic = value; }
void DocumentBuilder::set_underline(bool value) { format_.underline = value; }
void DocumentBuilder::set_strikethrough(bool value) { format_.strikethrough = value; }
void DocumentBuilder::set_font_name(const std::string& name) { format_.font_name = name; }
void DocumentBuilder::set_font_size(int size) { format_.font_size = size; }
void DocumentBuilder::set_color(const std::string& color_hex) { format_.color = color_hex; }
void DocumentBuilder::set_alignment(const std::string& alignment) { format_.alignment = alignment; }

void DocumentBuilder::clear_formatting() {
    format_ = FormattingState();
}

// Table Building
void DocumentBuilder::start_table() {
    pugi::xml_node body = get_body();
    current_table_ = body.append_child("w:tbl");
    in_table_ = true;
    
    // Add table properties
    pugi::xml_node tblPr = current_table_.append_child("w:tblPr");
    pugi::xml_node tblW = tblPr.append_child("w:tblW");
    tblW.append_attribute("w:w").set_value("5000");
    tblW.append_attribute("w:type").set_value("pct");
}

void DocumentBuilder::end_table() {
    in_table_ = false;
    current_table_ = pugi::xml_node();
    current_row_ = pugi::xml_node();
    current_cell_ = pugi::xml_node();
}

void DocumentBuilder::insert_row() {
    if (!in_table_) {
        return;
    }
    current_row_ = current_table_.append_child("w:tr");
}

void DocumentBuilder::insert_cell() {
    if (!in_table_ || !current_row_) {
        return;
    }
    current_cell_ = current_row_.append_child("w:tc");
    
    // Add cell properties
    pugi::xml_node tcPr = current_cell_.append_child("w:tcPr");
    pugi::xml_node tcW = tcPr.append_child("w:tcW");
    tcW.append_attribute("w:w").set_value("0");
    tcW.append_attribute("w:type").set_value("auto");
    
    // Add empty paragraph
    current_paragraph_ = current_cell_.append_child("w:p");
}

void DocumentBuilder::end_row() {
    current_row_ = pugi::xml_node();
    current_cell_ = pugi::xml_node();
}

// Hyperlink
void DocumentBuilder::insert_hyperlink(const std::string& text, const std::string& url) {
    ensure_paragraph();
    
    // TODO: Properly implement hyperlinks with relationships
    // For now, just insert text
    write(text);
}

// Bookmark
void DocumentBuilder::start_bookmark(const std::string& name) {
    if (!doc_) {
        return;
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
}

void DocumentBuilder::end_bookmark(const std::string& name) {
    if (!doc_) {
        return;
    }
    
    ensure_paragraph();
    
    // Find the bookmark ID from the stack
    auto it = bookmark_stack_.find(name);
    if (it == bookmark_stack_.end()) {
        // No matching start_bookmark called
        return;
    }
    
    int bookmark_id = it->second;
    bookmark_stack_.erase(it);
    
    // Create bookmarkEnd element
    pugi::xml_node bookmark_end = current_paragraph_.append_child("w:bookmarkEnd");
    bookmark_end.append_attribute("w:id").set_value(bookmark_id);
}

// Image
bool DocumentBuilder::insert_image(const std::string& image_path, double width, double height) {
    // TODO: Implement image insertion with relationships
    return false;
}

// ============================================================================
// DocumentSearch Implementation
// ============================================================================

std::optional<Range> DocumentSearch::find(Document& doc, const std::string& text) {
    // TODO: Implement search
    return std::nullopt;
}

std::vector<Range> DocumentSearch::find_all(Document& doc, const std::string& text) {
    // TODO: Implement find all
    return {};
}

bool DocumentSearch::replace(Document& doc, const std::string& old_text, const std::string& new_text) {
    // TODO: Implement replace
    return false;
}

int DocumentSearch::replace_all(Document& doc, const std::string& old_text, const std::string& new_text) {
    // TODO: Implement replace all
    return 0;
}

bool DocumentSearch::replace_with_formatting(Document& doc, const std::string& old_text,
                                             const std::string& new_text, formatting_flag flag) {
    // TODO: Implement replace with formatting
    return false;
}

int DocumentSearch::find_and_process(Document& doc, const std::string& pattern, SearchCallback callback) {
    // TODO: Implement find and process
    return 0;
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

