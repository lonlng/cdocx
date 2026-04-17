/**
 * @file base.h
 * @brief Base content classes for CDocx document model - DOM Style
 * @details Defines the fundamental content classes: Run, SpecialChar,
 *          Field, BookmarkStart, BookmarkEnd. These work with the DOM
 *          architecture where Document is the root CompositeNode.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0
 *
 * @par Document Structure Hierarchy:
 * @code
 * Document (CompositeNode)
 * ├── Section (CompositeNode)
 * │   ├── Body (CompositeNode)
 * │   │   ├── Paragraph (CompositeNode) - contains inline nodes
 * │   │   │   ├── Run (Inline) - formatted text segment
 * │   │   │   ├── SpecialChar (Inline) - breaks, tabs, etc.
 * │   │   │   ├── Field (Inline) - dynamic fields
 * │   │   │   ├── BookmarkStart/BookmarkEnd (Node) - bookmark markers
 * │   │   │   └── Hyperlink (Field) - hyperlinks
 * │   │   └── Table (CompositeNode)
 * │   │       └── Row (CompositeNode)
 * │   │           └── Cell (CompositeNode) - contains Paragraphs
 * │   └── HeaderFooter (CompositeNode)
 * @endcode
 */

#pragma once

#include <cdocx/constants.h>
#include <cdocx/format.h>
#include <cdocx/fwd.h>
#include <cdocx/node.h>
#include <cdocx/properties.h>

#include <pugixml.hpp>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations
class IteratorHelper;
class Paragraph;
class Document;

// ============================================================================
// Inline Class - Base for inline-level nodes (Run, SpecialChar, Field, etc.)
// ============================================================================

class Inline : public Node {
  public:
    Inline();
    explicit Inline(Document* doc);

    // Node overrides
    bool is_composite() const override { return false; }

    // Character formatting
    Font& get_font() { return font_; }
    const Font& get_font() const { return font_; }
    void set_font(const Font& font) { font_ = font; }

    // Parent paragraph
    std::shared_ptr<Paragraph> get_parent_paragraph() const;

    // Convenience formatting methods (chainable)
    Inline& set_bold(bool value);
    Inline& set_italic(bool value);
    Inline& set_underline(UnderlineType value);
    Inline& set_strikethrough(bool value);
    Inline& set_font_size(double size);
    Inline& set_font_name(const std::string& name);
    Inline& set_color(const Color& color);
    Inline& set_highlight(HighlightColor color);
    Inline& set_superscript();
    Inline& set_subscript();

  protected:
    Font font_;
};

// ============================================================================
// Run Class - Text with uniform formatting (Inline node)
// ============================================================================

class Run : public Inline {
  public:
    // Construction
    Run();
    explicit Run(Document* doc);
    Run(Document* doc, const std::string& text);
    Run(const Run& other);
    Run& operator=(const Run& other);

