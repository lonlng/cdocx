/**
 * @file constants.h
 * @brief CDocx library constants and formatting flags
 * @details Defines text formatting flags used throughout the CDocx library
 *          for applying styles to text runs in Word documents.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 *
 * @example
 * @code
 * #include <cdocx/constants.h>
 *
 * // Apply bold and italic formatting
 * paragraph->add_run("Bold Italic Text", cdocx::kBold | cdocx::kItalic);
 *
 * // Apply underline with strikethrough
 * paragraph->add_run("Underlined Strike", cdocx::kUnderline | cdocx::kStrikethrough);
 * @endcode
 */

#pragma once

namespace cdocx {

/**
 * @brief Formatting flag type for text styling
 * @details Used as a bitmask to combine multiple formatting options.
 *          Multiple flags can be combined using bitwise OR operator.
 * @since 0.1.0
 */
using FormattingFlag = unsigned int;

// ============================================================================
// Text Formatting Flags
// ============================================================================

/**
 * @name Text Formatting Flags
 * Bit flags for text formatting. Can be combined using bitwise OR.
 * @{
 */

/**
 * @brief No formatting applied
 * @details Default formatting with no special styling
 */
constexpr FormattingFlag kNone = 0;

/**
 * @brief Bold text formatting
 * @details Applies bold weight to the text
 * @see Run::set_bold()
 */
constexpr FormattingFlag kBold = 1 << 0;  ///< Bit 0

/**
 * @brief Italic text formatting
 * @details Applies italic style to the text
 * @see Run::set_italic()
 */
constexpr FormattingFlag kItalic = 1 << 1;  ///< Bit 1

/**
 * @brief Underline text formatting
 * @details Applies single underline to the text
 * @see Run::set_underline()
 */
constexpr FormattingFlag kUnderline = 1 << 2;  ///< Bit 2

/**
 * @brief Strikethrough text formatting
 * @details Draws a line through the text
 */
constexpr FormattingFlag kStrikethrough = 1 << 3;  ///< Bit 3

/**
 * @brief Superscript text formatting
 * @details Raises text above the baseline
 * @note Mutually exclusive with subscript
 * @see kSubscript
 */
constexpr FormattingFlag kSuperscript = 1 << 4;  ///< Bit 4

/**
 * @brief Subscript text formatting
 * @details Lowers text below the baseline
 * @note Mutually exclusive with superscript
 * @see kSuperscript
 */
constexpr FormattingFlag kSubscript = 1 << 5;  ///< Bit 5

/**
 * @brief Small caps text formatting
 * @details Converts lowercase letters to small capital letters
 */
constexpr FormattingFlag kSmallCaps = 1 << 6;  ///< Bit 6

/**
 * @brief Shadow text effect
 * @details Adds shadow effect to text
 */
constexpr FormattingFlag kShadow = 1 << 7;  ///< Bit 7

/** @} */  // End of Text Formatting Flags

// ============================================================================
// Common Formatting Combinations
// ============================================================================

/**
 * @name Predefined Formatting Combinations
 * Common combinations of formatting flags for convenience.
 * @{
 */

/**
 * @brief Bold and italic combination
 */
constexpr FormattingFlag kBoldItalic = kBold | kItalic;

/**
 * @brief Bold, italic and underline combination
 */
constexpr FormattingFlag kBoldItalicUnderline = kBold | kItalic | kUnderline;

/** @} */  // End of Predefined Formatting Combinations

}  // namespace cdocx
