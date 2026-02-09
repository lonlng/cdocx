/**
 * @file base.h
 * @brief Base content classes for CDocx document model
 * @details Defines the fundamental content classes: Run, Paragraph, TableCell,
 *          TableRow, and Table. These classes provide the core document
 *          structure and content manipulation capabilities.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 * 
 * @par 文档结构层次：
 * @code
 * Document
 * ├── Body
 * │   ├── Paragraph (contains Runs)
 * │   │   └── Run (formatted text segment)
 * │   └── Table (contains TableRows)
 * │       └── TableRow (contains TableCells)
 * │           └── TableCell (contains Paragraphs)
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/constants.h>
#include <pugixml.hpp>
#include <string>

namespace cdocx {

// Forward declaration for iterator helper
class IteratorHelper;

/**
 * @class Run
 * @brief Represents a formatted text segment (run) within a paragraph
 * @details A Run is the smallest unit of text with uniform formatting.
 *          Multiple runs can exist in a paragraph, each with different
 *          formatting attributes (bold, italic, font, color, etc.).
 * 
 * @par 使用示例：
 * @code
 * auto para = doc.paragraphs();
 * auto run = para.runs();
 * 
 * // 修改文本
 * run.set_text("New text");
 * 
 * // 应用格式
 * run.set_bold(true);
 * run.set_color("FF0000");  // 红色
 * run.set_font_size(24);    // 12pt
 * @endcode
 * 
 * @see Paragraph, formatting_flag
 * @since 0.1.0
 */
class Run {
private:
    friend class IteratorHelper;  ///< Grants access to set_parent/set_current
    
    pugi::xml_node parent_;   ///< Parent paragraph node
    pugi::xml_node current_;  ///< Current w:r element

public:
    /**
     * @brief Default constructor
     * @details Creates an empty run with null nodes
     */
    Run();
    
    /**
     * @brief Construct run with parent and current nodes
     * @param[in] parent The parent paragraph XML node
     * @param[in] current The current w:r XML node
     */
    Run(pugi::xml_node parent, pugi::xml_node current);

    /**
     * @brief Set the parent node and initialize to first run
     * @param[in] node The parent paragraph node
     */
    void set_parent(pugi::xml_node node);
    
    /**
     * @brief Set the current node directly
     * @param[in] node The w:r element to set as current
     */
    void set_current(pugi::xml_node node);
    
    /**
     * @brief Get the current XML node
     * @return The current w:r XML node
     */
    pugi::xml_node get_current() const;
    
    /**
     * @brief Get the parent XML node
     * @return The parent paragraph XML node
     */
    pugi::xml_node get_parent() const;

    /**
     * @brief Get the text content of this run
     * @return The text string (empty if no text)
     */
    std::string get_text() const;
    
    /**
     * @brief Set the text content of this run
     * @param[in] text The new text content
     * @return true if successful, false if run is invalid
     */
    bool set_text(const std::string& text) const;
    
    /**
     * @brief Set the text content (C-string version)
     * @param[in] text The new text content (null-terminated)
     * @return true if successful, false if run is invalid
     */
    bool set_text(const char* text) const;

    /**
     * @brief Move to the next run in the paragraph
     * @return Reference to this run (now pointing to next sibling)
     */
    Run& next();
    
    /**
     * @brief Check if this run is valid (has a current node)
     * @return true if valid, false if at end or invalid
     */
    bool has_next() const;

    // ========================================================================
    // Formatting Methods
    // ========================================================================
    
    /**
     * @brief Set the text color
     * @param[in] color_hex Hex color code (e.g., "FF0000" for red)
     * @return true if successful
     */
    bool set_color(const std::string& color_hex);
    
    /**
     * @brief Set the font size
     * @param[in] size Font size in half-points (e.g., 24 for 12pt)
     * @return true if successful
     */
    bool set_font_size(int size);
    
    /**
     * @brief Set the font name
     * @param[in] font_name Font family name (e.g., "Arial", "Times New Roman")
     * @return true if successful
     */
    bool set_font_name(const std::string& font_name);
    
    /**
     * @brief Set bold formatting
     * @param[in] bold true to apply bold, false to remove
     * @return true if successful
     */
    bool set_bold(bool bold);
    
    /**
     * @brief Set italic formatting
     * @param[in] italic true to apply italic, false to remove
     * @return true if successful
     */
    bool set_italic(bool italic);
    
    /**
     * @brief Set underline formatting
     * @param[in] underline true to apply underline, false to remove
     * @return true if successful
     */
    bool set_underline(bool underline);
};

/**
 * @class Paragraph
 * @brief Represents a paragraph in the document
 * @details A Paragraph is a block-level element containing one or more Run
 *          objects. It can have paragraph-level formatting (alignment,
 *          indentation, spacing, etc.) and contains the actual text content.
 * 
 * @par 使用示例：
 * @code
 * auto para = doc.paragraphs();
 * 
 * // 添加格式化的文本运行
 * para.add_run("Bold text", cdocx::bold);
 * para.add_run("Italic text", cdocx::italic);
 * 
 * // 设置段落格式
 * para.set_alignment("center");
 * para.set_line_spacing(360);  // 1.5 line spacing
 * para.set_indent(720, -1, 0); // Left indent 0.5 inch
 * @endcode
 * 
 * @see Run, Table
 * @since 0.1.0
 */
