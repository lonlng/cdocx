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
    p.add_run("bold text, ", cdocx::kBold);
    p.add_run("italic text, ", cdocx::kItalic);
    p.add_run("underlined text, ", cdocx::kUnderline);
    p.add_run("strikethrough text, ", cdocx::kStrikethrough);
    p.add_run("superscript", cdocx::kSuperscript);
    p.add_run(" or ");
    p.add_run("subscript, ", cdocx::kSubscript);
    p.add_run("small caps, ", cdocx::kSmallCaps);
    p.add_run("and shadow effects. ", cdocx::kShadow);
    
    // Add a run with combined formatting
    p.add_run("You can also combine them!", 
              static_cast<cdocx::FormattingFlag>(cdocx::kBold | cdocx::kItalic | cdocx::kUnderline));
    
    // Add another paragraph
    cdocx::Paragraph p2 = doc.paragraphs().insert_paragraph_after(
        "\nThis is a second paragraph with "
    );
    p2.add_run("colored and styled text", 
               static_cast<cdocx::FormattingFlag>(cdocx::kBold | cdocx::kItalic));
    p2.add_run(" to show more formatting options.");
    
    // Save the document
    doc.save();
    
    std::cout << "Document created successfully: output_02_basic_create.docx" << std::endl;
    
    return 0;
}
