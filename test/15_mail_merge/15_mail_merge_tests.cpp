/**
 * @file 15_mail_merge_tests.cpp
 * @brief MailMerge functionality tests
 * @since 0.7.0
 */

#include <cdocx.h>
#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include <map>

namespace fs = std::filesystem;
using namespace cdocx;

TEST(MailMergeTest, GetFieldNamesEmpty) {
    Document doc("test_mail_empty.docx");
    ASSERT_TRUE(doc.create_empty());

    MailMerge mail_merge(&doc);
    auto names = mail_merge.get_field_names();
    EXPECT_TRUE(names.empty());

    fs::remove("test_mail_empty.docx");
}

TEST(MailMergeTest, GetFieldNamesFromDom) {
    Document doc("test_mail_names.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    auto para = body->get_first_paragraph();

    auto field1 = std::make_shared<Field>(&doc, FieldType::MergeField);
    field1->set_field_code("MERGEFIELD FirstName");
    para->append_child(field1);

    auto field2 = std::make_shared<Field>(&doc, FieldType::MergeField);
    field2->set_field_code("MERGEFIELD LastName");
    para->append_child(field2);

    // Duplicate field name
    auto field3 = std::make_shared<Field>(&doc, FieldType::MergeField);
    field3->set_field_code("MERGEFIELD FirstName");
    para->append_child(field3);

    MailMerge mail_merge(&doc);
    auto names = mail_merge.get_field_names();

    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names[0], "FirstName");
    EXPECT_EQ(names[1], "LastName");

    fs::remove("test_mail_names.docx");
}

