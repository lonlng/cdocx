/**
 * @file 12_document_search_tests.cpp
 * @brief Document search and replace unit tests
 * @version 0.8.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <cdocx/advanced.h>
#include "../test_helpers.h"
#include <filesystem>

using namespace cdocx;
namespace fs = std::filesystem;
using cdocx::test::TempDoc;

// ============================================================================
// DocumentSearch::find Tests
// ============================================================================

TEST(DocumentSearchTest, FindExistingText) {
    TempDoc temp_doc("test_find.docx");
    Document doc("test_find.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello, World!");
    body->append_paragraph("Second paragraph");

    auto range = DocumentSearch::find(doc, "World");
    ASSERT_TRUE(range.has_value());
    // Note: Range::is_valid() depends on XML node binding, which may not be
    // present for pure DOM paragraphs created via append_paragraph().

    doc.save();
}

TEST(DocumentSearchTest, FindMissingText) {
    TempDoc temp_doc("test_find_missing.docx");
    Document doc("test_find_missing.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello, World!");

    auto range = DocumentSearch::find(doc, "Missing");
    EXPECT_FALSE(range.has_value());

    doc.save();
}

TEST(DocumentSearchTest, FindEmptyReturnsNullopt) {
    TempDoc temp_doc("test_find_empty.docx");
    Document doc("test_find_empty.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello");

    auto range = DocumentSearch::find(doc, "");
    EXPECT_FALSE(range.has_value());

    doc.save();
}

// ============================================================================
// DocumentSearch::find_all Tests
// ============================================================================

TEST(DocumentSearchTest, FindAllMultipleParagraphs) {
    TempDoc temp_doc("test_find_all.docx");
    Document doc("test_find_all.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello, World!");
    body->append_paragraph("World is great");
    body->append_paragraph("No match here");

    auto ranges = DocumentSearch::find_all(doc, "World");
    EXPECT_EQ(ranges.size(), 2u);

    doc.save();
}

TEST(DocumentSearchTest, FindAllNoMatch) {
    TempDoc temp_doc("test_find_all_none.docx");
    Document doc("test_find_all_none.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello");

    auto ranges = DocumentSearch::find_all(doc, "Missing");
    EXPECT_TRUE(ranges.empty());

    doc.save();
}

// ============================================================================
// DocumentSearch::replace Tests
// ============================================================================

TEST(DocumentSearchTest, ReplaceFirstOccurrence) {
    TempDoc temp_doc("test_replace.docx");
    Document doc("test_replace.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto para = body->append_paragraph("Hello, World! World!");

    bool replaced = DocumentSearch::replace(doc, "World", "CDocx");
    EXPECT_TRUE(replaced);
    EXPECT_EQ(para->get_text(), "Hello, CDocx! World!");

    doc.save();
}

TEST(DocumentSearchTest, ReplaceNoMatch) {
    TempDoc temp_doc("test_replace_none.docx");
    Document doc("test_replace_none.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello");

    bool replaced = DocumentSearch::replace(doc, "Missing", "X");
    EXPECT_FALSE(replaced);

    doc.save();
}

// ============================================================================
// DocumentSearch::replace_all Tests
// ============================================================================

TEST(DocumentSearchTest, ReplaceAllInSingleParagraph) {
    TempDoc temp_doc("test_replace_all.docx");
    Document doc("test_replace_all.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto para = body->append_paragraph("Hello, World! World!");

    int count = DocumentSearch::replace_all(doc, "World", "CDocx");
    EXPECT_EQ(count, 2);
    EXPECT_EQ(para->get_text(), "Hello, CDocx! CDocx!");

    doc.save();
}

TEST(DocumentSearchTest, ReplaceAllAcrossParagraphs) {
    TempDoc temp_doc("test_replace_all_multi.docx");
    Document doc("test_replace_all_multi.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto para1 = body->append_paragraph("First CDocx");
    auto para2 = body->append_paragraph("Second CDocx");
    auto para3 = body->append_paragraph("No match");

    int count = DocumentSearch::replace_all(doc, "CDocx", "Word");
    EXPECT_EQ(count, 2);
    EXPECT_EQ(para1->get_text(), "First Word");
    EXPECT_EQ(para2->get_text(), "Second Word");
    EXPECT_EQ(para3->get_text(), "No match");

    doc.save();
}

TEST(DocumentSearchTest, ReplaceAllEmptyPattern) {
    TempDoc temp_doc("test_replace_all_empty.docx");
    Document doc("test_replace_all_empty.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello");

    int count = DocumentSearch::replace_all(doc, "", "X");
    EXPECT_EQ(count, 0);

    doc.save();
}

// ============================================================================
// DocumentSearch::replace_with_formatting Tests
// ============================================================================

TEST(DocumentSearchTest, ReplaceWithFormatting) {
    TempDoc temp_doc("test_replace_fmt.docx");
    Document doc("test_replace_fmt.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto para = body->append_paragraph("Hello, World!");

    bool replaced = DocumentSearch::replace_with_formatting(
        doc, "World", "CDocx", static_cast<FormattingFlag>(cdocx::kBold));
    EXPECT_TRUE(replaced);
    EXPECT_EQ(para->get_text(), "Hello, CDocx!");

    auto run = para->get_first_run();
    ASSERT_NE(run, nullptr);
    EXPECT_TRUE(run->get_font().bold);

    doc.save();
}

// ============================================================================
// DocumentSearch::find_and_process Tests
// ============================================================================

TEST(DocumentSearchTest, FindAndProcessCallback) {
    TempDoc temp_doc("test_process.docx");
    Document doc("test_process.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello, World!");
    body->append_paragraph("World again");

    int call_count = 0;
    int result = DocumentSearch::find_and_process(doc, "World",
        [&call_count](const std::string& /*found_text*/, Range& /*range*/) {
            ++call_count;
            return true; // continue
        });

    EXPECT_EQ(result, 2);
    EXPECT_EQ(call_count, 2);

    doc.save();
}