class Paragraph {
private:
    friend class IteratorHelper;  ///< Grants access to set_parent/set_current
    
    pugi::xml_node parent_;   ///< Parent body/table cell node
    pugi::xml_node current_;  ///< Current w:p element
    Run run_;                 ///< Run iterator for this paragraph

public:
    /**
     * @brief Default constructor
     * @details Creates an empty paragraph with null nodes
     */
    Paragraph();
    
    /**
     * @brief Construct paragraph with parent and current nodes
     * @param[in] parent The parent body or cell node
     * @param[in] current The current w:p element
     */
    Paragraph(pugi::xml_node parent, pugi::xml_node current);

    /**
     * @brief Set the parent node and initialize to first paragraph
     * @param[in] node The parent body or cell node
     */
    void set_parent(pugi::xml_node node);
    
    /**
     * @brief Set the current node directly
     * @param[in] node The w:p element to set as current
     */
    void set_current(pugi::xml_node node);

    /**
     * @brief Move to the next paragraph
     * @return Reference to this paragraph (now pointing to next sibling)
     */
    Paragraph& next();
    
    /**
     * @brief Check if this paragraph is valid
     * @return true if valid, false if at end or invalid
     */
    bool has_next() const;

    /**
     * @brief Get the runs iterator for this paragraph
     * @return Reference to the Run iterator
     */
    Run& runs();
    
    /**
     * @brief Add a new run with text and formatting
     * @param[in] text The text content
     * @param[in] flag Formatting flags (default: none)
     * @return Reference to the new Run
     */
    Run& add_run(const std::string& text, formatting_flag flag = none);
    
    /**
     * @brief Add a new run (C-string version)
     * @param[in] text The text content (null-terminated)
     * @param[in] flag Formatting flags (default: none)
     * @return Reference to the new Run
     */
    Run& add_run(const char* text, formatting_flag flag = none);
    
    /**
     * @brief Remove a run from this paragraph
     * @param[in] r The run to remove
     */
    void remove_run(const Run& r);
    
    /**
     * @brief Insert a new paragraph after this one
     * @param[in] text Initial text content
     * @param[in] flag Formatting flags for initial run
     * @return Reference to the new Paragraph
     */
    Paragraph& insert_paragraph_after(const std::string& text,
                                       formatting_flag flag = none);
    
    /**
     * @brief Get all text in this paragraph
     * @return Concatenated text from all runs
     */
    std::string get_text() const;
    
    /**
     * @brief Clear all content from this paragraph
     * @return true if successful
     */
    bool clear();
    
    /**
     * @brief Remove this paragraph from the document
     * @return true if successful
     */
    bool remove();
    
    /**
     * @brief Insert a new paragraph before this one
     * @param[in] text Initial text content
     * @param[in] flag Formatting flags for initial run
     * @return Pointer to the new Paragraph
     */
    Paragraph* insert_before(const std::string& text, formatting_flag flag = none);

    // ========================================================================
    // Paragraph Formatting Methods
    // ========================================================================
    
    /**
     * @brief Set paragraph alignment
     * @param[in] alignment Alignment value: "left", "center", "right", "justify"
     * @return true if successful
     */
    bool set_alignment(const std::string& alignment);
    
    /**
     * @brief Set paragraph style
     * @param[in] style_id Style identifier (e.g., "Heading1", "Normal")
     * @return true if successful
     */
    bool set_style(const std::string& style_id);
    
    /**
     * @brief Set line spacing
     * @param[in] line_spacing Line spacing in twips (240 = single, 360 = 1.5, 480 = double)
     * @param[in] is_exact true for exact spacing, false for auto
     * @return true if successful
     */
    bool set_line_spacing(int line_spacing, bool is_exact = false);
    
    /**
     * @brief Set spacing before paragraph
     * @param[in] spacing Spacing in twips
     * @return true if successful
     */
    bool set_spacing_before(int spacing);
    
    /**
     * @brief Set spacing after paragraph
     * @param[in] spacing Spacing in twips
     * @return true if successful
     */
    bool set_spacing_after(int spacing);
    
    /**
     * @brief Set paragraph indentation
     * @param[in] left Left indent in twips (-1 to ignore)
     * @param[in] right Right indent in twips (-1 to ignore)
     * @param[in] first_line First line indent in twips (0 to ignore)
     * @return true if successful
     */
    bool set_indent(int left = -1, int right = -1, int first_line = 0);
    
    /**
     * @brief Get the current XML node (for advanced operations)
     * @return The w:p element
     */
    pugi::xml_node get_current_node() const { return current_; }
    
    /**
     * @brief Get the parent XML node (for advanced operations)
     * @return The parent body or cell node
     */
    pugi::xml_node get_parent_node() const { return parent_; }
};

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

/**
 * @class Table
 * @brief Represents a table in the document
 * @details A Table is a block-level element containing one or more TableRow
 *          objects. It can have table-level properties (width, borders,
 *          alignment, etc.).
 * 
 * @par 使用示例：
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
class Table {
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
};

} // namespace cdocx
