/**
 * @file document_sync.cpp
 * @brief DOM-Physical sync implementation for Document class
 * @details This file contains the helper functions and sync implementations
 *          for converting between DOM object tree and XML physical tree.
 */

#include <cdocx/base.h>
#include <cdocx/body.h>
#include <cdocx/comment.h>
#include <cdocx/document.h>
#include <cdocx/footnote.h>
#include <cdocx/format.h>
#include <cdocx/formfield.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/style.h>
#include <cdocx/table.h>

#include <cctype>
#include <chrono>
#include <cstring>
#include <ctime>

namespace cdocx {

// ============================================================================
// Forward declarations of internal helpers (defined below)
// ============================================================================
static void serialize_run_to_xml(pugi::xml_node parent, Run* run);
static void serialize_paragraph_format_to_xml(pugi::xml_node para_xml,
                                              const ParagraphFormat& format);
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
// Shading Helpers
// ============================================================================
static void serialize_shading_to_xml(pugi::xml_node parent, const Shading& shading) {
    if (!shading.has_fill())
        return;
    auto shd = parent.append_child("w:shd");
    shd.append_attribute("w:val").set_value(shading.texture.c_str());
    if (!shading.foreground.is_auto()) {
        shd.append_attribute("w:color").set_value(shading.foreground.to_hex_rgb().c_str());
    }
    if (!shading.background.is_auto()) {
        shd.append_attribute("w:fill").set_value(shading.background.to_hex_rgb().c_str());
    }
}

static void parse_shading_from_xml(pugi::xml_node shd, Shading& shading) {
    if (!shd)
        return;
    shading.texture = shd.attribute("w:val").value();
    if (shading.texture.empty()) {
        shading.texture = "clear";
    }
    auto color_attr = shd.attribute("w:color");
    if (color_attr) {
        std::string val = color_attr.value();
        if (val == "auto") {
            shading.foreground = Color::auto_color();
        } else {
            shading.foreground = Color::from_hex(val);
        }
    }
    auto fill_attr = shd.attribute("w:fill");
    if (fill_attr) {
        std::string val = fill_attr.value();
        if (val == "auto") {
            shading.background = Color::auto_color();
        } else {
            shading.background = Color::from_hex(val);
        }
    }
}

// ============================================================================
// Border Helpers
// ============================================================================
static void parse_border_from_xml(pugi::xml_node border_node, Border& border) {
    if (!border_node)
        return;
    const char* val = border_node.attribute("w:val").value();
    if (std::strcmp(val, "single") == 0) {
        border.type = BorderType::Single;
    } else if (std::strcmp(val, "thick") == 0) {
        border.type = BorderType::Thick;
    } else if (std::strcmp(val, "double") == 0) {
        border.type = BorderType::Double;
    } else if (std::strcmp(val, "dotted") == 0) {
        border.type = BorderType::Dotted;
    } else if (std::strcmp(val, "dashed") == 0) {
        border.type = BorderType::Dashed;
    } else if (std::strcmp(val, "dotDash") == 0) {
        border.type = BorderType::DotDash;
    } else if (std::strcmp(val, "dotDotDash") == 0) {
        border.type = BorderType::DotDotDash;
    } else if (std::strcmp(val, "triple") == 0) {
        border.type = BorderType::Triple;
    } else if (std::strcmp(val, "thinThickSmallGap") == 0) {
        border.type = BorderType::ThinThickSmall;
    } else if (std::strcmp(val, "thickThinSmallGap") == 0) {
        border.type = BorderType::ThickThinSmall;
    } else if (std::strcmp(val, "thinThickThinSmallGap") == 0) {
        border.type = BorderType::ThinThickThinSmall;
    } else if (std::strcmp(val, "thinThickMediumGap") == 0) {
        border.type = BorderType::ThinThickMedium;
    } else if (std::strcmp(val, "thickThinMediumGap") == 0) {
        border.type = BorderType::ThickThinMedium;
    } else if (std::strcmp(val, "thinThickThinMediumGap") == 0) {
        border.type = BorderType::ThinThickThinMedium;
    } else if (std::strcmp(val, "thinThickLargeGap") == 0) {
        border.type = BorderType::ThinThickLarge;
    } else if (std::strcmp(val, "thickThinLargeGap") == 0) {
        border.type = BorderType::ThickThinLarge;
    } else if (std::strcmp(val, "thinThickThinLargeGap") == 0) {
        border.type = BorderType::ThinThickThinLarge;
    } else if (std::strcmp(val, "wave") == 0) {
        border.type = BorderType::Wave;
    } else if (std::strcmp(val, "doubleWave") == 0) {
        border.type = BorderType::DoubleWave;
    } else if (std::strcmp(val, "dashSmallGap") == 0) {
        border.type = BorderType::DashSmall;
    } else if (std::strcmp(val, "threeDEmboss") == 0) {
        border.type = BorderType::ThreeDEmboss;
    } else if (std::strcmp(val, "threeDEngrave") == 0) {
        border.type = BorderType::ThreeDEngrave;
    } else if (std::strcmp(val, "outset") == 0) {
        border.type = BorderType::Outset;
    } else if (std::strcmp(val, "inset") == 0) {
        border.type = BorderType::Inset;
    } else if (std::strcmp(val, "clear") == 0) {
        border.type = BorderType::Clear;
    } else {
        border.type = BorderType::None;
    }

    auto sz = border_node.attribute("w:sz");
    if (sz) {
        border.width = sz.as_int() / 8.0;
    }

    auto space = border_node.attribute("w:space");
    if (space) {
        border.space = space.as_int();
    }

    auto color = border_node.attribute("w:color");
    if (color) {
        std::string c = color.value();
        if (c == "auto") {
            border.color = Color::auto_color();
        } else {
            border.color = Color::from_hex(c);
        }
    }
}

static void parse_borders_from_xml(pugi::xml_node borders_node, Borders& borders) {
    if (!borders_node)
        return;
    borders.explicitly_defined = true;
    if (borders_node.child("w:top")) {
        borders.top_defined = true;
        parse_border_from_xml(borders_node.child("w:top"), borders.top);
    }
    if (borders_node.child("w:left")) {
        borders.left_defined = true;
        parse_border_from_xml(borders_node.child("w:left"), borders.left);
    }
    if (borders_node.child("w:bottom")) {
        borders.bottom_defined = true;
        parse_border_from_xml(borders_node.child("w:bottom"), borders.bottom);
    }
    if (borders_node.child("w:right")) {
        borders.right_defined = true;
        parse_border_from_xml(borders_node.child("w:right"), borders.right);
    }
    if (borders_node.child("w:insideH")) {
        borders.inside_h_defined = true;
        parse_border_from_xml(borders_node.child("w:insideH"), borders.inside_horizontal);
    }
    if (borders_node.child("w:insideV")) {
        borders.inside_v_defined = true;
        parse_border_from_xml(borders_node.child("w:insideV"), borders.inside_vertical);
    }
}

static void serialize_border_to_xml(pugi::xml_node parent,
                                    const char* name,
                                    const Border& border,
                                    bool include_nil = false) {
    if (!border.is_visible()) {
        if (!include_nil || border.type != BorderType::None)
            return;
        auto node = parent.append_child(name);
        node.append_attribute("w:val").set_value("nil");
        return;
    }
    auto node = parent.append_child(name);
    const char* val = "single";
    switch (border.type) {
        case BorderType::Single:
            val = "single";
            break;
        case BorderType::Thick:
            val = "thick";
            break;
        case BorderType::Double:
            val = "double";
            break;
        case BorderType::Dotted:
            val = "dotted";
            break;
        case BorderType::Dashed:
            val = "dashed";
            break;
        case BorderType::DotDash:
            val = "dotDash";
            break;
        case BorderType::DotDotDash:
            val = "dotDotDash";
            break;
        case BorderType::Triple:
            val = "triple";
            break;
        case BorderType::ThinThickSmall:
            val = "thinThickSmallGap";
            break;
        case BorderType::ThickThinSmall:
            val = "thickThinSmallGap";
            break;
        case BorderType::ThinThickThinSmall:
            val = "thinThickThinSmallGap";
            break;
        case BorderType::ThinThickMedium:
            val = "thinThickMediumGap";
            break;
        case BorderType::ThickThinMedium:
            val = "thickThinMediumGap";
            break;
        case BorderType::ThinThickThinMedium:
            val = "thinThickThinMediumGap";
            break;
        case BorderType::ThinThickLarge:
            val = "thinThickLargeGap";
            break;
        case BorderType::ThickThinLarge:
            val = "thickThinLargeGap";
            break;
        case BorderType::ThinThickThinLarge:
            val = "thinThickThinLargeGap";
            break;
        case BorderType::Wave:
            val = "wave";
            break;
        case BorderType::DoubleWave:
            val = "doubleWave";
            break;
        case BorderType::DashSmall:
            val = "dashSmallGap";
            break;
        case BorderType::ThreeDEmboss:
            val = "threeDEmboss";
            break;
        case BorderType::ThreeDEngrave:
            val = "threeDEngrave";
            break;
        case BorderType::Outset:
            val = "outset";
            break;
        case BorderType::Inset:
            val = "inset";
            break;
        case BorderType::Clear:
            val = "clear";
            break;
        default:
            val = "single";
            break;
    }
    node.append_attribute("w:val").set_value(val);
    node.append_attribute("w:sz").set_value(static_cast<int>(border.width * 8));
    node.append_attribute("w:space").set_value(static_cast<int>(border.space));
    if (border.color.is_auto()) {
        node.append_attribute("w:color").set_value("auto");
    } else {
        node.append_attribute("w:color").set_value(border.color.to_hex_rgb().c_str());
    }
}

static void serialize_borders_to_xml(pugi::xml_node parent,
                                     const char* container_name,
                                     const Borders& borders) {
    if (!borders.has_visible() && !borders.explicitly_defined)
        return;
    auto container = parent.append_child(container_name);
    serialize_border_to_xml(container, "w:top", borders.top, borders.top_defined);
    serialize_border_to_xml(container, "w:left", borders.left, borders.left_defined);
    serialize_border_to_xml(container, "w:bottom", borders.bottom, borders.bottom_defined);
    serialize_border_to_xml(container, "w:right", borders.right, borders.right_defined);
    serialize_border_to_xml(container, "w:insideH", borders.inside_horizontal, borders.inside_h_defined);
    serialize_border_to_xml(container, "w:insideV", borders.inside_vertical, borders.inside_v_defined);
}

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
    sync_comments_to_physical();
    sync_footnotes_to_physical();
    sync_endnotes_to_physical();
    sync_builtin_properties_to_physical();
    sync_custom_properties_to_physical();
}

