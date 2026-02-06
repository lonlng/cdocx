/**
 * @file cdocx.h
 * @brief CDocx Public API Header
 * 
 * @mainpage CDocx - C++ DOCX Library
 * 
 * CDocx is a C++17 library for creating, reading, and writing Microsoft Office
 * Word (.docx) files. It provides a simple, iterator-based API for document
 * manipulation with support for:
 * - Text formatting (bold, italic, underline, etc.)
 * - Paragraph and table manipulation
 * - Template-based document generation
 * - Document insertion and merging
 * - XML Parts API for advanced operations
 * - Media file management (images)
 * 
 * @version 0.2.0
 * @author CDocx Contributors
 * @license MIT
 * 
 * @section example Example Usage
 * @code
 * #include <cdocx.h>
 * #include <iostream>
 * 
 * int main() {
 *     // Open a document
 *     cdocx::Document doc("input.docx");
 *     doc.open();
 *     
 *     // Read paragraphs
 *     for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
 *         for (auto r = p.runs(); r.has_next(); r.next()) {
 *             std::cout << r.get_text() << std::endl;
 *         }
 *     }
 *     
 *     return 0;
 * }
 * @endcode
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <set>

#include <pugixml.hpp>

/**
 * @namespace cdocx
 * @brief Main namespace for the CDocx library
 */
namespace cdocx {

// Forward declarations
struct zip_t;

/**
 * @defgroup formatting Formatting Flags
 * @brief Text formatting options for document content
 * 
 * These flags can be combined using bitwise OR operations.
 * @{
 */

/**
 * @brief Text formatting flags enumeration
 * 
 * Supports combination of multiple styles using bitwise operations:
 * @code
 * cdocx::bold | cdocx::italic  // Bold and italic text
 * @endcode
 */
enum formatting_flag {
    none = 0,           /**< No formatting */
    bold = 1 << 0,      /**< Bold text */
    italic = 1 << 1,    /**< Italic text */
    underline = 1 << 2, /**< Underlined text */
    strikethrough = 1 << 3, /**< Strikethrough text */
    superscript = 1 << 4,   /**< Superscript text */
    subscript = 1 << 5,     /**< Subscript text */
    smallcaps = 1 << 6,     /**< Small capitals */
    shadow = 1 << 7         /**< Shadow effect */
};

/** @} */ // end of formatting group

// Forward declarations for public classes
class Document;
class Paragraph;
class Table;
class Run;
class TableRow;
class TableCell;
class Template;
class DocumentInserter;

// Internal implementation (PIMPL)
class DocumentImpl;

/**
 * @defgroup content Content Classes
 * @brief Classes for manipulating document content
 * 
 * These classes provide access to the document's structural elements
 * such as paragraphs, runs, tables, and cells.
 * @{
 */

/**
 * @class Run
 * @brief Represents a text run within a paragraph
 * 
 * A run is a contiguous region of text with the same formatting.
 * Paragraphs can contain multiple runs with different formatting.
 * 
 * @code
 * // Get text from a run
 * std::string text = run.get_text();
 * 
 * // Set text in a run
 * run.set_text("New text content");
 * @endcode
 */
class Run {
  private:
    friend class Paragraph;
    friend class Template;
    friend class IteratorHelper;
    pugi::xml_node parent;   /**< Parent XML node */
    pugi::xml_node current;  /**< Current XML node */

  public:
    /** @brief Default constructor */
    Run();
    
    /**
     * @brief Construct a run with parent and current nodes
     * @param parent The parent XML node
     * @param current The current XML node
     */
    Run(pugi::xml_node parent, pugi::xml_node current);
    
    /** @brief Set the parent node
     *  @param node The new parent node */
    void set_parent(pugi::xml_node node);
    
    /** @brief Set the current node
     *  @param node The new current node */
    void set_current(pugi::xml_node node);
    
    /** @return The current XML node */
    pugi::xml_node get_current() const { return current; }
    
    /** @return The parent XML node */
    pugi::xml_node get_parent() const { return parent; }
    
