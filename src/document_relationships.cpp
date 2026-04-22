/**
 * @file document_relationships.cpp
 * @brief Document relationship and content type management
 * @internal Not part of the public API.
 */

#include <cdocx/document.h>

#include <algorithm>
#include <vector>

namespace cdocx {

// ============================================================================
// Content Types and Relationships
// ============================================================================

bool Document::load_content_types() {
    auto* content_types = get_content_types();
    if (!content_types) {
        return false;
    }

    content_types_.clear();

    auto root = content_types->child("Types");
    if (!root) {
        return false;
    }

    for (auto def = root.child("Default"); def; def = def.next_sibling("Default")) {
        ContentType ct;
        ct.extension = def.attribute("Extension").value();
        ct.content_type = def.attribute("ContentType").value();
        ct.is_default = true;
        content_types_.push_back(ct);
    }

    for (auto override = root.child("Override"); override;
         override = override.next_sibling("Override")) {
        ContentType ct;
        ct.part_name = override.attribute("PartName").value();
        ct.content_type = override.attribute("ContentType").value();
        ct.is_default = false;
        content_types_.push_back(ct);
    }

    return true;
}

void Document::parse_relationships(const std::string& rels_path) {
    auto* rels_doc = get_xml_part(rels_path);
    if (!rels_doc) {
        return;
    }

    auto root = rels_doc->child("Relationships");
    if (!root) {
        return;
    }

    std::vector<Relationship> rels;

    for (auto rel = root.child("Relationship"); rel; rel = rel.next_sibling("Relationship")) {
        Relationship r;
        r.id = rel.attribute("Id").value();
        r.type = rel.attribute("Type").value();
        r.target = rel.attribute("Target").value();
        r.target_mode = rel.attribute("TargetMode").value();
        rels.push_back(r);
    }

    relationships_[rels_path] = rels;
}

void Document::load_all_relationships() {
    parse_relationships("_rels/.rels");
    parse_relationships("word/_rels/document.xml.rels");

    // Load header/footer relationships
    for (int i = 1;; i++) {
        std::string path = "word/_rels/header" + std::to_string(i) + ".xml.rels";
        if (!has_xml_part(path)) {
            break;
        }
        parse_relationships(path);
    }

    for (int i = 1;; i++) {
        std::string path = "word/_rels/footer" + std::to_string(i) + ".xml.rels";
        if (!has_xml_part(path)) {
            break;
        }
        parse_relationships(path);
    }
}

std::string Document::add_relationship(const std::string& rels_path,
                                       const std::string& type,
                                       const std::string& target,
                                       const std::string& target_mode) {
    // Find next available rId
    int max_id = 0;
    for (const auto& rel : relationships_[rels_path]) {
        if (rel.id.substr(0, 3) == "rId") {
            int id = std::stoi(rel.id.substr(3));
            max_id = std::max(max_id, id);
        }
    }

    std::string new_id = "rId" + std::to_string(max_id + 1);

    Relationship r;
    r.id = new_id;
    r.type = type;
    r.target = target;
    r.target_mode = target_mode;
    relationships_[rels_path].push_back(r);

    modified_parts_.insert(rels_path);

    return new_id;
}

void Document::remove_relationship(const std::string& rels_path, const std::string& rel_id) {
    auto& rels = relationships_[rels_path];
    rels.erase(
        std::remove_if(
            rels.begin(), rels.end(), [&rel_id](const Relationship& r) { return r.id == rel_id; }),
        rels.end());
    modified_parts_.insert(rels_path);
}

std::string Document::find_relationship_id(const std::string& rels_path,
                                           const std::string& target) const {
    auto it = relationships_.find(rels_path);
    if (it == relationships_.end()) {
        return "";
    }

    for (const auto& rel : it->second) {
        if (rel.target == target) {
            return rel.id;
        }
    }
    return "";
}

std::string Document::get_relationship_target(const std::string& rels_path,
                                              const std::string& rel_id) const {
    auto it = relationships_.find(rels_path);
    if (it == relationships_.end()) {
        return "";
    }

    for (const auto& rel : it->second) {
        if (rel.id == rel_id) {
            return rel.target;
        }
    }
    return "";
}

void Document::update_relationships_xml(const std::string& rels_path) {
    auto& rels = relationships_[rels_path];
    if (rels.empty()) {
        return;
    }

    // Create or update the relationships XML
    pugi::xml_document* doc = nullptr;

    if (has_xml_part(rels_path)) {
        doc = get_xml_part(rels_path);
        doc->reset();
    } else {
        doc = &create_xml_part(rels_path);
    }

    auto root = doc->append_child("Relationships");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/relationships");

    for (const auto& rel : rels) {
        auto rel_node = root.append_child("Relationship");
        rel_node.append_attribute("Id").set_value(rel.id.c_str());
        rel_node.append_attribute("Type").set_value(rel.type.c_str());
        rel_node.append_attribute("Target").set_value(rel.target.c_str());
        if (!rel.target_mode.empty()) {
            rel_node.append_attribute("TargetMode").set_value(rel.target_mode.c_str());
        }
    }
}

void Document::add_content_type_override(const std::string& part_name,
                                         const std::string& content_type) {
    // Check if already exists
    for (auto& ct : content_types_) {
        if (ct.part_name == part_name) {
            ct.content_type = content_type;
            return;
        }
    }

    ContentType ct;
    ct.part_name = part_name;
    ct.content_type = content_type;
    ct.is_default = false;
    content_types_.push_back(ct);

    modified_parts_.insert("[Content_Types].xml");
}

void Document::add_content_type_default(const std::string& extension,
                                        const std::string& content_type) {
    // Check if already exists
    for (auto& ct : content_types_) {
        if (ct.is_default && ct.extension == extension) {
            ct.content_type = content_type;
            return;
        }
    }

    ContentType ct;
    ct.extension = extension;
    ct.content_type = content_type;
    ct.is_default = true;
    content_types_.push_back(ct);

    modified_parts_.insert("[Content_Types].xml");
}

void Document::update_content_types_xml() {
    if (content_types_.empty()) {
        return;
    }

    pugi::xml_document* doc = nullptr;

    if (has_xml_part("[Content_Types].xml")) {
        doc = get_content_types();
        doc->reset();
    } else {
        doc = &create_xml_part("[Content_Types].xml");
    }

    auto root = doc->append_child("Types");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/content-types");

    // Add defaults first
    for (const auto& ct : content_types_) {
        if (ct.is_default) {
            auto def = root.append_child("Default");
            def.append_attribute("Extension").set_value(ct.extension.c_str());
            def.append_attribute("ContentType").set_value(ct.content_type.c_str());
        }
    }

    // Then overrides
    for (const auto& ct : content_types_) {
        if (!ct.is_default) {
            auto override = root.append_child("Override");
            override.append_attribute("PartName").set_value(ct.part_name.c_str());
            override.append_attribute("ContentType").set_value(ct.content_type.c_str());
        }
    }
}

// ============================================================================

}  // namespace cdocx
