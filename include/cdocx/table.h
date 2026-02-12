/**
 * @file table.h
 * @brief Table classes for CDocx
 * @details Table, Row, Cell with full formatting support
 */

#pragma once

#include <pugixml.hpp>

#include <cdocx/node.h>
#include <cdocx/format.h>
#include <cdocx/paragraph.h>
#include <memory>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations
class Document;
class Body;
class Paragraph;
class ParagraphCollection;


/**
 * @class TableCell
 * @brief Represents a cell in a table
 * @details A TableCell contains one or more Paragraph objects and can have
 *          cell-specific properties (width, borders, shading, etc.).
 * 
 * @see TableRow, Table, Paragraph
 * @since 0.1.0
 */
class TableCell {
private:
    friend class IteratorHelper;
    
    pugi::xml_node parent_;      ///< Parent row node
    pugi::xml_node current_;     ///< Current w:tc element
    Paragraph paragraph_;        ///< Paragraph iterator for this cell

public:
    /**
     * @brief Default constructor
     */
    TableCell();
    
    /**
     * @brief Construct cell with parent and current nodes
     * @param[in] parent The parent row node
     * @param[in] current The current w:tc element
     */
    TableCell(pugi::xml_node parent, pugi::xml_node current);

    /**
     * @brief Set the parent node and initialize to first cell
     * @param[in] node The parent row node
     */
    void set_parent(pugi::xml_node node);
    
    /**
     * @brief Set the current node directly
     * @param[in] node The w:tc element to set as current
     */
    void set_current(pugi::xml_node node);

    /**
     * @brief Get the paragraphs iterator for this cell
     * @return Reference to the Paragraph iterator
     */
    Paragraph& paragraphs();

    /**
     * @brief Move to the next cell in the row
     * @return Reference to this cell (now pointing to next sibling)
     */
    TableCell& next();
    
    /**
     * @brief Check if this cell is valid
     * @return true if valid, false if at end or invalid
     */
    bool has_next() const;
};

/**
 * @class TableRow
 * @brief Represents a row in a table
 * @details A TableRow contains one or more TableCell objects arranged
 *          horizontally.
 * 
 * @see TableCell, Table
 * @since 0.1.0
 */
class TableRow {
private:
    friend class IteratorHelper;
    
    pugi::xml_node parent_;   ///< Parent table node
    pugi::xml_node current_;  ///< Current w:tr element
    TableCell cell_;          ///< Cell iterator for this row

public:
    /**
     * @brief Default constructor
     */
    TableRow();
    
    /**
     * @brief Construct row with parent and current nodes
     * @param[in] parent The parent table node
     * @param[in] current The current w:tr element
     */
    TableRow(pugi::xml_node parent, pugi::xml_node current);
    
    /**
     * @brief Set the parent node and initialize to first row
     * @param[in] node The parent table node
     */
    void set_parent(pugi::xml_node node);
    
    /**
     * @brief Set the current node directly
     * @param[in] node The w:tr element to set as current
     */
    void set_current(pugi::xml_node node);

    /**
     * @brief Get the cells iterator for this row
     * @return Reference to the TableCell iterator
     */
    TableCell& cells();

    /**
     * @brief Check if this row is valid
     * @return true if valid, false if at end or invalid
     */
    bool has_next() const;
    
    /**
     * @brief Move to the next row in the table
     * @return Reference to this row (now pointing to next sibling)
     */
    TableRow& next();
};


// ============================================================================
// Cell Class
// ============================================================================

class Cell : public CompositeNode {
public:
    Cell();
    explicit Cell(Document* doc);
    
    // Cell format
    CellFormat& get_cell_format() { return format_; }
    const CellFormat& get_cell_format() const { return format_; }
    
    // Content access
    ParagraphCollection get_paragraphs();
    std::shared_ptr<Paragraph> get_first_paragraph();
    
    // Ensure cell has at least one paragraph
    std::shared_ptr<Paragraph> ensure_minimum();
    
