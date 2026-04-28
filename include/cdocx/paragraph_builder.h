/**
 * @file paragraph_builder.h
 * @brief Paragraph builder for creating formatted paragraphs
 * @details Provides ParagraphBuilder class for programmatically creating
 *          Word paragraphs with runs and formatting.
 *
 * @copyright MIT License
 * @version 0.8.0
 */

#pragma once

#include <cdocx/fwd.h>

#include <memory>
#include <string>

namespace cdocx {

// Forward declarations
class Paragraph;
class Run;

/**
 * @class ParagraphBuilder
 * @brief Builder class for creating formatted paragraphs
 * @since 0.8.0
 *
 * @par Usage Example:
 * @code
 * auto para = cdocx::ParagraphBuilder()
 *     .add_run("Hello, ")
 *     .set_bold(true)
 *     .add_run("World!")
 *     .set_alignment("center")
 *     .build();
 * @endcode
 */
class ParagraphBuilder {
  public:
    /**
     * @brief Construct empty paragraph builder
     */
    ParagraphBuilder();

    /**
     * @brief Construct paragraph builder with initial text
     * @param text Initial paragraph text
     */
    explicit ParagraphBuilder(const std::string& text);

    /**
     * @brief Destructor
     */
    ~ParagraphBuilder() = default;

    // Disable copy, enable move
    ParagraphBuilder(const ParagraphBuilder&) = delete;
    ParagraphBuilder& operator=(const ParagraphBuilder&) = delete;
    ParagraphBuilder(ParagraphBuilder&&) = default;
    ParagraphBuilder& operator=(ParagraphBuilder&&) = default;

    // ========================================================================
    // Run Content
    // ========================================================================

    /**
     * @brief Add a run with text
     * @param text Run text content
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& add_run(const std::string& text);

    /**
     * @brief Add a run with text and formatting
     * @param text Run text content
     * @param bold Bold flag
     * @param italic Italic flag
     * @param font_size Font size in points
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& add_run(const std::string& text, bool bold, bool italic, int font_size);

    // ========================================================================
    // Formatting (applied to subsequent runs)
    // ========================================================================

    /**
     * @brief Set bold flag for subsequent runs
     * @param value true to enable bold
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_bold(bool value);

    /**
     * @brief Set italic flag for subsequent runs
     * @param value true to enable italic
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_italic(bool value);

    /**
     * @brief Set underline flag for subsequent runs
     * @param value true to enable underline
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_underline(bool value);

    /**
     * @brief Set font name for subsequent runs
     * @param name Font family name
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_font_name(const std::string& name);

    /**
     * @brief Set font size for subsequent runs
     * @param size Font size in points
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_font_size(int size);

    /**
     * @brief Set text color for subsequent runs
     * @param color_hex Hex color code (e.g., "FF0000")
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_color(const std::string& color_hex);

    /**
     * @brief Set paragraph alignment
     * @param alignment "left", "center", "right", or "justify"
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& set_alignment(const std::string& alignment);

    /**
     * @brief Clear all run formatting
     * @return Reference to this builder for chaining
     */
    ParagraphBuilder& clear_formatting();

    // ========================================================================
    // Build
    // ========================================================================

    /**
     * @brief Build the paragraph
     * @return Shared pointer to the created paragraph
     */
    std::shared_ptr<Paragraph> build();

  private:
    std::shared_ptr<Paragraph> para_;
    bool bold_ = false;
    bool italic_ = false;
    bool underline_ = false;
    std::string font_name_;
    int font_size_ = 0;
    std::string color_;
    std::string alignment_;

    void apply_current_formatting(Run& run);
};

}  // namespace cdocx
