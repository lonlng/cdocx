/**
 * @file sync_common.cpp
 * @brief Shared helpers and lookup tables for DOM-Physical sync
 * @internal Not part of the public API.
 */

#include "sync_common.h"

#include <cdocx/document.h>
#include <cdocx/document_builder.h>
#include <cdocx/formfield.h>

#include <charconv>
#include <cstring>
#include <ctime>

namespace cdocx {

// ============================================================================
// General helpers
// ============================================================================

void remove_managed_children(pugi::xml_node parent, std::initializer_list<const char*> names) {
    for (const char* name : names) {
        for (pugi::xml_node child = parent.child(name); child;
             child = parent.child(name)) {
            parent.remove_child(child);
        }
    }
}

std::string trim_whitespace(const std::string& str) {
    size_t start = 0;
    while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start]))) {
        ++start;
    }
    size_t end = str.size();
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
        --end;
    }
    return str.substr(start, end - start);
}

bool iequals(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(a[i])) !=
            std::tolower(static_cast<unsigned char>(b[i]))) {
            return false;
        }
    }
    return true;
}

std::string to_lower(std::string s) {
    for (auto& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

std::string collect_text_from_runs(pugi::xml_node para) {
    std::string result;
    for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
        const pugi::xml_node t = run.child("w:t");
        if (t) {
            result += t.text().get();
        }
    }
    return result;
}

bool is_para_node(const char* name) {
    return std::strcmp(name, "w:p") == 0;
}

bool is_table_node(const char* name) {
    return std::strcmp(name, "w:tbl") == 0;
}

bool is_sectpr_node(const char* name) {
    return std::strcmp(name, "w:sectPr") == 0;
}

bool is_content_node(const char* name) {
    return is_para_node(name) || is_table_node(name);
}

bool is_bookmark_start_node(const char* name) {
    return std::strcmp(name, "w:bookmarkStart") == 0;
}

bool is_bookmark_end_node(const char* name) {
    return std::strcmp(name, "w:bookmarkEnd") == 0;
}

bool is_run_node(const char* name) {
    return std::strcmp(name, "w:r") == 0;
}

std::vector<SectionRange> collect_section_ranges(pugi::xml_node body) {
    std::vector<SectionRange> ranges;
    pugi::xml_node current_begin = body.first_child();
    for (auto node = body.first_child(); node; node = node.next_sibling()) {
        if (is_sectpr_node(node.name())) {
            ranges.push_back({current_begin, node});
            current_begin = node.next_sibling();
        }
    }
    if (ranges.empty() && body.first_child()) {
        ranges.push_back({body.first_child(), pugi::xml_node()});
    }
    return ranges;
}

struct HeaderFooterTypeMapping {
    HeaderFooterType type;
    const char* xml_value;
};

static const HeaderFooterTypeMapping kHeaderFooterTypeMappings[] = {
    {HeaderFooterType::Default, "default"},
    {HeaderFooterType::Primary, "default"},
    {HeaderFooterType::FirstPage, "first"},
    {HeaderFooterType::First, "first"},
    {HeaderFooterType::EvenPages, "even"},
    {HeaderFooterType::Even, "even"},
};

const char* header_footer_type_to_string(HeaderFooterType type) {
    for (const auto& mapping : kHeaderFooterTypeMappings) {
        if (mapping.type == type) {
            return mapping.xml_value;
        }
    }
    return "default";
}

HeaderFooterType string_to_header_footer_type(const char* val) {
    for (const auto& mapping : kHeaderFooterTypeMappings) {
        if (std::strcmp(mapping.xml_value, val) == 0) {
            return mapping.type;
        }
    }
    return HeaderFooterType::Default;
}

// ============================================================================
// Lookup Tables
// ============================================================================

struct BorderTypeMapping {
    BorderType type{};
    const char* xml_value{};
};

static const BorderTypeMapping kBorderTypeMappings[] = {
    {BorderType::Single, "single"},
    {BorderType::Thick, "thick"},
    {BorderType::Double, "double"},
    {BorderType::Dotted, "dotted"},
    {BorderType::Dashed, "dashed"},
    {BorderType::DotDash, "dotDash"},
    {BorderType::DotDotDash, "dotDotDash"},
    {BorderType::Triple, "triple"},
    {BorderType::ThinThickSmall, "thinThickSmallGap"},
    {BorderType::ThickThinSmall, "thickThinSmallGap"},
    {BorderType::ThinThickThinSmall, "thinThickThinSmallGap"},
    {BorderType::ThinThickMedium, "thinThickMediumGap"},
    {BorderType::ThickThinMedium, "thickThinMediumGap"},
    {BorderType::ThinThickThinMedium, "thinThickThinMediumGap"},
    {BorderType::ThinThickLarge, "thinThickLargeGap"},
    {BorderType::ThickThinLarge, "thickThinLargeGap"},
    {BorderType::ThinThickThinLarge, "thinThickThinLargeGap"},
    {BorderType::Wave, "wave"},
    {BorderType::DoubleWave, "doubleWave"},
    {BorderType::DashSmall, "dashSmallGap"},
    {BorderType::ThreeDEmboss, "threeDEmboss"},
    {BorderType::ThreeDEngrave, "threeDEngrave"},
    {BorderType::Outset, "outset"},
    {BorderType::Inset, "inset"},
    {BorderType::Clear, "clear"},
};

const char* border_type_to_string(BorderType type) {
    for (const auto& m : kBorderTypeMappings) {
        if (m.type == type) {
            return m.xml_value;
        }
    }
    return "single";
}

BorderType string_to_border_type(const char* str) {
    for (const auto& m : kBorderTypeMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.type;
        }
    }
    return BorderType::None;
}

