/**
 * @file main.cpp
 * @brief Example: DocumentBuilder operations
 * @version 0.8.0
 */

#include <cdocx.h>
#include <cdocx/advanced.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // ------------------------------------------------------------------------
    // Example 1: Basic text with hyperlink
    // ------------------------------------------------------------------------
    cdocx::Document doc("document_builder_example.docx");
    if (!doc.create_empty()) {
        std::cerr << "Failed to create document" << std::endl;
        return 1;
    }

    cdocx::DocumentBuilder builder(&doc);
    builder.writeln("DocumentBuilder Demo");
    builder.clear_formatting();
    builder.write("Visit ");
    builder.insert_hyperlink("CDocx Project", "https://github.com/lonlng/cdocx");
    builder.writeln(" for more information.");

    // ------------------------------------------------------------------------
    // Example 2: Formatted hyperlink
    // ------------------------------------------------------------------------
    builder.set_bold(true);
    builder.set_color("0070C0");
    builder.insert_hyperlink("Bold Blue Link", "https://example.com");
    builder.clear_formatting();
    builder.writeln();

    // ------------------------------------------------------------------------
    // Example 3: Table
    // ------------------------------------------------------------------------
    builder.writeln("Sample Table:");
    builder.start_table();
    for (int row = 0; row < 3; ++row) {
        builder.insert_row();
        for (int col = 0; col < 3; ++col) {
            builder.insert_cell();
            builder.write("R" + std::to_string(row + 1) + "C" + std::to_string(col + 1));
        }
        builder.end_row();
    }
    builder.end_table();
    builder.writeln();

    // ------------------------------------------------------------------------
    // Example 4: Image insertion
    // ------------------------------------------------------------------------
    std::string image_path = "data/07_sample_image1.jpg";
    if (fs::exists(image_path)) {
        builder.write("Image: ");
        if (builder.insert_image(image_path, 120.0, 90.0)) {
            builder.writeln(" (inserted successfully)");
        } else {
            builder.writeln(" (failed to insert)");
        }
    } else {
        builder.writeln("Image file not found, skipping image insertion.");
    }

    // ------------------------------------------------------------------------
    // Save
    // ------------------------------------------------------------------------
    doc.save();
    std::cout << "Document saved successfully." << std::endl;
    return 0;
}
