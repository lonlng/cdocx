/**
 * @file watermark.h
 * @brief Document watermark support for CDocx
 * @details Provides elegant text and image watermark functionality.
 *          Watermarks are rendered as shapes in the document header.
 *
 * @since 0.8.0
 */

#pragma once

#include <cdocx/document.h>

#include <string>

namespace cdocx {

// ============================================================================
// Watermark Layout
// ============================================================================

enum class WatermarkLayout : std::uint8_t {
    Horizontal,
    Diagonal
};

// ============================================================================
// Text Watermark Options
// ============================================================================

struct TextWatermarkOptions {
    std::string font_family = "Calibri";
    std::string color = "C0C0C0";  ///< Silver, hex RGB
    float font_size = 0;           ///< 0 = auto
    bool semi_transparent = true;
    WatermarkLayout layout = WatermarkLayout::Diagonal;
};

// ============================================================================
// Image Watermark Options
// ============================================================================

struct ImageWatermarkOptions {
    double scale = 0;  ///< 0 = auto, otherwise percentage
    bool washout = true;
};

// ============================================================================
// Watermark Class
// ============================================================================

class Watermark {
  public:
    explicit Watermark(Document* doc);

    /// Set text watermark with default options
    void set_text(const std::string& text);

    /// Set text watermark with custom options
    void set_text(const std::string& text, const TextWatermarkOptions& options);

    /// Set image watermark from file
    void set_image(const std::string& image_path);

    /// Set image watermark from file with custom options
    void set_image(const std::string& image_path, const ImageWatermarkOptions& options);

    /// Remove all watermarks from the document
    void remove();

    /// Check if document has a watermark
    bool has_watermark() const;

  private:
    Document* document_;

    void ensure_header_for_watermark();
    void insert_text_watermark_into_header(const std::string& text,
                                           const TextWatermarkOptions& options);
    void insert_image_watermark_into_header(const std::string& image_path,
                                            const ImageWatermarkOptions& options);
    void clear_watermark_from_header();
};

}  // namespace cdocx
