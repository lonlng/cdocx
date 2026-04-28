/**
 * @file 11_table_merge_tests.cpp
 * @brief Table cell merge/split unit tests
 * @version 0.8.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <filesystem>
#include "../test_helpers.h"

using namespace cdocx;
namespace fs = std::filesystem;
using cdocx::test::TempDoc;

// ============================================================================
// Horizontal Merge Tests
// ============================================================================

TEST(TableMergeTest, HorizontalMergeTwoCells) {
    TempDoc temp_doc("test_hmerge.docx");
    Document doc("test_hmerge.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 3);
    table->get_cell(0, 0)->set_text("A");
    table->get_cell(0, 1)->set_text("B");
    table->get_cell(0, 2)->set_text("C");

    auto merged = table->merge_cells(0, 0, 0, 1);
    ASSERT_NE(merged, nullptr);

    // A 3-column table with a 2-cell merge still has 3 grid columns
    EXPECT_EQ(table->get_column_count(), 3);
    EXPECT_EQ(merged->get_horizontal_merge_span(), 2);
    EXPECT_TRUE(merged->is_horizontal_merge_start());
    EXPECT_TRUE(table->is_complex());

    // Content from both cells should be in the merged cell
    auto text = merged->get_text();
    EXPECT_NE(text.find("A"), std::string::npos);
    EXPECT_NE(text.find("B"), std::string::npos);

    // Second row should be unaffected (still has 3 physical cells)
    EXPECT_EQ(table->get_row(1)->get_cells().get_count(), 3u);

    doc.save();
}

TEST(TableMergeTest, VerticalMergeTwoCells) {
    TempDoc temp_doc("test_vmerge.docx");
    Document doc("test_vmerge.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(3, 2);
    table->get_cell(0, 0)->set_text("A");
    table->get_cell(1, 0)->set_text("B");

    auto merged = table->merge_cells(0, 0, 1, 0);
    ASSERT_NE(merged, nullptr);

    EXPECT_EQ(merged->get_cell_format().vertical_merge, true);
    EXPECT_TRUE(merged->is_vertical_merge_start());

    auto row1_cell = table->get_cell(1, 0);
    ASSERT_NE(row1_cell, nullptr);
    EXPECT_TRUE(row1_cell->is_vertical_merge_continue());

    doc.save();
}

TEST(TableMergeTest, RectangularMerge2x2) {
    TempDoc temp_doc("test_rect_merge.docx");
    Document doc("test_rect_merge.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(3, 4);
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 4; ++c) {
            table->get_cell(r, c)->set_text(std::string(1, 'A' + r * 4 + c));
        }
    }

    auto merged = table->merge_cells(0, 1, 1, 2);
    ASSERT_NE(merged, nullptr);

    EXPECT_EQ(table->get_column_count(), 4); // [C0][Merged(1-2)][C3] = 1+2+1 grid columns
    EXPECT_EQ(merged->get_horizontal_merge_span(), 2);
    EXPECT_TRUE(merged->is_vertical_merge_start());

    auto row1_merged = table->get_cell(1, 1);
    ASSERT_NE(row1_merged, nullptr);
    EXPECT_EQ(row1_merged->get_horizontal_merge_span(), 2);
    EXPECT_TRUE(row1_merged->is_vertical_merge_continue());

    doc.save();
}

TEST(TableMergeTest, MergeByCellPointers) {
    TempDoc temp_doc("test_ptr_merge.docx");
    Document doc("test_ptr_merge.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 2);
    auto c1 = table->get_cell(0, 0);
    auto c2 = table->get_cell(0, 1);

    auto merged = table->merge_cells(c1, c2);
    ASSERT_NE(merged, nullptr);
    EXPECT_EQ(merged->get_horizontal_merge_span(), 2);

    doc.save();
}

// ============================================================================
// Split Cell Tests
// ============================================================================

TEST(TableMergeTest, SplitHorizontalMerge) {
    TempDoc temp_doc("test_split_h.docx");
    Document doc("test_split_h.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 3);
    table->get_cell(0, 0)->set_text("A");
    table->get_cell(0, 1)->set_text("B");

    auto merged = table->merge_cells(0, 0, 0, 1);
    ASSERT_EQ(table->get_column_count(), 3);

    table->split_cell(merged, 1, 2);
    EXPECT_EQ(table->get_column_count(), 3);
    EXPECT_EQ(table->get_cell(0, 0)->get_horizontal_merge_span(), 1);
    EXPECT_EQ(table->get_cell(0, 1)->get_horizontal_merge_span(), 1);

    doc.save();
}

TEST(TableMergeTest, SplitVerticalMerge) {
    TempDoc temp_doc("test_split_v.docx");
    Document doc("test_split_v.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(3, 2);
    auto merged = table->merge_cells(0, 0, 1, 0);
    ASSERT_NE(merged, nullptr);

    table->split_cell(merged, 2, 1);
    EXPECT_EQ(table->get_cell(0, 0)->get_horizontal_merge_span(), 1);
    EXPECT_FALSE(table->get_cell(0, 0)->get_cell_format().vertical_merge);
    EXPECT_FALSE(table->get_cell(1, 0)->get_cell_format().vertical_merge);

    doc.save();
}

// ============================================================================
// Serialization Round-Trip Tests
// ============================================================================

TEST(TableMergeTest, MergeRoundTrip) {
    TempDoc temp_doc("test_merge_rt.docx");
    Document doc("test_merge_rt.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(3, 3);
    table->get_cell(0, 0)->set_text("TL");
    table->get_cell(0, 1)->set_text("TR");
    table->get_cell(1, 0)->set_text("BL");

    table->merge_cells(0, 0, 1, 1);
    doc.save();

    // Re-open and verify
    Document doc2("test_merge_rt.docx");
    doc2.open();

    auto loaded_tables = doc2.get_first_section()->get_body()->get_tables();
    ASSERT_FALSE(loaded_tables.empty());
    auto loaded_table = loaded_tables[0];
    EXPECT_TRUE(loaded_table->is_complex());

    auto cell00 = loaded_table->get_cell(0, 0);
    ASSERT_NE(cell00, nullptr);
    EXPECT_EQ(cell00->get_horizontal_merge_span(), 2);

    doc2.close();
}

TEST(TableMergeTest, GetCellAfterMerge) {
    TempDoc temp_doc("test_getcell_merge.docx");
    Document doc("test_getcell_merge.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 4);
    table->merge_cells(0, 1, 0, 2); // Merge C1 and C2

    EXPECT_EQ(table->get_column_count(), 4);
    EXPECT_NE(table->get_cell(0, 0), nullptr);
    EXPECT_NE(table->get_cell(0, 1), nullptr); // The merged cell
    EXPECT_NE(table->get_cell(0, 2), nullptr); // Same merged cell (spans 1-2)
    EXPECT_NE(table->get_cell(0, 3), nullptr); // C3
    EXPECT_EQ(table->get_cell(0, 4), nullptr); // Out of bounds

    doc.save();
}

TEST(TableMergeTest, InvalidMergeReturnsNull) {
    TempDoc temp_doc("test_invalid_merge.docx");
    Document doc("test_invalid_merge.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 2);

    EXPECT_EQ(table->merge_cells(0, 0, 5, 5), nullptr); // Out of bounds
    EXPECT_EQ(table->merge_cells(0, 0, 0, 5), nullptr); // Out of bounds horizontally
    EXPECT_EQ(table->merge_cells(0, 0, 5, 0), nullptr); // Out of bounds vertically
    // Merging (1,1) with (0,0) in a 2x2 table is equivalent to a valid 2x2 merge
    EXPECT_NE(table->merge_cells(1, 1, 0, 0), nullptr);

    doc.save();
}

// ============================================================================
// Column Insert/Delete Tests
// ============================================================================

TEST(TableColumnTest, InsertColumnAtIndex) {
    TempDoc temp_doc("test_insert_col.docx");
    Document doc("test_insert_col.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 3);
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 3; ++c) {
            table->get_cell(r, c)->set_text(std::to_string(r) + std::to_string(c));
        }
    }

    table->insert_column(1);
    EXPECT_EQ(table->get_column_count(), 4);
    EXPECT_EQ(table->get_cell(0, 0)->get_text(), "00");
    EXPECT_EQ(table->get_cell(0, 1)->get_text(), ""); // New column
    EXPECT_EQ(table->get_cell(0, 2)->get_text(), "01");
    EXPECT_EQ(table->get_cell(0, 3)->get_text(), "02");

    doc.save();
}

TEST(TableColumnTest, DeleteColumnAtIndex) {
    TempDoc temp_doc("test_delete_col.docx");
    Document doc("test_delete_col.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 4);
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 4; ++c) {
            table->get_cell(r, c)->set_text(std::to_string(r) + std::to_string(c));
        }
    }

    table->delete_column(1);
    EXPECT_EQ(table->get_column_count(), 3);
    EXPECT_EQ(table->get_cell(0, 0)->get_text(), "00");
    EXPECT_EQ(table->get_cell(0, 1)->get_text(), "02");
    EXPECT_EQ(table->get_cell(0, 2)->get_text(), "03");

    doc.save();
}

TEST(TableColumnTest, InsertDeleteColumnRoundTrip) {
    TempDoc temp_doc("test_col_rt.docx");
    Document doc("test_col_rt.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 2);
    table->get_cell(0, 0)->set_text("A");
    table->get_cell(0, 1)->set_text("B");
    table->insert_column(1);

    doc.save();

    Document doc2("test_col_rt.docx");
    doc2.open();

    auto loaded_tables = doc2.get_first_section()->get_body()->get_tables();
    ASSERT_FALSE(loaded_tables.empty());
    auto loaded_table = loaded_tables[0];
    EXPECT_EQ(loaded_table->get_column_count(), 3);
    EXPECT_EQ(loaded_table->get_cell(0, 0)->get_text(), "A");
    EXPECT_EQ(loaded_table->get_cell(0, 1)->get_text(), "");
    EXPECT_EQ(loaded_table->get_cell(0, 2)->get_text(), "B");

    doc2.close();
}

// ============================================================================
// AutoFit Tests
// ============================================================================

TEST(TableAutoFitTest, AutoFitToContents) {
    TempDoc temp_doc("test_autofit_contents.docx");
    Document doc("test_autofit_contents.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 2);
    table->auto_fit(AutoFitBehavior::AutoFitToContents);

    doc.save();

    Document doc2("test_autofit_contents.docx");
    doc2.open();

    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);
    auto tblPr = doc_xml->child("w:document").child("w:body").child("w:tbl").child("w:tblPr");
    ASSERT_TRUE(tblPr);

    auto tblLayout = tblPr.child("w:tblLayout");
    ASSERT_TRUE(tblLayout);
    EXPECT_STREQ(tblLayout.attribute("w:type").value(), "autofit");

    doc2.close();
}

TEST(TableAutoFitTest, AutoFitToWindow) {
    TempDoc temp_doc("test_autofit_window.docx");
    Document doc("test_autofit_window.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 2);
    table->auto_fit(AutoFitBehavior::AutoFitToWindow);

    doc.save();

    Document doc2("test_autofit_window.docx");
    doc2.open();

    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);
    auto tblPr = doc_xml->child("w:document").child("w:body").child("w:tbl").child("w:tblPr");
    ASSERT_TRUE(tblPr);

    auto tblW = tblPr.child("w:tblW");
    ASSERT_TRUE(tblW);
    EXPECT_STREQ(tblW.attribute("w:type").value(), "pct");

    auto tblLayout = tblPr.child("w:tblLayout");
    ASSERT_TRUE(tblLayout);
    EXPECT_STREQ(tblLayout.attribute("w:type").value(), "autofit");

    doc2.close();
}

TEST(TableAutoFitTest, FixedColumnWidth) {
    TempDoc temp_doc("test_autofit_fixed.docx");
    Document doc("test_autofit_fixed.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 2);
    table->auto_fit(AutoFitBehavior::FixedColumnWidth);

    doc.save();

    Document doc2("test_autofit_fixed.docx");
    doc2.open();

    auto* doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);
    auto tblPr = doc_xml->child("w:document").child("w:body").child("w:tbl").child("w:tblPr");
    ASSERT_TRUE(tblPr);

    auto tblLayout = tblPr.child("w:tblLayout");
    ASSERT_TRUE(tblLayout);
    EXPECT_STREQ(tblLayout.attribute("w:type").value(), "fixed");

    doc2.close();
}

TEST(TableAutoFitTest, AutoFitRoundTrip) {
    TempDoc temp_doc("test_autofit_rt.docx");
    Document doc("test_autofit_rt.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 2);
    table->auto_fit(AutoFitBehavior::AutoFitToWindow);
    doc.save();

    Document doc2("test_autofit_rt.docx");
    doc2.open();

    auto loaded_tables = doc2.get_first_section()->get_body()->get_tables();
    ASSERT_FALSE(loaded_tables.empty());
    auto loaded_table = loaded_tables[0];
    EXPECT_EQ(loaded_table->get_table_format().auto_fit_behavior, AutoFitBehavior::AutoFitToWindow);
    EXPECT_TRUE(loaded_table->get_table_format().allow_auto_fit);

    doc2.close();
}

// ============================================================================
// TableOperations Tests
// ============================================================================

TEST(TableOperationsTest, InsertRow) {
    TempDoc temp_doc("test_ops_insert_row.docx");
    Document doc("test_ops_insert_row.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 2);
    table->get_cell(0, 0)->set_text("R0C0");
    table->get_cell(1, 0)->set_text("R1C0");

    EXPECT_TRUE(TableOperations::insert_row(*table, 1));
    EXPECT_EQ(TableOperations::get_row_count(*table), 3u);
    EXPECT_EQ(table->get_cell(0, 0)->get_text(), "R0C0");
    EXPECT_EQ(table->get_cell(2, 0)->get_text(), "R1C0");

    doc.save();
}

TEST(TableOperationsTest, AppendRow) {
    TempDoc temp_doc("test_ops_append_row.docx");
    Document doc("test_ops_append_row.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 2);

    EXPECT_TRUE(TableOperations::append_row(*table));
    EXPECT_EQ(TableOperations::get_row_count(*table), 2u);
    EXPECT_EQ(TableOperations::get_column_count(*table), 2u);

    doc.save();
}

TEST(TableOperationsTest, DeleteRow) {
    TempDoc temp_doc("test_ops_delete_row.docx");
    Document doc("test_ops_delete_row.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(3, 2);
    table->get_cell(0, 0)->set_text("A");
    table->get_cell(1, 0)->set_text("B");
    table->get_cell(2, 0)->set_text("C");

    EXPECT_TRUE(TableOperations::delete_row(*table, 1));
    EXPECT_EQ(TableOperations::get_row_count(*table), 2u);
    EXPECT_EQ(table->get_cell(0, 0)->get_text(), "A");
    EXPECT_EQ(table->get_cell(1, 0)->get_text(), "C");

    doc.save();
}

TEST(TableOperationsTest, InsertAndDeleteCell) {
    TempDoc temp_doc("test_ops_cell.docx");
    Document doc("test_ops_cell.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 2);
    auto row = table->get_row(0);
    ASSERT_NE(row, nullptr);

    EXPECT_TRUE(TableOperations::insert_cell(*row, 1));
    EXPECT_EQ(row->get_cells().get_count(), 3u);

    EXPECT_TRUE(TableOperations::delete_cell(*row, 0));
    EXPECT_EQ(row->get_cells().get_count(), 2u);

    doc.save();
}

TEST(TableOperationsTest, MergeCellsHorizontal) {
    TempDoc temp_doc("test_ops_merge_h.docx");
    Document doc("test_ops_merge_h.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 3);
    auto row = table->get_row(0);
    ASSERT_NE(row, nullptr);

    EXPECT_TRUE(TableOperations::merge_cells_horizontal(*row, 0, 1));
    EXPECT_EQ(table->get_column_count(), 3);
    EXPECT_EQ(table->get_cell(0, 0)->get_horizontal_merge_span(), 2);

    doc.save();
}

TEST(TableOperationsTest, SetAndGetCellText) {
    TempDoc temp_doc("test_ops_cell_text.docx");
    Document doc("test_ops_cell_text.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(1, 1);
    auto cell = table->get_cell(0, 0);
    ASSERT_NE(cell, nullptr);

    EXPECT_TRUE(TableOperations::set_cell_text(*cell, "Hello TableOperations"));
    EXPECT_EQ(TableOperations::get_cell_text(*cell), "Hello TableOperations");

    doc.save();
}

TEST(TableLegacyIteratorTest, CellParagraphsAccess) {
    TempDoc temp_doc("test_legacy_cell_para.docx");
    Document doc("test_legacy_cell_para.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 2);
    auto cell00 = table->get_cell(0, 0);
    auto cell01 = table->get_cell(0, 1);
    ASSERT_NE(cell00, nullptr);
    ASSERT_NE(cell01, nullptr);

    // Set text in two different cells
    cell00->set_text("Cell 0,0");
    cell01->set_text("Cell 0,1");

    doc.sync_to_physical_tree();
    doc.save();

    // Reopen and use raw XML to construct legacy TableCell for testing
    Document doc2("test_legacy_cell_para.docx");
    doc2.open();
    ASSERT_TRUE(doc2.is_open());

    auto doc_xml = doc2.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);

    auto body_xml = doc_xml->child("w:document").child("w:body");
    ASSERT_TRUE(body_xml);

    auto tbl = body_xml.child("w:tbl");
    ASSERT_TRUE(tbl);

    auto tr = tbl.child("w:tr");
    ASSERT_TRUE(tr);

    // First row, first cell
    TableCell cell(tr, tr.child("w:tc"));
    ASSERT_TRUE(cell.has_next());

    auto* para = cell.paragraphs();
    ASSERT_NE(para, nullptr);
    EXPECT_NE(para->get_text().find("Cell 0,0"), std::string::npos);

    // Move to second cell in first row
    cell.next();
    ASSERT_TRUE(cell.has_next());

    para = cell.paragraphs();
    ASSERT_NE(para, nullptr);
    EXPECT_NE(para->get_text().find("Cell 0,1"), std::string::npos);

    doc2.close();
}

TEST(TablePropertiesTest, ApplyToXmlNode) {
    TempDoc temp_doc("test_table_props.docx");
    Document doc("test_table_props.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(2, 2);
    ASSERT_NE(table, nullptr);

    // Apply table properties directly to the XML node after sync
    doc.sync_to_physical_tree();

    auto doc_xml = doc.get_document_xml();
    ASSERT_NE(doc_xml, nullptr);

    auto tbl = doc_xml->child("w:document").child("w:body").child("w:tbl");
    ASSERT_TRUE(tbl);

    TableProperties props;
    props.width.type = TableProperties::WidthType::Absolute;
    props.width.value = 5000;
    props.alignment = ParagraphProperties::Alignment::Centered;
    props.borders.top = ParagraphProperties::Border{
        ParagraphProperties::Border::Style::Single, 8, "FF0000", 0};
    props.cell_margin.top = 100;
    props.cell_margin.left = 200;

    props.apply_to(tbl);

    // Verify width
    auto tblPr = tbl.child("w:tblPr");
    ASSERT_TRUE(tblPr);

    auto tblW = tblPr.child("w:tblW");
    ASSERT_TRUE(tblW);
    EXPECT_EQ(std::string(tblW.attribute("w:type").value()), "dxa");
    EXPECT_EQ(tblW.attribute("w:w").as_int(), 5000);

    // Verify alignment
    auto jc = tblPr.child("w:jc");
    ASSERT_TRUE(jc);
    EXPECT_EQ(std::string(jc.attribute("w:val").value()), "center");

    // Verify borders
    auto tblBorders = tblPr.child("w:tblBorders");
    ASSERT_TRUE(tblBorders);
    auto top = tblBorders.child("w:top");
    ASSERT_TRUE(top);
    EXPECT_EQ(std::string(top.attribute("w:val").value()), "single");
    EXPECT_EQ(top.attribute("w:sz").as_int(), 8);
    EXPECT_EQ(std::string(top.attribute("w:color").value()), "FF0000");

    // Verify cell margins
    auto tblCellMar = tblPr.child("w:tblCellMar");
    ASSERT_TRUE(tblCellMar);
    auto mar_top = tblCellMar.child("w:top");
    ASSERT_TRUE(mar_top);
    EXPECT_EQ(mar_top.attribute("w:w").as_int(), 100);
    EXPECT_EQ(std::string(mar_top.attribute("w:type").value()), "dxa");
    auto mar_left = tblCellMar.child("w:left");
    ASSERT_TRUE(mar_left);
    EXPECT_EQ(mar_left.attribute("w:w").as_int(), 200);

    doc.save();
}

// ============================================================================
// Table Convenience Methods Tests
// ============================================================================

TEST(TableConvenienceTest, AppendRowWithCellTexts) {
    TempDoc temp_doc("test_append_row_vec.docx");
    Document doc("test_append_row_vec.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(0, 3);
    auto row = table->append_row({"Name", "Age", "City"});

    ASSERT_NE(row, nullptr);
    EXPECT_EQ(table->get_row_count(), 1u);
    EXPECT_EQ(row->get_cells().get_count(), 3u);
    EXPECT_EQ(row->get_cell(0)->get_text(), "Name");
    EXPECT_EQ(row->get_cell(1)->get_text(), "Age");
    EXPECT_EQ(row->get_cell(2)->get_text(), "City");

    doc.save();
}

TEST(TableConvenienceTest, InsertRowWithCellTexts) {
    TempDoc temp_doc("test_insert_row_vec.docx");
    Document doc("test_insert_row_vec.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto table = body->append_table(0, 2);
    table->append_row({"A1", "A2"});
    table->insert_row(0, {"Header1", "Header2"});

    EXPECT_EQ(table->get_row_count(), 2u);
    EXPECT_EQ(table->get_row(0)->get_cell(0)->get_text(), "Header1");
    EXPECT_EQ(table->get_row(1)->get_cell(0)->get_text(), "A1");

    doc.save();
}

TEST(TableConvenienceTest, NestedTablesInCell) {
    TempDoc temp_doc("test_nested_tables.docx");
    Document doc("test_nested_tables.docx");
    ASSERT_TRUE(doc.create_empty());

    auto body = doc.get_first_section()->get_body();
    auto outer = body->append_table(2, 2);
    auto cell = outer->get_cell(0, 0);

    // Add nested table
    auto inner = cell->append_table(1, 1);
    inner->get_cell(0, 0)->set_text("Nested");

    // Get tables from cell
    auto nested = cell->get_tables();
    EXPECT_EQ(nested.size(), 1u);
    EXPECT_EQ(nested[0]->get_cell(0, 0)->get_text(), "Nested");

    doc.save();
}
