// CDocx - Document Implementation (PIMPL)
// This file implements the DocumentImpl class

#include "detail/cdocx_impl.h"
#include "cdocx.h"
#include <pugixml.hpp>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <ctime>

namespace cdocx {

// ============================================================================
// DocumentImpl Constructor/Destructor
// ============================================================================

DocumentImpl::DocumentImpl() 
    : paragraph_(new Paragraph()),
      table_(new Table()) {
}

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
        zip_handle_ = zip_open(filepath_.c_str(), 0, 'r');
        zip_dirty_ = false;
    }
    return zip_handle_ != nullptr;
}

std::vector<uint8_t> DocumentImpl::read_zip_entry(const std::string& entry_name) {
    std::vector<uint8_t> data;
    
    if (!zip_handle_) return data;
    
    if (zip_entry_open(zip_handle_, entry_name.c_str()) != 0) {
        return data;
    }
    
    void* buf = nullptr;
    size_t bufsize = 0;
    if (zip_entry_read(zip_handle_, &buf, &bufsize) == 0 && buf && bufsize > 0) {
        data = std::vector<uint8_t>(static_cast<uint8_t*>(buf), 
                                     static_cast<uint8_t*>(buf) + bufsize);
        free(buf);
    }
    
    zip_entry_close(zip_handle_);
    return data;
}

// ============================================================================
// Tree Loading
// ============================================================================

bool DocumentImpl::load_tree_from_zip() {
    if (!zip_handle_) return false;
    
    ssize_t entry_count = zip_entries_total(zip_handle_);
    if (entry_count < 0) return false;
    
    for (ssize_t i = 0; i < entry_count; i++) {
        if (zip_entry_openbyindex(zip_handle_, i) != 0) continue;
        
        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        std::string entry_name(name);
        
        // Skip directories
        if (entry_name.empty() || entry_name.back() == '/') {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        // Read entry data
        void* buf = nullptr;
        size_t bufsize = 0;
        ssize_t read_result = zip_entry_read(zip_handle_, &buf, &bufsize);
        
        if (read_result < 0 || !buf || bufsize == 0) {
            if (buf) free(buf);
            zip_entry_close(zip_handle_);
            continue;
        }
        
        std::vector<uint8_t> data(bufsize);
        std::memcpy(data.data(), buf, bufsize);
        free(buf);
        
        zip_entry_close(zip_handle_);
        
        // Add to tree
        load_zip_entry_to_tree(entry_name, data);
    }
    
    tree_.rebuild_path_map();
    return true;
}

std::shared_ptr<DocxTreeNode> DocumentImpl::load_zip_entry_to_tree(
    const std::string& entry_path, const std::vector<uint8_t>& data) {
    return tree_.add_zip_entry(entry_path, data);
}

void DocumentImpl::build_caches_from_tree() {
    xml_parts_cache_.clear();
    media_files_cache_.clear();
    
    tree_.iterate_files([this](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::XmlFile && node->xml_doc) {
            xml_parts_cache_[node->full_path] = node;
        } else if (node->type == DocxNodeType::MediaFile) {
            media_files_cache_[node->full_path] = node;
        }
    });
}

// ============================================================================
// Content Types and Relationships
// ============================================================================

bool DocumentImpl::load_content_types() {
    auto ct_node = tree_.find_node("[Content_Types].xml");
    if (!ct_node || !ct_node->xml_doc) return false;
    
    content_types_.clear();
    
    pugi::xml_node types = ct_node->xml_doc->child("Types");
    for (pugi::xml_node def = types.child("Default"); def; 
         def = def.next_sibling("Default")) {
        ContentType ct_entry;
        ct_entry.extension = def.attribute("Extension").value();
        ct_entry.content_type = def.attribute("ContentType").value();
        ct_entry.is_default = true;
        content_types_.push_back(ct_entry);
    }
    
    for (pugi::xml_node override = types.child("Override"); override;
         override = override.next_sibling("Override")) {
        ContentType ct_entry;
        ct_entry.part_name = override.attribute("PartName").value();
        ct_entry.content_type = override.attribute("ContentType").value();
        ct_entry.is_default = false;
        content_types_.push_back(ct_entry);
    }
    
    return true;
}

