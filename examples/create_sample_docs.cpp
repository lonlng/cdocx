/**
 * @file create_sample_docs.cpp
 * @brief Sample Document Generator
 * @version 0.2.0
 * 
 * This program creates dedicated Word documents for each example.
 * Run this first to generate all sample documents before running examples.
 * 
 * Each example gets its own data/ folder with sample documents.
 */

#include <cdocx.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "example_utils.h"

// Minimal 1x1 pixel JPEG image data (for embedding)
const unsigned char MINIMAL_JPEG[] = {
    0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
    0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
};

// Minimal PNG image (1x1 pixel transparent)
const unsigned char MINIMAL_PNG[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4,
    0x89, 0x00, 0x00, 0x00, 0x0A, 0x49, 0x44, 0x41,
    0x54, 0x78, 0x9C, 0x63, 0x60, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC, 0x33, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE,
    0x42, 0x60, 0x82
};

void save_binary_file(const std::string& path, const unsigned char* data, size_t size) {
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data), size);
}

// ============================================================================
// Example 01: Basic Read Document
// ============================================================================
void create_basic_read_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 01_basic_read/data/01_basic_read_sample.docx..." << std::endl;
    
    std::string data_dir = base_dir + "/01_basic_read/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/01_basic_read_sample.docx";
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    // Title
    auto p1 = doc.paragraphs().insert_paragraph_after("Basic Read Example Document");
    
    // Paragraph 2 - Multiple runs with different formatting
    auto p2 = doc.paragraphs().insert_paragraph_after("This document contains ");
    p2.add_run("bold text, ", cdocx::bold);
    p2.add_run("italic text, ", cdocx::italic);
    p2.add_run("and ", cdocx::none);
    p2.add_run("underlined text", cdocx::underline);
    p2.add_run(". It demonstrates text formatting.", cdocx::none);
    
    // Paragraph 3 - Mixed content
    auto p3 = doc.paragraphs().insert_paragraph_after("Second paragraph with ");
    p3.add_run("superscript", cdocx::superscript);
    p3.add_run(" and ");
    p3.add_run("subscript", cdocx::subscript);
    p3.add_run(" formatting.");
    
    // Paragraph 4 - More variety
    auto p4 = doc.paragraphs().insert_paragraph_after("Additional features include ");
    p4.add_run("strikethrough", cdocx::strikethrough);
    p4.add_run(", ");
    p4.add_run("small caps", cdocx::smallcaps);
    p4.add_run(", and ");
    p4.add_run("shadow effects", cdocx::shadow);
    p4.add_run(".");
    
    // Paragraph 5 - Combined formatting
    auto p5 = doc.paragraphs().insert_paragraph_after("You can also combine multiple formats: ");
    p5.add_run("bold italic", static_cast<cdocx::formatting_flag>(cdocx::bold | cdocx::italic));
    p5.add_run(", ");
    p5.add_run("bold underline", static_cast<cdocx::formatting_flag>(cdocx::bold | cdocx::underline));
    p5.add_run(", and ");
    p5.add_run("italic underline", static_cast<cdocx::formatting_flag>(cdocx::italic | cdocx::underline));
    p5.add_run(".");
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
}

// ============================================================================
// Example 03: Basic Template
// ============================================================================
void create_template_basic_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 03_template_basic/data/03_template_basic_sample.docx..." << std::endl;
    
    std::string data_dir = base_dir + "/03_template_basic/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/03_template_basic_sample.docx";
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    // Title
    auto p1 = doc.paragraphs().insert_paragraph_after("{{report_title}}");
    
    // Company info
    auto p2 = doc.paragraphs().insert_paragraph_after("Company: {{company_name}}");
    
    // Employee info
    auto p3 = doc.paragraphs().insert_paragraph_after("Employee: {{employee_name}}");
    auto p4 = doc.paragraphs().insert_paragraph_after("Department: {{department}}");
    
    // Date
    auto p5 = doc.paragraphs().insert_paragraph_after("Date: {{date}}");
    
    // Content placeholder
    auto p6 = doc.paragraphs().insert_paragraph_after("");
    auto p7 = doc.paragraphs().insert_paragraph_after("{{content}}");
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
}

