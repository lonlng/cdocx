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
 * @par Document Structure Hierarchy:
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
#include <cdocx/properties.h>
#include <cdocx/numbering.h>
#include <cdocx/node.h>
#include <cdocx/format.h>

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
 * @par Usage Example:
 * @code
 * auto para = doc.paragraphs();
 * auto run = para.runs();
 * 
 * // Modify text
 * run.set_text("New text");
 * 
 * // Apply formatting
 * run.set_bold(true);
 * run.set_color("FF0000");  // Red color
 * run.set_font_size(24);    // 12pt
 * @endcode
 * 
 * @see Paragraph, formatting_flag
 * @since 0.1.0
 */
class Run : public Node {
public:
    // Construction
    // Run();
    explicit Run(Document* doc);
    explicit Run(Document* doc, const std::string& text);
    
    // Text content
    // std::string get_text() const override { return text_; }
    void set_text(const std::string& text) { text_ = text; }
    
    // Append/prepend text
    void append_text(const std::string& text) { text_ += text; }
    void prepend_text(const std::string& text) { text_ = text + text_; }
    
    // Font formatting
    Font& get_font() { return font_; }
    const Font& get_font() const { return font_; }
    
    // Convenience formatting methods (return *this for chaining)
    Run& set_bold2(bool value) { font_.bold = value; return *this; }
    Run& set_italic2(bool value) { font_.italic = value; return *this; }
    Run& set_underline(UnderlineType value) { font_.underline = value; return *this; }
    Run& set_font_size(double size) { font_.size = size; return *this; }
    Run& set_font_name2(const std::string& name) { font_.name = name; return *this; }
    Run& set_color(const Color& color) { font_.color = color; return *this; }
    Run& set_highlight(HighlightColor color) { font_.highlight = color; return *this; }
    Run& set_superscript() { font_.script_type = ScriptType::Superscript; return *this; }
    Run& set_subscript() { font_.script_type = ScriptType::Subscript; return *this; }
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Run; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
private:
    std::string text_;
    Font font_;

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
    
    // ===================================================================
    // Enhanced Text Properties (v0.4.0)
    // ===================================================================
    
    /**
     * @brief Apply comprehensive text properties
     * @param[in] props TextProperties structure
     * @since 0.4.0
     */
    void set_properties(const TextProperties& props);
    
    /**
     * @brief Get current text properties
     * @return TextProperties structure
     * @since 0.4.0
     */
    TextProperties get_properties() const;
    
    /**
     * @brief Set highlight color
     * @param[in] color Highlight color
     * @return true if successful
     * @since 0.4.0
     */
    bool set_highlight(TextProperties::Highlight color);
    
    /**
     * @brief Set underline with style and color
     * @param[in] style Underline style
     * @param[in] color Color (RRGGBB or "auto")
     * @return true if successful
     * @since 0.4.0
     */
    bool set_underline_style(TextProperties::UnderlineStyle style, 
                             const std::string& color = "auto");
    
    /**
     * @brief Set strikethrough style
     * @param[in] style Strike style
     * @return true if successful
     * @since 0.4.0
     */
    bool set_strike(TextProperties::StrikeStyle style);
    
    /**
     * @brief Set character scale
     * @param[in] percent Scale percentage (1-600, 100 = normal)
     * @return true if successful
     * @since 0.4.0
     */
    bool set_scale(int percent);
    
    /**
     * @brief Set character spacing
     * @param[in] type Spacing type
     * @param[in] value Spacing value (20 = 1pt)
     * @return true if successful
     * @since 0.4.0
     */
    bool set_spacing(TextProperties::SpacingType type, int value);
    
    /**
     * @brief Set character position
     * @param[in] type Position type
     * @param[in] value Position value (2 = 1pt)
     * @return true if successful
     * @since 0.4.0
     */
    bool set_position(TextProperties::PositionType type, int value);
};


// ============================================================================
// SpecialChar Class - Special characters (breaks, tabs, etc.)
// ============================================================================

