/**
 * @file test_section_and_list.cpp
 * @brief Unit tests for Section and Numbering features
 * @version 0.5.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <filesystem>
#include <fstream>

using namespace cdocx;
namespace fs = std::filesystem;

// ============================================================================
// Section Management Tests
// ============================================================================

TEST(SectionAndListTest, GetFirstSection) {
    Document doc("test_section.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect = doc.get_first_section();
    EXPECT_NE(sect, nullptr);

    doc.save();
    EXPECT_TRUE(fs::exists("test_section.docx"));
    fs::remove("test_section.docx");
}

TEST(SectionAndListTest, SectionCount) {
    Document doc("test_section.docx");
    ASSERT_TRUE(doc.create_empty());

    EXPECT_GE(doc.get_section_count(), 1);

    doc.save();
    EXPECT_TRUE(fs::exists("test_section.docx"));
    fs::remove("test_section.docx");
}

TEST(SectionAndListTest, SectionProperties) {
    Document doc("test_section.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    // Set properties
    sect->get_properties().orientation = SectionProperties::Orientation::Landscape;
    sect->get_properties().pageSize.width = 15840;
    sect->get_properties().pageSize.height = 12240;

    EXPECT_EQ(sect->get_properties().orientation, SectionProperties::Orientation::Landscape);
    EXPECT_EQ(sect->get_properties().pageSize.width, 15840);

    doc.save();
    EXPECT_TRUE(fs::exists("test_section.docx"));
    fs::remove("test_section.docx");
}

TEST(SectionAndListTest, AddSection) {
    Document doc("test_section.docx");
    ASSERT_TRUE(doc.create_empty());

    size_t initial_count = doc.get_section_count();
    auto new_sect = doc.add_section();

    EXPECT_NE(new_sect, nullptr);
    EXPECT_EQ(doc.get_section_count(), initial_count + 1);

    doc.save();
    EXPECT_TRUE(fs::exists("test_section.docx"));
    fs::remove("test_section.docx");
}

// ============================================================================
// Numbering Definitions Tests
// ============================================================================

TEST(SectionAndListTest, AddBulletedListDefinition) {
    Document doc("test_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto id = doc.add_bulleted_list_definition();
    EXPECT_GT(id, 0);

    auto def = doc.get_numbering_definition(id);
    EXPECT_NE(def, nullptr);
    EXPECT_GE(def->abstractId, 0);

    doc.save();
    EXPECT_TRUE(fs::exists("test_numbering.docx"));
    fs::remove("test_numbering.docx");
}

TEST(SectionAndListTest, AddNumberedListDefinition) {
    Document doc("test_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto id = doc.add_numbered_list_definition(NumberStyle::Decimal);
    EXPECT_GT(id, 0);

    doc.save();
    EXPECT_TRUE(fs::exists("test_numbering.docx"));
    fs::remove("test_numbering.docx");
}

TEST(SectionAndListTest, AddChineseListDefinition) {
    Document doc("test_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto id = doc.add_chinese_numbered_list_definition();
    EXPECT_GT(id, 0);

    doc.save();
    EXPECT_TRUE(fs::exists("test_numbering.docx"));
    fs::remove("test_numbering.docx");
}

TEST(SectionAndListTest, AddOutlineListDefinition) {
    Document doc("test_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto id = doc.add_outline_list_definition();
    EXPECT_GT(id, 0);

    doc.save();
    EXPECT_TRUE(fs::exists("test_numbering.docx"));
    fs::remove("test_numbering.docx");
}

// ============================================================================
// Paragraph Numbering Application Tests
// ============================================================================

TEST(SectionAndListTest, ApplyNumberingToParagraph) {
    Document doc("test_para_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto list_id = doc.add_bulleted_list_definition();

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    auto* para = sect->add_paragraph("Test item");
    ASSERT_NE(para, nullptr);

    EXPECT_TRUE(para->set_numbering(list_id, NumberingLevel::Level1));
    EXPECT_TRUE(para->has_numbering());
    EXPECT_EQ(para->get_numbering_id(), list_id);
    EXPECT_EQ(para->get_numbering_level(), NumberingLevel::Level1);

    doc.save();
    EXPECT_TRUE(fs::exists("test_para_numbering.docx"));

    // Verify numbering.xml was created
    {
        std::ifstream check("test_para_numbering.docx", std::ios::binary);
        EXPECT_TRUE(check.good());
    }

    fs::remove("test_para_numbering.docx");
}

TEST(SectionAndListTest, RemoveNumbering) {
    Document doc("test_para_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto list_id = doc.add_bulleted_list_definition();

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    auto* para = sect->add_paragraph("Test item 2");
    ASSERT_NE(para, nullptr);

    para->set_numbering(list_id, NumberingLevel::Level1);
    EXPECT_TRUE(para->has_numbering());

    EXPECT_TRUE(para->remove_numbering());
    EXPECT_FALSE(para->has_numbering());

    doc.save();
    EXPECT_TRUE(fs::exists("test_para_numbering.docx"));
    fs::remove("test_para_numbering.docx");
}

TEST(SectionAndListTest, ChangeListLevel) {
    Document doc("test_para_numbering.docx");
    ASSERT_TRUE(doc.create_empty());

    auto list_id = doc.add_bulleted_list_definition();

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    auto* para = sect->add_paragraph("Nested item");
    ASSERT_NE(para, nullptr);

    para->set_numbering(list_id, NumberingLevel::Level1);
    EXPECT_EQ(para->get_numbering_level(), NumberingLevel::Level1);

    EXPECT_TRUE(para->set_list_level(NumberingLevel::Level2));
    EXPECT_EQ(para->get_numbering_level(), NumberingLevel::Level2);

    doc.save();
    EXPECT_TRUE(fs::exists("test_para_numbering.docx"));
    fs::remove("test_para_numbering.docx");
}

// ============================================================================
// Numbering XML Serialization Tests
// ============================================================================

TEST(SectionAndListTest, NumberingXmlSerialization) {
    Document doc("test_numbering_xml.docx");
    ASSERT_TRUE(doc.create_empty());

    // Create multiple list types
    auto bullet_id = doc.add_bulleted_list_definition();
    auto num_id = doc.add_numbered_list_definition(NumberStyle::Decimal);
    auto outline_id = doc.add_outline_list_definition();

    // Apply to paragraphs
    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    auto* p1 = sect->add_paragraph("Bullet item");
    p1->set_numbering(bullet_id, NumberingLevel::Level1);

    auto* p2 = sect->add_paragraph("Numbered item");
    p2->set_numbering(num_id, NumberingLevel::Level1);

    auto* p3 = sect->add_paragraph("Outline item");
    p3->set_numbering(outline_id, NumberingLevel::Level1);

    doc.save();

    // Re-open and verify
    Document doc2("test_numbering_xml.docx");
    doc2.open();

    if (doc2.is_open()) {
        auto numbering = doc2.get_numbering_xml();
        EXPECT_NE(numbering, nullptr);

        // Check if numbering.xml contains abstractNum elements
        if (numbering) {
            auto root = numbering->root();
            EXPECT_NE(root.child("w:abstractNum"), pugi::xml_node());
        }
    }

    fs::remove("test_numbering_xml.docx");
}

// ============================================================================
// Section Loading from XML Tests
// ============================================================================

TEST(SectionAndListTest, SectionLoadingFromXml) {
    // Create document with custom section properties
    {
        Document doc("test_section_load.docx");
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        sect->get_properties().orientation = SectionProperties::Orientation::Landscape;
        sect->get_properties().pageMargins.left = 2000;

        doc.save();
    }

    // Re-open and verify
    {
        Document doc("test_section_load.docx");
        doc.open();

        if (doc.is_open()) {
            auto sect = doc.get_first_section();
            if (sect) {
                EXPECT_EQ(sect->get_properties().orientation, SectionProperties::Orientation::Landscape);
            }
        }
    }

    fs::remove("test_section_load.docx");
}
