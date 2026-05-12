/**
 * @file fwd.h
 * @brief Forward declarations for CDocx library
 * @details Provides forward declarations for all public classes in the CDocx library.
 *          Use this header to reduce compile times when only forward declarations are needed.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 *
 * @par Usage Example:
 * @code
 * #include <cdocx/fwd.h>  // Lightweight, forward declarations only
 *
 * // Declare function parameters and return types
 * void process_document(cdocx::Document& doc);
 * cdocx::Paragraph* find_paragraph(cdocx::Document& doc, const std::string& text);
 * @endcode
 */

#pragma once

namespace pugi {
class xml_node;      // NOLINT(readability-identifier-naming): pugixml external API
class xml_document;  // NOLINT(readability-identifier-naming): pugixml external API
}  // namespace pugi

namespace cdocx {

// ============================================================================
// Core Document Classes
// ============================================================================

/**
 * @brief Main document class representing a DOCX file
 * @see Document
 */
class Document;

/**
 * @brief Text run class representing a segment of formatted text
 * @see Run
 */
class Run;

/**
 * @brief Paragraph class containing formatted text runs
 * @see Paragraph
 */
class Paragraph;

// ============================================================================
// Table Classes
// ============================================================================

/**
 * @brief Table cell containing paragraphs
 * @see TableCell
 */
class TableCell;

/**
 * @brief Table row containing cells
 * @see TableRow
 */
class TableRow;

/**
 * @brief Table containing rows
 * @see Table
 */
class Table;

// ============================================================================
// Template and Insertion Classes
// ============================================================================

/**
 * @brief Template class for placeholder replacement
 * @see Template
 */
class Template;

/**
 * @brief Document inserter for merging documents
 * @see DocumentInserter
 */
class DocumentInserter;

// ============================================================================
// Advanced Feature Classes
// ============================================================================

/**
 * @brief Bookmark for marking document locations
 * @see Bookmark
 */
class Bookmark;

/**
 * @brief Collection of bookmarks
 * @see BookmarkCollection
 */
class BookmarkCollection;

/**
 * @brief Range representing a portion of the document
 * @see Range
 */
class Range;

/**
 * @brief Builder class for constructing documents programmatically
 * @see DocumentBuilder
 */
class DocumentBuilder;

// ============================================================================
// Iterator Helper
// ============================================================================

/**
 * @brief Iterator helper for range-based for loops
 * @see IteratorHelper
 */
class IteratorHelper;

/**
 * @brief Template iterator for CDocx collections
 * @tparam T Element type
 * @tparam P Parent node type
 * @tparam C Current node type
 * @see Iterator
 */
template <class T, class P, class C = P>
class Iterator;

// ============================================================================
// Section and Numbering Classes (v0.5.0)
// ============================================================================

/**
 * @brief Section class for managing document sections
 * @see Section
 * @since 0.5.0
 */
class Section;

/**
 * @brief Section iterator
 * @see SectionIterator
 * @since 0.5.0
 */
class SectionIterator;

/**
 * @brief Section collection for range-based for loops
 * @see SectionCollection
 * @since 0.5.0
 */
class SectionCollection;

/**
 * @brief Numbering manager for list definitions
 * @see NumberingManager
 * @since 0.5.0
 */
class NumberingManager;

}  // namespace cdocx
