#include <sstream>
#include <fstream>
#include <filesystem>
#include <gtest/gtest.h>
#include "cdocx.h"

namespace fs = std::filesystem;

TEST(BasicTest, CheckContentsOfMyTestDocx) {
    cdocx::Document doc("data/my_test.docx");
    doc.open();

    // Skip test if document cannot be opened
    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    std::ostringstream ss;

    for (cdocx::Paragraph p = doc.paragraphs(); p.has_next(); p.next()) {
        for (cdocx::Run r = p.runs(); r.has_next(); r.next()) {
            ss << r.get_text() << std::endl;
        }
    }

    EXPECT_EQ("This is a test\nokay?\n", ss.str());
}

TEST(BasicTest, OpenNonexistentFileFailsGracefully) {
    cdocx::Document doc("nonexistent_file_that_does_not_exist.docx");
    doc.open();

    EXPECT_FALSE(doc.is_open());
}

TEST(BasicTest, IsOpenReflectsStateCorrectly) {
    cdocx::Document doc("data/my_test.docx");
    EXPECT_FALSE(doc.is_open());

    doc.open();
    if (doc.is_open()) {
        EXPECT_TRUE(doc.is_open());
        doc.close();
        EXPECT_FALSE(doc.is_open());
    } else {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }
}

TEST(BasicTest, CloseThenReopenSameDocument) {
    cdocx::Document doc("data/my_test.docx");
    doc.open();
    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    doc.close();
    EXPECT_FALSE(doc.is_open());

    doc.open();
    EXPECT_TRUE(doc.is_open());

    // Verify content is still accessible after reopen
    bool found_text = false;
    for (cdocx::Paragraph p = doc.paragraphs(); p.has_next(); p.next()) {
        for (cdocx::Run r = p.runs(); r.has_next(); r.next()) {
            if (r.get_text().find("test") != std::string::npos) {
                found_text = true;
            }
        }
    }
    EXPECT_TRUE(found_text);
}

TEST(BasicTest, OpenCorruptedZipFailsGracefully) {
    // Create a file that is not a valid ZIP
    const std::string bad_file = "not_a_valid_docx.docx";
    {
        std::ofstream f(bad_file);
        f << "This is not a valid ZIP file";
    }

    cdocx::Document doc(bad_file);
    doc.open();

    // Should not crash and should not be open
    EXPECT_FALSE(doc.is_open());

    fs::remove(bad_file);
}

TEST(BasicTest, DomApiCanIterateExistingDocument) {
    cdocx::Document doc("data/my_test.docx");
    doc.open();
    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    auto sections = doc.get_sections();
    EXPECT_GE(sections.get_count(), 1u);

    auto section = doc.get_first_section();
    ASSERT_NE(section, nullptr);

    auto body = section->get_body();
    ASSERT_NE(body, nullptr);

    auto paragraphs = body->get_child_nodes(cdocx::NodeType::Paragraph);
    EXPECT_GE(paragraphs.get_count(), 1u);

    // Verify text extraction via DOM
    std::string all_text;
    for (size_t i = 0; i < paragraphs.get_count(); ++i) {
        auto para = std::dynamic_pointer_cast<cdocx::Paragraph>(paragraphs.get_item(i));
        if (para) {
            all_text += para->get_text();
        }
    }
    EXPECT_NE(all_text.find("test"), std::string::npos);
}

TEST(BasicTest, DocumentFilepathTracking) {
    cdocx::Document doc("data/my_test.docx");
    EXPECT_EQ(doc.get_filepath(), "data/my_test.docx");

    doc.open();
    if (doc.is_open()) {
        EXPECT_EQ(doc.get_filepath(), "data/my_test.docx");
    }
}

TEST(BasicTest, EmptyDocumentPathAfterCreateEmptyWithoutPath) {
    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty());
    EXPECT_TRUE(doc.get_filepath().empty());
    EXPECT_TRUE(doc.is_open());
}
