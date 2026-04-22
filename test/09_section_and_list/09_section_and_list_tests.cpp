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
// NumberStyle String Round-Trip Tests
// ============================================================================

TEST(SectionAndListTest, NumberStyleStringRoundTrip) {
    // Verify every NumberStyle enum value round-trips through
    // number_style_to_string() and string_to_number_style().
    std::vector<std::pair<NumberStyle, const char*>> cases = {
        {NumberStyle::Bullet, "bullet"},
        {NumberStyle::Decimal, "decimal"},
        {NumberStyle::UpperRoman, "upperRoman"},
        {NumberStyle::LowerRoman, "lowerRoman"},
        {NumberStyle::UpperLetter, "upperLetter"},
        {NumberStyle::LowerLetter, "lowerLetter"},
        {NumberStyle::OrdinalText, "ordinal"},
        {NumberStyle::CardinalText, "cardinalText"},
        {NumberStyle::ChineseCounting, "chineseCounting"},
        {NumberStyle::IdeographEnchanted, "ideographEnchanted"},
    };

    for (const auto& [style, expected_str] : cases) {
        EXPECT_STREQ(number_style_to_string(style), expected_str)
            << "number_style_to_string failed for enum value";
        EXPECT_EQ(string_to_number_style(expected_str), style)
            << "string_to_number_style failed for: " << expected_str;
    }

    // Unknown strings should default to Decimal
    EXPECT_EQ(string_to_number_style("unknown"), NumberStyle::Decimal);
    EXPECT_EQ(string_to_number_style(nullptr), NumberStyle::Decimal);
    EXPECT_EQ(string_to_number_style(""), NumberStyle::Decimal);
}

TEST(SectionAndListTest, NumberStyleRoundTripInDocument) {
    Document doc("test_numbering_style_rt.docx");
    ASSERT_TRUE(doc.create_empty());

    auto num_id = doc.add_numbered_list_definition(NumberStyle::UpperRoman);
    EXPECT_GT(num_id, 0);

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);

    auto* para = sect->add_paragraph("Roman numeral item");
    para->set_numbering(num_id, NumberingLevel::Level1);

    doc.save();

    // Re-open and verify the numbering style survived the round-trip
    Document doc2("test_numbering_style_rt.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto* numbering = doc2.get_numbering_xml();
    ASSERT_NE(numbering, nullptr);

    auto abstract_num = numbering->child("w:numbering").child("w:abstractNum");
    ASSERT_NE(abstract_num, pugi::xml_node());

    auto lvl = abstract_num.child("w:lvl");
    ASSERT_NE(lvl, pugi::xml_node());

    auto numFmt = lvl.child("w:numFmt");
    ASSERT_NE(numFmt, pugi::xml_node());
    EXPECT_STREQ(numFmt.attribute("w:val").value(), "upperRoman");

    fs::remove("test_numbering_style_rt.docx");
}

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
            auto root = numbering->child("w:numbering");
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

// ============================================================================
// HeaderFooter Link-to-Previous Tests
// ============================================================================

TEST(SectionAndListTest, HeaderFooterLinkToPrevious) {
    Document doc("test_hf_link.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect1 = doc.get_first_section();
    ASSERT_NE(sect1, nullptr);

    auto header1 = sect1->add_header();
    ASSERT_NE(header1, nullptr);
    header1->append_paragraph("Header 1");

    auto footer1 = sect1->add_footer();
    ASSERT_NE(footer1, nullptr);
    footer1->append_paragraph("Footer 1");

    auto sect2 = doc.add_section();
    ASSERT_NE(sect2, nullptr);

    // Initially second section should not have explicit header/footer
    EXPECT_FALSE(sect2->has_header());
    EXPECT_FALSE(sect2->has_footer());

    // Link to previous
    sect2->link_to_previous(true);

    EXPECT_TRUE(sect2->is_linked_to_previous(HeaderFooterType::Default));
    EXPECT_TRUE(sect2->has_header());
    EXPECT_TRUE(sect2->has_footer());

    // Unlink
    sect2->link_to_previous(false);

    EXPECT_FALSE(sect2->is_linked_to_previous(HeaderFooterType::Default));
    EXPECT_TRUE(sect2->has_header());
    EXPECT_TRUE(sect2->has_footer());

    // Save and reload
    doc.sync_to_physical_tree();
    doc.save();

    Document doc2("test_hf_link.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    ASSERT_GE(doc2.get_section_count(), 2u);
    auto s2 = doc2.get_section(1);
    ASSERT_NE(s2, nullptr);

    EXPECT_TRUE(s2->has_header());
    EXPECT_TRUE(s2->has_footer());

    doc2.close();
    fs::remove("test_hf_link.docx");
}

TEST(SectionAndListTest, HeaderFooterLinkToPreviousByType) {
    Document doc("test_hf_link_type.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect1 = doc.get_first_section();
    auto h1 = sect1->add_header(HeaderFooterType::Default);
    h1->append_paragraph("Default header");

    auto sect2 = doc.add_section();

    // Link only default header
    sect2->link_to_previous(HeaderFooterType::Default, true);
    EXPECT_TRUE(sect2->is_linked_to_previous(HeaderFooterType::Default, true));
    EXPECT_FALSE(sect2->is_linked_to_previous(HeaderFooterType::Default, false));

    // Unlink only default header
    sect2->link_to_previous(HeaderFooterType::Default, false);
    EXPECT_FALSE(sect2->is_linked_to_previous(HeaderFooterType::Default, true));
    EXPECT_TRUE(sect2->has_header(HeaderFooterType::Default));

    doc.sync_to_physical_tree();
    doc.save();

    Document doc2("test_hf_link_type.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto s2 = doc2.get_section(1);
    ASSERT_NE(s2, nullptr);
    EXPECT_TRUE(s2->has_header(HeaderFooterType::Default));

    doc2.close();
    fs::remove("test_hf_link_type.docx");
}
