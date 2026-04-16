/**
 * @file style.h
 * @brief Style and StyleCollection classes for CDocx
 * @details Provides DOM-style access to document styles in word/styles.xml
 */

#pragma once

#include <cdocx/enums.h>
#include <cdocx/format.h>
#include <memory>
#include <string>
#include <vector>

namespace cdocx {

class Document;

// ============================================================================
// Style Class
// ============================================================================

/**
 * @brief Represents a single built-in or user-defined style.
 * @details Styles are metadata, not document content nodes.
 */
class Style : public std::enable_shared_from_this<Style> {
public:
    Style();
    explicit Style(Document* doc, StyleType type = StyleType::Paragraph);

    // ------------------------------------------------------------------------
    // Identity
    // ------------------------------------------------------------------------
    std::string get_name() const { return name_; }
    void set_name(const std::string& name) { name_ = name; }

    std::string get_style_id() const { return style_id_; }
    void set_style_id(const std::string& id) { style_id_ = id; }

    StyleIdentifier get_style_identifier() const { return style_identifier_; }
    void set_style_identifier(StyleIdentifier id) { style_identifier_ = id; }

    StyleType get_type() const { return type_; }
    void set_type(StyleType type) { type_ = type; }

    bool get_is_built_in() const { return is_built_in_; }
    void set_is_built_in(bool built_in) { is_built_in_ = built_in; }

    bool get_is_default() const { return is_default_; }
    void set_is_default(bool value) { is_default_ = value; }

    // ------------------------------------------------------------------------
    // Inheritance
    // ------------------------------------------------------------------------
    std::string get_base_style_name() const { return base_style_name_; }
    void set_base_style_name(const std::string& name) { base_style_name_ = name; }

    // ------------------------------------------------------------------------
    // Formatting
    // ------------------------------------------------------------------------
    Font& get_font() { return font_; }
    const Font& get_font() const { return font_; }
    void set_font(const Font& font) { font_ = font; }

    ParagraphFormat& get_paragraph_format() { return paragraph_format_; }
    const ParagraphFormat& get_paragraph_format() const { return paragraph_format_; }
    void set_paragraph_format(const ParagraphFormat& format) { paragraph_format_ = format; }

    // ------------------------------------------------------------------------
    // Document ownership
    // ------------------------------------------------------------------------
    Document* get_document() const { return document_; }
    void set_document(Document* doc) { document_ = doc; }

    // ------------------------------------------------------------------------
    // Operations
    // ------------------------------------------------------------------------
    void remove();

private:
    Document* document_ = nullptr;
    std::string name_;
    std::string style_id_;
    StyleIdentifier style_identifier_ = StyleIdentifier::User;
    StyleType type_ = StyleType::Paragraph;
    bool is_built_in_ = false;
    bool is_default_ = false;
    std::string base_style_name_;
    Font font_;
    ParagraphFormat paragraph_format_;
};

// ============================================================================
// StyleCollection Class
// ============================================================================

/**
 * @brief A collection of Style objects representing both built-in and user-defined styles.
 */
class StyleCollection {
    std::vector<std::shared_ptr<Style>> styles_;
    Document* document_ = nullptr;

public:
    using iterator = std::vector<std::shared_ptr<Style>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Style>>::const_iterator;

    StyleCollection() = default;
    explicit StyleCollection(Document* doc) : document_(doc) {}

    size_t get_count() const { return styles_.size(); }
    bool is_empty() const { return styles_.empty(); }

    std::shared_ptr<Style> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < styles_.size()) {
            return styles_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Style> operator[](int index) const { return get_item(index); }

    std::shared_ptr<Style> get_by_name(const std::string& name) const;
    std::shared_ptr<Style> get_by_style_id(const std::string& style_id) const;
    std::shared_ptr<Style> get_by_identifier(StyleIdentifier identifier) const;

    iterator begin() { return styles_.begin(); }
    iterator end() { return styles_.end(); }
    const_iterator begin() const { return styles_.begin(); }
    const_iterator end() const { return styles_.end(); }

    std::shared_ptr<Style> first() const {
        return styles_.empty() ? nullptr : styles_.front();
    }
    std::shared_ptr<Style> last() const {
        return styles_.empty() ? nullptr : styles_.back();
    }

    std::shared_ptr<Style> add(StyleType type, const std::string& name);
    void add(const std::shared_ptr<Style>& style);
    void remove(const std::shared_ptr<Style>& style);
    void remove_at(int index);
    void clear();

    // Internal: rebuild from document
    void load_from_document();
};

} // namespace cdocx
