/**
 * @file caption_generator.h
 * @brief Figure caption generation for CDocx
 * @details Provides CaptionGenerator class for creating standardized
 *          Chinese figure captions in the format "图 X [description]".
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 *
 * @par Usage Example:
 * @code
 * #include <cdocx/caption_generator.h>
 *
 * cdocx::Document doc("template.docx");
 * doc.open();
 *
 * // Insert figure caption after a specific paragraph
 * cdocx::CaptionGenerator::insert_figure_caption(&doc, para,
 *                                                "GPR Detection Result", 1);
 *
 * // Auto-numbered caption
 * int next_number = cdocx::CaptionGenerator::count_existing_figures(&doc) + 1;
 * cdocx::CaptionGenerator::insert_figure_caption(&doc, para,
 *                                                "Chart Analysis", next_number);
 *
 * doc.save("output.docx");
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>

#include <pugixml.hpp>
#include <string>
#include <vector>

namespace cdocx {

/**
 * @class CaptionGenerator
 * @brief Utility class for generating figure captions
 * @details Generates standardized Chinese figure captions with proper
 *          formatting (SimSun font for Chinese, Times New Roman for numbers).
 *
 * @par Format Specification:
 * - Text: "图 X [description]" (e.g., "图 1 GPR Detection Result")
 * - Font: Chinese = SimSun, Western = Times New Roman
 * - Size: 10.5pt (五号)
 * - Alignment: Center
 *
 * @since 0.3.0
 */
class CaptionGenerator {
  public:
    /**
     * @brief Insert a figure caption after specified paragraph
     * @param[in] doc Target document
     * @param[in] after_para Paragraph node after which to insert caption
     * @param[in] description Caption description text
     * @param[in] figure_number Figure number (auto-generated if 0)
     * @return The created caption paragraph node, or empty node on failure
     */
    static pugi::xml_node insert_figure_caption(Document* doc,
                                                pugi::xml_node after_para,
                                                const std::string& description,
                                                int figure_number = 0);

    /**
     * @brief Insert figure caption at end of document
     * @param[in] doc Target document
     * @param[in] description Caption description text
     * @param[in] figure_number Figure number (auto-generated if 0)
     * @return The created caption paragraph node, or empty node on failure
     */
    static pugi::xml_node insert_figure_caption_at_end(Document* doc,
                                                       const std::string& description,
                                                       int figure_number = 0);

    /**
     * @brief Count existing figures in document
     * @param[in] doc Target document
     * @return Number of figures detected in document
     * @details Searches for paragraphs starting with "图 X" pattern
     */
    static int count_existing_figures(Document* doc);

    /**
     * @brief Generate next figure number
     * @param[in] doc Target document
     * @return Next available figure number (count + 1)
     */
    static int get_next_figure_number(Document* doc);

    /**
     * @brief Check if paragraph is a figure caption
     * @param[in] para Paragraph node to check
     * @return true if paragraph starts with "图 X" pattern
     */
    static bool is_figure_caption(pugi::xml_node para);

    /**
     * @brief Get caption text from paragraph
     * @param[in] para Paragraph node
     * @return Caption text (description part only), or empty string
     */
    static std::string extract_caption_text(pugi::xml_node para);

  private:
    /**
     * @brief Create caption paragraph with proper formatting
     * @param[in] doc Target document
     * @param[in] full_text Complete caption text ("图 X description")
     * @param[in] insert_after Node to insert after (null for end)
     * @return Created paragraph node
     */
    static pugi::xml_node create_caption_paragraph(Document* doc,
                                                   const std::string& full_text,
                                                   pugi::xml_node insert_after);

    /**
     * @brief Generate full caption text
     * @param[in] figure_number Figure number
     * @param[in] description Description text
     * @return Formatted caption text
     */
    static std::string generate_caption_text(int figure_number, const std::string& description);

    /**
     * @brief Get document body node
     * @param[in] doc Target document
     * @return Body node, or empty node if not found
     */
    static pugi::xml_node get_body(Document* doc);
};

/**
 * @struct CaptionFormat
 * @brief Format specification for captions
 * @since 0.3.0
 */
struct CaptionFormat {
    std::string font_ascii = "Times New Roman";  ///< Western font
    std::string font_east_asia = "SimSun";       ///< Chinese font
    std::string font_hansi = "Times New Roman";  ///< ANSI font
    int font_size = 21;                          ///< Size in half-points (21 = 10.5pt)
    std::string alignment = "center";            ///< Paragraph alignment

    /**
     * @brief Create default Chinese caption format
     * @return CaptionFormat with Chinese defaults
     */
    static CaptionFormat chinese_default() {
        CaptionFormat fmt;
        fmt.font_ascii = "Times New Roman";
        fmt.font_east_asia = "SimSun";
        fmt.font_hansi = "Times New Roman";
        fmt.font_size = 21;  // 10.5pt
        fmt.alignment = "center";
        return fmt;
    }
};

}  // namespace cdocx
