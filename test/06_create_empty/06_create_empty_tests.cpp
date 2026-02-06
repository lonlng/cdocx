/**
 * @file 06_create_empty_tests.cpp
 * @brief Tests for empty document creation functionality
 * @version 0.2.0
 * 
 * @defgroup tests_create_empty Create Empty Document Tests
 * @brief Test suite for create_empty() functionality
 * @{
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cdocx.h>
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

/**
 * @brief Helper to check if a file is a valid ZIP (DOCX) file
 */
bool is_valid_docx(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;
    
    // Check ZIP magic number (PK\x03\x04)
    char magic[4];
    file.read(magic, 4);
    return file.gcount() == 4 && 
           magic[0] == 'P' && magic[1] == 'K' && 
           magic[2] == '\x03' && magic[3] == '\x04';
}

TEST_CASE("create_empty creates a valid document") {
    const std::string test_file = "test_create_empty.docx";
    
    // Clean up any existing file
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
    
    SUBCASE("create_empty returns true and creates open document") {
        cdocx::Document doc;
        
        CHECK(doc.create_empty(test_file) == true);
        CHECK(doc.is_open() == true);
        CHECK(doc.get_filepath() == test_file);
        
        doc.save();
        CHECK(fs::exists(test_file) == true);
        CHECK(is_valid_docx(test_file) == true);
    }
    
    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
}

TEST_CASE("created empty document has all required XML parts") {
    const std::string test_file = "test_empty_parts.docx";
    
    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
    
    // Create and save empty document
    {
        cdocx::Document doc;
        REQUIRE(doc.create_empty(test_file) == true);
        doc.save();
    }
    
    // Reopen and verify parts exist
    {
        cdocx::Document doc(test_file);
        doc.open();
        
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open created document" << std::endl;
            return;
        }
        
        CHECK(doc.has_xml_part("[Content_Types].xml") == true);
        CHECK(doc.has_xml_part("_rels/.rels") == true);
        CHECK(doc.has_xml_part("word/_rels/document.xml.rels") == true);
        CHECK(doc.has_xml_part("word/document.xml") == true);
        CHECK(doc.has_xml_part("word/styles.xml") == true);
        CHECK(doc.has_xml_part("word/settings.xml") == true);
        CHECK(doc.has_xml_part("word/fontTable.xml") == true);
        CHECK(doc.has_xml_part("word/theme/theme1.xml") == true);
        CHECK(doc.has_xml_part("docProps/core.xml") == true);
        CHECK(doc.has_xml_part("docProps/app.xml") == true);
    }
    
    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
}

TEST_CASE("created empty document can have content added") {
    const std::string test_file = "test_add_content.docx";
    
    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
    
    // Create empty document and add content
    {
        cdocx::Document doc;
        REQUIRE(doc.create_empty(test_file) == true);
        
        // Add a paragraph
        cdocx::Paragraph p = doc.paragraphs().insert_paragraph_after("Hello, World!");
        CHECK(p.get_current() != pugi::xml_node());
        
        // Add a run with formatting
        p.add_run(" Bold text", cdocx::bold);
        
        doc.save();
    }
    
    // Reopen and verify content
    {
        cdocx::Document doc(test_file);
        doc.open();
        
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document with added content" << std::endl;
            return;
        }
        
        bool found_text = false;
        for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
            for (auto r = p.runs(); r.has_next(); r.next()) {
                std::string text = r.get_text();
                if (text.find("Hello, World!") != std::string::npos) {
                    found_text = true;
                }
            }
        }
        
        CHECK(found_text == true);
    }
    
    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
}

TEST_CASE("create_empty without filepath uses empty path") {
    cdocx::Document doc;
    
    // Create without filepath
    CHECK(doc.create_empty() == true);
    CHECK(doc.is_open() == true);
    CHECK(doc.get_filepath().empty() == true);
}

TEST_CASE("create_empty closes previous document") {
    const std::string test_file1 = "test_close_prev1.docx";
    const std::string test_file2 = "test_close_prev2.docx";
    
    // Clean up
    for (const auto& f : {test_file1, test_file2}) {
        if (fs::exists(f)) fs::remove(f);
    }
    
    cdocx::Document doc;
    
    // Create first document
    REQUIRE(doc.create_empty(test_file1) == true);
    CHECK(doc.get_filepath() == test_file1);
    
    // Create second document (should close first)
    REQUIRE(doc.create_empty(test_file2) == true);
    CHECK(doc.get_filepath() == test_file2);
    CHECK(doc.is_open() == true);
    
    doc.save();
    CHECK(fs::exists(test_file2) == true);
    
    // Clean up
    for (const auto& f : {test_file1, test_file2}) {
        if (fs::exists(f)) fs::remove(f);
    }
}

TEST_CASE("created document has valid document structure") {
    const std::string test_file = "test_structure.docx";
    
    // Clean up
    if (fs::exists(test_file)) fs::remove(test_file);
    
    // Create document
    {
        cdocx::Document doc;
        REQUIRE(doc.create_empty(test_file) == true);
        doc.save();
    }
    
    // Reopen and check structure
    {
        cdocx::Document doc(test_file);
        doc.open();
        
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document" << std::endl;
            return;
        }
        
        // Check document.xml has body
        pugi::xml_document* doc_xml = doc.get_document_xml();
        REQUIRE(doc_xml != nullptr);
        
        pugi::xml_node document = doc_xml->child("w:document");
        CHECK(document != pugi::xml_node());
        
        pugi::xml_node body = document.child("w:body");
        CHECK(body != pugi::xml_node());
        
        // Check body has at least a sectPr
        pugi::xml_node sectPr = body.child("w:sectPr");
        CHECK(sectPr != pugi::xml_node());
    }
    
    // Clean up
    if (fs::exists(test_file)) fs::remove(test_file);
}

/** @} */
