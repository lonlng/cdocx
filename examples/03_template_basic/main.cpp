/**
 * Example 03: Basic Template Usage
 * 
 * This example demonstrates how to:
 * 1. Open a template document with placeholders
 * 2. Replace placeholders with actual values
 * 3. Save the result
 * 
 * Template format: {{placeholder_name}}
 */

#include <cdocx.h>
#include <iostream>
#include "../example_utils.h"

int main() {
    // Get the path to the template document
    std::string template_path = example_utils::get_resource_path("03_template_basic_sample.docx");
    std::string output_path = example_utils::get_output_path("output_03_template_basic.docx");
    
    std::cout << "Opening template: " << template_path << std::endl;
    
    // Open the template document
    cdocx::Document doc(template_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open template: " << template_path << std::endl;
        std::cerr << "Please ensure the template exists in the example directory." << std::endl;
        return 1;
    }
    
    // Create template processor
    cdocx::Template tmpl(&doc);
    
    // Set placeholder values
    tmpl.set("company_name", "ACME Corporation");
    tmpl.set("report_title", "Annual Performance Report");
    tmpl.set("employee_name", "John Smith");
    tmpl.set("department", "Engineering");
    tmpl.set("date", "February 6, 2026");
    
    // Replace all placeholders
    tmpl.replace_all();
    
    // Save the result
    doc.save(output_path);
    
    std::cout << "Template processed successfully!" << std::endl;
    std::cout << "Placeholder count: " << tmpl.size() << std::endl;
    std::cout << "Output saved to: " << output_path << std::endl;
    
    return 0;
}
