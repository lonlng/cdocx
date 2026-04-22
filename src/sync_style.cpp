/**
 * @file sync_style.cpp
 * @brief Style serialization and sync
 */

#include "sync_common.h"

#include <cdocx/document.h>

#include <cstring>

namespace cdocx {

// ============================================================================
// Style Serialization Helpers
// ============================================================================

static const char* style_type_to_string(StyleType type) {
    switch (type) {
        case StyleType::Paragraph:
            return "paragraph";
        case StyleType::Character:
            return "character";
        case StyleType::Table:
            return "table";
        case StyleType::List:
            return "numbering";
        default:
            return "paragraph";
    }
}

static StyleType string_to_style_type(const char* str) {
    if (std::strcmp(str, "character") == 0) {
        return StyleType::Character;
    }
    if (std::strcmp(str, "table") == 0) {
        return StyleType::Table;
    }
    if (std::strcmp(str, "numbering") == 0) {
        return StyleType::List;
    }
    return StyleType::Paragraph;
}

static void serialize_style_paragraph_format_to_xml(pugi::xml_node pPr, const ParagraphFormat& format) {
    serialize_paragraph_format_children_to_xml(pPr, format);
}

void parse_font_from_xml(pugi::xml_node rPr, Font& font) {
    if (!rPr) {
        return;
    }

    // Reset defaults to "not set" so only explicitly present properties are serialized
    font.size = 0;
    font.name = "";
    font.name_far_east = "";
    font.color = Color::auto_color();

    if (rPr.child("w:b")) {
        font.bold = true;
    }
    if (rPr.child("w:i")) {
        font.italic = true;
    }
    if (rPr.child("w:strike")) {
        font.strikethrough = true;
    }

    if (auto u = rPr.child("w:u")) {
        font.underline = string_to_underline_type(u.attribute("w:val").value());
    }

    if (auto sz = rPr.child("w:sz")) {
        font.size = sz.attribute("w:val").as_int() / 2.0;
    }

    auto rFonts = rPr.child("w:rFonts");
    if (rFonts) {
        font.name = rFonts.attribute("w:ascii").value();
        if (font.name.empty()) {
            font.name = rFonts.attribute("w:hAnsi").value();
        }
        font.name_far_east = rFonts.attribute("w:eastAsia").value();
    }

    auto color = rPr.child("w:color");
    if (color) {
        font.color = Color::from_hex(color.attribute("w:val").value());
    }

    auto vAlign = rPr.child("w:vertAlign");
    if (vAlign) {
        font.script_type = string_to_script_type(vAlign.attribute("w:val").value());
    }

    parse_shading_from_xml(rPr.child("w:shd"), font.shading);
}

static void parse_style_paragraph_format_from_xml(pugi::xml_node pPr, ParagraphFormat& format) {
    if (!pPr) {
        return;
    }
    parse_paragraph_format_children_from_xml(pPr, format);
}

static void serialize_style_to_xml(pugi::xml_node styles_root, const Style& style) {
    pugi::xml_node style_xml;

    if (style.has_preserved_style_xml()) {
        // Start from a deep copy of the original style XML for maximum fidelity
        style_xml = styles_root.append_copy(style.get_preserved_style_xml());

        // Overlay DOM-managed attributes
        style_xml.attribute("w:type").set_value(style_type_to_string(style.get_type()));
        style_xml.attribute("w:styleId").set_value(style.get_style_id().c_str());

        if (style.get_is_default()) {
            if (!style_xml.attribute("w:default")) {
                style_xml.append_attribute("w:default").set_value("1");
            }
        } else {
            style_xml.remove_attribute("w:default");
        }

        if (!style.get_is_built_in()) {
            if (!style_xml.attribute("w:customStyle")) {
                style_xml.append_attribute("w:customStyle").set_value("1");
            }
        } else {
            style_xml.remove_attribute("w:customStyle");
        }

        // Update name
        auto name_node = style_xml.child("w:name");
        if (!style.get_name().empty()) {
            if (!name_node) {
                name_node = style_xml.prepend_child("w:name");
            }
            name_node.attribute("w:val").set_value(style.get_name().c_str());
        } else if (name_node) {
            style_xml.remove_child(name_node);
        }

        // Update basedOn
        auto basedOn_node = style_xml.child("w:basedOn");
        if (!style.get_base_style_name().empty()) {
            if (!basedOn_node) {
                basedOn_node = style_xml.prepend_child("w:basedOn");
            }
            basedOn_node.attribute("w:val").set_value(style.get_base_style_name().c_str());
        } else if (basedOn_node) {
            style_xml.remove_child(basedOn_node);
        }
    } else {
        // No preserved XML: build from scratch (programmatically created style)
        style_xml = styles_root.append_child("w:style");
        style_xml.append_attribute("w:type").set_value(style_type_to_string(style.get_type()));
        style_xml.append_attribute("w:styleId").set_value(style.get_style_id().c_str());

        if (style.get_is_default()) {
            style_xml.append_attribute("w:default").set_value("1");
        }
        if (!style.get_is_built_in()) {
            style_xml.append_attribute("w:customStyle").set_value("1");
        }

        if (!style.get_name().empty()) {
            auto name = style_xml.append_child("w:name");
            name.append_attribute("w:val").set_value(style.get_name().c_str());
        }

        if (!style.get_base_style_name().empty()) {
            auto basedOn = style_xml.append_child("w:basedOn");
            basedOn.append_attribute("w:val").set_value(style.get_base_style_name().c_str());
        }
    }

    // Determine if DOM has explicit font/paragraph formatting
    const Font& font = style.get_font();
    bool has_font_formatting = font.bold || font.italic || font.strikethrough ||
                               font.underline != UnderlineType::None || font.size > 0 ||
                               !font.name.empty() || font.color != Color::auto_color() ||
                               font.script_type != ScriptType::Normal;

    const ParagraphFormat& para_format = style.get_paragraph_format();
    bool has_para_format =
        para_format.alignment != ParagraphAlignment::Left || para_format.left_indent != 0 ||
        para_format.right_indent != 0 || para_format.first_line_indent != 0 ||
        para_format.space_before != 0 || para_format.space_after != 0 ||
        para_format.line_spacing != 1.15 || para_format.keep_with_next ||
        para_format.keep_together || para_format.page_break_before || !para_format.widow_control ||
        para_format.outline_level != OutlineLevel::BodyText;

    // Merge w:rPr: preserve unknown children, overlay managed ones
    auto rPr = style_xml.child("w:rPr");
    if (has_font_formatting) {
        if (!rPr) {
            rPr = style_xml.append_child("w:rPr");
        }
        // Check if original rPr had szCs before we remove anything
        bool original_had_sz_cs = rPr.child("w:szCs") != nullptr;

        // Remove managed children that we will re-serialize
        remove_managed_children(rPr,
                                {"w:b",
                                 "w:i",
                                 "w:strike",
                                 "w:u",
                                 "w:sz",
                                 "w:szCs",
                                 "w:rFonts",
                                 "w:color",
                                 "w:vertAlign",
                                 "w:spacing",
                                 "w:w",
                                 "w:shd"});
        // Serialize current DOM font formatting directly into the existing rPr
        serialize_font_to_rPr(rPr, font, original_had_sz_cs);
    }

    // Merge w:pPr: preserve unknown children, overlay managed ones
    auto pPr = style_xml.child("w:pPr");
    if (has_para_format) {
        if (!pPr) {
            pPr = style_xml.append_child("w:pPr");
        }
        // Remove managed children that we will re-serialize
        remove_managed_children(pPr, {"w:jc", "w:ind", "w:spacing", "w:shd", "w:dropCap"});
        serialize_style_paragraph_format_to_xml(pPr, para_format);
    }
}

static std::shared_ptr<Style> parse_style_from_xml(pugi::xml_node style_node, Document* doc) {
    if (!style_node) {
        return nullptr;
    }

    auto style =
        std::make_shared<Style>(doc, string_to_style_type(style_node.attribute("w:type").value()));
    style->set_style_id(style_node.attribute("w:styleId").value());
    style->set_is_default(style_node.attribute("w:default").as_int() != 0);
    style->set_is_built_in(style_node.attribute("w:customStyle").as_int() == 0);

    auto name = style_node.child("w:name");
    if (name) {
        style->set_name(name.attribute("w:val").value());
    } else {
        style->set_name(style->get_style_id());
    }

    auto basedOn = style_node.child("w:basedOn");
    if (basedOn) {
        style->set_base_style_name(basedOn.attribute("w:val").value());
    }

    auto rPr = style_node.child("w:rPr");
    if (rPr) {
        Font font;
        parse_font_from_xml(rPr, font);
        style->set_font(font);
    } else {
        // No explicit rPr: set font to empty so defaults aren't serialized
        Font empty_font;
        empty_font.size = 0;
        empty_font.name = "";
        empty_font.name_far_east = "";
        empty_font.color = Color::auto_color();
        style->set_font(empty_font);
    }

    auto pPr = style_node.child("w:pPr");
    if (pPr) {
        ParagraphFormat format;
        parse_style_paragraph_format_from_xml(pPr, format);
        style->set_paragraph_format(format);
    } else {
        // No explicit pPr: set paragraph format to defaults so they aren't serialized
        style->set_paragraph_format(ParagraphFormat());
    }

    // Preserve full original style XML for round-trip fidelity
    style->preserve_style_xml(style_node);

    return style;
}

// ============================================================================
// Style Sync Methods
// ============================================================================

void Document::sync_styles_to_physical() {
    pugi::xml_document* styles_doc = get_styles();
    if (!styles_doc) {
        styles_doc = &create_xml_part("word/styles.xml");
        add_content_type_override(
            "/word/styles.xml",
            "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml");
    }

    auto root = styles_doc->child("w:styles");
    if (!root) {
        styles_doc->reset();
        root = styles_doc->append_child("w:styles");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    }

    // Remove only w:style nodes, preserve docDefaults, latentStyles, etc.
    for (auto child = root.first_child(); child;) {
        auto next = child.next_sibling();
        if (std::strcmp(child.name(), "w:style") == 0) {
            root.remove_child(child);
        }
        child = next;
    }

    for (const auto& style : styles()) {
        serialize_style_to_xml(root, *style);
    }

    mark_modified("word/styles.xml");
}

void Document::sync_styles_from_physical() {
    pugi::xml_document* styles_doc = get_styles();
    if (!styles_doc) {
        // Create default Normal style if styles.xml is missing
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
        return;
    }

    if (styles_) {
        styles_->clear();
    }

    auto styles_root = styles_doc->child("w:styles");
    if (!styles_root) {
        return;
    }

    for (auto style_node = styles_root.child("w:style"); style_node;
         style_node = style_node.next_sibling("w:style")) {
        if (auto style = parse_style_from_xml(style_node, this)) {
            if (styles_) {
                styles_->add(style);
            }
        }
    }
}


}  // namespace cdocx
