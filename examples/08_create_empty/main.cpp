/**
 * @file main.cpp
 * @brief Example 08: Create Empty Document
 * @version 0.2.0
 * 
 * @defgroup example_08_create_empty Example 08: Create Empty Document
 * @brief Demonstrates creating a new empty DOCX document from scratch
 * @{
 */

/**
 * Example 08: Create Empty Document
 * 
 * This example demonstrates how to:
 * 1. Create a new empty DOCX document programmatically
 * 2. Add content to the empty document
 * 3. Save the document
 * 
 * Output: 08_created_document.docx
 */

#include <cdocx.h>
#include <iostream>

int main() {
    std::cout << "Example 08: Create Empty Document" << std::endl;
    std::cout << "==================================" << std::endl;
    
    // Create a new empty document
    cdocx::Document doc("08_created_document.docx");
    
    std::cout << "Creating empty document..." << std::endl;
    
    if (!doc.create_empty("08_created_document.docx")) {
        std::cerr << "Failed to create empty document!" << std::endl;
        return 1;
    }
    
    std::cout << "Empty document created successfully." << std::endl;
    std::cout << "Adding content..." << std::endl;
    
    // Add a title paragraph
    cdocx::Paragraph title = doc.paragraphs().insert_paragraph_after("");
    title.add_run("New Document Created from Scratch", 
                  static_cast<cdocx::formatting_flag>(cdocx::bold | cdocx::underline));
    
    // Add some content paragraphs
    cdocx::Paragraph p1 = doc.paragraphs().insert_paragraph_after(
        "This document was created programmatically using CDocx. "
    );
    p1.add_run("No template file was needed!", cdocx::italic);
    
    cdocx::Paragraph p2 = doc.paragraphs().insert_paragraph_after(
        "\nThe create_empty() method creates a minimal valid DOCX file with all required XML parts:"
    );
    
    // Add a list of created parts
    cdocx::Paragraph p3 = doc.paragraphs().insert_paragraph_after("  • Content types definition");
    cdocx::Paragraph p4 = doc.paragraphs().insert_paragraph_after("  • Package and document relationships");
    cdocx::Paragraph p5 = doc.paragraphs().insert_paragraph_after("  • Main document content");
    cdocx::Paragraph p6 = doc.paragraphs().insert_paragraph_after("  • Styles, settings, and font table");
    cdocx::Paragraph p7 = doc.paragraphs().insert_paragraph_after("  • Theme");
    cdocx::Paragraph p8 = doc.paragraphs().insert_paragraph_after("  • Core and extended properties");
    
    // Add a closing paragraph
    cdocx::Paragraph closing = doc.paragraphs().insert_paragraph_after(
        "\nThis demonstrates the power of programmatic document generation!"
    );
    
    // Save the document
    doc.save();
    
    std::cout << "Document saved successfully: 08_created_document.docx" << std::endl;
    
    return 0;
}

/** @} */
