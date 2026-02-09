/**
 * @file cdocx.h
 * @brief Main header file for CDocx library
 * @details CDocx is a C++17 library for creating, reading, and writing
 *          Microsoft Office Word (.docx) files. This header includes
 *          all public API components.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 * 
 * @section Features
 * - Create and modify DOCX files
 * - Read and write paragraphs with formatted text
 * - Work with tables
 * - Manage images and media files
 * - Template-based placeholder replacement
 * - Document insertion and merging
 * - Advanced features: bookmarks, DocumentBuilder, search/replace
 * 
 * @section Example
 * @code
 * #include <cdocx.h>
 * #include <iostream>
 * 
 * int main() {
 *     // Create a new document
 *     cdocx::Document doc;
 *     doc.create_empty("output.docx");
 *     
 *     // Add content
 *     auto para = doc.paragraphs();
 *     para.add_run("Hello, ", cdocx::bold);
 *     para.add_run("World!", cdocx::italic);
 *     
 *     // Save
 *     doc.save();
 *     return 0;
 * }
 * @endcode
 * 
 * @section Links
 * - Repository: https://github.com/lonlng/CDocx
 * - Issues: https://github.com/lonlng/CDocx/issues
 */

#pragma once

// ============================================================================
// CDocx Library - Main Include
// ============================================================================

/**
 * @defgroup Core Core Components
 * Basic document structure and content classes
 */

/**
 * @defgroup Iterators Iterator Support
 * Classes for traversing document elements
 */

/**
 * @defgroup Advanced Advanced Features
 * Extended functionality including bookmarks, builders, and search
 */

/**
 * @defgroup Utilities Utility Classes
 * Helper classes and functions
 */

// Include all public headers
#include <cdocx/fwd.h>        ///< @ingroup Core Forward declarations
#include <cdocx/constants.h>  ///< @ingroup Core Formatting flags
#include <cdocx/iterator.h>   ///< @ingroup Iterators Iterator classes
#include <cdocx/base.h>       ///< @ingroup Core Base content classes
#include <cdocx/document.h>   ///< @ingroup Core Document class
#include <cdocx/template.h>   ///< @ingroup Utilities Template replacement
#include <cdocx/inserter.h>   ///< @ingroup Utilities Document insertion
#include <cdocx/advanced.h>   ///< @ingroup Advanced Advanced features

// ============================================================================
// Version Information
// ============================================================================

/**
 * @brief CDocx major version
 */
#define CDOCX_VERSION_MAJOR 0

/**
 * @brief CDocx minor version
 */
#define CDOCX_VERSION_MINOR 2

/**
 * @brief CDocx patch version
 */
#define CDOCX_VERSION_PATCH 0

/**
 * @brief CDocx version string
 */
#define CDOCX_VERSION "0.2.0"

// ============================================================================
// Namespace Documentation
// ============================================================================

/**
 * @namespace cdocx
 * @brief Main namespace for all CDocx library components
 * @details All public classes, functions, and constants are defined
 *          within the cdocx namespace.
 */
