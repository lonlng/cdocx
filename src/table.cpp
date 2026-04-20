/**
 * @file table.cpp
 * @brief Table, Row, Cell class implementations (DOM style)
 */

#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/properties.h>
#include <cdocx/table.h>

#include <iostream>

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
    if (!visitor)
        return;
    if (visitor->visit_cell_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_cell_end(*this);
    }
}

std::shared_ptr<Node> Cell::clone(bool deep) const {
    auto cloned = std::make_shared<Cell>(get_document());
    cloned->set_cell_format(format_);
    if (deep) {
        for (const auto& child : get_children()) {
            if (auto child_clone = child->clone(deep)) {
                cloned->append_child(child_clone);
            }
        }
    }
    return cloned;
}

std::vector<std::shared_ptr<Paragraph>> Cell::get_paragraphs() const {
    return get_children_of_type<Paragraph>();
}

std::shared_ptr<Paragraph> Cell::get_first_paragraph() const {
    return get_first_child<Paragraph>();
}

std::shared_ptr<Paragraph> Cell::append_paragraph(const std::string& text) {
    auto para = std::make_shared<Paragraph>(get_document());
    if (!text.empty()) {
        para->append_run(text);
    }
    append_child(para);
    return para;
}

std::shared_ptr<Paragraph> Cell::insert_paragraph(int index, const std::string& text) {
    auto para = std::make_shared<Paragraph>(get_document());
    if (!text.empty()) {
        para->append_run(text);
    }
    insert_child(index, para);
    return para;
}

std::shared_ptr<Paragraph> Cell::ensure_minimum() {
    auto paras = get_paragraphs();
    if (paras.empty()) {
        return append_paragraph();
    }
    return paras.front();
}

void Cell::set_text(const std::string& text) {
    remove_all_children();
    append_paragraph(text);
}

std::shared_ptr<Table> Cell::get_parent_table() const {
    auto row = get_parent_row();
    if (!row)
        return nullptr;
    return row->get_parent_table();
}

void Cell::merge_with(const std::shared_ptr<Cell>& other) {
    if (!other || other.get() == this)
        return;
    auto table = get_parent_table();
    if (!table)
        return;
    table->merge_cells(std::static_pointer_cast<Cell>(shared_from_this()),
                       std::static_pointer_cast<Cell>(other->shared_from_this()));
}

bool Cell::is_merged() const {
    return format_.is_merged();
}

bool Cell::is_first_merged_cell() const {
    return format_.horizontal_merge > 1 || format_.vertical_merge_start;
}

bool Cell::is_vertical_merge_start() const {
    return format_.is_vertical_merge_start();
}

bool Cell::is_vertical_merge_continue() const {
    return format_.is_vertical_merge_continue();
}

bool Cell::is_horizontal_merge_start() const {
    return format_.horizontal_merge > 1;
}

int Cell::get_horizontal_merge_span() const {
    return format_.horizontal_merge;
}

std::shared_ptr<Row> Cell::get_parent_row() const {
    Row* row = get_ancestor<Row>();
    if (row) {
        return std::static_pointer_cast<Row>(row->shared_from_this());
    }
    return nullptr;
}

int Cell::get_column_index() const {
    auto row = get_parent_row();
    if (!row)
        return -1;
    auto cells = row->get_cells();
    int col = 0;
    for (size_t i = 0; i < cells.get_count(); ++i) {
        if (cells[i].get() == this) {
            return col;
        }
        col += cells[i]->get_horizontal_merge_span();
    }
    return -1;
}

void Cell::set_vertical_alignment(CellVerticalAlignment align) {
    format_.vertical_alignment = align;
}

CellVerticalAlignment Cell::get_vertical_alignment() const {
    return format_.vertical_alignment;
}

void Cell::set_width(double width, bool preferred) {
    format_.width = width;
    format_.preferred_width = preferred;
}

