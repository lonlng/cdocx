/**
 * @file tree.cpp
 * @brief DocxTree and DocxTreeNode implementation
 * @details Implementation of the tree structure for managing DOCX package
 *          contents. Provides file/directory organization mirroring ZIP structure.
 *          Optimized version with lazy loading and parallel processing support.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 */

#include <detail/impl.h>

#include <algorithm>
#include <cstring>
#include <execution>
#include <fstream>
#include <iostream>
#include <thread>

extern "C" {
#include <zip.h>
}

// Platform-specific includes for memory mapping
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#endif

namespace cdocx {

// ============================================================================
// FileDataStorage Implementation
// ============================================================================

void FileDataStorage::set_lazy_load_info(zip_t* zip, int index, 
                                          const std::string& name, size_t size) {
    lazy_info_ = LazyLoadInfo{zip, index, name, size};
    storage_type_ = StorageType::NotLoaded;
    data_size_ = size;
}

bool FileDataStorage::ensure_loaded(const LoadConfig& config) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    if (storage_type_ != StorageType::NotLoaded || !lazy_info_) {
        return true;  // Already loaded or not lazy
    }
    
    if (!lazy_info_->zip_handle || lazy_info_->entry_index < 0) {
        return false;  // Cannot load
    }
    
    // Open entry
    if (zip_entry_openbyindex(lazy_info_->zip_handle, lazy_info_->entry_index) != 0) {
        return false;
    }
    
    // Read data
    void* data = nullptr;
    size_t size = 0;
    if (zip_entry_read(lazy_info_->zip_handle, &data, &size) != 0 || !data) {
        zip_entry_close(lazy_info_->zip_handle);
        return false;
    }
    
    std::vector<uint8_t> buffer(size);
    std::memcpy(buffer.data(), data, size);
    free(data);
    zip_entry_close(lazy_info_->zip_handle);
    
    // Select storage type based on size and config
    if (size > config.temp_file_threshold) {
        // Store in temp file
        auto temp_path = std::filesystem::temp_directory_path() / 
                        ("cdocx_" + std::to_string(std::hash<std::string>{}(lazy_info_->entry_name)));
        std::ofstream ofs(temp_path, std::ios::binary);
        if (ofs) {
            ofs.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
            store_temp_file(temp_path, size);
        } else {
            store_in_memory(std::move(buffer));
        }
    } else if (size > config.mmap_threshold && config.enable_lazy_loading) {
        // Could implement memory mapping here
        store_in_memory(std::move(buffer));
    } else {
        store_in_memory(std::move(buffer));
    }
    
    lazy_info_.reset();
    return true;
}

void FileDataStorage::store_in_memory(std::vector<uint8_t>&& data) {
    data_ = std::move(data);
    storage_type_ = StorageType::Memory;
    data_size_ = std::get<std::vector<uint8_t>>(data_).size();
    original_size_ = data_size_;
}

void FileDataStorage::store_memory_mapped(const std::string& path, size_t size) {
    // Platform-specific implementation would go here
    // For now, fall back to memory storage
    storage_type_ = StorageType::MemoryMapped;
    data_size_ = size;
    original_size_ = size;
}

void FileDataStorage::store_temp_file(const std::filesystem::path& path, size_t size) {
    data_ = path;
    storage_type_ = StorageType::TempFile;
    data_size_ = size;
    original_size_ = size;
}

void FileDataStorage::store_compressed(std::vector<uint8_t>&& data, size_t original_size) {
    data_ = std::make_pair(std::move(data), original_size);
    storage_type_ = StorageType::Compressed;
    data_size_ = std::get<std::pair<std::vector<uint8_t>, size_t>>(data_).first.size();
    original_size_ = original_size;
}

std::vector<uint8_t> FileDataStorage::get_data() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    
    switch (storage_type_) {
        case StorageType::Memory:
            return std::get<std::vector<uint8_t>>(data_);
            
        case StorageType::TempFile: {
            const auto& path = std::get<std::filesystem::path>(data_);
            std::ifstream ifs(path, std::ios::binary | std::ios::ate);
            if (!ifs) return {};
            auto size = ifs.tellg();
            ifs.seekg(0, std::ios::beg);
            std::vector<uint8_t> buffer(size);
            ifs.read(reinterpret_cast<char*>(buffer.data()), size);
            return buffer;
        }
        
        case StorageType::Compressed:
            return decompress_data(std::get<std::pair<std::vector<uint8_t>, size_t>>(data_).first,
                                  std::get<std::pair<std::vector<uint8_t>, size_t>>(data_).second);
            
        default:
            return {};
    }
}