struct UnderlineTypeMapping {
    UnderlineType type{};
    const char* xml_value{};
};

static const UnderlineTypeMapping kUnderlineTypeMappings[] = {
    {UnderlineType::Single, "single"},
    {UnderlineType::Words, "words"},
    {UnderlineType::Double, "double"},
    {UnderlineType::Dotted, "dotted"},
    {UnderlineType::Dash, "dash"},
    {UnderlineType::DashDot, "dashDot"},
    {UnderlineType::DashDotDot, "dashDotDot"},
    {UnderlineType::Wave, "wave"},
    {UnderlineType::Thick, "thick"},
    {UnderlineType::DottedHeavy, "dottedHeavy"},
    {UnderlineType::DashHeavy, "dashHeavy"},
    {UnderlineType::DashDotHeavy, "dashDotHeavy"},
    {UnderlineType::DashDotDotHeavy, "dashDotDotHeavy"},
    {UnderlineType::WaveHeavy, "waveHeavy"},
};

const char* underline_type_to_string(UnderlineType type) {
    for (const auto& m : kUnderlineTypeMappings) {
        if (m.type == type) {
            return m.xml_value;
        }
    }
    return nullptr;
}

UnderlineType string_to_underline_type(const char* str) {
    for (const auto& m : kUnderlineTypeMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.type;
        }
    }
    return UnderlineType::Single;
}

struct ParagraphAlignmentMapping {
    ParagraphAlignment alignment{};
    const char* xml_value{};
};

static const ParagraphAlignmentMapping kParagraphAlignmentMappings[] = {
    {ParagraphAlignment::Center, "center"},
    {ParagraphAlignment::Right, "right"},
    {ParagraphAlignment::Justify, "both"},
    {ParagraphAlignment::Distributed, "distribute"},
};

const char* paragraph_alignment_to_string(ParagraphAlignment alignment) {
    for (const auto& m : kParagraphAlignmentMappings) {
        if (m.alignment == alignment) {
            return m.xml_value;
        }
    }
    return "left";
}

ParagraphAlignment string_to_paragraph_alignment(const char* str) {
    for (const auto& m : kParagraphAlignmentMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.alignment;
        }
    }
    return ParagraphAlignment::Left;
}

// ParagraphProperties::Alignment lookup table
struct PpAlignmentMapping {
    ParagraphProperties::Alignment alignment{};
    const char* xml_value{};
};

static const PpAlignmentMapping kPpAlignmentMappings[] = {
    {ParagraphProperties::Alignment::Centered, "center"},
    {ParagraphProperties::Alignment::Right, "right"},
    {ParagraphProperties::Alignment::Justified, "both"},
    {ParagraphProperties::Alignment::Distributed, "distribute"},
};

