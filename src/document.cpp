/**
 * @file document.cpp
 * @brief Document class implementation - DOM Architecture
 * @details Implementation of the Document class using DOM architecture.
 *          Document inherits from CompositeNode and contains Sections.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.8.0 - DOM Architecture
 */

#include <cdocx/advanced.h>
#include <cdocx/base.h>
#include <cdocx/body.h>
#include <cdocx/convert_util.h>
#include <cdocx/comment.h>
#include <cdocx/document.h>
#include <cdocx/footnote.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/style.h>
#include <cdocx/table.h>
#include <cdocx/watermark.h>

#include <algorithm>
#include <cstring>
#include <functional>
#include <utility>
#include <vector>

namespace cdocx {

namespace {

// Default page setup constants (US Letter, 1-inch margins) in twips
// 1 inch = 1440 twips = 72 points * 20 twips/point
constexpr int kTwipsPerInch = 1440;
constexpr int kDefaultPageWidthTwips = 8 * kTwipsPerInch + 720;   // 8.5"
constexpr int kDefaultPageHeightTwips = 11 * kTwipsPerInch;       // 11"
constexpr int kDefaultMarginTwips = kTwipsPerInch;                // 1"
constexpr int kDefaultTabStopTwips = 720;                         // 0.5"

pugi::xml_node get_settings_root(const Document* doc) {
    const pugi::xml_document* settings = doc->get_settings();
    if (!settings) {
        return pugi::xml_node{};
    }
    return settings->child("w:settings");
}

}  // namespace

// ============================================================================
// Constructor / Destructor
// ============================================================================

Document::Document() {
    init_numbering_manager();
    styles_ = std::make_unique<StyleCollection>(this);
}

Document::Document(std::string filepath) : filepath_(std::move(filepath)) {
    init_numbering_manager();
    styles_ = std::make_unique<StyleCollection>(this);
}

Document::~Document() {
    close();
}

// NOLINTBEGIN(bugprone-use-after-move)
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
      default_section_properties_(other.default_section_properties_) {
    other.is_open_ = false;
    other.zip_handle_ = nullptr;
    other.sections_dirty_ = true;
}
// NOLINTEND(bugprone-use-after-move)

// NOLINTBEGIN(bugprone-use-after-move)
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

        other.is_open_ = false;
        other.zip_handle_ = nullptr;
        other.sections_dirty_ = true;
    }
    return *this;
}
// NOLINTEND(bugprone-use-after-move)

// ============================================================================
// Node Overrides
// ============================================================================

void Document::accept(DocumentVisitor* visitor) {
    if (!visitor) {
        return;
    }

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
        result.errors.emplace_back(
            LoadErrorType::ZipOpenFailed, filepath, "Failed to open ZIP file");
        result.integrity = DocumentIntegrity::Corrupted;
        last_load_result_ = result;
        return result;
    }

    // Load document tree with full result
    auto result = load_tree_with_result();

    // All data is now in memory; close the read handle so the file
    // is not locked on Windows (which prevents deletion/rename).
    close_zip();

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
        load_numbering();
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
    last_synced_xml_child_count_ = 0;
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
    pugi::xml_node root = get_settings_root(this);
    if (!root) {
        return;
    }

    // Remove existing protection
    root.remove_child("w:documentProtection");

    auto doc_prot = root.append_child("w:documentProtection");

    struct ProtectionTypeMapping {
        ProtectionType type{};
        const char* xml_value{};
    };
    static const ProtectionTypeMapping kProtectionTypeMappings[] = {
        {ProtectionType::AllowOnlyRevisions, "trackedChanges"},
        {ProtectionType::AllowOnlyComments, "comments"},
        {ProtectionType::AllowOnlyFormFields, "forms"},
        {ProtectionType::ReadOnly, "readOnly"},
    };
    const char* edit_val = "none";
    for (const auto& m : kProtectionTypeMappings) {
        if (m.type == type) {
            edit_val = m.xml_value;
            break;
        }
    }
    doc_prot.append_attribute("w:edit").set_value(edit_val);
    doc_prot.append_attribute("w:enforcement").set_value("1");

    if (!password.empty()) {
        // Word uses a specific password hashing algorithm.
        // For simplicity, we store a placeholder indicating password protection.
        // A production implementation would compute the proper SHA-1 hash with salt.
        doc_prot.append_attribute("w:cryptProviderType").set_value("rsaFull");
        doc_prot.append_attribute("w:cryptAlgorithmClass").set_value("hash");
        doc_prot.append_attribute("w:cryptAlgorithmType").set_value("typeAny");
        doc_prot.append_attribute("w:cryptAlgorithmSid").set_value("14");
        doc_prot.append_attribute("w:cryptSpinCount").set_value("100000");
        doc_prot.append_attribute("w:hash").set_value("");
        doc_prot.append_attribute("w:salt").set_value("");
    }

    mark_modified("word/settings.xml");
}

