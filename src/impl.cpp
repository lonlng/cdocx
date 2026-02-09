/**
 * @file impl.cpp
 * @brief DocumentImpl class implementation
 * @details Private implementation details for the Document class.
 *          Handles ZIP operations, XML parsing, and document structure.
 *          Optimized version with parallel loading and progress tracking.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 */

#include <detail/impl.h>

#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>

// ZIP library
extern "C" {
#include <zip.h>
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
// Progress Reporting
// ============================================================================

void DocumentImpl::report_progress(int percent, const std::string& current_file) {
    if (load_config_.progress_callback) {
        load_config_.progress_callback(percent, current_file);
    }
}

// ============================================================================
// Tree Loading - Optimized with Parallel Processing
// ============================================================================

bool DocumentImpl::load_tree_from_zip() {
    auto result = load_tree_with_result();
    return result.success;
}

LoadResult DocumentImpl::load_tree_with_result() {
    LoadResult result;
    LoadStatistics stats;
    stats.start_time = std::chrono::high_resolution_clock::now();
    
    if (!zip_handle_) {
        result.success = false;
        result.errors.emplace_back(LoadErrorType::ZipOpenFailed, "", "ZIP handle is null");
        result.integrity = DocumentIntegrity::Corrupted;
        return result;
    }
    
    // Set configuration for tree
    tree_.set_config(load_config_);
    tree_.set_zip_handle(zip_handle_, false);  // We own the handle, not the tree
    
    tree_.clear();
    
    // Get total entries
    int total_entries = zip_entries_total(zip_handle_);
    if (total_entries < 0) {
        result.success = false;
        result.errors.emplace_back(LoadErrorType::ZipOpenFailed, "", 
                                   "Failed to get ZIP entry count");
        result.integrity = DocumentIntegrity::Corrupted;
        return result;
    }
    
    result.total_files = static_cast<size_t>(total_entries);
    stats.total_entries = static_cast<size_t>(total_entries);
    
    // Decide whether to use parallel loading
    bool use_parallel = load_config_.enable_parallel_loading && 
                        static_cast<size_t>(total_entries) >= load_config_.parallel_threshold &&
                        std::thread::hardware_concurrency() > 1;
    
    if (use_parallel) {
        result.success = load_tree_parallel(stats);
    } else {
        // Sequential loading with progress tracking
        int last_reported_percent = -1;
        
        for (int i = 0; i < total_entries; ++i) {
            // Report progress every 5%
            int percent = (i * 100) / total_entries;
            if (percent != last_reported_percent && percent % 5 == 0) {
                report_progress(percent, "Loading...");
                last_reported_percent = percent;
            }
            
            // Open entry by index
            if (zip_entry_openbyindex(zip_handle_, i) != 0) {
                std::cerr << "Failed to open entry at index " << i << std::endl;
                if (!load_config_.skip_corrupted_files) {
                    result.errors.emplace_back(LoadErrorType::ZipEntryReadFailed, "",
                                               "Failed to open entry at index " + std::to_string(i));
                }
                continue;
            }
            
            // Get entry name
            const char* name = zip_entry_name(zip_handle_);
            if (!name) {
                zip_entry_close(zip_handle_);
                if (!load_config_.skip_corrupted_files) {
                    result.errors.emplace_back(LoadErrorType::ZipEntryReadFailed, "",
                                               "Failed to get entry name at index " + std::to_string(i));
                }
                continue;
            }
            
            std::string entry_name(name);
            bool is_dir = zip_entry_isdir(zip_handle_);
            
            if (!is_dir) {
                // Determine if we should load or lazy-load
                bool is_critical = (entry_name == "[Content_Types].xml" ||
                                   entry_name == "_rels/.rels" ||
                                   entry_name == "word/document.xml" ||
                                   entry_name.find(".rels") != std::string::npos);
                
                bool should_lazy_load = load_config_.enable_lazy_loading &&
                                       !is_critical &&
                                       entry_name.find("word/media/") == 0;
                
                size_t entry_size = zip_entry_size(zip_handle_);
                result.total_bytes += entry_size;
                
                if (should_lazy_load) {
                    // Mark for lazy loading
                    tree_.add_zip_entry(entry_name, {}, i, entry_size);
                    result.lazy_loaded_files.push_back(entry_name);
                    stats.lazy_loaded++;
                } else {
                    // Read entry data immediately
                    void* data = nullptr;
                    size_t size = 0;
                    
                    int read_result = zip_entry_read(zip_handle_, &data, &size);
                    if (read_result >= 0 && data && size > 0) {
                        std::vector<uint8_t> buffer(size);
                        std::memcpy(buffer.data(), data, size);
                        free(data);
                        
                        // Add to tree
                        auto node = tree_.add_zip_entry(entry_name, buffer, i, size);
                        if (node) {
                            result.loaded_files++;
                            result.loaded_bytes += size;
                            stats.total_bytes_read += size;
                            
                            // Track file types
                            if (node->type == DocxNodeType::XmlFile) {
                                stats.xml_files++;
                            } else if (node->type == DocxNodeType::MediaFile) {
                                stats.media_files++;
                            } else {
                                stats.binary_files++;
                            }
                        } else {
                            if (!load_config_.skip_corrupted_files) {
                                result.errors.emplace_back(LoadErrorType::XmlParseFailed,
                                                           entry_name,
                                                           "Failed to parse XML");
                            }
                        }
                    } else {
                        if (!load_config_.skip_corrupted_files) {
                            result.errors.emplace_back(LoadErrorType::ZipEntryReadFailed,
                                                       entry_name,
                                                       "Failed to read entry data");
                        }
                    }
                }
            }
            
            zip_entry_close(zip_handle_);
        }
        
        result.success = true;
    }
    
    stats.end_time = std::chrono::high_resolution_clock::now();
    result.load_time_ms = stats.get_elapsed_ms();
    
    // Build caches
    if (result.success) {
        build_caches_from_tree();
        load_all_relationships();
        load_content_types();
        
        // Determine integrity
        if (result.errors.empty()) {
            result.integrity = DocumentIntegrity::Complete;
        } else if (result.loaded_files > result.total_files / 2) {
            result.integrity = DocumentIntegrity::Partial;
        } else if (tree_.find_node("word/document.xml")) {
            result.integrity = DocumentIntegrity::Critical;
        }
    }
    
    last_load_stats_ = stats;
    last_load_result_ = result;
    
    report_progress(100, "Complete");
    return result;
}

bool DocumentImpl::load_tree_parallel(LoadStatistics& stats) {
    if (!zip_handle_) return false;
    
    int total_entries = zip_entries_total(zip_handle_);
    if (total_entries < 0) return false;
    
    // Collect all entries first (sequential, thread-safe)
    struct EntryInfo {
        int index;
        std::string name;
        size_t size;
        bool is_dir;
        bool is_critical;
    };
    
    std::vector<EntryInfo> entries;
    entries.reserve(total_entries);
    
    for (int i = 0; i < total_entries; ++i) {
        if (zip_entry_openbyindex(zip_handle_, i) != 0) continue;
        
        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        bool is_dir = zip_entry_isdir(zip_handle_);
        size_t size = zip_entry_size(zip_handle_);
        
        bool is_critical = (!is_dir && (
            std::string(name) == "[Content_Types].xml" ||
            std::string(name) == "_rels/.rels" ||
            std::string(name) == "word/document.xml" ||
            std::string(name).find(".rels") != std::string::npos
        ));
        
        entries.push_back({i, name, size, is_dir, is_critical});
        zip_entry_close(zip_handle_);
    }
    
    // Filter out directories and non-critical files that should be lazy-loaded
    std::vector<EntryInfo> to_load_now;
    std::vector<EntryInfo> to_lazy_load;
    
    for (const auto& entry : entries) {
        if (entry.is_dir) continue;
        
        bool should_lazy = load_config_.enable_lazy_loading &&
                          !entry.is_critical &&
                          entry.name.find("word/media/") == 0;
        
        if (should_lazy) {
            to_lazy_load.push_back(entry);
        } else {
            to_load_now.push_back(entry);
        }
    }
    
    // Mark lazy-load files in tree (single-threaded)
    for (const auto& entry : to_lazy_load) {
        tree_.add_zip_entry(entry.name, {}, entry.index, entry.size);
    }
    
    // Process non-lazy files in parallel
    size_t num_threads = load_config_.max_threads > 0 ? 
                         load_config_.max_threads : 
                         std::thread::hardware_concurrency();
    
    std::atomic<size_t> processed{0};
    std::atomic<size_t> errors{0};
    std::mutex tree_mutex;
    
    // Use parallel for_each if available, otherwise manual thread pool
    #if defined(__cpp_lib_parallel_algorithm)
    std::for_each(std::execution::par, to_load_now.begin(), to_load_now.end(),
        [&](const EntryInfo& entry) {
            // Open entry
            if (zip_entry_openbyindex(zip_handle_, entry.index) != 0) {
                errors++;
                return;
            }
            
            // Read data
            void* data = nullptr;
            size_t size = 0;
            if (zip_entry_read(zip_handle_, &data, &size) != 0 || !data) {
                zip_entry_close(zip_handle_);
                errors++;
                return;
            }
            
            std::vector<uint8_t> buffer(size);
            std::memcpy(buffer.data(), data, size);
            free(data);
            zip_entry_close(zip_handle_);
            
            // Add to tree (protected by mutex)
            {
                std::lock_guard<std::mutex> lock(tree_mutex);
                tree_.add_zip_entry(entry.name, buffer, entry.index, size);
            }
            
            processed++;
            
            // Progress report (throttled)
            int percent = static_cast<int>((processed * 100) / to_load_now.size());
            if (percent % 10 == 0) {
                report_progress(percent, entry.name);
            }
        });
    #else
    // Fallback: manual thread pool
    size_t batch_size = (to_load_now.size() + num_threads - 1) / num_threads;
    std::vector<std::thread> threads;
    
    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * batch_size;
        size_t end = std::min(start + batch_size, to_load_now.size());
        
        if (start >= end) break;
        
        threads.emplace_back([&, start, end]() {
            for (size_t i = start; i < end; ++i) {
                const auto& entry = to_load_now[i];
                
                // Each thread needs its own ZIP handle
                zip_t* local_zip = zip_open(filepath_.c_str(), 0, 'r');
                if (!local_zip) {
                    errors++;
                    continue;
                }
                
                if (zip_entry_openbyindex(local_zip, entry.index) != 0) {
                    zip_close(local_zip);
                    errors++;
                    continue;
                }
                
                void* data = nullptr;
                size_t size = 0;
                if (zip_entry_read(local_zip, &data, &size) != 0 || !data) {
                    zip_entry_close(local_zip);
                    zip_close(local_zip);
                    errors++;
                    continue;
                }
                
                std::vector<uint8_t> buffer(size);
                std::memcpy(buffer.data(), data, size);
                free(data);
                zip_entry_close(local_zip);
                zip_close(local_zip);
                
                {
                    std::lock_guard<std::mutex> lock(tree_mutex);
                    tree_.add_zip_entry(entry.name, buffer, entry.index, size);
                }
                
                processed++;
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    #endif
    
    return errors < to_load_now.size();  // Success if at least some files loaded
}

// ============================================================================
// Tree Loading - Legacy Helpers
// ============================================================================

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
    
    // Discover other relationship files
    tree_.iterate_files([this](std::shared_ptr<DocxTreeNode> node) {
        if (node->full_path.find("_rels/") != std::string::npos &&
            node->full_path.find(".rels") != std::string::npos) {
            if (relationships_.find(node->full_path) == relationships_.end()) {
                parse_relationships(node->full_path);
            }
        }
    });
}

bool DocumentImpl::load_content_types() {
    auto doc = tree_.find_node("[Content_Types].xml");
    if (!doc || !doc->xml_doc) {
        return false;
    }
    
    content_types_.clear();
    
    pugi::xml_node root = doc->xml_doc->child("Types");
    if (!root) return false;
    
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
            try {
                int id_num = std::stoi(rel.id.substr(3));
                max_id = std::max(max_id, id_num);
            } catch (...) {
                // Ignore invalid IDs
            }
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
    
    // First, ensure all lazy-loaded files are loaded
    tree_.preload_all();
    
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
        // Serialize XML with declaration
        xml_string_writer writer;
        node->xml_doc->save(writer, "  ");
        // Add original content as-is
        std::string xml_output = writer.result;
        
        success = zip_entry_write(zip, xml_output.data(), xml_output.size()) == 0;
    } else {
        // Write binary data - need to load if lazy
        node->file_storage.ensure_loaded(load_config_);
        auto data = node->file_storage.get_data();
        success = zip_entry_write(zip, data.data(), data.size()) == 0;
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
// Lazy Loading Helpers
// ============================================================================

bool DocumentImpl::preload_all_lazy_files() {
    return tree_.preload_all();
}

size_t DocumentImpl::unload_to_free_memory() {
    return tree_.unload_non_critical();
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
