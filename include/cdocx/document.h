/**
 * @file document.h
 * @brief Document class for working with DOCX files - DOM Style
 * @details Provides the main Document class for opening, creating, modifying,
 *          and saving Word documents (.docx). Now uses pure DOM architecture
 *          with Document inheriting from CompositeNode.
 *
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0 - DOM Architecture
 *
 * @par Usage Example:
 * @code
 * #include <cdocx/document.h>
 *
 * // Open existing document
 * cdocx::Document doc("input.docx");
 * doc.open();
 *
 * // Access sections
 * for (auto& section : doc.get_sections()) {
 *     auto body = section->get_body();
 *
 *     // Iterate paragraphs using DOM
 *     for (auto& para : body->get_child_nodes(cdocx::NodeType::Paragraph)) {
 *         std::cout << para->get_text() << std::endl;
 *     }
 * }
 *
 * // Create content using DOM API
 * auto section = doc.append_section();
 * auto body = section->get_body();
 * auto para = body->append_paragraph("Hello, World!");
 * para->append_run(" Bold text")->set_bold(true);
 *
 * doc.save("output.docx");
 * @endcode
 */

#pragma once

#include <cdocx/enums.h>
#include <cdocx/format.h>
#include <cdocx/node.h>
#include <cdocx/numbering.h>
#include <cdocx/properties.h>
#include <zip.h>

#include <pugixml.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <shared_mutex>
#include <string>
#include <vector>

namespace cdocx {

// Forward declarations
class Body;
class Paragraph;
class Table;
class Bookmark;
class BookmarkCollection;
class Comment;
class CommentCollection;
class Footnote;
class FootnoteCollection;
class EndnoteCollection;
class Range;
class DocumentBuilder;
class DocumentProperties;
class SectionCollection;
class ParagraphCollection;
class TableCollection;
class StyleCollection;
class Watermark;

// ============================================================================
// Document Package Tree Types (Physical structure)
// ============================================================================

enum class DocxNodeType : std::uint8_t {
    Root,       ///< Root node representing the package
    Directory,  ///< Directory/folder node
    XmlFile,    ///< XML file with parsed content
    MediaFile,  ///< Media file (image, etc.)
    BinaryFile  ///< Other binary file
};

struct DocxTreeNode : public std::enable_shared_from_this<DocxTreeNode> {
    std::string name;       ///< File/directory name
    std::string full_path;  ///< Full path in ZIP
    DocxNodeType type;      ///< Node type

    DocxTreeNode* parent;                          ///< Parent node
    std::vector<std::shared_ptr<DocxTreeNode>> children;  ///< Child nodes

    std::shared_ptr<pugi::xml_document> xml_doc;   ///< For XmlFile type
    std::vector<uint8_t> binary_data;              ///< Binary data storage
    std::string content_type;                      ///< MIME type

    bool is_modified = false;  ///< Modified since load
    bool is_new = false;       ///< Newly created
    bool is_deleted = false;   ///< Marked for deletion
    bool is_critical = false;  ///< Critical document part

    DocxTreeNode(std::string n, DocxNodeType t, DocxTreeNode* p = nullptr)
        : name(std::move(n)), type(t), parent(p) {}

    bool is_directory() const {
        return type == DocxNodeType::Directory || type == DocxNodeType::Root;
    }
    bool is_file() const { return !is_directory(); }

    std::shared_ptr<DocxTreeNode> find_child(const std::string& child_name) const;
    std::shared_ptr<DocxTreeNode> add_directory(const std::string& dir_name);
    std::shared_ptr<DocxTreeNode> add_file(const std::string& file_name, DocxNodeType file_type);
    std::shared_ptr<DocxTreeNode> find_or_create_directory(const std::string& dir_name);
    std::vector<uint8_t> serialize_xml_to_binary() const;
    void set_binary_data(std::vector<uint8_t>&& data);
};

class DocxTree {
  public:
    DocxTree();
    ~DocxTree();

    // Move constructor and move assignment (shared_mutex is not copyable)
    DocxTree(DocxTree&& other) noexcept;
    DocxTree& operator=(DocxTree&& other) noexcept;

