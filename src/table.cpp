/**
 * @file table.cpp
 * @brief Table, Row, Cell class implementations (DOM style)
 */

#include <cdocx/table.h>
#include <cdocx/document.h>

namespace cdocx {

// ============================================================================
// Cell Implementation
// ============================================================================

Cell::Cell() = default;

Cell::Cell(Document* doc) {
    set_document(doc);
}

std::string Cell::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

void Cell::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_cell_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_cell_end(*this);
    }
}

std::shared_ptr<Node> Cell::clone(bool deep) const {
    // TODO: Implement proper cloning
    return nullptr;
}

// ============================================================================
// Row Implementation
// ============================================================================

Row::Row() = default;

Row::Row(Document* doc) {
    set_document(doc);
}

std::string Row::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

void Row::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_row_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_row_end(*this);
    }
}

std::shared_ptr<Node> Row::clone(bool deep) const {
    // TODO: Implement proper cloning
    return nullptr;
}

// ============================================================================
// Table Implementation
// ============================================================================

Table::Table(Document* doc) {
    set_document(doc);
}

Table::Table(Document* doc, int rows, int cols) {
    set_document(doc);
    // TODO: Create rows and cells
}

std::string Table::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

void Table::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_table_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_table_end(*this);
    }
}

std::shared_ptr<Node> Table::clone(bool deep) const {
    // TODO: Implement proper cloning
    return nullptr;
}

// ============================================================================
// Legacy Iterator-style Implementation
// ============================================================================

// TableCell
TableCell::TableCell() = default;

TableCell::TableCell(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {
}

void TableCell::set_parent(pugi::xml_node node) {
    parent_ = node;
    current_ = parent_.child("w:tc");
}

void TableCell::set_current(pugi::xml_node node) {
    current_ = node;
}

bool TableCell::has_next() const {
    return current_ != nullptr;
}

TableCell& TableCell::next() {
    current_ = current_.next_sibling("w:tc");
    return *this;
}

Paragraph* TableCell::paragraphs() {
    // TODO: Implement proper paragraph access
    return nullptr;
}

// TableRow
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

// Legacy Table Iterator (these are methods of Table class)
Table::Table() = default;

Table::Table(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_xml_(parent_node), current_xml_(current_node) {
    row_.set_parent(current_xml_);
}

void Table::set_parent_xml(pugi::xml_node node) {
    parent_xml_ = node;
    current_xml_ = parent_xml_.child("w:tbl");
    row_.set_parent(current_xml_);
}

bool Table::has_next() const {
    return current_xml_ != nullptr;
}

Table& Table::next() {
    current_xml_ = current_xml_.next_sibling("w:tbl");
    if (current_xml_) {
        row_.set_parent(current_xml_);
    }
    return *this;
}

void Table::set_current_xml(pugi::xml_node node) {
    current_xml_ = node;
}

TableRow Table::rows_legacy() {
    row_.set_parent(current_xml_);
    return row_;
}

} // namespace cdocx
