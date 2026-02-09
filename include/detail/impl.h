/**
 * @file impl.h
 * @brief Private implementation details for CDocx
 * @warning This file contains internal implementation details and should NOT
 *          be included directly by users of the library. It is used internally
 *          by cdocx source files.
 * 
 * @author Amir Mohamadi (@amiremohamadi)
 * @copyright MIT License
 * @date 2024
 * @version 0.2.0
 * @internal
 */

#pragma once

#include <pugixml.hpp>
#include <zip.h>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>
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

// ============================================================================
// Node Types
// ============================================================================

/**
 * @enum DocxNodeType
 * @brief Types of nodes in the DOCX package tree
 * @internal
 */
enum class DocxNodeType {
    Root,       ///< Root node representing the package
    Directory,  ///< Directory/folder node
    XmlFile,    ///< XML file with parsed content
    MediaFile,  ///< Media file (image, etc.)
    BinaryFile  ///< Other binary file
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
struct DocxTreeNode {
    std::string name;                           ///< File/directory name
    std::string full_path;                      ///< Full path in ZIP
    DocxNodeType type;                          ///< Node type
    
    // Parent and children
    DocxTreeNode* parent;                       ///< Parent node
    std::vector<std::shared_ptr<DocxTreeNode>> children;  ///< Child nodes
    
    // Data storage (type-specific)
    std::shared_ptr<pugi::xml_document> xml_doc;  ///< For XmlFile type
    std::vector<uint8_t> binary_data;             ///< For Media/Binary files
    std::string content_type;                     ///< MIME type
    
    // State tracking
    bool is_modified = false;   ///< Modified since load
    bool is_new = false;        ///< Newly created
    bool is_deleted = false;    ///< Marked for deletion
    
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
// DOCX Tree
// ============================================================================

/**
 * @class DocxTree
 * @brief Manages the DOCX package tree structure
 * @details Provides tree operations for navigating and modifying
 *          the document package structure.
 * @internal
 */
class DocxTree {
private:
    std::shared_ptr<DocxTreeNode> root_;  ///< Root node
    std::map<std::string, std::weak_ptr<DocxTreeNode>> path_map_;  ///< Fast path lookup
    
public:
    /** @brief Construct empty tree */
    DocxTree();
    
    /** @return Root node */
    std::shared_ptr<DocxTreeNode> get_root() const { return root_; }
    
    /**
     * @brief Find node by path
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
    
    /** @brief Constructor */
    DocumentImpl();
    
    /** @brief Destructor */
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
    
    // Create empty document
    bool create_empty_document();
};

} // namespace cdocx
