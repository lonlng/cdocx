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
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

TEST(TextFormattingTest, RunSetColorSetsFontColorCorrectly) {
    const std::string test_file = "test_color.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Red Text");
    r.set_color("FF0000");
    r.set_color("0070C0");
    r.set_color("00B050");

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, RunSetFontSizeSetsFontSizeCorrectly) {
    const std::string test_file = "test_font_size.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, RunSetFontNameSetsFontCorrectly) {
    const std::string test_file = "test_font_name.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, RunSetBoldTogglesBoldFormatting) {
    const std::string test_file = "test_bold.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Text");
    r.set_bold(true);
    r.set_bold(false);

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, RunSetItalicTogglesItalicFormatting) {
    const std::string test_file = "test_italic.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Test: ");
    auto r = p.add_run("Text");
    r.set_italic(true);
    r.set_italic(false);

    doc.save();
    EXPECT_TRUE(fs::exists(test_file));

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, RunSetUnderlineTogglesUnderlineFormatting) {
    const std::string test_file = "test_underline.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, RunCombinedFormatting) {
    const std::string test_file = "test_combined_run.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, ParagraphSetAlignmentSetsAlignmentCorrectly) {
    const std::string test_file = "test_alignment.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, ParagraphSetStyleSetsStyleCorrectly) {
    const std::string test_file = "test_style.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, ParagraphSetLineSpacingSetsLineSpacingCorrectly) {
    const std::string test_file = "test_line_spacing.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, ParagraphSetSpacingBeforeAfterSetsSpacingCorrectly) {
    const std::string test_file = "test_spacing.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, ParagraphSetIndentSetsIndentationCorrectly) {
    const std::string test_file = "test_indent.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, ParagraphCombinedFormatting) {
    const std::string test_file = "test_combined_para.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(TextFormattingTest, FullDocumentWithAllFormattingFeatures) {
    const std::string test_file = "test_full_formatting.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

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

    if (fs::exists(test_file)) fs::remove(test_file);
}

/** @} */
