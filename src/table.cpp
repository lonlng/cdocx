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
