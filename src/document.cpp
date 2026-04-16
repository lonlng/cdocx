/**
 * @file document.cpp
 * @brief Document class implementation - DOM Architecture
 * @details Implementation of the Document class using DOM architecture.
 *          Document inherits from CompositeNode and contains Sections.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0 - DOM Architecture
 */

#include <cdocx/document.h>
#include <cdocx/section.h>
#include <cdocx/body.h>
#include <cstring>
#include <cdocx/paragraph.h>
#include <cdocx/table.h>
#include <cdocx/base.h>
#include <cdocx/advanced.h>
#include <cdocx/style.h>
#include <cdocx/watermark.h>
#include <cdocx/comment.h>
#include <detail/impl.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <set>
#include <sstream>

extern "C" {
#include <zip.h>
}

namespace cdocx {

// ============================================================================
// Constructor / Destructor
// ============================================================================

Document::Document()
    : filepath_(""), is_open_(false), zip_handle_(nullptr), zip_dirty_(false),
      sections_dirty_(true), next_header_number_(1), next_footer_number_(1),
      next_bookmark_id_(1) {
    // Initialize numbering manager
    init_numbering_manager();
    // Initialize styles collection
    styles_ = std::make_unique<StyleCollection>(this);
}

Document::Document(const std::string& filepath)
    : filepath_(filepath), is_open_(false), zip_handle_(nullptr), zip_dirty_(false),
      sections_dirty_(true), next_header_number_(1), next_footer_number_(1),
      next_bookmark_id_(1) {
    // Initialize numbering manager
    init_numbering_manager();
    // Initialize styles collection
    styles_ = std::make_unique<StyleCollection>(this);
}

Document::~Document() {
    close();
}

Document::Document(Document&& other) noexcept
    : CompositeNode(std::move(other)),
      filepath_(std::move(other.filepath_)),
      is_open_(other.is_open_),
      load_config_(std::move(other.load_config_)),
      tree_(std::move(other.tree_)),
      xml_parts_cache_(std::move(other.xml_parts_cache_)),
      media_files_cache_(std::move(other.media_files_cache_)),
      relationships_(std::move(other.relationships_)),
      modified_parts_(std::move(other.modified_parts_)),
      content_types_(std::move(other.content_types_)),
      zip_handle_(other.zip_handle_),
      zip_dirty_(other.zip_dirty_),
      last_load_stats_(other.last_load_stats_),
      last_load_result_(std::move(other.last_load_result_)),
      sections_cache_(std::move(other.sections_cache_)),
      sections_dirty_(other.sections_dirty_),
      numbering_manager_(std::move(other.numbering_manager_)),
      styles_(std::move(other.styles_)),
      builtin_properties_(std::move(other.builtin_properties_)),
      custom_properties_(std::move(other.custom_properties_)),
      next_header_number_(other.next_header_number_),
      next_footer_number_(other.next_footer_number_),
      next_bookmark_id_(other.next_bookmark_id_),
      default_section_properties_(other.default_section_properties_),
      impl_(std::move(other.impl_)) {
    other.is_open_ = false;
    other.zip_handle_ = nullptr;
    other.sections_dirty_ = true;
}

Document& Document::operator=(Document&& other) noexcept {
    if (this != &other) {
        CompositeNode::operator=(std::move(other));
        filepath_ = std::move(other.filepath_);
        is_open_ = other.is_open_;
        load_config_ = std::move(other.load_config_);
        tree_ = std::move(other.tree_);

        xml_parts_cache_ = std::move(other.xml_parts_cache_);
        media_files_cache_ = std::move(other.media_files_cache_);
        relationships_ = std::move(other.relationships_);
        modified_parts_ = std::move(other.modified_parts_);
        content_types_ = std::move(other.content_types_);

        last_load_stats_ = other.last_load_stats_;
        last_load_result_ = std::move(other.last_load_result_);
        sections_cache_ = std::move(other.sections_cache_);
        sections_dirty_ = other.sections_dirty_;
        numbering_manager_ = std::move(other.numbering_manager_);
        styles_ = std::move(other.styles_);
        builtin_properties_ = std::move(other.builtin_properties_);
        custom_properties_ = std::move(other.custom_properties_);
        next_header_number_ = other.next_header_number_;
        next_footer_number_ = other.next_footer_number_;
        next_bookmark_id_ = other.next_bookmark_id_;
        default_section_properties_ = other.default_section_properties_;
        impl_ = std::move(other.impl_);
        
        other.is_open_ = false;
        other.zip_handle_ = nullptr;
        other.sections_dirty_ = true;
    }
    return *this;
}

// ============================================================================
// Node Overrides
// ============================================================================

void Document::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    
    if (visitor->visit_document_start(*this) == VisitorAction::Continue) {
        // Visit all sections
        for (const auto& section : get_sections()) {
            section->accept(visitor);
        }
        visitor->visit_document_end(*this);
    }
}

std::shared_ptr<Node> Document::clone(bool deep) const {
    auto cloned = std::make_shared<Document>();
    cloned->filepath_ = filepath_;
    cloned->default_section_properties_ = default_section_properties_;
    
    if (deep) {
        for (const auto& section : get_sections()) {
            if (auto section_clone = std::dynamic_pointer_cast<Section>(section->clone(deep))) {
                cloned->append_child(section_clone);
            }
        }
    }
    
    return cloned;
}

// ============================================================================
// File Operations
// ============================================================================

void Document::open() {
    if (filepath_.empty()) {
        return;
    }
    open(filepath_);
}

void Document::open(const std::string& filepath) {
    open(filepath, nullptr);
}

void Document::open(const std::string& filepath, 
                    std::function<void(int, const std::string&)> callback) {
    // Close any currently open document first
    close();
    
    filepath_ = filepath;
    
    // Set up load configuration with progress callback
    LoadConfig config;
    config.progress_callback = std::move(callback);
    load_config_ = config;
    
    // Use the new load with result
    auto result = open_with_config(filepath, config);
    
    if (!result.is_usable()) {
        close();
        return;
    }
    
    is_open_ = true;
    sections_dirty_ = true;
}

