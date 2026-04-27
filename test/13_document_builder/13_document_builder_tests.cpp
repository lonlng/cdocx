/**
 * @file 13_document_builder_tests.cpp
 * @brief DocumentBuilder unit tests
 * @version 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include "../test_helpers.h"
#include <cdocx/advanced.h>
#include <filesystem>

using namespace cdocx;
namespace fs = std::filesystem;
using cdocx::test::TempDoc;

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
    TempDoc temp_doc("test_builder_link.docx");
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
}

TEST(DocumentBuilderTest, InsertHyperlinkWithFormatting) {
    TempDoc temp_doc("test_builder_link_fmt.docx");
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
}

// ============================================================================
// DocumentBuilder::insert_image Tests
// ============================================================================

TEST(DocumentBuilderTest, InsertImageWithAutoSize) {
    std::string image_path = get_test_image_path();
    if (image_path.empty()) {
        GTEST_SKIP() << "Test image not found, skipping image insertion test";
    }

    TempDoc temp_doc("test_builder_image.docx");
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
}

TEST(DocumentBuilderTest, InsertImageWithExplicitSize) {
    std::string image_path = get_test_image_path();
    if (image_path.empty()) {
        GTEST_SKIP() << "Test image not found, skipping image insertion test";
    }

    TempDoc temp_doc("test_builder_image_size.docx");
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
}

TEST(DocumentBuilderTest, InsertImageMissingFile) {
    TempDoc temp_doc("test_builder_image_missing.docx");
    Document doc("test_builder_image_missing.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    bool result = builder.insert_image("nonexistent_image.png");
    EXPECT_FALSE(result);

}

// ============================================================================
// DocumentBuilder Basic Operations Tests
// ============================================================================

TEST(DocumentBuilderTest, WriteAndFormat) {
    TempDoc temp_doc("test_builder_basic.docx");
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
}

TEST(DocumentBuilderTest, TableBuilding) {
    TempDoc temp_doc("test_builder_table.docx");
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
}

// ============================================================================
// DocumentBuilder Fluent Chaining Tests
// ============================================================================

TEST(DocumentBuilderTest, FluentChaining) {
    TempDoc temp_doc("test_builder_fluent.docx");
    Document doc("test_builder_fluent.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.move_to_document_start()
           .set_bold(true)
           .set_font_size(24)
           .writeln("Title")
           .clear_formatting()
           .write("Normal text ")
           .set_italic(true)
           .write("italic")
           .clear_formatting()
           .writeln(".");

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_fluent.docx");
    doc2.open();

    auto text = find_text_in_paragraphs(doc2.get_paragraphs());
    EXPECT_NE(text.find("Title"), std::string::npos);
    EXPECT_NE(text.find("Normal text italic"), std::string::npos);

    doc2.close();
}

TEST(DocumentBuilderTest, FluentTableAndBookmark) {
    TempDoc temp_doc("test_builder_fluent_table.docx");
    Document doc("test_builder_fluent_table.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.start_bookmark("TableStart")
           .start_table()
           .insert_row()
           .insert_cell()
           .write("Cell 1")
           .insert_cell()
           .write("Cell 2")
           .end_row()
           .end_table()
           .end_bookmark("TableStart");

    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_builder_fluent_table.docx");
    doc2.open();

    auto tables = doc2.get_tables();
    ASSERT_GT(tables.get_count(), 0);

    auto bookmarks = doc2.get_bookmarks();
    EXPECT_TRUE(bookmarks.contains("TableStart"));

    doc2.close();
}

// ============================================================================
// CDocx Factory Tests
// ============================================================================

TEST(CDocxFactoryTest, CreateDocument) {
    auto doc = CDocx::create_document();
    ASSERT_NE(doc, nullptr);
    EXPECT_TRUE(doc->is_open());
}

TEST(CDocxFactoryTest, VersionInfo) {
    EXPECT_EQ(CDocx::version(), "0.8.0");
    EXPECT_NE(CDocx::version_string().find("CDocx"), std::string::npos);
    EXPECT_NE(CDocx::version_string().find("0.8.0"), std::string::npos);
}

TEST(CDocxFactoryTest, DocumentBuilderFactory) {
    auto builder = CDocx::document();
    ASSERT_NE(builder, nullptr);
    builder->write("Hello from factory");
}

TEST(CDocxFactoryTest, TableBuilderFactory) {
    auto table = CDocx::table(2, 3);
    ASSERT_NE(table, nullptr);
    auto& ref = table->set_cell_text(0, 0, "A1").set_cell_text(1, 2, "B3");
    EXPECT_EQ(&ref, table.get());
}

// ============================================================================
// ParagraphBuilder Tests
// ============================================================================

TEST(ParagraphBuilderTest, BuildSimpleParagraph) {
    auto para = cdocx::ParagraphBuilder()
        .add_run("Hello, ")
        .add_run("World!")
        .build();

    ASSERT_NE(para, nullptr);
    EXPECT_EQ(para->get_text(), "Hello, World!");
}

TEST(ParagraphBuilderTest, BuildFormattedParagraph) {
    auto para = cdocx::ParagraphBuilder()
        .add_run("Bold ", true, false, 0)
        .add_run("and ")
        .set_bold(true)
        .set_italic(true)
        .add_run("bold-italic")
        .clear_formatting()
        .add_run(" normal")
        .set_alignment("center")
        .build();

    ASSERT_NE(para, nullptr);
    EXPECT_EQ(para->get_text(), "Bold and bold-italic normal");
}

TEST(ParagraphBuilderTest, InitialTextConstructor) {
    auto para = cdocx::ParagraphBuilder("Initial text").build();
    ASSERT_NE(para, nullptr);
    EXPECT_EQ(para->get_text(), "Initial text");
}

// ============================================================================
// Document::ensure_minimum Tests
// ============================================================================

TEST(DocumentEnsureMinimumTest, CreatesSectionAndParagraph) {
    auto doc = CDocx::create_document();
    ASSERT_NE(doc, nullptr);

    // Document from factory already has content, but let's verify ensure_minimum
    doc->ensure_minimum();

    EXPECT_GT(doc->get_section_count(), 0u);
    auto paras = doc->get_paragraphs();
    EXPECT_GT(paras.get_count(), 0u);
}

// ============================================================================
// Document::get_range Tests
// ============================================================================

TEST(DocumentRangeTest, GetRangeText) {
    TempDoc temp_doc("test_range.docx");
    Document doc("test_range.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.write("Hello").insert_break(BreakType::ParagraphBreak).write("World");
    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_range.docx");
    doc2.open();

    auto range = doc2.get_range();
    auto text = range.get_text();
    EXPECT_NE(text.find("Hello"), std::string::npos);
    EXPECT_NE(text.find("World"), std::string::npos);

    doc2.close();
}

TEST(DocumentRangeTest, RangeReplaceAll) {
    TempDoc temp_doc("test_range_replace.docx");
    Document doc("test_range_replace.docx");
    ASSERT_TRUE(doc.create_empty());

    DocumentBuilder builder(&doc);
    builder.write("Hello Hello");
    doc.sync_from_physical_tree();
    doc.save();

    Document doc2("test_range_replace.docx");
    doc2.open();

    auto range = doc2.get_range();
    int count = range.replace_all("Hello", "Hi");
    EXPECT_GT(count, 0);

    auto text = range.get_text();
    EXPECT_NE(text.find("Hi"), std::string::npos);
    EXPECT_EQ(text.find("Hello"), std::string::npos);

    doc2.close();
}

// ============================================================================
// ConvertUtil Tests
// ============================================================================

TEST(ConvertUtilTest, PointToInch) {
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::inch_to_point(1.0), 72.0);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::point_to_inch(72.0), 1.0);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::point_to_inch(144.0), 2.0);
}

TEST(ConvertUtilTest, MillimeterToPoint) {
    double a4_width = cdocx::ConvertUtil::millimeter_to_point(210.0);
    EXPECT_NEAR(a4_width, 595.276, 0.1);

    double a4_height = cdocx::ConvertUtil::millimeter_to_point(297.0);
    EXPECT_NEAR(a4_height, 841.89, 0.1);
}

TEST(ConvertUtilTest, CentimeterToPoint) {
    EXPECT_NEAR(cdocx::ConvertUtil::centimeter_to_point(2.54), 72.0, 0.01);
    EXPECT_NEAR(cdocx::ConvertUtil::point_to_centimeter(72.0), 2.54, 0.01);
}

TEST(ConvertUtilTest, PointToPixel) {
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::point_to_pixel(72.0), 96.0);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::pixel_to_point(96.0), 72.0);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::point_to_pixel(72.0, 300.0), 300.0);
}

TEST(ConvertUtilTest, PointToTwips) {
    EXPECT_EQ(cdocx::ConvertUtil::point_to_twips(72.0), 1440);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::twips_to_point(1440), 72.0);
}

TEST(ConvertUtilTest, PixelToNewDpi) {
    EXPECT_EQ(cdocx::ConvertUtil::pixel_to_new_dpi(96.0, 96.0, 192.0), 192);
    EXPECT_EQ(cdocx::ConvertUtil::pixel_to_new_dpi(100.0, 96.0, 48.0), 50);
}

TEST(ConvertUtilTest, CommonPaperSizes) {
    EXPECT_NEAR(cdocx::ConvertUtil::a4_width(), 595.276, 0.1);
    EXPECT_NEAR(cdocx::ConvertUtil::a4_height(), 841.89, 0.1);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::letter_width(), 612.0);
    EXPECT_DOUBLE_EQ(cdocx::ConvertUtil::letter_height(), 792.0);
}

// ============================================================================
// ControlChar Tests
// ============================================================================

TEST(ControlCharTest, Constants) {
    EXPECT_EQ(cdocx::ControlChar::tab(), std::string("\t"));
    EXPECT_EQ(cdocx::ControlChar::line_feed(), std::string("\n"));
    EXPECT_EQ(cdocx::ControlChar::paragraph_break(), std::string("\r"));
    EXPECT_EQ(cdocx::ControlChar::page_break(), std::string("\f"));
    EXPECT_EQ(cdocx::ControlChar::section_break(), std::string("\f"));
    EXPECT_EQ(cdocx::ControlChar::column_break(), std::string(1, '\x0e'));
    EXPECT_EQ(cdocx::ControlChar::non_breaking_space(), std::string(1, '\xa0'));
    EXPECT_EQ(cdocx::ControlChar::crlf(), std::string("\r\n"));
}

TEST(ControlCharTest, CharConstants) {
    EXPECT_EQ(cdocx::ControlChar::kTabChar, '\t');
    EXPECT_EQ(cdocx::ControlChar::kLineFeedChar, '\n');
    EXPECT_EQ(cdocx::ControlChar::kParagraphBreakChar, '\r');
    EXPECT_EQ(cdocx::ControlChar::kPageBreakChar, '\f');
    EXPECT_EQ(cdocx::ControlChar::kColumnBreakChar, '\x0e');
    EXPECT_EQ(cdocx::ControlChar::kNonBreakingSpaceChar, '\xa0');
    EXPECT_EQ(cdocx::ControlChar::kCellChar, '\x07');
}

// ============================================================================
// FileFormatUtil Tests
// ============================================================================

TEST(FileFormatUtilTest, DetectDocxFile) {
    TempDoc temp_doc("test_format_detect.docx");
    Document doc("test_format_detect.docx");
    ASSERT_TRUE(doc.create_empty());
    doc.save();

    auto info = cdocx::FileFormatUtil::detect_file_format("test_format_detect.docx");
    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->load_format(), cdocx::LoadFormat::Docx);
    EXPECT_FALSE(info->is_encrypted());

}

TEST(FileFormatUtilTest, DetectMissingFile) {
    auto info = cdocx::FileFormatUtil::detect_file_format("nonexistent_file.xyz");
    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->load_format(), cdocx::LoadFormat::Unknown);
}

TEST(FileFormatUtilTest, FormatToExtension) {
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Docx), ".docx");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Docm), ".docm");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Dotx), ".dotx");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Rtf), ".rtf");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Html), ".html");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Text), ".txt");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Markdown), ".md");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Xml), ".xml");
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_extension(cdocx::LoadFormat::Unknown), "");

    EXPECT_EQ(cdocx::FileFormatUtil::save_format_to_extension(cdocx::SaveFormat::Odt), ".odt");
}

TEST(FileFormatUtilTest, ExtensionToSaveFormat) {
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format("docx"), cdocx::SaveFormat::Docx);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".docx"), cdocx::SaveFormat::Docx);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".html"), cdocx::SaveFormat::Html);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".htm"), cdocx::SaveFormat::Html);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".md"), cdocx::SaveFormat::Markdown);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".rtf"), cdocx::SaveFormat::Rtf);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".txt"), cdocx::SaveFormat::Text);
    EXPECT_EQ(cdocx::FileFormatUtil::extension_to_save_format(".unknown"), cdocx::SaveFormat::Unknown);
}

TEST(FileFormatUtilTest, FormatConversions) {
    EXPECT_EQ(cdocx::FileFormatUtil::save_format_to_load_format(cdocx::SaveFormat::Docx), cdocx::LoadFormat::Docx);
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_save_format(cdocx::LoadFormat::Docx), cdocx::SaveFormat::Docx);
    EXPECT_EQ(cdocx::FileFormatUtil::save_format_to_load_format(cdocx::SaveFormat::Unknown), cdocx::LoadFormat::Unknown);
    EXPECT_EQ(cdocx::FileFormatUtil::load_format_to_save_format(cdocx::LoadFormat::Unknown), cdocx::SaveFormat::Unknown);
}

TEST(FileFormatUtilTest, DetectFromBuffer) {
    // HTML
    std::string html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></head></html>";
    std::vector<uint8_t> html_data(html.begin(), html.end());
    auto html_info = cdocx::FileFormatUtil::detect_file_format(html_data);
    EXPECT_EQ(html_info->load_format(), cdocx::LoadFormat::Html);
    EXPECT_EQ(html_info->encoding(), "UTF-8");

    // RTF
    std::string rtf = "{\\rtf1\\ansi test}";
    std::vector<uint8_t> rtf_data(rtf.begin(), rtf.end());
    auto rtf_info = cdocx::FileFormatUtil::detect_file_format(rtf_data);
    EXPECT_EQ(rtf_info->load_format(), cdocx::LoadFormat::Rtf);

    // Plain text
    std::string text = "This is plain text content.";
    std::vector<uint8_t> text_data(text.begin(), text.end());
    auto text_info = cdocx::FileFormatUtil::detect_file_format(text_data);
    EXPECT_EQ(text_info->load_format(), cdocx::LoadFormat::Text);

    // XML
    std::string xml = "<?xml version=\"1.0\"?><root/>";
    std::vector<uint8_t> xml_data(xml.begin(), xml.end());
    auto xml_info = cdocx::FileFormatUtil::detect_file_format(xml_data);
    EXPECT_EQ(xml_info->load_format(), cdocx::LoadFormat::Xml);
}

// ============================================================================
// Shading Serialization Tests
// ============================================================================

TEST(ShadingSyncTest, ParagraphShadingRoundTrip) {
    TempDoc temp_doc("test_shading_para.docx");
    Document doc("test_shading_para.docx");
    ASSERT_TRUE(doc.create_empty());

    auto para = doc.get_first_section()->get_body()->append_paragraph("Shaded paragraph");
    para->get_paragraph_format().shading.set_solid_fill(cdocx::Color::from_hex("FFCC00"));

    doc.sync_to_physical_tree();
    doc.save();

    Document doc2("test_shading_para.docx");
    doc2.open();
    auto paras = doc2.get_paragraphs();
    std::shared_ptr<cdocx::Paragraph> target_para;
    for (size_t i = 0; i < paras.get_count(); ++i) {
        if (paras[i]->get_text() == "Shaded paragraph") {
            target_para = paras[i];
            break;
        }
    }
    ASSERT_NE(target_para, nullptr);
    EXPECT_TRUE(target_para->get_paragraph_format().shading.has_fill());
    EXPECT_EQ(target_para->get_paragraph_format().shading.background.to_hex_rgb(), "FFCC00");

    doc2.close();
}

TEST(ShadingSyncTest, RunShadingRoundTrip) {
    TempDoc temp_doc("test_shading_run.docx");
    Document doc("test_shading_run.docx");
    ASSERT_TRUE(doc.create_empty());

    auto para = doc.get_first_section()->get_body()->append_paragraph();
    auto run = para->append_run("Shaded run");
    cdocx::Font font;
    font.shading.set_solid_fill(cdocx::Color::from_hex("00CCFF"));
    run->set_font(font);

    doc.sync_to_physical_tree();
    doc.save();

    Document doc2("test_shading_run.docx");
    doc2.open();
    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);
    bool found_shd = false;
    for (auto p = doc_xml->child("w:document").child("w:body").child("w:p"); p; p = p.next_sibling("w:p")) {
        for (auto r = p.child("w:r"); r; r = r.next_sibling("w:r")) {
            auto shd = r.child("w:rPr").child("w:shd");
            if (shd) {
                std::string fill = shd.attribute("w:fill").value();
                if (fill == "00CCFF") {
                    found_shd = true;
                }
            }
        }
    }
    EXPECT_TRUE(found_shd);

    doc2.close();
}

TEST(ShadingSyncTest, TableShadingRoundTrip) {
    TempDoc temp_doc("test_shading_table.docx");
    Document doc("test_shading_table.docx");
    ASSERT_TRUE(doc.create_empty());

    auto table = doc.get_first_section()->get_body()->append_table();
    table->get_table_format().shading.set_solid_fill(cdocx::Color::from_hex("CCFFCC"));

    doc.sync_to_physical_tree();
    doc.save();

    Document doc2("test_shading_table.docx");
    doc2.open();
    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);
    bool found_shd = false;
    for (auto tbl = doc_xml->child("w:document").child("w:body").child("w:tbl"); tbl; tbl = tbl.next_sibling("w:tbl")) {
        auto shd = tbl.child("w:tblPr").child("w:shd");
        if (shd) {
            std::string fill = shd.attribute("w:fill").value();
            if (fill == "CCFFCC") {
                found_shd = true;
            }
        }
    }
    EXPECT_TRUE(found_shd);

    doc2.close();
}
