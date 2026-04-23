/**
 * @file section.h
 * @brief Section support for CDocx - DOM Style
 * @details Provides Section class for managing document sections with independent
 *          page settings, headers, footers, and content.
 *          Section now inherits from CompositeNode and contains Body and HeaderFooter.
 *
 * @author CDocx Team
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0
 *
 * @par Usage Example:
 * @code
 * cdocx::Document doc("output.docx");
 * doc.open();
 *
 * // Add a section with landscape orientation
 * auto sect = doc.append_section();
 * sect->get_properties().orientation = SectionProperties::Orientation::Landscape;
 * sect->get_properties().page_size.width = 16840;  // A4 landscape width in twips
 * sect->get_properties().page_size.height = 11900; // A4 landscape height
 *
 * // Add content to section via body
 * auto body = sect->get_body();
 * auto para = body->append_paragraph("This is in landscape section");
 * para->append_run(" with bold text")->set_bold(true);
 *
 * doc.save();
 * @endcode
 */

#pragma once

#include <cdocx/body.h>
#include <cdocx/constants.h>
#include <cdocx/enums.h>
#include <cdocx/node.h>
#include <cdocx/paragraph.h>
#include <cdocx/properties.h>
#include <cdocx/table.h>

#include <list>
#include <memory>
#include <pugixml.hpp>
#include <vector>

namespace cdocx {

// Forward declarations
class Document;
class HeaderFooter;

// ============================================================================
// Header/Footer Reference Structure
// ============================================================================

struct HeaderFooterRef {
    HeaderFooterType type = HeaderFooterType::Default;
    std::string relationship_id;  ///< rId reference
    std::string part_path;        ///< Path like "word/header1.xml"
};

// ============================================================================
// Section Class - Document section (CompositeNode containing Body)
// ============================================================================

class Section : public CompositeNode {
  public:
    Section();
    explicit Section(Document* doc);

    // Legacy constructor (backward compatibility)
    Section(pugi::xml_node sect_pr, pugi::xml_node body, Document* doc, bool is_first);

    // Node overrides
    NodeType node_type() const override { return NodeType::Section; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;
    std::string get_text() const override;

    // Section properties
    SectionProperties& get_properties() { return properties_; }
    const SectionProperties& get_properties() const { return properties_; }
    void set_properties(const SectionProperties& props) { properties_ = props; }

    // Body (main content)
    std::shared_ptr<Body> get_body() const;
    void set_body(const std::shared_ptr<Body>& body);
    std::shared_ptr<Body> ensure_body();

    // Convenience: Access body content directly
    std::shared_ptr<class Paragraph> append_paragraph(const std::string& text = "");
    std::shared_ptr<class Table> append_table(int rows = 1, int cols = 1);

    // Legacy API (backward compatibility)
    class Paragraph* add_paragraph(const std::string& text = "", FormattingFlag flag = kNone);
    class Table* add_table(size_t rows, size_t cols);

    // Header/Footer operations
    std::shared_ptr<HeaderFooter> add_header(HeaderFooterType type = HeaderFooterType::Default);
    std::shared_ptr<HeaderFooter> add_footer(HeaderFooterType type = HeaderFooterType::Default);
    std::shared_ptr<HeaderFooter> get_header(
        HeaderFooterType type = HeaderFooterType::Default) const;
    std::shared_ptr<HeaderFooter> get_footer(
        HeaderFooterType type = HeaderFooterType::Default) const;
    bool has_header(HeaderFooterType type = HeaderFooterType::Default) const;
    bool has_footer(HeaderFooterType type = HeaderFooterType::Default) const;
    void remove_header(HeaderFooterType type = HeaderFooterType::Default);
    void remove_footer(HeaderFooterType type = HeaderFooterType::Default);

    // Get all headers/footers
    std::vector<std::shared_ptr<HeaderFooter>> get_all_headers() const;
    std::vector<std::shared_ptr<HeaderFooter>> get_all_footers() const;

    // Link to previous section's headers/footers (Aspose-aligned API)
    void link_to_previous(bool is_link_to_previous);
    void link_to_previous(HeaderFooterType type, bool is_link_to_previous);
    bool is_linked_to_previous(HeaderFooterType type, bool is_header) const;
    bool is_linked_to_previous(HeaderFooterType type) const;

    // Check if this is the first section
    bool is_first_section() const { return is_first_section_; }
    void set_first_section(bool is_first) { is_first_section_ = is_first; }

    // Parent document
    Document* get_document() const { return document_; }

    // Apply/load properties (for XML serialization)
    void apply_properties();
    void load_properties();

    // Set the underlying sectPr XML node (used during sync from physical)
    void set_sect_pr_node(pugi::xml_node node) { sect_pr_node_ = node; }

    // Add header/footer references (used during sync from physical)
    void add_header_ref(const HeaderFooterRef& ref);
    void add_footer_ref(const HeaderFooterRef& ref);

    // Get raw header/footer references (used during serialization)
    const std::vector<HeaderFooterRef>& get_header_refs() const { return header_refs_; }
    const std::vector<HeaderFooterRef>& get_footer_refs() const { return footer_refs_; }

  private:
    SectionProperties properties_;
    Document* document_ = nullptr;
    bool is_first_section_ = false;

    // Header/Footer references
    std::vector<HeaderFooterRef> header_refs_;
    std::vector<HeaderFooterRef> footer_refs_;

    // Cached HeaderFooter nodes
    mutable std::vector<std::shared_ptr<HeaderFooter>> headers_;
    mutable std::vector<std::shared_ptr<HeaderFooter>> footers_;

    // Legacy members (backward compatibility)
    pugi::xml_node sect_pr_node_;
    pugi::xml_node body_node_;
    std::list<class Paragraph> paragraphs_;
    std::list<class Table> tables_;
};

// ============================================================================
// HeaderFooter Class - Header or footer content (CompositeNode)
// ============================================================================

class HeaderFooter : public CompositeNode {
  public:
    HeaderFooter();
    HeaderFooter(Document* doc, HeaderFooterType type, bool is_header);