const char* pp_alignment_to_string(ParagraphProperties::Alignment alignment) {
    for (const auto& m : kPpAlignmentMappings) {
        if (m.alignment == alignment) {
            return m.xml_value;
        }
    }
    return "left";
}

ParagraphProperties::Alignment string_to_pp_alignment(const char* str) {
    for (const auto& m : kPpAlignmentMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.alignment;
        }
    }
    return ParagraphProperties::Alignment::Left;
}

// CellVerticalAlignment lookup table
struct CellVerticalAlignmentMapping {
    CellVerticalAlignment alignment{};
    const char* xml_value{};
};

static const CellVerticalAlignmentMapping kCellVerticalAlignmentMappings[] = {
    {CellVerticalAlignment::Center, "center"},
    {CellVerticalAlignment::Bottom, "bottom"},
};

const char* cell_vertical_alignment_to_string(CellVerticalAlignment alignment) {
    for (const auto& m : kCellVerticalAlignmentMappings) {
        if (m.alignment == alignment) {
            return m.xml_value;
        }
    }
    return "top";
}

CellVerticalAlignment string_to_cell_vertical_alignment(const char* str) {
    for (const auto& m : kCellVerticalAlignmentMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.alignment;
        }
    }
    return CellVerticalAlignment::Top;
}

// TableAlignment lookup table
struct TableAlignmentMapping {
    TableAlignment alignment{};
    const char* xml_value{};
};

static const TableAlignmentMapping kTableAlignmentMappings[] = {
    {TableAlignment::Center, "center"},
    {TableAlignment::Right, "right"},
};

const char* table_alignment_to_string(TableAlignment alignment) {
    for (const auto& m : kTableAlignmentMappings) {
        if (m.alignment == alignment) {
            return m.xml_value;
        }
    }
    return "left";
}

TableAlignment string_to_table_alignment(const char* str) {
    for (const auto& m : kTableAlignmentMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.alignment;
        }
    }
    return TableAlignment::Left;
}

// DropCapPosition lookup table
struct DropCapPositionMapping {
    DropCapPosition position{};
    const char* xml_value{};
};

static const DropCapPositionMapping kDropCapPositionMappings[] = {
    {DropCapPosition::Normal, "drop"},
    {DropCapPosition::Margin, "margin"},
};

const char* drop_cap_position_to_string(DropCapPosition position) {
    for (const auto& m : kDropCapPositionMappings) {
        if (m.position == position) {
            return m.xml_value;
        }
    }
    return nullptr;
}

DropCapPosition string_to_drop_cap_position(const char* str) {
    for (const auto& m : kDropCapPositionMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.position;
        }
    }
    return DropCapPosition::Normal;
}

// ScriptType lookup table
struct ScriptTypeMapping {
    ScriptType type{};
    const char* xml_value{};
};

static const ScriptTypeMapping kScriptTypeMappings[] = {
    {ScriptType::Superscript, "superscript"},
    {ScriptType::Subscript, "subscript"},
};

const char* script_type_to_string(ScriptType type) {
    for (const auto& m : kScriptTypeMappings) {
        if (m.type == type) {
            return m.xml_value;
        }
    }
    return nullptr;
}

ScriptType string_to_script_type(const char* str) {
    for (const auto& m : kScriptTypeMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.type;
        }
    }
    return ScriptType::Normal;
}

// LineSpacingRule lookup table
struct LineSpacingRuleMapping {
    LineSpacingRule rule{};
    const char* xml_value{};
};

static const LineSpacingRuleMapping kLineSpacingRuleMappings[] = {
    {LineSpacingRule::Exact, "exact"},
    {LineSpacingRule::AtLeast, "atLeast"},
};

const char* line_spacing_rule_to_string(LineSpacingRule rule) {
    for (const auto& m : kLineSpacingRuleMappings) {
        if (m.rule == rule) {
            return m.xml_value;
        }
    }
    return "auto";
}

