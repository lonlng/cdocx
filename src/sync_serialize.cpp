/**
 * @file sync_serialize.cpp
 * @brief DOM to Physical XML serialization
 */

#include "sync_common.h"

#include <cdocx/body.h>
#include <cdocx/convert_util.h>
#include <cdocx/comment.h>
#include <cdocx/document.h>
#include <cdocx/footnote.h>
#include <cdocx/formfield.h>
#include <cdocx/section.h>
#include <cdocx/table.h>

#include <cctype>
#include <cstring>

namespace cdocx {

static void serialize_section_to_xml(pugi::xml_node body_xml, const Section* section);
static void serialize_table_to_xml(pugi::xml_node parent, const Table* table);

static bool is_para_node(const char* name) {
    return std::strcmp(name, "w:p") == 0;
}

static bool is_table_node(const char* name) {
    return std::strcmp(name, "w:tbl") == 0;
}

static bool is_sectpr_node(const char* name) {
    return std::strcmp(name, "w:sectPr") == 0;
}

static bool is_content_node(const char* name) {
    return is_para_node(name) || is_table_node(name);
}

// ============================================================================
// DOM -> Physical (Serialization)
// ============================================================================

void Document::merge_sections_from_physical() {
    auto *doc_xml = get_document_xml();
    if (!doc_xml) {
        return;
    }

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return;
    }

    // Parse XML section ranges
    struct SectionRange {
        pugi::xml_node begin;
        pugi::xml_node end;
    };
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

    auto dom_sections = get_sections();
    std::vector<std::shared_ptr<Section>> dom_sections_vec;
    for (auto& s : dom_sections) {
        dom_sections_vec.push_back(s);
    }

    // Ensure we have enough DOM sections
    while (dom_sections_vec.size() < ranges.size()) {
        auto section = std::make_shared<Section>(this);
        section->set_first_section(dom_sections_vec.empty());
        auto sect_body = std::make_shared<Body>(this);
        section->set_body(sect_body);
        append_child(section);
        sections_cache_.push_back(section);
        dom_sections_vec.push_back(section);
    }

    // Merge each XML section into the corresponding DOM section
    for (size_t i = 0; i < ranges.size(); ++i) {
        const auto& section = dom_sections_vec[i];
        auto sect_body = section->get_body();
        if (!sect_body) {
            sect_body = std::make_shared<Body>(this);
            section->set_body(sect_body);
        }

        // Collect existing DOM children
        std::vector<std::shared_ptr<Node>> dom_children;
        for (const auto& child : sect_body->get_children()) {
            dom_children.push_back(child);
        }

        // Collect XML children
        std::vector<std::shared_ptr<Node>> xml_children;
        for (auto node = ranges[i].begin; node && node != ranges[i].end;
             node = node.next_sibling()) {
            const char* name = node.name();
            if (is_para_node(name)) {
                if (auto para = parse_paragraph_from_xml(node)) {
                    xml_children.push_back(para);
                }
            } else if (is_table_node(name)) {
                if (auto table = parse_table_from_xml(node)) {
                    xml_children.push_back(table);
                }
            }
        }

        // Merge by position: replace dirty-linked paragraphs, keep others,
        // append extra XML children, preserve extra DOM children
        const size_t merge_count = std::min(dom_children.size(), xml_children.size());
        for (size_t j = 0; j < merge_count; ++j) {
            bool should_replace = false;
            if (dom_children[j]->node_type() == NodeType::Paragraph) {
                auto* para = dynamic_cast<Paragraph*>(dom_children[j].get());
                if (para && para->get_current() &&
                    dirty_xml_paragraphs_.count(para->get_current()) > 0) {
                    should_replace = true;
                }
            }

            if (should_replace) {
                sect_body->insert_child(static_cast<int>(j), xml_children[j]);
                sect_body->remove_child(dom_children[j]);
            }
        }

        // Append extra XML children
        for (size_t j = merge_count; j < xml_children.size(); ++j) {
            sect_body->append_child(xml_children[j]);
        }

        // Update section properties
        if (ranges[i].end) {
            section->set_sect_pr_node(ranges[i].end);
            section->load_properties();
        }
    }

    sections_dirty_ = false;
}

