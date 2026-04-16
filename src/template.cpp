/**
 * @file template.cpp
 * @brief Template class implementation
 * @details Implementation of placeholder replacement
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/template.h>
#include <cdocx/document.h>
#include <cdocx/table.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/advanced.h>
#include <pugixml.hpp>
#include <filesystem>

namespace cdocx {

// ============================================================================
// Constructor
// ============================================================================

Template::Template(Document* document) : doc_(document) {}

Template::Template(Document* document, const std::string& prefix, const std::string& suffix)
    : doc_(document), pattern_prefix_(prefix), pattern_suffix_(suffix) {}

// ============================================================================
// Placeholder Management
// ============================================================================

void Template::set(const std::string& key, const std::string& value) {
    placeholders_[key] = value;
}

void Template::set(const std::string& key, const char* value) {
    placeholders_[key] = std::string(value);
}

void Template::set_image(const std::string& key, const std::string& image_path) {
    image_placeholders_[key] = image_path;
}

void Template::set_pattern(const std::string& prefix, const std::string& suffix) {
    pattern_prefix_ = prefix;
    pattern_suffix_ = suffix;
}

void Template::clear() {
    placeholders_.clear();
    image_placeholders_.clear();
}

// ============================================================================
// Text Replacement
// ============================================================================

bool Template::try_replace_in_text(std::string& text) {
    bool replaced = false;

    for (const auto& [key, value] : placeholders_) {
        std::string pattern = pattern_prefix_ + key + pattern_suffix_;
        size_t pos = 0;
        while ((pos = text.find(pattern, pos)) != std::string::npos) {
            text.replace(pos, pattern.length(), value);
            pos += value.length();
            replaced = true;
        }
    }

    return replaced;
}

// ============================================================================
// FSM-based Cross-Run Placeholder Replacement
// ============================================================================

bool Template::try_replace_single_run(Run& r) {
    std::string text = r.get_text();
    if (try_replace_in_text(text)) {
        r.set_text(text);
        return true;
    }
    return false;
}

void Template::transition_to_collecting_state(PlaceholderContext& ctx, Run& r,
                                              const std::string& text, size_t prefix_pos) {
    ctx.first_run = &r;
    ctx.prefix_pos = prefix_pos;
    ctx.collected_text = text.substr(prefix_pos);
    ctx.runs_to_delete.clear();
}

bool Template::try_replace_placeholder(const PlaceholderContext& ctx, Paragraph& p) {
    (void)p;
    if (!ctx.first_run) return false;

    size_t best_pos = std::string::npos;
    std::string best_value;
    std::string best_pattern;

    for (const auto& [key, value] : placeholders_) {
        std::string pattern = pattern_prefix_ + key + pattern_suffix_;
        size_t pos = ctx.collected_text.find(pattern);
        if (pos != std::string::npos) {
            if (best_pos == std::string::npos || pos < best_pos) {
                best_pos = pos;
                best_value = value;
                best_pattern = pattern;
            }
        }
    }

    if (best_pos == std::string::npos) return false;

    size_t pattern_end = best_pos + best_pattern.length();
    std::string trailing = ctx.collected_text.substr(pattern_end);

    std::string first_run_text = ctx.first_run->get_text();
    std::string new_text = first_run_text.substr(0, ctx.prefix_pos) + best_value + trailing;
    ctx.first_run->set_text(new_text);
    return true;
}

void Template::delete_collected_runs(const PlaceholderContext& ctx, Paragraph& p) {
    for (Run* run : ctx.runs_to_delete) {
        for (auto& child : p.get_children()) {
            if (child.get() == run) {
                p.remove_child(child);
                break;
            }
        }
    }
}

void Template::process_paragraph(Paragraph& p) {
    PlaceholderContext ctx;
    ctx.clear();

    int i = 0;
    while (i < static_cast<int>(p.get_child_count())) {
        auto child = p.get_child(i);
        auto run = std::dynamic_pointer_cast<Run>(child);
        if (!run) {
            if (ctx.first_run) {
                ctx.clear();
            }
            ++i;
            continue;
        }

        std::string text = run->get_text();

        if (!ctx.first_run) {
            // Idle state: try single-run replacement first
            if (try_replace_single_run(*run)) {
                text = run->get_text();
            }

            size_t prefix_start = text.rfind(pattern_prefix_);
            if (prefix_start != std::string::npos) {
                std::string candidate = text.substr(prefix_start);
                bool has_complete = false;
                for (const auto& [key, value] : placeholders_) {
                    (void)value;
                    std::string pattern = pattern_prefix_ + key + pattern_suffix_;
                    if (candidate.find(pattern) != std::string::npos) {
                        has_complete = true;
                        break;
                    }
                }
                if (!has_complete) {
                    transition_to_collecting_state(ctx, *run, text, prefix_start);
                }
            }
            ++i;
        } else {
            // Collecting state: accumulate text across runs
            ctx.collected_text += text;
            ctx.runs_to_delete.push_back(run.get());

            if (try_replace_placeholder(ctx, p)) {
                delete_collected_runs(ctx, p);
                ctx.clear();
                i = 0;
                continue;
            }
            ++i;
        }
    }

    if (ctx.first_run) {
        ctx.clear();
    }
}

bool Template::process_paragraph_legacy(Paragraph& para) {
    process_paragraph(para);
    return true;
}

// ============================================================================
// Main Replacement Functions
// ============================================================================

bool Template::replace_image_in_run(const std::shared_ptr<Run>& run) {
    if (!run || !doc_) return false;

    std::string text = run->get_text();
    for (const auto& [key, image_path] : image_placeholders_) {
        std::string pattern = pattern_prefix_ + key + pattern_suffix_;
        if (text != pattern) continue;

        if (!std::filesystem::exists(image_path)) continue;

        ImageSize size;
        if (!detect_image_size(image_path, size)) continue;

        std::string rel_id = doc_->add_media_with_rel(image_path, nullptr);
        if (rel_id.empty()) continue;

        run->set_text("");

        pugi::xml_document drawing_doc;
        pugi::xml_node drawing = drawing_doc.append_child("w:drawing");
        drawing.append_attribute("xmlns:wp").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");

        pugi::xml_node inline_node = drawing.append_child("wp:inline");
        inline_node.append_attribute("distT").set_value(0);
        inline_node.append_attribute("distB").set_value(0);
        inline_node.append_attribute("distL").set_value(0);
        inline_node.append_attribute("distR").set_value(0);

        pugi::xml_node extent = inline_node.append_child("wp:extent");
        extent.append_attribute("cx").set_value(size.width_emu());
        extent.append_attribute("cy").set_value(size.height_emu());

        pugi::xml_node docPr = inline_node.append_child("wp:docPr");
        static int image_id_counter = 1;
        docPr.append_attribute("id").set_value(image_id_counter++);
        docPr.append_attribute("name").set_value("Picture");

        pugi::xml_node graphic = inline_node.append_child("a:graphic");
        graphic.append_attribute("xmlns:a").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/main");

        pugi::xml_node graphic_data = graphic.append_child("a:graphicData");
        graphic_data.append_attribute("uri").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node pic = graphic_data.append_child("pic:pic");
        pic.append_attribute("xmlns:pic").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node nvPicPr = pic.append_child("pic:nvPicPr");
        pugi::xml_node cnvPr = nvPicPr.append_child("pic:cNvPr");
        cnvPr.append_attribute("id").set_value(0);
        cnvPr.append_attribute("name").set_value(image_path.c_str());
        nvPicPr.append_child("pic:cNvPicPr");

        pugi::xml_node blipFill = pic.append_child("pic:blipFill");
        pugi::xml_node blip = blipFill.append_child("a:blip");
        blip.append_attribute("r:embed").set_value(rel_id.c_str());
        pugi::xml_node stretch = blipFill.append_child("a:stretch");
        stretch.append_child("a:fillRect");

        pugi::xml_node spPr = pic.append_child("pic:spPr");
        pugi::xml_node xfrm = spPr.append_child("a:xfrm");
        pugi::xml_node ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx").set_value(size.width_emu());
        ext.append_attribute("cy").set_value(size.height_emu());
        pugi::xml_node prstGeom = spPr.append_child("a:prstGeom");
        prstGeom.append_attribute("prst").set_value("rect");
        prstGeom.append_child("a:avLst");

        run->preserve_child(drawing);
        return true;
    }
    return false;
}

void Template::replace_in_paragraph(const std::shared_ptr<Paragraph>& para) {
    if (!para) return;

    // First pass: handle image placeholders (exact single-run match)
    for (auto& child : para->get_children()) {
        if (auto run = std::dynamic_pointer_cast<Run>(child)) {
            replace_image_in_run(run);
        }
    }

    // Second pass: handle text placeholders with FSM (cross-run support)
    process_paragraph(*para);
}

void Template::replace_in_table(const std::shared_ptr<Table>& table) {
    if (!table) return;
    for (auto& row_child : table->get_children()) {
        if (auto row = std::dynamic_pointer_cast<Row>(row_child)) {
            for (auto& cell_child : row->get_children()) {
                if (auto cell = std::dynamic_pointer_cast<Cell>(cell_child)) {
                    for (auto& para_child : cell->get_children()) {
                        if (auto para = std::dynamic_pointer_cast<Paragraph>(para_child)) {
                            replace_in_paragraph(para);
                        }
                    }
                }
            }
        }
    }
}

void Template::replace_in_paragraphs() {
    if (!doc_) return;
    auto paragraphs = doc_->get_paragraphs();
    for (auto& para : paragraphs) {
        replace_in_paragraph(para);
    }
}

void Template::replace_in_tables() {
    if (!doc_) return;
    auto tables = doc_->get_tables();
    for (auto& table : tables) {
        replace_in_table(table);
    }
}

void Template::replace_all() {
    if (!doc_ || !doc_->is_open()) {
        return;
    }
    replace_in_paragraphs();
    replace_in_tables();
    replace_in_headers_footers();
}

void Template::replace_in_headers_footers() {
    if (!doc_) return;
    for (auto& section : doc_->get_sections()) {
        if (!section) continue;
        for (auto& header : section->get_all_headers()) {
            if (!header) continue;
            for (auto& para : header->get_paragraphs()) {
                replace_in_paragraph(para);
            }
            for (auto& table : header->get_tables()) {
                replace_in_table(table);
            }
        }
        for (auto& footer : section->get_all_footers()) {
            if (!footer) continue;
            for (auto& para : footer->get_paragraphs()) {
                replace_in_paragraph(para);
            }
            for (auto& table : footer->get_tables()) {
                replace_in_table(table);
            }
        }
    }
}

bool Template::has_placeholders() const {
    return !placeholders_.empty() || !image_placeholders_.empty();
}

size_t Template::get_placeholder_count() const {
    return placeholders_.size() + image_placeholders_.size();
}

} // namespace cdocx