LineSpacingRule string_to_line_spacing_rule(const char* str) {
    for (const auto& m : kLineSpacingRuleMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.rule;
        }
    }
    return LineSpacingRule::Auto;
}

void strip_whitespace_text_nodes(pugi::xml_node node) {
    for (pugi::xml_node child = node.first_child(); child;) {
        const pugi::xml_node next = child.next_sibling();
        if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata) {
            node.remove_child(child);
        }
        child = next;
    }
}

// ============================================================================
// Shading Helpers
// ============================================================================
void serialize_shading_to_xml(pugi::xml_node parent, const Shading& shading) {
    if (!shading.has_fill()) {
        return;
    }
    auto shd = parent.append_child("w:shd");
    shd.append_attribute("w:val").set_value(shading.texture.c_str());
    if (!shading.foreground.is_auto()) {
        shd.append_attribute("w:color").set_value(shading.foreground.to_hex_rgb().c_str());
    }
    if (!shading.background.is_auto()) {
        shd.append_attribute("w:fill").set_value(shading.background.to_hex_rgb().c_str());
    }
}

void parse_shading_from_xml(pugi::xml_node shd, Shading& shading) {
    if (!shd) {
        return;
    }
    shading.texture = shd.attribute("w:val").value();
    if (shading.texture.empty()) {
        shading.texture = "clear";
    }
    auto color_attr = shd.attribute("w:color");
    if (color_attr) {
        const std::string val = color_attr.value();
        if (val == "auto") {
            shading.foreground = Color::auto_color();
        } else {
            shading.foreground = Color::from_hex(val);
        }
    }
    auto fill_attr = shd.attribute("w:fill");
    if (fill_attr) {
        const std::string val = fill_attr.value();
        if (val == "auto") {
            shading.background = Color::auto_color();
        } else {
            shading.background = Color::from_hex(val);
        }
    }
}

// ============================================================================
// Border Helpers
// ============================================================================
void parse_border_from_xml(pugi::xml_node border_node, Border& border) {
    if (!border_node) {
        return;
    }
    border.type = string_to_border_type(border_node.attribute("w:val").value());

    if (auto sz = border_node.attribute("w:sz")) {
        border.width = sz.as_int() / 8.0;
    }
    if (auto space = border_node.attribute("w:space")) {
        border.space = space.as_int();
    }
    if (auto color = border_node.attribute("w:color")) {
        const std::string c = color.value();
        if (c == "auto") {
            border.color = Color::auto_color();
        } else {
            border.color = Color::from_hex(c);
        }
    }
}

struct BorderParseMapping {
    const char* child_name;
    bool Borders::*defined_flag;
    Border Borders::*border_member;
};

static const BorderParseMapping kBorderParseMappings[] = {
    {"w:top", &Borders::top_defined, &Borders::top},
    {"w:left", &Borders::left_defined, &Borders::left},
    {"w:bottom", &Borders::bottom_defined, &Borders::bottom},
    {"w:right", &Borders::right_defined, &Borders::right},
    {"w:insideH", &Borders::inside_h_defined, &Borders::inside_horizontal},
    {"w:insideV", &Borders::inside_v_defined, &Borders::inside_vertical},
};

void parse_borders_from_xml(pugi::xml_node borders_node, Borders& borders) {
    if (!borders_node) {
        return;
    }
    borders.explicitly_defined = true;
    for (const auto& mapping : kBorderParseMappings) {
        if (auto child = borders_node.child(mapping.child_name)) {
            borders.*mapping.defined_flag = true;
            parse_border_from_xml(child, borders.*mapping.border_member);
        }
    }
}

static void serialize_border_to_xml(pugi::xml_node parent,
                                 const char* name,
                                 const Border& border,
                                 bool include_nil = false) {
    if (!border.is_visible()) {
        if (!include_nil || border.type != BorderType::None) {
            return;
        }
        auto node = parent.append_child(name);
        node.append_attribute("w:val").set_value("nil");
        return;
    }
    auto node = parent.append_child(name);
    node.append_attribute("w:val").set_value(border_type_to_string(border.type));
    node.append_attribute("w:sz").set_value(static_cast<int>(border.width * 8));
    node.append_attribute("w:space").set_value(static_cast<int>(border.space));
    if (border.color.is_auto()) {
        node.append_attribute("w:color").set_value("auto");
    } else {
        node.append_attribute("w:color").set_value(border.color.to_hex_rgb().c_str());
    }
}

