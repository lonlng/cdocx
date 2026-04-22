/**
 * @file table_builder.cpp
 * @brief Table builder implementation
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.5.0
 */

#include <cdocx/advanced.h>
#include <cdocx/caption_generator.h>
#include <cdocx/document.h>
#include <cdocx/table_builder.h>

namespace cdocx {

// ============================================================================
// TableBuilder Implementation
// ============================================================================

TableBuilder::TableBuilder(int rows, int cols) : rows_(rows), cols_(cols) {
    cells_.resize(rows, std::vector<CellData>(cols));
}

TableBuilder& TableBuilder::SetBorders(const TableBorders& borders) {
    borders_ = borders;
    return *this;
}

TableBuilder& TableBuilder::SetWidth(int width, bool auto_width) {
    width_ = width;
    auto_width_ = auto_width;
    return *this;
}

TableBuilder& TableBuilder::SetCellMargins(int top, int left, int bottom, int right) {
    cell_margin_top_ = top;
    cell_margin_left_ = left;
    cell_margin_bottom_ = bottom;
    cell_margin_right_ = right;
    return *this;
}

TableBuilder& TableBuilder::SetCellText(int row, int col, const std::string& text) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        cells_[row][col].text = text;
    }
    return *this;
}

TableBuilder& TableBuilder::SetCellTextFormatted(
    int row, int col, const std::string& text, bool bold, bool italic, int font_size) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        cells_[row][col].text = text;
        cells_[row][col].bold = bold;
        cells_[row][col].italic = italic;
        cells_[row][col].font_size = font_size;
    }
    return *this;
}

TableBuilder& TableBuilder::SetCellVerticalAlign(int row, int col, const std::string& align) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        cells_[row][col].v_align = align;
    }
    return *this;
}

TableBuilder& TableBuilder::MergeCellsHorizontal(int row, int col, int span) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_ && span > 1) {
        for (int c = 0; c < span && col + c < cols_; c++) {
            cells_[row][col + c].col_span = (c == 0) ? span : 0;
        }
    }
    return *this;
}

TableBuilder& TableBuilder::MergeCellsVertical(int col, int row, int span) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_ && span > 1) {
        for (int r = 0; r < span && row + r < rows_; r++) {
            cells_[row + r][col].row_span = (r == 0) ? span : 0;
            cells_[row + r][col].is_vmerge_restart = (r == 0);
        }
    }
    return *this;
}

TableBuilder& TableBuilder::MergeCells(int start_row, int start_col, int row_span, int col_span) {
    if (row_span > 1) {
        MergeCellsVertical(start_col, start_row, row_span);
    }
    if (col_span > 1) {
        MergeCellsHorizontal(start_row, start_col, col_span);
    }
    return *this;
}

void TableBuilder::CreateTableStructure(pugi::xml_node tbl) const {


    // Create tblPr (table properties)
    pugi::xml_node tblPr = tbl.append_child("w:tblPr");

    // Table width
    pugi::xml_node tblW = tblPr.append_child("w:tblW");
    tblW.append_attribute("w:w").set_value(auto_width_ ? 0 : width_);
    tblW.append_attribute("w:type").set_value(auto_width_ ? "auto" : "dxa");

    // Table indentation
    pugi::xml_node tblInd = tblPr.append_child("w:tblInd");
    tblInd.append_attribute("w:w").set_value(0);
    tblInd.append_attribute("w:type").set_value("dxa");

    // Borders
    if (borders_.top || borders_.left || borders_.bottom || borders_.right || borders_.inside_h ||
        borders_.inside_v) {
        pugi::xml_node tblBorders = tblPr.append_child("w:tblBorders");

        auto add_border = [&](const char* name, bool enabled) {
            if (enabled) {
                pugi::xml_node border = tblBorders.append_child(name);
                border.append_attribute("w:val").set_value("single");
                border.append_attribute("w:color").set_value(borders_.color.c_str());
                border.append_attribute("w:sz").set_value(borders_.size);
                border.append_attribute("w:space").set_value(0);
            }
        };

        add_border("w:top", borders_.top);
        add_border("w:left", borders_.left);
        add_border("w:bottom", borders_.bottom);
        add_border("w:right", borders_.right);
        add_border("w:insideH", borders_.inside_h);
        add_border("w:insideV", borders_.inside_v);
    }

    // Table layout
    pugi::xml_node tblLayout = tblPr.append_child("w:tblLayout");
    tblLayout.append_attribute("w:type").set_value("autofit");

    // Cell margins
    pugi::xml_node tblCellMar = tblPr.append_child("w:tblCellMar");
    auto add_margin = [&](const char* name, int value) {
        pugi::xml_node m = tblCellMar.append_child(name);
        m.append_attribute("w:w").set_value(value);
        m.append_attribute("w:type").set_value("dxa");
    };
    add_margin("w:top", cell_margin_top_);
    add_margin("w:left", cell_margin_left_);
    add_margin("w:bottom", cell_margin_bottom_);
    add_margin("w:right", cell_margin_right_);

    // Create tblGrid (column definitions)
    pugi::xml_node tblGrid = tbl.append_child("w:tblGrid");
    int col_width = auto_width_ ? 2840 : (width_ / cols_);
    for (int c = 0; c < cols_; c++) {
        pugi::xml_node gridCol = tblGrid.append_child("w:gridCol");
        gridCol.append_attribute("w:w").set_value(col_width);
    }
}

