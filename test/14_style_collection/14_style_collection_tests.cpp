#include <gtest/gtest.h>
#include <cdocx.h>
#include <cstring>
#include <filesystem>

namespace fs = std::filesystem;

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
    if (fs::exists("test_styles.docx")) fs::remove("test_styles.docx");
}

TEST(StyleCollectionTest, GetByIdentifierNormal) {
    cdocx::Document doc("test_style_id.docx");
    ASSERT_TRUE(doc.create_empty());

    auto& styles = doc.styles();
    auto normal = styles.get_by_identifier(cdocx::StyleIdentifier::Normal);
    ASSERT_NE(normal, nullptr);
    EXPECT_EQ(normal->get_name(), "Normal");

    doc.close();
    if (fs::exists("test_style_id.docx")) fs::remove("test_style_id.docx");
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
    if (fs::exists("test_remove_style.docx")) fs::remove("test_remove_style.docx");
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
    if (fs::exists("test_style_xml.docx")) fs::remove("test_style_xml.docx");
}
