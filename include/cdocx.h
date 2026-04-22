/**
 * @file cdocx.h
 * @brief CDocx v2.0 - Main aggregated header
 * @version 0.7.0
 *
 * CDocx is a modern C++17 library for creating, reading, and writing
 * Microsoft Office Word (.docx) files.
 *
 * Usage:
 *   #include <cdocx.h>
 *   using namespace cdocx;
 *
 *   // Create a new document
 *   auto doc = CDocx::create_document();
 *
 *   // Add content using fluent API
 *   doc->add_paragraph("Hello, World!")
 *      ->add_run(" Bold text", Font().set_bold(true));
 *
 *   // Save the document
 *   doc->save("output.docx");
 */

#pragma once

// Version information
#define CDOCX_VERSION_MAJOR 0
#define CDOCX_VERSION_MINOR 7
#define CDOCX_VERSION_PATCH 0
#define CDOCX_VERSION "0.7.0"

// ============================================================================
// Core Headers
// ============================================================================

#include "cdocx/advanced.h"
#include "cdocx/base.h"
#include "cdocx/body.h"
#include "cdocx/bookmark_inserter.h"
#include "cdocx/caption_generator.h"
#include "cdocx/comment.h"
#include "cdocx/control_char.h"
#include "cdocx/convert_util.h"
#include "cdocx/document.h"
#include "cdocx/enums.h"
#include "cdocx/file_format_util.h"
#include "cdocx/footnote.h"
#include "cdocx/format.h"
#include "cdocx/formfield.h"
#include "cdocx/inserter.h"
#include "cdocx/mail_merge.h"
#include "cdocx/node.h"
#include "cdocx/paragraph.h"
#include "cdocx/paragraph_builder.h"
#include "cdocx/properties.h"
#include "cdocx/section.h"
#include "cdocx/style.h"
#include "cdocx/table.h"
#include "cdocx/table_builder.h"
#include "cdocx/template.h"
#include "cdocx/template_engine.h"
#include "cdocx/watermark.h"

// ============================================================================
// Convenience / Aggregated Header
// ============================================================================

namespace cdocx {

// Forward declarations for builder classes
class DocumentBuilder;
class ParagraphBuilder;
class TableBuilder;

/**
 * @brief Main CDocx API entry point
 *
 * Provides static factory methods for creating documents and builders.
 */
class CDocx {
  public:
    // ========================================================================
    // Document Factory Methods
    // ========================================================================

    /**
     * @brief Create a new empty document
     * @return Shared pointer to the new document
     */
    static std::shared_ptr<Document> create_document();

    /**
     * @brief Load a document from file
     * @param path Path to the DOCX file
     * @return Shared pointer to the loaded document, or nullptr if failed
     */
    static std::shared_ptr<Document> load_document(const std::string& path);

    /**
     * @brief Save a document to file
     * @param doc Document to save
     * @param path Path where to save the document
     * @return true if successful, false otherwise
     */
    static bool save_document(std::shared_ptr<Document> doc, const std::string& path);

    // ========================================================================
    // Builder Factory Methods (Fluent API)
    // ========================================================================

    /**
     * @brief Create a new document builder
     * @return Shared pointer to a DocumentBuilder
     */
    static std::shared_ptr<DocumentBuilder> document();

    /**
     * @brief Create a new paragraph builder
     * @return Shared pointer to a ParagraphBuilder
     */
    static std::shared_ptr<ParagraphBuilder> paragraph();

    /**
     * @brief Create a new paragraph builder with initial text
     * @param text Initial text for the paragraph
     * @return Shared pointer to a ParagraphBuilder
     */
    static std::shared_ptr<ParagraphBuilder> paragraph(const std::string& text);

    /**
     * @brief Create a new table builder
     * @return Shared pointer to a TableBuilder
     */
    static std::shared_ptr<TableBuilder> table();

    /**
     * @brief Create a new table builder with specified dimensions
     * @param rows Number of rows
     * @param columns Number of columns
     * @return Shared pointer to a TableBuilder
     */
    static std::shared_ptr<TableBuilder> table(size_t rows, size_t columns);

    // ========================================================================
    // Version Information
    // ========================================================================

    /**
     * @brief Get the library version string
     * @return Version string (e.g., "0.7.0")
     */
    static std::string version();

    /**
     * @brief Get the full library version string
     * @return Full version string (e.g., "CDocx v0.7.0")
     */
    static std::string version_string();
};

}  // namespace cdocx
