/**
 * @file document.h
 * @brief Document class for working with DOCX files
 * @details Provides the main Document class for opening, creating, modifying,
 *          and saving Word documents (.docx). The Document class uses the
 *          PIMPL (Pointer to Implementation) idiom to hide implementation
 *          details and maintain ABI stability.
 * 
 *          Optimized version with lazy loading, parallel processing, and
 *          advanced memory management.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 * 
 * @par Usage Example:
 * @code
 * #include <cdocx/document.h>
 * 
 * // Open existing document
 * cdocx::Document doc("input.docx");
 * doc.open();
 * 
 * if (doc.is_open()) {
 *     // Iterate paragraphs
 *     for (auto& para : doc.paragraphs()) {
 *         std::cout << para.get_text() << std::endl;
 *     }
 *     
 *     // Save changes
 *     doc.save("output.docx");
 * }
 * 
 * // Create new document
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
#include <cstdint>
#include <functional>
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

// Forward declaration for PIMPL idiom
class DocumentImpl;

// Forward declarations for optimized loading
struct LoadConfig;
struct LoadResult;

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
 * @par Memory Management:
 * Document uses the PIMPL idiom for implementation hiding. Move semantics
 * are supported for efficient transfer of document ownership.
 * 
 * @par Thread Safety:
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
     * @brief Open a document with progress callback
     * @param[in] filepath Path to the DOCX file to open
     * @param[in] callback Progress callback function (percent, current_file)
     * @post is_open() returns true if successful
     * @since 0.3.0
     */
    void open(const std::string& filepath, 
              std::function<void(int, const std::string&)> callback);

    /**
     * @brief Open with custom load configuration
     * @param[in] filepath Path to the DOCX file to open
     * @param[in] config Load configuration options
     * @return Detailed load result with statistics
     * @since 0.3.0
     */
    LoadResult open_with_config(const std::string& filepath, const LoadConfig& config);

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
     * @brief Get detailed information about the last open operation
     * @return Load result with statistics and error information
     * @since 0.3.0
     */
    LoadResult get_last_load_result() const;

    // ========================================================================
    // Memory Management (Optimized)
    // ========================================================================

    /**
     * @brief Preload all lazy-loaded files
     * @return true if all files loaded successfully
     * @details Forces loading of all files that were marked for lazy loading
     * @since 0.3.0
     */
    bool preload_all_files();

    /**
     * @brief Unload non-critical files to free memory
     * @return Number of files unloaded
     * @details Serializes XML documents and unloads media files that are not
     *          critical document parts. They will be reloaded on demand.
     * @since 0.3.0
     */
    size_t unload_to_free_memory();

    /**
     * @brief Configure lazy loading behavior
     * @param[in] enable Enable/disable lazy loading
     * @param[in] lazy_media Enable lazy loading for media files
     * @since 0.3.0
     */
    void configure_lazy_loading(bool enable, bool lazy_media = true);

    /**
     * @brief Set size thresholds for different storage strategies
     * @param[in] memory_threshold Files smaller than this stay in memory (bytes)
     * @param[in] mmap_threshold Files larger than this use memory mapping (bytes)
     * @since 0.3.0
     */
    void set_storage_thresholds(size_t memory_threshold, size_t mmap_threshold);

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

// ============================================================================
// Load Configuration
// ============================================================================

/**
 * @struct LoadConfig
 * @brief Configuration for document loading behavior
 * @details Allows fine-tuning of loading performance and memory usage.
 * @since 0.3.0
 */
struct LoadConfig {
    // Lazy loading settings
    bool enable_lazy_loading = true;           ///< Enable lazy loading
    bool lazy_load_media = true;               ///< Lazy load media files
    bool lazy_load_xml = false;                ///< Lazy load non-critical XML
    
    // Size thresholds (bytes)
    size_t memory_threshold = 10 * 1024 * 1024;     ///< 10MB, small files in memory
    size_t mmap_threshold = 50 * 1024 * 1024;       ///< 50MB, large files memory mapped
    size_t temp_file_threshold = 100 * 1024 * 1024; ///< 100MB, huge files temp storage
    
    // Parallel loading settings
    bool enable_parallel_loading = true;       ///< Enable parallel loading
    size_t parallel_threshold = 50;            ///< Enable parallel above this file count
    size_t max_threads = 0;                    ///< 0 = use hardware concurrency
    
    // Cache settings
    bool enable_lru_cache = true;              ///< Enable LRU cache
    size_t max_cached_xml_nodes = 20;          ///< Max cached XML nodes
    size_t max_cached_media_mb = 100;          ///< Max cached media size (MB)
    
    // Error handling
    bool allow_partial_load = true;            ///< Allow partial load
    bool skip_corrupted_files = true;          ///< Skip corrupted files
    size_t max_errors = 100;                   ///< Max error count
    
    // XML parsing optimization
    bool enable_xml_prealloc = true;           ///< XML memory preallocation
    size_t xml_prealloc_factor = 2;            ///< Preallocation factor
    
    // Progress callback
    std::function<void(int percent, const std::string& current_file)> progress_callback;
    
