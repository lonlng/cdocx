/**
 * @file bookmark.h
 * @brief Bookmark management for CDocx
 * @details Provides Bookmark and BookmarkCollection classes for creating,
 *          reading, updating, and deleting document bookmarks.
 *
 * @since 0.3.0
 */

#pragma once

#include <cdocx/base.h>
#include <cdocx/constants.h>

#include <optional>
#include <string>
#include <vector>

namespace cdocx {

// ============================================================================
// Bookmark Format Structure
// ============================================================================

/**
 * @struct BookmarkFormat
 * @brief Represents formatting information extracted from a bookmark
 * @since 0.3.0
 */
struct BookmarkFormat {
    std::string font_ascii;
    std::string font_far_east;
    std::string font_hansi;
    std::string font_hint;
    int font_size = 0;
    std::string color;
    bool bold = false;
    bool italic = false;
    bool underline = false;
    bool strikethrough = false;

    std::string alignment;
    int line_spacing = 0;
    std::string line_rule;
    int space_before = 0;
    int space_after = 0;
    int first_line_indent = 0;
    int left_indent = 0;
    int right_indent = 0;
    bool keep_next = false;
    bool keep_lines = false;
    bool page_break_before = false;

    bool is_valid() const { return font_size > 0 || !font_ascii.empty() || !font_far_east.empty(); }

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
// Bookmark
// ============================================================================

/**
 * @class Bookmark
 * @brief Represents a bookmark in the document
 * @since 0.2.0
 */
class Bookmark {
  private:
    friend class Document;
    friend class BookmarkCollection;

    Document* doc_ = nullptr;
    std::string name_;
    pugi::xml_node start_node_;
    pugi::xml_node end_node_;

  public:
    Bookmark();
    Bookmark(Document* doc, std::string name, pugi::xml_node start, pugi::xml_node end);

    std::string get_name() const;
    void set_name(const std::string& name);
    std::string get_text() const;
    bool set_text(const std::string& text);
    bool is_valid() const;
    bool remove();
    bool remove_with_content();

    BookmarkFormat get_format() const;
    bool set_text_keep_format(const std::string& text);
    bool set_text_formatted(const std::string& text, const BookmarkFormat& format);
    bool is_cross_paragraph() const;
    std::vector<pugi::xml_node> get_covered_paragraphs() const;
    bool set_text_cross_paragraph(const std::string& text);
};

// ============================================================================
// BookmarkCollection
// ============================================================================

/**
 * @class BookmarkCollection
 * @brief Collection of bookmarks in a document
 * @since 0.2.0
 */
class BookmarkCollection {
  private:
    friend class Document;

    Document* doc_ = nullptr;
    mutable std::vector<Bookmark> bookmarks_;
    mutable bool collected_ = false;

    void collect_bookmarks() const;

  public:
    BookmarkCollection() : collected_(true) {}
    explicit BookmarkCollection(Document* doc);

    size_t count() const;
    Bookmark get(size_t index) const;
    std::optional<Bookmark> get(const std::string& name) const;
    bool contains(const std::string& name) const;
    bool remove(const std::string& name);
    bool remove_at(size_t index);
    void clear();
    Bookmark add(const std::string& name, Paragraph& para);

    std::vector<Bookmark>::iterator begin();
    std::vector<Bookmark>::iterator end();
    std::vector<Bookmark>::const_iterator begin() const;
    std::vector<Bookmark>::const_iterator end() const;

    std::vector<std::string> get_names() const;
};

}  // namespace cdocx
