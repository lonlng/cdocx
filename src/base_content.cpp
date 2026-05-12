/**
 * @file base_content.cpp
 * @brief Implementation of base content classes (Run, SpecialChar, Field, etc.)
 * @version 0.8.0 - DOM Style
 */

#include <cdocx/base.h>
#include <cdocx/convert_util.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>

#include <cstring>
#include <utility>

#include "sync_common.h"

namespace cdocx {

namespace {

struct HighlightMapping {
    TextProperties::Highlight highlight;
    HighlightColor color;
};

static const HighlightMapping kHighlightMappings[] = {
    {TextProperties::Highlight::Yellow, HighlightColor::Yellow},
    {TextProperties::Highlight::Green, HighlightColor::Green},
    {TextProperties::Highlight::Cyan, HighlightColor::Turquoise},
    {TextProperties::Highlight::Magenta, HighlightColor::Pink},
    {TextProperties::Highlight::Blue, HighlightColor::Blue},
    {TextProperties::Highlight::Red, HighlightColor::Red},
    {TextProperties::Highlight::Black, HighlightColor::Black},
    {TextProperties::Highlight::White, HighlightColor::White},
    {TextProperties::Highlight::DarkRed, HighlightColor::DarkRed},
    {TextProperties::Highlight::DarkGreen, HighlightColor::BrightGreen},
    {TextProperties::Highlight::DarkBlue, HighlightColor::DarkBlue},
    {TextProperties::Highlight::DarkYellow, HighlightColor::DarkYellow},
    {TextProperties::Highlight::DarkCyan, HighlightColor::Teal},
    {TextProperties::Highlight::DarkMagenta, HighlightColor::Violet},
    {TextProperties::Highlight::DarkGray, HighlightColor::Gray50},
    {TextProperties::Highlight::LightGray, HighlightColor::Gray25},
};

static HighlightColor highlight_to_color(TextProperties::Highlight highlight) {
    for (const auto& mapping : kHighlightMappings) {
        if (mapping.highlight == highlight) {
            return mapping.color;
        }
    }
    return HighlightColor::None;
}

struct UnderlineStyleMapping {
    TextProperties::UnderlineStyle style{};
    const char* xml_value{};
};

static const UnderlineStyleMapping kUnderlineStyleMappings[] = {
    {TextProperties::UnderlineStyle::Words, "words"},
    {TextProperties::UnderlineStyle::Single, "single"},
    {TextProperties::UnderlineStyle::Double, "double"},
    {TextProperties::UnderlineStyle::Thick, "thick"},
    {TextProperties::UnderlineStyle::Dotted, "dotted"},
    {TextProperties::UnderlineStyle::DottedHeavy, "dottedHeavy"},
    {TextProperties::UnderlineStyle::Dash, "dash"},
    {TextProperties::UnderlineStyle::DashedHeavy, "dashedHeavy"},
    {TextProperties::UnderlineStyle::DashLong, "dashLong"},
    {TextProperties::UnderlineStyle::DashLongHeavy, "dashLongHeavy"},
    {TextProperties::UnderlineStyle::DotDash, "dotDash"},
    {TextProperties::UnderlineStyle::DashDotHeavy, "dashDotHeavy"},
    {TextProperties::UnderlineStyle::DotDotDash, "dotDotDash"},
    {TextProperties::UnderlineStyle::DashDotDotHeavy, "dashDotDotHeavy"},
    {TextProperties::UnderlineStyle::Wave, "wave"},
    {TextProperties::UnderlineStyle::WavyDouble, "wavyDouble"},
    {TextProperties::UnderlineStyle::WavyHeavy, "wavyHeavy"},
};

const char* underline_style_to_string(TextProperties::UnderlineStyle style) {
    for (const auto& m : kUnderlineStyleMappings) {
        if (m.style == style) {
            return m.xml_value;
        }
    }
    return "single";
}

TextProperties::UnderlineStyle string_to_underline_style(const char* str) {
    for (const auto& m : kUnderlineStyleMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.style;
        }
    }
    return TextProperties::UnderlineStyle::Single;
}

struct UnderlineStyleToTypeMapping {
    TextProperties::UnderlineStyle style{};
    UnderlineType type{};
};

static const UnderlineStyleToTypeMapping kUnderlineStyleToTypeMappings[] = {
    {TextProperties::UnderlineStyle::None, UnderlineType::None},
    {TextProperties::UnderlineStyle::Words, UnderlineType::Words},
    {TextProperties::UnderlineStyle::Single, UnderlineType::Single},
    {TextProperties::UnderlineStyle::Double, UnderlineType::Double},
    {TextProperties::UnderlineStyle::Thick, UnderlineType::Thick},
    {TextProperties::UnderlineStyle::Dotted, UnderlineType::Dotted},
    {TextProperties::UnderlineStyle::DottedHeavy, UnderlineType::DottedHeavy},
    {TextProperties::UnderlineStyle::Dash, UnderlineType::Dash},
    {TextProperties::UnderlineStyle::DashedHeavy, UnderlineType::DashHeavy},
    {TextProperties::UnderlineStyle::DashLong, UnderlineType::Dash},
    {TextProperties::UnderlineStyle::DashLongHeavy, UnderlineType::DashHeavy},
    {TextProperties::UnderlineStyle::DotDash, UnderlineType::DashDot},
    {TextProperties::UnderlineStyle::DashDotHeavy, UnderlineType::DashDotHeavy},
    {TextProperties::UnderlineStyle::DotDotDash, UnderlineType::DashDotDot},
    {TextProperties::UnderlineStyle::DashDotDotHeavy, UnderlineType::DashDotDotHeavy},
    {TextProperties::UnderlineStyle::Wave, UnderlineType::Wave},
    {TextProperties::UnderlineStyle::WavyDouble, UnderlineType::Wave},
    {TextProperties::UnderlineStyle::WavyHeavy, UnderlineType::WaveHeavy},
};

UnderlineType underline_style_to_type(TextProperties::UnderlineStyle style) {
    for (const auto& m : kUnderlineStyleToTypeMappings) {
        if (m.style == style) {
            return m.type;
        }
    }
    return UnderlineType::Single;
}

// ---------------------------------------------------------------------------
// Position Type (vertAlign)
// ---------------------------------------------------------------------------

struct PositionTypeMapping {
    TextProperties::PositionType type;
    const char* xml_value;
};

static const PositionTypeMapping kPositionTypeMappings[] = {
    {TextProperties::PositionType::Raised, "superscript"},
    {TextProperties::PositionType::Lowered, "subscript"},
};

static const char* position_type_to_string(TextProperties::PositionType type) {
    for (const auto& m : kPositionTypeMappings) {
        if (m.type == type) {
            return m.xml_value;
        }
    }
    return nullptr;
}

static TextProperties::PositionType string_to_position_type(const char* val) {
    if (!val || !*val) {
        return TextProperties::PositionType::Normal;
    }
    for (const auto& m : kPositionTypeMappings) {
        if (std::strcmp(m.xml_value, val) == 0) {
            return m.type;
        }
    }
    return TextProperties::PositionType::Normal;
}

// ---------------------------------------------------------------------------
// PositionType → ScriptType (for Run::set_position)
// ---------------------------------------------------------------------------

struct PositionScriptMapping {
    TextProperties::PositionType position;
    ScriptType script;
};

static const PositionScriptMapping kPositionScriptMappings[] = {
    {TextProperties::PositionType::Raised, ScriptType::Superscript},
    {TextProperties::PositionType::Lowered, ScriptType::Subscript},
};

// ---------------------------------------------------------------------------
// SpacingType → sign multiplier (for Run::set_spacing)
// ---------------------------------------------------------------------------

struct SpacingSignMapping {
    TextProperties::SpacingType type;
    int sign;
};

static const SpacingSignMapping kSpacingSignMappings[] = {
    {TextProperties::SpacingType::Expanded, 1},
    {TextProperties::SpacingType::Condensed, -1},
};

}  // anonymous namespace

