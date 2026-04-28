/**
 * @file main.cpp
 * @brief Example: Watermark API
 * @version 0.8.0
 *
 * Demonstrates how to:
 * 1. Add a diagonal text watermark
 * 2. Add a horizontal text watermark with custom options
 * 3. Add an image watermark
 * 4. Check if a watermark exists
 * 5. Remove a watermark
 */

#include <cdocx.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::cout << "=== CDocx Watermark Example ===" << std::endl;

    // ------------------------------------------------------------------------
    // Example 1: Text watermark with default options (diagonal)
    // ------------------------------------------------------------------------
    std::cout << "\n1. Creating document with diagonal text watermark..." << std::endl;

    {
        cdocx::Document doc;
        doc.create_empty("watermark_text_default.docx");

        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("This document has a default diagonal text watermark.");

        cdocx::Watermark watermark(&doc);
        watermark.set_text("CONFIDENTIAL");

        std::cout << "   Has watermark: " << (watermark.has_watermark() ? "yes" : "no") << std::endl;

        doc.save();
        std::cout << "   Saved: watermark_text_default.docx" << std::endl;
    }

    // ------------------------------------------------------------------------
    // Example 2: Custom text watermark (horizontal, colored)
    // ------------------------------------------------------------------------
    std::cout << "\n2. Creating document with custom horizontal watermark..." << std::endl;

    {
        cdocx::Document doc;
        doc.create_empty("watermark_text_custom.docx");

        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("This document has a custom horizontal watermark.");

        cdocx::TextWatermarkOptions options;
        options.font_family = "Arial";
        options.color = "FF0000";           // Red
        options.font_size = 72;             // Large text
        options.semi_transparent = false;   // Opaque
        options.layout = cdocx::WatermarkLayout::Horizontal;

        cdocx::Watermark watermark(&doc);
        watermark.set_text("DRAFT", options);

        doc.save();
        std::cout << "   Saved: watermark_text_custom.docx" << std::endl;
    }

    // ------------------------------------------------------------------------
    // Example 3: Image watermark
    // ------------------------------------------------------------------------
    std::cout << "\n3. Creating document with image watermark..." << std::endl;

    {
        cdocx::Document doc;
        doc.create_empty("watermark_image.docx");

        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("This document has an image watermark.");

        cdocx::Watermark watermark(&doc);

        // Use a sample image if available; otherwise fall back to text
        std::string image_path = "data/sample_logo.png";
        if (fs::exists(image_path)) {
            cdocx::ImageWatermarkOptions img_options;
            img_options.scale = 50;     // 50% of page width
            img_options.washout = true; // Faded look

            watermark.set_image(image_path, img_options);
            std::cout << "   Image watermark applied." << std::endl;
        } else {
            watermark.set_text("LOGO");
            std::cout << "   Image not found; applied text fallback." << std::endl;
        }

        doc.save();
        std::cout << "   Saved: watermark_image.docx" << std::endl;
    }

    // ------------------------------------------------------------------------
    // Example 4: Remove watermark
    // ------------------------------------------------------------------------
    std::cout << "\n4. Removing watermark from document..." << std::endl;

    {
        cdocx::Document doc;
        doc.create_empty("watermark_removed.docx");

        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("This document had a watermark, then it was removed.");

        cdocx::Watermark watermark(&doc);
        watermark.set_text("TEMPORARY");
        std::cout << "   Added temporary watermark." << std::endl;

        watermark.remove();
        std::cout << "   Has watermark after removal: "
                  << (watermark.has_watermark() ? "yes" : "no") << std::endl;

        doc.save();
        std::cout << "   Saved: watermark_removed.docx" << std::endl;
    }

    std::cout << "\n=== Example Complete ===" << std::endl;
    return 0;
}
