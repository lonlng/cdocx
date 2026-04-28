/**
 * @file table.h
 * @brief Table classes for CDocx - DOM Style
 * @details Table, Row, Cell with full DOM support, all inheriting from CompositeNode
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.8.0
 */

#pragma once

#include <cdocx/format.h>
#include <cdocx/node.h>
#include <cdocx/paragraph.h>
#include <cdocx/properties.h>

#include <memory>
#include <pugixml.hpp>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations
class Document;
class Paragraph;

// ============================================================================
// Legacy TableRow/TableCell Forward Declarations (for backward compatibility)
// ============================================================================

class TableRow;   // Forward declaration
class TableCell;  // Forward declaration

// ============================================================================
// Cell Class - Table cell (CompositeNode containing Paragraphs and Tables)
// ============================================================================

class Cell : public CompositeNode {
  public:
    Cell();
    explicit Cell(Document* doc);

    // Node overrides
    NodeType node_type() const override { return NodeType::Cell; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;
    std::string get_text() const override;

    // Cell format
    CellFormat& get_cell_format() { return format_; }
    const CellFormat& get_cell_format() const { return format_; }
    void set_cell_format(const CellFormat& format) { format_ = format; }

    // Content access (Cell contains Paragraphs and Tables)
    std::vector<std::shared_ptr<Paragraph>> get_paragraphs() const;
    std::vector<std::shared_ptr<class Table>> get_tables() const;
    std::shared_ptr<Paragraph> get_first_paragraph() const;

    // Content creation
    std::shared_ptr<Paragraph> append_paragraph(const std::string& text = "");
    std::shared_ptr<Paragraph> insert_paragraph(int index, const std::string& text = "");
    std::shared_ptr<class Table> append_table(int rows = 1, int cols = 1);

    // Ensure cell has at least one paragraph
    std::shared_ptr<Paragraph> ensure_minimum();

    // Convenient text setting
    void set_text(const std::string& text);

    // Merge operations
    void merge_with(const std::shared_ptr<Cell>& other);
    bool is_merged() const;
    bool is_first_merged_cell() const;
    bool is_vertical_merge_start() const;
    bool is_vertical_merge_continue() const;
    bool is_horizontal_merge_start() const;
    int get_horizontal_merge_span() const;

    // Parent row access
    std::shared_ptr<class Row> get_parent_row() const;

    // Parent table access
    std::shared_ptr<class Table> get_parent_table() const;

    // Column index
    int get_column_index() const;

    // Cell properties shortcuts
    void set_vertical_alignment(CellVerticalAlignment align);
    CellVerticalAlignment get_vertical_alignment() const;

    void set_width(double width, bool preferred = false);
    double get_width() const;

  private:
    CellFormat format_;
};

// ============================================================================
// CellCollection Class
// ============================================================================

class CellCollection {
    std::vector<std::shared_ptr<Cell>> cells_;

  public:
    using iterator = std::vector<std::shared_ptr<Cell>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Cell>>::const_iterator;

    CellCollection() = default;
    explicit CellCollection(const std::vector<std::shared_ptr<Cell>>& cells) : cells_(cells) {}

    size_t get_count() const { return cells_.size(); }
    std::shared_ptr<Cell> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < cells_.size()) {
            return cells_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Cell> operator[](int index) const { return get_item(index); }

    iterator begin() { return cells_.begin(); }
    iterator end() { return cells_.end(); }
    const_iterator begin() const { return cells_.begin(); }
    const_iterator end() const { return cells_.end(); }

    void add(std::shared_ptr<Cell> cell);
    void remove(std::shared_ptr<Cell> cell);
    void remove_at(int index);
    void clear();
    void insert(int index, std::shared_ptr<Cell> cell);

    std::shared_ptr<Cell> first() const { return cells_.empty() ? nullptr : cells_.front(); }
    std::shared_ptr<Cell> last() const { return cells_.empty() ? nullptr : cells_.back(); }

    std::string get_text() const;
};

// ============================================================================
// Row Class - Table row (CompositeNode containing Cells)
// ============================================================================

class Row : public CompositeNode {
  public:
    Row();
    explicit Row(Document* doc);

