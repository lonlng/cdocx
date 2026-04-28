/**
 * @file properties.cpp
 * @brief Implementation of property structures
 * @since 0.4.0
 */

#include "sync_common.h"

#include <cdocx/base.h>
#include <cdocx/convert_util.h>
#include <cdocx/format_context.h>
#include <cdocx/paragraph.h>
#include <cdocx/properties.h>
#include <cdocx/table.h>

#include <algorithm>
#include <cstring>

namespace cdocx {

namespace {

// ============================================================================
// Lookup Tables for TextProperties enum↔string mapping
// ============================================================================

struct UnderlineStyleMapping {
    TextProperties::UnderlineStyle style;
    const char* xml_value;
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

struct HighlightMapping {
    TextProperties::Highlight value;
    const char* name;
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

// ---------------------------------------------------------------------------
// Border Style
// ---------------------------------------------------------------------------

struct BorderStyleMapping {
    ParagraphProperties::Border::Style style;
    const char* xml_value;
};

static const BorderStyleMapping kBorderStyleMappings[] = {
    {ParagraphProperties::Border::Style::None, "nil"},
    {ParagraphProperties::Border::Style::Single, "single"},
    {ParagraphProperties::Border::Style::Double, "double"},
    {ParagraphProperties::Border::Style::Thick, "thick"},
    {ParagraphProperties::Border::Style::Dotted, "dotted"},
    {ParagraphProperties::Border::Style::Dash, "dash"},
    {ParagraphProperties::Border::Style::DotDash, "dotDash"},
    {ParagraphProperties::Border::Style::Wave, "wave"},
};

static const char* border_style_to_string(ParagraphProperties::Border::Style style) {
    for (const auto& mapping : kBorderStyleMappings) {
        if (mapping.style == style) {
            return mapping.xml_value;
        }
    }
    return "single";
}

}  // namespace

// ============================================================================
// TextProperties Implementation
// ============================================================================

void TextProperties::apply_to(Run& run) const {
    if (!run.get_current_xml()) {
        return;
    }
    apply_to(run.get_current_xml());
}

void TextProperties::apply_to(pugi::xml_node run_node) const {
    if (!run_node) {
        return;
    }

    // Get or create r_pr node
    pugi::xml_node r_pr = run_node.child("w:rPr");
    if (!r_pr) {
        r_pr = run_node.prepend_child("w:rPr");
    }

    // Font settings
    if (font) {
        pugi::xml_node r_fonts = r_pr.child("w:rFonts");
        if (!r_fonts) {
            r_fonts = r_pr.append_child("w:rFonts");
        }
        if (!font->ascii.empty()) {
            r_fonts.append_attribute("w:ascii").set_value(font->ascii.c_str());
        }
        if (!font->east_asia.empty()) {
            r_fonts.append_attribute("w:eastAsia").set_value(font->east_asia.c_str());
        }
        if (!font->h_ansi.empty()) {
            r_fonts.append_attribute("w:hAnsi").set_value(font->h_ansi.c_str());
        }
        if (!font->cs.empty()) {
            r_fonts.append_attribute("w:cs").set_value(font->cs.c_str());
        }
        // Font hint
        if (font->hint != Font::Hint::Default) {
            const char* hint_str = (font->hint == Font::Hint::EastAsia) ? "eastAsia" : "cs";
            r_fonts.append_attribute("w:hint").set_value(hint_str);
        }
    }

    // Font style (bold/italic)
    if (font_style.bold) {
        r_pr.append_child("w:b");
    }
    if (font_style.italic) {
        r_pr.append_child("w:i");
    }

    // Font size
    if (font_size > 0) {
        pugi::xml_node sz = r_pr.append_child("w:sz");
        sz.append_attribute("w:val").set_value(font_size);
        pugi::xml_node sz_cs = r_pr.append_child("w:szCs");
        sz_cs.append_attribute("w:val").set_value(font_size);
    }

    // Color
    if (!color.empty()) {
        pugi::xml_node color_node = r_pr.append_child("w:color");
        color_node.append_attribute("w:val").set_value(color.c_str());
    }

    // Underline
    if (underline.style != UnderlineStyle::None) {
        pugi::xml_node u = r_pr.append_child("w:u");
        const char* style_str = "single";
        for (const auto& m : kUnderlineStyleMappings) {
            if (m.style == underline.style) {
                style_str = m.xml_value;
                break;
            }
        }
        u.append_attribute("w:val").set_value(style_str);
        if (underline.color != "auto") {
            u.append_attribute("w:color").set_value(underline.color.c_str());
        }
    }

    // Strikethrough
    if (strike == StrikeStyle::Single) {
        r_pr.append_child("w:strike");
    } else if (strike == StrikeStyle::Double) {
        pugi::xml_node strike_node = r_pr.append_child("w:dstrike");
        strike_node.append_attribute("w:val").set_value("true");
    }

    // Vertical align
    if (vert_align == VertAlign::Superscript) {
        pugi::xml_node v_align = r_pr.append_child("w:vertAlign");
        v_align.append_attribute("w:val").set_value("superscript");
    } else if (vert_align == VertAlign::Subscript) {
        pugi::xml_node v_align = r_pr.append_child("w:vertAlign");
        v_align.append_attribute("w:val").set_value("subscript");
    }

    // Highlight
    if (highlight != Highlight::None) {
        for (const auto& m : kHighlightMappings) {
            if (m.value == highlight) {
                pugi::xml_node highlight_node = r_pr.append_child("w:highlight");
                highlight_node.append_attribute("w:val").set_value(m.name);
                break;
            }
        }
    }

    // Scale
    if (scale != 100) {
        pugi::xml_node w_node = r_pr.append_child("w:w");
        w_node.append_attribute("w:val").set_value(scale);
    }

    // Spacing
    if (spacing.type != SpacingType::Normal) {
        pugi::xml_node spacing_node = r_pr.append_child("w:spacing");
        spacing_node.append_attribute("w:val").set_value(
            spacing.type == SpacingType::Expanded ? spacing.value : -spacing.value);
    }

    // Position
    if (position.type != PositionType::Normal) {
        pugi::xml_node pos_node = r_pr.append_child("w:position");
        const int val = (position.type == PositionType::Raised) ? position.value : -position.value;
        pos_node.append_attribute("w:val").set_value(val);
    }
}

TextProperties TextProperties::extract_from(const Run& run) {
    return extract_from(run.get_current_xml());
}

TextProperties TextProperties::extract_from(pugi::xml_node run_node) {
    TextProperties props;
    if (!run_node) {
        return props;
    }

    const pugi::xml_node r_pr = run_node.child("w:rPr");
    if (!r_pr) {
        return props;
    }

    // Extract font
    const pugi::xml_node r_fonts = r_pr.child("w:rFonts");
    if (r_fonts) {
        TextProperties::Font font;
        font.ascii = r_fonts.attribute("w:ascii").value();
        font.east_asia = r_fonts.attribute("w:eastAsia").value();
        font.h_ansi = r_fonts.attribute("w:hAnsi").value();
        font.cs = r_fonts.attribute("w:cs").value();

        const char* hint = r_fonts.attribute("w:hint").value();
        if (strcmp(hint, "eastAsia") == 0) {
            font.hint = Font::Hint::EastAsia;
        } else if (strcmp(hint, "cs") == 0) {
            font.hint = Font::Hint::ComplexScript;
        }
        props.font = font;
    }

    // Extract bold/italic
    props.font_style.bold = r_pr.child("w:b") != nullptr;
    props.font_style.italic = r_pr.child("w:i") != nullptr;

    // Extract font size
    const pugi::xml_node sz = r_pr.child("w:sz");
    if (sz) {
        props.font_size = sz.attribute("w:val").as_int();
    }

    // Extract color
    const pugi::xml_node color = r_pr.child("w:color");
    if (color) {
        props.color = color.attribute("w:val").value();
    }

    // Extract underline
    const pugi::xml_node u = r_pr.child("w:u");
    if (u) {
        const char* val = u.attribute("w:val").value();
        props.underline.color = u.attribute("w:color").value();

        props.underline.style = UnderlineStyle::Single;
        for (const auto& m : kUnderlineStyleMappings) {
            if (strcmp(val, m.xml_value) == 0) {
                props.underline.style = m.style;
                break;
            }
        }
    }

    // Extract strikethrough
    if (r_pr.child("w:strike")) {
        props.strike = StrikeStyle::Single;
    } else if (r_pr.child("w:dstrike")) {
        props.strike = StrikeStyle::Double;
    }

    // Extract vertical align
    const pugi::xml_node v_align = r_pr.child("w:vertAlign");
    if (v_align) {
        const char* val = v_align.attribute("w:val").value();
        if (strcmp(val, "superscript") == 0) {
            props.vert_align = VertAlign::Superscript;
        } else if (strcmp(val, "subscript") == 0) {
            props.vert_align = VertAlign::Subscript;
        }
    }

    // Extract highlight
    const pugi::xml_node highlight = r_pr.child("w:highlight");
    if (highlight) {
        const char* val = highlight.attribute("w:val").value();
        for (const auto& m : kHighlightMappings) {
            if (strcmp(val, m.name) == 0) {
                props.highlight = m.value;
                break;
            }
        }
    }

    return props;
}

// ============================================================================
// ParagraphProperties Implementation
// ============================================================================

void ParagraphProperties::apply_to(Paragraph& para) const {
    apply_to(para.get_current_node());
}

void ParagraphProperties::apply_to(pugi::xml_node para_node) const {
    if (!para_node) {
        return;
    }

    // Get or create p_pr node
    pugi::xml_node p_pr = para_node.child("w:pPr");
    if (!p_pr) {
        p_pr = para_node.prepend_child("w:pPr");
    }

    // Style ID
    if (!style_id.empty()) {
        pugi::xml_node p_style = p_pr.child("w:pStyle");
        if (!p_style) {
            p_style = p_pr.append_child("w:pStyle");
        }
        p_style.append_attribute("w:val").set_value(style_id.c_str());
    }

    // Alignment
    if (align) {
        pugi::xml_node jc = p_pr.append_child("w:jc");
        jc.append_attribute("w:val").set_value(pp_alignment_to_string(*align));
    }

    // Outline level
    if (outline_level != OutlineLevel::BodyText) {
        const int level = static_cast<int>(outline_level);
        pugi::xml_node outline = p_pr.append_child("w:outlineLvl");
        outline.append_attribute("w:val").set_value(level);
    }

    // Indentation
    if (indent) {
        pugi::xml_node ind = p_pr.append_child("w:ind");
        // Left
        if (indent->left.value != 0) {
            const char* attr =
                (indent->left.type == Indentation::Type::Character) ? "w:firstLineChars" : "w:left";
            ind.append_attribute(attr).set_value(indent->left.value);
        }
        // Right
        if (indent->right.value != 0) {
            ind.append_attribute("w:right").set_value(indent->right.value);
        }
        // Special
        if (indent->special.kind != Indentation::Special::Kind::None) {
            const char* attr = (indent->special.kind == Indentation::Special::Kind::FirstLine)
                                   ? "w:firstLine"
                                   : "w:hanging";
            ind.append_attribute(attr).set_value(indent->special.value);
        }
    }

    // Spacing
    if (spacing) {
        pugi::xml_node sp = p_pr.append_child("w:spacing");
        // Before
        if (spacing->before.type != Spacing::Type::Auto || spacing->before.value != 0) {
            sp.append_attribute("w:before").set_value(spacing->before.value);
        }
        // After
        if (spacing->after.type != Spacing::Type::Auto || spacing->after.value != 0) {
            sp.append_attribute("w:after").set_value(spacing->after.value);
        }
        // Line spacing
        if (spacing->line_spacing.type == Spacing::LineSpacingType::AtLeast) {
            sp.append_attribute("w:lineRule").set_value("atLeast");
        } else if (spacing->line_spacing.type == Spacing::LineSpacingType::Exactly) {
            sp.append_attribute("w:lineRule").set_value("exact");
        }
        sp.append_attribute("w:line").set_value(spacing->line_spacing.value);
    }

    // Page break control
    if (keep_next) {
        p_pr.append_child("w:keep_next");
    }
    if (keep_lines) {
        p_pr.append_child("w:keep_lines");
    }
    if (page_break_before) {
        p_pr.append_child("w:page_break_before");
    }
    if (page_break_after) {
        pugi::xml_node pb = p_pr.append_child("w:page_break_after");
        pb.append_attribute("w:val").set_value("true");
    }

    // Borders
    if (borders) {
        pugi::xml_node p_bdr = p_pr.append_child("w:pBdr");
        auto add_border = [&p_bdr](const char* name, const std::optional<Border>& border) {
            if (border) {
                pugi::xml_node b = p_bdr.append_child(name);
                b.append_attribute("w:val").set_value(border_style_to_string(border->style));
                b.append_attribute("w:sz").set_value(border->size);
                b.append_attribute("w:color").set_value(border->color.c_str());
                b.append_attribute("w:space").set_value(border->space);
            }
        };
        add_border("w:top", borders->top);
        add_border("w:left", borders->left);
        add_border("w:bottom", borders->bottom);
        add_border("w:right", borders->right);
    }

    // Tab stops
    if (tab_stops) {
        tab_stops->apply_to(para_node);
    }
}

ParagraphProperties ParagraphProperties::extract_from(const Paragraph& para) {
    return extract_from(para.get_current_node());
}

ParagraphProperties ParagraphProperties::extract_from(pugi::xml_node para_node) {
    ParagraphProperties props;
    if (!para_node) {
        return props;
    }

    const pugi::xml_node p_pr = para_node.child("w:pPr");
    if (!p_pr) {
        return props;
    }

    // Extract style ID
    const pugi::xml_node p_style = p_pr.child("w:pStyle");
    if (p_style) {
        props.style_id = p_style.attribute("w:val").value();
    }

    // Extract alignment
    const pugi::xml_node jc = p_pr.child("w:jc");
    if (jc) {
        props.align = string_to_pp_alignment(jc.attribute("w:val").value());
    }

    // Extract outline level
    const pugi::xml_node outline = p_pr.child("w:outlineLvl");
    if (outline) {
        const int level = outline.attribute("w:val").as_int();
        if (level >= 0 && level <= 8) {
            props.outline_level = static_cast<OutlineLevel>(level);
        }
    }

    // Extract tab stops
    props.tab_stops = TabStopCollection::extract_from(para_node);

    return props;
}

// ============================================================================
// TabStopCollection Implementation
// ============================================================================

namespace {

struct TabAlignmentMapping {
    TabAlignment alignment{};
    const char* xml_value{};
};

static const TabAlignmentMapping kTabAlignmentMappings[] = {
    {TabAlignment::Center, "center"},
    {TabAlignment::Right, "right"},
    {TabAlignment::Decimal, "decimal"},
    {TabAlignment::Bar, "bar"},
    {TabAlignment::List, "list"},
    {TabAlignment::Clear, "clear"},
};

const char* tab_alignment_to_string(TabAlignment alignment) {
    for (const auto& m : kTabAlignmentMappings) {
        if (m.alignment == alignment) {
            return m.xml_value;
        }
    }
    return "left";
}

TabAlignment string_to_tab_alignment(const char* str) {
    for (const auto& m : kTabAlignmentMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.alignment;
        }
    }
    return TabAlignment::Left;
}

struct TabLeaderMapping {
    TabLeader leader{};
    const char* xml_value{};
};

static const TabLeaderMapping kTabLeaderMappings[] = {
    {TabLeader::Dots, "dot"},
    {TabLeader::Dashes, "hyphen"},
    {TabLeader::Line, "underscore"},
    {TabLeader::Heavy, "heavy"},
    {TabLeader::MiddleDot, "middleDot"},
};

const char* tab_leader_to_string(TabLeader leader) {
    for (const auto& m : kTabLeaderMappings) {
        if (m.leader == leader) {
            return m.xml_value;
        }
    }
    return "none";
}

TabLeader string_to_tab_leader(const char* str) {
    for (const auto& m : kTabLeaderMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.leader;
        }
    }
    return TabLeader::None;
}

}  // anonymous namespace

void TabStopCollection::add(const TabStop& tab_stop) {
    // Replace existing tab stop at the same position
    for (auto& ts : tab_stops_) {
        if (ts.position == tab_stop.position) {
            ts = tab_stop;
            return;
        }
    }
    tab_stops_.push_back(tab_stop);
}

void TabStopCollection::add(double position, TabAlignment alignment, TabLeader leader) {
    add(TabStop(position, alignment, leader));
}

void TabStopCollection::remove(double position) {
    tab_stops_.erase(
        std::remove_if(tab_stops_.begin(),
                       tab_stops_.end(),
                       [position](const TabStop& ts) { return ts.position == position; }),
        tab_stops_.end());
}

void TabStopCollection::remove_at(size_t index) {
    if (index < tab_stops_.size()) {
        tab_stops_.erase(tab_stops_.begin() + static_cast<std::ptrdiff_t>(index));
    }
}

void TabStopCollection::clear() {
    tab_stops_.clear();
}

const TabStop* TabStopCollection::get(double position) const {
    for (const auto& ts : tab_stops_) {
        if (ts.position == position) {
            return &ts;
        }
    }
    return nullptr;
}

bool TabStopCollection::contains(double position) const {
    return get(position) != nullptr;
}

void TabStopCollection::apply_to(pugi::xml_node para_node) const {
    if (!para_node || tab_stops_.empty()) {
        return;
    }

    pugi::xml_node p_pr = para_node.child("w:pPr");
    if (!p_pr) {
        p_pr = para_node.prepend_child("w:pPr");
    }

    // Remove existing tabs element
    p_pr.remove_child("w:tabs");

    pugi::xml_node tabs = p_pr.append_child("w:tabs");
    for (const auto& ts : tab_stops_) {
        pugi::xml_node tab = tabs.append_child("w:tab");
        tab.append_attribute("w:val").set_value(tab_alignment_to_string(ts.alignment));
        tab.append_attribute("w:pos").set_value(
            ConvertUtil::point_to_twips(ts.position));
        if (ts.leader != TabLeader::None) {
            tab.append_attribute("w:leader").set_value(tab_leader_to_string(ts.leader));
        }
    }
}

TabStopCollection TabStopCollection::extract_from(pugi::xml_node para_node) {
    TabStopCollection collection;
    if (!para_node) {
        return collection;
    }

    const pugi::xml_node p_pr = para_node.child("w:pPr");
    if (!p_pr) {
        return collection;
    }

    const pugi::xml_node tabs = p_pr.child("w:tabs");
    if (!tabs) {
        return collection;
    }

    for (pugi::xml_node tab = tabs.child("w:tab"); tab; tab = tab.next_sibling("w:tab")) {
        TabStop ts;
        ts.alignment = string_to_tab_alignment(tab.attribute("w:val").value());
        ts.position = ConvertUtil::twips_to_point(tab.attribute("w:pos").as_int());

        const pugi::xml_attribute leader_attr = tab.attribute("w:leader");
        if (leader_attr) {
            ts.leader = string_to_tab_leader(leader_attr.value());
        }

        collection.add(ts);
    }

    return collection;
}

// ============================================================================
// TableProperties Implementation
// ============================================================================

void TableProperties::apply_to(Table& table) const {
    const pugi::xml_node tbl_xml = table.get_current_xml();
    if (tbl_xml) {
        apply_to(tbl_xml);
    }
}

void TableProperties::apply_to(pugi::xml_node tbl_node) const {
    if (!tbl_node) {
        return;
    }

    pugi::xml_node tbl_pr = tbl_node.child("w:tblPr");
    if (!tbl_pr) {
        tbl_pr = tbl_node.prepend_child("w:tblPr");
    }

    auto ensure_attr = [](pugi::xml_node node, const char* name) {
        pugi::xml_attribute attr = node.attribute(name);
        if (!attr) {
            attr = node.append_attribute(name);
        }
        return attr;
    };

    // Table width
    pugi::xml_node tbl_w = tbl_pr.child("w:tblW");
    if (!tbl_w) {
        tbl_w = tbl_pr.append_child("w:tblW");
    }
    const char* typestr = "auto";
    if (width.type == WidthType::Percent) {
        typestr = "pct";
    } else if (width.type == WidthType::Absolute) {
        typestr = "dxa";
    }
    ensure_attr(tbl_w, "w:type").set_value(typestr);
    ensure_attr(tbl_w, "w:w").set_value(width.value);

    // Table alignment
    if (alignment != ParagraphProperties::Alignment::Left) {
        pugi::xml_node jc = tbl_pr.child("w:jc");
        if (!jc) {
            jc = tbl_pr.append_child("w:jc");
        }
        const char* align_val = "left";
        switch (alignment) {
            case ParagraphProperties::Alignment::Centered:
                align_val = "center";
                break;
            case ParagraphProperties::Alignment::Right:
                align_val = "right";
                break;
            default:
                break;
        }
        ensure_attr(jc, "w:val").set_value(align_val);
    } else {
        tbl_pr.remove_child("w:jc");
    }

    // Table borders
    if (borders.top || borders.left || borders.bottom || borders.right) {
        pugi::xml_node tbl_borders = tbl_pr.child("w:tblBorders");
        if (!tbl_borders) {
            tbl_borders = tbl_pr.append_child("w:tblBorders");
        }

        auto apply_border = [&tbl_borders, &ensure_attr](
                                const char* name,
                                const std::optional<ParagraphProperties::Border>& border) {
            if (!border) {
                tbl_borders.remove_child(name);
                return;
            }
            pugi::xml_node b = tbl_borders.child(name);
            if (!b) {
                b = tbl_borders.append_child(name);
            }
            ensure_attr(b, "w:val").set_value(border_style_to_string(border->style));
            ensure_attr(b, "w:sz").set_value(border->size);
            ensure_attr(b, "w:color").set_value(border->color.c_str());
            ensure_attr(b, "w:space").set_value(border->space);
        };

        apply_border("w:top", borders.top);
        apply_border("w:left", borders.left);
        apply_border("w:bottom", borders.bottom);
        apply_border("w:right", borders.right);
    } else {
        tbl_pr.remove_child("w:tblBorders");
    }

    // Cell margins
    if (cell_margin.top > 0 || cell_margin.left > 0 || cell_margin.bottom > 0 ||
        cell_margin.right > 0) {
        pugi::xml_node tbl_cell_mar = tbl_pr.child("w:tblCellMar");
        if (!tbl_cell_mar) {
            tbl_cell_mar = tbl_pr.append_child("w:tblCellMar");
        }

        auto apply_margin = [&tbl_cell_mar, &ensure_attr](const char* name, int value) {
            if (value <= 0) {
                tbl_cell_mar.remove_child(name);
                return;
            }
            pugi::xml_node m = tbl_cell_mar.child(name);
            if (!m) {
                m = tbl_cell_mar.append_child(name);
            }
            ensure_attr(m, "w:w").set_value(value);
            ensure_attr(m, "w:type").set_value("dxa");
        };

        apply_margin("w:top", cell_margin.top);
        apply_margin("w:left", cell_margin.left);
        apply_margin("w:bottom", cell_margin.bottom);
        apply_margin("w:right", cell_margin.right);
    } else {
        tbl_pr.remove_child("w:tblCellMar");
    }
}

// ============================================================================
// SectionProperties Implementation
// ============================================================================

void SectionProperties::apply_to(pugi::xml_node sect_pr_node) const {
    if (!sect_pr_node) {
        return;
    }

    // Page size
    pugi::xml_node pg_sz = sect_pr_node.child("w:pgSz");
    if (!pg_sz) {
        pg_sz = sect_pr_node.append_child("w:pgSz");
    }
    pg_sz.append_attribute("w:w").set_value(page_size.width);
    pg_sz.append_attribute("w:h").set_value(page_size.height);
    if (orientation == Orientation::Landscape) {
        pg_sz.append_attribute("w:orient").set_value("landscape");
    }

    // Page margins
    pugi::xml_node pg_mar = sect_pr_node.child("w:pgMar");
    if (!pg_mar) {
        pg_mar = sect_pr_node.append_child("w:pgMar");
    }
    pg_mar.append_attribute("w:top").set_value(page_margins.top);
    pg_mar.append_attribute("w:right").set_value(page_margins.right);
    pg_mar.append_attribute("w:bottom").set_value(page_margins.bottom);
    pg_mar.append_attribute("w:left").set_value(page_margins.left);
    pg_mar.append_attribute("w:header").set_value(page_margins.header);
    pg_mar.append_attribute("w:footer").set_value(page_margins.footer);

    // Columns
    pugi::xml_node cols = sect_pr_node.child("w:cols");
    if (!cols) {
        cols = sect_pr_node.append_child("w:cols");
    }
    cols.append_attribute("w:num").set_value(columns.count);
    cols.append_attribute("w:space").set_value(columns.space);
    if (columns.separator) {
        cols.append_attribute("w:sep").set_value("true");
    }
}

}  // namespace cdocx