const std::vector<uint8_t>* FileDataStorage::get_memory_data() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    
    if (storage_type_ == StorageType::Memory) {
        return &std::get<std::vector<uint8_t>>(data_);
    }
    return nullptr;
}

void FileDataStorage::unload() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    if (storage_type_ == StorageType::TempFile) {
        // Delete temp file
        auto& path = std::get<std::filesystem::path>(data_);
        std::error_code ec;
        std::filesystem::remove(path, ec);
    }
    
    data_ = std::monostate{};
    storage_type_ = StorageType::NotLoaded;
    data_size_ = 0;
}

std::vector<uint8_t> FileDataStorage::compress_data(const std::vector<uint8_t>& data) {
    // Simple RLE compression for demonstration
    // In production, use zlib or similar
    std::vector<uint8_t> compressed;
    compressed.reserve(data.size());
    
    for (size_t i = 0; i < data.size(); ) {
        uint8_t count = 1;
        while (i + count < data.size() && count < 255 && data[i] == data[i + count]) {
            count++;
        }
        if (count > 2) {
            compressed.push_back(0);  // RLE marker
            compressed.push_back(data[i]);
            compressed.push_back(count);
            i += count;
        } else {
            compressed.push_back(data[i]);
            i++;
        }
    }
    
    return compressed.size() < data.size() ? compressed : data;
}

std::vector<uint8_t> FileDataStorage::decompress_data(const std::vector<uint8_t>& data, 
                                                       size_t original_size) {
    std::vector<uint8_t> decompressed;
    decompressed.reserve(original_size);
    
    for (size_t i = 0; i < data.size(); ) {
        if (data[i] == 0 && i + 2 < data.size()) {
            uint8_t value = data[i + 1];
            uint8_t count = data[i + 2];
            decompressed.insert(decompressed.end(), count, value);
            i += 3;
        } else {
            decompressed.push_back(data[i]);
            i++;
        }
    }
    
    return decompressed;
}

// ============================================================================
// LRUCache Implementation
// ============================================================================

std::shared_ptr<DocxTreeNode> LRUCache::touch(const std::string& path) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    auto it = cache_.find(path);
    if (it == cache_.end()) {
        return nullptr;
    }
    
    // Move to front
    lru_list_.erase(it->second.second);
    lru_list_.push_front(path);
    it->second.second = lru_list_.begin();
    
    return it->second.first;
}

void LRUCache::add(const std::string& path, std::shared_ptr<DocxTreeNode> node, 
                   size_t estimated_mb) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    // Remove if already exists
    auto it = cache_.find(path);
    if (it != cache_.end()) {
        lru_list_.erase(it->second.second);
        cache_.erase(it);
        current_size_--;
    }
    
    // Add to front
    lru_list_.push_front(path);
    cache_[path] = {node, lru_list_.begin()};
    current_size_++;
    current_memory_mb_ += estimated_mb;
    
    lock.unlock();
    evict_if_needed();
}

void LRUCache::remove(const std::string& path) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    auto it = cache_.find(path);
    if (it != cache_.end()) {
        lru_list_.erase(it->second.second);
        cache_.erase(it);
        current_size_--;
    }
}

void LRUCache::evict_if_needed() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    while ((current_size_ > max_size_ || current_memory_mb_ > max_memory_mb_) && 
           !lru_list_.empty()) {
        // Evict least recently used
        auto last = lru_list_.back();
        auto it = cache_.find(last);
        if (it != cache_.end()) {
            auto node = it->second.first;
            // Serialize XML and free memory
            if (node->xml_doc && node->type == DocxNodeType::XmlFile) {
                // Store serialized version in file_storage
                auto data = node->serialize_xml_to_binary();
                node->file_storage.store_in_memory(std::move(data));
                node->xml_doc.reset();
            }
            cache_.erase(it);
            current_size_--;
        }
        lru_list_.pop_back();
    }
}

void LRUCache::clear() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    cache_.clear();
    lru_list_.clear();
    current_size_ = 0;
    current_memory_mb_ = 0;
}

