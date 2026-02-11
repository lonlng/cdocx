/**
 * @file section.h
 * @brief Section (分节) support for CDocx
 * @details Provides Section class for managing document sections with independent
 *          page settings, headers, footers, and content.
 * 
 * @author CDocx Team
 * @copyright MIT License
 * @date 2026
 * @version 0.5.0
 * 
 * @par Usage Example:
 * @code
 * cdocx::Document doc("output.docx");
 * doc.open();
 * 
 * // Add a section with landscape orientation
 * auto sect = doc.add_section();
 * sect->prop.orientation = SectionProperties::Orientation::Landscape;
 * sect->prop.pageSize.width = 16840;  // A4 landscape width in twips
 * sect->prop.pageSize.height = 11900; // A4 landscape height
 * 
 * // Add content to section
 * auto para = sect->add_paragraph();
 * para->add_run("This is in landscape section");
 * 
 * doc.save();
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/properties.h>
#include <cdocx/base.h>
#include <memory>
#include <list>

namespace cdocx {

// Forward declarations
class Section;
class SectionIterator;
using SectionPointer = std::shared_ptr<Section>;

/**
 * @brief Header/Footer type enumeration
 */
enum class HeaderFooterType {
    Default,    ///< Default header/footer
    First,      ///< First page only
    Even        ///< Even pages only
};

/**
 * @brief Header/Footer reference structure
 */
struct HeaderFooterRef {
    HeaderFooterType type = HeaderFooterType::Default;
    std::string relationship_id;  ///< rId reference
    std::string part_path;        ///< Path like "word/header1.xml"
};

/**
 * @class Section
 * @brief Represents a document section with independent page settings
 * @details A Section is a container for paragraphs and tables with its own
 *          page setup (size, orientation, margins), headers, and footers.
 *          Multiple sections allow different page layouts within one document.
 * 
 * @par Section Properties:
 * - Page size and orientation
 * - Page margins
 * - Headers and footers
 * - Column layout
 * - Line numbering
 * 
 * @since 0.5.0
 */
class Section {
private:
    friend class Document;
    friend class SectionIterator;
    
    pugi::xml_node sectPr_node_;        ///< Section properties node
    pugi::xml_node body_node_;          ///< Body content node (for first section)
    Document* document_ = nullptr;      ///< Parent document
    
    // Content tracking
    std::list<Paragraph> paragraphs_;   ///< Paragraphs in this section
    std::list<Table> tables_;           ///< Tables in this section
    
    // Header/Footer references
    std::vector<HeaderFooterRef> headers_;
    std::vector<HeaderFooterRef> footers_;
    
    bool is_first_section_ = false;     ///< Is this the first section?

public:
    /**
     * @brief Section properties
     * @details Public structure for easy property access
     */
    SectionProperties prop;

public:
    /**
     * @brief Default constructor
     */
    Section();
    
    /**
     * @brief Construct section with XML nodes
     * @param sectPr Section properties node
     * @param body Body content node (nullptr for non-first sections)
     * @param doc Parent document
     * @param is_first Whether this is the first section
     */
    Section(pugi::xml_node sectPr, pugi::xml_node body, 
            Document* doc, bool is_first = false);
    
    /**
     * @brief Destructor
     */
    ~Section() = default;

    // =======================================================================
    // Content Operations
    // =======================================================================
    
    /**
     * @brief Add a paragraph to this section
     * @param text Optional initial text
     * @param flag Formatting flags for initial run
     * @return Pointer to the new paragraph
     */
    Paragraph* add_paragraph(const std::string& text = "", 
                              formatting_flag flag = none);
    
    /**
     * @brief Add a table to this section
     * @param rows Number of rows
     * @param cols Number of columns
     * @return Pointer to the new table
     */
    Table* add_table(size_t rows, size_t cols);
    
    /**
     * @brief Get all paragraphs in this section
     * @return List of paragraphs
     */
    std::list<Paragraph>& paragraphs();
    
