/*
 * CDocx Advanced CRUD Operations Example
 * 
 * This example demonstrates the new CRUD features inspired by Aspose.Words:
 * - Create: Insert paragraphs, text, tables, bookmarks using DocumentBuilder
 * - Read: Get text from ranges, paragraphs; list bookmarks
 * - Update: Replace text, modify formatting
 * - Delete: Remove paragraphs, bookmarks, content
 */

#include <cdocx.h>
#include <cdocx_advanced.h>
#include <iostream>
#include <fstream>

using namespace cdocx;

void print_section(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

// ============================================================================
// Example 1: Creating documents with DocumentBuilder
// ============================================================================
void example_create_document() {
    print_section("Example 1: Creating Documents with DocumentBuilder");
    
    Document doc("output_create.docx");
    if (!doc.create_empty()) {
        std::cerr << "Failed to create document!" << std::endl;
        return;
    }
    
    // Use DocumentBuilder for easy document construction
    DocumentBuilder builder(&doc);
    
    // Add title with formatting
    builder.set_bold(true);
    builder.set_font_size(28);
    builder.set_alignment("center");
    builder.writeln("CDocx Advanced Features Demo");
    builder.writeln();
    
    // Reset formatting and add normal text
    builder.clear_formatting();
    builder.set_font_size(22);
    builder.writeln("This document demonstrates the new CRUD operations.");
    builder.writeln();
    
    // Add section with formatting
    builder.set_bold(true);
    builder.set_color("0000FF");
    builder.writeln("1. Text Formatting");
    builder.clear_formatting();
    
    builder.write("You can apply ");
    builder.set_bold(true);
    builder.write("bold");
    builder.clear_formatting();
    builder.write(", ");
    builder.set_italic(true);
    builder.write("italic");
    builder.clear_formatting();
    builder.write(", or ");
    builder.set_underline(true);
    builder.write("underlined");
    builder.clear_formatting();
    builder.writeln(" formatting.");
    builder.writeln();
    
    // Add hyperlink
    builder.writeln("2. Hyperlinks");
    builder.insert_hyperlink("Visit CDocx on GitHub", "https://github.com/lonlng/CDocx");
    builder.writeln();
    builder.writeln();
    
    // Add bookmarks
    builder.writeln("3. Bookmarks");
    builder.start_bookmark("Section3");
    builder.writeln("This text is bookmarked!");
    builder.end_bookmark("Section3");
    builder.writeln();
    
    // Add table
    builder.writeln("4. Tables");
    builder.start_table();
    
    // First row
    builder.insert_row();
    builder.insert_cell();
    builder.set_bold(true);
    builder.write("Name");
    builder.insert_cell();
    builder.write("Value");
    builder.end_row();
    
    // Second row
    builder.insert_row();
    builder.insert_cell();
    builder.clear_formatting();
    builder.write("Feature");
    builder.insert_cell();
    builder.write("Supported");
    builder.end_row();
    
    // Third row
    builder.insert_row();
    builder.insert_cell();
    builder.write("CRUD Operations");
    builder.insert_cell();
    builder.write("Yes");
    builder.end_row();
    
    builder.end_table();
    builder.writeln();
    
    // Add another paragraph
    builder.writeln("Document created successfully!");
    
    // Save document
    doc.save();
    std::cout << "Document saved to: output_create.docx" << std::endl;
}

// ============================================================================
// Example 2: Reading document content
// ============================================================================
void example_read_document() {
    print_section("Example 2: Reading Document Content");
    
    // First create a document to read
    {
        Document doc("output_read.docx");
        doc.create_empty();
        DocumentBuilder builder(&doc);
        builder.writeln("First paragraph with some text.");
        builder.writeln("Second paragraph for demonstration.");
        builder.start_bookmark("MyBookmark");
        builder.writeln("This is inside a bookmark.");
        builder.end_bookmark("MyBookmark");
        doc.save();
    }
    
    // Now read it
    Document doc("output_read.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return;
    }
    
    // Read all paragraphs
    std::cout << "\nParagraphs in document:" << std::endl;
    int para_count = 0;
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        std::string text;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            text += r.get_text();
        }
        if (!text.empty()) {
            std::cout << "  [" << ++para_count << "] " << text << std::endl;
        }
    }
    
    // List bookmarks
    std::cout << "\nBookmarks in document:" << std::endl;
    BookmarkCollection bookmarks(&doc);
    std::cout << "  Total bookmarks: " << bookmarks.count() << std::endl;
    for (const auto& bm : bookmarks) {
        std::cout << "  - " << bm.get_name() << ": \"" << bm.get_text() << "\"" << std::endl;
    }
    
    // Get full document text using Range
    std::cout << "\nFull document text:" << std::endl;
    pugi::xml_document* doc_xml = doc.get_document_xml();
    if (doc_xml) {
        Range full_range(&doc, 
            doc_xml->child("w:document").child("w:body").child("w:p"),
            doc_xml->child("w:document").child("w:body").last_child());
        std::cout << full_range.get_text() << std::endl;
    }
}

// ============================================================================
// Example 3: Updating document content
// ============================================================================
void example_update_document() {
    print_section("Example 3: Updating Document Content");
    
    // Create a document
    {
        Document doc("output_update.docx");
        doc.create_empty();
        DocumentBuilder builder(&doc);
        builder.writeln("The quick brown fox jumps over the lazy dog.");
        builder.writeln("Old text that needs to be replaced.");
        builder.writeln("Another line with old content.");
        doc.save();
    }
    
    // Update the document
    Document doc("output_update.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return;
    }
    
    // Simple text replacement
    std::cout << "\nReplacing text..." << std::endl;
    int count = DocumentSearch::replace_all(doc, "old", "NEW");
    std::cout << "  Replaced " << count << " occurrence(s) of 'old' with 'NEW'" << std::endl;
    
    // Replace with formatting
    bool replaced = DocumentSearch::replace_with_formatting(doc, "fox", "CAT", 
                                                           cdocx::bold | cdocx::italic);
    std::cout << "  Replaced 'fox' with bold+italic 'CAT': " 
              << (replaced ? "Yes" : "No") << std::endl;
    
    doc.save();
    std::cout << "\nDocument saved to: output_update.docx" << std::endl;
}

