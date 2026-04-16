/**
 * @file 10_dom_sync_tests.cpp
 * @brief DOM-XML synchronization regression tests
 * @version 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <cstring>
#include <filesystem>
#include <fstream>

using namespace cdocx;
namespace fs = std::filesystem;

// ============================================================================
// Node Tree Traversal Tests
// ============================================================================

TEST(DomSyncTest, PreOrderTraversal) {
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

    ASSERT_GE(order.size(), 6u);
    EXPECT_EQ(order[0], NodeType::Body);
    EXPECT_EQ(order[1], NodeType::Paragraph);
    EXPECT_EQ(order[2], NodeType::Run);
    EXPECT_EQ(order[3], NodeType::Paragraph);
    EXPECT_EQ(order[4], NodeType::Run);

    fs::remove("test_traversal.docx");
}

TEST(DomSyncTest, LogicalNavigation) {
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

    fs::remove("test_logical.docx");
}

// ============================================================================
// Field Round-Trip Tests
// ============================================================================

TEST(DomSyncTest, FieldRoundTrip) {
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
                EXPECT_EQ(field->get_field_code(), " PAGE ");
                EXPECT_EQ(field->get_result(), "1");
                found_field = true;
                break;
            }
        }
        EXPECT_TRUE(found_field);
    }

    fs::remove("test_field.docx");
}

// ============================================================================
// Hyperlink Round-Trip Tests
// ============================================================================

TEST(DomSyncTest, HyperlinkRoundTrip) {
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

    fs::remove("test_hyperlink.docx");
}

TEST(DomSyncTest, HyperlinkBookmarkRoundTrip) {
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

    fs::remove("test_hyperlink_bm.docx");
}

// ============================================================================
// Unknown XML Node Preservation Tests
// ============================================================================

TEST(DomSyncTest, PreserveUnknownXmlNodes) {
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

    fs::remove("test_unknown.docx");
}
