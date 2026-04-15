/**
 * @file document_sync.cpp
 * @brief DOM-Physical sync implementation for Document class
 * @details This file contains the helper functions and sync implementations
 *          for converting between DOM object tree and XML physical tree.
 */

#include <cdocx/document.h>
#include <cdocx/section.h>
#include <cdocx/body.h>
#include <cdocx/paragraph.h>
#include <cdocx/table.h>
#include <cdocx/base.h>
#include <cdocx/format.h>
#include <cdocx/style.h>

#include <cctype>
#include <cstring>

namespace cdocx {

// ============================================================================
// Forward declarations of internal helpers (defined below)
// ============================================================================
static void serialize_run_to_xml(pugi::xml_node parent, Run* run);
static void serialize_paragraph_format_to_xml(pugi::xml_node para_xml, const ParagraphFormat& format);
static void serialize_list_format_to_xml(pugi::xml_node para_xml, const ListFormat& list_format);
static void serialize_paragraph_to_xml(pugi::xml_node parent, Paragraph* para);
static void serialize_cell_to_xml(pugi::xml_node parent, Cell* cell);
static void serialize_row_to_xml(pugi::xml_node parent, Row* row);
static void serialize_table_to_xml(pugi::xml_node parent, Table* table);
static void serialize_body_to_xml(pugi::xml_node body_xml, Body* body);
static void serialize_section_to_xml(pugi::xml_node body_xml, Section* section);

static void serialize_style_to_xml(pugi::xml_node styles_root, const Style& style);
static std::shared_ptr<Style> parse_style_from_xml(pugi::xml_node style_node, Document* doc);

static void parse_run_format_from_xml(Inline* run, pugi::xml_node run_node);

// ============================================================================
// Public Sync Methods
// ============================================================================

void Document::sync_dom_and_xml(bool dom_to_xml) {
    if (dom_to_xml) {
        sync_to_physical_tree();
    } else {
        sync_from_physical_tree();
    }
}

void Document::sync_to_physical_tree() {
    sync_sections_to_physical();
}

void Document::sync_from_physical_tree() {
    sync_sections_from_physical();
}

// ============================================================================
// DOM -> Physical (Serialization)
// ============================================================================

void Document::sync_sections_to_physical() {
    auto doc_xml = get_document_xml();
    if (!doc_xml) return;

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body) return;

    // If DOM has no sections, preserve existing XML
    auto sections = get_sections();
    if (sections.is_empty()) {
        return;
    }

