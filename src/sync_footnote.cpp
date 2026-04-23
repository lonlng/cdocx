/**
 * @file sync_footnote.cpp
 * @brief Footnote and endnote sync
 */

#include "sync_common.h"

#include <cdocx/document.h>
#include <cdocx/footnote.h>

#include <cstring>

namespace cdocx {

// ============================================================================
// Footnote / Endnote Helpers
// ============================================================================

static void sync_notes_to_physical_impl(Document* doc,
                                    const char* xml_part,
                                    const char* root_name,
                                    const char* child_name,
                                    const std::vector<std::shared_ptr<Footnote>>& cache) {
    auto *notes_xml = doc->get_xml_part(xml_part);
    if (!notes_xml) {
        if (cache.empty()) {
            return;
        }
        notes_xml = &doc->create_xml_part(xml_part);
    }

    auto root = notes_xml->child(root_name);
    if (!root) {
        root = notes_xml->prepend_child(root_name);
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    }

    // Collect separator nodes to preserve them
    std::vector<pugi::xml_node> separators;
    for (auto child = root.first_child(); child;) {
        auto next = child.next_sibling();
        const int note_id = child.attribute("w:id").as_int();
        if (note_id < 0 || note_id == 0) {
            separators.push_back(child);
        }
        root.remove_child(child);
        child = next;
    }

    // Re-add separators first, or create them if missing
    if (separators.empty()) {
        auto sep = root.prepend_child(child_name);
        sep.append_attribute("w:id").set_value(-1);
        sep.append_attribute("w:type").set_value("separator");
        auto sep_para = sep.append_child("w:p");
        auto sep_run = sep_para.append_child("w:r");
        sep_run.append_child("w:separator");

        auto cont_sep = root.prepend_child(child_name);
        cont_sep.append_attribute("w:id").set_value(0);
        cont_sep.append_attribute("w:type").set_value("continuationSeparator");
        auto cont_para = cont_sep.append_child("w:p");
        auto cont_run = cont_para.append_child("w:r");
        cont_run.append_child("w:continuationSeparator");
    } else {
        for (auto& sep : separators) {
            root.append_copy(sep);
        }
    }

    for (const auto& note : cache) {
        auto node = root.append_child(child_name);
        node.append_attribute("w:id").set_value(note->get_id());
        if (!note->is_auto() && !note->get_reference_mark().empty()) {
            node.append_attribute("w:type").set_value("normal");
        }
        for (const auto& child : note->get_children()) {
            if (child->node_type() == NodeType::Paragraph) {
                serialize_paragraph_to_xml(node, dynamic_cast<Paragraph*>(child.get()));
            }
        }
    }

    doc->mark_modified(xml_part);
}

static void sync_notes_from_physical_impl(Document* doc,
                                      const char* xml_part,
                                      const char* root_name,
                                      const char* child_name,
                                      std::vector<std::shared_ptr<Footnote>>& cache,
                                      int& next_id,
                                      FootnoteType type) {
    auto *notes_xml = doc->get_xml_part(xml_part);
    if (!notes_xml) {
        return;
    }

    cache.clear();

    auto root = notes_xml->child(root_name);
    if (!root) {
        return;
    }

    for (auto node = root.child(child_name); node; node = node.next_sibling(child_name)) {
        const int id = node.attribute("w:id").as_int();
        if (id < 0 || id == 0) {
            continue;
        }

        auto note = std::make_shared<Footnote>(doc, type);
        note->set_id(id);

        const char* typeattr = node.attribute("w:type").value();
        if (typeattr && std::strcmp(typeattr, "normal") == 0) {
            note->set_auto(false);
        }

        for (auto para_node = node.child("w:p"); para_node;
             para_node = para_node.next_sibling("w:p")) {
            if (auto para = doc->parse_paragraph_from_xml(para_node)) {
                note->append_child(para);
            }
        }

        cache.push_back(note);
    }

    for (const auto& note : cache) {
        if (note->get_id() >= next_id) {
            next_id = note->get_id() + 1;
        }
    }
}

// ============================================================================
// Footnote Sync
// ============================================================================

void Document::sync_footnotes_to_physical() {
    sync_notes_to_physical_impl(
        this, "word/footnotes.xml", "w:footnotes", "w:footnote", footnotes_cache_);
}

void Document::sync_footnotes_from_physical() {
    sync_notes_from_physical_impl(this,
                                  "word/footnotes.xml",
                                  "w:footnotes",
                                  "w:footnote",
                                  footnotes_cache_,
                                  next_footnote_id_,
                                  FootnoteType::Footnote);
}

// ============================================================================
// Endnote Sync
// ============================================================================

void Document::sync_endnotes_to_physical() {
    sync_notes_to_physical_impl(
        this, "word/endnotes.xml", "w:endnotes", "w:endnote", endnotes_cache_);
}

void Document::sync_endnotes_from_physical() {
    sync_notes_from_physical_impl(this,
                                  "word/endnotes.xml",
                                  "w:endnotes",
                                  "w:endnote",
                                  endnotes_cache_,
                                  next_endnote_id_,
                                  FootnoteType::Endnote);
}

}  // namespace cdocx
