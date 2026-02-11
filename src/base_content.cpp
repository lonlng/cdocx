/**
 * @file base_content.cpp
 * @brief Implementation of base content classes (Run, Paragraph, Table, etc.)
 * @details This file contains the implementation of the fundamental content
 *          classes that make up the document structure.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/base.h>
#include <cdocx/document.h>
#include <cdocx/format_context.h>
#include <cctype>
#include <cstring>

namespace cdocx {

// ============================================================================
// Run Implementation
// ============================================================================

Run::Run() = default;

Run::Run(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {}

void Run::set_parent(pugi::xml_node node) {
    parent_ = node;
    // Find first run child in the paragraph
    current_ = parent_.child("w:r");
}

void Run::set_current(pugi::xml_node node) {
    current_ = node;
}

pugi::xml_node Run::get_current() const {
    return current_;
}

pugi::xml_node Run::get_parent() const {
    return parent_;
}

std::string Run::get_text() const {
    if (!current_) {
        return "";
    }
    return current_.child("w:t").text().get();
}

bool Run::set_text(const std::string& text) const {
    if (!current_) {
        return false;
    }
    return current_.child("w:t").text().set(text.c_str());
}

bool Run::set_text(const char* text) const {
    if (!current_) {
        return false;
    }
    return current_.child("w:t").text().set(text);
}

Run& Run::next() {
    // Move to next w:r sibling (skip non-run elements)
    current_ = current_.next_sibling("w:r");
    return *this;
}

bool Run::has_next() const {
    return current_ != nullptr;
}

// ============================================================================
// Run Formatting Methods
// ============================================================================

bool Run::set_color(const std::string& color_hex) {
    return TextFormatContext::apply_color(current_, color_hex);
}

bool Run::set_font_size(int size) {
    return TextFormatContext::apply_font_size(current_, size);
}

bool Run::set_font_name(const std::string& font_name) {
    return TextFormatContext::apply_font_name(current_, font_name);
}

bool Run::set_bold(bool bold) {
    return TextFormatContext::apply_bold(current_, bold);
}

bool Run::set_italic(bool italic) {
    return TextFormatContext::apply_italic(current_, italic);
}

bool Run::set_underline(bool underline) {
    return TextFormatContext::apply_underline(current_, underline);
}

// ============================================================================
// Paragraph Implementation
// ============================================================================

Paragraph::Paragraph() = default;

Paragraph::Paragraph(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {
    run_.set_parent(current_);
}

void Paragraph::set_parent(pugi::xml_node node) {
    parent_ = node;
    // Find first paragraph child
    current_ = parent_.child("w:p");
    // Initialize run iterator for this paragraph
    if (current_) {
        run_.set_parent(current_);
    }
}

void Paragraph::set_current(pugi::xml_node node) {
    current_ = node;
}

Paragraph& Paragraph::next() {
    // Move to next w:p sibling (skip non-paragraph elements like w:sectPr)
    current_ = current_.next_sibling("w:p");
    // Update run iterator for new paragraph
    if (current_) {
        run_.set_parent(current_);
    }
    return *this;
}

bool Paragraph::has_next() const {
    return current_ != nullptr;
}

Run& Paragraph::runs() {
    run_.set_parent(current_);
    return run_;
}

Run& Paragraph::add_run(const std::string& text, formatting_flag f) {
    return add_run(text.c_str(), f);
}

Run& Paragraph::add_run(const char* text, formatting_flag f) {
    if (!current_) {
        return run_;
    }
    
    // Create new run element
    pugi::xml_node new_run = current_.append_child("w:r");
    
    // Create run properties element
    pugi::xml_node meta = new_run.append_child("w:rPr");
    
    // Apply formatting flags
    if (f & bold) {
        meta.append_child("w:b");
    }
    if (f & italic) {
        meta.append_child("w:i");
    }
    if (f & underline) {
        meta.append_child("w:u").append_attribute("w:val").set_value("single");
    }
    if (f & strikethrough) {
        meta.append_child("w:strike").append_attribute("w:val").set_value("true");
    }
    if (f & superscript) {
        meta.append_child("w:vertAlign").append_attribute("w:val").set_value("superscript");
    } else if (f & subscript) {
        meta.append_child("w:vertAlign").append_attribute("w:val").set_value("subscript");
    }
    if (f & smallcaps) {
        meta.append_child("w:smallCaps").append_attribute("w:val").set_value("true");
    }
    if (f & shadow) {
        meta.append_child("w:shadow").append_attribute("w:val").set_value("true");
    }
    
    // Create text element
    pugi::xml_node new_run_text = new_run.append_child("w:t");
    
    // Preserve spaces if text starts or ends with whitespace
    if (*text != 0 && (std::isspace(text[0]) || std::isspace(text[std::strlen(text) - 1]))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }
    
    // Set text content
    new_run_text.text().set(text);
    run_.set_current(new_run);
    
    return run_;
}

Run& Paragraph::add_run_with_bookmark(Document& doc, const std::string& text, const std::string& bookmark_name, formatting_flag f) {
    return add_run_with_bookmark(doc, text.c_str(), bookmark_name, f);
}

Run& Paragraph::add_run_with_bookmark(Document& doc, const char* text, const std::string& bookmark_name, formatting_flag f) {
    if (!current_) {
        return run_;
    }
    
    // Generate unique bookmark ID
    int bookmark_id = doc.generate_unique_bookmark_id();
    
    // Create bookmarkStart element before the run
    pugi::xml_node bookmark_start = current_.append_child("w:bookmarkStart");
    bookmark_start.append_attribute("w:id").set_value(bookmark_id);
    bookmark_start.append_attribute("w:name").set_value(bookmark_name.c_str());
    
    // Create new run element (same as add_run)
    pugi::xml_node new_run = current_.append_child("w:r");
    
    // Create run properties element
    pugi::xml_node meta = new_run.append_child("w:rPr");
    
    // Apply formatting flags
    if (f & bold) {
        meta.append_child("w:b");
    }
    if (f & italic) {
        meta.append_child("w:i");
    }
    if (f & underline) {
        meta.append_child("w:u").append_attribute("w:val").set_value("single");
    }
    if (f & strikethrough) {
        meta.append_child("w:strike").append_attribute("w:val").set_value("true");
    }
    if (f & superscript) {
        meta.append_child("w:vertAlign").append_attribute("w:val").set_value("superscript");
    } else if (f & subscript) {
        meta.append_child("w:vertAlign").append_attribute("w:val").set_value("subscript");
    }
    if (f & smallcaps) {
        meta.append_child("w:smallCaps").append_attribute("w:val").set_value("true");
    }
    if (f & shadow) {
        meta.append_child("w:shadow").append_attribute("w:val").set_value("true");
    }
    
    // Create text element
    pugi::xml_node new_run_text = new_run.append_child("w:t");
    
    // Preserve spaces if text starts or ends with whitespace
    if (*text != 0 && (std::isspace(text[0]) || std::isspace(text[std::strlen(text) - 1]))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }
    
    // Set text content
    new_run_text.text().set(text);
    
    // Create bookmarkEnd element after the run
    pugi::xml_node bookmark_end = current_.append_child("w:bookmarkEnd");
    bookmark_end.append_attribute("w:id").set_value(bookmark_id);
    
    run_.set_current(new_run);
    
    return run_;
}

void Paragraph::remove_run(const Run& r) {
    if (!current_) {
        return;
    }
    current_.remove_child(r.get_current());
}

Paragraph& Paragraph::insert_paragraph_after(const std::string& text, formatting_flag f) {
    // Insert new paragraph after current
    pugi::xml_node new_para = parent_.insert_child_after("w:p", current_);
    
    // Create static pointer to avoid stack allocation issues
    // Note: This is a potential memory leak in the original code
    static Paragraph* p = nullptr;
    if (p) {
        delete p;
    }
    p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);
    
    return *p;
}

std::string Paragraph::get_text() const {
    if (!current_) {
        return "";
    }
    
    std::string result;
    // Iterate through all runs in this paragraph
    for (pugi::xml_node run = current_.child("w:r"); run; run = run.next_sibling("w:r")) {
        pugi::xml_node t = run.child("w:t");
        if (t) {
            result += t.text().get();
        }
    }
    return result;
}

bool Paragraph::clear() {
    if (!current_) {
        return false;
    }
    
    // Remove all run elements
    pugi::xml_node run = current_.child("w:r");
    while (run) {
        pugi::xml_node next = run.next_sibling("w:r");
        current_.remove_child(run);
        run = next;
    }
    return true;
}

bool Paragraph::remove() {
    if (!parent_ || !current_) {
        return false;
    }
    return parent_.remove_child(current_);
}

Paragraph* Paragraph::insert_before(const std::string& text, formatting_flag f) {
    if (!parent_ || !current_) {
        return nullptr;
    }
    
    // Insert new paragraph before current
    pugi::xml_node new_para = parent_.insert_child_before("w:p", current_);
    
    // Note: This returns a pointer to a heap-allocated object
    // Caller is responsible for deletion (but API design suggests this is managed)
    Paragraph* p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);
    
    return p;
}

// ============================================================================
// Paragraph Formatting Methods
// ============================================================================

/**
 * @internal
 * @brief Get or create paragraph properties element
 * @param para The w:p element
 * @return The w:pPr element
 */