void Document::unprotect() {
    pugi::xml_node root = get_settings_root(this);
    if (!root) {
        return;
    }

    root.remove_child("w:documentProtection");
    mark_modified("word/settings.xml");
}

bool Document::is_protected() const {
    const pugi::xml_node root = get_settings_root(this);
    if (!root) {
        return false;
    }

    const pugi::xml_node doc_prot = root.child("w:documentProtection");
    if (!doc_prot) {
        return false;
    }

    const pugi::xml_attribute enforcement = doc_prot.attribute("w:enforcement");
    return enforcement && std::strcmp(enforcement.value(), "1") == 0;
}

Watermark Document::watermark() {
    return Watermark(this);
}

double Document::get_default_tab_stop() const {
    const pugi::xml_node root = get_settings_root(this);
    if (!root) {
        return 36.0;  // Word default: 0.5 inch = 36 points
    }

    const pugi::xml_node default_tab_stop = root.child("w:defaultTabStop");
    if (!default_tab_stop) {
        return 36.0;
    }

    const int twips = default_tab_stop.attribute("w:val").as_int(kDefaultTabStopTwips);
    return ConvertUtil::twips_to_point(twips);
}

void Document::set_default_tab_stop(double points) {
    pugi::xml_node root = get_settings_root(this);
    if (!root) {
        return;
    }

    root.remove_child("w:defaultTabStop");
    auto dts = root.append_child("w:defaultTabStop");
    dts.append_attribute("w:val").set_value(ConvertUtil::point_to_twips(points));

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

    // Load relationships into the in-memory map so that subsequent
    // add_relationship() / update_relationships_xml() calls preserve
    // the initial set instead of overwriting them.
    load_all_relationships();

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
    if (!section) {
        return;
    }

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
    if (!section) {
        return nullptr;
    }
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
    auto *doc_xml = get_document_xml();
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
        return {};
    }

    const pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    const pugi::xml_node first_para = body.child("w:p");
    pugi::xml_node last_para;
    for (pugi::xml_node para = first_para; para; para = para.next_sibling("w:p")) {
        last_para = para;
    }

    if (!first_para) {
        return {};
    }

    return {this, first_para, last_para};
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
    init_numbering_manager();
    return numbering_manager_->add_bulleted_list_definition();
}

NumberingId Document::add_numbered_list_definition(NumberStyle style) {
    init_numbering_manager();
    return numbering_manager_->add_numbered_list_definition(style);
}

NumberingId Document::add_chinese_numbered_list_definition() {
    init_numbering_manager();
    return numbering_manager_->add_chinese_numbered_list_definition();
}

NumberingId Document::add_outline_list_definition() {
    init_numbering_manager();
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
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        styles_ = std::make_unique<StyleCollection>(const_cast<Document*>(this));
    }
    return *styles_;
}

pugi::xml_document* Document::get_settings() {
    return get_xml_part("word/settings.xml");
}

const pugi::xml_document* Document::get_settings() const {
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
    const std::string name = "word/header" + std::to_string(index) + ".xml";
    return get_xml_part(name);
}

pugi::xml_document* Document::get_footer(int index) {
    const std::string name = "word/footer" + std::to_string(index) + ".xml";
    return get_xml_part(name);
}