void DocumentImpl::parse_relationships(const std::string& rels_path) {
    auto node = tree_.find_node(rels_path);
    if (!node || !node->xml_doc) return;
    
    std::vector<Relationship> rels;
    pugi::xml_node root = node->xml_doc->child("Relationships");
    
    for (pugi::xml_node rel = root.child("Relationship"); rel; 
         rel = rel.next_sibling("Relationship")) {
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
    // Find all .rels files in the tree
    auto rels_files = tree_.get_all_xml_files();
    for (const auto& node : rels_files) {
        if (node->full_path.find(".rels") != std::string::npos) {
            parse_relationships(node->full_path);
        }
    }
}

void DocumentImpl::discover_parts_from_rels() {
    // Discover parts referenced in document relationships
    auto it = relationships_.find("word/_rels/document.xml.rels");
    if (it == relationships_.end()) return;
    
    for (const auto& rel : it->second) {
        if (!rel.target_mode.empty() && rel.target_mode == "External")
            continue;
        
        std::string target = rel.target;
        
        if (target.substr(0, 2) == "..") {
            target = target.substr(3);
        } else if (target.find(":/") == std::string::npos && target[0] != '/') {
            target = "word/" + target;
        }
        
        if (!tree_.find_node(target) && zip_handle_) {
            if (zip_entry_open(zip_handle_, target.c_str()) == 0) {
                void* buf = nullptr;
                size_t size = 0;
                if (zip_entry_read(zip_handle_, &buf, &size) == 0 && buf && size > 0) {
                    std::vector<uint8_t> data(static_cast<uint8_t*>(buf), 
                                               static_cast<uint8_t*>(buf) + size);
                    free(buf);
                    load_zip_entry_to_tree(target, data);
                }
                zip_entry_close(zip_handle_);
            }
        }
    }
}

std::string DocumentImpl::get_content_type(const std::string& extension) const {
    std::string ext_lower = extension;
    std::transform(ext_lower.begin(), ext_lower.end(), ext_lower.begin(), ::tolower);
    
    for (const auto& ct : content_types_) {
        if (ct.is_default) {
            std::string ct_ext = ct.extension;
            std::transform(ct_ext.begin(), ct_ext.end(), ct_ext.begin(), ::tolower);
            if (ct_ext == ext_lower) {
                return ct.content_type;
            }
        }
    }
    return "application/octet-stream";
}

void DocumentImpl::add_content_type_override(const std::string& part_name, 
                                              const std::string& content_type) {
    for (const auto& ct : content_types_) {
        if (!ct.is_default && ct.part_name == part_name) {
            return;
        }
    }
    
    ContentType ct;
    ct.part_name = part_name;
    ct.content_type = content_type;
    ct.is_default = false;
    content_types_.push_back(ct);
}

void DocumentImpl::update_content_types_xml() {
    auto ct_node = tree_.find_or_create_node("[Content_Types].xml", DocxNodeType::XmlFile);
    if (!ct_node->xml_doc) {
        ct_node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    
    ct_node->xml_doc->reset();
    pugi::xml_node types = ct_node->xml_doc->append_child("Types");
    types.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/content-types");
    
    std::set<std::string> added_extensions;
    for (const auto& ct_entry : content_types_) {
        if (ct_entry.is_default && added_extensions.find(ct_entry.extension) == added_extensions.end()) {
            pugi::xml_node def = types.append_child("Default");
            def.append_attribute("Extension").set_value(ct_entry.extension.c_str());
            def.append_attribute("ContentType").set_value(ct_entry.content_type.c_str());
            added_extensions.insert(ct_entry.extension);
        }
    }
    
    for (const auto& ct_entry : content_types_) {
        if (!ct_entry.is_default) {
            pugi::xml_node override = types.append_child("Override");
            override.append_attribute("PartName").set_value(ct_entry.part_name.c_str());
            override.append_attribute("ContentType").set_value(ct_entry.content_type.c_str());
        }
    }
    
    tree_.iterate_files([this, &types](std::shared_ptr<DocxTreeNode> node) {
        if (node->full_path == "[Content_Types].xml") return;
        
        bool found = false;
        std::string part_name = "/" + node->full_path;
        
        for (const auto& ct_entry : content_types_) {
            if (!ct_entry.is_default && ct_entry.part_name == part_name) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::string content_type = "application/xml";
            if (node->full_path.find("word/document.xml") != std::string::npos) {
                content_type = "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml";
            } else if (node->full_path.find("styles.xml") != std::string::npos) {
                content_type = "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml";
            } else if (node->full_path.find("settings.xml") != std::string::npos) {
                content_type = "application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml";
            } else if (node->full_path.find("rels") != std::string::npos) {
                content_type = "application/vnd.openxmlformats-package.relationships+xml";
            } else if (node->type == DocxNodeType::MediaFile) {
                content_type = node->content_type.empty() ? "image/png" : node->content_type;
            }
            
            pugi::xml_node override = types.append_child("Override");
            override.append_attribute("PartName").set_value(part_name.c_str());
            override.append_attribute("ContentType").set_value(content_type.c_str());
        }
    });
}

std::string DocumentImpl::add_relationship(const std::string& rels_path,
                                            const std::string& type,
                                            const std::string& target,
                                            const std::string& target_mode) {
    std::vector<Relationship>& rels = relationships_[rels_path];
    
    int max_id = 0;
    for (const auto& rel : rels) {
        if (rel.id.size() > 3 && rel.id.substr(0, 3) == "rId") {
            try {
                int id_num = std::stoi(rel.id.substr(3));
                max_id = std::max(max_id, id_num);
            } catch (...) {}
        }
    }
    
    std::string new_id = "rId" + std::to_string(max_id + 1);
    
    Relationship rel;
    rel.id = new_id;
    rel.type = type;
    rel.target = target;
    rel.target_mode = target_mode;
    rels.push_back(rel);
    
    modified_parts_.insert(rels_path);
    
    return new_id;
}

void DocumentImpl::remove_relationship(const std::string& rels_path,
                                        const std::string& rel_id) {
    auto it = relationships_.find(rels_path);
    if (it == relationships_.end()) return;
    
    auto& rels = it->second;
    for (auto rit = rels.begin(); rit != rels.end(); ++rit) {
        if (rit->id == rel_id) {
            rels.erase(rit);
            modified_parts_.insert(rels_path);
            return;
        }
    }
}

std::string DocumentImpl::find_relationship_id(const std::string& rels_path,
                                                const std::string& target) const {
    auto it = relationships_.find(rels_path);
    if (it == relationships_.end()) return "";
    
    for (const auto& rel : it->second) {
        if (rel.target == target) {
            return rel.id;
        }
    }
    return "";
}

void DocumentImpl::update_relationships_xml(const std::string& rels_path) {
    auto rels_it = relationships_.find(rels_path);
    if (rels_it == relationships_.end()) return;
    
    auto node = tree_.find_or_create_node(rels_path, DocxNodeType::XmlFile);
    if (!node->xml_doc) {
        node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    
    node->xml_doc->reset();
    pugi::xml_node root = node->xml_doc->append_child("Relationships");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/relationships");
    
    for (const auto& rel : rels_it->second) {
        pugi::xml_node rel_node = root.append_child("Relationship");
        rel_node.append_attribute("Id").set_value(rel.id.c_str());
        rel_node.append_attribute("Type").set_value(rel.type.c_str());
        rel_node.append_attribute("Target").set_value(rel.target.c_str());
        if (!rel.target_mode.empty()) {
            rel_node.append_attribute("TargetMode").set_value(rel.target_mode.c_str());
        }
    }
}

// ============================================================================
// Save Operations
// ============================================================================

bool DocumentImpl::save_to_zip(const std::string& output_path) {
    std::string temp_path = output_path + ".tmp";
    
    ::zip_t* zip = zip_open(temp_path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    if (!zip) return false;
    
    bool success = save_tree_to_zip(zip);
    
    zip_close(zip);
    
    if (!success) {
        std::remove(temp_path.c_str());
        return false;
    }
    
    if (output_path == filepath_ && std::filesystem::exists(filepath_)) {
        std::filesystem::remove(filepath_);
    }
    
    try {
        std::filesystem::rename(temp_path, output_path);
    } catch (...) {
        std::remove(temp_path.c_str());
        return false;
    }
    
    return true;
}

bool DocumentImpl::save_tree_to_zip(::zip_t* zip) {
    bool success = true;
    
    tree_.iterate_files([this, zip, &success](std::shared_ptr<DocxTreeNode> node) {
        if (!success || node->is_deleted) return;
        
        if (!write_tree_node(zip, node)) {
            success = false;
        }
    });
    
    return success;
}

bool DocumentImpl::write_tree_node(::zip_t* zip, std::shared_ptr<DocxTreeNode> node) {
    if (zip_entry_open(zip, node->full_path.c_str()) != 0) {
        return false;
    }
    
    bool write_success = false;
    
    if (node->type == DocxNodeType::XmlFile && node->xml_doc) {
        xml_string_writer writer;
        node->xml_doc->print(writer);
        write_success = (zip_entry_write(zip, writer.result.c_str(), writer.result.length()) == 0);
    } else if (!node->binary_data.empty()) {
        write_success = (zip_entry_write(zip, node->binary_data.data(), node->binary_data.size()) == 0);
    } else {
        write_success = true;
    }
    
    zip_entry_close(zip);
    return write_success;
}

// ============================================================================
// Media Helpers
// ============================================================================

std::string DocumentImpl::get_mime_type(const std::string& filename) const {
    size_t dot_pos = filename.rfind('.');
    if (dot_pos == std::string::npos) return "application/octet-stream";
    
    std::string ext = filename.substr(dot_pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    if (ext == "png") return "image/png";
    if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
    if (ext == "gif") return "image/gif";
    if (ext == "bmp") return "image/bmp";
    if (ext == "tiff" || ext == "tif") return "image/tiff";
    if (ext == "webp") return "image/webp";
    if (ext == "svg") return "image/svg+xml";
    
    return "application/octet-stream";
}

std::string DocumentImpl::get_extension_from_mime(const std::string& mime_type) const {
    if (mime_type == "image/png") return ".png";
    if (mime_type == "image/jpeg") return ".jpg";
    if (mime_type == "image/gif") return ".gif";
    if (mime_type == "image/bmp") return ".bmp";
    if (mime_type == "image/tiff") return ".tiff";
    if (mime_type == "image/webp") return ".webp";
    if (mime_type == "image/svg+xml") return ".svg";
    return "";
}

// ============================================================================
// Create Empty Document
// ============================================================================

bool DocumentImpl::create_empty_document() {
    // Clear any existing data
    tree_.clear();
    xml_parts_cache_.clear();
    media_files_cache_.clear();
    relationships_.clear();
    modified_parts_.clear();
    content_types_.clear();
    
    // Define XML namespaces
    const char* ns_ct = "http://schemas.openxmlformats.org/package/2006/content-types";
    const char* ns_rels = "http://schemas.openxmlformats.org/package/2006/relationships";
    const char* ns_w = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";
    const char* ns_r = "http://schemas.openxmlformats.org/officeDocument/2006/relationships";
    const char* ns_cp = "http://schemas.openxmlformats.org/package/2006/metadata/core-properties";
    const char* ns_dc = "http://purl.org/dc/elements/1.1/";
    const char* ns_dcterms = "http://purl.org/dc/terms/";
    const char* ns_dcmitype = "http://purl.org/dc/dcmitype/";
    const char* ns_xsi = "http://www.w3.org/2001/XMLSchema-instance";
    const char* ns_ep = "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties";
    const char* ns_vt = "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes";
    const char* ns_w14 = "http://schemas.microsoft.com/office/word/2010/wordml";
    const char* ns_mc = "http://schemas.openxmlformats.org/markup-compatibility/2006";
    const char* ns_a = "http://schemas.openxmlformats.org/drawingml/2006/main";
    
    // Helper lambda to create XML part
    auto create_xml_part_impl = [this](const std::string& path) -> pugi::xml_document& {
        auto node = tree_.find_or_create_node(path, DocxNodeType::XmlFile);
        if (!node->xml_doc) {
            node->xml_doc = std::make_shared<pugi::xml_document>();
        }
        node->is_new = true;
        node->is_modified = true;
        modified_parts_.insert(path);
        xml_parts_cache_[path] = node;
        return *node->xml_doc;
    };
    
    // 1. Create [Content_Types].xml
    {
        pugi::xml_document& doc = create_xml_part_impl("[Content_Types].xml");
        pugi::xml_node types = doc.append_child("Types");
        types.append_attribute("xmlns").set_value(ns_ct);
        
        auto add_default = [&types](const char* ext, const char* type) {
            pugi::xml_node def = types.append_child("Default");
            def.append_attribute("Extension").set_value(ext);
            def.append_attribute("ContentType").set_value(type);
        };
        
        auto add_override = [&types](const char* part, const char* type) {
            pugi::xml_node over = types.append_child("Override");
            over.append_attribute("PartName").set_value(part);
            over.append_attribute("ContentType").set_value(type);
        };
        
        add_default("rels", "application/vnd.openxmlformats-package.relationships+xml");
        add_default("xml", "application/xml");
        add_override("/docProps/app.xml", "application/vnd.openxmlformats-officedocument.extended-properties+xml");
        add_override("/docProps/core.xml", "application/vnd.openxmlformats-package.core-properties+xml");
        add_override("/word/document.xml", "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml");
        add_override("/word/fontTable.xml", "application/vnd.openxmlformats-officedocument.wordprocessingml.fontTable+xml");
        add_override("/word/settings.xml", "application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml");
        add_override("/word/styles.xml", "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml");
        add_override("/word/theme/theme1.xml", "application/vnd.openxmlformats-officedocument.theme+xml");
    }
    
    // 2. Create _rels/.rels (package relationships)
    {
        pugi::xml_document& doc = create_xml_part_impl("_rels/.rels");
        pugi::xml_node rels = doc.append_child("Relationships");
        rels.append_attribute("xmlns").set_value(ns_rels);
        
        auto add_rel = [&rels](const char* id, const char* type, const char* target) {
            pugi::xml_node r = rels.append_child("Relationship");
            r.append_attribute("Id").set_value(id);
            r.append_attribute("Type").set_value(type);
            r.append_attribute("Target").set_value(target);
        };
        
        add_rel("rId1", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties", "docProps/app.xml");
        add_rel("rId2", "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties", "docProps/core.xml");
        add_rel("rId3", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/custom-properties", "docProps/custom.xml");
        add_rel("rId4", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument", "word/document.xml");
    }
    
    // 3. Create word/_rels/document.xml.rels
    {
        pugi::xml_document& doc = create_xml_part_impl("word/_rels/document.xml.rels");
        pugi::xml_node rels = doc.append_child("Relationships");
        rels.append_attribute("xmlns").set_value(ns_rels);
        
        auto add_rel = [&rels](const char* id, const char* type, const char* target) {
            pugi::xml_node r = rels.append_child("Relationship");
            r.append_attribute("Id").set_value(id);
            r.append_attribute("Type").set_value(type);
            r.append_attribute("Target").set_value(target);
        };
        
        add_rel("rId1", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles", "styles.xml");
        add_rel("rId2", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/settings", "settings.xml");
        add_rel("rId3", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme", "theme/theme1.xml");
        add_rel("rId4", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/fontTable", "fontTable.xml");
    }
    
    // 4. Create word/document.xml (minimal empty document)
    {
        pugi::xml_document& doc = create_xml_part_impl("word/document.xml");
        pugi::xml_node root = doc.append_child("w:document");
        root.append_attribute("xmlns:w").set_value(ns_w);
        root.append_attribute("xmlns:r").set_value(ns_r);
        root.append_attribute("xmlns:w14").set_value(ns_w14);
        root.append_attribute("xmlns:mc").set_value(ns_mc);
        root.append_attribute("mc:Ignorable").set_value("w14");
        
        pugi::xml_node body = root.append_child("w:body");
        
        // Add empty paragraph (required for valid document)
        pugi::xml_node p = body.append_child("w:p");
        
        // Add section properties
        pugi::xml_node sectPr = body.append_child("w:sectPr");
        pugi::xml_node pgSz = sectPr.append_child("w:pgSz");
        pgSz.append_attribute("w:w").set_value("11906");  // A4 width in twips
        pgSz.append_attribute("w:h").set_value("16838");  // A4 height in twips
        
        pugi::xml_node pgMar = sectPr.append_child("w:pgMar");
        pgMar.append_attribute("w:top").set_value("1440");    // 1 inch
        pgMar.append_attribute("w:right").set_value("1800");  // 1.25 inches
        pgMar.append_attribute("w:bottom").set_value("1440"); // 1 inch
        pgMar.append_attribute("w:left").set_value("1800");   // 1.25 inches
        pgMar.append_attribute("w:header").set_value("851");
        pgMar.append_attribute("w:footer").set_value("992");
        pgMar.append_attribute("w:gutter").set_value("0");
        
        pugi::xml_node cols = sectPr.append_child("w:cols");
        cols.append_attribute("w:space").set_value("425");
        cols.append_attribute("w:num").set_value("1");
        
        pugi::xml_node docGrid = sectPr.append_child("w:docGrid");
        docGrid.append_attribute("w:type").set_value("lines");
        docGrid.append_attribute("w:linePitch").set_value("312");
        docGrid.append_attribute("w:charSpace").set_value("0");
    }
    
    // 5. Create word/styles.xml (minimal styles)
    {
        pugi::xml_document& doc = create_xml_part_impl("word/styles.xml");
        pugi::xml_node styles = doc.append_child("w:styles");
        styles.append_attribute("xmlns:w").set_value(ns_w);
        
        // Add document defaults
        pugi::xml_node docDefaults = styles.append_child("w:docDefaults");
        pugi::xml_node rPrDefault = docDefaults.append_child("w:rPrDefault");
        pugi::xml_node rPr = rPrDefault.append_child("w:rPr");
        pugi::xml_node rFonts = rPr.append_child("w:rFonts");
        rFonts.append_attribute("w:asciiTheme").set_value("minorHAnsi");
        rFonts.append_attribute("w:hAnsiTheme").set_value("minorHAnsi");
        
        // Add Normal style
        pugi::xml_node normal = styles.append_child("w:style");
        normal.append_attribute("w:type").set_value("paragraph");
        normal.append_attribute("w:default").set_value("1");
        normal.append_attribute("w:styleId").set_value("Normal");
        
        pugi::xml_node name = normal.append_child("w:name");
        name.append_attribute("w:val").set_value("Normal");
    }
    
    // 6. Create word/settings.xml (minimal settings)
    {
        pugi::xml_document& doc = create_xml_part_impl("word/settings.xml");
        pugi::xml_node settings = doc.append_child("w:settings");
        settings.append_attribute("xmlns:w").set_value(ns_w);
        
        pugi::xml_node zoom = settings.append_child("w:zoom");
        zoom.append_attribute("w:percent").set_value("100");
        
        pugi::xml_node defaultTabStop = settings.append_child("w:defaultTabStop");
        defaultTabStop.append_attribute("w:val").set_value("420");
        
        pugi::xml_node characterSpacingControl = settings.append_child("w:characterSpacingControl");
        characterSpacingControl.append_attribute("w:val").set_value("doNotCompress");
        
        pugi::xml_node compat = settings.append_child("w:compat");
        pugi::xml_node compatSetting = compat.append_child("w:compatSetting");
        compatSetting.append_attribute("w:name").set_value("compatibilityMode");
        compatSetting.append_attribute("w:uri").set_value("http://schemas.microsoft.com/office/word");
        compatSetting.append_attribute("w:val").set_value("15");
    }
    
    // 7. Create word/fontTable.xml (minimal font table)
    {
        pugi::xml_document& doc = create_xml_part_impl("word/fontTable.xml");
        pugi::xml_node fonts = doc.append_child("w:fonts");
        fonts.append_attribute("xmlns:w").set_value(ns_w);
        
        // Add Times New Roman
        pugi::xml_node font = fonts.append_child("w:font");
        font.append_attribute("w:name").set_value("Times New Roman");
        
        pugi::xml_node panose1 = font.append_child("w:panose1");
        panose1.append_attribute("w:val").set_value("02020603050405020304");
        
        pugi::xml_node charset = font.append_child("w:charset");
        charset.append_attribute("w:val").set_value("00");
        
        pugi::xml_node family = font.append_child("w:family");
        family.append_attribute("w:val").set_value("roman");
        
        pugi::xml_node pitch = font.append_child("w:pitch");
        pitch.append_attribute("w:val").set_value("variable");
    }
    
    // 8. Create word/theme/theme1.xml (minimal theme)
    {
        pugi::xml_document& doc = create_xml_part_impl("word/theme/theme1.xml");
        pugi::xml_node theme = doc.append_child("a:theme");
        theme.append_attribute("xmlns:a").set_value(ns_a);
        theme.append_attribute("name").set_value("Office Theme");
        
        pugi::xml_node themeElements = theme.append_child("a:themeElements");
        
        // Color scheme
        pugi::xml_node clrScheme = themeElements.append_child("a:clrScheme");
        clrScheme.append_attribute("name").set_value("Office");
        
        // Add minimal colors (dk1, lt1)
        pugi::xml_node dk1 = clrScheme.append_child("a:dk1");
        pugi::xml_node sysClr1 = dk1.append_child("a:sysClr");
        sysClr1.append_attribute("val").set_value("windowText");
        sysClr1.append_attribute("lastClr").set_value("000000");
        
        pugi::xml_node lt1 = clrScheme.append_child("a:lt1");
        pugi::xml_node sysClr2 = lt1.append_child("a:sysClr");
        sysClr2.append_attribute("val").set_value("window");
        sysClr2.append_attribute("lastClr").set_value("FFFFFF");
        
        // Font scheme
        pugi::xml_node fontScheme = themeElements.append_child("a:fontScheme");
        fontScheme.append_attribute("name").set_value("Office");
        
        pugi::xml_node majorFont = fontScheme.append_child("a:majorFont");
        pugi::xml_node latin = majorFont.append_child("a:latin");
        latin.append_attribute("typeface").set_value("Calibri Light");
        
        pugi::xml_node minorFont = fontScheme.append_child("a:minorFont");
        pugi::xml_node latin2 = minorFont.append_child("a:latin");
        latin2.append_attribute("typeface").set_value("Calibri");
    }
    
    // 9. Create docProps/core.xml (core properties)
    {
        pugi::xml_document& doc = create_xml_part_impl("docProps/core.xml");
        pugi::xml_node core = doc.append_child("cp:coreProperties");
        core.append_attribute("xmlns:cp").set_value(ns_cp);
        core.append_attribute("xmlns:dc").set_value(ns_dc);
        core.append_attribute("xmlns:dcterms").set_value(ns_dcterms);
        core.append_attribute("xmlns:dcmitype").set_value(ns_dcmitype);
        core.append_attribute("xmlns:xsi").set_value(ns_xsi);
        
        pugi::xml_node creator = core.append_child("dc:creator");
        creator.text().set("CDocx Library");
        
        pugi::xml_node lastModifiedBy = core.append_child("cp:lastModifiedBy");
        lastModifiedBy.text().set("CDocx Library");
        
        pugi::xml_node revision = core.append_child("cp:revision");
        revision.text().set("1");
        
        // Add created time (current time)
        auto now = std::time(nullptr);
        struct std::tm tm;
#ifdef _WIN32
        gmtime_s(&tm, &now);
#else
        gmtime_r(&now, &tm);
#endif
        char time_str[32];
        std::strftime(time_str, sizeof(time_str), "%Y-%m-%dT%H:%M:%SZ", &tm);
        
        pugi::xml_node created = core.append_child("dcterms:created");
        created.append_attribute("xsi:type").set_value("dcterms:W3CDTF");
        created.text().set(time_str);
        
        pugi::xml_node modified = core.append_child("dcterms:modified");
        modified.append_attribute("xsi:type").set_value("dcterms:W3CDTF");
        modified.text().set(time_str);
    }
    
    // 10. Create docProps/app.xml (extended properties)
    {
        pugi::xml_document& doc = create_xml_part_impl("docProps/app.xml");
        pugi::xml_node props = doc.append_child("Properties");
        props.append_attribute("xmlns").set_value(ns_ep);
        props.append_attribute("xmlns:vt").set_value(ns_vt);
        
        pugi::xml_node template_node = props.append_child("Template");
        template_node.text().set("Normal.dotm");
        
        pugi::xml_node pages = props.append_child("Pages");
        pages.text().set("1");
        
        pugi::xml_node words = props.append_child("Words");
        words.text().set("0");
        
        pugi::xml_node characters = props.append_child("Characters");
        characters.text().set("0");
        
        pugi::xml_node app = props.append_child("Application");
        app.text().set("CDocx Library");
        
        pugi::xml_node docSecurity = props.append_child("DocSecurity");
        docSecurity.text().set("0");
    }
    
    // 11. Create docProps/custom.xml (custom properties - minimal)
    {
        pugi::xml_document& doc = create_xml_part_impl("docProps/custom.xml");
        pugi::xml_node props = doc.append_child("Properties");
        props.append_attribute("xmlns").set_value("http://schemas.openxmlformats.org/officeDocument/2006/custom-properties");
        props.append_attribute("xmlns:vt").set_value(ns_vt);
    }
    
    // Build relationship caches
    load_all_relationships();
    
    // Build content types cache
    load_content_types();
    
    return true;
}

} // namespace cdocx
