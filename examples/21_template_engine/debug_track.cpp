#include <cdocx.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/template.h>
#include <iostream>

bool is_node_in_tree(pugi::xml_node node, pugi::xml_node root) {
    if (!node || !root) return false;
    if (node == root) return true;
    for (pugi::xml_node child = root.first_child(); child; child = child.next_sibling()) {
        if (is_node_in_tree(node, child)) return true;
    }
    return false;
}

int main() {
    cdocx::Document d("template_engine_bookmarked.docx");
    d.open();

    cdocx::Template tmpl(&d, "{{", "}}");
    tmpl.set("company", "Acme Inc.");
    tmpl.replace_all();
    d.sync_to_physical_tree();

    cdocx::BookmarkReplacer replacer(&d);
    auto bm_opt = replacer.get_bookmark("AUTHOR");
    if (!bm_opt) {
        std::cout << "Bookmark not found\n";
        return 1;
    }

    pugi::xml_document* xml = d.get_document_xml();
    pugi::xml_node body = xml->child("w:document").child("w:body");

    std::cout << "start_node in tree: " << is_node_in_tree(bm_opt->start_node_, body) << "\n";
    std::cout << "end_node in tree: " << is_node_in_tree(bm_opt->end_node_, body) << "\n";

    // Get the para from bookmark
    pugi::xml_node bm_para = bm_opt->start_node_.parent();
    std::cout << "bm_para in tree: " << is_node_in_tree(bm_para, body) << "\n";
    std::cout << "bm_para == body.first_child: " << (bm_para == body.first_child()) << "\n";

    // Find which child of body it is
    int idx = 0;
    for (pugi::xml_node p = body.child("w:p"); p; p = p.next_sibling("w:p")) {
        if (p == bm_para) {
            std::cout << "bm_para is body child #" << idx << "\n";
            break;
        }
        ++idx;
    }

    // Now replace
    bool ok = replacer.replace_text("AUTHOR", "Jane Doe");
    std::cout << "replace_text result: " << ok << "\n";

    // Check again
    std::cout << "After replace, start_node in tree: " << is_node_in_tree(bm_opt->start_node_, body) << "\n";
    std::cout << "After replace, bm_para in tree: " << is_node_in_tree(bm_para, body) << "\n";

    // Dump body para #2
    idx = 0;
    for (pugi::xml_node p = body.child("w:p"); p; p = p.next_sibling("w:p")) {
        if (idx == 2) {
            std::cout << "Body para #2 children:\n";
            for (pugi::xml_node c = p.first_child(); c; c = c.next_sibling()) {
                std::cout << "  " << c.name();
                if (std::string(c.name()) == "w:r") {
                    for (pugi::xml_node t = c.child("w:t"); t; t = t.next_sibling("w:t")) {
                        std::cout << " text='" << (t.text() ? t.text().get() : "") << "'";
                    }
                }
                std::cout << "\n";
            }
            break;
        }
        ++idx;
    }

    return 0;
}
