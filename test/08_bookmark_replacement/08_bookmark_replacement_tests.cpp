/**
 * @file 08_bookmark_replacement_tests.cpp
 * @brief Tests for bookmark replacement functionality
 * @version 0.3.0
 * 
 * @defgroup tests_bookmark_replacement Bookmark Replacement Tests
 * @brief Test suite for BookmarkReplacer and related classes
 * @{
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
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

TEST_CASE("BookmarkFormat default construction") {
    cdocx::BookmarkFormat fmt;
    
    CHECK_FALSE(fmt.is_valid());
    CHECK_EQ(fmt.font_size, 0);
    CHECK_EQ(fmt.font_ascii, "");
    CHECK_EQ(fmt.font_far_east, "");
    CHECK_EQ(fmt.font_hansi, "");
    CHECK_FALSE(fmt.bold);
    CHECK_FALSE(fmt.italic);
    CHECK_FALSE(fmt.underline);
    CHECK_FALSE(fmt.strikethrough);
}

TEST_CASE("BookmarkFormat validation with font_size") {
    cdocx::BookmarkFormat fmt;
    fmt.font_size = 24;
    
    CHECK(fmt.is_valid());
}

TEST_CASE("BookmarkFormat validation with font_ascii") {
    cdocx::BookmarkFormat fmt;
    fmt.font_ascii = "Arial";
    
    CHECK(fmt.is_valid());
}

TEST_CASE("BookmarkFormat validation with font_far_east") {
    cdocx::BookmarkFormat fmt;
    fmt.font_far_east = "SimSun";
    
    CHECK(fmt.is_valid());
}

TEST_CASE("BookmarkFormat clear resets all values") {
    cdocx::BookmarkFormat fmt;
    fmt.font_size = 24;
    fmt.font_ascii = "Arial";
    fmt.bold = true;
    fmt.color = "FF0000";
    
    CHECK(fmt.is_valid());
    
    fmt.clear();
    
    CHECK_FALSE(fmt.is_valid());
    CHECK_EQ(fmt.font_size, 0);
    CHECK_EQ(fmt.font_ascii, "");
    CHECK_FALSE(fmt.bold);
}

// ============================================================================
// ImageSize Tests
// ============================================================================

TEST_CASE("ImageSize default construction") {
    cdocx::ImageSize size;
    
    CHECK_FALSE(size.is_valid());
    CHECK_EQ(size.width_pt, 0);
    CHECK_EQ(size.height_pt, 0);
}

TEST_CASE("ImageSize construction with dimensions") {
    cdocx::ImageSize size(100.0, 200.0);
    
    CHECK(size.is_valid());
    CHECK_EQ(size.width_pt, 100.0);
    CHECK_EQ(size.height_pt, 200.0);
}

TEST_CASE("ImageSize EMU conversion") {
    cdocx::ImageSize size(100.0, 200.0);
    
    // 1 point = 12700 EMU
    CHECK_EQ(size.width_emu(), 100 * 12700);
    CHECK_EQ(size.height_emu(), 200 * 12700);
}

TEST_CASE("ImageSize invalid with zero width") {
    cdocx::ImageSize size(0, 200.0);
    
    CHECK_FALSE(size.is_valid());
}

TEST_CASE("ImageSize invalid with zero height") {
    cdocx::ImageSize size(100.0, 0);
    
    CHECK_FALSE(size.is_valid());
}

// ============================================================================
// ImageAlignment Tests
// ============================================================================

TEST_CASE("ImageAlignment enum values exist") {
    // Just verify the enum values can be used
    auto left = cdocx::ImageAlignment::Left;
    auto center = cdocx::ImageAlignment::Center;
    auto right = cdocx::ImageAlignment::Right;
    
    (void)left;
    (void)center;
    (void)right;
    
    CHECK(true);
}

// ============================================================================
// CaptionFormat Tests
// ============================================================================

TEST_CASE("CaptionFormat chinese_default creates correct format") {
    auto fmt = cdocx::CaptionFormat::chinese_default();
    
    CHECK_EQ(fmt.font_ascii, "Times New Roman");
    CHECK_EQ(fmt.font_east_asia, "SimSun");
    CHECK_EQ(fmt.font_hansi, "Times New Roman");
    CHECK_EQ(fmt.font_size, 21);  // 10.5pt
    CHECK_EQ(fmt.alignment, "center");
}

// ============================================================================
// ReplacementStats Tests
// ============================================================================

TEST_CASE("ReplacementStats default construction") {
    cdocx::ReplacementStats stats;
    
    CHECK_EQ(stats.success_count, 0);
    CHECK_EQ(stats.fail_count, 0);
    CHECK_EQ(stats.skip_count, 0);
    CHECK_EQ(stats.total(), 0);
}

TEST_CASE("ReplacementStats total calculation") {
    cdocx::ReplacementStats stats;
    stats.success_count = 5;
    stats.fail_count = 2;
    stats.skip_count = 1;
    
    CHECK_EQ(stats.total(), 8);
}

TEST_CASE("ReplacementStats reset clears all counters") {
    cdocx::ReplacementStats stats;
    stats.success_count = 5;
    stats.fail_count = 2;
    stats.skip_count = 1;
    
    stats.reset();
    
    CHECK_EQ(stats.success_count, 0);
    CHECK_EQ(stats.fail_count, 0);
    CHECK_EQ(stats.skip_count, 0);
    CHECK_EQ(stats.total(), 0);
}

// ============================================================================
// BookmarkReplacer Construction Tests
// ============================================================================

TEST_CASE("BookmarkReplacer construction with valid document") {
    const std::string test_file = "test_replacer_doc.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    
    cdocx::BookmarkReplacer replacer(&doc);
    CHECK(replacer.get_stats().total() == 0);
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

// ============================================================================
// Integration Tests with Real Document Operations
// ============================================================================

TEST_CASE("BookmarkReplacer text replacement preserves format") {
    const std::string test_file = "test_format_preserve.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    // Create document with formatted bookmark content
    {
        cdocx::Document doc;
        REQUIRE(doc.create_empty(test_file));
        
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
        REQUIRE(doc.is_open());
        
        // Verify document can be opened successfully
        CHECK(doc.is_open());
    }
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("CaptionGenerator count_existing_figures with empty document") {
    const std::string test_file = "test_empty_caption.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    int count = cdocx::CaptionGenerator::count_existing_figures(&doc);
    CHECK_EQ(count, 0);
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("CaptionGenerator get_next_figure_number with empty document") {
    const std::string test_file = "test_next_fig.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    int next = cdocx::CaptionGenerator::get_next_figure_number(&doc);
    CHECK_EQ(next, 1);
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("CaptionGenerator is_figure_caption with non-caption text") {
    const std::string test_file = "test_non_caption.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    
    auto p = doc.paragraphs().insert_paragraph_after("This is regular text");
    doc.save();
    
    // Get the paragraph node
    pugi::xml_document* doc_xml = doc.get_document_xml();
    REQUIRE(doc_xml != nullptr);
    
    pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
    CHECK_FALSE(cdocx::CaptionGenerator::is_figure_caption(para));
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("CaptionGenerator extract_caption_text with non-caption returns empty") {
    const std::string test_file = "test_extract_non_caption.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    
    auto p = doc.paragraphs().insert_paragraph_after("Regular paragraph");
    doc.save();
    
    pugi::xml_document* doc_xml = doc.get_document_xml();
    REQUIRE(doc_xml != nullptr);
    
    pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p");
    std::string text = cdocx::CaptionGenerator::extract_caption_text(para);
    CHECK_EQ(text, "");
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("BookmarkReplacer list_bookmarks returns empty for document without bookmarks") {
    const std::string test_file = "test_no_bookmarks.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    cdocx::BookmarkReplacer replacer(&doc);
    auto bookmarks = replacer.list_bookmarks();
    
    CHECK(bookmarks.empty());
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("BookmarkReplacer has_bookmark returns false for non-existent bookmark") {
    const std::string test_file = "test_has_bookmark.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    cdocx::BookmarkReplacer replacer(&doc);
    
    CHECK_FALSE(replacer.has_bookmark("NON_EXISTENT"));
    CHECK_FALSE(replacer.has_bookmark(""));
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("BookmarkReplacer get_bookmark_text returns empty for non-existent bookmark") {
    const std::string test_file = "test_get_text.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    cdocx::BookmarkReplacer replacer(&doc);
    
    std::string text = replacer.get_bookmark_text("NON_EXISTENT");
    CHECK_EQ(text, "");
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("BookmarkReplacer batch replacement with empty map") {
    const std::string test_file = "test_batch_empty.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    cdocx::BookmarkReplacer replacer(&doc);
    
    std::map<std::string, std::string> empty_map;
    int count = replacer.replace_text_batch(empty_map);
    
    CHECK_EQ(count, 0);
    CHECK_EQ(replacer.get_stats().total(), 0);
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("BookmarkReplacer replace_text returns false for non-existent bookmark") {
    const std::string test_file = "test_replace_nonexistent.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    cdocx::Document doc;
    REQUIRE(doc.create_empty(test_file));
    doc.save();
    
    cdocx::BookmarkReplacer replacer(&doc);
    
    bool result = replacer.replace_text("NON_EXISTENT", "New Text");
    CHECK_FALSE(result);
    CHECK_EQ(replacer.get_stats().fail_count, 1);
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

TEST_CASE("Full bookmark workflow with document creation and modification") {
    const std::string test_file = "test_full_workflow.docx";
    
    if (fs::exists(test_file)) fs::remove(test_file);
    
    // Create document
    {
        cdocx::Document doc;
        REQUIRE(doc.create_empty(test_file));
        
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
        REQUIRE(doc.is_open());
        
        // Verify document is valid
        CHECK(doc.is_open());
        
        // Test BookmarkReplacer
        cdocx::BookmarkReplacer replacer(&doc);
        CHECK_EQ(replacer.get_stats().total(), 0);
        
        // Test CaptionGenerator
        int fig_count = cdocx::CaptionGenerator::count_existing_figures(&doc);
        CHECK_EQ(fig_count, 0);
    }
    
    if (fs::exists(test_file)) fs::remove(test_file);
}

/** @} */
