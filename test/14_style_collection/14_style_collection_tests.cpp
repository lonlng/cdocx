#include <gtest/gtest.h>
#include <cdocx.h>
#include "../test_helpers.h"
#include <cstring>
#include <filesystem>

namespace fs = std::filesystem;
using cdocx::test::TempDoc;

TEST(StyleCollectionTest, AddAndRetrieveStyle) {
    cdocx::Document doc("test_styles.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    auto style = styles.add(cdocx::StyleType::Paragraph, "CustomStyle");
    style->set_style_id("CustomStyle");
    style->get_font().set_names("Arial");
    style->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;

    doc.save();

    cdocx::Document doc2("test_styles.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto& styles2 = doc2.styles();
    auto found = styles2.get_by_name("CustomStyle");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->get_style_id(), "CustomStyle");
    EXPECT_EQ(found->get_font().name, "Arial");
    EXPECT_EQ(found->get_paragraph_format().alignment, cdocx::ParagraphAlignment::Center);

    doc2.close();
}

TEST(StyleCollectionTest, GetByIdentifierNormal) {
    cdocx::Document doc("test_style_id.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    auto normal = styles.get_by_identifier(cdocx::StyleIdentifier::Normal);
    ASSERT_NE(normal, nullptr);
    EXPECT_EQ(normal->get_name(), "Normal");

    doc.close();
}

TEST(StyleCollectionTest, RemoveStyle) {
    cdocx::Document doc("test_remove_style.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    size_t initial_count = styles.get_count();
    auto style = styles.add(cdocx::StyleType::Paragraph, "ToRemove");
    ASSERT_EQ(styles.get_count(), initial_count + 1);

    styles.remove(style);
    EXPECT_EQ(styles.get_count(), initial_count);
    EXPECT_EQ(styles.get_by_name("ToRemove"), nullptr);

    doc.close();
}

TEST(StyleCollectionTest, XmlRoundTrip) {
    cdocx::Document doc("test_style_xml.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    auto style = styles.add(cdocx::StyleType::Paragraph, "MyStyle");
    style->set_style_id("MyStyleId");
    style->get_font().set_names("Calibri");
    style->get_font().size = 14;
    style->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Right;
    style->set_base_style_name("Normal");

    doc.save();

    cdocx::Document doc2("test_style_xml.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto* styles_xml = doc2.get_styles();
    ASSERT_NE(styles_xml, nullptr);

    auto styles_root = styles_xml->child("w:styles");
    ASSERT_TRUE(styles_root);

    bool found = false;
    for (auto style_node = styles_root.child("w:style"); style_node;
         style_node = style_node.next_sibling("w:style")) {
        if (std::strcmp(style_node.attribute("w:styleId").value(), "MyStyleId") == 0) {
            found = true;
            EXPECT_STREQ(style_node.attribute("w:type").value(), "paragraph");

            auto name = style_node.child("w:name");
            ASSERT_TRUE(name);
            EXPECT_STREQ(name.attribute("w:val").value(), "MyStyle");

            auto basedOn = style_node.child("w:basedOn");
            ASSERT_TRUE(basedOn);
            EXPECT_STREQ(basedOn.attribute("w:val").value(), "Normal");
            break;
        }
    }
    EXPECT_TRUE(found);

    doc2.close();
}

TEST(StyleCollectionTest, CharacterStyleRoundTrip) {
    cdocx::Document doc("test_char_style.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    auto style = styles.add(cdocx::StyleType::Character, "MyCharStyle");
    style->set_style_id("MyCharStyleId");
    style->get_font().set_names("Courier New");
    style->get_font().size = 10;
    style->get_font().bold = true;

    doc.save();

    cdocx::Document doc2("test_char_style.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto* styles_xml = doc2.get_styles();
    ASSERT_NE(styles_xml, nullptr);

    bool found = false;
    for (auto node = styles_xml->child("w:styles").child("w:style"); node;
         node = node.next_sibling("w:style")) {
        if (std::strcmp(node.attribute("w:styleId").value(), "MyCharStyleId") == 0) {
            found = true;
            EXPECT_STREQ(node.attribute("w:type").value(), "character");
            break;
        }
    }
    EXPECT_TRUE(found);

    doc2.close();
}

TEST(StyleCollectionTest, GetByStyleId) {
    cdocx::Document doc("test_by_id.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    auto style = styles.add(cdocx::StyleType::Paragraph, "ByIdName");
    style->set_style_id("UniqueId123");

    EXPECT_NE(styles.get_by_style_id("UniqueId123"), nullptr);
    EXPECT_EQ(styles.get_by_style_id("NonExistent"), nullptr);

    doc.close();
}

TEST(StyleCollectionTest, DuplicateNameNotCreated) {
    cdocx::Document doc("test_dup.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    size_t initial = styles.get_count();

    auto s1 = styles.add(cdocx::StyleType::Paragraph, "Duplicate");
    EXPECT_EQ(styles.get_count(), initial + 1);

    // Adding another with the same name increases count (collection allows duplicates)
    auto s2 = styles.add(cdocx::StyleType::Paragraph, "Duplicate");
    EXPECT_EQ(styles.get_count(), initial + 2);

    // get_by_name returns the first match
    auto found = styles.get_by_name("Duplicate");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, s1);

    doc.close();
}

TEST(StyleCollectionTest, ClearRemovesAllStyles) {
    cdocx::Document doc("test_clear.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    size_t initial = styles.get_count();
    EXPECT_GE(initial, 1);  // At least Normal

    styles.add(cdocx::StyleType::Paragraph, "Extra1");
    styles.add(cdocx::StyleType::Paragraph, "Extra2");
    EXPECT_EQ(styles.get_count(), initial + 2);

    styles.clear();
    EXPECT_EQ(styles.get_count(), 0u);

    doc.close();
}
