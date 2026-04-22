/**
 * @file 16_comment_collection_tests.cpp
 * @brief CommentCollection functionality tests
 * @since 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cdocx;

TEST(CommentCollectionTest, EmptyDocument) {
    Document doc("test_comments_empty.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    EXPECT_EQ(comments.count(), 0u);
    EXPECT_EQ(comments.get(0), nullptr);
    EXPECT_EQ(comments.get_by_id(1), nullptr);
    EXPECT_FALSE(comments.contains(1));

    fs::remove("test_comments_empty.docx");
}

TEST(CommentCollectionTest, AddAndRetrieve) {
    Document doc("test_comments_add.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    auto c1 = comments.add("Alice", "First comment");
    auto c2 = comments.add("Bob", "Second comment");

    ASSERT_NE(c1, nullptr);
    ASSERT_NE(c2, nullptr);
    EXPECT_EQ(c1->get_author(), "Alice");
    EXPECT_EQ(c2->get_author(), "Bob");

    EXPECT_EQ(comments.count(), 2u);
    EXPECT_TRUE(comments.contains(c1->get_id()));
    EXPECT_TRUE(comments.contains(c2->get_id()));

    auto retrieved = comments.get_by_id(c1->get_id());
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->get_text(), "First comment");

    fs::remove("test_comments_add.docx");
}

TEST(CommentCollectionTest, IteratorAccess) {
    Document doc("test_comments_iter.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    comments.add("Author", "Comment A");
    comments.add("Author", "Comment B");

    int count = 0;
    for (const auto& c : comments) {
        EXPECT_FALSE(c->get_text().empty());
        ++count;
    }
    EXPECT_EQ(count, 2);

    fs::remove("test_comments_iter.docx");
}

TEST(CommentCollectionTest, RemoveById) {
    Document doc("test_comments_remove.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    auto c = comments.add("Author", "To be removed");
    int id = c->get_id();

    EXPECT_EQ(comments.count(), 1u);
    EXPECT_TRUE(comments.remove(id));
    EXPECT_EQ(comments.count(), 0u);
    EXPECT_FALSE(comments.contains(id));

    fs::remove("test_comments_remove.docx");
}

TEST(CommentCollectionTest, RemoveAtIndex) {
    Document doc("test_comments_remove_idx.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    comments.add("Author", "First");
    comments.add("Author", "Second");

    EXPECT_EQ(comments.count(), 2u);
    EXPECT_TRUE(comments.remove_at(0));
    EXPECT_EQ(comments.count(), 1u);

    fs::remove("test_comments_remove_idx.docx");
}

TEST(CommentCollectionTest, ClearAll) {
    Document doc("test_comments_clear.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    comments.add("Author", "One");
    comments.add("Author", "Two");
    comments.add("Author", "Three");

    EXPECT_EQ(comments.count(), 3u);
    comments.clear();
    EXPECT_EQ(comments.count(), 0u);

    fs::remove("test_comments_clear.docx");
}

TEST(CommentCollectionTest, RoundTripAfterSave) {
    const std::string path = "test_comments_rt.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());
        auto comments = doc.get_comments();
        auto c = comments.add("Reviewer", "Please check this section.");
        c->set_initial("R");
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto comments = doc.get_comments();
        EXPECT_EQ(comments.count(), 1u);

        auto c = comments.get(0);
        ASSERT_NE(c, nullptr);
        EXPECT_EQ(c->get_author(), "Reviewer");
        EXPECT_EQ(c->get_initial(), "R");
        EXPECT_NE(c->get_text().find("Please check"), std::string::npos);
    }

    fs::remove(path);
}

// ============================================================================
// Extended Comment API Tests
// ============================================================================

TEST(CommentCollectionTest, ModifyCommentText) {
    Document doc("test_comments_mod.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    auto c = comments.add("Author", "Original text");
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->get_text(), "Original text");

    c->set_text("Updated text");
    EXPECT_EQ(c->get_text(), "Updated text");

    fs::remove("test_comments_mod.docx");
}

TEST(CommentCollectionTest, CommentProperties) {
    Document doc("test_comments_props.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    auto c = comments.add("Alice", "Property test");
    c->set_initial("A");
    c->set_done(true);
    c->set_parent_comment_id(5);

    auto now = std::chrono::system_clock::now();
    c->set_date_time(now);

    EXPECT_EQ(c->get_author(), "Alice");
    EXPECT_EQ(c->get_initial(), "A");
    EXPECT_TRUE(c->is_done());
    EXPECT_EQ(c->get_parent_comment_id(), 5);
    // Allow small tolerance for clock granularity
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(c->get_date_time() - now).count();
    EXPECT_LE(std::abs(diff), 1);

    fs::remove("test_comments_props.docx");
}

TEST(CommentCollectionTest, AppendParagraphToComment) {
    Document doc("test_comments_para.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    auto c = comments.add("Reviewer", "First paragraph.");
    auto para = c->append_paragraph("Second paragraph.");
    ASSERT_NE(para, nullptr);

    auto text = c->get_text();
    EXPECT_NE(text.find("First paragraph."), std::string::npos);
    EXPECT_NE(text.find("Second paragraph."), std::string::npos);

    fs::remove("test_comments_para.docx");
}

TEST(CommentCollectionTest, RemoveInvalidIndex) {
    Document doc("test_comments_bad_idx.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    comments.add("Author", "One");

    EXPECT_EQ(comments.count(), 1u);
    EXPECT_FALSE(comments.remove_at(5));   // Out of range
    EXPECT_FALSE(comments.remove_at(1));   // Out of range
    EXPECT_TRUE(comments.remove_at(0));    // Valid

    fs::remove("test_comments_bad_idx.docx");
}

TEST(CommentCollectionTest, RemoveNonExistentId) {
    Document doc("test_comments_bad_id.docx");
    ASSERT_TRUE(doc.create_empty());

    auto comments = doc.get_comments();
    auto c = comments.add("Author", "One");
    int real_id = c->get_id();

    EXPECT_EQ(comments.count(), 1u);
    EXPECT_FALSE(comments.remove(real_id + 999));
    EXPECT_TRUE(comments.remove(real_id));

    fs::remove("test_comments_bad_id.docx");
}

TEST(CommentCollectionTest, MultipleCommentsSameAuthor) {
    const std::string path = "test_comments_same_author.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());
        auto comments = doc.get_comments();
        comments.add("Alice", "Comment one");
        comments.add("Alice", "Comment two");
        comments.add("Bob", "Comment three");
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto comments = doc.get_comments();
        EXPECT_EQ(comments.count(), 3u);

        int alice_count = 0;
        int bob_count = 0;
        for (const auto& c : comments) {
            if (c->get_author() == "Alice") ++alice_count;
            if (c->get_author() == "Bob") ++bob_count;
        }
        EXPECT_EQ(alice_count, 2);
        EXPECT_EQ(bob_count, 1);
    }

    fs::remove(path);
}
