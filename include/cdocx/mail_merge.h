/**
 * @file mail_merge.h
 * @brief Mail merge functionality for CDocx
 * @details Aligns with Aspose.Words C++ MailMerge API.
 *          Replaces MERGEFIELD fields with data source values.
 *
 * @since 0.7.0
 */

#pragma once

#include <cdocx/base.h>
#include <cdocx/document.h>
#include <cdocx/section.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace cdocx {

// ============================================================================
// Cleanup Options
// ============================================================================

enum class MailMergeCleanupOptions : std::uint8_t {
    None = 0,
    RemoveEmptyParagraphs = 1,
    RemoveUnusedFields = 2,
    RemoveEmptyRegions = 4
};

inline MailMergeCleanupOptions operator|(MailMergeCleanupOptions lhs, MailMergeCleanupOptions rhs) {
    return static_cast<MailMergeCleanupOptions>(static_cast<std::uint8_t>(lhs) |
                                                static_cast<std::uint8_t>(rhs));
}

inline MailMergeCleanupOptions operator&(MailMergeCleanupOptions lhs, MailMergeCleanupOptions rhs) {
    return static_cast<MailMergeCleanupOptions>(static_cast<std::uint8_t>(lhs) &
                                                static_cast<std::uint8_t>(rhs));
}

// ============================================================================
// MailMerge
// ============================================================================

class MailMerge {
  public:
    explicit MailMerge(Document* doc);

    /**
     * @brief Perform simple mail merge with a map of field names to values.
     * @param data Map of field names (case-insensitive) to replacement values.
     */
    void execute(const std::map<std::string, std::string>& data);

    /**
     * @brief Perform simple mail merge with a vector of pairs.
     * @param data Vector of field name / value pairs.
     */
    void execute(const std::vector<std::pair<std::string, std::string>>& data);

    /**
     * @brief Get all MERGEFIELD names available in the document.
     * @return Vector of unique field names (without MERGEFIELD prefix).
     */
    std::vector<std::string> get_field_names() const;

    /**
     * @brief Remove all MERGEFIELD and NEXT fields from the document.
     */
    void delete_fields();

    // Cleanup options
    MailMergeCleanupOptions get_cleanup_options() const { return cleanup_options_; }
    void set_cleanup_options(MailMergeCleanupOptions options) { cleanup_options_ = options; }

  private:
    Document* doc_ = nullptr;
    MailMergeCleanupOptions cleanup_options_ = MailMergeCleanupOptions::RemoveUnusedFields;

    void execute_impl(const std::map<std::string, std::string>& data);
    std::vector<std::string> collect_field_names() const;
    void apply_cleanup();
};

}  // namespace cdocx
