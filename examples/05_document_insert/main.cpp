/**
 * Example 05: Document Insertion
 * 
 * This example demonstrates how to:
 * 1. Process a template document
 * 2. Insert processed content into another document
 * 3. Use different insertion methods
 */

#include <cdocx.h>
#include <iostream>
#include "../example_utils.h"

int main() {
    std::cout << "=== Document Insertion Example ===" << std::endl;
    
    // Get paths to resource files
    std::string template_path = example_utils::get_resource_path("05_insert_template_sample.docx");
    std::string main_doc_path = example_utils::get_resource_path("05_insert_main_sample.docx");
    std::string output_path = example_utils::get_output_path("output_05_document_insert.docx");
    std::string temp_path = example_utils::get_output_path("temp_processed.docx");
    
    // Step 1: Process template
    std::cout << "\nStep 1: Processing template..." << std::endl;
    std::cout << "  Template: " << template_path << std::endl;
    
    cdocx::Document template_doc(template_path);
    template_doc.open();
    
    if (!template_doc.is_open()) {
        std::cerr << "Error: Could not open template document" << std::endl;
        return 1;
    }
    
    cdocx::Template tmpl(&template_doc);
    tmpl.set("name", "Alice Johnson");
    tmpl.set("title", "Senior Engineer");
    tmpl.set("department", "Research & Development");
    tmpl.replace_all();
    
    // Save processed template
    template_doc.save(temp_path);
    std::cout << "Template processed." << std::endl;
    
    // Step 2: Open main document
    std::cout << "\nStep 2: Opening main document..." << std::endl;
    std::cout << "  Main doc: " << main_doc_path << std::endl;
    
    cdocx::Document main_doc(main_doc_path);
    main_doc.open();
    
    if (!main_doc.is_open()) {
        std::cerr << "Error: Could not open main document" << std::endl;
        return 1;
    }
    
    // Step 3: Insert content
    std::cout << "\nStep 3: Inserting processed content..." << std::endl;
    cdocx::Document processed_doc(temp_path);
    processed_doc.open();
    
    cdocx::DocumentInserter inserter(&main_doc);
    
    // Insert at the end of the document
    inserter.insert_document(&processed_doc);
    
    // Save final result
    main_doc.save(output_path);
    std::cout << "Final document saved: " << output_path << std::endl;
    
    // Cleanup temporary file
    std::remove(temp_path.c_str());
    
    std::cout << "\n=== Success! ===" << std::endl;
    return 0;
}
