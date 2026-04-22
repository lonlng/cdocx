/**
 * @file range.h
 * @brief Document range operations for CDocx
 * @details Provides the Range class for text extraction and replacement
 *          within a specific portion of the document.
 *
 * @since 0.3.0
 */

#pragma once

#include <cdocx/base.h>

#include <string>

namespace cdocx {

class Document;
class DocumentSearch;

// ============================================================================
// Range
// ============================================================================

/**
 * @class Range
 * @brief Represents a range within the document
 * @since 0.2.0
 */
class Range {
  private:
    friend class Document;
    friend class DocumentSearch;

    Document* doc_ = nullptr;
    pugi::xml_node start_para_;
    pugi::xml_node end_para_;
    size_t start_offset_ = 0;
    size_t end_offset_ = 0;

  public:
    Range();
    Range(Document* doc, pugi::xml_node start, pugi::xml_node end);

    std::string get_text() const;
    bool replace(const std::string& old_text, const std::string& new_text);
    int replace_all(const std::string& old_text, const std::string& new_text);
    bool delete_content();
    bool is_valid() const;
    void collapse(bool to_start = true);
};

}  // namespace cdocx
