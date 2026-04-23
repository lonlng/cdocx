/**
 * @file document_io.cpp
 * @brief Document ZIP I/O and tree loading
 * @internal Not part of the public API.
 */

#include <cdocx/document.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <thread>
#include <vector>

extern "C" {
#include <zip.h>
}

namespace cdocx {

namespace {

bool string_ends_with(const std::string& str, const std::string& suffix) {
    if (suffix.size() > str.size()) {
        return false;
    }
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

}  // namespace

// Internal ZIP Operations
// ============================================================================

bool Document::open_zip(const std::string& path) {
    zip_handle_ = zip_open(path.c_str(), 0, 'r');
    return zip_handle_ != nullptr;
}

void Document::close_zip() {
    if (zip_handle_) {
        zip_close(zip_handle_);
        zip_handle_ = nullptr;
    }
}

bool Document::ensure_zip_handle() {
    if (!zip_handle_ || zip_dirty_) {
        close_zip();
        if (!filepath_.empty()) {
            return open_zip(filepath_);
        }
        return false;
    }
    return true;
}

std::vector<uint8_t> Document::read_zip_entry(const std::string& entry_name) {
    std::vector<uint8_t> data;
    if (!zip_handle_) {
        return data;
    }

    if (zip_entry_open(zip_handle_, entry_name.c_str()) != 0) {
        return data;
    }

    void* buf = nullptr;
    size_t bufsize = 0;
    if (zip_entry_read(zip_handle_, &buf, &bufsize) == 0 && buf) {
        data.resize(bufsize);
        std::memcpy(data.data(), buf, bufsize);
        free(buf);
    }

    zip_entry_close(zip_handle_);
    return data;
}

// ============================================================================
// Tree Loading
// ============================================================================

bool Document::load_tree_from_zip() {
    if (!zip_handle_) {
        return false;
    }

    const int n = zip_entries_total(zip_handle_);
    if (n < 0) {
        return false;
    }

    tree_.clear();

    zip_entry_openbyindex(zip_handle_, 0);

    for (int i = 0; i < n; i++) {
        zip_entry_openbyindex(zip_handle_, i);

        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }

        const std::string entry_name(name);
        const bool is_dir = zip_entry_isdir(zip_handle_);

        if (is_dir) {
            zip_entry_close(zip_handle_);
            continue;
        }

        // Read entry data
        void* buf = nullptr;
        size_t bufsize = 0;

        if (zip_entry_read(zip_handle_, &buf, &bufsize) < 0) {
            zip_entry_close(zip_handle_);
            continue;
        }

        std::vector<uint8_t> data(static_cast<uint8_t*>(buf), static_cast<uint8_t*>(buf) + bufsize);
        free(buf);

        // Add to tree
        auto node = tree_.add_zip_entry(entry_name, data);

        // Parse XML files
        if (string_ends_with(entry_name, ".xml") || string_ends_with(entry_name, ".rels")) {
            node->type = DocxNodeType::XmlFile;
            node->xml_doc = std::make_shared<pugi::xml_document>();

            const pugi::xml_parse_result result = node->xml_doc->load_buffer(
                data.data(),
                data.size(),
                pugi::parse_default | pugi::parse_declaration | pugi::parse_ws_pcdata);

            if (!result) {
                // XML parse failed, treat as binary
                node->type = DocxNodeType::BinaryFile;
                node->xml_doc.reset();
            }
        } else if (entry_name.find("word/media/") != std::string::npos) {
            node->type = DocxNodeType::MediaFile;
        } else {
            node->type = DocxNodeType::BinaryFile;
        }

        zip_entry_close(zip_handle_);
    }