// ============================================================================
// Run DOM Implementation
// ============================================================================

Run::Run() = default;

Run::Run(Document* doc) {
    set_document(doc);
}

Run::Run(Document* doc, std::string text) : text_(std::move(text)) {
    set_document(doc);
}

Run::Run(const Run& other)
    : Inline(other),
      parent_xml_(other.parent_xml_),
      current_xml_(other.current_xml_),
      text_(other.text_) {
    for (auto child = other.preserved_children_.first_child(); child;
         child = child.next_sibling()) {
        preserved_children_.append_copy(child);
    }
}

Run& Run::operator=(const Run& other) {
    if (this != &other) {
        Inline::operator=(other);
        text_ = other.text_;
        parent_xml_ = other.parent_xml_;
        current_xml_ = other.current_xml_;
        preserved_children_.reset();
        for (auto child = other.preserved_children_.first_child(); child;
             child = child.next_sibling()) {
            preserved_children_.append_copy(child);
        }
    }
    return *this;
}

Run& Run::set_properties(const TextProperties& props) {
    props.apply_to(*this);
    return *this;
}

Run& Run::set_underline_style(TextProperties::UnderlineStyle style, const std::string& color) {
    set_underline(underline_style_to_type(style));
    if (!color.empty() && color != "auto") {
        font_.underline_color = Color(color);
    }
    return *this;
}

