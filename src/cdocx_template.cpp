// CDocx - Template and DocumentInserter Implementation

#include "cdocx.h"
#include "detail/cdocx_impl.h"
#include <pugixml.hpp>

namespace cdocx {

// ============================================================================
// Template Implementation
// ============================================================================

struct Template::PlaceholderContext {
    Run* first_run = nullptr;
    std::vector<Run*> runs_to_delete;
    std::string collected_text;
    size_t prefix_pos = 0;
    void clear() {
        first_run = nullptr;
        runs_to_delete.clear();
        collected_text.clear();
        prefix_pos = 0;
    }
};

Template::Template(Document* document) : doc_(document) {}

Template::Template(Document* document, const std::string& prefix, const std::string& suffix)
    : doc_(document), pattern_prefix_(prefix), pattern_suffix_(suffix) {}

void Template::set(const std::string& key, const std::string& value) {
    placeholders_[key] = value;
}

void Template::set(const std::string& key, const char* value) {
    placeholders_[key] = std::string(value);
}

void Template::set_image(const std::string& key, const std::string& image_path) {
    image_placeholders_[key] = image_path;
}

void Template::set_pattern(const std::string& prefix, const std::string& suffix) {
    pattern_prefix_ = prefix;
    pattern_suffix_ = suffix;
}

bool Template::replace_in_string(std::string& text) const {
    bool replaced = false;
    
    for (const auto& ph : placeholders_) {
        std::string pattern = pattern_prefix_ + ph.first + pattern_suffix_;
        size_t pos = text.find(pattern);
        while (pos != std::string::npos) {
            text.replace(pos, pattern.length(), ph.second);
            replaced = true;
            pos = text.find(pattern, pos + ph.second.length());
        }
    }
    
    return replaced;
}

void Template::replace_all() {
    if (!doc_ || !doc_->is_open()) return;
    
    replace_in_paragraphs();
    replace_in_tables();
    
    doc_->mark_modified("word/document.xml");
}

void Template::replace_in_paragraphs() {
    auto& paras = doc_->paragraphs();
    
    for (auto p = paras; p.has_next(); p.next()) {
        process_paragraph(p);
    }
}

void Template::replace_in_tables() {
    auto& tbls = doc_->tables();
    
    for (auto t = tbls; t.has_next(); t.next()) {
        auto& rows = t.rows();
        for (auto row = rows; row.has_next(); row.next()) {
            auto& cells = row.cells();
            for (auto cell = cells; cell.has_next(); cell.next()) {
                auto& cell_paras = cell.paragraphs();
                for (auto p = cell_paras; p.has_next(); p.next()) {
                    process_paragraph(p);
                }
            }
        }
    }
}

bool Template::try_replace_single_run(Run& r) const {
    std::string text = r.get_text();
    if (this->replace_in_string(text)) {
        r.set_text(text);
        return true;
    }
    return false;
}

void Template::process_paragraph(Paragraph& p) {
    // Simple implementation: just try single-run replacement
    for (auto r = p.runs(); r.has_next(); r.next()) {
        try_replace_single_run(r);
    }
}

void Template::clear() {
    placeholders_.clear();
    image_placeholders_.clear();
}

size_t Template::size() const {
    return placeholders_.size();
}

// ============================================================================
// DocumentInserter Implementation
// ============================================================================

DocumentInserter::DocumentInserter(Document* target) : target_doc_(target) {}

pugi::xml_node DocumentInserter::clone_paragraph(const pugi::xml_node& source_para,
                                                  pugi::xml_node target_parent) {
    return target_parent.append_copy(source_para);
}

pugi::xml_node DocumentInserter::clone_table(const pugi::xml_node& source_table,
                                              pugi::xml_node target_parent) {
    return target_parent.append_copy(source_table);
}

void DocumentInserter::insert_document(Document* source) {
    if (!target_doc_ || !target_doc_->is_open()) return;
    if (!source || !source->is_open()) return;
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc_xml = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc_xml) return;
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc_xml->child("w:document").child("w:body");
    
    if (!target_body || !source_body) return;
    
    for (pugi::xml_node child = source_body.first_child(); child; 
         child = child.next_sibling()) {
        std::string node_name = child.name();
        if (node_name == "w:p") {
            clone_paragraph(child, target_body);
        } else if (node_name == "w:tbl") {
            clone_table(child, target_body);
        }
    }
    
    target_doc_->mark_modified("word/document.xml");
}

