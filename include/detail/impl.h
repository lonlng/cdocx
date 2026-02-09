/**
 * @file impl.h
 * @brief Private implementation details for CDocx
 * @warning This file contains internal implementation details and should NOT
 *          be included directly by users of the library. It is used internally
 *          by cdocx source files.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0 - Optimized Version with Lazy Loading & Parallel Processing
 * @internal
 */

#pragma once

#include <cdocx/document.h>

#include <pugixml.hpp>
#include <zip.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <shared_mutex>
#include <string>
#include <variant>
#include <vector>

// Forward declarations for internal use
struct zip_t;

namespace cdocx {

// ============================================================================
// Forward Declarations
// ============================================================================

class Document;
class Paragraph;
class Table;
class Template;
class DocumentInserter;
struct LoadConfig;
struct LoadResult;
enum class LoadErrorType;
enum class DocumentIntegrity;

// ============================================================================
// Node Types
// ============================================================================

/**
 * @enum DocxNodeType
 * @brief Types of nodes in the DOCX package tree
 * @internal
 */
enum class DocxNodeType {
    Root,           ///< Root node representing the package
    Directory,      ///< Directory/folder node
    XmlFile,        ///< XML file with parsed content
    MediaFile,      ///< Media file (image, etc.)
    BinaryFile      ///< Other binary file
};

/**
 * @enum StorageType
 * @brief How file data is stored
 * @internal
 */
enum class StorageType {
    NotLoaded,      ///< Not loaded yet (lazy loading)
    Memory,         ///< In memory (vector<uint8_t>)
    MemoryMapped,   ///< Memory mapped file
    TempFile,       ///< Stored in temporary file
    Compressed      ///< Compressed in memory
};

// ============================================================================
// File Data Storage
// ============================================================================

/**
 * @class FileDataStorage
 * @brief Manages file data with multiple storage backends
 * @internal
 */
class FileDataStorage {
public:
    using DataVariant = std::variant<
        std::monostate,                      // Not loaded
        std::vector<uint8_t>,                // Memory
        std::shared_ptr<void>,               // Memory mapped (platform specific)
        std::filesystem::path,               // Temp file path
        std::pair<std::vector<uint8_t>, size_t>  // Compressed (data, original_size)
    >;
    
private:
    mutable std::shared_mutex mutex_;
    DataVariant data_;
    StorageType storage_type_ = StorageType::NotLoaded;
    size_t data_size_ = 0;
    size_t original_size_ = 0;
    
    // For lazy loading
    struct LazyLoadInfo {
        zip_t* zip_handle = nullptr;
        int entry_index = -1;
        std::string entry_name;
        size_t entry_size = 0;
    };
    std::optional<LazyLoadInfo> lazy_info_;
    
public:
    FileDataStorage() = default;
    
    // Storage type query
    StorageType get_storage_type() const { return storage_type_; }
    bool is_loaded() const { return storage_type_ != StorageType::NotLoaded; }
    size_t get_size() const { return data_size_; }
    
    // Initialize lazy loading info
    void set_lazy_load_info(zip_t* zip, int index, const std::string& name, size_t size);
    
    // Load data (if in lazy loading mode)
    bool ensure_loaded(const LoadConfig& config);
    
    // Store data
    void store_in_memory(std::vector<uint8_t>&& data);
    void store_memory_mapped(const std::string& path, size_t size);
    void store_temp_file(const std::filesystem::path& path, size_t size);
    void store_compressed(std::vector<uint8_t>&& data, size_t original_size);
    
    // Get data
    std::vector<uint8_t> get_data() const;
    const std::vector<uint8_t>* get_memory_data() const;
    
    // Convert to specified storage type
    bool convert_to(StorageType target_type, const LoadConfig& config);
    
    // Release data
    void unload();
    
    // Compress/Decompress
    static std::vector<uint8_t> compress_data(const std::vector<uint8_t>& data);
    static std::vector<uint8_t> decompress_data(const std::vector<uint8_t>& data, size_t original_size);
};

// ============================================================================
// Tree Node
// ============================================================================

/**
 * @struct DocxTreeNode
 * @brief Node in the DOCX package tree structure
 * @details Represents a file or directory within the DOCX package.
 *          Tree structure mirrors the ZIP file organization.
 * @internal
 */
struct DocxTreeNode : public std::enable_shared_from_this<DocxTreeNode> {
    std::string name;                           ///< File/directory name
    std::string full_path;                      ///< Full path in ZIP
    DocxNodeType type;                          ///< Node type
    
    // Parent and children
    DocxTreeNode* parent;                       ///< Parent node
    std::vector<std::shared_ptr<DocxTreeNode>> children;  ///< Child nodes
    