Run& Run::set_spacing(TextProperties::SpacingType type, int value) {
    for (const auto& mapping : kSpacingSignMappings) {
        if (mapping.type == type) {
            font_.spacing = mapping.sign * ConvertUtil::twips_to_point(value);
            return *this;
        }
    }
    font_.spacing = 0;
    return *this;
}

Run& Run::set_position(TextProperties::PositionType type, int value) {
    (void)value;
    for (const auto& mapping : kPositionScriptMappings) {
        if (mapping.position == type) {
            font_.script_type = mapping.script;
            return *this;
        }
    }
    font_.script_type = ScriptType::Normal;
    return *this;
}

Run& Run::set_scale(int percent) {
    font_.scale = percent;
    return *this;
}

Run& Run::set_strike(TextProperties::StrikeStyle style) {
    set_strikethrough(style != TextProperties::StrikeStyle::None);
    return *this;
}

Run& Run::set_highlight(TextProperties::Highlight color) {
    font_.highlight = highlight_to_color(color);
    return *this;
}

void Run::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_run(*this);
    }
}

std::shared_ptr<Node> Run::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<Run>(get_document(), text_);
    cloned->font_ = font_;
    if (preserved_r_pr_.first_child()) {
        cloned->preserved_r_pr_.append_copy(preserved_r_pr_.first_child());
    }
    if (preserved_children_.first_child()) {
        for (auto child = preserved_children_.first_child(); child; child = child.next_sibling()) {
            cloned->preserved_children_.append_copy(child);
        }
    }
    return cloned;
}

void Run::preserve_child(pugi::xml_node child) {
    if (child) {
        preserved_children_.append_copy(child);
    }
}

void Run::serialize_preserved_children(pugi::xml_node run_xml) const {
    for (auto child = preserved_children_.first_child(); child; child = child.next_sibling()) {
        run_xml.append_copy(child);
    }
}

bool Run::has_preserved_children() const {
    return preserved_children_.first_child() != nullptr;
}

// ============================================================================
// Run Legacy Implementation (XML-based)
// ============================================================================

Run::Run(pugi::xml_node parent, pugi::xml_node current)
    : parent_xml_(parent), current_xml_(current) {
}

void Run::set_parent_xml(pugi::xml_node node) {
    parent_xml_ = node;
    current_xml_ = parent_xml_.child("w:r");
}

void Run::set_current_xml(pugi::xml_node node) {
    current_xml_ = node;
}

Run& Run::next() {
    current_xml_ = current_xml_.next_sibling("w:r");
    return *this;
}

bool Run::has_next() const {
    return current_xml_ != nullptr;
}

std::string Run::get_text_xml() const {
    if (!current_xml_) {
        return "";
    }
    return current_xml_.child("w:t").text().get();
}

bool Run::set_text_xml(const std::string& text) const {
    if (!current_xml_) {
        return false;
    }
    return current_xml_.child("w:t").text().set(text.c_str());
}

namespace {
pugi::xml_node ensure_r_pr(pugi::xml_node current_xml) {
    auto r_pr = current_xml.child("w:rPr");
    if (!r_pr) {
        // Insert after any w:rPr element? Just prepend before w:t or other children
        r_pr = current_xml.prepend_child("w:rPr");
    }
    return r_pr;
}

pugi::xml_attribute set_attr(pugi::xml_node node, const char* name, const char* value) {
    auto attr = node.attribute(name);
    if (!attr) {
        attr = node.append_attribute(name);
    }
    attr.set_value(value);
    return attr;
}

pugi::xml_attribute set_attr(pugi::xml_node node, const char* name, int value) {
    auto attr = node.attribute(name);
    if (!attr) {
        attr = node.append_attribute(name);
    }
    attr.set_value(value);
    return attr;
}
}  // namespace

