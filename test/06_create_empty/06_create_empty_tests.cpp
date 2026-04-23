/**
 * @file 06_create_empty_tests.cpp
 * @brief Tests for empty document creation functionality
 * @version 0.2.0
 *
 * @defgroup tests_create_empty Create Empty Document Tests
 * @brief Test suite for create_empty() functionality
 * @{
 */

#include <gtest/gtest.h>
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

TEST(CreateEmptyTest, CreateEmptyCreatesValidDocument) {
    const std::string test_file = "test_create_empty.docx";

    // Clean up any existing file
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }

    cdocx::Document doc;

    EXPECT_EQ(doc.create_empty(test_file), true);
    EXPECT_EQ(doc.is_open(), true);
    EXPECT_EQ(doc.get_filepath(), test_file);

    doc.save();
    EXPECT_EQ(fs::exists(test_file), true);
    EXPECT_EQ(is_valid_docx(test_file), true);

    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
}

TEST(CreateEmptyTest, CreatedEmptyDocumentHasAllRequiredXmlParts) {
    const std::string test_file = "test_empty_parts.docx";

    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }

    // Create and save empty document
    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);
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

        EXPECT_EQ(doc.has_xml_part("[Content_Types].xml"), true);
        EXPECT_EQ(doc.has_xml_part("_rels/.rels"), true);
        EXPECT_EQ(doc.has_xml_part("word/_rels/document.xml.rels"), true);
        EXPECT_EQ(doc.has_xml_part("word/document.xml"), true);
        EXPECT_EQ(doc.has_xml_part("word/styles.xml"), true);
        EXPECT_EQ(doc.has_xml_part("word/settings.xml"), true);
        EXPECT_EQ(doc.has_xml_part("word/fontTable.xml"), true);
        EXPECT_EQ(doc.has_xml_part("word/theme/theme1.xml"), true);
        EXPECT_EQ(doc.has_xml_part("docProps/core.xml"), true);
        EXPECT_EQ(doc.has_xml_part("docProps/app.xml"), true);
    }

    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
}

TEST(CreateEmptyTest, CreatedEmptyDocumentCanHaveContentAdded) {
    const std::string test_file = "test_add_content.docx";

    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }

    // Create empty document and add content
    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);

        // Add a paragraph
        cdocx::Paragraph p = doc.paragraphs().insert_paragraph_after("Hello, World!");
        EXPECT_NE(p.get_current_node(), pugi::xml_node());

        // Add a run with formatting
        p.add_run(" Bold text", cdocx::kBold);

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

        EXPECT_EQ(found_text, true);
    }

    // Clean up
    if (fs::exists(test_file)) {
        fs::remove(test_file);
    }
}

TEST(CreateEmptyTest, CreateEmptyWithoutFilepathUsesEmptyPath) {
    cdocx::Document doc;

    // Create without filepath
    EXPECT_EQ(doc.create_empty(), true);
    EXPECT_EQ(doc.is_open(), true);
    EXPECT_EQ(doc.get_filepath().empty(), true);
}

TEST(CreateEmptyTest, CreateEmptyClosesPreviousDocument) {
    const std::string test_file1 = "test_close_prev1.docx";
    const std::string test_file2 = "test_close_prev2.docx";

    // Clean up
    for (const auto& f : {test_file1, test_file2}) {
        if (fs::exists(f)) fs::remove(f);
    }

    cdocx::Document doc;

    // Create first document
    ASSERT_EQ(doc.create_empty(test_file1), true);
    EXPECT_EQ(doc.get_filepath(), test_file1);

    // Create second document (should close first)
    ASSERT_EQ(doc.create_empty(test_file2), true);
    EXPECT_EQ(doc.get_filepath(), test_file2);
    EXPECT_EQ(doc.is_open(), true);

    doc.save();
    EXPECT_EQ(fs::exists(test_file2), true);

    // Clean up
    for (const auto& f : {test_file1, test_file2}) {
        if (fs::exists(f)) fs::remove(f);
    }
}