struct BorderSerializeMapping {
    const char* child_name;
    const Border Borders::*border_member;
    bool Borders::*defined_flag;
};

static const BorderSerializeMapping kBorderSerializeMappings[] = {
    {"w:top", &Borders::top, &Borders::top_defined},
    {"w:left", &Borders::left, &Borders::left_defined},
    {"w:bottom", &Borders::bottom, &Borders::bottom_defined},
    {"w:right", &Borders::right, &Borders::right_defined},
    {"w:insideH", &Borders::inside_horizontal, &Borders::inside_h_defined},
    {"w:insideV", &Borders::inside_vertical, &Borders::inside_v_defined},
};

void serialize_borders_to_xml(pugi::xml_node parent,
                                  const char* container_name,
                                  const Borders& borders) {
    if (!borders.has_visible() && !borders.explicitly_defined) {
        return;
    }
    auto container = parent.append_child(container_name);
    for (const auto& mapping : kBorderSerializeMappings) {
        serialize_border_to_xml(
            container, mapping.child_name, borders.*mapping.border_member, borders.*mapping.defined_flag);
    }
}

// ============================================================================
// Property Helpers
// ============================================================================

std::string time_to_w3cdtf(std::time_t t) {
    if (t == 0) {
        return "";
    }
    std::tm utc{};
#ifdef _WIN32
    if (gmtime_s(&utc, &t) != 0) {
        return "";
    }
#else
    if (gmtime_r(&t, &utc) == nullptr) {
        return "";
    }
#endif
    char buf[32];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &utc) == 0) {
        return "";
    }
    return buf;
}

std::time_t timegm_wrapper(std::tm* tm) {
#ifdef _WIN32
    return _mkgmtime(tm);
#else
    return ::timegm(tm);
#endif
}

std::time_t w3cdtf_to_time(const std::string& s) {
    if (s.empty() || s.size() < 19) {
        return 0;
    }
    auto parse_component = [](const char* p, const char** end) -> int {
        int value = 0;
        auto result = std::from_chars(p, p + 4, value);
        *end = result.ptr;
        return value;
    };
    std::tm utc = {};
    const char* p = s.c_str();
    const char* end = nullptr;
    utc.tm_year = parse_component(p, &end) - 1900;
    p = end + 1;  // skip '-'
    utc.tm_mon = parse_component(p, &end) - 1;
    p = end + 1;  // skip '-'
    utc.tm_mday = parse_component(p, &end);
    p = end + 1;  // skip 'T'
    utc.tm_hour = parse_component(p, &end);
    p = end + 1;  // skip ':'
    utc.tm_min = parse_component(p, &end);
    p = end + 1;  // skip ':'
    utc.tm_sec = parse_component(p, &end);
    return timegm_wrapper(&utc);
}

pugi::xml_node get_or_create_child(pugi::xml_node parent, const char* name) {
    pugi::xml_node child = parent.child(name);
    if (!child) {
        child = parent.append_child(name);
    } else {
        child.remove_children();
    }
    return child;
}

pugi::xml_node ensure_child(pugi::xml_node parent, const char* name) {
    pugi::xml_node child = parent.child(name);
    if (!child) {
        child = parent.append_child(name);
    }
    return child;
}

void set_text_child(pugi::xml_node parent, const char* name, const std::string& value) {
    if (value.empty()) {
        const pugi::xml_node child = parent.child(name);
        if (child) {
            parent.remove_child(child);
        }
        return;
    }
    pugi::xml_node child = get_or_create_child(parent, name);
    child.append_child(pugi::node_pcdata).set_value(value.c_str());
}

// Highlight lookup table
struct HighlightMapping {
    TextProperties::Highlight highlight{};
    const char* xml_value{};
};

