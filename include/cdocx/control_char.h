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
 * @since 0.7.0
 */

#pragma once

#include <string>

namespace cdocx {

/**
 * @class ControlChar
 * @brief Control characters commonly used in Word documents
 * @since 0.7.0
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
    static std::string column_break() { return std::string(1, '\x0e'); }

    /// @brief Non-breaking space character
    static std::string non_breaking_space() { return std::string(1, '\xa0'); }

    /// @brief End of a table cell or table row marker
    static std::string cell() { return std::string(1, '\x07'); }

    // Character code constants
    static constexpr char tab_char = '\t';
    static constexpr char line_feed_char = '\n';
    static constexpr char line_break_char = '\v';
    static constexpr char page_break_char = '\f';
    static constexpr char section_break_char = '\f';
    static constexpr char paragraph_break_char = '\r';
    static constexpr char column_break_char = '\x0e';
    static constexpr char non_breaking_space_char = '\xa0';
    static constexpr char cell_char = '\x07';
    static constexpr char field_start_char = '\x13';
    static constexpr char field_separator_char = '\x14';
    static constexpr char field_end_char = '\x15';
};

} // namespace cdocx
