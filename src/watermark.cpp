/**
 * @file watermark.cpp
 * @brief Watermark implementation
 */

#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/table.h>
#include <cdocx/watermark.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

namespace cdocx {

// ============================================================================
// Helper Functions

static bool is_word_watermark_shape(const pugi::xml_node shape) {
    const pugi::xml_attribute id_attr = shape.attribute("id");
    return id_attr && std::strcmp(id_attr.value(), "PowerPlusWaterMarkObject") == 0;
}
// ============================================================================

struct XmlEscapeMapping {
    char c;
    const char* replacement;
};

static const XmlEscapeMapping kXmlEscapeMappings[] = {
    {'&', "&amp;"},
    {'<', "&lt;"},
    {'>', "&gt;"},
    {'"', "&quot;"},
    {'\'', "&apos;"},
};

static std::string escape_xml(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (const char c : text) {
        bool found = false;
        for (const auto& mapping : kXmlEscapeMappings) {
            if (mapping.c == c) {
                result += mapping.replacement;
                found = true;
                break;
            }
        }
        if (!found) {
            result += c;
        }
    }
    return result;
}

static pugi::xml_node get_first_header_xml(Document* doc) {
    auto names = doc->get_header_names();
    if (names.empty()) {
        return pugi::xml_node{};
    }
    pugi::xml_document* header_doc = doc->get_header(0);
    if (!header_doc) {
        return pugi::xml_node{};
    }
    return header_doc->child("w:hdr");
}

static void remove_watermark_nodes(pugi::xml_node header) {
    if (!header) {
        return;
    }
    for (pugi::xml_node para = header.child("w:p"); para;) {
        bool is_watermark = false;
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            for (pugi::xml_node pict = run.child("w:pict"); pict;
                 pict = pict.next_sibling("w:pict")) {
                const pugi::xml_node shape = pict.child("v:shape");
                if (shape) {
                    if (is_word_watermark_shape(shape)) {
                        is_watermark = true;
                        break;
                    }
                }
            }
            if (is_watermark) {
                break;
            }
            for (pugi::xml_node drawing = run.child("w:drawing"); drawing;
                 drawing = drawing.next_sibling("w:drawing")) {
                const pugi::xml_node doc_pr =
                    drawing.child("wp:anchor").child("a:graphic").child("a:graphicData");
                if (doc_pr) {
                    const pugi::xml_attribute name_attr = doc_pr.attribute("uri");
                    if (name_attr && std::strstr(name_attr.value(), "watermark") != nullptr) {
                        is_watermark = true;
                        break;
                    }
                }
            }
            if (is_watermark) {
                break;
            }
        }
        const pugi::xml_node next_para = para.next_sibling("w:p");
        if (is_watermark) {
            header.remove_child(para);
        }
        para = next_para;
    }
}

// ============================================================================
// Watermark Implementation
// ============================================================================

Watermark::Watermark(Document* doc) : document_(doc) {
}

void Watermark::set_text(const std::string& text) {
    const TextWatermarkOptions options;
    set_text(text, options);
}

void Watermark::set_text(const std::string& text, const TextWatermarkOptions& options) {
    if (!document_) {
        return;
    }
    remove();
    ensure_header_for_watermark();
    insert_text_watermark_into_header(text, options);
}

void Watermark::set_image(const std::string& image_path) {
    const ImageWatermarkOptions options;
    set_image(image_path, options);
}

void Watermark::set_image(const std::string& image_path, const ImageWatermarkOptions& options) {
    if (!document_) {
        return;
    }
    remove();
    ensure_header_for_watermark();
    insert_image_watermark_into_header(image_path, options);
}

void Watermark::remove() {
    if (!document_) {
        return;
    }
    const pugi::xml_node header = get_first_header_xml(document_);
    if (header) {
        remove_watermark_nodes(header);
    }
}