    /**
     * @brief Get the text content of this run
     * @return The text content as a string
     */
    std::string get_text() const;
    
    /**
     * @brief Set the text content of this run
     * @param text The new text content
     * @return true if successful, false otherwise
     */
    bool set_text(const std::string& text) const;
    
    /**
     * @brief Set the text content (C-string version)
     * @param text The new text content
     * @return true if successful, false otherwise
     */
    bool set_text(const char* text) const;
    
    /**
     * @brief Move to the next run
     * @return Reference to this run (now pointing to next)
     */
    Run& next();
    
    /**
     * @brief Check if there is a next run
     * @return true if there is a next run, false otherwise
     */
    bool has_next() const;
    
    /**
     * @defgroup run_formatting Run Formatting
     * @brief Methods for setting text formatting properties
     * @{
     */
    
    /**
     * @brief Set the font color of this run
     * @param color_hex Color in hex format (e.g., "FF0000" for red, "0070C0" for blue)
     * @return true if successful, false otherwise
     */
    bool set_color(const std::string& color_hex);
    
    /**
     * @brief Set the font size of this run
     * @param size Size in half-points (e.g., 24 for 12pt, 48 for 24pt)
     * @return true if successful, false otherwise
     */
    bool set_font_size(int size);
    
    /**
     * @brief Set the font name for this run
     * @param font_name Font family name (e.g., "Arial", "Times New Roman", "宋体")
     * @return true if successful, false otherwise
     */
    bool set_font_name(const std::string& font_name);
    
    /**
     * @brief Set bold formatting for this run
     * @param bold true to enable bold, false to disable
     * @return true if successful, false otherwise
     */
    bool set_bold(bool bold = true);
    
    /**
     * @brief Set italic formatting for this run
     * @param italic true to enable italic, false to disable
     * @return true if successful, false otherwise
     */
    bool set_italic(bool italic = true);
    
    /**
     * @brief Set underline formatting for this run
     * @param underline true to enable underline, false to disable
     * @return true if successful, false otherwise
     */
    bool set_underline(bool underline = true);
    
    /** @} */ // end of run_formatting group
};

/**
 * @class Paragraph
 * @brief Represents a paragraph in the document
 * 
 * Paragraphs are the primary containers for text content in a DOCX document.
 * Each paragraph contains one or more runs with text and formatting.
 * 
 * @code
 * // Insert a new paragraph with formatted text
 * cdocx::Paragraph p = doc.paragraphs().insert_paragraph_after("Hello ");
 * p.add_run("World", cdocx::bold);
 * @endcode
 */
class Paragraph {
  private:
    friend class Document;
    friend class TableCell;
    friend class Template;
    friend class IteratorHelper;
    pugi::xml_node parent;   /**< Parent XML node */
    pugi::xml_node current;  /**< Current XML node */
    Run run;                 /**< Current run iterator */

  public:
    /** @brief Default constructor */
    Paragraph();
    
    /**
     * @brief Construct a paragraph with parent and current nodes
     * @param parent The parent XML node
     * @param current The current XML node
     */
    Paragraph(pugi::xml_node parent, pugi::xml_node current);
    
    /** @brief Set the parent node
     *  @param node The new parent node */
    void set_parent(pugi::xml_node node);
    
    /** @brief Set the current node
     *  @param node The new current node */
    void set_current(pugi::xml_node node);
    
    /** @return The current XML node */
    pugi::xml_node get_current() const { return current; }
    
    /**
     * @brief Move to the next paragraph
     * @return Reference to this paragraph (now pointing to next)
     */
    Paragraph& next();
    
    /**
     * @brief Check if there is a next paragraph
     * @return true if there is a next paragraph, false otherwise
     */
    bool has_next() const;
    
    /**
     * @brief Get the runs in this paragraph
     * @return Reference to the run iterator
     */
    Run& runs();
    