void DocumentInserter::insert_document_after(Document* source, Paragraph& after_para) {
    if (!target_doc_ || !target_doc_->is_open()) return;
    if (!source || !source->is_open()) return;
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc_xml = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc_xml) return;
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc_xml->child("w:document").child("w:body");
    pugi::xml_node after_node = after_para.get_current();
    
    if (!target_body || !source_body || !after_node) return;
    
    pugi::xml_node insert_pos = after_node;
    for (pugi::xml_node child = source_body.first_child(); child;
         child = child.next_sibling()) {
        std::string node_name = child.name();
        if (node_name == "w:p" || node_name == "w:tbl") {
            pugi::xml_node new_node = target_body.insert_copy_after(child, insert_pos);
            if (new_node) {
                insert_pos = new_node;
            }
        }
    }
    
    target_doc_->mark_modified("word/document.xml");
}

void DocumentInserter::insert_document_at(Document* source, int position) {
    if (!target_doc_ || !target_doc_->is_open()) return;
    if (!source || !source->is_open()) return;
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc_xml = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc_xml) return;
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc_xml->child("w:document").child("w:body");
    
    if (!target_body || !source_body) return;
    
    if (position < 0) {
        insert_document(source);
        return;
    }
    
    pugi::xml_node insert_pos;
    int current_pos = 0;
    
    for (pugi::xml_node child = target_body.first_child(); child;
         child = child.next_sibling()) {
        std::string node_name = child.name();
        if (node_name == "w:p" || node_name == "w:tbl") {
            if (current_pos == position) {
                insert_pos = child;
                break;
            }
            current_pos++;
        }
    }
    
    if (!insert_pos) {
        insert_document(source);
        return;
    }
    
    for (pugi::xml_node child = source_body.first_child(); child;
         child = child.next_sibling()) {
        std::string node_name = child.name();
        if (node_name == "w:p" || node_name == "w:tbl") {
            target_body.insert_copy_before(child, insert_pos);
        }
    }
    
    target_doc_->mark_modified("word/document.xml");
}

void DocumentInserter::insert_paragraphs(Document* source, int position) {
    if (!target_doc_ || !target_doc_->is_open()) return;
    if (!source || !source->is_open()) return;
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc_xml = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc_xml) return;
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc_xml->child("w:document").child("w:body");
    
    if (!target_body || !source_body) return;
    
    pugi::xml_node insert_pos;
    if (position >= 0) {
        int current_pos = 0;
        for (pugi::xml_node child = target_body.first_child(); child;
             child = child.next_sibling()) {
            if (std::string(child.name()) == "w:p") {
                if (current_pos == position) {
                    insert_pos = child;
                    break;
                }
                current_pos++;
            }
        }
    }
    
    std::vector<pugi::xml_node> source_paras;
    for (pugi::xml_node child = source_body.first_child(); child;
         child = child.next_sibling()) {
        if (std::string(child.name()) == "w:p") {
            source_paras.push_back(child);
        }
    }
    
    if (insert_pos) {
        for (auto it = source_paras.rbegin(); it != source_paras.rend(); ++it) {
            target_body.insert_copy_before(*it, insert_pos);
        }
    } else {
        for (const auto& para : source_paras) {
            target_body.append_copy(para);
        }
    }
    
    target_doc_->mark_modified("word/document.xml");
}

void DocumentInserter::insert_tables(Document* source, int position) {
    if (!target_doc_ || !target_doc_->is_open()) return;
    if (!source || !source->is_open()) return;
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc_xml = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc_xml) return;
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc_xml->child("w:document").child("w:body");
    
    if (!target_body || !source_body) return;
    
    pugi::xml_node insert_pos;
    if (position >= 0) {
        int current_pos = 0;
        for (pugi::xml_node child = target_body.first_child(); child;
             child = child.next_sibling()) {
            if (std::string(child.name()) == "w:tbl") {
                if (current_pos == position) {
                    insert_pos = child;
                    break;
                }
                current_pos++;
            }
        }
    }
    
    std::vector<pugi::xml_node> source_tables;
    for (pugi::xml_node child = source_body.first_child(); child;
         child = child.next_sibling()) {
        if (std::string(child.name()) == "w:tbl") {
            source_tables.push_back(child);
        }
    }
    
    if (insert_pos) {
        for (auto it = source_tables.rbegin(); it != source_tables.rend(); ++it) {
            target_body.insert_copy_before(*it, insert_pos);
        }
    } else {
        for (const auto& tbl : source_tables) {
            target_body.append_copy(tbl);
        }
    }
    
    target_doc_->mark_modified("word/document.xml");
}

} // namespace cdocx
