/**
 * @file table_builder.h
 * @brief Table builder for creating and inserting tables
 * @details Provides TableBuilder class for programmatically creating Word tables
 *          with support for borders, cell merging, and content.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.5.0
 */

#pragma once

#include <cdocx/fwd.h>

#include <pugixml.hpp>
#include <string>
#include <vector>

namespace cdocx {

// Forward declaration
class Document;
class Paragraph;

/**
 * @struct TableBorders
 * @brief Table border configuration
 */
struct TableBorders {
    bool top = true;
    bool left = true;
    bool bottom = true;
    bool right = true;
    bool inside_h = true;
    bool inside_v = true;
    std::string color = "auto";
    int size = 4;  // In eighths of a point

    /**
     * @brief No borders preset
     */
    static TableBorders None() {
        TableBorders b;
        b.top = b.left = b.bottom = b.right = b.inside_h = b.inside_v = false;
        return b;
    }

    /**
     * @brief All borders preset (default)
     */
    static TableBorders All() { return TableBorders(); }

    /**
     * @brief Outside borders only preset
     */
    static TableBorders OutsideOnly() {
        TableBorders b;
        b.inside_h = b.inside_v = false;
        return b;
    }
};

/**
 * @struct CellMerge
 * @brief Cell merge configuration
 */
struct CellMerge {
    int row_span = 1;        ///< Number of rows to span
    int col_span = 1;        ///< Number of columns to span
    bool is_restart = true;  ///< true for merge start, false for continue
};

/**
 * @class TableBuilder
 * @brief Builder class for creating tables
 * @since 0.5.0
 *
 * @par Usage Example:
 * @code
 * TableBuilder builder(3, 3);  // 3x3 table
 * builder.SetBorders(TableBorders::All());
 * builder.SetCellText(0, 0, "Cell 1");
 * builder.SetCellText(0, 1, "Cell 2");
 * builder.MergeCells(0, 0, 1, 2);  // Merge first row
 *
 * Paragraph& para = doc.paragraphs();
 * builder.InsertAt(doc, para);
 * @endcode
 */
class TableBuilder {
  public:
    /**
     * @brief Construct table builder with dimensions
     * @param rows Number of rows
     * @param cols Number of columns
     */
    TableBuilder(int rows, int cols);

    /**
     * @brief Destructor
     */
    ~TableBuilder() = default;

    // Disable copy, enable move
    TableBuilder(const TableBuilder&) = delete;
    TableBuilder& operator=(const TableBuilder&) = delete;
    TableBuilder(TableBuilder&&) = default;
    TableBuilder& operator=(TableBuilder&&) = default;

    // ========================================================================
    // Table Properties
    // ========================================================================

    /**
     * @brief Set table borders
     * @param borders Border configuration
     * @return Reference to this builder for chaining
     */
    TableBuilder& SetBorders(const TableBorders& borders);

    /**
     * @brief Set table width
     * @param width Width in twips (1/20 of a point), or 0 for auto
     * @param auto_width true for auto width
     * @return Reference to this builder for chaining
     */
    TableBuilder& SetWidth(int width, bool auto_width = false);

    /**
     * @brief Set cell margins
     * @param top Top margin in twips
     * @param left Left margin in twips
     * @param bottom Bottom margin in twips
     * @param right Right margin in twips
     * @return Reference to this builder for chaining
     */
    TableBuilder& SetCellMargins(int top, int left, int bottom, int right);

    // ========================================================================
    // Cell Content
    // ========================================================================

    /**
     * @brief Set cell text
     * @param row Row index (0-based)
     * @param col Column index (0-based)
     * @param text Text content
     * @return Reference to this builder for chaining
     */
    TableBuilder& SetCellText(int row, int col, const std::string& text);

    /**
     * @brief Set cell text with format
     * @param row Row index
     * @param col Column index
     * @param text Text content
     * @param bold Bold flag
     * @param italic Italic flag
     * @param font_size Font size in half-points
     * @return Reference to this builder for chaining
     */
    TableBuilder& SetCellTextFormatted(
        int row, int col, const std::string& text, bool bold, bool italic, int font_size);

    /**
     * @brief Set cell vertical alignment
     * @param row Row index
     * @param col Column index
     * @param align Alignment ("top", "center", "bottom")
     * @return Reference to this builder for chaining
     */
    TableBuilder& SetCellVerticalAlign(int row, int col, const std::string& align);

    // ========================================================================
    // Cell Merging
    // ========================================================================

    /**
     * @brief Merge cells horizontally
     * @param row Row index
     * @param col Starting column index
     * @param span Number of columns to merge
     * @return Reference to this builder for chaining
     */
    TableBuilder& MergeCellsHorizontal(int row, int col, int span);

