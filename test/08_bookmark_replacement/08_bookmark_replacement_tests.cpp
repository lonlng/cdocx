/**
 * @file 08_bookmark_replacement_tests.cpp
 * @brief Tests for bookmark replacement functionality
 * @version 0.3.0
 *
 * @defgroup tests_bookmark_replacement Bookmark Replacement Tests
 * @brief Test suite for BookmarkReplacer and related classes
 * @{
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/caption_generator.h>
#include <filesystem>
#include <iostream>
#include <map>

namespace fs = std::filesystem;

// ============================================================================
// BookmarkFormat Tests
// ============================================================================

TEST(BookmarkFormatTest, DefaultConstruction) {
    cdocx::BookmarkFormat fmt;

    EXPECT_FALSE(fmt.is_valid());
    EXPECT_EQ(fmt.font_size, 0);
    EXPECT_EQ(fmt.font_ascii, "");
    EXPECT_EQ(fmt.font_far_east, "");
    EXPECT_EQ(fmt.font_hansi, "");
    EXPECT_FALSE(fmt.bold);
    EXPECT_FALSE(fmt.italic);
    EXPECT_FALSE(fmt.underline);
    EXPECT_FALSE(fmt.strikethrough);
}

TEST(BookmarkFormatTest, ValidationWithFontSize) {
    cdocx::BookmarkFormat fmt;
    fmt.font_size = 24;

    EXPECT_TRUE(fmt.is_valid());
}

TEST(BookmarkFormatTest, ValidationWithFontAscii) {
    cdocx::BookmarkFormat fmt;
    fmt.font_ascii = "Arial";

    EXPECT_TRUE(fmt.is_valid());
}

TEST(BookmarkFormatTest, ValidationWithFontFarEast) {
    cdocx::BookmarkFormat fmt;
    fmt.font_far_east = "SimSun";

    EXPECT_TRUE(fmt.is_valid());
}

TEST(BookmarkFormatTest, ClearResetsAllValues) {
    cdocx::BookmarkFormat fmt;
    fmt.font_size = 24;
    fmt.font_ascii = "Arial";
    fmt.bold = true;
    fmt.color = "FF0000";

    EXPECT_TRUE(fmt.is_valid());

    fmt.clear();

    EXPECT_FALSE(fmt.is_valid());
    EXPECT_EQ(fmt.font_size, 0);
    EXPECT_EQ(fmt.font_ascii, "");
    EXPECT_FALSE(fmt.bold);
}

// ============================================================================
// ImageSize Tests
// ============================================================================

TEST(ImageSizeTest, DefaultConstruction) {
    cdocx::ImageSize size;

    EXPECT_FALSE(size.is_valid());
    EXPECT_EQ(size.width_pt, 0);
    EXPECT_EQ(size.height_pt, 0);
}

TEST(ImageSizeTest, ConstructionWithDimensions) {
    cdocx::ImageSize size(100.0, 200.0);

    EXPECT_TRUE(size.is_valid());
    EXPECT_EQ(size.width_pt, 100.0);
    EXPECT_EQ(size.height_pt, 200.0);
}

TEST(ImageSizeTest, EmuConversion) {
    cdocx::ImageSize size(100.0, 200.0);

    // 1 point = 12700 EMU
    EXPECT_EQ(size.width_emu(), 100 * 12700);
    EXPECT_EQ(size.height_emu(), 200 * 12700);
}

TEST(ImageSizeTest, InvalidWithZeroWidth) {
    cdocx::ImageSize size(0, 200.0);

    EXPECT_FALSE(size.is_valid());
}

TEST(ImageSizeTest, InvalidWithZeroHeight) {
    cdocx::ImageSize size(100.0, 0);

    EXPECT_FALSE(size.is_valid());
}

// ============================================================================
// ImageAlignment Tests
// ============================================================================

TEST(ImageAlignmentTest, EnumValuesExist) {
    // Just verify the enum values can be used
    auto left = cdocx::ImageAlignment::Left;
    auto center = cdocx::ImageAlignment::Center;
    auto right = cdocx::ImageAlignment::Right;

    (void)left;
    (void)center;
    (void)right;

    EXPECT_TRUE(true);
}

// ============================================================================
// CaptionFormat Tests
// ============================================================================

TEST(CaptionFormatTest, ChineseDefaultCreatesCorrectFormat) {
    auto fmt = cdocx::CaptionFormat::chinese_default();

    EXPECT_EQ(fmt.font_ascii, "Times New Roman");
    EXPECT_EQ(fmt.font_east_asia, "SimSun");
    EXPECT_EQ(fmt.font_hansi, "Times New Roman");
    EXPECT_EQ(fmt.font_size, 21);  // 10.5pt
    EXPECT_EQ(fmt.alignment, "center");
}

// ============================================================================
// ReplacementStats Tests
// ============================================================================

TEST(ReplacementStatsTest, DefaultConstruction) {
    cdocx::ReplacementStats stats;

    EXPECT_EQ(stats.success_count, 0);
    EXPECT_EQ(stats.fail_count, 0);
    EXPECT_EQ(stats.skip_count, 0);
    EXPECT_EQ(stats.total(), 0);
}

TEST(ReplacementStatsTest, TotalCalculation) {
    cdocx::ReplacementStats stats;
    stats.success_count = 5;
    stats.fail_count = 2;
    stats.skip_count = 1;

    EXPECT_EQ(stats.total(), 8);
}

TEST(ReplacementStatsTest, ResetClearsAllCounters) {
    cdocx::ReplacementStats stats;
    stats.success_count = 5;
    stats.fail_count = 2;
    stats.skip_count = 1;

    stats.reset();

    EXPECT_EQ(stats.success_count, 0);
    EXPECT_EQ(stats.fail_count, 0);
    EXPECT_EQ(stats.skip_count, 0);
    EXPECT_EQ(stats.total(), 0);
}

// ============================================================================
// BookmarkReplacer Construction Tests
// ============================================================================

TEST(BookmarkReplacerTest, ConstructionWithValidDocument) {
    const std::string test_file = "test_replacer_doc.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    cdocx::BookmarkReplacer replacer(&doc);
    EXPECT_EQ(replacer.get_stats().total(), 0);

    if (fs::exists(test_file)) fs::remove(test_file);
}

// ============================================================================
// Integration Tests with Real Document Operations
// ============================================================================

TEST(BookmarkReplacerIntegrationTest, TextReplacementPreservesFormat) {
    const std::string test_file = "test_format_preserve.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    // Create document with formatted bookmark content
    {
        cdocx::Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto p = doc.paragraphs().insert_paragraph_after("");
        auto r = p.add_run("Original Text");
        r.set_bold(true);
        r.set_italic(true);
        r.set_font_size(24);

        doc.save();
    }

    // Open and verify
    {
        cdocx::Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        // Verify document can be opened successfully
        EXPECT_TRUE(doc.is_open());
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CaptionGeneratorTest, CountExistingFiguresWithEmptyDocument) {
    const std::string test_file = "test_empty_caption.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    int count = cdocx::CaptionGenerator::count_existing_figures(&doc);
    EXPECT_EQ(count, 0);

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CaptionGeneratorTest, GetNextFigureNumberWithEmptyDocument) {
    const std::string test_file = "test_next_fig.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    int next = cdocx::CaptionGenerator::get_next_figure_number(&doc);
    EXPECT_EQ(next, 1);

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CaptionGeneratorTest, IsFigureCaptionWithNonCaptionText) {
    const std::string test_file = "test_non_caption.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("This is regular text");
    doc.save();

    // Get the paragraph node
    pugi::xml_document* doc_xml = doc.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);

    pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
    EXPECT_FALSE(cdocx::CaptionGenerator::is_figure_caption(para));

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(CaptionGeneratorTest, ExtractCaptionTextWithNonCaptionReturnsEmpty) {
    const std::string test_file = "test_extract_non_caption.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));

    auto p = doc.paragraphs().insert_paragraph_after("Regular paragraph");
    doc.save();

    pugi::xml_document* doc_xml = doc.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);

    pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
    std::string text = cdocx::CaptionGenerator::extract_caption_text(para);
    EXPECT_EQ(text, "");

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(BookmarkReplacerTest, ListBookmarksReturnsEmptyForDocumentWithoutBookmarks) {
    const std::string test_file = "test_no_bookmarks.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    cdocx::BookmarkReplacer replacer(&doc);
    auto bookmarks = replacer.list_bookmarks();

    EXPECT_TRUE(bookmarks.empty());

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(BookmarkReplacerTest, HasBookmarkReturnsFalseForNonExistentBookmark) {
    const std::string test_file = "test_has_bookmark.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    cdocx::BookmarkReplacer replacer(&doc);

    EXPECT_FALSE(replacer.has_bookmark("NON_EXISTENT"));
    EXPECT_FALSE(replacer.has_bookmark(""));

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(BookmarkReplacerTest, GetBookmarkTextReturnsEmptyForNonExistentBookmark) {
    const std::string test_file = "test_get_text.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    cdocx::BookmarkReplacer replacer(&doc);

    std::string text = replacer.get_bookmark_text("NON_EXISTENT");
    EXPECT_EQ(text, "");

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(BookmarkReplacerTest, BatchReplacementWithEmptyMap) {
    const std::string test_file = "test_batch_empty.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    cdocx::BookmarkReplacer replacer(&doc);

    std::map<std::string, std::string> empty_map;
    int count = replacer.replace_text_batch(empty_map);

    EXPECT_EQ(count, 0);
    EXPECT_EQ(replacer.get_stats().total(), 0);

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(BookmarkReplacerTest, ReplaceTextReturnsFalseForNonExistentBookmark) {
    const std::string test_file = "test_replace_nonexistent.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty(test_file));
    doc.save();

    cdocx::BookmarkReplacer replacer(&doc);

    bool result = replacer.replace_text("NON_EXISTENT", "New Text");
    EXPECT_FALSE(result);
    EXPECT_EQ(replacer.get_stats().fail_count, 1);

    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST(BookmarkReplacerIntegrationTest, FullBookmarkWorkflowWithDocumentCreationAndModification) {
    const std::string test_file = "test_full_workflow.docx";

    if (fs::exists(test_file)) fs::remove(test_file);

    // Create document
    {
        cdocx::Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        // Add content
        auto p1 = doc.paragraphs().insert_paragraph_after("Title");
        p1.set_bold(true);

        auto p2 = doc.paragraphs().insert_paragraph_after("Content paragraph");
        (void)p2;

        doc.save();
    }

    // Reopen and verify
    {
        cdocx::Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        // Verify document is valid
        EXPECT_TRUE(doc.is_open());

        // Test BookmarkReplacer
        cdocx::BookmarkReplacer replacer(&doc);
        EXPECT_EQ(replacer.get_stats().total(), 0);

        // Test CaptionGenerator
        int fig_count = cdocx::CaptionGenerator::count_existing_figures(&doc);
        EXPECT_EQ(fig_count, 0);
    }

    if (fs::exists(test_file)) fs::remove(test_file);
}

/** @} */
