// CDocx - Private Implementation Header
// This file contains internal implementation details and should NOT be included
// by external users of the library. It is used internally by cdocx source files.

#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <functional>
#include <cstdint>
#include <pugixml.hpp>
#include <zip.h>

// Forward declarations for internal use
struct zip_t;

namespace cdocx {

// ============================================================================
// Forward declarations for public types
// ============================================================================
class Document;
class Paragraph;
class Table;
class Template;
class DocumentInserter;

// ============================================================================
// Node types in the DOCX tree
// ============================================================================
enum class DocxNodeType {
    Root,       // Root node (represents the package)
    Directory,  // Directory/folder
    XmlFile,    // XML file (parsed into pugi::xml_document)
    MediaFile,  // Media file (binary data)
    BinaryFile  // Other binary files
};

// ============================================================================
// Tree node for DOCX package structure
// ============================================================================
struct DocxTreeNode {
    std::string name;                           // File/directory name
    std::string full_path;                      // Full path in ZIP
    DocxNodeType type;                          // Node type
    
    // Parent and children
    DocxTreeNode* parent;
    std::vector<std::shared_ptr<DocxTreeNode>> children;
    
    // Data storage (type-specific)
    std::shared_ptr<pugi::xml_document> xml_doc;     // For XmlFile type
    std::vector<uint8_t> binary_data;                // For MediaFile/BinaryFile
    std::string content_type;                        // MIME type
    
    // State tracking
    bool is_modified = false;
    bool is_new = false;
    bool is_deleted = false;
    
    DocxTreeNode(const std::string& n, DocxNodeType t, DocxTreeNode* p = nullptr)
        : name(n), type(t), parent(p) {}
    
    // Helper methods
    bool is_directory() const { 
        return type == DocxNodeType::Directory || type == DocxNodeType::Root; 
    }
    bool is_file() const { return !is_directory(); }
    
    // Add child directory
    std::shared_ptr<DocxTreeNode> add_directory(const std::string& dir_name);
    
    // Add child file
    std::shared_ptr<DocxTreeNode> add_file(const std::string& file_name, DocxNodeType file_type);
    
    // Find child by name
    std::shared_ptr<DocxTreeNode> find_child(const std::string& child_name) const;
    
    // Find or create directory
    std::shared_ptr<DocxTreeNode> find_or_create_directory(const std::string& dir_name);
};

// ============================================================================
// DOCX Tree - Manages the tree structure
// ============================================================================
class DocxTree {
private:
    std::shared_ptr<DocxTreeNode> root_;
    std::map<std::string, std::weak_ptr<DocxTreeNode>> path_map_;  // Fast path lookup
    
public:
    DocxTree();
    
    // Get root node
    std::shared_ptr<DocxTreeNode> get_root() const { return root_; }
    
    // Find node by path
    std::shared_ptr<DocxTreeNode> find_node(const std::string& path) const;
    
    // Find or create node (creates intermediate directories)
    std::shared_ptr<DocxTreeNode> find_or_create_node(const std::string& path, DocxNodeType type);
    
    // Add file from ZIP entry
    std::shared_ptr<DocxTreeNode> add_zip_entry(const std::string& entry_path, 
                                                 const std::vector<uint8_t>& data);
    
    // Add XML file
    std::shared_ptr<DocxTreeNode> add_xml_file(const std::string& path, 
                                                pugi::xml_document&& doc);
    
    // Add media file
    std::shared_ptr<DocxTreeNode> add_media_file(const std::string& path,
                                                  const std::vector<uint8_t>& data,
                                                  const std::string& content_type);
    
    // Remove node
    bool remove_node(const std::string& path);
    
