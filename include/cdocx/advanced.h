/**
 * @file advanced.h
 * @brief Advanced features for CDocx document manipulation
 * @details Provides advanced functionality including:
 *          - Bookmark management (create, read, update, delete bookmarks)
 *          - Document range operations (text extraction, replacement)
 *          - DocumentBuilder for fluent document construction
 *          - DocumentSearch for find and replace operations
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 * 
 * @par Usage Example:
 * @code
 * #include <cdocx/advanced.h>
 * 
 * // ========== Bookmarks ==========
 * auto bookmarks = doc.get_bookmarks();
 * auto bm = bookmarks.get("Section1");
 * if (bm) {
 *     bm->set_text("New content");
 * }
 * 
 * // ========== DocumentBuilder ==========
 * cdocx::DocumentBuilder builder(&doc);
 * builder.move_to_document_end();
 * builder.set_bold(true);
 * builder.set_font_size(24);
 * builder.writeln("Chapter 1");
 * builder.clear_formatting();
 * 
 * // Create table
 * builder.start_table();
 * builder.insert_row();
 * builder.insert_cell();
 * builder.write("Cell 1");
 * builder.insert_cell();
 * builder.write("Cell 2");
 * builder.end_row();
 * builder.end_table();
 * 
 * // ========== Search and Replace ==========
 * cdocx::DocumentSearch::replace_all(doc, "old", "new");
 * int count = cdocx::DocumentSearch::replace_all(doc, "TODO", "DONE");
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/base.h>
#include <cdocx/constants.h>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace cdocx {

// Forward declarations
class Range;
class DocumentSearch;

// ============================================================================
// Bookmark Classes
// ============================================================================

/**
 * @class Bookmark
 * @brief Represents a bookmark in the document
 * @details A bookmark marks a location or range in the document that can be
 *          referenced by name. Bookmarks can be used for navigation,
 *          cross-references, or as placeholders for content replacement.
 * 
 * @par Usage Example:
 * @code
 * auto bookmarks = doc.get_bookmarks();
 * 
 * // Get bookmark by name
 * auto bm = bookmarks.get("Introduction");
 * if (bm) {
 *     std::string text = bm->get_text();
 *     bm->set_text("New introduction text");
 *     bm->remove();  // Delete bookmark but keep text
 * }
 * @endcode
 * 
 * @see BookmarkCollection
 * @since 0.2.0
 */
class Bookmark {
private:
    friend class Document;           ///< Grants access to private constructor
    friend class BookmarkCollection; ///< Grants access to internal members
    
    Document* doc_;              ///< Owning document
    std::string name_;           ///< Bookmark name
    pugi::xml_node start_node_;  ///< Bookmark start marker node
    pugi::xml_node end_node_;    ///< Bookmark end marker node

public:
    /**
     * @brief Default constructor
     * @details Creates an invalid bookmark
     */
    Bookmark();

    /**
     * @brief Construct bookmark with all properties
     * @param[in] doc Owning document
     * @param[in] name Bookmark name
     * @param[in] start Start marker node
     * @param[in] end End marker node
     */
    Bookmark(Document* doc, const std::string& name,
             pugi::xml_node start, pugi::xml_node end);

    /**
     * @brief Get bookmark name
     * @return The bookmark name
     */
    std::string get_name() const;

    /**
     * @brief Set bookmark name
     * @param[in] name New name for the bookmark
     */
    void set_name(const std::string& name);

    /**
     * @brief Get text content within the bookmark range
     * @return Concatenated text from all runs within bookmark
     */
    std::string get_text() const;

    /**
     * @brief Set text content within the bookmark range
     * @param[in] text New text content
     * @return true if successful
     */
    bool set_text(const std::string& text);

    /**
     * @brief Check if bookmark is valid
     * @return true if both start and end markers exist
     */
    bool is_valid() const;

    /**
     * @brief Remove the bookmark but keep the content
     * @return true if successful
     * @details Removes the bookmark markers but preserves the text
     */
    bool remove();

    /**
     * @brief Remove the bookmark and its content
     * @return true if successful
     * @details Removes both the bookmark markers and all enclosed content
     */
    bool remove_with_content();
};