    /**
     * @brief Add a new run to this paragraph
     * @param text The text content for the run
     * @param f Formatting flags (default: none)
     * @return Reference to the new run
     */
    Run& add_run(const std::string& text, cdocx::formatting_flag f = cdocx::none);
    
    /**
     * @brief Add a new run (C-string version)
     * @param text The text content for the run
     * @param f Formatting flags (default: none)
     * @return Reference to the new run
     */
    Run& add_run(const char* text, cdocx::formatting_flag f = cdocx::none);
    
    /**
     * @brief Remove a run from this paragraph
     * @param r The run to remove
     */
    void remove_run(const Run& r);
    
    /**
     * @brief Insert a new paragraph after this one
     * @param text The text content for the new paragraph
     * @param f Formatting flags for the text (default: none)
     * @return Reference to the new paragraph
     */
    Paragraph& insert_paragraph_after(const std::string& text,
                                      cdocx::formatting_flag f = cdocx::none);
    
    /**
     * @defgroup paragraph_formatting Paragraph Formatting
     * @brief Methods for setting paragraph formatting properties
     * @{
     */
    
    /**
     * @brief Set paragraph alignment
     * @param alignment Alignment type: "left", "center", "right", "both" (justified)
     * @return true if successful, false otherwise
     */
    bool set_alignment(const std::string& alignment);
    
    /**
     * @brief Set paragraph style
     * @param style_id Style ID (e.g., "1" for Heading 1, "2" for Heading 2, "Normal")
     * @return true if successful, false otherwise
     */
    bool set_style(const std::string& style_id);
    
    /**
     * @brief Set line spacing for this paragraph
     * @param line_spacing Line spacing value (in 240ths of a line, e.g., 240 = single, 360 = 1.5, 480 = double)
     * @param is_exact If true, line_spacing is in twips (1/20 of a point); if false, in 240ths
     * @return true if successful, false otherwise
     */
    bool set_line_spacing(int line_spacing, bool is_exact = false);
    
    /**
     * @brief Set spacing before this paragraph
     * @param spacing Spacing in twips (1/20 of a point)
     * @return true if successful, false otherwise
     */
    bool set_spacing_before(int spacing);
    
    /**
     * @brief Set spacing after this paragraph
     * @param spacing Spacing in twips (1/20 of a point)
     * @return true if successful, false otherwise
     */
    bool set_spacing_after(int spacing);
    
    /**
     * @brief Set paragraph indentation
     * @param left Left indent in twips (1/20 of a point), -1 to leave unchanged
     * @param right Right indent in twips, -1 to leave unchanged
     * @param first_line First line indent (hanging if negative), -1 to leave unchanged
     * @return true if successful, false otherwise
     */
    bool set_indent(int left = -1, int right = -1, int first_line = -1);
    
    /** @} */ // end of paragraph_formatting group
};

/**
 * @class TableCell
 * @brief Represents a cell within a table row
 * 
 * Table cells contain paragraphs and can have their own formatting.
 */
class TableCell {
  private:
    friend class TableRow;
    friend class IteratorHelper;
    pugi::xml_node parent;   /**< Parent XML node */
    pugi::xml_node current;  /**< Current XML node */
    Paragraph paragraph;     /**< Current paragraph iterator */

  public:
    /** @brief Default constructor */
    TableCell();
    
    /**
     * @brief Construct a cell with parent and current nodes
     * @param parent The parent XML node
     * @param current The current XML node
     */
    TableCell(pugi::xml_node parent, pugi::xml_node current);
    
    /** @brief Set the parent node
     *  @param node The new parent node */
    void set_parent(pugi::xml_node node);
    
    /** @brief Set the current node
     *  @param node The new current node */
    void set_current(pugi::xml_node node);
    
    /** @return The current XML node */
    pugi::xml_node get_current() const { return current; }
    
    /**
     * @brief Get the paragraphs in this cell
     * @return Reference to the paragraph iterator
     */
    Paragraph& paragraphs();
    
    /**
     * @brief Move to the next cell
     * @return Reference to this cell (now pointing to next)
     */
    TableCell& next();
    
