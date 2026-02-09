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
#include <filesystem>

// Forward declaration
bool create_sample_documents(const std::string& main_doc_path,
                             const std::string& template_path);

int main() {
    std::cout << "=== Document Insertion Example ===" << std::endl;
    
    std::string main_doc_path = "data/05_insert_main_sample.docx";
    std::string template_path = "data/05_insert_template_sample.docx";
    std::string output_path = "output_05_document_insert.docx";
    std::string temp_path = "temp_processed.docx";
    
    // Create data directory if needed
    std::filesystem::create_directories("data");
    
    // Create sample documents if they don't exist
    if (!std::filesystem::exists(main_doc_path) || !std::filesystem::exists(template_path)) {
        std::cout << "Creating sample documents..." << std::endl;
        if (!create_sample_documents(main_doc_path, template_path)) {
            std::cerr << "Failed to create sample documents" << std::endl;
            return 1;
        }
    }
    
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

// Create the sample documents used by this example
bool create_sample_documents(const std::string& main_doc_path,
                             const std::string& template_path) {
    // Create main document
    {
        cdocx::Document doc(main_doc_path);
        
        if (!doc.create_empty()) {
            std::cerr << "Failed to create main document" << std::endl;
            return false;
        }
        
        auto p1 = doc.paragraphs().insert_paragraph_after("Main Document");
        auto p2 = doc.paragraphs().insert_paragraph_after("This is the main document that will receive content from another document.");
        auto p3 = doc.paragraphs().insert_paragraph_after("");
        auto p4 = doc.paragraphs().insert_paragraph_after("--- Inserted content will appear below ---");
        auto p5 = doc.paragraphs().insert_paragraph_after("");
        
        doc.save(main_doc_path);
        std::cout << "  Created: " << main_doc_path << std::endl;
    }
    
    // Create template document
    {
        cdocx::Document doc(template_path);
        
        if (!doc.create_empty()) {
            std::cerr << "Failed to create template document" << std::endl;
            return false;
        }
        
        auto p1 = doc.paragraphs().insert_paragraph_after("Template Section");
        auto p2 = doc.paragraphs().insert_paragraph_after("Name: {{name}}");
        auto p3 = doc.paragraphs().insert_paragraph_after("Title: {{title}}");
        auto p4 = doc.paragraphs().insert_paragraph_after("Department: {{department}}");
        
        doc.save(template_path);
        std::cout << "  Created: " << template_path << std::endl;
    }
    
    return true;
}
