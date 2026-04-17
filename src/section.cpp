/**
 * @file section.cpp
 * @brief Section class implementation
 */

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

/**
 * @brief Generate a unique relationship ID
 */
static std::string generate_rel_id(int id) {
    return "rId" + std::to_string(id);
}

/**
 * @brief Get header/footer type string for XML
 */
static const char* get_header_footer_type_str(HeaderFooterType type) {
    switch (type) {
        case HeaderFooterType::First:
            return "first";
        case HeaderFooterType::Even:
            return "even";
        default:
            return "default";
    }
}

static void remove_ref_from_node(pugi::xml_node sectPr, HeaderFooterType type, bool is_header) {
    if (!sectPr)
        return;
    const char* node_name = is_header ? "w:headerReference" : "w:footerReference";
    const char* type_str = get_header_footer_type_str(type);
    for (auto child = sectPr.child(node_name); child; child = child.next_sibling(node_name)) {
        if (std::strcmp(child.attribute("w:type").value(), type_str) == 0) {
            sectPr.remove_child(child);
            break;
        }
    }
}

// ============================================================================
// Section Implementation
// ============================================================================

Section::Section() : CompositeNode(), document_(nullptr), is_first_section_(false) {
}

Section::Section(Document* doc) : CompositeNode(), document_(doc), is_first_section_(false) {
    set_document(doc);
}

Section::Section(pugi::xml_node sectPr, pugi::xml_node body, Document* doc, bool is_first)
    : CompositeNode(),
      document_(doc),
      is_first_section_(is_first),
      sectPr_node_(sectPr),
      body_node_(body) {
    if (sectPr_node_) {
        load_properties();
    }
}

void Section::accept(DocumentVisitor* visitor) {
    if (!visitor)
        return;
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
    if (!body)
        return;

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
    if (!body)
        return nullptr;
    return body->append_paragraph(text);
}

std::shared_ptr<class Table> Section::append_table(int rows, int cols) {
    auto body = ensure_body();
    if (!body)
        return nullptr;
    return body->append_table(rows, cols);
}

Paragraph* Section::add_paragraph(const std::string& text, formatting_flag flag) {
    if (!document_)
        return nullptr;

    // Get the body element to append to
    pugi::xml_node body;
    if (is_first_section_ && body_node_) {
        body = body_node_;
    } else {
        // For subsequent sections, we need to find the body
        // and insert before sectPr
        body = sectPr_node_.parent();
    }

    if (!body)
        return nullptr;

    // Create paragraph before sectPr if not first section
    pugi::xml_node p;
    if (is_first_section_) {
        p = body.append_child("w:p");
    } else {
        p = body.insert_child_before("w:p", sectPr_node_);
    }

    if (!p)
        return nullptr;

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
    if (!document_ || rows == 0 || cols == 0)
        return nullptr;

    // Get the body element
    pugi::xml_node body;
    if (is_first_section_ && body_node_) {
        body = body_node_;
    } else {
        body = sectPr_node_.parent();
    }

    if (!body)
        return nullptr;

    // Create table XML
    pugi::xml_node tbl;
    if (is_first_section_) {
        tbl = body.append_child("w:tbl");
    } else {
        tbl = body.insert_child_before("w:tbl", sectPr_node_);
    }

    if (!tbl)
        return nullptr;

    // Add table properties
    auto tblPr = tbl.append_child("w:tblPr");
    auto tblW = tblPr.append_child("w:tblW");
    tblW.append_attribute("w:w").set_value("0");
    tblW.append_attribute("w:type").set_value("auto");

    // Create rows and cells
    for (size_t r = 0; r < rows; ++r) {
        auto tr = tbl.append_child("w:tr");
        auto trPr = tr.append_child("w:trPr");

        for (size_t c = 0; c < cols; ++c) {
            auto tc = tr.append_child("w:tc");
            auto tcPr = tc.append_child("w:tcPr");

            // Add a paragraph to each cell
            auto p = tc.append_child("w:p");
            auto rPr = p.append_child("w:r");
            auto t = rPr.append_child("w:t");
            t.text().set("");
        }
    }

    // Create table object
    tables_.emplace_back(body, tbl);
    return &tables_.back();
}