// ============================================================================
// Example 04: Advanced Template
// ============================================================================
void create_template_advanced_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 04_template_advanced/data/..." << std::endl;
    
    std::string data_dir = base_dir + "/04_template_advanced/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/04_template_advanced_sample.docx";
    std::string jpeg_path = data_dir + "/04_test_image1.jpg";
    std::string png_path = data_dir + "/04_test_image2.png";
    
    // Create sample images
    save_binary_file(jpeg_path, MINIMAL_JPEG, sizeof(MINIMAL_JPEG));
    save_binary_file(png_path, MINIMAL_PNG, sizeof(MINIMAL_PNG));
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    // Header
    auto p1 = doc.paragraphs().insert_paragraph_after("{{company_name}}");
    auto p2 = doc.paragraphs().insert_paragraph_after("{{report_title}}");
    
    // Employee info section
    auto p3 = doc.paragraphs().insert_paragraph_after("");
    auto p4 = doc.paragraphs().insert_paragraph_after("Employee Information:");
    auto p5 = doc.paragraphs().insert_paragraph_after("  Name: {{employee_name}}");
    auto p6 = doc.paragraphs().insert_paragraph_after("  Department: {{department}}");
    auto p7 = doc.paragraphs().insert_paragraph_after("  Quarter: {{quarter}}");
    
    // Performance section
    auto p8 = doc.paragraphs().insert_paragraph_after("");
    auto p9 = doc.paragraphs().insert_paragraph_after("Performance Summary:");
    auto p10 = doc.paragraphs().insert_paragraph_after("  Total Sales: {{total_sales}}");
    auto p11 = doc.paragraphs().insert_paragraph_after("  Rating: {{performance_rating}}");
    
    // Notes section
    auto p12 = doc.paragraphs().insert_paragraph_after("");
    auto p13 = doc.paragraphs().insert_paragraph_after("{{notes}}");
    
    // Date
    auto p14 = doc.paragraphs().insert_paragraph_after("");
    auto p15 = doc.paragraphs().insert_paragraph_after("Report Date: {{date}}");
    
    // Add images
    doc.add_media_with_rel(jpeg_path);
    doc.add_media_with_rel(png_path);
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
    std::cout << "  Created: " << jpeg_path << std::endl;
    std::cout << "  Created: " << png_path << std::endl;
}

// ============================================================================
// Example 05: Document Insert Main Document
// ============================================================================
void create_insert_main_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 05_document_insert/data/05_insert_main_sample.docx..." << std::endl;
    
    std::string data_dir = base_dir + "/05_document_insert/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/05_insert_main_sample.docx";
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    auto p1 = doc.paragraphs().insert_paragraph_after("Main Document");
    auto p2 = doc.paragraphs().insert_paragraph_after("This is the main document that will receive content from another document.");
    auto p3 = doc.paragraphs().insert_paragraph_after("");
    auto p4 = doc.paragraphs().insert_paragraph_after("--- Inserted content will appear below ---");
    auto p5 = doc.paragraphs().insert_paragraph_after("");
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
}

// ============================================================================
// Example 05: Document Insert Template
// ============================================================================
void create_insert_template_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 05_document_insert/data/05_insert_template_sample.docx..." << std::endl;
    
    std::string data_dir = base_dir + "/05_document_insert/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/05_insert_template_sample.docx";
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    auto p1 = doc.paragraphs().insert_paragraph_after("Template Section");
    auto p2 = doc.paragraphs().insert_paragraph_after("Name: {{name}}");
    auto p3 = doc.paragraphs().insert_paragraph_after("Title: {{title}}");
    auto p4 = doc.paragraphs().insert_paragraph_after("Department: {{department}}");
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
}

// ============================================================================
// Example 06: XML Parts Analysis
// ============================================================================
void create_xml_parts_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 06_xml_parts/data/06_xml_parts_sample.docx..." << std::endl;
    
    std::string data_dir = base_dir + "/06_xml_parts/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/06_xml_parts_sample.docx";
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    auto p1 = doc.paragraphs().insert_paragraph_after("XML Parts Analysis Document");
    auto p2 = doc.paragraphs().insert_paragraph_after("This document is used to demonstrate the XML Parts API.");
    auto p3 = doc.paragraphs().insert_paragraph_after("It contains multiple paragraphs and runs for analysis.");
    auto p4 = doc.paragraphs().insert_paragraph_after("");
    auto p5 = doc.paragraphs().insert_paragraph_after("Features demonstrated:");
    auto p6 = doc.paragraphs().insert_paragraph_after("  - Core properties access");
    auto p7 = doc.paragraphs().insert_paragraph_after("  - Content types analysis");
    auto p8 = doc.paragraphs().insert_paragraph_after("  - Document part enumeration");
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
}

