/**
 * @file sync_deserialize.cpp
 * @brief Physical XML to DOM deserialization
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

#include <cstring>

namespace cdocx {

static void parse_content_children(Document* doc,
                                 pugi::xml_node start,
                                 pugi::xml_node end,
                                 CompositeNode* container);
static void parse_header_footer_content(Document* doc, HeaderFooter* hf);

// Helper: create a DOM node that only needs an ID set from XML
// (BookmarkEnd, CommentRangeStart, CommentRangeEnd, FootnoteReference, EndnoteReference)
template <typename T>
static void append_id_node(Paragraph* para, Document* doc, pugi::xml_node node) {
    auto obj = std::make_shared<T>(doc);
    obj->set_id(node.attribute("w:id").as_int());
    para->append_child(obj);
}

static std::shared_ptr<FormField> parse_form_field_from_xml(Document* doc,
                                                            pugi::xml_node fld_char,
                                                            pugi::xml_node& child) {
    auto ff_data = fld_char.child("w:ffData");
    if (!ff_data) {
        return nullptr;
    }

    FormFieldType fftype = FormFieldType::TextInput;
    auto ff_text_input = ff_data.child("w:textInput");
    auto ff_check_box = ff_data.child("w:checkBox");
    auto ff_dd_list = ff_data.child("w:ddList");
    if (ff_check_box) {
        fftype = FormFieldType::CheckBox;
    } else if (ff_dd_list) {
        fftype = FormFieldType::ComboBox;
    }

    auto form_field = std::make_shared<FormField>(doc, fftype);

    auto ff_name = ff_data.child("w:name");
    if (ff_name) {
        form_field->set_name(ff_name.attribute("w:val").value());
    }

    auto ff_enabled = ff_data.child("w:enabled");
    if (ff_enabled) {
        form_field->set_enabled(ff_enabled.attribute("w:val").as_int() != 0);
    }

    auto ff_calc = ff_data.child("w:calcOnExit");
    if (ff_calc) {
        form_field->set_calculate_on_exit(ff_calc.attribute("w:val").as_int() != 0);
    }

    if (ff_text_input) {
        auto ttype = ff_text_input.child("w:type");
        if (ttype) {
            const char* tv = ttype.attribute("w:val").value();
            form_field->set_text_input_type(string_to_text_form_field_type(tv));
        }
        auto tdef = ff_text_input.child("w:default");
        if (tdef) {
            form_field->set_text_input_default(tdef.attribute("w:val").value());
        }
        auto tmax = ff_text_input.child("w:maxLength");
        if (tmax) {
            form_field->set_max_length(tmax.attribute("w:val").as_int());
        }
        auto tfmt = ff_text_input.child("w:format");
        if (tfmt) {
            form_field->set_text_input_format(tfmt.attribute("w:val").value());
        }
    } else if (ff_check_box) {
        auto cb_default = ff_check_box.child("w:default");
        if (cb_default) {
            form_field->set_default_value(cb_default.attribute("w:val").as_int() != 0);
        }
        auto cb_checked = ff_check_box.child("w:checked");
        if (cb_checked) {
            form_field->set_checked(cb_checked.attribute("w:val").as_int() != 0);
        }
        auto cb_size = ff_check_box.child("w:size");
        if (cb_size) {
            form_field->set_is_check_box_exact_size(true);
            form_field->set_check_box_size(cb_size.attribute("w:val").as_int() / 2.0);
        } else {
            form_field->set_is_check_box_exact_size(false);
        }
    } else if (ff_dd_list) {
        std::vector<std::string> items;
        for (auto entry = ff_dd_list.child("w:listEntry"); entry;
             entry = entry.next_sibling("w:listEntry")) {
            items.emplace_back(entry.attribute("w:val").value());
        }
        form_field->set_drop_down_items(items);
        auto dd_default = ff_dd_list.child("w:default");
        if (dd_default) {
            form_field->set_drop_down_selected_index(dd_default.attribute("w:val").as_int());
        }
    }

    std::string field_result;
    auto end_node = walk_field_sequence(child, nullptr, &field_result);
    if (end_node) {
        child = end_node;
    }
    form_field->set_result(field_result);
    return form_field;
}

// ============================================================================
// Physical -> DOM (Deserialization)
// ============================================================================

void Document::sync_sections_from_physical() {
    auto *doc_xml = get_document_xml();
    if (!doc_xml) {
        return;
    }

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return;
    }

    // Clear existing DOM sections
    remove_all_children();
    sections_cache_.clear();
    sections_dirty_ = false;

    auto ranges = collect_section_ranges(body);

    bool is_first = true;
    for (const auto& range : ranges) {
        auto section = std::make_shared<Section>(this);
        section->set_first_section(is_first);
        is_first = false;

        sections_cache_.push_back(section);

        auto sect_body = std::make_shared<Body>(this);

        // Parse content nodes
        parse_content_children(this, range.begin, range.end, sect_body.get());

        // Load section properties
        if (range.end) {
            section->set_sect_pr_node(range.end);
            section->load_properties();

            // Parse header/footer references
            for (auto ref = range.end.child("w:headerReference"); ref;
                 ref = ref.next_sibling("w:headerReference")) {
                HeaderFooterRef hf_ref;
                hf_ref.relationship_id = ref.attribute("r:id").value();
                hf_ref.type = string_to_header_footer_type(ref.attribute("w:type").value());
                section->add_header_ref(hf_ref);
            }
            for (auto ref = range.end.child("w:footerReference"); ref;
                 ref = ref.next_sibling("w:footerReference")) {
                HeaderFooterRef hf_ref;
                hf_ref.relationship_id = ref.attribute("r:id").value();
                hf_ref.type = string_to_header_footer_type(ref.attribute("w:type").value());
                section->add_footer_ref(hf_ref);
            }

            // Parse header/footer content from XML into DOM
            for (auto& header : section->get_all_headers()) {
                parse_header_footer_content(this, header.get());
            }
            for (auto& footer : section->get_all_footers()) {
                parse_header_footer_content(this, footer.get());
            }
        }

        section->set_body(sect_body);
        append_child(section);
    }

    // If body is completely empty, create a default section
    if (ranges.empty()) {
        auto section = std::make_shared<Section>(this);
        section->set_first_section(true);
        auto sect_body = std::make_shared<Body>(this);
        section->set_body(sect_body);
        append_child(section);
    }
}

void parse_run_format_from_xml(Inline* run, pugi::xml_node run_node) {
    if (!run || !run_node) {
        return;
    }

    auto r_pr = run_node.child("w:rPr");
    if (!r_pr) {
        // No explicit formatting: set font to empty so defaults aren't serialized
        Font empty_font;
        empty_font.size = 0;
        empty_font.name = "";
        empty_font.name_far_east = "";
        empty_font.color = Color::auto_color();
        run->set_font(empty_font);
        return;
    }

    // Preserve the original r_pr for round-trip fidelity of unmanaged properties
    run->preserve_r_pr(r_pr);

    Font font;
    parse_font_from_xml(r_pr, font);

    if (auto sp = r_pr.child("w:spacing")) {
        font.spacing = ConvertUtil::twips_to_point(sp.attribute("w:val").as_int());
    }

    if (auto w = r_pr.child("w:w")) {
        font.scale = w.attribute("w:val").as_int(100);
    }

    run->set_font(font);
}

std::shared_ptr<Run> Document::parse_run_from_xml(pugi::xml_node run_node) {
    if (!run_node) {
        return nullptr;
    }

    auto run = std::make_shared<Run>(this);

    // Get text content
    auto text_node = run_node.child("w:t");
    if (text_node) {
        run->set_text(text_node.text().get());
    }

    // Parse formatting
    parse_run_format_from_xml(run.get(), run_node);

    // Preserve unknown children (e.g., w:drawing) for round-trip fidelity.
    // Skip whitespace text nodes introduced by pretty-printed XML.
    for (auto child = run_node.first_child(); child; child = child.next_sibling()) {
        if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata) {
            continue;
        }
        const char* name = child.name();
        if (std::strcmp(name, "w:t") != 0 && std::strcmp(name, "w:rPr") != 0) {
            run->preserve_child(child);
        }
    }

    return run;
}

void parse_paragraph_format_children_from_xml(pugi::xml_node p_pr, ParagraphFormat& format) {
    parse_shading_from_xml(p_pr.child("w:shd"), format.shading);

    auto drop_cap = p_pr.child("w:dropCap");
    if (drop_cap) {
        format.lines_to_drop = drop_cap.attribute("w:lines").as_int(1);
        format.drop_cap_position = string_to_drop_cap_position(drop_cap.attribute("w:type").value());
    }

    auto jc = p_pr.child("w:jc");
    if (jc) {
        format.alignment = string_to_paragraph_alignment(jc.attribute("w:val").value());
    }

    auto ind = p_pr.child("w:ind");
    if (ind) {
        format.left_indent = ConvertUtil::twips_to_point(ind.attribute("w:left").as_int());
        format.right_indent = ConvertUtil::twips_to_point(ind.attribute("w:right").as_int());
        format.first_line_indent = ConvertUtil::twips_to_point(ind.attribute("w:firstLine").as_int());
    }

    auto spacing = p_pr.child("w:spacing");
    if (spacing) {
        format.space_before = ConvertUtil::twips_to_point(spacing.attribute("w:before").as_int());
        format.space_after = ConvertUtil::twips_to_point(spacing.attribute("w:after").as_int());
        const char* line_rule = spacing.attribute("w:lineRule").value();
        const int line_value = spacing.attribute("w:line").as_int();
        if (line_value != 0) {
            format.line_spacing_rule = string_to_line_spacing_rule(line_rule);
            if (format.line_spacing_rule == LineSpacingRule::Exact ||
                format.line_spacing_rule == LineSpacingRule::AtLeast) {
                format.line_spacing = ConvertUtil::twips_to_point(line_value);
            } else {
                format.line_spacing = line_value / 240.0;
            }
        }
    }

    struct ParagraphBoolFlagMapping {
        const char* child_name;
        bool ParagraphFormat::*flag;
    };
    static const ParagraphBoolFlagMapping kParagraphBoolFlagMappings[] = {
        {"w:keepNext", &ParagraphFormat::keep_with_next},
        {"w:keepLines", &ParagraphFormat::keep_together},
        {"w:pageBreakBefore", &ParagraphFormat::page_break_before},
    };
    for (const auto& mapping : kParagraphBoolFlagMappings) {
        if (p_pr.child(mapping.child_name)) {
            format.*mapping.flag = true;
        }
    }
    auto widow_control = p_pr.child("w:widowControl");
    if (widow_control) {
        format.widow_control = widow_control.attribute("w:val").as_int(1) != 0;
    }
    auto outline_lvl = p_pr.child("w:outlineLvl");
    if (outline_lvl) {
        const int level = outline_lvl.attribute("w:val").as_int(9);
        if (level >= 0 && level <= 8) {
            format.outline_level = static_cast<OutlineLevel>(level);
        } else {
            format.outline_level = OutlineLevel::BodyText;
        }
    }
}

// Walks a field sequence starting from the given run (which should be the begin run).
// Returns the node containing w:fld_char[end], or empty node if not found.
pugi::xml_node walk_field_sequence(pugi::xml_node start_run,
                                       std::string* out_instr_text,
                                       std::string* out_resulttext) {
    bool in_result = false;
    for (auto node = start_run; node; node = node.next_sibling()) {
        if (!is_run_node(node.name())) {
            continue;
        }

        auto fc = node.child("w:fldChar");
        if (fc) {
            const char* fct = fc.attribute("w:fldCharType").value();
            if (std::strcmp(fct, "separate") == 0) {
                in_result = true;
                continue;
            }
            if (std::strcmp(fct, "end") == 0) {
                return node;
            }
            if (std::strcmp(fct, "begin") == 0) {
                continue;
            }
        }

        auto instr = node.child("w:instrText");
        if (instr && !in_result && out_instr_text) {
            *out_instr_text += instr.text().get();
        }

        auto text_node = node.child("w:t");
        if (text_node && in_result && out_resulttext) {
            *out_resulttext += text_node.text().get();
        }
    }
    return pugi::xml_node{};
}

void parse_field_code_and_switches(const std::string& code, Field* field) {
    std::string trimmed = trim_whitespace(code);
    size_t switch_pos = std::string::npos;
    for (size_t i = 0; i + 1 < trimmed.size(); ++i) {
        if (trimmed[i] == ' ' && trimmed[i + 1] == '\\') {
            switch_pos = i;
            break;
        }
    }
    if (switch_pos == std::string::npos) {
        field->set_field_code(trimmed);
        return;
    }

    std::string base = trimmed.substr(0, switch_pos);
    while (!base.empty() && base.back() == ' ') {
        base.pop_back();
    }
    field->set_field_code(base);

    std::string rest = trimmed.substr(switch_pos + 1);
    size_t sw_start = 0;
    for (size_t i = 0; i + 1 < rest.size(); ++i) {
        if (rest[i] == ' ' && rest[i + 1] == '\\') {
            field->add_switch(rest.substr(sw_start, i - sw_start));
            sw_start = i + 1;
        }
    }
    if (sw_start < rest.size()) {
        std::string last_switch = rest.substr(sw_start);
        last_switch = trim_whitespace(last_switch);
        if (!last_switch.empty()) {
            field->add_switch(last_switch);
        }
    }
}

static void parse_hyperlink_from_xml(Document* doc,
                                     pugi::xml_node hyperlink_node,
                                     const std::shared_ptr<Paragraph>& para) {
    auto hyperlink = std::make_shared<Hyperlink>(doc);

    const char* rel_id = hyperlink_node.attribute("r:id").value();
    if (rel_id && *rel_id) {
        const std::string target =
            doc->get_relationship_target("word/_rels/document.xml.rels", rel_id);
        if (!target.empty()) {
            hyperlink->set_address(target);
        }
    }

    const char* anchor = hyperlink_node.attribute("w:anchor").value();
    if (anchor && *anchor) {
        hyperlink->set_bookmark_name(anchor);
    }

    const char* tooltip = hyperlink_node.attribute("w:tooltip").value();
    if (tooltip && *tooltip) {
        hyperlink->set_tooltip(tooltip);
    }

    std::string link_text;
    bool formatting_parsed = false;
    for (auto run_node = hyperlink_node.child("w:r"); run_node;
         run_node = run_node.next_sibling("w:r")) {
        auto text_node = run_node.child("w:t");
        if (text_node) {
            link_text += text_node.text().get();
        }
        if (!formatting_parsed) {
            parse_run_format_from_xml(hyperlink.get(), run_node);
            formatting_parsed = true;
        }
    }
    hyperlink->set_result(link_text);
    para->append_child(hyperlink);
}

static void parse_header_footer_content(Document* doc, HeaderFooter* hf) {
    auto *xml_doc = doc->get_xml_part(hf->get_part_path());
    if (!xml_doc) {
        return;
    }
    auto root = xml_doc->child(hf->is_header() ? "w:hdr" : "w:ftr");
    if (!root) {
        return;
    }
    hf->remove_all_children();
    parse_content_children(doc, root.first_child(), pugi::xml_node(), hf);
}

static void parse_content_children(Document* doc,
                                 pugi::xml_node start,
                                 pugi::xml_node end,
                                 CompositeNode* container) {
    for (auto node = start; node && node != end; node = node.next_sibling()) {
        const char* name = node.name();
        if (is_para_node(name)) {
            if (auto para = doc->parse_paragraph_from_xml(node)) {
                container->append_child(para);
            }
        } else if (is_table_node(name)) {
            if (auto table = doc->parse_table_from_xml(node)) {
                container->append_child(table);
            }
        }
    }
}

struct BreakTypeMapping {
    const char* xml_value;
    std::shared_ptr<SpecialChar> (*factory)();
};

static const BreakTypeMapping kBreakTypeMappings[] = {
    {"page", &SpecialChar::page_break},
    {"column", &SpecialChar::column_break},
};

std::shared_ptr<Paragraph> Document::parse_paragraph_from_xml(pugi::xml_node para_node) {
    if (!para_node) {
        return nullptr;
    }

    auto para = std::make_shared<Paragraph>(this);
    para->set_current(para_node);

    // Parse paragraph properties
    auto p_pr = para_node.child("w:pPr");
    if (p_pr) {
        para->preserve_p_pr(p_pr);
        parse_paragraph_format_children_from_xml(p_pr, para->get_paragraph_format());

        auto p_style = p_pr.child("w:pStyle");
        if (p_style) {
            para->get_paragraph_format().style_name = p_style.attribute("w:val").value();
        }

        auto num_pr = p_pr.child("w:numPr");
        if (num_pr) {
            auto ilvl = num_pr.child("w:ilvl");
            auto num_id = num_pr.child("w:numId");
            if (num_id) {
                para->get_list_format().list_id = num_id.attribute("w:val").as_uint();
                para->get_list_format().level =
                    ilvl ? static_cast<NumberingLevel>(ilvl.attribute("w:val").as_int())
                         : NumberingLevel::Level1;
            }
        }
    }

    // Parse inline content
    for (auto child = para_node.first_child(); child; child = child.next_sibling()) {
        const char* name = child.name();
        if (std::strcmp(name, "w:r") == 0) {
            auto fld_char = child.child("w:fldChar");
            if (fld_char &&
                std::strcmp(fld_char.attribute("w:fldCharType").value(), "begin") == 0) {
                // Check if this is a form field
                auto ff_data = fld_char.child("w:ffData");
                if (ff_data) {
                    auto form_field = parse_form_field_from_xml(this, fld_char, child);
                    if (form_field) {
                        para->append_child(form_field);
                    }
                } else {
                    auto field = std::make_shared<Field>(this, FieldType::Unknown);
                    std::string field_code;
                    std::string field_result;
                    auto end_node = walk_field_sequence(child, &field_code, &field_result);
                    if (end_node) {
                        child = end_node;
                    }

                    parse_field_code_and_switches(field_code, field.get());
                    field->set_result(field_result);
                    para->append_child(field);
                }
            } else if (auto run = parse_run_from_xml(child)) {
                para->append_child(run);
            }
        } else if (std::strcmp(name, "w:hyperlink") == 0) {
            parse_hyperlink_from_xml(this, child, para);
        } else if (std::strcmp(name, "w:br") == 0) {
            const char* type = child.attribute("w:type").value();
            bool found = false;
            for (const auto& mapping : kBreakTypeMappings) {
                if (std::strcmp(type, mapping.xml_value) == 0) {
                    para->append_child(mapping.factory());
                    found = true;
                    break;
                }
            }
            if (!found) {
                para->append_child(SpecialChar::line_break());
            }
        } else if (std::strcmp(name, "w:tab") == 0) {
            para->append_child(SpecialChar::tab());
        } else if (is_bookmark_start_node(name)) {
            auto bookmark = std::make_shared<BookmarkStart>(this);
            bookmark->set_id(child.attribute("w:id").as_int());
            bookmark->set_name(child.attribute("w:name").value());
            para->append_child(bookmark);
        } else if (is_bookmark_end_node(name)) {
            append_id_node<BookmarkEnd>(para.get(), this, child);
        } else if (std::strcmp(name, "w:commentRangeStart") == 0) {
            append_id_node<CommentRangeStart>(para.get(), this, child);
        } else if (std::strcmp(name, "w:commentRangeEnd") == 0) {
            append_id_node<CommentRangeEnd>(para.get(), this, child);
        } else if (std::strcmp(name, "w:commentReference") == 0) {
            // Skip comment references - they are auto-generated during serialization
            continue;
        } else if (std::strcmp(name, "w:footnoteReference") == 0) {
            append_id_node<FootnoteReference>(para.get(), this, child);
        } else if (std::strcmp(name, "w:endnoteReference") == 0) {
            append_id_node<EndnoteReference>(para.get(), this, child);
        }
    }

    return para;
}

std::shared_ptr<Table> Document::parse_table_from_xml(pugi::xml_node table_node) {
    if (!table_node) {
        return nullptr;
    }

    auto table = std::make_shared<Table>(this);

    // Parse table properties
    auto tbl_pr = table_node.child("w:tblPr");
    if (tbl_pr) {
        table->preserve_tbl_pr(tbl_pr);
        auto jc = tbl_pr.child("w:jc");
        if (jc) {
            table->get_table_format().alignment =
                string_to_table_alignment(jc.attribute("w:val").value());
        }
        auto tbl_ind = tbl_pr.child("w:tblInd");
        if (tbl_ind) {
            table->get_table_format().left_indent = ConvertUtil::twips_to_point(tbl_ind.attribute("w:w").as_int());
        }
        auto tbl_style = tbl_pr.child("w:tblStyle");
        if (tbl_style) {
            table->set_style(tbl_style.attribute("w:val").value());
        }
        parse_shading_from_xml(tbl_pr.child("w:shd"), table->get_table_format().shading);
        parse_borders_from_xml(tbl_pr.child("w:tblBorders"), table->get_table_format().borders);
        auto tbl_layout = tbl_pr.child("w:tblLayout");
        if (tbl_layout) {
            const char* layout_type = tbl_layout.attribute("w:type").value();
            if (std::strcmp(layout_type, "fixed") == 0) {
                table->get_table_format().auto_fit_behavior = AutoFitBehavior::FixedColumnWidth;
                table->get_table_format().allow_auto_fit = false;
            } else {
                auto tbl_w = tbl_pr.child("w:tblW");
                if (tbl_w) {
                    const char* width_type = tbl_w.attribute("w:type").value();
                    if (std::strcmp(width_type, "pct") == 0) {
                        table->get_table_format().auto_fit_behavior =
                            AutoFitBehavior::AutoFitToWindow;
                    } else {
                        table->get_table_format().auto_fit_behavior =
                            AutoFitBehavior::AutoFitToContents;
                    }
                } else {
                    table->get_table_format().auto_fit_behavior =
                        AutoFitBehavior::AutoFitToContents;
                }
                table->get_table_format().allow_auto_fit = true;
            }
        }
    }

    // Preserve table grid for round-trip fidelity
    auto tbl_grid = table_node.child("w:tblGrid");
    if (tbl_grid) {
        table->preserve_tbl_grid(tbl_grid);
    }

    for (auto tr = table_node.child("w:tr"); tr; tr = tr.next_sibling("w:tr")) {
        auto row = std::make_shared<Row>(this);

        // Parse row properties
        auto tr_pr = tr.child("w:trPr");
        if (tr_pr) {
            auto tr_height = tr_pr.child("w:trHeight");
            if (tr_height) {
                row->get_row_format().height = ConvertUtil::twips_to_point(tr_height.attribute("w:val").as_int());
                const char* rule = tr_height.attribute("w:hRule").value();
                row->get_row_format().height_rule_exact = (std::strcmp(rule, "exact") == 0);
            }
            struct RowBoolFlagMapping {
                const char* child_name;
                bool RowFormat::*flag;
                bool value;
            };
            static const RowBoolFlagMapping kRowBoolFlagMappings[] = {
                {"w:tblHeader", &RowFormat::heading, true},
                {"w:cantSplit", &RowFormat::allow_break_across_pages, false},
            };
            for (const auto& mapping : kRowBoolFlagMappings) {
                if (tr_pr.child(mapping.child_name)) {
                    row->get_row_format().*mapping.flag = mapping.value;
                }
            }
        }

        for (auto tc = tr.child("w:tc"); tc; tc = tc.next_sibling("w:tc")) {
            auto cell = std::make_shared<Cell>(this);

            // Parse cell properties
            auto tc_pr = tc.child("w:tcPr");
            if (tc_pr) {
                auto tc_w = tc_pr.child("w:tcW");
                if (tc_w) {
                    cell->get_cell_format().width = ConvertUtil::twips_to_point(tc_w.attribute("w:w").as_int());
                    const char* typeval = tc_w.attribute("w:type").value();
                    cell->get_cell_format().preferred_width = (std::strcmp(typeval, "pct") == 0);
                }
                auto v_align = tc_pr.child("w:vAlign");
                if (v_align) {
                    cell->get_cell_format().vertical_alignment =
                        string_to_cell_vertical_alignment(v_align.attribute("w:val").value());
                }
                auto grid_span = tc_pr.child("w:gridSpan");
                if (grid_span) {
                    cell->get_cell_format().horizontal_merge =
                        grid_span.attribute("w:val").as_int(1);
                    cell->get_cell_format().horizontal_merge =
                        std::max(1, cell->get_cell_format().horizontal_merge);
                }
                auto v_merge = tc_pr.child("w:vMerge");
                if (v_merge) {
                    cell->get_cell_format().vertical_merge = true;
                    const char* vmerge_val = v_merge.attribute("w:val").value();
                    cell->get_cell_format().vertical_merge_start =
                        (std::strcmp(vmerge_val, "restart") == 0);
                }
                parse_shading_from_xml(tc_pr.child("w:shd"), cell->get_cell_format().shading);
                parse_borders_from_xml(tc_pr.child("w:tcBorders"), cell->get_cell_format().borders);
            }

            // Parse cell content
            parse_content_children(this, tc.first_child(), pugi::xml_node(), cell.get());

            cell->ensure_minimum();
            row->append_child(cell);
        }

        table->append_child(row);
    }

    return table;
}

std::shared_ptr<Body> Document::parse_body_from_xml(pugi::xml_node body_node) {
    if (!body_node) {
        return nullptr;
    }

    auto body = std::make_shared<Body>(this);

    // Parse paragraphs and tables (stop at sect_pr)
    for (auto node = body_node.first_child(); node; node = node.next_sibling()) {
        const char* name = node.name();
        if (is_para_node(name)) {
            if (auto para = parse_paragraph_from_xml(node)) {
                body->append_child(para);
            }
        } else if (is_table_node(name)) {
            if (auto table = parse_table_from_xml(node)) {
                body->append_child(table);
            }
        } else if (is_sectpr_node(name)) {
            break;
        }
    }

    return body;
}


}  // namespace cdocx
