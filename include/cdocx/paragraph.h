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
    
private:
    ParagraphFormat format_;
    ListFormat list_format_;
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