/**
 * @class BookmarkCollection
 * @brief Collection of bookmarks in a document
 * @details Provides access to all bookmarks in the document. Bookmarks are
 *          collected on first access and cached for performance.
 * 
 * @par Usage Example:
 * @code
 * auto bookmarks = doc.get_bookmarks();
 * 
 * // Iterate all bookmarks
 * for (auto& bm : bookmarks) {
 *     std::cout << bm.get_name() << std::endl;
 * }
 * 
 * // Check if exists
 * if (bookmarks.contains("Summary")) {
 *     // ...
 * }
 * 
 * // Delete bookmark
 * bookmarks.remove("TempBookmark");
 * @endcode
 * 
 * @see Bookmark
 * @since 0.2.0
 */
class BookmarkCollection {
private:
    friend class Document;  ///< Grants access to private constructor
    
    Document* doc_;                    ///< Owning document
    mutable std::vector<Bookmark> bookmarks_;  ///< Cached bookmarks
    mutable bool collected_ = false;   ///< Collection status flag

    /**
     * @brief Collect all bookmarks from document
     * @details Scans the document for bookmark markers and populates
     *          the bookmarks vector. Called on first access.
     */
    void collect_bookmarks() const;

public:
    /**
     * @brief Construct collection for a document
     * @param[in] doc Target document
     */
    explicit BookmarkCollection(Document* doc);

    /**
     * @brief Get bookmark count
     * @return Number of bookmarks in document
     */
    size_t count() const;

    /**
     * @brief Get bookmark by index
     * @param[in] index Zero-based index
     * @return The bookmark at specified index
     * @pre index < count()
     */
    Bookmark get(size_t index) const;

    /**
     * @brief Get bookmark by name
     * @param[in] name Bookmark name (case-insensitive)
     * @return Bookmark if found, std::nullopt otherwise
     */
    std::optional<Bookmark> get(const std::string& name) const;

    /**
     * @brief Check if bookmark exists
     * @param[in] name Bookmark name (case-insensitive)
     * @return true if bookmark exists
     */
    bool contains(const std::string& name) const;

    /**
     * @brief Remove bookmark by name
     * @param[in] name Bookmark name to remove
     * @return true if bookmark was found and removed
     */
    bool remove(const std::string& name);

    /**
     * @brief Remove bookmark by index
     * @param[in] index Zero-based index
     * @return true if index is valid and bookmark was removed
     */
    bool remove_at(size_t index);

    /**
     * @brief Remove all bookmarks
     */
    void clear();

    /**
     * @brief Add a new bookmark at paragraph position
     * @param[in] name Bookmark name
     * @param[in] para Target paragraph
     * @return The newly created bookmark
     */
    Bookmark add(const std::string& name, Paragraph& para);

    // Iterator support
    std::vector<Bookmark>::iterator begin();
    std::vector<Bookmark>::iterator end();
    std::vector<Bookmark>::const_iterator begin() const;
    std::vector<Bookmark>::const_iterator end() const;
};

// ============================================================================
// Range Class
// ============================================================================

/**
 * @class Range
 * @brief Represents a range within the document
 * @details A Range specifies a portion of the document between two points.
 *          It can be used for text extraction, replacement, and deletion
 *          operations within a specific area.
 * 
 * @see DocumentSearch
 * @since 0.2.0
 */
class Range {
private:
    friend class Document;       ///< Grants access to private constructor
    friend class DocumentSearch; ///< Grants access to search operations
    
    Document* doc_;              ///< Owning document
    pugi::xml_node start_para_;  ///< Start paragraph node
    pugi::xml_node end_para_;    ///< End paragraph node
    size_t start_offset_;        ///< Character offset in start paragraph
    size_t end_offset_;          ///< Character offset in end paragraph

public:
    /**
     * @brief Default constructor
     */
    Range();

    /**
     * @brief Construct range with boundaries
     * @param[in] doc Owning document
     * @param[in] start Start paragraph
     * @param[in] end End paragraph
     */
    Range(Document* doc, pugi::xml_node start, pugi::xml_node end);

    /**
     * @brief Get all text in the range
     * @return Concatenated text from all paragraphs in range
     */
    std::string get_text() const;

    /**
     * @brief Replace first occurrence of text in range
     * @param[in] old_text Text to find
     * @param[in] new_text Replacement text
     * @return true if replacement was made
     */
    bool replace(const std::string& old_text, const std::string& new_text);

    /**
     * @brief Replace all occurrences of text in range
     * @param[in] old_text Text to find
     * @param[in] new_text Replacement text
     * @return Number of replacements made
     */
    int replace_all(const std::string& old_text, const std::string& new_text);

    /**
     * @brief Delete all content in the range
     * @return true if successful
     */
    bool delete_content();

    /**
     * @brief Check if range is valid
     * @return true if range has valid boundaries
     */
    bool is_valid() const;