    // Delete copy constructor and copy assignment
    DocxTree(const DocxTree&) = delete;
    DocxTree& operator=(const DocxTree&) = delete;

    std::shared_ptr<DocxTreeNode> get_root() const { return root_; }
    std::shared_ptr<DocxTreeNode> find_node(const std::string& path) const;
    std::shared_ptr<DocxTreeNode> find_or_create_node(const std::string& path, DocxNodeType type);
    std::shared_ptr<DocxTreeNode> add_zip_entry(const std::string& entry_path,
                                                const std::vector<uint8_t>& data);
    bool remove_node(const std::string& path);
    void iterate_files(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const;
    void iterate_all(std::function<void(std::shared_ptr<DocxTreeNode>)> callback) const;
    std::vector<std::shared_ptr<DocxTreeNode>> get_all_xml_files() const;
    std::vector<std::shared_ptr<DocxTreeNode>> get_all_media_files() const;
    void rebuild_path_map();
    void clear();

  private:
    std::shared_ptr<DocxTreeNode> root_;
    std::map<std::string, std::weak_ptr<DocxTreeNode>> path_map_;
    mutable std::shared_mutex path_map_mutex_;

    bool is_critical_part(const std::string& path) const;
};

// ============================================================================
// Relationship and Content Type
// ============================================================================

struct Relationship {
    std::string id;
    std::string type;
    std::string target;
    std::string target_mode;

    Relationship() = default;
    Relationship(std::string i,
                 std::string t,
                 std::string tgt,
                 std::string tm = "")
        : id(std::move(i)), type(std::move(t)), target(std::move(tgt)),
          target_mode(std::move(tm)) {}
    // Pass-by-value + std::move is the canonical modern C++ idiom for
    // constructors that unconditionally capture their arguments.
};

struct ContentType {
    std::string extension;
    std::string part_name;
    std::string content_type;
    bool is_default = false;
};

// ============================================================================
// Load Configuration and Results
// ============================================================================

struct LoadConfig {
    bool enable_parallel_loading = true;
    size_t parallel_threshold = 50;
    size_t max_threads = 0;
    bool allow_partial_load = true;
    bool skip_corrupted_files = true;
    size_t max_errors = 100;
    std::function<void(int percent, const std::string& current_file)> progress_callback;

    static LoadConfig optimized_for_speed() {
        LoadConfig cfg;
        cfg.enable_parallel_loading = true;
        cfg.max_threads = 0;
        return cfg;
    }
};

enum class LoadErrorType : std::uint8_t {
    None,
    ZipOpenFailed,
    ZipEntryReadFailed,
    XmlParseFailed,
    InvalidStructure,
    CorruptedFile,
    MemoryAllocation,
    IoError,
    Timeout,
    Unknown
};

enum class DocumentIntegrity : std::uint8_t {
    Complete,
    Partial,
    Critical,
    Corrupted
};

enum class ProtectionType : std::uint8_t {
    NoProtection = 0,
    AllowOnlyRevisions,
    AllowOnlyComments,
    AllowOnlyFormFields,
    ReadOnly
};

struct LoadError {
    LoadErrorType type = LoadErrorType::None;
    std::string file_path;
    std::string message;
    size_t line = 0;

    LoadError() = default;
    LoadError(LoadErrorType t, std::string path, std::string msg)
        : type(t), file_path(std::move(path)), message(std::move(msg)) {}
};

struct LoadResult {
    bool success = false;
    DocumentIntegrity integrity = DocumentIntegrity::Corrupted;
    std::vector<LoadError> errors;
    std::vector<std::string> skipped_files;
    size_t total_files = 0;
    size_t loaded_files = 0;
    double load_time_ms = 0.0;

    bool is_usable() const {
        return success && (integrity == DocumentIntegrity::Complete ||
                           integrity == DocumentIntegrity::Partial);
    }
    bool is_complete() const { return success && integrity == DocumentIntegrity::Complete; }
};

struct LoadStatistics {
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    size_t total_entries = 0;
    size_t processed_entries = 0;
    size_t xml_files = 0;
    size_t media_files = 0;
    size_t binary_files = 0;

    double get_elapsed_ms() const {
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }
};

// ============================================================================
// Document Class - DOM Root Node
// ============================================================================

class Document : public CompositeNode {
  public:
    // Construction
    Document();
    explicit Document(std::string filepath);
    ~Document() override;

