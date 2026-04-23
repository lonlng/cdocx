/**
 * @file template.h
 * @brief Template-based placeholder replacement for DOCX documents
 * @details Provides the Template class for replacing placeholder strings
 *          in documents using customizable patterns (default: {{key}}).
 *          Supports both text and image placeholders with FSM-based
 *          processing for handling placeholders split across multiple runs.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 *
 * @par Usage Example:
 * @code
 * #include <cdocx/template.h>
 *
 * cdocx::Document doc("template.docx");
 * doc.open();
 *
 * // Create template processor
 * cdocx::Template tmpl(&doc);
 *
 * // Set text placeholder
 * tmpl.set("name", "John Doe");
 * tmpl.set("date", "2024-01-15");
 * tmpl.set("company", "Acme Inc.");
 *
 * // Set image placeholder
 * tmpl.set_image("logo", "path/to/logo.png");
 *
 * // Execute replacement
 * tmpl.replace_all();
 *
 * // Save result
 * doc.save("output.docx");
 * @endcode
 */

#pragma once

#include <cdocx/base.h>
#include <cdocx/fwd.h>
#include <cdocx/paragraph.h>

#include <map>
#include <string>
#include <vector>

namespace cdocx {

/**
 * @class Template
 * @brief Template engine for placeholder replacement in DOCX documents
 * @details The Template class provides a powerful mechanism for replacing
 *          placeholders in Word documents. It uses a Finite State Machine (FSM)
 *          to handle placeholders that may be split across multiple text runs.
 *
 * @par Supported Placeholder Formats:
 * - Default format: {{key}}
 * - Custom format: set prefix and suffix via set_pattern()
 *
 * @par Processing Flow:
 * 1. Set placeholder values (set(), set_image())
 * 2. Execute replacement (replace_all())
 * 3. Save document
 *
 * @par Notes:
 * - Placeholder matching is case-sensitive
 * - Supports placeholders across multiple runs
 * - Image placeholders are replaced with actual images
 *
 * @see Document, Document::get_paragraphs()
 * @since 0.1.0
 */
class Template {
  private:
    Document* doc_;                                          ///< Target document pointer
    std::map<std::string, std::string> placeholders_;        ///< Text placeholders
    std::map<std::string, std::string> image_placeholders_;  ///< Image placeholders
    std::string pattern_prefix_ = "{{";                      ///< Placeholder start pattern
    std::string pattern_suffix_ = "}}";                      ///< Placeholder end pattern

    /**
     * @struct PlaceholderContext
     * @brief Internal state for FSM-based placeholder processing
     * @details Maintains state while scanning for multi-run placeholders
     */
    struct PlaceholderContext {
        Run* first_run = nullptr;          ///< First run of current placeholder
        std::vector<Run*> runs_to_delete;  ///< Runs to clean up after replacement
        std::string collected_text;        ///< Accumulated text across runs
        size_t prefix_pos = 0;             ///< Position in prefix pattern

        /**
         * @brief Reset the context state
         */
        void clear() {
            first_run = nullptr;
            runs_to_delete.clear();
            collected_text.clear();
            prefix_pos = 0;
        }
    };

    /**
     * @brief Replace placeholders in a string
     * @param[in,out] text Text to process (modified in place)
     * @return true if any replacement was made
     */
    bool try_replace_in_text(std::string& text);

    /**
     * @brief Replace placeholders in all paragraphs
     */
    void replace_in_paragraphs();

    /**
     * @brief Replace placeholders in all tables
     */
    void replace_in_tables();

    /**
     * @brief Replace placeholders in headers and footers
     * @return true if any replacement was made
     */
    bool replace_in_headers_footers();

    /**
     * @brief Replace placeholders in a single paragraph
     * @return true if any replacement was made
     */
    bool replace_in_paragraph(const std::shared_ptr<Paragraph>& para);

    /**
     * @brief Replace placeholders in a single table
     * @return true if any replacement was made
     */
    bool replace_in_table(const std::shared_ptr<Table>& table);

    /**
     * @brief Replace only the first placeholder in a single paragraph
     * @return true if a replacement was made
     */
    bool replace_first_in_paragraph(const std::shared_ptr<Paragraph>& para);

    /**
     * @brief Replace only the first placeholder in a single table
     * @return true if a replacement was made
     */
    bool replace_first_in_table(const std::shared_ptr<Table>& table);

    /**
     * @brief Replace only the first placeholder in headers/footers
     * @return true if a replacement was made
     */
    bool replace_first_in_headers_footers();

    /**
     * @brief Replace image placeholder in a single run
     */
    bool replace_image_in_run(const std::shared_ptr<Run>& run);

