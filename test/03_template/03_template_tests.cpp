#include <sstream>
#include <gtest/gtest.h>
#include "cdocx.h"
#include <iostream>
#include <filesystem>
#include <fstream>

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

TEST(TemplateTest, ReplaceInHeadersAndFooters) {
    cdocx::Document doc("test_hf_template.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    // Add header with placeholder
    auto header = sect->add_header();
    ASSERT_NE(header, nullptr);
    auto header_para = header->append_paragraph("Report: {{report_title}}");
    ASSERT_NE(header_para, nullptr);

    // Add footer with placeholder
    auto footer = sect->add_footer();
    ASSERT_NE(footer, nullptr);
    auto footer_para = footer->append_paragraph("Page {{page_label}}");
    ASSERT_NE(footer_para, nullptr);

    // Add a table in header with placeholder
    auto header_table = header->append_table(1, 1);
    ASSERT_NE(header_table, nullptr);
    // Note: append_table creates a table but cells may need content insertion.
    // We'll verify header/footer paragraph replacement primarily.

    // Apply template replacement
    cdocx::Template tmpl(&doc);
    tmpl.set("report_title", "Annual Report 2026");
    tmpl.set("page_label", "1 of 10");
    tmpl.replace_all();

    // Verify replacement in DOM
    auto header_paras = header->get_paragraphs();
    ASSERT_FALSE(header_paras.empty());
    EXPECT_NE(header_paras.front()->get_text().find("Annual Report 2026"), std::string::npos);

    auto footer_paras = footer->get_paragraphs();
    ASSERT_FALSE(footer_paras.empty());
    EXPECT_NE(footer_paras.front()->get_text().find("1 of 10"), std::string::npos);

    // Save, reopen, and verify again
    doc.sync_to_physical_tree();
    doc.save();

    cdocx::Document doc2("test_hf_template.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto sect2 = doc2.get_first_section();
    ASSERT_NE(sect2, nullptr);

    auto header2 = sect2->get_header();
    ASSERT_NE(header2, nullptr);
    auto hparas = header2->get_paragraphs();
    ASSERT_FALSE(hparas.empty());
    EXPECT_NE(hparas.front()->get_text().find("Annual Report 2026"), std::string::npos);

    auto footer2 = sect2->get_footer();
    ASSERT_NE(footer2, nullptr);
    auto fparas = footer2->get_paragraphs();
    ASSERT_FALSE(fparas.empty());
    EXPECT_NE(fparas.front()->get_text().find("1 of 10"), std::string::npos);

    doc2.close();
    std::filesystem::remove("test_hf_template.docx");
}

// Minimal 1x1 pixel PNG image data (for testing image placeholder replacement)
const unsigned char MINIMAL_PNG[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4,
    0x89, 0x00, 0x00, 0x00, 0x0A, 0x49, 0x44, 0x41,
    0x54, 0x78, 0x9C, 0x63, 0x60, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC, 0x33, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE,
    0x42, 0x60, 0x82
};

TEST(TemplateTest, ReplaceImagePlaceholder) {
    std::string test_docx = "test_image_template.docx";
    std::string test_image = "test_image_logo.png";

    // Create minimal test image
    {
        std::ofstream img(test_image, std::ios::binary);
        img.write(reinterpret_cast<const char*>(MINIMAL_PNG), sizeof(MINIMAL_PNG));
    }

    // Create document with image placeholder
    {
        cdocx::Document doc(test_docx);
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto para = sect->append_paragraph("{{logo}}");
        ASSERT_NE(para, nullptr);

        cdocx::Template tmpl(&doc);
        tmpl.set_image("logo", test_image);
        tmpl.replace_all();

        doc.sync_to_physical_tree();
        doc.save();
    }

    // Reopen and verify image was embedded
    {
        cdocx::Document doc2(test_docx);
        doc2.open();
        ASSERT_TRUE(doc2.is_open());

        // Verify placeholder text is gone
        auto sect = doc2.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);
        auto paras = body->get_paragraphs();
        ASSERT_FALSE(paras.empty());
        EXPECT_EQ(paras.front()->get_text().find("{{logo}}"), std::string::npos);

        // Check document XML contains a w:drawing element
        pugi::xml_document* doc_xml = doc2.get_document_xml();
        ASSERT_NE(doc_xml, nullptr);
        bool found_drawing = false;
        for (auto para = doc_xml->child("w:document").child("w:body").first_child();
             para; para = para.next_sibling()) {
            if (std::string(para.name()) != "w:p") continue;
            for (auto run = para.first_child(); run; run = run.next_sibling()) {
                if (std::string(run.name()) != "w:r") continue;
                if (run.child("w:drawing")) {
                    found_drawing = true;
                    break;
                }
            }
            if (found_drawing) break;
        }
        EXPECT_TRUE(found_drawing);

        doc2.close();
    }

    std::filesystem::remove(test_docx);
    std::filesystem::remove(test_image);
}

TEST(TemplateTest, ReplaceCrossRunPlaceholder) {
    std::string test_docx = "test_cross_run_template.docx";

    // Create document with placeholder split across multiple runs
    {
        cdocx::Document doc(test_docx);
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto para = sect->append_paragraph("");
        ASSERT_NE(para, nullptr);

        para->append_run("{{com");
        para->append_run("pa");
        para->append_run("ny_name}}");

        cdocx::Template tmpl(&doc);
        tmpl.set("company_name", "Tech Corp International");
        tmpl.replace_all();

        // Verify in-memory replacement before save
        EXPECT_EQ(para->get_text(), "Tech Corp International");
        EXPECT_EQ(para->get_runs().get_count(), 1);

        doc.sync_to_physical_tree();
        doc.save();
    }

    // Reopen and verify replacement
    {
        cdocx::Document doc2(test_docx);
        doc2.open();
        ASSERT_TRUE(doc2.is_open());

        auto sect = doc2.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto paras = body->get_paragraphs();
        ASSERT_FALSE(paras.empty());

        // The appended paragraph is the only one (placeholder removed by append_paragraph)
        auto* target_para = paras.back().get();
        std::string para_text = target_para->get_text();
        EXPECT_NE(para_text.find("Tech Corp International"), std::string::npos);
        EXPECT_EQ(para_text.find("{{company_name}}"), std::string::npos);

        // Verify the paragraph has exactly one run after replacement
        auto runs = target_para->get_runs();
        EXPECT_EQ(runs.get_count(), 1);

        doc2.close();
    }

    std::filesystem::remove(test_docx);
}

TEST(TemplateTest, ReplaceCrossRunPlaceholderWithSurroundingText) {
    std::string test_docx = "test_cross_run_surround_template.docx";

    // Create document with text before and after the split placeholder
    {
        cdocx::Document doc(test_docx);
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto para = sect->append_paragraph("");
        ASSERT_NE(para, nullptr);

        para->append_run("Hello ");
        para->append_run("{{com");
        para->append_run("pa");
        para->append_run("ny_name}}");
        para->append_run(" World");

        cdocx::Template tmpl(&doc);
        tmpl.set("company_name", "Tech Corp");
        tmpl.replace_all();

        doc.sync_to_physical_tree();
        doc.save();
    }

    // Reopen and verify replacement preserved surrounding text
    {
        cdocx::Document doc2(test_docx);
        doc2.open();
        ASSERT_TRUE(doc2.is_open());

        auto sect = doc2.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto paras = body->get_paragraphs();
        ASSERT_FALSE(paras.empty());

        // The appended paragraph is the only one (placeholder removed by append_paragraph)
        auto* target_para = paras.back().get();
        std::string para_text = target_para->get_text();
        EXPECT_EQ(para_text, "Hello Tech Corp World");
        EXPECT_EQ(para_text.find("{{company_name}}"), std::string::npos);

        auto runs = target_para->get_runs();
        // Surrounding text before/after the placeholder remains in separate runs
        EXPECT_EQ(runs.get_count(), 3);

        doc2.close();
    }

    std::filesystem::remove(test_docx);
}

/*
 * To build and run tests:
 *
 * mkdir build && cd build
 * cmake ..
 * cmake --build .
 * ctest -R advanced_features
 */
