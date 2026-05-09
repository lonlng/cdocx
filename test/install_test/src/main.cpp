#include <cdocx.h>
#include <iostream>
#include <fstream>

int main() {
    // Create an empty document using the CDocx factory
    auto doc = cdocx::CDocx::create_document();

    // Try to save to a temp file (validates full linkage)
    try {
        doc->save("install_test_output.docx");
    } catch (const std::exception& e) {
        std::cerr << "FAIL: Could not save document: " << e.what() << std::endl;
        return 1;
    }

    // Verify the file was actually written
    std::ifstream file("install_test_output.docx", std::ios::binary);
    if (!file.good()) {
        std::cerr << "FAIL: Output file was not created" << std::endl;
        return 1;
    }

    // Check it's a valid ZIP (DOCX is a ZIP container)
    char header[4];
    file.read(header, 4);
    if (header[0] != 'P' || header[1] != 'K') {
        std::cerr << "FAIL: Output is not a valid ZIP/DOCX file" << std::endl;
        return 1;
    }

    std::cout << "PASS: cdocx installed package works correctly" << std::endl;
    return 0;
}
