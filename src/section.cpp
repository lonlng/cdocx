/**
 * @file section.cpp
 * @brief Section class implementation
 */

#include "sync_common.h"

#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/table.h>

#include <algorithm>
#include <cstring>
#include <sstream>

namespace cdocx {

// ============================================================================
// Helper Functions
// ============================================================================

struct OrientationMapping {
    SectionProperties::Orientation orientation;
    const char* xml_value;
};

static const OrientationMapping kOrientationMappings[] = {
    {SectionProperties::Orientation::Landscape, "landscape"},
};

static SectionProperties::Orientation string_to_orientation(const char* val) {
    if (!val || !*val) {
        return SectionProperties::Orientation::Portrait;
    }
    for (const auto& mapping : kOrientationMappings) {
        if (std::strcmp(mapping.xml_value, val) == 0) {
            return mapping.orientation;
        }
    }
    return SectionProperties::Orientation::Portrait;
}

static void remove_ref_from_node(pugi::xml_node sect_pr, HeaderFooterType type, bool is_header) {
    if (!sect_pr) {
        return;
    }
    const char* node_name = is_header ? "w:header_reference" : "w:footer_reference";
    const char* typestr = header_footer_type_to_string(type);
    for (auto child = sect_pr.child(node_name); child; child = child.next_sibling(node_name)) {
        if (std::strcmp(child.attribute("w:type").value(), typestr) == 0) {
            sect_pr.remove_child(child);
            break;
        }
    }
}

static bool has_header_footer(const std::vector<std::shared_ptr<HeaderFooter>>& collection,
                            HeaderFooterType type) {
    return std::any_of(collection.begin(), collection.end(),
                       [type](const auto& hf) {
                           return hf && hf->get_header_footer_type() == type;
                       });
}

static std::shared_ptr<HeaderFooter> get_header_footer(
    const std::vector<std::shared_ptr<HeaderFooter>>& collection, HeaderFooterType type) {
    for (const auto& hf : collection) {
        if (hf && hf->get_header_footer_type() == type) {
            return hf;
        }
    }
    return nullptr;
}

static std::vector<std::shared_ptr<HeaderFooter>> get_all_header_footer(
    const std::vector<std::shared_ptr<HeaderFooter>>& collection) {
    std::vector<std::shared_ptr<HeaderFooter>> result;
    for (const auto& hf : collection) {
        if (hf) {
            result.push_back(hf);
        }
    }
    return result;
}

static void remove_header_footer(HeaderFooterType type,
                               std::vector<std::shared_ptr<HeaderFooter>>& collection,
                               std::vector<HeaderFooterRef>& refs,
                               pugi::xml_node sect_pr,
                               bool is_header) {
    collection.erase(std::remove_if(collection.begin(),
                                    collection.end(),
                                    [type](const std::shared_ptr<HeaderFooter>& hf) {
                                        return hf && hf->get_header_footer_type() == type;
                                    }),
                     collection.end());
    remove_ref_from_node(sect_pr, type, is_header);
    refs.erase(
        std::remove_if(
            refs.begin(), refs.end(), [type](const HeaderFooterRef& r) { return r.type == type; }),
        refs.end());
}

static void link_hf_to_previous(Document* doc,
                                const HeaderFooterRef* prev_ref,
                                const HeaderFooterRef* curr_ref,
                                std::vector<HeaderFooterRef>& refs,
                                std::vector<std::shared_ptr<HeaderFooter>>& collection,
                                pugi::xml_node sect_pr,
                                HeaderFooterType type,
                                bool is_header,
                                bool is_link_to_previous) {
    const char* ref_tag = is_header ? "w:header_reference" : "w:footer_reference";
    const char* part_prefix = is_header ? "word/header" : "word/footer";
    const char* root_tag = is_header ? "w:hdr" : "w:ftr";
    const char* rel_type =
        is_header
            ? "http://schemas.openxmlformats.org/officeDocument/2006/relationships/header"
            : "http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer";

    auto add_ref = [&](const HeaderFooterRef& ref) {
        auto node = sect_pr.append_child(ref_tag);
        node.append_attribute("r:id").set_value(ref.relationship_id.c_str());
        node.append_attribute("w:type").set_value(header_footer_type_to_string(type));
        refs.push_back(ref);
        auto hf = std::make_shared<HeaderFooter>(doc, type, is_header);
        hf->set_part_path(ref.part_path);
        hf->set_relationship_id(ref.relationship_id);
        collection.push_back(hf);
    };

    if (is_link_to_previous) {
        if (curr_ref) {
            if (prev_ref && curr_ref->part_path == prev_ref->part_path) {
                // already linked
            } else if (prev_ref) {
                remove_header_footer(type, collection, refs, sect_pr, is_header);
                add_ref(*prev_ref);
            } else {
                remove_header_footer(type, collection, refs, sect_pr, is_header);
            }
        } else if (prev_ref) {
            add_ref(*prev_ref);
        }
    } else if (prev_ref) {
        const bool need_copy = (!curr_ref) || (curr_ref->part_path == prev_ref->part_path);
        if (need_copy) {
            const std::string new_part =
                part_prefix +
                std::to_string(is_header ? doc->get_next_header_number()
                                         : doc->get_next_footer_number()) +
                ".xml";

            auto* prev_xml = doc->get_xml_part(prev_ref->part_path);
            if (prev_xml) {
                auto& new_xml = doc->create_xml_part(new_part);
                new_xml.reset();
                for (auto child = prev_xml->first_child(); child;
                     child = child.next_sibling()) {
                    new_xml.append_copy(child);
                }
            } else {
                auto& new_xml = doc->create_xml_part(new_part);
                auto root = new_xml.append_child(root_tag);
                root.append_attribute("xmlns:w").set_value(
                    "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
                root.append_attribute("xmlns:r").set_value(
                    "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
            }

            const std::string new_rel_id =
                doc->add_relationship("word/_rels/document.xml.rels", rel_type,
                                      new_part.substr(5));

            remove_header_footer(type, collection, refs, sect_pr, is_header);

            auto node = sect_pr.append_child(ref_tag);
            node.append_attribute("r:id").set_value(new_rel_id.c_str());
            node.append_attribute("w:type").set_value(header_footer_type_to_string(type));

            HeaderFooterRef ref;
            ref.type = type;
            ref.relationship_id = new_rel_id;
            ref.part_path = new_part;
            refs.push_back(ref);
            auto hf = std::make_shared<HeaderFooter>(doc, type, is_header);
            hf->set_part_path(new_part);
            hf->set_relationship_id(new_rel_id);
            collection.push_back(hf);
        }
    }
}

// ============================================================================
// Section Implementation
// ============================================================================

Section::Section() : CompositeNode() {
}

Section::Section(Document* doc) : CompositeNode(), document_(doc) {
    set_document(doc);
}

Section::Section(pugi::xml_node sect_pr, pugi::xml_node body, Document* doc, bool is_first)
    : CompositeNode(),
      document_(doc),
      is_first_section_(is_first),
      sect_pr_node_(sect_pr),
      body_node_(body) {
    if (sect_pr_node_) {
        load_properties();
    }
}

void Section::accept(DocumentVisitor* visitor) {
    if (!visitor) {
        return;
    }
    if (visitor->visit_section_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_section_end(*this);
    }
}

std::shared_ptr<Node> Section::clone(bool deep) const {
    auto cloned = std::make_shared<Section>(get_document());
    cloned->set_properties(properties_);
    cloned->set_first_section(is_first_section_);
    cloned->header_refs_ = header_refs_;
    cloned->footer_refs_ = footer_refs_;
    if (deep) {
        if (auto body = get_body()) {
            if (auto body_clone = std::dynamic_pointer_cast<Body>(body->clone(deep))) {
                cloned->set_body(body_clone);
            }
        }
        for (const auto& header : headers_) {
            if (auto h_clone = std::dynamic_pointer_cast<HeaderFooter>(header->clone(deep))) {
                cloned->headers_.push_back(h_clone);
            }
        }
        for (const auto& footer : footers_) {
            if (auto f_clone = std::dynamic_pointer_cast<HeaderFooter>(footer->clone(deep))) {
                cloned->footers_.push_back(f_clone);
            }
        }
    }
    return cloned;
}

std::string Section::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

std::shared_ptr<Body> Section::get_body() const {
    // Return the first Body child if exists
    for (const auto& child : get_children()) {
        if (auto body = std::dynamic_pointer_cast<Body>(child)) {
            return body;
        }
    }
    return nullptr;
}

void Section::set_body(const std::shared_ptr<Body>& body) {
    if (!body) {
        return;
    }

    // Remove existing body if any
    auto existing = get_body();
    if (existing) {
        remove_child(existing);
    }

    // Add new body as child
    body->set_document(get_document());
    const_cast<Section*>(this)->append_child(body);
}

std::shared_ptr<Body> Section::ensure_body() {
    auto body = get_body();
    if (!body) {
        body = std::make_shared<Body>(get_document());
        set_body(body);
    }
    return body;
}

std::shared_ptr<class Paragraph> Section::append_paragraph(const std::string& text) {
    auto body = ensure_body();
    if (!body) {
        return nullptr;
    }
    return body->append_paragraph(text);
}

std::shared_ptr<class Table> Section::append_table(int rows, int cols) {
    auto body = ensure_body();
    if (!body) {
        return nullptr;
    }
    return body->append_table(rows, cols);
}

Paragraph* Section::add_paragraph(const std::string& text, FormattingFlag flag) {
    if (!document_) {
        return nullptr;
    }

    // Get the body element to append to
    pugi::xml_node body;
    if (body_node_) {
        body = body_node_;
    } else if (sect_pr_node_) {
        body = sect_pr_node_.parent();
    }

    if (!body) {
        return nullptr;
    }

    // Always insert before sect_pr when it exists so content stays inside the section;
    // otherwise append to the body.
    pugi::xml_node p;
    if (sect_pr_node_) {
        p = body.insert_child_before("w:p", sect_pr_node_);
    } else {
        p = body.append_child("w:p");
    }

    if (!p) {
        return nullptr;
    }

    // Create paragraph object
    paragraphs_.emplace_back(body, p);
    Paragraph* para = &paragraphs_.back();

    // Add initial text if provided
    if (!text.empty()) {
        para->add_run(text, flag);
    }

    return para;
}

Table* Section::add_table(size_t rows, size_t cols) {
    if (!document_ || rows == 0 || cols == 0) {
        return nullptr;
    }

    // Get the body element
    pugi::xml_node body;
    if (body_node_) {
        body = body_node_;
    } else if (sect_pr_node_) {
        body = sect_pr_node_.parent();
    }

    if (!body) {
        return nullptr;
    }

    // Always insert before sect_pr when it exists so content stays inside the section;
    // otherwise append to the body.
    pugi::xml_node tbl;
    if (sect_pr_node_) {
        tbl = body.insert_child_before("w:tbl", sect_pr_node_);
    } else {
        tbl = body.append_child("w:tbl");
    }

    if (!tbl) {
        return nullptr;
    }

    // Add table properties
    auto tbl_pr = tbl.append_child("w:tblPr");
    auto tbl_w = tbl_pr.append_child("w:tblW");
    tbl_w.append_attribute("w:w").set_value("0");
    tbl_w.append_attribute("w:type").set_value("auto");

    // Create rows and cells
    for (size_t r = 0; r < rows; ++r) {
        auto tr = tbl.append_child("w:tr");
        tr.append_child("w:trPr");

        for (size_t c = 0; c < cols; ++c) {
            auto tc = tr.append_child("w:tc");
            tc.append_child("w:tcPr");

            // Add a paragraph to each cell
            auto p = tc.append_child("w:p");
            auto r_pr = p.append_child("w:r");
            auto t = r_pr.append_child("w:t");
            t.text().set("");
        }
    }

    // Create table object
    tables_.emplace_back(body, tbl);
    return &tables_.back();
}

std::shared_ptr<HeaderFooter> Section::add_header(HeaderFooterType type) {
    if (!document_) {
        return nullptr;
    }

    // Check if already exists
    if (auto existing = get_header_footer(headers_, type)) {
        return existing;
    }

    // Generate unique part name
    const std::string part_name =
        "word/header" + std::to_string(document_->get_next_header_number()) + ".xml";

    // Create header XML
    auto& header_doc = document_->create_xml_part(part_name);
    auto root = header_doc.append_child("w:hdr");
    root.append_attribute("xmlns:w").set_value(
        "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    root.append_attribute("xmlns:r").set_value(
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships");

    // Add paragraph to header
    auto p = root.append_child("w:p");
    auto r = p.append_child("w:r");
    auto t = r.append_child("w:t");
    t.text().set("");

    // Add relationship and capture the generated ID so the sect_pr reference
    // and the relationship entry stay in sync.
    const std::string rel_id = document_->add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/header",
        part_name.substr(5));  // Remove "word/" prefix

    // Add header reference to section properties if node exists
    if (sect_pr_node_) {
        auto header_ref = sect_pr_node_.append_child("w:header_reference");
        header_ref.append_attribute("r:id").set_value(rel_id.c_str());
        header_ref.append_attribute("w:type").set_value(header_footer_type_to_string(type));
    }

    // Create HeaderFooter object
    auto header = std::make_shared<HeaderFooter>(document_, type, true);
    header->set_part_path(part_name);
    header->set_relationship_id(rel_id);
    headers_.push_back(header);

    // Add to refs
    HeaderFooterRef ref;
    ref.type = type;
    ref.relationship_id = rel_id;
    ref.part_path = part_name;
    header_refs_.push_back(ref);

    return header;
}

std::shared_ptr<HeaderFooter> Section::add_footer(HeaderFooterType type) {
    if (!document_) {
        return nullptr;
    }

    // Check if already exists
    if (auto existing = get_header_footer(footers_, type)) {
        return existing;
    }

    // Generate unique part name
    const std::string part_name =
        "word/footer" + std::to_string(document_->get_next_footer_number()) + ".xml";

    // Create footer XML
    auto& footer_doc = document_->create_xml_part(part_name);
    auto root = footer_doc.append_child("w:ftr");
    root.append_attribute("xmlns:w").set_value(
        "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    root.append_attribute("xmlns:r").set_value(
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships");

    // Add paragraph to footer
    auto p = root.append_child("w:p");
    auto r = p.append_child("w:r");
    auto t = r.append_child("w:t");
    t.text().set("");

    // Add relationship and capture the generated ID so the sect_pr reference
    // and the relationship entry stay in sync.
    const std::string rel_id = document_->add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer",
        part_name.substr(5));

    // Add footer reference to section properties if node exists
    if (sect_pr_node_) {
        auto footer_ref = sect_pr_node_.append_child("w:footer_reference");
        footer_ref.append_attribute("r:id").set_value(rel_id.c_str());
        footer_ref.append_attribute("w:type").set_value(header_footer_type_to_string(type));
    }

    // Create HeaderFooter object
    auto footer = std::make_shared<HeaderFooter>(document_, type, false);
    footer->set_part_path(part_name);
    footer->set_relationship_id(rel_id);
    footers_.push_back(footer);

    // Add to refs
    HeaderFooterRef ref;
    ref.type = type;
    ref.relationship_id = rel_id;
    ref.part_path = part_name;
    footer_refs_.push_back(ref);

    return footer;
}

std::shared_ptr<HeaderFooter> Section::get_header(HeaderFooterType type) const {
    return get_header_footer(headers_, type);
}

std::shared_ptr<HeaderFooter> Section::get_footer(HeaderFooterType type) const {
    return get_header_footer(footers_, type);
}

bool Section::has_header(HeaderFooterType type) const {
    return has_header_footer(headers_, type);
}

bool Section::has_footer(HeaderFooterType type) const {
    return has_header_footer(footers_, type);
}

void Section::remove_header(HeaderFooterType type) {
    remove_header_footer(type, headers_, header_refs_, sect_pr_node_, true);
}

void Section::remove_footer(HeaderFooterType type) {
    remove_header_footer(type, footers_, footer_refs_, sect_pr_node_, false);
}

std::vector<std::shared_ptr<HeaderFooter>> Section::get_all_headers() const {
    return get_all_header_footer(headers_);
}

std::vector<std::shared_ptr<HeaderFooter>> Section::get_all_footers() const {
    return get_all_header_footer(footers_);
}

void Section::apply_properties() {
    if (!sect_pr_node_) {
        return;
    }

    properties_.apply_to(sect_pr_node_);
}

void Section::load_properties() {
    if (!sect_pr_node_) {
        return;
    }

    // Load from XML into prop structure
    auto pg_sz = sect_pr_node_.child("w:pgSz");
    if (pg_sz) {
        properties_.page_size.width = pg_sz.attribute("w:w").as_int();
        properties_.page_size.height = pg_sz.attribute("w:h").as_int();
        properties_.orientation = string_to_orientation(pg_sz.attribute("w:orient").value());
    }

    auto pg_mar = sect_pr_node_.child("w:pgMar");
    if (pg_mar) {
        properties_.page_margins.top = pg_mar.attribute("w:top").as_int();
        properties_.page_margins.right = pg_mar.attribute("w:right").as_int();
        properties_.page_margins.bottom = pg_mar.attribute("w:bottom").as_int();
        properties_.page_margins.left = pg_mar.attribute("w:left").as_int();
        properties_.page_margins.header = pg_mar.attribute("w:header").as_int(720);
        properties_.page_margins.footer = pg_mar.attribute("w:footer").as_int(720);
    }

    auto cols = sect_pr_node_.child("w:cols");
    if (cols) {
        properties_.columns.count = cols.attribute("w:num").as_int(1);
        properties_.columns.space = cols.attribute("w:space").as_int(720);
        properties_.columns.separator = cols.attribute("w:sep").as_bool(false);
    }
}

void Section::add_header_ref(const HeaderFooterRef& ref) {
    header_refs_.push_back(ref);
    if (document_ && !ref.relationship_id.empty()) {
        const std::string target =
            document_->get_relationship_target("word/_rels/document.xml.rels", ref.relationship_id);
        if (!target.empty()) {
            auto header = std::make_shared<HeaderFooter>(document_, ref.type, true);
            header->set_part_path("word/" + target);
            header->set_relationship_id(ref.relationship_id);
            headers_.push_back(header);
        }
    }
}

void Section::add_footer_ref(const HeaderFooterRef& ref) {
    footer_refs_.push_back(ref);
    if (document_ && !ref.relationship_id.empty()) {
        const std::string target =
            document_->get_relationship_target("word/_rels/document.xml.rels", ref.relationship_id);
        if (!target.empty()) {
            auto footer = std::make_shared<HeaderFooter>(document_, ref.type, false);
            footer->set_part_path("word/" + target);
            footer->set_relationship_id(ref.relationship_id);
            footers_.push_back(footer);
        }
    }
}

static const HeaderFooterRef* find_ref(const std::vector<HeaderFooterRef>& refs,
                                      HeaderFooterType type) {
    for (const auto& ref : refs) {
        if (ref.type == type) {
            return &ref;
        }
    }
    return nullptr;
}

void Section::link_to_previous(bool is_link_to_previous) {
    link_to_previous(HeaderFooterType::Default, is_link_to_previous);
    link_to_previous(HeaderFooterType::First, is_link_to_previous);
    link_to_previous(HeaderFooterType::Even, is_link_to_previous);
}

void Section::link_to_previous(HeaderFooterType type, bool is_link_to_previous) {
    if (!document_ || is_first_section_) {
        return;
    }
    auto prev = document_->get_previous_section(this);
    if (!prev) {
        return;
    }

    link_hf_to_previous(document_,
                        find_ref(prev->get_header_refs(), type),
                        find_ref(header_refs_, type),
                        header_refs_,
                        headers_,
                        sect_pr_node_,
                        type,
                        true,
                        is_link_to_previous);

    link_hf_to_previous(document_,
                        find_ref(prev->get_footer_refs(), type),
                        find_ref(footer_refs_, type),
                        footer_refs_,
                        footers_,
                        sect_pr_node_,
                        type,
                        false,
                        is_link_to_previous);
}

bool Section::is_linked_to_previous(HeaderFooterType type, bool is_header) const {
    if (!document_ || is_first_section_) {
        return false;
    }
    auto prev = document_->get_previous_section(this);
    if (!prev) {
        return false;
    }

    const HeaderFooterRef* prev_ref = is_header ? find_ref(prev->get_header_refs(), type)
                                                : find_ref(prev->get_footer_refs(), type);
    const HeaderFooterRef* curr_ref =
        is_header ? find_ref(header_refs_, type) : find_ref(footer_refs_, type);

    if (!prev_ref) {
        return false;
    }
    if (!curr_ref) {
        // If current section has no explicit ref but previous does,
        // Word may still treat it as linked (inherited). We treat it as linked.
        return true;
    }
    return curr_ref->part_path == prev_ref->part_path;
}

bool Section::is_linked_to_previous(HeaderFooterType type) const {
    return is_linked_to_previous(type, true) || is_linked_to_previous(type, false);
}

// ============================================================================
// HeaderFooter Implementation
// ============================================================================

HeaderFooter::HeaderFooter() : CompositeNode() {
}

HeaderFooter::HeaderFooter(Document* doc, HeaderFooterType type, bool is_header)
    : CompositeNode(), type_(type), is_header_(is_header) {
    set_document(doc);
}

std::string HeaderFooter::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

void HeaderFooter::accept(DocumentVisitor* visitor) {
    if (!visitor) {
        return;
    }

    // Determine visitor action based on header/footer type
    VisitorAction action = VisitorAction::Continue;
    if (is_header()) {
        action = visitor->visit_header_start(*this);
    } else {
        action = visitor->visit_footer_start(*this);
    }

    if (action == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }

        if (is_header()) {
            visitor->visit_header_end(*this);
        } else {
            visitor->visit_footer_end(*this);
        }
    }
}

std::shared_ptr<Node> HeaderFooter::clone(bool deep) const {
    auto cloned = std::make_shared<HeaderFooter>(get_document(), type_, is_header_);
    cloned->set_part_path(part_path_);
    cloned->set_relationship_id(relationship_id_);
    if (deep) {
        for (const auto& child : get_children()) {
            if (auto child_clone = child->clone(deep)) {
                cloned->append_child(child_clone);
            }
        }
    }
    return cloned;
}

std::shared_ptr<class Paragraph> HeaderFooter::append_paragraph(const std::string& text) {
    auto para = std::make_shared<Paragraph>(get_document());
    if (!text.empty()) {
        para->append_run(text);
    }
    append_child(para);
    return para;
}

std::shared_ptr<class Table> HeaderFooter::append_table(int rows, int cols) {
    auto table = std::make_shared<Table>(get_document(), rows, cols);
    append_child(table);
    return table;
}

std::vector<std::shared_ptr<class Paragraph>> HeaderFooter::get_paragraphs() const {
    return get_children_of_type<Paragraph>();
}

std::vector<std::shared_ptr<class Table>> HeaderFooter::get_tables() const {
    return get_children_of_type<Table>();
}

std::shared_ptr<Section> HeaderFooter::get_parent_section() const {
    auto* sect = get_ancestor<Section>();
    if (sect) {
        return std::static_pointer_cast<Section>(sect->shared_from_this());
    }
    return nullptr;
}

void HeaderFooter::ensure_minimum() {
    auto paras = get_paragraphs();
    if (paras.empty()) {
        append_paragraph();
    }
}

}  // namespace cdocx