    /**
     * @brief Collapse range to a single point
     * @param[in] to_start If true, collapse to start; otherwise to end
     */
    void collapse(bool to_start = true);
};

// ============================================================================
// Table Operations
// ============================================================================

/**
 * @class TableOperations
 * @brief Static utility class for table manipulation
 * @details Provides static methods for common table operations such as
 *          inserting/deleting rows and cells, merging cells, etc.
 * 
 * @see Table, TableRow, TableCell
 * @since 0.2.0
 */
class TableOperations {
public:
    /**
     * @brief Insert a row at specified index
     * @param[in,out] table Target table
     * @param[in] index Row index (0-based)
     * @return true if successful
     */
    static bool insert_row(Table& table, size_t index);

    /**
     * @brief Append a row at the end
     * @param[in,out] table Target table
     * @return true if successful
     */
    static bool append_row(Table& table);

    /**
     * @brief Delete a row at specified index
     * @param[in,out] table Target table
     * @param[in] index Row index (0-based)
     * @return true if successful
     */
    static bool delete_row(Table& table, size_t index);

    /**
     * @brief Insert a cell at specified position
     * @param[in,out] row Target row
     * @param[in] index Cell index (0-based)
     * @return true if successful
     */
    static bool insert_cell(TableRow& row, size_t index);

    /**
     * @brief Delete a cell at specified position
     * @param[in,out] row Target row
     * @param[in] index Cell index (0-based)
     * @return true if successful
     */
    static bool delete_cell(TableRow& row, size_t index);

    /**
     * @brief Get row count
     * @param[in] table Target table
     * @return Number of rows
     */
    static size_t get_row_count(const Table& table);

    /**
     * @brief Get column count (maximum cells in any row)
     * @param[in] table Target table
     * @return Maximum number of cells in any row
     */
    static size_t get_column_count(const Table& table);

    /**
     * @brief Merge cells horizontally
     * @param[in,out] row Target row
     * @param[in] start Start cell index
     * @param[in] end End cell index (inclusive)
     * @return true if successful
     */
    static bool merge_cells_horizontal(TableRow& row, size_t start, size_t end);

    /**
     * @brief Set cell text
     * @param[in,out] cell Target cell
     * @param[in] text New text content
     * @return true if successful
     */
    static bool set_cell_text(TableCell& cell, const std::string& text);

    /**
     * @brief Get cell text
     * @param[in] cell Target cell
     * @return Cell text content
     */
    static std::string get_cell_text(const TableCell& cell);
};

// ============================================================================
// DocumentBuilder Class
// ============================================================================

/**
 * @class DocumentBuilder
 * @brief Fluent API for building documents programmatically
 * @details DocumentBuilder provides a convenient way to construct documents
 *          without manually managing XML nodes. It maintains a cursor position
 *          and formatting state, allowing for intuitive document construction.
 * 
 * @par Main Features:
 * - Navigation: Move to any position in document
 * - Writing: Add formatted text
 * - Tables: Create and populate tables
 * - Bookmarks: Create bookmark markers
 * - Hyperlinks: Insert hyperlinks
 * - Images: Insert images
 * 
 * @par Usage Example:
 * @code
 * cdocx::DocumentBuilder builder(&doc);
 * 
 * // Write formatted text
 * builder.set_bold(true);
 * builder.set_font_size(24);
 * builder.writeln("Title");
 * builder.clear_formatting();
 * 
 * // Create table
 * builder.start_table();
 * for (int i = 0; i < 3; i++) {
 *     builder.insert_row();
 *     for (int j = 0; j < 2; j++) {
 *         builder.insert_cell();
 *         builder.write("Cell " + std::to_string(i) + "," + std::to_string(j));
 *     }
 *     builder.end_row();
 * }
 * builder.end_table();
 * 
 * // Insert hyperlink
 * builder.insert_hyperlink("Click here", "https://example.com");
 * 
 * // Create bookmark
 * builder.start_bookmark("Section1");
 * builder.writeln("Important section");
 * builder.end_bookmark("Section1");
 * @endcode
 * 
 * @see Document
 * @since 0.2.0
 */
class DocumentBuilder {
private:
    Document* doc_;                    ///< Target document
    pugi::xml_node current_node_;      ///< Current position node
    pugi::xml_node current_paragraph_; ///< Current paragraph node

