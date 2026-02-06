// CDocx - Document Class Implementation (PIMPL)

#include "cdocx.h"
#include "detail/cdocx_impl.h"
#include <filesystem>
#include <fstream>
#include <algorithm>

// Include pugixml
#include <pugixml.hpp>

namespace cdocx {

// ============================================================================
// Document Constructor/Destructor
// ============================================================================

Document::Document() : impl_(std::make_unique<DocumentImpl>()) {}

Document::Document(const std::string& filepath) : impl_(std::make_unique<DocumentImpl>()) {
    impl_->filepath_ = filepath;
}

Document::~Document() = default;

Document::Document(Document&& other) noexcept = default;
Document& Document::operator=(Document&& other) noexcept = default;

// ============================================================================
// Basic Operations
// ============================================================================

void Document::file(const std::string& filepath) {
    impl_->filepath_ = filepath;
}

void Document::open() {
    if (impl_->filepath_.empty()) return;
    open(impl_->filepath_);
}

void Document::open(const std::string& filepath) {
    close();
    
    impl_->filepath_ = filepath;
    
    if (!impl_->open_zip(filepath)) {
        return;
    }
    
    if (!impl_->load_tree_from_zip()) {
        close();
        return;
    }
    
    impl_->build_caches_from_tree();
    impl_->load_all_relationships();
    impl_->load_content_types();
    
    impl_->is_open_ = true;
    
    // Initialize paragraph iterator
    pugi::xml_document* doc_xml = get_document_xml();
    if (doc_xml) {
        pugi::xml_node body = doc_xml->child("w:document").child("w:body");
        if (body) {
            impl_->paragraph_->set_parent(body);
            impl_->table_->set_parent(body);
        }
    }
}

void Document::close() {
    impl_->close_zip();
    impl_->tree_.clear();
    impl_->xml_parts_cache_.clear();
    impl_->media_files_cache_.clear();
    impl_->relationships_.clear();
    impl_->modified_parts_.clear();
    impl_->content_types_.clear();
    impl_->is_open_ = false;
}

void Document::save() {
    if (!is_open() || impl_->filepath_.empty()) return;
    save(impl_->filepath_);
}

void Document::save(const std::string& filepath) {
    if (!is_open()) return;
    
    // Update all modified parts
    for (const auto& rels_pair : impl_->relationships_) {
        impl_->update_relationships_xml(rels_pair.first);
    }
    impl_->update_content_types_xml();
    
    if (!impl_->save_to_zip(filepath)) {
        return;
    }
    
    // Clear modified flags
    impl_->tree_.iterate_all([](std::shared_ptr<DocxTreeNode> node) {
        node->is_modified = false;
        node->is_new = false;
    });
    impl_->modified_parts_.clear();
    
    impl_->zip_dirty_ = true;
}

bool Document::is_open() const {
    return impl_->is_open_;
}

bool Document::create_empty(const std::string& filepath) {
    close();
    
    if (!filepath.empty()) {
        impl_->filepath_ = filepath;
    }
    
    // Create all required XML parts for an empty document
    if (!impl_->create_empty_document()) {
        close();
        return false;
    }
    
    impl_->is_open_ = true;
    
    // Initialize paragraph iterator
    pugi::xml_document* doc_xml = get_document_xml();
    if (doc_xml) {
        pugi::xml_node body = doc_xml->child("w:document").child("w:body");
        if (body) {
            impl_->paragraph_->set_parent(body);
            impl_->table_->set_parent(body);
        }
    }
    
    return true;
}

std::string Document::get_filepath() const {
    return impl_->filepath_;
}

void Document::clear() {
    close();
    impl_->filepath_.clear();
}

// ============================================================================
// Document Content Access
// ============================================================================

Paragraph& Document::paragraphs() {
    if (!is_open()) {
        static Paragraph empty;
        return empty;
    }
    
    pugi::xml_document* doc = get_document_xml();
    if (!doc) {
        static Paragraph empty;
        return empty;
    }
    
    pugi::xml_node body = doc->child("w:document").child("w:body");
    if (!body) {
        static Paragraph empty;
        return empty;
    }
    
    impl_->paragraph_->set_parent(body);
    return *impl_->paragraph_;
}

Table& Document::tables() {
    if (!is_open()) {
        static Table empty;
        return empty;
    }
    
    pugi::xml_document* doc = get_document_xml();
    if (!doc) {
        static Table empty;
        return empty;
    }
    
    pugi::xml_node body = doc->child("w:document").child("w:body");
    if (!body) {
        static Table empty;
        return empty;
    }
    
    impl_->table_->set_parent(body);
    return *impl_->table_;
}

// ============================================================================
// XML Parts API
// ============================================================================

pugi::xml_document* Document::get_xml_part(const std::string& part_path) {
    auto node = impl_->tree_.find_node(part_path);
    if (node && node->xml_doc) {
        return node->xml_doc.get();
    }
    return nullptr;
}

const pugi::xml_document* Document::get_xml_part(const std::string& part_path) const {
    auto node = impl_->tree_.find_node(part_path);
    if (node && node->xml_doc) {
        return node->xml_doc.get();
    }
    return nullptr;
}

bool Document::has_xml_part(const std::string& part_path) const {
    auto node = impl_->tree_.find_node(part_path);
    return node && node->type == DocxNodeType::XmlFile;
}

std::vector<std::string> Document::get_all_part_names() const {
    std::vector<std::string> names;
    impl_->tree_.iterate_files([&names](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::XmlFile) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

size_t Document::get_part_count() const {
    size_t count = 0;
    impl_->tree_.iterate_files([&count](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::XmlFile) {
            count++;
        }
    });
    return count;
}

pugi::xml_document& Document::create_xml_part(const std::string& part_path) {
    auto node = impl_->tree_.find_or_create_node(part_path, DocxNodeType::XmlFile);
    if (!node->xml_doc) {
        node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    node->is_new = true;
    node->is_modified = true;
    impl_->modified_parts_.insert(part_path);
    impl_->xml_parts_cache_[part_path] = node;
    return *node->xml_doc;
}

void Document::remove_xml_part(const std::string& part_path) {
    auto node = impl_->tree_.find_node(part_path);
    if (node) {
        node->is_deleted = true;
    }
    impl_->xml_parts_cache_.erase(part_path);
    impl_->modified_parts_.erase(part_path);
}

void Document::mark_modified(const std::string& part_path) {
    impl_->modified_parts_.insert(part_path);
    auto node = impl_->tree_.find_node(part_path);
    if (node) {
        node->is_modified = true;
    }
}

// ============================================================================
// Convenience Part Accessors
// ============================================================================

pugi::xml_document* Document::get_document_xml() {
    return get_xml_part("word/document.xml");
}

pugi::xml_document* Document::get_core_properties() {
    return get_xml_part("docProps/core.xml");
}

pugi::xml_document* Document::get_app_properties() {
    return get_xml_part("docProps/app.xml");
}

pugi::xml_document* Document::get_content_types() {
    return get_xml_part("[Content_Types].xml");
}

pugi::xml_document* Document::get_styles() {
    return get_xml_part("word/styles.xml");
}

pugi::xml_document* Document::get_settings() {
    return get_xml_part("word/settings.xml");
}

pugi::xml_document* Document::get_font_table() {
    return get_xml_part("word/fontTable.xml");
}

pugi::xml_document* Document::get_numbering() {
    return get_xml_part("word/numbering.xml");
}

pugi::xml_document* Document::get_footnotes() {
    return get_xml_part("word/footnotes.xml");
}

pugi::xml_document* Document::get_endnotes() {
    return get_xml_part("word/endnotes.xml");
}

pugi::xml_document* Document::get_document_rels() {
    return get_xml_part("word/_rels/document.xml.rels");
}

pugi::xml_document* Document::get_package_rels() {
    return get_xml_part("_rels/.rels");
}

pugi::xml_document* Document::get_header(int index) {
    std::string name = "word/header" + std::to_string(index) + ".xml";
    return get_xml_part(name);
}

pugi::xml_document* Document::get_footer(int index) {
    std::string name = "word/footer" + std::to_string(index) + ".xml";
    return get_xml_part(name);
}

std::vector<std::string> Document::get_header_names() const {
    std::vector<std::string> names;
    impl_->tree_.iterate_files([&names](std::shared_ptr<DocxTreeNode> node) {
        if (node->full_path.find("word/header") != std::string::npos &&
            node->full_path.find(".xml") != std::string::npos) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

std::vector<std::string> Document::get_footer_names() const {
    std::vector<std::string> names;
    impl_->tree_.iterate_files([&names](std::shared_ptr<DocxTreeNode> node) {
        if (node->full_path.find("word/footer") != std::string::npos &&
            node->full_path.find(".xml") != std::string::npos) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

// ============================================================================
// Media Management
// ============================================================================

bool Document::add_media(const std::string& image_path, const std::string* image_name) {
    if (!is_open()) return false;
    if (!std::filesystem::exists(image_path)) return false;
    if (!validate_image_format(image_path)) return false;
    
    std::string filename;
    if (image_name && !image_name->empty()) {
        filename = *image_name;
    } else {
        filename = std::filesystem::path(image_path).filename().string();
    }
    
    std::string media_path = "word/media/" + filename;
    if (impl_->tree_.find_node(media_path)) {
        filename = generate_unique_image_name(filename);
        media_path = "word/media/" + filename;
    }
    
    std::ifstream file(image_path, std::ios::binary);
    if (!file) return false;
    
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
    file.close();
    
    if (data.empty()) return false;
    
    auto node = impl_->tree_.add_media_file(media_path, data, impl_->get_mime_type(filename));
    if (!node) return false;
    
    node->is_new = true;
    node->is_modified = true;
    impl_->media_files_cache_[media_path] = node;
    
    impl_->add_content_type_override("/" + media_path, impl_->get_mime_type(filename));
    
    return true;
}

bool Document::add_media_from_memory(const std::string& name,
                                     const std::vector<uint8_t>& data,
                                     const std::string& content_type) {
    if (!is_open()) return false;
    if (data.empty()) return false;
    
    std::string media_path = "word/media/" + name;
    
    auto node = impl_->tree_.add_media_file(media_path, data, 
        content_type.empty() ? impl_->get_mime_type(name) : content_type);
    if (!node) return false;
    
    node->is_new = true;
    node->is_modified = true;
    impl_->media_files_cache_[media_path] = node;
    
    impl_->add_content_type_override("/" + media_path, node->content_type);
    
    return true;
}

bool Document::delete_media(const std::string& image_name) {
    if (!is_open()) return false;
    
    std::string media_path = "word/media/" + image_name;
    auto node = impl_->tree_.find_node(media_path);
    if (!node) return false;
    
    node->is_deleted = true;
    
    // Remove relationship
    std::string target = "media/" + image_name;
    std::string rel_id = impl_->find_relationship_id("word/_rels/document.xml.rels", target);
    if (!rel_id.empty()) {
        impl_->remove_relationship("word/_rels/document.xml.rels", rel_id);
    }
    
    impl_->media_files_cache_.erase(media_path);
    
    return true;
}

bool Document::replace_media(const std::string& image_name, const std::string& new_image_path) {
    if (!is_open()) return false;
    if (!std::filesystem::exists(new_image_path)) return false;
    
    std::string media_path = "word/media/" + image_name;
    auto node = impl_->tree_.find_node(media_path);
    if (!node) return false;
    
    std::ifstream file(new_image_path, std::ios::binary);
    if (!file) return false;
    
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
    file.close();
    
    if (data.empty()) return false;
    
    node->binary_data = std::move(data);
    node->is_modified = true;
    
    return true;
}

bool Document::has_media(const std::string& image_name) const {
    if (!is_open()) return false;
    std::string media_path = "word/media/" + image_name;
    auto node = impl_->tree_.find_node(media_path);
    return node && !node->is_deleted;
}

std::vector<std::string> Document::list_media() const {
    std::vector<std::string> result;
    impl_->tree_.iterate_files([&result](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::MediaFile && !node->is_deleted) {
            std::string name = node->full_path;
            if (name.substr(0, 11) == "word/media/") {
                result.push_back(name.substr(11));
            }
        }
    });
    return result;
}

bool Document::export_media(const std::string& image_name, const std::string& output_path) const {
    if (!is_open()) return false;
    
    std::string media_path = "word/media/" + image_name;
    auto node = impl_->tree_.find_node(media_path);
    if (!node || node->is_deleted) return false;
    
    std::ofstream file(output_path, std::ios::binary);
    if (!file) return false;
    
    file.write(reinterpret_cast<const char*>(node->binary_data.data()), 
               node->binary_data.size());
    
    return file.good();
}

std::vector<uint8_t> Document::get_media_data(const std::string& image_name) const {
    std::vector<uint8_t> result;
    if (!is_open()) return result;
    
    std::string media_path = "word/media/" + image_name;
    auto node = impl_->tree_.find_node(media_path);
    if (node && !node->is_deleted) {
        result = node->binary_data;
    }
    return result;
}

std::string Document::add_media_with_rel(const std::string& image_path,
                                          const std::string* image_name) {
    if (!add_media(image_path, image_name)) return "";
    
    std::string name = (image_name && !image_name->empty()) ? *image_name 
        : std::filesystem::path(image_path).filename().string();
    
    return impl_->add_relationship("word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
        "media/" + name);
}

bool Document::validate_image_format(const std::string& image_path) const {
    std::string ext = std::filesystem::path(image_path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    static const std::set<std::string> valid_exts = {
        ".png", ".jpg", ".jpeg", ".gif", ".bmp", ".tiff", ".tif", ".webp"
    };
    
    return valid_exts.find(ext) != valid_exts.end();
}

bool Document::validate_image_size(const std::string& image_path, size_t max_size) const {
    if (!std::filesystem::exists(image_path)) return false;
    
    std::error_code ec;
    auto size = std::filesystem::file_size(image_path, ec);
    return !ec && size <= max_size;
}

std::string Document::generate_unique_image_name(const std::string& base_name) const {
    std::filesystem::path path(base_name);
    std::string stem = path.stem().string();
    std::string ext = path.extension().string();
    
    std::string name = base_name;
    int counter = 1;
    
    while (has_media(name)) {
        name = stem + "_" + std::to_string(counter) + ext;
        counter++;
    }
    
    return name;
}

// ============================================================================
// Legacy Compatibility Methods
// ============================================================================

void Document::preload_image_cache() {}
void Document::clear_image_cache() {}
size_t Document::get_image_cache_size() const {
    size_t count = 0;
    impl_->tree_.iterate_files([&count](std::shared_ptr<DocxTreeNode> node) {
        if (node->type == DocxNodeType::MediaFile && !node->is_deleted) count++;
    });
    return count;
}

std::string Document::add_media_optimized(const std::string& image_path,
                                           const std::string& image_name,
                                           bool overwrite) {
    if (!overwrite && has_media(image_name)) return "";
    return add_media_with_rel(image_path, image_name.empty() ? nullptr : &image_name);
}

bool Document::delete_media_optimized(const std::string& image_name) {
    return delete_media(image_name);
}

bool Document::replace_media_optimized(const std::string& image_name, 
                                        const std::string& new_image_path) {
    return replace_media(image_name, new_image_path);
}

bool Document::export_media_optimized(const std::string& image_name, 
                                       const std::string& output_path) const {
    return export_media(image_name, output_path);
}

bool Document::has_media_optimized(const std::string& image_name) const {
    return has_media(image_name);
}

} // namespace cdocx
