#include <cdocx.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/template.h>
#include <iostream>

void dump_para(const pugi::xml_node& para, const char* label) {
    std::cout << label << ":\n";
    for (pugi::xml_node child = para.first_child(); child; child = child.next_sibling()) {
        std::cout << "  " << child.name();
        if (std::string(child.name()) == "w:bookmarkStart") {
            std::cout << " id=" << child.attribute("w:id").value()
                      << " name=" << child.attribute("w:name").value();
        }
        if (std::string(child.name()) == "w:r") {
            for (pugi::xml_node t = child.child("w:t"); t; t = t.next_sibling("w:t")) {
                std::cout << " text=\"" << (t.text() ? t.text().get() : "") << "\"";
            }
        }
        std::cout << "\n";
    }
}

void dump_doc(cdocx::Document* doc, const char* phase) {
    pugi::xml_document* xml = doc->get_document_xml();
    pugi::xml_node body = xml->child("w:document").child("w:body");
    std::cout << "\n=== " << phase << " ===\n";
    int idx = 0;
    for (pugi::xml_node p = body.child("w:p"); p; p = p.next_sibling("w:p")) {
        dump_para(p, ("Para " + std::to_string(idx)).c_str());
        ++idx;
    }
}

int main() {
    cdocx::Document d("template_engine_bookmarked.docx");
    d.open();
    dump_doc(&d, "After open");

    // Phase 1: Template placeholder replacement (DOM)
    cdocx::Template tmpl(&d, "{{", "}}");
    tmpl.set("company", "Acme Inc.");
    tmpl.set("date", "2025-04-21");
    tmpl.set("title", "Annual Report");
    tmpl.replace_all();
    dump_doc(&d, "After Template::replace_all");

    d.sync_to_physical_tree();
    dump_doc(&d, "After sync_to_physical_tree");

    // Phase 2: Bookmark replacement
    cdocx::BookmarkReplacer replacer(&d);
    std::cout << "\nHas AUTHOR: " << replacer.has_bookmark("AUTHOR") << "\n";
    bool ok1 = replacer.replace_text("AUTHOR", "Jane Doe");
    std::cout << "Replace AUTHOR: " << ok1 << "\n";
    bool ok2 = replacer.replace_text("SIGNATURE", "APPROVED");
    std::cout << "Replace SIGNATURE: " << ok2 << "\n";

    dump_doc(&d, "After bookmark replace");

    d.sync_from_physical_tree();
    dump_doc(&d, "After sync_from_physical_tree");

    d.save("debug_phases_out.docx");
    return 0;
}