bool Watermark::has_watermark() const {
    if (!document_) {
        return false;
    }
    const pugi::xml_node header = get_first_header_xml(document_);
    if (!header) {
        return false;
    }
    for (pugi::xml_node para = header.child("w:p"); para; para = para.next_sibling("w:p")) {
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            for (pugi::xml_node pict = run.child("w:pict"); pict;
                 pict = pict.next_sibling("w:pict")) {
                const pugi::xml_node shape = pict.child("v:shape");
                if (shape) {
                    if (is_word_watermark_shape(shape)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Watermark::ensure_header_for_watermark() {
    auto sect = document_->get_first_section();
    if (!sect) {
        return;
    }
    if (!sect->has_header(HeaderFooterType::Default)) {
        sect->add_header(HeaderFooterType::Default);
    }
}

void Watermark::insert_text_watermark_into_header(const std::string& text,
                                                  const TextWatermarkOptions& options) {
    pugi::xml_node header = get_first_header_xml(document_);
    if (!header) {
        return;
    }

    auto para = header.append_child("w:p");
    auto p_pr = para.append_child("w:pPr");
    p_pr.append_child("w:pStyle").append_attribute("w:val").set_value("Header");

    auto run = para.append_child("w:r");
    auto pict = run.append_child("w:pict");

    // VML namespace
    auto shapetype = pict.append_child("v:shapetype");
    shapetype.append_attribute("id").set_value("_x0000_t136");
    shapetype.append_attribute("coordsize").set_value("21600,21600");
    shapetype.append_attribute("o:spt").set_value("136");
    shapetype.append_attribute("adj").set_value("10800");
    shapetype.append_attribute("path").set_value("m@7,l@8,m@5,21600l@6,21600e");

    auto formulas = shapetype.append_child("v:formulas");
    formulas.append_child("v:f").append_attribute("eqn").set_value("sum #0 0 10800");
    formulas.append_child("v:f").append_attribute("eqn").set_value("prod #0 2 1");
    formulas.append_child("v:f").append_attribute("eqn").set_value("sum 21600 0 @1");
    formulas.append_child("v:f").append_attribute("eqn").set_value("sum 0 0 @2");
    formulas.append_child("v:f").append_attribute("eqn").set_value("sum 21600 0 @3");
    formulas.append_child("v:f").append_attribute("eqn").set_value("if @0 @3 0");
    formulas.append_child("v:f").append_attribute("eqn").set_value("if @0 21600 @1");
    formulas.append_child("v:f").append_attribute("eqn").set_value("if @0 0 @2");
    formulas.append_child("v:f").append_attribute("eqn").set_value("if @0 @4 21600");
    formulas.append_child("v:f").append_attribute("eqn").set_value("mid @5 @6");
    formulas.append_child("v:f").append_attribute("eqn").set_value("mid @8 @5");
    formulas.append_child("v:f").append_attribute("eqn").set_value("mid @6 @8");
    formulas.append_child("v:f").append_attribute("eqn").set_value("mid @7 @8");
    formulas.append_child("v:f").append_attribute("eqn").set_value("sum @6 0 @5");

    auto path = shapetype.append_child("v:path");
    path.append_attribute("textpathok").set_value("t");
    path.append_attribute("o:connecttype").set_value("custom");
    path.append_attribute("o:connectlocs").set_value("@9,0;@10,10800;@11,21600;@12,10800");
    path.append_attribute("o:connectangles").set_value("270,180,90,0");

    auto textpath = shapetype.append_child("v:textpath");
    textpath.append_attribute("on").set_value("t");
    textpath.append_attribute("fitshape").set_value("t");

    auto handles = shapetype.append_child("v:handles");
    auto h = handles.append_child("v:h");
    h.append_attribute("position").set_value("#0,bottomRight");
    h.append_attribute("xrange").set_value("6629,14971");

    auto lock = shapetype.append_child("o:lock");
    lock.append_attribute("v:ext").set_value("edit");
    lock.append_attribute("text").set_value("t");
    lock.append_attribute("shapetype").set_value("t");

    // Main watermark shape
    auto shape = pict.append_child("v:shape");
    shape.append_attribute("id").set_value("PowerPlusWaterMarkObject");
    shape.append_attribute("o:spid").set_value("_x0000_s2049");
    shape.append_attribute("type").set_value("#_x0000_t136");

    const int rotation = (options.layout == WatermarkLayout::Diagonal) ? 315 : 0;
    std::string style = "position:absolute;margin-left:0;margin-top:0;width:468pt;height:117pt;";
    style += "rotation:" + std::to_string(rotation) + ";";
    style += "z-index:-251658752;";
    style += "mso-position-horizontal:center;mso-position-horizontal-relative:margin;";
    style += "mso-position-vertical:center;mso-position-vertical-relative:margin";
    shape.append_attribute("style").set_value(style.c_str());
    shape.append_attribute("o:allowincell").set_value("f");
    shape.append_attribute("fillcolor").set_value(("#" + options.color).c_str());
    shape.append_attribute("stroked").set_value("f");

    auto fill = shape.append_child("v:fill");
    fill.append_attribute("opacity").set_value(options.semi_transparent ? ".5" : "1");

    const float font_size = options.font_size > 0 ? options.font_size : 1.0f;
    const std::string font_style =
        "font-family:\"" + options.font_family + "\";font-size:" + std::to_string(font_size) + "pt";

    auto tp = shape.append_child("v:textpath");
    tp.append_attribute("style").set_value(font_style.c_str());
    tp.append_attribute("string").set_value(escape_xml(text).c_str());

    auto wrap = shape.append_child("w10:wrap");
    wrap.append_attribute("anchorx").set_value("margin");
    wrap.append_attribute("anchory").set_value("margin");
}

void Watermark::insert_image_watermark_into_header(const std::string& image_path,
                                                   const ImageWatermarkOptions& options) {
    if (!document_) {
        return;
    }

    // Read image file into memory
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        return;
    }
    const std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());
    file.close();
    if (data.empty()) {
        return;
    }

    // Determine media filename and ensure uniqueness
    std::string filename = std::filesystem::path(image_path).filename().string();
    if (document_->has_media(filename)) {
        filename = document_->generate_unique_image_name(filename);
    }

    // Add media to document
    if (!document_->add_media_from_memory(filename, data)) {
        return;
    }

    // Find the first header and its rels path
    auto header_names = document_->get_header_names();
    if (header_names.empty()) {
        return;
    }

    const std::string& header_path = header_names[0];
    std::string rels_path;
    if (header_path.find('/') != std::string::npos) {
        rels_path = header_path.substr(0, header_path.rfind('/') + 1) + "_rels/" +
                    header_path.substr(header_path.rfind('/') + 1) + ".rels";
    } else {
        rels_path = "word/_rels/" + header_path + ".rels";
    }

    // Create relationship in header rels
    const std::string rel_id = document_->add_relationship(
        rels_path,
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
        "media/" + filename);
    if (rel_id.empty()) {
        return;
    }

    pugi::xml_node header = get_first_header_xml(document_);
    if (!header) {
        return;
    }

    auto para = header.append_child("w:p");
    auto p_pr = para.append_child("w:pPr");
    auto jc = p_pr.append_child("w:jc");
    jc.append_attribute("w:val").set_value("center");

    auto run = para.append_child("w:r");
    auto pict = run.append_child("w:pict");
    auto shape = pict.append_child("v:shape");
    shape.append_attribute("id").set_value("PowerPlusWaterMarkObject");
    shape.append_attribute("style").set_value(
        "position:absolute;margin-left:0;margin-top:0;width:400pt;height:300pt;z-index:-251658752;"
        "mso-position-horizontal:center;mso-position-horizontal-relative:margin;mso-position-"
        "vertical:center;mso-position-vertical-relative:margin");
    shape.append_attribute("o:allowincell").set_value("f");
    shape.append_attribute("stroked").set_value("f");

    // Apply scale if explicitly set (> 0)
    if (options.scale > 0) {
        const int width_pt = static_cast<int>(400.0 * options.scale / 100.0);
        const int height_pt = static_cast<int>(300.0 * options.scale / 100.0);
        const std::string style =
            "position:absolute;margin-left:0;margin-top:0;width:" + std::to_string(width_pt) +
            "pt;height:" + std::to_string(height_pt) +
            "pt;z-index:-251658752;"
            "mso-position-horizontal:center;mso-position-horizontal-relative:margin;"
            "mso-position-vertical:center;mso-position-vertical-relative:margin";
        shape.attribute("style").set_value(style.c_str());
    }

    // Apply washout effect (grayscale + reduced contrast)
    if (options.washout) {
        auto fill = shape.append_child("v:fill");
        fill.append_attribute("type").set_value("frame");
        fill.append_attribute("opacity").set_value("0.5");
        auto image = shape.append_child("v:image");
        image.append_attribute("o:title").set_value("Watermark");
        image.append_attribute("cropleft").set_value("f");
    }

    auto imagedata = shape.append_child("v:imagedata");
    imagedata.append_attribute("r:id").set_value(rel_id.c_str());
    imagedata.append_attribute("o:title").set_value("Watermark");
}

void Watermark::clear_watermark_from_header() {
    remove();
}

}  // namespace cdocx
