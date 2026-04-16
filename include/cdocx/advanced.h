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
#include <cdocx/formfield.h>
#include <cdocx/constants.h>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace cdocx {

// Forward declarations
class Range;
class DocumentSearch;
class BookmarkReplacer;
class CaptionGenerator;
class Footnote;

// ============================================================================
// Bookmark Format Structure (v0.3.0)
// ============================================================================

/**
 * @struct BookmarkFormat
 * @brief Represents formatting information extracted from a bookmark
 * @details Stores character formatting properties that can be extracted
 *          from bookmark content and reapplied after text replacement.
 * 
 * @see Bookmark
 * @since 0.3.0
 */
struct BookmarkFormat {
    // Character formatting (from w:rPr)
    std::string font_ascii;      ///< Western font name (ASCII)
    std::string font_far_east;   ///< East Asian font name (FarEast)
    std::string font_hansi;      ///< ANSI font name
    std::string font_hint;       ///< Font hint (eastAsia, default)
    int font_size = 0;           ///< Font size in half-points
    std::string color;           ///< Text color (RGB hex)
    bool bold = false;           ///< Bold flag
    bool italic = false;         ///< Italic flag
    bool underline = false;      ///< Underline flag
    bool strikethrough = false;  ///< Strikethrough flag
    
    // Paragraph formatting (from w:pPr) - P1 enhancement
    std::string alignment;       ///< Paragraph alignment (left, center, right, both, distribute)
    int line_spacing = 0;        ///< Line spacing in twips (1/20 of a point)
    std::string line_rule;       ///< Line rule (auto, exact, atLeast)
    int space_before = 0;        ///< Space before paragraph in twips
    int space_after = 0;         ///< Space after paragraph in twips
    int first_line_indent = 0;   ///< First line indent in twips (positive) or hanging (negative)
    int left_indent = 0;         ///< Left indent in twips
    int right_indent = 0;        ///< Right indent in twips
    bool keep_next = false;      ///< Keep with next paragraph
    bool keep_lines = false;     ///< Keep lines together (no page break within)
    bool page_break_before = false; ///< Page break before paragraph
    
    /**
     * @brief Check if format is valid (has meaningful data)
     * @return true if font_size > 0 or any font is specified
     */
    bool is_valid() const { return font_size > 0 || !font_ascii.empty() || !font_far_east.empty(); }
    
    /**
     * @brief Reset all format values to defaults
     */
    void clear() {
        font_ascii.clear();
        font_far_east.clear();
        font_hansi.clear();
        font_hint.clear();
        font_size = 0;
        color.clear();
        bold = false;
        italic = false;
        underline = false;
        strikethrough = false;
        alignment.clear();
        line_spacing = 0;
        line_rule.clear();
        space_before = 0;
        space_after = 0;
        first_line_indent = 0;
        left_indent = 0;
        right_indent = 0;
        keep_next = false;
        keep_lines = false;
        page_break_before = false;
    }
};

// ============================================================================
// Image Support Structures (v0.3.0)
// ============================================================================

/**
 * @enum ImageAlignment
 * @brief Image alignment options for inserted images
 * @since 0.3.0
 */
enum class ImageAlignment : std::uint8_t {
    Left,    ///< Left-aligned (using anchor positioning)
    Center,  ///< Center-aligned (using inline positioning)
    Right    ///< Right-aligned (using anchor positioning)
};

/**
 * @struct ImageSize
 * @brief Image dimensions specification
 * @details Supports both point and EMU (English Metric Unit) measurements.
 *          1 point = 12700 EMU
 * @since 0.3.0
 */
struct ImageSize {
    double width_pt = 0;   ///< Width in points (1 inch = 72 points)
    double height_pt = 0;  ///< Height in points
    
    /**
     * @brief Default constructor
     */
    ImageSize() = default;
    
    /**
     * @brief Construct with dimensions
     * @param w Width in points
     * @param h Height in points
     */
    ImageSize(double w, double h) : width_pt(w), height_pt(h) {}
    
    /**
     * @brief Convert width to EMU
     * @return Width in EMU units
     */
    int64_t width_emu() const { return static_cast<int64_t>(width_pt * 12700); }
    
    /**
     * @brief Convert height to EMU
     * @return Height in EMU units
     */
    int64_t height_emu() const { return static_cast<int64_t>(height_pt * 12700); }
    
    /**
     * @brief Check if size is valid (both dimensions > 0)
     * @return true if valid
     */
    bool is_valid() const { return width_pt > 0 && height_pt > 0; }
};

// ============================================================================
// Image Utilities (P1 Enhancement)
// ============================================================================

/**
 * @brief Detect image dimensions from file data
 * @param[in] image_path Path to image file
 * @param[out] size Detected image size in points (using 96 DPI default)
 * @return true if dimensions were successfully detected
 * @details Supports PNG, JPEG, BMP, and GIF formats
 */