bool Run::set_color_xml(const std::string& color_hex) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (color_hex.empty() || color_hex == "auto") {
        r_pr.remove_child("w:color");
        return true;
    }
    auto color = r_pr.child("w:color");
    if (!color) {
        color = r_pr.append_child("w:color");
    }
    set_attr(color, "w:val", color_hex.c_str());
    return true;
}

bool Run::set_font_size_xml(int size) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (size <= 0) {
        r_pr.remove_child("w:sz");
        r_pr.remove_child("w:szCs");
        return true;
    }
    auto sz = r_pr.child("w:sz");
    if (!sz) {
        sz = r_pr.append_child("w:sz");
    }
    set_attr(sz, "w:val", size);
    auto sz_cs = r_pr.child("w:szCs");
    if (!sz_cs) {
        sz_cs = r_pr.append_child("w:szCs");
    }
    set_attr(sz_cs, "w:val", size);
    return true;
}

bool Run::set_font_name_xml(const std::string& font_name) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (font_name.empty()) {
        r_pr.remove_child("w:rFonts");
        return true;
    }
    auto fonts = r_pr.child("w:rFonts");
    if (!fonts) {
        fonts = r_pr.append_child("w:rFonts");
    }
    set_attr(fonts, "w:ascii", font_name.c_str());
    set_attr(fonts, "w:hAnsi", font_name.c_str());
    set_attr(fonts, "w:cs", font_name.c_str());
    set_attr(fonts, "w:eastAsia", font_name.c_str());
    return true;
}

bool Run::set_bold_xml(bool bold) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (bold) {
        ensure_child(r_pr, "w:b");
    } else {
        r_pr.remove_child("w:b");
    }
    return true;
}

bool Run::set_italic_xml(bool italic) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (italic) {
        ensure_child(r_pr, "w:i");
    } else {
        r_pr.remove_child("w:i");
    }
    return true;
}

bool Run::set_underline_xml(bool underline) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (underline) {
        auto u = r_pr.child("w:u");
        if (!u) {
            u = r_pr.append_child("w:u");
        }
        set_attr(u, "w:val", "single");
    } else {
        r_pr.remove_child("w:u");
    }
    return true;
}

void Run::set_properties_xml(const TextProperties& props) {
    if (!current_xml_) {
        return;
    }

    if (props.font) {
        set_font_name_xml(props.font->ascii);
    }
    set_bold_xml(props.font_style.bold);
    set_italic_xml(props.font_style.italic);
    if (props.font_size > 0) {
        set_font_size_xml(props.font_size);
    }
    if (!props.color.empty()) {
        set_color_xml(props.color);
    }
    if (props.underline.style != TextProperties::UnderlineStyle::None) {
        set_underline_style_xml(props.underline.style, props.underline.color);
    } else {
        auto r_pr = current_xml_.child("w:rPr");
        if (r_pr) {
            r_pr.remove_child("w:u");
        }
    }
    set_strike_xml(props.strike);
    if (props.highlight != TextProperties::Highlight::None) {
        set_highlight_xml(props.highlight);
    } else {
        auto r_pr = current_xml_.child("w:rPr");
        if (r_pr) {
            r_pr.remove_child("w:highlight");
        }
    }
    if (props.scale != 100) {
        set_scale_xml(props.scale);
    } else {
        auto r_pr = current_xml_.child("w:rPr");
        if (r_pr) {
            r_pr.remove_child("w:w");
        }
    }
    if (props.spacing.type != TextProperties::SpacingType::Normal) {
        set_spacing_xml(props.spacing.type, props.spacing.value);
    } else {
        auto r_pr = current_xml_.child("w:rPr");
        if (r_pr) {
            r_pr.remove_child("w:spacing");
        }
    }
    if (props.position.type != TextProperties::PositionType::Normal) {
        set_position_xml(props.position.type, props.position.value);
    } else {
        auto r_pr = current_xml_.child("w:rPr");
        if (r_pr) {
            r_pr.remove_child("w:vertAlign");
            r_pr.remove_child("w:position");
        }
    }
}

