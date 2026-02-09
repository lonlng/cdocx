/**
 * @file document.h
 * @brief Document class for working with DOCX files
 * @details Provides the main Document class for opening, creating, modifying,
 *          and saving Word documents (.docx). The Document class uses the
 *          PIMPL (Pointer to Implementation) idiom to hide implementation
 *          details and maintain ABI stability.
 * 
 * @author Amir Mohamadi (@amiremohamadi)
 * @copyright MIT License
 * @date 2024
 * @version 0.2.0
 * 
 * @par 使用示例：
 * @code
 * #include <cdocx/document.h>
 * 
 * // 打开现有文档
 * cdocx::Document doc("input.docx");
 * doc.open();
 * 
 * if (doc.is_open()) {
 *     // 遍历段落
 *     for (auto& para : doc.paragraphs()) {
 *         std::cout << para.get_text() << std::endl;
 *     }
 *     
 *     // 保存修改
 *     doc.save("output.docx");
 * }
 * 
 * // 创建新文档
 * cdocx::Document new_doc;
 * new_doc.create_empty("new.docx");
 * auto para = new_doc.paragraphs();
 * para.add_run("Hello, World!", cdocx::bold);
 * new_doc.save();
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/base.h>
#include <cdocx/iterator.h>
#include <pugixml.hpp>
#include <memory>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations for friend classes
class Template;
class Bookmark;
class BookmarkCollection;
class Range;
class DocumentBuilder;
class DocumentSearch;
class IteratorHelper;

/**
 * @class Document
 * @brief Main class for working with DOCX documents
 * @details The Document class represents an entire Word document and provides
 *          methods for:
 *          - Opening existing DOCX files
 *          - Creating new empty documents
 *          - Accessing and modifying document content
 *          - Managing media files (images)
 *          - Working with XML parts
 *          - Saving documents
 * 
 * @par 内存管理：
 * Document uses the PIMPL idiom for implementation hiding. Move semantics
 * are supported for efficient transfer of document ownership.
 * 
 * @par 线程安全：
 * Document objects are NOT thread-safe. Concurrent access from multiple
 * threads requires external synchronization.
 * 
 * @see Paragraph, Table, Template, DocumentInserter
 * @since 0.1.0
 */
class Document {
private:
    // Grant access to private implementation
    friend class Template;
    friend class Bookmark;
    friend class BookmarkCollection;
    friend class Range;
    friend class DocumentBuilder;
    friend class DocumentSearch;
    friend class IteratorHelper;

    /**
     * @brief Private implementation class (PIMPL idiom)
     * @details Contains all implementation details, hidden from public API
     */
    class DocumentImpl;
    
    std::unique_ptr<DocumentImpl> impl_;  ///< Pointer to implementation

public:
    /**
     * @brief Default constructor
     * @details Creates an empty document object. Use open() or create_empty()
     *          to initialize with actual document content.
     */
    Document();

    /**
     * @brief Construct with file path
     * @param[in] filepath Path to the DOCX file to open
     * @note The file is not actually opened until open() is called
     */
    explicit Document(const std::string& filepath);

    /**
     * @brief Destructor
     * @details Automatically closes any open file handles
     */
    ~Document();

    /**
     * @brief Move constructor
     * @param[in,out] other Document to move from (will be empty after)
     */
    Document(Document&& other) noexcept;

    /**
     * @brief Move assignment operator
     * @param[in,out] other Document to move from (will be empty after)
     * @return Reference to this document
     */
    Document& operator=(Document&& other) noexcept;

    // Disable copy operations (heavy resource)
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;

    // ========================================================================
    // File Operations
    // ========================================================================

    /**
     * @brief Set the file path without opening
     * @param[in] filepath Path to the DOCX file
     */
    void file(const std::string& filepath);

    /**
     * @brief Open the document with previously set path
     * @details Opens the document file specified in the constructor or
     *          the last call to file().
     * @post is_open() returns true if successful
     * @see file(), is_open()
     */
    void open();

    /**
     * @brief Open a document file
     * @param[in] filepath Path to the DOCX file to open
     * @post is_open() returns true if successful
     */
    void open(const std::string& filepath);

    /**
     * @brief Close the document
     * @details Closes all file handles and releases resources.
     *          Any unsaved changes are lost.
     * @post is_open() returns false
     */
    void close();

    /**
     * @brief Save the document to the current file path
     * @details Saves all changes to the file specified in constructor
     *          or the last call to open() or file().
     * @pre is_open() must return true
     */
    void save();