static const HighlightMapping kHighlightMappings[] = {
    {TextProperties::Highlight::Black, "black"},
    {TextProperties::Highlight::White, "white"},
    {TextProperties::Highlight::Red, "red"},
    {TextProperties::Highlight::Green, "green"},
    {TextProperties::Highlight::Blue, "blue"},
    {TextProperties::Highlight::Yellow, "yellow"},
    {TextProperties::Highlight::Cyan, "cyan"},
    {TextProperties::Highlight::Magenta, "magenta"},
    {TextProperties::Highlight::DarkRed, "darkRed"},
    {TextProperties::Highlight::DarkGreen, "darkGreen"},
    {TextProperties::Highlight::DarkBlue, "darkBlue"},
    {TextProperties::Highlight::DarkYellow, "darkYellow"},
    {TextProperties::Highlight::DarkCyan, "darkCyan"},
    {TextProperties::Highlight::DarkMagenta, "darkMagenta"},
    {TextProperties::Highlight::DarkGray, "darkGray"},
    {TextProperties::Highlight::LightGray, "lightGray"},
};

const char* highlight_to_string(TextProperties::Highlight highlight) {
    for (const auto& m : kHighlightMappings) {
        if (m.highlight == highlight) {
            return m.xml_value;
        }
    }
    return "yellow";
}

TextProperties::Highlight string_to_highlight(const char* str) {
    for (const auto& m : kHighlightMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.highlight;
        }
    }
    return TextProperties::Highlight::None;
}

// TextFormFieldType lookup table
struct TextFormFieldTypeMapping {
    TextFormFieldType type{};
    const char* xml_value{};
};

static const TextFormFieldTypeMapping kTextFormFieldTypeMappings[] = {
    {TextFormFieldType::Number, "number"},
    {TextFormFieldType::Date, "date"},
    {TextFormFieldType::CurrentDate, "currentDate"},
    {TextFormFieldType::CurrentTime, "currentTime"},
    {TextFormFieldType::Calculated, "calculated"},
};

const char* text_form_field_type_to_string(TextFormFieldType type) {
    for (const auto& m : kTextFormFieldTypeMappings) {
        if (m.type == type) {
            return m.xml_value;
        }
    }
    return "regular";
}

TextFormFieldType string_to_text_form_field_type(const char* str) {
    for (const auto& m : kTextFormFieldTypeMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.type;
        }
    }
    return TextFormFieldType::Regular;
}

// ============================================================================
// Image Drawing Helper
// ============================================================================

