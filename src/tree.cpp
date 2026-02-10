/**
 * @file tree.cpp
 * @brief DocxTree and DocxTreeNode implementation
 * @details Implementation of the tree structure for managing DOCX package
 *          contents. Provides file/directory organization mirroring ZIP structure.
 *          Simplified version - all data stored directly in memory.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.4.0
 */

#include <detail/impl.h>

#include <algorithm>
#include <cstring>
#include <fstream>

namespace cdocx {

// ============================================================================
// DocxTreeNode Implementation
// ============================================================================

std::vector<uint8_t> DocxTreeNode::serialize_xml_to_binary() const {
    if (!xml_doc) {
        return {};
    }
    
    xml_string_writer writer;
    xml_doc->save(writer, "  ");
    
    std::vector<uint8_t> result(writer.result.size());
    std::memcpy(result.data(), writer.result.data(), writer.result.size());
    return result;
}

void DocxTreeNode::set_binary_data(std::vector<uint8_t>&& data) {
    if (type == DocxNodeType::XmlFile && xml_doc) {
        // Parse new XML data
        auto new_doc = std::make_shared<pugi::xml_document>();
        auto result = new_doc->load_buffer(data.data(), data.size(), 
                                           pugi::parse_default, pugi::encoding_utf8);
        if (result) {
            xml_doc = std::move(new_doc);
        }
    } else {
        file_storage.store_in_memory(std::move(data));
    }
    is_modified = true;
}

std::shared_ptr<DocxTreeNode> DocxTreeNode::add_directory(const std::string& dir_name) {
    auto existing = find_child(dir_name);
    if (existing) {
        return existing;
    }
    
    auto node = std::make_shared<DocxTreeNode>(dir_name, DocxNodeType::Directory, this);
    children.push_back(node);
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTreeNode::add_file(const std::string& file_name,
                                                      DocxNodeType file_type) {
    auto existing = find_child(file_name);
    if (existing) {
        return existing;
    }
    
    std::string full_path = name.empty() ? file_name : this->full_path + "/" + file_name;
    
    auto node = std::make_shared<DocxTreeNode>(file_name, file_type, this);
    node->full_path = full_path;
    children.push_back(node);
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTreeNode::find_child(const std::string& child_name) const {
    for (const auto& child : children) {
        if (child->name == child_name) {
            return child;
        }
    }
    return nullptr;
}

std::shared_ptr<DocxTreeNode> DocxTreeNode::find_or_create_directory(const std::string& dir_name) {
    auto existing = find_child(dir_name);
    if (existing) {
        return existing;
    }
    return add_directory(dir_name);
}

// ============================================================================
// DocxTree Implementation
// ============================================================================

DocxTree::DocxTree() {
    root_ = std::make_shared<DocxTreeNode>("", DocxNodeType::Root, nullptr);
    root_->full_path = "";
}

DocxTree::~DocxTree() = default;

bool DocxTree::is_critical_part(const std::string& path) const {
    static const std::set<std::string> critical_parts = {
        "[Content_Types].xml",
        "_rels/.rels",
        "word/_rels/document.xml.rels",
        "word/document.xml",
        "word/styles.xml",
        "word/settings.xml"
    };
    return critical_parts.find(path) != critical_parts.end();
}

std::shared_ptr<DocxTreeNode> DocxTree::find_node(const std::string& path) const {
    // Try path map first for O(1) lookup
    {
        std::shared_lock<std::shared_mutex> lock(path_map_mutex_);
        auto it = path_map_.find(path);
        if (it != path_map_.end()) {
            auto node = it->second.lock();
            if (node && !node->is_deleted) {
                return node;
            }
        }
    }
    
    // Fall back to tree traversal
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = path.find('/');
    
    while (end != std::string::npos) {
        parts.push_back(path.substr(start, end - start));
        start = end + 1;
        end = path.find('/', start);
    }
    parts.push_back(path.substr(start));
    
    auto current = root_;
    for (const auto& part : parts) {
        if (part.empty()) continue;
        
        current = current->find_child(part);
        if (!current) {
            return nullptr;
        }
    }
    
    return current && !current->is_deleted ? current : nullptr;
}

std::shared_ptr<DocxTreeNode> DocxTree::find_or_create_node(const std::string& path,
                                                             DocxNodeType type) {
    auto existing = find_node(path);
    if (existing) {
        return existing;
    }
    
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = path.find('/');
    
    while (end != std::string::npos) {
        parts.push_back(path.substr(start, end - start));
        start = end + 1;
        end = path.find('/', start);
    }
    parts.push_back(path.substr(start));
    
    auto current = root_;
    std::string current_path;
    
    for (size_t i = 0; i < parts.size(); ++i) {
        const auto& part = parts[i];
        if (part.empty()) continue;
        
        if (!current_path.empty()) {
            current_path += "/";
        }
        current_path += part;
        
        if (i == parts.size() - 1) {
            auto node = current->add_file(part, type);
            node->full_path = current_path;
            node->is_critical = is_critical_part(current_path);
            
            std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
            path_map_[current_path] = node;
            return node;
        } else {
            current = current->find_or_create_directory(part);
            current->full_path = current_path;
            
            std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
            path_map_[current_path] = current;
        }
    }
    
    return nullptr;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_zip_entry(const std::string& entry_path,
                                                       const std::vector<uint8_t>& data) {
    // Determine file type from extension
    DocxNodeType type = DocxNodeType::BinaryFile;
    
    if (entry_path.find("word/media/") != std::string::npos) {
        type = DocxNodeType::MediaFile;
    } else if (entry_path.size() > 4) {
        if (entry_path.substr(entry_path.size() - 4) == ".xml") {
            type = DocxNodeType::XmlFile;
        } else if (entry_path.size() > 5 && entry_path.substr(entry_path.size() - 5) == ".rels") {
            type = DocxNodeType::XmlFile;
        }
    }
    
    // Create node
    auto node = find_or_create_node(entry_path, type);
    if (!node) {
        return nullptr;
    }
    
    // Store data immediately
    if (type == DocxNodeType::XmlFile) {
        node->xml_doc = std::make_shared<pugi::xml_document>();
        pugi::xml_parse_result result = node->xml_doc->load_buffer(
            data.data(), data.size(), pugi::parse_full, pugi::encoding_utf8);
        
        if (!result) {
            return nullptr;
        }
    } else {
        auto data_copy = data;
        node->file_storage.store_in_memory(std::move(data_copy));
    }
    
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_xml_file(const std::string& path,
                                                      pugi::xml_document&& doc) {
    auto node = find_or_create_node(path, DocxNodeType::XmlFile);
    if (!node) {
        return nullptr;
    }
    
    node->xml_doc = std::make_shared<pugi::xml_document>();
    for (pugi::xml_node child = doc.first_child(); child; child = child.next_sibling()) {
        node->xml_doc->append_copy(child);
    }
    
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_media_file(const std::string& path,
                                                        const std::vector<uint8_t>& data,
                                                        const std::string& content_type) {
    auto node = find_or_create_node(path, DocxNodeType::MediaFile);
    if (!node) {
        return nullptr;
    }
    
    auto data_copy = data;
    node->file_storage.store_in_memory(std::move(data_copy));
    node->content_type = content_type;
    
    return node;
}

bool DocxTree::remove_node(const std::string& path) {
    auto node = find_node(path);
    if (!node) {
        return false;
    }
    
    node->is_deleted = true;
    
    std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
    path_map_.erase(path);
    
    return true;
}

void DocxTree::iterate_files(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const {
    std::function<void(std::shared_ptr<DocxTreeNode>)> traverse;
    traverse = [&traverse, &callback](std::shared_ptr<DocxTreeNode> node) {
        if (!node || node->is_deleted) return;
        
        if (node->is_file()) {
            callback(node);
        }
        
        for (const auto& child : node->children) {
            traverse(child);
        }
    };
    
    traverse(root_);
}

void DocxTree::iterate_all(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const {
    std::function<void(std::shared_ptr<DocxTreeNode>)> traverse;
    traverse = [&traverse, &callback](std::shared_ptr<DocxTreeNode> node) {
        if (!node || node->is_deleted) return;
        
        callback(node);
        
        for (const auto& child : node->children) {
            traverse(child);
        }
    };
    
    traverse(root_);
}

std::vector<std::shared_ptr<DocxTreeNode>> DocxTree::get_all_xml_files() const {
    std::vector<std::shared_ptr<DocxTreeNode>> result;
    iterate_files([&result](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::XmlFile) {
            result.push_back(node);
        }
    });
    return result;
}

std::vector<std::shared_ptr<DocxTreeNode>> DocxTree::get_all_media_files() const {
    std::vector<std::shared_ptr<DocxTreeNode>> result;
    iterate_files([&result](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::MediaFile) {
            result.push_back(node);
        }
    });
    return result;
}

void DocxTree::rebuild_path_map() {
    std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
    path_map_.clear();
    
    iterate_all([this](std::shared_ptr<DocxTreeNode> node) {
        if (!node->full_path.empty()) {
            path_map_[node->full_path] = node;
        }
    });
}

void DocxTree::clear() {
    {
        std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
        path_map_.clear();
    }
    root_->children.clear();
}

} // namespace cdocx
