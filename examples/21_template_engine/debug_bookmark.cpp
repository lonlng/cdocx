#include <cdocx.h>
#include <cdocx/bookmark_inserter.h>
#include <cdocx/bookmark_replacer.h>
#include <iostream>

int main() {
    // Create doc with text
    auto doc = cdocx::CDocx::create_document();
    auto sections = doc->get_sections();
    auto body = sections[0]->get_body();
    body->append_paragraph("Author: John Smith");
    doc->save("debug_bm.docx");

    // Insert bookmark
    cdocx::Document d("debug_bm.docx");
    d.open();
    cdocx::BookmarkInserter inserter(&d);
    bool inserted = inserter.insert("AUTHOR", "John Smith");
    std::cout << "Inserted: " << inserted << "\n";
    d.sync_from_physical_tree();
    d.save("debug_bm_tmpl.docx");

    // Replace via BookmarkReplacer
    cdocx::Document d2("debug_bm_tmpl.docx");
    d2.open();
    cdocx::BookmarkReplacer replacer(&d2);
    std::cout << "Has AUTHOR: " << replacer.has_bookmark("AUTHOR") << "\n";
    bool ok = replacer.replace_text("AUTHOR", "Jane Doe");
    std::cout << "Replace result: " << ok << "\n";
    d2.save("debug_bm_out.docx");
    std::cout << "Done\n";
    return 0;
}