// ============================================================================
// Example 07: Media Management
// ============================================================================
void create_media_management_doc(const std::string& template_path, const std::string& base_dir) {
    std::cout << "Creating 07_media_management/data/..." << std::endl;
    
    std::string data_dir = base_dir + "/07_media_management/data";
    std::filesystem::create_directories(data_dir);
    std::string output_path = data_dir + "/07_media_management_sample.docx";
    std::string jpeg_path = data_dir + "/07_sample_image1.jpg";
    std::string png_path = data_dir + "/07_sample_image2.png";
    
    // Create sample images
    save_binary_file(jpeg_path, MINIMAL_JPEG, sizeof(MINIMAL_JPEG));
    save_binary_file(png_path, MINIMAL_PNG, sizeof(MINIMAL_PNG));
    
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "  Failed to open template" << std::endl;
        return;
    }
    
    auto p1 = doc.paragraphs().insert_paragraph_after("Media Management Sample Document");
    auto p2 = doc.paragraphs().insert_paragraph_after("This document contains embedded images for media management demonstration.");
    auto p3 = doc.paragraphs().insert_paragraph_after("");
    auto p4 = doc.paragraphs().insert_paragraph_after("Images in this document:");
    auto p5 = doc.paragraphs().insert_paragraph_after("  - sample_image1.jpg (JPEG)");
    auto p6 = doc.paragraphs().insert_paragraph_after("  - sample_image2.png (PNG)");
    
    // Add images
    doc.add_media_with_rel(jpeg_path);
    doc.add_media_with_rel(png_path);
    
    doc.save(output_path);
    std::cout << "  Created: " << output_path << std::endl;
    std::cout << "  Created: " << jpeg_path << std::endl;
    std::cout << "  Created: " << png_path << std::endl;
}

// ============================================================================
// Main
// ============================================================================
int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "CDocx Sample Document Generator" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    // Find template file
    std::string template_path;
    std::string base_dir;
    
    // Check if template path provided as argument
    if (argc > 1) {
        template_path = argv[1];
    } else {
        // Try to find template in common locations
        std::vector<std::string> search_paths = {
            "../../examples/data/my_test.docx",      // From build dir
            "../examples/data/my_test.docx",         // From build/examples dir
            "examples/data/my_test.docx",            // From project root
            "data/my_test.docx",                     // Local data dir
            "my_test.docx"                           // Current dir
        };
        
        for (const auto& path : search_paths) {
            if (std::filesystem::exists(path)) {
                template_path = path;
                break;
            }
        }
    }
    
    if (template_path.empty()) {
        std::cerr << "Error: Could not find template file (my_test.docx)" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <path-to-my_test.docx> [base-dir]" << std::endl;
        return 1;
    }
    
    // Determine base directory (parent of examples)
    if (argc > 2) {
        base_dir = argv[2];
    } else {
        // Default: use examples directory relative to executable
        base_dir = example_utils::get_executable_dir();
        // Try to find examples directory
        if (std::filesystem::exists(base_dir + "/../examples")) {
            base_dir = base_dir + "/../examples";
        } else if (std::filesystem::exists(base_dir + "/examples")) {
            base_dir = base_dir + "/examples";
        }
    }
    
    std::cout << "Using template: " << template_path << std::endl;
    std::cout << "Base directory: " << base_dir << std::endl;
    std::cout << std::endl;
    
    try {
        create_basic_read_doc(template_path, base_dir);
        create_template_basic_doc(template_path, base_dir);
        create_template_advanced_doc(template_path, base_dir);
        create_insert_main_doc(template_path, base_dir);
        create_insert_template_doc(template_path, base_dir);
        create_xml_parts_doc(template_path, base_dir);
        create_media_management_doc(template_path, base_dir);
        
        std::cout << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "All sample documents created successfully!" << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