static std::vector<std::string> collect_part_names(const DocxTree& tree, const char* part_prefix) {
    std::vector<std::string> names;
    tree.iterate_files([&names, part_prefix](const std::shared_ptr<DocxTreeNode>& node) {
        if (node->full_path.find(part_prefix) != std::string::npos &&
            node->full_path.find(".xml") != std::string::npos) {
            names.push_back(node->full_path);
        }
    });
    return names;
}

std::vector<std::string> Document::get_header_names() const {
    return collect_part_names(tree_, "word/header");
}

std::vector<std::string> Document::get_footer_names() const {
    return collect_part_names(tree_, "word/footer");
}

int Document::get_next_header_number() {
    return next_header_number_++;
}

int Document::get_next_footer_number() {
    return next_footer_number_++;
}

// Bookmark Management
// ============================================================================

BookmarkCollection Document::get_bookmarks() {
    sync_to_physical_tree();
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
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:w14")
            .set_value("http://schemas.microsoft.com/office/word/2010/wordml");
        root.append_attribute("xmlns:w15")
            .set_value("http://schemas.microsoft.com/office/word/2012/wordml");
    }

    // Add content type override if needed
    add_content_type_override(
        "/word/comments.xml",
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
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return CommentCollection(const_cast<Document*>(this));
}

