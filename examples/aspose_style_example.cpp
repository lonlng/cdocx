/*
 * CDocx Full - Aspose.Words Style Example
 * Demonstrates the full API similar to Aspose.Words
 */

#include <cdocx_full.h>
#include <iostream>
#include <memory>

using namespace cdocx;

void example_create_document() {
    std::cout << "=== Creating Document with Aspose-style API ===" << std::endl;
    
    // Create new document
    Document doc;
    
    // Create and configure section
    Section* section = new Section();
    section->get_page_setup()->set_page_width(ConvertUtil::inch_to_point(8.5));
    section->get_page_setup()->set_page_height(ConvertUtil::inch_to_point(11));
    section->get_page_setup()->set_left_margin(ConvertUtil::inch_to_point(1));
    section->get_page_setup()->set_right_margin(ConvertUtil::inch_to_point(1));
    section->get_page_setup()->set_top_margin(ConvertUtil::inch_to_point(1));
    section->get_page_setup()->set_bottom_margin(ConvertUtil::inch_to_point(1));
    doc.get_sections().add(section);
    
    // Use DocumentBuilder for easy content creation
    DocumentBuilder builder(&doc);
    
    // Title with formatting
    builder.set_bold(true);
    builder.set_font_size(24);
    builder.set_paragraph_alignment(ParagraphAlignment::Center);
    builder.writeln("Company Report");
    builder.clear_formatting();
    
    // Subtitle
    builder.set_font_size(14);
    builder.set_italic(true);
    builder.set_paragraph_alignment(ParagraphAlignment::Center);
    builder.writeln("Annual Summary 2024");
    builder.writeln();
    builder.clear_formatting();
    
    // Normal paragraph
    builder.set_paragraph_alignment(ParagraphAlignment::Justify);
    builder.writeln("This is a comprehensive report detailing the company's performance "
                    "over the past fiscal year. The following sections outline key "
                    "achievements and future goals.");
    builder.writeln();
    
    // Heading 1
    builder.set_bold(true);
    builder.set_font_size(16);
    builder.set_paragraph_space_before(12);
    builder.set_paragraph_space_after(6);
    builder.writeln("1. Executive Summary");
    builder.clear_formatting();
    
    // Content
    builder.writeln("The company has achieved significant growth in multiple sectors. "
                    "Revenue increased by 25% compared to the previous year.");
    builder.writeln();
    
    // Create a table
    builder.set_bold(true);
    builder.writeln("2. Financial Highlights");
    builder.clear_formatting();
    
    Table* table = builder.start_table();
    
    // Header row
    builder.insert_row();
    builder.insert_cell();
    builder.set_bold(true);
    builder.write("Quarter");
    builder.insert_cell();
    builder.write("Revenue");
    builder.insert_cell();
    builder.write("Growth");
    builder.end_row();
    
    // Data rows
    builder.insert_row();
    builder.insert_cell();
    builder.write("Q1");
    builder.insert_cell();
    builder.write("$1.2M");
    builder.insert_cell();
    builder.write("+15%");
    builder.end_row();
    
    builder.insert_row();
    builder.insert_cell();
    builder.write("Q2");
    builder.insert_cell();
    builder.write("$1.5M");
    builder.insert_cell();
    builder.write("+25%");
    builder.end_row();
    
    builder.insert_row();
    builder.insert_cell();
    builder.write("Q3");
    builder.insert_cell();
    builder.write("$1.8M");
    builder.insert_cell();
    builder.write("+20%");
    builder.end_row();
    
    builder.insert_row();
    builder.insert_cell();
    builder.write("Q4");
    builder.insert_cell();
    builder.write("$2.1M");
    builder.insert_cell();
    builder.write("+17%");
    builder.end_row();
    
    builder.end_table();
    builder.writeln();
    
    // Add a hyperlink
    builder.write("For more details, visit our website: ");
    builder.insert_hyperlink("www.company.com", "https://www.company.com", false);
    builder.writeln();
    
    // Save document
    doc.save("aspose_style_output.docx");
    std::cout << "Document saved: aspose_style_output.docx" << std::endl;
}