    // Content creation
    std::shared_ptr<Paragraph> append_paragraph(const std::string& text = "");
    std::shared_ptr<Paragraph> insert_paragraph(int index, const std::string& text = "");
    
    // Convenient text setting
    void set_text(const std::string& text);
    std::string get_text() const override;
    
    // Merge operations
    void merge_with(std::shared_ptr<Cell> other);
    bool is_merged() const;
    bool is_first_merged_cell() const;
    bool is_vertical_merge_start() const;
    bool is_vertical_merge_continue() const;
    bool is_horizontal_merge_start() const;
    int get_horizontal_merge_span() const;
    
    // Parent row access
    std::shared_ptr<class Row> get_parent_row();
    
    // Column index
    int get_column_index() const;
    
    // Cell properties shortcuts
    void set_vertical_alignment(CellVerticalAlignment align);
    CellVerticalAlignment get_vertical_alignment() const;
    
    void set_width(double width, bool preferred = false);
    double get_width() const;
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Cell; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
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
    
    size_t get_count() const { return cells_.size(); }
    std::shared_ptr<Cell> get_item(int index) const;
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
    
    std::shared_ptr<Cell> first() const;
    std::shared_ptr<Cell> last() const;
    
    // Get all text from all cells
    std::string get_text() const;
};

// ============================================================================
// Row Class
// ============================================================================

class Row : public CompositeNode {
public:
    Row();
    explicit Row(Document* doc);
    
    // Row format
    RowFormat& get_row_format() { return format_; }
    const RowFormat& get_row_format() const { return format_; }
    
    // Cell access
    CellCollection get_cells();
    std::shared_ptr<Cell> get_first_cell();
    std::shared_ptr<Cell> get_last_cell();
    std::shared_ptr<Cell> get_cell(int index);
    
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
    std::shared_ptr<class Table> get_parent_table();
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Row; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
    // Text content
    std::string get_text() const override;
    
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
    
    size_t get_count() const { return rows_.size(); }
    std::shared_ptr<Row> get_item(int index) const;
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
    
    std::shared_ptr<Row> first() const;
    std::shared_ptr<Row> last() const;
};


/**
 * @class Table
 * @brief Represents a table in the document
 * @details A Table is a block-level element containing one or more TableRow
 *          objects. It can have table-level properties (width, borders,
 *          alignment, etc.).
 * 
 * @par Usage Example:
 * @code
 * auto table = doc.tables();
 * 
 * while (table.has_next()) {
 *     auto row = table.rows();
 *     while (row.has_next()) {
 *         auto cell = row.cells();
 *         while (cell.has_next()) {
 *             auto para = cell.paragraphs();
 *             std::cout << para.get_text() << std::endl;
 *             cell.next();
 *         }
 *         row.next();
 *     }
 *     table.next();
 * }
 * @endcode
 * 
 * @see TableRow, TableCell
 * @since 0.1.0
 */
class Table : public CompositeNode {
public:
    // Table();
    explicit Table(Document* doc);
    
    // Create table with dimensions
    Table(Document* doc, int rows, int cols);
    
    // Table format
    TableFormat& get_table_format() { return format_; }
    const TableFormat& get_table_format() const { return format_; }
    
    // Row access
    RowCollection get_rows();
    std::shared_ptr<Row> get_first_row();
    std::shared_ptr<Row> get_last_row();
    std::shared_ptr<Row> get_row(int index);
    
    // Row creation
    std::shared_ptr<Row> append_row();
    std::shared_ptr<Row> insert_row(int index);
    std::shared_ptr<Row> append_row(const std::vector<std::string>& cell_texts);
    std::shared_ptr<Row> insert_row(int index, const std::vector<std::string>& cell_texts);
    
    // Row removal
    void remove_row(std::shared_ptr<Row> row);
    void remove_row(int index);
    void remove_all_rows();
    