LoadResult Document::open_with_config(const std::string& filepath, const LoadConfig& config) {
    // Close any currently open document first
    close();
    
    filepath_ = filepath;
    load_config_ = config;
    
    // Open the ZIP archive
    if (!open_zip(filepath)) {
        LoadResult result;
        result.success = false;
        result.errors.emplace_back(LoadErrorType::ZipOpenFailed, filepath, 
                                   "Failed to open ZIP file");
        result.integrity = DocumentIntegrity::Corrupted;
        last_load_result_ = result;
        return result;
    }
    
    // Load document tree with full result
    auto result = load_tree_with_result();
    
    if (!result.is_usable() && !config.allow_partial_load) {
        close();
        return result;
    }
    
    // Build quick-access caches from tree
    build_caches_from_tree();
    
    // Load relationships from all _rels files
    load_all_relationships();
    
    // Load content types
    load_content_types();
    
    is_open_ = result.is_usable();
    sections_dirty_ = true;
    
    // Sync DOM from physical tree
    if (is_open_) {
        sync_from_physical_tree();
        sync_styles_from_physical();
    }

    return result;
}

void Document::close() {
    // Close ZIP handle
    close_zip();
    
    // Clear all internal structures
    tree_.clear();
    xml_parts_cache_.clear();
    media_files_cache_.clear();
    relationships_.clear();
    modified_parts_.clear();
    content_types_.clear();
    sections_cache_.clear();
    if (styles_) {
        styles_->clear();
    }

    is_open_ = false;
    sections_dirty_ = true;
}

void Document::save() {
    if (!is_open() || filepath_.empty()) {
        return;
    }
    save(filepath_);
}

void Document::save(const std::string& filepath) {
    if (!is_open()) {
        return;
    }
    
    // Sync DOM to physical tree
    sync_to_physical_tree();

    // Save styles to physical tree
    sync_styles_to_physical();

    // Save numbering definitions (create/update numbering.xml)
    save_numbering();
    
    // Update all modified relationship files
    for (const auto& rels_pair : relationships_) {
        update_relationships_xml(rels_pair.first);
    }
    
    // Update content types XML
    update_content_types_xml();
    
    // Save to ZIP file
    if (!save_to_zip(filepath)) {
        return;
    }
    
    // Clear modification flags after successful save
    tree_.iterate_all([](const std::shared_ptr<DocxTreeNode>& node) {
        node->is_modified = false;
        node->is_new = false;
    });
    modified_parts_.clear();
    
    zip_dirty_ = true;
}

void Document::protect(ProtectionType type, const std::string& password) {
    pugi::xml_document* settings = get_settings();
    if (!settings) return;

    pugi::xml_node root = settings->child("w:settings");
    if (!root) return;

    // Remove existing protection
    root.remove_child("w:documentProtection");

    auto docProt = root.append_child("w:documentProtection");

    const char* edit_val = nullptr;
    switch (type) {
        case ProtectionType::AllowOnlyRevisions:  edit_val = "trackedChanges"; break;
        case ProtectionType::AllowOnlyComments:   edit_val = "comments"; break;
        case ProtectionType::AllowOnlyFormFields: edit_val = "forms"; break;
        case ProtectionType::ReadOnly:            edit_val = "readOnly"; break;
        default:                                  edit_val = "none"; break;
    }

    if (edit_val) {
        docProt.append_attribute("w:edit").set_value(edit_val);
    }
    docProt.append_attribute("w:enforcement").set_value("1");

    if (!password.empty()) {
        // Word uses a specific password hashing algorithm.
        // For simplicity, we store a placeholder indicating password protection.
        // A production implementation would compute the proper SHA-1 hash with salt.
        docProt.append_attribute("w:cryptProviderType").set_value("rsaFull");
        docProt.append_attribute("w:cryptAlgorithmClass").set_value("hash");
        docProt.append_attribute("w:cryptAlgorithmType").set_value("typeAny");
        docProt.append_attribute("w:cryptAlgorithmSid").set_value("14");
        docProt.append_attribute("w:cryptSpinCount").set_value("100000");
        docProt.append_attribute("w:hash").set_value("");
        docProt.append_attribute("w:salt").set_value("");
    }

    mark_modified("word/settings.xml");
}

void Document::unprotect() {
    pugi::xml_document* settings = get_settings();
    if (!settings) return;

    pugi::xml_node root = settings->child("w:settings");
    if (!root) return;

    root.remove_child("w:documentProtection");
    mark_modified("word/settings.xml");
}

bool Document::is_protected() const {
    pugi::xml_document* settings = const_cast<Document*>(this)->get_settings();
    if (!settings) return false;

    pugi::xml_node root = settings->child("w:settings");
    if (!root) return false;

    pugi::xml_node docProt = root.child("w:documentProtection");
    if (!docProt) return false;

    pugi::xml_attribute enforcement = docProt.attribute("w:enforcement");
    return enforcement && std::strcmp(enforcement.value(), "1") == 0;
}

Watermark Document::watermark() {
    return Watermark(this);
}

double Document::get_default_tab_stop() const {
    pugi::xml_document* settings = const_cast<Document*>(this)->get_settings();
    if (!settings) return 36.0;  // Word default: 0.5 inch = 36 points

    pugi::xml_node root = settings->child("w:settings");
    if (!root) return 36.0;

    pugi::xml_node defaultTabStop = root.child("w:defaultTabStop");
    if (!defaultTabStop) return 36.0;

    int twips = defaultTabStop.attribute("w:val").as_int(720);
    return twips / 20.0;  // twips to points
}

