#include <cdocx.h>
#include <iostream>

int main() {
    std::cout << "Testing Document load..." << std::endl;
    
    cdocx::Document doc("test_data/template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "Failed to open document" << std::endl;
        return 1;
    }
    
    std::cout << "Document opened successfully" << std::endl;
    
    auto parts = doc.get_all_part_names();
    std::cout << "XML parts count: " << parts.size() << std::endl;
    
    for (const auto& part : parts) {
        std::cout << "  - " << part << std::endl;
    }
    
    auto media = doc.list_media();
    std::cout << "Media files count: " << media.size() << std::endl;
    
    for (const auto& m : media) {
        auto data = doc.get_media_data(m);
        std::cout << "  - " << m << " (" << data.size() << " bytes)" << std::endl;
    }
    
    return 0;
}