void Document::sync_from_physical_tree() {
    sync_sections_from_physical();
    sync_comments_from_physical();
    sync_footnotes_from_physical();
    sync_endnotes_from_physical();
    sync_builtin_properties_from_physical();
    sync_custom_properties_from_physical();
}

// ============================================================================
// Property Helpers
// ============================================================================

static std::string time_to_w3cdtf(std::time_t t) {
    if (t == 0)
        return "";
    std::tm utc;
#ifdef _WIN32
    gmtime_s(&utc, &t);
#else
    gmtime_r(&t, &utc);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &utc);
    return buf;
}

static std::time_t w3cdtf_to_time(const std::string& s) {
    if (s.empty())
        return 0;
    std::tm utc = {};
    std::sscanf(s.c_str(),
                "%d-%d-%dT%d:%d:%d",
                &utc.tm_year,
                &utc.tm_mon,
                &utc.tm_mday,
                &utc.tm_hour,
                &utc.tm_min,
                &utc.tm_sec);
    utc.tm_year -= 1900;
    utc.tm_mon -= 1;
    return timegm(&utc);
}

static pugi::xml_node get_or_create_child(pugi::xml_node parent, const char* name) {
    pugi::xml_node child = parent.child(name);
    if (!child) {
        child = parent.append_child(name);
    } else {
        child.remove_children();
    }
    return child;
}

static void set_text_child(pugi::xml_node parent, const char* name, const std::string& value) {
    if (value.empty()) {
        pugi::xml_node child = parent.child(name);
        if (child)
            parent.remove_child(child);
        return;
    }
    pugi::xml_node child = get_or_create_child(parent, name);
    child.append_child(pugi::node_pcdata).set_value(value.c_str());
}

// ============================================================================
// Built-in Properties Sync
// ============================================================================

void Document::sync_builtin_properties_to_physical() {
    // Sync core.xml
    pugi::xml_document* core_doc = get_core_properties();
    if (core_doc) {
        auto root = core_doc->child("cp:coreProperties");
        if (root) {
            set_text_child(root, "dc:title", builtin_properties_.title);
            set_text_child(root, "dc:subject", builtin_properties_.subject);
            set_text_child(root, "dc:creator", builtin_properties_.author);
            set_text_child(root, "cp:keywords", builtin_properties_.keywords);
            set_text_child(root, "dc:description", builtin_properties_.comments);
            set_text_child(root,
                           "cp:lastModifiedBy",
                           builtin_properties_.manager);  // using manager as lastModifiedBy
            set_text_child(root, "cp:category", builtin_properties_.category);
            set_text_child(root, "cp:contentStatus", builtin_properties_.content_status);
            set_text_child(root, "cp:contentType", builtin_properties_.content_type);
            set_text_child(root, "cp:revision", builtin_properties_.revision);

            if (builtin_properties_.created != 0) {
                auto created = get_or_create_child(root, "dcterms:created");
                created.append_attribute("xsi:type").set_value("dcterms:W3CDTF");
                created.append_child(pugi::node_pcdata)
                    .set_value(time_to_w3cdtf(builtin_properties_.created).c_str());
            }
            if (builtin_properties_.modified != 0) {
                auto modified = get_or_create_child(root, "dcterms:modified");
                modified.append_attribute("xsi:type").set_value("dcterms:W3CDTF");
                modified.append_child(pugi::node_pcdata)
                    .set_value(time_to_w3cdtf(builtin_properties_.modified).c_str());
            }
            if (builtin_properties_.last_printed != 0) {
                set_text_child(
                    root, "cp:lastPrinted", time_to_w3cdtf(builtin_properties_.last_printed));
            }
        }
        mark_modified("docProps/core.xml");
    }

    // Sync app.xml
    pugi::xml_document* app_doc = get_app_properties();
    if (app_doc) {
        auto root = app_doc->child("Properties");
        if (root) {
            set_text_child(root, "Template", builtin_properties_.template_name);
            set_text_child(root, "Application", "CDocx");
            set_text_child(root, "Company", builtin_properties_.company);
            set_text_child(root, "AppVersion", "16.0000");

            if (builtin_properties_.total_pages >= 0) {
                set_text_child(root, "Pages", std::to_string(builtin_properties_.total_pages));
            }
            if (builtin_properties_.total_words >= 0) {
                set_text_child(root, "Words", std::to_string(builtin_properties_.total_words));
            }
            if (builtin_properties_.total_chars >= 0) {
                set_text_child(root, "Characters", std::to_string(builtin_properties_.total_chars));
            }
            if (builtin_properties_.total_lines >= 0) {
                set_text_child(root, "Lines", std::to_string(builtin_properties_.total_lines));
            }
            if (builtin_properties_.total_paragraphs >= 0) {
                set_text_child(
                    root, "Paragraphs", std::to_string(builtin_properties_.total_paragraphs));
            }
        }
        mark_modified("docProps/app.xml");
    }
}

void Document::sync_builtin_properties_from_physical() {
    // Load core.xml
    pugi::xml_document* core_doc = get_core_properties();
    if (core_doc) {
        auto root = core_doc->child("cp:coreProperties");
        if (root) {
            if (auto n = root.child("dc:title").first_child())
                builtin_properties_.title = n.value();
            if (auto n = root.child("dc:subject").first_child())
                builtin_properties_.subject = n.value();
            if (auto n = root.child("dc:creator").first_child())
                builtin_properties_.author = n.value();
            if (auto n = root.child("cp:keywords").first_child())
                builtin_properties_.keywords = n.value();
            if (auto n = root.child("dc:description").first_child())
                builtin_properties_.comments = n.value();
            if (auto n = root.child("cp:lastModifiedBy").first_child())
                builtin_properties_.manager = n.value();
            if (auto n = root.child("cp:category").first_child())
                builtin_properties_.category = n.value();
            if (auto n = root.child("cp:contentStatus").first_child())
                builtin_properties_.content_status = n.value();
            if (auto n = root.child("cp:contentType").first_child())
                builtin_properties_.content_type = n.value();
            if (auto n = root.child("cp:revision").first_child())
                builtin_properties_.revision = n.value();
            if (auto n = root.child("dcterms:created").first_child())
                builtin_properties_.created = w3cdtf_to_time(n.value());
            if (auto n = root.child("dcterms:modified").first_child())
                builtin_properties_.modified = w3cdtf_to_time(n.value());
            if (auto n = root.child("cp:lastPrinted").first_child())
                builtin_properties_.last_printed = w3cdtf_to_time(n.value());
        }
    }

    // Load app.xml
    pugi::xml_document* app_doc = get_app_properties();
    if (app_doc) {
        auto root = app_doc->child("Properties");
        if (root) {
            if (auto n = root.child("Template").first_child())
                builtin_properties_.template_name = n.value();
            if (auto n = root.child("Company").first_child())
                builtin_properties_.company = n.value();
            if (auto n = root.child("Pages").first_child())
                builtin_properties_.total_pages = std::atoi(n.value());
            if (auto n = root.child("Words").first_child())
                builtin_properties_.total_words = std::atoi(n.value());
            if (auto n = root.child("Characters").first_child())
                builtin_properties_.total_chars = std::atoi(n.value());
            if (auto n = root.child("Lines").first_child())
                builtin_properties_.total_lines = std::atoi(n.value());
            if (auto n = root.child("Paragraphs").first_child())
                builtin_properties_.total_paragraphs = std::atoi(n.value());
        }
    }
}

// ============================================================================
// Custom Properties Sync
// ============================================================================

void Document::sync_custom_properties_to_physical() {
    if (custom_properties_.custom_properties.empty()) {
        // Remove custom.xml if no custom properties
        if (has_xml_part("docProps/custom.xml")) {
            remove_xml_part("docProps/custom.xml");
            // Remove relationship
            std::string rel_id = find_relationship_id("_rels/.rels", "docProps/custom.xml");
            if (!rel_id.empty()) {
                remove_relationship("_rels/.rels", rel_id);
            }
        }
        return;
    }

    pugi::xml_document* custom_doc = get_xml_part("docProps/custom.xml");
    if (!custom_doc) {
        custom_doc = &create_xml_part("docProps/custom.xml");
        add_content_type_override(
            "/docProps/custom.xml",
            "application/vnd.openxmlformats-officedocument.custom-properties+xml");

        std::string rel_id = find_relationship_id("_rels/.rels", "docProps/custom.xml");
        if (rel_id.empty()) {
            add_relationship("_rels/.rels",
                             "http://schemas.openxmlformats.org/officeDocument/2006/relationships/"
                             "custom-properties",
                             "docProps/custom.xml");
        }
    }

    custom_doc->reset();
    auto root = custom_doc->append_child("Properties");
    root.append_attribute("xmlns").set_value(
        "http://schemas.openxmlformats.org/officeDocument/2006/custom-properties");
    root.append_attribute("xmlns:vt")
        .set_value("http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");

    int pid = 2;
    for (const auto& kv : custom_properties_.custom_properties) {
        auto prop = root.append_child("property");
        prop.append_attribute("fmtid").set_value("{D5CDD505-2E9C-101B-9397-08002B2CF9AE}");
        prop.append_attribute("pid").set_value(pid++);
        prop.append_attribute("name").set_value(kv.first.c_str());
        auto val = prop.append_child("vt:lpwstr");
        val.append_child(pugi::node_pcdata).set_value(kv.second.c_str());
    }

    mark_modified("docProps/custom.xml");
}

