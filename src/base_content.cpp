/**
 * @file base_content.cpp
 * @brief Implementation of base content classes (Run, Paragraph, Table, etc.)
 * @details This file contains the implementation of the fundamental content
 *          classes that make up the document structure.
 * 
 * @author Amir Mohamadi (@amiremohamadi)
 * @copyright MIT License
 * @date 2024
 * @version 0.2.0
 */

#include <cdocx/base.h>
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
    current_ = current_.next_sibling();
    return *this;
}

bool Run::has_next() const {
    return current_ != nullptr;
}

// ============================================================================
// Run Formatting Methods
// ============================================================================

/**
 * @internal
 * @brief Get or create the w:rPr (run properties) element
 * @param run The w:r element
 * @return The w:rPr element (created if didn't exist)
 */
static pugi::xml_node get_or_create_rPr(pugi::xml_node run) {
    pugi::xml_node rPr = run.child("w:rPr");
    if (!rPr) {
        // Prepend to ensure rPr comes before w:t
        rPr = run.prepend_child("w:rPr");
    }
    return rPr;
}

bool Run::set_color(const std::string& color_hex) {
    if (!current_) {
        return false;
    }
    
    // Get or create run properties
    pugi::xml_node rPr = get_or_create_rPr(current_);
    
    // Get or create color element
    pugi::xml_node color = rPr.child("w:color");
    if (!color) {
        color = rPr.append_child("w:color");
    }
    
    // Set color value (hex without #)
    color.append_attribute("w:val").set_value(color_hex.c_str());
    return true;
}

bool Run::set_font_size(int size) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node rPr = get_or_create_rPr(current_);
    
    // Set sz (size) element
    pugi::xml_node sz = rPr.child("w:sz");
    if (!sz) {
        sz = rPr.append_child("w:sz");
    }
    sz.append_attribute("w:val").set_value(size);
    
    // Set szCs (complex script size) element
    pugi::xml_node szCs = rPr.child("w:szCs");
    if (!szCs) {
        szCs = rPr.append_child("w:szCs");
    }
    szCs.append_attribute("w:val").set_value(size);
    
    return true;
}

bool Run::set_font_name(const std::string& font_name) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node rPr = get_or_create_rPr(current_);
    
    // Get or create rFonts element
    pugi::xml_node rFonts = rPr.child("w:rFonts");
    if (!rFonts) {
        rFonts = rPr.append_child("w:rFonts");
    }
    
    // Set font attributes for different character sets
    rFonts.append_attribute("w:ascii").set_value(font_name.c_str());
    rFonts.append_attribute("w:hAnsi").set_value(font_name.c_str());
    rFonts.append_attribute("w:cs").set_value(font_name.c_str());
    
    return true;
}

bool Run::set_bold(bool bold) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node rPr = get_or_create_rPr(current_);
    
    if (bold) {
        // Add bold element if not present
        if (!rPr.child("w:b")) {
            rPr.append_child("w:b");
        }
    } else {
        // Remove bold element
        rPr.remove_child("w:b");
    }
    return true;
}

bool Run::set_italic(bool italic) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node rPr = get_or_create_rPr(current_);
    
    if (italic) {
        if (!rPr.child("w:i")) {
            rPr.append_child("w:i");
        }
    } else {
        rPr.remove_child("w:i");
    }
    return true;
}

bool Run::set_underline(bool underline) {
    if (!current_) {
        return false;
    }
    
    pugi::xml_node rPr = get_or_create_rPr(current_);
    
    if (underline) {
        pugi::xml_node u = rPr.child("w:u");
        if (!u) {
            u = rPr.append_child("w:u");
        }
        u.append_attribute("w:val").set_value("single");
    } else {
        rPr.remove_child("w:u");
    }
    return true;
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
    current_ = parent_.child("w:p");
    run_.set_parent(current_);
}

void Paragraph::set_current(pugi::xml_node node) {
    current_ = node;
}

Paragraph& Paragraph::next() {
    current_ = current_.next_sibling();
    run_.set_parent(current_);
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
    current_ = current_.next_sibling();
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
    current_ = current_.next_sibling();
    cell_.set_parent(current_);
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
    current_ = current_.next_sibling();
    row_.set_parent(current_);
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
