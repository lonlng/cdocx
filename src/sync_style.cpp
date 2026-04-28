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

struct StyleTypeMapping {
    StyleType type{};
    const char* xml_value{};
};

static const StyleTypeMapping kStyleTypeMappings[] = {
    {StyleType::Character, "character"},
    {StyleType::Table, "table"},
    {StyleType::List, "numbering"},
};

static const char* style_type_to_string(StyleType type) {
    for (const auto& m : kStyleTypeMappings) {
        if (m.type == type) {
            return m.xml_value;
        }
    }
    return "paragraph";
}

static StyleType string_to_style_type(const char* str) {
    for (const auto& m : kStyleTypeMappings) {
        if (std::strcmp(m.xml_value, str) == 0) {
            return m.type;
        }
    }
    return StyleType::Paragraph;
}

static void serialize_style_paragraph_format_to_xml(pugi::xml_node p_pr, const ParagraphFormat& format) {
    serialize_paragraph_format_children_to_xml(p_pr, format);
}

void parse_font_from_xml(pugi::xml_node r_pr, Font& font) {
    if (!r_pr) {
        return;
    }

    // Reset defaults to "not set" so only explicitly present properties are serialized
    font.size = 0;
    font.name = "";
    font.name_far_east = "";
    font.color = Color::auto_color();

    struct FontBoolFlagMapping {
        const char* child_name;
        bool Font::*flag;
    };
    static const FontBoolFlagMapping kFontBoolFlagMappings[] = {
        {"w:b", &Font::bold},
        {"w:i", &Font::italic},
        {"w:strike", &Font::strikethrough},
    };
    for (const auto& mapping : kFontBoolFlagMappings) {
        if (r_pr.child(mapping.child_name)) {
            font.*mapping.flag = true;
        }
    }

    if (auto u = r_pr.child("w:u")) {
        font.underline = string_to_underline_type(u.attribute("w:val").value());
    }

    if (auto sz = r_pr.child("w:sz")) {
        font.size = sz.attribute("w:val").as_int() / 2.0;
    }

    auto r_fonts = r_pr.child("w:rFonts");
    if (r_fonts) {
        font.name = r_fonts.attribute("w:ascii").value();
        if (font.name.empty()) {
            font.name = r_fonts.attribute("w:hAnsi").value();
        }
        font.name_far_east = r_fonts.attribute("w:eastAsia").value();
    }

    auto color = r_pr.child("w:color");
    if (color) {
        font.color = Color::from_hex(color.attribute("w:val").value());
    }

    auto v_align = r_pr.child("w:vertAlign");
    if (v_align) {
        font.script_type = string_to_script_type(v_align.attribute("w:val").value());
    }

    parse_shading_from_xml(r_pr.child("w:shd"), font.shading);
}

static void parse_style_paragraph_format_from_xml(pugi::xml_node p_pr, ParagraphFormat& format) {
    if (!p_pr) {
        return;
    }
    parse_paragraph_format_children_from_xml(p_pr, format);
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
        auto based_on_node = style_xml.child("w:basedOn");
        if (!style.get_base_style_name().empty()) {
            if (!based_on_node) {
                based_on_node = style_xml.prepend_child("w:basedOn");
            }
            based_on_node.attribute("w:val").set_value(style.get_base_style_name().c_str());
        } else if (based_on_node) {
            style_xml.remove_child(based_on_node);
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
            auto based_on = style_xml.append_child("w:basedOn");
            based_on.append_attribute("w:val").set_value(style.get_base_style_name().c_str());
        }
    }

    // Determine if DOM has explicit font/paragraph formatting
    const Font& font = style.get_font();
    const bool has_font_formatting = font.bold || font.italic || font.strikethrough ||
                                     font.underline != UnderlineType::None || font.size > 0 ||
                                     !font.name.empty() || font.color != Color::auto_color() ||
                                     font.script_type != ScriptType::Normal;

    const ParagraphFormat& para_format = style.get_paragraph_format();
    const bool has_para_format =
        para_format.alignment != ParagraphAlignment::Left || para_format.left_indent != 0 ||
        para_format.right_indent != 0 || para_format.first_line_indent != 0 ||
        para_format.space_before != 0 || para_format.space_after != 0 ||
        para_format.line_spacing != 1.15 || para_format.keep_with_next ||
        para_format.keep_together || para_format.page_break_before || !para_format.widow_control ||
        para_format.outline_level != OutlineLevel::BodyText;

    // Merge w:rPr: preserve unknown children, overlay managed ones
    auto r_pr = style_xml.child("w:rPr");
    if (has_font_formatting) {
        if (!r_pr) {
            r_pr = style_xml.append_child("w:rPr");
        }
        // Check if original r_pr had szCs before we remove anything
        const bool original_had_sz_cs = r_pr.child("w:szCs") != nullptr;

        // Remove managed children that we will re-serialize
        remove_managed_children(r_pr,
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
        // Serialize current DOM font formatting directly into the existing r_pr
        serialize_font_to_r_pr(r_pr, font, original_had_sz_cs);
    }

    // Merge w:pPr: preserve unknown children, overlay managed ones
    auto p_pr = style_xml.child("w:pPr");
    if (has_para_format) {
        if (!p_pr) {
            p_pr = style_xml.append_child("w:pPr");
        }
        // Remove managed children that we will re-serialize
        remove_managed_children(p_pr, {"w:jc", "w:ind", "w:spacing", "w:shd", "w:dropCap"});
        serialize_style_paragraph_format_to_xml(p_pr, para_format);
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

    auto based_on = style_node.child("w:basedOn");
    if (based_on) {
        style->set_base_style_name(based_on.attribute("w:val").value());
    }

    auto r_pr = style_node.child("w:rPr");
    if (r_pr) {
        Font font;
        parse_font_from_xml(r_pr, font);
        style->set_font(font);
    } else {
        // No explicit r_pr: set font to empty so defaults aren't serialized
        Font empty_font;
        empty_font.size = 0;
        empty_font.name = "";
        empty_font.name_far_east = "";
        empty_font.color = Color::auto_color();
        style->set_font(empty_font);
    }

    auto p_pr = style_node.child("w:pPr");
    if (p_pr) {
        ParagraphFormat format;
        parse_style_paragraph_format_from_xml(p_pr, format);
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
