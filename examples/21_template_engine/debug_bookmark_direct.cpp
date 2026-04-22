#include <cdocx.h>
#include <cdocx/advanced.h>
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

int main() {
    cdocx::Document d("template_engine_bookmarked.docx");
    d.open();

    pugi::xml_document* xml = d.get_document_xml();
    pugi::xml_node body = xml->child("w:document").child("w:body");

    // Find AUTHOR paragraph
    pugi::xml_node author_para;
    for (pugi::xml_node p = body.child("w:p"); p; p = p.next_sibling("w:p")) {
        for (pugi::xml_node child = p.first_child(); child; child = child.next_sibling()) {
            if (std::string(child.name()) == "w:bookmarkStart") {
                if (std::string(child.attribute("w:name").value()) == "AUTHOR") {
                    author_para = p;
                    break;
                }
            }
        }
        if (author_para) break;
    }

    std::cout << "=== Before ===\n";
    dump_para(author_para, "AUTHOR para");

    // Get bookmark via collection
    auto bookmarks = d.get_bookmarks();
    auto bm_opt = bookmarks.get("AUTHOR");
    if (!bm_opt) {
        std::cout << "Bookmark not found!\n";
        return 1;
    }

    std::cout << "Bookmark valid: " << bm_opt->is_valid() << "\n";
    std::cout << "Bookmark text: '" << bm_opt->get_text() << "'\n";

    bool ok = bm_opt->set_text_keep_format("Jane Doe");
    std::cout << "set_text_keep_format result: " << ok << "\n";

    std::cout << "\n=== After ===\n";
    dump_para(author_para, "AUTHOR para");

    // Now try direct manipulation
    std::cout << "\n=== Direct manipulation ===\n";
    pugi::xml_node bm_start;
    for (pugi::xml_node child = author_para.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "w:bookmarkStart") {
            if (std::string(child.attribute("w:name").value()) == "AUTHOR") {
                bm_start = child;
                break;
            }
        }
    }

    if (bm_start) {
        pugi::xml_node bm_end = bm_start;
        while (bm_end && std::string(bm_end.name()) != "w:bookmarkEnd") {
            bm_end = bm_end.next_sibling();
        }

        if (bm_end) {
            std::cout << "Found bookmarkStart and bookmarkEnd\n";
            pugi::xml_node current = bm_start.next_sibling();
            while (current && current != bm_end) {
                pugi::xml_node next = current.next_sibling();
                std::cout << "Removing: " << current.name() << "\n";
                if (std::string(current.name()) == "w:r") {
                    author_para.remove_child(current);
                }
                current = next;
            }
            pugi::xml_node new_run = author_para.insert_child_before("w:r", bm_end);
            new_run.append_child("w:t").text().set("DIRECT_REPLACE");
            std::cout << "Inserted new run\n";
        }
    }

    std::cout << "\n=== After direct ===\n";
    dump_para(author_para, "AUTHOR para");

    d.save("debug_direct_out.docx");
    return 0;
}
