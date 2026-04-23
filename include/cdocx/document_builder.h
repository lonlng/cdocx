/**
 * @file document_builder.h
 * @brief Fluent document construction API for CDocx
 * @details Provides the DocumentBuilder class for programmatically building
 *          documents without manually managing XML nodes.
 *
 * @since 0.3.0
 */

#pragma once

#include <cdocx/base.h>
#include <cdocx/constants.h>
#include <cdocx/formfield.h>
#include <cdocx/fwd.h>

#include <map>
#include <memory>
#include <string>

namespace cdocx {

// ============================================================================
// Image Support
// ============================================================================

enum class ImageAlignment : std::uint8_t {
    Left,
    Center,
    Right
};

struct ImageSize {
    double width_pt = 0;
    double height_pt = 0;

    ImageSize() = default;
    ImageSize(double w, double h) : width_pt(w), height_pt(h) {}

    int64_t width_emu() const { return static_cast<int64_t>(width_pt * 12700); }
    int64_t height_emu() const { return static_cast<int64_t>(height_pt * 12700); }
    bool is_valid() const { return width_pt > 0 && height_pt > 0; }
};

struct ImageFormatInfo {
    std::string format;
    std::string mime_type;
    int width = 0;
    int height = 0;
    int dpi_x = 96;
    int dpi_y = 96;
    bool is_valid = false;
    std::string error_message;
};

bool detect_image_size(const std::string& image_path, ImageSize& size);
bool detect_image_size_from_memory(const std::vector<uint8_t>& data, ImageSize& size);
ImageFormatInfo validate_image_format_detailed(const std::string& image_path);
ImageFormatInfo validate_image_format_from_memory(const std::vector<uint8_t>& data);

// ============================================================================
// DocumentBuilder
// ============================================================================

/**
 * @class DocumentBuilder
 * @brief Fluent API for building documents programmatically
 * @since 0.2.0
 */
class DocumentBuilder {
  public:
    DocumentBuilder();
    ~DocumentBuilder();

    DocumentBuilder& with_title(const std::string& title);
    DocumentBuilder& with_author(const std::string& author);
    DocumentBuilder& with_subject(const std::string& subject);
    DocumentBuilder& with_keywords(const std::string& keywords);

    DocumentBuilder& with_page_size(double width, double height);
    DocumentBuilder& with_margins(double top, double bottom, double left, double right);
    DocumentBuilder& with_orientation(PageOrientation orientation);

    DocumentBuilder& add_paragraph(std::shared_ptr<Paragraph> paragraph);
    DocumentBuilder& add_paragraph(const std::string& text);
    DocumentBuilder& add_table(std::shared_ptr<Table> table);
    DocumentBuilder& add_table(size_t rows, size_t columns);

    std::shared_ptr<Document> build();

  private:
    std::shared_ptr<Document> doc_sptr_;

  private:
    Document* doc_ = nullptr;
    pugi::xml_document* target_xml_doc_ = nullptr;
    pugi::xml_node current_node_;
    pugi::xml_node current_paragraph_;

    struct FormattingState {
        bool bold = false;
        bool italic = false;
        bool underline = false;
        bool strikethrough = false;
        std::string font_name;
        int font_size = 0;
        std::string color;
        std::string alignment;
    };
    FormattingState format_;

    bool in_table_ = false;
    pugi::xml_node current_table_;
    pugi::xml_node current_row_;
    pugi::xml_node current_cell_;

    std::map<std::string, int> bookmark_stack_;

    std::shared_ptr<FormField> insert_form_field_impl(const std::shared_ptr<FormField>& field);
    void ensure_paragraph();
    void apply_formatting(pugi::xml_node run) const;
    pugi::xml_node get_body();

  public:
    explicit DocumentBuilder(Document* doc);
    explicit DocumentBuilder(const std::shared_ptr<Document>& doc);

    // Navigation
    DocumentBuilder& move_to_document_start();
    DocumentBuilder& move_to_document_end();
    DocumentBuilder& move_to_section(size_t index);
    DocumentBuilder& move_to_paragraph(size_t index);
    DocumentBuilder& move_to_paragraph(size_t paragraph_index, size_t character_index);
    DocumentBuilder& move_to_bookmark(const std::string& name);
    bool move_to_merge_field(const std::string& field_name);
    DocumentBuilder& move_to_cell(size_t table_index, size_t row_index, size_t cell_index);

    // Text Insertion
    DocumentBuilder& write(const std::string& text);
    DocumentBuilder& writeln(const std::string& text);
    DocumentBuilder& writeln();

    // Paragraph Operations
    Paragraph* insert_paragraph();
    DocumentBuilder& insert_break();
    DocumentBuilder& insert_break(BreakType break_type);
    DocumentBuilder& move_to_header_footer(HeaderFooterType type);
    std::shared_ptr<Footnote> insert_footnote(FootnoteType type, const std::string& text);
    std::shared_ptr<Footnote> insert_footnote(FootnoteType type,
                                              const std::string& text,
                                              const std::string& reference_mark);
    std::shared_ptr<Field> insert_field(FieldType field_type, bool update_field = false);
    std::shared_ptr<Field> insert_field(const std::string& field_code);
    std::shared_ptr<Field> insert_field(const std::string& field_code,
                                        const std::string& field_value);

  private:
    std::shared_ptr<Field> insert_field_node(const std::shared_ptr<Field>& field);

  public:
    std::shared_ptr<Field> insert_page_number(const std::string& switches = "");
    std::shared_ptr<Field> insert_num_pages();
    std::shared_ptr<Field> insert_date(const std::string& switches = "");
    std::shared_ptr<Field> insert_time(const std::string& switches = "");
    std::shared_ptr<Field> insert_merge_field(const std::string& field_name,
                                              const std::string& switches = "");
    std::shared_ptr<Field> insert_table_of_contents(const std::string& switches);

    // Formatting
    DocumentBuilder& set_bold(bool value);
    DocumentBuilder& set_italic(bool value);
    DocumentBuilder& set_underline(bool value);
    DocumentBuilder& set_strikethrough(bool value);
    DocumentBuilder& set_font_name(const std::string& name);
    DocumentBuilder& set_font_size(int size);
    DocumentBuilder& set_color(const std::string& color_hex);
    DocumentBuilder& set_alignment(const std::string& alignment);
    DocumentBuilder& clear_formatting();

    // Table Building
    DocumentBuilder& start_table();
    DocumentBuilder& end_table();
    DocumentBuilder& insert_row();
    DocumentBuilder& insert_cell();
    DocumentBuilder& end_row();

    // Hyperlink
    DocumentBuilder& insert_hyperlink(const std::string& text, const std::string& url);

    // Bookmark
    DocumentBuilder& start_bookmark(const std::string& name);
    DocumentBuilder& end_bookmark(const std::string& name);

    // Form Fields
    std::shared_ptr<FormField> insert_text_input(const std::string& name,
                                                  TextFormFieldType type = TextFormFieldType::Regular,
                                                  const std::string& format = "",
                                                  const std::string& field_value = "",
                                                  int max_length = 0);
    std::shared_ptr<FormField> insert_check_box(const std::string& name,
                                                bool checked_value,
                                                int size = 0);
    std::shared_ptr<FormField> insert_check_box(const std::string& name,
                                                bool default_value,
                                                bool checked_value,
                                                int size);
    std::shared_ptr<FormField> insert_combo_box(const std::string& name,
                                                const std::vector<std::string>& items,
                                                int selected_index = 0);

    // Image
    bool insert_image(const std::string& image_path, double width = 0, double height = 0);
};

}  // namespace cdocx