void TableBuilder::CreateCell(pugi::xml_node tr, int row, int col) const {


    const CellData& cell = cells_[row][col];

    // Skip cells that are part of a merge but not the start
    if (cell.col_span == 0 || cell.row_span == 0) {
        return;
    }

    pugi::xml_node tc = tr.append_child("w:tc");

    // Cell properties
    pugi::xml_node tcPr = tc.append_child("w:tcPr");

    // Cell width
    pugi::xml_node tcW = tcPr.append_child("w:tcW");
    tcW.append_attribute("w:w").set_value(2840);  // Default width
    tcW.append_attribute("w:type").set_value("dxa");

    // Horizontal merge (gridSpan)
    if (cell.col_span > 1) {
        pugi::xml_node gridSpan = tcPr.append_child("w:gridSpan");
        gridSpan.append_attribute("w:val").set_value(cell.col_span);
    }

    // Vertical merge (vMerge)
    if (cell.row_span > 1) {
        pugi::xml_node vMerge = tcPr.append_child("w:vMerge");
        vMerge.append_attribute("w:val").set_value("restart");
    }

    // Vertical alignment
    if (!cell.v_align.empty()) {
        pugi::xml_node v_align = tcPr.append_child("w:vAlign");
        v_align.append_attribute("w:val").set_value(cell.v_align.c_str());
    }

    // Create paragraph with text
    pugi::xml_node p = tc.append_child("w:p");
    pugi::xml_node pPr = p.append_child("w:pPr");
    pPr.append_child("w:rPr");

    if (!cell.text.empty()) {
        pugi::xml_node r = p.append_child("w:r");

        // Run properties
        pugi::xml_node rPr = r.append_child("w:rPr");

        if (cell.bold) {
            rPr.append_child("w:b");
        }
        if (cell.italic) {
            rPr.append_child("w:i");
        }
        if (cell.font_size > 0) {
            pugi::xml_node sz = rPr.append_child("w:sz");
            sz.append_attribute("w:val").set_value(cell.font_size);
            pugi::xml_node szCs = rPr.append_child("w:szCs");
            szCs.append_attribute("w:val").set_value(cell.font_size);
        }

        // Text
        pugi::xml_node t = r.append_child("w:t");
        t.text().set(cell.text.c_str());
    }
}

pugi::xml_node TableBuilder::Build(pugi::xml_document& doc_xml) const {
    pugi::xml_node tbl = doc_xml.append_child("w:tbl");

    CreateTableStructure(tbl);

    // Create rows
    for (int r = 0; r < rows_; r++) {
        pugi::xml_node tr = tbl.append_child("w:tr");

        for (int c = 0; c < cols_; c++) {
            CreateCell(tr, r, c);
        }
    }

    return tbl;
}

bool TableBuilder::InsertAtBookmark(Document& doc, const std::string& bookmark_name) {
    BookmarkCollection bookmarks = doc.get_bookmarks();
    auto bm = bookmarks.get(bookmark_name);
    if (!bm) {
        return false;
    }

    auto paras = bm->get_covered_paragraphs();
    if (paras.empty()) {
        return false;
    }

    pugi::xml_node para = paras[0];
    pugi::xml_node parent = para.parent();

    // Build table XML
    pugi::xml_document temp_doc;
    pugi::xml_node tbl = Build(temp_doc);

    // Import and insert after the paragraph
    pugi::xml_node imported_tbl = parent.insert_child_after("w:tbl", para);
    imported_tbl.set_name("w:tbl");

    // Copy all children
    for (pugi::xml_node child = tbl.first_child(); child; child = child.next_sibling()) {
        imported_tbl.append_copy(child);
    }

    // Clear bookmark content but keep bookmark
    bm->set_text("");

    return true;
}

