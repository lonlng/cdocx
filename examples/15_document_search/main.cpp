/**
 * @file main.cpp
 * @brief Example: Document search and replace operations
 * @version 0.7.0
 */

#include <cdocx.h>
#include <cdocx/advanced.h>
#include <iostream>

int main() {
    cdocx::Document doc("document_search_example.docx");
    if (!doc.create_empty()) {
        std::cerr << "Failed to create document" << std::endl;
        return 1;
    }

    auto body = doc.get_first_section()->get_body();

    // ------------------------------------------------------------------------
    // Create sample content
    // ------------------------------------------------------------------------
    body->append_paragraph("CDocx is a C++ library for working with Word documents.");
    body->append_paragraph("CDocx supports DOM-style API and XML Parts API.");
    body->append_paragraph("With CDocx, you can create, read, and modify DOCX files.");
    body->append_paragraph("Thank you for using CDocx!");

    // ------------------------------------------------------------------------
    // Example 1: Find text
    // ------------------------------------------------------------------------
    auto range = cdocx::DocumentSearch::find(doc, "DOM");
    if (range) {
        std::cout << "Found 'DOM' in the document." << std::endl;
    } else {
        std::cout << "'DOM' not found." << std::endl;
    }

    // ------------------------------------------------------------------------
    // Example 2: Find all occurrences
    // ------------------------------------------------------------------------
    auto ranges = cdocx::DocumentSearch::find_all(doc, "CDocx");
    std::cout << "Found 'CDocx' in " << ranges.size() << " paragraph(s)." << std::endl;

    // ------------------------------------------------------------------------
    // Example 3: Replace first occurrence
    // ------------------------------------------------------------------------
    bool replaced = cdocx::DocumentSearch::replace(doc, "CDocx", "MyLibrary");
    std::cout << "First replacement: " << (replaced ? "success" : "not found") << std::endl;

    // ------------------------------------------------------------------------
    // Example 4: Replace all occurrences
    // ------------------------------------------------------------------------
    // Reset document for clean demo
    cdocx::Document doc2("document_search_example.docx");
    doc2.create_empty();
    auto body2 = doc2.get_first_section()->get_body();
    body2->append_paragraph("CDocx is powerful.");
    body2->append_paragraph("CDocx is easy to use.");
    body2->append_paragraph("We love CDocx!");

    int count = cdocx::DocumentSearch::replace_all(doc2, "CDocx", "OpenDocx");
    std::cout << "Replaced " << count << " occurrence(s) of 'CDocx' with 'OpenDocx'." << std::endl;

    // ------------------------------------------------------------------------
    // Example 5: Replace with formatting
    // ------------------------------------------------------------------------
    cdocx::Document doc3("document_search_formatted.docx");
    doc3.create_empty();
    auto body3 = doc3.get_first_section()->get_body();
    body3->append_paragraph("Important: please read the manual.");

    cdocx::DocumentSearch::replace_with_formatting(
        doc3, "Important", "WARNING", static_cast<cdocx::FormattingFlag>(cdocx::kBold));
    std::cout << "Replaced 'Important' with bold 'WARNING'." << std::endl;

    // ------------------------------------------------------------------------
    // Example 6: Find and process with callback
    // ------------------------------------------------------------------------
    cdocx::Document doc4("document_search_callback.docx");
    doc4.create_empty();
    auto body4 = doc4.get_first_section()->get_body();
    body4->append_paragraph("Task 1: TODO - Write tests");
    body4->append_paragraph("Task 2: TODO - Write documentation");
    body4->append_paragraph("Task 3: DONE - Setup project");

    int todo_count = cdocx::DocumentSearch::find_and_process(doc4, "TODO",
        [](const std::string& /*found_text*/, cdocx::Range& range) {
            std::cout << "Found task: " << range.get_text() << std::endl;
            return true; // continue searching
        });
    std::cout << "Processed " << todo_count << " TODO item(s)." << std::endl;

    // ------------------------------------------------------------------------
    // Save
    // ------------------------------------------------------------------------
    doc.save();
    doc2.save();
    doc3.save();
    doc4.save();

    std::cout << "Documents saved successfully." << std::endl;
    return 0;
}
