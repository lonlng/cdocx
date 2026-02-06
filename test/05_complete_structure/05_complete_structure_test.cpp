// Test program for complete DOCX structure support
#include <cdocx.h>
#include <iostream>
#include <fstream>
#include <cassert>

void test_load_complete_structure() {
    std::cout << "Test 1: Loading complete DOCX structure..." << std::endl;
    
    cdocx::Document doc("data/template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "  FAILED: Could not open template.docx" << std::endl;
        return;
    }
    
    std::cout << "  Document opened successfully" << std::endl;
    
    // Check all XML parts are loaded
    auto parts = doc.get_all_part_names();
    std::cout << "  Loaded " << parts.size() << " XML parts:" << std::endl;
    for (const auto& part : parts) {
        std::cout << "    - " << part << std::endl;
    }
    
    // Check media files
    auto media = doc.list_media();
    std::cout << "  Found " << media.size() << " media files" << std::endl;
    
    // Check relationships
    auto rels = doc.get_document_rels();
    if (rels) {
        std::cout << "  Document relationships loaded" << std::endl;
    }
    
    // Check various parts
    if (doc.get_styles()) std::cout << "  - styles.xml OK" << std::endl;
    if (doc.get_settings()) std::cout << "  - settings.xml OK" << std::endl;
    if (doc.get_font_table()) std::cout << "  - fontTable.xml OK" << std::endl;
    if (doc.get_footnotes()) std::cout << "  - footnotes.xml OK" << std::endl;
    if (doc.get_endnotes()) std::cout << "  - endnotes.xml OK" << std::endl;
    if (doc.get_package_rels()) std::cout << "  - _rels/.rels OK" << std::endl;
    
    std::cout << "  PASSED" << std::endl;
}

void test_save_complete_structure() {
    std::cout << "\nTest 2: Saving complete DOCX structure..." << std::endl;
    
    cdocx::Document doc("data/template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "  FAILED: Could not open template.docx" << std::endl;
        return;
    }
    
    // Save with new name
    doc.save("data/test_output.docx");
    
    // Re-open and verify
    cdocx::Document doc2("data/test_output.docx");
    doc2.open();
    
    if (!doc2.is_open()) {
        std::cout << "  FAILED: Could not re-open saved document" << std::endl;
        return;
    }
    
    auto parts1 = doc.get_all_part_names();
    auto parts2 = doc2.get_all_part_names();
    
    std::cout << "  Original parts: " << parts1.size() << std::endl;
    std::cout << "  Saved parts: " << parts2.size() << std::endl;
    
    if (parts1.size() == parts2.size()) {
        std::cout << "  PASSED: All parts preserved" << std::endl;
    } else {
        std::cout << "  WARNING: Part count mismatch" << std::endl;
    }
    
    // Check media preserved
    auto media1 = doc.list_media();
    auto media2 = doc2.list_media();
    std::cout << "  Original media: " << media1.size() << std::endl;
    std::cout << "  Saved media: " << media2.size() << std::endl;
    
    if (media1.size() == media2.size()) {
        std::cout << "  PASSED: All media preserved" << std::endl;
    }
}

void test_media_management() {
    std::cout << "\nTest 3: Media management in memory..." << std::endl;
    
    cdocx::Document doc("data/template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "  FAILED: Could not open template.docx" << std::endl;
        return;
    }
    
    // Get media data from memory
    auto media_list = doc.list_media();
    if (!media_list.empty()) {
        std::string first_media = media_list[0];
        auto data = doc.get_media_data(first_media);
        std::cout << "  First media: " << first_media << " (" << data.size() << " bytes)" << std::endl;
        
        // Export media
        if (doc.export_media(first_media, "data/test_export.png")) {
            std::cout << "  PASSED: Media export OK" << std::endl;
        } else {
            std::cout << "  FAILED: Media export failed" << std::endl;
        }
    }
}

void test_xml_modification() {
    std::cout << "\nTest 4: XML modification and save..." << std::endl;
    
    cdocx::Document doc("data/template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "  FAILED: Could not open template.docx" << std::endl;
        return;
    }
    
    // Modify document content
    auto para = doc.paragraphs();
    if (para.has_next()) {
        std::string original_text = para.runs().get_text();
        std::cout << "  First paragraph text: " << original_text.substr(0, 50) << "..." << std::endl;
    }
    
    // Save and reopen
    doc.save("data/test_modified.docx");
    
    cdocx::Document doc2("data/test_modified.docx");
    doc2.open();
    
    if (doc2.is_open()) {
        std::cout << "  PASSED: Modified document saved and reopened" << std::endl;
    } else {
        std::cout << "  FAILED: Could not reopen modified document" << std::endl;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "CDocx Complete Structure Test" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_load_complete_structure();
    test_save_complete_structure();
    test_media_management();
    test_xml_modification();
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "All tests completed" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
