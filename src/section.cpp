/**
 * @file section.cpp
 * @brief Section class implementation
 */

#include <cdocx/section.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/table.h>
#include <detail/impl.h>
#include <sstream>

namespace cdocx {

// ============================================================================
// Helper Functions
// ============================================================================

/**
 * @brief Generate a unique relationship ID
 */
static std::string generate_rel_id(int& counter) {
    return "rId" + std::to_string(++counter);
}

/**
 * @brief Get header/footer type string for XML
 */
static const char* get_header_footer_type_str(HeaderFooterType type) {
    switch (type) {
        case HeaderFooterType::First: return "first";
        case HeaderFooterType::Even: return "even";
        default: return "default";
    }
}

// ============================================================================
// Section Implementation
// ============================================================================

Section::Section() 
    : document_(nullptr), is_first_section_(false) {
}

Section::Section(pugi::xml_node sectPr, pugi::xml_node body, 
                 Document* doc, bool is_first)
    : sectPr_node_(sectPr), body_node_(body), 
      document_(doc), is_first_section_(is_first) {
    
    if (sectPr_node_) {
        load_properties();
    }
}

Paragraph* Section::add_paragraph(const std::string& text, formatting_flag flag) {
    if (!document_) return nullptr;
    
    // Get the body element to append to
    pugi::xml_node body;
    if (is_first_section_ && body_node_) {
        body = body_node_;
    } else {
        // For subsequent sections, we need to find the body
        // and insert before sectPr
        body = sectPr_node_.parent();
    }
    
    if (!body) return nullptr;
    
    // Create paragraph before sectPr if not first section
    pugi::xml_node p;
    if (is_first_section_) {
        p = body.append_child("w:p");
    } else {
        p = body.insert_child_before("w:p", sectPr_node_);
    }
    
    if (!p) return nullptr;
    
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
    if (!document_ || rows == 0 || cols == 0) return nullptr;
    
    // Get the body element
    pugi::xml_node body;
    if (is_first_section_ && body_node_) {
        body = body_node_;
    } else {
        body = sectPr_node_.parent();
    }
    
    if (!body) return nullptr;
    
    // Create table XML
    pugi::xml_node tbl;
    if (is_first_section_) {
        tbl = body.append_child("w:tbl");
    } else {
        tbl = body.insert_child_before("w:tbl", sectPr_node_);
    }
    
    if (!tbl) return nullptr;
    
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

std::list<Paragraph>& Section::paragraphs() {
    return paragraphs_;
}

std::list<Table>& Section::tables() {
    return tables_;
}

bool Section::add_header(HeaderFooterType type) {
    if (!document_ || !sectPr_node_) return false;
    
    // Check if already exists
    if (has_header(type)) return true;
    
    // Get document implementation for relationship management
    // Generate unique part name
    std::string part_name = "word/header" + std::to_string(document_->impl_->get_next_header_number()) + ".xml";
    
    int& rel_counter = document_->impl_->next_bookmark_id_;
    std::string rel_id = generate_rel_id(rel_counter);
    
    // Create header XML
    auto& header_doc = document_->impl_->create_xml_part(part_name);
    auto root = header_doc.append_child("w:hdr");
    root.append_attribute("xmlns:w").set_value("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    root.append_attribute("xmlns:r").set_value("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    
    // Add paragraph to header
    auto p = root.append_child("w:p");
    auto r = p.append_child("w:r");
    auto t = r.append_child("w:t");
    t.text().set("");
    
    // Add relationship
    document_->impl_->add_relationship("word/_rels/document.xml.rels", 
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/header",
        part_name.substr(5)); // Remove "word/" prefix
    
    // Add header reference to section properties
    auto headerRef = sectPr_node_.append_child("w:headerReference");
    headerRef.append_attribute("r:id").set_value(rel_id.c_str());
    headerRef.append_attribute("w:type").set_value(get_header_footer_type_str(type));
    
    // Store reference
    HeaderFooterRef ref;
    ref.type = type;
    ref.relationship_id = rel_id;
    ref.part_path = part_name;
    headers_.push_back(ref);
    
    return true;
}

bool Section::add_footer(HeaderFooterType type) {
    if (!document_ || !sectPr_node_) return false;
    
    // Check if already exists
    if (has_footer(type)) return true;
    
    // Generate unique part name
    std::string part_name = "word/footer" + std::to_string(document_->impl_->get_next_footer_number()) + ".xml";
    
    std::string rel_id = generate_rel_id(document_->impl_->next_bookmark_id_);
    
    // Create footer XML
    auto& footer_doc = document_->impl_->create_xml_part(part_name);
    auto root = footer_doc.append_child("w:ftr");
    root.append_attribute("xmlns:w").set_value("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    root.append_attribute("xmlns:r").set_value("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    
    // Add paragraph to footer
    auto p = root.append_child("w:p");
    auto r = p.append_child("w:r");
    auto t = r.append_child("w:t");
    t.text().set("");
    
    // Add relationship
    document_->impl_->add_relationship("word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer",
        part_name.substr(5));
    
    // Add footer reference to section properties
    auto footerRef = sectPr_node_.append_child("w:footerReference");
    footerRef.append_attribute("r:id").set_value(rel_id.c_str());
    footerRef.append_attribute("w:type").set_value(get_header_footer_type_str(type));
    
    // Store reference
    HeaderFooterRef ref;
    ref.type = type;
    ref.relationship_id = rel_id;
    ref.part_path = part_name;
    footers_.push_back(ref);
    
    return true;
}

bool Section::has_header(HeaderFooterType type) const {
    for (const auto& h : headers_) {
        if (h.type == type) return true;
    }
    return false;
}

bool Section::has_footer(HeaderFooterType type) const {
    for (const auto& f : footers_) {
        if (f.type == type) return true;
    }
    return false;
}

pugi::xml_document* Section::get_header_xml(HeaderFooterType type) {
    for (const auto& h : headers_) {
        if (h.type == type && document_) {
            return document_->get_xml_part(h.part_path);
        }
    }
    return nullptr;
}

pugi::xml_document* Section::get_footer_xml(HeaderFooterType type) {
    for (const auto& f : footers_) {
        if (f.type == type && document_) {
            return document_->get_xml_part(f.part_path);
        }
    }
    return nullptr;
}

void Section::apply_properties() {
    if (!sectPr_node_) return;
    
    prop.applyTo(sectPr_node_);
}

void Section::load_properties() {
    if (!sectPr_node_) return;
    
    // Load from XML into prop structure
    // This is handled by the properties extraction mechanism
    // For now, we keep default values
}

// ============================================================================
// SectionIterator Implementation
// ============================================================================

SectionIterator::SectionIterator() : document_(nullptr) {
}

SectionIterator::SectionIterator(Document& doc) : document_(&doc) {
    // Initialize iteration over document sections
    // This will be implemented when Document sections_ member is added
}

SectionIterator& SectionIterator::next() {
    if (current_ != end_) {
        ++current_;
    }
    return *this;
}

bool SectionIterator::has_next() const {
    return current_ != end_;
}

Section& SectionIterator::current() {
    return *current_;
}

// ============================================================================
// SectionCollection Implementation
// ============================================================================

SectionIterator SectionCollection::begin() {
    return SectionIterator(document_);
}

SectionIterator SectionCollection::end() {
    return SectionIterator();
}

} // namespace cdocx
