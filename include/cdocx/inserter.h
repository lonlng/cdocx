/**
 * @file inserter.h
 * @brief Document insertion functionality for merging DOCX files
 * @details Provides the DocumentInserter class for inserting content from
 *          one document into another. Supports inserting entire documents,
 *          paragraphs only, or tables only, at various positions.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 * 
 * @par Usage Example:
 * @code
 * #include <cdocx/inserter.h>
 * 
 * // Open target document
 * cdocx::Document target("main.docx");
 * target.open();
 * 
 * // Open source document
 * cdocx::Document source("content.docx");
 * source.open();
 * 
 * // Create inserter
 * cdocx::DocumentInserter inserter(&target);
 * 
 * // Insert entire document at end
 * inserter.insert_document(&source);
 * 
 * // Insert at specific position (0 = beginning, -1 = end)
 * inserter.insert_document_at(&source, 2);
 * 
 * // Insert paragraphs only
 * inserter.insert_paragraphs(&source);
 * 
 * // Save result
 * target.save("combined.docx");
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/base.h>
#include <pugixml.hpp>

namespace cdocx {

/**
 * @class DocumentInserter
 * @brief Inserts content from one document into another
 * @details The DocumentInserter class provides flexible content insertion
 *          capabilities. It can insert:
 *          - Complete documents (paragraphs and tables)
 *          - Paragraphs only
 *          - Tables only
 * 
 * @par Insert Positions:
 * - Default: end of document
 * - Specified index: 0 = document start, 1 = after first element, -1 = document end
 * - Specified paragraph: insert after specific paragraph
 * 
 * @par Notes:
 * - Source document content is cloned, source document is not modified
 * - Styles may need manual synchronization
 * - Media files like images need separate handling
 * 
 * @see Document
 * @since 0.1.0
 */
class DocumentInserter {
private:
    Document* target_doc_;  ///< Target document for insertion

    /**
     * @brief Clone a paragraph from source to target
     * @param[in] source_para Source paragraph node
     * @param[in] target_parent Target parent node (body or cell)
     * @return The cloned paragraph node
     */
    pugi::xml_node clone_paragraph(const pugi::xml_node& source_para, 
                                    pugi::xml_node target_parent);

    /**
     * @brief Clone a table from source to target
     * @param[in] source_table Source table node
     * @param[in] target_parent Target parent node
     * @return The cloned table node
     */
    pugi::xml_node clone_table(const pugi::xml_node& source_table,
                               pugi::xml_node target_parent);

public:
    /**
     * @brief Construct inserter for target document
     * @param[in] target Target document (must remain valid during operations)
     */
    explicit DocumentInserter(Document* target);

    /**
     * @brief Insert entire document at the end
     * @param[in] source Source document to insert
     * @details Inserts all paragraphs and tables from source at the end
     *          of the target document.
     * @pre Both documents must be open
     */
    void insert_document(Document* source);

    /**
     * @brief Insert document after a specific paragraph
     * @param[in] source Source document to insert
     * @param[in] after_para Paragraph after which to insert
     * @pre Both documents must be open
     */
    void insert_document_after(Document* source, Paragraph& after_para);

    /**
     * @brief Insert document at specific position
     * @param[in] source Source document to insert
     * @param[in] position Insert position:
     *                     - 0 = beginning of document
     *                     - N = after Nth block element
     *                     - -1 = end of document (default)
     * @pre Both documents must be open
     */
    void insert_document_at(Document* source, int position);

    /**
     * @brief Insert only paragraphs from source document
     * @param[in] source Source document
     * @param[in] position Insert position (default: -1 = end)
     * @pre Both documents must be open
     */
    void insert_paragraphs(Document* source, int position = -1);

    /**
     * @brief Insert only tables from source document
     * @param[in] source Source document
     * @param[in] position Insert position (default: -1 = end)
     * @pre Both documents must be open
     */
    void insert_tables(Document* source, int position = -1);
};

} // namespace cdocx