bool Document::remove_comment(int id) {
    auto it = std::remove_if(comments_cache_.begin(),
                             comments_cache_.end(),
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
// Footnote/Endnote Management
// ============================================================================

std::shared_ptr<Footnote> Document::add_footnote(const std::string& text,
                                                 const std::string& reference_mark) {
    auto footnote = std::make_shared<Footnote>(this, FootnoteType::Footnote);
    footnote->set_id(get_next_footnote_id());
    if (!reference_mark.empty()) {
        footnote->set_reference_mark(reference_mark);
    }
    if (!text.empty()) {
        footnote->set_text(text);
    }
    footnotes_cache_.push_back(footnote);
    footnotes_dirty_ = false;

    // Ensure footnotes.xml exists
    pugi::xml_document* footnotes_xml = get_xml_part("word/footnotes.xml");
    if (!footnotes_xml) {
        footnotes_xml = &create_xml_part("word/footnotes.xml");
        auto root = footnotes_xml->append_child("w:footnotes");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    }

    add_content_type_override(
        "/word/footnotes.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.footnotes+xml");

    add_relationship(
        "word/_rels/document.xml.rels",
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/footnotes",
        "footnotes.xml");

    mark_modified("word/footnotes.xml");
    return footnote;
}

std::shared_ptr<Footnote> Document::add_endnote(const std::string& text,
                                                const std::string& reference_mark) {
    auto endnote = std::make_shared<Footnote>(this, FootnoteType::Endnote);
    endnote->set_id(get_next_endnote_id());
    if (!reference_mark.empty()) {
        endnote->set_reference_mark(reference_mark);
    }
    if (!text.empty()) {
        endnote->set_text(text);
    }
    endnotes_cache_.push_back(endnote);
    endnotes_dirty_ = false;

    // Ensure endnotes.xml exists
    pugi::xml_document* endnotes_xml = get_xml_part("word/endnotes.xml");
    if (!endnotes_xml) {
        endnotes_xml = &create_xml_part("word/endnotes.xml");
        auto root = endnotes_xml->append_child("w:endnotes");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    }

    add_content_type_override(
        "/word/endnotes.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.endnotes+xml");

    add_relationship("word/_rels/document.xml.rels",
                     "http://schemas.openxmlformats.org/officeDocument/2006/relationships/endnotes",
                     "endnotes.xml");

    mark_modified("word/endnotes.xml");
    return endnote;
}

FootnoteCollection Document::footnotes() const {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return FootnoteCollection(const_cast<Document*>(this));
}

EndnoteCollection Document::endnotes() const {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return EndnoteCollection(const_cast<Document*>(this));
}

bool Document::remove_footnote(int id) {
    auto it = std::remove_if(
        footnotes_cache_.begin(), footnotes_cache_.end(), [id](const std::shared_ptr<Footnote>& f) {
            return f->get_id() == id;
        });
    if (it != footnotes_cache_.end()) {
        footnotes_cache_.erase(it, footnotes_cache_.end());
        mark_modified("word/footnotes.xml");
        return true;
    }
    return false;
}

bool Document::remove_endnote(int id) {
    auto it = std::remove_if(
        endnotes_cache_.begin(), endnotes_cache_.end(), [id](const std::shared_ptr<Footnote>& f) {
            return f->get_id() == id;
        });
    if (it != endnotes_cache_.end()) {
        endnotes_cache_.erase(it, endnotes_cache_.end());
        mark_modified("word/endnotes.xml");
        return true;
    }
    return false;
}

void Document::clear_footnotes() {
    footnotes_cache_.clear();
    mark_modified("word/footnotes.xml");
}

void Document::clear_endnotes() {
    endnotes_cache_.clear();
    mark_modified("word/endnotes.xml");
}

int Document::get_next_footnote_id() {
    return next_footnote_id_++;
}

int Document::get_next_endnote_id() {
    return next_endnote_id_++;
}

// ============================================================================
// Sync Methods (implemented in document_sync.cpp)
// ============================================================================

// ============================================================================
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
        rels.append_attribute("ContentType")
            .set_value("application/vnd.openxmlformats-package.relationships+xml");

        auto xml = root.append_child("Default");
        xml.append_attribute("Extension").set_value("xml");
        xml.append_attribute("ContentType").set_value("application/xml");

        auto doc_override = root.append_child("Override");
        doc_override.append_attribute("PartName").set_value("/word/document.xml");
        doc_override.append_attribute("ContentType")
            .set_value(
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
            "http://schemas.openxmlformats.org/package/2006/relationships/metadata/"
            "core-properties");
        rel2.append_attribute("Target").set_value("docProps/core.xml");

        auto rel3 = root.append_child("Relationship");
        rel3.append_attribute("Id").set_value("rId3");
        rel3.append_attribute("Type").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/"
            "extended-properties");
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

        add_rel("rId1",
                "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles",
                "styles.xml");
        add_rel("rId2",
                "http://schemas.openxmlformats.org/officeDocument/2006/relationships/settings",
                "settings.xml");
        add_rel("rId3",
                "http://schemas.openxmlformats.org/officeDocument/2006/relationships/fontTable",
                "fontTable.xml");
        add_rel("rId4",
                "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme",
                "theme/theme1.xml");
        add_rel("rId5",
                "http://schemas.openxmlformats.org/officeDocument/2006/relationships/webSettings",
                "webSettings.xml");
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
        auto sect_pr = body.append_child("w:sectPr");
        auto pg_sz = sect_pr.append_child("w:pgSz");
        pg_sz.append_attribute("w:w").set_value(kDefaultPageWidthTwips);
        pg_sz.append_attribute("w:h").set_value(kDefaultPageHeightTwips);

        auto pg_mar = sect_pr.append_child("w:pgMar");
        pg_mar.append_attribute("w:top").set_value(kDefaultMarginTwips);
        pg_mar.append_attribute("w:right").set_value(kDefaultMarginTwips);
        pg_mar.append_attribute("w:bottom").set_value(kDefaultMarginTwips);
        pg_mar.append_attribute("w:left").set_value(kDefaultMarginTwips);
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
        root.append_child("w:defaultTabStop")
            .append_attribute("w:val")
            .set_value(kDefaultTabStopTwips);
        root.append_child("w:characterSpacingControl")
            .append_attribute("w:val")
            .set_value("doNotCompress");
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

    // Create word/webSettings.xml
    {
        auto& doc = create_xml_part("word/webSettings.xml");
        auto root = doc.append_child("w:webSettings");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_child("w:optimizeForBrowser");
    }

    // Create docProps/core.xml
    {
        auto& doc = create_xml_part("docProps/core.xml");
        auto root = doc.append_child("cp:coreProperties");
        root.append_attribute("xmlns:cp")
            .set_value("http://schemas.openxmlformats.org/package/2006/metadata/core-properties");
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
        root.append_child("dcterms:created")
            .append_attribute("xsi:type")
            .set_value("dcterms:W3CDTF");
        root.append_child("dcterms:modified")
            .append_attribute("xsi:type")
            .set_value("dcterms:W3CDTF");
    }

    // Create docProps/app.xml
    {
        auto& doc = create_xml_part("docProps/app.xml");
        auto root = doc.append_child("Properties");
        root.append_attribute("xmlns").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties");
        root.append_attribute("xmlns:vt")
            .set_value("http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");
        root.append_child("Template").append_child(pugi::node_pcdata).set_value("Normal.dotm");
        root.append_child("TotalTime").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Pages").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("Words").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Characters").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Application")
            .append_child(pugi::node_pcdata)
            .set_value("Microsoft Office Word");
        root.append_child("DocSecurity").append_child(pugi::node_pcdata).set_value("0");
        root.append_child("Lines").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("Paragraphs").append_child(pugi::node_pcdata).set_value("1");
        root.append_child("Company");
        root.append_child("AppVersion").append_child(pugi::node_pcdata).set_value("16.0000");
    }

    // Register content types for all parts
    add_content_type_default("rels", "application/vnd.openxmlformats-package.relationships+xml");
    add_content_type_default("xml", "application/xml");

    add_content_type_override(
        "/word/styles.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml");
    add_content_type_override(
        "/word/settings.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml");
    add_content_type_override(
        "/word/webSettings.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.webSettings+xml");
    add_content_type_override(
        "/word/fontTable.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.fontTable+xml");
    add_content_type_override("/word/theme/theme1.xml",
                              "application/vnd.openxmlformats-officedocument.theme+xml");
    add_content_type_override("/docProps/core.xml",
                              "application/vnd.openxmlformats-package.core-properties+xml");
    add_content_type_override(
        "/docProps/app.xml",
        "application/vnd.openxmlformats-officedocument.extended-properties+xml");
    add_content_type_override(
        "/word/document.xml",
        "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml");

    // Initialize default styles in DOM
    if (styles_) {
        styles_->clear();

        auto add_builtin_style = [this](StyleType type,
                                        const char* style_id,
                                        const char* name,
                                        StyleIdentifier identifier) {
            auto style = std::make_shared<Style>(this, type);
            style->set_style_id(style_id);
            style->set_name(name);
            style->set_style_identifier(identifier);
            style->set_is_built_in(true);
            return style;
        };

        // Normal - default paragraph style
        auto normal =
            add_builtin_style(StyleType::Paragraph, "Normal", "Normal", StyleIdentifier::Normal);
        normal->set_is_default(true);
        styles_->add(normal);

        // Heading 1-9 - paragraph styles with outline levels
        struct HeadingDef {
            const char* style_id;
            const char* name;
            double font_size;
            double space_before;
            StyleIdentifier identifier;
            OutlineLevel outline_level;
        };
        static const HeadingDef kHeadings[] = {
            {"Heading1", "heading 1", 16, 24, StyleIdentifier::Heading1, OutlineLevel::Level1},
            {"Heading2", "heading 2", 14, 18, StyleIdentifier::Heading2, OutlineLevel::Level2},
            {"Heading3", "heading 3", 12, 12, StyleIdentifier::Heading3, OutlineLevel::Level3},
            {"Heading4", "heading 4", 12, 12, StyleIdentifier::Heading4, OutlineLevel::Level4},
            {"Heading5", "heading 5", 11, 12, StyleIdentifier::Heading5, OutlineLevel::Level5},
            {"Heading6", "heading 6", 11, 12, StyleIdentifier::Heading6, OutlineLevel::Level6},
            {"Heading7", "heading 7", 11, 12, StyleIdentifier::Heading7, OutlineLevel::Level7},
            {"Heading8", "heading 8", 11, 12, StyleIdentifier::Heading8, OutlineLevel::Level8},
            {"Heading9", "heading 9", 11, 12, StyleIdentifier::Heading9, OutlineLevel::Level9},
        };
        for (const auto& def : kHeadings) {
            auto heading =
                add_builtin_style(StyleType::Paragraph, def.style_id, def.name, def.identifier);
            heading->set_base_style_name("Normal");
            heading->get_font().bold = true;
            heading->get_font().size = def.font_size;
            heading->get_paragraph_format().space_before = def.space_before;
            heading->get_paragraph_format().space_after = 6;
            heading->get_paragraph_format().keep_with_next = true;
            heading->get_paragraph_format().keep_together = true;
            heading->get_paragraph_format().outline_level = def.outline_level;
            styles_->add(heading);
        }

        // Title
        auto title =
            add_builtin_style(StyleType::Paragraph, "Title", "Title", StyleIdentifier::Title);
        title->set_base_style_name("Normal");
        title->get_font().size = 28;
        title->get_paragraph_format().alignment = ParagraphAlignment::Center;
        title->get_paragraph_format().space_after = 0;
        styles_->add(title);

        // Subtitle
        auto subtitle = add_builtin_style(
            StyleType::Paragraph, "Subtitle", "Subtitle", StyleIdentifier::Subtitle);
        subtitle->set_base_style_name("Normal");
        subtitle->get_font().size = 24;
        subtitle->get_paragraph_format().alignment = ParagraphAlignment::Center;
        subtitle->get_paragraph_format().space_after = 0;
        styles_->add(subtitle);

        // List Paragraph
        auto list_para = add_builtin_style(StyleType::Paragraph,
                                           "ListParagraph",
                                           "List Paragraph",
                                           StyleIdentifier::ListParagraph);
        list_para->set_base_style_name("Normal");
        styles_->add(list_para);

        // Strong - character style
        auto strong =
            add_builtin_style(StyleType::Character, "Strong", "Strong", StyleIdentifier::Strong);
        strong->get_font().bold = true;
        styles_->add(strong);

        // Emphasis - character style
        auto emphasis = add_builtin_style(
            StyleType::Character, "Emphasis", "Emphasis", StyleIdentifier::Emphasis);
        emphasis->get_font().italic = true;
        styles_->add(emphasis);

        // Hyperlink - character style
        auto hyperlink = add_builtin_style(
            StyleType::Character, "Hyperlink", "Hyperlink", StyleIdentifier::Hyperlink);
        hyperlink->get_font().color = Color::from_rgb(0x00, 0x00, 0xFF);
        hyperlink->get_font().underline = UnderlineType::Single;
        styles_->add(hyperlink);
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
    init_numbering_manager();
    auto *doc = get_numbering_xml();
    if (doc) {
        auto root = doc->child("w:numbering");
        if (root) {
            numbering_manager_->load_from_xml(root);
        }
    }
}