    // Node overrides
    NodeType node_type() const override { return NodeType::Run; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string get_text() const override {
        if (current_xml_) {
            return get_text_xml();
        }
        return text_;
    }

    // Text content
    void set_text(const std::string& text) { text_ = text; }
    void append_text(const std::string& text) { text_ += text; }
    void prepend_text(const std::string& text) { text_ = text + text_; }

    // Convenience formatting (override Inline methods for chainability)
    Run& set_bold(bool value) {
        font_.bold = value;
        return *this;
    }
    Run& set_italic(bool value) {
        font_.italic = value;
        return *this;
    }
    Run& set_underline(UnderlineType value) {
        font_.underline = value;
        return *this;
    }
    Run& set_strikethrough(bool value) {
        font_.strikethrough = value;
        return *this;
    }
    Run& set_font_size(double size) {
        font_.size = size;
        return *this;
    }
    Run& set_font_name(const std::string& name) {
        font_.name = name;
        return *this;
    }
    Run& set_color(const Color& color) {
        font_.color = color;
        return *this;
    }
    Run& set_color(const std::string& color_hex) {
        font_.color = Color(color_hex);
        return *this;
    }
    Run& set_highlight(HighlightColor color) {
        font_.highlight = color;
        return *this;
    }
    Run& set_highlight(TextProperties::Highlight color);
    Run& set_superscript() {
        font_.script_type = ScriptType::Superscript;
        return *this;
    }
    Run& set_subscript() {
        font_.script_type = ScriptType::Subscript;
        return *this;
    }

    // Enhanced properties (v0.4.0+)
    Run& set_properties(const TextProperties& props);
    Run& set_underline_style(TextProperties::UnderlineStyle style,
                             const std::string& color = "auto");
    Run& set_spacing(TextProperties::SpacingType type, int value);
    Run& set_position(TextProperties::PositionType type, int value);
    Run& set_scale(int percent);
    Run& set_strike(TextProperties::StrikeStyle style);

    // Legacy API support (for backward compatibility)
    Run& set_bold2(bool value) { return set_bold(value); }
    Run& set_italic2(bool value) { return set_italic(value); }
    Run& set_font_name2(const std::string& name) { return set_font_name(name); }

    // Legacy iterator-style API (deprecated but kept for compatibility)
    // These methods work with XML nodes directly
  private:
    friend class IteratorHelper;

    pugi::xml_node parent_xml_;   ///< Parent paragraph XML node (legacy)
    pugi::xml_node current_xml_;  ///< Current w:r XML element (legacy)

  public:
    // Legacy constructors and XML node methods
    Run(pugi::xml_node parent, pugi::xml_node current);
    void set_parent_xml(pugi::xml_node node);
    void set_current_xml(pugi::xml_node node);
    pugi::xml_node get_current_xml() const { return current_xml_; }
    pugi::xml_node get_parent_xml() const { return parent_xml_; }

    // Legacy iteration methods
    Run& next();
    bool has_next() const;

    // Legacy text methods (work with XML)
    bool set_text_xml(const std::string& text) const;
    std::string get_text_xml() const;

    // Legacy formatting methods (work with XML)
    bool set_color_xml(const std::string& color_hex);
    bool set_font_size_xml(int size);
    bool set_font_name_xml(const std::string& font_name);
    bool set_bold_xml(bool bold);
    bool set_italic_xml(bool italic);
    bool set_underline_xml(bool underline);

    // Enhanced properties (v0.4.0) - XML versions
    void set_properties_xml(const TextProperties& props);
    TextProperties get_properties_xml() const;
    bool set_highlight_xml(TextProperties::Highlight color);
    bool set_underline_style_xml(TextProperties::UnderlineStyle style,
                                 const std::string& color = "auto");
    bool set_strike_xml(TextProperties::StrikeStyle style);
    bool set_scale_xml(int percent);
    bool set_spacing_xml(TextProperties::SpacingType type, int value);
    bool set_position_xml(TextProperties::PositionType type, int value);

  public:
    // Preserve unknown XML children (e.g., w:drawing) through DOM roundtrips
    void preserve_child(pugi::xml_node child);
    void serialize_preserved_children(pugi::xml_node run_xml) const;
    bool has_preserved_children() const;

  private:
    std::string text_;
    pugi::xml_document preserved_children_;
};


// ============================================================================
// SpecialChar Class - Special characters (breaks, tabs, etc.)
// ============================================================================

class SpecialChar : public Inline {
  public:
    SpecialChar();
    explicit SpecialChar(char16_t char_code);

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
    char16_t char_code_ = 0;
};


// ============================================================================
// RunCollection Class
// ============================================================================

class RunCollection {
    std::vector<std::shared_ptr<Run>> runs_;

  public:
    using iterator = std::vector<std::shared_ptr<Run>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Run>>::const_iterator;

    RunCollection() = default;
    explicit RunCollection(const std::vector<std::shared_ptr<Run>>& runs) : runs_(runs) {}

    size_t get_count() const { return runs_.size(); }
    std::shared_ptr<Run> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < runs_.size()) {
            return runs_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Run> operator[](int index) const { return get_item(index); }

    iterator begin() { return runs_.begin(); }
    iterator end() { return runs_.end(); }
    const_iterator begin() const { return runs_.begin(); }
    const_iterator end() const { return runs_.end(); }

    void add(const std::shared_ptr<Run>& run);
    void remove(const std::shared_ptr<Run>& run);
    void remove_at(int index);
    void clear();

    std::shared_ptr<Run> first() const { return runs_.empty() ? nullptr : runs_.front(); }
    std::shared_ptr<Run> last() const { return runs_.empty() ? nullptr : runs_.back(); }

    std::string get_text() const;
};


// ============================================================================
// Field Class - Dynamic field (inline)
// ============================================================================

class Field : public Inline {
  public:
    Field();
    explicit Field(FieldType type);
    explicit Field(Document* doc, FieldType type = FieldType::Unknown);

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

    // Field switches (e.g., \"\\* MERGEFORMAT\", \"\\@ \"yyyy-MM-dd\"")
    void add_switch(const std::string& switch_text);
    void clear_switches();
    const std::vector<std::string>& get_switches() const { return switches_; }
    std::string get_switches_text() const;

    // Full field instruction code including switches
    std::string get_full_field_code() const;

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
    FieldType type_ = FieldType::Unknown;
    std::string field_code_;
    std::string result_;
    std::vector<std::string> switches_;
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
    explicit BookmarkStart(Document* doc);

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
    explicit BookmarkEnd(Document* doc);

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
    explicit Hyperlink(Document* doc);

    void set_address(const std::string& url);
    void set_bookmark_name(const std::string& name);
    void set_tooltip(const std::string& tooltip);
    void set_screen_tip(const std::string& tip);

    std::string get_address() const;
    std::string get_bookmark_name() const;
    std::string get_tooltip() const;
    std::string get_screen_tip() const;

    // Node overrides
    NodeType node_type() const override { return cdocx::NodeType::Hyperlink; }
    std::shared_ptr<Node> clone(bool deep = true) const override;
    void accept(DocumentVisitor* visitor) override;
    void update() override;

  private:
    std::string address_;
    std::string bookmark_name_;
    std::string tooltip_;
    std::string screen_tip_;
};

}  // namespace cdocx
