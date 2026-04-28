/**
 * @file main.cpp
 * @brief Example: DocumentBuilder build-from-scratch and convenience APIs
 * @version 0.8.0
 */

#include <cdocx.h>
#include <cdocx/advanced.h>
#include <iostream>

int main() {
    // ========================================================================
    // Example 1: Build a complete document from scratch
    // ========================================================================
    {
        cdocx::DocumentBuilder builder;

        auto doc = builder
            .with_title("Build from Scratch Demo")
            .with_author("CDocx Team")
            .with_subject("Demonstrating build-from-scratch API")
            .with_keywords("CDocx, builder, demo")
            .with_page_size(8.5, 11.0)
            .with_margins(1.0, 1.0, 1.0, 1.0)
            .with_orientation(cdocx::PageOrientation::Portrait)
            .add_paragraph("This document was built entirely from scratch.")
            .add_paragraph("No existing document needed!")
            .add_table(2, 3)
            .build();

        doc->save("build_from_scratch.docx");
        std::cout << "Saved build_from_scratch.docx" << std::endl;
    }

    // ========================================================================
    // Example 2: Paragraph parent access
    // ========================================================================
    {
        cdocx::Document doc;
        doc.create_empty();

        auto body = doc.get_first_section()->get_body();
        auto para = body->append_paragraph("I am a paragraph.");

        // Navigate up the DOM tree
        auto parent_body = para->get_parent_body();
        auto parent_section = para->get_parent_section();

        std::cout << "Paragraph parent body found: " << (parent_body != nullptr) << std::endl;
        std::cout << "Paragraph parent section found: " << (parent_section != nullptr) << std::endl;
        std::cout << "Is in cell: " << para->is_in_cell() << std::endl;
        std::cout << "Is end of section: " << para->is_end_of_section() << std::endl;

        // Add a table with a paragraph inside a cell
        auto table = body->append_table(1, 1);
        auto cell_para = table->get_cell(0, 0)->append_paragraph("Inside cell");

        std::cout << "Cell paragraph is_in_cell: " << cell_para->is_in_cell() << std::endl;
        auto cell = cell_para->get_parent_cell();
        std::cout << "Cell paragraph parent cell found: " << (cell != nullptr) << std::endl;

        doc.save("paragraph_parent_access.docx");
        std::cout << "Saved paragraph_parent_access.docx" << std::endl;
    }

    // ========================================================================
    // Example 3: Table convenience methods
    // ========================================================================
    {
        cdocx::Document doc;
        doc.create_empty();

        auto body = doc.get_first_section()->get_body();
        auto table = body->append_table(0, 3);

        // Add rows with cell text in one call
        table->append_row({"Name", "Age", "City"});
        table->append_row({"Alice", "30", "New York"});
        table->insert_row(1, {"Bob", "25", "London"});

        // Nested table inside a cell
        auto cell = table->get_cell(0, 0);
        auto nested = cell->append_table(1, 1);
        nested->get_cell(0, 0)->set_text("Nested!");

        auto nested_tables = cell->get_tables();
        std::cout << "Nested tables in cell: " << nested_tables.size() << std::endl;

        doc.save("table_convenience.docx");
        std::cout << "Saved table_convenience.docx" << std::endl;
    }

    return 0;
}