void example_work_with_styles() {
    std::cout << "\n=== Working with Styles ===" << std::endl;
    
    Document doc;
    
    // Create custom styles
    Style* heading1 = new Style();
    heading1->set_name("Custom Heading 1");
    heading1->set_type(StyleType::Paragraph);
    heading1->get_font()->set_bold(true);
    heading1->get_font()->set_size(16);
    heading1->get_font()->set_color("2E74B5");
    heading1->get_paragraph_format()->set_space_before(12);
    heading1->get_paragraph_format()->set_space_after(6);
    doc.get_styles().add(heading1);
    
    Style* codeStyle = new Style();
    codeStyle->set_name("Code");
    codeStyle->set_type(StyleType::Paragraph);
    codeStyle->get_font()->set_name("Consolas");
    codeStyle->get_font()->set_size(10);
    codeStyle->get_paragraph_format()->set_shading()->set_background_color("F2F2F2");
    doc.get_styles().add(codeStyle);
    
    // Apply styles using DocumentBuilder
    DocumentBuilder builder(&doc);
    
    builder.get_paragraph_format()->set_style(heading1);
    builder.writeln("Code Example");
    
    builder.get_paragraph_format()->set_style(codeStyle);
    builder.writeln("int main() {");
    builder.writeln("    return 0;");
    builder.writeln("}");
    
    doc.save("styles_output.docx");
    std::cout << "Document with styles saved: styles_output.docx" << std::endl;
}

void example_bookmarks_and_fields() {
    std::cout << "\n=== Working with Bookmarks and Fields ===" << std::endl;
    
    Document doc;
    DocumentBuilder builder(&doc);
    
    // Create bookmark
    builder.start_bookmark("Introduction");
    builder.set_bold(true);
    builder.writeln("Introduction");
    builder.clear_formatting();
    builder.write("This document demonstrates bookmarks and fields.");
    builder.end_bookmark("Introduction");
    builder.writeln();
    
    // Insert page number field
    builder.write("Page ");
    builder.insert_field("PAGE");
    builder.write(" of ");
    builder.insert_field("NUMPAGES");
    builder.writeln();
    
    // Insert date field
    builder.write("Document generated on: ");
    builder.insert_field("DATE", "01/01/2024");
    builder.writeln();
    
    // Access bookmarks
    BookmarkCollection& bookmarks = doc.get_bookmarks();
    std::cout << "Number of bookmarks: " << bookmarks.get_count() << std::endl;
    
    Bookmark* intro = bookmarks.get_item("Introduction");
    if (intro) {
        std::cout << "Found bookmark: " << intro->get_name() << std::endl;
    }
    
    doc.save("bookmarks_fields_output.docx");
    std::cout << "Document saved: bookmarks_fields_output.docx" << std::endl;
}

void example_comments() {
    std::cout << "\n=== Working with Comments ===" << std::endl;
    
    Document doc;
    DocumentBuilder builder(&doc);
    
    builder.writeln("This is an important paragraph that needs review.");
    
    // Add comment
    Comment* comment = builder.start_comment("John Doe", "JD");
    comment->set_text("Please verify this information before finalizing.");
    builder.end_comment();
    
    builder.writeln("Another paragraph here.");
    
    // Add reply to comment
    Comment* reply = new Comment();
    reply->set_author("Jane Smith");
    reply->set_initial("JS");
    reply->set_text("Verified and approved.");
    reply->set_ancestor(comment);
    comment->get_replies()->add(reply);
    
    std::cout << "Total comments: " << doc.get_comments().get_count() << std::endl;
    
    doc.save("comments_output.docx");
    std::cout << "Document saved: comments_output.docx" << std::endl;
}

