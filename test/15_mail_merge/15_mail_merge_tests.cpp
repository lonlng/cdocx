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