    /**
     * @brief Merge cells vertically
     * @param col Column index
     * @param row Starting row index
     * @param span Number of rows to merge
     * @return Reference to this builder for chaining
     */
    TableBuilder& MergeCellsVertical(int col, int row, int span);

    /**
     * @brief Merge cells in a rectangle
     * @param start_row Starting row
     * @param start_col Starting column
     * @param row_span Number of rows
     * @param col_span Number of columns
     * @return Reference to this builder for chaining
     */
    TableBuilder& MergeCells(int start_row, int start_col, int row_span, int col_span);

    // ========================================================================
    // Insertion
    // ========================================================================

    /**
     * @brief Insert table at bookmark location
     * @param doc Document to insert into
     * @param bookmark_name Name of the bookmark
     * @return true if successful
     */
    bool InsertAtBookmark(Document& doc, const std::string& bookmark_name);

    /**
     * @brief Insert table after a paragraph
     * @param doc Document to insert into
     * @param para Paragraph to insert after
     * @return true if successful
     */
    bool InsertAfterParagraph(Document& doc, Paragraph& para);

    /**
     * @brief Build the table XML node
     * @param doc_xml Document XML to create nodes in
     * @return Created table node
     */
    pugi::xml_node Build(pugi::xml_document& doc_xml) const;

  private:
    int rows_;
    int cols_;
    TableBorders borders_;
    int width_ = 0;
    bool auto_width_ = true;
    int cell_margin_top_ = 0;
    int cell_margin_left_ = 108;
    int cell_margin_bottom_ = 0;
    int cell_margin_right_ = 108;

    // Cell data storage
    struct CellData {
        std::string text;
        bool bold = false;
        bool italic = false;
        int font_size = 0;  // 0 = use default
        std::string v_align;
        int row_span = 1;
        int col_span = 1;
        bool is_vmerge_restart = false;
    };
    std::vector<std::vector<CellData>> cells_;

    void CreateTableStructure(pugi::xml_node tbl) const;
    void CreateCell(pugi::xml_node tr, int row, int col) const;
};

/**
 * @brief Insert a simple table at bookmark location
 * @param doc Target document
 * @param bookmark_name Bookmark name
 * @param rows Number of rows
 * @param cols Number of columns
 * @param headers Optional header row texts
 * @param data Table data (row by row)
 * @return true if successful
 *
 * @par Example:
 * @code
 * InsertSimpleTable(doc, "TABLE_BOOKMARK", 3, 2,
 *                   {"Name", "Value"},
 *                   {{"Item1", "100"}, {"Item2", "200"}});
 * @endcode
 */
bool InsertSimpleTable(Document& doc,
                       const std::string& bookmark_name,
                       int rows,
                       int cols,
                       const std::vector<std::string>& headers,
                       const std::vector<std::vector<std::string>>& data);

/**
 * @brief Insert table with caption
 * @param doc Target document
 * @param bookmark_name Bookmark name
 * @param table_builder Configured table builder
 * @param caption Table caption text
 * @param caption_above true for caption above table, false for below
 * @return true if successful
 */
bool InsertTableWithCaption(Document& doc,
                            const std::string& bookmark_name,
                            TableBuilder& table_builder,
                            const std::string& caption,
                            bool caption_above = true);

// ============================================================================
// Table Caption Functions
// ============================================================================

/**
 * @brief Get the next table number for caption
 * @param[in] doc Target document
 * @return Next available table number (count + 1)
 */
int get_next_table_number(Document* doc);

/**
 * @brief Count existing tables with captions in document
 * @param[in] doc Target document
 * @return Number of table captions detected
 * @details Searches for paragraphs starting with "表 X" pattern
 */
int count_existing_tables(Document* doc);

/**
 * @brief Check if paragraph is a table caption
 * @param[in] para Paragraph node to check
 * @return true if paragraph starts with "表 X" pattern
 */
bool is_table_caption(pugi::xml_node para);

/**
 * @brief Insert a table caption after specified node
 * @param[in] doc Target document
 * @param[in] after_node Node after which to insert caption (table node)
 * @param[in] description Caption description text
 * @param[in] table_number Table number (auto-generated if 0)
 * @return The created caption paragraph node, or empty node on failure
 * @details Generates caption in format "表 X description" with Chinese formatting
 */
pugi::xml_node insert_table_caption(Document* doc,
                                    pugi::xml_node after_node,
                                    const std::string& description,
                                    int table_number = 0);

}  // namespace cdocx