void Document::set_default_tab_stop(double points) {
    pugi::xml_document* settings = get_settings();
    if (!settings) return;

    pugi::xml_node root = settings->child("w:settings");
    if (!root) return;

    root.remove_child("w:defaultTabStop");
    auto dts = root.append_child("w:defaultTabStop");
    dts.append_attribute("w:val").set_value(static_cast<int>(points * 20));  // points to twips

    mark_modified("word/settings.xml");
}

bool Document::create_empty(const std::string& filepath) {
    close();
    
    if (!filepath.empty()) {
        filepath_ = filepath;
    }
    
    // Create all required XML parts for an empty document
    if (!create_empty_document()) {
        close();
        return false;
    }
    
    is_open_ = true;
    sections_dirty_ = true;
    
    // Sync XML to DOM so get_first_section() etc work immediately
    sync_from_physical_tree();
    
    return true;
}

void Document::clear() {
    close();
    filepath_.clear();
}

// ============================================================================
// Section Management
// ============================================================================

SectionCollection Document::get_sections() const {
    if (sections_dirty_) {
        // Rebuild sections cache from DOM
        sections_cache_.clear();
        for (const auto& child : get_children()) {
            if (auto section = std::dynamic_pointer_cast<Section>(child)) {
                sections_cache_.push_back(section);
            }
        }
        sections_dirty_ = false;
    }
    
    return SectionCollection(sections_cache_);
}

std::shared_ptr<Section> Document::get_first_section() const {
    auto sections = get_sections();
    return sections.first();
}

std::shared_ptr<Section> Document::get_last_section() const {
    auto sections = get_sections();
    return sections.last();
}

std::shared_ptr<Section> Document::append_section() {
    auto section = std::make_shared<Section>(const_cast<Document*>(this));
    section->set_properties(default_section_properties_);
    
    // Create body for the section
    auto body = std::make_shared<Body>(const_cast<Document*>(this));
    section->set_body(body);
    
    const_cast<Document*>(this)->append_child(section);
    sections_dirty_ = true;
    
    return section;
}

std::shared_ptr<Section> Document::insert_section(int index) {
    auto section = std::make_shared<Section>(this);
    section->set_properties(default_section_properties_);
    
    // Create body for the section
    auto body = std::make_shared<Body>(this);
    section->set_body(body);
    
    insert_child(index, section);
    sections_dirty_ = true;
    
    return section;
}

void Document::remove_section(const std::shared_ptr<Section>& section) {
    if (!section) return;
    
    remove_child(section);
    sections_dirty_ = true;
}

size_t Document::get_section_count() const {
    return get_sections().get_count();
}

std::shared_ptr<Section> Document::get_section(size_t index) const {
    auto sections = get_sections();
    return sections.get_item(static_cast<int>(index));
}

std::shared_ptr<Section> Document::get_previous_section(const Section* section) const {
    if (!section) return nullptr;
    auto sections = get_sections();
    for (size_t i = 0; i < sections.get_count(); ++i) {
        if (sections.get_item(static_cast<int>(i)).get() == section) {
            if (i > 0) {
                return sections.get_item(static_cast<int>(i - 1));
            }
            break;
        }
    }
    return nullptr;
}

ParagraphCollection Document::get_paragraphs() const {
    std::vector<std::shared_ptr<Paragraph>> all_paragraphs;
    
    for (const auto& section : get_sections()) {
        if (auto body = section->get_body()) {
            auto paras = body->get_paragraphs();
            all_paragraphs.insert(all_paragraphs.end(), paras.begin(), paras.end());
        }
    }
    
    return ParagraphCollection(all_paragraphs);
}

Paragraph Document::paragraphs() {
    // Legacy API: return Paragraph iterator pointing to first paragraph in document
    Paragraph para;
    
    if (!is_open_) {
        return para;
    }
    
    // Get document.xml
    auto doc_xml = get_document_xml();
    if (!doc_xml) {
        return para;
    }
    
    // Find body element
    auto body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return para;
    }
    
    // Find first paragraph
    auto first_para = body.child("w:p");
    if (!first_para) {
        // No paragraph found, create one
        return para;
    }
    
    para.set_parent(body);
    para.set_current(first_para);
    return para;
}

TableCollection Document::get_tables() const {
    std::vector<std::shared_ptr<Table>> all_tables;

    for (const auto& section : get_sections()) {
        if (auto body = section->get_body()) {
            auto tables = body->get_tables();
            all_tables.insert(all_tables.end(), tables.begin(), tables.end());
        }
    }

    return TableCollection(all_tables);
}

void Document::ensure_minimum() {
    if (get_section_count() == 0) {
        append_section();
    }

    auto sections = get_sections();
    for (auto& section : sections) {
        auto body = section->get_body();
        if (body) {
            body->ensure_minimum();
        }
    }
}

Range Document::get_range() {
    pugi::xml_document* doc_xml = get_document_xml();
    if (!doc_xml) {
        return Range();
    }

    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    pugi::xml_node first_para = body.child("w:p");
    pugi::xml_node last_para;
    for (pugi::xml_node para = first_para; para; para = para.next_sibling("w:p")) {
        last_para = para;
    }

    if (!first_para) {
        return Range();
    }

    return Range(this, first_para, last_para);
}

void Document::set_default_section_properties(const SectionProperties& props) {
    default_section_properties_ = props;
}

SectionProperties Document::get_default_section_properties() const {
    return default_section_properties_;
}

// ============================================================================
// Numbering (List) Support
// ============================================================================

NumberingId Document::add_bulleted_list_definition() {
    if (!numbering_manager_) {
        init_numbering_manager();
    }
    return numbering_manager_->add_bulleted_list_definition();
}

NumberingId Document::add_numbered_list_definition(NumberStyle style) {
    if (!numbering_manager_) {
        init_numbering_manager();
    }
    return numbering_manager_->add_numbered_list_definition(style);
}

