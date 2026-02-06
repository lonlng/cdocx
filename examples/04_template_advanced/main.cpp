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
#include "../example_utils.h"

int main() {
    std::cout << "=== Advanced Template Example ===" << std::endl;
    
    // Get paths to resource files
    std::string template_path = example_utils::get_resource_path("04_template_advanced_sample.docx");
    std::string image1_path = example_utils::get_resource_path("04_test_image1.jpg");
    std::string image2_path = example_utils::get_resource_path("04_test_image2.png");
    std::string output_path = example_utils::get_output_path("output_04_template_advanced.docx");
    
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
    // Note: The image files should exist in the example directory
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
