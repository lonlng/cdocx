/**
 * @file sync_properties.cpp
 * @brief Built-in and custom property sync for Document class
 */

#include "sync_common.h"

#include <cdocx/document.h>

#include <cstdlib>

namespace cdocx {

// ============================================================================
// Built-in Properties Sync
// ============================================================================

void Document::sync_builtin_properties_to_physical() {
    // Sync core.xml
    pugi::xml_document* core_doc = get_core_properties();
    if (core_doc) {
        auto root = core_doc->child("cp:coreProperties");
        if (root) {
            set_text_child(root, "dc:title", builtin_properties_.title);
            set_text_child(root, "dc:subject", builtin_properties_.subject);
            set_text_child(root, "dc:creator", builtin_properties_.author);
            set_text_child(root, "cp:keywords", builtin_properties_.keywords);
            set_text_child(root, "dc:description", builtin_properties_.comments);
            set_text_child(root,
                           "cp:lastModifiedBy",
                           builtin_properties_.manager);  // using manager as lastModifiedBy
            set_text_child(root, "cp:category", builtin_properties_.category);
            set_text_child(root, "cp:contentStatus", builtin_properties_.content_status);
            set_text_child(root, "cp:contentType", builtin_properties_.content_type);
            set_text_child(root, "cp:revision", builtin_properties_.revision);

            if (builtin_properties_.created != 0) {
                auto created = get_or_create_child(root, "dcterms:created");
                created.append_attribute("xsi:type").set_value("dcterms:W3CDTF");
                created.append_child(pugi::node_pcdata)
                    .set_value(time_to_w3cdtf(builtin_properties_.created).c_str());
            }
            if (builtin_properties_.modified != 0) {
                auto modified = get_or_create_child(root, "dcterms:modified");
                modified.append_attribute("xsi:type").set_value("dcterms:W3CDTF");
                modified.append_child(pugi::node_pcdata)
                    .set_value(time_to_w3cdtf(builtin_properties_.modified).c_str());
            }
            if (builtin_properties_.last_printed != 0) {
                set_text_child(
                    root, "cp:lastPrinted", time_to_w3cdtf(builtin_properties_.last_printed));
            }
        }
        mark_modified("docProps/core.xml");
    }

    // Sync app.xml
    pugi::xml_document* app_doc = get_app_properties();
    if (app_doc) {
        auto root = app_doc->child("Properties");
        if (root) {
            set_text_child(root, "Template", builtin_properties_.template_name);
            set_text_child(root, "Application", "CDocx");
            set_text_child(root, "Company", builtin_properties_.company);
            set_text_child(root, "AppVersion", "16.0000");

            if (builtin_properties_.total_pages >= 0) {
                set_text_child(root, "Pages", std::to_string(builtin_properties_.total_pages));
            }
            if (builtin_properties_.total_words >= 0) {
                set_text_child(root, "Words", std::to_string(builtin_properties_.total_words));
            }
            if (builtin_properties_.total_chars >= 0) {
                set_text_child(root, "Characters", std::to_string(builtin_properties_.total_chars));
            }
            if (builtin_properties_.total_lines >= 0) {
                set_text_child(root, "Lines", std::to_string(builtin_properties_.total_lines));
            }
            if (builtin_properties_.total_paragraphs >= 0) {
                set_text_child(
                    root, "Paragraphs", std::to_string(builtin_properties_.total_paragraphs));
            }
        }
        mark_modified("docProps/app.xml");
    }
}

void Document::sync_builtin_properties_from_physical() {
    // Load core.xml
    pugi::xml_document* core_doc = get_core_properties();
    if (core_doc) {
        auto root = core_doc->child("cp:coreProperties");
        if (root) {
            if (auto n = root.child("dc:title").first_child()) {
                builtin_properties_.title = n.value();
            }
            if (auto n = root.child("dc:subject").first_child()) {
                builtin_properties_.subject = n.value();
            }
            if (auto n = root.child("dc:creator").first_child()) {
                builtin_properties_.author = n.value();
            }
            if (auto n = root.child("cp:keywords").first_child()) {
                builtin_properties_.keywords = n.value();
            }
            if (auto n = root.child("dc:description").first_child()) {
                builtin_properties_.comments = n.value();
            }
            if (auto n = root.child("cp:lastModifiedBy").first_child()) {
                builtin_properties_.manager = n.value();
            }
            if (auto n = root.child("cp:category").first_child()) {
                builtin_properties_.category = n.value();
            }
            if (auto n = root.child("cp:contentStatus").first_child()) {
                builtin_properties_.content_status = n.value();
            }
            if (auto n = root.child("cp:contentType").first_child()) {
                builtin_properties_.content_type = n.value();
            }
            if (auto n = root.child("cp:revision").first_child()) {
                builtin_properties_.revision = n.value();
            }
            if (auto n = root.child("dcterms:created").first_child()) {
                builtin_properties_.created = w3cdtf_to_time(n.value());
            }
            if (auto n = root.child("dcterms:modified").first_child()) {
                builtin_properties_.modified = w3cdtf_to_time(n.value());
            }
            if (auto n = root.child("cp:lastPrinted").first_child()) {
                builtin_properties_.last_printed = w3cdtf_to_time(n.value());
            }
        }
    }

    // Load app.xml
    pugi::xml_document* app_doc = get_app_properties();
    if (app_doc) {
        auto root = app_doc->child("Properties");
        if (root) {
            if (auto n = root.child("Template").first_child()) {
                builtin_properties_.template_name = n.value();
            }
            if (auto n = root.child("Company").first_child()) {
                builtin_properties_.company = n.value();
            }
            auto safe_atoi = [](const char* str) -> int {
                char* end = nullptr;
                return static_cast<int>(std::strtol(str, &end, 10));
            };
            if (auto n = root.child("Pages").first_child()) {
                builtin_properties_.total_pages = safe_atoi(n.value());
            }
            if (auto n = root.child("Words").first_child()) {
                builtin_properties_.total_words = safe_atoi(n.value());
            }
            if (auto n = root.child("Characters").first_child()) {
                builtin_properties_.total_chars = safe_atoi(n.value());
            }
            if (auto n = root.child("Lines").first_child()) {
                builtin_properties_.total_lines = safe_atoi(n.value());
            }
            if (auto n = root.child("Paragraphs").first_child()) {
                builtin_properties_.total_paragraphs = safe_atoi(n.value());
            }
        }
    }
}

// ============================================================================
// Custom Properties Sync
// ============================================================================

void Document::sync_custom_properties_to_physical() {
    if (custom_properties_.custom_properties.empty()) {
        // Remove custom.xml if no custom properties
        if (has_xml_part("docProps/custom.xml")) {
            remove_xml_part("docProps/custom.xml");
            // Remove relationship
            const std::string rel_id = find_relationship_id("_rels/.rels", "docProps/custom.xml");
            if (!rel_id.empty()) {
                remove_relationship("_rels/.rels", rel_id);
            }
        }
        return;
    }

    pugi::xml_document* custom_doc = get_xml_part("docProps/custom.xml");
    if (!custom_doc) {
        custom_doc = &create_xml_part("docProps/custom.xml");
        add_content_type_override(
            "/docProps/custom.xml",
            "application/vnd.openxmlformats-officedocument.custom-properties+xml");

        const std::string rel_id = find_relationship_id("_rels/.rels", "docProps/custom.xml");
        if (rel_id.empty()) {
            add_relationship("_rels/.rels",
                             "http://schemas.openxmlformats.org/officeDocument/2006/relationships/"
                             "custom-properties",
                             "docProps/custom.xml");
        }
    }

    custom_doc->reset();
    auto root = custom_doc->append_child("Properties");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/officeDocument/2006/custom-properties");
    root.append_attribute("xmlns:vt")
        .set_value("http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");

    int pid = 2;
    for (const auto& kv : custom_properties_.custom_properties) {
        auto prop = root.append_child("property");
        prop.append_attribute("fmtid").set_value("{D5CDD505-2E9C-101B-9397-08002B2CF9AE}");
        prop.append_attribute("pid").set_value(pid++);
        prop.append_attribute("name").set_value(kv.first.c_str());
        auto val = prop.append_child("vt:lpwstr");
        val.append_child(pugi::node_pcdata).set_value(kv.second.c_str());
    }

    mark_modified("docProps/custom.xml");
}

void Document::sync_custom_properties_from_physical() {
    custom_properties_.custom_properties.clear();

    pugi::xml_document* custom_doc = get_xml_part("docProps/custom.xml");
    if (!custom_doc) {
        return;
    }

    auto root = custom_doc->child("Properties");
    if (!root) {
        return;
    }

    for (auto prop = root.child("property"); prop; prop = prop.next_sibling("property")) {
        const pugi::xml_attribute name_attr = prop.attribute("name");
        if (!name_attr) {
            continue;
        }

        std::string value;
        if (auto lpwstr = prop.child("vt:lpwstr").first_child()) {
            value = lpwstr.value();
        } else if (auto text = prop.first_child().first_child()) {
            value = text.value();
        }

        custom_properties_.custom_properties[name_attr.value()] = value;
    }
}


}  // namespace cdocx