    /**
     * @brief Check if there is a next cell
     * @return true if there is a next cell, false otherwise
     */
    bool has_next() const;
};

/**
 * @class TableRow
 * @brief Represents a row within a table
 * 
 * Table rows contain cells that hold the actual content.
 */
class TableRow {
  private:
    friend class Table;
    friend class IteratorHelper;
    pugi::xml_node parent;   /**< Parent XML node */
    pugi::xml_node current;  /**< Current XML node */
    TableCell cell;          /**< Current cell iterator */

  public:
    /** @brief Default constructor */
    TableRow();
    
    /**
     * @brief Construct a row with parent and current nodes
     * @param parent The parent XML node
     * @param current The current XML node
     */
    TableRow(pugi::xml_node parent, pugi::xml_node current);
    
    /** @brief Set the parent node
     *  @param node The new parent node */
    void set_parent(pugi::xml_node node);
    
    /** @brief Set the current node
     *  @param node The new current node */
    void set_current(pugi::xml_node node);
    
    /** @return The current XML node */
    pugi::xml_node get_current() const { return current; }
    
    /**
     * @brief Get the cells in this row
     * @return Reference to the cell iterator
     */
    TableCell& cells();
    
    /**
     * @brief Check if there is a next row
     * @return true if there is a next row, false otherwise
     */
    bool has_next() const;
    
    /**
     * @brief Move to the next row
     * @return Reference to this row (now pointing to next)
     */
    TableRow& next();
};

/**
 * @class Table
 * @brief Represents a table in the document
 * 
 * Tables contain rows, which in turn contain cells with content.
 */
class Table {
  private:
    friend class Document;
    friend class IteratorHelper;
    pugi::xml_node parent;   /**< Parent XML node */
    pugi::xml_node current;  /**< Current XML node */
    TableRow row;            /**< Current row iterator */

  public:
    /** @brief Default constructor */
    Table();
    
    /**
     * @brief Construct a table with parent and current nodes
     * @param parent The parent XML node
     * @param current The current XML node
     */
    Table(pugi::xml_node parent, pugi::xml_node current);
    
    /** @brief Set the parent node
     *  @param node The new parent node */
    void set_parent(pugi::xml_node node);
    
    /** @brief Set the current node
     *  @param node The new current node */
    void set_current(pugi::xml_node node);
    
    /** @return The current XML node */
    pugi::xml_node get_current() const { return current; }
    
    /**
     * @brief Move to the next table
     * @return Reference to this table (now pointing to next)
     */
    Table& next();
    
    /**
     * @brief Check if there is a next table
     * @return true if there is a next table, false otherwise
     */
    bool has_next() const;
    
    /**
     * @brief Get the rows in this table
     * @return Reference to the row iterator
     */
    TableRow& rows();
};

/** @} */ // end of content group

/**
 * @defgroup document Document Class
 * @brief Main document manipulation interface
 * 
 * The Document class is the primary interface for working with DOCX files.
 * It uses the PIMPL (Pointer to Implementation) pattern to hide internal details.
 * @{
 */

/**
 * @class Document
 * @brief Main class for DOCX document manipulation
 * 
 * This class provides the primary interface for opening, modifying, and saving
 * DOCX files. It supports both basic operations (paragraphs, tables) and
 * advanced features (XML parts, media management, templates).
 * 
 * @code
 * // Basic usage example
 * cdocx::Document doc("document.docx");
 * doc.open();
 * 
 * // Iterate paragraphs
 * for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
 *     // Process paragraph
 * }
 * 
 * doc.save("output.docx");
 * @endcode
 */
class Document {
  private:
    std::unique_ptr<DocumentImpl> impl_;  /**< Private implementation (PIMPL) */
    
  public:
    /** @brief Default constructor */
    Document();
    
    /**
     * @brief Construct with file path
     * @param filepath Path to the DOCX file
     */
    explicit Document(const std::string& filepath);
    
    /** @brief Destructor */
    ~Document();
    
