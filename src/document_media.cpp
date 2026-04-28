/**
 * @file document_media.cpp
 * @brief Document media and thumbnail management
 * @internal Not part of the public API.
 */

#include <cdocx/document.h>

#include "sync_common.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <map>
#include <vector>

namespace cdocx {

// ============================================================================
// Media Management
// ============================================================================

bool Document::add_media(const std::string& image_path, const std::string* image_name) {
    if (!is_open()) {
        return false;
    }
    if (!std::filesystem::exists(image_path)) {
        return false;
    }

    // Determine the filename in the document
    std::string filename;
    if (image_name && !image_name->empty()) {
        filename = *image_name;
    } else {
        filename = std::filesystem::path(image_path).filename().string();
    }

    // Generate unique name if already exists
    std::string media_path = "word/media/" + filename;
    if (tree_.find_node(media_path)) {
        filename = generate_unique_image_name(filename);
        media_path = "word/media/" + filename;
    }

    // Read image file
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        return false;
    }

    const std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());
    file.close();

    if (data.empty()) {
        return false;
    }

    // Add to tree
    auto node = tree_.add_zip_entry(media_path, data);
    if (!node) {
        return false;
    }

    node->type = DocxNodeType::MediaFile;
    node->content_type = get_mime_type(filename);
    node->is_new = true;
    node->is_modified = true;
    media_files_cache_[media_path] = node;

    // Register content type
    add_content_type_override("/" + media_path, get_mime_type(filename));

    return true;
}

bool Document::add_media_from_memory(const std::string& name,
                                     const std::vector<uint8_t>& data,
                                     const std::string& content_type) {
    if (!is_open()) {
        return false;
    }
    if (data.empty()) {
        return false;
    }

    const std::string media_path = "word/media/" + name;

    auto node = tree_.add_zip_entry(media_path, data);
    if (!node) {
        return false;
    }

    node->type = DocxNodeType::MediaFile;
    node->content_type = content_type.empty() ? get_mime_type(name) : content_type;
    node->is_new = true;
    node->is_modified = true;
    media_files_cache_[media_path] = node;

    add_content_type_override("/" + media_path, node->content_type);

    return true;
}

std::string Document::add_media_from_memory_with_rel(const std::string& name,
                                                     const std::vector<uint8_t>& data,
                                                     const std::string& content_type) {
    if (!add_media_from_memory(name, data, content_type)) {
        return "";
    }

    return add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
        "media/" + name);
}

bool Document::delete_media(const std::string& image_name) {
    if (!is_open()) {
        return false;
    }

    const std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    if (!node) {
        return false;
    }

    node->is_deleted = true;

    // Remove relationship if exists
    const std::string target = "media/" + image_name;
    const std::string rel_id = find_relationship_id("word/_rels/document.xml.rels", target);
    if (!rel_id.empty()) {
        remove_relationship("word/_rels/document.xml.rels", rel_id);
    }

    media_files_cache_.erase(media_path);

    return true;
}

bool Document::replace_media(const std::string& image_name, const std::string& new_image_path) {
    if (!is_open()) {
        return false;
    }
    if (!std::filesystem::exists(new_image_path)) {
        return false;
    }

    const std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    if (!node) {
        return false;
    }

    // Read new image data
    std::ifstream file(new_image_path, std::ios::binary);
    if (!file) {
        return false;
    }

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    file.close();

    if (data.empty()) {
        return false;
    }

    node->binary_data = std::move(data);
    node->is_modified = true;

    return true;
}


bool Document::has_media(const std::string& image_name) const {
    if (!is_open()) {
        return false;
    }
    const std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    return node && !node->is_deleted;
}

std::vector<std::string> Document::list_media() const {
    std::vector<std::string> result;
    tree_.iterate_files([&result](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->type == DocxNodeType::MediaFile && !node->is_deleted) {
            const std::string name = node->full_path;
            if (name.substr(0, 11) == "word/media/") {
                result.push_back(name.substr(11));
            }
        }
    });
    return result;
}

bool Document::export_media(const std::string& image_name, const std::string& output_path) const {
    if (!is_open()) {
        return false;
    }

    const std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    if (!node || node->is_deleted) {
        return false;
    }

    std::ofstream file(output_path, std::ios::binary);
    if (!file) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(node->binary_data.data()), node->binary_data.size());

    return file.good();
}

std::vector<uint8_t> Document::get_media_data(const std::string& image_name) const {
    std::vector<uint8_t> result;
    if (!is_open()) {
        return result;
    }

    const std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    if (node && !node->is_deleted) {
        result = node->binary_data;
    }
    return result;
}