bool detect_image_size(const std::string& image_path, ImageSize& size);

/**
 * @brief Detect image dimensions from memory buffer
 * @param[in] data Binary image data
 * @param[out] size Detected image size in points
 * @return true if dimensions were successfully detected
 */
bool detect_image_size_from_memory(const std::vector<uint8_t>& data, ImageSize& size);

/**
 * @brief Image format information
 */
struct ImageFormatInfo {
    std::string format;          ///< Detected format ("PNG", "JPEG", "BMP", "GIF", "UNKNOWN")
    std::string mime_type;       ///< MIME type
    int width = 0;               ///< Width in pixels
    int height = 0;              ///< Height in pixels
    int dpi_x = 96;              ///< Horizontal DPI
    int dpi_y = 96;              ///< Vertical DPI
    bool is_valid = false;       ///< Whether the file is valid
    std::string error_message;   ///< Error message if detection failed
};

/**
 * @brief Validate and detect image format using magic numbers
 * @param[in] image_path Path to image file
 * @return ImageFormatInfo with detection results
 * @details Performs file header (magic number) validation, not just extension check
 */
ImageFormatInfo validate_image_format_detailed(const std::string& image_path);

/**
 * @brief Validate image format from memory buffer
 * @param[in] data Binary image data
 * @return ImageFormatInfo with detection results
 */
ImageFormatInfo validate_image_format_from_memory(const std::vector<uint8_t>& data);

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
    
    // ===================================================================
    // Enhanced Format-Preserving Methods (New in v0.3.0)
    // ===================================================================
    
    /**
     * @brief Extract formatting information from bookmark content
     * @return BookmarkFormat structure containing extracted format
     * @details Scans the first run within the bookmark range and extracts
     *          all formatting properties including fonts, size, color, etc.
     * @since 0.3.0
     */
    BookmarkFormat get_format() const;
    
    /**
     * @brief Set text content while preserving original format
     * @param[in] text New text content
     * @return true if successful
     * @details Extracts format from existing content before replacement,
     *          then applies the same format to the new text.
     * @since 0.3.0
     */
    bool set_text_keep_format(const std::string& text);
    
    /**
     * @brief Set text with explicit format control
     * @param[in] text New text content
     * @param[in] format Format specification to apply
     * @return true if successful
     * @since 0.3.0
     */
    bool set_text_formatted(const std::string& text, const BookmarkFormat& format);
    
    /**
     * @brief Check if bookmark spans multiple paragraphs
     * @return true if start and end are in different paragraphs
     * @since 0.3.0
     */
    bool is_cross_paragraph() const;
    
    /**
     * @brief Get all paragraphs covered by this bookmark
     * @return Vector of paragraph xml_nodes
     * @since 0.3.0
     */
    std::vector<pugi::xml_node> get_covered_paragraphs() const;
    
    /**
     * @brief Set text for cross-paragraph bookmark
     * @param[in] text New text content
     * @return true if successful
     * @details Merges multiple paragraphs into one and sets text.
     *          Use with caution as it modifies document structure.
     * @since 0.3.0
     */
    bool set_text_cross_paragraph(const std::string& text);
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
     * @brief Default constructor (creates empty collection)
     */
    BookmarkCollection() : doc_(nullptr), collected_(true) {}
    
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
    
    /**
     * @brief Get bookmark names as a list
     * @return Vector of bookmark names
     * @since 0.3.0
     */
    std::vector<std::string> get_names() const;
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
    static bool insert_cell(Row& row, size_t index);

    /**
     * @brief Delete a cell at specified position
     * @param[in,out] row Target row
     * @param[in] index Cell index (0-based)
     * @return true if successful
     */
    static bool delete_cell(Row& row, size_t index);

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
    static bool merge_cells_horizontal(Row& row, size_t start, size_t end);

    /**
     * @brief Set cell text
     * @param[in,out] cell Target cell
     * @param[in] text New text content
     * @return true if successful
     */
    static bool set_cell_text(Cell& cell, const std::string& text);

    /**
     * @brief Get cell text
     * @param[in] cell Target cell
     * @return Cell text content
     */
    static std::string get_cell_text(const Cell& cell);
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

public:
    DocumentBuilder();
    ~DocumentBuilder();
    
    // Document properties
    DocumentBuilder& with_title(const std::string& title);
    DocumentBuilder& with_author(const std::string& author);
    DocumentBuilder& with_subject(const std::string& subject);
    DocumentBuilder& with_keywords(const std::string& keywords);
    
    // Page setup
    DocumentBuilder& with_page_size(double width, double height);
    DocumentBuilder& with_margins(double top, double bottom, double left, double right);
    DocumentBuilder& with_orientation(PageOrientation orientation);
    
    // Content
    DocumentBuilder& add_paragraph(std::shared_ptr<Paragraph> paragraph);
    DocumentBuilder& add_paragraph(const std::string& text);
    DocumentBuilder& add_table(std::shared_ptr<Table> table);
    DocumentBuilder& add_table(size_t rows, size_t columns);
    
    // Builder
    std::shared_ptr<Document> build();
    