TEST(MailMergeTest, ExecuteSimpleMerge) {
    Document doc("test_mail_exec.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    auto para = body->get_first_paragraph();

    para->append_run("Dear ");
    auto field1 = std::make_shared<Field>(&doc, FieldType::MergeField);
    field1->set_field_code("MERGEFIELD Name");
    para->append_child(field1);
    para->append_run(", your score is ");
    auto field2 = std::make_shared<Field>(&doc, FieldType::MergeField);
    field2->set_field_code("MERGEFIELD Score");
    para->append_child(field2);
    para->append_run(".");

    MailMerge mail_merge(&doc);
    std::map<std::string, std::string> data = {
        {"Name", "Alice"},
        {"Score", "95"}
    };
    mail_merge.execute(data);
    doc.save();

    // Verify by reopening
    Document doc2("test_mail_exec.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());
    auto text = doc2.get_text();
    EXPECT_NE(text.find("Dear Alice, your score is 95."), std::string::npos);

    fs::remove("test_mail_exec.docx");
}

TEST(MailMergeTest, ExecuteWithMissingField) {
    Document doc("test_mail_missing.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    auto para = body->get_first_paragraph();

    para->append_run("Hello ");
    auto field = std::make_shared<Field>(&doc, FieldType::MergeField);
    field->set_field_code("MERGEFIELD Name");
    para->append_child(field);
    para->append_run("!");

    MailMerge mail_merge(&doc);
    mail_merge.set_cleanup_options(MailMergeCleanupOptions::RemoveUnusedFields);

    // No data for "Name"
    mail_merge.execute(std::map<std::string, std::string>{});
    doc.save();

    Document doc2("test_mail_missing.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());
    auto text = doc2.get_text();
    EXPECT_NE(text.find("Hello !"), std::string::npos);

    fs::remove("test_mail_missing.docx");
}

TEST(MailMergeTest, ExecuteWithVectorPairs) {
    Document doc("test_mail_vec.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    auto para = body->get_first_paragraph();

    auto field = std::make_shared<Field>(&doc, FieldType::MergeField);
    field->set_field_code("MERGEFIELD Company");
    para->append_child(field);

    MailMerge mail_merge(&doc);
    std::vector<std::pair<std::string, std::string>> data = {
        {"Company", "ELEGANCE Labs"}
    };
    mail_merge.execute(data);
    doc.save();

    Document doc2("test_mail_vec.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());
    auto text = doc2.get_text();
    EXPECT_NE(text.find("ELEGANCE Labs"), std::string::npos);

    fs::remove("test_mail_vec.docx");
}

TEST(MailMergeTest, DeleteFields) {
    Document doc("test_mail_delete.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    auto para = body->get_first_paragraph();

    para->append_run("A");
    auto field = std::make_shared<Field>(&doc, FieldType::MergeField);
    field->set_field_code("MERGEFIELD X");
    para->append_child(field);
    para->append_run("B");

    MailMerge mail_merge(&doc);
    mail_merge.delete_fields();
    doc.save();

    Document doc2("test_mail_delete.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());
    MailMerge mail_merge2(&doc2);
    auto names = mail_merge2.get_field_names();
    EXPECT_TRUE(names.empty());

    auto text = doc2.get_text();
    EXPECT_NE(text.find("AB"), std::string::npos);

    fs::remove("test_mail_delete.docx");
}

// ============================================================================
// Cleanup Options Tests
// ============================================================================

TEST(MailMergeTest, GetAndSetCleanupOptions) {
    Document doc("test_mail_opts.docx");
    ASSERT_TRUE(doc.create_empty());

    MailMerge mail_merge(&doc);
    // Default is RemoveUnusedFields
    EXPECT_EQ(static_cast<std::uint8_t>(mail_merge.get_cleanup_options()),
              static_cast<std::uint8_t>(MailMergeCleanupOptions::RemoveUnusedFields));

    mail_merge.set_cleanup_options(MailMergeCleanupOptions::None);
    EXPECT_EQ(static_cast<std::uint8_t>(mail_merge.get_cleanup_options()),
              static_cast<std::uint8_t>(MailMergeCleanupOptions::None));

    mail_merge.set_cleanup_options(MailMergeCleanupOptions::RemoveEmptyParagraphs |
                                   MailMergeCleanupOptions::RemoveUnusedFields);
    EXPECT_NE(static_cast<std::uint8_t>(mail_merge.get_cleanup_options() &
                                        MailMergeCleanupOptions::RemoveEmptyParagraphs),
              0);

    fs::remove("test_mail_opts.docx");
}

TEST(MailMergeTest, CleanupOptionsNonePreservesEmptyParagraph) {
    Document doc("test_mail_none.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    // Ensure body has the placeholder removed and our controlled content
    body->remove_all_children();

    // Paragraph with only a merge field (will become empty after merge)
    auto para = body->append_paragraph();
    auto field = std::make_shared<Field>(&doc, FieldType::MergeField);
    field->set_field_code("MERGEFIELD MissingField");
    para->append_child(field);

    // Another paragraph with text to keep body non-empty
    body->append_paragraph("Footer text");

    MailMerge mail_merge(&doc);
    mail_merge.set_cleanup_options(MailMergeCleanupOptions::None);
    mail_merge.execute(std::map<std::string, std::string>{});
    doc.save();

    Document doc2("test_mail_none.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto paras = doc2.get_paragraphs();
    // With None cleanup, the empty paragraph should be preserved
    EXPECT_GE(paras.get_count(), 2u);

    fs::remove("test_mail_none.docx");
}

TEST(MailMergeTest, CleanupOptionsRemoveEmptyParagraphs) {
    Document doc("test_mail_empty_para.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    body->remove_all_children();

    // Paragraph with only a merge field replaced by empty string
    auto para = body->append_paragraph();
    auto field = std::make_shared<Field>(&doc, FieldType::MergeField);
    field->set_field_code("MERGEFIELD EmptyValue");
    para->append_child(field);

    // Another paragraph with text
    body->append_paragraph("Remaining text");

    MailMerge mail_merge(&doc);
    mail_merge.set_cleanup_options(MailMergeCleanupOptions::RemoveEmptyParagraphs);
    std::map<std::string, std::string> data = {{"EmptyValue", ""}};
    mail_merge.execute(data);

    // The field is replaced with a Run containing empty text, so the paragraph
    // should be considered empty and removed by cleanup.
    auto dom_paras = body->get_paragraphs();
    EXPECT_EQ(dom_paras.size(), 1u);
    EXPECT_EQ(dom_paras[0]->get_text(), "Remaining text");

    doc.save();

    Document doc2("test_mail_empty_para.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto text = doc2.get_text();
    EXPECT_NE(text.find("Remaining text"), std::string::npos);

    fs::remove("test_mail_empty_para.docx");
}

TEST(MailMergeTest, MultipleParagraphsMerge) {
    Document doc("test_mail_multi_para.docx");
    ASSERT_TRUE(doc.create_empty());

    auto section = doc.get_first_section();
    auto body = section->get_body();
    body->remove_all_children();

    auto para1 = body->append_paragraph("Hello ");
    auto f1 = std::make_shared<Field>(&doc, FieldType::MergeField);
    f1->set_field_code("MERGEFIELD Name");
    para1->append_child(f1);

    auto para2 = body->append_paragraph("Score: ");
    auto f2 = std::make_shared<Field>(&doc, FieldType::MergeField);
    f2->set_field_code("MERGEFIELD Score");
    para2->append_child(f2);

    MailMerge mail_merge(&doc);
    std::map<std::string, std::string> data = {
        {"Name", "Bob"},
        {"Score", "88"}
    };
    mail_merge.execute(data);
    doc.save();

    Document doc2("test_mail_multi_para.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto text = doc2.get_text();
    EXPECT_NE(text.find("Hello Bob"), std::string::npos);
    EXPECT_NE(text.find("Score: 88"), std::string::npos);

    fs::remove("test_mail_multi_para.docx");
}
