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
 * @version 0.3.0 - Optimized Version with Parallel Processing
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
 * @brief File data storage type (kept for API compatibility)
 * @internal
 * @note Simplified - all data is now stored in memory
 */
enum class StorageType {
    Memory = 0      ///< In memory (vector<uint8_t>)
};

// ============================================================================
// File Data Storage
// ============================================================================

/**
 * @class FileDataStorage
 * @brief Simple file data storage in memory
 * @internal
 * @note Simplified version - all data stored directly in memory
 */
class FileDataStorage {
private:
    mutable std::shared_mutex mutex_;
    std::vector<uint8_t> data_;
    size_t data_size_ = 0;
    
public:
    FileDataStorage() = default;
    
    // Size query
    size_t get_size() const { return data_size_; }
    bool empty() const { return data_.empty(); }
    
    // Store data (directly in memory)
    void store_in_memory(std::vector<uint8_t>&& data) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        data_ = std::move(data);
        data_size_ = data_.size();
    }
    
    // Get data
    std::vector<uint8_t> get_data() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_;
    }
    
    // Get direct pointer to data (read-only)
    const std::vector<uint8_t>* get_memory_data() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return &data_;
    }
    
    // Clear data
    void clear() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        data_.clear();
        data_size_ = 0;
    }
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
     * @brief Get binary data
     * @return Binary data vector (always from memory)
     */
    std::vector<uint8_t> get_binary_data() const {
        if (type == DocxNodeType::XmlFile && xml_doc) {
            // Serialize XML to binary
            return serialize_xml_to_binary();
        }
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
 *          the document package structure.
 *          All data is stored directly in memory.
 * @internal
 */
class DocxTree {
private:
    std::shared_ptr<DocxTreeNode> root_;  ///< Root node
    std::map<std::string, std::weak_ptr<DocxTreeNode>> path_map_;  ///< Fast path lookup
    
    // Thread safety
    mutable std::shared_mutex path_map_mutex_;
    
public:
    /** @brief Construct empty tree */
    DocxTree();
    
    /** @brief Destructor */
    ~DocxTree();
    
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
     * @brief Add file from ZIP entry
     * @param entry_path Entry path
     * @param data Binary data
     * @return Created node
     */
    std::shared_ptr<DocxTreeNode> add_zip_entry(const std::string& entry_path, 
                                                 const std::vector<uint8_t>& data);
    
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
    
private:
    // Determine if node is a critical document part
    bool is_critical_part(const std::string& path) const;
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
    
    // Bookmark ID generation
    int next_bookmark_id_ = 1;  ///< Next available bookmark ID
    
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
    
    // Create empty document
    bool create_empty_document();
    
    // Statistics
    const LoadStatistics& get_last_load_stats() const { return last_load_stats_; }
    const LoadResult& get_last_load_result() const { return last_load_result_; }
};

} // namespace cdocx
