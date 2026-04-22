#include <cdocx.h>
#include <cdocx/bookmark_replacer.h>
#include <iostream>

std::string extract_text_from_para(const pugi::xml_node& para) {
    std::string result;
    for (pugi::xml_node r = para.child("w:r"); r; r = r.next_sibling("w:r")) {
        for (pugi::xml_node t = r.child("w:t"); t; t = t.next_sibling("w:t")) {
            if (t.text()) result += t.text().get();
        }
    }
    return result;
}

void dump_para(const pugi::xml_node& para, const char* label) {
    std::cout << label << ": " << extract_text_from_para(para) << "\n";
    for (pugi::xml_node child = para.first_child(); child; child = child.next_sibling()) {
        std::cout << "  " << child.name();
        if (std::string(child.name()) == "w:bookmarkStart") {
            std::cout << " name=" << child.attribute("w:name").value();
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

    std::cout << "=== Before ===\n";
    int idx = 0;
    for (pugi::xml_node p = body.child("w:p"); p; p = p.next_sibling("w:p")) {
        dump_para(p, ("Para " + std::to_string(idx)).c_str());
        ++idx;
    }

    cdocx::BookmarkReplacer replacer(&d);
    std::cout << "\nHas AUTHOR: " << replacer.has_bookmark("AUTHOR") << "\n";
    std::cout << "AUTHOR text: '" << replacer.get_bookmark_text("AUTHOR") << "'\n";

    bool ok = replacer.replace_text("AUTHOR", "Jane Doe");
    std::cout << "replace_text result: " << ok << "\n";

    std::cout << "\n=== After ===\n";
    idx = 0;
    for (pugi::xml_node p = body.child("w:p"); p; p = p.next_sibling("w:p")) {
        dump_para(p, ("Para " + std::to_string(idx)).c_str());
        ++idx;
    }

    d.save("debug_author_out.docx");
    return 0;
}