bool TableBuilder::InsertAfterParagraph(Document& doc, Paragraph& para) {
    // Get the underlying XML node from paragraph
    // This requires access to paragraph's internal XML node
    // For now, return false as we need internal access
    return false;
}

// ============================================================================
// Table Caption Functions
// ============================================================================

int get_next_table_number(Document* doc) {
    return count_existing_tables(doc) + 1;
}

int count_existing_tables(Document* doc) {
    if (!doc) {
        return 0;
    }

    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) {
        return 0;
    }

    int count = 0;
    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return 0;
    }

    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (is_table_caption(para)) {
            count++;
        }
    }

    return count;
}

bool is_table_caption(pugi::xml_node para) {
    if (!para) {
        return false;
    }

    // Extract all text from paragraph
    std::string text;
    for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
        pugi::xml_node t = run.child("w:t");
        if (t && t.text()) {
            text += t.text().get();
        }
    }

    // trim whitespace
    size_t start = text.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return false;
    }
    text = text.substr(start);

    // Check if starts with "表" followed by number
    // Support both "表 1" and "表1" formats
    if (text.length() < 2) {
        return false;
    }

    // Check for "表" character (UTF-8: 0xE8 0xA1 0xA8)
    if (text.substr(0, 3) != "\xE8\xA1\xA8") {
        return false;
    }

    // Check for number after "表"
    size_t pos = 3;
    // Skip optional space
    if (pos < text.length() && text[pos] == ' ') {
        pos++;
    }

    // Check for digit
    if (pos < text.length() && std::isdigit(static_cast<unsigned char>(text[pos]))) {
        return true;
    }

    return false;
}

pugi::xml_node insert_table_caption(Document* doc,
                                        pugi::xml_node after_node,
                                        const std::string& description,
                                        int table_number) {
    if (!doc) {
        return pugi::xml_node();
    }

    // Auto-generate table number if not provided
    if (table_number <= 0) {
        table_number = get_next_table_number(doc);
    }

    // Generate full caption text: "表 X description"
    std::string full_text = "\xE8\xA1\xA8 " + std::to_string(table_number);  // "表 "
    if (!description.empty()) {
        full_text += " " + description;
    }

    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) {
        return pugi::xml_node();
    }

    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return pugi::xml_node();
    }

    // Create new paragraph after the table node
    pugi::xml_node caption_para;
    if (after_node) {
        caption_para = body.insert_child_after("w:p", after_node);
    } else {
        caption_para = body.append_child("w:p");
    }

    if (!caption_para) {
        return pugi::xml_node();
    }

    // Create paragraph properties with center alignment
    pugi::xml_node pPr = caption_para.append_child("w:pPr");
    if (pPr) {
        pugi::xml_node jc = pPr.append_child("w:jc");
        if (jc) {
            jc.append_attribute("w:val").set_value("center");
        }

        // Add spacing before and after
        pugi::xml_node spacing = pPr.append_child("w:spacing");
        if (spacing) {
            spacing.append_attribute("w:before").set_value(100);  // 5pt
            spacing.append_attribute("w:after").set_value(100);   // 5pt
        }
    }

    // Create run with text
    pugi::xml_node run = caption_para.append_child("w:r");
    if (!run) {
        return caption_para;
    }

    // Add run properties with fonts (same as figure caption)
    pugi::xml_node rPr = run.append_child("w:rPr");
    if (rPr) {
        // Font settings: SimSun for Chinese, Times New Roman for Western
        pugi::xml_node rFonts = rPr.append_child("w:rFonts");
        if (rFonts) {
            rFonts.append_attribute("w:ascii").set_value("Times New Roman");
            rFonts.append_attribute("w:eastAsia").set_value("SimSun");
            rFonts.append_attribute("w:hAnsi").set_value("Times New Roman");
        }

        // Font size: 10.5pt (21 half-points)
        pugi::xml_node sz = rPr.append_child("w:sz");
        if (sz) {
            sz.append_attribute("w:val").set_value(21);
        }
        pugi::xml_node sz_cs = rPr.append_child("w:szCs");
        if (sz_cs) {
            sz_cs.append_attribute("w:val").set_value(21);
        }
    }

    // Add text
    pugi::xml_node t = run.append_child("w:t");
    if (t) {
        t.text().set(full_text.c_str());
    }

    return caption_para;
}

}  // namespace cdocx
