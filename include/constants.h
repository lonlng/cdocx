/**
 * @file constants.h
 * @brief Formatting flag constants for CDocx
 * 
 * This file defines text formatting flags that can be combined
 * using bitwise operations to apply multiple styles to text.
 * 
 * @code
 * // Apply bold and italic formatting
 * cdocx::bold | cdocx::italic
 * @endcode
 */

#pragma once

namespace cdocx {

/**
 * @typedef formatting_flag
 * @brief Type alias for formatting flags
 */
typedef unsigned const int formatting_flag;

/**
 * @defgroup formatting_constants Formatting Constants
 * @brief Text formatting flags
 * 
 * These flags can be combined using bitwise OR to apply multiple styles.
 * @{
 */

/** @brief No formatting applied */
formatting_flag none = 0;
/** @brief Bold text */
formatting_flag bold = 1 << 0;
/** @brief Italic text */
formatting_flag italic = 1 << 1;
/** @brief Underlined text */
formatting_flag underline = 1 << 2;
/** @brief Strikethrough text */
formatting_flag strikethrough = 1 << 3;
/** @brief Superscript text */
formatting_flag superscript = 1 << 4;
/** @brief Subscript text */
formatting_flag subscript = 1 << 5;
/** @brief Small capitals */
formatting_flag smallcaps = 1 << 6;
/** @brief Shadow effect */
formatting_flag shadow = 1 << 7;

/** @} */ // end of formatting_constants group

} // namespace cdocx