private:
    std::shared_ptr<Document> doc_sptr;

private:
    Document* doc_ = nullptr;          ///< Target document
    pugi::xml_document* target_xml_doc_ = nullptr; ///< Active XML document (document.xml or header/footer)
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
    
    // Bookmark stack for tracking open bookmarks
    std::map<std::string, int> bookmark_stack_;

    /**
     * @brief Internal helper to insert a form field at current position
     * @param[in] field The form field to insert
     * @return The inserted form field
     */
    std::shared_ptr<FormField> insert_form_field_impl(const std::shared_ptr<FormField>& field);

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

    /**
     * @brief Construct builder owning a document
     * @param[in] doc Shared pointer to target document
     */
    explicit DocumentBuilder(std::shared_ptr<Document> doc);

    // ========================================================================
    // Navigation
    // ========================================================================

    /** @brief Move cursor to document start */
    DocumentBuilder& move_to_document_start();

    /** @brief Move cursor to document end */
    DocumentBuilder& move_to_document_end();

    /**
     * @brief Move to specific section
     * @param[in] index Section index (0-based)
     */
    DocumentBuilder& move_to_section(size_t index);

    /**
     * @brief Move to specific paragraph
     * @param[in] index Paragraph index (0-based)
     */
    DocumentBuilder& move_to_paragraph(size_t index);

    /**
     * @brief Move to specific paragraph and character position
     * @param[in] paragraph_index Paragraph index (0-based)
     * @param[in] character_index Character index within paragraph (0-based)
     */
    DocumentBuilder& move_to_paragraph(size_t paragraph_index, size_t character_index);

    /**
     * @brief Move to bookmark
     * @param[in] name Bookmark name
     */
    DocumentBuilder& move_to_bookmark(const std::string& name);

    /**
     * @brief Move to merge field
     * @param[in] field_name Merge field name
     * @return true if field was found
     */
    bool move_to_merge_field(const std::string& field_name);

    /**
     * @brief Move to specific cell
     * @param[in] table_index Table index (0-based)
     * @param[in] row_index Row index (0-based)
     * @param[in] cell_index Cell index (0-based)
     */
    DocumentBuilder& move_to_cell(size_t table_index, size_t row_index, size_t cell_index);

    // ========================================================================
    // Text Insertion
    // ========================================================================

    /**
     * @brief Write text at current position
     * @param[in] text Text to write
     */
    DocumentBuilder& write(const std::string& text);

    /**
     * @brief Write text with newline
     * @param[in] text Text to write
     */
    DocumentBuilder& writeln(const std::string& text);

    /** @brief Write empty paragraph */
    DocumentBuilder& writeln();

    // ========================================================================
    // Paragraph Operations
    // ========================================================================

    /**
     * @brief Insert new paragraph
     * @return Pointer to the new paragraph
     */
    Paragraph* insert_paragraph();

    /** @brief Insert page break */
    DocumentBuilder& insert_break();

    /** @brief Insert break of specific type */
    DocumentBuilder& insert_break(BreakType break_type);

    /** @brief Move cursor to header/footer */
    DocumentBuilder& move_to_header_footer(HeaderFooterType type);

    /**
     * @brief Insert footnote or endnote
     * @param[in] type Footnote or endnote
     * @param[in] text Note text
     * @return The inserted footnote node
     */
    std::shared_ptr<Footnote> insert_footnote(FootnoteType type, const std::string& text);

    /**
     * @brief Insert footnote or endnote with custom reference mark
     * @param[in] type Footnote or endnote
     * @param[in] text Note text
     * @param[in] reference_mark Custom reference mark
     * @return The inserted footnote node
     */
    std::shared_ptr<Footnote> insert_footnote(FootnoteType type, const std::string& text,
                                               const std::string& reference_mark);

    /**
     * @brief Insert field by type
     * @param[in] field_type Type of field to insert
     * @param[in] update_field Whether to update the field immediately
     * @return The inserted field node
     */
    std::shared_ptr<Field> insert_field(FieldType field_type, bool update_field = false);

    /**
     * @brief Insert field by code
     * @param[in] field_code Field code (e.g., "PAGE", "DATE")
     * @return The inserted field node
     */
    std::shared_ptr<Field> insert_field(const std::string& field_code);

    /**
     * @brief Insert field by code with preset value
     * @param[in] field_code Field code
     * @param[in] field_value Preset field result
     * @return The inserted field node
     */
    std::shared_ptr<Field> insert_field(const std::string& field_code,
                                        const std::string& field_value);

    /** @brief Insert page number field */
    std::shared_ptr<Field> insert_page_number();

    /** @brief Insert number of pages field */
    std::shared_ptr<Field> insert_num_pages();

    /** @brief Insert date field */
    std::shared_ptr<Field> insert_date();

    /** @brief Insert time field */
    std::shared_ptr<Field> insert_time();

    /** @brief Insert merge field */
    std::shared_ptr<Field> insert_merge_field(const std::string& field_name);

    /**
     * @brief Insert table of contents field
     * @param[in] switches TOC switches (e.g., "\\o \"1-3\" \\h \\z \\u")
     * @return The inserted TOC field
     */
    std::shared_ptr<Field> insert_table_of_contents(const std::string& switches);

    // ========================================================================
    // Formatting
    // ========================================================================

    /** @param[in] value true to enable bold */
    DocumentBuilder& set_bold(bool value);

    /** @param[in] value true to enable italic */
    DocumentBuilder& set_italic(bool value);

    /** @param[in] value true to enable underline */
    DocumentBuilder& set_underline(bool value);

    /** @param[in] value true to enable strikethrough */
    DocumentBuilder& set_strikethrough(bool value);

    /** @param[in] name Font family name */
    DocumentBuilder& set_font_name(const std::string& name);

    /** @param[in] size Font size in points */
    DocumentBuilder& set_font_size(int size);

    /** @param[in] color_hex Hex color code (e.g., "FF0000") */
    DocumentBuilder& set_color(const std::string& color_hex);

    /** @param[in] alignment "left", "center", "right", or "justify" */
    DocumentBuilder& set_alignment(const std::string& alignment);

    /** @brief Clear all formatting */
    DocumentBuilder& clear_formatting();

    // ========================================================================
    // Table Building
    // ========================================================================

    /** @brief Start a new table */
    DocumentBuilder& start_table();

    /** @brief End current table */
    DocumentBuilder& end_table();

    /** @brief Insert a new row in current table */
    DocumentBuilder& insert_row();

    /** @brief Insert a cell in current row */
    DocumentBuilder& insert_cell();

    /** @brief End current row */
    DocumentBuilder& end_row();

    // ========================================================================
    // Hyperlink
    // ========================================================================

    /**
     * @brief Insert a hyperlink
     * @param[in] text Display text
     * @param[in] url Target URL
     */
    DocumentBuilder& insert_hyperlink(const std::string& text, const std::string& url);

    // ========================================================================
    // Bookmark
    // ========================================================================

    /**
     * @brief Start a bookmark range
     * @param[in] name Bookmark name
     */
    DocumentBuilder& start_bookmark(const std::string& name);

    /**
     * @brief End a bookmark range
     * @param[in] name Bookmark name (must match start_bookmark)
     */
    DocumentBuilder& end_bookmark(const std::string& name);

    // ========================================================================
    // Form Fields
    // ========================================================================

    /**
     * @brief Insert a text input form field
     * @param[in] name Field name
     * @param[in] type Text form field type
     * @param[in] format Format string
     * @param[in] field_value Display value
     * @param[in] max_length Maximum length (0 = unlimited)
     * @return The inserted form field
     */
    std::shared_ptr<FormField> insert_text_input(
        const std::string& name,
        TextFormFieldType type = TextFormFieldType::Regular,
        const std::string& format = "",
        const std::string& field_value = "",
        int max_length = 0);

    /**
     * @brief Insert a checkbox form field
     * @param[in] name Field name
     * @param[in] checked_value Checked state
     * @param[in] size Size in points (0 = auto)
     * @return The inserted form field
     */
    std::shared_ptr<FormField> insert_check_box(
        const std::string& name,
        bool checked_value,
        int size = 0);

    /**
     * @brief Insert a checkbox form field with default value
     * @param[in] name Field name
     * @param[in] default_value Default checked state
     * @param[in] checked_value Current checked state
     * @param[in] size Size in points (0 = auto)
     * @return The inserted form field
     */
    std::shared_ptr<FormField> insert_check_box(
        const std::string& name,
        bool default_value,
        bool checked_value,
        int size);

    /**
     * @brief Insert a combobox form field
     * @param[in] name Field name
     * @param[in] items Dropdown items
     * @param[in] selected_index Selected item index
     * @return The inserted form field
     */
    std::shared_ptr<FormField> insert_combo_box(
        const std::string& name,
        const std::vector<std::string>& items,
        int selected_index = 0);

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
    static int find_and_process(Document& doc, const std::string& pattern, const SearchCallback& callback);
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
