/**
 * @file impl.cpp
 * @brief DocumentImpl class implementation
 * @details Private implementation details for the Document class.
 *          Handles ZIP operations, XML parsing, and document structure.
 * 
 * @author Amir Mohamadi (@amiremohamadi)
 * @copyright MIT License
 * @date 2024
 * @version 0.2.0
 */

#include <detail/impl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

// ZIP library
extern "C" {
#include <zip/zip.h>
}

namespace cdocx {

// ============================================================================
// DocumentImpl Constructor / Destructor
// ============================================================================

DocumentImpl::DocumentImpl() = default;

DocumentImpl::~DocumentImpl() {
    close_zip();
    delete paragraph_;
    delete table_;
}

// ============================================================================
// ZIP Operations
// ============================================================================

bool DocumentImpl::open_zip(const std::string& path) {
    zip_handle_ = zip_open(path.c_str(), 0, 'r');
    return zip_handle_ != nullptr;
}

void DocumentImpl::close_zip() {
    if (zip_handle_) {
        zip_close(zip_handle_);
        zip_handle_ = nullptr;
    }
}

bool DocumentImpl::ensure_zip_handle() {
    if (zip_dirty_ || !zip_handle_) {
        close_zip();
        if (!filepath_.empty()) {
            return open_zip(filepath_);
        }
        return false;
    }
    return zip_handle_ != nullptr;
}

std::vector<uint8_t> DocumentImpl::read_zip_entry(const std::string& entry_name) {
    std::vector<uint8_t> result;
    
    if (!zip_handle_) {
        return result;
    }
    
    // Open entry
    if (zip_entry_open(zip_handle_, entry_name.c_str()) != 0) {
        return result;
    }
    
    // Get entry size
    void* data = nullptr;
    size_t size = 0;
    if (zip_entry_read(zip_handle_, &data, &size) == 0 && data && size > 0) {
        result.resize(size);
        std::memcpy(result.data(), data, size);
        free(data);
    }
    
    zip_entry_close(zip_handle_);
    return result;
}

// ============================================================================
// Tree Loading
// ============================================================================

bool DocumentImpl::load_tree_from_zip() {
    if (!zip_handle_) {
        return false;
    }
    
    tree_.clear();
    
    // Get total entries
    int total_entries = zip_total_entries(zip_handle_);
    if (total_entries < 0) {
        return false;
    }
    
    // Iterate all entries
    for (int i = 0; i < total_entries; ++i) {
        // Open entry by index
        if (zip_entry_openbyindex(zip_handle_, i) != 0) {
            continue;
        }
        
        // Get entry name
        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        std::string entry_name(name);
        bool is_dir = zip_entry_isdir(zip_handle_);
        
        if (!is_dir) {
            // Read entry data
            void* data = nullptr;
            size_t size = 0;
            
            if (zip_entry_read(zip_handle_, &data, &size) == 0 && data && size > 0) {
                std::vector<uint8_t> buffer(size);
                std::memcpy(buffer.data(), data, size);
                free(data);
                
                // Add to tree
                tree_.add_zip_entry(entry_name, buffer);
            }
        }
        
        zip_entry_close(zip_handle_);
    }
    
    tree_.rebuild_path_map();
    return true;
}

void DocumentImpl::build_caches_from_tree() {
    xml_parts_cache_.clear();
    media_files_cache_.clear();
    
    // Iterate all files in tree
    tree_.iterate_files([this](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::XmlFile) {
            xml_parts_cache_[node->full_path] = node;
        } else if (node->type == DocxNodeType::MediaFile) {
            media_files_cache_[node->full_path] = node;
        }
    });
}

// ============================================================================
// Relationships and Content Types
// ============================================================================

void DocumentImpl::parse_relationships(const std::string& rels_path) {
    auto doc = tree_.find_node(rels_path);
    if (!doc || !doc->xml_doc) {
        return;
    }
    
    std::vector<Relationship> rels;
    
    pugi::xml_node root = doc->xml_doc->child("Relationships");
    for (pugi::xml_node rel = root.child("Relationship"); rel; rel = rel.next_sibling("Relationship")) {
        Relationship r;
        r.id = rel.attribute("Id").value();
        r.type = rel.attribute("Type").value();
        r.target = rel.attribute("Target").value();
        r.target_mode = rel.attribute("TargetMode").value();
        rels.push_back(r);
    }
    
    relationships_[rels_path] = std::move(rels);
}

void DocumentImpl::load_all_relationships() {
    // Load package relationships
    if (tree_.find_node("_rels/.rels")) {
        parse_relationships("_rels/.rels");
    }
    
    // Load document relationships
    if (tree_.find_node("word/_rels/document.xml.rels")) {
        parse_relationships("word/_rels/document.xml.rels");
    }
}