double Cell::get_width() const {
    return format_.width;
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
    if (!visitor)
        return;
    if (visitor->visit_row_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_row_end(*this);
    }
}

std::shared_ptr<Node> Row::clone(bool deep) const {
    auto cloned = std::make_shared<Row>(get_document());
    cloned->get_row_format() = format_;
    if (deep) {
        for (const auto& child : get_children()) {
            if (auto child_clone = child->clone(deep)) {
                cloned->append_child(child_clone);
            }
        }
    }
    return cloned;
}

CellCollection Row::get_cells() const {
    return CellCollection(get_children_of_type<Cell>());
}

std::shared_ptr<Cell> Row::get_first_cell() const {
    return get_first_child<Cell>();
}

std::shared_ptr<Cell> Row::get_last_cell() const {
    return get_last_child<Cell>();
}

std::shared_ptr<Cell> Row::get_cell(int index) const {
    auto cells = get_children_of_type<Cell>();
    int col = 0;
    for (const auto& cell : cells) {
        int span = cell->get_horizontal_merge_span();
        if (col <= index && index < col + span) {
            return cell;
        }
        col += span;
    }
    return nullptr;
}

std::shared_ptr<Cell> Row::append_cell() {
    auto cell = std::make_shared<Cell>(get_document());
    append_child(cell);
    return cell;
}

std::shared_ptr<Cell> Row::insert_cell(int index) {
    auto cell = std::make_shared<Cell>(get_document());
    insert_child(index, cell);
    return cell;
}

std::shared_ptr<Cell> Row::append_cell(const std::string& text) {
    auto cell = append_cell();
    if (!text.empty()) {
        cell->append_paragraph(text);
    }
    return cell;
}

std::shared_ptr<Cell> Row::ensure_minimum() {
    auto cells = get_children_of_type<Cell>();
    if (cells.empty()) {
        return append_cell();
    }
    return cells.front();
}

