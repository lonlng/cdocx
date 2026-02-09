/**
 * Example 04: Advanced Template Features
 * 
 * This example demonstrates how to:
 * 1. Use custom placeholder delimiters
 * 2. Set text and image placeholders
 * 3. Process complex templates
 * 4. Work with template statistics
 */

#include <cdocx.h>
#include <iostream>
#include <filesystem>
#include <fstream>

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

// Forward declaration
bool create_sample_template(const std::string& template_path, 
                            const std::string& image1_path,
                            const std::string& image2_path);

int main() {
    std::cout << "=== Advanced Template Example ===" << std::endl;
    
    std::string template_path = "data/04_template_advanced_sample.docx";
    std::string image1_path = "data/04_test_image1.jpg";
    std::string image2_path = "data/04_test_image2.png";
    std::string output_path = "output_04_template_advanced.docx";
    
    // Create data directory if needed
    std::filesystem::create_directories("data");
    
    // Create sample template and images if they don't exist
    if (!std::filesystem::exists(template_path)) {
        std::cout << "Creating sample template and images..." << std::endl;
        if (!create_sample_template(template_path, image1_path, image2_path)) {
            std::cerr << "Failed to create sample template" << std::endl;
            return 1;
        }
    }
    
    std::cout << "Opening template: " << template_path << std::endl;
    
    // Open the template document
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open template document: " << template_path << std::endl;
        return 1;
    }
    
    // Create template processor with custom delimiters (default is {{ }})
    cdocx::Template tmpl(&doc);
    
    // Set text placeholders
    tmpl.set("company_name", "Tech Corp International");
    tmpl.set("report_title", "Quarterly Performance Report");
    tmpl.set("employee_name", "Jane Doe");
    tmpl.set("department", "Research & Development");
    tmpl.set("quarter", "Q4 2025");
    tmpl.set("total_sales", "$2,500,000");
    tmpl.set("performance_rating", "Excellent");
    tmpl.set("date", "February 6, 2026");
    
    // Set image placeholders (format: {{image:key}})
    std::cout << "Using images:" << std::endl;
    std::cout << "  Logo: " << image1_path << std::endl;
    std::cout << "  Signature: " << image2_path << std::endl;
    
    tmpl.set_image("logo", image1_path);
    tmpl.set_image("signature", image2_path);
    
    // Replace all placeholders
    std::cout << "Replacing placeholders..." << std::endl;
    tmpl.replace_all();
    std::cout << "Placeholder count: " << tmpl.size() << std::endl;
    
    // Save the result
    doc.save(output_path);
    std::cout << "Output saved to: " << output_path << std::endl;
    
    std::cout << "\n=== Success! ===" << std::endl;
    return 0;
}

// Create the sample template and images used by this example
bool create_sample_template(const std::string& template_path,
                            const std::string& image1_path,
                            const std::string& image2_path) {
    // Create sample images
    save_binary_file(image1_path, MINIMAL_JPEG, sizeof(MINIMAL_JPEG));
    save_binary_file(image2_path, MINIMAL_PNG, sizeof(MINIMAL_PNG));
    std::cout << "  Created: " << image1_path << std::endl;
    std::cout << "  Created: " << image2_path << std::endl;
    
    cdocx::Document doc(template_path);
    
    if (!doc.create_empty()) {
        std::cerr << "Failed to create empty document" << std::endl;
        return false;
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
    doc.add_media_with_rel(image1_path);
    doc.add_media_with_rel(image2_path);
    
    doc.save(template_path);
    std::cout << "  Created: " << template_path << std::endl;
    return true;
}

/**
 * Expected template format in template_sample.docx:
 * 
 * {{company_name}}
 * {{report_title}}
 * 
 * Employee: {{employee_name}}
 * Department: {{department}}
 * Quarter: {{quarter}}
 * 
 * Performance Summary:
 * Total Sales: {{total_sales}}
 * Rating: {{performance_rating}}
 * 
 * Date: {{date}}
 */