    /**
     * @brief Save the document to a new file
     * @param[in] filepath Path where to save the document
     * @pre is_open() must return true
     */
    void save(const std::string& filepath);

    /**
     * @brief Check if document is open
     * @return true if document is open and ready for operations
     * @return false if document is closed or failed to open
     */
    bool is_open() const;

    /**
     * @brief Create a new empty document
     * @param[in] filepath Optional path for the new document (can be empty)
     * @return true if document was created successfully
     * @post is_open() returns true if successful
     */
    bool create_empty(const std::string& filepath = "");

    /**
     * @brief Get the current file path
     * @return The file path, or empty string if not set
     */
    std::string get_filepath() const;

    /**
     * @brief Clear the document and close
     * @details Closes the document and clears all resources
     * @post is_open() returns false, get_filepath() returns empty
     */
    void clear();

    // ========================================================================
    // Content Access
    // ========================================================================

    /**
     * @brief Get the paragraphs iterator
     * @return Reference to paragraph iterator positioned at first paragraph
     * @note Returns empty iterator if document is not open
     */
    Paragraph& paragraphs();

    /**
     * @brief Get the tables iterator
     * @return Reference to table iterator positioned at first table
     * @note Returns empty iterator if document is not open
     */
    Table& tables();

    // ========================================================================
    // XML Parts API
    // ========================================================================

    /**
     * @brief Get an XML part by path
     * @param[in] part_path Path to the XML part (e.g., "word/styles.xml")
     * @return Pointer to the XML document, or nullptr if not found
     */
    pugi::xml_document* get_xml_part(const std::string& part_path);

    /**
     * @brief Get an XML part by path (const version)
     * @param[in] part_path Path to the XML part
     * @return Const pointer to the XML document, or nullptr if not found
     */
    const pugi::xml_document* get_xml_part(const std::string& part_path) const;

    /**
     * @brief Check if an XML part exists
     * @param[in] part_path Path to the XML part
     * @return true if the part exists
     */
    bool has_xml_part(const std::string& part_path) const;

    /**
     * @brief Get all loaded XML part names
     * @return Vector of part paths
     */
    std::vector<std::string> get_all_part_names() const;

    /**
     * @brief Get count of loaded parts
     * @return Number of XML parts in the document
     */
    size_t get_part_count() const;

    /**
     * @brief Create or get an XML part
     * @param[in] part_path Path to the XML part
     * @return Reference to the XML document (created if didn't exist)
     */
    pugi::xml_document& create_xml_part(const std::string& part_path);

    /**
     * @brief Remove an XML part
     * @param[in] part_path Path to the XML part to remove
     */
    void remove_xml_part(const std::string& part_path);

    /**
     * @brief Mark an XML part as modified
     * @param[in] part_path Path to the modified part
     * @details Ensures the part will be saved even if not explicitly modified
     */
    void mark_modified(const std::string& part_path);

    // ========================================================================
    // Convenience Part Accessors
    // ========================================================================

    /** @brief Get the main document XML (word/document.xml) */
    pugi::xml_document* get_document_xml();
    
    /** @brief Get core properties (docProps/core.xml) */
    pugi::xml_document* get_core_properties();
    
    /** @brief Get extended properties (docProps/app.xml) */
    pugi::xml_document* get_app_properties();
    
    /** @brief Get content types ([Content_Types].xml) */
    pugi::xml_document* get_content_types();
    
    /** @brief Get styles (word/styles.xml) */
    pugi::xml_document* get_styles();
    
    /** @brief Get settings (word/settings.xml) */
    pugi::xml_document* get_settings();
    
    /** @brief Get font table (word/fontTable.xml) */
    pugi::xml_document* get_font_table();
    
    /** @brief Get numbering definitions (word/numbering.xml) */
    pugi::xml_document* get_numbering();
    
    /** @brief Get footnotes (word/footnotes.xml) */
    pugi::xml_document* get_footnotes();
    
    /** @brief Get endnotes (word/endnotes.xml) */
    pugi::xml_document* get_endnotes();
    
    /** @brief Get document relationships (word/_rels/document.xml.rels) */
    pugi::xml_document* get_document_rels();
    
    /** @brief Get package relationships (_rels/.rels) */
    pugi::xml_document* get_package_rels();