    return true;
}

LoadResult Document::load_tree_with_result() {
    LoadResult result;
    last_load_stats_.start_time = std::chrono::high_resolution_clock::now();

    if (!zip_handle_) {
        result.success = false;
        result.errors.emplace_back(LoadErrorType::ZipOpenFailed, filepath_, "ZIP handle is null");
        result.integrity = DocumentIntegrity::Corrupted;
        last_load_result_ = result;
        return result;
    }

    const int n = zip_entries_total(zip_handle_);
    if (n < 0) {
        result.success = false;
        result.errors.emplace_back(
            LoadErrorType::ZipOpenFailed, filepath_, "Failed to get entry count");
        result.integrity = DocumentIntegrity::Corrupted;
        last_load_result_ = result;
        return result;
    }

    result.total_files = static_cast<size_t>(n);
    last_load_stats_.total_entries = result.total_files;

    tree_.clear();

    // Use parallel loading when enabled and threshold is met
    const bool use_parallel = load_config_.enable_parallel_loading &&
                              static_cast<size_t>(n) >= load_config_.parallel_threshold &&
                              std::thread::hardware_concurrency() > 1;

    if (use_parallel) {
        const bool parallel_ok = load_tree_parallel(last_load_stats_);
        if (parallel_ok) {
            last_load_stats_.end_time = std::chrono::high_resolution_clock::now();
            result.success = last_load_stats_.xml_files > 0;
            result.loaded_files = last_load_stats_.processed_entries;
            result.load_time_ms = last_load_stats_.get_elapsed_ms();

            if (result.errors.empty()) {
                result.integrity = DocumentIntegrity::Complete;
            } else if (result.loaded_files > result.errors.size() * 2) {
                result.integrity = DocumentIntegrity::Partial;
            } else {
                result.integrity = DocumentIntegrity::Corrupted;
            }

            last_load_result_ = result;
            return result;
        }
        // Fall back to sequential on failure
        tree_.clear();
    }

    for (int i = 0; i < n; i++) {
        if (zip_entry_openbyindex(zip_handle_, i) != 0) {
            result.errors.emplace_back(
                LoadErrorType::ZipEntryReadFailed, "", "Failed to open entry " + std::to_string(i));
            continue;
        }

        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }

        const std::string entry_name(name);

        if (zip_entry_isdir(zip_handle_)) {
            zip_entry_close(zip_handle_);
            continue;
        }

        // Read entry data
        void* buf = nullptr;
        size_t bufsize = 0;

        if (zip_entry_read(zip_handle_, &buf, &bufsize) < 0) {
            result.errors.emplace_back(
                LoadErrorType::ZipEntryReadFailed, entry_name, "Failed to read entry");
            zip_entry_close(zip_handle_);
            continue;
        }

        std::vector<uint8_t> data(static_cast<uint8_t*>(buf), static_cast<uint8_t*>(buf) + bufsize);
        free(buf);

        // Add to tree
        auto node = tree_.add_zip_entry(entry_name, data);

        // Parse XML files
        if (string_ends_with(entry_name, ".xml") || string_ends_with(entry_name, ".rels")) {
            node->type = DocxNodeType::XmlFile;
            node->xml_doc = std::make_shared<pugi::xml_document>();

            const pugi::xml_parse_result parse_result = node->xml_doc->load_buffer(
                data.data(),
                data.size(),
                pugi::parse_default | pugi::parse_declaration | pugi::parse_ws_pcdata);

            if (parse_result) {
                last_load_stats_.xml_files++;
            } else {
                result.errors.emplace_back(
                    LoadErrorType::XmlParseFailed, entry_name, "Failed to parse XML");
                node->type = DocxNodeType::BinaryFile;
                node->xml_doc.reset();
            }
        } else if (entry_name.find("word/media/") != std::string::npos) {
            node->type = DocxNodeType::MediaFile;
            last_load_stats_.media_files++;
        } else {
            node->type = DocxNodeType::BinaryFile;
            last_load_stats_.binary_files++;
        }

        last_load_stats_.processed_entries++;

        // Report progress
        if (load_config_.progress_callback) {
            const int percent = ((i + 1) * 100 / n);
            load_config_.progress_callback(percent, entry_name);
        }

        zip_entry_close(zip_handle_);
    }

    last_load_stats_.end_time = std::chrono::high_resolution_clock::now();

    result.success = last_load_stats_.xml_files > 0;
    result.loaded_files = last_load_stats_.processed_entries;
    result.load_time_ms = last_load_stats_.get_elapsed_ms();

    // Determine integrity
    if (result.errors.empty()) {
        result.integrity = DocumentIntegrity::Complete;
    } else if (result.loaded_files > result.errors.size() * 2) {
        result.integrity = DocumentIntegrity::Partial;
    } else {
        result.integrity = DocumentIntegrity::Corrupted;
    }

    last_load_result_ = result;
    return result;
}

