/**
 * @file template_engine.h
 * @brief Unified template engine for DOCX documents
 * @details Provides a dictionary-style API for template population:
 *          engine["key"] = TemplateValue::text("hello");
 *          engine.set("logo", TemplateValue::image("logo.png"));
 *          Supports text, image, custom format, preserve/original format,
 *          replace/insert modes, first/all match scope.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.1.0
 *
 * @par Usage Example:
 * @code
 * #include <cdocx/template_engine.h>
 *
 * cdocx::Document doc("template.docx");
 * doc.open();
 *
 * cdocx::TemplateEngine engine(&doc);
 *
 * // Dictionary style
 * engine["company"] = cdocx::TemplateValue::text("Acme Inc.");
 * engine["date"]    = cdocx::TemplateValue::text("2025-04-21");
 * engine["logo"]    = cdocx::TemplateValue::image("logo.png")
 *                                      .sized(400, 300)
 *                                      .centered();
 *
 * // With custom format
 * engine["title"] = cdocx::TemplateValue::text("Annual Report")
 *     .with_format(cdocx::TemplateFormat().bold().size(24).color("FF0000"));
 *
 * // Batch from map
 * std::map<std::string, std::string> data = {
 *     {"name", "John"}, {"dept", "Engineering"}
 * };
 * engine.set_batch(data);
 *
 * // Configure behavior
 * engine.with_scope(cdocx::TemplateScope::All)
 *       .with_target(cdocx::TemplateTarget::Auto)
 *       .with_format_policy(cdocx::FormatPolicy::Preserve);
 *
 * auto result = engine.apply();
 * std::cout << "Replaced: " << result.success << std::endl;
 *
 * doc.save("output.docx");
 * @endcode
 */

#pragma once

#include <cdocx/advanced.h>
#include <cdocx/base.h>
#include <cdocx/fwd.h>

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>

namespace cdocx {

// ============================================================================
// Forward Declarations
// ============================================================================

class TemplateValue;
class TemplateEngine;

// ============================================================================
// TemplateValueType
// ============================================================================

/**
 * @enum TemplateValueType
 * @brief Types of values that can be inserted into a template
 * @since 0.8.0
 */
enum class TemplateValueType : std::uint8_t {
    Text,   ///< Plain text content
    Image,  ///< Image file (PNG, JPEG, etc.)
};

// ============================================================================
// TemplateAction
// ============================================================================

/**
 * @enum TemplateAction
 * @brief How to apply the value to the template
 * @since 0.8.0
 */
enum class TemplateAction : std::uint8_t {
    Replace,  ///< Replace existing content (default)
    Insert,   ///< Insert new content without removing existing
};

// ============================================================================
// TemplateScope
// ============================================================================

/**
 * @enum TemplateScope
 * @brief How many occurrences to match
 * @since 0.8.0
 */
enum class TemplateScope : std::uint8_t {
    First,  ///< Match only the first occurrence
    All,    ///< Match all occurrences (default)
};

// ============================================================================
// TemplateTarget
// ============================================================================

/**
 * @enum TemplateTarget
 * @brief What to search for in the document
 * @since 0.8.0
 */
enum class TemplateTarget : std::uint8_t {
    Placeholder,  ///< Search for {{key}} style placeholders
    BookmarkTarget,     ///< Search for Word bookmarks by name
    Auto,         ///< Try bookmark first, fallback to placeholder (default)
};

// ============================================================================
// FormatPolicy
// ============================================================================

/**
 * @enum FormatPolicy
 * @brief How to handle formatting during replacement
 * @since 0.8.0
 */
enum class FormatPolicy : std::uint8_t {
    Preserve,  ///< Preserve original document formatting (default)
    Override,  ///< Use the format specified in TemplateValue
    Custom,    ///< Use the explicitly set format, fall back to Preserve
};

// ============================================================================
// TemplateFormat
// ============================================================================

/**
 * @class TemplateFormat
 * @brief Formatting specification for template values
 * @details Chainable builder for text formatting. Unspecified fields are
 *          ignored unless FormatPolicy::Override is set.
 *
 * @par Usage:
 * @code
 * auto fmt = cdocx::TemplateFormat()
 *     .bold()
 *     .italic()
 *     .size(14)
 *     .font("SimSun")
 *     .color("FF0000")
 *     .alignment("center");
 * @endcode
 *
 * @since 0.8.0
 */
class TemplateFormat {
  public:
    TemplateFormat() = default;

