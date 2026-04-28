/**
 * @file document_builder.cpp
 * @brief DocumentBuilder and image utility implementation
 * @since 0.3.0
 */

#include "sync_common.h"

#include <cdocx/document_builder.h>
#include <cdocx/document.h>
#include <cdocx/footnote.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <vector>

namespace cdocx {

namespace {

struct BreakTypeMapping {
    BreakType type;
    const char* xml_value;
};

static const BreakTypeMapping kBreakTypeMappings[] = {
    {BreakType::PageBreak, "page"},
    {BreakType::ColumnBreak, "column"},
    {BreakType::SectionBreakNextPage, "nextPage"},
    {BreakType::SectionBreakContinuous, "continuous"},
    {BreakType::SectionBreakEvenPage, "evenPage"},
    {BreakType::SectionBreakOddPage, "oddPage"},
};

static const char* break_type_to_string(BreakType type) {
    for (const auto& mapping : kBreakTypeMappings) {
        if (mapping.type == type) {
            return mapping.xml_value;
        }
    }
    return nullptr;
}

}  // namespace

// DocumentBuilder Implementation
// ============================================================================

DocumentBuilder::DocumentBuilder(Document* doc)
    : doc_(doc), target_xml_doc_(doc ? doc->get_document_xml() : nullptr) {}

DocumentBuilder::DocumentBuilder(const std::shared_ptr<Document>& doc)
    : doc_sptr_(doc), doc_(doc.get()), target_xml_doc_(doc.get() ? doc->get_document_xml() : nullptr) {}

DocumentBuilder::~DocumentBuilder() = default;

void DocumentBuilder::ensure_paragraph() {
    if (!current_paragraph_ || !is_para_node(current_paragraph_.name())) {
        pugi::xml_node body = get_body();
        const pugi::xml_node sect_pr = body.child("w:sectPr");
        if (sect_pr) {
            current_paragraph_ = body.insert_child_before("w:p", sect_pr);
        } else {
            current_paragraph_ = body.append_child("w:p");
        }
        current_node_ = current_paragraph_;
        if (doc_) {
            doc_->mark_xml_paragraph_dirty(current_paragraph_);
        }
    }
}

pugi::xml_node DocumentBuilder::get_body() {
    pugi::xml_document* doc_xml = target_xml_doc_ ? target_xml_doc_ : doc_->get_document_xml();
    if (!doc_xml) {
        return pugi::xml_node{};
    }
    pugi::xml_node root = doc_xml->first_child();
    if (!root) {
        return pugi::xml_node{};
    }
    // document.xml has w:document -> w:body, header/footer XML has w:hdr/w:ftr directly
    if (std::strcmp(root.name(), "w:document") == 0) {
        return root.child("w:body");
    }
    if (std::strcmp(root.name(), "w:hdr") == 0 || std::strcmp(root.name(), "w:ftr") == 0) {
        return root;
    }
    return pugi::xml_node{};
}

void DocumentBuilder::apply_formatting(pugi::xml_node run) const {
    if (!run) {
        return;
    }

    pugi::xml_node r_pr = run.child("w:rPr");
    if (!r_pr) {
        r_pr = run.prepend_child("w:rPr");
    }

    // Apply formatting flags
    if (format_.bold) {
        ensure_child(r_pr, "w:b");
    }
    if (format_.italic) {
        ensure_child(r_pr, "w:i");
    }
    if (format_.underline) {
        pugi::xml_node u = ensure_child(r_pr, "w:u");
        u.append_attribute("w:val").set_value("single");
    }
    if (format_.strikethrough) {
        ensure_child(r_pr, "w:strike");
    }
    if (!format_.font_name.empty()) {
        pugi::xml_node r_fonts = r_pr.child("w:rFonts");
        if (!r_fonts) {
            r_fonts = r_pr.append_child("w:rFonts");
        }
        r_fonts.append_attribute("w:ascii").set_value(format_.font_name.c_str());
        r_fonts.append_attribute("w:hAnsi").set_value(format_.font_name.c_str());
    }
    if (format_.font_size > 0) {
        pugi::xml_node sz = r_pr.child("w:sz");
        if (!sz) {
            sz = r_pr.append_child("w:sz");
        }
        sz.append_attribute("w:val").set_value(format_.font_size * 2);
    }
    if (!format_.color.empty()) {
        pugi::xml_node color = r_pr.child("w:color");
        if (!color) {
            color = r_pr.append_child("w:color");
        }
        color.append_attribute("w:val").set_value(format_.color.c_str());
    }
}

// Navigation
DocumentBuilder& DocumentBuilder::move_to_document_start() {
    const pugi::xml_node body = get_body();
    current_paragraph_ = body.child("w:p");
    current_node_ = current_paragraph_;
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_document_end() {
    const pugi::xml_node body = get_body();
    // Find the last w:p node, not just any last child
    pugi::xml_node last_para;
    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        last_para = para;
    }
    current_paragraph_ = last_para;
    current_node_ = current_paragraph_;
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_paragraph(size_t index) {
    move_to_paragraph(index, 0);
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_paragraph(size_t paragraph_index,
                                                    size_t character_index) {
    const pugi::xml_node body = get_body();
    size_t count = 0;

    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (count == paragraph_index) {
            current_paragraph_ = para;
            // Find run containing the character index
            size_t char_count = 0;
            for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
                const pugi::xml_node t = run.child("w:t");
                if (t) {
                    const size_t text_len = std::strlen(t.text().get());
                    if (char_count + text_len >= character_index) {
                        current_node_ = run;
                        return *this;
                    }
                    char_count += text_len;
                }
            }
            current_node_ = para;
            return *this;
        }
        count++;
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_section(size_t index) {
    auto sections = doc_->get_sections();
    if (index >= sections.get_count()) {
        return *this;
    }

    auto body = sections[static_cast<int>(index)]->get_body();
    if (!body) {
        return *this;
    }

    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        return *this;
    }

    const pugi::xml_node xml_body = doc_xml->child("w:document").child("w:body");
    size_t sect_count = 0;
    for (pugi::xml_node para = xml_body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (sect_count == index) {
            current_paragraph_ = para;
            current_node_ = para;
            target_xml_doc_ = doc_xml;
            return *this;
        }
        // Check if this paragraph ends a section
        if (para.child("w:sectPr")) {
            sect_count++;
            if (sect_count == index) {
                const pugi::xml_node next = para.next_sibling();
                if (next && is_para_node(next.name())) {
                    current_paragraph_ = next;
                    current_node_ = next;
                } else {
                    current_paragraph_ = para;
                    current_node_ = para;
                }
                target_xml_doc_ = doc_xml;
                return *this;
            }
        }
    }
    // If no section breaks found, just move to first paragraph
    if (index == 0) {
        current_paragraph_ = xml_body.child("w:p");
        current_node_ = current_paragraph_;
        target_xml_doc_ = doc_xml;
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_bookmark(const std::string& name) {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        return *this;
    }

    for (pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p"); para;
         para = para.next_sibling("w:p")) {
        for (pugi::xml_node bm = para.child("w:bookmarkStart"); bm;
             bm = bm.next_sibling("w:bookmarkStart")) {
            const pugi::xml_attribute name_attr = bm.attribute("w:name");
            if (name_attr && name_attr.value() == name) {
                target_xml_doc_ = doc_xml;
                current_paragraph_ = para;
                current_node_ = bm;
                return *this;
            }
        }
        // Also search inside runs
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            for (pugi::xml_node bm = run.child("w:bookmarkStart"); bm;
                 bm = bm.next_sibling("w:bookmarkStart")) {
                const pugi::xml_attribute name_attr = bm.attribute("w:name");
                if (name_attr && name_attr.value() == name) {
                    target_xml_doc_ = doc_xml;
                    current_paragraph_ = para;
                    current_node_ = run;
                    return *this;
                }
            }
        }
    }
    return *this;
}

bool DocumentBuilder::move_to_merge_field(const std::string& field_name) {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        return false;
    }

    const std::string target_code = "MERGEFIELD " + field_name;

    for (pugi::xml_node para = doc_xml->child("w:document").child("w:body").child("w:p"); para;
         para = para.next_sibling("w:p")) {
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            const pugi::xml_node fld_char = run.child("w:fldChar");
            if (fld_char &&
                std::strcmp(fld_char.attribute("w:fldCharType").value(), "begin") == 0) {
                std::string field_code;
                if (walk_field_sequence(run, &field_code, nullptr)) {
                    const std::string trimmed = trim_whitespace(field_code);
                    if (trimmed.find(target_code) == 0) {
                        target_xml_doc_ = doc_xml;
                        current_paragraph_ = para;
                        current_node_ = run;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

DocumentBuilder& DocumentBuilder::move_to_cell(size_t table_index,
                                               size_t row_index,
                                               size_t cell_index) {
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        return *this;
    }

    const pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    size_t t_idx = 0;
    for (pugi::xml_node tbl = body.child("w:tbl"); tbl; tbl = tbl.next_sibling("w:tbl")) {
        if (t_idx == table_index) {
            size_t r_idx = 0;
            for (pugi::xml_node tr = tbl.child("w:tr"); tr; tr = tr.next_sibling("w:tr")) {
                if (r_idx == row_index) {
                    size_t c_idx = 0;
                    for (pugi::xml_node tc = tr.child("w:tc"); tc; tc = tc.next_sibling("w:tc")) {
                        if (c_idx == cell_index) {
                            target_xml_doc_ = doc_xml;
                            current_table_ = tbl;
                            current_row_ = tr;
                            current_cell_ = tc;
                            current_paragraph_ = tc.child("w:p");
                            if (!current_paragraph_) {
                                current_paragraph_ = tc.append_child("w:p");
                            }
                            current_node_ = current_paragraph_;
                            in_table_ = true;
                            return *this;
                        }
                        ++c_idx;
                    }
                }
                ++r_idx;
            }
        }
        ++t_idx;
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::move_to_header_footer(HeaderFooterType type) {
    auto sect = doc_->get_first_section();
    if (!sect) {
        return *this;
    }

    std::shared_ptr<HeaderFooter> hf;
    if (sect->has_header(type)) {
        hf = sect->get_header(type);
    } else {
        hf = sect->add_header(type);
    }
    if (!hf) {
        return *this;
    }

    // Find the header XML document via relationship
    auto header_names = doc_->get_header_names();
    for (size_t i = 0; i < header_names.size(); ++i) {
        // This is a simplified match; in practice we'd match by relationship
        pugi::xml_document* header_doc = doc_->get_header(static_cast<int>(i));
        if (header_doc) {
            target_xml_doc_ = header_doc;
            pugi::xml_node hdr = header_doc->child("w:hdr");
            current_paragraph_ = hdr.child("w:p");
            if (!current_paragraph_) {
                current_paragraph_ = hdr.append_child("w:p");
            }
            current_node_ = current_paragraph_;
            current_table_ = pugi::xml_node();
            current_row_ = pugi::xml_node();
            current_cell_ = pugi::xml_node();
            in_table_ = false;
            return *this;
        }
    }
    return *this;
}

// Text Insertion
DocumentBuilder& DocumentBuilder::write(const std::string& text) {
    ensure_paragraph();

    pugi::xml_node run = current_paragraph_.append_child("w:r");
    apply_formatting(run);

    const pugi::xml_node t = run.append_child("w:t");
    t.text().set(text.c_str());

    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return *this;
}

DocumentBuilder& DocumentBuilder::writeln(const std::string& text) {
    write(text);
    insert_break(BreakType::ParagraphBreak);
    return *this;
}

DocumentBuilder& DocumentBuilder::writeln() {
    insert_break(BreakType::ParagraphBreak);
    return *this;
}

Paragraph* DocumentBuilder::insert_paragraph() {
    pugi::xml_node body = get_body();
    const pugi::xml_node sect_pr = body.child("w:sectPr");
    if (sect_pr) {
        current_paragraph_ = body.insert_child_before("w:p", sect_pr);
    } else {
        current_paragraph_ = body.append_child("w:p");
    }
    current_node_ = current_paragraph_;

    // Return pointer to a new Paragraph object
    // Note: This creates a memory management issue - needs proper handling
    static Paragraph* para = nullptr;
    delete para;
    para = new Paragraph();
    para->set_current(current_paragraph_);
    return para;
}

DocumentBuilder& DocumentBuilder::insert_break() {
    insert_break(BreakType::PageBreak);
    return *this;
}

DocumentBuilder& DocumentBuilder::insert_break(BreakType break_type) {
    switch (break_type) {
        case BreakType::ParagraphBreak: {
            pugi::xml_node body = get_body();
            const pugi::xml_node sect_pr = body.child("w:sectPr");
            if (sect_pr) {
                current_paragraph_ = body.insert_child_before("w:p", sect_pr);
            } else {
                current_paragraph_ = body.append_child("w:p");
            }
            current_node_ = current_paragraph_;
            break;
        }
        case BreakType::PageBreak:
        case BreakType::ColumnBreak:
        case BreakType::SectionBreakNextPage:
        case BreakType::SectionBreakContinuous:
        case BreakType::SectionBreakEvenPage:
        case BreakType::SectionBreakOddPage: {
            ensure_paragraph();
            pugi::xml_node run = current_paragraph_.append_child("w:r");
            pugi::xml_node br = run.append_child("w:br");
            if (const char* typeval = break_type_to_string(break_type)) {
                br.append_attribute("w:type").set_value(typeval);
            }
            break;
        }
        case BreakType::LineBreak: {
            ensure_paragraph();
            pugi::xml_node run = current_paragraph_.append_child("w:r");
            run.append_child("w:br");
            break;
        }
    }
    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return *this;
}

std::shared_ptr<Footnote> DocumentBuilder::insert_footnote(FootnoteType type,
                                                           const std::string& text) {
    return insert_footnote(type, text, "");
}

std::shared_ptr<Footnote> DocumentBuilder::insert_footnote(FootnoteType type,
                                                           const std::string& text,
                                                           const std::string& reference_mark) {
    ensure_paragraph();
    if (!doc_) {
        return nullptr;
    }

    std::shared_ptr<Footnote> footnote;
    if (type == FootnoteType::Endnote) {
        footnote = doc_->add_endnote(text, reference_mark);
    } else {
        footnote = doc_->add_footnote(text, reference_mark);
    }
    if (!footnote) {
        return nullptr;
    }

    const int id = footnote->get_id();

    // Insert footnote reference in current paragraph
    pugi::xml_node run = current_paragraph_.append_child("w:r");
    pugi::xml_node ref = run.append_child(type == FootnoteType::Endnote ? "w:endnoteReference"
                                                                        : "w:footnoteReference");
    ref.append_attribute("w:id").set_value(id);
    if (!reference_mark.empty()) {
        ref.append_attribute("w:customMarkFollows").set_value("1");
        pugi::xml_node mark_run = current_paragraph_.append_child("w:r");
        const pugi::xml_node mark_t = mark_run.append_child("w:t");
        mark_t.text().set(reference_mark.c_str());
    }

    doc_->mark_xml_paragraph_dirty(current_paragraph_);
    return footnote;
}

namespace {

struct FieldTypeMapping {
    FieldType type;
    const char* code;
    const char* result;
};

static const FieldTypeMapping kFieldTypeMappings[] = {
    {FieldType::Page, "PAGE", "1"},
    {FieldType::NumPages, "NUMPAGES", "1"},
    {FieldType::Date, "DATE", ""},
    {FieldType::Time, "TIME", ""},
    {FieldType::CreateDate, "CREATEDATE", ""},
    {FieldType::SaveDate, "SAVEDATE", ""},
    {FieldType::Author, "AUTHOR", ""},
    {FieldType::Title, "TITLE", ""},
    {FieldType::Subject, "SUBJECT", ""},
    {FieldType::Keywords, "KEYWORDS", ""},
    {FieldType::FileName, "FILENAME", ""},
    {FieldType::FileSize, "FILESIZE", "0"},
    {FieldType::NumWords, "NUMWORDS", "0"},
    {FieldType::NumChars, "NUMCHARS", "0"},
    {FieldType::Ref, "REF", ""},
    {FieldType::PageRef, "PAGEREF", ""},
    {FieldType::Formula, "=", ""},
};

const FieldTypeMapping* find_field_mapping(FieldType type) {
    for (const auto& m : kFieldTypeMappings) {
        if (m.type == type) {
            return &m;
        }
    }
    return nullptr;
}

}  // anonymous namespace

std::shared_ptr<Field> DocumentBuilder::insert_field(FieldType field_type, bool /*update_field*/) {
    auto field = std::make_shared<Field>(doc_, field_type);
    const auto* mapping = find_field_mapping(field_type);
    if (mapping) {
        field->set_field_code(mapping->code);
        field->set_result(mapping->result);
    } else {
        field->set_field_code("PAGE");
    }
    return insert_field_node(field);
}

std::shared_ptr<Field> DocumentBuilder::insert_field(const std::string& field_code) {
    return insert_field(field_code, "");
}

std::shared_ptr<Field> DocumentBuilder::insert_field(const std::string& field_code,
                                                     const std::string& field_value) {
    auto field = std::make_shared<Field>(doc_, FieldType::Unknown);
    field->set_field_code(field_code);
    field->set_result(field_value);
    return insert_field_node(field);
}

std::shared_ptr<Field> DocumentBuilder::insert_field_node(const std::shared_ptr<Field>& field) {
    ensure_paragraph();
    if (!field) {
        return nullptr;
    }

    pugi::xml_node run_start = current_paragraph_.append_child("w:r");
    pugi::xml_node fld_char_start = run_start.append_child("w:fldChar");
    fld_char_start.append_attribute("w:fldCharType").set_value("begin");

    const std::string full_code = field->get_full_field_code();
    if (!full_code.empty()) {
        pugi::xml_node run_instr = current_paragraph_.append_child("w:r");
        pugi::xml_node instr_text = run_instr.append_child("w:instrText");
        instr_text.append_attribute("xml:space").set_value("preserve");
        instr_text.text().set((" " + full_code + " \\* MERGEFORMAT").c_str());
    }

    pugi::xml_node run_sep = current_paragraph_.append_child("w:r");
    pugi::xml_node fld_char_sep = run_sep.append_child("w:fldChar");
    fld_char_sep.append_attribute("w:fldCharType").set_value("separate");

    const std::string result = field->get_result();
    if (!result.empty()) {
        pugi::xml_node run_result = current_paragraph_.append_child("w:r");
        const pugi::xml_node t = run_result.append_child("w:t");
        t.text().set(result.c_str());
    }

    pugi::xml_node run_end = current_paragraph_.append_child("w:r");
    pugi::xml_node fld_char_end = run_end.append_child("w:fldChar");
    fld_char_end.append_attribute("w:fldCharType").set_value("end");

    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return field;
}

std::shared_ptr<Field> DocumentBuilder::insert_page_number(const std::string& switches) {
    auto field = std::make_shared<Field>(doc_, FieldType::Page);
    field->set_field_code("PAGE");
    field->set_result("1");
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    return insert_field_node(field);
}

std::shared_ptr<Field> DocumentBuilder::insert_num_pages() {
    return insert_field(FieldType::NumPages);
}

std::shared_ptr<Field> DocumentBuilder::insert_date(const std::string& switches) {
    auto field = std::make_shared<Field>(doc_, FieldType::Date);
    field->set_field_code("DATE");
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    return insert_field_node(field);
}

std::shared_ptr<Field> DocumentBuilder::insert_time(const std::string& switches) {
    auto field = std::make_shared<Field>(doc_, FieldType::Time);
    field->set_field_code("TIME");
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    return insert_field_node(field);
}

std::shared_ptr<Field> DocumentBuilder::insert_merge_field(const std::string& field_name,
                                                           const std::string& switches) {
    auto field = std::make_shared<Field>(doc_, FieldType::Unknown);
    field->set_field_code("MERGEFIELD " + field_name);
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    return insert_field_node(field);
}

std::shared_ptr<Field> DocumentBuilder::insert_table_of_contents(const std::string& switches) {
    ensure_paragraph();

    auto field = std::make_shared<Field>(doc_, FieldType::Unknown);
    field->set_field_code("TOC");
    field->set_result("\nClick here to update table of contents.\n");
    if (!switches.empty()) {
        field->add_switch(switches);
    }

    const std::string full_code = field->get_full_field_code();

    pugi::xml_node run_start = current_paragraph_.append_child("w:r");
    pugi::xml_node fld_char_start = run_start.append_child("w:fldChar");
    fld_char_start.append_attribute("w:fldCharType").set_value("begin");

    pugi::xml_node run_instr = current_paragraph_.append_child("w:r");
    pugi::xml_node instr_text = run_instr.append_child("w:instrText");
    instr_text.append_attribute("xml:space").set_value("preserve");
    instr_text.text().set((" " + full_code + " \\h").c_str());

    pugi::xml_node run_sep = current_paragraph_.append_child("w:r");
    pugi::xml_node fld_char_sep = run_sep.append_child("w:fldChar");
    fld_char_sep.append_attribute("w:fldCharType").set_value("separate");

    pugi::xml_node run_result = current_paragraph_.append_child("w:r");
    const pugi::xml_node t = run_result.append_child("w:t");
    t.text().set(field->get_result().c_str());

    pugi::xml_node run_end = current_paragraph_.append_child("w:r");
    pugi::xml_node fld_char_end = run_end.append_child("w:fldChar");
    fld_char_end.append_attribute("w:fldCharType").set_value("end");

    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return field;
}

// Formatting
DocumentBuilder& DocumentBuilder::set_bold(bool value) {
    format_.bold = value;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_italic(bool value) {
    format_.italic = value;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_underline(bool value) {
    format_.underline = value;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_strikethrough(bool value) {
    format_.strikethrough = value;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_font_name(const std::string& name) {
    format_.font_name = name;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_font_size(int size) {
    format_.font_size = size;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_color(const std::string& color_hex) {
    format_.color = color_hex;
    return *this;
}
DocumentBuilder& DocumentBuilder::set_alignment(const std::string& alignment) {
    format_.alignment = alignment;
    return *this;
}

DocumentBuilder& DocumentBuilder::clear_formatting() {
    format_ = FormattingState();
    return *this;
}

// Table Building
DocumentBuilder& DocumentBuilder::start_table() {
    pugi::xml_node body = get_body();
    const pugi::xml_node sect_pr = body.child("w:sectPr");
    if (sect_pr) {
        current_table_ = body.insert_child_before("w:tbl", sect_pr);
    } else {
        current_table_ = body.append_child("w:tbl");
    }
    in_table_ = true;

    // Add table properties
    pugi::xml_node tbl_pr = current_table_.append_child("w:tblPr");
    pugi::xml_node tbl_w = tbl_pr.append_child("w:tblW");
    tbl_w.append_attribute("w:w").set_value("5000");
    tbl_w.append_attribute("w:type").set_value("pct");
    return *this;
}

DocumentBuilder& DocumentBuilder::end_table() {
    in_table_ = false;
    current_table_ = pugi::xml_node();
    current_row_ = pugi::xml_node();
    current_cell_ = pugi::xml_node();
    return *this;
}

DocumentBuilder& DocumentBuilder::insert_row() {
    if (!in_table_) {
        return *this;
    }
    current_row_ = current_table_.append_child("w:tr");
    return *this;
}

DocumentBuilder& DocumentBuilder::insert_cell() {
    if (!in_table_ || !current_row_) {
        return *this;
    }
    current_cell_ = current_row_.append_child("w:tc");

    // Add cell properties
    pugi::xml_node tc_pr = current_cell_.append_child("w:tcPr");
    pugi::xml_node tc_w = tc_pr.append_child("w:tcW");
    tc_w.append_attribute("w:w").set_value("0");
    tc_w.append_attribute("w:type").set_value("auto");

    // Add empty paragraph
    current_paragraph_ = current_cell_.append_child("w:p");
    return *this;
}

DocumentBuilder& DocumentBuilder::end_row() {
    current_row_ = pugi::xml_node();
    current_cell_ = pugi::xml_node();
    return *this;
}

// Hyperlink
DocumentBuilder& DocumentBuilder::insert_hyperlink(const std::string& text,
                                                   const std::string& url) {
    ensure_paragraph();

    if (!doc_ || url.empty()) {
        write(text);
        return *this;
    }

    // Create relationship for the hyperlink
    std::string rel_id = doc_->find_relationship_id("word/_rels/document.xml.rels", url);
    if (rel_id.empty()) {
        rel_id = doc_->add_relationship(
            "word/_rels/document.xml.rels",
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink",
            url,
            "External");
    }

    // Create hyperlink element
    pugi::xml_node hyperlink = current_paragraph_.append_child("w:hyperlink");
    hyperlink.append_attribute("r:id").set_value(rel_id.c_str());

    // Create run with text and apply current formatting
    pugi::xml_node run = hyperlink.append_child("w:r");
    apply_formatting(run);

    const pugi::xml_node t = run.append_child("w:t");
    t.text().set(text.c_str());
    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return *this;
}

// Bookmark
DocumentBuilder& DocumentBuilder::start_bookmark(const std::string& name) {
    if (!doc_) {
        return *this;
    }

    ensure_paragraph();

    // Generate unique bookmark ID
    const int bookmark_id = doc_->generate_unique_bookmark_id();

    // Store bookmark ID for later matching with end_bookmark
    bookmark_stack_[name] = bookmark_id;

    // Create bookmark_start element
    pugi::xml_node bookmark_start = current_paragraph_.append_child("w:bookmarkStart");
    bookmark_start.append_attribute("w:id").set_value(bookmark_id);
    bookmark_start.append_attribute("w:name").set_value(name.c_str());
    return *this;
}

DocumentBuilder& DocumentBuilder::end_bookmark(const std::string& name) {
    if (!doc_) {
        return *this;
    }

    ensure_paragraph();

    // Find the bookmark ID from the stack
    auto it = bookmark_stack_.find(name);
    if (it == bookmark_stack_.end()) {
        // No matching start_bookmark called
        return *this;
    }

    const int bookmark_id = it->second;
    bookmark_stack_.erase(it);

    // Create bookmark_end element
    pugi::xml_node bookmark_end = current_paragraph_.append_child("w:bookmarkEnd");
    bookmark_end.append_attribute("w:id").set_value(bookmark_id);
    return *this;
}

// Image
bool DocumentBuilder::insert_image(const std::string& image_path, double width, double height) {
    if (!doc_) {
        return false;
    }

    namespace fs = std::filesystem;
    if (!fs::exists(image_path)) {
        return false;
    }

    // Detect image size if not provided
    ImageSize size;
    if (width <= 0 || height <= 0) {
        if (!detect_image_size(image_path, size)) {
            return false;
        }
    } else {
        size = ImageSize(width, height);
    }

    // Add media and get relationship
    const std::string rel_id = doc_->add_media_with_rel(image_path, nullptr);
    if (rel_id.empty()) {
        return false;
    }

    ensure_paragraph();

    // Create run with drawing
    pugi::xml_node run = current_paragraph_.append_child("w:r");
    static int image_id_counter = 1;
    append_image_drawing(run, rel_id, size, ImageAlignment::Center,
                         image_id_counter++, image_path);

    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return true;
}

// Form Fields

std::shared_ptr<FormField> DocumentBuilder::insert_form_field_impl(
    const std::shared_ptr<FormField>& field) {
    if (!doc_) {
        return field;
    }

    ensure_paragraph();

    // Compute default result for checkbox / combobox when empty
    std::string result = field->get_result();
    if (result.empty()) {
        if (field->get_form_field_type() == FormFieldType::CheckBox) {
            result = field->get_checked() ? "\u2611" : "\u2610";  // ballot box symbols
        } else if (field->get_form_field_type() == FormFieldType::ComboBox) {
            const auto& items = field->get_drop_down_items();
            const int idx = field->get_drop_down_selected_index();
            if (idx >= 0 && idx < static_cast<int>(items.size())) {
                result = items[idx];
            }
        }
    }
    if (!result.empty()) {
        field->set_result(result);
    }

    append_form_field_sequence(current_paragraph_, field.get(), doc_);

    if (doc_) {
        doc_->mark_xml_paragraph_dirty(current_paragraph_);
    }
    return field;
}

std::shared_ptr<FormField> DocumentBuilder::insert_text_input(const std::string& name,
                                                              TextFormFieldType type,
                                                              const std::string& format,
                                                              const std::string& field_value,
                                                              int max_length) {
    auto field = std::make_shared<FormField>(doc_, FormFieldType::TextInput);
    field->set_name(name);
    field->set_text_input_type(type);
    field->set_text_input_format(format);
    field->set_result(field_value);
    field->set_text_input_default(field_value);
    field->set_max_length(max_length);
    return insert_form_field_impl(field);
}

std::shared_ptr<FormField> DocumentBuilder::insert_check_box(const std::string& name,
                                                             bool checked_value,
                                                             int size) {
    return insert_check_box(name, checked_value, checked_value, size);
}

std::shared_ptr<FormField> DocumentBuilder::insert_check_box(const std::string& name,
                                                             bool default_value,
                                                             bool checked_value,
                                                             int size) {
    auto field = std::make_shared<FormField>(doc_, FormFieldType::CheckBox);
    field->set_name(name);
    field->set_default_value(default_value);
    field->set_checked(checked_value);
    field->set_result(checked_value ? "\u2611" : "\u2610");
    if (size > 0) {
        field->set_is_check_box_exact_size(true);
        field->set_check_box_size(size);
    }
    return insert_form_field_impl(field);
}

std::shared_ptr<FormField> DocumentBuilder::insert_combo_box(const std::string& name,
                                                             const std::vector<std::string>& items,
                                                             int selected_index) {
    auto field = std::make_shared<FormField>(doc_, FormFieldType::ComboBox);
    field->set_name(name);
    field->set_drop_down_items(items);
    field->set_drop_down_selected_index(selected_index);
    if (selected_index >= 0 && selected_index < static_cast<int>(items.size())) {
        field->set_result(items[selected_index]);
    }
    return insert_form_field_impl(field);
}

// ============================================================================
// Image Utility Functions (P1 Enhancement)
// ============================================================================

namespace {

// PNG signature
bool is_png(const std::vector<uint8_t>& data) {
    return data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 && data[2] == 0x4E &&
           data[3] == 0x47 && data[4] == 0x0D && data[5] == 0x0A && data[6] == 0x1A &&
           data[7] == 0x0A;
}

// JPEG signature
bool is_jpeg(const std::vector<uint8_t>& data) {
    return data.size() >= 3 && data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF;
}

// GIF signature
bool is_gif(const std::vector<uint8_t>& data) {
    return data.size() >= 6 && data[0] == 'G' && data[1] == 'I' && data[2] == 'F' &&
           data[3] == '8' && (data[4] == '7' || data[4] == '9') && data[5] == 'a';
}

// BMP signature
bool is_bmp(const std::vector<uint8_t>& data) {
    return data.size() >= 2 && data[0] == 'B' && data[1] == 'M';
}

// Read PNG dimensions from data
bool read_png_dimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    if (data.size() < 24) {
        return false;
    }
    // IHDR chunk: width at offset 16, height at offset 20 (big-endian)
    width = (data[16] << 24) | (data[17] << 16) | (data[18] << 8) | data[19];
    height = (data[20] << 24) | (data[21] << 16) | (data[22] << 8) | data[23];
    return width > 0 && height > 0 && width < 100000 && height < 100000;
}

// Read JPEG dimensions from data
bool read_jpeg_dimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    size_t pos = 2;  // Skip SOI marker
    while (pos < data.size()) {
        if (data[pos] != 0xFF) {
            pos++;
            continue;
        }
        while (pos < data.size() && data[pos] == 0xFF) {
            pos++;
        }
        if (pos >= data.size()) {
            break;
        }
        const uint8_t marker = data[pos++];
        if (marker == 0xC0 || marker == 0xC2) {  // SOF0 or SOF2
            if (pos + 9 >= data.size()) {
                return false;
            }
            height = (data[pos + 3] << 8) | data[pos + 4];
            width = (data[pos + 5] << 8) | data[pos + 6];
            return width > 0 && height > 0 && width < 100000 && height < 100000;
        }
        if (marker == 0xD9) {
            break;  // EOI
        }
        if (pos + 2 > data.size()) {
            break;
        }
        const uint16_t len = (data[pos] << 8) | data[pos + 1];
        pos += len;
    }
    return false;
}

// Read GIF dimensions from data
bool read_gif_dimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    if (data.size() < 10) {
        return false;
    }
    width = data[6] | (data[7] << 8);
    height = data[8] | (data[9] << 8);
    return width > 0 && height > 0 && width < 100000 && height < 100000;
}

// Read BMP dimensions from data
bool read_bmp_dimensions(const std::vector<uint8_t>& data, int& width, int& height) {
    if (data.size() < 26) {
        return false;
    }
    // DIB header size at offset 14 (little-endian uint32_t)
    const uint32_t dib_size = data[14] | (data[15] << 8) | (data[16] << 16) | (data[17] << 24);
    if (dib_size == 12) {  // BITMAPCOREHEADER
        if (data.size() < 22) {
            return false;
        }
        width = data[18] | (data[19] << 8);
        height = data[20] | (data[21] << 8);
    } else {  // BITMAPINFOHEADER or later
        width = data[18] | (data[19] << 8) | (data[20] << 16) |
                (data[21] << 24);
        auto h = static_cast<int32_t>(data[22] | (data[23] << 8) | (data[24] << 16) |
                                      (data[25] << 24));
        height = std::abs(h);
    }
    return width > 0 && height > 0 && width < 100000 && height < 100000;
}

struct ImageFormatMapping {
    bool (*detector)(const std::vector<uint8_t>&);
    bool (*reader)(const std::vector<uint8_t>&, int&, int&);
    const char* format_name;
    const char* mime_type;
};

static const ImageFormatMapping kImageFormatMappings[] = {
    {is_png, read_png_dimensions, "PNG", "image/png"},
    {is_jpeg, read_jpeg_dimensions, "JPEG", "image/jpeg"},
    {is_gif, read_gif_dimensions, "GIF", "image/gif"},
    {is_bmp, read_bmp_dimensions, "BMP", "image/bmp"},
};

static bool detect_image_format_type(const std::vector<uint8_t>& data,
                                     const char** out_format,
                                     const char** out_mime) {
    for (const auto& m : kImageFormatMappings) {
        if (m.detector(data)) {
            *out_format = m.format_name;
            *out_mime = m.mime_type;
            return true;
        }
    }
    return false;
}

}  // anonymous namespace

bool detect_image_size(const std::string& image_path, ImageSize& size) {
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        return false;
    }

    // Read file header
    std::vector<uint8_t> data(65536);  // Read up to 64KB
    file.read(reinterpret_cast<char*>(data.data()),  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
              static_cast<std::streamsize>(data.size()));
    const size_t bytes_read = file.gcount();
    data.resize(bytes_read);

    return detect_image_size_from_memory(data, size);
}

bool detect_image_size_from_memory(const std::vector<uint8_t>& data, ImageSize& size) {
    if (data.size() < 8) {
        return false;
    }

    int width = 0;
    int height = 0;
    bool success = false;

    for (const auto& m : kImageFormatMappings) {
        if (m.detector(data)) {
            success = m.reader(data, width, height);
            break;
        }
    }

    if (success) {
        // Convert pixels to points (assuming 96 DPI)
        size = ImageSize(width * 72.0 / 96.0, height * 72.0 / 96.0);
    }

    return success;
}

ImageFormatInfo validate_image_format_detailed(const std::string& image_path) {
    ImageFormatInfo info;
    std::ifstream file(image_path, std::ios::binary);

    if (!file) {
        info.error_message = "File not found or cannot be opened";
        return info;
    }

    // Check file size
    file.seekg(0, std::ios::end);
    const size_t file_size = file.tellg();
    file.seekg(0);

    if (file_size > static_cast<size_t>(50) * 1024 * 1024) {
        info.error_message = "File too large (max 50MB)";
        return info;
    }

    // Read header
    std::vector<uint8_t> data(65536);
    file.read(reinterpret_cast<char*>(data.data()),  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
              static_cast<std::streamsize>(data.size()));
    data.resize(file.gcount());

    // Detect format
    const char* format_name = nullptr;
    const char* mime_type = nullptr;
    if (!detect_image_format_type(data, &format_name, &mime_type)) {
        info.error_message = "Unknown or unsupported image format";
        return info;
    }
    info.format = format_name;
    info.mime_type = mime_type;

    // Try to read dimensions
    ImageSize size;
    if (detect_image_size_from_memory(data, size)) {
        info.width = static_cast<int>(size.width_pt * 96.0 / 72.0);
        info.height = static_cast<int>(size.height_pt * 96.0 / 72.0);
        info.is_valid = true;
    } else {
        info.error_message = "Cannot read image dimensions, file may be corrupted";
    }

    return info;
}

ImageFormatInfo validate_image_format_from_memory(const std::vector<uint8_t>& data) {
    ImageFormatInfo info;

    if (data.size() < 8) {
        info.error_message = "Data too small to be a valid image";
        return info;
    }

    // Detect format
    const char* format_name = nullptr;
    const char* mime_type = nullptr;
    if (!detect_image_format_type(data, &format_name, &mime_type)) {
        info.error_message = "Unknown or unsupported image format";
        return info;
    }
    info.format = format_name;
    info.mime_type = mime_type;

    // Try to read dimensions
    ImageSize size;
    if (detect_image_size_from_memory(data, size)) {
        info.width = static_cast<int>(size.width_pt * 96.0 / 72.0);
        info.height = static_cast<int>(size.height_pt * 96.0 / 72.0);
        info.is_valid = true;
    } else {
        info.error_message = "Cannot read image dimensions, data may be corrupted";
    }

    return info;
}


}  // namespace cdocx