void Document::sync_custom_properties_from_physical() {
    custom_properties_.custom_properties.clear();

    pugi::xml_document* custom_doc = get_xml_part("docProps/custom.xml");
    if (!custom_doc)
        return;

    auto root = custom_doc->child("Properties");
    if (!root)
        return;

    for (auto prop = root.child("property"); prop; prop = prop.next_sibling("property")) {
        pugi::xml_attribute name_attr = prop.attribute("name");
        if (!name_attr)
            continue;

        std::string value;
        if (auto lpwstr = prop.child("vt:lpwstr").first_child()) {
            value = lpwstr.value();
        } else if (auto text = prop.first_child().first_child()) {
            value = text.value();
        }

        custom_properties_.custom_properties[name_attr.value()] = value;
    }
}

// ============================================================================
// DOM -> Physical (Serialization)
// ============================================================================

void Document::merge_sections_from_physical() {
    auto doc_xml = get_document_xml();
    if (!doc_xml)
        return;

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body)
        return;

    // Parse XML section ranges
    struct SectionRange {
        pugi::xml_node begin;
        pugi::xml_node end;
    };
    std::vector<SectionRange> ranges;

    pugi::xml_node current_begin = body.first_child();
    for (auto node = body.first_child(); node; node = node.next_sibling()) {
        if (std::strcmp(node.name(), "w:sectPr") == 0) {
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
        auto section = dom_sections_vec[i];
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
            if (std::strcmp(name, "w:p") == 0) {
                if (auto para = parse_paragraph_from_xml(node)) {
                    xml_children.push_back(para);
                }
            } else if (std::strcmp(name, "w:tbl") == 0) {
                if (auto table = parse_table_from_xml(node)) {
                    xml_children.push_back(table);
                }
            }
        }

        // Merge by position: replace dirty-linked paragraphs, keep others,
        // append extra XML children, preserve extra DOM children
        size_t merge_count = std::min(dom_children.size(), xml_children.size());
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
            section->set_sectPr_node(ranges[i].end);
            section->load_properties();
        }
    }

    sections_dirty_ = false;
}