    // Disable copy, enable move
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;
    Document(Document&&) noexcept;
    Document& operator=(Document&&) noexcept;
    
    /**
     * @defgroup fileops File Operations
     * @brief Methods for opening, saving, and closing documents
     * @{
     */
    
    /**
     * @brief Set the file path
     * @param filepath Path to the DOCX file
     */
    void file(const std::string& filepath);
    
    /** @brief Open the document using the set file path */
    void open();
    
    /**
     * @brief Create a new empty document
     * 
     * Creates a minimal valid DOCX document with all required XML parts:
     * - Content types definition
     * - Package relationships
     * - Document relationships
     * - Main document content (empty body)
     * - Styles, settings, font table
     * - Theme
     * - Core and extended properties
     * 
     * After calling this method, the document is in an open state and
     * ready for content to be added.
     * 
     * @param filepath Path for the new document (optional, can be set later via file())
     * @return true if successful, false otherwise
     * 
     * @code
     * cdocx::Document doc;
     * if (doc.create_empty("new.docx")) {
     *     doc.paragraphs().insert_paragraph_after("Hello, World!");
     *     doc.save();
     * }
     * @endcode
     */
    bool create_empty(const std::string& filepath = "");
    
    /**
     * @brief Open a document at the specified path
     * @param filepath Path to the DOCX file
     */
    void open(const std::string& filepath);
    
    /** @brief Save the document to the current file path */
    void save();
    
    /**
     * @brief Save the document to a specific path
     * @param filepath Output file path
     */
    void save(const std::string& filepath);
    
    /** @brief Close the document and release resources */
    void close();
    
    /**
     * @brief Check if a document is currently open
     * @return true if open, false otherwise
     */
    bool is_open() const;
    
    /**
     * @brief Get the current file path
     * @return The file path as a string
     */
    std::string get_filepath() const;
    
    /** @} */ // end of fileops
    
    /**
     * @defgroup contentops Content Access
     * @brief Methods for accessing document content
     * @{
     */
    
    /**
     * @brief Get the paragraphs in the document
     * @return Reference to the paragraph iterator
     */
    Paragraph& paragraphs();
    
    /**
     * @brief Get the tables in the document
     * @return Reference to the table iterator
     */
    Table& tables();
    
    /** @} */ // end of contentops
    
    /**
     * @defgroup xmlparts XML Parts API
     * @brief Low-level access to DOCX package XML parts
     * 
     * These methods provide direct access to the XML components
     * that make up a DOCX file.
     * @{
     */
    
    /**
     * @brief Get an XML part by path
     * @param part_path Path to the XML part (e.g., "word/document.xml")
     * @return Pointer to the XML document, or nullptr if not found
     */
    pugi::xml_document* get_xml_part(const std::string& part_path);
    
    /**
     * @brief Get an XML part (const version)
     * @param part_path Path to the XML part
     * @return Const pointer to the XML document
     */
    const pugi::xml_document* get_xml_part(const std::string& part_path) const;
    
    /**
     * @brief Check if an XML part exists
     * @param part_path Path to the XML part
     * @return true if exists, false otherwise
     */
    bool has_xml_part(const std::string& part_path) const;
    
    /**
     * @brief Get all loaded XML part names
     * @return Vector of part paths
     */
    std::vector<std::string> get_all_part_names() const;
    
    /**
     * @brief Get the count of loaded XML parts
     * @return Number of parts
     */
    size_t get_part_count() const;
    
    /**
     * @brief Create a new XML part
     * @param part_path Path for the new part
     * @return Reference to the created XML document
     */
    pugi::xml_document& create_xml_part(const std::string& part_path);
    
    /**
     * @brief Remove an XML part
     * @param part_path Path to the part to remove
     */
    void remove_xml_part(const std::string& part_path);
    
    /**
     * @brief Mark a part as modified
     * @param part_path Path to the modified part
     */
    void mark_modified(const std::string& part_path);
    