static pugi::xml_node get_or_create_pPr(pugi::xml_node para) {
    pugi::xml_node pPr = para.child("w:pPr");
    if (!pPr) {
        pPr = para.prepend_child("w:pPr");
    }
    return pPr;
}

bool Paragraph::set_alignment(const std::string& alignment) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node pPr = get_or_create_pPr(current_);
    
    // Get or create justification element
    pugi::xml_node jc = pPr.child("w:jc");
    if (!jc) {
        jc = pPr.append_child("w:jc");
    }
    
    jc.append_attribute("w:val").set_value(alignment.c_str());
    return true;
}

bool Paragraph::set_style(const std::string& style_id) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node pPr = get_or_create_pPr(current_);
    
    // Get or create paragraph style element
    pugi::xml_node pStyle = pPr.child("w:pStyle");
    if (!pStyle) {
        pStyle = pPr.prepend_child("w:pStyle");
    }
    
    pStyle.append_attribute("w:val").set_value(style_id.c_str());
    return true;
}

bool Paragraph::set_line_spacing(int line_spacing, bool is_exact) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node pPr = get_or_create_pPr(current_);
    
    // Get or create spacing element
    pugi::xml_node spacing = pPr.child("w:spacing");
    if (!spacing) {
        spacing = pPr.append_child("w:spacing");
    }
    
    // Set line rule
    spacing.append_attribute("w:lineRule").set_value(is_exact ? "exact" : "auto");
    spacing.append_attribute("w:line").set_value(line_spacing);
    
    return true;
}

