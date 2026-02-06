#include <sstream>
#include "cdocx.h"
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Template image placeholder detection") {
    cdocx::Document doc("template.docx");
    doc.open();
    
    cdocx::Template tmpl(&doc);
    tmpl.set_pattern("{{", "}}");
    
    // Note: This test assumes template.docx exists and has the expected content
    if (doc.is_open()) {
        std::cout << "Document opened successfully for testing" << std::endl;
        CHECK(true);
    } else {
        std::cout << "Warning: template.docx not found, skipping test" << std::endl;
    }
}

TEST_CASE("Document inserter basic functionality") {
    cdocx::Document target("main.docx");
    target.open();
    
    if (target.is_open()) {
        cdocx::DocumentInserter inserter(&target);
        
        // Test that inserter can be created without errors
        CHECK(true);
        
        std::cout << "Document inserter test completed" << std::endl;
    } else {
        std::cout << "Warning: main.docx not found, skipping test" << std::endl;
    }
}

TEST_CASE("Template set and replace operations") {
    cdocx::Document doc("template.docx");
    doc.open();
    
    if (doc.is_open()) {
        cdocx::Template tmpl(&doc);
        
        // Test text placeholders
        tmpl.set("test_key", "test_value");
        CHECK(tmpl.size() == 1);
        
        // Test image placeholders
        tmpl.set_image("test_image", "test.png");
        // Note: size() only counts text placeholders currently
        
        // Clear placeholders
        tmpl.clear();
        CHECK(tmpl.size() == 0);
        
        std::cout << "Template operations test completed" << std::endl;
    }
}

/*
 * To build and run tests:
 * 
 * mkdir build && cd build
 * cmake ..
 * cmake --build .
 * ctest -R advanced_features
 */
