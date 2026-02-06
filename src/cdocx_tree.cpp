// CDocx - Tree Structure Implementation
// This file implements the DocxTree and DocxTreeNode classes

#include "detail/cdocx_impl.h"
#include <algorithm>
#include <cstring>
#include <stack>

namespace cdocx {

// ============================================================================
// DocxTreeNode Implementation
// ============================================================================

std::shared_ptr<DocxTreeNode> DocxTreeNode::add_directory(const std::string& dir_name) {
    auto child = std::make_shared<DocxTreeNode>(dir_name, DocxNodeType::Directory, this);
    child->full_path = full_path.empty() ? dir_name : full_path + "/" + dir_name;
    children.push_back(child);
    return child;
}

std::shared_ptr<DocxTreeNode> DocxTreeNode::add_file(const std::string& file_name, 
                                                      DocxNodeType file_type) {
    auto child = std::make_shared<DocxTreeNode>(file_name, file_type, this);
    child->full_path = full_path.empty() ? file_name : full_path + "/" + file_name;
    children.push_back(child);
    return child;
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
    if (existing && existing->is_directory()) {
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

std::shared_ptr<DocxTreeNode> DocxTree::find_node(const std::string& path) const {
    // Fast lookup using path map
    auto it = path_map_.find(path);
    if (it != path_map_.end()) {
        return it->second.lock();
    }
    return nullptr;
}

std::shared_ptr<DocxTreeNode> DocxTree::find_or_create_node(const std::string& path, 
                                                             DocxNodeType type) {
    // Check if already exists
    auto existing = find_node(path);
    if (existing) {
        return existing;
    }
    
    // Parse path and create intermediate directories
    std::shared_ptr<DocxTreeNode> current = root_;
    std::string current_path;
    
    size_t start = 0;
    size_t end = path.find('/');
    
    while (end != std::string::npos) {
        std::string dir_name = path.substr(start, end - start);
        if (!dir_name.empty()) {
            current_path = current_path.empty() ? dir_name : current_path + "/" + dir_name;
            
            auto child = current->find_child(dir_name);
            if (!child) {
                child = current->add_directory(dir_name);
                child->full_path = current_path;
                path_map_[current_path] = child;
            }
            current = child;
        }
        start = end + 1;
        end = path.find('/', start);
    }
    
    // Create final node
    std::string file_name = path.substr(start);
    if (!file_name.empty()) {
        auto child = current->add_file(file_name, type);
        child->full_path = path;
        path_map_[path] = child;
        return child;
    }
    
    return current;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_zip_entry(const std::string& entry_path,
                                                       const std::vector<uint8_t>& data) {
    // Determine node type based on path
    DocxNodeType type = DocxNodeType::BinaryFile;
    
    if (entry_path.size() > 4 && entry_path.substr(entry_path.size() - 4) == ".xml") {
        type = DocxNodeType::XmlFile;
    } else if (entry_path.size() > 5 && entry_path.substr(entry_path.size() - 5) == ".rels") {
        type = DocxNodeType::XmlFile;
    } else if (entry_path.substr(0, 11) == "word/media/") {
        type = DocxNodeType::MediaFile;
    }
    
    // Create or get node
    auto node = find_or_create_node(entry_path, type);
    if (!node) return nullptr;
    
    // Store data based on type
    if (type == DocxNodeType::XmlFile) {
        // Try to parse as XML
        auto xml_doc = std::make_shared<pugi::xml_document>();
        pugi::xml_parse_result result = xml_doc->load_buffer(data.data(), data.size());
        if (result) {
            node->xml_doc = std::move(xml_doc);
            node->binary_data = data;  // Also keep original data
        } else {
            // Store as binary if parsing fails
            node->type = DocxNodeType::BinaryFile;
            node->binary_data = data;
        }
    } else {
        node->binary_data = data;
    }
    
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_xml_file(const std::string& path,
                                                       pugi::xml_document&& doc) {
    auto node = find_or_create_node(path, DocxNodeType::XmlFile);
    if (!node) return nullptr;
    
    node->xml_doc = std::make_shared<pugi::xml_document>();
    // Copy the document
    for (pugi::xml_node child = doc.first_child(); child; child = child.next_sibling()) {
        node->xml_doc->append_copy(child);
    }
    
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_media_file(const std::string& path,
                                                        const std::vector<uint8_t>& data,
                                                        const std::string& content_type) {
    auto node = find_or_create_node(path, DocxNodeType::MediaFile);
    if (!node) return nullptr;
    
    node->binary_data = data;
    node->content_type = content_type;
    
    return node;
}

bool DocxTree::remove_node(const std::string& path) {
    auto node = find_node(path);
    if (!node) return false;
    
    node->is_deleted = true;
    return true;
}

void DocxTree::iterate_files(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const {
    std::stack<std::shared_ptr<DocxTreeNode>> stack;
    stack.push(root_);
    
    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        
        if (node->is_file()) {
            callback(node);
        }
        
        for (const auto& child : node->children) {
            stack.push(child);
        }
    }
}

void DocxTree::iterate_all(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const {
    std::stack<std::shared_ptr<DocxTreeNode>> stack;
    stack.push(root_);
    
    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        
        callback(node);
        
        for (const auto& child : node->children) {
            stack.push(child);
        }
    }
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
    path_map_.clear();
    iterate_all([this](std::shared_ptr<DocxTreeNode> node) {
        if (!node->full_path.empty()) {
            path_map_[node->full_path] = node;
        }
    });
}

void DocxTree::clear() {
    root_->children.clear();
    path_map_.clear();
}

} // namespace cdocx
