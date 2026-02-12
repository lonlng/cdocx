/**
 * @file paragraph.h
 * @brief Paragraph and Run classes for CDocx
 * @details Paragraph formatting and text runs
 */

#pragma once

#include <cdocx/node.h>
#include <cdocx/format.h>
#include <cdocx/base.h>
#include <memory>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations
class Document;
class Section;
class Body;
class Cell;
class Field;
class BookmarkStart;
class BookmarkEnd;
class Run;
class RunCollection;
class SpecialChar;


/**
 * @class Paragraph
 * @brief Represents a paragraph in the document
 * @details A Paragraph is a block-level element containing one or more Run
 *          objects. It can have paragraph-level formatting (alignment,
 *          indentation, spacing, etc.) and contains the actual text content.
 * 
 * @par Usage Example:
 * @code
 * auto para = doc.paragraphs();
 * 
 * // Add formatted text run
 * para.add_run("Bold text", cdocx::bold);
 * para.add_run("Italic text", cdocx::italic);
 * 
 * // Set paragraph formatting
 * para.set_alignment("center");
 * para.set_line_spacing(360);  // 1.5 line spacing
 * para.set_indent(720, -1, 0); // Left indent 0.5 inch
 * @endcode
 * 
 * @see Run, Table
 * @since 0.1.0
 */
class Paragraph : public CompositeNode {
public:
    // Construction
    // Paragraph();
    explicit Paragraph(Document* doc);
    
    // Formatting
    ParagraphFormat& get_paragraph_format() { return format_; }
    const ParagraphFormat& get_paragraph_format() const { return format_; }
    
    // List formatting
    bool is_in_list() const { return !format_.style_name.empty() && format_.style_name.find("List") != std::string::npos; }
    void remove_list_format();
    
    // Runs access
    RunCollection get_runs();
    
    // Text content (combines all runs)
    // std::string get_text2() const override;
    void set_text(const std::string& text);
    void append_text(const std::string& text);
    void prepend_text(const std::string& text);
    
    // Run creation
    std::shared_ptr<Run> append_run(const std::string& text = "");
    std::shared_ptr<Run> insert_run(int index, const std::string& text = "");
    std::shared_ptr<Run> append_run(const std::string& text, const Font& font);
    
    // Special characters
    std::shared_ptr<SpecialChar> append_break(BreakType break_type);
    std::shared_ptr<SpecialChar> append_tab();
    
    // Field creation
    std::shared_ptr<Field> append_field(FieldType type);
    std::shared_ptr<Field> append_page_number();
    std::shared_ptr<Field> append_num_pages();
    std::shared_ptr<Field> append_date(const std::string& format = "");
    std::shared_ptr<Field> append_time(const std::string& format = "");
    std::shared_ptr<Field> append_hyperlink(const std::string& text, const std::string& url);
    std::shared_ptr<Field> append_hyperlink(const std::string& text, const std::string& bookmark_name, bool is_bookmark);
    
    // Bookmark creation
    std::shared_ptr<BookmarkStart> append_bookmark_start(const std::string& name);
    std::shared_ptr<BookmarkEnd> append_bookmark_end(const std::string& name);
    void append_bookmark_range(const std::string& name, const std::string& text);
    
    // Insert at specific position
    std::shared_ptr<Node> insert_node(int index, std::shared_ptr<Node> node);
    
    // State checks
    bool is_in_cell() const;
    bool is_end_of_cell() const;
    bool is_end_of_section() const;
    bool is_end_of_document() const;
    bool is_empty() const;
    
    // Join with next paragraph
    bool join_next();
    
    // Split at position
    std::shared_ptr<Paragraph> split_at(int run_index, int char_index);
    
    // Convenience: Get parent story (Body, HeaderFooter, Cell, etc.)
    std::shared_ptr<CompositeNode> get_parent_story();
    std::shared_ptr<Section> get_parent_section();
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Paragraph; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
private:
    ParagraphFormat format_;


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
     * @brief Add a new run with text, formatting and bookmark
     * @param[in] doc The document to add bookmark to (needed for generating unique ID)
     * @param[in] text The text content
     * @param[in] bookmark_name Name of the bookmark to create around this run
     * @param[in] flag Formatting flags (default: none)
     * @return Reference to the new Run
     * @since 0.3.0
     * @par Usage Example:
     * @code
     * auto para = doc.paragraphs();
     * para.add_run_with_bookmark(doc, "Report Number: BGP-2024-001", "REPORT_NO", cdocx::bold);
     * @endcode
     */
    Run& add_run_with_bookmark(Document& doc, const std::string& text, const std::string& bookmark_name, formatting_flag flag = none);
    
    /**
     * @brief Add a new run with bookmark (C-string version)
     * @param[in] doc The document to add bookmark to (needed for generating unique ID)
     * @param[in] text The text content (null-terminated)
     * @param[in] bookmark_name Name of the bookmark to create around this run
     * @param[in] flag Formatting flags (default: none)
     * @return Reference to the new Run
     * @since 0.3.0
     */
    Run& add_run_with_bookmark(Document& doc, const char* text, const std::string& bookmark_name, formatting_flag flag = none);
    
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
    