void Document::save_numbering() {
    if (!numbering_manager_) {
        return;
    }

    // If the manager has no definitions, do not overwrite an existing
    // numbering.xml that may contain data loaded from the original document.
    if (!numbering_manager_->has_definitions()) {
        return;
    }

    // If definitions were loaded from XML but never modified, preserve the
    // original XML to avoid losing rich formatting not tracked by the manager.
    if (!numbering_manager_->is_modified()) {
        return;
    }

    pugi::xml_document* doc = nullptr;
    if (has_xml_part("word/numbering.xml")) {
        doc = get_numbering_xml();
        if (doc) {
            doc->reset();
        }
    } else {
        doc = &create_xml_part("word/numbering.xml");
        add_content_type_override(
            "/word/numbering.xml",
            "application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml");
    }

    if (!doc) {
        return;
    }

    // Ensure document.xml.rels has a relationship to numbering.xml
    const std::string rels_path = "word/_rels/document.xml.rels";
    const std::string numbering_target = "numbering.xml";
    if (find_relationship_id(rels_path, numbering_target).empty()) {
        add_relationship(
            rels_path,
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/numbering",
            numbering_target);
    }

    auto root = doc->append_child("w:numbering");
    numbering_manager_->save_to_xml(root);
}

// ============================================================================
// Progress Reporting
// ============================================================================

void Document::report_progress(int percent, const std::string& current_file) const {
    if (load_config_.progress_callback) {
        load_config_.progress_callback(percent, current_file);
    }
}

}  // namespace cdocx