TextProperties Run::get_properties_xml() const {
    TextProperties props;
    if (!current_xml_) {
        return props;
    }

    auto r_pr = current_xml_.child("w:rPr");
    if (!r_pr) {
        return props;
    }

    // Font
    auto r_fonts = r_pr.child("w:rFonts");
    if (r_fonts) {
        TextProperties::Font font;
        font.ascii = r_fonts.attribute("w:ascii").value();
        font.h_ansi = r_fonts.attribute("w:hAnsi").value();
        font.cs = r_fonts.attribute("w:cs").value();
        font.east_asia = r_fonts.attribute("w:eastAsia").value();
        props.font = font;
    }

    // Bold / Italic
    props.font_style.bold = r_pr.child("w:b") != nullptr;
    props.font_style.italic = r_pr.child("w:i") != nullptr;

    // Font size
    auto sz = r_pr.child("w:sz");
    if (sz) {
        props.font_size = sz.attribute("w:val").as_int();
    }

    // Color
    auto color = r_pr.child("w:color");
    if (color) {
        props.color = color.attribute("w:val").value();
    }

    // Underline
    auto u = r_pr.child("w:u");
    if (u) {
        auto& ul = props.underline;
        ul.style = string_to_underline_style(u.attribute("w:val").value());
        auto ucolor = u.attribute("w:color");
        if (ucolor) {
            ul.color = ucolor.value();
        }
    }

    // Strike
    if (r_pr.child("w:dstrike")) {
        props.strike = TextProperties::StrikeStyle::Double;
    } else if (r_pr.child("w:strike")) {
        props.strike = TextProperties::StrikeStyle::Single;
    }

    // Highlight
    auto hl = r_pr.child("w:highlight");
    if (hl) {
        props.highlight = string_to_highlight(hl.attribute("w:val").value());
    }

    // Scale
    auto w = r_pr.child("w:w");
    if (w) {
        props.scale = w.attribute("w:val").as_int(100);
    }

    // Spacing
    auto sp = r_pr.child("w:spacing");
    if (sp) {
        const int sval = sp.attribute("w:val").as_int();
        if (sval >= 0) {
            props.spacing.type = TextProperties::SpacingType::Expanded;
            props.spacing.value = sval;
        } else {
            props.spacing.type = TextProperties::SpacingType::Condensed;
            props.spacing.value = -sval;
        }
    }

    // Position (vertAlign / position)
    if (auto va = r_pr.child("w:vertAlign")) {
        props.position.type = string_to_position_type(va.attribute("w:val").value());
        if (auto pos = r_pr.child("w:position")) {
            props.position.value = std::abs(pos.attribute("w:val").as_int());
        }
    }

    return props;
}

bool Run::set_highlight_xml(TextProperties::Highlight color) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (color == TextProperties::Highlight::None) {
        r_pr.remove_child("w:highlight");
        return true;
    }
    const char* val = highlight_to_string(color);
    auto hl = r_pr.child("w:highlight");
    if (!hl) {
        hl = r_pr.append_child("w:highlight");
    }
    set_attr(hl, "w:val", val);
    return true;
}

bool Run::set_underline_style_xml(TextProperties::UnderlineStyle style, const std::string& color) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (style == TextProperties::UnderlineStyle::None) {
        r_pr.remove_child("w:u");
        return true;
    }

    const char* val = underline_style_to_string(style);
    auto u = r_pr.child("w:u");
    if (!u) {
        u = r_pr.append_child("w:u");
    }
    set_attr(u, "w:val", val);
    if (!color.empty() && color != "auto") {
        set_attr(u, "w:color", color.c_str());
    }
    return true;
}

bool Run::set_strike_xml(TextProperties::StrikeStyle style) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    r_pr.remove_child("w:strike");
    r_pr.remove_child("w:dstrike");
    if (style == TextProperties::StrikeStyle::Single) {
        r_pr.append_child("w:strike");
    } else if (style == TextProperties::StrikeStyle::Double) {
        r_pr.append_child("w:dstrike");
    }
    return true;
}