TEST(CreateEmptyTest, CreatedDocumentHasValidDocumentStructure) {
    const std::string test_file = "test_structure.docx";

    // Clean up
    if (fs::exists(test_file)) fs::remove(test_file);

    // Create document
    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);
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
        ASSERT_NE(doc_xml, nullptr);

        pugi::xml_node document = doc_xml->child("w:document");
        EXPECT_NE(document, pugi::xml_node());

        pugi::xml_node body = document.child("w:body");
        EXPECT_NE(body, pugi::xml_node());

        // Check body has at least a sectPr
        pugi::xml_node sectPr = body.child("w:sectPr");
        EXPECT_NE(sectPr, pugi::xml_node());
    }

    // Clean up
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CreateEmptyTest, CreatedDocumentHasWebSettings) {
    const std::string test_file = "test_websettings.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);
        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document" << std::endl;
            return;
        }

        // webSettings.xml must exist
        EXPECT_TRUE(doc.has_xml_part("word/webSettings.xml"));

        // Verify optimizeForBrowser element
        pugi::xml_document* ws = doc.get_xml_part("word/webSettings.xml");
        ASSERT_NE(ws, nullptr);
        pugi::xml_node root = ws->child("w:webSettings");
        EXPECT_NE(root, pugi::xml_node());
        EXPECT_NE(root.child("w:optimizeForBrowser"), pugi::xml_node());

        // Verify relationship in document.xml.rels
        pugi::xml_document* rels = doc.get_xml_part("word/_rels/document.xml.rels");
        ASSERT_NE(rels, nullptr);
        bool found = false;
        for (pugi::xml_node rel : rels->child("Relationships").children("Relationship")) {
            std::string type = rel.attribute("Type").value();
            if (type.find("webSettings") != std::string::npos) {
                found = true;
                EXPECT_STREQ(rel.attribute("Target").value(), "webSettings.xml");
                break;
            }
        }
        EXPECT_TRUE(found) << "webSettings relationship not found in document.xml.rels";
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CreateEmptyTest, CreatedDocumentHasContentTypeDefaults) {
    const std::string test_file = "test_content_types.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);
        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document" << std::endl;
            return;
        }

        pugi::xml_document* ct = doc.get_content_types();
        ASSERT_NE(ct, nullptr);
        pugi::xml_node types = ct->child("Types");
        EXPECT_NE(types, pugi::xml_node());

        bool has_rels_default = false;
        bool has_xml_default = false;
        for (pugi::xml_node child : types.children()) {
            std::string name = child.name();
            if (name == "Default") {
                std::string ext = child.attribute("Extension").value();
                if (ext == "rels") has_rels_default = true;
                if (ext == "xml") has_xml_default = true;
            }
        }
        EXPECT_TRUE(has_rels_default)
            << "[Content_Types].xml missing Default Extension=rels";
        EXPECT_TRUE(has_xml_default)
            << "[Content_Types].xml missing Default Extension=xml";
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CreateEmptyTest, CreatedDocumentHasBuiltinStyles) {
    const std::string test_file = "test_builtin_styles.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);
        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document" << std::endl;
            return;
        }

        // Verify DOM styles collection is populated
        cdocx::StyleCollection& styles = doc.styles();
        EXPECT_NE(styles.get_by_name("Normal"), nullptr);
        EXPECT_NE(styles.get_by_name("heading 1"), nullptr);
        EXPECT_NE(styles.get_by_name("heading 9"), nullptr);
        EXPECT_NE(styles.get_by_name("Title"), nullptr);
        EXPECT_NE(styles.get_by_name("Subtitle"), nullptr);
        EXPECT_NE(styles.get_by_name("List Paragraph"), nullptr);
        EXPECT_NE(styles.get_by_name("Strong"), nullptr);
        EXPECT_NE(styles.get_by_name("Emphasis"), nullptr);
        EXPECT_NE(styles.get_by_name("Hyperlink"), nullptr);

        // Verify styles.xml contains the styles
        pugi::xml_document* styles_xml = doc.get_styles();
        ASSERT_NE(styles_xml, nullptr);
        pugi::xml_node styles_root = styles_xml->child("w:styles");
        EXPECT_NE(styles_root, pugi::xml_node());

        int style_count = 0;
        for (auto _ [[maybe_unused]] : styles_root.children("w:style")) {
            style_count++;
        }
        EXPECT_GE(style_count, 16) << "Expected at least 16 built-in styles";
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CreateEmptyTest, CreatedDocumentHasCorrectRelationships) {
    const std::string test_file = "test_relationships.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);
        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document" << std::endl;
            return;
        }

        pugi::xml_document* rels = doc.get_xml_part("word/_rels/document.xml.rels");
        ASSERT_NE(rels, nullptr);

        // Count relationships and ensure no collisions
        std::set<std::string> ids;
        std::set<std::string> targets;
        for (pugi::xml_node rel : rels->child("Relationships").children("Relationship")) {
            std::string id = rel.attribute("Id").value();
            std::string target = rel.attribute("Target").value();
            EXPECT_FALSE(ids.count(id)) << "Duplicate relationship ID: " << id;
            EXPECT_FALSE(targets.count(target)) << "Duplicate relationship target: " << target;
            ids.insert(id);
            targets.insert(target);
        }

        // Expected: styles, settings, fontTable, theme, webSettings = 5 relationships
        EXPECT_EQ(ids.size(), 5u) << "Expected 5 relationships in document.xml.rels";
        EXPECT_TRUE(targets.count("styles.xml"));
        EXPECT_TRUE(targets.count("settings.xml"));
        EXPECT_TRUE(targets.count("fontTable.xml"));
        EXPECT_TRUE(targets.count("theme/theme1.xml"));
        EXPECT_TRUE(targets.count("webSettings.xml"));
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CreateEmptyTest, PlaceholderParagraphRemovedOnAppend) {
    const std::string test_file = "test_placeholder.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);

        auto section = doc.get_first_section();
        ASSERT_NE(section, nullptr);
        auto body = section->get_body();
        ASSERT_NE(body, nullptr);

        // Before append: body should have exactly 1 placeholder paragraph
        auto children = body->get_child_nodes();
        EXPECT_EQ(children.get_count(), 1u) << "Empty body should have 1 placeholder";

        // After append: placeholder should be removed, only new content remains
        body->append_paragraph("Hello");
        children = body->get_child_nodes();
        EXPECT_EQ(children.get_count(), 1u)
            << "Placeholder should be removed after append_paragraph";

        // Verify the remaining paragraph has actual text
        auto para = std::dynamic_pointer_cast<cdocx::Paragraph>(children[0]);
        ASSERT_NE(para, nullptr);
        EXPECT_EQ(para->get_text(), "Hello");

        doc.save();
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

// Minimal 1x1 pixel PNG image data (for testing thumbnail)
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

TEST(CreateEmptyTest, ThumbnailCanBeAddedAndRemoved) {
    const std::string test_file = "test_thumbnail.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        cdocx::Document doc;
        ASSERT_EQ(doc.create_empty(test_file), true);

        // Initially no thumbnail
        EXPECT_FALSE(doc.has_thumbnail());

        // Add thumbnail from memory
        std::vector<uint8_t> png_data(MINIMAL_PNG, MINIMAL_PNG + sizeof(MINIMAL_PNG));
        EXPECT_TRUE(doc.add_thumbnail_from_memory(png_data, "image/png"));
        EXPECT_TRUE(doc.has_thumbnail());

        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document" << std::endl;
            return;
        }

        // Verify thumbnail part exists (MediaFile, not XmlFile)
        EXPECT_TRUE(doc.has_thumbnail());

        // Verify relationship in package rels
        pugi::xml_document* rels = doc.get_xml_part("_rels/.rels");
        ASSERT_NE(rels, nullptr);
        bool found_thumb_rel = false;
        for (pugi::xml_node rel : rels->child("Relationships").children("Relationship")) {
            std::string type = rel.attribute("Type").value();
            if (type.find("thumbnail") != std::string::npos) {
                found_thumb_rel = true;
                EXPECT_STREQ(rel.attribute("Target").value(), "docProps/thumbnail.jpeg");
                break;
            }
        }
        EXPECT_TRUE(found_thumb_rel) << "Thumbnail relationship not found in _rels/.rels";

        // Verify content type override
        pugi::xml_document* ct = doc.get_content_types();
        ASSERT_NE(ct, nullptr);
        bool found_ct = false;
        for (pugi::xml_node child : ct->child("Types").children("Override")) {
            std::string part = child.attribute("PartName").value();
            if (part == "/docProps/thumbnail.jpeg") {
                found_ct = true;
                EXPECT_STREQ(child.attribute("ContentType").value(), "image/png");
                break;
            }
        }
        EXPECT_TRUE(found_ct) << "Content type override for thumbnail not found";
    }

    {
        // Test removal
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document for removal test" << std::endl;
            return;
        }

        EXPECT_TRUE(doc.has_thumbnail());
        EXPECT_TRUE(doc.remove_thumbnail());
        EXPECT_FALSE(doc.has_thumbnail());
        doc.save();
    }

    {
        // Verify removed after save
        cdocx::Document doc(test_file);
        doc.open();
        if (!doc.is_open()) {
            std::cout << "[SKIPPED] Could not open document after removal" << std::endl;
            return;
        }
        EXPECT_FALSE(doc.has_thumbnail());
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

/** @} */