    // ========================================================================
    // Text Formatting Methods (Applied to first run or create new run)
    // ========================================================================
    
    /**
     * @brief Set text color for the paragraph
     * @details Applies to the first run if exists, otherwise creates a new run
     * @param[in] color_hex Hex color code (e.g., "FF0000" for red)
     * @return true if successful
     */
    bool set_color(const std::string& color_hex);
    
    /**
     * @brief Set font size for the paragraph
     * @details Applies to the first run if exists, otherwise creates a new run
     * @param[in] size Font size in half-points (e.g., 24 for 12pt)
     * @return true if successful
     */
    bool set_font_size(int size);
    
    /**
     * @brief Set font name for the paragraph
     * @details Applies to the first run if exists, otherwise creates a new run
     * @param[in] font_name Font family name (e.g., "Arial", "Times New Roman")
     * @return true if successful
     */
    bool set_font_name(const std::string& font_name);
    
    /**
     * @brief Set bold formatting for the paragraph
     * @details Applies to the first run if exists, otherwise creates a new run
     * @param[in] bold true to apply bold, false to remove
     * @return true if successful
     */
    bool set_bold(bool bold);
    
    /**
     * @brief Set italic formatting for the paragraph
     * @details Applies to the first run if exists, otherwise creates a new run
     * @param[in] italic true to apply italic, false to remove
     * @return true if successful
     */
    bool set_italic(bool italic);
    
    /**
     * @brief Set underline formatting for the paragraph
     * @details Applies to the first run if exists, otherwise creates a new run
     * @param[in] underline true to apply underline, false to remove
     * @return true if successful
     */
    bool set_underline(bool underline);
    
    // ===================================================================
    // Enhanced Paragraph Properties (v0.4.0)
    // ===================================================================
    
    /**
     * @brief Apply comprehensive paragraph properties
     * @param[in] props ParagraphProperties structure
     * @since 0.4.0
     */
    void set_properties(const ParagraphProperties& props);
    
    /**
     * @brief Get current paragraph properties
     * @return ParagraphProperties structure
     * @since 0.4.0
     */
    ParagraphProperties get_properties() const;
    
    /**
     * @brief Set outline level
     * @param[in] level Outline level
     * @return true if successful
     * @since 0.4.0
     */
    bool set_outline_level(ParagraphProperties::OutlineLevel level);
    
    /**
     * @brief Set keep with next paragraph
     * @param[in] value true to keep with next
     * @return true if successful
     * @since 0.4.0
     */
    bool set_keep_next(bool value);
    
    /**
     * @brief Set keep lines together
     * @param[in] value true to keep lines on same page
     * @return true if successful
     * @since 0.4.0
     */
    bool set_keep_lines(bool value);
    
    /**
     * @brief Set page break before
     * @param[in] value true to insert page break before
     * @return true if successful
     * @since 0.4.0
     */
    bool set_page_break_before(bool value);
    
    /**
     * @brief Set page break after
     * @param[in] value true to insert page break after
     * @return true if successful
     * @since 0.4.0
     */
    bool set_page_break_after(bool value);
    
    /**
     * @brief Set paragraph borders
     * @param[in] borders Borders structure
     * @return true if successful
     * @since 0.4.0
     */
    bool set_borders(const ParagraphProperties::Borders& borders);
    
    // ===================================================================
    // List/Numbering Support (v0.5.0)
    // ===================================================================
    
    /**
     * @brief Set numbering/list properties
     * @param numId Numbering definition ID
     * @param level List level (default: Level1)
     * @return true if successful
     * @since 0.5.0
     * @par Usage Example:
     * @code
     * auto numId = doc.add_bulleted_list_definition();
     * auto para = doc.paragraphs().add_paragraph_after("Item 1");
     * para.set_numbering(numId, NumberingLevel::Level1);
     * @endcode
     */
    bool set_numbering(NumberingId numId, NumberingLevel level = NumberingLevel::Level1);
    
    /**
     * @brief Remove numbering from paragraph
     * @return true if successful
     * @since 0.5.0
     */
    bool remove_numbering();
    
    /**
     * @brief Check if paragraph has numbering
     * @return true if paragraph is part of a list
     * @since 0.5.0
     */
    bool has_numbering() const;
    
    /**
     * @brief Get current numbering ID
     * @return NumberingId, 0 if none
     * @since 0.5.0
     */
    NumberingId get_numbering_id() const;
    
    /**
     * @brief Get current numbering level
     * @return NumberingLevel
     * @since 0.5.0
     */
    NumberingLevel get_numbering_level() const;
    
    /**
     * @brief Set list level
     * @param level New level
     * @return true if successful
     * @since 0.5.0
     */
    bool set_list_level(NumberingLevel level);
    
    /**
     * @brief Increment list level (make it more indented)
     * @return true if successful
     * @since 0.5.0
     */
    bool increase_list_level();
    
    /**
     * @brief Decrement list level (make it less indented)
     * @return true if successful
     * @since 0.5.0
     */
    bool decrease_list_level();
};


} // namespace cdocx
