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
 * @version 0.7.0 - Uses types from document.h
 * @internal
 */

#pragma once

#include <cdocx/document.h>
#include <cdocx/section.h>

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
enum class LoadErrorType : std::uint8_t;
enum class DocumentIntegrity : std::uint8_t;

// ============================================================================
// Storage Type (kept for API compatibility)
// ============================================================================

/**
 * @enum StorageType
 * @brief File data storage type (kept for API compatibility)
 * @internal
 * @note Simplified - all data is now stored in memory
 */
enum class StorageType : std::uint8_t {
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
// DocxTreeNode Extension Methods
// ============================================================================

// These methods are defined in tree.cpp
// DocxTreeNode is defined in document.h

// ============================================================================
// DocxTree Extension Methods
// ============================================================================

// DocxTree is defined in document.h
// Additional methods are defined in tree.cpp

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
 * @note This is kept for backward compatibility during the transition to DOM architecture.
 *       New code should use Document class directly.
 */
class DocumentImpl {
public:
    // Reference to the public Document class
    Document* document_ = nullptr;
    
    // File state
    std::string filepath_;  ///< Document file path
    bool is_open_ = false;  ///< Open status flag
    
    // Configuration
    LoadConfig load_config_;  ///< Loading configuration
    
    // Tree structure (now uses DocxTree from document.h)
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
    
    // Iterator helpers (legacy)
    Paragraph* paragraph_ = nullptr;
    Table* table_ = nullptr;
    
    // Statistics
    LoadStatistics last_load_stats_;
    LoadResult last_load_result_;
    
    // Bookmark ID generation
    int next_bookmark_id_ = 1;  ///< Next available bookmark ID
    
    // Section support (v0.5.0)
    std::list<Section> sections_;  ///< Document sections
    Section* current_section_ = nullptr;  ///< Current active section
    
    // Numbering support (v0.5.0)
    std::unique_ptr<NumberingManager> numbering_manager_;  ///< List/numbering manager
    
    // Header/Footer counters (v0.5.0)
    int next_header_number_ = 1;  ///< Next header file number
    int next_footer_number_ = 1;  ///< Next footer file number
    
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
    bool write_tree_node(::zip_t* zip, const std::shared_ptr<DocxTreeNode>& node);
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
    
    // Section support (v0.5.0)
    void load_sections();
    void save_sections();
    Section* add_section_internal();
    int get_next_header_number() { return next_header_number_++; }
    int get_next_footer_number() { return next_footer_number_++; }
    
    // Numbering support (v0.5.0)
    void init_numbering_manager();
    void load_numbering();
    void save_numbering();
    
    // XML Part helpers (v0.5.0)
    pugi::xml_document* get_xml_part(const std::string& part_path);
    pugi::xml_document& create_xml_part(const std::string& part_path);
};

} // namespace cdocx