void example_find_replace() {
    std::cout << "\n=== Find and Replace ===" << std::endl;
    
    Document doc;
    DocumentBuilder builder(&doc);
    
    builder.writeln("The quick brown fox jumps over the lazy dog.");
    builder.writeln("The fox is quick and the dog is lazy.");
    builder.writeln("All foxes are quick and all dogs are lazy.");
    
    // Get document range
    Range* range = doc.get_range();
    
    // Simple replace
    int count = range->replace("fox", "cat");
    std::cout << "Replaced 'fox' with 'cat' in " << count << " place(s)" << std::endl;
    
    // Replace all
    count = range->replace("dog", "wolf", "");
    std::cout << "Replaced 'dog' with 'wolf' in " << count << " place(s)" << std::endl;
    
    std::cout << "Result text: " << range->get_text() << std::endl;
    
    doc.save("find_replace_output.docx");
}

void example_table_operations() {
    std::cout << "\n=== Table Operations ===" << std::endl;
    
    Document doc;
    DocumentBuilder builder(&doc);
    
    builder.set_bold(true);
    builder.writeln("Sales Report");
    builder.clear_formatting();
    
    // Create formatted table
    Table* table = builder.start_table();
    
    // Set table properties
    table->set_alignment(TableAlignment::Center);
    table->set_allow_auto_fit(true);
    
    // Header row
    builder.insert_row();
    for (const char* header : {"Product", "Q1", "Q2", "Q3", "Q4", "Total"}) {
        builder.insert_cell();
        builder.set_bold(true);
        builder.set_paragraph_alignment(ParagraphAlignment::Center);
        builder.write(header);
    }
    builder.end_row();
    
    // Sample data
    const char* products[] = {"Product A", "Product B", "Product C"};
    for (const char* product : products) {
        builder.insert_row();
        
        builder.insert_cell();
        builder.write(product);
        
        for (int i = 0; i < 4; ++i) {
            builder.insert_cell();
            builder.set_paragraph_alignment(ParagraphAlignment::Right);
            builder.write("$" + std::to_string(1000 + i * 100));
        }
        
        builder.insert_cell();
        builder.set_bold(true);
        builder.set_paragraph_alignment(ParagraphAlignment::Right);
        builder.write("$4600");
        
        builder.end_row();
    }
    
    builder.end_table();
    
    std::cout << "Table rows: " << table->get_row_count() << std::endl;
    
    doc.save("table_output.docx");
    std::cout << "Document saved: table_output.docx" << std::endl;
}

void example_document_properties() {
    std::cout << "\n=== Document Properties ===" << std::endl;
    
    Document doc;
    
    // Set built-in properties
    DocumentPropertyCollection& props = doc.get_builtin_document_properties();
    props.add("Title", "Sample Document");
    props.add("Subject", "Demonstration");
    props.add("Author", "John Doe");
    props.add("Keywords", "DOCX, C++, Library");
    props.add("Comments", "Created with CDocx");
    
    // Set custom properties
    DocumentPropertyCollection& custom = doc.get_custom_document_properties();
    custom.add("Department", "Engineering");
    custom.add("Project ID", 12345);
    custom.add("Confidential", true);
    
    std::cout << "Built-in properties: " << props.get_count() << std::endl;
    std::cout << "Custom properties: " << custom.get_count() << std::endl;
    
    // Document variables
    VariableCollection& vars = doc.get_variables();
    vars.add("CompanyName", "Acme Corp");
    vars.add("ReportDate", "2024-01-15");
    
    std::cout << "Variables: " << vars.get_count() << std::endl;
    
    doc.save("properties_output.docx");
    std::cout << "Document saved: properties_output.docx" << std::endl;
}

int main() {
    std::cout << R"(
    ____      _                _____ _ _          _     
   / ___|___ | | ___   ___ ___|  ___| (_)_ __ ___| |__  
  | |   / _ \| |/ _ \ / __/ __| |_  | | | '__/ __| '_ \ 
  | |__| (_) | | (_) | (__\__ \  _| | | | |  \__ \ | | |
   \____\___/|_|\___/ \___|___/_|   |_|_|_|  |___/_| |_|
                                                        
   Full Aspose-style Word Processing Library
)" << std::endl;
    
    try {
        example_create_document();
        example_work_with_styles();
        example_bookmarks_and_fields();
        example_comments();
        example_find_replace();
        example_table_operations();
        example_document_properties();
        
        std::cout << "\n=== All examples completed successfully! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