bool Document::load_tree_parallel(LoadStatistics& stats) {
    if (!zip_handle_) {
        return false;
    }

    const int total_entries = zip_entries_total(zip_handle_);
    if (total_entries < 0) {
        return false;
    }

    struct EntryInfo {
        int index = 0;
        std::string name;
        bool is_dir = false;
    };

    std::vector<EntryInfo> entries;
    entries.reserve(total_entries);

    // Phase 1: Collect metadata sequentially (zip handles are not thread-safe)
    for (int i = 0; i < total_entries; ++i) {
        if (zip_entry_openbyindex(zip_handle_, i) != 0) {
            continue;
        }

        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }

        entries.push_back({i, name, zip_entry_isdir(zip_handle_) != 0});
        zip_entry_close(zip_handle_);
    }

    std::vector<EntryInfo> files_to_load;
    for (const auto& entry : entries) {
        if (!entry.is_dir) {
            files_to_load.push_back(entry);
        }
    }

    if (files_to_load.empty()) {
        return true;
    }

    size_t num_threads = load_config_.max_threads > 0 ? load_config_.max_threads
                                                      : std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 2;
    }
    num_threads = std::min(num_threads, files_to_load.size());

    std::atomic<size_t> processed{0};
    std::atomic<size_t> error_count{0};
    std::atomic<size_t> xml_count{0};
    std::atomic<size_t> media_count{0};
    std::atomic<size_t> binary_count{0};

    const size_t batch_size = (files_to_load.size() + num_threads - 1) / num_threads;
    std::vector<std::thread> threads;

    for (size_t t = 0; t < num_threads; ++t) {
        const size_t start = t * batch_size;
        const size_t end = std::min(start + batch_size, files_to_load.size());
        if (start >= end) {
            break;
        }

        threads.emplace_back([&, start, end]() {
            // Each thread opens its own zip handle for thread safety
            zip_t* local_zip = zip_open(filepath_.c_str(), 0, 'r');
            if (!local_zip) {
                error_count += (end - start);
                return;
            }

            for (size_t i = start; i < end; ++i) {
                const auto& entry = files_to_load[i];

                if (zip_entry_openbyindex(local_zip, entry.index) != 0) {
                    ++error_count;
                    continue;
                }

                void* data = nullptr;
                size_t size = 0;
                if (zip_entry_read(local_zip, &data, &size) < 0 || !data) {
                    zip_entry_close(local_zip);
                    ++error_count;
                    continue;
                }

                std::vector<uint8_t> buffer(size);
                std::memcpy(buffer.data(), data, size);
                free(data);
                zip_entry_close(local_zip);

                // DocxTree::add_zip_entry is internally synchronized
                auto node = tree_.add_zip_entry(entry.name, buffer);
                if (!node) {
                    ++error_count;
                    continue;
                }

                // Classify for stats
                if (node->type == DocxNodeType::XmlFile) {
                    ++xml_count;
                } else if (node->type == DocxNodeType::MediaFile) {
                    ++media_count;
                } else {
                    ++binary_count;
                }

                const size_t current = ++processed;

                // Throttled progress reporting
                if (load_config_.progress_callback && current % 10 == 0) {
                    const int percent = static_cast<int>((current * 100) / files_to_load.size());
                    load_config_.progress_callback(percent, entry.name);
                }
            }

            zip_close(local_zip);
        });
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    stats.processed_entries = processed.load();
    stats.xml_files = xml_count.load();
    stats.media_files = media_count.load();
    stats.binary_files = binary_count.load();

    return error_count.load() < files_to_load.size();
}

void Document::build_caches_from_tree() {
    xml_parts_cache_.clear();
    media_files_cache_.clear();

    tree_.iterate_files([this](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->type == DocxNodeType::XmlFile) {
            xml_parts_cache_[node->full_path] = node;
        } else if (node->type == DocxNodeType::MediaFile) {
            media_files_cache_[node->full_path] = node;
        }
    });
}

// Save Operations
// ============================================================================

bool Document::save_to_zip(const std::string& output_path) {
    zip_t* zip = zip_open(output_path.c_str(), 9, 'w');
    if (!zip) {
        return false;
    }

    const bool success = save_tree_to_zip(zip);

    zip_close(zip);
    return success;
}

bool Document::save_tree_to_zip(zip_t* zip) {
    if (!zip) {
        return false;
    }

    // First pass: create directories
    tree_.iterate_all([zip](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->is_directory() && !node->name.empty()) {
            zip_entry_open(zip, (node->full_path + "/").c_str());
            zip_entry_close(zip);
        }
    });

    // Second pass: write files
    tree_.iterate_files([this, zip](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->is_deleted) {
            return;
        }

        zip_entry_open(zip, node->full_path.c_str());

        if (node->type == DocxNodeType::XmlFile && node->xml_doc) {
            // Serialize XML
            std::vector<uint8_t> data = node->serialize_xml_to_binary();
            zip_entry_write(zip, data.data(), data.size());
        } else {
            // Write binary data
            zip_entry_write(zip, node->binary_data.data(), node->binary_data.size());
        }

        zip_entry_close(zip);
    });

    return true;
}

bool Document::write_tree_node(zip_t* /*zip*/, const std::shared_ptr<DocxTreeNode>& /*node*/) {
    // This method is now integrated into save_tree_to_zip
    return true;
}


}  // namespace cdocx