void Document::sync_sections_to_physical() {
    auto *doc_xml = get_document_xml();
    if (!doc_xml) {
        return;
    }

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return;
    }

    // If DOM has no sections, preserve existing XML
    auto sections = get_sections();
    if (sections.is_empty()) {
        return;
    }

    // Count XML paragraph/table children
    int xml_child_count = 0;
    for (auto child = body.first_child(); child; child = child.next_sibling()) {
        const char* name = child.name();
        if (is_content_node(name)) {
            ++xml_child_count;
        }
    }

    // Count DOM paragraph/table children across all sections
    int dom_child_count = 0;
    for (auto& section : sections) {
        if (auto sect_body = section->get_body()) {
            for (const auto& child : sect_body->get_children()) {
                if (child->node_type() == NodeType::Paragraph ||
                    child->node_type() == NodeType::Table) {
                    ++dom_child_count;
                }
            }
        }
    }

    // Update DOM paragraphs whose XML was explicitly modified by DocumentBuilder
    // or legacy API, so their content is not lost during DOM serialization.
    for (auto& section : sections) {
        if (auto sect_body = section->get_body()) {
            for (const auto& child : sect_body->get_children()) {
                if (child->node_type() == NodeType::Paragraph) {
                    auto* para = dynamic_cast<Paragraph*>(child.get());
                    if (para && para->get_current() &&
                        dirty_xml_paragraphs_.count(para->get_current()) > 0) {
                        for (auto xml_para = body.child("w:p"); xml_para;
                             xml_para = xml_para.next_sibling("w:p")) {
                            if (xml_para == para->get_current()) {
                                if (auto updated = parse_paragraph_from_xml(xml_para)) {
                                    para->remove_all_children();
                                    for (const auto& new_child : updated->get_children()) {
                                        para->append_child(new_child);
                                    }
                                }
                                para->set_current(pugi::xml_node());
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    // If XML has more content than DOM, physical XML may have been modified
    // directly (legacy API, DocumentBuilder). We only sync from physical when
    // the XML child count has INCREASED since the last sync — that indicates
    // new content was added to physical XML outside the DOM. If the count is
    // unchanged, the DOM intentionally deleted content and we must trust it.
    if (xml_child_count > dom_child_count &&
        xml_child_count > last_synced_xml_child_count_) {
        if (!dirty_xml_paragraphs_.empty()) {
            merge_sections_from_physical();
        } else {
            sync_from_physical_tree();
        }
        sections = get_sections();
    }
    dirty_xml_paragraphs_.clear();

    // Preserve unknown nodes (not paragraphs, tables, or section properties)
    pugi::xml_document preserved_doc;
    for (auto child = body.first_child(); child;) {
        auto next = child.next_sibling();
        const char* name = child.name();
        if (!is_content_node(name) && !is_sectpr_node(name)) {
            preserved_doc.append_copy(child);
        }
        child = next;
    }

    // Remove all existing children from body
    while (body.first_child()) {
        body.remove_child(body.first_child());
    }

    // Serialize each section
    for (auto& section : sections) {
        serialize_section_to_xml(body, section.get());
    }

    // Re-append preserved unknown nodes at the end
    for (auto child = preserved_doc.first_child(); child; child = child.next_sibling()) {
        body.append_copy(child);
    }

    // Record the synced child count so future calls can detect physical-only
    // additions (e.g. legacy API direct XML manipulation).
    int synced_count = 0;
    for (auto child = body.first_child(); child; child = child.next_sibling()) {
        const char* name = child.name();
        if (is_content_node(name)) {
            ++synced_count;
        }
    }
    last_synced_xml_child_count_ = synced_count;

    mark_modified("word/document.xml");
}

void serialize_font_to_r_pr(pugi::xml_node r_pr, const Font& font, bool add_sz_cs) {
    serialize_shading_to_xml(r_pr, font.shading);
    if (font.bold) {
        r_pr.append_child("w:b");
    }
    if (font.italic) {
        r_pr.append_child("w:i");
    }
    if (font.strikethrough) {
        auto strike = r_pr.append_child("w:strike");
        strike.append_attribute("w:val").set_value("true");
    }
    if (font.underline != UnderlineType::None) {
        auto u = r_pr.append_child("w:u");
        const char* val = underline_type_to_string(font.underline);
        if (!val) {
            val = "single";
        }
        u.append_attribute("w:val").set_value(val);
    }
    if (font.size > 0) {
        auto sz = r_pr.append_child("w:sz");
        sz.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
        if (add_sz_cs) {
            auto sz_cs = r_pr.append_child("w:szCs");
            sz_cs.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
        }
    }
    if (!font.name.empty()) {
        auto r_fonts = r_pr.append_child("w:rFonts");
        r_fonts.append_attribute("w:ascii").set_value(font.name.c_str());
        r_fonts.append_attribute("w:hAnsi").set_value(font.name.c_str());
        if (!font.name_far_east.empty()) {
            r_fonts.append_attribute("w:eastAsia").set_value(font.name_far_east.c_str());
        }
    }
    if (font.color != Color::auto_color()) {
        auto color = r_pr.append_child("w:color");
        color.append_attribute("w:val").set_value(font.color.to_hex_rgb().c_str());
    }
    if (font.script_type != ScriptType::Normal) {
        auto v_align = r_pr.append_child("w:vertAlign");
        v_align.append_attribute("w:val").set_value(script_type_to_string(font.script_type));
    }
    if (font.spacing != 0) {
        auto sp = r_pr.append_child("w:spacing");
        sp.append_attribute("w:val").set_value(ConvertUtil::point_to_twips(font.spacing));
    }
    if (font.scale != 100) {
        auto w = r_pr.append_child("w:w");
        w.append_attribute("w:val").set_value(font.scale);
    }
}

static void serialize_run_formatting_to_xml(pugi::xml_node run_xml,
                                        const Font& font,
                                        pugi::xml_node preserved_r_pr) {
    const bool has_formatting = font.bold || font.italic || font.strikethrough ||
                                font.underline != UnderlineType::None || font.size != 12.0 ||
                                font.name != "Times New Roman" || font.color != Color::black() ||
                                font.script_type != ScriptType::Normal || font.shading.has_fill() ||
                                font.spacing != 0 || font.scale != 100;

    if (!has_formatting && !preserved_r_pr) {
        return;
    }

    auto r_pr = run_xml.child("w:rPr");
    if (!r_pr) {
        if (preserved_r_pr) {
            r_pr = run_xml.prepend_copy(preserved_r_pr);
            strip_whitespace_text_nodes(r_pr);
        } else {
            r_pr = run_xml.prepend_child("w:rPr");
        }
    }

    // Remember whether the original had w:sz_cs before we remove managed children
    const bool original_had_sz_cs = preserved_r_pr && preserved_r_pr.child("w:szCs");

    // Remove managed children that we will re-serialize from DOM font state.
    // w:r_fonts is handled separately: if font.name is empty we leave the
    // original r_fonts untouched so that attributes like w:hint survive.
    remove_managed_children(r_pr,
                            {"w:b",
                             "w:i",
                             "w:strike",
                             "w:u",
                             "w:sz",
                             "w:szCs",
                             "w:color",
                             "w:vertAlign",
                             "w:spacing",
                             "w:w",
                             "w:shd"});
    if (!font.name.empty()) {
        remove_managed_children(r_pr, {"w:rFonts"});
    }

    // Re-add managed children from current font state
    serialize_font_to_r_pr(r_pr, font, original_had_sz_cs);

    // If r_pr ended up empty, remove it entirely to avoid <w:r_pr/> bloat.
    if (!r_pr.first_child()) {
        run_xml.remove_child(r_pr);
    }
}

static void serialize_run_to_xml(pugi::xml_node parent, const Run* run) {
    if (!run) {
        return;
    }

    auto run_xml = parent.append_child("w:r");
    serialize_run_formatting_to_xml(
        run_xml,
        run->get_font(),
        run->has_preserved_r_pr() ? run->get_preserved_r_pr() : pugi::xml_node());

    const std::string& text = run->get_text();
    if (!text.empty()) {
        auto text_node = run_xml.append_child("w:t");
        if (std::isspace(static_cast<unsigned char>(text.front())) ||
            std::isspace(static_cast<unsigned char>(text.back()))) {
            text_node.append_attribute("xml:space").set_value("preserve");
        }
        text_node.text().set(text.c_str());
    }

    // Serialize preserved children (e.g., w:drawing) for round-trip fidelity
    if (run->has_preserved_children()) {
        run->serialize_preserved_children(run_xml);
    }
}

static void serialize_field_to_xml(pugi::xml_node parent, Field* field) {
    if (!field) {
        return;
    }

    auto begin_run = parent.append_child("w:r");
    begin_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("begin");

    const std::string code = field->get_full_field_code();
    if (!code.empty()) {
        auto instr_run = parent.append_child("w:r");
        auto instr_text = instr_run.append_child("w:instrText");
        instr_text.append_attribute("xml:space").set_value("preserve");
        instr_text.text().set(code.c_str());
    }

    auto sep_run = parent.append_child("w:r");
    sep_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("separate");

    const std::string result = field->get_result();
    if (!result.empty()) {
        auto resultrun = parent.append_child("w:r");
        auto text_node = resultrun.append_child("w:t");
        text_node.text().set(result.c_str());
    }

    auto end_run = parent.append_child("w:r");
    end_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("end");
}

static void serialize_form_field_to_xml(pugi::xml_node parent, const FormField* field) {
    append_form_field_sequence(parent, field, field ? field->get_document() : nullptr);
}

static void serialize_hyperlink_to_xml(pugi::xml_node parent, Hyperlink* link) {
    if (!link) {
        return;
    }

    auto hyperlink_xml = parent.append_child("w:hyperlink");

    const std::string address = link->get_address();
    const std::string bookmark = link->get_bookmark_name();

    Document* doc = link->get_document();
    if (!address.empty() && doc) {
        std::string rel_id = doc->find_relationship_id("word/_rels/document.xml.rels", address);
        if (rel_id.empty()) {
            rel_id = doc->add_relationship(
                "word/_rels/document.xml.rels",
                "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink",
                address,
                "External");
        }
        hyperlink_xml.append_attribute("r:id").set_value(rel_id.c_str());
    } else if (!bookmark.empty()) {
        hyperlink_xml.append_attribute("w:anchor").set_value(bookmark.c_str());
    }

    if (!link->get_tooltip().empty()) {
        hyperlink_xml.append_attribute("w:tooltip").set_value(link->get_tooltip().c_str());
    }

    auto run_xml = hyperlink_xml.append_child("w:r");
    serialize_run_formatting_to_xml(
        run_xml,
        link->get_font(),
        link->has_preserved_r_pr() ? link->get_preserved_r_pr() : pugi::xml_node());

    const std::string result = link->get_result();
    if (!result.empty()) {
        auto text_node = run_xml.append_child("w:t");
        text_node.text().set(result.c_str());
    }
}

struct SpecialCharMapping {
    char16_t code;
    const char* element_name;
    const char* break_type;  // nullptr if no type attribute
};

static const SpecialCharMapping kSpecialCharMappings[] = {
    {0x0009, "w:tab", nullptr},
    {0x000A, "w:br", nullptr},
    {0x000C, "w:br", "page"},
    {0x000E, "w:br", "column"},
};

static void serialize_special_char_to_xml(pugi::xml_node parent, SpecialChar* sc) {
    if (!sc) {
        return;
    }
    const char16_t code = sc->get_char();
    for (const auto& mapping : kSpecialCharMappings) {
        if (mapping.code == code) {
            auto node = parent.append_child(mapping.element_name);
            if (mapping.break_type) {
                node.append_attribute("w:type").set_value(mapping.break_type);
            }
            return;
        }
    }
    // For other special chars, append as text in a run
    auto run = parent.append_child("w:r");
    auto t = run.append_child("w:t");
    t.text().set(sc->get_text().c_str());
}

void serialize_paragraph_format_children_to_xml(pugi::xml_node p_pr,
                                                  const ParagraphFormat& format) {
    serialize_shading_to_xml(p_pr, format.shading);

    if (format.drop_cap_position != DropCapPosition::None) {
        auto drop_cap = p_pr.append_child("w:dropCap");
        drop_cap.append_attribute("w:lines").set_value(format.lines_to_drop);
        drop_cap.append_attribute("w:type").set_value(
            drop_cap_position_to_string(format.drop_cap_position));
    }

    if (format.alignment != ParagraphAlignment::Left) {
        auto jc = p_pr.append_child("w:jc");
        jc.append_attribute("w:val").set_value(paragraph_alignment_to_string(format.alignment));
    }

    if (format.left_indent != 0 || format.right_indent != 0 || format.first_line_indent != 0) {
        auto ind = p_pr.append_child("w:ind");
        if (format.left_indent != 0) {
            ind.append_attribute("w:left").set_value(ConvertUtil::point_to_twips(format.left_indent));
        }
        if (format.right_indent != 0) {
            ind.append_attribute("w:right").set_value(ConvertUtil::point_to_twips(format.right_indent));
        }
        if (format.first_line_indent != 0) {
            ind.append_attribute("w:firstLine")
                .set_value(ConvertUtil::point_to_twips(format.first_line_indent));
        }
    }

    if (format.space_before != 0 || format.space_after != 0 || format.line_spacing != 1.15) {
        auto spacing = p_pr.append_child("w:spacing");
        if (format.space_before != 0) {
            spacing.append_attribute("w:before")
                .set_value(ConvertUtil::point_to_twips(format.space_before));
        }
        if (format.space_after != 0) {
            spacing.append_attribute("w:after").set_value(
                ConvertUtil::point_to_twips(format.space_after));
        }
        if (format.line_spacing != 1.15) {
            int line_value = static_cast<int>(format.line_spacing * 240);
            if (format.line_spacing_rule == LineSpacingRule::Exact ||
                format.line_spacing_rule == LineSpacingRule::AtLeast) {
                line_value = ConvertUtil::point_to_twips(format.line_spacing);
            }
            spacing.append_attribute("w:lineRule")
                .set_value(line_spacing_rule_to_string(format.line_spacing_rule));
            spacing.append_attribute("w:line").set_value(line_value);
        }
    }

    if (format.keep_with_next) {
        p_pr.append_child("w:keepNext");
    }
    if (format.keep_together) {
        p_pr.append_child("w:keepLines");
    }
    if (format.page_break_before) {
        p_pr.append_child("w:pageBreakBefore");
    }
    if (!format.widow_control) {
        auto widow = p_pr.append_child("w:widowControl");
        widow.append_attribute("w:val").set_value("0");
    }
    if (format.outline_level != OutlineLevel::BodyText) {
        auto outline = p_pr.append_child("w:outlineLvl");
        outline.append_attribute("w:val").set_value(static_cast<int>(format.outline_level));
    }
}

static void serialize_paragraph_format_to_xml(pugi::xml_node para_xml, const ParagraphFormat& format) {
    const bool has_format =
        format.alignment != ParagraphAlignment::Left || format.left_indent != 0 ||
        format.right_indent != 0 || format.first_line_indent != 0 || format.space_before != 0 ||
        format.space_after != 0 || format.line_spacing != 1.15 || !format.style_name.empty() ||
        format.shading.has_fill() || format.drop_cap_position != DropCapPosition::None ||
        format.keep_with_next || format.keep_together || format.page_break_before ||
        !format.widow_control || format.outline_level != OutlineLevel::BodyText;

    if (!has_format) {
        return;
    }

    auto p_pr = para_xml.prepend_child("w:pPr");
    serialize_paragraph_format_children_to_xml(p_pr, format);

    if (!format.style_name.empty()) {
        auto p_style = p_pr.append_child("w:pStyle");
        p_style.append_attribute("w:val").set_value(format.style_name.c_str());
    }
}

static void serialize_list_format_to_xml(pugi::xml_node para_xml, const ListFormat& list_format) {
    if (!list_format.is_list_item()) {
        return;
    }

    auto p_pr = para_xml.child("w:pPr");
    if (!p_pr) {
        p_pr = para_xml.prepend_child("w:pPr");
    }

    auto num_pr = p_pr.append_child("w:numPr");
    auto ilvl = num_pr.append_child("w:ilvl");
    ilvl.append_attribute("w:val").set_value(static_cast<int>(list_format.level));
    auto num_id = num_pr.append_child("w:numId");
    num_id.append_attribute("w:val").set_value(static_cast<unsigned int>(list_format.list_id));
}

template <typename T>
static void serialize_id_node_to_xml(pugi::xml_node parent, const char* tag_name, T* node) {
    if (!node) {
        return;
    }
    auto xml = parent.append_child(tag_name);
    xml.append_attribute("w:id").set_value(node->get_id());
}

static void serialize_bookmark_start_to_xml(pugi::xml_node parent, BookmarkStart* bookmark) {
    if (!bookmark) {
        return;
    }
    auto xml = parent.append_child("w:bookmarkStart");
    xml.append_attribute("w:id").set_value(bookmark->get_id());
    xml.append_attribute("w:name").set_value(bookmark->get_name().c_str());
}

static void serialize_bookmark_end_to_xml(pugi::xml_node parent, BookmarkEnd* bookmark) {
    serialize_id_node_to_xml(parent, "w:bookmarkEnd", bookmark);
}

static void serialize_comment_range_start_to_xml(pugi::xml_node parent, CommentRangeStart* comment) {
    serialize_id_node_to_xml(parent, "w:commentRangeStart", comment);
}

static void serialize_comment_range_end_to_xml(pugi::xml_node parent, CommentRangeEnd* comment) {
    serialize_id_node_to_xml(parent, "w:commentRangeEnd", comment);
}

static void serialize_comment_reference_to_xml(pugi::xml_node parent, int id) {
    auto r = parent.append_child("w:r");
    auto ref = r.append_child("w:commentReference");
    ref.append_attribute("w:id").set_value(id);
}

static void serialize_footnote_reference_to_xml(pugi::xml_node parent, FootnoteReference* ref) {
    serialize_id_node_to_xml(parent, "w:footnoteReference", ref);
}

static void serialize_endnote_reference_to_xml(pugi::xml_node parent, EndnoteReference* ref) {
    serialize_id_node_to_xml(parent, "w:endnoteReference", ref);
}

void serialize_paragraph_to_xml(pugi::xml_node parent, const Paragraph* para) {
    if (!para) {
        return;
    }
    auto para_xml = parent.append_child("w:p");

    serialize_paragraph_format_to_xml(para_xml, para->get_paragraph_format());
    serialize_list_format_to_xml(para_xml, para->get_list_format());

    // Preserve unmanaged p_pr children and attributes that ParagraphFormat doesn't track.
    if (para->has_preserved_p_pr()) {
        const pugi::xml_node preserved_p_pr = para->get_preserved_p_pr();
        pugi::xml_node p_pr = para_xml.child("w:pPr");
        if (!p_pr) {
            para_xml.prepend_copy(preserved_p_pr);
        } else {
            for (pugi::xml_node child = preserved_p_pr.first_child(); child;
                 child = child.next_sibling()) {
                // Skip whitespace text nodes from pretty-printed XML
                if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata) {
                    continue;
                }
                const char* name = child.name();
                pugi::xml_node existing = p_pr.child(name);
                if (!existing) {
                    p_pr.append_copy(child);
                } else {
                    // Merge any attributes that the DOM serialization didn't create
                    for (pugi::xml_attribute attr = child.first_attribute(); attr;
                         attr = attr.next_attribute()) {
                        if (!existing.attribute(attr.name())) {
                            existing.append_copy(attr);
                        }
                    }
                }
            }
        }
    }

    std::vector<int> comment_ids_for_reference;
    for (const auto& child : para->get_children()) {
        switch (child->node_type()) {
            case NodeType::Run:
                serialize_run_to_xml(para_xml, dynamic_cast<Run*>(child.get()));
                break;
            case NodeType::SpecialChar:
                serialize_special_char_to_xml(para_xml, dynamic_cast<SpecialChar*>(child.get()));
                break;
            case NodeType::BookmarkStart:
                serialize_bookmark_start_to_xml(para_xml,
                                                dynamic_cast<BookmarkStart*>(child.get()));
                break;
            case NodeType::BookmarkEnd:
                serialize_bookmark_end_to_xml(para_xml, dynamic_cast<BookmarkEnd*>(child.get()));
                break;
            case NodeType::CommentRangeStart:
                serialize_comment_range_start_to_xml(para_xml,
                                                     dynamic_cast<CommentRangeStart*>(child.get()));
                break;
            case NodeType::CommentRangeEnd:
                serialize_comment_range_end_to_xml(para_xml,
                                                   dynamic_cast<CommentRangeEnd*>(child.get()));
                if (auto* cre = dynamic_cast<CommentRangeEnd*>(child.get())) {
                    comment_ids_for_reference.push_back(cre->get_id());
                }
                break;
            case NodeType::FieldStart:
                serialize_field_to_xml(para_xml, dynamic_cast<Field*>(child.get()));
                break;
            case NodeType::FormField:
                serialize_form_field_to_xml(para_xml, dynamic_cast<FormField*>(child.get()));
                break;
            case NodeType::Hyperlink:
                serialize_hyperlink_to_xml(para_xml, dynamic_cast<Hyperlink*>(child.get()));
                break;
            case NodeType::FootnoteReference:
                serialize_footnote_reference_to_xml(para_xml,
                                                    dynamic_cast<FootnoteReference*>(child.get()));
                break;
            case NodeType::EndnoteReference:
                serialize_endnote_reference_to_xml(para_xml,
                                                   dynamic_cast<EndnoteReference*>(child.get()));
                break;
            case NodeType::FieldSeparator:  // NOLINT(bugprone-branch-clone)
            case NodeType::FieldEnd:
                // These node types are not used as standalone DOM nodes
                break;
            default:
                break;
        }
    }
    // Add comment references after the paragraph content
    for (const int comment_id : comment_ids_for_reference) {
        serialize_comment_reference_to_xml(para_xml, comment_id);
    }
}

static void serialize_cell_to_xml(pugi::xml_node parent, Cell* cell) {
    if (!cell) {
        return;
    }
    auto tc = parent.append_child("w:tc");

    // Cell properties — always write tc_pr with at least a default tc_w so that
    // Word has structural information for layout.  Omitting tc_pr entirely can
    // cause unexpected default behaviour in some consumers.
    const CellFormat& fmt = cell->get_cell_format();
    auto tc_pr = tc.append_child("w:tcPr");
    {
        auto tc_w = tc_pr.append_child("w:tcW");
        if (fmt.width != 0) {
            tc_w.append_attribute("w:w").set_value(ConvertUtil::point_to_twips(fmt.width));
            tc_w.append_attribute("w:type").set_value(fmt.preferred_width ? "pct" : "dxa");
        } else {
            tc_w.append_attribute("w:w").set_value("0");
            tc_w.append_attribute("w:type").set_value("auto");
        }
    }
    if (fmt.vertical_alignment != CellVerticalAlignment::Top) {
        auto v_align = tc_pr.append_child("w:vAlign");
        v_align.append_attribute("w:val").set_value(
            cell_vertical_alignment_to_string(fmt.vertical_alignment));
    }
    if (fmt.horizontal_merge > 1) {
        auto grid_span = tc_pr.append_child("w:gridSpan");
        grid_span.append_attribute("w:val").set_value(fmt.horizontal_merge);
    }
    if (fmt.vertical_merge) {
        auto v_merge = tc_pr.append_child("w:vMerge");
        if (fmt.vertical_merge_start) {
            v_merge.append_attribute("w:val").set_value("restart");
        }
    }
    serialize_borders_to_xml(tc_pr, "w:tcBorders", fmt.borders);
    serialize_shading_to_xml(tc_pr, fmt.shading);

    for (const auto& child : cell->get_children()) {
        if (child->node_type() == NodeType::Paragraph) {
            serialize_paragraph_to_xml(tc, dynamic_cast<Paragraph*>(child.get()));
        } else if (child->node_type() == NodeType::Table) {
            serialize_table_to_xml(tc, dynamic_cast<Table*>(child.get()));
        }
    }

    // Ensure at least one paragraph
    if (tc.child("w:p") == nullptr) {
        tc.append_child("w:p").append_child("w:r").append_child("w:t");
    }
}

static void serialize_row_to_xml(pugi::xml_node parent, Row* row) {
    if (!row) {
        return;
    }
    auto tr = parent.append_child("w:tr");

    const RowFormat& fmt = row->get_row_format();
    const bool has_row_props = fmt.height != 0 || fmt.heading || !fmt.allow_break_across_pages;
    if (has_row_props) {
        auto tr_pr = tr.append_child("w:trPr");
        if (fmt.height != 0) {
            auto tr_height = tr_pr.append_child("w:trHeight");
            tr_height.append_attribute("w:val").set_value(ConvertUtil::point_to_twips(fmt.height));
            tr_height.append_attribute("w:hRule").set_value(fmt.height_rule_exact ? "exact"
                                                                                  : "atLeast");
        }
        if (fmt.heading) {
            tr_pr.append_child("w:tblHeader");
        }
        if (!fmt.allow_break_across_pages) {
            tr_pr.append_child("w:cantSplit");
        }
    }

    for (const auto& child : row->get_children()) {
        if (child->node_type() == NodeType::Cell) {
            serialize_cell_to_xml(tr, dynamic_cast<Cell*>(child.get()));
        }
    }
}

static void serialize_table_to_xml(pugi::xml_node parent, const Table* table) {
    if (!table) {
        return;
    }
    auto tbl = parent.append_child("w:tbl");

    // Table properties
    const TableFormat& fmt = table->get_table_format();
    pugi::xml_node tbl_pr;
    if (table->has_preserved_tbl_pr()) {
        tbl_pr = tbl.append_copy(table->get_preserved_tbl_pr());
        strip_whitespace_text_nodes(tbl_pr);
        // Remove managed children so we can re-serialize current DOM state
        remove_managed_children(
            tbl_pr,
            {"w:tblW", "w:tblLayout", "w:jc", "w:tblInd", "w:tblStyle", "w:shd", "w:tblBorders"});
    } else {
        tbl_pr = tbl.append_child("w:tblPr");
    }

    auto tbl_w = tbl_pr.append_child("w:tblW");
    if (fmt.auto_fit_behavior == AutoFitBehavior::AutoFitToWindow) {
        tbl_w.append_attribute("w:w").set_value("5000");
        tbl_w.append_attribute("w:type").set_value("pct");
    } else {
        tbl_w.append_attribute("w:w").set_value("0");
        tbl_w.append_attribute("w:type").set_value("auto");
    }

    auto tbl_layout = tbl_pr.append_child("w:tblLayout");
    if (fmt.auto_fit_behavior == AutoFitBehavior::FixedColumnWidth) {
        tbl_layout.append_attribute("w:type").set_value("fixed");
    } else {
        tbl_layout.append_attribute("w:type").set_value("autofit");
    }

    if (fmt.alignment != TableAlignment::Left) {
        auto jc = tbl_pr.append_child("w:jc");
        jc.append_attribute("w:val").set_value(table_alignment_to_string(fmt.alignment));
    }

    if (fmt.left_indent != 0) {
        auto tbl_ind = tbl_pr.append_child("w:tblInd");
        tbl_ind.append_attribute("w:w").set_value(ConvertUtil::point_to_twips(fmt.left_indent));
        tbl_ind.append_attribute("w:type").set_value("dxa");
    }

    const std::string style_name = table->get_style_name();
    if (!style_name.empty()) {
        auto tbl_style = tbl_pr.append_child("w:tblStyle");
        tbl_style.append_attribute("w:val").set_value(style_name.c_str());
    }

    serialize_shading_to_xml(tbl_pr, fmt.shading);
    serialize_borders_to_xml(tbl_pr, "w:tblBorders", fmt.borders);

    // Table grid
    if (table->has_preserved_tbl_grid()) {
        tbl.append_copy(table->get_preserved_tbl_grid());
    } else {
        auto rows = table->get_rows();
        if (rows.get_count() > 0) {
            auto tbl_grid = tbl.append_child("w:tblGrid");
            auto first_row = rows.first();
            if (first_row) {
                auto cells = first_row->get_cells();
                for (size_t c = 0; c < cells.get_count(); ++c) {
                    tbl_grid.append_child("w:gridCol");
                }
            }
        }
    }

    for (const auto& child : table->get_children()) {
        if (child->node_type() == NodeType::Row) {
            serialize_row_to_xml(tbl, dynamic_cast<Row*>(child.get()));
        }
    }
}

static void serialize_node_child_to_xml(pugi::xml_node parent, const Node* child) {
    switch (child->node_type()) {
        case NodeType::Paragraph:
            serialize_paragraph_to_xml(parent, dynamic_cast<const Paragraph*>(child));
            break;
        case NodeType::Table:
            serialize_table_to_xml(parent, dynamic_cast<const Table*>(child));
            break;
        default:
            break;
    }
}

static void serialize_body_to_xml(pugi::xml_node body_xml, Body* body) {
    if (!body) {
        return;
    }
    for (const auto& child : body->get_children()) {
        serialize_node_child_to_xml(body_xml, child.get());
    }
}

static void serialize_header_footer_to_xml(HeaderFooter* hf, Document* doc) {
    if (!hf || !doc) {
        return;
    }
    auto *xml_doc = doc->get_xml_part(hf->get_part_path());
    if (!xml_doc) {
        return;
    }

    auto root = xml_doc->child("w:hdr");
    if (!root) {
        root = xml_doc->child("w:ftr");
    }
    if (!root) {
        root = xml_doc->append_child(hf->is_header() ? "w:hdr" : "w:ftr");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    } else {
        while (root.first_child()) {
            root.remove_child(root.first_child());
        }
    }

    for (const auto& child : hf->get_children()) {
        serialize_node_child_to_xml(root, child.get());
    }

    doc->mark_modified(hf->get_part_path());
}

static void serialize_section_to_xml(pugi::xml_node body_xml, const Section* section) {
    if (!section) {
        return;
    }

    // Serialize body content
    if (auto body = section->get_body()) {
        serialize_body_to_xml(body_xml, body.get());
    }

    // Section properties
    auto sect_pr = body_xml.append_child("w:sectPr");
    section->get_properties().apply_to(sect_pr);

    // Header/footer references
    for (const auto& ref : section->get_header_refs()) {
        auto header_ref = sect_pr.append_child("w:headerReference");
        header_ref.append_attribute("r:id").set_value(ref.relationship_id.c_str());
        header_ref.append_attribute("w:type").set_value(header_footer_type_to_string(ref.type));
    }
    for (const auto& ref : section->get_footer_refs()) {
        auto footer_ref = sect_pr.append_child("w:footerReference");
        footer_ref.append_attribute("r:id").set_value(ref.relationship_id.c_str());
        footer_ref.append_attribute("w:type").set_value(header_footer_type_to_string(ref.type));
    }

    // Serialize header/footer content
    for (auto& header : section->get_all_headers()) {
        serialize_header_footer_to_xml(header.get(), section->get_document());
    }
    for (auto& footer : section->get_all_footers()) {
        serialize_header_footer_to_xml(footer.get(), section->get_document());
    }
}


}  // namespace cdocx