    // Convenience accessors for common parts
    pugi::xml_document* get_document_xml();      /**< Get word/document.xml */
    pugi::xml_document* get_core_properties();   /**< Get docProps/core.xml */
    pugi::xml_document* get_app_properties();    /**< Get docProps/app.xml */
    pugi::xml_document* get_content_types();     /**< Get [Content_Types].xml */
    pugi::xml_document* get_styles();            /**< Get word/styles.xml */
    pugi::xml_document* get_settings();          /**< Get word/settings.xml */
    pugi::xml_document* get_font_table();        /**< Get word/fontTable.xml */
    pugi::xml_document* get_numbering();         /**< Get word/numbering.xml */
    pugi::xml_document* get_footnotes();         /**< Get word/footnotes.xml */
    pugi::xml_document* get_endnotes();          /**< Get word/endnotes.xml */
    pugi::xml_document* get_document_rels();     /**< Get word/_rels/document.xml.rels */
    pugi::xml_document* get_package_rels();      /**< Get _rels/.rels */
    pugi::xml_document* get_header(int index);   /**< Get header by index */
    pugi::xml_document* get_footer(int index);   /**< Get footer by index */
    std::vector<std::string> get_header_names() const; /**< Get all header names */
    std::vector<std::string> get_footer_names() const; /**< Get all footer names */
    
    /** @} */ // end of xmlparts
    
    /**
     * @defgroup media Media API
     * @brief Methods for managing media files (images, etc.)
     * @{
     */
    
    /**
     * @brief Add a media file to the document
     * @param image_path Path to the image file
     * @param image_name Optional name for the image in the document
     * @return true if successful, false otherwise
     */
    bool add_media(const std::string& image_path, const std::string* image_name = nullptr);
    
    /**
     * @brief Add media from memory
     * @param name Name for the media
     * @param data Binary data of the media
     * @param content_type MIME type (auto-detected if empty)
     * @return true if successful, false otherwise
     */
    bool add_media_from_memory(const std::string& name, const std::vector<uint8_t>& data,
                               const std::string& content_type = "");
    
    /**
     * @brief Delete a media file
     * @param image_name Name of the image to delete
     * @return true if successful, false otherwise
     */
    bool delete_media(const std::string& image_name);
    
    /**
     * @brief Replace a media file
     * @param image_name Name of the image to replace
     * @param new_image_path Path to the new image file
     * @return true if successful, false otherwise
     */
    bool replace_media(const std::string& image_name, const std::string& new_image_path);
    
    /**
     * @brief Replace media from memory
     * @param image_name Name of the image to replace
     * @param data Binary data of the new image
     * @param content_type MIME type
     * @return true if successful, false otherwise
     */
    bool replace_media_from_memory(const std::string& image_name, 
                                   const std::vector<uint8_t>& data,
                                   const std::string& content_type = "");
    
    /**
     * @brief Check if a media file exists
     * @param image_name Name of the image
     * @return true if exists, false otherwise
     */
    bool has_media(const std::string& image_name) const;
    
    /**
     * @brief List all media files
     * @return Vector of media file names
     */
    std::vector<std::string> list_media() const;
    
    /**
     * @brief Export a media file
     * @param image_name Name of the image
     * @param output_path Output file path
     * @return true if successful, false otherwise
     */
    bool export_media(const std::string& image_name, const std::string& output_path) const;
    
    /**
     * @brief Get media data as bytes
     * @param image_name Name of the image
     * @return Vector of bytes containing the image data
     */
    std::vector<uint8_t> get_media_data(const std::string& image_name) const;
    
    /**
     * @brief Add media with relationship
     * @param image_path Path to the image
     * @param image_name Optional name
     * @return Relationship ID
     */
    std::string add_media_with_rel(const std::string& image_path, 
                                   const std::string* image_name = nullptr);
    
    /**
     * @brief Add media from memory with relationship
     * @param name Name for the media
     * @param data Binary data
     * @param content_type MIME type
     * @return Relationship ID
     */
    std::string add_media_from_memory_with_rel(const std::string& name,
                                               const std::vector<uint8_t>& data,
                                               const std::string& content_type = "");
    