    /**
     * @brief Create default configuration optimized for speed
     */
    static LoadConfig optimized_for_speed() {
        LoadConfig cfg;
        cfg.enable_parallel_loading = true;
        cfg.enable_lazy_loading = false;
        cfg.max_threads = 0;
        return cfg;
    }
    
    /**
     * @brief Create default configuration optimized for memory
     */
    static LoadConfig optimized_for_memory() {
        LoadConfig cfg;
        cfg.enable_lazy_loading = true;
        cfg.lazy_load_media = true;
        cfg.lazy_load_xml = true;
        cfg.memory_threshold = 5 * 1024 * 1024;   // 5MB
        cfg.max_cached_xml_nodes = 10;
        cfg.max_cached_media_mb = 50;
        return cfg;
    }
};

// ============================================================================
// Error Handling Types
// ============================================================================

/**
 * @enum LoadErrorType
 * @brief Types of load errors
 * @since 0.3.0
 */
enum class LoadErrorType {
    None,               ///< No error
    ZipOpenFailed,      ///< Failed to open ZIP file
    ZipEntryReadFailed, ///< Failed to read ZIP entry
    XmlParseFailed,     ///< XML parsing failed
    InvalidStructure,   ///< Invalid document structure
    CorruptedFile,      ///< Corrupted file content
    MemoryAllocation,   ///< Memory allocation failed
    IoError,            ///< I/O error
    Timeout,            ///< Operation timeout
    Unknown             ///< Unknown error
};

/**
 * @enum DocumentIntegrity
 * @brief Document integrity assessment
 * @since 0.3.0
 */
enum class DocumentIntegrity {
    Complete,       ///< All parts loaded successfully
    Partial,        ///< Some non-critical parts failed
    Critical,       ///< Critical parts missing but usable
    Corrupted       ///< Document severely corrupted
};

/**
 * @struct LoadError
 * @brief Detailed load error information
 * @since 0.3.0
 */
struct LoadError {
    LoadErrorType type = LoadErrorType::None;  ///< Error type
    std::string file_path;                      ///< File that caused error
    std::string message;                        ///< Error message
    size_t line = 0;                           ///< Line number (for XML)
    
    LoadError() = default;
    LoadError(LoadErrorType t, const std::string& path, const std::string& msg)
        : type(t), file_path(path), message(msg) {}
        
    /**
     * @brief Get human-readable error type name
     */
    std::string get_type_name() const {
        switch (type) {
            case LoadErrorType::ZipOpenFailed: return "ZipOpenFailed";
            case LoadErrorType::ZipEntryReadFailed: return "ZipEntryReadFailed";
            case LoadErrorType::XmlParseFailed: return "XmlParseFailed";
            case LoadErrorType::InvalidStructure: return "InvalidStructure";
            case LoadErrorType::CorruptedFile: return "CorruptedFile";
            case LoadErrorType::MemoryAllocation: return "MemoryAllocation";
            case LoadErrorType::IoError: return "IoError";
            case LoadErrorType::Timeout: return "Timeout";
            case LoadErrorType::Unknown: return "Unknown";
            default: return "None";
        }
    }
};

/**
 * @struct LoadResult
 * @brief Comprehensive load result with statistics
 * @since 0.3.0
 */
struct LoadResult {
    bool success = false;                       ///< Overall success
    DocumentIntegrity integrity = DocumentIntegrity::Corrupted;  ///< Integrity level
    std::vector<LoadError> errors;              ///< All errors encountered
    std::vector<std::string> skipped_files;     ///< Files that were skipped
    std::vector<std::string> lazy_loaded_files; ///< Files marked for lazy loading
    
    size_t total_files = 0;                     ///< Total files in document
    size_t loaded_files = 0;                    ///< Successfully loaded files
    size_t total_bytes = 0;                     ///< Total bytes
    size_t loaded_bytes = 0;                    ///< Loaded bytes
    double load_time_ms = 0.0;                  ///< Load time in milliseconds
    
    /**
     * @brief Check if document is usable despite any errors
     */
    bool is_usable() const {
        return success && (integrity == DocumentIntegrity::Complete || 
                          integrity == DocumentIntegrity::Partial);
    }
    
    /**
     * @brief Check if document is fully intact
     */
    bool is_complete() const {
        return success && integrity == DocumentIntegrity::Complete;
    }
    
    /**
     * @brief Get summary string for logging
     */
    std::string get_summary() const {
        std::string integrity_str;
        switch (integrity) {
            case DocumentIntegrity::Complete: integrity_str = "Complete"; break;
            case DocumentIntegrity::Partial: integrity_str = "Partial"; break;
            case DocumentIntegrity::Critical: integrity_str = "Critical"; break;
            default: integrity_str = "Corrupted"; break;
        }
        
        return "Load " + std::string(success ? "succeeded" : "failed") +
               " (" + integrity_str + "): " +
               std::to_string(loaded_files) + "/" + std::to_string(total_files) + " files, " +
               std::to_string(static_cast<size_t>(load_time_ms)) + "ms, " +
               std::to_string(errors.size()) + " errors";
    }
};

} // namespace cdocx
