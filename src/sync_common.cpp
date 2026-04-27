/**
 * @file sync_common.cpp
 * @brief Shared helpers and lookup tables for DOM-Physical sync
 * @internal Not part of the public API.
 */

#include "sync_common.h"

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

const char* header_footer_type_to_string(HeaderFooterType type) {
    switch (type) {
        case HeaderFooterType::First:
        case HeaderFooterType::FirstPage:
            return "first";
        case HeaderFooterType::Even:
        case HeaderFooterType::EvenPages:
            return "even";
        default:
            return "default";
    }
}

HeaderFooterType string_to_header_footer_type(const char* val) {
    if (std::strcmp(val, "first") == 0) {
        return HeaderFooterType::First;
    }
    if (std::strcmp(val, "even") == 0) {
        return HeaderFooterType::Even;
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

void parse_borders_from_xml(pugi::xml_node borders_node, Borders& borders) {
    if (!borders_node) {
        return;
    }
    borders.explicitly_defined = true;
    if (borders_node.child("w:top")) {
        borders.top_defined = true;
        parse_border_from_xml(borders_node.child("w:top"), borders.top);
    }
    if (borders_node.child("w:left")) {
        borders.left_defined = true;
        parse_border_from_xml(borders_node.child("w:left"), borders.left);
    }
    if (borders_node.child("w:bottom")) {
        borders.bottom_defined = true;
        parse_border_from_xml(borders_node.child("w:bottom"), borders.bottom);
    }
    if (borders_node.child("w:right")) {
        borders.right_defined = true;
        parse_border_from_xml(borders_node.child("w:right"), borders.right);
    }
    if (borders_node.child("w:insideH")) {
        borders.inside_h_defined = true;
        parse_border_from_xml(borders_node.child("w:insideH"), borders.inside_horizontal);
    }
    if (borders_node.child("w:insideV")) {
        borders.inside_v_defined = true;
        parse_border_from_xml(borders_node.child("w:insideV"), borders.inside_vertical);
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

void serialize_borders_to_xml(pugi::xml_node parent,
                                  const char* container_name,
                                  const Borders& borders) {
    if (!borders.has_visible() && !borders.explicitly_defined) {
        return;
    }
    auto container = parent.append_child(container_name);
    serialize_border_to_xml(container, "w:top", borders.top, borders.top_defined);
    serialize_border_to_xml(container, "w:left", borders.left, borders.left_defined);
    serialize_border_to_xml(container, "w:bottom", borders.bottom, borders.bottom_defined);
    serialize_border_to_xml(container, "w:right", borders.right, borders.right_defined);
    serialize_border_to_xml(
        container, "w:insideH", borders.inside_horizontal, borders.inside_h_defined);
    serialize_border_to_xml(
        container, "w:insideV", borders.inside_vertical, borders.inside_v_defined);
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

}  // namespace cdocx
