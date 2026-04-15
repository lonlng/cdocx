#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc("../../test/08_bookmark_replacement/test_format_preserve.docx");
    doc.open();
    std::cout << "open: " << doc.is_open() << std::endl;
    if (!doc.is_open()) {
        auto r = doc.get_last_load_result();
        std::cout << "errors: " << r.errors.size() << std::endl;
        for (const auto& e : r.errors) {
            std::cout << "  " << e.message << std::endl;
        }
    }
    return 0;
}
