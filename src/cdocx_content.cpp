// CDocx - Content Classes Implementation
// Run, Paragraph, TableCell, TableRow, Table

#include "cdocx.h"
#include <cctype>
#include <cstring>

namespace cdocx {

// ============================================================================
// Run Implementation
// ============================================================================

Run::Run() = default;

Run::Run(pugi::xml_node parent_node, pugi::xml_node current_node) 
    : parent(parent_node), current(current_node) {}

void Run::set_parent(pugi::xml_node node) {
    parent = node;
    current = parent.child("w:r");
}

void Run::set_current(pugi::xml_node node) {
    current = node;
}

std::string Run::get_text() const {
    if (!current) return "";
    return current.child("w:t").text().get();
}

bool Run::set_text(const std::string& text) const {
    if (!current) return false;
    return current.child("w:t").text().set(text.c_str());
}

bool Run::set_text(const char* text) const {
    if (!current) return false;
    return current.child("w:t").text().set(text);
}

Run& Run::next() {
    current = current.next_sibling();
    return *this;
}

bool Run::has_next() const {
    return current != nullptr;
}

// ============================================================================
// Paragraph Implementation
// ============================================================================

Paragraph::Paragraph() = default;

Paragraph::Paragraph(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent(parent_node), current(current_node) {
    run.set_parent(current);
}

void Paragraph::set_parent(pugi::xml_node node) {
    parent = node;
    current = parent.child("w:p");
    run.set_parent(current);
}

void Paragraph::set_current(pugi::xml_node node) {
    current = node;
}

Paragraph& Paragraph::next() {
    current = current.next_sibling();
    run.set_parent(current);
    return *this;
}

bool Paragraph::has_next() const {
    return current != nullptr;
}

Run& Paragraph::runs() {
    run.set_parent(current);
    return run;
}

Run& Paragraph::add_run(const std::string& text, formatting_flag f) {
    return add_run(text.c_str(), f);
}

Run& Paragraph::add_run(const char* text, formatting_flag f) {
    if (!current) return run;
    
    pugi::xml_node new_run = current.append_child("w:r");
    pugi::xml_node meta = new_run.append_child("w:rPr");
    
    if (f & bold) meta.append_child("w:b");
    if (f & italic) meta.append_child("w:i");
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
    
    pugi::xml_node new_run_text = new_run.append_child("w:t");
    
    if (*text != 0 && (std::isspace(text[0]) || std::isspace(text[std::strlen(text) - 1]))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }
    
    new_run_text.text().set(text);
    run.set_current(new_run);
    return run;
}

void Paragraph::remove_run(const Run& r) {
    if (!current) return;
    current.remove_child(r.get_current());
}

Paragraph& Paragraph::insert_paragraph_after(const std::string& text, formatting_flag f) {
    pugi::xml_node new_para = parent.insert_child_after("w:p", current);
    
    static Paragraph* p = nullptr;
    if (p) delete p;
    p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);
    
    return *p;
}

// ============================================================================
// Run Formatting Methods
// ============================================================================

bool Run::set_color(const std::string& color_hex) {
    if (!current) return false;
    
    pugi::xml_node rPr = current.child("w:rPr");
    if (!rPr) {
        rPr = current.prepend_child("w:rPr");
    }
    
    pugi::xml_node color = rPr.child("w:color");
    if (!color) {
        color = rPr.append_child("w:color");
    }
    
    color.append_attribute("w:val").set_value(color_hex.c_str());
    return true;
}

bool Run::set_font_size(int size) {
    if (!current) return false;
    
    pugi::xml_node rPr = current.child("w:rPr");
    if (!rPr) {
        rPr = current.prepend_child("w:rPr");
    }
    
    pugi::xml_node sz = rPr.child("w:sz");
    if (!sz) {
        sz = rPr.append_child("w:sz");
    }
    sz.append_attribute("w:val").set_value(size);
    
    // Also set szCs for complex script
    pugi::xml_node szCs = rPr.child("w:szCs");
    if (!szCs) {
        szCs = rPr.append_child("w:szCs");
    }
    szCs.append_attribute("w:val").set_value(size);
    
    return true;
}

bool Run::set_font_name(const std::string& font_name) {
    if (!current) return false;
    
    pugi::xml_node rPr = current.child("w:rPr");
    if (!rPr) {
        rPr = current.prepend_child("w:rPr");
    }
    
    pugi::xml_node rFonts = rPr.child("w:rFonts");
    if (!rFonts) {
        rFonts = rPr.append_child("w:rFonts");
    }
    
    rFonts.append_attribute("w:ascii").set_value(font_name.c_str());
    rFonts.append_attribute("w:hAnsi").set_value(font_name.c_str());
    rFonts.append_attribute("w:cs").set_value(font_name.c_str());
    
    return true;
}

bool Run::set_bold(bool bold) {
    if (!current) return false;
    
    pugi::xml_node rPr = current.child("w:rPr");
    if (!rPr) {
        rPr = current.prepend_child("w:rPr");
    }
    
    if (bold) {
        if (!rPr.child("w:b")) {
            rPr.append_child("w:b");
        }
    } else {
        rPr.remove_child("w:b");
    }
    return true;
}

bool Run::set_italic(bool italic) {
    if (!current) return false;
    
    pugi::xml_node rPr = current.child("w:rPr");
    if (!rPr) {
        rPr = current.prepend_child("w:rPr");
    }
    
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
    if (!current) return false;
    
    pugi::xml_node rPr = current.child("w:rPr");
    if (!rPr) {
        rPr = current.prepend_child("w:rPr");
    }
    
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
// Paragraph Formatting Methods
// ============================================================================

bool Paragraph::set_alignment(const std::string& alignment) {
    if (!current) return false;
    
    pugi::xml_node pPr = current.child("w:pPr");
    if (!pPr) {
        pPr = current.prepend_child("w:pPr");
    }
    
    pugi::xml_node jc = pPr.child("w:jc");
    if (!jc) {
        jc = pPr.append_child("w:jc");
    }
    
    jc.append_attribute("w:val").set_value(alignment.c_str());
    return true;
}

bool Paragraph::set_style(const std::string& style_id) {
    if (!current) return false;
    
    pugi::xml_node pPr = current.child("w:pPr");
    if (!pPr) {
        pPr = current.prepend_child("w:pPr");
    }
    
    pugi::xml_node pStyle = pPr.child("w:pStyle");
    if (!pStyle) {
        pStyle = pPr.prepend_child("w:pStyle");
    }
    
    pStyle.append_attribute("w:val").set_value(style_id.c_str());
    return true;
}

bool Paragraph::set_line_spacing(int line_spacing, bool is_exact) {
    if (!current) return false;
    
    pugi::xml_node pPr = current.child("w:pPr");
    if (!pPr) {
        pPr = current.prepend_child("w:pPr");
    }
    
    pugi::xml_node spacing = pPr.child("w:spacing");
    if (!spacing) {
        spacing = pPr.append_child("w:spacing");
    }
    
    if (is_exact) {
        spacing.append_attribute("w:lineRule").set_value("exact");
    } else {
        spacing.append_attribute("w:lineRule").set_value("auto");
    }
    spacing.append_attribute("w:line").set_value(line_spacing);
    return true;
}

bool Paragraph::set_spacing_before(int spacing) {
    if (!current) return false;
    
    pugi::xml_node pPr = current.child("w:pPr");
    if (!pPr) {
        pPr = current.prepend_child("w:pPr");
    }
    
    pugi::xml_node sp = pPr.child("w:spacing");
    if (!sp) {
        sp = pPr.append_child("w:spacing");
    }
    
    sp.append_attribute("w:before").set_value(spacing);
    return true;
}

bool Paragraph::set_spacing_after(int spacing) {
    if (!current) return false;
    
    pugi::xml_node pPr = current.child("w:pPr");
    if (!pPr) {
        pPr = current.prepend_child("w:pPr");
    }
    
    pugi::xml_node sp = pPr.child("w:spacing");
    if (!sp) {
        sp = pPr.append_child("w:spacing");
    }
    
    sp.append_attribute("w:after").set_value(spacing);
    return true;
}

bool Paragraph::set_indent(int left, int right, int first_line) {
    if (!current) return false;
    
    pugi::xml_node pPr = current.child("w:pPr");
    if (!pPr) {
        pPr = current.prepend_child("w:pPr");
    }
    
    pugi::xml_node ind = pPr.child("w:ind");
    if (!ind) {
        ind = pPr.append_child("w:ind");
    }
    
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
    : parent(parent_node), current(current_node) {
    paragraph.set_parent(current);
}

void TableCell::set_parent(pugi::xml_node node) {
    parent = node;
    current = parent.child("w:tc");
    paragraph.set_parent(current);
}

void TableCell::set_current(pugi::xml_node node) {
    current = node;
}

bool TableCell::has_next() const {
    return current != nullptr;
}

TableCell& TableCell::next() {
    current = current.next_sibling();
    return *this;
}

Paragraph& TableCell::paragraphs() {
    paragraph.set_parent(current);
    return paragraph;
}

// ============================================================================
// TableRow Implementation
// ============================================================================

TableRow::TableRow() = default;

TableRow::TableRow(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent(parent_node), current(current_node) {
    cell.set_parent(current);
}

void TableRow::set_parent(pugi::xml_node node) {
    parent = node;
    current = parent.child("w:tr");
    cell.set_parent(current);
}

void TableRow::set_current(pugi::xml_node node) {
    current = node;
}

TableRow& TableRow::next() {
    current = current.next_sibling();
    cell.set_parent(current);
    return *this;
}

TableCell& TableRow::cells() {
    cell.set_parent(current);
    return cell;
}

bool TableRow::has_next() const {
    return current != nullptr;
}

// ============================================================================
// Table Implementation
// ============================================================================

Table::Table() = default;

Table::Table(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent(parent_node), current(current_node) {
    row.set_parent(current);
}

void Table::set_parent(pugi::xml_node node) {
    parent = node;
    current = parent.child("w:tbl");
    row.set_parent(current);
}

bool Table::has_next() const {
    return current != nullptr;
}

Table& Table::next() {
    current = current.next_sibling();
    row.set_parent(current);
    return *this;
}

void Table::set_current(pugi::xml_node node) {
    current = node;
}

TableRow& Table::rows() {
    row.set_parent(current);
    return row;
}

} // namespace cdocx