// ============================================================================
// Example 4: Deleting content
// ============================================================================
void example_delete_content() {
    print_section("Example 4: Deleting Content");
    
    // Create a document with bookmarks
    {
        Document doc("output_delete.docx");
        doc.create_empty();
        DocumentBuilder builder(&doc);
        builder.writeln("This paragraph will stay.");
        builder.start_bookmark("ToRemove");
        builder.writeln("This paragraph will be removed with the bookmark.");
        builder.end_bookmark("ToRemove");
        builder.writeln("This paragraph will also stay.");
        doc.save();
    }
    
    // Delete content
    Document doc("output_delete.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return;
    }
    
    std::cout << "\nBefore deletion:" << std::endl;
    BookmarkCollection bookmarks_before(&doc);
    std::cout << "  Bookmarks: " << bookmarks_before.count() << std::endl;
    
    // Remove bookmark with its content
    auto bm = bookmarks_before.get("ToRemove");
    if (bm) {
        bm->remove_with_content();
        std::cout << "  Removed bookmark 'ToRemove' with its content" << std::endl;
    }
    
    // Clear a specific paragraph
    // This demonstrates finding and clearing content
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        std::string para_text;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            para_text += r.get_text();
        }
        if (para_text.find("also stay") != std::string::npos) {
            // We could clear this paragraph if needed
            // p.clear();
            std::cout << "  Found paragraph: \"" << para_text << "\"" << std::endl;
        }
    }
    
    doc.save();
    std::cout << "\nDocument saved to: output_delete.docx" << std::endl;
}

// ============================================================================
// Example 5: Advanced search and replace
// ============================================================================
void example_search_and_process() {
    print_section("Example 5: Advanced Search and Process");
    
    // Create a document
    {
        Document doc("output_search.docx");
        doc.create_empty();
        DocumentBuilder builder(&doc);
        builder.writeln("Invoice #12345 for Customer A");
        builder.writeln("Invoice #12346 for Customer B");
        builder.writeln("Invoice #12347 for Customer C");
        doc.save();
    }
    
    // Process the document
    Document doc("output_search.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return;
    }
    
    std::cout << "\nFinding all occurrences of 'Invoice':" << std::endl;
    auto ranges = DocumentSearch::find_all(doc, "Invoice");
    std::cout << "  Found " << ranges.size() << " occurrence(s)" << std::endl;
    
    for (size_t i = 0; i < ranges.size(); ++i) {
        std::cout << "  [" << (i+1) << "] \"" << ranges[i].get_text() << "\"" << std::endl;
    }
    
    // Search and process with callback
    std::cout << "\nProcessing with callback:" << std::endl;
    int processed = DocumentSearch::find_and_process(doc, "Invoice", 
        [](const std::string& found_text, Range& range) {
            std::cout << "  Processing: \"" << found_text << "\"" << std::endl;
            // Could modify the range here
            return true; // Continue processing
        });
    std::cout << "  Processed " << processed << " item(s)" << std::endl;
}

// ============================================================================
// Example 6: Working with XML Parts directly
// ============================================================================
void example_xml_parts() {
    print_section("Example 6: Working with XML Parts");
    
    Document doc("TestWord.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return;
    }
    
    // List all XML parts
    std::cout << "\nXML Parts in document:" << std::endl;
    auto parts = doc.get_all_part_names();
    for (const auto& part : parts) {
        std::cout << "  - " << part << std::endl;
    }
    std::cout << "  Total: " << doc.get_part_count() << " part(s)" << std::endl;
    
    // Access specific parts
    std::cout << "\nAccessing specific parts:" << std::endl;
    if (doc.get_document_xml()) {
        std::cout << "  - word/document.xml: Available" << std::endl;
    }
    if (doc.get_styles()) {
        std::cout << "  - word/styles.xml: Available" << std::endl;
    }
    if (doc.get_settings()) {
        std::cout << "  - word/settings.xml: Available" << std::endl;
    }
    
    // List media files
    std::cout << "\nMedia files:" << std::endl;
    auto media = doc.list_media();
    if (media.empty()) {
        std::cout << "  (none)" << std::endl;
    } else {
        for (const auto& m : media) {
            std::cout << "  - " << m << std::endl;
        }
    }
}

// ============================================================================
// Main
// ============================================================================
int main() {
    std::cout << R"(
   ____      _                
  / ___|___ | | ___   ___ ___ 
 | |   / _ \| |/ _ \ / __/ __|
 | |__| (_) | | (_) | (__\__ \
  \____\___/|_|\___/ \___|___/
                              
  Advanced CRUD Operations Demo
)" << std::endl;
    
    try {
        example_create_document();
        example_read_document();
        example_update_document();
        example_delete_content();
        example_search_and_process();
        example_xml_parts();
        
        print_section("All Examples Completed Successfully!");
        std::cout << "\nGenerated files:" << std::endl;
        std::cout << "  - output_create.docx" << std::endl;
        std::cout << "  - output_read.docx" << std::endl;
        std::cout << "  - output_update.docx" << std::endl;
        std::cout << "  - output_delete.docx" << std::endl;
        std::cout << "  - output_search.docx" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