    // Character formatting
    TemplateFormat& bold(bool value = true);
    TemplateFormat& italic(bool value = true);
    TemplateFormat& underline(bool value = true);
    TemplateFormat& strikethrough(bool value = true);
    TemplateFormat& size(int half_points);
    TemplateFormat& font(const std::string& name);
    TemplateFormat& font_ascii(const std::string& name);
    TemplateFormat& font_far_east(const std::string& name);
    TemplateFormat& color(const std::string& hex);

    // Paragraph formatting
    TemplateFormat& alignment(const std::string& align);
    TemplateFormat& line_spacing(int twips);
    TemplateFormat& space_before(int twips);
    TemplateFormat& space_after(int twips);

    // Conversion to BookmarkFormat for internal use
    BookmarkFormat to_bookmark_format() const;

    // Check if any format is specified
    bool is_empty() const;

    // Accessors
    const std::optional<bool>& bold_opt() const { return bold_; }
    const std::optional<bool>& italic_opt() const { return italic_; }
    const std::optional<bool>& underline_opt() const { return underline_; }
    const std::optional<int>& size_opt() const { return size_; }
    const std::optional<std::string>& font_opt() const { return font_; }
    const std::optional<std::string>& color_opt() const { return color_; }
    const std::optional<std::string>& alignment_opt() const { return alignment_; }

  private:
    std::optional<bool> bold_;
    std::optional<bool> italic_;
    std::optional<bool> underline_;
    std::optional<bool> strikethrough_;
    std::optional<int> size_;            ///< Font size in half-points
    std::optional<std::string> font_;    ///< Font name (applies to all scripts)
    std::optional<std::string> font_ascii_;
    std::optional<std::string> font_far_east_;
    std::optional<std::string> color_;   ///< Hex color (e.g. "FF0000")
    std::optional<std::string> alignment_;
    std::optional<int> line_spacing_;
    std::optional<int> space_before_;
    std::optional<int> space_after_;
};

// ============================================================================
// TemplateValue
// ============================================================================

/**
 * @class TemplateValue
 * @brief A polymorphic value for template population
 * @details Represents either text or image content, with optional formatting
 *          and sizing. Created via static factory methods and configured
 *          through chainable setters.
 *
 * @par Usage:
 * @code
 * auto text = cdocx::TemplateValue::text("Hello World")
 *     .with_format(cdocx::TemplateFormat().bold().size(24));
 *
 * auto img = cdocx::TemplateValue::image("chart.png")
 *     .sized(400, 300)
 *     .centered()
 *     .with_caption("Figure 1");
 * @endcode
 *
 * @since 0.8.0
 */
class TemplateValue {
  public:
    // ===================================================================
    // Construction
    // ===================================================================

    /** @brief Default constructor (creates empty text value) */
    TemplateValue() : type_(TemplateValueType::Text), data_(TextData{}) {}

    // ===================================================================
    // Factory Methods
    // ===================================================================

    /**
     * @brief Create a text value
     * @param content Text content
     * @return TemplateValue configured as text
     */
    static TemplateValue text(const std::string& content);

    /**
     * @brief Create a text value with format
     * @param content Text content
     * @param format Format specification
     * @return TemplateValue configured as text
     */
    static TemplateValue text(const std::string& content, const TemplateFormat& format);

    /**
     * @brief Create an image value
     * @param path Path to image file
     * @return TemplateValue configured as image
     */
    static TemplateValue image(const std::string& path);

    /**
     * @brief Create an image value with explicit size
     * @param path Path to image file
     * @param width Width in points
     * @param height Height in points
     * @return TemplateValue configured as image
     */
    static TemplateValue image(const std::string& path, double width, double height);

    // ===================================================================
    // Chainable Configuration
    // ===================================================================

    /** @brief Set format for text values */
    TemplateValue& with_format(const TemplateFormat& format);

    /** @brief Set image size in points */
    TemplateValue& sized(double width_pt, double height_pt);

    /** @brief Set image size via ImageSize */
    TemplateValue& sized(const ImageSize& size);

    /** @brief Center the image (shorthand for alignment) */
    TemplateValue& centered();

    /** @brief Left-align the image */
    TemplateValue& left_aligned();

    /** @brief Right-align the image */
    TemplateValue& right_aligned();

    /** @brief Set image caption */
    TemplateValue& with_caption(const std::string& caption);

    /** @brief Set image alignment */
    TemplateValue& with_alignment(ImageAlignment align);

    // ===================================================================
    // Queries
    // ===================================================================

