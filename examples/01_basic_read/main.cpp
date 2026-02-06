/**
 * Example 01: Basic Document Reading
 * 
 * This example demonstrates how to:
 * 1. Open an existing DOCX file
 * 2. Iterate through paragraphs and runs
 * 3. Extract text content from the document
 */

#include <cdocx.h>
#include <iostream>
#include "../example_utils.h"

int main() {
    // Get the path to the test document
    std::string doc_path = example_utils::get_resource_path("01_basic_read_sample.docx");
    
    std::cout << "Opening: " << doc_path << std::endl;
    
    // Open an existing document
    cdocx::Document doc(doc_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document: " << doc_path << std::endl;
        std::cerr << "Please ensure the document exists in the example directory." << std::endl;
        return 1;
    }
    
    std::cout << "=== Document Content ===" << std::endl;
    
    // Iterate through all paragraphs
    int para_count = 0;
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        para_count++;
        std::cout << "\n[Paragraph " << para_count << "]" << std::endl;
        
        // Iterate through all runs in the paragraph
        int run_count = 0;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            run_count++;
            std::cout << "  Run " << run_count << ": " << r.get_text() << std::endl;
        }
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Total paragraphs: " << para_count << std::endl;
    
    return 0;
}