    /**
     * @brief Add multiple media files in batch
     * @param images Vector of (path, name) pairs
     * @return true if all successful, false otherwise
     */
    bool add_media_batch(const std::vector<std::pair<std::string, std::string>>& images);
    
    /**
     * @brief Delete multiple media files in batch
     * @param image_names Vector of image names to delete
     * @return true if all successful, false otherwise
     */
    bool delete_media_batch(const std::vector<std::string>& image_names);
    
    /**
     * @brief Preload image cache (legacy)
     */
    void preload_image_cache();
    
    /**
     * @brief Clear image cache (legacy)
     */
    void clear_image_cache();
    
    /**
     * @brief Get the number of cached images
     * @return Number of cached images
     */
    size_t get_image_cache_size() const;
    
    /**
     * @brief Add media with optimization options (legacy compatibility)
     * @param image_path Path to the image
     * @param image_name Name for the image
     * @param overwrite Whether to overwrite existing image
     * @return Relationship ID string
     */
    std::string add_media_optimized(const std::string& image_path,
                                    const std::string& image_name,
                                    bool overwrite = false);
    
    /**
     * @brief Delete media with optimization (legacy compatibility)
     * @param image_name Name of the image
     * @return true if successful
     */
    bool delete_media_optimized(const std::string& image_name);
    
    /**
     * @brief Replace media with optimization (legacy compatibility)
     * @param image_name Name of the image
     * @param new_image_path Path to new image
     * @return true if successful
     */
    bool replace_media_optimized(const std::string& image_name,
                                  const std::string& new_image_path);
    
    /**
     * @brief Export media with optimization (legacy compatibility)
     * @param image_name Name of the image
     * @param output_path Output file path
     * @return true if successful
     */
    bool export_media_optimized(const std::string& image_name,
                                 const std::string& output_path) const;
    
    /**
     * @brief Check if media exists (legacy compatibility)
     * @param image_name Name of the image
     * @return true if exists
     */
    bool has_media_optimized(const std::string& image_name) const;
    
    /** @} */ // end of media
    
    /**
     * @defgroup utility Utility Methods
     * @brief Helper methods for various tasks
     * @{
     */
    
    /**
     * @brief Validate image file format
     * @param image_path Path to the image
     * @return true if valid, false otherwise
     */
    bool validate_image_format(const std::string& image_path) const;
    
    /**
     * @brief Validate image file size
     * @param image_path Path to the image
     * @param max_size Maximum allowed size in bytes (default: 10MB)
     * @return true if within limit, false otherwise
     */
    bool validate_image_size(const std::string& image_path, size_t max_size = 10*1024*1024) const;
    
    /**
     * @brief Generate a unique image name
     * @param base_name Base name to use
     * @return Unique name
     */
    std::string generate_unique_image_name(const std::string& base_name) const;
    
    /**
     * @brief Get the relationship ID for a media file
     * @param image_name Name of the image
     * @return Relationship ID string
     */
    std::string get_media_relationship_id(const std::string& image_name) const;
    
    /** @brief Clear all document data */
    void clear();
    
    // Legacy accessors
    pugi::xml_document* getDocumentXML() { return get_document_xml(); }
    
    /** @} */ // end of utility
};

/** @} */ // end of document group

/**
 * @defgroup template Template System
 * @brief Template-based document generation
 * 
 * The Template class provides placeholder replacement functionality
 * for generating documents from templates.
 * @{
 */

/**
 * @class Template
 * @brief Template processor for placeholder replacement
 * 
 * This class allows you to create documents from templates by replacing
 * placeholders with actual values.
 * 
 * @code
 * cdocx::Document doc("template.docx");
 * doc.open();
 * 
 * cdocx::Template tmpl(&doc);
 * tmpl.set("name", "John Doe");
 * tmpl.set("date", "2024-01-01");
 * tmpl.replace_all();
 * 
 * doc.save("output.docx");
 * @endcode
 */
class Template {
  private:
    Document* doc_;
    std::map<std::string, std::string> placeholders_;
    std::map<std::string, std::string> image_placeholders_;
    std::string pattern_prefix_ = "{{";
    std::string pattern_suffix_ = "}}";
    
