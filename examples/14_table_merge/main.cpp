/**
 * @file main.cpp
 * @brief Example: Table cell merge and split operations
 * @version 0.8.0
 */

#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc("table_merge_example.docx");
    if (!doc.create_empty()) {
        std::cerr << "Failed to create document" << std::endl;
        return 1;
    }

    auto body = doc.get_first_section()->get_body();

    // ------------------------------------------------------------------------
    // Example 1: Horizontal merge (title row)
    // ------------------------------------------------------------------------
    auto title_para = body->append_paragraph("Table Merge Example");
    title_para->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;

    auto table1 = body->append_table(3, 4);
    table1->get_table_format().alignment = cdocx::TableAlignment::Center;

    // Fill data
    std::vector<std::vector<std::string>> data1 = {
        {"Name", "Age", "City", "Country"},
        {"Alice", "30", "New York", "USA"},
        {"Bob", "25", "London", "UK"}
    };
    for (size_t r = 0; r < data1.size(); ++r) {
        for (size_t c = 0; c < data1[r].size(); ++c) {
            table1->get_cell(static_cast<int>(r), static_cast<int>(c))->set_text(data1[r][c]);
        }
    }

    // Merge the first row into a title cell
    auto title_cell = table1->merge_cells(0, 0, 0, 3);
    title_cell->set_text("Employee Information");
    title_cell->get_first_paragraph()->append_run("Employee Information")
        ->get_font().bold = true;
    title_cell->get_first_paragraph()->append_run("Employee Information")
        ->get_font().size = 14;

    // ------------------------------------------------------------------------
    // Example 2: Vertical merge
    // ------------------------------------------------------------------------
    body->append_paragraph(); // Spacing

    auto table2 = body->append_table(4, 3);
    table2->get_table_format().alignment = cdocx::TableAlignment::Center;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 3; ++c) {
            table2->get_cell(r, c)->set_text("R" + std::to_string(r) + "C" + std::to_string(c));
        }
    }

    // Merge first column rows 1-2
    auto vmerge = table2->merge_cells(1, 0, 2, 0);
    vmerge->set_text("Merged Vertically");

    // ------------------------------------------------------------------------
    // Example 3: Rectangular merge (2x2)
    // ------------------------------------------------------------------------
    body->append_paragraph(); // Spacing

    auto table3 = body->append_table(4, 4);
    table3->get_table_format().alignment = cdocx::TableAlignment::Center;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            table3->get_cell(r, c)->set_text(std::string(1, 'A' + r * 4 + c));
        }
    }

    // Merge a 2x2 block in the center
    auto center = table3->merge_cells(1, 1, 2, 2);
    center->set_text("2x2 Merge");

    // ------------------------------------------------------------------------
    // Example 4: Split a merged cell
    // ------------------------------------------------------------------------
    body->append_paragraph(); // Spacing

    auto table4 = body->append_table(2, 3);
    table4->get_table_format().alignment = cdocx::TableAlignment::Center;

    table4->get_cell(0, 0)->set_text("A");
    table4->get_cell(0, 1)->set_text("B");
    table4->get_cell(0, 2)->set_text("C");
    table4->get_cell(1, 0)->set_text("D");
    table4->get_cell(1, 1)->set_text("E");
    table4->get_cell(1, 2)->set_text("F");

    auto merged = table4->merge_cells(0, 0, 0, 1);
    std::cout << "Before split: " << table4->get_column_count() << " columns" << std::endl;

    table4->split_cell(merged, 1, 2);
    std::cout << "After split: " << table4->get_column_count() << " columns" << std::endl;

    // ------------------------------------------------------------------------
    // Example 5: Insert and delete columns
    // ------------------------------------------------------------------------
    body->append_paragraph(); // Spacing

    auto table5 = body->append_table(2, 3);
    table5->get_table_format().alignment = cdocx::TableAlignment::Center;
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 3; ++c) {
            table5->get_cell(r, c)->set_text(std::to_string(r) + std::to_string(c));
        }
    }
    table5->insert_column(1);
    table5->get_cell(0, 1)->set_text("Inserted");
    std::cout << "After insert column: " << table5->get_column_count() << " columns" << std::endl;

    table5->delete_column(2);
    std::cout << "After delete column: " << table5->get_column_count() << " columns" << std::endl;

    // ------------------------------------------------------------------------
    // Example 6: Auto-fit behaviors
    // ------------------------------------------------------------------------
    body->append_paragraph(); // Spacing

    auto table6 = body->append_table(2, 2);
    table6->auto_fit(cdocx::AutoFitBehavior::AutoFitToWindow);
    table6->get_cell(0, 0)->set_text("Window");
    table6->get_cell(0, 1)->set_text("Fit");

    // ------------------------------------------------------------------------
    // Save
    // ------------------------------------------------------------------------
    doc.save();
    std::cout << "Document saved: table_merge_example.docx" << std::endl;

    return 0;
}