std::string Document::add_media_with_rel(const std::string& image_path,
                                         const std::string* image_name) {
    if (!add_media(image_path, image_name)) {
        return "";
    }

    const std::string name = (image_name && !image_name->empty())
                                 ? *image_name
                                 : std::filesystem::path(image_path).filename().string();

    return add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
        "media/" + name);
}

// ============================================================================
// Thumbnail Management
// ============================================================================

bool Document::add_thumbnail(const std::string& image_path) {
    if (!is_open()) {
        return false;
    }
    if (!std::filesystem::exists(image_path)) {
        return false;
    }

    const std::string filename = std::filesystem::path(image_path).filename().string();

    // Read image file
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        return false;
    }

    const std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());
    file.close();

    if (data.empty()) {
        return false;
    }

    const std::string ct = get_mime_type(filename);
    return add_thumbnail_from_memory(data, ct);
}

bool Document::add_thumbnail_from_memory(const std::vector<uint8_t>& data,
                                         const std::string& content_type) {
    if (!is_open() || data.empty()) {
        return false;
    }

    // Thumbnail is always stored as thumbnail.jpeg in docProps/
    const std::string thumb_path = "docProps/thumbnail.jpeg";

    // Remove existing thumbnail first
    remove_thumbnail();

    // Add to tree
    auto node = tree_.add_zip_entry(thumb_path, data);
    if (!node) {
        return false;
    }

    node->type = DocxNodeType::MediaFile;
    node->content_type = content_type.empty() ? "image/jpeg" : content_type;
    node->is_new = true;
    node->is_modified = true;

    // Register content type override
    add_content_type_override("/" + thumb_path, node->content_type);

    // Add relationship in package rels (_rels/.rels)
    add_relationship("_rels/.rels",
                     "http://schemas.openxmlformats.org/package/2006/relationships/metadata/"
                     "thumbnail",
                     "docProps/thumbnail.jpeg");

    return true;
}

bool Document::remove_thumbnail() {
    if (!is_open()) {
        return false;
    }

    const std::string thumb_path = "docProps/thumbnail.jpeg";
    auto node = tree_.find_node(thumb_path);
    if (!node) {
        return false;
    }

    node->is_deleted = true;

    // Remove relationship if exists
    const std::string rel_id = find_relationship_id("_rels/.rels", "docProps/thumbnail.jpeg");
    if (!rel_id.empty()) {
        remove_relationship("_rels/.rels", rel_id);
    }

    return true;
}

bool Document::has_thumbnail() const {
    if (!is_open()) {
        return false;
    }

    auto node = tree_.find_node("docProps/thumbnail.jpeg");
    return node && !node->is_deleted;
}

// ============================================================================
// Media Helpers
// ============================================================================

std::string Document::get_mime_type(const std::string& filename) const {
    std::string ext = std::filesystem::path(filename).extension().string();
    if (!ext.empty() && ext[0] == '.') {
        ext = ext.substr(1);
    }
    ext = to_lower(ext);

    static const std::map<std::string, std::string> kMimeMap = {
        {"png", "image/png"},
        {"jpg", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"gif", "image/gif"},
        {"bmp", "image/bmp"},
        {"tiff", "image/tiff"},
        {"tif", "image/tiff"},
        {"wmf", "image/x-wmf"},
        {"emf", "image/x-emf"},
        {"svg", "image/svg+xml"},
    };

    auto it = kMimeMap.find(ext);
    if (it != kMimeMap.end()) {
        return it->second;
    }
    return "application/octet-stream";
}

std::string Document::get_extension_from_mime(const std::string& mime_type) const {
    static const std::map<std::string, std::string> kExtMap = {
        {"image/png", ".png"},
        {"image/jpeg", ".jpg"},
        {"image/gif", ".gif"},
        {"image/bmp", ".bmp"},
        {"image/tiff", ".tiff"},
        {"image/x-wmf", ".wmf"},
        {"image/x-emf", ".emf"},
        {"image/svg+xml", ".svg"},
    };

    auto it = kExtMap.find(mime_type);
    if (it != kExtMap.end()) {
        return it->second;
    }
    return "";
}

std::string Document::generate_unique_image_name(const std::string& base_name) const {
    const std::filesystem::path path(base_name);
    const std::string stem = path.stem().string();
    const std::string ext = path.extension().string();

    std::string name = base_name;
    int counter = 1;

    while (has_media(name)) {
        name = stem;
        name += "_";
        name += std::to_string(counter);
        name += ext;
        counter++;
    }

    return name;
}

}  // namespace cdocx