bool DocumentImpl::load_content_types() {
    auto doc = tree_.find_node("[Content_Types].xml");
    if (!doc || !doc->xml_doc) {
        return false;
    }
    
    content_types_.clear();
    
    pugi::xml_node root = doc->xml_doc->child("Types");
    
    // Parse Defaults
    for (pugi::xml_node def = root.child("Default"); def; def = def.next_sibling("Default")) {
        ContentType ct;
        ct.extension = def.attribute("Extension").value();
        ct.content_type = def.attribute("ContentType").value();
        ct.is_default = true;
        content_types_.push_back(ct);
    }
    
    // Parse Overrides
    for (pugi::xml_node over = root.child("Override"); over; over = over.next_sibling("Override")) {
        ContentType ct;
        ct.part_name = over.attribute("PartName").value();
        ct.content_type = over.attribute("ContentType").value();
        ct.is_default = false;
        content_types_.push_back(ct);
    }
    
    return true;
}

std::string DocumentImpl::add_relationship(const std::string& rels_path,
                                            const std::string& type,
                                            const std::string& target,
                                            const std::string& target_mode) {
    // Find next available rId
    int max_id = 0;
    auto& rels = relationships_[rels_path];
    
    for (const auto& rel : rels) {
        if (rel.id.substr(0, 3) == "rId") {
            int id_num = std::stoi(rel.id.substr(3));
            max_id = std::max(max_id, id_num);
        }
    }
    
    std::string new_id = "rId" + std::to_string(max_id + 1);
    rels.emplace_back(new_id, type, target, target_mode);
    
    return new_id;
}

void DocumentImpl::remove_relationship(const std::string& rels_path, const std::string& rel_id) {
    auto& rels = relationships_[rels_path];
    rels.erase(std::remove_if(rels.begin(), rels.end(),
                              [&rel_id](const Relationship& r) { return r.id == rel_id; }),
               rels.end());
}

std::string DocumentImpl::find_relationship_id(const std::string& rels_path,
                                                const std::string& target) const {
    auto it = relationships_.find(rels_path);
    if (it == relationships_.end()) {
        return "";
    }
    
    for (const auto& rel : it->second) {
        if (rel.target == target) {
            return rel.id;
        }
    }
    
    return "";
}