    /**
     * @brief Get all tables in this section
     * @return List of tables
     */
    std::list<Table>& tables();

    // =======================================================================
    // Header/Footer Operations
    // =======================================================================
    
    /**
     * @brief Add a header to this section
     * @param type Header type (default, first, even)
     * @return true if successful
     */
    bool add_header(HeaderFooterType type = HeaderFooterType::Default);
    
    /**
     * @brief Add a footer to this section
     * @param type Footer type (default, first, even)
     * @return true if successful
     */
    bool add_footer(HeaderFooterType type = HeaderFooterType::Default);
    
    /**
     * @brief Check if section has header
     * @param type Header type to check
     * @return true if header exists
     */
    bool has_header(HeaderFooterType type = HeaderFooterType::Default) const;
    
    /**
     * @brief Check if section has footer
     * @param type Footer type to check
     * @return true if footer exists
     */
    bool has_footer(HeaderFooterType type = HeaderFooterType::Default) const;
    
    /**
     * @brief Get header XML document
     * @param type Header type
     * @return Pointer to header XML, nullptr if not exists
     */
    pugi::xml_document* get_header_xml(HeaderFooterType type = HeaderFooterType::Default);
    
    /**
     * @brief Get footer XML document
     * @param type Footer type
     * @return Pointer to footer XML, nullptr if not exists
     */
    pugi::xml_document* get_footer_xml(HeaderFooterType type = HeaderFooterType::Default);

    // =======================================================================
    // Properties Application
    // =======================================================================
    
    /**
     * @brief Apply section properties to XML
     * @internal Called by Document before saving
     */
    void apply_properties();
    
    /**
     * @brief Load section properties from XML
     * @internal Called by Document when loading
     */
    void load_properties();

    // =======================================================================
    // Utility Methods
    // =======================================================================
    
    /**
     * @brief Get the section properties XML node
     * @return The w:sectPr node
     */
    pugi::xml_node get_sectPr_node() const { return sectPr_node_; }
    
    /**
     * @brief Check if this is the first section
     * @return true if first section
     */
    bool is_first_section() const { return is_first_section_; }
    
    /**
     * @brief Get parent document
     * @return Pointer to parent document
     */
    Document* get_document() const { return document_; }
};

/**
 * @class SectionIterator
 * @brief Iterator for traversing sections in a document
 * @since 0.5.0
 */
class SectionIterator {
private:
    Document* document_ = nullptr;
    std::list<Section>::iterator current_;
    std::list<Section>::iterator end_;
    
public:
    /**
     * @brief Default constructor
     */
    SectionIterator();
    
    /**
     * @brief Construct iterator for document
     * @param doc Parent document
     */
    explicit SectionIterator(Document& doc);
    
    /**
     * @brief Move to next section
     * @return Reference to this iterator
     */
    SectionIterator& next();
    
    /**
     * @brief Check if more sections available
     * @return true if valid section available
     */
    bool has_next() const;
    
    /**
     * @brief Get current section
     * @return Reference to current section
     */
    Section& current();
    
    /**
     * @brief Dereference operator
     * @return Reference to current section
     */
    Section& operator*() { return current(); }
    
    /**
     * @brief Arrow operator
     * @return Pointer to current section
     */
    Section* operator->() { return &current(); }
    
    /**
     * @brief Prefix increment
     * @return Reference to this iterator
     */
    SectionIterator& operator++() { next(); return *this; }
};

/**
 * @brief Section collection for range-based for loops
 * @since 0.5.0
 */
class SectionCollection {
private:
    Document& document_;
    
public:
    /**
     * @brief Construct collection for document
     * @param doc Parent document
     */
    explicit SectionCollection(Document& doc) : document_(doc) {}
    
    /**
     * @brief Get begin iterator
     * @return Iterator to first section
     */
    SectionIterator begin();
    
    /**
     * @brief Get end iterator
     * @return End iterator
     */
    SectionIterator end();
};

} // namespace cdocx