    // Preserve unknown nodes (not paragraphs, tables, or section properties)
    pugi::xml_document preserved_doc;
    for (auto child = body.first_child(); child; ) {
        auto next = child.next_sibling();
        const char* name = child.name();
        if (std::strcmp(name, "w:p") != 0 &&
            std::strcmp(name, "w:tbl") != 0 &&
            std::strcmp(name, "w:sectPr") != 0) {
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

    mark_modified("word/document.xml");
}

static void serialize_run_formatting_to_xml(pugi::xml_node run_xml, const Font& font) {
    bool has_formatting = font.bold || font.italic || font.strikethrough ||
                          font.underline != UnderlineType::None || font.size > 0 ||
                          !font.name.empty() || font.color != Color::auto_color() ||
                          font.script_type != ScriptType::Normal;

    if (!has_formatting) return;

    auto rPr = run_xml.prepend_child("w:rPr");
    if (font.bold) {
        rPr.append_child("w:b");
    }
    if (font.italic) {
        rPr.append_child("w:i");
    }
    if (font.strikethrough) {
        auto strike = rPr.append_child("w:strike");
        strike.append_attribute("w:val").set_value("true");
    }
    if (font.underline != UnderlineType::None) {
        auto u = rPr.append_child("w:u");
        const char* val = "single";
        switch (font.underline) {
            case UnderlineType::Single: val = "single"; break;
            case UnderlineType::Words: val = "words"; break;
            case UnderlineType::Double: val = "double"; break;
            case UnderlineType::Dotted: val = "dotted"; break;
            case UnderlineType::Dash: val = "dash"; break;
            case UnderlineType::DashDot: val = "dashDot"; break;
            case UnderlineType::DashDotDot: val = "dashDotDot"; break;
            case UnderlineType::Wave: val = "wave"; break;
            case UnderlineType::Thick: val = "thick"; break;
            case UnderlineType::DottedHeavy: val = "dottedHeavy"; break;
            case UnderlineType::DashHeavy: val = "dashHeavy"; break;
            case UnderlineType::DashDotHeavy: val = "dashDotHeavy"; break;
            case UnderlineType::DashDotDotHeavy: val = "dashDotDotHeavy"; break;
            case UnderlineType::WaveHeavy: val = "waveHeavy"; break;
            default: break;
        }
        u.append_attribute("w:val").set_value(val);
    }
    if (font.size > 0) {
        auto sz = rPr.append_child("w:sz");
        sz.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
        auto szCs = rPr.append_child("w:szCs");
        szCs.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
    }
    if (!font.name.empty()) {
        auto rFonts = rPr.append_child("w:rFonts");
        rFonts.append_attribute("w:ascii").set_value(font.name.c_str());
        rFonts.append_attribute("w:hAnsi").set_value(font.name.c_str());
        if (!font.name_far_east.empty()) {
            rFonts.append_attribute("w:eastAsia").set_value(font.name_far_east.c_str());
        }
    }
    if (font.color != Color::auto_color()) {
        auto color = rPr.append_child("w:color");
        color.append_attribute("w:val").set_value(font.color.to_hex_rgb().c_str());
    }
    if (font.script_type == ScriptType::Superscript) {
        auto vAlign = rPr.append_child("w:vertAlign");
        vAlign.append_attribute("w:val").set_value("superscript");
    } else if (font.script_type == ScriptType::Subscript) {
        auto vAlign = rPr.append_child("w:vertAlign");
        vAlign.append_attribute("w:val").set_value("subscript");
    }
}

static void serialize_run_to_xml(pugi::xml_node parent, Run* run) {
    if (!run) return;

    auto run_xml = parent.append_child("w:r");
    serialize_run_formatting_to_xml(run_xml, run->get_font());

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
    if (!field) return;

    auto begin_run = parent.append_child("w:r");
    begin_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("begin");

    std::string code = field->get_field_code();
    if (!code.empty()) {
        auto instr_run = parent.append_child("w:r");
        auto instr_text = instr_run.append_child("w:instrText");
        instr_text.text().set(code.c_str());
    }

    auto sep_run = parent.append_child("w:r");
    sep_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("separate");

    std::string result = field->get_result();
    if (!result.empty()) {
        auto result_run = parent.append_child("w:r");
        auto text_node = result_run.append_child("w:t");
        text_node.text().set(result.c_str());
    }

    auto end_run = parent.append_child("w:r");
    end_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("end");
}

static void serialize_hyperlink_to_xml(pugi::xml_node parent, Hyperlink* link) {
    if (!link) return;

    auto hyperlink_xml = parent.append_child("w:hyperlink");

    std::string address = link->get_address();
    std::string bookmark = link->get_bookmark_name();

    Document* doc = link->get_document();
    if (!address.empty() && doc) {
        std::string rel_id = doc->find_relationship_id(
            "word/_rels/document.xml.rels", address);
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
    serialize_run_formatting_to_xml(run_xml, link->get_font());

    std::string result = link->get_result();
    if (!result.empty()) {
        auto text_node = run_xml.append_child("w:t");
        text_node.text().set(result.c_str());
    }
}

static void serialize_special_char_to_xml(pugi::xml_node parent, SpecialChar* sc) {
    if (!sc) return;
    char16_t code = sc->get_char();
    switch (code) {
        case 0x0009: // Tab
            parent.append_child("w:tab");
            break;
        case 0x000A: // Line break
            parent.append_child("w:br");
            break;
        case 0x000C: // Page break
        {
            auto br = parent.append_child("w:br");
            br.append_attribute("w:type").set_value("page");
            break;
        }
        case 0x000E: // Column break
        {
            auto br = parent.append_child("w:br");
            br.append_attribute("w:type").set_value("column");
            break;
        }
        default:
            // For other special chars, append as text in a run
        {
            auto run = parent.append_child("w:r");
            auto t = run.append_child("w:t");
            t.text().set(sc->get_text().c_str());
        }
    }
}

static void serialize_paragraph_format_to_xml(pugi::xml_node para_xml, const ParagraphFormat& format) {
    bool has_format = format.alignment != ParagraphAlignment::Left ||
                      format.left_indent != 0 || format.right_indent != 0 ||
                      format.first_line_indent != 0 || format.space_before != 0 ||
                      format.space_after != 0 || format.line_spacing != 1.15 ||
                      !format.style_name.empty();
    
    if (!has_format) return;
    
    auto pPr = para_xml.prepend_child("w:pPr");
    
    if (!format.style_name.empty()) {
        auto pStyle = pPr.append_child("w:pStyle");
        pStyle.append_attribute("w:val").set_value(format.style_name.c_str());
    }
    
    if (format.alignment != ParagraphAlignment::Left) {
        auto jc = pPr.append_child("w:jc");
        const char* val = "left";
        switch (format.alignment) {
            case ParagraphAlignment::Center: val = "center"; break;
            case ParagraphAlignment::Right: val = "right"; break;
            case ParagraphAlignment::Justify: val = "both"; break;
            case ParagraphAlignment::Distributed: val = "distribute"; break;
            default: break;
        }
        jc.append_attribute("w:val").set_value(val);
    }
    
    if (format.left_indent != 0 || format.right_indent != 0 || format.first_line_indent != 0) {
        auto ind = pPr.append_child("w:ind");
        if (format.left_indent != 0) {
            ind.append_attribute("w:left").set_value(static_cast<int>(format.left_indent * 20));
        }
        if (format.right_indent != 0) {
            ind.append_attribute("w:right").set_value(static_cast<int>(format.right_indent * 20));
        }
        if (format.first_line_indent != 0) {
            ind.append_attribute("w:firstLine").set_value(static_cast<int>(format.first_line_indent * 20));
        }
    }
    
    if (format.space_before != 0 || format.space_after != 0 || format.line_spacing != 1.15) {
        auto spacing = pPr.append_child("w:spacing");
        if (format.space_before != 0) {
            spacing.append_attribute("w:before").set_value(static_cast<int>(format.space_before * 20));
        }
        if (format.space_after != 0) {
            spacing.append_attribute("w:after").set_value(static_cast<int>(format.space_after * 20));
        }
        if (format.line_spacing != 1.15) {
            const char* rule = "auto";
            int line_value = static_cast<int>(format.line_spacing * 240);
            if (format.line_spacing_rule == LineSpacingRule::Exact) {
                rule = "exact";
                line_value = static_cast<int>(format.line_spacing * 20);
            } else if (format.line_spacing_rule == LineSpacingRule::AtLeast) {
                rule = "atLeast";
                line_value = static_cast<int>(format.line_spacing * 20);
            }
            spacing.append_attribute("w:lineRule").set_value(rule);
            spacing.append_attribute("w:line").set_value(line_value);
        }
    }
}

static void serialize_list_format_to_xml(pugi::xml_node para_xml, const ListFormat& list_format) {
    if (!list_format.is_list_item()) return;
    
    auto pPr = para_xml.child("w:pPr");
    if (!pPr) {
        pPr = para_xml.prepend_child("w:pPr");
    }
    
    auto numPr = pPr.append_child("w:numPr");
    auto ilvl = numPr.append_child("w:ilvl");
    ilvl.append_attribute("w:val").set_value(static_cast<int>(list_format.level));
    auto numId = numPr.append_child("w:numId");
    numId.append_attribute("w:val").set_value(static_cast<unsigned int>(list_format.list_id));
}

static void serialize_bookmark_start_to_xml(pugi::xml_node parent, BookmarkStart* bookmark) {
    if (!bookmark) return;
    auto xml = parent.append_child("w:bookmarkStart");
    xml.append_attribute("w:id").set_value(bookmark->get_id());
    xml.append_attribute("w:name").set_value(bookmark->get_name().c_str());
}

static void serialize_bookmark_end_to_xml(pugi::xml_node parent, BookmarkEnd* bookmark) {
    if (!bookmark) return;
    auto xml = parent.append_child("w:bookmarkEnd");
    xml.append_attribute("w:id").set_value(bookmark->get_id());
}

static void serialize_paragraph_to_xml(pugi::xml_node parent, Paragraph* para) {
    if (!para) return;
    auto para_xml = parent.append_child("w:p");
    
    serialize_paragraph_format_to_xml(para_xml, para->get_paragraph_format());
    serialize_list_format_to_xml(para_xml, para->get_list_format());
    
    for (const auto& child : para->get_children()) {
        switch (child->node_type()) {
            case NodeType::Run:
                serialize_run_to_xml(para_xml, dynamic_cast<Run*>(child.get()));
                break;
            case NodeType::SpecialChar:
                serialize_special_char_to_xml(para_xml, dynamic_cast<SpecialChar*>(child.get()));
                break;
            case NodeType::BookmarkStart:
                serialize_bookmark_start_to_xml(para_xml, dynamic_cast<BookmarkStart*>(child.get()));
                break;
            case NodeType::BookmarkEnd:
                serialize_bookmark_end_to_xml(para_xml, dynamic_cast<BookmarkEnd*>(child.get()));
                break;
            case NodeType::FieldStart:
                serialize_field_to_xml(para_xml, dynamic_cast<Field*>(child.get()));
                break;
            case NodeType::Hyperlink:
                serialize_hyperlink_to_xml(para_xml, dynamic_cast<Hyperlink*>(child.get()));
                break;
            case NodeType::FieldSeparator:
            case NodeType::FieldEnd:
                // These node types are not used as standalone DOM nodes
                break;
            default:
                break;
        }
    }
}

static void serialize_cell_to_xml(pugi::xml_node parent, Cell* cell) {
    if (!cell) return;
    auto tc = parent.append_child("w:tc");
    
    // Cell properties
    const CellFormat& fmt = cell->get_cell_format();
    bool has_props = fmt.width != 0 || fmt.vertical_alignment != CellVerticalAlignment::Top ||
                     fmt.horizontal_merge > 1 || fmt.vertical_merge;
    if (has_props) {
        auto tcPr = tc.append_child("w:tcPr");
        if (fmt.width != 0) {
            auto tcW = tcPr.append_child("w:tcW");
            tcW.append_attribute("w:w").set_value(static_cast<int>(fmt.width * 20));
            tcW.append_attribute("w:type").set_value(fmt.preferred_width ? "pct" : "dxa");
        }
        if (fmt.vertical_alignment != CellVerticalAlignment::Top) {
            auto vAlign = tcPr.append_child("w:vAlign");
            const char* val = "top";
            switch (fmt.vertical_alignment) {
                case CellVerticalAlignment::Center: val = "center"; break;
                case CellVerticalAlignment::Bottom: val = "bottom"; break;
                default: break;
            }
            vAlign.append_attribute("w:val").set_value(val);
        }
        if (fmt.horizontal_merge > 1) {
            auto gridSpan = tcPr.append_child("w:gridSpan");
            gridSpan.append_attribute("w:val").set_value(fmt.horizontal_merge);
        }
        if (fmt.vertical_merge) {
            auto vMerge = tcPr.append_child("w:vMerge");
            if (fmt.vertical_merge_start) {
                vMerge.append_attribute("w:val").set_value("restart");
            }
        }
    }
    
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
    if (!row) return;
    auto tr = parent.append_child("w:tr");
    
    const RowFormat& fmt = row->get_row_format();
    bool has_row_props = fmt.height != 0 || fmt.heading || !fmt.allow_break_across_pages;
    if (has_row_props) {
        auto trPr = tr.append_child("w:trPr");
        if (fmt.height != 0) {
            auto trHeight = trPr.append_child("w:trHeight");
            trHeight.append_attribute("w:val").set_value(static_cast<int>(fmt.height * 20));
            trHeight.append_attribute("w:hRule").set_value(fmt.height_rule_exact ? "exact" : "atLeast");
        }
        if (fmt.heading) {
            trPr.append_child("w:tblHeader");
        }
        if (!fmt.allow_break_across_pages) {
            trPr.append_child("w:cantSplit");
        }
    }
    
    for (const auto& child : row->get_children()) {
        if (child->node_type() == NodeType::Cell) {
            serialize_cell_to_xml(tr, dynamic_cast<Cell*>(child.get()));
        }
    }
}

static void serialize_table_to_xml(pugi::xml_node parent, Table* table) {
    if (!table) return;
    auto tbl = parent.append_child("w:tbl");
    
    // Table properties
    const TableFormat& fmt = table->get_table_format();
    auto tblPr = tbl.append_child("w:tblPr");
    
    auto tblW = tblPr.append_child("w:tblW");
    if (fmt.auto_fit_behavior == AutoFitBehavior::AutoFitToWindow) {
        tblW.append_attribute("w:w").set_value("5000");
        tblW.append_attribute("w:type").set_value("pct");
    } else {
        tblW.append_attribute("w:w").set_value("0");
        tblW.append_attribute("w:type").set_value("auto");
    }

    auto tblLayout = tblPr.append_child("w:tblLayout");
    if (fmt.auto_fit_behavior == AutoFitBehavior::FixedColumnWidth) {
        tblLayout.append_attribute("w:type").set_value("fixed");
    } else {
        tblLayout.append_attribute("w:type").set_value("autofit");
    }

    if (fmt.alignment != TableAlignment::Left) {
        auto jc = tblPr.append_child("w:jc");
        const char* align_val = "left";
        switch (fmt.alignment) {
            case TableAlignment::Center: align_val = "center"; break;
            case TableAlignment::Right: align_val = "right"; break;
            default: break;
        }
        jc.append_attribute("w:val").set_value(align_val);
    }
    
    if (fmt.left_indent != 0) {
        auto tblInd = tblPr.append_child("w:tblInd");
        tblInd.append_attribute("w:w").set_value(static_cast<int>(fmt.left_indent * 20));
        tblInd.append_attribute("w:type").set_value("dxa");
    }
    
    std::string style_name = table->get_style_name();
    if (!style_name.empty()) {
        auto tblStyle = tblPr.append_child("w:tblStyle");
        tblStyle.append_attribute("w:val").set_value(style_name.c_str());
    }
    
    auto rows = table->get_rows();
    if (rows.get_count() > 0) {
        // Table grid
        auto tblGrid = tbl.append_child("w:tblGrid");
        auto first_row = rows.first();
        if (first_row) {
            auto cells = first_row->get_cells();
            for (size_t c = 0; c < cells.get_count(); ++c) {
                tblGrid.append_child("w:gridCol");
            }
        }
    }
    
    for (const auto& child : table->get_children()) {
        if (child->node_type() == NodeType::Row) {
            serialize_row_to_xml(tbl, dynamic_cast<Row*>(child.get()));
        }
    }
}

static void serialize_body_to_xml(pugi::xml_node body_xml, Body* body) {
    if (!body) return;
    for (const auto& child : body->get_children()) {
        switch (child->node_type()) {
            case NodeType::Paragraph:
                serialize_paragraph_to_xml(body_xml, dynamic_cast<Paragraph*>(child.get()));
                break;
            case NodeType::Table:
                serialize_table_to_xml(body_xml, dynamic_cast<Table*>(child.get()));
                break;
            default:
                break;
        }
    }
}

static void serialize_section_to_xml(pugi::xml_node body_xml, Section* section) {
    if (!section) return;
    
    // Serialize body content
    if (auto body = section->get_body()) {
        serialize_body_to_xml(body_xml, body.get());
    }
    
    // Section properties
    auto sectPr = body_xml.append_child("w:sectPr");
    section->get_properties().applyTo(sectPr);
    
    // Header/footer references
    for (const auto& ref : section->get_header_refs()) {
        auto headerRef = sectPr.append_child("w:headerReference");
        headerRef.append_attribute("r:id").set_value(ref.relationship_id.c_str());
        const char* type_str = "default";
        switch (ref.type) {
            case HeaderFooterType::First: type_str = "first"; break;
            case HeaderFooterType::Even: type_str = "even"; break;
            default: break;
        }
        headerRef.append_attribute("w:type").set_value(type_str);
    }
    for (const auto& ref : section->get_footer_refs()) {
        auto footerRef = sectPr.append_child("w:footerReference");
        footerRef.append_attribute("r:id").set_value(ref.relationship_id.c_str());
        const char* type_str = "default";
        switch (ref.type) {
            case HeaderFooterType::First: type_str = "first"; break;
            case HeaderFooterType::Even: type_str = "even"; break;
            default: break;
        }
        footerRef.append_attribute("w:type").set_value(type_str);
    }
}

// ============================================================================
// Physical -> DOM (Deserialization)
// ============================================================================

void Document::sync_sections_from_physical() {
    auto doc_xml = get_document_xml();
    if (!doc_xml) return;
    
    auto body = doc_xml->child("w:document").child("w:body");
    if (!body) return;
    
    // Clear existing DOM sections
    remove_all_children();
    sections_cache_.clear();
    sections_dirty_ = false;
    
    // Collect section boundaries
    struct SectionRange {
        pugi::xml_node begin;
        pugi::xml_node end;  // points to w:sectPr
    };
    std::vector<SectionRange> ranges;
    
    pugi::xml_node current_begin = body.first_child();
    for (auto node = body.first_child(); node; node = node.next_sibling()) {
        if (std::strcmp(node.name(), "w:sectPr") == 0) {
            ranges.push_back({current_begin, node});
            current_begin = node.next_sibling();
        }
    }
    
    // If no sectPr found, the entire body is one section
    if (ranges.empty() && body.first_child()) {
        ranges.push_back({body.first_child(), pugi::xml_node()});
    }
    
    bool is_first = true;
    for (const auto& range : ranges) {
        auto section = std::make_shared<Section>(this);
        section->set_first_section(is_first);
        is_first = false;
        
        sections_cache_.push_back(section);
        
        auto sect_body = std::make_shared<Body>(this);
        
        // Parse content nodes
        for (auto node = range.begin; node && node != range.end; node = node.next_sibling()) {
            const char* name = node.name();
            if (std::strcmp(name, "w:p") == 0) {
                if (auto para = parse_paragraph_from_xml(node)) {
                    sect_body->append_child(para);
                }
            } else if (std::strcmp(name, "w:tbl") == 0) {
                if (auto table = parse_table_from_xml(node)) {
                    sect_body->append_child(table);
                }
            }
        }
        
        // Load section properties
        if (range.end) {
            section->set_sectPr_node(range.end);
            section->load_properties();
            
            // Parse header/footer references
            for (auto ref = range.end.child("w:headerReference"); ref; ref = ref.next_sibling("w:headerReference")) {
                HeaderFooterRef hf_ref;
                hf_ref.relationship_id = ref.attribute("r:id").value();
                const char* type_val = ref.attribute("w:type").value();
                if (std::strcmp(type_val, "first") == 0) hf_ref.type = HeaderFooterType::First;
                else if (std::strcmp(type_val, "even") == 0) hf_ref.type = HeaderFooterType::Even;
                else hf_ref.type = HeaderFooterType::Default;
                // part_path will be resolved from relationships
                section->add_header_ref(hf_ref);
            }
            for (auto ref = range.end.child("w:footerReference"); ref; ref = ref.next_sibling("w:footerReference")) {
                HeaderFooterRef hf_ref;
                hf_ref.relationship_id = ref.attribute("r:id").value();
                const char* type_val = ref.attribute("w:type").value();
                if (std::strcmp(type_val, "first") == 0) hf_ref.type = HeaderFooterType::First;
                else if (std::strcmp(type_val, "even") == 0) hf_ref.type = HeaderFooterType::Even;
                else hf_ref.type = HeaderFooterType::Default;
                section->add_footer_ref(hf_ref);
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

static void parse_run_format_from_xml(Inline* run, pugi::xml_node run_node) {
    if (!run || !run_node) return;
    
    auto rPr = run_node.child("w:rPr");
    if (!rPr) return;
    
    Font font;
    if (rPr.child("w:b")) font.bold = true;
    if (rPr.child("w:i")) font.italic = true;
    if (rPr.child("w:strike")) font.strikethrough = true;
    
    auto u = rPr.child("w:u");
    if (u) {
        const char* val = u.attribute("w:val").value();
        if (std::strcmp(val, "single") == 0) font.underline = UnderlineType::Single;
        else if (std::strcmp(val, "words") == 0) font.underline = UnderlineType::Words;
        else if (std::strcmp(val, "double") == 0) font.underline = UnderlineType::Double;
        else if (std::strcmp(val, "dotted") == 0) font.underline = UnderlineType::Dotted;
        else if (std::strcmp(val, "dash") == 0) font.underline = UnderlineType::Dash;
        else if (std::strcmp(val, "dashDot") == 0) font.underline = UnderlineType::DashDot;
        else if (std::strcmp(val, "dashDotDot") == 0) font.underline = UnderlineType::DashDotDot;
        else if (std::strcmp(val, "wave") == 0) font.underline = UnderlineType::Wave;
        else if (std::strcmp(val, "thick") == 0) font.underline = UnderlineType::Thick;
        else if (std::strcmp(val, "dottedHeavy") == 0) font.underline = UnderlineType::DottedHeavy;
        else if (std::strcmp(val, "dashHeavy") == 0) font.underline = UnderlineType::DashHeavy;
        else if (std::strcmp(val, "dashDotHeavy") == 0) font.underline = UnderlineType::DashDotHeavy;
        else if (std::strcmp(val, "dashDotDotHeavy") == 0) font.underline = UnderlineType::DashDotDotHeavy;
        else if (std::strcmp(val, "waveHeavy") == 0) font.underline = UnderlineType::WaveHeavy;
        else font.underline = UnderlineType::Single;
    }
    
    auto sz = rPr.child("w:sz");
    if (sz) {
        font.size = sz.attribute("w:val").as_int() / 2.0;
    }
    
    auto rFonts = rPr.child("w:rFonts");
    if (rFonts) {
        font.name = rFonts.attribute("w:ascii").value();
        font.name_far_east = rFonts.attribute("w:eastAsia").value();
    }
    
    auto color = rPr.child("w:color");
    if (color) {
        font.color = Color::from_hex(color.attribute("w:val").value());
    }
    
    auto vAlign = rPr.child("w:vertAlign");
    if (vAlign) {
        const char* val = vAlign.attribute("w:val").value();
        if (std::strcmp(val, "superscript") == 0) font.script_type = ScriptType::Superscript;
        else if (std::strcmp(val, "subscript") == 0) font.script_type = ScriptType::Subscript;
    }
    
    run->set_font(font);
}

std::shared_ptr<Run> Document::parse_run_from_xml(pugi::xml_node run_node) {
    if (!run_node) return nullptr;

    auto run = std::make_shared<Run>(this);

    // Get text content
    auto text_node = run_node.child("w:t");
    if (text_node) {
        run->set_text(text_node.text().get());
    }

    // Parse formatting
    parse_run_format_from_xml(run.get(), run_node);

    // Preserve unknown children (e.g., w:drawing) for round-trip fidelity
    for (auto child = run_node.first_child(); child; child = child.next_sibling()) {
        const char* name = child.name();
        if (std::strcmp(name, "w:t") != 0 && std::strcmp(name, "w:rPr") != 0) {
            run->preserve_child(child);
        }
    }

    return run;
}

std::shared_ptr<Paragraph> Document::parse_paragraph_from_xml(pugi::xml_node para_node) {
    if (!para_node) return nullptr;
    
    auto para = std::make_shared<Paragraph>(this);
    
    // Parse paragraph properties
    auto pPr = para_node.child("w:pPr");
    if (pPr) {
        auto jc = pPr.child("w:jc");
        if (jc) {
            const char* val = jc.attribute("w:val").value();
            if (std::strcmp(val, "center") == 0) para->get_paragraph_format().alignment = ParagraphAlignment::Center;
            else if (std::strcmp(val, "right") == 0) para->get_paragraph_format().alignment = ParagraphAlignment::Right;
            else if (std::strcmp(val, "both") == 0) para->get_paragraph_format().alignment = ParagraphAlignment::Justify;
            else if (std::strcmp(val, "distribute") == 0) para->get_paragraph_format().alignment = ParagraphAlignment::Distributed;
        }
        
        auto ind = pPr.child("w:ind");
        if (ind) {
            para->get_paragraph_format().left_indent = ind.attribute("w:left").as_int() / 20.0;
            para->get_paragraph_format().right_indent = ind.attribute("w:right").as_int() / 20.0;
            para->get_paragraph_format().first_line_indent = ind.attribute("w:firstLine").as_int() / 20.0;
        }
        
        auto spacing = pPr.child("w:spacing");
        if (spacing) {
            para->get_paragraph_format().space_before = spacing.attribute("w:before").as_int() / 20.0;
            para->get_paragraph_format().space_after = spacing.attribute("w:after").as_int() / 20.0;
            const char* line_rule = spacing.attribute("w:lineRule").value();
            int line_value = spacing.attribute("w:line").as_int();
            if (line_value != 0) {
                if (std::strcmp(line_rule, "exact") == 0) {
                    para->get_paragraph_format().line_spacing_rule = LineSpacingRule::Exact;
                    para->get_paragraph_format().line_spacing = line_value / 20.0;
                } else if (std::strcmp(line_rule, "atLeast") == 0) {
                    para->get_paragraph_format().line_spacing_rule = LineSpacingRule::AtLeast;
                    para->get_paragraph_format().line_spacing = line_value / 20.0;
                } else {
                    para->get_paragraph_format().line_spacing_rule = LineSpacingRule::Auto;
                    para->get_paragraph_format().line_spacing = line_value / 240.0;
                }
            }
        }
        
        auto pStyle = pPr.child("w:pStyle");
        if (pStyle) {
            para->get_paragraph_format().style_name = pStyle.attribute("w:val").value();
        }
        
        auto numPr = pPr.child("w:numPr");
        if (numPr) {
            auto ilvl = numPr.child("w:ilvl");
            auto numId = numPr.child("w:numId");
            if (numId) {
                para->get_list_format().list_id = numId.attribute("w:val").as_uint();
                para->get_list_format().level = ilvl ? 
                    static_cast<NumberingLevel>(ilvl.attribute("w:val").as_int()) : NumberingLevel::Level1;
            }
        }
    }
    
    // Parse inline content
    for (auto child = para_node.first_child(); child; child = child.next_sibling()) {
        const char* name = child.name();
        if (std::strcmp(name, "w:r") == 0) {
            auto fld_char = child.child("w:fldChar");
            if (fld_char && std::strcmp(fld_char.attribute("w:fldCharType").value(), "begin") == 0) {
                // Parse field sequence
                auto field = std::make_shared<Field>(this, FieldType::Unknown);
                std::string field_code;
                std::string field_result;
                bool in_result = false;

                for (auto field_child = child; field_child; field_child = field_child.next_sibling()) {
                    if (std::strcmp(field_child.name(), "w:r") != 0) continue;

                    auto fc = field_child.child("w:fldChar");
                    if (fc) {
                        const char* fct = fc.attribute("w:fldCharType").value();
                        if (std::strcmp(fct, "separate") == 0) {
                            in_result = true;
                            continue;
                        } else if (std::strcmp(fct, "end") == 0) {
                            child = field_child;
                            break;
                        } else if (std::strcmp(fct, "begin") == 0) {
                            continue;
                        }
                    }

                    auto instr = field_child.child("w:instrText");
                    if (instr && !in_result) {
                        field_code += instr.text().get();
                    }

                    auto text_node = field_child.child("w:t");
                    if (text_node) {
                        if (in_result) {
                            field_result += text_node.text().get();
                        }
                    }
                }

                field->set_field_code(field_code);
                field->set_result(field_result);
                para->append_child(field);
            } else if (auto run = parse_run_from_xml(child)) {
                para->append_child(run);
            }
        } else if (std::strcmp(name, "w:hyperlink") == 0) {
            auto hyperlink = std::make_shared<Hyperlink>(this);

            const char* rel_id = child.attribute("r:id").value();
            if (rel_id && *rel_id) {
                std::string target = get_relationship_target("word/_rels/document.xml.rels", rel_id);
                if (!target.empty()) {
                    hyperlink->set_address(target);
                }
            }

            const char* anchor = child.attribute("w:anchor").value();
            if (anchor && *anchor) {
                hyperlink->set_bookmark_name(anchor);
            }

            const char* tooltip = child.attribute("w:tooltip").value();
            if (tooltip && *tooltip) {
                hyperlink->set_tooltip(tooltip);
            }

            std::string link_text;
            bool formatting_parsed = false;
            for (auto run_node = child.child("w:r"); run_node; run_node = run_node.next_sibling("w:r")) {
                auto text_node = run_node.child("w:t");
                if (text_node) {
                    link_text += text_node.text().get();
                }
                // Parse formatting from the first run only
                if (!formatting_parsed) {
                    parse_run_format_from_xml(hyperlink.get(), run_node);
                    formatting_parsed = true;
                }
            }
            hyperlink->set_result(link_text);
            para->append_child(hyperlink);
        } else if (std::strcmp(name, "w:br") == 0) {
            const char* type = child.attribute("w:type").value();
            if (std::strcmp(type, "page") == 0) {
                para->append_child(SpecialChar::page_break());
            } else if (std::strcmp(type, "column") == 0) {
                para->append_child(SpecialChar::column_break());
            } else {
                para->append_child(SpecialChar::line_break());
            }
        } else if (std::strcmp(name, "w:tab") == 0) {
            para->append_child(SpecialChar::tab());
        } else if (std::strcmp(name, "w:bookmarkStart") == 0) {
            auto bookmark = std::make_shared<BookmarkStart>(this);
            bookmark->set_id(child.attribute("w:id").as_int());
            bookmark->set_name(child.attribute("w:name").value());
            para->append_child(bookmark);
        } else if (std::strcmp(name, "w:bookmarkEnd") == 0) {
            auto bookmark = std::make_shared<BookmarkEnd>(this);
            bookmark->set_id(child.attribute("w:id").as_int());
            para->append_child(bookmark);
        }
    }
    
    return para;
}

std::shared_ptr<Table> Document::parse_table_from_xml(pugi::xml_node table_node) {
    if (!table_node) return nullptr;
    
    auto table = std::make_shared<Table>(this);
    
    // Parse table properties
    auto tblPr = table_node.child("w:tblPr");
    if (tblPr) {
        auto jc = tblPr.child("w:jc");
        if (jc) {
            const char* val = jc.attribute("w:val").value();
            if (std::strcmp(val, "center") == 0) {
                table->get_table_format().alignment = TableAlignment::Center;
            } else if (std::strcmp(val, "right") == 0) {
                table->get_table_format().alignment = TableAlignment::Right;
            }
        }
        auto tblInd = tblPr.child("w:tblInd");
        if (tblInd) {
            table->get_table_format().left_indent = tblInd.attribute("w:w").as_int() / 20.0;
        }
        auto tblStyle = tblPr.child("w:tblStyle");
        if (tblStyle) {
            table->set_style(tblStyle.attribute("w:val").value());
        }
        auto tblLayout = tblPr.child("w:tblLayout");
        if (tblLayout) {
            const char* layout_type = tblLayout.attribute("w:type").value();
            if (std::strcmp(layout_type, "fixed") == 0) {
                table->get_table_format().auto_fit_behavior = AutoFitBehavior::FixedColumnWidth;
                table->get_table_format().allow_auto_fit = false;
            } else {
                auto tblW = tblPr.child("w:tblW");
                if (tblW) {
                    const char* width_type = tblW.attribute("w:type").value();
                    if (std::strcmp(width_type, "pct") == 0) {
                        table->get_table_format().auto_fit_behavior = AutoFitBehavior::AutoFitToWindow;
                    } else {
                        table->get_table_format().auto_fit_behavior = AutoFitBehavior::AutoFitToContents;
                    }
                } else {
                    table->get_table_format().auto_fit_behavior = AutoFitBehavior::AutoFitToContents;
                }
                table->get_table_format().allow_auto_fit = true;
            }
        }
    }
    
    for (auto tr = table_node.child("w:tr"); tr; tr = tr.next_sibling("w:tr")) {
        auto row = std::make_shared<Row>(this);
        
        // Parse row properties
        auto trPr = tr.child("w:trPr");
        if (trPr) {
            auto trHeight = trPr.child("w:trHeight");
            if (trHeight) {
                row->get_row_format().height = trHeight.attribute("w:val").as_int() / 20.0;
                const char* rule = trHeight.attribute("w:hRule").value();
                row->get_row_format().height_rule_exact = (std::strcmp(rule, "exact") == 0);
            }
            if (trPr.child("w:tblHeader")) {
                row->get_row_format().heading = true;
            }
            if (trPr.child("w:cantSplit")) {
                row->get_row_format().allow_break_across_pages = false;
            }
        }
        
        for (auto tc = tr.child("w:tc"); tc; tc = tc.next_sibling("w:tc")) {
            auto cell = std::make_shared<Cell>(this);
            
            // Parse cell properties
            auto tcPr = tc.child("w:tcPr");
            if (tcPr) {
                auto tcW = tcPr.child("w:tcW");
                if (tcW) {
                    cell->get_cell_format().width = tcW.attribute("w:w").as_int() / 20.0;
                    const char* type_val = tcW.attribute("w:type").value();
                    cell->get_cell_format().preferred_width = (std::strcmp(type_val, "pct") == 0);
                }
                auto vAlign = tcPr.child("w:vAlign");
                if (vAlign) {
                    const char* val = vAlign.attribute("w:val").value();
                    if (std::strcmp(val, "center") == 0) {
                        cell->get_cell_format().vertical_alignment = CellVerticalAlignment::Center;
                    } else if (std::strcmp(val, "bottom") == 0) {
                        cell->get_cell_format().vertical_alignment = CellVerticalAlignment::Bottom;
                    }
                }
                auto gridSpan = tcPr.child("w:gridSpan");
                if (gridSpan) {
                    cell->get_cell_format().horizontal_merge = gridSpan.attribute("w:val").as_int(1);
                    if (cell->get_cell_format().horizontal_merge < 1) {
                        cell->get_cell_format().horizontal_merge = 1;
                    }
                }
                auto vMerge = tcPr.child("w:vMerge");
                if (vMerge) {
                    cell->get_cell_format().vertical_merge = true;
                    const char* vmerge_val = vMerge.attribute("w:val").value();
                    cell->get_cell_format().vertical_merge_start = (std::strcmp(vmerge_val, "restart") == 0);
                }
            }
            
            // Parse cell content
            for (auto child = tc.first_child(); child; child = child.next_sibling()) {
                const char* name = child.name();
                if (std::strcmp(name, "w:p") == 0) {
                    if (auto para = parse_paragraph_from_xml(child)) {
                        cell->append_child(para);
                    }
                } else if (std::strcmp(name, "w:tbl") == 0) {
                    if (auto nested = parse_table_from_xml(child)) {
                        cell->append_child(nested);
                    }
                }
            }
            
            cell->ensure_minimum();
            row->append_child(cell);
        }
        
        table->append_child(row);
    }
    
    return table;
}

std::shared_ptr<Body> Document::parse_body_from_xml(pugi::xml_node body_node) {
    if (!body_node) return nullptr;
    
    auto body = std::make_shared<Body>(this);
    
    // Parse paragraphs and tables (stop at sectPr)
    for (auto node = body_node.first_child(); node; node = node.next_sibling()) {
        const char* name = node.name();
        if (std::strcmp(name, "w:p") == 0) {
            if (auto para = parse_paragraph_from_xml(node)) {
                body->append_child(para);
            }
        } else if (std::strcmp(name, "w:tbl") == 0) {
            if (auto table = parse_table_from_xml(node)) {
                body->append_child(table);
            }
        } else if (std::strcmp(name, "w:sectPr") == 0) {
            break;
        }
    }
    
    return body;
}

// ============================================================================
// Style Serialization Helpers
// ============================================================================

static const char* style_type_to_string(StyleType type) {
    switch (type) {
        case StyleType::Paragraph: return "paragraph";
        case StyleType::Character: return "character";
        case StyleType::Table: return "table";
        case StyleType::List: return "numbering";
        default: return "paragraph";
    }
}

static StyleType string_to_style_type(const char* str) {
    if (std::strcmp(str, "character") == 0) return StyleType::Character;
    if (std::strcmp(str, "table") == 0) return StyleType::Table;
    if (std::strcmp(str, "numbering") == 0) return StyleType::List;
    return StyleType::Paragraph;
}

static void serialize_style_paragraph_format_to_xml(pugi::xml_node pPr, const ParagraphFormat& format) {
    if (format.alignment != ParagraphAlignment::Left) {
        auto jc = pPr.append_child("w:jc");
        const char* val = "left";
        switch (format.alignment) {
            case ParagraphAlignment::Center: val = "center"; break;
            case ParagraphAlignment::Right: val = "right"; break;
            case ParagraphAlignment::Justify: val = "both"; break;
            case ParagraphAlignment::Distributed: val = "distribute"; break;
            default: break;
        }
        jc.append_attribute("w:val").set_value(val);
    }

    if (format.left_indent != 0 || format.right_indent != 0 || format.first_line_indent != 0) {
        auto ind = pPr.append_child("w:ind");
        if (format.left_indent != 0) {
            ind.append_attribute("w:left").set_value(static_cast<int>(format.left_indent * 20));
        }
        if (format.right_indent != 0) {
            ind.append_attribute("w:right").set_value(static_cast<int>(format.right_indent * 20));
        }
        if (format.first_line_indent != 0) {
            ind.append_attribute("w:firstLine").set_value(static_cast<int>(format.first_line_indent * 20));
        }
    }

    if (format.space_before != 0 || format.space_after != 0 || format.line_spacing != 1.15) {
        auto spacing = pPr.append_child("w:spacing");
        if (format.space_before != 0) {
            spacing.append_attribute("w:before").set_value(static_cast<int>(format.space_before * 20));
        }
        if (format.space_after != 0) {
            spacing.append_attribute("w:after").set_value(static_cast<int>(format.space_after * 20));
        }
        if (format.line_spacing != 1.15) {
            const char* rule = "auto";
            int line_value = static_cast<int>(format.line_spacing * 240);
            if (format.line_spacing_rule == LineSpacingRule::Exact) {
                rule = "exact";
                line_value = static_cast<int>(format.line_spacing * 20);
            } else if (format.line_spacing_rule == LineSpacingRule::AtLeast) {
                rule = "atLeast";
                line_value = static_cast<int>(format.line_spacing * 20);
            }
            spacing.append_attribute("w:lineRule").set_value(rule);
            spacing.append_attribute("w:line").set_value(line_value);
        }
    }
}

static void parse_font_from_xml(pugi::xml_node rPr, Font& font) {
    if (!rPr) return;

    if (rPr.child("w:b")) font.bold = true;
    if (rPr.child("w:i")) font.italic = true;
    if (rPr.child("w:strike")) font.strikethrough = true;

    auto u = rPr.child("w:u");
    if (u) {
        const char* val = u.attribute("w:val").value();
        if (std::strcmp(val, "single") == 0) font.underline = UnderlineType::Single;
        else if (std::strcmp(val, "words") == 0) font.underline = UnderlineType::Words;
        else if (std::strcmp(val, "double") == 0) font.underline = UnderlineType::Double;
        else if (std::strcmp(val, "dotted") == 0) font.underline = UnderlineType::Dotted;
        else if (std::strcmp(val, "dash") == 0) font.underline = UnderlineType::Dash;
        else if (std::strcmp(val, "dashDot") == 0) font.underline = UnderlineType::DashDot;
        else if (std::strcmp(val, "dashDotDot") == 0) font.underline = UnderlineType::DashDotDot;
        else if (std::strcmp(val, "wave") == 0) font.underline = UnderlineType::Wave;
        else if (std::strcmp(val, "thick") == 0) font.underline = UnderlineType::Thick;
        else if (std::strcmp(val, "dottedHeavy") == 0) font.underline = UnderlineType::DottedHeavy;
        else if (std::strcmp(val, "dashHeavy") == 0) font.underline = UnderlineType::DashHeavy;
        else if (std::strcmp(val, "dashDotHeavy") == 0) font.underline = UnderlineType::DashDotHeavy;
        else if (std::strcmp(val, "dashDotDotHeavy") == 0) font.underline = UnderlineType::DashDotDotHeavy;
        else if (std::strcmp(val, "waveHeavy") == 0) font.underline = UnderlineType::WaveHeavy;
        else font.underline = UnderlineType::Single;
    }

    auto sz = rPr.child("w:sz");
    if (sz) {
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
        const char* val = vAlign.attribute("w:val").value();
        if (std::strcmp(val, "superscript") == 0) font.script_type = ScriptType::Superscript;
        else if (std::strcmp(val, "subscript") == 0) font.script_type = ScriptType::Subscript;
    }
}

static void parse_style_paragraph_format_from_xml(pugi::xml_node pPr, ParagraphFormat& format) {
    if (!pPr) return;

    auto jc = pPr.child("w:jc");
    if (jc) {
        const char* val = jc.attribute("w:val").value();
        if (std::strcmp(val, "center") == 0) format.alignment = ParagraphAlignment::Center;
        else if (std::strcmp(val, "right") == 0) format.alignment = ParagraphAlignment::Right;
        else if (std::strcmp(val, "both") == 0) format.alignment = ParagraphAlignment::Justify;
        else if (std::strcmp(val, "distribute") == 0) format.alignment = ParagraphAlignment::Distributed;
    }

    auto ind = pPr.child("w:ind");
    if (ind) {
        format.left_indent = ind.attribute("w:left").as_int() / 20.0;
        format.right_indent = ind.attribute("w:right").as_int() / 20.0;
        format.first_line_indent = ind.attribute("w:firstLine").as_int() / 20.0;
    }

    auto spacing = pPr.child("w:spacing");
    if (spacing) {
        format.space_before = spacing.attribute("w:before").as_int() / 20.0;
        format.space_after = spacing.attribute("w:after").as_int() / 20.0;
        const char* line_rule = spacing.attribute("w:lineRule").value();
        int line_value = spacing.attribute("w:line").as_int();
        if (line_value != 0) {
            if (std::strcmp(line_rule, "exact") == 0) {
                format.line_spacing_rule = LineSpacingRule::Exact;
                format.line_spacing = line_value / 20.0;
            } else if (std::strcmp(line_rule, "atLeast") == 0) {
                format.line_spacing_rule = LineSpacingRule::AtLeast;
                format.line_spacing = line_value / 20.0;
            } else {
                format.line_spacing_rule = LineSpacingRule::Auto;
                format.line_spacing = line_value / 240.0;
            }
        }
    }
}

static void serialize_style_to_xml(pugi::xml_node styles_root, const Style& style) {
    auto style_xml = styles_root.append_child("w:style");
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

    // Serialize font formatting as w:rPr
    const Font& font = style.get_font();
    bool has_font_formatting = font.bold || font.italic || font.strikethrough ||
                               font.underline != UnderlineType::None || font.size > 0 ||
                               !font.name.empty() || font.color != Color::auto_color() ||
                               font.script_type != ScriptType::Normal;

    if (has_font_formatting) {
        auto run_xml = style_xml.append_child("w:r");
        serialize_run_formatting_to_xml(run_xml, font);
        // Move w:rPr from w:r to directly under w:style
        auto rPr = run_xml.child("w:rPr");
        if (rPr) {
            style_xml.insert_move_after(rPr, style_xml.last_child());
            run_xml.parent().remove_child(run_xml);
        }
    }

    // Serialize paragraph formatting as w:pPr (for paragraph and table styles)
    const ParagraphFormat& para_format = style.get_paragraph_format();
    bool has_para_format = para_format.alignment != ParagraphAlignment::Left ||
                          para_format.left_indent != 0 || para_format.right_indent != 0 ||
                          para_format.first_line_indent != 0 || para_format.space_before != 0 ||
                          para_format.space_after != 0 || para_format.line_spacing != 1.15;

    if (has_para_format) {
        auto pPr = style_xml.append_child("w:pPr");
        serialize_style_paragraph_format_to_xml(pPr, para_format);
    }
}

static std::shared_ptr<Style> parse_style_from_xml(pugi::xml_node style_node, Document* doc) {
    if (!style_node) return nullptr;

    auto style = std::make_shared<Style>(doc, string_to_style_type(style_node.attribute("w:type").value()));
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
    }

    auto pPr = style_node.child("w:pPr");
    if (pPr) {
        ParagraphFormat format;
        parse_style_paragraph_format_from_xml(pPr, format);
        style->set_paragraph_format(format);
    }

    return style;
}

// ============================================================================
// Style Sync Methods
// ============================================================================

void Document::sync_styles_to_physical() {
    pugi::xml_document* styles_doc = get_styles();
    if (!styles_doc) {
        styles_doc = &create_xml_part("word/styles.xml");
        add_content_type_override("/word/styles.xml",
            "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml");
    }

    styles_doc->reset();
    auto root = styles_doc->append_child("w:styles");
    root.append_attribute("xmlns:w").set_value(
        "http://schemas.openxmlformats.org/wordprocessingml/2006/main");

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
    if (!styles_root) return;

    for (auto style_node = styles_root.child("w:style"); style_node;
         style_node = style_node.next_sibling("w:style")) {
        if (auto style = parse_style_from_xml(style_node, this)) {
            if (styles_) {
                styles_->add(style);
            }
        }
    }
}

} // namespace cdocx

