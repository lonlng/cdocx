/**
 * Example 02: Basic Document Creation (DOM API)
 *
 * This example demonstrates how to:
 * 1. Create a new DOCX file using the CDocx factory
 * 2. Add paragraphs with formatted text via DOM API
 * 3. Apply various text formatting (bold, italic, underline, etc.)
 * 4. Save the document
 */

#include <cdocx.h>
#include <iostream>

int main() {
    // Create a new document using the CDocx factory (recommended)
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    // Create a paragraph with mixed formatting
    auto para = body->append_paragraph("This example demonstrates various text formatting options: ");

    // Add runs with different formatting using DOM API
    para->append_run("bold text, ")
        ->get_font()
        .bold = true;

    para->append_run("italic text, ")
        ->get_font()
        .italic = true;

    para->append_run("underlined text, ")
        ->get_font()
        .underline = cdocx::UnderlineType::Single;

    para->append_run("strikethrough text, ")
        ->get_font()
        .strike = cdocx::StrikeType::Single;

    para->append_run("superscript")
        ->get_font()
        .script_type = cdocx::ScriptType::Superscript;

    para->append_run(" or ");

    para->append_run("subscript, ")
        ->get_font()
        .script_type = cdocx::ScriptType::Subscript;

    para->append_run("small caps, ")
        ->get_font()
        .small_caps = true;

    para->append_run("and colored text. ")
        ->get_font()
        .color = cdocx::Color::from_hex("FF6600");

    // Combined formatting via chaining
    para->append_run("You can also combine them!")
        ->get_font()
        .bold = true;
    para->get_last_run()->get_font().italic = true;
    para->get_last_run()->get_font().underline = cdocx::UnderlineType::Single;

    // Second paragraph with color
    auto para2 = body->append_paragraph("This is a second paragraph with ");
    para2->append_run("colored and styled text")
        ->get_font()
        .bold = true;
    para2->get_last_run()->get_font().italic = true;
    para2->get_last_run()->get_font().color = cdocx::Color::from_hex("0070C0");
    para2->append_run(" to show more formatting options.");

    // Save the document using the factory
    cdocx::CDocx::save_document(doc, "output_02_basic_create.docx");

    std::cout << "Document created successfully: output_02_basic_create.docx" << std::endl;

    return 0;
}
