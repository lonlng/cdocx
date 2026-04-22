/**
 * @file document_search.h
 * @brief Document search and replace for CDocx
 * @details Provides the DocumentSearch static utility class for finding
 *          and replacing text throughout the document.
 *
 * @since 0.3.0
 */

#pragma once

#include <cdocx/range.h>

#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace cdocx {

// ============================================================================
// DocumentSearch
// ============================================================================

/**
 * @class DocumentSearch
 * @brief Static utility class for searching and replacing text
 * @since 0.2.0
 */
class DocumentSearch {
  public:
    using SearchCallback = std::function<bool(const std::string& found_text, Range& range)>;

    static std::optional<Range> find(Document& doc, const std::string& text);
    static std::vector<Range> find_all(Document& doc, const std::string& text);
    static bool replace(Document& doc, const std::string& old_text, const std::string& new_text);
    static int replace_all(Document& doc, const std::string& old_text, const std::string& new_text);
    static bool replace_with_formatting(Document& doc,
                                        const std::string& old_text,
                                        const std::string& new_text,
                                        formatting_flag flag);
    static int find_and_process(Document& doc,
                                const std::string& pattern,
                                const SearchCallback& callback);
};

}  // namespace cdocx
