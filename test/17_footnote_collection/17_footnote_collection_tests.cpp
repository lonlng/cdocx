/**
 * @file 17_footnote_collection_tests.cpp
 * @brief FootnoteCollection and EndnoteCollection functionality tests
 * @since 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cdocx;

TEST(FootnoteCollectionTest, EmptyDocument) {
    Document doc("test_footnotes_empty.docx");
    ASSERT_TRUE(doc.create_empty());

    auto footnotes = doc.footnotes();
    EXPECT_EQ(footnotes.count(), 0u);
    EXPECT_EQ(footnotes.get(0), nullptr);
    EXPECT_EQ(footnotes.get_by_id(1), nullptr);
    EXPECT_FALSE(footnotes.contains(1));

    fs::remove("test_footnotes_empty.docx");
}

TEST(FootnoteCollectionTest, AddAndRetrieve) {
    Document doc("test_footnotes_add.docx");
    ASSERT_TRUE(doc.create_empty());

    auto footnotes = doc.footnotes();
    auto f1 = footnotes.add("First footnote");
    auto f2 = footnotes.add("Second footnote", "*");

    ASSERT_NE(f1, nullptr);
    ASSERT_NE(f2, nullptr);
    EXPECT_EQ(f1->get_footnote_type(), FootnoteType::Footnote);
    EXPECT_EQ(f2->get_footnote_type(), FootnoteType::Footnote);
    EXPECT_TRUE(f1->is_auto());
    EXPECT_EQ(f2->get_reference_mark(), "*");

    EXPECT_EQ(footnotes.count(), 2u);
    EXPECT_TRUE(footnotes.contains(f1->get_id()));
    EXPECT_TRUE(footnotes.contains(f2->get_id()));

    auto retrieved = footnotes.get_by_id(f1->get_id());
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->get_text(), "First footnote");

    fs::remove("test_footnotes_add.docx");
}

TEST(FootnoteCollectionTest, IteratorAccess) {
    Document doc("test_footnotes_iter.docx");
    ASSERT_TRUE(doc.create_empty());

    auto footnotes = doc.footnotes();
    footnotes.add("Footnote A");
    footnotes.add("Footnote B");

    int count = 0;
    for (const auto& f : footnotes) {
        EXPECT_FALSE(f->get_text().empty());
        ++count;
    }
    EXPECT_EQ(count, 2);

    fs::remove("test_footnotes_iter.docx");
}

TEST(FootnoteCollectionTest, RemoveById) {
    Document doc("test_footnotes_remove.docx");
    ASSERT_TRUE(doc.create_empty());

    auto footnotes = doc.footnotes();
    auto f = footnotes.add("To be removed");
    int id = f->get_id();

    EXPECT_EQ(footnotes.count(), 1u);
    EXPECT_TRUE(footnotes.remove(id));
    EXPECT_EQ(footnotes.count(), 0u);
    EXPECT_FALSE(footnotes.contains(id));

    fs::remove("test_footnotes_remove.docx");
}

TEST(FootnoteCollectionTest, ClearAll) {
    Document doc("test_footnotes_clear.docx");
    ASSERT_TRUE(doc.create_empty());

    auto footnotes = doc.footnotes();
    footnotes.add("One");
    footnotes.add("Two");

    EXPECT_EQ(footnotes.count(), 2u);
    footnotes.clear();
    EXPECT_EQ(footnotes.count(), 0u);

    fs::remove("test_footnotes_clear.docx");
}

TEST(FootnoteCollectionTest, RoundTripAfterSave) {
    const std::string path = "test_footnotes_rt.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());
        auto footnotes = doc.footnotes();
        footnotes.add("Please check this reference.");
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto footnotes = doc.footnotes();
        EXPECT_EQ(footnotes.count(), 1u);

        auto f = footnotes.get(0);
        ASSERT_NE(f, nullptr);
        EXPECT_NE(f->get_text().find("Please check"), std::string::npos);
    }

    fs::remove(path);
}

TEST(EndnoteCollectionTest, AddAndRetrieve) {
    Document doc("test_endnotes_add.docx");
    ASSERT_TRUE(doc.create_empty());

    auto endnotes = doc.endnotes();
    auto e1 = endnotes.add("First endnote");
    auto e2 = endnotes.add("Second endnote", "#");

    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_EQ(e1->get_footnote_type(), FootnoteType::Endnote);
    EXPECT_EQ(e2->get_footnote_type(), FootnoteType::Endnote);
    EXPECT_EQ(e2->get_reference_mark(), "#");

    EXPECT_EQ(endnotes.count(), 2u);

    fs::remove("test_endnotes_add.docx");
}

TEST(EndnoteCollectionTest, RoundTripAfterSave) {
    const std::string path = "test_endnotes_rt.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());
        auto endnotes = doc.endnotes();
        endnotes.add("See appendix for details.");
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto endnotes = doc.endnotes();
        EXPECT_EQ(endnotes.count(), 1u);

        auto e = endnotes.get(0);
        ASSERT_NE(e, nullptr);
        EXPECT_EQ(e->get_footnote_type(), FootnoteType::Endnote);
        EXPECT_NE(e->get_text().find("appendix"), std::string::npos);
    }

    fs::remove(path);
}

TEST(FootnoteCollectionTest, DocumentBuilderInsertsFootnote) {
    const std::string path = "test_footnotes_builder.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());
        DocumentBuilder builder(&doc);
        builder.move_to_document_start();
        builder.write("Hello");
        builder.insert_footnote(FootnoteType::Footnote, "Builder footnote text");
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto footnotes = doc.footnotes();
        EXPECT_EQ(footnotes.count(), 1u);

        auto f = footnotes.get(0);
        ASSERT_NE(f, nullptr);
        EXPECT_EQ(f->get_text(), "Builder footnote text");
    }

    fs::remove(path);
}