    // Data storage (type-specific)
    std::shared_ptr<pugi::xml_document> xml_doc;  ///< For XmlFile type
    FileDataStorage file_storage;                 ///< Unified file data storage
    std::string content_type;                     ///< MIME type
    
    // State tracking
    bool is_modified = false;   ///< Modified since load
    bool is_new = false;        ///< Newly created
    bool is_deleted = false;    ///< Marked for deletion
    bool is_critical = false;   ///< Critical document part
    
    /**
     * @brief Construct tree node
     * @param n Node name
     * @param t Node type
     * @param p Parent node
     */
    DocxTreeNode(const std::string& n, DocxNodeType t, DocxTreeNode* p = nullptr)
        : name(n), type(t), parent(p) {}
    
    /**
     * @brief Check if node is a directory
     * @return true if directory or root
     */
    bool is_directory() const { 
        return type == DocxNodeType::Directory || type == DocxNodeType::Root; 
    }
    
    /**
     * @brief Check if node is a file
     * @return true if file (not directory)
     */
    bool is_file() const { return !is_directory(); }
    
    /**
     * @brief Get binary data (loads if necessary)
     * @return Binary data vector
     */
    std::vector<uint8_t> get_binary_data(const LoadConfig& config) {
        if (type == DocxNodeType::XmlFile && xml_doc) {
            // Serialize XML to binary
            return serialize_xml_to_binary();
        }
        file_storage.ensure_loaded(config);
        return file_storage.get_data();
    }
    
    /**
     * @brief Set binary data
     */
    void set_binary_data(std::vector<uint8_t>&& data);
    
    /**
     * @brief Serialize XML to binary
     */
    std::vector<uint8_t> serialize_xml_to_binary() const;
    
    /**
     * @brief Add child directory
     * @param dir_name Directory name
     * @return Shared pointer to new directory node
     */
    std::shared_ptr<DocxTreeNode> add_directory(const std::string& dir_name);
    
    /**
     * @brief Add child file
     * @param file_name File name
     * @param file_type File type
     * @return Shared pointer to new file node
     */
    std::shared_ptr<DocxTreeNode> add_file(const std::string& file_name, 
                                           DocxNodeType file_type);
    
    /**
     * @brief Find child by name
     * @param child_name Child name to find
     * @return Shared pointer to child, or nullptr
     */
    std::shared_ptr<DocxTreeNode> find_child(const std::string& child_name) const;
    
    /**
     * @brief Find or create directory
     * @param dir_name Directory name
     * @return Shared pointer to directory node
     */
    std::shared_ptr<DocxTreeNode> find_or_create_directory(const std::string& dir_name);
};

// ============================================================================
// LRU Cache for XML Nodes
// ============================================================================

/**
 * @class LRUCache
 * @brief LRU cache for managing XML node memory
 * @internal
 */
class LRUCache {
public:
    using NodePtr = std::shared_ptr<DocxTreeNode>;
    
private:
    size_t max_size_;
    size_t current_size_ = 0;
    size_t max_memory_mb_;
    size_t current_memory_mb_ = 0;
    
    std::list<std::string> lru_list_;  ///< Most recent at front
    std::map<std::string, std::pair<NodePtr, std::list<std::string>::iterator>> cache_;
    mutable std::shared_mutex mutex_;
    
public:
    LRUCache(size_t max_nodes, size_t max_memory_mb)
        : max_size_(max_nodes), max_memory_mb_(max_memory_mb) {}
    
    // Access node (update LRU)
    NodePtr touch(const std::string& path);
    
    // Add node to cache
    void add(const std::string& path, NodePtr node, size_t estimated_mb);
    
    // Remove from cache
    void remove(const std::string& path);
    
    // Serialize and release least recently used nodes until memory limit is met
    void evict_if_needed();
    
    // Clear cache
    void clear();
    
    size_t size() const { return current_size_; }
};

// ============================================================================
// Loading Statistics
// ============================================================================

/**
 * @struct LoadStatistics
 * @brief Statistics for loading operations
 * @internal
 */
struct LoadStatistics {
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    
    size_t total_entries = 0;
    size_t processed_entries = 0;
    size_t xml_files = 0;
    size_t media_files = 0;
    size_t binary_files = 0;
    size_t lazy_loaded = 0;
    size_t memory_mapped = 0;
    size_t temp_files = 0;
    
    size_t total_bytes_read = 0;
    size_t peak_memory_usage = 0;
    
    double get_elapsed_ms() const {
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }
};

// ============================================================================
// DOCX Tree
// ============================================================================

/**
 * @class DocxTree
 * @brief Manages the DOCX package tree structure
 * @details Provides tree operations for navigating and modifying
 *          the document package structure with lazy loading support.
 * @internal
 */
class DocxTree {
private:
    std::shared_ptr<DocxTreeNode> root_;  ///< Root node
    std::map<std::string, std::weak_ptr<DocxTreeNode>> path_map_;  ///< Fast path lookup
    