    // Node overrides
    NodeType node_type() const override { return NodeType::Row; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;
    std::string get_text() const override;

    // Row format
    RowFormat& get_row_format() { return format_; }
    const RowFormat& get_row_format() const { return format_; }
    void set_row_format(const RowFormat& format) { format_ = format; }

    // Cell access
    CellCollection get_cells() const;
    std::shared_ptr<Cell> get_first_cell() const;
    std::shared_ptr<Cell> get_last_cell() const;
    std::shared_ptr<Cell> get_cell(int index) const;

    // Cell creation
    std::shared_ptr<Cell> append_cell();
    std::shared_ptr<Cell> insert_cell(int index);
    std::shared_ptr<Cell> append_cell(const std::string& text);

    // Insert cells with text
    std::shared_ptr<Cell> append_cells(int count);
    void append_cells(const std::vector<std::string>& texts);

    // Ensure row has at least one cell
    std::shared_ptr<Cell> ensure_minimum();

    // Row properties
    int get_row_index() const;
    bool is_first_row() const;
    bool is_last_row() const;

    // Parent table
    std::shared_ptr<class Table> get_parent_table() const;

  private:
    RowFormat format_;
};

// ============================================================================
// RowCollection Class
// ============================================================================

class RowCollection {
    std::vector<std::shared_ptr<Row>> rows_;

  public:
    using iterator = std::vector<std::shared_ptr<Row>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Row>>::const_iterator;

    RowCollection() = default;
    explicit RowCollection(const std::vector<std::shared_ptr<Row>>& rows) : rows_(rows) {}

    size_t get_count() const { return rows_.size(); }
    std::shared_ptr<Row> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < rows_.size()) {
            return rows_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Row> operator[](int index) const { return get_item(index); }

    iterator begin() { return rows_.begin(); }
    iterator end() { return rows_.end(); }
    const_iterator begin() const { return rows_.begin(); }
    const_iterator end() const { return rows_.end(); }

    void add(std::shared_ptr<Row> row);
    void remove(std::shared_ptr<Row> row);
    void remove_at(int index);
    void clear();
    void insert(int index, std::shared_ptr<Row> row);

    std::shared_ptr<Row> first() const { return rows_.empty() ? nullptr : rows_.front(); }
    std::shared_ptr<Row> last() const { return rows_.empty() ? nullptr : rows_.back(); }
};

// ============================================================================
// Legacy TableCell Class (for backward compatibility)
// ============================================================================

class TableCell {
  private:
    friend class IteratorHelper;

    pugi::xml_node parent_;   ///< Parent row node
    pugi::xml_node current_;  ///< Current w:tc element
    Paragraph paragraph_;     ///< Paragraph iterator for this cell

  public:
    TableCell();
    TableCell(pugi::xml_node parent, pugi::xml_node current);

    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    Paragraph* paragraphs();
    TableCell& next();
    bool has_next() const;
};

// ============================================================================
// Legacy TableRow Class (for backward compatibility)
// ============================================================================

class TableRow {
  private:
    friend class IteratorHelper;

    pugi::xml_node parent_;   ///< Parent table node
    pugi::xml_node current_;  ///< Current w:tr element
    TableCell cell_;          ///< Cell iterator for this row

  public:
    TableRow();
    TableRow(pugi::xml_node parent, pugi::xml_node current);

    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    TableCell& cells();
    bool has_next() const;
    TableRow& next();
};

// ============================================================================
// Table Class - Table (CompositeNode containing Rows)
// ============================================================================

class Table : public CompositeNode {
  public:
    Table();
    explicit Table(Document* doc);
    Table(Document* doc, int rows, int cols);