    /**
     * @brief Get header by index
     * @param[in] index Header number (1-based)
     * @return Pointer to header XML, or nullptr if not found
     */
    pugi::xml_document* get_header(int index);

    /**
     * @brief Get footer by index
     * @param[in] index Footer number (1-based)
     * @return Pointer to footer XML, or nullptr if not found
     */
    pugi::xml_document* get_footer(int index);

    /** @brief Get all header file names */
    std::vector<std::string> get_header_names() const;
    
    /** @brief Get all footer file names */
    std::vector<std::string> get_footer_names() const;

    // ========================================================================
    // Media Management
    // ========================================================================

    /**
     * @brief Add a media file from disk
     * @param[in] image_path Path to the image file
     * @param[in] image_name Optional name for the image in document
     * @return true if added successfully
     */
    bool add_media(const std::string& image_path, const std::string* image_name = nullptr);

    /**
     * @brief Add a media file from memory
     * @param[in] name Name for the image in document
     * @param[in] data Binary image data
     * @param[in] content_type MIME type (e.g., "image/png")
     * @return true if added successfully
     */
    bool add_media_from_memory(const std::string& name, const std::vector<uint8_t>& data,
                               const std::string& content_type = "");

    /**
     * @brief Delete a media file
     * @param[in] image_name Name of the image to delete
     * @return true if deleted successfully
     */
    bool delete_media(const std::string& image_name);

    /**
     * @brief Replace a media file
     * @param[in] image_name Name of the image to replace
     * @param[in] new_image_path Path to the new image file
     * @return true if replaced successfully
     */
    bool replace_media(const std::string& image_name, const std::string& new_image_path);

    /**
     * @brief Check if a media file exists
     * @param[in] image_name Name of the image
     * @return true if the image exists
     */
    bool has_media(const std::string& image_name) const;

    /**
     * @brief List all media files
     * @return Vector of image names
     */
    std::vector<std::string> list_media() const;

    /**
     * @brief Export a media file to disk
     * @param[in] image_name Name of the image in document
     * @param[in] output_path Path where to save the image
     * @return true if exported successfully
     */
    bool export_media(const std::string& image_name, const std::string& output_path) const;

    /**
     * @brief Get media file data
     * @param[in] image_name Name of the image
     * @return Binary image data (empty if not found)
     */
    std::vector<uint8_t> get_media_data(const std::string& image_name) const;

    /**
     * @brief Add media with automatic relationship creation
     * @param[in] image_path Path to the image file
     * @param[in] image_name Optional name for the image
     * @return Relationship ID, or empty string on failure
     */
    std::string add_media_with_rel(const std::string& image_path, const std::string* image_name = nullptr);

    /**
     * @brief Validate image format
     * @param[in] image_path Path to the image file
     * @return true if format is supported (png, jpg, gif, etc.)
     */
    bool validate_image_format(const std::string& image_path) const;

    /**
     * @brief Validate image file size
     * @param[in] image_path Path to the image file
     * @param[in] max_size Maximum allowed size in bytes
     * @return true if file exists and size <= max_size
     */
    bool validate_image_size(const std::string& image_path, size_t max_size) const;

    /**
     * @brief Generate a unique image name
     * @param[in] base_name Base name for the image
     * @return Unique name (e.g., "image_1.png" if "image.png" exists)
     */
    std::string generate_unique_image_name(const std::string& base_name) const;

    // ========================================================================
    // Legacy Compatibility Methods
    // ========================================================================
    
    /** @brief Preload image cache (deprecated, no-op) */
    void preload_image_cache();
    
    /** @brief Clear image cache (deprecated, no-op) */
    void clear_image_cache();
    
    /** @brief Get image cache size (deprecated, returns media count) */
    size_t get_image_cache_size() const;

    /**
     * @brief Add media with relationship (optimized version)
     * @deprecated Use add_media_with_rel() instead
     */
    std::string add_media_optimized(const std::string& image_path,
                                    const std::string& image_name = "",
                                    bool overwrite = false);
    
    /** @brief Delete media (optimized version) */
    bool delete_media_optimized(const std::string& image_name);
    
    /** @brief Replace media (optimized version) */
    bool replace_media_optimized(const std::string& image_name, const std::string& new_image_path);
    
    /** @brief Export media (optimized version) */
    bool export_media_optimized(const std::string& image_name, const std::string& output_path) const;
    
    /** @brief Check media exists (optimized version) */
    bool has_media_optimized(const std::string& image_name) const;
};

} // namespace cdocx