    // Iterate all files (non-directories)
    void iterate_files(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const;
    
    // Iterate all nodes
    void iterate_all(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const;
    
    // Get all XML files
    std::vector<std::shared_ptr<DocxTreeNode>> get_all_xml_files() const;
    
    // Get all media files
    std::vector<std::shared_ptr<DocxTreeNode>> get_all_media_files() const;
    
    // Build path map for fast lookup
    void rebuild_path_map();
    
    // Clear tree
    void clear();
};

// ============================================================================
// Relationship Entry - For _rels files
// ============================================================================
struct Relationship {
    std::string id;                      // Relationship ID (e.g., "rId1")
    std::string type;                    // Relationship type URL
    std::string target;                  // Target path
    std::string target_mode;             // Target mode (External/Internal)
    
    Relationship() = default;
    Relationship(const std::string& i, const std::string& t, 
                 const std::string& tgt, const std::string& tm = "")
        : id(i), type(t), target(tgt), target_mode(tm) {}
};

// ============================================================================
// Content types cache
// ============================================================================
struct ContentType {
    std::string extension;   // For Default
    std::string part_name;   // For Override
    std::string content_type;
    bool is_default = false;
};

// ============================================================================
// Iterator Helper - Internal implementation
// ============================================================================
class IteratorHelper {
public:
    template<typename T>
    static T& get_begin(T& container) {
        container.set_parent(container.get_parent());
        return container;
    }
    
    template<typename T>
    static bool not_end(const T& iter, const T& end) {
        (void)end;
        return iter.has_next();
    }
    
    template<typename T>
    static void advance(T& iter) {
        iter.next();
    }
};

// ============================================================================
// XML String Writer - For serializing XML
// ============================================================================
struct xml_string_writer : pugi::xml_writer {
    std::string result;
    
    void write(const void* data, size_t size) override {
        result.append(static_cast<const char*>(data), size);
    }
};

// ============================================================================
// Document Private Implementation
// ============================================================================
class DocumentImpl {
public:
    // File path
    std::string filepath_;
    bool is_open_ = false;
    
    // Tree structure - primary storage for all DOCX content
    DocxTree tree_;
    
    // Quick access caches (for backward compatibility and performance)
    std::map<std::string, std::shared_ptr<DocxTreeNode>> xml_parts_cache_;
    std::map<std::string, std::shared_ptr<DocxTreeNode>> media_files_cache_;
    
    // Relationships cache
    std::map<std::string, std::vector<Relationship>> relationships_;
    
    // Track modified parts for incremental save
    std::set<std::string> modified_parts_;
    
    // ZIP handle for lazy operations
    zip_t* zip_handle_ = nullptr;
    bool zip_dirty_ = false;
    
    // Content types cache
    std::vector<ContentType> content_types_;
    
    // Iterator helpers (raw pointers to avoid incomplete type issues)
    Paragraph* paragraph_;
    Table* table_;
    
    // Constructor/Destructor
    DocumentImpl();
    ~DocumentImpl();
    
    // ZIP operations
    bool open_zip(const std::string& path);
    void close_zip();
    bool ensure_zip_handle();
    std::vector<uint8_t> read_zip_entry(const std::string& entry_name);
    
    // Tree loading
    bool load_tree_from_zip();
    std::shared_ptr<DocxTreeNode> load_zip_entry_to_tree(const std::string& entry_path,
                                                          const std::vector<uint8_t>& data);
    void build_caches_from_tree();
    
    // Legacy loading
    bool load_all_entries();
    bool load_xml_part(const std::string& part_path, const std::vector<uint8_t>& data);
    bool load_media_file(const std::string& entry_name, const std::vector<uint8_t>& data);
    
    // Content types and relationships
    bool load_content_types();
    void parse_relationships(const std::string& rels_path);
    void load_all_relationships();
    void discover_parts_from_rels();
    
    // Content type helpers
    std::string get_content_type(const std::string& extension) const;
    void add_content_type_override(const std::string& part_name, const std::string& content_type);
    void update_content_types_xml();
    
    // Relationship helpers
    std::string add_relationship(const std::string& rels_path, const std::string& type, 
                                 const std::string& target, const std::string& target_mode = "");
    void remove_relationship(const std::string& rels_path, const std::string& rel_id);
    std::string find_relationship_id(const std::string& rels_path, const std::string& target) const;
    void update_relationships_xml(const std::string& rels_path);
    
    // Save operations
    bool save_to_zip(const std::string& output_path);
    bool save_tree_to_zip(::zip_t* zip);
    bool write_tree_node(::zip_t* zip, std::shared_ptr<DocxTreeNode> node);
    
    // Legacy save helpers
    bool write_xml_part(zip_t* zip, const std::string& part_path);
    bool write_media_files(zip_t* zip);
    bool write_zip_entries(zip_t* zip);
    
    // Media helpers
    std::string get_mime_type(const std::string& filename) const;
    std::string get_extension_from_mime(const std::string& mime_type) const;
    
    // Tree access
    std::shared_ptr<DocxTreeNode> get_tree_node(const std::string& path) const;
    std::shared_ptr<DocxTreeNode> create_tree_node(const std::string& path, DocxNodeType type);
    
    // Create empty document
    bool create_empty_document();
};

} // namespace cdocx
