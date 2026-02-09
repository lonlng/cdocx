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
#include <filesystem>

// Forward declaration
bool create_sample_template(const std::string& template_path);

int main() {
    std::string template_path = "data/03_template_basic_sample.docx";
    std::string output_path = "output_03_template_basic.docx";
    
    // Create data directory if needed
    std::filesystem::create_directories("data");
    
    // Create sample template if it doesn't exist
    if (!std::filesystem::exists(template_path)) {
        std::cout << "Creating sample template..." << std::endl;
        if (!create_sample_template(template_path)) {
            std::cerr << "Failed to create sample template" << std::endl;
            return 1;
        }
    }
    
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

// Create the sample template used by this example
bool create_sample_template(const std::string& template_path) {
    cdocx::Document doc(template_path);
    
    if (!doc.create_empty()) {
        std::cerr << "Failed to create empty document" << std::endl;
        return false;
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
    
    doc.save(template_path);
    std::cout << "  Created: " << template_path << std::endl;
    return true;
}