class SpecialChar : public Node {
public:
    explicit SpecialChar(char16_t char_code = 0);
    
    char16_t get_char() const { return char_code_; }
    void set_char(char16_t ch) { char_code_ = ch; }
    
    // Static factory methods for common special chars
    static std::shared_ptr<SpecialChar> paragraph_break();
    static std::shared_ptr<SpecialChar> line_break();
    static std::shared_ptr<SpecialChar> page_break();
    static std::shared_ptr<SpecialChar> column_break();
    static std::shared_ptr<SpecialChar> tab();
    
    // Node overrides
    NodeType node_type() const override { return NodeType::SpecialChar; }
    std::string get_text() const override;
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
private:
    char16_t char_code_;
};


// ============================================================================
// RunCollection Class
// ============================================================================

class RunCollection {
    std::vector<std::shared_ptr<Run>> runs_;
    
public:
    using iterator = std::vector<std::shared_ptr<Run>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Run>>::const_iterator;
    
    size_t get_count() const { return runs_.size(); }
    std::shared_ptr<Run> get_item(int index) const;
    std::shared_ptr<Run> operator[](int index) const { return get_item(index); }
    
    iterator begin() { return runs_.begin(); }
    iterator end() { return runs_.end(); }
    const_iterator begin() const { return runs_.begin(); }
    const_iterator end() const { return runs_.end(); }
    
    void add(std::shared_ptr<Run> run);
    void remove(std::shared_ptr<Run> run);
    void remove_at(int index);
    void clear();
    
    std::shared_ptr<Run> first() const;
    std::shared_ptr<Run> last() const;
    
    // Get all text from all runs
    std::string get_text() const;
};


// ============================================================================
// Field Classes
// ============================================================================

class Field : public Node {
public:
    explicit Field(FieldType type = FieldType::Unknown);
    
    FieldType get_type() const { return type_; }
    void set_type(FieldType type) { type_ = type; }
    
    std::string get_field_code() const { return field_code_; }
    void set_field_code(const std::string& code) { field_code_ = code; }
    
    std::string get_result() const { return result_; }
    void set_result(const std::string& result) { result_ = result; }
    
    bool is_locked() const { return is_locked_; }
    void set_locked(bool locked) { is_locked_ = locked; }
    
    bool is_dirty() const { return is_dirty_; }
    void set_dirty(bool dirty) { is_dirty_ = dirty; }
    
    // Update field (subclasses implement)
    virtual void update();
    
    // Unlink field (replace with result)
    void unlink();
    
    // Node overrides
    NodeType node_type() const override { return NodeType::FieldStart; }
    std::string get_text() const override { return result_; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
private:
    FieldType type_;
    std::string field_code_;
    std::string result_;
    bool is_locked_ = false;
    bool is_dirty_ = true;
};


// ============================================================================
// BookmarkStart/BookmarkEnd Classes
// ============================================================================

class BookmarkStart : public Node {
public:
    BookmarkStart();
    BookmarkStart(const std::string& name, int id);
    
    std::string get_name() const { return name_; }
    void set_name(const std::string& name) { name_ = name; }
    
    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }
    
    // Node overrides
    NodeType node_type() const override { return NodeType::BookmarkStart; }
    std::string get_text() const override { return ""; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
private:
    std::string name_;
    int id_ = 0;
};

class BookmarkEnd : public Node {
public:
    BookmarkEnd();
    explicit BookmarkEnd(int id);
    
    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }
    
    // Node overrides
    NodeType node_type() const override { return NodeType::BookmarkEnd; }
    std::string get_text() const override { return ""; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
private:
    int id_ = 0;
};


// ============================================================================
// Hyperlink Class
// ============================================================================

class Hyperlink : public Field {
public:
    Hyperlink();
    
    void set_address(const std::string& url);
    void set_bookmark_name(const std::string& name);
    void set_tooltip(const std::string& tooltip);
    void set_screen_tip(const std::string& tip);
    
    std::string get_address() const;
    std::string get_bookmark_name() const;
    
    // Node overrides
    void update() override;
};
} // namespace cdocx
