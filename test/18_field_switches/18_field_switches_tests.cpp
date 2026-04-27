/**
 * @file 18_field_switches_tests.cpp
 * @brief Field switches and round-trip tests
 * @since 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include "../test_helpers.h"
#include <filesystem>

namespace fs = std::filesystem;
using cdocx::test::TempDoc;
using namespace cdocx;

TEST(FieldSwitchesTest, PageNumberWithSwitches) {
    Document doc("test_field_page.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.move_to_document_start();
    auto field = builder.insert_page_number("\\* ROMAN");

    ASSERT_NE(field, nullptr);
    EXPECT_EQ(field->get_type(), FieldType::Page);
    EXPECT_EQ(field->get_field_code(), "PAGE");
    EXPECT_EQ(field->get_switches_text(), "\\* ROMAN");
    EXPECT_EQ(field->get_full_field_code(), "PAGE \\* ROMAN");

}

TEST(FieldSwitchesTest, DateWithFormatSwitch) {
    Document doc("test_field_date.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.move_to_document_start();
    auto field = builder.insert_date("\\@ \"yyyy-MM-dd\"");

    ASSERT_NE(field, nullptr);
    EXPECT_EQ(field->get_type(), FieldType::Date);
    EXPECT_EQ(field->get_field_code(), "DATE");
    EXPECT_EQ(field->get_switches_text(), "\\@ \"yyyy-MM-dd\"");

}

TEST(FieldSwitchesTest, MergeFieldWithSwitches) {
    Document doc("test_field_merge.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.move_to_document_start();
    auto field = builder.insert_merge_field("Name", "\\* Upper");

    ASSERT_NE(field, nullptr);
    EXPECT_EQ(field->get_field_code(), "MERGEFIELD Name");
    EXPECT_EQ(field->get_switches_text(), "\\* Upper");

}

TEST(FieldSwitchesTest, FieldAddMultipleSwitches) {
    auto field = std::make_shared<Field>();
    field->set_field_code("PAGE");
    field->add_switch("\\* MERGEFORMAT");
    field->add_switch("\\# \"0\"");

    EXPECT_EQ(field->get_switches().size(), 2u);
    EXPECT_EQ(field->get_full_field_code(), "PAGE \\* MERGEFORMAT \\# \"0\"");

    field->clear_switches();
    EXPECT_TRUE(field->get_switches().empty());
    EXPECT_EQ(field->get_full_field_code(), "PAGE");
}

TEST(FieldSwitchesTest, RoundTripAfterSaveAndLoad) {
    const std::string path = "test_field_rt.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());
        DocumentBuilder builder(&doc);
        builder.move_to_document_start();
        builder.insert_page_number("\\* ROMAN");
        builder.insert_paragraph();
        builder.insert_date("\\@ \"yyyy-MM-dd\"");
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_paragraphs();
        ASSERT_GE(paras.get_count(), 2u);

        // First paragraph should contain a page number field
        auto first_para = paras.get_item(0);
        ASSERT_NE(first_para, nullptr);
        bool found_page_field = false;
        for (const auto& child : first_para->get_children()) {
            if (child->node_type() == NodeType::FieldStart) {
                auto* f = dynamic_cast<Field*>(child.get());
                if (f && f->get_field_code() == "PAGE") {
                    found_page_field = true;
                    EXPECT_NE(f->get_switches_text().find("ROMAN"), std::string::npos);
                    break;
                }
            }
        }
        EXPECT_TRUE(found_page_field);

        // Second paragraph should contain a date field
        auto second_para = paras.get_item(1);
        ASSERT_NE(second_para, nullptr);
        bool found_date_field = false;
        for (const auto& child : second_para->get_children()) {
            if (child->node_type() == NodeType::FieldStart) {
                auto* f = dynamic_cast<Field*>(child.get());
                if (f && f->get_field_code() == "DATE") {
                    found_date_field = true;
                    EXPECT_NE(f->get_switches_text().find("yyyy-MM-dd"), std::string::npos);
                    break;
                }
            }
        }
        EXPECT_TRUE(found_date_field);
    }

    fs::remove(path);
}

TEST(FieldSwitchesTest, TableOfContentsUsesSwitches) {
    Document doc("test_field_toc.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.move_to_document_start();
    auto field = builder.insert_table_of_contents("\\o \"1-3\" \\h \\z");

    ASSERT_NE(field, nullptr);
    EXPECT_EQ(field->get_field_code(), "TOC");
    EXPECT_NE(field->get_switches_text().find("1-3"), std::string::npos);

}

TEST(FieldSwitchesTest, FieldClonePreservesSwitches) {
    auto field = std::make_shared<Field>();
    field->set_field_code("DATE");
    field->add_switch("\\@ \"dd/MM/yyyy\"");
    field->set_result("01/01/2026");

    auto cloned = std::dynamic_pointer_cast<Field>(field->clone(true));
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->get_field_code(), "DATE");
    EXPECT_EQ(cloned->get_switches_text(), "\\@ \"dd/MM/yyyy\"");
    EXPECT_EQ(cloned->get_result(), "01/01/2026");
}

// ============================================================================
// Extended Field API Tests
// ============================================================================

TEST(FieldSwitchesTest, InsertTimeField) {
    Document doc("test_field_time.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.move_to_document_start();
    auto field = builder.insert_time("\\@ \"HH:mm\"");

    ASSERT_NE(field, nullptr);
    EXPECT_EQ(field->get_type(), FieldType::Time);
    EXPECT_EQ(field->get_field_code(), "TIME");
    EXPECT_NE(field->get_switches_text().find("HH:mm"), std::string::npos);

}

TEST(FieldSwitchesTest, FieldLockedAndDirty) {
    auto field = std::make_shared<Field>();
    field->set_field_code("PAGE");

    EXPECT_FALSE(field->is_locked());
    EXPECT_TRUE(field->is_dirty());  // Default is dirty

    field->set_locked(true);
    field->set_dirty(false);

    EXPECT_TRUE(field->is_locked());
    EXPECT_FALSE(field->is_dirty());
}

TEST(FieldSwitchesTest, FieldUnlink) {
    auto field = std::make_shared<Field>(FieldType::MergeField);
    field->set_field_code("MERGEFIELD Name");
    field->set_result("Alice");

    // unlink() replaces the field with its result text
    field->unlink();
    EXPECT_EQ(field->get_text(), "Alice");
}

TEST(FieldSwitchesTest, FieldResultRoundTrip) {
    const std::string path = "test_field_result_rt.docx";

    {
        Document doc(path);
        ASSERT_TRUE(doc.create_empty());

        // Use pure DOM API (not DocumentBuilder) so the result is written
        // directly by sync_to_physical_tree() without dirty-XML merge issues.
        auto para = doc.get_first_section()->get_body()->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto field = std::make_shared<Field>(&doc, FieldType::Page);
        field->set_field_code("PAGE");
        field->set_result("42");
        para->append_child(field);
        doc.save();
    }

    {
        Document doc(path);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto paras = doc.get_paragraphs();
        ASSERT_GE(paras.get_count(), 1u);

        auto first_para = paras.get_item(0);
        ASSERT_NE(first_para, nullptr);

        bool found_result = false;
        for (const auto& child : first_para->get_children()) {
            if (child->node_type() == NodeType::FieldStart) {
                auto* f = dynamic_cast<Field*>(child.get());
                if (f && f->get_field_code() == "PAGE") {
                    EXPECT_EQ(f->get_result(), "42");
                    found_result = true;
                    break;
                }
            }
        }
        EXPECT_TRUE(found_result);
    }

    fs::remove(path);
}

TEST(FieldSwitchesTest, EmptyFieldCodeEdgeCase) {
    auto field = std::make_shared<Field>();
    field->set_field_code("");
    field->add_switch("\\* MERGEFORMAT");

    EXPECT_TRUE(field->get_field_code().empty());
    EXPECT_EQ(field->get_switches().size(), 1u);
    // get_full_field_code() does not prepend a space when field_code is empty
    EXPECT_EQ(field->get_full_field_code(), "\\* MERGEFORMAT");
}
