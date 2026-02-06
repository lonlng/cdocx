/**
 * Example 02: Basic Document Creation
 * 
 * This example demonstrates how to:
 * 1. Create a new DOCX file
 * 2. Add paragraphs with formatted text
 * 3. Apply various text formatting (bold, italic, underline, etc.)
 * 4. Save the document
 */

#include <cdocx.h>
#include <iostream>

int main() {
    // Create a new document (or open existing)
    cdocx::Document doc("output_02_basic_create.docx");
    doc.open();
    
    // Insert a paragraph with formatted text
    cdocx::Paragraph p = doc.paragraphs().insert_paragraph_after(
        "This example demonstrates various text formatting options: "
    );
    
    // Add runs with different formatting
    p.add_run("bold text, ", cdocx::bold);
    p.add_run("italic text, ", cdocx::italic);
    p.add_run("underlined text, ", cdocx::underline);
    p.add_run("strikethrough text, ", cdocx::strikethrough);
    p.add_run("superscript", cdocx::superscript);
    p.add_run(" or ");
    p.add_run("subscript, ", cdocx::subscript);
    p.add_run("small caps, ", cdocx::smallcaps);
    p.add_run("and shadow effects. ", cdocx::shadow);
    
    // Add a run with combined formatting
    p.add_run("You can also combine them!", 
              static_cast<cdocx::formatting_flag>(cdocx::bold | cdocx::italic | cdocx::underline));
    
    // Add another paragraph
    cdocx::Paragraph p2 = doc.paragraphs().insert_paragraph_after(
        "\nThis is a second paragraph with "
    );
    p2.add_run("colored and styled text", 
               static_cast<cdocx::formatting_flag>(cdocx::bold | cdocx::italic));
    p2.add_run(" to show more formatting options.");
    
    // Save the document
    doc.save();
    
    std::cout << "Document created successfully: output_02_basic_create.docx" << std::endl;
    
    return 0;
}
