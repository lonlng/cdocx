/**
 * @file sync_common.h
 * @brief Internal shared declarations for DOM-Physical sync modules
 * @internal Not part of the public API.
 */

#pragma once

#include <cdocx/base.h>
#include <cdocx/format.h>
#include <cdocx/paragraph.h>
#include <cdocx/style.h>

#include <string>

namespace cdocx {

// Forward declarations (defined in document_builder.h)
struct ImageSize;
enum class ImageAlignment : std::uint8_t;

// Forward declarations
class Document;
class FormField;

// ---------------------------------------------------------------------------
// General helpers
// ---------------------------------------------------------------------------
void remove_managed_children(pugi::xml_node parent, std::initializer_list<const char*> names);

const char* header_footer_type_to_string(HeaderFooterType type);
HeaderFooterType string_to_header_footer_type(const char* val);

std::string trim_whitespace(const std::string& str);
bool iequals(const std::string& a, const std::string& b);
std::string to_lower(std::string s);
std::string collect_text_from_runs(pugi::xml_node para);

pugi::xml_node walk_field_sequence(pugi::xml_node start_run,
                                 std::string* out_instr_text,
                                 std::string* out_resulttext);
void parse_field_code_and_switches(const std::string& code, Field* field);

void strip_whitespace_text_nodes(pugi::xml_node node);

// ---------------------------------------------------------------------------
// Node name helpers (shared between serialize and deserialize)
// ---------------------------------------------------------------------------
bool is_para_node(const char* name);
bool is_table_node(const char* name);
bool is_sectpr_node(const char* name);
bool is_content_node(const char* name);

// ---------------------------------------------------------------------------
// Section range helpers (shared between serialize and deserialize)
// ---------------------------------------------------------------------------
struct SectionRange {
    pugi::xml_node begin;
    pugi::xml_node end;  // points to w:sectPr, or empty for trailing section
};
std::vector<SectionRange> collect_section_ranges(pugi::xml_node body);

// ---------------------------------------------------------------------------
// Time / property helpers
// ---------------------------------------------------------------------------
std::string time_to_w3cdtf(std::time_t t);
std::time_t timegm_wrapper(std::tm* tm);
std::time_t w3cdtf_to_time(const std::string& s);

pugi::xml_node get_or_create_child(pugi::xml_node parent, const char* name);
pugi::xml_node ensure_child(pugi::xml_node parent, const char* name);
void set_text_child(pugi::xml_node parent, const char* name, const std::string& value);

// ---------------------------------------------------------------------------
// Lookup table accessors
// ---------------------------------------------------------------------------
const char* border_type_to_string(BorderType type);
BorderType string_to_border_type(const char* str);

const char* underline_type_to_string(UnderlineType type);
UnderlineType string_to_underline_type(const char* str);

const char* paragraph_alignment_to_string(ParagraphAlignment alignment);
ParagraphAlignment string_to_paragraph_alignment(const char* str);

const char* pp_alignment_to_string(ParagraphProperties::Alignment alignment);
ParagraphProperties::Alignment string_to_pp_alignment(const char* str);

const char* cell_vertical_alignment_to_string(CellVerticalAlignment alignment);
CellVerticalAlignment string_to_cell_vertical_alignment(const char* str);

const char* table_alignment_to_string(TableAlignment alignment);
TableAlignment string_to_table_alignment(const char* str);

const char* drop_cap_position_to_string(DropCapPosition position);
DropCapPosition string_to_drop_cap_position(const char* str);

const char* script_type_to_string(ScriptType type);
ScriptType string_to_script_type(const char* str);

const char* line_spacing_rule_to_string(LineSpacingRule rule);
LineSpacingRule string_to_line_spacing_rule(const char* str);

const char* highlight_to_string(TextProperties::Highlight highlight);
TextProperties::Highlight string_to_highlight(const char* str);

const char* text_form_field_type_to_string(TextFormFieldType type);
TextFormFieldType string_to_text_form_field_type(const char* str);

// ---------------------------------------------------------------------------
// Shading
// ---------------------------------------------------------------------------
void serialize_shading_to_xml(pugi::xml_node parent, const Shading& shading);
void parse_shading_from_xml(pugi::xml_node shd, Shading& shading);

// ---------------------------------------------------------------------------
// Border
// ---------------------------------------------------------------------------
void parse_border_from_xml(pugi::xml_node border_node, Border& border);
void parse_borders_from_xml(pugi::xml_node borders_node, Borders& borders);
void serialize_border_to_xml(pugi::xml_node parent, const char* name, const Border& border);
void serialize_borders_to_xml(pugi::xml_node parent, const char* container_name, const Borders& borders);

// ---------------------------------------------------------------------------
// Font / Run format (shared between serialize, deserialize, and style)
// ---------------------------------------------------------------------------
void serialize_font_to_r_pr(pugi::xml_node r_pr, const Font& font, bool add_sz_cs);
void serialize_run_formatting_to_xml(pugi::xml_node run_xml, const Font& font, const Shading& shading);
void parse_font_from_xml(pugi::xml_node r_pr, Font& font);
void parse_run_format_from_xml(Inline* run, pugi::xml_node run_node);
void parse_paragraph_format_children_from_xml(pugi::xml_node p_pr, ParagraphFormat& format);
void serialize_paragraph_to_xml(pugi::xml_node parent, const Paragraph* para);
void serialize_paragraph_format_children_to_xml(pugi::xml_node p_pr, const ParagraphFormat& format);

// ---------------------------------------------------------------------------
// Image Drawing
// ---------------------------------------------------------------------------
pugi::xml_node append_image_drawing(pugi::xml_node parent,
                                    const std::string& rel_id,
                                    const ImageSize& size,
                                    ImageAlignment align,
                                    int image_id,
                                    const std::string& image_name);

// ---------------------------------------------------------------------------
// Form Field
// ---------------------------------------------------------------------------
void serialize_ffdata_to_fld_char(pugi::xml_node fld_char, const FormField* field);
void append_form_field_sequence(pugi::xml_node parent, const FormField* field, Document* doc);

}  // namespace cdocx
