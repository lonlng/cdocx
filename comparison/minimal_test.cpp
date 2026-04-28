#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc;
    doc.create_empty("minimal_test.docx");

    auto section = doc.get_first_section();
    auto body = section->get_body();

    // Simple paragraph with no formatting
    body->append_paragraph("Hello world");

    doc.save();
    std::cout << "Created minimal_test.docx" << std::endl;
    return 0;
}