    // Disable copy, enable move
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;
    Document(Document&& other) noexcept;
    Document& operator=(Document&& other) noexcept;

    // Node overrides
    NodeType node_type() const override { return NodeType::Document; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;

    // File operations
    void open();
    void open(const std::string& filepath);
    void open(const std::string& filepath, std::function<void(int, const std::string&)> callback);
    LoadResult open_with_config(const std::string& filepath, const LoadConfig& config);
    void close();
    void save();
    void save(const std::string& filepath);
    bool is_open() const { return is_open_; }

    // Document creation
    bool create_empty(const std::string& filepath = "");
    std::string get_filepath() const { return filepath_; }
    void clear();

    // Section access (Document contains Sections)
    SectionCollection get_sections() const;
    std::shared_ptr<Section> get_first_section() const;
    std::shared_ptr<Section> get_last_section() const;
    std::shared_ptr<Section> append_section();
    std::shared_ptr<Section> add_section() { return append_section(); }
    std::shared_ptr<Section> insert_section(int index);
    void remove_section(const std::shared_ptr<Section>& section);
    size_t get_section_count() const;
    std::shared_ptr<Section> get_section(size_t index) const;

    // Get the section immediately before the given section
    std::shared_ptr<Section> get_previous_section(const Section* section) const;

    // Convenience: Get all paragraphs across all sections
    ParagraphCollection get_paragraphs() const;

    // Legacy API: Get paragraph iterator (backward compatibility)
    Paragraph paragraphs();

    // Convenience: Get all tables across all sections
    TableCollection get_tables() const;

    // Ensure document has at least one section with one paragraph
    void ensure_minimum();

    /**
     * @brief Get a Range representing the entire document
     * @return Range covering all content
     */
    Range get_range();

    // Section properties
    void set_default_section_properties(const SectionProperties& props);
    SectionProperties get_default_section_properties() const;

    // Numbering (List) support
    NumberingId add_bulleted_list_definition();
    NumberingId add_numbered_list_definition(NumberStyle style = NumberStyle::Decimal);
    NumberingId add_chinese_numbered_list_definition();
    NumberingId add_outline_list_definition();
    NumberingManager* get_numbering_manager() { return numbering_manager_.get(); }
    const NumberingDefinition* get_numbering_definition(NumberingId id) const;

    // Styles
    StyleCollection& styles();
    const StyleCollection& styles() const;

    // XML Parts API (physical structure access)
    pugi::xml_document* get_xml_part(const std::string& part_path);
    const pugi::xml_document* get_xml_part(const std::string& part_path) const;
    bool has_xml_part(const std::string& part_path) const;
    std::vector<std::string> get_all_part_names() const;
    size_t get_part_count() const;
    pugi::xml_document& create_xml_part(const std::string& part_path);
    void remove_xml_part(const std::string& part_path);
    void mark_modified(const std::string& part_path);
    void mark_xml_paragraph_dirty(pugi::xml_node para) { dirty_xml_paragraphs_.insert(para); }

    // Convenience XML accessors
    pugi::xml_document* get_document_xml();
    pugi::xml_document* get_core_properties();
    pugi::xml_document* get_app_properties();
    pugi::xml_document* get_content_types();
    pugi::xml_document* get_styles();
    pugi::xml_document* get_settings();
    const pugi::xml_document* get_settings() const;
    pugi::xml_document* get_font_table();
    pugi::xml_document* get_numbering_xml();
    pugi::xml_document* get_footnotes();
    pugi::xml_document* get_endnotes();
    pugi::xml_document* get_document_rels();
    pugi::xml_document* get_package_rels();
    pugi::xml_document* get_header(int index);
    pugi::xml_document* get_footer(int index);
    std::vector<std::string> get_header_names() const;
    std::vector<std::string> get_footer_names() const;

    // Media management
    bool add_media(const std::string& image_path, const std::string* image_name = nullptr);
    bool add_media_from_memory(const std::string& name,
                               const std::vector<uint8_t>& data,
                               const std::string& content_type = "");
    std::string add_media_from_memory_with_rel(const std::string& name,
                                               const std::vector<uint8_t>& data,
                                               const std::string& content_type = "");
    bool delete_media(const std::string& image_name);
    bool replace_media(const std::string& image_name, const std::string& new_image_path);
    bool has_media(const std::string& image_name) const;
    std::vector<std::string> list_media() const;
    bool export_media(const std::string& image_name, const std::string& output_path) const;
    std::vector<uint8_t> get_media_data(const std::string& image_name) const;
    std::string add_media_with_rel(const std::string& image_path,
                                   const std::string* image_name = nullptr);

    // Thumbnail management (opt-in, for file preview in Windows Explorer)
    bool add_thumbnail(const std::string& image_path);
    bool add_thumbnail_from_memory(const std::vector<uint8_t>& data,
                                   const std::string& content_type = "image/jpeg");
    bool remove_thumbnail();
    bool has_thumbnail() const;

    // Bookmark management
    BookmarkCollection get_bookmarks();
    int generate_unique_bookmark_id();

    // Comment management
    std::shared_ptr<Comment> add_comment(const std::string& author, const std::string& text);
    std::shared_ptr<Comment> get_comment(int id) const;
    CommentCollection get_comments() const;
    bool remove_comment(int id);
    void clear_comments();
    int get_next_comment_id();

    // Footnote/Endnote management
    FootnoteCollection footnotes() const;
    EndnoteCollection endnotes() const;
    std::shared_ptr<Footnote> add_footnote(const std::string& text,
                                           const std::string& reference_mark = "");
    std::shared_ptr<Footnote> add_endnote(const std::string& text,
                                          const std::string& reference_mark = "");
    bool remove_footnote(int id);
    bool remove_endnote(int id);
    void clear_footnotes();
    void clear_endnotes();
    int get_next_footnote_id();
    int get_next_endnote_id();

    // Header/Footer management (used by Section)
    int get_next_header_number();
    int get_next_footer_number();

    // Document properties
    DocumentProperties& get_builtin_document_properties() { return builtin_properties_; }
    DocumentProperties& get_custom_document_properties() { return custom_properties_; }

    // Default tab stop (in points)
    double get_default_tab_stop() const;
    void set_default_tab_stop(double points);

    // Watermark
    Watermark watermark();

    // Document protection
    void protect(ProtectionType type, const std::string& password = "");
    void unprotect();
    bool is_protected() const;

    // Statistics
    LoadResult get_last_load_result() const { return last_load_result_; }

    // Internal: Get physical tree (for advanced users)
    DocxTree& get_physical_tree() { return tree_; }
    const DocxTree& get_physical_tree() const { return tree_; }

    // Sync DOM to physical tree (called before save)
    void sync_to_physical_tree();

    // Sync physical tree to DOM (called after load)
    void sync_from_physical_tree();

    // Merge physical tree into existing DOM sections (preserves DOM-only content)
    void merge_sections_from_physical();

    /**
     * @brief Synchronize between DOM and XML representations
     * @param dom_to_xml true = DOM→XML, false = XML→DOM
     */
    void sync_dom_and_xml(bool dom_to_xml = true);

  protected:
    // Physical document state
    std::string filepath_;
    bool is_open_ = false;
    LoadConfig load_config_;
    DocxTree tree_;

    // Caches
    std::map<std::string, std::shared_ptr<DocxTreeNode>> xml_parts_cache_;
    std::map<std::string, std::shared_ptr<DocxTreeNode>> media_files_cache_;
    std::map<std::string, std::vector<Relationship>> relationships_;
    std::set<std::string> modified_parts_;
    std::vector<ContentType> content_types_;

    // ZIP handling
    zip_t* zip_handle_ = nullptr;
    bool zip_dirty_ = false;

    // Statistics
    LoadStatistics last_load_stats_;
    LoadResult last_load_result_;

    // DOM state (Document contains Sections as children)
    mutable std::vector<std::shared_ptr<Section>> sections_cache_;
    mutable bool sections_dirty_ = true;

    // XML paragraphs modified by DocumentBuilder or legacy API
    std::set<pugi::xml_node> dirty_xml_paragraphs_;

    // Tracks the paragraph/table child count in physical XML at the time of the
    // last successful sync_to_physical_tree(). Used to detect whether physical
    // XML was modified directly (count increased) vs. DOM deleted content.
    int last_synced_xml_child_count_ = 0;

    // Numbering
    std::unique_ptr<NumberingManager> numbering_manager_;

    // Styles
    mutable std::unique_ptr<StyleCollection> styles_;

    // Properties
    DocumentProperties builtin_properties_;
    DocumentProperties custom_properties_;

    // Header/Footer counters
    int next_header_number_ = 1;
    int next_footer_number_ = 1;
    int next_bookmark_id_ = 1;
    int next_comment_id_ = 0;

    friend class CommentCollection;
    friend class FootnoteCollection;
    friend class EndnoteCollection;

    // Comments cache
    mutable std::vector<std::shared_ptr<Comment>> comments_cache_;
    mutable bool comments_dirty_ = true;

    // Footnotes/Endnotes cache
    mutable std::vector<std::shared_ptr<Footnote>> footnotes_cache_;
    mutable std::vector<std::shared_ptr<Footnote>> endnotes_cache_;
    mutable bool footnotes_dirty_ = true;
    mutable bool endnotes_dirty_ = true;
    int next_footnote_id_ = 1;
    int next_endnote_id_ = 1;

    // Section properties
    SectionProperties default_section_properties_;


    // Internal methods
    bool open_zip(const std::string& path);
    void close_zip();
    bool ensure_zip_handle();
    std::vector<uint8_t> read_zip_entry(const std::string& entry_name);
    bool load_tree_from_zip();
    LoadResult load_tree_with_result();
    bool load_tree_parallel(LoadStatistics& stats);
    void build_caches_from_tree();
    void report_progress(int percent, const std::string& current_file) const;

    // Content types and relationships
    bool load_content_types();
    void parse_relationships(const std::string& rels_path);
    void load_all_relationships();
    void remove_relationship(const std::string& rels_path, const std::string& rel_id);
    void update_relationships_xml(const std::string& rels_path);
    void update_content_types_xml();

  public:
    // Relationship management (public for Section and other internal classes)
    std::string find_relationship_id(const std::string& rels_path, const std::string& target) const;
    std::string add_relationship(const std::string& rels_path,
                                 const std::string& type,
                                 const std::string& target,
                                 const std::string& target_mode = "");
    std::string get_relationship_target(const std::string& rels_path,
                                        const std::string& rel_id) const;
    void add_content_type_override(const std::string& part_name, const std::string& content_type);
    void add_content_type_default(const std::string& extension, const std::string& content_type);

    // Save operations
    bool save_to_zip(const std::string& output_path);
    bool save_tree_to_zip(::zip_t* zip);
    bool write_tree_node(::zip_t* zip, const std::shared_ptr<DocxTreeNode>& node);

    // Media helpers
    std::string get_mime_type(const std::string& filename) const;
    std::string get_extension_from_mime(const std::string& mime_type) const;
    std::string generate_unique_image_name(const std::string& base_name) const;

    // Create empty document
    bool create_empty_document();

    // Numbering
    void init_numbering_manager();
    void load_numbering();
    void save_numbering();

    // Sync helpers
    void sync_sections_to_physical();
    void sync_sections_from_physical();
    void sync_styles_to_physical();
    void sync_styles_from_physical();
    void sync_comments_to_physical();
    void sync_comments_from_physical();
    void sync_footnotes_to_physical();
    void sync_footnotes_from_physical();
    void sync_endnotes_to_physical();
    void sync_endnotes_from_physical();
    void sync_builtin_properties_to_physical();
    void sync_builtin_properties_from_physical();
    void sync_custom_properties_to_physical();
    void sync_custom_properties_from_physical();
    std::shared_ptr<Body> parse_body_from_xml(pugi::xml_node body_node);
    std::shared_ptr<Paragraph> parse_paragraph_from_xml(pugi::xml_node para_node);
    std::shared_ptr<Table> parse_table_from_xml(pugi::xml_node table_node);
    std::shared_ptr<Run> parse_run_from_xml(pugi::xml_node run_node);
};

// SectionCollection, ParagraphCollection, TableCollection are defined in their respective headers

}  // namespace cdocx