bool Run::set_scale_xml(int percent) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (percent <= 0 || percent == 100) {
        r_pr.remove_child("w:w");
        return true;
    }
    auto w = r_pr.child("w:w");
    if (!w) {
        w = r_pr.append_child("w:w");
    }
    set_attr(w, "w:val", percent);
    return true;
}

bool Run::set_spacing_xml(TextProperties::SpacingType type, int value) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (type == TextProperties::SpacingType::Normal || value == 0) {
        r_pr.remove_child("w:spacing");
        return true;
    }
    auto sp = r_pr.child("w:spacing");
    if (!sp) {
        sp = r_pr.append_child("w:spacing");
    }
    const int val = (type == TextProperties::SpacingType::Expanded) ? value : -value;
    set_attr(sp, "w:val", val);
    return true;
}

bool Run::set_position_xml(TextProperties::PositionType type, int value) {
    if (!current_xml_) {
        return false;
    }
    auto r_pr = ensure_r_pr(current_xml_);
    if (type == TextProperties::PositionType::Normal) {
        r_pr.remove_child("w:vertAlign");
        r_pr.remove_child("w:position");
        return true;
    }
    const char* valign = position_type_to_string(type);
    auto va = r_pr.child("w:vertAlign");
    if (!va) {
        va = r_pr.append_child("w:vertAlign");
    }
    set_attr(va, "w:val", valign);
    if (value != 0) {
        auto pos = r_pr.child("w:position");
        if (!pos) {
            pos = r_pr.append_child("w:position");
        }
        const int val = (type == TextProperties::PositionType::Raised) ? value : -value;
        set_attr(pos, "w:val", val);
    } else {
        r_pr.remove_child("w:position");
    }
    return true;
}

// ============================================================================
// RunCollection Implementation
// ============================================================================

void RunCollection::add(const std::shared_ptr<Run>& run) {
    if (run) {
        runs_.push_back(run);
    }
}

void RunCollection::remove(const std::shared_ptr<Run>& run) {
    if (!run) {
        return;
    }
    for (auto it = runs_.begin(); it != runs_.end(); ++it) {
        if (*it == run) {
            runs_.erase(it);
            return;
        }
    }
}

void RunCollection::remove_at(int index) {
    if (index >= 0 && static_cast<size_t>(index) < runs_.size()) {
        runs_.erase(runs_.begin() + index);
    }
}

void RunCollection::clear() {
    runs_.clear();
}

// get_item, first, last are inline in base.h

std::string RunCollection::get_text() const {
    std::string result;
    for (const auto& run : runs_) {
        if (run) {
            result += run->get_text();
        }
    }
    return result;
}

// ============================================================================
// SpecialChar Implementation
// ============================================================================

SpecialChar::SpecialChar() = default;

SpecialChar::SpecialChar(char16_t char_code) : char_code_(char_code) {
}

std::string SpecialChar::get_text() const {
    // Convert char16_t to UTF-8 string
    std::string result;
    if (char_code_ <= 0x7F) {
        result += static_cast<char>(char_code_);
    } else if (char_code_ <= 0x7FF) {
        result += static_cast<char>(0xC0 | ((char_code_ >> 6) & 0x1F));
        result += static_cast<char>(0x80 | (char_code_ & 0x3F));
    } else {
        result += static_cast<char>(0xE0 | ((char_code_ >> 12) & 0x0F));
        result += static_cast<char>(0x80 | ((char_code_ >> 6) & 0x3F));
        result += static_cast<char>(0x80 | (char_code_ & 0x3F));
    }
    return result;
}

void SpecialChar::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_special_char(*this);
    }
}

std::shared_ptr<Node> SpecialChar::clone(bool /*deep*/) const {
    return std::make_shared<SpecialChar>(char_code_);
}

std::shared_ptr<SpecialChar> SpecialChar::paragraph_break() {
    return std::make_shared<SpecialChar>(0x000D);  // CR
}

std::shared_ptr<SpecialChar> SpecialChar::line_break() {
    return std::make_shared<SpecialChar>(0x000A);  // LF
}

std::shared_ptr<SpecialChar> SpecialChar::page_break() {
    return std::make_shared<SpecialChar>(0x000C);  // Form feed
}

std::shared_ptr<SpecialChar> SpecialChar::column_break() {
    return std::make_shared<SpecialChar>(0x000E);  // SO
}