    /**
     * @brief Legacy: Process a single paragraph for placeholders
     * @param[in,out] p Paragraph to process
     * @param[in] stop_after_first If true, return after first successful replacement
     * @return true if any replacement was made
     */
    bool process_paragraph(Paragraph& p, bool stop_after_first = false);

    /**
     * @brief Legacy: Try to replace placeholder in a single run
     * @param[in,out] r The run to process
     * @param[in] first_only If true, replace only the first occurrence
     * @return true if replacement was successful
     */
    bool try_replace_single_run(Run& r, bool first_only = false);

    /**
     * @brief Legacy: Try to replace a collected placeholder
     * @param[in] ctx Placeholder context
     * @param[in,out] p Current paragraph
     * @return true if replacement was successful
     */
    bool try_replace_placeholder(const PlaceholderContext& ctx, Paragraph& p);

    /**
     * @brief Legacy: Delete runs collected during placeholder detection
     * @param[in] ctx Placeholder context
     * @param[in,out] p Current paragraph
     */
    void delete_collected_runs(const PlaceholderContext& ctx, Paragraph& p);

    /**
     * @brief Legacy: Transition to collecting state in FSM
     * @param[in,out] ctx Placeholder context
     * @param[in,out] r Current run
     * @param[in] text Current text
     * @param[in] prefix_pos Position in prefix pattern
     */
    void transition_to_collecting_state(PlaceholderContext& ctx,
                                        Run& r,
                                        const std::string& text,
                                        size_t prefix_pos);

    /**
     * @brief Legacy: Process a paragraph using old API
     * @param[in,out] para Paragraph to process
     * @return true if any replacement was made
     */
    bool process_paragraph_legacy(Paragraph& para);

  public:
    /**
     * @brief Construct template processor with default pattern
     * @param[in] document Target document (must remain valid during processing)
     */
    explicit Template(Document* document);

    /**
     * @brief Construct template processor with custom pattern
     * @param[in] document Target document
     * @param[in] prefix Placeholder start pattern (e.g., "<%")
     * @param[in] suffix Placeholder end pattern (e.g., "%>")
     */
    Template(Document* document, std::string prefix, std::string suffix);

    /**
     * @brief Set a text placeholder value
     * @param[in] key Placeholder key (without delimiters)
     * @param[in] value Replacement value
     *
     * @par Example:
     * @code
     * tmpl.set("name", "John Doe");
     * // Will replace {{name}} with "John Doe"
     * @endcode
     */
    void set(const std::string& key, const std::string& value);

    /**
     * @brief Set a text placeholder value (C-string version)
     * @param[in] key Placeholder key
     * @param[in] value Replacement value
     */
    void set(const std::string& key, const char* value);

    /**
     * @brief Set an image placeholder
     * @param[in] key Placeholder key
     * @param[in] image_path Path to the image file
     *
     * @par Example:
     * @code
     * tmpl.set_image("logo", "images/company_logo.png");
     * // Will replace {{logo}} with the image
     * @endcode
     */
    void set_image(const std::string& key, const std::string& image_path);

    /**
     * @brief Set custom placeholder pattern
     * @param[in] prefix Start pattern
     * @param[in] suffix End pattern
     *
     * @par Example:
     * @code
     * tmpl.set_pattern("<%", "%>");  // Will match <%key%>
     * tmpl.set_pattern("${", "}");   // Will match ${key}
     * @endcode
     */
    void set_pattern(const std::string& prefix, const std::string& suffix);

    /**
     * @brief Replace all placeholders in the document
     * @details Scans all paragraphs and tables, replacing placeholders
     *          with their corresponding values.
     * @pre Document must be open
     * @post All matching placeholders are replaced
     */
    void replace_all();

    /**
     * @brief Replace only the first placeholder found in the document
     * @details Scans paragraphs, tables, and headers/footers in order,
     *          replacing the first matching placeholder and stopping.
     * @return true if a replacement was made
     * @since 0.8.0
     */
    bool replace_first();

    /**
     * @brief Clear all placeholder values
     * @details Removes all set values but keeps the pattern configuration
     */
    void clear();

    /**
     * @brief Get the number of set placeholders
     * @return Total count of text and image placeholders
     */
    size_t size() const { return placeholders_.size() + image_placeholders_.size(); }

    /**
     * @brief Check if any placeholders are set
     * @return true if there are placeholders to replace
     */
    bool has_placeholders() const;

    /**
     * @brief Get total placeholder count
     * @return Total number of placeholders
     */
    size_t get_placeholder_count() const;
};

}  // namespace cdocx
