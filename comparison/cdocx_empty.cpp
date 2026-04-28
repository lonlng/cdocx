/**
 * Generate a true empty cdocx document for baseline comparison.
 */
#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc;
    doc.create_empty("cdocx_empty.docx");
    doc.save();
    std::cout << "Created cdocx_empty.docx" << std::endl;
    return 0;
}