    // Node overrides
    NodeType node_type() const override { return NodeType::Table; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;
    std::string get_text() const override;

    // Table format
    TableFormat& get_table_format() { return format_; }
    const TableFormat& get_table_format() const { return format_; }
    void set_table_format(const TableFormat& format) { format_ = format; }

    // Row access
    RowCollection get_rows() const;
    std::shared_ptr<Row> get_first_row() const;
    std::shared_ptr<Row> get_last_row() const;
    std::shared_ptr<Row> get_row(int index) const;

    // Row creation
    std::shared_ptr<Row> append_row();
    std::shared_ptr<Row> insert_row(int index);
    std::shared_ptr<Row> append_row(const std::vector<std::string>& cell_texts);
    std::shared_ptr<Row> insert_row(int index, const std::vector<std::string>& cell_texts);

    // Row removal
    void remove_row(const std::shared_ptr<Row>& row);
    void remove_row(int index);
    void remove_all_rows();

    // Cell access (convenience)
    std::shared_ptr<Cell> get_cell(int row, int col) const;

    // Column operations
    void insert_column(int index);
    void delete_column(int index) const;

    // Dimensions
    int get_row_count() const;
    int get_column_count() const;

    // Auto fit
    void auto_fit(AutoFitBehavior behavior);

    // Style
    void set_style(const std::string& style_name);
    void set_style(StyleIdentifier style);
    std::string get_style_name() const;

    // Ensure table has at least one row with one cell
    void ensure_minimum();

    // Merge cells
    std::shared_ptr<Cell> merge_cells(const std::shared_ptr<Cell>& start_cell,
                                      const std::shared_ptr<Cell>& end_cell);
    std::shared_ptr<Cell> merge_cells(int start_row, int start_col, int end_row, int end_col) const;

    // Split cell
    void split_cell(const std::shared_ptr<Cell>& cell, int row_count, int col_count);

    // Convert to text (with optional separator)
    std::string to_text(const std::string& separator = "\t",
                        const std::string& row_separator = "\n") const;

    // Import data
    void import_data(const std::vector<std::vector<std::string>>& data);

    // Check if table is complex (has merged cells, etc.)
    bool is_complex() const;

    // Legacy iterator-style API (deprecated but kept for compatibility)
  private:
    friend class IteratorHelper;

    pugi::xml_node parent_xml_;   ///< Parent body XML node (legacy)
    pugi::xml_node current_xml_;  ///< Current w:tbl XML element (legacy)
    TableRow row_;                ///< Row iterator for this table

  public:
    Table(pugi::xml_node parent, pugi::xml_node current);
    void set_parent_xml(pugi::xml_node node);
    void set_current_xml(pugi::xml_node node);
    pugi::xml_node get_current_xml() const { return current_xml_; }
    pugi::xml_node get_parent_xml() const { return parent_xml_; }

    Table& next();
    bool has_next() const;

    // Legacy row access
    TableRow rows_legacy();

    // Legacy cell access (convenience)
    TableCell cell_at(size_t row, size_t col) const;
    TableCell cell_at_unsafe(size_t row, size_t col) const;
    TableCell merge(size_t start_row, size_t start_col, size_t row_count, size_t col_count);
    void split(size_t row, size_t col);
    void dump_structure() const;
    void set_properties(const TableProperties& props);

    // Preserve original tbl_pr and tbl_grid for round-trip fidelity
    void preserve_tbl_pr(pugi::xml_node tbl_pr);
    pugi::xml_node get_preserved_tbl_pr() const;
    bool has_preserved_tbl_pr() const;

    void preserve_tbl_grid(pugi::xml_node tbl_grid);
    pugi::xml_node get_preserved_tbl_grid() const;
    bool has_preserved_tbl_grid() const;

  private:
    TableFormat format_;
    pugi::xml_document preserved_tbl_pr_;
    pugi::xml_document preserved_tbl_grid_;
};

// ============================================================================
// TableCollection
// ============================================================================

class TableCollection {
    std::vector<std::shared_ptr<Table>> tables_;

  public:
    using iterator = std::vector<std::shared_ptr<Table>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Table>>::const_iterator;

    TableCollection() = default;
    explicit TableCollection(const std::vector<std::shared_ptr<Table>>& tables) : tables_(tables) {}

    size_t get_count() const { return tables_.size(); }
    std::shared_ptr<Table> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < tables_.size()) {
            return tables_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Table> operator[](int index) const { return get_item(index); }

    iterator begin() { return tables_.begin(); }
    iterator end() { return tables_.end(); }
    const_iterator begin() const { return tables_.begin(); }
    const_iterator end() const { return tables_.end(); }

    std::shared_ptr<Table> first() const { return tables_.empty() ? nullptr : tables_.front(); }
    std::shared_ptr<Table> last() const { return tables_.empty() ? nullptr : tables_.back(); }
};

}  // namespace cdocx