    /**
     * @struct FormattingState
     * @brief Current formatting state
     */
    struct FormattingState {
        bool bold = false;              ///< Bold flag
        bool italic = false;            ///< Italic flag
        bool underline = false;         ///< Underline flag
        bool strikethrough = false;     ///< Strikethrough flag
        std::string font_name;          ///< Font family name
        int font_size = 0;              ///< Font size in points
        std::string color;              ///< Text color (hex)
        std::string alignment;          ///< Paragraph alignment
    };
    FormattingState format_;            ///< Current formatting state

    // Table building state
    bool in_table_ = false;             ///< Currently in table flag
    pugi::xml_node current_table_;      ///< Current table node
    pugi::xml_node current_row_;        ///< Current row node
    pugi::xml_node current_cell_;       ///< Current cell node

    /**
     * @brief Ensure current paragraph exists
     * @details Creates a paragraph if none exists at current position
     */
    void ensure_paragraph();

    /**
     * @brief Apply current formatting to a run
     * @param[in,out] run The run to format
     */
    void apply_formatting(pugi::xml_node run);

    /**
     * @brief Get document body node
     * @return The w:body element
     */
    pugi::xml_node get_body();

public:
    /**
     * @brief Construct builder for a document
     * @param[in] doc Target document
     */
    explicit DocumentBuilder(Document* doc);

    // ========================================================================
    // Navigation
    // ========================================================================

    /** @brief Move cursor to document start */
    void move_to_document_start();

    /** @brief Move cursor to document end */
    void move_to_document_end();

    /**
     * @brief Move to specific paragraph
     * @param[in] index Paragraph index (0-based)
     */
    void move_to_paragraph(size_t index);

    /**
     * @brief Move to bookmark
     * @param[in] name Bookmark name
     */
    void move_to_bookmark(const std::string& name);

    /**
     * @brief Move to specific cell
     * @param[in] table_index Table index (0-based)
     * @param[in] row_index Row index (0-based)
     * @param[in] cell_index Cell index (0-based)
     */
    void move_to_cell(size_t table_index, size_t row_index, size_t cell_index);

    // ========================================================================
    // Text Insertion
    // ========================================================================

    /**
     * @brief Write text at current position
     * @param[in] text Text to write
     */
    void write(const std::string& text);

    /**
     * @brief Write text with newline
     * @param[in] text Text to write
     */
    void writeln(const std::string& text);

    /** @brief Write empty paragraph */
    void writeln();

    // ========================================================================
    // Paragraph Operations
    // ========================================================================

    /**
     * @brief Insert new paragraph
     * @return Pointer to the new paragraph
     */
    Paragraph* insert_paragraph();

    /** @brief Insert page break */
    void insert_break();

    // ========================================================================
    // Formatting
    // ========================================================================

    /** @param[in] value true to enable bold */
    void set_bold(bool value);
    
    /** @param[in] value true to enable italic */
    void set_italic(bool value);
    
    /** @param[in] value true to enable underline */
    void set_underline(bool value);
    
    /** @param[in] value true to enable strikethrough */
    void set_strikethrough(bool value);
    
    /** @param[in] name Font family name */
    void set_font_name(const std::string& name);
    
    /** @param[in] size Font size in points */
    void set_font_size(int size);
    
    /** @param[in] color_hex Hex color code (e.g., "FF0000") */
    void set_color(const std::string& color_hex);
    
    /** @param[in] alignment "left", "center", "right", or "justify" */
    void set_alignment(const std::string& alignment);
    
    /** @brief Clear all formatting */
    void clear_formatting();

    // ========================================================================
    // Table Building
    // ========================================================================

    /** @brief Start a new table */
    void start_table();
    
    /** @brief End current table */
    void end_table();
    
    /** @brief Insert a new row in current table */
    void insert_row();
    
    /** @brief Insert a cell in current row */
    void insert_cell();
    
    /** @brief End current row */
    void end_row();

    // ========================================================================
    // Hyperlink
    // ========================================================================

    /**
     * @brief Insert a hyperlink
     * @param[in] text Display text
     * @param[in] url Target URL
     */
    void insert_hyperlink(const std::string& text, const std::string& url);

    // ========================================================================
    // Bookmark
    // ========================================================================

    /**
     * @brief Start a bookmark range
     * @param[in] name Bookmark name
     */
    void start_bookmark(const std::string& name);

    /**
     * @brief End a bookmark range
     * @param[in] name Bookmark name (must match start_bookmark)
     */
    void end_bookmark(const std::string& name);

    // ========================================================================
    // Image
    // ========================================================================

