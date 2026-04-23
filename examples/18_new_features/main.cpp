#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc;
    doc.create_empty();

    // Default tab stop
    doc.set_default_tab_stop(48.0);  // 48pt = 0.67 inch
    std::cout << "Default tab stop: " << doc.get_default_tab_stop() << "pt\n";

    // Section with paragraph
    auto section = doc.append_section();
    auto body = section->get_body();
    auto para = body->append_paragraph("Hello, Aspose-Aligned CDocx!");

    // Tab stops
    cdocx::ParagraphProperties props;
    cdocx::TabStopCollection tabs;
    tabs.add(72.0, cdocx::TabAlignment::Left, cdocx::TabLeader::Dots);
    tabs.add(144.0, cdocx::TabAlignment::Right, cdocx::TabLeader::Line);
    props.tab_stops = tabs;
    props.apply_to(*para);

    // DocumentBuilder with fields and footnote
    cdocx::DocumentBuilder builder(&doc);
    builder.move_to_document_end();
    builder.writeln();
    builder.write("Page ");
    builder.insert_page_number();
    builder.write(" of ");
    builder.insert_num_pages();
    builder.writeln();

    builder.write("Date: ");
    builder.insert_date();
    builder.writeln();

    // Footnote
    builder.write("This sentence has a footnote");
    builder.insert_footnote(cdocx::FootnoteType::Footnote, "This is the footnote text.");
    builder.writeln();

    // Endnote
    builder.write("This sentence has an endnote");
    builder.insert_footnote(cdocx::FootnoteType::Endnote, "This is the endnote text.");
    builder.writeln();

    // Comment
    auto comment_para = body->append_paragraph("Commented paragraph");
    auto comment_start = std::make_shared<cdocx::CommentRangeStart>(&doc, 0);
    auto comment_end = std::make_shared<cdocx::CommentRangeEnd>(&doc, 0);
    comment_para->insert_child(0, comment_start);
    comment_para->append_child(comment_end);

    auto comment = doc.add_comment("Author", "This is a comment.");
    comment->set_initial("A");

    // Form fields
    builder.move_to_document_end();
    builder.writeln("Form Fields Demo:");
    builder.write("Name: ");
    builder.insert_text_input("Name", cdocx::TextFormFieldType::Regular, "",
                              "John Doe", 50);
    builder.writeln();

    builder.write("Age: ");
    builder.insert_text_input("Age", cdocx::TextFormFieldType::Number, "",
                              "30", 3);
    builder.writeln();

    builder.write("Subscribe: ");
    builder.insert_check_box("Subscribe", true, 12);
    builder.writeln();

    builder.write("Department: ");
    builder.insert_combo_box("Department",
                             {"Engineering", "Sales", "Marketing", "HR"}, 0);
    builder.writeln();

    // TOC
    builder.move_to_document_end();
    builder.insert_table_of_contents("\\o \"1-3\" \\h \\z \\u");

    // Document properties
    doc.get_builtin_document_properties().title = "CDocx New Features Demo";
    doc.get_builtin_document_properties().author = "CDocx Team";
    doc.get_builtin_document_properties().subject = "Demonstration of v0.7.0 features";
    doc.get_builtin_document_properties().keywords = "CDocx, DOCX, C++";
    doc.get_builtin_document_properties().company = "ELEGANCE Labs";
    doc.get_builtin_document_properties().category = "Demo";
    doc.get_builtin_document_properties().revision = "1";

    doc.get_custom_document_properties().set_custom("ProjectId", "CDOCX-2026");
    doc.get_custom_document_properties().set_custom("BuildDate", "2026-04-15");
    std::cout << "Properties set: " << doc.get_builtin_document_properties().title << "\n";

    // Document protection
    doc.protect(cdocx::ProtectionType::ReadOnly);
    std::cout << "Document protected: " << doc.is_protected() << "\n";

    doc.save("new_features.docx");
    std::cout << "Saved new_features.docx\n";
    return 0;
}