pugi::xml_node append_image_drawing(pugi::xml_node parent,
                                    const std::string& rel_id,
                                    const ImageSize& size,
                                    ImageAlignment align,
                                    int image_id,
                                    const std::string& image_name) {
    pugi::xml_node drawing = parent.append_child("w:drawing");
    drawing.append_attribute("xmlns:wp")
        .set_value("http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");

    // Build the picture subtree (shared between inline and anchor)
    auto build_pic = [&](pugi::xml_node container) {
        pugi::xml_node graphic = container.append_child("a:graphic");
        graphic.append_attribute("xmlns:a")
            .set_value("http://schemas.openxmlformats.org/drawingml/2006/main");

        pugi::xml_node graphic_data = graphic.append_child("a:graphicData");
        graphic_data.append_attribute("uri")
            .set_value("http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node pic = graphic_data.append_child("pic:pic");
        pic.append_attribute("xmlns:pic")
            .set_value("http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node nv_pic_pr = pic.append_child("pic:nvPicPr");
        pugi::xml_node cnv_pr = nv_pic_pr.append_child("pic:cNvPr");
        cnv_pr.append_attribute("id").set_value(0);
        cnv_pr.append_attribute("name").set_value(image_name.c_str());
        nv_pic_pr.append_child("pic:cNvPicPr");

        pugi::xml_node blip_fill = pic.append_child("pic:blipFill");
        pugi::xml_node blip = blip_fill.append_child("a:blip");
        blip.append_attribute("r:embed").set_value(rel_id.c_str());
        pugi::xml_node stretch = blip_fill.append_child("a:stretch");
        stretch.append_child("a:fillRect");

        pugi::xml_node sp_pr = pic.append_child("pic:spPr");
        pugi::xml_node xfrm = sp_pr.append_child("a:xfrm");
        pugi::xml_node ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx").set_value(size.width_emu());
        ext.append_attribute("cy").set_value(size.height_emu());
        pugi::xml_node prst_geom = sp_pr.append_child("a:prstGeom");
        prst_geom.append_attribute("prst").set_value("rect");
        prst_geom.append_child("a:avLst");
    };

    if (align == ImageAlignment::Center) {
        pugi::xml_node inline_node = drawing.append_child("wp:inline");
        inline_node.append_attribute("distT").set_value(0);
        inline_node.append_attribute("distB").set_value(0);
        inline_node.append_attribute("distL").set_value(0);
        inline_node.append_attribute("distR").set_value(0);

        pugi::xml_node extent = inline_node.append_child("wp:extent");
        extent.append_attribute("cx").set_value(size.width_emu());
        extent.append_attribute("cy").set_value(size.height_emu());

        pugi::xml_node doc_pr = inline_node.append_child("wp:docPr");
        doc_pr.append_attribute("id").set_value(image_id);
        doc_pr.append_attribute("name").set_value("Picture");

        build_pic(inline_node);
    } else {
        pugi::xml_node anchor = drawing.append_child("wp:anchor");
        anchor.append_attribute("simplePos").set_value(0);
        anchor.append_attribute("relativeHeight").set_value(251658240);
        anchor.append_attribute("behindDoc").set_value(0);
        anchor.append_attribute("locked").set_value(0);
        anchor.append_attribute("layoutInCell").set_value(1);
        anchor.append_attribute("allowOverlap").set_value(1);

        pugi::xml_node simple_pos = anchor.append_child("wp:simplePos");
        simple_pos.append_attribute("x").set_value(0);
        simple_pos.append_attribute("y").set_value(0);

        pugi::xml_node position_h = anchor.append_child("wp:positionH");
        position_h.append_attribute("relativeFrom").set_value("column");
        const pugi::xml_node align_node = position_h.append_child("wp:align");
        align_node.text().set(align == ImageAlignment::Left ? "left" : "right");

        pugi::xml_node position_v = anchor.append_child("wp:positionV");
        position_v.append_attribute("relativeFrom").set_value("paragraph");
        const pugi::xml_node pos_v_align = position_v.append_child("wp:align");
        pos_v_align.text().set("top");

        pugi::xml_node extent = anchor.append_child("wp:extent");
        extent.append_attribute("cx").set_value(size.width_emu());
        extent.append_attribute("cy").set_value(size.height_emu());

        pugi::xml_node doc_pr = anchor.append_child("wp:docPr");
        doc_pr.append_attribute("id").set_value(image_id);
        doc_pr.append_attribute("name").set_value("Picture");

        build_pic(anchor);
    }

    return drawing;
}

// ============================================================================
// Form Field Helpers
// ============================================================================

void serialize_ffdata_to_fld_char(pugi::xml_node fld_char, const FormField* field) {
    if (!field) {
        return;
    }
    auto ff_data = fld_char.append_child("w:ffData");
    if (!field->get_name().empty()) {
        ff_data.append_child("w:name").append_attribute("w:val").set_value(
            field->get_name().c_str());
    }
    ff_data.append_child("w:enabled")
        .append_attribute("w:val")
        .set_value(field->get_enabled() ? "1" : "0");
    ff_data.append_child("w:calcOnExit")
        .append_attribute("w:val")
        .set_value(field->get_calculate_on_exit() ? "1" : "0");
    if (!field->get_status_text().empty()) {
        ff_data.append_child("w:statusText")
            .append_attribute("w:val")
            .set_value(field->get_status_text().c_str());
    }
    if (!field->get_help_text().empty()) {
        ff_data.append_child("w:helpText")
            .append_attribute("w:val")
            .set_value(field->get_help_text().c_str());
    }
    if (!field->get_entry_macro().empty()) {
        ff_data.append_child("w:entryMacro")
            .append_attribute("w:val")
            .set_value(field->get_entry_macro().c_str());
    }
    if (!field->get_exit_macro().empty()) {
        ff_data.append_child("w:exitMacro")
            .append_attribute("w:val")
            .set_value(field->get_exit_macro().c_str());
    }

    switch (field->get_form_field_type()) {
        case FormFieldType::TextInput: {
            auto text_input = ff_data.append_child("w:textInput");
            const char* typeval = text_form_field_type_to_string(field->get_text_input_type());
            text_input.append_child("w:type").append_attribute("w:val").set_value(typeval);
            if (!field->get_text_input_default().empty()) {
                text_input.append_child("w:default")
                    .append_attribute("w:val")
                    .set_value(field->get_text_input_default().c_str());
            }
            if (field->get_max_length() > 0) {
                text_input.append_child("w:maxLength")
                    .append_attribute("w:val")
                    .set_value(field->get_max_length());
            }
            if (!field->get_text_input_format().empty()) {
                text_input.append_child("w:format")
                    .append_attribute("w:val")
                    .set_value(field->get_text_input_format().c_str());
            }
            break;
        }
        case FormFieldType::CheckBox: {
            auto check_box = ff_data.append_child("w:checkBox");
            if (field->get_is_check_box_exact_size() && field->get_check_box_size() > 0) {
                auto size = check_box.append_child("w:size");
                size.append_attribute("w:val").set_value(
                    static_cast<int>(field->get_check_box_size() * 2));
            } else {
                check_box.append_child("w:sizeAuto");
            }
            check_box.append_child("w:default")
                .append_attribute("w:val")
                .set_value(field->get_default_value() ? "1" : "0");
            check_box.append_child("w:checked")
                .append_attribute("w:val")
                .set_value(field->get_checked() ? "1" : "0");
            break;
        }
        case FormFieldType::ComboBox: {
            auto dd_list = ff_data.append_child("w:ddList");
            for (const auto& item : field->get_drop_down_items()) {
                dd_list.append_child("w:listEntry").append_attribute("w:val").set_value(
                    item.c_str());
            }
            if (field->get_drop_down_selected_index() >= 0) {
                dd_list.append_child("w:default")
                    .append_attribute("w:val")
                    .set_value(field->get_drop_down_selected_index());
            }
            break;
        }
    }
}

void append_form_field_sequence(pugi::xml_node parent, const FormField* field, Document* doc) {
    if (!field) {
        return;
    }

    int bookmark_id = 0;
    if (!field->get_name().empty() && doc) {
        auto bm_start = parent.append_child("w:bookmarkStart");
        bookmark_id = doc->generate_unique_bookmark_id();
        bm_start.append_attribute("w:id").set_value(bookmark_id);
        bm_start.append_attribute("w:name").set_value(field->get_name().c_str());
    }

    auto begin_run = parent.append_child("w:r");
    auto fld_char = begin_run.append_child("w:fldChar");
    fld_char.append_attribute("w:fldCharType").set_value("begin");

    serialize_ffdata_to_fld_char(fld_char, field);

    // Instruction text
    struct FormFieldInstrMapping {
        FormFieldType type;
        const char* instr;
    };
    static const FormFieldInstrMapping kFormFieldInstrMappings[] = {
        {FormFieldType::TextInput, "FORMTEXT"},
        {FormFieldType::CheckBox, "FORMCHECKBOX"},
        {FormFieldType::ComboBox, "FORMDROPDOWN"},
    };
    const char* instr = "FORMTEXT";
    for (const auto& mapping : kFormFieldInstrMappings) {
        if (mapping.type == field->get_form_field_type()) {
            instr = mapping.instr;
            break;
        }
    }
    auto instr_run = parent.append_child("w:r");
    auto instr_text = instr_run.append_child("w:instrText");
    instr_text.text().set(instr);

    auto sep_run = parent.append_child("w:r");
    sep_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("separate");

    const std::string result = field->get_result();
    if (!result.empty()) {
        auto res_run = parent.append_child("w:r");
        auto text_node = res_run.append_child("w:t");
        text_node.text().set(result.c_str());
    }

    auto end_run = parent.append_child("w:r");
    end_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("end");

    if (bookmark_id != 0) {
        auto bm_end = parent.append_child("w:bookmarkEnd");
        bm_end.append_attribute("w:id").set_value(bookmark_id);
    }
}

}  // namespace cdocx