    TemplateValueType type() const { return type_; }
    bool is_text() const { return type_ == TemplateValueType::Text; }
    bool is_image() const { return type_ == TemplateValueType::Image; }

    /** @brief True if this value has no meaningful content (empty text or no image path) */
    bool is_empty() const { return (is_text() && text_content().empty()) || (is_image() && image_path().empty()); }

    const std::string& text_content() const;
    const TemplateFormat& text_format() const;

    const std::string& image_path() const;
    const ImageSize& image_size() const;
    const std::string& image_caption() const;
    ImageAlignment image_alignment() const;

  private:
    struct TextData {
        std::string content;
        TemplateFormat format;
    };

    struct ImageData {
        std::string path;
        ImageSize size;
        std::string caption;
        ImageAlignment align = ImageAlignment::Center;
    };

    TemplateValueType type_;
    std::variant<TextData, ImageData> data_;

    explicit TemplateValue(TextData data);
    explicit TemplateValue(ImageData data);
};

// ============================================================================
// TemplateEngine
// ============================================================================

/**
 * @class TemplateEngine
 * @brief Unified dictionary-style template engine
 * @details The one-stop API for template population. Supports both
 *          placeholder (`{{key}}`) and bookmark-based replacement.
 *
 * @par Dictionary Style:
 * @code
 * cdocx::TemplateEngine engine(&doc);
 * engine["name"] = cdocx::TemplateValue::text("John");
 * engine["logo"] = cdocx::TemplateValue::image("logo.png");
 * engine.apply();
 * @endcode
 *
 * @par Programmatic Style:
 * @code
 * engine.set("name", "John")
 *       .set("logo", cdocx::TemplateValue::image("logo.png"))
 *       .with_scope(cdocx::TemplateScope::All)
 *       .apply();
 * @endcode
 *
 * @par Batch Style:
 * @code
 * std::map<std::string, std::string> texts = {{"a", "1"}, {"b", "2"}};
 * engine.set_batch(texts).apply();
 * @endcode
 *
 * @since 0.8.0
 */
class TemplateEngine {
  public:
    // ===================================================================
    // Result
    // ===================================================================

    /**
     * @struct Result
     * @brief Execution statistics
     */
    struct Result {
        int success = 0;  ///< Number of successful replacements
        int failed = 0;   ///< Number of failed replacements
        int skipped = 0;  ///< Number of skipped (empty value) entries

        int total() const { return success + failed + skipped; }
        bool all_succeeded() const { return failed == 0 && skipped == 0; }
    };

    // ===================================================================
    // Setter Proxy (for operator[])
    // ===================================================================

    /**
     * @class Setter
     * @brief Proxy object returned by operator[]
     * @details Enables syntax: engine["key"] = value;
     */
    class Setter {
      public:
        Setter(TemplateEngine* engine, std::string key);

        /** @brief Assign a TemplateValue */
        Setter& operator=(const TemplateValue& value);

        /** @brief Assign a plain string (auto-wrapped as Text) */
        Setter& operator=(const std::string& text);

        /** @brief Assign a C-string (auto-wrapped as Text) */
        Setter& operator=(const char* text);

      private:
        TemplateEngine* engine_;
        std::string key_;
    };

    // ===================================================================
    // Construction
    // ===================================================================

    /**
     * @brief Construct engine bound to a document
     * @param doc Target document (must remain valid during engine lifetime)
     */
    explicit TemplateEngine(Document* doc);

    ~TemplateEngine() = default;

    // Disable copy, enable move
    TemplateEngine(const TemplateEngine&) = delete;
    TemplateEngine& operator=(const TemplateEngine&) = delete;
    TemplateEngine(TemplateEngine&&) = default;
    TemplateEngine& operator=(TemplateEngine&&) = default;

    // ===================================================================
    // Dictionary API
    // ===================================================================

    /**
     * @brief Dictionary-style access
     * @param key Template key (bookmark name or placeholder key without delimiters)
     * @return Setter proxy for assignment
     *
     * @par Usage:
     * @code
     * engine["company"] = cdocx::TemplateValue::text("Acme");
     * engine["date"]    = "2025-04-21";  // auto-wrapped
     * @endcode
     */
    Setter operator[](const std::string& key);

    /**
     * @brief Set a template value
     * @param key Template key
     * @param value TemplateValue (Text or Image)
     * @return Reference to this for chaining
     */
    TemplateEngine& set(const std::string& key, const TemplateValue& value);