bool Paragraph::set_spacing_before(int spacing) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node pPr = get_or_create_pPr(current_);
    
    pugi::xml_node sp = pPr.child("w:spacing");
    if (!sp) {
        sp = pPr.append_child("w:spacing");
    }
    
    sp.append_attribute("w:before").set_value(spacing);
    return true;
}

bool Paragraph::set_spacing_after(int spacing) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node pPr = get_or_create_pPr(current_);
    
    pugi::xml_node sp = pPr.child("w:spacing");
    if (!sp) {
        sp = pPr.append_child("w:spacing");
    }
    
    sp.append_attribute("w:after").set_value(spacing);
    return true;
}

bool Paragraph::set_indent(int left, int right, int first_line) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node pPr = get_or_create_pPr(current_);
    
    // Get or create indentation element
    pugi::xml_node ind = pPr.child("w:ind");
    if (!ind) {
        ind = pPr.append_child("w:ind");
    }
    
    // Set indentation values (-1 means ignore)
    if (left >= 0) {
        ind.append_attribute("w:left").set_value(left);
    }
    if (right >= 0) {
        ind.append_attribute("w:right").set_value(right);
    }
    if (first_line != 0) {
        ind.append_attribute("w:firstLine").set_value(first_line);
    }
    
    return true;
}