std::shared_ptr<HeaderFooter> Section::add_header(HeaderFooterType type) {
    if (!document_)
        return nullptr;

    // Check if already exists
    if (has_header(type)) {
        // Return existing header
        for (auto& h : headers_) {
            if (h && h->get_header_footer_type() == type)
                return h;
        }
    }

    // Generate unique part name
    std::string part_name =
        "word/header" + std::to_string(document_->get_next_header_number()) + ".xml";
    int rel_id_num = document_->generate_unique_bookmark_id();
    std::string rel_id = generate_rel_id(rel_id_num);

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

    // Add relationship
    document_->add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/header",
        part_name.substr(5));  // Remove "word/" prefix

    // Add header reference to section properties if node exists
    if (sectPr_node_) {
        auto headerRef = sectPr_node_.append_child("w:headerReference");
        headerRef.append_attribute("r:id").set_value(rel_id.c_str());
        headerRef.append_attribute("w:type").set_value(get_header_footer_type_str(type));
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
    if (!document_)
        return nullptr;

    // Check if already exists
    if (has_footer(type)) {
        // Return existing footer
        for (auto& f : footers_) {
            if (f && f->get_header_footer_type() == type)
                return f;
        }
    }

    // Generate unique part name
    std::string part_name =
        "word/footer" + std::to_string(document_->get_next_footer_number()) + ".xml";
    int rel_id_num = document_->generate_unique_bookmark_id();
    std::string rel_id = generate_rel_id(rel_id_num);

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

    // Add relationship
    document_->add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer",
        part_name.substr(5));

    // Add footer reference to section properties if node exists
    if (sectPr_node_) {
        auto footerRef = sectPr_node_.append_child("w:footerReference");
        footerRef.append_attribute("r:id").set_value(rel_id.c_str());
        footerRef.append_attribute("w:type").set_value(get_header_footer_type_str(type));
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
    for (const auto& h : headers_) {
        if (h && h->get_header_footer_type() == type) {
            return h;
        }
    }
    return nullptr;
}

std::shared_ptr<HeaderFooter> Section::get_footer(HeaderFooterType type) const {
    for (const auto& f : footers_) {
        if (f && f->get_header_footer_type() == type) {
            return f;
        }
    }
    return nullptr;
}

bool Section::has_header(HeaderFooterType type) const {
    for (const auto& h : headers_) {
        if (h && h->get_header_footer_type() == type)
            return true;
    }
    return false;
}

bool Section::has_footer(HeaderFooterType type) const {
    for (const auto& f : footers_) {
        if (f && f->get_header_footer_type() == type)
            return true;
    }
    return false;
}

void Section::remove_header(HeaderFooterType type) {
    headers_.erase(std::remove_if(headers_.begin(),
                                  headers_.end(),
                                  [type](const std::shared_ptr<HeaderFooter>& h) {
                                      return h && h->get_header_footer_type() == type;
                                  }),
                   headers_.end());
    remove_ref_from_node(sectPr_node_, type, true);
    header_refs_.erase(std::remove_if(header_refs_.begin(),
                                      header_refs_.end(),
                                      [type](const HeaderFooterRef& r) { return r.type == type; }),
                       header_refs_.end());
}

void Section::remove_footer(HeaderFooterType type) {
    footers_.erase(std::remove_if(footers_.begin(),
                                  footers_.end(),
                                  [type](const std::shared_ptr<HeaderFooter>& f) {
                                      return f && f->get_header_footer_type() == type;
                                  }),
                   footers_.end());
    remove_ref_from_node(sectPr_node_, type, false);
    footer_refs_.erase(std::remove_if(footer_refs_.begin(),
                                      footer_refs_.end(),
                                      [type](const HeaderFooterRef& r) { return r.type == type; }),
                       footer_refs_.end());
}

std::vector<std::shared_ptr<HeaderFooter>> Section::get_all_headers() const {
    std::vector<std::shared_ptr<HeaderFooter>> result;
    for (const auto& h : headers_) {
        if (h)
            result.push_back(h);
    }
    return result;
}

std::vector<std::shared_ptr<HeaderFooter>> Section::get_all_footers() const {
    std::vector<std::shared_ptr<HeaderFooter>> result;
    for (const auto& f : footers_) {
        if (f)
            result.push_back(f);
    }
    return result;
}