    struct PlaceholderContext;
    
    bool replace_in_string(std::string& text) const;
    void replace_in_paragraphs();
    void replace_in_tables();
    bool try_replace_single_run(Run& r) const;
    void process_paragraph(Paragraph& p);

  public:
    /**
     * @brief Construct with default pattern {{ }}
     * @param document Pointer to the Document
     */
    explicit Template(Document* document);
    
    /**
     * @brief Construct with custom pattern
     * @param document Pointer to the Document
     * @param prefix Pattern prefix (e.g., "{{")
     * @param suffix Pattern suffix (e.g., "}}")
     */
    Template(Document* document, const std::string& prefix, const std::string& suffix);
    
    /**
     * @brief Set a text placeholder
     * @param key Placeholder name
     * @param value Replacement value
     */
    void set(const std::string& key, const std::string& value);
    
    /**
     * @brief Set a text placeholder (C-string version)
     * @param key Placeholder name
     * @param value Replacement value
     */
    void set(const std::string& key, const char* value);
    
    /**
     * @brief Set an image placeholder
     * @param key Placeholder name
     * @param image_path Path to the image
     */
    void set_image(const std::string& key, const std::string& image_path);
    
    /**
     * @brief Set the placeholder pattern
     * @param prefix Pattern prefix
     * @param suffix Pattern suffix
     */
    void set_pattern(const std::string& prefix, const std::string& suffix);
    
    /** @brief Replace all placeholders in the document */
    void replace_all();
    
    /** @brief Clear all placeholders */
    void clear();
    
    /**
     * @brief Get the number of placeholders
     * @return Count of placeholders
     */
    size_t size() const;
};

/** @} */ // end of template group

/**
 * @defgroup insertion Document Insertion
 * @brief Insert content between documents
 * 
 * The DocumentInserter class allows inserting content from one document
 * into another at various positions.
 * @{
 */

/**
 * @class DocumentInserter
 * @brief Insert content from one document into another
 * 
 * @code
 * cdocx::Document target("main.docx");
 * target.open();
 * 
 * cdocx::Document source("content.docx");
 * source.open();
 * 
 * cdocx::DocumentInserter inserter(&target);
 * inserter.insert_document(&source);
 * 
 * target.save("merged.docx");
 * @endcode
 */
class DocumentInserter {
  private:
    Document* target_doc_;
    
    pugi::xml_node clone_paragraph(const pugi::xml_node& source_para, 
                                   pugi::xml_node target_parent);
    pugi::xml_node clone_table(const pugi::xml_node& source_table,
                               pugi::xml_node target_parent);

  public:
    /**
     * @brief Constructor
     * @param target Pointer to the target document
     */
    explicit DocumentInserter(Document* target);
    
    /**
     * @brief Insert entire document at the end
     * @param source Pointer to the source document
     */
    void insert_document(Document* source);
    
    /**
     * @brief Insert after a specific paragraph
     * @param source Pointer to the source document
     * @param after_para Paragraph after which to insert
     */
    void insert_document_after(Document* source, Paragraph& after_para);
    
    /**
     * @brief Insert at a specific position
     * @param source Pointer to the source document
     * @param position Position index (0-based)
     */
    void insert_document_at(Document* source, int position);
    
    /**
     * @brief Insert only paragraphs
     * @param source Pointer to the source document
     * @param position Position index (-1 for end)
     */
    void insert_paragraphs(Document* source, int position = -1);
    
    /**
     * @brief Insert only tables
     * @param source Pointer to the source document
     * @param position Position index (-1 for end)
     */
    void insert_tables(Document* source, int position = -1);
};

/** @} */ // end of insertion group

} // namespace cdocx
