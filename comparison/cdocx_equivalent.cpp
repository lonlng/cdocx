/**
 * Generate a cdocx document equivalent to python-docx's 01_basic_document.docx
 * for structural comparison.
 */
#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc;
    doc.create_empty("cdocx_equivalent.docx");

    auto section = doc.get_first_section();
    auto body = section->get_body();

    // Title (bold, large, centered)
    {
        auto p = body->append_paragraph("Test Document");
        p->set_bold(true);
        p->set_font_size(32);  // ~16pt heading size
        p->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;
    }

    // Normal paragraph with mixed formatting
    {
        auto p = body->append_paragraph("This is a normal paragraph with ");
        p->append_run("bold text")->set_bold(true);
        p->append_run(" and ");
        p->append_run("italic text")->set_italic(true);
        p->append_run(".");
    }

    // Styled run with font size and color
    {
        auto p = body->append_paragraph();
        auto run = p->append_run("Styled run with font size and color");
        run->set_font_size(28);  // 14pt
        run->set_color("FF0000");
        run->set_font_name("Arial");
    }

    // Table 2x3
    {
        auto table = body->append_table(2, 3);
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                auto cell = table->get_cell(i, j);
                cell->get_first_paragraph()->append_run(
                    std::to_string(i) + "," + std::to_string(j));
            }
        }
    }

    // Numbered list items
    {
        auto numbering_id = doc.add_numbered_list_definition();
        auto p1 = body->append_paragraph("First item");
        p1->set_numbering(numbering_id);
        auto p2 = body->append_paragraph("Second item");
        p2->set_numbering(numbering_id);
    }

    // Bullet list items
    {
        auto bullet_id = doc.add_bulleted_list_definition();
        auto p1 = body->append_paragraph("Bullet one");
        p1->set_numbering(bullet_id);
        auto p2 = body->append_paragraph("Bullet two");
        p2->set_numbering(bullet_id);
    }

    doc.save();
    std::cout << "Created cdocx_equivalent.docx" << std::endl;
    return 0;
}
