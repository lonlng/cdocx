/**
 * @file 10_dom_sync_tests.cpp
 * @brief DOM-XML synchronization regression tests
 * @version 0.8.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include "../test_helpers.h"
#include <cstring>
#include <filesystem>
#include <fstream>

using namespace cdocx;
namespace fs = std::filesystem;
using cdocx::test::TempDoc;

// ============================================================================
// Node Tree Traversal Tests
// ============================================================================

TEST(DomSyncTest, PreOrderTraversal) {
    TempDoc temp_doc("test_traversal.docx");
    Document doc("test_traversal.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);
    auto body = sect->get_body();
    ASSERT_NE(body, nullptr);

    auto para1 = body->append_paragraph("First");
    auto run1 = para1->append_run("Run1");
    auto para2 = body->append_paragraph("Second");
    auto run2 = para2->append_run("Run2");

    std::vector<NodeType> order;
    auto current = std::static_pointer_cast<Node>(body);
    while (current) {
        order.push_back(current->node_type());
        current = current->get_next_node_in_document();
    }

    ASSERT_GE(order.size(), 7u);
    EXPECT_EQ(order[0], NodeType::Body);
    EXPECT_EQ(order[1], NodeType::Paragraph);
    EXPECT_EQ(order[2], NodeType::Run);
    EXPECT_EQ(order[3], NodeType::Run);
    EXPECT_EQ(order[4], NodeType::Paragraph);
    EXPECT_EQ(order[5], NodeType::Run);
    EXPECT_EQ(order[6], NodeType::Run);

}

TEST(DomSyncTest, LogicalNavigation) {
    TempDoc temp_doc("test_logical.docx");
    Document doc("test_logical.docx");
    ASSERT_TRUE(doc.create_empty());

    auto sect = doc.get_first_section();
    ASSERT_NE(sect, nullptr);
    auto body = sect->get_body();
    ASSERT_NE(body, nullptr);

    // Remove the default empty paragraph so we control the content
    body->remove_all_children();

    auto para1 = body->append_paragraph("First");
    auto para2 = body->append_paragraph("Second");
    auto para3 = body->append_paragraph("Third");

    // Forward logical navigation (sibling-based)
    EXPECT_EQ(para1->get_next_logical(), para2);
    EXPECT_EQ(para2->get_next_logical(), para3);
    EXPECT_EQ(para3->get_next_logical(), nullptr);

    // Backward logical navigation (sibling-based)
    EXPECT_EQ(para3->get_previous_logical(), para2);
    EXPECT_EQ(para2->get_previous_logical(), para1);
    EXPECT_EQ(para1->get_previous_logical(), nullptr);

}

// ============================================================================
// Field Round-Trip Tests
// ============================================================================

TEST(DomSyncTest, FieldRoundTrip) {
    TempDoc temp_doc("test_field.docx");
    {
        Document doc("test_field.docx");
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto para = body->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto field = para->append_field(FieldType::Page);
        field->set_field_code(" PAGE ");
        field->set_result("1");

        doc.save();
    }

    {
        Document doc("test_field.docx");
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto para = body->get_first_paragraph();
        ASSERT_NE(para, nullptr);

        auto children = para->get_children();
        bool found_field = false;
        for (const auto& child : children) {
            if (child->node_type() == NodeType::FieldStart) {
                auto field = std::dynamic_pointer_cast<Field>(child);
                ASSERT_NE(field, nullptr);
                EXPECT_EQ(field->get_field_code(), "PAGE");
                EXPECT_EQ(field->get_result(), "1");
                found_field = true;
                break;
            }
        }
        EXPECT_TRUE(found_field);
    }

}

// ============================================================================
// Hyperlink Round-Trip Tests
// ============================================================================

TEST(DomSyncTest, HyperlinkRoundTrip) {
    TempDoc temp_doc("test_hyperlink.docx");
    {
        Document doc("test_hyperlink.docx");
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto para = body->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto link = std::make_shared<Hyperlink>(&doc);
        link->set_address("https://example.com");
        link->set_tooltip("Example tooltip");
        link->set_result("Click here");
        link->set_bold(true);
        para->append_child(link);

        doc.save();
    }

    {
        Document doc("test_hyperlink.docx");
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto para = body->get_first_paragraph();
        ASSERT_NE(para, nullptr);

        auto children = para->get_children();
        bool found_link = false;
        for (const auto& child : children) {
            if (child->node_type() == NodeType::Hyperlink) {
                auto link = std::dynamic_pointer_cast<Hyperlink>(child);
                ASSERT_NE(link, nullptr);
                EXPECT_EQ(link->get_address(), "https://example.com");
                EXPECT_EQ(link->get_tooltip(), "Example tooltip");
                EXPECT_EQ(link->get_result(), "Click here");
                EXPECT_TRUE(link->get_font().bold);
                found_link = true;
                break;
            }
        }
        EXPECT_TRUE(found_link);
    }

}

TEST(DomSyncTest, HyperlinkBookmarkRoundTrip) {
    TempDoc temp_doc("test_hyperlink_bm.docx");
    {
        Document doc("test_hyperlink_bm.docx");
        ASSERT_TRUE(doc.create_empty());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto para = body->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto link = std::make_shared<Hyperlink>(&doc);
        link->set_bookmark_name("_Toc1");
        link->set_result("Go to TOC");
        para->append_child(link);

        doc.save();
    }

    {
        Document doc("test_hyperlink_bm.docx");
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto body = sect->get_body();
        ASSERT_NE(body, nullptr);

        auto para = body->get_first_paragraph();
        ASSERT_NE(para, nullptr);

        auto children = para->get_children();
        bool found_link = false;
        for (const auto& child : children) {
            if (child->node_type() == NodeType::Hyperlink) {
                auto link = std::dynamic_pointer_cast<Hyperlink>(child);
                ASSERT_NE(link, nullptr);
                EXPECT_EQ(link->get_bookmark_name(), "_Toc1");
                EXPECT_EQ(link->get_result(), "Go to TOC");
                found_link = true;
                break;
            }
        }
        EXPECT_TRUE(found_link);
    }

}

// ============================================================================
// Unknown XML Node Preservation Tests
// ============================================================================

TEST(DomSyncTest, PreserveUnknownXmlNodes) {
    TempDoc temp_doc("test_unknown.docx");
    {
        Document doc("test_unknown.docx");
        ASSERT_TRUE(doc.create_empty());

        // Manually inject an unknown node into the body via XML API
        auto doc_xml = doc.get_document_xml();
        ASSERT_NE(doc_xml, nullptr);
        auto body = doc_xml->child("w:document").child("w:body");
        ASSERT_NE(body, nullptr);

        auto custom = body.prepend_child("w:customXml");
        custom.append_attribute("w:uri").set_value("http://example.com");
        custom.append_attribute("w:element").set_value("custom");
        doc.mark_modified("word/document.xml");

        // Add a paragraph so the body isn't empty after DOM sync
        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        auto dom_body = sect->get_body();
        ASSERT_NE(dom_body, nullptr);
        dom_body->append_paragraph("Hello");

        doc.save();
    }

    {
        Document doc("test_unknown.docx");
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto doc_xml = doc.get_document_xml();
        ASSERT_NE(doc_xml, nullptr);
        auto body = doc_xml->child("w:document").child("w:body");
        ASSERT_NE(body, nullptr);

        bool found_custom = false;
        for (auto child = body.first_child(); child; child = child.next_sibling()) {
            if (std::strcmp(child.name(), "w:customXml") == 0) {
                found_custom = true;
                EXPECT_STREQ(child.attribute("w:uri").value(), "http://example.com");
                EXPECT_STREQ(child.attribute("w:element").value(), "custom");
                break;
            }
        }
        EXPECT_TRUE(found_custom);
    }

}

// ============================================================================
// Enum Mapping Round-Trip Tests
// ============================================================================

TEST(DomSyncTest, CellVerticalAlignmentRoundTrip) {
    TempDoc temp_doc("test_cell_valign.docx");
    const std::string& test_file = temp_doc.path();

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto table = doc.get_first_section()->get_body()->append_table(1, 3);
        table->get_cell(0, 0)->get_cell_format().vertical_alignment = CellVerticalAlignment::Top;
        table->get_cell(0, 1)->get_cell_format().vertical_alignment = CellVerticalAlignment::Center;
        table->get_cell(0, 2)->get_cell_format().vertical_alignment = CellVerticalAlignment::Bottom;

        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto table = doc.get_first_section()->get_body()->get_first_table();
        ASSERT_NE(table, nullptr);

        EXPECT_EQ(table->get_cell(0, 0)->get_cell_format().vertical_alignment,
                  CellVerticalAlignment::Top);
        EXPECT_EQ(table->get_cell(0, 1)->get_cell_format().vertical_alignment,
                  CellVerticalAlignment::Center);
        EXPECT_EQ(table->get_cell(0, 2)->get_cell_format().vertical_alignment,
                  CellVerticalAlignment::Bottom);
    }

}

TEST(DomSyncTest, TableAlignmentRoundTrip) {
    TempDoc temp_doc("test_tbl_align.docx");
    const std::string& test_file = temp_doc.path();

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto t1 = doc.get_first_section()->get_body()->append_table(1, 1);
        t1->get_table_format().alignment = TableAlignment::Left;

        auto t2 = doc.get_first_section()->get_body()->append_table(1, 1);
        t2->get_table_format().alignment = TableAlignment::Center;

        auto t3 = doc.get_first_section()->get_body()->append_table(1, 1);
        t3->get_table_format().alignment = TableAlignment::Right;

        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto body = doc.get_first_section()->get_body();
        auto children = body->get_children();
        ASSERT_GE(children.size(), 3u);

        // Find tables among children (body may contain placeholder paragraphs)
        std::vector<std::shared_ptr<Table>> tables;
        for (const auto& child : children) {
            if (auto tbl = std::dynamic_pointer_cast<Table>(child)) {
                tables.push_back(tbl);
            }
        }
        ASSERT_EQ(tables.size(), 3u);

        EXPECT_EQ(tables[0]->get_table_format().alignment, TableAlignment::Left);
        EXPECT_EQ(tables[1]->get_table_format().alignment, TableAlignment::Center);
        EXPECT_EQ(tables[2]->get_table_format().alignment, TableAlignment::Right);
    }

}

TEST(DomSyncTest, ScriptTypeRoundTrip) {
    TempDoc temp_doc("test_script.docx");
    const std::string& test_file = temp_doc.path();

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto para = doc.get_first_section()->get_body()->append_paragraph();
        auto run1 = para->append_run("Normal");
        run1->get_font().script_type = ScriptType::Normal;

        auto run2 = para->append_run("Superscript");
        run2->get_font().script_type = ScriptType::Superscript;

        auto run3 = para->append_run("Subscript");
        run3->get_font().script_type = ScriptType::Subscript;

        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto para = doc.get_first_section()->get_body()->get_last_paragraph();
        ASSERT_NE(para, nullptr);

        auto runs = para->get_runs();
        ASSERT_EQ(runs.get_count(), 3u);

        EXPECT_EQ(runs[0]->get_font().script_type, ScriptType::Normal);
        EXPECT_EQ(runs[1]->get_font().script_type, ScriptType::Superscript);
        EXPECT_EQ(runs[2]->get_font().script_type, ScriptType::Subscript);
    }

}

TEST(DomSyncTest, LineSpacingRuleRoundTrip) {
    TempDoc temp_doc("test_line_rule.docx");
    const std::string& test_file = temp_doc.path();

    {
        Document doc;
        ASSERT_TRUE(doc.create_empty(test_file));

        auto p1 = doc.get_first_section()->get_body()->append_paragraph("Auto");
        p1->get_paragraph_format().line_spacing_rule = LineSpacingRule::Auto;
        p1->get_paragraph_format().line_spacing = 1.5;

        auto p2 = doc.get_first_section()->get_body()->append_paragraph("Exact");
        p2->get_paragraph_format().line_spacing_rule = LineSpacingRule::Exact;
        p2->get_paragraph_format().line_spacing = 20.0;

        auto p3 = doc.get_first_section()->get_body()->append_paragraph("AtLeast");
        p3->get_paragraph_format().line_spacing_rule = LineSpacingRule::AtLeast;
        p3->get_paragraph_format().line_spacing = 24.0;

        doc.save();
    }

    {
        Document doc(test_file);
        doc.open();
        ASSERT_TRUE(doc.is_open());

        auto body = doc.get_first_section()->get_body();
        auto children = body->get_children();
        ASSERT_GE(children.size(), 3u);

        auto p1 = std::dynamic_pointer_cast<Paragraph>(children[0]);
        auto p2 = std::dynamic_pointer_cast<Paragraph>(children[1]);
        auto p3 = std::dynamic_pointer_cast<Paragraph>(children[2]);

        ASSERT_NE(p1, nullptr);
        ASSERT_NE(p2, nullptr);
        ASSERT_NE(p3, nullptr);

        EXPECT_EQ(p1->get_paragraph_format().line_spacing_rule, LineSpacingRule::Auto);
        EXPECT_EQ(p2->get_paragraph_format().line_spacing_rule, LineSpacingRule::Exact);
        EXPECT_EQ(p3->get_paragraph_format().line_spacing_rule, LineSpacingRule::AtLeast);
    }
}

// ============================================================================
// Paragraph Convenience Methods Round-Trip
// ============================================================================

TEST(DomSyncTest, ParagraphAppendHyperlinkRoundTrip) {
    TempDoc temp("test_para_hyperlink_rt.docx");

    {
        Document doc(temp.path());
        ASSERT_TRUE(doc.create_empty());
        auto para = doc.get_first_section()->get_body()->append_paragraph();
        auto link = para->append_hyperlink("Click here", "https://example.com");
        ASSERT_NE(link, nullptr);
        EXPECT_EQ(link->get_address(), "https://example.com");
        EXPECT_EQ(link->get_result(), "Click here");
        doc.save();
    }

    {
        Document doc(temp.path());
        doc.open();
        ASSERT_TRUE(doc.is_open());
        auto para = doc.get_first_section()->get_body()->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto children = para->get_children();
        ASSERT_EQ(children.size(), 1u);
        auto link = std::dynamic_pointer_cast<Hyperlink>(children[0]);
        ASSERT_NE(link, nullptr);
        EXPECT_EQ(link->get_address(), "https://example.com");
        EXPECT_EQ(link->get_result(), "Click here");
    }
}

TEST(DomSyncTest, ParagraphAppendPageNumberRoundTrip) {
    TempDoc temp("test_para_pagenum_rt.docx");

    {
        Document doc(temp.path());
        ASSERT_TRUE(doc.create_empty());
        auto para = doc.get_first_section()->get_body()->append_paragraph();
        auto field = para->append_page_number("\\* ROMAN");
        ASSERT_NE(field, nullptr);
        EXPECT_EQ(field->get_type(), FieldType::Page);
        EXPECT_EQ(field->get_field_code(), "PAGE");
        doc.save();
    }

    {
        Document doc(temp.path());
        doc.open();
        ASSERT_TRUE(doc.is_open());
        auto para = doc.get_first_section()->get_body()->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto fields = para->get_fields();
        ASSERT_EQ(fields.size(), 1u);
        // Note: field type is not preserved on round-trip (parsed as Unknown)
        EXPECT_EQ(fields[0]->get_field_code(), "PAGE");
    }
}

TEST(DomSyncTest, ParagraphAppendDateRoundTrip) {
    TempDoc temp("test_para_date_rt.docx");

    {
        Document doc(temp.path());
        ASSERT_TRUE(doc.create_empty());
        auto para = doc.get_first_section()->get_body()->append_paragraph();
        auto field = para->append_date("\\@ \"yyyy-MM-dd\"");
        ASSERT_NE(field, nullptr);
        EXPECT_EQ(field->get_type(), FieldType::Date);
        EXPECT_EQ(field->get_field_code(), "DATE");
        doc.save();
    }

    {
        Document doc(temp.path());
        doc.open();
        ASSERT_TRUE(doc.is_open());
        auto para = doc.get_first_section()->get_body()->get_first_paragraph();
        ASSERT_NE(para, nullptr);
        auto fields = para->get_fields();
        ASSERT_EQ(fields.size(), 1u);
        // Note: field type is not preserved on round-trip (parsed as Unknown)
        EXPECT_EQ(fields[0]->get_field_code(), "DATE");
    }
}

TEST(DomSyncTest, SectionEnsureHeaderFooter) {
    TempDoc temp("test_ensure_hf.docx");

    {
        Document doc(temp.path());
        ASSERT_TRUE(doc.create_empty());
        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);

        auto h1 = sect->ensure_header();
        ASSERT_NE(h1, nullptr);
        h1->append_paragraph("Header text");

        auto h2 = sect->ensure_header();
        EXPECT_EQ(h1.get(), h2.get());

        auto f1 = sect->ensure_footer();
        ASSERT_NE(f1, nullptr);
        f1->append_paragraph("Footer text");

        auto f2 = sect->ensure_footer();
        EXPECT_EQ(f1.get(), f2.get());

        doc.save();
    }

    {
        Document doc(temp.path());
        doc.open();
        ASSERT_TRUE(doc.is_open());
        auto sect = doc.get_first_section();
        ASSERT_NE(sect, nullptr);
        EXPECT_TRUE(sect->has_header());
        EXPECT_TRUE(sect->has_footer());
    }
}