std::shared_ptr<SpecialChar> SpecialChar::tab() {
    return std::make_shared<SpecialChar>(0x0009);  // Tab
}

// ============================================================================
// Field Implementation
// ============================================================================

Field::Field() = default;

Field::Field(FieldType type) : type_(type) {
}

Field::Field(Document* doc, FieldType type) : type_(type) {
    set_document(doc);
}

void Field::update() {
    // Subclasses implement
}

void Field::unlink() {
    // Replace field with its result
    result_ = get_text();
}

void Field::accept(DocumentVisitor* visitor) {
    if (!visitor) {
        return;
    }
    if (visitor->visit_field_start(*this) == VisitorAction::Continue) {
        visitor->visit_field_end(*this);
    }
}

void Field::add_switch(const std::string& switch_text) {
    switches_.push_back(switch_text);
}

void Field::clear_switches() {
    switches_.clear();
}

std::string Field::get_switches_text() const {
    std::string result;
    for (const auto& sw : switches_) {
        if (!result.empty()) {
            result += " ";
        }
        result += sw;
    }
    return result;
}

std::string Field::get_full_field_code() const {
    std::string result = field_code_;
    const std::string sw = get_switches_text();
    if (!sw.empty()) {
        if (!result.empty()) {
            result += " ";
        }
        result += sw;
    }
    return result;
}

std::shared_ptr<Node> Field::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<Field>(get_document(), type_);
    cloned->field_code_ = field_code_;
    cloned->result_ = result_;
    cloned->switches_ = switches_;
    cloned->is_locked_ = is_locked_;
    cloned->is_dirty_ = is_dirty_;
    return cloned;
}

// ============================================================================
// BookmarkStart Implementation
// ============================================================================

BookmarkStart::BookmarkStart() = default;

BookmarkStart::BookmarkStart(std::string name, int id) : name_(std::move(name)), id_(id) {
}

BookmarkStart::BookmarkStart(Document* doc) {
    set_document(doc);
}

void BookmarkStart::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_bookmark_start(*this);
    }
}

std::shared_ptr<Node> BookmarkStart::clone(bool /*deep*/) const {
    return std::make_shared<BookmarkStart>(name_, id_);
}

// ============================================================================
// BookmarkEnd Implementation
// ============================================================================

BookmarkEnd::BookmarkEnd() = default;

BookmarkEnd::BookmarkEnd(int id) : id_(id) {
}

BookmarkEnd::BookmarkEnd(Document* doc) {
    set_document(doc);
}

void BookmarkEnd::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_bookmark_end(*this);
    }
}

std::shared_ptr<Node> BookmarkEnd::clone(bool /*deep*/) const {
    return std::make_shared<BookmarkEnd>(id_);
}

// ============================================================================
// Hyperlink Implementation
// ============================================================================

Hyperlink::Hyperlink() = default;

Hyperlink::Hyperlink(Document* doc) {
    set_document(doc);
}

void Hyperlink::set_address(const std::string& url) {
    address_ = url;
    bookmark_name_.clear();
}

void Hyperlink::set_bookmark_name(const std::string& name) {
    bookmark_name_ = name;
    address_.clear();
}

void Hyperlink::set_tooltip(const std::string& tooltip) {
    tooltip_ = tooltip;
}

void Hyperlink::set_screen_tip(const std::string& tip) {
    screen_tip_ = tip;
}

std::string Hyperlink::get_address() const {
    return address_;
}

std::string Hyperlink::get_bookmark_name() const {
    return bookmark_name_;
}

std::string Hyperlink::get_tooltip() const {
    return tooltip_;
}

std::string Hyperlink::get_screen_tip() const {
    return screen_tip_;
}

std::shared_ptr<Node> Hyperlink::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<Hyperlink>(get_document());
    cloned->set_field_code(get_field_code());
    cloned->set_result(get_result());
    cloned->set_locked(is_locked());
    cloned->set_dirty(is_dirty());
    cloned->address_ = address_;
    cloned->bookmark_name_ = bookmark_name_;
    cloned->tooltip_ = tooltip_;
    cloned->screen_tip_ = screen_tip_;
    cloned->get_font() = get_font();
    return cloned;
}

void Hyperlink::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_field_start(*this);
    }
}

void Hyperlink::update() {
    // Subclasses can override for dynamic updates
}

}  // namespace cdocx