    /**
     * @brief Insert an image
     * @param[in] image_path Path to image file
     * @param[in] width Width in points (0 = auto)
     * @param[in] height Height in points (0 = auto)
     * @return true if successful
     */
    bool insert_image(const std::string& image_path, double width = 0, double height = 0);
};

// ============================================================================
// DocumentSearch Class
// ============================================================================

/**
 * @class DocumentSearch
 * @brief Static utility class for searching and replacing text
 * @details Provides static methods for finding text and replacing content
 *          throughout the document.
 * 
 * @par Usage Example:
 * @code
 * // Simple replace
 * cdocx::DocumentSearch::replace(doc, "old", "new");
 * 
 * // Replace all
 * int count = cdocx::DocumentSearch::replace_all(doc, "TODO", "DONE");
 * std::cout << "Replaced " << count << " occurrences" << std::endl;
 * 
 * // Replace with formatting
 * cdocx::DocumentSearch::replace_with_formatting(
 *     doc, "important", "IMPORTANT", cdocx::bold | cdocx::italic);
 * @endcode
 * 
 * @see Range
 * @since 0.2.0
 */
class DocumentSearch {
public:
    /**
     * @brief Callback function type for search operations
     * @param[in] found_text The text that was found
     * @param[in,out] range The range containing the found text
     * @return true to continue searching, false to stop
     */
    using SearchCallback = std::function<bool(const std::string& found_text, Range& range)>;

    /**
     * @brief Find first occurrence of text
     * @param[in,out] doc Document to search
     * @param[in] text Text to find
     * @return Range if found, std::nullopt otherwise
     */
    static std::optional<Range> find(Document& doc, const std::string& text);

    /**
     * @brief Find all occurrences of text
     * @param[in,out] doc Document to search
     * @param[in] text Text to find
     * @return Vector of ranges for all occurrences
     */
    static std::vector<Range> find_all(Document& doc, const std::string& text);

    /**
     * @brief Replace first occurrence of text
     * @param[in,out] doc Document to modify
     * @param[in] old_text Text to find
     * @param[in] new_text Replacement text
     * @return true if replacement was made
     */
    static bool replace(Document& doc, const std::string& old_text, const std::string& new_text);

    /**
     * @brief Replace all occurrences of text
     * @param[in,out] doc Document to modify
     * @param[in] old_text Text to find
     * @param[in] new_text Replacement text
     * @return Number of replacements made
     */
    static int replace_all(Document& doc, const std::string& old_text, const std::string& new_text);

    /**
     * @brief Replace with formatting
     * @param[in,out] doc Document to modify
     * @param[in] old_text Text to find
     * @param[in] new_text Replacement text
     * @param[in] flag Formatting to apply
     * @return true if replacement was made
     */
    static bool replace_with_formatting(Document& doc, const std::string& old_text,
                                        const std::string& new_text, formatting_flag flag);

    /**
     * @brief Find and process with callback
     * @param[in,out] doc Document to search
     * @param[in] pattern Text pattern to find
     * @param[in] callback Function to call for each match
     * @return Number of matches processed
     */
    static int find_and_process(Document& doc, const std::string& pattern, SearchCallback callback);
};

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * @namespace utils
 * @brief Utility functions for document processing
 */
namespace utils {
    /**
     * @brief Convert points to twips
     * @param points Points value
     * @return Twips value (1 point = 20 twips)
     */
    inline int points_to_twips(double points) {
        return static_cast<int>(points * 20);
    }

    /**
     * @brief Convert twips to points
     * @param twips Twips value
     * @return Points value
     */
    inline double twips_to_points(int twips) {
        return twips / 20.0;
    }

    /**
     * @brief Convert inches to twips
     * @param inches Inches value
     * @return Twips value (1 inch = 1440 twips)
     */
    inline int inches_to_twips(double inches) {
        return static_cast<int>(inches * 1440);
    }

    /**
     * @brief Check if string starts with prefix (case-insensitive)
     * @param str String to check
     * @param prefix Prefix to look for
     * @return true if str starts with prefix
     */
    bool starts_with_ci(const std::string& str, const std::string& prefix);

    /**
     * @brief Check if string contains substring (case-insensitive)
     * @param str String to search
     * @param substr Substring to find
     * @return true if str contains substr
     */
    bool contains_ci(const std::string& str, const std::string& substr);

    /**
     * @brief Convert string to lowercase
     * @param str String to convert
     * @return Lowercase version of str
     */
    std::string to_lower(const std::string& str);
}

} // namespace cdocx