    // Caches
    std::unique_ptr<LRUCache> xml_cache_;
    
    // Configuration
    LoadConfig config_;
    
    // ZIP handle for lazy loading
    zip_t* zip_handle_ = nullptr;
    bool owns_zip_handle_ = false;
    
    // Thread safety
    mutable std::shared_mutex path_map_mutex_;
    
public:
    /** @brief Construct empty tree */
    DocxTree();
    
    /** @brief Destructor */
    ~DocxTree();
    
    /** @brief Set load configuration */
    void set_config(const LoadConfig& config) { config_ = config; }
    const LoadConfig& get_config() const { return config_; }
    
    /** @brief Set ZIP handle for lazy loading */
    void set_zip_handle(zip_t* handle, bool owns = false);
    
    /** @return Root node */
    std::shared_ptr<DocxTreeNode> get_root() const { return root_; }
    
    /**
     * @brief Find node by path (thread-safe)
     * @param path File path
     * @return Node if found, nullptr otherwise
     */
    std::shared_ptr<DocxTreeNode> find_node(const std::string& path) const;
    
    /**
     * @brief Find or create node
     * @param path File path
     * @param type Node type
     * @return Node (created if didn't exist)
     */
    std::shared_ptr<DocxTreeNode> find_or_create_node(const std::string& path, 
                                                       DocxNodeType type);
    
    /**
     * @brief Add file from ZIP entry with lazy loading support
     * @param entry_path Entry path
     * @param data Binary data (empty if lazy loading)
     * @param entry_index ZIP entry index for lazy loading
     * @param entry_size Entry size
     * @return Created node
     */
    std::shared_ptr<DocxTreeNode> add_zip_entry(const std::string& entry_path, 
                                                 const std::vector<uint8_t>& data,
                                                 int entry_index = -1,
                                                 size_t entry_size = 0);
    
    /**
     * @brief Add XML file
     * @param path File path
     * @param doc XML document
     * @return Created node
     */
    std::shared_ptr<DocxTreeNode> add_xml_file(const std::string& path, 
                                                pugi::xml_document&& doc);
    
    /**
     * @brief Add media file
     * @param path File path
     * @param data Binary data
     * @param content_type MIME type
     * @return Created node
     */
    std::shared_ptr<DocxTreeNode> add_media_file(const std::string& path,
                                                  const std::vector<uint8_t>& data,
                                                  const std::string& content_type);
    
    /**
     * @brief Remove node
     * @param path File path
     * @return true if node existed and was removed
     */
    bool remove_node(const std::string& path);
    
