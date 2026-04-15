/**
 * @file 11_table_merge_tests.cpp
 * @brief Table cell merge/split unit tests
 * @version 0.7.0
 */

#include <gtest/gtest.h>
#include <cdocx.h>
#include <filesystem>

using namespace cdocx;
namespace fs = std::filesystem;

// ============================================================================
// Horizontal Merge Tests
// ============================================================================

TEST(TableMergeTest, HorizontalMergeTwoCells) {
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
    fs::remove("test_hmerge.docx");
}

TEST(TableMergeTest, VerticalMergeTwoCells) {
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
    fs::remove("test_vmerge.docx");
}

TEST(TableMergeTest, RectangularMerge2x2) {
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
    fs::remove("test_rect_merge.docx");
}

TEST(TableMergeTest, MergeByCellPointers) {
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
    fs::remove("test_ptr_merge.docx");
}

// ============================================================================
// Split Cell Tests
// ============================================================================

TEST(TableMergeTest, SplitHorizontalMerge) {
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
    fs::remove("test_split_h.docx");
}

TEST(TableMergeTest, SplitVerticalMerge) {
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
    fs::remove("test_split_v.docx");
}

// ============================================================================
// Serialization Round-Trip Tests
// ============================================================================

TEST(TableMergeTest, MergeRoundTrip) {
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
    fs::remove("test_merge_rt.docx");
}

TEST(TableMergeTest, GetCellAfterMerge) {
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
    fs::remove("test_getcell_merge.docx");
}

TEST(TableMergeTest, InvalidMergeReturnsNull) {
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
    fs::remove("test_invalid_merge.docx");
}

// ============================================================================
// Column Insert/Delete Tests
// ============================================================================

TEST(TableColumnTest, InsertColumnAtIndex) {
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
    fs::remove("test_insert_col.docx");
}

TEST(TableColumnTest, DeleteColumnAtIndex) {
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
    fs::remove("test_delete_col.docx");
}

TEST(TableColumnTest, InsertDeleteColumnRoundTrip) {
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
    fs::remove("test_col_rt.docx");
}

// ============================================================================
// AutoFit Tests
// ============================================================================

TEST(TableAutoFitTest, AutoFitToContents) {
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
    fs::remove("test_autofit_contents.docx");
}

TEST(TableAutoFitTest, AutoFitToWindow) {
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
    fs::remove("test_autofit_window.docx");
}

TEST(TableAutoFitTest, FixedColumnWidth) {
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
    fs::remove("test_autofit_fixed.docx");
}

TEST(TableAutoFitTest, AutoFitRoundTrip) {
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
    fs::remove("test_autofit_rt.docx");
}
