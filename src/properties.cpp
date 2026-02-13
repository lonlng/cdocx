/**
 * @file properties.cpp
 * @brief Implementation of property structures
 * @since 0.4.0
 */

#include <cdocx/properties.h>
#include <cdocx/base.h>
#include <cdocx/format_context.h>
#include <cdocx/paragraph.h>

#include <cstring>

namespace cdocx {

// ============================================================================
// TextProperties Implementation
// ============================================================================

void TextProperties::applyTo(Run& run) const {
    if (!run.get_current_xml()) {
        return;
    }
    applyTo(run.get_current_xml());
}

void TextProperties::applyTo(pugi::xml_node run_node) const {
    if (!run_node) {
        return;
    }
    
    // Get or create rPr node
    pugi::xml_node rPr = run_node.child("w:rPr");
    if (!rPr) {
        rPr = run_node.prepend_child("w:rPr");
    }
    
    // Font settings
    if (font) {
        pugi::xml_node rFonts = rPr.child("w:rFonts");
        if (!rFonts) {
            rFonts = rPr.append_child("w:rFonts");
        }
        if (!font->ascii.empty()) {
            rFonts.append_attribute("w:ascii").set_value(font->ascii.c_str());
        }
        if (!font->eastAsia.empty()) {
            rFonts.append_attribute("w:eastAsia").set_value(font->eastAsia.c_str());
        }
        if (!font->hAnsi.empty()) {
            rFonts.append_attribute("w:hAnsi").set_value(font->hAnsi.c_str());
        }
        if (!font->cs.empty()) {
            rFonts.append_attribute("w:cs").set_value(font->cs.c_str());
        }
        // Font hint
        if (font->hint != Font::Hint::Default) {
            const char* hint_str = (font->hint == Font::Hint::EastAsia) ? "eastAsia" : "cs";
            rFonts.append_attribute("w:hint").set_value(hint_str);
        }
    }
    
    // Font style (bold/italic)
    if (fontStyle.bold) {
        rPr.append_child("w:b");
    }
    if (fontStyle.italic) {
        rPr.append_child("w:i");
    }
    
    // Font size
    if (fontSize > 0) {
        pugi::xml_node sz = rPr.append_child("w:sz");
        sz.append_attribute("w:val").set_value(fontSize);
        pugi::xml_node szCs = rPr.append_child("w:szCs");
        szCs.append_attribute("w:val").set_value(fontSize);
    }
    
    // Color
    if (!color.empty()) {
        pugi::xml_node color_node = rPr.append_child("w:color");
        color_node.append_attribute("w:val").set_value(color.c_str());
    }
    
    // Underline
    if (underline.style != UnderlineStyle::None) {
        pugi::xml_node u = rPr.append_child("w:u");
        const char* style_str = "single";
        switch (underline.style) {
            case UnderlineStyle::Words: style_str = "words"; break;
            case UnderlineStyle::Single: style_str = "single"; break;
            case UnderlineStyle::Double: style_str = "double"; break;
            case UnderlineStyle::Thick: style_str = "thick"; break;
            case UnderlineStyle::Dotted: style_str = "dotted"; break;
            case UnderlineStyle::DottedHeavy: style_str = "dottedHeavy"; break;
            case UnderlineStyle::Dash: style_str = "dash"; break;
            case UnderlineStyle::DashedHeavy: style_str = "dashedHeavy"; break;
            case UnderlineStyle::DashLong: style_str = "dashLong"; break;
            case UnderlineStyle::DashLongHeavy: style_str = "dashLongHeavy"; break;
            case UnderlineStyle::DotDash: style_str = "dotDash"; break;
            case UnderlineStyle::DashDotHeavy: style_str = "dashDotHeavy"; break;
            case UnderlineStyle::DotDotDash: style_str = "dotDotDash"; break;
            case UnderlineStyle::DashDotDotHeavy: style_str = "dashDotDotHeavy"; break;
            case UnderlineStyle::Wave: style_str = "wave"; break;
            case UnderlineStyle::WavyDouble: style_str = "wavyDouble"; break;
            case UnderlineStyle::WavyHeavy: style_str = "wavyHeavy"; break;
            default: style_str = "single"; break;
        }
        u.append_attribute("w:val").set_value(style_str);
        if (underline.color != "auto") {
            u.append_attribute("w:color").set_value(underline.color.c_str());
        }
    }
    
    // Strikethrough
    if (strike == StrikeStyle::Single) {
        rPr.append_child("w:strike");
    } else if (strike == StrikeStyle::Double) {
        pugi::xml_node strike_node = rPr.append_child("w:dstrike");
        strike_node.append_attribute("w:val").set_value("true");
    }
    
    // Vertical align
    if (vertAlign == VertAlign::Superscript) {
        pugi::xml_node vAlign = rPr.append_child("w:vertAlign");
        vAlign.append_attribute("w:val").set_value("superscript");
    } else if (vertAlign == VertAlign::Subscript) {
        pugi::xml_node vAlign = rPr.append_child("w:vertAlign");
        vAlign.append_attribute("w:val").set_value("subscript");
    }
    
    // Highlight
    if (highlight != Highlight::None) {
        static const char* highlight_names[] = {
            "none", "black", "white", "red", "green", "blue", "yellow", "cyan", "magenta",
            "darkRed", "darkGreen", "darkBlue", "darkYellow", "darkCyan", "darkMagenta",
            "darkGray", "lightGray"
        };
        int idx = static_cast<int>(highlight);
        if (idx >= 0 && idx < sizeof(highlight_names)/sizeof(highlight_names[0])) {
            pugi::xml_node highlight_node = rPr.append_child("w:highlight");
            highlight_node.append_attribute("w:val").set_value(highlight_names[idx]);
        }
    }
    
    // Scale
    if (scale != 100) {
        pugi::xml_node w_node = rPr.append_child("w:w");
        w_node.append_attribute("w:val").set_value(scale);
    }
    
    // Spacing
    if (spacing.type != SpacingType::Normal) {
        pugi::xml_node spacing_node = rPr.append_child("w:spacing");
        spacing_node.append_attribute("w:val").set_value(
            spacing.type == SpacingType::Expanded ? spacing.value : -spacing.value);
    }
    
    // Position
    if (position.type != PositionType::Normal) {
        pugi::xml_node pos_node = rPr.append_child("w:position");
        int val = (position.type == PositionType::Raised) ? position.value : -position.value;
        pos_node.append_attribute("w:val").set_value(val);
    }
}

TextProperties TextProperties::extractFrom(const Run& run) {
    return extractFrom(run.get_current_xml());
}

TextProperties TextProperties::extractFrom(pugi::xml_node run_node) {
    TextProperties props;
    if (!run_node) {
        return props;
    }
    
    pugi::xml_node rPr = run_node.child("w:rPr");
    if (!rPr) {
        return props;
    }
    
    // Extract font
    pugi::xml_node rFonts = rPr.child("w:rFonts");
    if (rFonts) {
        TextProperties::Font font;
        font.ascii = rFonts.attribute("w:ascii").value();
        font.eastAsia = rFonts.attribute("w:eastAsia").value();
        font.hAnsi = rFonts.attribute("w:hAnsi").value();
        font.cs = rFonts.attribute("w:cs").value();
        
        const char* hint = rFonts.attribute("w:hint").value();
        if (strcmp(hint, "eastAsia") == 0) {
            font.hint = Font::Hint::EastAsia;
        } else if (strcmp(hint, "cs") == 0) {
            font.hint = Font::Hint::ComplexScript;
        }
        props.font = font;
    }
    
    // Extract bold/italic
    props.fontStyle.bold = rPr.child("w:b") != nullptr;
    props.fontStyle.italic = rPr.child("w:i") != nullptr;
    
    // Extract font size
    pugi::xml_node sz = rPr.child("w:sz");
    if (sz) {
        props.fontSize = sz.attribute("w:val").as_int();
    }
    
    // Extract color
    pugi::xml_node color = rPr.child("w:color");
    if (color) {
        props.color = color.attribute("w:val").value();
    }
    
    // Extract underline
    pugi::xml_node u = rPr.child("w:u");
    if (u) {
        const char* val = u.attribute("w:val").value();
        props.underline.color = u.attribute("w:color").value();
        
        if (strcmp(val, "words") == 0) props.underline.style = UnderlineStyle::Words;
        else if (strcmp(val, "double") == 0) props.underline.style = UnderlineStyle::Double;
        else if (strcmp(val, "thick") == 0) props.underline.style = UnderlineStyle::Thick;
        else if (strcmp(val, "dotted") == 0) props.underline.style = UnderlineStyle::Dotted;
        else if (strcmp(val, "dottedHeavy") == 0) props.underline.style = UnderlineStyle::DottedHeavy;
        else if (strcmp(val, "dash") == 0) props.underline.style = UnderlineStyle::Dash;
        else if (strcmp(val, "dashedHeavy") == 0) props.underline.style = UnderlineStyle::DashedHeavy;
        else if (strcmp(val, "dashLong") == 0) props.underline.style = UnderlineStyle::DashLong;
        else if (strcmp(val, "dashLongHeavy") == 0) props.underline.style = UnderlineStyle::DashLongHeavy;
        else if (strcmp(val, "dotDash") == 0) props.underline.style = UnderlineStyle::DotDash;
        else if (strcmp(val, "dashDotHeavy") == 0) props.underline.style = UnderlineStyle::DashDotHeavy;
        else if (strcmp(val, "dotDotDash") == 0) props.underline.style = UnderlineStyle::DotDotDash;
        else if (strcmp(val, "dashDotDotHeavy") == 0) props.underline.style = UnderlineStyle::DashDotDotHeavy;
        else if (strcmp(val, "wave") == 0) props.underline.style = UnderlineStyle::Wave;
        else if (strcmp(val, "wavyDouble") == 0) props.underline.style = UnderlineStyle::WavyDouble;
        else if (strcmp(val, "wavyHeavy") == 0) props.underline.style = UnderlineStyle::WavyHeavy;
        else props.underline.style = UnderlineStyle::Single;
    }
    
    // Extract strikethrough
    if (rPr.child("w:strike")) {
        props.strike = StrikeStyle::Single;
    } else if (rPr.child("w:dstrike")) {
        props.strike = StrikeStyle::Double;
    }
    
    // Extract vertical align
    pugi::xml_node vAlign = rPr.child("w:vertAlign");
    if (vAlign) {
        const char* val = vAlign.attribute("w:val").value();
        if (strcmp(val, "superscript") == 0) {
            props.vertAlign = VertAlign::Superscript;
        } else if (strcmp(val, "subscript") == 0) {
            props.vertAlign = VertAlign::Subscript;
        }
    }
    
    // Extract highlight
    pugi::xml_node highlight = rPr.child("w:highlight");
    if (highlight) {
        const char* val = highlight.attribute("w:val").value();
        static struct { const char* name; Highlight value; } highlight_map[] = {
            {"black", Highlight::Black}, {"white", Highlight::White},
            {"red", Highlight::Red}, {"green", Highlight::Green},
            {"blue", Highlight::Blue}, {"yellow", Highlight::Yellow},
            {"cyan", Highlight::Cyan}, {"magenta", Highlight::Magenta},
            {"darkRed", Highlight::DarkRed}, {"darkGreen", Highlight::DarkGreen},
            {"darkBlue", Highlight::DarkBlue}, {"darkYellow", Highlight::DarkYellow},
            {"darkCyan", Highlight::DarkCyan}, {"darkMagenta", Highlight::DarkMagenta},
            {"darkGray", Highlight::DarkGray}, {"lightGray", Highlight::LightGray}
        };
        for (const auto& item : highlight_map) {
            if (strcmp(val, item.name) == 0) {
                props.highlight = item.value;
                break;
            }
        }
    }
    
    return props;
}

// ============================================================================
// ParagraphProperties Implementation
// ============================================================================

void ParagraphProperties::applyTo(Paragraph& para) const {
    applyTo(para.get_current_node());
}

void ParagraphProperties::applyTo(pugi::xml_node para_node) const {
    if (!para_node) {
        return;
    }
    
    // Get or create pPr node
    pugi::xml_node pPr = para_node.child("w:pPr");
    if (!pPr) {
        pPr = para_node.prepend_child("w:pPr");
    }
    
    // Style ID
    if (!styleId.empty()) {
        pugi::xml_node pStyle = pPr.child("w:pStyle");
        if (!pStyle) {
            pStyle = pPr.append_child("w:pStyle");
        }
        pStyle.append_attribute("w:val").set_value(styleId.c_str());
    }
    
    // Alignment
    if (align) {
        pugi::xml_node jc = pPr.append_child("w:jc");
        const char* align_str = "left";
        switch (*align) {
            case Alignment::Left: align_str = "left"; break;
            case Alignment::Centered: align_str = "center"; break;
            case Alignment::Right: align_str = "right"; break;
            case Alignment::Justified: align_str = "both"; break;
            case Alignment::Distributed: align_str = "distribute"; break;
        }
        jc.append_attribute("w:val").set_value(align_str);
    }
    
    // Outline level
    if (outlineLevel != OutlineLevel::BodyText) {
        int level = static_cast<int>(outlineLevel);
        pugi::xml_node outline = pPr.append_child("w:outlineLvl");
        outline.append_attribute("w:val").set_value(level);
    }
    
    // Indentation
    if (indent) {
        pugi::xml_node ind = pPr.append_child("w:ind");
        // Left
        if (indent->left.value != 0) {
            const char* attr = (indent->left.type == Indentation::Type::Character) 
                               ? "w:firstLineChars" : "w:left";
            ind.append_attribute(attr).set_value(indent->left.value);
        }
        // Right
        if (indent->right.value != 0) {
            ind.append_attribute("w:right").set_value(indent->right.value);
        }
        // Special
        if (indent->special.kind != Indentation::Special::Kind::None) {
            const char* attr = (indent->special.kind == Indentation::Special::Kind::FirstLine) 
                               ? "w:firstLine" : "w:hanging";
            ind.append_attribute(attr).set_value(indent->special.value);
        }
    }
    
    // Spacing
    if (spacing) {
        pugi::xml_node sp = pPr.append_child("w:spacing");
        // Before
        if (spacing->before.type != Spacing::Type::Auto || spacing->before.value != 0) {
            sp.append_attribute("w:before").set_value(spacing->before.value);
        }
        // After
        if (spacing->after.type != Spacing::Type::Auto || spacing->after.value != 0) {
            sp.append_attribute("w:after").set_value(spacing->after.value);
        }
        // Line spacing
        if (spacing->lineSpacing.type == Spacing::LineSpacingType::AtLeast) {
            sp.append_attribute("w:lineRule").set_value("atLeast");
        } else if (spacing->lineSpacing.type == Spacing::LineSpacingType::Exactly) {
            sp.append_attribute("w:lineRule").set_value("exact");
        }
        sp.append_attribute("w:line").set_value(spacing->lineSpacing.value);
    }
    
    // Page break control
    if (keepNext) {
        pPr.append_child("w:keepNext");
    }
    if (keepLines) {
        pPr.append_child("w:keepLines");
    }
    if (pageBreakBefore) {
        pPr.append_child("w:pageBreakBefore");
    }
    if (pageBreakAfter) {
        pugi::xml_node pb = pPr.append_child("w:pageBreakAfter");
        pb.append_attribute("w:val").set_value("true");
    }
    
    // Borders
    if (borders) {
        pugi::xml_node pBdr = pPr.append_child("w:pBdr");
        auto addBorder = [&pBdr](const char* name, const std::optional<Border>& border) {
            if (border) {
                pugi::xml_node b = pBdr.append_child(name);
                const char* style_str = "single";
                switch (border->style) {
                    case Border::Style::None: style_str = "nil"; break;
                    case Border::Style::Single: style_str = "single"; break;
                    case Border::Style::Double: style_str = "double"; break;
                    case Border::Style::Thick: style_str = "thick"; break;
                    case Border::Style::Dotted: style_str = "dotted"; break;
                    case Border::Style::Dash: style_str = "dash"; break;
                    case Border::Style::DotDash: style_str = "dotDash"; break;
                    case Border::Style::Wave: style_str = "wave"; break;
                    default: style_str = "single"; break;
                }
                b.append_attribute("w:val").set_value(style_str);
                b.append_attribute("w:sz").set_value(border->size);
                b.append_attribute("w:color").set_value(border->color.c_str());
                b.append_attribute("w:space").set_value(border->space);
            }
        };
        addBorder("w:top", borders->top);
        addBorder("w:left", borders->left);
        addBorder("w:bottom", borders->bottom);
        addBorder("w:right", borders->right);
    }
}

ParagraphProperties ParagraphProperties::extractFrom(const Paragraph& para) {
    return extractFrom(para.get_current_node());
}

ParagraphProperties ParagraphProperties::extractFrom(pugi::xml_node para_node) {
    ParagraphProperties props;
    if (!para_node) {
        return props;
    }
    
    pugi::xml_node pPr = para_node.child("w:pPr");
    if (!pPr) {
        return props;
    }
    
    // Extract style ID
    pugi::xml_node pStyle = pPr.child("w:pStyle");
    if (pStyle) {
        props.styleId = pStyle.attribute("w:val").value();
    }
    
    // Extract alignment
    pugi::xml_node jc = pPr.child("w:jc");
    if (jc) {
        const char* val = jc.attribute("w:val").value();
        if (strcmp(val, "center") == 0) props.align = Alignment::Centered;
        else if (strcmp(val, "right") == 0) props.align = Alignment::Right;
        else if (strcmp(val, "both") == 0) props.align = Alignment::Justified;
        else if (strcmp(val, "distribute") == 0) props.align = Alignment::Distributed;
        else props.align = Alignment::Left;
    }
    
    // Extract outline level
    pugi::xml_node outline = pPr.child("w:outlineLvl");
    if (outline) {
        int level = outline.attribute("w:val").as_int();
        if (level >= 0 && level <= 8) {
            props.outlineLevel = static_cast<OutlineLevel>(level);
        }
    }
    
    return props;
}

// ============================================================================
// TableProperties Implementation
// ============================================================================

void TableProperties::applyTo(Table& table) const {
    // TODO: Get table XML node and apply
    (void)table;
}

void TableProperties::applyTo(pugi::xml_node tbl_node) const {
    if (!tbl_node) {
        return;
    }
    
    pugi::xml_node tblPr = tbl_node.child("w:tblPr");
    if (!tblPr) {
        tblPr = tbl_node.prepend_child("w:tblPr");
    }
    
    // Table width
    pugi::xml_node tblW = tblPr.child("w:tblW");
    if (!tblW) {
        tblW = tblPr.append_child("w:tblW");
    }
    const char* type_str = "auto";
    if (width.type == WidthType::Percent) type_str = "pct";
    else if (width.type == WidthType::Absolute) type_str = "dxa";
    tblW.append_attribute("w:type").set_value(type_str);
    tblW.append_attribute("w:w").set_value(width.value);
    
    // TODO: Apply alignment, borders, cell margins
}

// ============================================================================
// SectionProperties Implementation
// ============================================================================

void SectionProperties::applyTo(pugi::xml_node sectPr_node) const {
    if (!sectPr_node) {
        return;
    }
    
    // Page size
    pugi::xml_node pgSz = sectPr_node.child("w:pgSz");
    if (!pgSz) {
        pgSz = sectPr_node.append_child("w:pgSz");
    }
    pgSz.append_attribute("w:w").set_value(pageSize.width);
    pgSz.append_attribute("w:h").set_value(pageSize.height);
    if (orientation == Orientation::Landscape) {
        pgSz.append_attribute("w:orient").set_value("landscape");
    }
    
    // Page margins
    pugi::xml_node pgMar = sectPr_node.child("w:pgMar");
    if (!pgMar) {
        pgMar = sectPr_node.append_child("w:pgMar");
    }
    pgMar.append_attribute("w:top").set_value(pageMargins.top);
    pgMar.append_attribute("w:right").set_value(pageMargins.right);
    pgMar.append_attribute("w:bottom").set_value(pageMargins.bottom);
    pgMar.append_attribute("w:left").set_value(pageMargins.left);
    pgMar.append_attribute("w:header").set_value(pageMargins.header);
    pgMar.append_attribute("w:footer").set_value(pageMargins.footer);
    
    // Columns
    pugi::xml_node cols = sectPr_node.child("w:cols");
    if (!cols) {
        cols = sectPr_node.append_child("w:cols");
    }
    cols.append_attribute("w:num").set_value(columns.count);
    cols.append_attribute("w:space").set_value(columns.space);
    if (columns.separator) {
        cols.append_attribute("w:sep").set_value("true");
    }
}

} // namespace cdocx
