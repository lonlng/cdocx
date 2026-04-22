/**
 * @file caption_generator.cpp
 * @brief CaptionGenerator implementation
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 */

#include <cdocx/caption_generator.h>
#include <cdocx/document.h>

#include <cctype>

namespace cdocx {

// ============================================================================
// Public Methods
// ============================================================================

pugi::xml_node CaptionGenerator::insert_figure_caption(Document* doc,
                                                       pugi::xml_node after_para,
                                                       const std::string& description,
                                                       int figure_number) {
    if (!doc) {
        return pugi::xml_node();
    }

    // Auto-generate figure number if not provided
    if (figure_number <= 0) {
        figure_number = get_next_figure_number(doc);
    }

    // Generate full caption text
    std::string full_text = generate_caption_text(figure_number, description);

    // Create caption paragraph
    return create_caption_paragraph(doc, full_text, after_para);
}

pugi::xml_node CaptionGenerator::insert_figure_caption_at_end(Document* doc,
                                                              const std::string& description,
                                                              int figure_number) {
    if (!doc) {
        return pugi::xml_node();
    }

    // Auto-generate figure number if not provided
    if (figure_number <= 0) {
        figure_number = get_next_figure_number(doc);
    }

    // Generate full caption text
    std::string full_text = generate_caption_text(figure_number, description);

    // Create caption paragraph at end (no insert_after)
    return create_caption_paragraph(doc, full_text, pugi::xml_node());
}

int CaptionGenerator::count_existing_figures(Document* doc) {
    if (!doc) {
        return 0;
    }

    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) {
        return 0;
    }

    int count = 0;

    // Get all paragraphs in document body
    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return 0;
    }

    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (is_figure_caption(para)) {
            count++;
        }
    }

    return count;
}

int CaptionGenerator::get_next_figure_number(Document* doc) {
    return count_existing_figures(doc) + 1;
}

bool CaptionGenerator::is_figure_caption(pugi::xml_node para) {
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

    // Check if starts with "图" followed by number
    // Support both "图 1" and "图1" formats
    if (text.length() < 2) {
        return false;
    }

    // Check for "图" character (UTF-8: 0xE5 0x9B 0xBE)
    if (text.substr(0, 3) != "\xE5\x9B\xBE") {
        return false;
    }

    // Check for number after "图"
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

std::string CaptionGenerator::extract_caption_text(pugi::xml_node para) {
    if (!is_figure_caption(para)) {
        return "";
    }

    // Extract all text
    std::string text;
    for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
        pugi::xml_node t = run.child("w:t");
        if (t && t.text()) {
            text += t.text().get();
        }
    }

    // Find position after figure number
    // Pattern: "图 X " or "图X "
    size_t pos = text.find("\xE5\x9B\xBE");  // "图"
    if (pos == std::string::npos) {
        return "";
    }

    pos += 3;  // Skip "图"

    // Skip optional space
    if (pos < text.length() && text[pos] == ' ') {
        pos++;
    }

    // Skip number
    while (pos < text.length() && std::isdigit(static_cast<unsigned char>(text[pos]))) {
        pos++;
    }

    // Skip space after number
    if (pos < text.length() && text[pos] == ' ') {
        pos++;
    }

    // Return remaining text (description)
    return text.substr(pos);
}

// ============================================================================
// Private Methods
// ============================================================================

pugi::xml_node CaptionGenerator::create_caption_paragraph(Document* doc,
                                                          const std::string& full_text,
                                                          pugi::xml_node insert_after) {
    if (!doc) {
        return pugi::xml_node();
    }

    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) {
        return pugi::xml_node();
    }

    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        return pugi::xml_node();
    }

    // Create new paragraph
    pugi::xml_node caption_para;
    if (insert_after) {
        caption_para = body.insert_child_after("w:p", insert_after);
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

    // Add run properties with fonts
    pugi::xml_node rPr = run.append_child("w:rPr");
    if (rPr) {
        CaptionFormat fmt = CaptionFormat::chinese_default();

        // Font settings
        pugi::xml_node rFonts = rPr.append_child("w:rFonts");
        if (rFonts) {
            rFonts.append_attribute("w:ascii").set_value(fmt.font_ascii.c_str());
            rFonts.append_attribute("w:eastAsia").set_value(fmt.font_east_asia.c_str());
            rFonts.append_attribute("w:hAnsi").set_value(fmt.font_hansi.c_str());
        }

        // Font size
        pugi::xml_node sz = rPr.append_child("w:sz");
        if (sz) {
            sz.append_attribute("w:val").set_value(fmt.font_size);
        }
        pugi::xml_node szCs = rPr.append_child("w:szCs");
        if (szCs) {
            szCs.append_attribute("w:val").set_value(fmt.font_size);
        }
    }

    // Add text
    pugi::xml_node t = run.append_child("w:t");
    if (t) {
        t.text().set(full_text.c_str());
    }

    return caption_para;
}

std::string CaptionGenerator::generate_caption_text(int figure_number,
                                                    const std::string& description) {
    // Format: "图 X description"
    std::string result = "\xE5\x9B\xBE " + std::to_string(figure_number);  // "图 "

    if (!description.empty()) {
        result += " " + description;
    }

    return result;
}

pugi::xml_node CaptionGenerator::get_body(Document* doc) {
    if (!doc) {
        return pugi::xml_node();
    }

    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) {
        return pugi::xml_node();
    }

    return doc_xml->child("w:document").child("w:body");
}

}  // namespace cdocx
