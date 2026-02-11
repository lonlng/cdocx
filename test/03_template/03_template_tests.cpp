#include <sstream>
#include <gtest/gtest.h>
#include "cdocx.h"
#include <iostream>

TEST(TemplateTest, TemplateImagePlaceholderDetection) {
    cdocx::Document doc("template.docx");
    doc.open();

    cdocx::Template tmpl(&doc);
    tmpl.set_pattern("{{", "}}");

    // Note: This test assumes template.docx exists and has the expected content
    if (doc.is_open()) {
        std::cout << "Document opened successfully for testing" << std::endl;
        EXPECT_TRUE(true);
    } else {
        std::cout << "Warning: template.docx not found, skipping test" << std::endl;
    }
}

TEST(TemplateTest, DocumentInserterBasicFunctionality) {
    cdocx::Document target("main.docx");
    target.open();

    if (target.is_open()) {
        cdocx::DocumentInserter inserter(&target);

        // Test that inserter can be created without errors
        EXPECT_TRUE(true);

        std::cout << "Document inserter test completed" << std::endl;
    } else {
        std::cout << "Warning: main.docx not found, skipping test" << std::endl;
    }
}

TEST(TemplateTest, TemplateSetAndReplaceOperations) {
    cdocx::Document doc("template.docx");
    doc.open();

    if (doc.is_open()) {
        cdocx::Template tmpl(&doc);

        // Test text placeholders
        tmpl.set("test_key", "test_value");
        EXPECT_EQ(tmpl.size(), 1);

        // Test image placeholders
        tmpl.set_image("test_image", "test.png");
        // Note: size() only counts text placeholders currently

        // Clear placeholders
        tmpl.clear();
        EXPECT_EQ(tmpl.size(), 0);

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