void Section::apply_properties() {
    if (!sectPr_node_)
        return;

    properties_.applyTo(sectPr_node_);
}

void Section::load_properties() {
    if (!sectPr_node_)
        return;

    // Load from XML into prop structure
    auto pgSz = sectPr_node_.child("w:pgSz");
    if (pgSz) {
        properties_.pageSize.width = pgSz.attribute("w:w").as_int();
        properties_.pageSize.height = pgSz.attribute("w:h").as_int();
        const char* orient = pgSz.attribute("w:orient").value();
        if (std::strcmp(orient, "landscape") == 0) {
            properties_.orientation = SectionProperties::Orientation::Landscape;
        } else {
            properties_.orientation = SectionProperties::Orientation::Portrait;
        }
    }

    auto pgMar = sectPr_node_.child("w:pgMar");
    if (pgMar) {
        properties_.pageMargins.top = pgMar.attribute("w:top").as_int();
        properties_.pageMargins.right = pgMar.attribute("w:right").as_int();
        properties_.pageMargins.bottom = pgMar.attribute("w:bottom").as_int();
        properties_.pageMargins.left = pgMar.attribute("w:left").as_int();
        properties_.pageMargins.header = pgMar.attribute("w:header").as_int(720);
        properties_.pageMargins.footer = pgMar.attribute("w:footer").as_int(720);
    }

    auto cols = sectPr_node_.child("w:cols");
    if (cols) {
        properties_.columns.count = cols.attribute("w:num").as_int(1);
        properties_.columns.space = cols.attribute("w:space").as_int(720);
        properties_.columns.separator = cols.attribute("w:sep").as_bool(false);
    }
}

void Section::add_header_ref(const HeaderFooterRef& ref) {
    header_refs_.push_back(ref);
    if (document_ && !ref.relationship_id.empty()) {
        std::string target =
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
        std::string target =
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
        if (ref.type == type)
            return &ref;
    }
    return nullptr;
}

void Section::link_to_previous(bool is_link_to_previous) {
    link_to_previous(HeaderFooterType::Default, is_link_to_previous);
    link_to_previous(HeaderFooterType::First, is_link_to_previous);
    link_to_previous(HeaderFooterType::Even, is_link_to_previous);
}

