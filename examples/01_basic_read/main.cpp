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
#include <filesystem>

// Forward declaration
bool create_sample_document(const std::string& doc_path);

int main() {
    std::string doc_path = "data/01_basic_read_sample.docx";
    
    // Create data directory if needed
    std::filesystem::create_directories("data");
    
    // Create sample document if it doesn't exist
    if (!std::filesystem::exists(doc_path)) {
        std::cout << "Creating sample document..." << std::endl;
        if (!create_sample_document(doc_path)) {
            std::cerr << "Failed to create sample document" << std::endl;
            return 1;
        }
    }
    
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

// Create the sample document used by this example
bool create_sample_document(const std::string& doc_path) {
    // Use a simple template - create an empty doc
    cdocx::Document doc(doc_path);
    
    // We need a base template. Try to find one or create from empty
    // First try to create from empty
    if (!doc.create_empty()) {
        std::cerr << "Failed to create empty document" << std::endl;
        return false;
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
    
    // Paragraph 6 - Simple test paragraph
    auto p6 = doc.paragraphs().insert_paragraph_after("This is a test");
    
    // Paragraph 7 - End
    auto p7 = doc.paragraphs().insert_paragraph_after("okay?");
    
    doc.save(doc_path);
    std::cout << "  Created: " << doc_path << std::endl;
    return true;
}