    // Node overrides
    NodeType node_type() const override { return is_header_ ? NodeType::Header : NodeType::Footer; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;
    std::string get_text() const override;

    // Type
    HeaderFooterType get_header_footer_type() const { return type_; }
    void set_header_footer_type(HeaderFooterType type) { type_ = type; }

    // Is header (false = footer)
    bool is_header() const { return is_header_; }
    bool is_footer() const { return !is_header_; }

    // Content operations
    std::shared_ptr<class Paragraph> append_paragraph(const std::string& text = "");
    std::shared_ptr<class Table> append_table(int rows = 1, int cols = 1);
    std::vector<std::shared_ptr<class Paragraph>> get_paragraphs() const;
    std::vector<std::shared_ptr<class Table>> get_tables() const;

    // Parent section
    std::shared_ptr<Section> get_parent_section() const;

    // Ensure minimum content
    void ensure_minimum();

    // XML part path
    std::string get_part_path() const { return part_path_; }
    void set_part_path(const std::string& path) { part_path_ = path; }

    // Relationship ID
    std::string get_relationship_id() const { return relationship_id_; }
    void set_relationship_id(const std::string& id) { relationship_id_ = id; }

  private:
    HeaderFooterType type_ = HeaderFooterType::Default;
    bool is_header_ = true;
    std::string part_path_;
    std::string relationship_id_;
};

// ============================================================================
// SectionCollection
// ============================================================================

class SectionCollection {
    std::vector<std::shared_ptr<Section>> sections_;

  public:
    using iterator = std::vector<std::shared_ptr<Section>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Section>>::const_iterator;

    SectionCollection() = default;
    explicit SectionCollection(const std::vector<std::shared_ptr<Section>>& sections)
        : sections_(sections) {}

    size_t get_count() const { return sections_.size(); }
    std::shared_ptr<Section> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < sections_.size()) {
            return sections_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Section> operator[](int index) const { return get_item(index); }

    iterator begin() { return sections_.begin(); }
    iterator end() { return sections_.end(); }
    const_iterator begin() const { return sections_.begin(); }
    const_iterator end() const { return sections_.end(); }

    std::shared_ptr<Section> first() const {
        return sections_.empty() ? nullptr : sections_.front();
    }
    std::shared_ptr<Section> last() const { return sections_.empty() ? nullptr : sections_.back(); }

    bool is_empty() const { return sections_.empty(); }
};

// ============================================================================
// HeaderFooterCollection
// ============================================================================

class HeaderFooterCollection {
    std::vector<std::shared_ptr<HeaderFooter>> items_;

  public:
    using iterator = std::vector<std::shared_ptr<HeaderFooter>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<HeaderFooter>>::const_iterator;

    HeaderFooterCollection() = default;
    explicit HeaderFooterCollection(const std::vector<std::shared_ptr<HeaderFooter>>& items)
        : items_(items) {}

    size_t get_count() const { return items_.size(); }
    std::shared_ptr<HeaderFooter> get_item(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < items_.size()) {
            return items_[index];
        }
        return nullptr;
    }
    std::shared_ptr<HeaderFooter> operator[](int index) const { return get_item(index); }

    iterator begin() { return items_.begin(); }
    iterator end() { return items_.end(); }
    const_iterator begin() const { return items_.begin(); }
    const_iterator end() const { return items_.end(); }

    std::shared_ptr<HeaderFooter> first() const {
        return items_.empty() ? nullptr : items_.front();
    }
    std::shared_ptr<HeaderFooter> last() const { return items_.empty() ? nullptr : items_.back(); }
};

}  // namespace cdocx
