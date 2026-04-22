/**
 * @file advanced.h
 * @brief Advanced features for CDocx (aggregate header)
 * @details This header includes all advanced functionality:
 *          - Bookmark management (bookmark.h)
 *          - Document range operations (range.h)
 *          - DocumentBuilder for fluent construction (document_builder.h)
 *          - DocumentSearch for find/replace (document_search.h)
 *
 *          For finer-grained includes, include the specific headers directly.
 *
 * @since 0.2.0
 * @deprecated_include Prefer including bookmark.h, range.h, document_builder.h,
 *                     or document_search.h directly depending on your needs.
 */

#pragma once

#include <cdocx/bookmark.h>
#include <cdocx/document_builder.h>
#include <cdocx/document_search.h>
#include <cdocx/range.h>

#include <cdocx/base.h>
#include <cdocx/formfield.h>

#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace cdocx {

// ============================================================================
// Table Operations
// ============================================================================

/**
 * @class TableOperations
 * @brief Static utility class for table manipulation
 * @since 0.2.0
 */
class TableOperations {
  public:
    static bool insert_row(Table& table, size_t index);
    static bool append_row(Table& table);
    static bool delete_row(Table& table, size_t index);
    static bool insert_cell(Row& row, size_t index);
    static bool delete_cell(Row& row, size_t index);
    static size_t get_row_count(const Table& table);
    static size_t get_column_count(const Table& table);
    static bool merge_cells_horizontal(Row& row, size_t start, size_t end);
    static bool set_cell_text(Cell& cell, const std::string& text);
    static std::string get_cell_text(const Cell& cell);
};

// ============================================================================
// Utility Functions
// ============================================================================

namespace utils {

inline int points_to_twips(double points) {
    return static_cast<int>(points * 20);
}

inline double twips_to_points(int twips) {
    return twips / 20.0;
}

inline int inches_to_twips(double inches) {
    return static_cast<int>(inches * 1440);
}

inline bool starts_with_ci(const std::string& str, const std::string& prefix) {
    if (prefix.size() > str.size()) {
        return false;
    }
    return std::equal(prefix.begin(), prefix.end(), str.begin(), [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    });
}

inline bool contains_ci(const std::string& str, const std::string& substr) {
    if (substr.empty()) {
        return true;
    }
    if (substr.size() > str.size()) {
        return false;
    }
    auto it = std::search(str.begin(), str.end(), substr.begin(), substr.end(), [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    });
    return it != str.end();
}

inline std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

}  // namespace utils

}  // namespace cdocx