// ============================================================================
// DocxTreeNode Implementation
// ============================================================================

std::vector<uint8_t> DocxTreeNode::serialize_xml_to_binary() const {
    if (!xml_doc) {
        return {};
    }
    
    xml_string_writer writer;
    xml_doc->save(writer, "  ");
    
    // Ensure standardized XML declaration format
    std::string xml_output = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
    
    if (writer.result.find("<?xml") == 0) {
        // Skip existing declaration and add rest of content
        size_t decl_end = writer.result.find("?>");
        if (decl_end != std::string::npos) {
            // Skip declaration and any following whitespace/newline
            size_t content_start = decl_end + 2;
            while (content_start < writer.result.size() && 
                   (writer.result[content_start] == '\n' || writer.result[content_start] == '\r')) {
                content_start++;
            }
            xml_output += writer.result.substr(content_start);
        } else {
            xml_output += writer.result;
        }
    } else {
        // Add original content as-is
        xml_output += writer.result;
    }
    
    std::vector<uint8_t> result(xml_output.size());
    std::memcpy(result.data(), xml_output.data(), xml_output.size());
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
    // Check if already exists
    auto existing = find_child(dir_name);
    if (existing) {
        return existing;
    }
    
    // Create new directory node
    auto node = std::make_shared<DocxTreeNode>(dir_name, DocxNodeType::Directory, this);
    children.push_back(node);
    return node;
}

std::shared_ptr<DocxTreeNode> DocxTreeNode::add_file(const std::string& file_name,
                                                      DocxNodeType file_type) {
    // Check if already exists
    auto existing = find_child(file_name);
    if (existing) {
        return existing;
    }
    
    // Build full path
    std::string full_path = name.empty() ? file_name : this->full_path + "/" + file_name;
    
    // Create new file node
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
    // Create root node with empty name
    root_ = std::make_shared<DocxTreeNode>("", DocxNodeType::Root, nullptr);
    root_->full_path = "";
    
    // Initialize LRU cache with defaults
    xml_cache_ = std::make_unique<LRUCache>(20, 100);
}

DocxTree::~DocxTree() {
    if (owns_zip_handle_ && zip_handle_) {
        zip_close(zip_handle_);
    }
}

void DocxTree::set_zip_handle(zip_t* handle, bool owns) {
    zip_handle_ = handle;
    owns_zip_handle_ = owns;
}