    /**
     * @brief Set a text value (convenience overload)
     * @param key Template key
     * @param text Plain text (auto-wrapped as TemplateValue::Text)
     * @return Reference to this for chaining
     */
    TemplateEngine& set(const std::string& key, const std::string& text);

    /**
     * @brief Set a text value (C-string convenience overload)
     * @param key Template key
     * @param text Plain text
     * @return Reference to this for chaining
     */
    TemplateEngine& set(const std::string& key, const char* text);

    // ===================================================================
    // Batch API
    // ===================================================================

    /**
     * @brief Set multiple values from a map
     * @param data Map of key -> TemplateValue
     * @return Reference to this for chaining
     */
    TemplateEngine& set_batch(const std::map<std::string, TemplateValue>& data);

    /**
     * @brief Set multiple text values from a string map
     * @param data Map of key -> text
     * @return Reference to this for chaining
     */
    TemplateEngine& set_batch(const std::map<std::string, std::string>& data);

    // ===================================================================
    // Global Configuration
    // ===================================================================

    /** @brief Set action mode for subsequent apply() calls */
    TemplateEngine& with_action(TemplateAction action);

    /** @brief Set match scope for subsequent apply() calls */
    TemplateEngine& with_scope(TemplateScope scope);

    /** @brief Set target type for subsequent apply() calls */
    TemplateEngine& with_target(TemplateTarget target);

    /** @brief Set format policy for subsequent apply() calls */
    TemplateEngine& with_format_policy(FormatPolicy policy);

    /** @brief Set default format applied when FormatPolicy::Override */
    TemplateEngine& with_default_format(const TemplateFormat& format);

    /** @brief Set placeholder delimiters (default: {{ }}) */
    TemplateEngine& with_delimiters(const std::string& prefix,
                                    const std::string& suffix);

    // ===================================================================
    // Execution
    // ===================================================================

    /**
     * @brief Apply all queued template values
     * @return Result statistics
     * @details Executes replacements in order: first all bookmark targets,
     *          then all placeholder targets. Clears the queue on success.
     */
    Result apply();

    /**
     * @brief Apply a single key
     * @param key The key to apply
     * @return Result statistics (0 or 1 success/fail)
     */
    Result apply(const std::string& key);

    /**
     * @brief Apply only keys matching a predicate
     * @param predicate Function(key) -> bool
     * @return Result statistics
     */
    Result apply_if(const std::function<bool(const std::string&)>& predicate);

    // ===================================================================
    // Query
    // ===================================================================

    /** @brief Check if a key has been set */
    bool has(const std::string& key) const;

    /** @brief Remove a queued key */
    TemplateEngine& remove(const std::string& key);

    /** @brief Clear all queued keys */
    TemplateEngine& clear();

    /** @brief Get number of queued entries */
    size_t size() const;

    /** @brief Get last execution result */
    const Result& last_result() const { return last_result_; }

  private:
    Document* doc_;

    std::map<std::string, TemplateValue> queue_;
    TemplateAction default_action_ = TemplateAction::Replace;
    TemplateScope default_scope_ = TemplateScope::All;
    TemplateTarget default_target_ = TemplateTarget::Auto;
    FormatPolicy default_format_policy_ = FormatPolicy::Preserve;
    TemplateFormat default_format_;
    std::string delimiter_prefix_ = "{{";
    std::string delimiter_suffix_ = "}}";

    Result last_result_;

    // Internal execution
    Result apply_bookmark(const std::string& key, const TemplateValue& value);
    Result apply_bookmark(Bookmark& bookmark, const TemplateValue& value);
    Result apply_placeholder(const std::string& key, const TemplateValue& value);

    // Helpers (string-based — look up bookmark by name)
    bool apply_text_to_bookmark(const std::string& name,
                                const std::string& text,
                                const TemplateFormat& format,
                                FormatPolicy policy);
    bool apply_image_to_bookmark(const std::string& name,
                                 const TemplateValue& value);

    // Helpers (Bookmark& — use pre-resolved bookmark to avoid sync issues)
    bool apply_text_to_bookmark(Bookmark& bookmark,
                                const std::string& text,
                                const TemplateFormat& format,
                                FormatPolicy policy);
    bool apply_image_to_bookmark(Bookmark& bookmark,
                                 const TemplateValue& value);

    bool apply_text_to_placeholder(const std::string& key,
                                   const std::string& text);
    bool apply_image_to_placeholder(const std::string& key,
                                    const TemplateValue& value);
};

}  // namespace cdocx