TEST(DocumentSearchTest, FindAndProcessStopEarly) {
    TempDoc temp_doc("test_process_stop.docx");
    Document doc("test_process_stop.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Hello, World!");
    body->append_paragraph("World again");

    int call_count = 0;
    int result = DocumentSearch::find_and_process(doc, "World",
        [&call_count](const std::string& /*found_text*/, Range& /*range*/) {
            ++call_count;
            return false; // stop after first
        });

    EXPECT_EQ(result, 1);
    EXPECT_EQ(call_count, 1);

    doc.save();
}

// ============================================================================
// Round-Trip Tests
// ============================================================================

TEST(DocumentSearchTest, ReplaceAllRoundTrip) {
    TempDoc temp_doc("test_replace_rt.docx");
    Document doc("test_replace_rt.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Template: {{NAME}}");
    body->append_paragraph("Value: {{NAME}}");

    int count = DocumentSearch::replace_all(doc, "{{NAME}}", "CDocx");
    EXPECT_EQ(count, 2);
    doc.save();

    // Re-open and verify
    Document doc2("test_replace_rt.docx");
    doc2.open();

    auto paras = doc2.get_paragraphs();
    bool found_cdocx = false;
    for (auto& para : paras) {
        if (para->get_text().find("CDocx") != std::string::npos) {
            found_cdocx = true;
            break;
        }
    }
    EXPECT_TRUE(found_cdocx);

    doc2.close();
}

// ============================================================================
// Range::replace Tests
// ============================================================================

TEST(DocumentSearchTest, RangeReplace) {
    TempDoc temp_doc("test_range_replace.docx");
    Document doc("test_range_replace.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->remove_all_children();
    body->append_paragraph("Hello, World!");
    body->append_paragraph("Goodbye, World!");

    auto range = DocumentSearch::find(doc, "Hello");
    ASSERT_TRUE(range.has_value());

    bool replaced = range->replace("World", "CDocx");
    EXPECT_TRUE(replaced);

    auto paras = doc.get_paragraphs();
    EXPECT_EQ(paras[0]->get_text(), "Hello, CDocx!");
    EXPECT_EQ(paras[1]->get_text(), "Goodbye, World!");

    doc.save();
}

TEST(DocumentSearchTest, RangeReplaceAll) {
    TempDoc temp_doc("test_range_replace_all.docx");
    Document doc("test_range_replace_all.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    body->remove_all_children();
    body->append_paragraph("A B A B");
    body->append_paragraph("C D");

    auto range = DocumentSearch::find(doc, "A B");
    ASSERT_TRUE(range.has_value());

    int count = range->replace_all("A", "X");
    EXPECT_EQ(count, 2);

    auto paras = doc.get_paragraphs();
    EXPECT_EQ(paras[0]->get_text(), "X B X B");
    EXPECT_EQ(paras[1]->get_text(), "C D");

    doc.save();
}
