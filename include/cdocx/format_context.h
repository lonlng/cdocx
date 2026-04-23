/**
 * @file format_context.h
 * @brief Text formatting context for unified formatting operations
 * @details Provides a unified way to apply text formatting (color, font size,
 *          font name, bold, italic, underline) to XML run elements. This class
 *          is used internally by Run and Paragraph to avoid code duplication.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 */

#pragma once

#include <pugixml.hpp>
#include <string>

namespace cdocx {

/**
 * @class TextFormatContext
 * @brief Helper class for applying text formatting to XML run elements
 * @details This class provides static methods to apply various text formatting
 *          attributes to a w:r (run) element. It centralizes the formatting logic
 *          to ensure consistency between Run and Paragraph classes.
 *
 * @par Usage Example:
 * @code
 * pugi::xml_node run = ...; // Get a run element
 *
 * // Apply formatting
 * TextFormatContext::apply_color(run, "FF0000");
 * TextFormatContext::apply_font_size(run, 24);
 * TextFormatContext::apply_bold(run, true);
 * @endcode
 *
 * @see Run, Paragraph
 * @since 0.3.0
 */
class TextFormatContext {
  public:
    /**
     * @brief Apply text color to a run
     * @param[in] run The w:r XML element
     * @param[in] color_hex Hex color code (e.g., "FF0000" for red)
     * @return true if successful, false if run is invalid
     */
    static bool apply_color(pugi::xml_node run, const std::string& color_hex);

    /**
     * @brief Apply font size to a run
     * @param[in] run The w:r XML element
     * @param[in] size Font size in half-points (e.g., 24 for 12pt)
     * @return true if successful, false if run is invalid
     */
    static bool apply_font_size(pugi::xml_node run, int size);

    /**
     * @brief Apply font name to a run
     * @param[in] run The w:r XML element
     * @param[in] font_name Font family name (e.g., "Arial", "Times New Roman")
     * @return true if successful, false if run is invalid
     */
    static bool apply_font_name(pugi::xml_node run, const std::string& font_name);

    /**
     * @brief Apply bold formatting to a run
     * @param[in] run The w:r XML element
     * @param[in] bold true to apply bold, false to remove
     * @return true if successful, false if run is invalid
     */
    static bool apply_bold(pugi::xml_node run, bool bold);

    /**
     * @brief Apply italic formatting to a run
     * @param[in] run The w:r XML element
     * @param[in] italic true to apply italic, false to remove
     * @return true if successful, false if run is invalid
     */
    static bool apply_italic(pugi::xml_node run, bool italic);

    /**
     * @brief Apply underline formatting to a run
     * @param[in] run The w:r XML element
     * @param[in] underline true to apply underline, false to remove
     * @return true if successful, false if run is invalid
     */
    static bool apply_underline(pugi::xml_node run, bool underline);

  private:
    /**
     * @brief Get or create the w:rPr (run properties) element
     * @param[in] run The w:r element
     * @return The w:rPr element (created if didn't exist)
     */
    static pugi::xml_node get_or_create_r_pr(pugi::xml_node run);
};

}  // namespace cdocx
