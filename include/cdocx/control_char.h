/**
 * @file control_char.h
 * @brief Control characters often encountered in documents
 * @details Provides constants for special characters used in Word documents,
 *          such as paragraph breaks, page breaks, tab characters, etc.
 *
 * @par Usage Example:
 * @code
 * builder.write("Line 1" + cdocx::ControlChar::paragraph_break());
 * builder.write("Column A" + cdocx::ControlChar::tab() + "Column B");
 * @endcode
 *
 * @since 0.8.0
 */

#pragma once

#include <string>

namespace cdocx {

/**
 * @class ControlChar
 * @brief Control characters commonly used in Word documents
 * @since 0.8.0
 */
class ControlChar {
  public:
    ControlChar() = delete;

    /// @brief Tab character: "\t"
    static std::string tab() { return "\t"; }

    /// @brief Line feed character: "\n"
    static std::string line_feed() { return "\n"; }

    /// @brief Line break character: "\v"
    static std::string line_break() { return "\v"; }

    /// @brief Page break character: "\f"
    static std::string page_break() { return "\f"; }

    /// @brief Section break character: "\f"
    static std::string section_break() { return "\f"; }

    /// @brief Paragraph break character: "\r"
    static std::string paragraph_break() { return "\r"; }

    /// @brief Carriage return + line feed: "\r\n"
    static std::string crlf() { return "\r\n"; }

    /// @brief Column break character
    static std::string column_break() {
        return std::string(1, '\x0e');
    }  // NOLINT(modernize-return-braced-init-list)

    /// @brief Non-breaking space character
    static std::string non_breaking_space() {
        return std::string(1, '\xa0');
    }  // NOLINT(modernize-return-braced-init-list)

    /// @brief End of a table cell or table row marker
    static std::string cell() {
        return std::string(1, '\x07');
    }  // NOLINT(modernize-return-braced-init-list)

    // Character code constants
    static constexpr char kTabChar = '\t';
    static constexpr char kLineFeedChar = '\n';
    static constexpr char kLineBreakChar = '\v';
    static constexpr char kPageBreakChar = '\f';
    static constexpr char kSectionBreakChar = '\f';
    static constexpr char kParagraphBreakChar = '\r';
    static constexpr char kColumnBreakChar = '\x0e';
    static constexpr char kNonBreakingSpaceChar = '\xa0';
    static constexpr char kCellChar = '\x07';
    static constexpr char kFieldStartChar = '\x13';
    static constexpr char kFieldSeparatorChar = '\x14';
    static constexpr char kFieldEndChar = '\x15';
};

}  // namespace cdocx
