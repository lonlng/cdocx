#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc;
    doc.create_empty("styled_output.docx");

    auto& styles = doc.styles();

    // Create a custom paragraph style
    auto custom = styles.add(cdocx::StyleType::Paragraph, "MyCustomStyle");
    custom->get_font().set_names("Calibri");
    custom->get_font().size = 14;
    custom->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;

    // Apply it to a paragraph
    auto section = doc.get_first_section();
    auto para = section->get_body()->append_paragraph("Hello, styled world!");
    para->get_paragraph_format().style_name = "MyCustomStyle";

    doc.save();
    std::cout << "Saved styled_output.docx" << std::endl;
    return 0;
}