    // Cell access (convenience)
    std::shared_ptr<Cell> get_cell(int row, int col);
    
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
    std::shared_ptr<Cell> merge_cells(std::shared_ptr<Cell> start_cell, 
                                       std::shared_ptr<Cell> end_cell);
    std::shared_ptr<Cell> merge_cells(int start_row, int start_col,
                                       int end_row, int end_col);
    
    // Split cell
    void split_cell(std::shared_ptr<Cell> cell, int row_count, int col_count);
    
    // Convert to text (with optional separator)
    std::string to_text(const std::string& separator = "\t", 
                        const std::string& row_separator = "\n") const;
    
    // Import data
    void import_data(const std::vector<std::vector<std::string>>& data);
    
    // Check if table is complex (has merged cells, etc.)
    bool is_complex() const;
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Table; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string get_text() const override;
    
private:
    TableFormat format_;    
private:
    friend class IteratorHelper;
    
    pugi::xml_node parent_;   ///< Parent body node
    pugi::xml_node current_;  ///< Current w:tbl element
    TableRow row_;            ///< Row iterator for this table

public:
    /**
     * @brief Default constructor
     */
    Table();
    
    /**
     * @brief Construct table with parent and current nodes
     * @param[in] parent The parent body node
     * @param[in] current The current w:tbl element
     */
    Table(pugi::xml_node parent, pugi::xml_node current);
    
    /**
     * @brief Set the parent node and initialize to first table
     * @param[in] node The parent body node
     */
    void set_parent(pugi::xml_node node);
    
    /**
     * @brief Set the current node directly
     * @param[in] node The w:tbl element to set as current
     */
    void set_current(pugi::xml_node node);

    /**
     * @brief Move to the next table in the document
     * @return Reference to this table (now pointing to next sibling)
     */
    Table& next();
    
    /**
     * @brief Check if this table is valid
     * @return true if valid, false if at end or invalid
     */
    bool has_next() const;

    /**
     * @brief Get the rows iterator for this table
     * @return Reference to the TableRow iterator
     */
    TableRow& rows();
    
    // ===================================================================
    // Enhanced Table Operations (v0.4.0)
    // ===================================================================
    
    /**
     * @brief Access cell at specific position (with bounds checking)
     * @param[in] row Row index (0-based)
     * @param[in] col Column index (0-based)
     * @return TableCell at the position (may be invalid if out of bounds)
     * @since 0.4.0
     */
    TableCell cellAt(size_t row, size_t col) const;
    
    /**
     * @brief Access cell at specific position (no bounds checking)
     * @param[in] row Row index (0-based)
     * @param[in] col Column index (0-based)
     * @return TableCell at the position (undefined if out of bounds)
     * @since 0.4.0
     */
    TableCell cellAtUnsafe(size_t row, size_t col) const;
    
    /**
     * @brief Get number of rows
     * @return Row count
     * @since 0.4.0
     */
    size_t getRowCount() const;
    
    /**
     * @brief Get number of columns (max columns in any row)
     * @return Column count
     * @since 0.4.0
     */
    size_t getColumnCount() const;
    
    /**
     * @brief Merge cells in a range
     * @param[in] startRow Start row index
     * @param[in] startCol Start column index
     * @param[in] rowCount Number of rows to merge
     * @param[in] colCount Number of columns to merge
     * @return The merged cell
     * @since 0.4.0
     */
    TableCell merge(size_t startRow, size_t startCol, 
                    size_t rowCount, size_t colCount);
    
    /**
     * @brief Split a merged cell
     * @param[in] row Row index of the merged cell
     * @param[in] col Column index of the merged cell
     * @since 0.4.0
     */
    void split(size_t row, size_t col);
    
    /**
     * @brief Dump table structure to console (for debugging)
     * @since 0.4.0
     */
    void dumpStructure() const;
    
    /**
     * @brief Apply table properties
     * @param[in] props TableProperties structure
     * @since 0.4.0
     */
    void set_properties(const TableProperties& props);
};


} // namespace cdocx
