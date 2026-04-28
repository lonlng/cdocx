/**
 * @file main.cpp
 * @brief FootnoteCollection and EndnoteCollection usage demonstration
 * @since 0.8.0
 */

#include <cdocx.h>
#include <iostream>

int main() {
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    // Add a paragraph with text
    auto para = body->append_paragraph(
        "This is a sample text with a footnote reference.");

    // Add a footnote
    auto footnotes = doc->footnotes();
    auto fn = footnotes.add("This is the footnote text.");
    std::cout << "Added footnote with id: " << fn->get_id() << "\n";

    // Add a footnote with custom reference mark
    auto fn2 = footnotes.add("Second footnote content.", "*");
    std::cout << "Added footnote with custom mark: " << fn2->get_reference_mark() << "\n";

    // Iterate over all footnotes
    std::cout << "\nAll footnotes:\n";
    for (const auto& f : footnotes) {
        std::cout << "  [" << f->get_id() << "] " << f->get_text() << "\n";
    }

    // Add an endnote
    auto endnotes = doc->endnotes();
    auto en = endnotes.add("This is an endnote.");
    std::cout << "\nAdded endnote with id: " << en->get_id() << "\n";

    // Save the document
    doc->save("footnote_collection_demo.docx");
    std::cout << "\nSaved: footnote_collection_demo.docx\n";

    return 0;
}