    /**
     * @brief Iterate all files
     * @param callback Function called for each file node
     */
    void iterate_files(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const;
    
    /**
     * @brief Iterate all nodes
     * @param callback Function called for each node
     */
    void iterate_all(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const;
    
    /**
     * @brief Get all XML files
     * @return Vector of XML file nodes
     */
    std::vector<std::shared_ptr<DocxTreeNode>> get_all_xml_files() const;
    
    /**
     * @brief Get all media files
     * @return Vector of media file nodes
     */
    std::vector<std::shared_ptr<DocxTreeNode>> get_all_media_files() const;
    
    /** @brief Rebuild path map for fast lookup */
    void rebuild_path_map();
    
    /** @brief Clear all nodes */
    void clear();
    
    /** @brief Preload all lazy-loaded files */
    bool preload_all();
    
    /** @brief Unload non-critical nodes to free memory */
    size_t unload_non_critical();
    
private:
    // Determine if node is a critical document part
    bool is_critical_part(const std::string& path) const;
    
    // Select appropriate storage type
    StorageType select_storage_type(size_t file_size) const;
};

// ============================================================================
// Relationship Entry
// ============================================================================

/**
 * @struct Relationship
 * @brief Single relationship entry from _rels file
 * @internal
 */
struct Relationship {
    std::string id;           ///< Relationship ID (e.g., "rId1")
    std::string type;         ///< Relationship type URL
    std::string target;       ///< Target path
    std::string target_mode;  ///< Target mode (External/Internal)
    
    Relationship() = default;
    
    Relationship(const std::string& i, const std::string& t, 
                 const std::string& tgt, const std::string& tm = "")
        : id(i), type(t), target(tgt), target_mode(tm) {}
};

// ============================================================================
// Content Type
// ============================================================================

/**
 * @struct ContentType
 * @brief Content type entry from [Content_Types].xml
 * @internal
 */
struct ContentType {
    std::string extension;    ///< File extension (for Default entries)
    std::string part_name;    ///< Part path (for Override entries)
    std::string content_type; ///< MIME content type
    bool is_default = false;  ///< True for Default, false for Override
};

// ============================================================================
// XML String Writer
// ============================================================================

/**
 * @struct xml_string_writer
 * @brief Custom XML writer for serializing to string
 * @internal
 */
struct xml_string_writer : pugi::xml_writer {
    std::string result;  ///< Output string
    
    void write(const void* data, size_t size) override {
        result.append(static_cast<const char*>(data), size);
    }
};

// ============================================================================
// Document Private Implementation
// ============================================================================

/**
 * @class DocumentImpl
 * @brief Private implementation of Document class
 * @details Contains all internal state and operations for Document.
 *          Separated from public API using PIMPL idiom.
 * @internal
 */
class DocumentImpl {
public:
    // File state
    std::string filepath_;  ///< Document file path
    bool is_open_ = false;  ///< Open status flag
    
    // Configuration
    LoadConfig load_config_;  ///< Loading configuration
    
    // Tree structure
    DocxTree tree_;  ///< Package tree
    
    // Quick access caches
    std::map<std::string, std::shared_ptr<DocxTreeNode>> xml_parts_cache_;
    std::map<std::string, std::shared_ptr<DocxTreeNode>> media_files_cache_;
    
    // Relationships
    std::map<std::string, std::vector<Relationship>> relationships_;
    
    // Modified tracking
    std::set<std::string> modified_parts_;
    
    // ZIP handling
    zip_t* zip_handle_ = nullptr;  ///< ZIP file handle
    bool zip_dirty_ = false;       ///< ZIP needs reopening
    
    // Content types
    std::vector<ContentType> content_types_;
    
    // Iterator helpers
    Paragraph* paragraph_ = nullptr;
    Table* table_ = nullptr;
    
    // Statistics
    LoadStatistics last_load_stats_;
    LoadResult last_load_result_;
    
    /** @brief Constructor */
    DocumentImpl();
    
    /** @brief Destructor */
    ~DocumentImpl();
    
    // Configuration
    void set_load_config(const LoadConfig& config) { load_config_ = config; }
    const LoadConfig& get_load_config() const { return load_config_; }
    
    // ZIP operations
    bool open_zip(const std::string& path);
    void close_zip();
    bool ensure_zip_handle();
    std::vector<uint8_t> read_zip_entry(const std::string& entry_name);
    
    // Tree loading (optimized versions)
    bool load_tree_from_zip();
    LoadResult load_tree_with_result();
    
    // Parallel loading
    bool load_tree_parallel(LoadStatistics& stats);
    bool load_entries_batch(const std::vector<std::pair<int, std::string>>& entries,
                           LoadStatistics& stats);
    
    // Legacy loading helpers
    std::shared_ptr<DocxTreeNode> load_zip_entry_to_tree(const std::string& entry_path,
                                                          const std::vector<uint8_t>& data);
    void build_caches_from_tree();
    
    // Progress reporting
    void report_progress(int percent, const std::string& current_file);
    
    // Content types and relationships
    bool load_content_types();
    void parse_relationships(const std::string& rels_path);
    void load_all_relationships();
    void discover_parts_from_rels();
    
    // Content type helpers
    std::string get_content_type(const std::string& extension) const;
    void add_content_type_override(const std::string& part_name, 
                                   const std::string& content_type);
    void update_content_types_xml();
    
    // Relationship helpers
    std::string add_relationship(const std::string& rels_path, 
                                 const std::string& type, 
                                 const std::string& target, 
                                 const std::string& target_mode = "");
    void remove_relationship(const std::string& rels_path, const std::string& rel_id);
    std::string find_relationship_id(const std::string& rels_path, 
                                     const std::string& target) const;
    void update_relationships_xml(const std::string& rels_path);
    
    // Save operations
    bool save_to_zip(const std::string& output_path);
    bool save_tree_to_zip(::zip_t* zip);
    bool write_tree_node(::zip_t* zip, std::shared_ptr<DocxTreeNode> node);
    bool write_xml_part(zip_t* zip, const std::string& part_path);
    bool write_media_files(zip_t* zip);
    bool write_zip_entries(zip_t* zip);
    
    // Media helpers
    std::string get_mime_type(const std::string& filename) const;
    std::string get_extension_from_mime(const std::string& mime_type) const;
    
    // Tree access
    std::shared_ptr<DocxTreeNode> get_tree_node(const std::string& path) const;
    std::shared_ptr<DocxTreeNode> create_tree_node(const std::string& path, 
                                                   DocxNodeType type);
    
    // Lazy loading helpers
    bool preload_all_lazy_files();
    size_t unload_to_free_memory();
    
    // Create empty document
    bool create_empty_document();
    
    // Statistics
    const LoadStatistics& get_last_load_stats() const { return last_load_stats_; }
    const LoadResult& get_last_load_result() const { return last_load_result_; }
};

} // namespace cdocx
