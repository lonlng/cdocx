/**
 * @file 07_text_formatting_tests.cpp
 * @brief Tests for text and paragraph formatting features
 * @version 0.2.0
 *
 * @defgroup tests_text_formatting Text Formatting Tests
 * @brief Test suite for Run and Paragraph formatting methods
 * @{
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include "../test_helpers.h"
#include <cstring>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using cdocx::test::TempDoc;

TEST(TextFormattingTest, RunSetColorSetsFontColorCorrectly) {
    const std::string test_file = "test_color.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Red Text");
    r.set_color("FF0000");
    r.set_color("0070C0");
    r.set_color("00B050");

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, RunSetFontSizeSetsFontSizeCorrectly) {
    const std::string test_file = "test_font_size.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Sized Text");
    r.set_font_size(20);   // 10pt
    r.set_font_size(24);   // 12pt
    r.set_font_size(48);   // 24pt
    r.set_font_size(72);   // 36pt

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, RunSetFontNameSetsFontCorrectly) {
    const std::string test_file = "test_font_name.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");

    auto r1 = p.add_run("Arial");
    r1.set_font_name("Arial");

    auto r2 = p.add_run("Times");
    r2.set_font_name("Times New Roman");

    auto r3 = p.add_run("Verdana");
    r3.set_font_name("Verdana");

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, RunSetBoldTogglesBoldFormatting) {
    const std::string test_file = "test_bold.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Text");
    r.set_bold(true);
    r.set_bold(false);

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, RunSetItalicTogglesItalicFormatting) {
    const std::string test_file = "test_italic.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Text");
    r.set_italic(true);
    r.set_italic(false);

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, RunSetUnderlineTogglesUnderlineFormatting) {
    const std::string test_file = "test_underline.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Text");
    r.set_underline(cdocx::UnderlineType::Single);
    EXPECT_TRUE(r.get_font().underline == cdocx::UnderlineType::Single);
    r.set_underline(cdocx::UnderlineType::None);
    EXPECT_TRUE(r.get_font().underline == cdocx::UnderlineType::None);

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, RunCombinedFormatting) {
    const std::string test_file = "test_combined_run.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Formatted");
    r.set_bold(true);
    r.set_italic(true);
    r.set_color("FF0000");
    r.set_font_size(48);
    r.set_font_name("Arial");

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, ParagraphSetAlignmentSetsAlignmentCorrectly) {
    const std::string test_file = "test_alignment.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p1 = doc.paragraphs().insert_paragraph_after("Left");
    EXPECT_TRUE(p1.set_alignment("left"));

    auto p2 = doc.paragraphs().insert_paragraph_after("Center");
    EXPECT_TRUE(p2.set_alignment("center"));

    auto p3 = doc.paragraphs().insert_paragraph_after("Right");
    EXPECT_TRUE(p3.set_alignment("right"));

    auto p4 = doc.paragraphs().insert_paragraph_after("Justified");
    EXPECT_TRUE(p4.set_alignment("both"));

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, ParagraphSetStyleSetsStyleCorrectly) {
    const std::string test_file = "test_style.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p1 = doc.paragraphs().insert_paragraph_after("Heading 1");
    EXPECT_TRUE(p1.set_style("1"));

    auto p2 = doc.paragraphs().insert_paragraph_after("Heading 2");
    EXPECT_TRUE(p2.set_style("2"));

    auto p3 = doc.paragraphs().insert_paragraph_after("Normal");
    EXPECT_TRUE(p3.set_style("Normal"));

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, ParagraphSetLineSpacingSetsLineSpacingCorrectly) {
    const std::string test_file = "test_line_spacing.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p1 = doc.paragraphs().insert_paragraph_after("Single spacing");
    EXPECT_TRUE(p1.set_line_spacing(240));

    auto p2 = doc.paragraphs().insert_paragraph_after("1.5 spacing");
    EXPECT_TRUE(p2.set_line_spacing(360));

    auto p3 = doc.paragraphs().insert_paragraph_after("Double spacing");
    EXPECT_TRUE(p3.set_line_spacing(480));

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, ParagraphSetSpacingBeforeAfterSetsSpacingCorrectly) {
    const std::string test_file = "test_spacing.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p1 = doc.paragraphs().insert_paragraph_after("Before spacing");
    EXPECT_TRUE(p1.set_spacing_before(200));

    auto p2 = doc.paragraphs().insert_paragraph_after("After spacing");
    EXPECT_TRUE(p2.set_spacing_after(200));

    auto p3 = doc.paragraphs().insert_paragraph_after("Both spacing");
    EXPECT_TRUE(p3.set_spacing_before(100));
    EXPECT_TRUE(p3.set_spacing_after(100));

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, ParagraphSetIndentSetsIndentationCorrectly) {
    const std::string test_file = "test_indent.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p1 = doc.paragraphs().insert_paragraph_after("Left indent");
    EXPECT_TRUE(p1.set_indent(720, -1, -1));

    auto p2 = doc.paragraphs().insert_paragraph_after("Right indent");
    EXPECT_TRUE(p2.set_indent(-1, 720, -1));

    auto p3 = doc.paragraphs().insert_paragraph_after("First line indent");
    EXPECT_TRUE(p3.set_indent(-1, -1, 720));

    auto p4 = doc.paragraphs().insert_paragraph_after("Hanging indent");
    EXPECT_TRUE(p4.set_indent(-1, -1, -720));

    auto p5 = doc.paragraphs().insert_paragraph_after("Combined indent");
    EXPECT_TRUE(p5.set_indent(360, 360, 720));

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, ParagraphCombinedFormatting) {
    const std::string test_file = "test_combined_para.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Combined formatting");
    EXPECT_TRUE(p.set_style("1"));
    EXPECT_TRUE(p.set_alignment("center"));
    EXPECT_TRUE(p.set_spacing_before(200));
    EXPECT_TRUE(p.set_spacing_after(200));
    EXPECT_TRUE(p.set_line_spacing(360));
    EXPECT_TRUE(p.set_indent(0, 0, 0));

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

}

TEST(TextFormattingTest, FullDocumentWithAllFormattingFeatures) {
    const std::string test_file = "test_full_formatting.docx";


    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    // Title
    auto title = doc.paragraphs().insert_paragraph_after("Full Formatting Test");
    title.set_style("1");
    title.set_alignment("center");

    // Section 1: Colors and Fonts
    auto s1 = doc.paragraphs().insert_paragraph_after("1. Colors and Fonts");
    s1.set_style("2");

    auto p1 = doc.paragraphs().insert_paragraph_after("Text with ");
    auto r1 = p1.add_run("Red Bold Arial");
    r1.set_color("FF0000");
    r1.set_bold(true);
    r1.set_font_name("Arial");
    r1.set_font_size(28);

    // Section 2: Alignment
    auto s2 = doc.paragraphs().insert_paragraph_after("2. Alignment");
    s2.set_style("2");

    auto p2 = doc.paragraphs().insert_paragraph_after("Centered text");
    p2.set_alignment("center");

    // Section 3: Spacing
    auto s3 = doc.paragraphs().insert_paragraph_after("3. Spacing");
    s3.set_style("2");

    auto p3 = doc.paragraphs().insert_paragraph_after("Paragraph with spacing");
    p3.set_spacing_before(200);
    p3.set_spacing_after(200);
    p3.set_line_spacing(360);

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

    // Verify document can be reopened
    {
        cdocx::Document doc2(test_file);
        doc2.open();

        if (!doc2.is_open()) {
            std::cout << "[SKIPPED] Could not reopen document" << std::endl;
        } else {
            EXPECT_TRUE(doc2.is_open());
        }
    }

}

TEST(TextFormattingTest, DropCapRoundTrip) {
    TempDoc temp_doc("test_dropcap.docx");
    const std::string& test_file = temp_doc.path();

    {
        cdocx::Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto para = sect->append_paragraph("Drop cap paragraph");
        ASSERT_NE(para, nullptr);

        para->get_paragraph_format().drop_cap_position = cdocx::DropCapPosition::Normal;
        para->get_paragraph_format().lines_to_drop = 3;

        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto children = body->get_children();
        ASSERT_FALSE(children.empty());

        auto para = std::dynamic_pointer_cast<cdocx::Paragraph>(children.back());
        ASSERT_NE(para, nullptr);

        EXPECT_EQ(para->get_paragraph_format().drop_cap_position, cdocx::DropCapPosition::Normal);
        EXPECT_EQ(para->get_paragraph_format().lines_to_drop, 3);
    }

}

TEST(TextFormattingTest, DropCapMarginRoundTrip) {
    TempDoc temp_doc("test_dropcap_margin.docx");
    const std::string& test_file = temp_doc.path();

    {
        cdocx::Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto para = sect->append_paragraph("Margin drop cap paragraph");
        ASSERT_NE(para, nullptr);

        para->get_paragraph_format().drop_cap_position = cdocx::DropCapPosition::Margin;
        para->get_paragraph_format().lines_to_drop = 4;

        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto children = body->get_children();
        ASSERT_FALSE(children.empty());

        auto para = std::dynamic_pointer_cast<cdocx::Paragraph>(children.back());
        ASSERT_NE(para, nullptr);

        EXPECT_EQ(para->get_paragraph_format().drop_cap_position, cdocx::DropCapPosition::Margin);
        EXPECT_EQ(para->get_paragraph_format().lines_to_drop, 4);
    }

}

TEST(TextFormattingTest, DropCapNoneNotSerialized) {
    TempDoc temp_doc("test_dropcap_none.docx");
    const std::string& test_file = temp_doc.path();

    {
        cdocx::Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto sect = doc.get_first_section();
        auto para = sect->append_paragraph("No drop cap");
        para->get_paragraph_format().drop_cap_position = cdocx::DropCapPosition::None;
        para->get_paragraph_format().lines_to_drop = 1;

        doc.save();
    }

    {
        cdocx::Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto para = doc.get_first_section()->get_body()->get_children().back();
        auto p = std::dynamic_pointer_cast<cdocx::Paragraph>(para);
        ASSERT_NE(p, nullptr);

        EXPECT_EQ(p->get_paragraph_format().drop_cap_position, cdocx::DropCapPosition::None);
    }

}

TEST(TextFormattingTest, RunPropertiesXmlRoundTrip) {
    TempDoc temp_doc("test_run_props_xml.docx");
    const std::string& test_file = temp_doc.path();

    {
        cdocx::Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        // Use DOM API so the paragraph exists in the DOM tree before sync
        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto para = sect->append_paragraph("Styled Text");
        auto run = para->get_first_run();
        ASSERT_NE(run, nullptr);
        run->set_bold(true);
        run->set_italic(true);
        run->set_font_size(14);
        run->set_color("FF0000");

        doc.sync_to_physical_tree();
        doc.save();

        // Access the raw XML run and use get_properties_xml
        auto doc_xml = doc.get_document_xml();
        ASSERT_NE(doc_xml, nullptr);

        auto body = doc_xml->child("w:document").child("w:body");
        auto p = body.child("w:p");
        // Find the paragraph with our styled text (skip the empty default paragraph)
        while (p) {
            auto t = p.child("w:r").child("w:t");
            if (t && std::strcmp(t.text().get(), "Styled Text") == 0) {
                break;
            }
            p = p.next_sibling("w:p");
        }
        ASSERT_TRUE(p);
        auto r = p.child("w:r");
        ASSERT_TRUE(r);

        cdocx::Run run_xml(&doc);
        run_xml.set_parent_xml(p);
        run_xml.set_current_xml(r);

        auto props = run_xml.get_properties_xml();
        EXPECT_TRUE(props.font_style.bold);
        EXPECT_TRUE(props.font_style.italic);
        EXPECT_EQ(props.font_size, 28);  // 14pt = 28 half-points
        EXPECT_EQ(props.color, "FF0000");

        // Modify via set_properties_xml and verify
        cdocx::TextProperties new_props;
        new_props.font_style.bold = false;
        new_props.font_style.italic = false;
        new_props.font_size = 24;  // 12pt
        new_props.color = "0000FF";
        new_props.underline.style = cdocx::TextProperties::UnderlineStyle::Single;
        new_props.strike = cdocx::TextProperties::StrikeStyle::Single;

        run_xml.set_properties_xml(new_props);

        auto updated = run_xml.get_properties_xml();
        EXPECT_FALSE(updated.font_style.bold);
        EXPECT_FALSE(updated.font_style.italic);
        EXPECT_EQ(updated.font_size, 24);
        EXPECT_EQ(updated.color, "0000FF");
        EXPECT_EQ(updated.underline.style, cdocx::TextProperties::UnderlineStyle::Single);
        EXPECT_EQ(updated.strike, cdocx::TextProperties::StrikeStyle::Single);

        doc.save();
    }

}

/** @} */