void DocumentImpl::update_relationships_xml(const std::string& rels_path) {
    auto node = tree_.find_node(rels_path);
    if (!node) {
        // Create new relationships file if it doesn't exist
        node = tree_.find_or_create_node(rels_path, DocxNodeType::XmlFile);
        node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    
    if (!node->xml_doc) {
        node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    
    node->xml_doc->reset();
    
    // Create root element
    pugi::xml_node root = node->xml_doc->append_child("Relationships");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/relationships");
    
    // Add all relationships
    auto it = relationships_.find(rels_path);
    if (it != relationships_.end()) {
        for (const auto& rel : it->second) {
            pugi::xml_node rel_node = root.append_child("Relationship");
            rel_node.append_attribute("Id").set_value(rel.id.c_str());
            rel_node.append_attribute("Type").set_value(rel.type.c_str());
            rel_node.append_attribute("Target").set_value(rel.target.c_str());
            if (!rel.target_mode.empty()) {
                rel_node.append_attribute("TargetMode").set_value(rel.target_mode.c_str());
            }
        }
    }
    
    node->is_modified = true;
}

void DocumentImpl::add_content_type_override(const std::string& part_name,
                                              const std::string& content_type) {
    // Check if already exists
    for (auto& ct : content_types_) {
        if (!ct.is_default && ct.part_name == part_name) {
            ct.content_type = content_type;
            return;
        }
    }
    
    // Add new override
    ContentType ct;
    ct.part_name = part_name;
    ct.content_type = content_type;
    ct.is_default = false;
    content_types_.push_back(ct);
}

void DocumentImpl::update_content_types_xml() {
    auto node = tree_.find_or_create_node("[Content_Types].xml", DocxNodeType::XmlFile);
    if (!node->xml_doc) {
        node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    
    node->xml_doc->reset();
    
    // Create root element
    pugi::xml_node root = node->xml_doc->append_child("Types");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/content-types");
    
    // Add defaults first
    for (const auto& ct : content_types_) {
        if (ct.is_default) {
            pugi::xml_node def = root.append_child("Default");
            def.append_attribute("Extension").set_value(ct.extension.c_str());
            def.append_attribute("ContentType").set_value(ct.content_type.c_str());
        }
    }
    
    // Add overrides
    for (const auto& ct : content_types_) {
        if (!ct.is_default) {
            pugi::xml_node over = root.append_child("Override");
            over.append_attribute("PartName").set_value(ct.part_name.c_str());
            over.append_attribute("ContentType").set_value(ct.content_type.c_str());
        }
    }
    
    node->is_modified = true;
}

// ============================================================================
// Save Operations
// ============================================================================

bool DocumentImpl::save_to_zip(const std::string& output_path) {
    // Create new ZIP file
    zip_t* zip = zip_open(output_path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    if (!zip) {
        return false;
    }
    
    bool success = save_tree_to_zip(zip);
    
    zip_close(zip);
    return success;
}

bool DocumentImpl::save_tree_to_zip(::zip_t* zip) {
    if (!zip) {
        return false;
    }
    
    // Iterate all files in tree
    bool success = true;
    tree_.iterate_files([this, zip, &success](std::shared_ptr<DocxTreeNode> node) {
        if (!success || node->is_deleted) {
            return;
        }
        
        success = write_tree_node(zip, node);
    });
    
    return success;
}

bool DocumentImpl::write_tree_node(::zip_t* zip, std::shared_ptr<DocxTreeNode> node) {
    if (!zip || !node || node->is_deleted) {
        return false;
    }
    
    // Open entry
    if (zip_entry_open(zip, node->full_path.c_str()) != 0) {
        return false;
    }
    
    bool success = false;
    
    if (node->type == DocxNodeType::XmlFile && node->xml_doc) {
        // Serialize XML
        xml_string_writer writer;
        node->xml_doc->save(writer, "  ");
        
        // Add XML declaration if not present
        std::string xml_output = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
        xml_output += writer.result;
        
        success = zip_entry_write(zip, xml_output.data(), xml_output.size()) == 0;
    } else {
        // Write binary data
        success = zip_entry_write(zip, node->binary_data.data(), 
                                   node->binary_data.size()) == 0;
    }
    
    zip_entry_close(zip);
    return success;
}

// ============================================================================
// Media Helpers
// ============================================================================

std::string DocumentImpl::get_mime_type(const std::string& filename) const {
    size_t dot_pos = filename.rfind('.');
    if (dot_pos == std::string::npos) {
        return "application/octet-stream";
    }
    
    std::string ext = filename.substr(dot_pos);
    
    // Convert to lowercase
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    static const std::map<std::string, std::string> mime_types = {
        {".png", "image/png"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".gif", "image/gif"},
        {".bmp", "image/bmp"},
        {".tiff", "image/tiff"},
        {".tif", "image/tiff"},
        {".webp", "image/webp"},
        {".xml", "application/xml"},
        {".rels", "application/vnd.openxmlformats-package.relationships+xml"}
    };
    
    auto it = mime_types.find(ext);
    if (it != mime_types.end()) {
        return it->second;
    }
    
    return "application/octet-stream";
}

// ============================================================================
// Empty Document Creation
// ============================================================================

bool DocumentImpl::create_empty_document() {
    tree_.clear();
    
    // Create [Content_Types].xml
    {
        auto node = tree_.find_or_create_node("[Content_Types].xml", DocxNodeType::XmlFile);
        node->xml_doc = std::make_shared<pugi::xml_document>();
        
        pugi::xml_node types = node->xml_doc->append_child("Types");
        types.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/package/2006/content-types");
        
        // Add defaults
        auto add_default = [&types](const char* ext, const char* ct) {
            pugi::xml_node def = types.append_child("Default");
            def.append_attribute("Extension").set_value(ext);
            def.append_attribute("ContentType").set_value(ct);
        };
        
        add_default("rels", "application/vnd.openxmlformats-package.relationships+xml");
        add_default("xml", "application/xml");
        
        // Add overrides
        auto add_override = [&types](const char* pn, const char* ct) {
            pugi::xml_node over = types.append_child("Override");
            over.append_attribute("PartName").set_value(pn);
            over.append_attribute("ContentType").set_value(ct);
        };
        
        add_override("/word/document.xml",
                     "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml");
    }
    
    // Create _rels/.rels
    {
        auto node = tree_.find_or_create_node("_rels/.rels", DocxNodeType::XmlFile);
        node->xml_doc = std::make_shared<pugi::xml_document>();
        
        pugi::xml_node rels = node->xml_doc->append_child("Relationships");
        rels.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/package/2006/relationships");
        
        pugi::xml_node rel = rels.append_child("Relationship");
        rel.append_attribute("Id").set_value("rId1");
        rel.append_attribute("Type").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument");
        rel.append_attribute("Target").set_value("word/document.xml");
    }
    
    // Create word/_rels/document.xml.rels
    {
        auto node = tree_.find_or_create_node("word/_rels/document.xml.rels", DocxNodeType::XmlFile);
        node->xml_doc = std::make_shared<pugi::xml_document>();
        
        pugi::xml_node rels = node->xml_doc->append_child("Relationships");
        rels.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/package/2006/relationships");
        // Empty relationships
    }
    
    // Create word/document.xml
    {
        auto node = tree_.find_or_create_node("word/document.xml", DocxNodeType::XmlFile);
        node->xml_doc = std::make_shared<pugi::xml_document>();
        
        pugi::xml_node doc = node->xml_doc->append_child("w:document");
        doc.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        doc.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
        doc.append_attribute("xmlns:wp").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");
        
        pugi::xml_node body = doc.append_child("w:body");
        
        // Add one empty paragraph
        pugi::xml_node para = body.append_child("w:p");
        pugi::xml_node run = para.append_child("w:r");
        run.append_child("w:t");
    }
    
    // Rebuild caches
    tree_.rebuild_path_map();
    build_caches_from_tree();
    load_all_relationships();
    load_content_types();
    
    return true;
}

} // namespace cdocx