int Row::get_row_index() const {
    auto table = get_parent_table();
    if (!table)
        return -1;
    auto rows = table->get_rows();
    for (size_t i = 0; i < rows.get_count(); ++i) {
        if (rows[i].get() == this) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool Row::is_first_row() const {
    return get_row_index() == 0;
}

bool Row::is_last_row() const {
    auto table = get_parent_table();
    if (!table)
        return true;
    return get_row_index() == static_cast<int>(table->get_row_count() - 1);
}

std::shared_ptr<Table> Row::get_parent_table() const {
    Table* table = get_ancestor<Table>();
    if (table) {
        return std::static_pointer_cast<Table>(table->shared_from_this());
    }
    return nullptr;
}

// ============================================================================
// Table Implementation
// ============================================================================

Table::Table() = default;

Table::Table(Document* doc) {
    set_document(doc);
}

Table::Table(Document* doc, int rows, int cols) {
    set_document(doc);
    for (int r = 0; r < rows; ++r) {
        auto row = std::make_shared<Row>(doc);
        for (int c = 0; c < cols; ++c) {
            auto cell = std::make_shared<Cell>(doc);
            cell->ensure_minimum();
            row->append_child(cell);
        }
        append_child(row);
    }
}

std::string Table::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

void Table::accept(DocumentVisitor* visitor) {
    if (!visitor)
        return;
    if (visitor->visit_table_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_table_end(*this);
    }
}

void Table::preserve_tblPr(pugi::xml_node tblPr) {
    if (!tblPr)
        return;
    preserved_tblPr_.reset();
    preserved_tblPr_.append_copy(tblPr);
}

pugi::xml_node Table::get_preserved_tblPr() const {
    return preserved_tblPr_.first_child();
}

bool Table::has_preserved_tblPr() const {
    return preserved_tblPr_.first_child() != nullptr;
}

void Table::preserve_tblGrid(pugi::xml_node tblGrid) {
    if (!tblGrid)
        return;
    preserved_tblGrid_.reset();
    preserved_tblGrid_.append_copy(tblGrid);
}

pugi::xml_node Table::get_preserved_tblGrid() const {
    return preserved_tblGrid_.first_child();
}

bool Table::has_preserved_tblGrid() const {
    return preserved_tblGrid_.first_child() != nullptr;
}

std::shared_ptr<Node> Table::clone(bool deep) const {
    auto cloned = std::make_shared<Table>(get_document());
    cloned->set_table_format(format_);
    if (has_preserved_tblPr()) {
        cloned->preserve_tblPr(get_preserved_tblPr());
    }
    if (has_preserved_tblGrid()) {
        cloned->preserve_tblGrid(get_preserved_tblGrid());
    }
    if (deep) {
        for (const auto& child : get_children()) {
            if (auto child_clone = child->clone(deep)) {
                cloned->append_child(child_clone);
            }
        }
    }
    return cloned;
}

RowCollection Table::get_rows() const {
    return RowCollection(get_children_of_type<Row>());
}

std::shared_ptr<Row> Table::get_first_row() const {
    return get_first_child<Row>();
}

std::shared_ptr<Row> Table::get_last_row() const {
    return get_last_child<Row>();
}

std::shared_ptr<Row> Table::get_row(int index) const {
    auto rows = get_children_of_type<Row>();
    if (index >= 0 && static_cast<size_t>(index) < rows.size()) {
        return rows[index];
    }
    return nullptr;
}

std::shared_ptr<Row> Table::append_row() {
    auto row = std::make_shared<Row>(get_document());
    append_child(row);
    return row;
}

std::shared_ptr<Row> Table::insert_row(int index) {
    auto row = std::make_shared<Row>(get_document());
    insert_child(index, row);
    return row;
}

void Table::remove_row(const std::shared_ptr<Row>& row) {
    remove_child(row);
}

void Table::remove_row(int index) {
    auto row = get_row(index);
    if (row) {
        remove_child(row);
    }
}

void Table::remove_all_rows() {
    remove_all_children();
}

std::shared_ptr<Cell> Table::get_cell(int row, int col) const {
    auto r = get_row(row);
    if (!r)
        return nullptr;
    return r->get_cell(col);
}

int Table::get_row_count() const {
    return static_cast<int>(get_children_of_type<Row>().size());
}

int Table::get_column_count() const {
    auto first_row = get_first_row();
    if (!first_row)
        return 0;
    int count = 0;
    auto cells = first_row->get_cells();
    for (size_t i = 0; i < cells.get_count(); ++i) {
        count += cells[static_cast<int>(i)]->get_horizontal_merge_span();
    }
    return count;
}

void Table::ensure_minimum() {
    if (get_row_count() == 0) {
        auto row = append_row();
        auto cell = row->append_cell();
        cell->ensure_minimum();
    }
}

std::string Table::to_text(const std::string& separator, const std::string& row_separator) const {
    std::string result;
    auto rows = get_rows();
    for (size_t r = 0; r < rows.get_count(); ++r) {
        if (r > 0)
            result += row_separator;
        auto cells = rows[static_cast<int>(r)]->get_cells();
        for (size_t c = 0; c < cells.get_count(); ++c) {
            if (c > 0)
                result += separator;
            result += cells[static_cast<int>(c)]->get_text();
        }
    }
    return result;
}

void Table::import_data(const std::vector<std::vector<std::string>>& data) {
    remove_all_children();
    for (const auto& row_data : data) {
        auto row = append_row();
        for (const auto& cell_text : row_data) {
            auto cell = row->append_cell(cell_text);
            (void)cell;
        }
    }
}

bool Table::is_complex() const {
    for (const auto& row : get_rows()) {
        for (const auto& cell : row->get_cells()) {
            if (cell->is_merged())
                return true;
        }
    }
    return false;
}

void Table::auto_fit(AutoFitBehavior behavior) {
    format_.auto_fit_behavior = behavior;
    format_.allow_auto_fit = (behavior != AutoFitBehavior::FixedColumnWidth);
}

void Table::insert_column(int index) {
    if (index < 0)
        index = 0;

    for (const auto& row : get_rows()) {
        int current_col = 0;
        int cell_index = 0;
        bool inserted = false;
        for (const auto& cell : row->get_cells()) {
            int span = cell->get_horizontal_merge_span();
            if (current_col <= index && index < current_col + span) {
                // Insert at this position
                auto new_cell = std::make_shared<Cell>(get_document());
                new_cell->ensure_minimum();
                row->insert_child(cell_index, new_cell);
                inserted = true;
                break;
            }
            current_col += span;
            ++cell_index;
        }
        if (!inserted) {
            // Append at the end
            auto new_cell = std::make_shared<Cell>(get_document());
            new_cell->ensure_minimum();
            row->append_child(new_cell);
        }
    }
}

void Table::delete_column(int index) {
    if (index < 0)
        return;

    for (const auto& row : get_rows()) {
        int current_col = 0;
        int cell_index = 0;
        for (const auto& cell : row->get_cells()) {
            int span = cell->get_horizontal_merge_span();
            if (current_col <= index && index < current_col + span) {
                row->remove_child(cell);
                break;
            }
            current_col += span;
            ++cell_index;
        }
    }
}

void Table::set_style(const std::string& style_name) {
    format_.style_name = style_name;
}

void Table::set_style(StyleIdentifier style) {
    format_.style_identifier = style;
}

std::string Table::get_style_name() const {
    return format_.style_name;
}

std::shared_ptr<Cell> Table::merge_cells(const std::shared_ptr<Cell>& start_cell,
                                         const std::shared_ptr<Cell>& end_cell) {
    if (!start_cell || !end_cell || start_cell.get() == end_cell.get()) {
        return start_cell;
    }

    auto start_row = start_cell->get_parent_row();
    auto end_row = end_cell->get_parent_row();
    if (!start_row || !end_row)
        return nullptr;

    auto table = start_row->get_parent_table();
    if (!table || table.get() != this)
        return nullptr;
    if (start_row->get_parent_table().get() != this)
        return nullptr;

    int start_row_idx = start_row->get_row_index();
    int end_row_idx = end_row->get_row_index();
    int start_col_idx = start_cell->get_column_index();
    int end_col_idx = end_cell->get_column_index();

    if (start_row_idx < 0 || end_row_idx < 0 || start_col_idx < 0 || end_col_idx < 0) {
        return nullptr;
    }
    if (start_row_idx > end_row_idx)
        std::swap(start_row_idx, end_row_idx);
    if (start_col_idx > end_col_idx)
        std::swap(start_col_idx, end_col_idx);

    return merge_cells(start_row_idx, start_col_idx, end_row_idx, end_col_idx);
}

std::shared_ptr<Cell> Table::merge_cells(int start_row, int start_col, int end_row, int end_col) {
    if (start_row > end_row)
        std::swap(start_row, end_row);
    if (start_col > end_col)
        std::swap(start_col, end_col);

    int row_count = get_row_count();
    if (start_row < 0 || end_row >= row_count)
        return nullptr;

    // Validate that all rows have enough columns (accounting for existing merges)
    for (int r = start_row; r <= end_row; ++r) {
        auto row = get_row(r);
        if (!row)
            return nullptr;
        int col_count = 0;
        for (const auto& cell : row->get_cells()) {
            col_count += cell->get_horizontal_merge_span();
        }
        if (end_col >= col_count)
            return nullptr;
    }

    int col_span = end_col - start_col + 1;
    int row_span = end_row - start_row + 1;

    for (int r = start_row; r <= end_row; ++r) {
        auto row = get_row(r);
        auto cells = row->get_cells();

        // Find the cell at start_col and the cells to merge/remove
        int current_col = 0;
        std::shared_ptr<Cell> first_cell_in_row;
        std::vector<std::shared_ptr<Cell>> cells_to_remove;
        bool found_start = false;

        for (const auto& cell : cells) {
            int span = cell->get_horizontal_merge_span();
            if (!found_start) {
                if (current_col <= start_col && start_col < current_col + span) {
                    first_cell_in_row = cell;
                    found_start = true;
                    // Collect cells within the horizontal merge range
                    int inner_col = current_col + span;
                    for (size_t i = static_cast<size_t>(cell->get_column_index()) + 1;
                         i < cells.get_count();
                         ++i) {
                        auto next_cell = cells[static_cast<int>(i)];
                        if (inner_col > end_col)
                            break;
                        cells_to_remove.push_back(next_cell);
                        inner_col += next_cell->get_horizontal_merge_span();
                    }
                    break;
                }
            }
            current_col += span;
        }

        if (!first_cell_in_row)
            continue;

        // Move content from cells to be removed into the first cell
        for (const auto& removed_cell : cells_to_remove) {
            for (const auto& child : removed_cell->get_children()) {
                first_cell_in_row->append_child(child->clone(true));
            }
            row->remove_child(removed_cell);
        }

        // Set merge properties
        first_cell_in_row->get_cell_format().horizontal_merge = col_span;
        if (row_span > 1) {
            first_cell_in_row->get_cell_format().vertical_merge = true;
            first_cell_in_row->get_cell_format().vertical_merge_start = (r == start_row);
        } else {
            first_cell_in_row->get_cell_format().vertical_merge = false;
            first_cell_in_row->get_cell_format().vertical_merge_start = false;
        }
    }

    auto result = get_cell(start_row, start_col);
    return result;
}

void Table::split_cell(const std::shared_ptr<Cell>& cell, int row_count, int col_count) {
    if (!cell || row_count < 1 || col_count < 1)
        return;
    if (row_count == 1 && col_count == 1)
        return;

    auto row = cell->get_parent_row();
    if (!row)
        return;
    auto table = row->get_parent_table();
    if (!table || table.get() != this)
        return;

    int row_idx = row->get_row_index();
    int col_idx = cell->get_column_index();
    if (row_idx < 0 || col_idx < 0)
        return;

    int original_col_span = cell->get_horizontal_merge_span();
    int original_row_span = 1;
    if (cell->get_cell_format().vertical_merge) {
        // Count how many rows this cell spans
        if (cell->get_cell_format().vertical_merge_start) {
            for (int r = row_idx + 1; r < table->get_row_count(); ++r) {
                auto next_row = table->get_row(r);
                auto next_cell = next_row->get_cell(col_idx);
                if (!next_cell || !next_cell->get_cell_format().vertical_merge ||
                    next_cell->get_cell_format().vertical_merge_start) {
                    break;
                }
                original_row_span++;
            }
        } else {
            // Cell is a continuation; find the start and delegate
            for (int r = row_idx - 1; r >= 0; --r) {
                auto prev_row = table->get_row(r);
                auto prev_cell = prev_row->get_cell(col_idx);
                if (prev_cell && prev_cell->get_cell_format().vertical_merge_start) {
                    split_cell(prev_cell, row_count, col_count);
                    return;
                }
            }
            return;
        }
    }

    if (row_count > original_row_span || col_count > original_col_span) {
        // Cannot split into more parts than the original span
        return;
    }

    // For simplicity, we only support splitting back into individual cells
    // Reset the top-left cell
    cell->get_cell_format().horizontal_merge = 1;
    cell->get_cell_format().vertical_merge = false;
    cell->get_cell_format().vertical_merge_start = false;

    // Insert missing cells in the first row
    for (int c = 1; c < col_count; ++c) {
        auto new_cell = std::make_shared<Cell>(get_document());
        new_cell->ensure_minimum();
        int insert_pos = col_idx + c;
        // Clamp insert position
        if (insert_pos > static_cast<int>(row->get_children().size())) {
            insert_pos = static_cast<int>(row->get_children().size());
        }
        row->insert_child(insert_pos, new_cell);
    }

    // For each continuation row, insert cells
    for (int r = 1; r < row_count; ++r) {
        auto current_row = get_row(row_idx + r);
        if (!current_row)
            continue;

        // Remove the continuation cell if it exists
        auto cont_cell = current_row->get_cell(col_idx);
        if (cont_cell) {
            current_row->remove_child(cont_cell);
        }

        // Insert new cells
        for (int c = 0; c < col_count; ++c) {
            auto new_cell = std::make_shared<Cell>(get_document());
            new_cell->ensure_minimum();
            int insert_pos = col_idx + c;
            if (insert_pos > static_cast<int>(current_row->get_children().size())) {
                insert_pos = static_cast<int>(current_row->get_children().size());
            }
            current_row->insert_child(insert_pos, new_cell);
        }
    }

    // Remove any extra continuation rows that were part of the original merge
    // but are not covered by the new row_count
    for (int r = row_count; r < original_row_span; ++r) {
        auto current_row = get_row(row_idx + r);
        if (!current_row)
            continue;
        auto cont_cell = current_row->get_cell(col_idx);
        if (cont_cell && cont_cell->get_cell_format().vertical_merge &&
            !cont_cell->get_cell_format().vertical_merge_start) {
            current_row->remove_child(cont_cell);
        }
    }
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
    if (!current_) {
        return nullptr;
    }
    paragraph_.set_parent(current_);
    if (paragraph_.has_next()) {
        return &paragraph_;
    }
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

TableCell Table::cellAt(size_t row, size_t col) const {
    (void)row;
    (void)col;
    return TableCell();
}

TableCell Table::cellAtUnsafe(size_t row, size_t col) const {
    (void)row;
    (void)col;
    return TableCell();
}

size_t Table::getRowCount() const {
    return static_cast<size_t>(get_row_count());
}

size_t Table::getColumnCount() const {
    return static_cast<size_t>(get_column_count());
}

TableCell Table::merge(size_t startRow, size_t startCol, size_t rowCount, size_t colCount) {
    (void)startRow;
    (void)startCol;
    (void)rowCount;
    (void)colCount;
    return TableCell();
}

void Table::split(size_t row, size_t col) {
    (void)row;
    (void)col;
}

void Table::dumpStructure() const {
    std::cout << "Table structure:" << std::endl;

    // Legacy path: dump from XML
    if (current_xml_) {
        size_t row_idx = 0;
        for (auto tr = current_xml_.child("w:tr"); tr; tr = tr.next_sibling("w:tr"), ++row_idx) {
            std::cout << "  Row " << row_idx << ": ";
            size_t col_idx = 0;
            for (auto tc = tr.child("w:tc"); tc; tc = tc.next_sibling("w:tc"), ++col_idx) {
                auto grid_span = tc.child("w:tcPr").child("w:gridSpan");
                if (grid_span) {
                    std::cout << "[span=" << grid_span.attribute("w:val").as_int() << "] ";
                } else {
                    std::cout << "[cell] ";
                }
            }
            std::cout << std::endl;
        }
        return;
    }

    // DOM path: dump from child nodes
    size_t row_idx = 0;
    for (const auto& child : get_children()) {
        if (child->node_type() != NodeType::Row)
            continue;
        std::cout << "  Row " << row_idx << ": ";
        auto row = std::dynamic_pointer_cast<Row>(child);
        if (row) {
            size_t col_idx = 0;
            for (const auto& cell_node : row->get_children()) {
                if (cell_node->node_type() != NodeType::Cell)
                    continue;
                std::cout << "[cell] ";
                ++col_idx;
            }
            std::cout << "(" << col_idx << " cells)";
        }
        std::cout << std::endl;
        ++row_idx;
    }
}

void Table::set_properties(const TableProperties& props) {
    props.applyTo(*this);
}

}  // namespace cdocx