bool DocxTree::is_critical_part(const std::string& path) const {
    // Critical parts that should not be lazy loaded
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

StorageType DocxTree::select_storage_type(size_t file_size) const {
    if (!config_.enable_lazy_loading) {
        return StorageType::Memory;
    }
    
    if (file_size > config_.temp_file_threshold) {
        return StorageType::TempFile;
    } else if (file_size > config_.mmap_threshold) {
        return StorageType::MemoryMapped;
    }
    return StorageType::Memory;
}

std::shared_ptr<DocxTreeNode> DocxTree::find_node(const std::string& path) const {
    // Try path map first for O(1) lookup
    {
        std::shared_lock<std::shared_mutex> lock(path_map_mutex_);
        auto it = path_map_.find(path);
        if (it != path_map_.end()) {
            auto node = it->second.lock();
            if (node && !node->is_deleted) {
                // Touch LRU cache if XML file
                if (config_.enable_lru_cache && node->type == DocxNodeType::XmlFile) {
                    const_cast<LRUCache*>(xml_cache_.get())->touch(path);
                }
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
    // Check if already exists
    auto existing = find_node(path);
    if (existing) {
        return existing;
    }
    
    // Split path into components
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = path.find('/');
    
    while (end != std::string::npos) {
        parts.push_back(path.substr(start, end - start));
        start = end + 1;
        end = path.find('/', start);
    }
    parts.push_back(path.substr(start));
    
    // Create directory structure
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
            // Last part - create file node
            auto node = current->add_file(part, type);
            node->full_path = current_path;
            node->is_critical = is_critical_part(current_path);
            
            std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
            path_map_[current_path] = node;
            return node;
        } else {
            // Intermediate directory
            current = current->find_or_create_directory(part);
            current->full_path = current_path;
            
            std::unique_lock<std::shared_mutex> lock(path_map_mutex_);
            path_map_[current_path] = current;
        }
    }
    
    return nullptr;
}

std::shared_ptr<DocxTreeNode> DocxTree::add_zip_entry(const std::string& entry_path,
                                                       const std::vector<uint8_t>& data,
                                                       int entry_index,
                                                       size_t entry_size) {
    // Determine file type from extension
    DocxNodeType type = DocxNodeType::BinaryFile;
    
    if (entry_path.find("word/media/") != std::string::npos) {
        type = DocxNodeType::MediaFile;
    } else if (entry_path.size() > 4) {
        // Check for .xml extension
        if (entry_path.size() > 4 && entry_path.substr(entry_path.size() - 4) == ".xml") {
            type = DocxNodeType::XmlFile;
        }
        // Check for .rels extension (relationships files)
        else if (entry_path.size() > 5 && entry_path.substr(entry_path.size() - 5) == ".rels") {
            type = DocxNodeType::XmlFile;
        }
    }
    
    // Create node
    auto node = find_or_create_node(entry_path, type);
    if (!node) {
        return nullptr;
    }
    
    // Determine if we should lazy load
    bool should_lazy_load = config_.enable_lazy_loading &&
                           !is_critical_part(entry_path) &&
                           ((type == DocxNodeType::MediaFile && config_.lazy_load_media) ||
                            (type == DocxNodeType::XmlFile && config_.lazy_load_xml));
    
    if (should_lazy_load && entry_index >= 0) {
        // Set up lazy loading
        node->file_storage.set_lazy_load_info(zip_handle_, entry_index, entry_path, entry_size);
    } else if (!data.empty()) {
        // Store data immediately
        if (type == DocxNodeType::XmlFile) {
            // Pre-allocate if enabled
            if (config_.enable_xml_prealloc && data.size() > 1024) {
                size_t estimated_nodes = data.size() / 100;  // Rough estimate
                // pugixml doesn't expose pre-allocation API, but we can hint
            }
            
            // Parse XML
            node->xml_doc = std::make_shared<pugi::xml_document>();
            pugi::xml_parse_result result = node->xml_doc->load_buffer(
                data.data(), data.size(), pugi::parse_default, pugi::encoding_utf8);
            if (!result) {
                return nullptr;
            }
        } else {
            // Store binary data
            auto storage_type = select_storage_type(data.size());
            switch (storage_type) {
                case StorageType::TempFile: {
                    auto temp_path = std::filesystem::temp_directory_path() / 
                                    ("cdocx_" + std::to_string(std::hash<std::string>{}(entry_path)));
                    std::ofstream ofs(temp_path, std::ios::binary);
                    if (ofs) {
                        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
                        node->file_storage.store_temp_file(temp_path, data.size());
                    } else {
                        auto data_copy = data;
                        node->file_storage.store_in_memory(std::move(data_copy));
                    }
                    break;
                }
                default:
                    auto data_copy = data;
                    node->file_storage.store_in_memory(std::move(data_copy));
                    break;
            }
        }
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
    // Move document content
    for (pugi::xml_node child = doc.first_child(); child; child = child.next_sibling()) {
        node->xml_doc->append_copy(child);
    }
    
    // Add to LRU cache
    if (config_.enable_lru_cache) {
        size_t estimated_size = node->serialize_xml_to_binary().size() / (1024 * 1024);
        xml_cache_->add(path, node, (std::max)(size_t(1), estimated_size));
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
    xml_cache_->remove(path);
    
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
    xml_cache_->clear();
    root_->children.clear();
}

bool DocxTree::preload_all() {
    bool all_success = true;
    iterate_files([this, &all_success](std::shared_ptr<DocxTreeNode> node) {
        if (!node->file_storage.ensure_loaded(config_)) {
            all_success = false;
        }
    });
    return all_success;
}

size_t DocxTree::unload_non_critical() {
    size_t unloaded = 0;
    iterate_files([this, &unloaded](std::shared_ptr<DocxTreeNode> node) {
        if (!node->is_critical && node->file_storage.get_storage_type() == StorageType::Memory) {
            // Serialize XML if needed
            if (node->type == DocxNodeType::XmlFile && node->xml_doc) {
                auto data = node->serialize_xml_to_binary();
                node->file_storage.store_in_memory(std::move(data));
                node->xml_doc.reset();
            }
            node->file_storage.unload();
            unloaded++;
        }
    });
    return unloaded;
}

} // namespace cdocx