void Section::link_to_previous(HeaderFooterType type, bool is_link_to_previous) {
    if (!document_ || is_first_section_)
        return;
    auto prev = document_->get_previous_section(this);
    if (!prev)
        return;

    // Handle header
    {
        auto* prev_ref = find_ref(prev->get_header_refs(), type);
        auto* curr_ref = find_ref(header_refs_, type);
        if (is_link_to_previous) {
            if (curr_ref) {
                // Already has a header; if it's already linked, nothing to do
                if (prev_ref && curr_ref->part_path == prev_ref->part_path) {
                    // already linked
                } else if (prev_ref) {
                    // Link to previous
                    remove_ref_from_node(sectPr_node_, type, true);
                    header_refs_.erase(
                        std::remove_if(header_refs_.begin(),
                                       header_refs_.end(),
                                       [type](const HeaderFooterRef& r) { return r.type == type; }),
                        header_refs_.end());
                    remove_header(type);
                    HeaderFooterRef new_ref = *prev_ref;
                    auto headerRef = sectPr_node_.append_child("w:headerReference");
                    headerRef.append_attribute("r:id").set_value(new_ref.relationship_id.c_str());
                    headerRef.append_attribute("w:type").set_value(
                        get_header_footer_type_str(type));
                    header_refs_.push_back(new_ref);
                    auto header = std::make_shared<HeaderFooter>(document_, type, true);
                    header->set_part_path(new_ref.part_path);
                    header->set_relationship_id(new_ref.relationship_id);
                    headers_.push_back(header);
                } else {
                    // Previous has no header of this type; remove current to inherit
                    remove_ref_from_node(sectPr_node_, type, true);
                    header_refs_.erase(
                        std::remove_if(header_refs_.begin(),
                                       header_refs_.end(),
                                       [type](const HeaderFooterRef& r) { return r.type == type; }),
                        header_refs_.end());
                    remove_header(type);
                }
            } else {
                // Current has no header; link to previous if previous has one
                if (prev_ref) {
                    HeaderFooterRef new_ref = *prev_ref;
                    auto headerRef = sectPr_node_.append_child("w:headerReference");
                    headerRef.append_attribute("r:id").set_value(new_ref.relationship_id.c_str());
                    headerRef.append_attribute("w:type").set_value(
                        get_header_footer_type_str(type));
                    header_refs_.push_back(new_ref);
                    auto header = std::make_shared<HeaderFooter>(document_, type, true);
                    header->set_part_path(new_ref.part_path);
                    header->set_relationship_id(new_ref.relationship_id);
                    headers_.push_back(header);
                }
            }
        } else {
            // Unlink: copy previous header to a new part if needed
            if (prev_ref) {
                bool need_copy = (!curr_ref) || (curr_ref->part_path == prev_ref->part_path);
                if (need_copy) {
                    // Generate new part name
                    std::string new_part = "word/header" +
                                           std::to_string(document_->get_next_header_number()) +
                                           ".xml";
                    int rel_id_num = document_->generate_unique_bookmark_id();
                    std::string new_rel_id = generate_rel_id(rel_id_num);

                    // Copy XML content from previous part
                    auto* prev_doc = document_->get_xml_part(prev_ref->part_path);
                    if (prev_doc) {
                        auto& new_doc = document_->create_xml_part(new_part);
                        new_doc.reset();
                        for (auto child = prev_doc->first_child(); child;
                             child = child.next_sibling()) {
                            new_doc.append_copy(child);
                        }
                    } else {
                        auto& new_doc = document_->create_xml_part(new_part);
                        auto root = new_doc.append_child("w:hdr");
                        root.append_attribute("xmlns:w").set_value(
                            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
                        root.append_attribute("xmlns:r").set_value(
                            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
                    }

                    document_->add_relationship("word/_rels/document.xml.rels",
                                                "http://schemas.openxmlformats.org/officeDocument/"
                                                "2006/relationships/header",
                                                new_part.substr(5));

                    remove_ref_from_node(sectPr_node_, type, true);
                    header_refs_.erase(
                        std::remove_if(header_refs_.begin(),
                                       header_refs_.end(),
                                       [type](const HeaderFooterRef& r) { return r.type == type; }),
                        header_refs_.end());
                    remove_header(type);

                    auto headerRef = sectPr_node_.append_child("w:headerReference");
                    headerRef.append_attribute("r:id").set_value(new_rel_id.c_str());
                    headerRef.append_attribute("w:type").set_value(
                        get_header_footer_type_str(type));

                    HeaderFooterRef ref;
                    ref.type = type;
                    ref.relationship_id = new_rel_id;
                    ref.part_path = new_part;
                    header_refs_.push_back(ref);
                    auto header = std::make_shared<HeaderFooter>(document_, type, true);
                    header->set_part_path(new_part);
                    header->set_relationship_id(new_rel_id);
                    headers_.push_back(header);
                }
            }
        }
    }

    // Handle footer (mirror of header logic)
    {
        auto* prev_ref = find_ref(prev->get_footer_refs(), type);
        auto* curr_ref = find_ref(footer_refs_, type);
        if (is_link_to_previous) {
            if (curr_ref) {
                if (prev_ref && curr_ref->part_path == prev_ref->part_path) {
                    // already linked
                } else if (prev_ref) {
                    remove_ref_from_node(sectPr_node_, type, false);
                    footer_refs_.erase(
                        std::remove_if(footer_refs_.begin(),
                                       footer_refs_.end(),
                                       [type](const HeaderFooterRef& r) { return r.type == type; }),
                        footer_refs_.end());
                    remove_footer(type);
                    HeaderFooterRef new_ref = *prev_ref;
                    auto footerRef = sectPr_node_.append_child("w:footerReference");
                    footerRef.append_attribute("r:id").set_value(new_ref.relationship_id.c_str());
                    footerRef.append_attribute("w:type").set_value(
                        get_header_footer_type_str(type));
                    footer_refs_.push_back(new_ref);
                    auto footer = std::make_shared<HeaderFooter>(document_, type, false);
                    footer->set_part_path(new_ref.part_path);
                    footer->set_relationship_id(new_ref.relationship_id);
                    footers_.push_back(footer);
                } else {
                    remove_ref_from_node(sectPr_node_, type, false);
                    footer_refs_.erase(
                        std::remove_if(footer_refs_.begin(),
                                       footer_refs_.end(),
                                       [type](const HeaderFooterRef& r) { return r.type == type; }),
                        footer_refs_.end());
                    remove_footer(type);
                }
            } else {
                if (prev_ref) {
                    HeaderFooterRef new_ref = *prev_ref;
                    auto footerRef = sectPr_node_.append_child("w:footerReference");
                    footerRef.append_attribute("r:id").set_value(new_ref.relationship_id.c_str());
                    footerRef.append_attribute("w:type").set_value(
                        get_header_footer_type_str(type));
                    footer_refs_.push_back(new_ref);
                    auto footer = std::make_shared<HeaderFooter>(document_, type, false);
                    footer->set_part_path(new_ref.part_path);
                    footer->set_relationship_id(new_ref.relationship_id);
                    footers_.push_back(footer);
                }
            }
        } else {
            if (prev_ref) {
                bool need_copy = (!curr_ref) || (curr_ref->part_path == prev_ref->part_path);
                if (need_copy) {
                    std::string new_part = "word/footer" +
                                           std::to_string(document_->get_next_footer_number()) +
                                           ".xml";
                    int rel_id_num = document_->generate_unique_bookmark_id();
                    std::string new_rel_id = generate_rel_id(rel_id_num);

                    auto* prev_doc = document_->get_xml_part(prev_ref->part_path);
                    if (prev_doc) {
                        auto& new_doc = document_->create_xml_part(new_part);
                        new_doc.reset();
                        for (auto child = prev_doc->first_child(); child;
                             child = child.next_sibling()) {
                            new_doc.append_copy(child);
                        }
                    } else {
                        auto& new_doc = document_->create_xml_part(new_part);
                        auto root = new_doc.append_child("w:ftr");
                        root.append_attribute("xmlns:w").set_value(
                            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
                        root.append_attribute("xmlns:r").set_value(
                            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
                    }

                    document_->add_relationship("word/_rels/document.xml.rels",
                                                "http://schemas.openxmlformats.org/officeDocument/"
                                                "2006/relationships/footer",
                                                new_part.substr(5));

                    remove_ref_from_node(sectPr_node_, type, false);
                    footer_refs_.erase(
                        std::remove_if(footer_refs_.begin(),
                                       footer_refs_.end(),
                                       [type](const HeaderFooterRef& r) { return r.type == type; }),
                        footer_refs_.end());
                    remove_footer(type);

                    auto footerRef = sectPr_node_.append_child("w:footerReference");
                    footerRef.append_attribute("r:id").set_value(new_rel_id.c_str());
                    footerRef.append_attribute("w:type").set_value(
                        get_header_footer_type_str(type));

                    HeaderFooterRef ref;
                    ref.type = type;
                    ref.relationship_id = new_rel_id;
                    ref.part_path = new_part;
                    footer_refs_.push_back(ref);
                    auto footer = std::make_shared<HeaderFooter>(document_, type, false);
                    footer->set_part_path(new_part);
                    footer->set_relationship_id(new_rel_id);
                    footers_.push_back(footer);
                }
            }
        }
    }
}

bool Section::is_linked_to_previous(HeaderFooterType type, bool is_header) const {
    if (!document_ || is_first_section_)
        return false;
    auto prev = document_->get_previous_section(this);
    if (!prev)
        return false;

    const HeaderFooterRef* prev_ref = is_header ? find_ref(prev->get_header_refs(), type)
                                                : find_ref(prev->get_footer_refs(), type);
    const HeaderFooterRef* curr_ref =
        is_header ? find_ref(header_refs_, type) : find_ref(footer_refs_, type);

    if (!prev_ref)
        return false;
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

HeaderFooter::HeaderFooter() : CompositeNode(), type_(HeaderFooterType::Default), is_header_(true) {
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
    if (!visitor)
        return;

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
    Section* sect = get_ancestor<Section>();
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