NumberingId Document::add_chinese_numbered_list_definition() {
    if (!numbering_manager_) {
        init_numbering_manager();
    }
    return numbering_manager_->add_chinese_numbered_list_definition();
}

NumberingId Document::add_outline_list_definition() {
    if (!numbering_manager_) {
        init_numbering_manager();
    }
    return numbering_manager_->add_outline_list_definition();
}

const NumberingDefinition* Document::get_numbering_definition(NumberingId id) const {
    if (!numbering_manager_) {
        return nullptr;
    }
    return numbering_manager_->get_numbering_definition(id);
}

// ============================================================================
// XML Parts API
// ============================================================================

pugi::xml_document* Document::get_xml_part(const std::string& part_path) {
    auto node = tree_.find_node(part_path);
    if (node && node->xml_doc) {
        return node->xml_doc.get();
    }
    return nullptr;
}

const pugi::xml_document* Document::get_xml_part(const std::string& part_path) const {
    auto node = tree_.find_node(part_path);
    if (node && node->xml_doc) {
        return node->xml_doc.get();
    }
    return nullptr;
}

bool Document::has_xml_part(const std::string& part_path) const {
    auto node = tree_.find_node(part_path);
    return node && node->type == DocxNodeType::XmlFile;
}

std::vector<std::string> Document::get_all_part_names() const {
    std::vector<std::string> names;
    tree_.iterate_files([&names](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->type == DocxNodeType::XmlFile) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

size_t Document::get_part_count() const {
    size_t count = 0;
    tree_.iterate_files([&count](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->type == DocxNodeType::XmlFile) {
            count++;
        }
    });
    return count;
}

pugi::xml_document& Document::create_xml_part(const std::string& part_path) {
    auto node = tree_.find_or_create_node(part_path, DocxNodeType::XmlFile);
    if (!node->xml_doc) {
        node->xml_doc = std::make_shared<pugi::xml_document>();
    }
    node->is_new = true;
    node->is_modified = true;
    modified_parts_.insert(part_path);
    xml_parts_cache_[part_path] = node;
    return *node->xml_doc;
}

void Document::remove_xml_part(const std::string& part_path) {
    auto node = tree_.find_node(part_path);
    if (node) {
        node->is_deleted = true;
    }
    xml_parts_cache_.erase(part_path);
    modified_parts_.erase(part_path);
}

void Document::mark_modified(const std::string& part_path) {
    modified_parts_.insert(part_path);
    auto node = tree_.find_node(part_path);
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

StyleCollection& Document::styles() {
    if (!styles_) {
        styles_ = std::make_unique<StyleCollection>(this);
    }
    return *styles_;
}

const StyleCollection& Document::styles() const {
    if (!styles_) {
        const_cast<Document*>(this)->styles_ = std::make_unique<StyleCollection>(
            const_cast<Document*>(this));
    }
    return *styles_;
}

pugi::xml_document* Document::get_settings() {
    return get_xml_part("word/settings.xml");
}

pugi::xml_document* Document::get_font_table() {
    return get_xml_part("word/fontTable.xml");
}

pugi::xml_document* Document::get_numbering_xml() {
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
    tree_.iterate_files([&names](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->full_path.find("word/header") != std::string::npos &&
            node->full_path.find(".xml") != std::string::npos) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

std::vector<std::string> Document::get_footer_names() const {
    std::vector<std::string> names;
    tree_.iterate_files([&names](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->full_path.find("word/footer") != std::string::npos &&
            node->full_path.find(".xml") != std::string::npos) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

int Document::get_next_header_number() {
    return next_header_number_++;
}

int Document::get_next_footer_number() {
    return next_footer_number_++;
}

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
    
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
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
    
    std::string media_path = "word/media/" + name;
    
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
    
    return add_relationship("word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
        "media/" + name);
}

bool Document::delete_media(const std::string& image_name) {
    if (!is_open()) {
        return false;
    }
    
    std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    if (!node) {
        return false;
    }
    
    node->is_deleted = true;
    
    // Remove relationship if exists
    std::string target = "media/" + image_name;
    std::string rel_id = find_relationship_id("word/_rels/document.xml.rels", target);
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
    
    std::string media_path = "word/media/" + image_name;
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

static bool string_ends_with(const std::string& str, const std::string& suffix) {
    if (suffix.size() > str.size()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

bool Document::has_media(const std::string& image_name) const {
    if (!is_open()) {
        return false;
    }
    std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    return node && !node->is_deleted;
}

std::vector<std::string> Document::list_media() const {
    std::vector<std::string> result;
    tree_.iterate_files([&result](const std::shared_ptr<DocxTreeNode>& node) {
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
    if (!is_open()) {
        return false;
    }
    
    std::string media_path = "word/media/" + image_name;
    auto node = tree_.find_node(media_path);
    if (!node || node->is_deleted) {
        return false;
    }
    
    std::ofstream file(output_path, std::ios::binary);
    if (!file) {
        return false;
    }
    
    file.write(reinterpret_cast<const char*>(node->binary_data.data()), 
               node->binary_data.size());
    
    return file.good();
}

std::vector<uint8_t> Document::get_media_data(const std::string& image_name) const {
    std::vector<uint8_t> result;
    if (!is_open()) {
        return result;
    }
    
    std::string media_path = "word/media/" + image_name;
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
    
    std::string name = (image_name && !image_name->empty()) ? *image_name 
        : std::filesystem::path(image_path).filename().string();
    
    return add_relationship("word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
        "media/" + name);
}

// ============================================================================
// Bookmark Management
// ============================================================================

BookmarkCollection Document::get_bookmarks() {
    sync_to_physical_tree();
    sync_from_physical_tree();
    return BookmarkCollection(this);
}

int Document::generate_unique_bookmark_id() {
    return next_bookmark_id_++;
}

// ============================================================================
// Comment Management
// ============================================================================

std::shared_ptr<Comment> Document::add_comment(const std::string& author, const std::string& text) {
    auto comment = std::make_shared<Comment>(this, author, text);
    comment->set_id(get_next_comment_id());
    comments_cache_.push_back(comment);
    comments_dirty_ = false;

    // Ensure comments.xml exists
    pugi::xml_document* comments_xml = get_xml_part("word/comments.xml");
    if (!comments_xml) {
        comments_xml = &create_xml_part("word/comments.xml");
        auto root = comments_xml->append_child("w:comments");
        root.append_attribute("xmlns:w").set_value("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:w14").set_value("http://schemas.microsoft.com/office/word/2010/wordml");
        root.append_attribute("xmlns:w15").set_value("http://schemas.microsoft.com/office/word/2012/wordml");
    }

    // Add content type override if needed
    add_content_type_override("/word/comments.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.comments+xml");

    // Add relationship if needed
    add_relationship("word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/comments",
        "comments.xml");

    mark_modified("word/comments.xml");
    return comment;
}

std::shared_ptr<Comment> Document::get_comment(int id) const {
    for (const auto& comment : comments_cache_) {
        if (comment->get_id() == id) {
            return comment;
        }
    }
    return nullptr;
}

CommentCollection Document::get_comments() const {
    return CommentCollection(const_cast<Document*>(this));
}

bool Document::remove_comment(int id) {
    auto it = std::remove_if(comments_cache_.begin(), comments_cache_.end(),
        [id](const std::shared_ptr<Comment>& c) { return c->get_id() == id; });
    if (it != comments_cache_.end()) {
        comments_cache_.erase(it, comments_cache_.end());
        mark_modified("word/comments.xml");
        return true;
    }
    return false;
}

void Document::clear_comments() {
    comments_cache_.clear();
    mark_modified("word/comments.xml");
}

int Document::get_next_comment_id() {
    return next_comment_id_++;
}

// ============================================================================
// Sync Methods (implemented in document_sync.cpp)
// ============================================================================

// ============================================================================
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
    if (!zip_handle_) return data;
    
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
    if (!zip_handle_) return false;
    
    int n = zip_entries_total(zip_handle_);
    if (n < 0) return false;
    
    tree_.clear();
    
    zip_entry_openbyindex(zip_handle_, 0);
    
    for (int i = 0; i < n; i++) {
        zip_entry_openbyindex(zip_handle_, i);
        
        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        std::string entry_name(name);
        bool is_dir = zip_entry_isdir(zip_handle_);
        
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
        
        std::vector<uint8_t> data(static_cast<uint8_t*>(buf), 
                                  static_cast<uint8_t*>(buf) + bufsize);
        free(buf);
        
        // Add to tree
        auto node = tree_.add_zip_entry(entry_name, data);
        
        // Parse XML files
        if (string_ends_with(entry_name, ".xml") || string_ends_with(entry_name, ".rels")) {
            node->type = DocxNodeType::XmlFile;
            node->xml_doc = std::make_shared<pugi::xml_document>();
            
            pugi::xml_parse_result result = node->xml_doc->load_buffer(
                data.data(), data.size(), 
                pugi::parse_default | pugi::parse_declaration);
            
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
        result.errors.emplace_back(LoadErrorType::ZipOpenFailed, filepath_, 
                                   "ZIP handle is null");
        result.integrity = DocumentIntegrity::Corrupted;
        last_load_result_ = result;
        return result;
    }
    
    int n = zip_entries_total(zip_handle_);
    if (n < 0) {
        result.success = false;
        result.errors.emplace_back(LoadErrorType::ZipOpenFailed, filepath_, 
                                   "Failed to get entry count");
        result.integrity = DocumentIntegrity::Corrupted;
        last_load_result_ = result;
        return result;
    }
    
    result.total_files = static_cast<size_t>(n);
    last_load_stats_.total_entries = result.total_files;
    
    tree_.clear();
    
    for (int i = 0; i < n; i++) {
        if (zip_entry_openbyindex(zip_handle_, i) != 0) {
            result.errors.emplace_back(LoadErrorType::ZipEntryReadFailed, "", 
                                       "Failed to open entry " + std::to_string(i));
            continue;
        }
        
        const char* name = zip_entry_name(zip_handle_);
        if (!name) {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        std::string entry_name(name);
        
        if (zip_entry_isdir(zip_handle_)) {
            zip_entry_close(zip_handle_);
            continue;
        }
        
        // Read entry data
        void* buf = nullptr;
        size_t bufsize = 0;
        
        if (zip_entry_read(zip_handle_, &buf, &bufsize) < 0) {
            result.errors.emplace_back(LoadErrorType::ZipEntryReadFailed, entry_name, 
                                       "Failed to read entry");
            zip_entry_close(zip_handle_);
            continue;
        }
        
        std::vector<uint8_t> data(static_cast<uint8_t*>(buf), 
                                  static_cast<uint8_t*>(buf) + bufsize);
        free(buf);
        
        // Add to tree
        auto node = tree_.add_zip_entry(entry_name, data);
        
        // Parse XML files
        if (string_ends_with(entry_name, ".xml") || string_ends_with(entry_name, ".rels")) {
            node->type = DocxNodeType::XmlFile;
            node->xml_doc = std::make_shared<pugi::xml_document>();
            
            pugi::xml_parse_result parse_result = node->xml_doc->load_buffer(
                data.data(), data.size(), 
                pugi::parse_default | pugi::parse_declaration);
            
            if (parse_result) {
                last_load_stats_.xml_files++;
            } else {
                result.errors.emplace_back(LoadErrorType::XmlParseFailed, entry_name, 
                                           "Failed to parse XML");
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
            int percent = static_cast<int>((i + 1) * 100 / n);
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
    // TODO: Implement parallel loading
    return load_tree_from_zip();
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

// ============================================================================
// Content Types and Relationships
// ============================================================================

bool Document::load_content_types() {
    auto* content_types = get_content_types();
    if (!content_types) return false;
    
    content_types_.clear();
    
    auto root = content_types->child("Types");
    if (!root) return false;
    
    for (auto def = root.child("Default"); def; def = def.next_sibling("Default")) {
        ContentType ct;
        ct.extension = def.attribute("Extension").value();
        ct.content_type = def.attribute("ContentType").value();
        ct.is_default = true;
        content_types_.push_back(ct);
    }
    
    for (auto override = root.child("Override"); override; 
         override = override.next_sibling("Override")) {
        ContentType ct;
        ct.part_name = override.attribute("PartName").value();
        ct.content_type = override.attribute("ContentType").value();
        ct.is_default = false;
        content_types_.push_back(ct);
    }
    
    return true;
}

void Document::parse_relationships(const std::string& rels_path) {
    auto* rels_doc = get_xml_part(rels_path);
    if (!rels_doc) return;
    
    auto root = rels_doc->child("Relationships");
    if (!root) return;
    
    std::vector<Relationship> rels;
    
    for (auto rel = root.child("Relationship"); rel; 
         rel = rel.next_sibling("Relationship")) {
        Relationship r;
        r.id = rel.attribute("Id").value();
        r.type = rel.attribute("Type").value();
        r.target = rel.attribute("Target").value();
        r.target_mode = rel.attribute("TargetMode").value();
        rels.push_back(r);
    }
    
    relationships_[rels_path] = rels;
}

void Document::load_all_relationships() {
    parse_relationships("_rels/.rels");
    parse_relationships("word/_rels/document.xml.rels");
    
    // Load header/footer relationships
    for (int i = 1; ; i++) {
        std::string path = "word/_rels/header" + std::to_string(i) + ".xml.rels";
        if (!has_xml_part(path)) break;
        parse_relationships(path);
    }
    
    for (int i = 1; ; i++) {
        std::string path = "word/_rels/footer" + std::to_string(i) + ".xml.rels";
        if (!has_xml_part(path)) break;
        parse_relationships(path);
    }
}

std::string Document::add_relationship(const std::string& rels_path, 
                                       const std::string& type, 
                                       const std::string& target, 
                                       const std::string& target_mode) {
    // Find next available rId
    int max_id = 0;
    for (const auto& rel : relationships_[rels_path]) {
        if (rel.id.substr(0, 3) == "rId") {
            int id = std::stoi(rel.id.substr(3));
            max_id = std::max(max_id, id);
        }
    }
    
    std::string new_id = "rId" + std::to_string(max_id + 1);
    
    Relationship r;
    r.id = new_id;
    r.type = type;
    r.target = target;
    r.target_mode = target_mode;
    relationships_[rels_path].push_back(r);
    
    modified_parts_.insert(rels_path);
    
    return new_id;
}

void Document::remove_relationship(const std::string& rels_path, const std::string& rel_id) {
    auto& rels = relationships_[rels_path];
    rels.erase(std::remove_if(rels.begin(), rels.end(),
                              [&rel_id](const Relationship& r) { return r.id == rel_id; }),
               rels.end());
    modified_parts_.insert(rels_path);
}

std::string Document::find_relationship_id(const std::string& rels_path,
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

std::string Document::get_relationship_target(const std::string& rels_path,
                                              const std::string& rel_id) const {
    auto it = relationships_.find(rels_path);
    if (it == relationships_.end()) return "";

    for (const auto& rel : it->second) {
        if (rel.id == rel_id) {
            return rel.target;
        }
    }
    return "";
}

void Document::update_relationships_xml(const std::string& rels_path) {
    auto& rels = relationships_[rels_path];
    if (rels.empty()) return;
    
    // Create or update the relationships XML
    pugi::xml_document* doc = nullptr;
    
    if (has_xml_part(rels_path)) {
        doc = get_xml_part(rels_path);
        doc->reset();
    } else {
        doc = &create_xml_part(rels_path);
    }
    
    auto root = doc->append_child("Relationships");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/relationships");
    
    for (const auto& rel : rels) {
        auto rel_node = root.append_child("Relationship");
        rel_node.append_attribute("Id").set_value(rel.id.c_str());
        rel_node.append_attribute("Type").set_value(rel.type.c_str());
        rel_node.append_attribute("Target").set_value(rel.target.c_str());
        if (!rel.target_mode.empty()) {
            rel_node.append_attribute("TargetMode").set_value(rel.target_mode.c_str());
        }
    }
}

void Document::add_content_type_override(const std::string& part_name, 
                                         const std::string& content_type) {
    // Check if already exists
    for (auto& ct : content_types_) {
        if (ct.part_name == part_name) {
            ct.content_type = content_type;
            return;
        }
    }
    
    ContentType ct;
    ct.part_name = part_name;
    ct.content_type = content_type;
    ct.is_default = false;
    content_types_.push_back(ct);
    
    modified_parts_.insert("[Content_Types].xml");
}

void Document::update_content_types_xml() {
    if (content_types_.empty()) return;
    
    pugi::xml_document* doc = nullptr;
    
    if (has_xml_part("[Content_Types].xml")) {
        doc = get_content_types();
        doc->reset();
    } else {
        doc = &create_xml_part("[Content_Types].xml");
    }
    
    auto root = doc->append_child("Types");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/package/2006/content-types");
    
    // Add defaults first
    for (const auto& ct : content_types_) {
        if (ct.is_default) {
            auto def = root.append_child("Default");
            def.append_attribute("Extension").set_value(ct.extension.c_str());
            def.append_attribute("ContentType").set_value(ct.content_type.c_str());
        }
    }
    
    // Then overrides
    for (const auto& ct : content_types_) {
        if (!ct.is_default) {
            auto override = root.append_child("Override");
            override.append_attribute("PartName").set_value(ct.part_name.c_str());
            override.append_attribute("ContentType").set_value(ct.content_type.c_str());
        }
    }
}

// ============================================================================
// Save Operations
// ============================================================================

bool Document::save_to_zip(const std::string& output_path) {
    zip_t* zip = zip_open(output_path.c_str(), 9, 'w');
    if (!zip) {
        return false;
    }
    
    bool success = save_tree_to_zip(zip);
    
    zip_close(zip);
    return success;
}

bool Document::save_tree_to_zip(zip_t* zip) {
    if (!zip) return false;
    
    // First pass: create directories
    tree_.iterate_all([zip](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->is_directory() && !node->name.empty()) {
            zip_entry_open(zip, (node->full_path + "/").c_str());
            zip_entry_close(zip);
        }
    });
    
    // Second pass: write files
    tree_.iterate_files([this, zip](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->is_deleted) return;
        
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

bool Document::write_tree_node(zip_t* zip, const std::shared_ptr<DocxTreeNode>& node) {
    // This method is now integrated into save_tree_to_zip
    return true;
}

// ============================================================================
// Media Helpers
// ============================================================================

std::string Document::get_mime_type(const std::string& filename) const {
    std::string ext = std::filesystem::path(filename).extension().string();
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
        {".svg", "image/svg+xml"},
        {".xml", "application/xml"},
        {".rels", "application/vnd.openxmlformats-package.relationships+xml"}
    };
    
    auto it = mime_types.find(ext);
    if (it != mime_types.end()) {
        return it->second;
    }
    return "application/octet-stream";
}

std::string Document::get_extension_from_mime(const std::string& mime_type) const {
    static const std::map<std::string, std::string> ext_map = {
        {"image/png", ".png"},
        {"image/jpeg", ".jpg"},
        {"image/gif", ".gif"},
        {"image/bmp", ".bmp"},
        {"image/tiff", ".tiff"},
        {"image/webp", ".webp"},
        {"image/svg+xml", ".svg"}
    };
    
    auto it = ext_map.find(mime_type);
    if (it != ext_map.end()) {
        return it->second;
    }
    return "";
}

std::string Document::generate_unique_image_name(const std::string& base_name) {
    std::filesystem::path path(base_name);
    std::string stem = path.stem().string();
    std::string ext = path.extension().string();
    
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

// ============================================================================
// Empty Document Creation
// ============================================================================

bool Document::create_empty_document() {
    tree_.clear();
    
    // Create [Content_Types].xml
    {
        auto& doc = create_xml_part("[Content_Types].xml");
        auto root = doc.append_child("Types");
        root.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/package/2006/content-types");
        
        auto rels = root.append_child("Default");
        rels.append_attribute("Extension").set_value("rels");
        rels.append_attribute("ContentType").set_value(
            "application/vnd.openxmlformats-package.relationships+xml");
        
        auto xml = root.append_child("Default");
        xml.append_attribute("Extension").set_value("xml");
        xml.append_attribute("ContentType").set_value("application/xml");
        
        auto doc_override = root.append_child("Override");
        doc_override.append_attribute("PartName").set_value("/word/document.xml");
        doc_override.append_attribute("ContentType").set_value(
            "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml");
    }
    
    // Create _rels/.rels
    {
        auto& doc = create_xml_part("_rels/.rels");
        auto root = doc.append_child("Relationships");
        root.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/package/2006/relationships");

        auto rel1 = root.append_child("Relationship");
        rel1.append_attribute("Id").set_value("rId1");
        rel1.append_attribute("Type").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument");
        rel1.append_attribute("Target").set_value("word/document.xml");

        auto rel2 = root.append_child("Relationship");
        rel2.append_attribute("Id").set_value("rId2");
        rel2.append_attribute("Type").set_value(
            "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties");
        rel2.append_attribute("Target").set_value("docProps/core.xml");

        auto rel3 = root.append_child("Relationship");
        rel3.append_attribute("Id").set_value("rId3");
        rel3.append_attribute("Type").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties");
        rel3.append_attribute("Target").set_value("docProps/app.xml");
    }

    // Create word/_rels/document.xml.rels
    {
        auto& doc = create_xml_part("word/_rels/document.xml.rels");
        auto root = doc.append_child("Relationships");
        root.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/package/2006/relationships");

        auto add_rel = [&root](const char* id, const char* type, const char* target) {
            auto rel = root.append_child("Relationship");
            rel.append_attribute("Id").set_value(id);
            rel.append_attribute("Type").set_value(type);
            rel.append_attribute("Target").set_value(target);
        };

        add_rel("rId1", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles",
                "styles.xml");
        add_rel("rId2", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/settings",
                "settings.xml");
        add_rel("rId3", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/fontTable",
                "fontTable.xml");
        add_rel("rId4", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme",
                "theme/theme1.xml");
    }

    // Create word/document.xml
    {
        auto& doc = create_xml_part("word/document.xml");
        auto root = doc.append_child("w:document");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");

        auto body = root.append_child("w:body");

        // Add empty paragraph
        auto para = body.append_child("w:p");
        auto run = para.append_child("w:r");
        run.append_child("w:t");

        // Add section properties
        auto sectPr = body.append_child("w:sectPr");
        auto pgSz = sectPr.append_child("w:pgSz");
        pgSz.append_attribute("w:w").set_value("12240");
        pgSz.append_attribute("w:h").set_value("15840");

        auto pgMar = sectPr.append_child("w:pgMar");
        pgMar.append_attribute("w:top").set_value("1440");
        pgMar.append_attribute("w:right").set_value("1440");
        pgMar.append_attribute("w:bottom").set_value("1440");
        pgMar.append_attribute("w:left").set_value("1440");
    }

    // Create word/styles.xml with default Normal style
    {
        auto& doc = create_xml_part("word/styles.xml");
        auto root = doc.append_child("w:styles");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");

        auto style = root.append_child("w:style");
        style.append_attribute("w:type").set_value("paragraph");
        style.append_attribute("w:default").set_value("1");
        style.append_attribute("w:styleId").set_value("Normal");

        auto name = style.append_child("w:name");
        name.append_attribute("w:val").set_value("Normal");
    }

    // Create word/settings.xml
    {
        auto& doc = create_xml_part("word/settings.xml");
        auto root = doc.append_child("w:settings");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_child("w:zoom").append_attribute("w:percent").set_value("100");
        root.append_child("w:defaultTabStop").append_attribute("w:val").set_value("720");
        root.append_child("w:characterSpacingControl").append_attribute("w:val").set_value("doNotCompress");
        root.append_child("w:compat");
        root.append_child("w:docVars");
    }

    // Create word/fontTable.xml
    {
        auto& doc = create_xml_part("word/fontTable.xml");
        auto root = doc.append_child("w:fonts");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        auto font = root.append_child("w:font");
        font.append_attribute("w:name").set_value("Calibri");
        font.append_child("w:panose1").append_attribute("w:val").set_value("020F0502020204030204");
        font.append_child("w:charset").append_attribute("w:val").set_value("00");
        font.append_child("w:family").append_attribute("w:val").set_value("swiss");
        font.append_child("w:pitch").append_attribute("w:val").set_value("variable");
    }

    // Create word/theme/theme1.xml
    {
        auto& doc = create_xml_part("word/theme/theme1.xml");
        auto root = doc.append_child("a:theme");
        root.append_attribute("xmlns:a").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/main");
        root.append_attribute("name").set_value("Office Theme");
        auto theme_elem = root.append_child("a:themeElements");
        auto clr_scheme = theme_elem.append_child("a:clrScheme");
        clr_scheme.append_attribute("name").set_value("Office");
        auto font_scheme = theme_elem.append_child("a:fontScheme");
        font_scheme.append_attribute("name").set_value("Office");
        auto fmt_scheme = theme_elem.append_child("a:fmtScheme");
        fmt_scheme.append_attribute("name").set_value("Office");
    }

    // Create docProps/core.xml
    {
        auto& doc = create_xml_part("docProps/core.xml");
        auto root = doc.append_child("cp:coreProperties");
        root.append_attribute("xmlns:cp").set_value(
            "http://schemas.openxmlformats.org/package/2006/metadata/core-properties");
        root.append_attribute("xmlns:dc").set_value("http://purl.org/dc/elements/1.1/");
        root.append_attribute("xmlns:dcterms").set_value("http://purl.org/dc/terms/");
        root.append_attribute("xmlns:dcmitype").set_value("http://purl.org/dc/dcmitype/");
        root.append_attribute("xmlns:xsi").set_value("http://www.w3.org/2001/XMLSchema-instance");
        root.append_child("dc:title");
        root.append_child("dc:subject");
        root.append_child("dc:creator");
        root.append_child("cp:keywords");
        root.append_child("dc:description");
        root.append_child("cp:lastModifiedBy");
        root.append_child("cp:revision").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("dcterms:created").append_attribute("xsi:type").set_value(
            "dcterms:W3CDTF");
        root.append_child("dcterms:modified").append_attribute("xsi:type").set_value(
            "dcterms:W3CDTF");
    }

    // Create docProps/app.xml
    {
        auto& doc = create_xml_part("docProps/app.xml");
        auto root = doc.append_child("Properties");
        root.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties");
        root.append_attribute("xmlns:vt").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");
        root.append_child("Template").append_child(pugi::node_pcdata).set_value("Normal.dotm");
        root.append_child("TotalTime").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Pages").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("Words").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Characters").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Application").append_child(pugi::node_pcdata).set_value("Microsoft Office Word");
        root.append_child("DocSecurity").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Lines").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("Paragraphs").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("Company");
        root.append_child("AppVersion").append_child(pugi::node_pcdata).set_value("16.0000");
    }

    // Register content types for all parts
    add_content_type_override("/word/styles.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml");
    add_content_type_override("/word/settings.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml");
    add_content_type_override("/word/fontTable.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.fontTable+xml");
    add_content_type_override("/word/theme/theme1.xml",
        "application/vnd.openxmlformats-officedocument.theme+xml");
    add_content_type_override("/docProps/core.xml",
        "application/vnd.openxmlformats-package.core-properties+xml");
    add_content_type_override("/docProps/app.xml",
        "application/vnd.openxmlformats-officedocument.extended-properties+xml");
    add_content_type_override("/word/document.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml");

    // Initialize default styles in DOM
    if (styles_) {
        styles_->clear();
        auto normal = std::make_shared<Style>(this, StyleType::Paragraph);
        normal->set_name("Normal");
        normal->set_style_id("Normal");
        normal->set_style_identifier(StyleIdentifier::Normal);
        normal->set_is_built_in(true);
        normal->set_is_default(true);
        styles_->add(normal);
    }

    return true;
}

// ============================================================================
// Numbering
// ============================================================================

void Document::init_numbering_manager() {
    if (!numbering_manager_) {
        numbering_manager_ = std::make_unique<NumberingManager>();
    }
}

void Document::load_numbering() {
    // TODO: Implement loading numbering from XML
}

void Document::save_numbering() {
    if (!numbering_manager_) return;
    
    pugi::xml_document* doc = nullptr;
    if (has_xml_part("word/numbering.xml")) {
        doc = get_numbering_xml();
        if (doc) doc->reset();
    } else {
        doc = &create_xml_part("word/numbering.xml");
        add_content_type_override("/word/numbering.xml",
            "application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml");
    }
    
    if (!doc) return;
    auto root = doc->append_child("w:numbering");
    numbering_manager_->save_to_xml(root);
}

// ============================================================================
// Progress Reporting
// ============================================================================

void Document::report_progress(int percent, const std::string& current_file) {
    if (load_config_.progress_callback) {
        load_config_.progress_callback(percent, current_file);
    }
}

} // namespace cdocx