void Document::sync_sections_to_physical() {
    auto doc_xml = get_document_xml();
    if (!doc_xml)
        return;

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body)
        return;

    // If DOM has no sections, preserve existing XML
    auto sections = get_sections();
    if (sections.is_empty()) {
        return;
    }

    // Count XML paragraph/table children
    int xml_child_count = 0;
    for (auto child = body.first_child(); child; child = child.next_sibling()) {
        const char* name = child.name();
        if (std::strcmp(name, "w:p") == 0 || std::strcmp(name, "w:tbl") == 0) {
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
    // If XML has more content than DOM, legacy API or DocumentBuilder may have
    // modified XML directly. Use merge when DocumentBuilder is involved to
    // preserve DOM-only content; otherwise fall back to full sync.
    if (xml_child_count > dom_child_count) {
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
        if (std::strcmp(name, "w:p") != 0 && std::strcmp(name, "w:tbl") != 0 &&
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

static void serialize_run_formatting_to_xml(pugi::xml_node run_xml,
                                              const Font& font,
                                              pugi::xml_node preserved_rPr) {
    bool has_formatting = font.bold || font.italic || font.strikethrough ||
                          font.underline != UnderlineType::None || font.size > 0 ||
                          !font.name.empty() || font.color != Color::auto_color() ||
                          font.script_type != ScriptType::Normal || font.shading.has_fill() ||
                          font.spacing != 0 || font.scale != 100;

    if (!has_formatting && !preserved_rPr)
        return;

    auto rPr = run_xml.child("w:rPr");
    if (!rPr) {
        if (preserved_rPr) {
            rPr = run_xml.prepend_copy(preserved_rPr);
            // Strip whitespace text nodes from pretty-printed XML
            for (pugi::xml_node child = rPr.first_child(); child;) {
                pugi::xml_node next = child.next_sibling();
                if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata) {
                    rPr.remove_child(child);
                }
                child = next;
            }
        } else {
            rPr = run_xml.prepend_child("w:rPr");
        }
    }

    // Remember whether the original had w:szCs before we remove managed children
    bool original_had_szCs = preserved_rPr && preserved_rPr.child("w:szCs");

    // Remove managed children that we will re-serialize from DOM font state.
    // w:rFonts is handled separately: if font.name is empty we leave the
    // original rFonts untouched so that attributes like w:hint survive.
    const char* managed[] = {"w:b",     "w:i",     "w:strike", "w:u",
                             "w:sz",    "w:szCs",  "w:color",  "w:vertAlign",
                             "w:spacing", "w:w",     "w:shd"};
    for (const char* name : managed) {
        pugi::xml_node child = rPr.child(name);
        if (child)
            rPr.remove_child(child);
    }
    if (!font.name.empty()) {
        pugi::xml_node child = rPr.child("w:rFonts");
        if (child)
            rPr.remove_child(child);
    }

    // Re-add managed children from current font state
    serialize_shading_to_xml(rPr, font.shading);
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
            case UnderlineType::Single:
                val = "single";
                break;
            case UnderlineType::Words:
                val = "words";
                break;
            case UnderlineType::Double:
                val = "double";
                break;
            case UnderlineType::Dotted:
                val = "dotted";
                break;
            case UnderlineType::Dash:
                val = "dash";
                break;
            case UnderlineType::DashDot:
                val = "dashDot";
                break;
            case UnderlineType::DashDotDot:
                val = "dashDotDot";
                break;
            case UnderlineType::Wave:
                val = "wave";
                break;
            case UnderlineType::Thick:
                val = "thick";
                break;
            case UnderlineType::DottedHeavy:
                val = "dottedHeavy";
                break;
            case UnderlineType::DashHeavy:
                val = "dashHeavy";
                break;
            case UnderlineType::DashDotHeavy:
                val = "dashDotHeavy";
                break;
            case UnderlineType::DashDotDotHeavy:
                val = "dashDotDotHeavy";
                break;
            case UnderlineType::WaveHeavy:
                val = "waveHeavy";
                break;
            default:
                break;
        }
        u.append_attribute("w:val").set_value(val);
    }
    if (font.size > 0) {
        auto sz = rPr.append_child("w:sz");
        sz.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
        if (original_had_szCs) {
            auto szCs = rPr.append_child("w:szCs");
            szCs.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
        }
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
    if (font.spacing != 0) {
        auto sp = rPr.append_child("w:spacing");
        sp.append_attribute("w:val").set_value(static_cast<int>(font.spacing * 20));
    }
    if (font.scale != 100) {
        auto w = rPr.append_child("w:w");
        w.append_attribute("w:val").set_value(font.scale);
    }
}

static void serialize_run_to_xml(pugi::xml_node parent, Run* run) {
    if (!run)
        return;

    auto run_xml = parent.append_child("w:r");
    serialize_run_formatting_to_xml(run_xml, run->get_font(),
                                     run->has_preserved_rPr() ? run->get_preserved_rPr()
                                                              : pugi::xml_node());

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
    if (!field)
        return;

    auto begin_run = parent.append_child("w:r");
    begin_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("begin");

    std::string code = field->get_full_field_code();
    if (!code.empty()) {
        auto instr_run = parent.append_child("w:r");
        auto instr_text = instr_run.append_child("w:instrText");
        instr_text.append_attribute("xml:space").set_value("preserve");
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

static void serialize_form_field_to_xml(pugi::xml_node parent, FormField* field) {
    if (!field)
        return;

    int bookmark_id = 0;
    if (!field->get_name().empty()) {
        auto bm_start = parent.append_child("w:bookmarkStart");
        bookmark_id =
            field->get_document() ? field->get_document()->generate_unique_bookmark_id() : 1;
        bm_start.append_attribute("w:id").set_value(bookmark_id);
        bm_start.append_attribute("w:name").set_value(field->get_name().c_str());
    }

    auto begin_run = parent.append_child("w:r");
    auto fld_char = begin_run.append_child("w:fldChar");
    fld_char.append_attribute("w:fldCharType").set_value("begin");

    auto ff_data = fld_char.append_child("w:ffData");
    if (!field->get_name().empty()) {
        ff_data.append_child("w:name").append_attribute("w:val").set_value(
            field->get_name().c_str());
    }
    ff_data.append_child("w:enabled")
        .append_attribute("w:val")
        .set_value(field->get_enabled() ? "1" : "0");
    ff_data.append_child("w:calcOnExit")
        .append_attribute("w:val")
        .set_value(field->get_calculate_on_exit() ? "1" : "0");

    switch (field->get_form_field_type()) {
        case FormFieldType::TextInput: {
            auto text_input = ff_data.append_child("w:textInput");
            const char* type_val = "regular";
            switch (field->get_text_input_type()) {
                case TextFormFieldType::Number:
                    type_val = "number";
                    break;
                case TextFormFieldType::Date:
                    type_val = "date";
                    break;
                case TextFormFieldType::CurrentDate:
                    type_val = "currentDate";
                    break;
                case TextFormFieldType::CurrentTime:
                    type_val = "currentTime";
                    break;
                case TextFormFieldType::Calculated:
                    type_val = "calculated";
                    break;
                default:
                    break;
            }
            text_input.append_child("w:type").append_attribute("w:val").set_value(type_val);
            if (!field->get_text_input_default().empty()) {
                text_input.append_child("w:default")
                    .append_attribute("w:val")
                    .set_value(field->get_text_input_default().c_str());
            }
            if (field->get_max_length() > 0) {
                text_input.append_child("w:maxLength")
                    .append_attribute("w:val")
                    .set_value(field->get_max_length());
            }
            if (!field->get_text_input_format().empty()) {
                text_input.append_child("w:format")
                    .append_attribute("w:val")
                    .set_value(field->get_text_input_format().c_str());
            }
            break;
        }
        case FormFieldType::CheckBox: {
            auto check_box = ff_data.append_child("w:checkBox");
            if (field->get_is_check_box_exact_size() && field->get_check_box_size() > 0) {
                auto size = check_box.append_child("w:size");
                size.append_attribute("w:val").set_value(
                    static_cast<int>(field->get_check_box_size() * 2));
            } else {
                check_box.append_child("w:sizeAuto");
            }
            check_box.append_child("w:default")
                .append_attribute("w:val")
                .set_value(field->get_default_value() ? "1" : "0");
            check_box.append_child("w:checked")
                .append_attribute("w:val")
                .set_value(field->get_checked() ? "1" : "0");
            break;
        }
        case FormFieldType::ComboBox: {
            auto dd_list = ff_data.append_child("w:ddList");
            for (const auto& item : field->get_drop_down_items()) {
                dd_list.append_child("w:listEntry")
                    .append_attribute("w:val")
                    .set_value(item.c_str());
            }
            if (field->get_drop_down_selected_index() >= 0) {
                dd_list.append_child("w:default")
                    .append_attribute("w:val")
                    .set_value(field->get_drop_down_selected_index());
            }
            break;
        }
    }

    auto instr_run = parent.append_child("w:r");
    auto instr_text = instr_run.append_child("w:instrText");
    const char* instr = "FORMTEXT";
    if (field->get_form_field_type() == FormFieldType::CheckBox) {
        instr = "FORMCHECKBOX";
    } else if (field->get_form_field_type() == FormFieldType::ComboBox) {
        instr = "FORMDROPDOWN";
    }
    instr_text.text().set(instr);

    auto sep_run = parent.append_child("w:r");
    sep_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("separate");

    std::string result = field->get_result();
    if (!result.empty()) {
        auto res_run = parent.append_child("w:r");
        auto text_node = res_run.append_child("w:t");
        text_node.text().set(result.c_str());
    }

    auto end_run = parent.append_child("w:r");
    end_run.append_child("w:fldChar").append_attribute("w:fldCharType").set_value("end");

    if (bookmark_id != 0) {
        auto bm_end = parent.append_child("w:bookmarkEnd");
        bm_end.append_attribute("w:id").set_value(bookmark_id);
    }
}

static void serialize_hyperlink_to_xml(pugi::xml_node parent, Hyperlink* link) {
    if (!link)
        return;

    auto hyperlink_xml = parent.append_child("w:hyperlink");

    std::string address = link->get_address();
    std::string bookmark = link->get_bookmark_name();

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
    serialize_run_formatting_to_xml(run_xml, link->get_font(),
                                     link->has_preserved_rPr() ? link->get_preserved_rPr()
                                                              : pugi::xml_node());

    std::string result = link->get_result();
    if (!result.empty()) {
        auto text_node = run_xml.append_child("w:t");
        text_node.text().set(result.c_str());
    }
}

static void serialize_special_char_to_xml(pugi::xml_node parent, SpecialChar* sc) {
    if (!sc)
        return;
    char16_t code = sc->get_char();
    switch (code) {
        case 0x0009:  // Tab
            parent.append_child("w:tab");
            break;
        case 0x000A:  // Line break
            parent.append_child("w:br");
            break;
        case 0x000C:  // Page break
        {
            auto br = parent.append_child("w:br");
            br.append_attribute("w:type").set_value("page");
            break;
        }
        case 0x000E:  // Column break
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

static void serialize_paragraph_format_to_xml(pugi::xml_node para_xml,
                                              const ParagraphFormat& format) {
    bool has_format =
        format.alignment != ParagraphAlignment::Left || format.left_indent != 0 ||
        format.right_indent != 0 || format.first_line_indent != 0 || format.space_before != 0 ||
        format.space_after != 0 || format.line_spacing != 1.15 || !format.style_name.empty() ||
        format.shading.has_fill() || format.drop_cap_position != DropCapPosition::None;

    if (!has_format)
        return;

    auto pPr = para_xml.prepend_child("w:pPr");

    serialize_shading_to_xml(pPr, format.shading);

    if (format.drop_cap_position != DropCapPosition::None) {
        auto dropCap = pPr.append_child("w:dropCap");
        dropCap.append_attribute("w:lines").set_value(format.lines_to_drop);
        const char* type_str = "drop";
        if (format.drop_cap_position == DropCapPosition::Margin) {
            type_str = "margin";
        }
        dropCap.append_attribute("w:type").set_value(type_str);
    }

    if (!format.style_name.empty()) {
        auto pStyle = pPr.append_child("w:pStyle");
        pStyle.append_attribute("w:val").set_value(format.style_name.c_str());
    }

    if (format.alignment != ParagraphAlignment::Left) {
        auto jc = pPr.append_child("w:jc");
        const char* val = "left";
        switch (format.alignment) {
            case ParagraphAlignment::Center:
                val = "center";
                break;
            case ParagraphAlignment::Right:
                val = "right";
                break;
            case ParagraphAlignment::Justify:
                val = "both";
                break;
            case ParagraphAlignment::Distributed:
                val = "distribute";
                break;
            default:
                break;
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
            ind.append_attribute("w:firstLine")
                .set_value(static_cast<int>(format.first_line_indent * 20));
        }
    }

    if (format.space_before != 0 || format.space_after != 0 || format.line_spacing != 1.15) {
        auto spacing = pPr.append_child("w:spacing");
        if (format.space_before != 0) {
            spacing.append_attribute("w:before")
                .set_value(static_cast<int>(format.space_before * 20));
        }
        if (format.space_after != 0) {
            spacing.append_attribute("w:after").set_value(
                static_cast<int>(format.space_after * 20));
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
    if (!list_format.is_list_item())
        return;

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
    if (!bookmark)
        return;
    auto xml = parent.append_child("w:bookmarkStart");
    xml.append_attribute("w:id").set_value(bookmark->get_id());
    xml.append_attribute("w:name").set_value(bookmark->get_name().c_str());
}

static void serialize_bookmark_end_to_xml(pugi::xml_node parent, BookmarkEnd* bookmark) {
    if (!bookmark)
        return;
    auto xml = parent.append_child("w:bookmarkEnd");
    xml.append_attribute("w:id").set_value(bookmark->get_id());
}

static void serialize_comment_range_start_to_xml(pugi::xml_node parent,
                                                 CommentRangeStart* comment) {
    if (!comment)
        return;
    auto xml = parent.append_child("w:commentRangeStart");
    xml.append_attribute("w:id").set_value(comment->get_id());
}

static void serialize_comment_range_end_to_xml(pugi::xml_node parent, CommentRangeEnd* comment) {
    if (!comment)
        return;
    auto xml = parent.append_child("w:commentRangeEnd");
    xml.append_attribute("w:id").set_value(comment->get_id());
}

static void serialize_comment_reference_to_xml(pugi::xml_node parent, int id) {
    auto r = parent.append_child("w:r");
    auto ref = r.append_child("w:commentReference");
    ref.append_attribute("w:id").set_value(id);
}

static void serialize_paragraph_to_xml(pugi::xml_node parent, Paragraph* para) {
    if (!para)
        return;
    auto para_xml = parent.append_child("w:p");

    serialize_paragraph_format_to_xml(para_xml, para->get_paragraph_format());
    serialize_list_format_to_xml(para_xml, para->get_list_format());

    // Preserve unmanaged pPr children and attributes that ParagraphFormat doesn't track.
    if (para->has_preserved_pPr()) {
        pugi::xml_node preserved_pPr = para->get_preserved_pPr();
        pugi::xml_node pPr = para_xml.child("w:pPr");
        if (!pPr) {
            para_xml.prepend_copy(preserved_pPr);
        } else {
            for (pugi::xml_node child = preserved_pPr.first_child(); child;
                 child = child.next_sibling()) {
                // Skip whitespace text nodes from pretty-printed XML
                if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata)
                    continue;
                const char* name = child.name();
                pugi::xml_node existing = pPr.child(name);
                if (!existing) {
                    pPr.append_copy(child);
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
            case NodeType::FootnoteReference: {
                auto ref = para_xml.append_child("w:footnoteReference");
                if (auto* fnr = dynamic_cast<FootnoteReference*>(child.get())) {
                    ref.append_attribute("w:id").set_value(fnr->get_id());
                }
                break;
            }
            case NodeType::EndnoteReference: {
                auto ref = para_xml.append_child("w:endnoteReference");
                if (auto* enr = dynamic_cast<EndnoteReference*>(child.get())) {
                    ref.append_attribute("w:id").set_value(enr->get_id());
                }
                break;
            }
            case NodeType::FieldSeparator:
            case NodeType::FieldEnd:
                // These node types are not used as standalone DOM nodes
                break;
            default:
                break;
        }
    }
    // Add comment references after the paragraph content
    for (int comment_id : comment_ids_for_reference) {
        serialize_comment_reference_to_xml(para_xml, comment_id);
    }
}

static void serialize_cell_to_xml(pugi::xml_node parent, Cell* cell) {
    if (!cell)
        return;
    auto tc = parent.append_child("w:tc");

    // Cell properties
    const CellFormat& fmt = cell->get_cell_format();
    bool has_props = fmt.width != 0 || fmt.vertical_alignment != CellVerticalAlignment::Top ||
                     fmt.horizontal_merge > 1 || fmt.vertical_merge ||
                     fmt.borders.has_visible() || fmt.shading.has_fill();
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
                case CellVerticalAlignment::Center:
                    val = "center";
                    break;
                case CellVerticalAlignment::Bottom:
                    val = "bottom";
                    break;
                default:
                    break;
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
        serialize_borders_to_xml(tcPr, "w:tcBorders", fmt.borders);
        serialize_shading_to_xml(tcPr, fmt.shading);
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
    if (!row)
        return;
    auto tr = parent.append_child("w:tr");

    const RowFormat& fmt = row->get_row_format();
    bool has_row_props = fmt.height != 0 || fmt.heading || !fmt.allow_break_across_pages;
    if (has_row_props) {
        auto trPr = tr.append_child("w:trPr");
        if (fmt.height != 0) {
            auto trHeight = trPr.append_child("w:trHeight");
            trHeight.append_attribute("w:val").set_value(static_cast<int>(fmt.height * 20));
            trHeight.append_attribute("w:hRule").set_value(fmt.height_rule_exact ? "exact"
                                                                                 : "atLeast");
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
    if (!table)
        return;
    auto tbl = parent.append_child("w:tbl");

    // Table properties
    const TableFormat& fmt = table->get_table_format();
    pugi::xml_node tblPr;
    if (table->has_preserved_tblPr()) {
        tblPr = tbl.append_copy(table->get_preserved_tblPr());
        // Strip whitespace text nodes from pretty-printed XML
        for (pugi::xml_node child = tblPr.first_child(); child;) {
            pugi::xml_node next = child.next_sibling();
            if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata) {
                tblPr.remove_child(child);
            }
            child = next;
        }
        // Remove managed children so we can re-serialize current DOM state
        const char* managed[] = {"w:tblW", "w:tblLayout", "w:jc",
                                 "w:tblInd", "w:tblStyle", "w:shd", "w:tblBorders"};
        for (const char* name : managed) {
            pugi::xml_node child = tblPr.child(name);
            if (child)
                tblPr.remove_child(child);
        }
    } else {
        tblPr = tbl.append_child("w:tblPr");
    }

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
            case TableAlignment::Center:
                align_val = "center";
                break;
            case TableAlignment::Right:
                align_val = "right";
                break;
            default:
                break;
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

    serialize_shading_to_xml(tblPr, fmt.shading);
    serialize_borders_to_xml(tblPr, "w:tblBorders", fmt.borders);

    // Table grid
    if (table->has_preserved_tblGrid()) {
        tbl.append_copy(table->get_preserved_tblGrid());
    } else {
        auto rows = table->get_rows();
        if (rows.get_count() > 0) {
            auto tblGrid = tbl.append_child("w:tblGrid");
            auto first_row = rows.first();
            if (first_row) {
                auto cells = first_row->get_cells();
                for (size_t c = 0; c < cells.get_count(); ++c) {
                    tblGrid.append_child("w:gridCol");
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

static void serialize_body_to_xml(pugi::xml_node body_xml, Body* body) {
    if (!body)
        return;
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

static void serialize_header_footer_to_xml(HeaderFooter* hf, Document* doc) {
    if (!hf || !doc)
        return;
    auto xml_doc = doc->get_xml_part(hf->get_part_path());
    if (!xml_doc)
        return;

    auto root = xml_doc->child("w:hdr");
    if (!root)
        root = xml_doc->child("w:ftr");
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
        switch (child->node_type()) {
            case NodeType::Paragraph:
                serialize_paragraph_to_xml(root, dynamic_cast<Paragraph*>(child.get()));
                break;
            case NodeType::Table:
                serialize_table_to_xml(root, dynamic_cast<Table*>(child.get()));
                break;
            default:
                break;
        }
    }

    doc->mark_modified(hf->get_part_path());
}

static void serialize_section_to_xml(pugi::xml_node body_xml, Section* section) {
    if (!section)
        return;

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
            case HeaderFooterType::First:
                type_str = "first";
                break;
            case HeaderFooterType::Even:
                type_str = "even";
                break;
            default:
                break;
        }
        headerRef.append_attribute("w:type").set_value(type_str);
    }
    for (const auto& ref : section->get_footer_refs()) {
        auto footerRef = sectPr.append_child("w:footerReference");
        footerRef.append_attribute("r:id").set_value(ref.relationship_id.c_str());
        const char* type_str = "default";
        switch (ref.type) {
            case HeaderFooterType::First:
                type_str = "first";
                break;
            case HeaderFooterType::Even:
                type_str = "even";
                break;
            default:
                break;
        }
        footerRef.append_attribute("w:type").set_value(type_str);
    }

    // Serialize header/footer content
    for (auto& header : section->get_all_headers()) {
        serialize_header_footer_to_xml(header.get(), section->get_document());
    }
    for (auto& footer : section->get_all_footers()) {
        serialize_header_footer_to_xml(footer.get(), section->get_document());
    }
}

// ============================================================================
// Physical -> DOM (Deserialization)
// ============================================================================

void Document::sync_sections_from_physical() {
    auto doc_xml = get_document_xml();
    if (!doc_xml)
        return;

    auto body = doc_xml->child("w:document").child("w:body");
    if (!body)
        return;

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
            for (auto ref = range.end.child("w:headerReference"); ref;
                 ref = ref.next_sibling("w:headerReference")) {
                HeaderFooterRef hf_ref;
                hf_ref.relationship_id = ref.attribute("r:id").value();
                const char* type_val = ref.attribute("w:type").value();
                if (std::strcmp(type_val, "first") == 0)
                    hf_ref.type = HeaderFooterType::First;
                else if (std::strcmp(type_val, "even") == 0)
                    hf_ref.type = HeaderFooterType::Even;
                else
                    hf_ref.type = HeaderFooterType::Default;
                // part_path will be resolved from relationships
                section->add_header_ref(hf_ref);
            }
            for (auto ref = range.end.child("w:footerReference"); ref;
                 ref = ref.next_sibling("w:footerReference")) {
                HeaderFooterRef hf_ref;
                hf_ref.relationship_id = ref.attribute("r:id").value();
                const char* type_val = ref.attribute("w:type").value();
                if (std::strcmp(type_val, "first") == 0)
                    hf_ref.type = HeaderFooterType::First;
                else if (std::strcmp(type_val, "even") == 0)
                    hf_ref.type = HeaderFooterType::Even;
                else
                    hf_ref.type = HeaderFooterType::Default;
                section->add_footer_ref(hf_ref);
            }

            // Parse header/footer content from XML into DOM
            for (auto& header : section->get_all_headers()) {
                auto xml_doc = get_xml_part(header->get_part_path());
                if (xml_doc) {
                    auto root = xml_doc->child("w:hdr");
                    if (root) {
                        header->remove_all_children();
                        for (auto node = root.first_child(); node; node = node.next_sibling()) {
                            const char* name = node.name();
                            if (std::strcmp(name, "w:p") == 0) {
                                if (auto para = parse_paragraph_from_xml(node)) {
                                    header->append_child(para);
                                }
                            } else if (std::strcmp(name, "w:tbl") == 0) {
                                if (auto table = parse_table_from_xml(node)) {
                                    header->append_child(table);
                                }
                            }
                        }
                    }
                }
            }
            for (auto& footer : section->get_all_footers()) {
                auto xml_doc = get_xml_part(footer->get_part_path());
                if (xml_doc) {
                    auto root = xml_doc->child("w:ftr");
                    if (root) {
                        footer->remove_all_children();
                        for (auto node = root.first_child(); node; node = node.next_sibling()) {
                            const char* name = node.name();
                            if (std::strcmp(name, "w:p") == 0) {
                                if (auto para = parse_paragraph_from_xml(node)) {
                                    footer->append_child(para);
                                }
                            } else if (std::strcmp(name, "w:tbl") == 0) {
                                if (auto table = parse_table_from_xml(node)) {
                                    footer->append_child(table);
                                }
                            }
                        }
                    }
                }
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
    if (!run || !run_node)
        return;

    auto rPr = run_node.child("w:rPr");
    if (!rPr) {
        // No explicit formatting: set font to empty so defaults aren't serialized
        Font empty_font;
        empty_font.size = 0;
        empty_font.name = "";
        empty_font.name_far_east = "";
        empty_font.color = Color::auto_color();
        run->set_font(empty_font);
        return;
    }

    // Preserve the original rPr for round-trip fidelity of unmanaged properties
    run->preserve_rPr(rPr);

    Font font;
    // Reset defaults to "not set" so only explicitly present properties are serialized
    font.size = 0;
    font.name = "";
    font.name_far_east = "";
    font.color = Color::auto_color();
    if (rPr.child("w:b"))
        font.bold = true;
    if (rPr.child("w:i"))
        font.italic = true;
    if (rPr.child("w:strike"))
        font.strikethrough = true;

    auto u = rPr.child("w:u");
    if (u) {
        const char* val = u.attribute("w:val").value();
        if (std::strcmp(val, "single") == 0)
            font.underline = UnderlineType::Single;
        else if (std::strcmp(val, "words") == 0)
            font.underline = UnderlineType::Words;
        else if (std::strcmp(val, "double") == 0)
            font.underline = UnderlineType::Double;
        else if (std::strcmp(val, "dotted") == 0)
            font.underline = UnderlineType::Dotted;
        else if (std::strcmp(val, "dash") == 0)
            font.underline = UnderlineType::Dash;
        else if (std::strcmp(val, "dashDot") == 0)
            font.underline = UnderlineType::DashDot;
        else if (std::strcmp(val, "dashDotDot") == 0)
            font.underline = UnderlineType::DashDotDot;
        else if (std::strcmp(val, "wave") == 0)
            font.underline = UnderlineType::Wave;
        else if (std::strcmp(val, "thick") == 0)
            font.underline = UnderlineType::Thick;
        else if (std::strcmp(val, "dottedHeavy") == 0)
            font.underline = UnderlineType::DottedHeavy;
        else if (std::strcmp(val, "dashHeavy") == 0)
            font.underline = UnderlineType::DashHeavy;
        else if (std::strcmp(val, "dashDotHeavy") == 0)
            font.underline = UnderlineType::DashDotHeavy;
        else if (std::strcmp(val, "dashDotDotHeavy") == 0)
            font.underline = UnderlineType::DashDotDotHeavy;
        else if (std::strcmp(val, "waveHeavy") == 0)
            font.underline = UnderlineType::WaveHeavy;
        else
            font.underline = UnderlineType::Single;
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
        if (std::strcmp(val, "superscript") == 0)
            font.script_type = ScriptType::Superscript;
        else if (std::strcmp(val, "subscript") == 0)
            font.script_type = ScriptType::Subscript;
    }

    auto sp = rPr.child("w:spacing");
    if (sp) {
        font.spacing = sp.attribute("w:val").as_int() / 20.0;
    }

    auto w = rPr.child("w:w");
    if (w) {
        font.scale = w.attribute("w:val").as_int(100);
    }

    parse_shading_from_xml(rPr.child("w:shd"), font.shading);

    run->set_font(font);
}

std::shared_ptr<Run> Document::parse_run_from_xml(pugi::xml_node run_node) {
    if (!run_node)
        return nullptr;

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

std::shared_ptr<Paragraph> Document::parse_paragraph_from_xml(pugi::xml_node para_node) {
    if (!para_node)
        return nullptr;

    auto para = std::make_shared<Paragraph>(this);
    para->set_current(para_node);

    // Parse paragraph properties
    auto pPr = para_node.child("w:pPr");
    if (pPr) {
        para->preserve_pPr(pPr);
        auto jc = pPr.child("w:jc");
        if (jc) {
            const char* val = jc.attribute("w:val").value();
            if (std::strcmp(val, "center") == 0)
                para->get_paragraph_format().alignment = ParagraphAlignment::Center;
            else if (std::strcmp(val, "right") == 0)
                para->get_paragraph_format().alignment = ParagraphAlignment::Right;
            else if (std::strcmp(val, "both") == 0)
                para->get_paragraph_format().alignment = ParagraphAlignment::Justify;
            else if (std::strcmp(val, "distribute") == 0)
                para->get_paragraph_format().alignment = ParagraphAlignment::Distributed;
        }

        auto ind = pPr.child("w:ind");
        if (ind) {
            para->get_paragraph_format().left_indent = ind.attribute("w:left").as_int() / 20.0;
            para->get_paragraph_format().right_indent = ind.attribute("w:right").as_int() / 20.0;
            para->get_paragraph_format().first_line_indent =
                ind.attribute("w:firstLine").as_int() / 20.0;
        }

        auto spacing = pPr.child("w:spacing");
        if (spacing) {
            para->get_paragraph_format().space_before =
                spacing.attribute("w:before").as_int() / 20.0;
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

        parse_shading_from_xml(pPr.child("w:shd"), para->get_paragraph_format().shading);

        auto dropCap = pPr.child("w:dropCap");
        if (dropCap) {
            para->get_paragraph_format().lines_to_drop = dropCap.attribute("w:lines").as_int(1);
            const char* type_val = dropCap.attribute("w:type").value();
            if (std::strcmp(type_val, "margin") == 0) {
                para->get_paragraph_format().drop_cap_position = DropCapPosition::Margin;
            } else {
                para->get_paragraph_format().drop_cap_position = DropCapPosition::Normal;
            }
        }

        auto numPr = pPr.child("w:numPr");
        if (numPr) {
            auto ilvl = numPr.child("w:ilvl");
            auto numId = numPr.child("w:numId");
            if (numId) {
                para->get_list_format().list_id = numId.attribute("w:val").as_uint();
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
                    // Parse form field
                    FormFieldType fftype = FormFieldType::TextInput;
                    auto ff_textInput = ff_data.child("w:textInput");
                    auto ff_checkBox = ff_data.child("w:checkBox");
                    auto ff_ddList = ff_data.child("w:ddList");
                    if (ff_checkBox) {
                        fftype = FormFieldType::CheckBox;
                    } else if (ff_ddList) {
                        fftype = FormFieldType::ComboBox;
                    }

                    auto form_field = std::make_shared<FormField>(this, fftype);

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

                    if (ff_textInput) {
                        auto ttype = ff_textInput.child("w:type");
                        if (ttype) {
                            const char* tv = ttype.attribute("w:val").value();
                            if (std::strcmp(tv, "number") == 0)
                                form_field->set_text_input_type(TextFormFieldType::Number);
                            else if (std::strcmp(tv, "date") == 0)
                                form_field->set_text_input_type(TextFormFieldType::Date);
                            else if (std::strcmp(tv, "currentDate") == 0)
                                form_field->set_text_input_type(TextFormFieldType::CurrentDate);
                            else if (std::strcmp(tv, "currentTime") == 0)
                                form_field->set_text_input_type(TextFormFieldType::CurrentTime);
                            else if (std::strcmp(tv, "calculated") == 0)
                                form_field->set_text_input_type(TextFormFieldType::Calculated);
                        }
                        auto tdef = ff_textInput.child("w:default");
                        if (tdef) {
                            form_field->set_text_input_default(tdef.attribute("w:val").value());
                        }
                        auto tmax = ff_textInput.child("w:maxLength");
                        if (tmax) {
                            form_field->set_max_length(tmax.attribute("w:val").as_int());
                        }
                        auto tfmt = ff_textInput.child("w:format");
                        if (tfmt) {
                            form_field->set_text_input_format(tfmt.attribute("w:val").value());
                        }
                    } else if (ff_checkBox) {
                        auto cb_default = ff_checkBox.child("w:default");
                        if (cb_default) {
                            form_field->set_default_value(cb_default.attribute("w:val").as_int() !=
                                                          0);
                        }
                        auto cb_checked = ff_checkBox.child("w:checked");
                        if (cb_checked) {
                            form_field->set_checked(cb_checked.attribute("w:val").as_int() != 0);
                        }
                        auto cb_size = ff_checkBox.child("w:size");
                        if (cb_size) {
                            form_field->set_is_check_box_exact_size(true);
                            form_field->set_check_box_size(cb_size.attribute("w:val").as_int() /
                                                           2.0);
                        } else {
                            form_field->set_is_check_box_exact_size(false);
                        }
                    } else if (ff_ddList) {
                        std::vector<std::string> items;
                        for (auto entry = ff_ddList.child("w:listEntry"); entry;
                             entry = entry.next_sibling("w:listEntry")) {
                            items.push_back(entry.attribute("w:val").value());
                        }
                        form_field->set_drop_down_items(items);
                        auto dd_default = ff_ddList.child("w:default");
                        if (dd_default) {
                            form_field->set_drop_down_selected_index(
                                dd_default.attribute("w:val").as_int());
                        }
                    }

                    // Parse field sequence for result
                    std::string field_result;
                    bool in_result = false;
                    for (auto field_child = child; field_child;
                         field_child = field_child.next_sibling()) {
                        if (std::strcmp(field_child.name(), "w:r") != 0)
                            continue;

                        auto fc = field_child.child("w:fldChar");
                        if (fc) {
                            const char* fct = fc.attribute("w:fldCharType").value();
                            if (std::strcmp(fct, "separate") == 0) {
                                in_result = true;
                                continue;
                            } else if (std::strcmp(fct, "end") == 0) {
                                child = field_child;
                                break;
                            }
                        }

                        auto text_node = field_child.child("w:t");
                        if (text_node && in_result) {
                            field_result += text_node.text().get();
                        }
                    }
                    form_field->set_result(field_result);
                    para->append_child(form_field);
                } else {
                    // Parse regular field sequence
                    auto field = std::make_shared<Field>(this, FieldType::Unknown);
                    std::string field_code;
                    std::string field_result;
                    bool in_result = false;

                    for (auto field_child = child; field_child;
                         field_child = field_child.next_sibling()) {
                        if (std::strcmp(field_child.name(), "w:r") != 0)
                            continue;

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

                    // Parse base code and switches from instruction text
                    std::string trimmed = field_code;
                    size_t trim_start = 0;
                    while (trim_start < trimmed.size() &&
                           std::isspace(static_cast<unsigned char>(trimmed[trim_start]))) {
                        ++trim_start;
                    }
                    size_t trim_end = trimmed.size();
                    while (trim_end > trim_start &&
                           std::isspace(static_cast<unsigned char>(trimmed[trim_end - 1]))) {
                        --trim_end;
                    }
                    trimmed = trimmed.substr(trim_start, trim_end - trim_start);

                    size_t switch_pos = std::string::npos;
                    for (size_t i = 0; i + 1 < trimmed.size(); ++i) {
                        if (trimmed[i] == ' ' && trimmed[i + 1] == '\\') {
                            switch_pos = i;
                            break;
                        }
                    }

                    if (switch_pos == std::string::npos) {
                        field->set_field_code(trimmed);
                    } else {
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
                            while (!last_switch.empty() &&
                                   std::isspace(static_cast<unsigned char>(last_switch.back()))) {
                                last_switch.pop_back();
                            }
                            if (!last_switch.empty()) {
                                field->add_switch(last_switch);
                            }
                        }
                    }

                    field->set_result(field_result);
                    para->append_child(field);
                }
            } else if (auto run = parse_run_from_xml(child)) {
                para->append_child(run);
            }
        } else if (std::strcmp(name, "w:hyperlink") == 0) {
            auto hyperlink = std::make_shared<Hyperlink>(this);

            const char* rel_id = child.attribute("r:id").value();
            if (rel_id && *rel_id) {
                std::string target =
                    get_relationship_target("word/_rels/document.xml.rels", rel_id);
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
            for (auto run_node = child.child("w:r"); run_node;
                 run_node = run_node.next_sibling("w:r")) {
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
        } else if (std::strcmp(name, "w:commentRangeStart") == 0) {
            auto comment = std::make_shared<CommentRangeStart>(this);
            comment->set_id(child.attribute("w:id").as_int());
            para->append_child(comment);
        } else if (std::strcmp(name, "w:commentRangeEnd") == 0) {
            auto comment = std::make_shared<CommentRangeEnd>(this);
            comment->set_id(child.attribute("w:id").as_int());
            para->append_child(comment);
        } else if (std::strcmp(name, "w:commentReference") == 0) {
            // Skip comment references - they are auto-generated during serialization
            continue;
        } else if (std::strcmp(name, "w:footnoteReference") == 0) {
            auto ref = std::make_shared<FootnoteReference>(this);
            ref->set_id(child.attribute("w:id").as_int());
            para->append_child(ref);
        } else if (std::strcmp(name, "w:endnoteReference") == 0) {
            auto ref = std::make_shared<EndnoteReference>(this);
            ref->set_id(child.attribute("w:id").as_int());
            para->append_child(ref);
        }
    }

    return para;
}

std::shared_ptr<Table> Document::parse_table_from_xml(pugi::xml_node table_node) {
    if (!table_node)
        return nullptr;

    auto table = std::make_shared<Table>(this);

    // Parse table properties
    auto tblPr = table_node.child("w:tblPr");
    if (tblPr) {
        table->preserve_tblPr(tblPr);
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
        parse_shading_from_xml(tblPr.child("w:shd"), table->get_table_format().shading);
        parse_borders_from_xml(tblPr.child("w:tblBorders"), table->get_table_format().borders);
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
    auto tblGrid = table_node.child("w:tblGrid");
    if (tblGrid) {
        table->preserve_tblGrid(tblGrid);
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
                    cell->get_cell_format().horizontal_merge =
                        gridSpan.attribute("w:val").as_int(1);
                    if (cell->get_cell_format().horizontal_merge < 1) {
                        cell->get_cell_format().horizontal_merge = 1;
                    }
                }
                auto vMerge = tcPr.child("w:vMerge");
                if (vMerge) {
                    cell->get_cell_format().vertical_merge = true;
                    const char* vmerge_val = vMerge.attribute("w:val").value();
                    cell->get_cell_format().vertical_merge_start =
                        (std::strcmp(vmerge_val, "restart") == 0);
                }
                parse_shading_from_xml(tcPr.child("w:shd"), cell->get_cell_format().shading);
                parse_borders_from_xml(tcPr.child("w:tcBorders"), cell->get_cell_format().borders);
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
    if (!body_node)
        return nullptr;

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
    if (std::strcmp(str, "character") == 0)
        return StyleType::Character;
    if (std::strcmp(str, "table") == 0)
        return StyleType::Table;
    if (std::strcmp(str, "numbering") == 0)
        return StyleType::List;
    return StyleType::Paragraph;
}

static void serialize_style_paragraph_format_to_xml(pugi::xml_node pPr,
                                                    const ParagraphFormat& format) {
    serialize_shading_to_xml(pPr, format.shading);

    if (format.drop_cap_position != DropCapPosition::None) {
        auto dropCap = pPr.append_child("w:dropCap");
        dropCap.append_attribute("w:lines").set_value(format.lines_to_drop);
        const char* type_str = "drop";
        if (format.drop_cap_position == DropCapPosition::Margin) {
            type_str = "margin";
        }
        dropCap.append_attribute("w:type").set_value(type_str);
    }

    if (format.alignment != ParagraphAlignment::Left) {
        auto jc = pPr.append_child("w:jc");
        const char* val = "left";
        switch (format.alignment) {
            case ParagraphAlignment::Center:
                val = "center";
                break;
            case ParagraphAlignment::Right:
                val = "right";
                break;
            case ParagraphAlignment::Justify:
                val = "both";
                break;
            case ParagraphAlignment::Distributed:
                val = "distribute";
                break;
            default:
                break;
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
            ind.append_attribute("w:firstLine")
                .set_value(static_cast<int>(format.first_line_indent * 20));
        }
    }

    if (format.space_before != 0 || format.space_after != 0 || format.line_spacing != 1.15) {
        auto spacing = pPr.append_child("w:spacing");
        if (format.space_before != 0) {
            spacing.append_attribute("w:before")
                .set_value(static_cast<int>(format.space_before * 20));
        }
        if (format.space_after != 0) {
            spacing.append_attribute("w:after").set_value(
                static_cast<int>(format.space_after * 20));
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
    if (!rPr)
        return;

    // Reset defaults to "not set" so only explicitly present properties are serialized
    font.size = 0;
    font.name = "";
    font.name_far_east = "";
    font.color = Color::auto_color();

    if (rPr.child("w:b"))
        font.bold = true;
    if (rPr.child("w:i"))
        font.italic = true;
    if (rPr.child("w:strike"))
        font.strikethrough = true;

    auto u = rPr.child("w:u");
    if (u) {
        const char* val = u.attribute("w:val").value();
        if (std::strcmp(val, "single") == 0)
            font.underline = UnderlineType::Single;
        else if (std::strcmp(val, "words") == 0)
            font.underline = UnderlineType::Words;
        else if (std::strcmp(val, "double") == 0)
            font.underline = UnderlineType::Double;
        else if (std::strcmp(val, "dotted") == 0)
            font.underline = UnderlineType::Dotted;
        else if (std::strcmp(val, "dash") == 0)
            font.underline = UnderlineType::Dash;
        else if (std::strcmp(val, "dashDot") == 0)
            font.underline = UnderlineType::DashDot;
        else if (std::strcmp(val, "dashDotDot") == 0)
            font.underline = UnderlineType::DashDotDot;
        else if (std::strcmp(val, "wave") == 0)
            font.underline = UnderlineType::Wave;
        else if (std::strcmp(val, "thick") == 0)
            font.underline = UnderlineType::Thick;
        else if (std::strcmp(val, "dottedHeavy") == 0)
            font.underline = UnderlineType::DottedHeavy;
        else if (std::strcmp(val, "dashHeavy") == 0)
            font.underline = UnderlineType::DashHeavy;
        else if (std::strcmp(val, "dashDotHeavy") == 0)
            font.underline = UnderlineType::DashDotHeavy;
        else if (std::strcmp(val, "dashDotDotHeavy") == 0)
            font.underline = UnderlineType::DashDotDotHeavy;
        else if (std::strcmp(val, "waveHeavy") == 0)
            font.underline = UnderlineType::WaveHeavy;
        else
            font.underline = UnderlineType::Single;
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
        if (std::strcmp(val, "superscript") == 0)
            font.script_type = ScriptType::Superscript;
        else if (std::strcmp(val, "subscript") == 0)
            font.script_type = ScriptType::Subscript;
    }

    parse_shading_from_xml(rPr.child("w:shd"), font.shading);
}

static void parse_style_paragraph_format_from_xml(pugi::xml_node pPr, ParagraphFormat& format) {
    if (!pPr)
        return;

    parse_shading_from_xml(pPr.child("w:shd"), format.shading);

    auto dropCap = pPr.child("w:dropCap");
    if (dropCap) {
        format.lines_to_drop = dropCap.attribute("w:lines").as_int(1);
        const char* type_val = dropCap.attribute("w:type").value();
        if (std::strcmp(type_val, "margin") == 0) {
            format.drop_cap_position = DropCapPosition::Margin;
        } else {
            format.drop_cap_position = DropCapPosition::Normal;
        }
    }

    auto jc = pPr.child("w:jc");
    if (jc) {
        const char* val = jc.attribute("w:val").value();
        if (std::strcmp(val, "center") == 0)
            format.alignment = ParagraphAlignment::Center;
        else if (std::strcmp(val, "right") == 0)
            format.alignment = ParagraphAlignment::Right;
        else if (std::strcmp(val, "both") == 0)
            format.alignment = ParagraphAlignment::Justify;
        else if (std::strcmp(val, "distribute") == 0)
            format.alignment = ParagraphAlignment::Distributed;
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
    bool has_para_format = para_format.alignment != ParagraphAlignment::Left ||
                           para_format.left_indent != 0 || para_format.right_indent != 0 ||
                           para_format.first_line_indent != 0 || para_format.space_before != 0 ||
                           para_format.space_after != 0 || para_format.line_spacing != 1.15;

    // Merge w:rPr: preserve unknown children, overlay managed ones
    auto rPr = style_xml.child("w:rPr");
    if (has_font_formatting) {
        if (!rPr) {
            rPr = style_xml.append_child("w:rPr");
        }
        // Check if original rPr had szCs before we remove anything
        bool original_had_szCs = rPr.child("w:szCs") != nullptr;

        // Remove managed children that we will re-serialize
        static const char* managed_rPr[] = {"w:b",   "w:i",     "w:strike", "w:u",
                                              "w:sz",  "w:szCs",  "w:rFonts", "w:color",
                                              "w:vertAlign", "w:spacing", "w:w", "w:shd"};
        for (const char* tag : managed_rPr) {
            for (auto child = rPr.child(tag); child; child = rPr.child(tag)) {
                rPr.remove_child(child);
            }
        }
        // Serialize current DOM font formatting into the existing rPr
        auto run_xml = rPr.parent().append_child("w:r");
        serialize_run_formatting_to_xml(run_xml, font, pugi::xml_node());
        auto new_rPr = run_xml.child("w:rPr");
        if (new_rPr) {
            // Move all children from new_rPr into the existing rPr
            for (auto child = new_rPr.first_child(); child;) {
                auto next = child.next_sibling();
                rPr.append_move(child);
                child = next;
            }
            run_xml.parent().remove_child(run_xml);
        }
        // Restore szCs if the original had it and we have a font size
        if (original_had_szCs && font.size > 0) {
            auto szCs = rPr.append_child("w:szCs");
            szCs.append_attribute("w:val").set_value(static_cast<int>(font.size * 2));
        }
    }

    // Merge w:pPr: preserve unknown children, overlay managed ones
    auto pPr = style_xml.child("w:pPr");
    if (has_para_format) {
        if (!pPr) {
            pPr = style_xml.append_child("w:pPr");
        }
        // Remove managed children that we will re-serialize
        static const char* managed_pPr[] = {"w:jc", "w:ind", "w:spacing", "w:shd", "w:dropCap"};
        for (const char* tag : managed_pPr) {
            for (auto child = pPr.child(tag); child; child = pPr.child(tag)) {
                pPr.remove_child(child);
            }
        }
        serialize_style_paragraph_format_to_xml(pPr, para_format);
    }
}

static std::shared_ptr<Style> parse_style_from_xml(pugi::xml_node style_node, Document* doc) {
    if (!style_node)
        return nullptr;

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
    if (!styles_root)
        return;

    for (auto style_node = styles_root.child("w:style"); style_node;
         style_node = style_node.next_sibling("w:style")) {
        if (auto style = parse_style_from_xml(style_node, this)) {
            if (styles_) {
                styles_->add(style);
            }
        }
    }
}

// ============================================================================
// Comment Sync
// ============================================================================

void Document::sync_comments_to_physical() {
    if (comments_cache_.empty()) {
        return;
    }

    auto comments_xml = get_xml_part("word/comments.xml");
    if (!comments_xml) {
        comments_xml = &create_xml_part("word/comments.xml");
    }

    auto root = comments_xml->child("w:comments");
    if (!root) {
        root = comments_xml->prepend_child("w:comments");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:w14")
            .set_value("http://schemas.microsoft.com/office/word/2010/wordml");
        root.append_attribute("xmlns:w15")
            .set_value("http://schemas.microsoft.com/office/word/2012/wordml");
    }

    // Remove existing comment nodes
    for (auto child = root.first_child(); child;) {
        auto next = child.next_sibling();
        if (std::strcmp(child.name(), "w:comment") == 0) {
            root.remove_child(child);
        }
        child = next;
    }

    for (const auto& comment : comments_cache_) {
        auto cxml = root.append_child("w:comment");
        cxml.append_attribute("w:id").set_value(comment->get_id());
        cxml.append_attribute("w:author").set_value(comment->get_author().c_str());
        cxml.append_attribute("w:initials").set_value(comment->get_initial().c_str());

        auto dt = comment->get_date_time();
        auto time_t = std::chrono::system_clock::to_time_t(dt);
        std::tm tm = {};
#if defined(_WIN32)
        gmtime_s(&tm, &time_t);
#else
        gmtime_r(&time_t, &tm);
#endif
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
        cxml.append_attribute("w:date").set_value(buf);

        // Serialize comment paragraphs
        for (const auto& child : comment->get_children()) {
            if (child->node_type() == NodeType::Paragraph) {
                serialize_paragraph_to_xml(cxml, dynamic_cast<Paragraph*>(child.get()));
            }
        }
    }

    mark_modified("word/comments.xml");
}

void Document::sync_comments_from_physical() {
    auto comments_xml = get_xml_part("word/comments.xml");
    if (!comments_xml) {
        return;
    }

    comments_cache_.clear();

    auto root = comments_xml->child("w:comments");
    if (!root) {
        return;
    }

    for (auto cxml = root.child("w:comment"); cxml; cxml = cxml.next_sibling("w:comment")) {
        auto comment = std::make_shared<Comment>(this);
        comment->set_id(cxml.attribute("w:id").as_int());
        comment->set_author(cxml.attribute("w:author").value());
        comment->set_initial(cxml.attribute("w:initials").value());

        const char* date_str = cxml.attribute("w:date").value();
        if (date_str && *date_str) {
            std::tm tm = {};
            std::sscanf(date_str,
                        "%d-%d-%dT%d:%d:%dZ",
                        &tm.tm_year,
                        &tm.tm_mon,
                        &tm.tm_mday,
                        &tm.tm_hour,
                        &tm.tm_min,
                        &tm.tm_sec);
            tm.tm_year -= 1900;
            tm.tm_mon -= 1;
            auto time = timegm(&tm);
            comment->set_date_time(std::chrono::system_clock::from_time_t(time));
        }

        for (auto para_node = cxml.child("w:p"); para_node;
             para_node = para_node.next_sibling("w:p")) {
            auto para = parse_paragraph_from_xml(para_node);
            if (para) {
                comment->append_child(para);
            }
        }

        comments_cache_.push_back(comment);
    }

    for (const auto& comment : comments_cache_) {
        if (comment->get_id() >= next_comment_id_) {
            next_comment_id_ = comment->get_id() + 1;
        }
    }
}

// ============================================================================
// Footnote Sync
// ============================================================================

void Document::sync_footnotes_to_physical() {
    auto footnotes_xml = get_xml_part("word/footnotes.xml");
    if (!footnotes_xml) {
        if (footnotes_cache_.empty()) {
            return;
        }
        footnotes_xml = &create_xml_part("word/footnotes.xml");
    }

    auto root = footnotes_xml->child("w:footnotes");
    if (!root) {
        root = footnotes_xml->prepend_child("w:footnotes");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    }

    // Collect separator nodes to preserve them
    std::vector<pugi::xml_node> separators;
    for (auto child = root.first_child(); child;) {
        auto next = child.next_sibling();
        int note_id = child.attribute("w:id").as_int();
        if (note_id < 0 || note_id == 0) {
            // Keep separator/continuationSeparator references
            separators.push_back(child);
        }
        root.remove_child(child);
        child = next;
    }

    // Re-add separators first, or create them if missing
    if (separators.empty()) {
        auto sep = root.prepend_child("w:footnote");
        sep.append_attribute("w:id").set_value(-1);
        sep.append_attribute("w:type").set_value("separator");
        auto sep_para = sep.append_child("w:p");
        auto sep_run = sep_para.append_child("w:r");
        sep_run.append_child("w:separator");

        auto cont_sep = root.prepend_child("w:footnote");
        cont_sep.append_attribute("w:id").set_value(0);
        cont_sep.append_attribute("w:type").set_value("continuationSeparator");
        auto cont_para = cont_sep.append_child("w:p");
        auto cont_run = cont_para.append_child("w:r");
        cont_run.append_child("w:continuationSeparator");
    } else {
        for (auto& sep : separators) {
            root.append_copy(sep);
        }
    }

    for (const auto& footnote : footnotes_cache_) {
        auto fxml = root.append_child("w:footnote");
        fxml.append_attribute("w:id").set_value(footnote->get_id());
        if (!footnote->is_auto() && !footnote->get_reference_mark().empty()) {
            fxml.append_attribute("w:type").set_value("normal");
        }

        for (const auto& child : footnote->get_children()) {
            if (child->node_type() == NodeType::Paragraph) {
                serialize_paragraph_to_xml(fxml, dynamic_cast<Paragraph*>(child.get()));
            }
        }
    }

    mark_modified("word/footnotes.xml");
}

void Document::sync_footnotes_from_physical() {
    auto footnotes_xml = get_xml_part("word/footnotes.xml");
    if (!footnotes_xml) {
        return;
    }

    footnotes_cache_.clear();

    auto root = footnotes_xml->child("w:footnotes");
    if (!root) {
        return;
    }

    for (auto fxml = root.child("w:footnote"); fxml; fxml = fxml.next_sibling("w:footnote")) {
        int id = fxml.attribute("w:id").as_int();
        if (id < 0 || id == 0) {
            // Skip separator and continuationSeparator
            continue;
        }

        auto footnote = std::make_shared<Footnote>(this, FootnoteType::Footnote);
        footnote->set_id(id);

        const char* type_attr = fxml.attribute("w:type").value();
        if (type_attr && std::strcmp(type_attr, "normal") == 0) {
            footnote->set_auto(false);
        }

        for (auto para_node = fxml.child("w:p"); para_node;
             para_node = para_node.next_sibling("w:p")) {
            auto para = parse_paragraph_from_xml(para_node);
            if (para) {
                footnote->append_child(para);
            }
        }

        footnotes_cache_.push_back(footnote);
    }

    for (const auto& footnote : footnotes_cache_) {
        if (footnote->get_id() >= next_footnote_id_) {
            next_footnote_id_ = footnote->get_id() + 1;
        }
    }
}

// ============================================================================
// Endnote Sync
// ============================================================================

void Document::sync_endnotes_to_physical() {
    auto endnotes_xml = get_xml_part("word/endnotes.xml");
    if (!endnotes_xml) {
        if (endnotes_cache_.empty()) {
            return;
        }
        endnotes_xml = &create_xml_part("word/endnotes.xml");
    }

    auto root = endnotes_xml->child("w:endnotes");
    if (!root) {
        root = endnotes_xml->prepend_child("w:endnotes");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:r").set_value(
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    }

    // Collect separator nodes to preserve them
    std::vector<pugi::xml_node> separators;
    for (auto child = root.first_child(); child;) {
        auto next = child.next_sibling();
        int note_id = child.attribute("w:id").as_int();
        if (note_id < 0 || note_id == 0) {
            separators.push_back(child);
        }
        root.remove_child(child);
        child = next;
    }

    // Re-add separators first, or create them if missing
    if (separators.empty()) {
        auto sep = root.prepend_child("w:endnote");
        sep.append_attribute("w:id").set_value(-1);
        sep.append_attribute("w:type").set_value("separator");
        auto sep_para = sep.append_child("w:p");
        auto sep_run = sep_para.append_child("w:r");
        sep_run.append_child("w:separator");

        auto cont_sep = root.prepend_child("w:endnote");
        cont_sep.append_attribute("w:id").set_value(0);
        cont_sep.append_attribute("w:type").set_value("continuationSeparator");
        auto cont_para = cont_sep.append_child("w:p");
        auto cont_run = cont_para.append_child("w:r");
        cont_run.append_child("w:continuationSeparator");
    } else {
        for (auto& sep : separators) {
            root.append_copy(sep);
        }
    }

    for (const auto& endnote : endnotes_cache_) {
        auto exml = root.append_child("w:endnote");
        exml.append_attribute("w:id").set_value(endnote->get_id());
        if (!endnote->is_auto() && !endnote->get_reference_mark().empty()) {
            exml.append_attribute("w:type").set_value("normal");
        }

        for (const auto& child : endnote->get_children()) {
            if (child->node_type() == NodeType::Paragraph) {
                serialize_paragraph_to_xml(exml, dynamic_cast<Paragraph*>(child.get()));
            }
        }
    }

    mark_modified("word/endnotes.xml");
}

void Document::sync_endnotes_from_physical() {
    auto endnotes_xml = get_xml_part("word/endnotes.xml");
    if (!endnotes_xml) {
        return;
    }

    endnotes_cache_.clear();

    auto root = endnotes_xml->child("w:endnotes");
    if (!root) {
        return;
    }

    for (auto exml = root.child("w:endnote"); exml; exml = exml.next_sibling("w:endnote")) {
        int id = exml.attribute("w:id").as_int();
        if (id < 0 || id == 0) {
            continue;
        }

        auto endnote = std::make_shared<Footnote>(this, FootnoteType::Endnote);
        endnote->set_id(id);

        const char* type_attr = exml.attribute("w:type").value();
        if (type_attr && std::strcmp(type_attr, "normal") == 0) {
            endnote->set_auto(false);
        }

        for (auto para_node = exml.child("w:p"); para_node;
             para_node = para_node.next_sibling("w:p")) {
            auto para = parse_paragraph_from_xml(para_node);
            if (para) {
                endnote->append_child(para);
            }
        }

        endnotes_cache_.push_back(endnote);
    }

    for (const auto& endnote : endnotes_cache_) {
        if (endnote->get_id() >= next_endnote_id_) {
            next_endnote_id_ = endnote->get_id() + 1;
        }
    }
}

}  // namespace cdocx
