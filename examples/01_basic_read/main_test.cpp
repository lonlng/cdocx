#include <cdocx.h>
#include <iostream>

int main() {
    std::string doc_path = "../../TestWord.docx";  // Use original test file
    
    std::cout << "Opening: " << doc_path << std::endl;
    
    cdocx::Document doc(doc_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document: " << doc_path << std::endl;
        return 1;
    }
    
    std::cout << "Document opened successfully!" << std::endl;
    
    // Iterate through all paragraphs
    int para_count = 0;
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        para_count++;
        std::cout << "\n[Paragraph " << para_count << "]" << std::endl;
        
        int run_count = 0;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            run_count++;
            std::cout << "  Run " << run_count << ": " << r.get_text() << std::endl;
        }
    }
    
    std::cout << "\nTotal paragraphs: " << para_count << std::endl;
    return 0;
}
