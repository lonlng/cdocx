/**
 * @file paragraph.h
 * @brief Paragraph class for CDocx - DOM Style
 * @details The Paragraph class represents a paragraph of text and can contain
 *          inline-level nodes like Run, Bookmark, Field, etc.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0
 */

#pragma once

#include <cdocx/node.h>
#include <cdocx/format.h>
#include <cdocx/base.h>
#include <cdocx/numbering.h>

#include <pugixml.hpp>

#include <memory>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations
class Document;
class Body;
class Cell;
class Section;
class Run;
class Field;
class BookmarkStart;
class BookmarkEnd;
class SpecialChar;
class ParagraphCollection;

// ============================================================================
// Paragraph Class - Block-level container for inline content
// ============================================================================

class Paragraph : public CompositeNode {
public:
    Paragraph();
    explicit Paragraph(Document* doc);
    Paragraph(pugi::xml_node parent_node, pugi::xml_node current_node);
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Paragraph; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string get_text() const override;
    
    // Formatting
    ParagraphFormat& get_paragraph_format() { return format_; }
    const ParagraphFormat& get_paragraph_format() const { return format_; }
    void set_paragraph_format(const ParagraphFormat& format) { format_ = format; }
    
    // List formatting
    ListFormat& get_list_format() { return list_format_; }
    const ListFormat& get_list_format() const { return list_format_; }
    
    // Run operations
    std::shared_ptr<Run> append_run(const std::string& text = "");
    std::shared_ptr<Run> insert_run(int index, const std::string& text = "");
    std::shared_ptr<Run> get_first_run() const;
    std::shared_ptr<Run> get_last_run() const;
    RunCollection get_runs() const;
    
    // Field operations
    std::shared_ptr<Field> append_field(FieldType type);
    std::shared_ptr<Field> insert_field(int index, FieldType type);
    std::vector<std::shared_ptr<Field>> get_fields() const;
    
    // Bookmark operations
    std::shared_ptr<BookmarkStart> append_bookmark_start(const std::string& name);
    std::shared_ptr<BookmarkEnd> append_bookmark_end(int id);
    
    // Special character operations
    std::shared_ptr<SpecialChar> append_special_char(char16_t char_code);
    std::shared_ptr<SpecialChar> append_break(BreakType break_type);
    std::shared_ptr<SpecialChar> append_page_break();
    std::shared_ptr<SpecialChar> append_line_break();
    std::shared_ptr<SpecialChar> append_tab();
    
    // Parent access
    std::shared_ptr<Body> get_parent_body() const;
    std::shared_ptr<Cell> get_parent_cell() const;
    std::shared_ptr<Section> get_parent_section() const;
    
    // Utility methods
    int join_runs_with_same_formatting();
    void ensure_minimum();  // Ensure at least one run
    bool is_in_cell() const;
    bool is_end_of_cell() const;
    bool is_end_of_section() const;
    bool is_list_item() const;
    
    // Quick text setting (clears existing content)
    void set_text(const std::string& text);
    
    // Append/prepend text (creates new run if needed)
    void append_text(const std::string& text);
    void prepend_text(const std::string& text);
    
    // Legacy API support (backward compatibility with iterator style)
    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);
    pugi::xml_node get_current() const { return current_; }
    pugi::xml_node get_current_node() const { return current_; }
    
    // Legacy iteration methods
    Paragraph& next();
    bool has_next() const;
    Run& runs();
    Run& add_run(const std::string& text, formatting_flag f = 0);
    Run& add_run(const char* text, formatting_flag f = 0);
    Run& add_run_with_bookmark(Document& doc, const std::string& text, 
                               const std::string& bookmark_name, formatting_flag f = 0);
    Run& add_run_with_bookmark(Document& doc, const char* text,
                               const std::string& bookmark_name, formatting_flag f = 0);
    void remove_run(const Run& r);
    Paragraph& insert_paragraph_after(const std::string& text, formatting_flag f = 0);
    Paragraph* insert_before(const std::string& text, formatting_flag f = 0);
    bool clear();
    bool remove();
    
    // Legacy formatting methods
    bool set_alignment(const std::string& alignment);
    bool set_style(const std::string& style_id);
    bool set_line_spacing(int line_spacing, bool is_exact = false);
    bool set_spacing_before(int spacing);
    bool set_spacing_after(int spacing);
    bool set_indent(int left = -1, int right = -1, int first_line = 0);
    bool set_color(const std::string& color_hex);
    bool set_font_size(int size);
    bool set_font_name(const std::string& font_name);
    bool set_bold(bool bold);
    bool set_italic(bool italic);
    bool set_underline(bool underline);
    
    // Legacy numbering methods
    bool set_numbering(NumberingId numId, NumberingLevel level = NumberingLevel::Level1);
    bool remove_numbering();
    bool has_numbering() const;
    NumberingId get_numbering_id() const;
    NumberingLevel get_numbering_level() const;
    bool set_list_level(NumberingLevel level);
    bool increase_list_level();
    bool decrease_list_level();

    // Enhanced properties (v0.4.0+)
    Paragraph& set_properties(const ParagraphProperties& props);
    Paragraph& set_outline_level(cdocx::ParagraphProperties::OutlineLevel level);
    Paragraph& set_keep_next(bool value);
    Paragraph& set_keep_lines(bool value);
    Paragraph& set_page_break_before(bool value);

private:
    ParagraphFormat format_;
    ListFormat list_format_;
    
    // Legacy iterator-style members
    pugi::xml_node parent_;
    pugi::xml_node current_;
    Run run_;
};

// ============================================================================
// ParagraphCollection - Collection of paragraphs
// ============================================================================

class ParagraphCollection {
    std::vector<std::shared_ptr<Paragraph>> paragraphs_;
    
public:
    using iterator = std::vector<std::shared_ptr<Paragraph>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Paragraph>>::const_iterator;
    
    ParagraphCollection() = default;
    explicit ParagraphCollection(const std::vector<std::shared_ptr<Paragraph>>& paragraphs)
        : paragraphs_(paragraphs) {}
    
    size_t get_count() const { return paragraphs_.size(); }
    std::shared_ptr<Paragraph> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < paragraphs_.size()) {
            return paragraphs_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Paragraph> operator[](int index) const { return get_item(index); }
    
    iterator begin() { return paragraphs_.begin(); }
    iterator end() { return paragraphs_.end(); }
    const_iterator begin() const { return paragraphs_.begin(); }
    const_iterator end() const { return paragraphs_.end(); }
    
    std::shared_ptr<Paragraph> first() const {
        return paragraphs_.empty() ? nullptr : paragraphs_.front();
    }
    std::shared_ptr<Paragraph> last() const {
        return paragraphs_.empty() ? nullptr : paragraphs_.back();
    }
    
    std::string get_text() const;
};

} // namespace cdocx