// ============================================================================
// Paragraph Text Formatting Methods
// ============================================================================

/**
 * @internal
 * @brief Get or create the first run in a paragraph for formatting
 * @param para The w:p element
 * @return The w:r element (created if didn't exist)
 */
static pugi::xml_node get_or_create_first_run(pugi::xml_node para) {
    pugi::xml_node run = para.child("w:r");
    if (!run) {
        // Create new run element
        run = para.append_child("w:r");
        // Create run properties
        run.append_child("w:rPr");
        // Create empty text element
        pugi::xml_node t = run.append_child("w:t");
        t.text().set("");
    }
    return run;
}

bool Paragraph::set_color(const std::string& color_hex) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_color(run, color_hex);
}

bool Paragraph::set_font_size(int size) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_font_size(run, size);
}

bool Paragraph::set_font_name(const std::string& font_name) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_font_name(run, font_name);
}

bool Paragraph::set_bold(bool bold) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_bold(run, bold);
}

bool Paragraph::set_italic(bool italic) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_italic(run, italic);
}

bool Paragraph::set_underline(bool underline) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_underline(run, underline);
}

// ============================================================================
// TableCell Implementation
// ============================================================================

TableCell::TableCell() = default;

TableCell::TableCell(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {
    paragraph_.set_parent(current_);
}

void TableCell::set_parent(pugi::xml_node node) {
    parent_ = node;
    current_ = parent_.child("w:tc");
    paragraph_.set_parent(current_);
}

void TableCell::set_current(pugi::xml_node node) {
    current_ = node;
}

bool TableCell::has_next() const {
    return current_ != nullptr;
}

TableCell& TableCell::next() {
    current_ = current_.next_sibling("w:tc");
    if (current_) {
        paragraph_.set_parent(current_);
    }
    return *this;
}

Paragraph& TableCell::paragraphs() {
    paragraph_.set_parent(current_);
    return paragraph_;
}

// ============================================================================
// TableRow Implementation
// ============================================================================

TableRow::TableRow() = default;

TableRow::TableRow(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {
    cell_.set_parent(current_);
}

void TableRow::set_parent(pugi::xml_node node) {
    parent_ = node;
    current_ = parent_.child("w:tr");
    cell_.set_parent(current_);
}

void TableRow::set_current(pugi::xml_node node) {
    current_ = node;
}

TableRow& TableRow::next() {
    current_ = current_.next_sibling("w:tr");
    if (current_) {
        cell_.set_parent(current_);
    }
    return *this;
}

TableCell& TableRow::cells() {
    cell_.set_parent(current_);
    return cell_;
}

bool TableRow::has_next() const {
    return current_ != nullptr;
}

// ============================================================================
// Table Implementation
// ============================================================================

Table::Table() = default;

Table::Table(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {
    row_.set_parent(current_);
}

void Table::set_parent(pugi::xml_node node) {
    parent_ = node;
    current_ = parent_.child("w:tbl");
    row_.set_parent(current_);
}

bool Table::has_next() const {
    return current_ != nullptr;
}

Table& Table::next() {
    current_ = current_.next_sibling("w:tbl");
    if (current_) {
        row_.set_parent(current_);
    }
    return *this;
}

void Table::set_current(pugi::xml_node node) {
    current_ = node;
}

TableRow& Table::rows() {
    row_.set_parent(current_);
    return row_;
}

} // namespace cdocx
