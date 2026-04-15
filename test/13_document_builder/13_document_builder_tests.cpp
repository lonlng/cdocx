/**
 * @file 13_document_builder_tests.cpp
 * @brief DocumentBuilder unit tests
 * @version 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <cdocx/advanced.h>
#include <filesystem>

using namespace cdocx;
namespace fs = std::filesystem;

static std::string find_text_in_paragraphs(const ParagraphCollection& paras) {
    std::string all_text;
    for (int i = 0; i < static_cast<int>(paras.get_count()); ++i) {
        if (auto para = paras[i]) {
            all_text += para->get_text();
        }
    }
    return all_text;
}

static std::string get_test_image_path() {
    std::vector<std::string> candidates = {
        "test/05_complete_structure/data/test_export.png",
        "../test/05_complete_structure/data/test_export.png",
        "../../test/05_complete_structure/data/test_export.png",
    };
    for (const auto& path : candidates) {
        if (fs::exists(path)) {
            return path;
        }
    }
    return "";
}

// ============================================================================
// DocumentBuilder::insert_hyperlink Tests
// ============================================================================

TEST(DocumentBuilderTest, InsertHyperlink) {
    Document doc("test_builder_link.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.write("Visit ");
    builder.insert_hyperlink("Example", "https://example.com");
    builder.write(" for more info.");

    // Sync physical changes back to DOM before saving
    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_link.docx");
    doc2.open();

    auto text = find_text_in_paragraphs(doc2.get_paragraphs());
    EXPECT_NE(text.find("Visit"), std::string::npos);
    EXPECT_NE(text.find("Example"), std::string::npos);
    EXPECT_NE(text.find("for more info."), std::string::npos);

    // Check that hyperlink relationship exists
    auto* rels_xml = doc2.get_xml_part("word/_rels/document.xml.rels");
    ASSERT_NE(rels_xml, nullptr);

    bool found_rel = false;
    for (auto rel = rels_xml->child("Relationships").child("Relationship"); rel; rel = rel.next_sibling("Relationship")) {
        std::string type = rel.attribute("Type").value();
        std::string target = rel.attribute("Target").value();
        if (type.find("hyperlink") != std::string::npos && target == "https://example.com") {
            found_rel = true;
            break;
        }
    }
    EXPECT_TRUE(found_rel);

    doc2.close();
    fs::remove("test_builder_link.docx");
}

TEST(DocumentBuilderTest, InsertHyperlinkWithFormatting) {
    Document doc("test_builder_link_fmt.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.set_bold(true);
    builder.insert_hyperlink("Bold Link", "https://example.com");

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_link_fmt.docx");
    doc2.open();

    auto text = find_text_in_paragraphs(doc2.get_paragraphs());
    EXPECT_NE(text.find("Bold Link"), std::string::npos);

    doc2.close();
    fs::remove("test_builder_link_fmt.docx");
}

// ============================================================================
// DocumentBuilder::insert_image Tests
// ============================================================================

TEST(DocumentBuilderTest, InsertImageWithAutoSize) {
    std::string image_path = get_test_image_path();
    if (image_path.empty()) {
        GTEST_SKIP() << "Test image not found, skipping image insertion test";
    }

    Document doc("test_builder_image.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.write("Here is an image: ");
    bool result = builder.insert_image(image_path);
    EXPECT_TRUE(result);
    builder.write(" End of text.");

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_image.docx");
    doc2.open();

    // Check that image relationship exists
    auto* rels_xml = doc2.get_xml_part("word/_rels/document.xml.rels");
    ASSERT_NE(rels_xml, nullptr);

    bool found_image_rel = false;
    for (auto rel = rels_xml->child("Relationships").child("Relationship"); rel; rel = rel.next_sibling("Relationship")) {
        std::string type = rel.attribute("Type").value();
        if (type.find("image") != std::string::npos) {
            found_image_rel = true;
            break;
        }
    }
    EXPECT_TRUE(found_image_rel);

    // Check that drawing element exists in document XML
    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);

    bool found_drawing = false;
    for (auto p = doc_xml->child("w:document").child("w:body").child("w:p"); p; p = p.next_sibling("w:p")) {
        for (auto r = p.child("w:r"); r; r = r.next_sibling("w:r")) {
            if (r.child("w:drawing")) {
                found_drawing = true;
                break;
            }
        }
        if (found_drawing) break;
    }
    EXPECT_TRUE(found_drawing);

    doc2.close();
    fs::remove("test_builder_image.docx");
}

TEST(DocumentBuilderTest, InsertImageWithExplicitSize) {
    std::string image_path = get_test_image_path();
    if (image_path.empty()) {
        GTEST_SKIP() << "Test image not found, skipping image insertion test";
    }

    Document doc("test_builder_image_size.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    bool result = builder.insert_image(image_path, 100.0, 80.0);
    EXPECT_TRUE(result);

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_image_size.docx");
    doc2.open();

    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);

    bool found_drawing = false;
    int64_t expected_cx = static_cast<int64_t>(100.0 * 12700);
    int64_t expected_cy = static_cast<int64_t>(80.0 * 12700);

    for (auto p = doc_xml->child("w:document").child("w:body").child("w:p"); p; p = p.next_sibling("w:p")) {
        for (auto r = p.child("w:r"); r; r = r.next_sibling("w:r")) {
            auto drawing = r.child("w:drawing");
            if (drawing) {
                auto inline_node = drawing.child("wp:inline");
                if (inline_node) {
                    auto extent = inline_node.child("wp:extent");
                    if (extent) {
                        int64_t cx = extent.attribute("cx").as_llong();
                        int64_t cy = extent.attribute("cy").as_llong();
                        if (cx == expected_cx && cy == expected_cy) {
                            found_drawing = true;
                        }
                    }
                }
            }
        }
        if (found_drawing) break;
    }
    EXPECT_TRUE(found_drawing);

    doc2.close();
    fs::remove("test_builder_image_size.docx");
}

TEST(DocumentBuilderTest, InsertImageMissingFile) {
    Document doc("test_builder_image_missing.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    bool result = builder.insert_image("nonexistent_image.png");
    EXPECT_FALSE(result);

    fs::remove("test_builder_image_missing.docx");
}

// ============================================================================
// DocumentBuilder Basic Operations Tests
// ============================================================================

TEST(DocumentBuilderTest, WriteAndFormat) {
    Document doc("test_builder_basic.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.set_bold(true);
    builder.write("Bold ");
    builder.clear_formatting();
    builder.write("Normal");

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_basic.docx");
    doc2.open();

    auto text = find_text_in_paragraphs(doc2.get_paragraphs());
    EXPECT_NE(text.find("Bold"), std::string::npos);
    EXPECT_NE(text.find("Normal"), std::string::npos);

    doc2.close();
    fs::remove("test_builder_basic.docx");
}

TEST(DocumentBuilderTest, TableBuilding) {
    Document doc("test_builder_table.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.start_table();
    builder.insert_row();
    builder.insert_cell();
    builder.write("A1");
    builder.insert_cell();
    builder.write("A2");
    builder.end_row();
    builder.insert_row();
    builder.insert_cell();
    builder.write("B1");
    builder.insert_cell();
    builder.write("B2");
    builder.end_row();
    builder.end_table();

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_table.docx");
    doc2.open();

    auto tables = doc2.get_tables();
    ASSERT_GT(tables.get_count(), 0);
    EXPECT_EQ(tables[0]->get_row_count(), 2);

    doc2.close();
    fs::remove("test_builder_table.docx");
}
