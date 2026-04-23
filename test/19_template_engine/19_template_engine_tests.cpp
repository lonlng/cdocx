/**
 * @file 19_template_engine_tests.cpp
 * @brief Tests for TemplateEngine unified template API
 * @version 0.8.0
 *
 * @defgroup tests_template_engine TemplateEngine Tests
 * @brief Test suite for dictionary-style template population
 * @{
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <cdocx/bookmark_inserter.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/template_engine.h>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;
using namespace cdocx;

// ============================================================================
// TemplateFormat Tests
// ============================================================================

TEST(TemplateFormatTest, DefaultConstructionIsEmpty) {
    TemplateFormat fmt;
    EXPECT_TRUE(fmt.is_empty());
}

TEST(TemplateFormatTest, ChainableBuilders) {
    TemplateFormat fmt;
    fmt.bold().italic().underline().size(24).font("Arial").color("FF0000")
       .alignment("center").line_spacing(360).space_before(120).space_after(120);

    EXPECT_FALSE(fmt.is_empty());
    EXPECT_TRUE(fmt.bold_opt().value());
    EXPECT_TRUE(fmt.italic_opt().value());
    EXPECT_TRUE(fmt.underline_opt().value());
    EXPECT_EQ(fmt.size_opt().value(), 24);
    EXPECT_EQ(fmt.font_opt().value(), "Arial");
    EXPECT_EQ(fmt.color_opt().value(), "FF0000");
    EXPECT_EQ(fmt.alignment_opt().value(), "center");
}

TEST(TemplateFormatTest, ToBookmarkFormatConversion) {
    TemplateFormat fmt;
    fmt.bold().size(24).font_ascii("Arial").color("FF0000").alignment("center");

    BookmarkFormat bmf = fmt.to_bookmark_format();
    EXPECT_TRUE(bmf.bold);
    EXPECT_EQ(bmf.font_size, 24);
    EXPECT_EQ(bmf.font_ascii, "Arial");
    EXPECT_EQ(bmf.color, "FF0000");
    EXPECT_EQ(bmf.alignment, "center");
}

// ============================================================================
// TemplateValue Tests
// ============================================================================

TEST(TemplateValueTest, DefaultConstructionIsEmptyText) {
    TemplateValue val;
    EXPECT_TRUE(val.is_text());
    EXPECT_EQ(val.text_content(), "");
}

TEST(TemplateValueTest, TextFactory) {
    auto val = TemplateValue::text("Hello World");
    EXPECT_TRUE(val.is_text());
    EXPECT_EQ(val.text_content(), "Hello World");
    EXPECT_TRUE(val.text_format().is_empty());
}

TEST(TemplateValueTest, TextWithFormat) {
    TemplateFormat fmt;
    fmt.bold().size(28);
    auto val = TemplateValue::text("Hello", fmt);
    EXPECT_TRUE(val.is_text());
    EXPECT_EQ(val.text_content(), "Hello");
    EXPECT_TRUE(val.text_format().bold_opt().value());
}

TEST(TemplateValueTest, ImageFactory) {
    auto val = TemplateValue::image("logo.png");
    EXPECT_TRUE(val.is_image());
    EXPECT_EQ(val.image_path(), "logo.png");
    EXPECT_EQ(val.image_alignment(), ImageAlignment::Center);
}

TEST(TemplateValueTest, ImageWithSize) {
    auto val = TemplateValue::image("logo.png", 400.0, 300.0);
    EXPECT_TRUE(val.is_image());
    EXPECT_TRUE(val.image_size().is_valid());
    EXPECT_EQ(val.image_size().width_pt, 400.0);
    EXPECT_EQ(val.image_size().height_pt, 300.0);
}

TEST(TemplateValueTest, ImageChainableConfig) {
    auto val = TemplateValue::image("logo.png")
                   .sized(400.0, 300.0)
                   .left_aligned()
                   .with_caption("Company Logo");
    EXPECT_TRUE(val.is_image());
    EXPECT_EQ(val.image_alignment(), ImageAlignment::Left);
    EXPECT_EQ(val.image_caption(), "Company Logo");
}

// ============================================================================
// TemplateEngine Construction and Queue Tests
// ============================================================================

TEST(TemplateEngineTest, EmptyQueueHasSizeZero) {
    Document doc;
    TemplateEngine engine(&doc);
    EXPECT_EQ(engine.size(), 0u);
    EXPECT_FALSE(engine.has("anything"));
}

TEST(TemplateEngineTest, DictionaryStyleAssignment) {
    Document doc;
    TemplateEngine engine(&doc);

    engine["name"] = TemplateValue::text("John");
    engine["date"] = "2025-04-21";

    EXPECT_EQ(engine.size(), 2u);
    EXPECT_TRUE(engine.has("name"));
    EXPECT_TRUE(engine.has("date"));
}

TEST(TemplateEngineTest, SetApi) {
    Document doc;
    TemplateEngine engine(&doc);

    engine.set("key1", TemplateValue::text("value1"))
          .set("key2", std::string("value2"))
          .set("key3", "value3");

    EXPECT_EQ(engine.size(), 3u);
}

TEST(TemplateEngineTest, SetBatch) {
    Document doc;
    TemplateEngine engine(&doc);

    std::map<std::string, std::string> texts = {
        {"a", "1"}, {"b", "2"}, {"c", "3"}};
    engine.set_batch(texts);

    EXPECT_EQ(engine.size(), 3u);
    EXPECT_TRUE(engine.has("a"));
}

TEST(TemplateEngineTest, RemoveAndClear) {
    Document doc;
    TemplateEngine engine(&doc);

    engine.set("key", "value");
    EXPECT_TRUE(engine.has("key"));

    engine.remove("key");
    EXPECT_FALSE(engine.has("key"));

    engine.set("k1", "v1").set("k2", "v2");
    engine.clear();
    EXPECT_EQ(engine.size(), 0u);
}

// ============================================================================
// TemplateEngine Placeholder Replacement Tests
// ============================================================================

TEST(TemplateEngineTest, PlaceholderTextReplacement) {
    const std::string test_file = "test_te_placeholder.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Company: {{company}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["company"] = "Acme Inc.";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        EXPECT_EQ(result.failed, 0);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        EXPECT_EQ(paras[0]->get_text(), "Company: Acme Inc.");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, MultiplePlaceholderReplacement) {
    const std::string test_file = "test_te_multi_placeholder.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{greeting}} {{name}}!");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["greeting"] = "Hello";
        engine["name"] = "World";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 2);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        EXPECT_EQ(paras[0]->get_text(), "Hello World!");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, PlaceholderReplacementWithFormat) {
    const std::string test_file = "test_te_fmt_placeholder.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Title: {{title}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["title"] = TemplateValue::text("Annual Report")
                              .with_format(TemplateFormat().bold().size(28));
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    fs::remove(test_file);
}

// ============================================================================
// TemplateEngine Bookmark Replacement Tests
// ============================================================================

TEST(TemplateEngineTest, BookmarkTextReplacement) {
    const std::string test_file = "test_te_bookmark.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Author: John Doe");
        doc.sync_to_physical_tree();

        BookmarkInserter inserter(&doc);
        inserter.insert("AUTHOR", "John Doe");
        doc.sync_from_physical_tree();
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["AUTHOR"] = "Jane Doe";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        EXPECT_EQ(result.failed, 0);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto bookmarks = doc.get_bookmarks();
        auto bm = bookmarks.get("AUTHOR");
        ASSERT_TRUE(bm.has_value());
        EXPECT_EQ(bm->get_text(), "Jane Doe");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, MultipleBookmarkReplacement) {
    const std::string test_file = "test_te_multi_bookmark.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Author: Alice");
        body->append_paragraph("Reviewer: Bob");
        doc.sync_to_physical_tree();

        BookmarkInserter inserter(&doc);
        inserter.insert("AUTHOR", "Alice");
        inserter.insert("REVIEWER", "Bob");
        doc.sync_from_physical_tree();
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["AUTHOR"] = "Alice Smith";
        engine["REVIEWER"] = "Bob Jones";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 2);
        EXPECT_EQ(result.failed, 0);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto bookmarks = doc.get_bookmarks();
        EXPECT_EQ(bookmarks.count(), 2u);

        auto author = bookmarks.get("AUTHOR");
        ASSERT_TRUE(author.has_value());
        EXPECT_EQ(author->get_text(), "Alice Smith");

        auto reviewer = bookmarks.get("REVIEWER");
        ASSERT_TRUE(reviewer.has_value());
        EXPECT_EQ(reviewer->get_text(), "Bob Jones");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, MixedPlaceholderAndBookmark) {
    const std::string test_file = "test_te_mixed.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Company: {{company}}");
        body->append_paragraph("Author: Unknown");
        doc.sync_to_physical_tree();

        BookmarkInserter inserter(&doc);
        inserter.insert("AUTHOR", "Unknown");
        doc.sync_from_physical_tree();
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["company"] = "Acme Inc.";
        engine["AUTHOR"] = "Jane Doe";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 2);
        EXPECT_EQ(result.failed, 0);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_GE(paras.size(), 1u);
        EXPECT_EQ(paras[0]->get_text(), "Company: Acme Inc.");

        auto bookmarks = doc.get_bookmarks();
        auto author = bookmarks.get("AUTHOR");
        ASSERT_TRUE(author.has_value());
        EXPECT_EQ(author->get_text(), "Jane Doe");
    }

    fs::remove(test_file);
}

// ============================================================================
// TemplateEngine Batch and Conditional Tests
// ============================================================================

TEST(TemplateEngineTest, BatchStringReplacement) {
    const std::string test_file = "test_te_batch.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{a}} and {{b}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        std::map<std::string, std::string> data = {{"a", "Apple"}, {"b", "Banana"}};
        engine.set_batch(data);
        auto result = engine.apply();

        EXPECT_EQ(result.success, 2);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        EXPECT_EQ(paras[0]->get_text(), "Apple and Banana");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, ApplyIfPredicate) {
    const std::string test_file = "test_te_apply_if.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{foo}} {{bar}} {{baz}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["foo"] = "FOO";
        engine["bar"] = "BAR";
        engine["baz"] = "BAZ";

        // Only apply keys starting with "b"
        auto result = engine.apply_if([](const std::string& key) {
            return !key.empty() && key[0] == 'b';
        });

        EXPECT_EQ(result.success, 2);
        EXPECT_EQ(result.skipped, 1);  // foo skipped
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        // {{foo}} remains, bar and baz are replaced
        EXPECT_EQ(paras[0]->get_text(), "{{foo}} BAR BAZ");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, EmptyValuesAreSkipped) {
    const std::string test_file = "test_te_skip_empty.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{empty}} {{filled}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["empty"] = "";
        engine["filled"] = "VALUE";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        EXPECT_EQ(result.skipped, 1);
        doc.save();
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, ApplySingleKey) {
    const std::string test_file = "test_te_single.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{a}} {{b}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine["a"] = "A";
        engine["b"] = "B";

        // Apply only "a"
        auto result = engine.apply("a");
        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        EXPECT_EQ(paras[0]->get_text(), "A {{b}}");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, CustomDelimiters) {
    const std::string test_file = "test_te_delims.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Name: [%name%]");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_delimiters("[%", "%]");
        engine["name"] = "John";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        EXPECT_EQ(paras[0]->get_text(), "Name: John");
    }

    fs::remove(test_file);
}

// ============================================================================
// TemplateEngine Configuration Tests
// ============================================================================

TEST(TemplateEngineTest, GlobalConfigurationChaining) {
    Document doc;
    TemplateEngine engine(&doc);

    engine.with_action(TemplateAction::Replace)
          .with_scope(TemplateScope::All)
          .with_target(TemplateTarget::Auto)
          .with_format_policy(FormatPolicy::Preserve)
          .with_default_format(TemplateFormat().bold().size(14))
          .with_delimiters("[[", "]]");

    // Configurations are applied internally; just verify no crash
    EXPECT_EQ(engine.size(), 0u);
}

TEST(TemplateEngineTest, ScopeFirstReplacesOnlyFirstOccurrence) {
    const std::string test_file = "test_te_scope_first.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{item}} {{item}} {{item}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_scope(TemplateScope::First);
        engine["item"] = "X";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        // Only first {{item}} is replaced
        EXPECT_EQ(paras[0]->get_text(), "X {{item}} {{item}}");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, ScopeAllReplacesAllOccurrences) {
    const std::string test_file = "test_te_scope_all.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{item}} {{item}} {{item}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_scope(TemplateScope::All);
        engine["item"] = "X";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        // All {{item}} are replaced
        EXPECT_EQ(paras[0]->get_text(), "X X X");
    }

    fs::remove(test_file);
}

// ============================================================================
// TemplateEngine Insert Mode Tests
// ============================================================================

TEST(TemplateEngineTest, PlaceholderInsertMode) {
    const std::string test_file = "test_te_insert_placeholder.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Prefix {{item}} Suffix");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_action(TemplateAction::Insert);
        engine["item"] = "INSERTED";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        // Insert mode prepends value before placeholder, keeping it intact
        EXPECT_EQ(paras[0]->get_text(), "Prefix INSERTED{{item}} Suffix");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, PlaceholderInsertModeFirstScope) {
    const std::string test_file = "test_te_insert_first.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("{{item}} and {{item}}");
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_action(TemplateAction::Insert).with_scope(TemplateScope::First);
        engine["item"] = "X";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_first_section()->get_body()->get_paragraphs();
        ASSERT_EQ(paras.size(), 1u);
        // Only first placeholder gets the insertion
        EXPECT_EQ(paras[0]->get_text(), "X{{item}} and {{item}}");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, BookmarkInsertMode) {
    const std::string test_file = "test_te_insert_bookmark.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Original text");
        doc.sync_to_physical_tree();

        BookmarkInserter inserter(&doc);
        inserter.insert("MARK", "Original text");
        doc.sync_from_physical_tree();
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_action(TemplateAction::Insert);
        engine["MARK"] = " [INSERTED]";
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto bookmarks = doc.get_bookmarks();
        auto bm = bookmarks.get("MARK");
        ASSERT_TRUE(bm.has_value());
        // Insert mode keeps original bookmark content and adds new text
        EXPECT_EQ(bm->get_text(), " [INSERTED]Original text");
    }

    fs::remove(test_file);
}

TEST(TemplateEngineTest, BookmarkInsertModeWithFormat) {
    const std::string test_file = "test_te_insert_fmt.docx";
    if (fs::exists(test_file)) fs::remove(test_file);

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));
        auto body = doc.get_first_section()->get_body();
        body->append_paragraph("Target");
        doc.sync_to_physical_tree();

        BookmarkInserter inserter(&doc);
        inserter.insert("MARK", "Target");
        doc.sync_from_physical_tree();
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        TemplateEngine engine(&doc);
        engine.with_action(TemplateAction::Insert)
              .with_format_policy(FormatPolicy::Override);
        engine["MARK"] = TemplateValue::text("BoldPrefix")
                              .with_format(TemplateFormat().bold().size(28));
        auto result = engine.apply();

        EXPECT_EQ(result.success, 1);
        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto bookmarks = doc.get_bookmarks();
        auto bm = bookmarks.get("MARK");
        ASSERT_TRUE(bm.has_value());
        // Bookmark still exists with original + inserted content
        EXPECT_TRUE(bm->get_text().find("BoldPrefix") != std::string::npos);
        EXPECT_TRUE(bm->get_text().find("Target") != std::string::npos);
    }

    fs::remove(test_file);
}

/** @} */
