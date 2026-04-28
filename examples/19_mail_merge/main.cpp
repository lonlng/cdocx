/**
 * @file main.cpp
 * @brief MailMerge example - aligns with Aspose.Words MailMerge API
 * @since 0.8.0
 */

#include <cdocx.h>
#include <iostream>

int main() {
    // Create a document with merge fields
    cdocx::Document doc;
    doc.create_empty();

    auto section = doc.append_section();
    auto body = section->get_body();

    // Title
    auto title = body->append_paragraph("Invoice");
    title->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;

    // Customer info with merge fields
    auto para = body->append_paragraph("Dear ");
    auto name_field = std::make_shared<cdocx::Field>(&doc, cdocx::FieldType::MergeField);
    name_field->set_field_code("MERGEFIELD CustomerName");
    para->append_child(name_field);
    para->append_run(",");

    auto para2 = body->append_paragraph("Your order total is $");
    auto total_field = std::make_shared<cdocx::Field>(&doc, cdocx::FieldType::MergeField);
    total_field->set_field_code("MERGEFIELD OrderTotal");
    para2->append_child(total_field);
    para2->append_run(".");

    auto para3 = body->append_paragraph("Ship to: ");
    auto city_field = std::make_shared<cdocx::Field>(&doc, cdocx::FieldType::MergeField);
    city_field->set_field_code("MERGEFIELD City");
    para3->append_child(city_field);

    // Show available fields
    cdocx::MailMerge mail_merge(&doc);
    auto fields = mail_merge.get_field_names();
    std::cout << "Available merge fields: ";
    for (const auto& f : fields) {
        std::cout << f << " ";
    }
    std::cout << "\n";

    // Execute mail merge
    std::map<std::string, std::string> data = {
        {"CustomerName", "ELEGANCE Customer"},
        {"OrderTotal", "1,299.00"},
        {"City", "Shanghai"}
    };
    mail_merge.execute(data);

    doc.save("mail_merge.docx");
    std::cout << "Saved mail_merge.docx\n";
    return 0;
}
