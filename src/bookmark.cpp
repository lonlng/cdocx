/**
 * @file bookmark.cpp
 * @brief Bookmark and BookmarkCollection implementation
 * @since 0.3.0
 */

#include <cdocx/bookmark.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>

#include "sync_common.h"

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace cdocx {

// Bookmark Implementation
// ============================================================================

Bookmark::Bookmark() = default;

Bookmark::Bookmark(Document* doc, std::string name, pugi::xml_node start, pugi::xml_node end)
    : doc_(doc), name_(std::move(name)), start_node_(start), end_node_(end) {
}

std::string Bookmark::get_name() const {
    return name_;
}

void Bookmark::set_name(const std::string& name) {
    name_ = name;
    // Update XML attributes
    if (start_node_) {
        start_node_.attribute("w:name").set_value(name.c_str());
    }
    if (end_node_) {
        end_node_.attribute("w:name").set_value(name.c_str());
    }
}

std::string Bookmark::get_text() const {
    if (!is_valid()) {
        return "";
    }

    std::string result;

    const pugi::xml_node start_para = start_node_.parent();
    const pugi::xml_node end_para = end_node_.parent();

    // Simple case: same paragraph
    if (start_para == end_para) {
        bool inside = false;
        for (pugi::xml_node child = start_para.first_child(); child; child = child.next_sibling()) {
            if (child == start_node_) {
                inside = true;
                continue;
            }
            if (child == end_node_) {
                break;
            }
            if (inside) {
                const pugi::xml_node t = child.child("w:t");
                if (t) {
                    result += t.text().get();
                }
            }
        }
    } else {
        // Cross-paragraph: collect text after bookmark_start in start paragraph
        bool after_start = false;
        for (pugi::xml_node child = start_para.first_child(); child; child = child.next_sibling()) {
            if (child == start_node_) {
                after_start = true;
                continue;
            }
            if (after_start) {
                const pugi::xml_node t = child.child("w:t");
                if (t) {
                    result += t.text().get();
                }
            }
        }

        // Middle paragraphs: collect all text
        pugi::xml_node current = start_para.next_sibling("w:p");
        while (current && current != end_para) {
            result += collect_text_from_runs(current);
            current = current.next_sibling("w:p");
        }

        // End paragraph: collect text before bookmark_end
        for (pugi::xml_node child = end_para.first_child(); child; child = child.next_sibling()) {
            if (child == end_node_) {
                break;
            }
            const pugi::xml_node t = child.child("w:t");
            if (t) {
                result += t.text().get();
            }
        }
    }

    return result;
}

bool Bookmark::set_text(const std::string& text) {
    if (!is_valid()) {
        return false;
    }

    pugi::xml_node current = start_node_.parent();

    // Clear existing runs
    pugi::xml_node run = current.child("w:r");
    while (run) {
        const pugi::xml_node next = run.next_sibling("w:r");
        current.remove_child(run);
        run = next;
    }

    // Create new run with text
    pugi::xml_node new_run = current.append_child("w:r");
    const pugi::xml_node t = new_run.append_child("w:t");
    t.text().set(text.c_str());

    return true;
}

bool Bookmark::is_valid() const {
    return start_node_ && end_node_;
}

bool Bookmark::remove() {
    if (!is_valid()) {
        return false;
    }

    // Remove bookmark markers but keep content
    start_node_.parent().remove_child(start_node_);
    end_node_.parent().remove_child(end_node_);

    return true;
}

bool Bookmark::remove_with_content() {
    if (!is_valid()) {
        return false;
    }

    pugi::xml_node start_para = start_node_.parent();
    pugi::xml_node end_para = end_node_.parent();

    if (start_para == end_para) {
        // Same paragraph: remove all nodes between bookmark_start and bookmark_end
        pugi::xml_node current = start_node_.next_sibling();
        while (current && current != end_node_) {
            const pugi::xml_node next = current.next_sibling();
            start_para.remove_child(current);
            current = next;
        }
        start_para.remove_child(start_node_);
        start_para.remove_child(end_node_);
    } else {
        // Cross-paragraph
        // 1. Remove all content after bookmark_start in start paragraph
        pugi::xml_node current = start_node_.next_sibling();
        while (current) {
            const pugi::xml_node next = current.next_sibling();
            start_para.remove_child(current);
            current = next;
        }
        start_para.remove_child(start_node_);

        // 2. Remove intermediate paragraphs entirely
        pugi::xml_node mid_para = start_para.next_sibling("w:p");
        while (mid_para && mid_para != end_para) {
            const pugi::xml_node next = mid_para.next_sibling("w:p");
            start_para.parent().remove_child(mid_para);
            mid_para = next;
        }

        // 3. Remove all content before bookmark_end in end paragraph (inclusive of bookmark_end)
        std::vector<pugi::xml_node> to_remove;
        for (pugi::xml_node child = end_para.first_child(); child && child != end_node_;
             child = child.next_sibling()) {
            to_remove.push_back(child);
        }
        for (auto& node : to_remove) {
            end_para.remove_child(node);
        }
        end_para.remove_child(end_node_);
    }

    start_node_ = pugi::xml_node();
    end_node_ = pugi::xml_node();
    return true;
}

// ============================================================================
// Enhanced Format-Preserving Methods (v0.3.0)
// ============================================================================

BookmarkFormat Bookmark::get_format() const {
    BookmarkFormat fmt;

    if (!is_valid()) {
        return fmt;
    }

    // Get the paragraph containing the bookmark
    const pugi::xml_node para = start_node_.parent();

    // ========== Extract Paragraph Format (w:pPr) ==========
    const pugi::xml_node p_pr = para.child("w:pPr");
    if (p_pr) {
        // Alignment (w:jc)
        const pugi::xml_node jc = p_pr.child("w:jc");
        if (jc) {
            fmt.alignment = jc.attribute("w:val").value();
        }

        // Spacing (w:spacing)
        const pugi::xml_node spacing = p_pr.child("w:spacing");
        if (spacing) {
            fmt.line_spacing = spacing.attribute("w:line").as_int();
            fmt.line_rule = spacing.attribute("w:lineRule").value();
            fmt.space_before = spacing.attribute("w:before").as_int();
            fmt.space_after = spacing.attribute("w:after").as_int();
        }

        // Indentation (w:ind)
        const pugi::xml_node ind = p_pr.child("w:ind");
        if (ind) {
            fmt.first_line_indent = ind.attribute("w:firstLine").as_int();
            if (fmt.first_line_indent == 0) {
                // Check for hanging indent (negative first line)
                fmt.first_line_indent = -ind.attribute("w:hanging").as_int();
            }
            fmt.left_indent = ind.attribute("w:left").as_int();
            fmt.right_indent = ind.attribute("w:right").as_int();
        }

        // Keep with next (w:keepNext)
        fmt.keep_next = p_pr.child("w:keepNext") != nullptr;

        // Keep lines together (w:keepLines)
        fmt.keep_lines = p_pr.child("w:keepLines") != nullptr;

        // Page break before (w:pageBreakBefore)
        fmt.page_break_before = p_pr.child("w:pageBreakBefore") != nullptr;
    }

    // ========== Extract Character Format (w:rPr) ==========
    // Only look at runs between bookmarkStart and bookmarkEnd markers
    bool inside_bookmark = false;
    for (pugi::xml_node child = para.first_child(); child; child = child.next_sibling()) {
        if (child == start_node_) {
            inside_bookmark = true;
            continue;
        }
        if (child == end_node_) {
            break;
        }
        if (!inside_bookmark) {
            continue;
        }
        if (std::strcmp(child.name(), "w:r") != 0) {
            continue;
        }
        const pugi::xml_node r_pr = child.child("w:rPr");
        if (!r_pr) {
            continue;
        }

        // Extract fonts
        const pugi::xml_node r_fonts = r_pr.child("w:rFonts");
        if (r_fonts) {
            fmt.font_ascii = r_fonts.attribute("w:ascii").value();
            fmt.font_far_east = r_fonts.attribute("w:eastAsia").value();
            fmt.font_hansi = r_fonts.attribute("w:hAnsi").value();
            fmt.font_hint = r_fonts.attribute("w:hint").value();
        }

        // Extract font size
        const pugi::xml_node sz = r_pr.child("w:sz");
        if (sz) {
            fmt.font_size = sz.attribute("w:val").as_int();
        }

        // Extract color
        const pugi::xml_node color = r_pr.child("w:color");
        if (color) {
            fmt.color = color.attribute("w:val").value();
        }

        // Extract bold
        const pugi::xml_node b = r_pr.child("w:b");
        fmt.bold = b != nullptr;

        // Extract italic
        const pugi::xml_node i = r_pr.child("w:i");
        fmt.italic = i != nullptr;

        // Extract underline
        const pugi::xml_node u = r_pr.child("w:u");
        fmt.underline = u != nullptr;

        // Extract strikethrough
        const pugi::xml_node strike = r_pr.child("w:strike");
        fmt.strikethrough = strike != nullptr;

        // Format found, return it
        return fmt;
    }

    return fmt;
}

bool Bookmark::set_text_keep_format(const std::string& text) {
    if (!is_valid()) {
        return false;
    }

    // Extract existing format
    const BookmarkFormat fmt = get_format();

    // Use formatted text setting
    return set_text_formatted(text, fmt);
}

bool Bookmark::set_text_formatted(const std::string& text, const BookmarkFormat& format) {
    if (!is_valid()) {
        return false;
    }

    pugi::xml_node para = start_node_.parent();

    // ========== Apply Paragraph Format (w:pPr) ==========
    pugi::xml_node p_pr = para.child("w:pPr");
    if (!p_pr) {
        p_pr = para.prepend_child("w:pPr");
    }

    // Alignment (w:jc)
    if (!format.alignment.empty()) {
        pugi::xml_node jc = p_pr.child("w:jc");
        if (!jc) {
            jc = p_pr.append_child("w:jc");
        }
        jc.append_attribute("w:val").set_value(format.alignment.c_str());
    }

    // Spacing (w:spacing)
    if (format.line_spacing > 0 || format.space_before > 0 || format.space_after > 0 ||
        !format.line_rule.empty()) {
        pugi::xml_node spacing = p_pr.child("w:spacing");
        if (!spacing) {
            spacing = p_pr.append_child("w:spacing");
        }
        if (format.line_spacing > 0) {
            spacing.append_attribute("w:line").set_value(format.line_spacing);
        }
        if (!format.line_rule.empty()) {
            spacing.append_attribute("w:lineRule").set_value(format.line_rule.c_str());
        }
        if (format.space_before > 0) {
            spacing.append_attribute("w:before").set_value(format.space_before);
        }
        if (format.space_after > 0) {
            spacing.append_attribute("w:after").set_value(format.space_after);
        }
    }

    // Indentation (w:ind)
    if (format.first_line_indent != 0 || format.left_indent > 0 || format.right_indent > 0) {
        pugi::xml_node ind = p_pr.child("w:ind");
        if (!ind) {
            ind = p_pr.append_child("w:ind");
        }
        if (format.first_line_indent > 0) {
            ind.append_attribute("w:firstLine").set_value(format.first_line_indent);
        } else if (format.first_line_indent < 0) {
            ind.append_attribute("w:hanging").set_value(-format.first_line_indent);
        }
        if (format.left_indent > 0) {
            ind.append_attribute("w:left").set_value(format.left_indent);
        }
        if (format.right_indent > 0) {
            ind.append_attribute("w:right").set_value(format.right_indent);
        }
    }

    // Keep with next (w:keepNext)
    if (format.keep_next) {
        ensure_child(p_pr, "w:keepNext");
    }

    // Keep lines together (w:keepLines)
    if (format.keep_lines) {
        ensure_child(p_pr, "w:keepLines");
    }

    // Page break before (w:pageBreakBefore)
    if (format.page_break_before) {
        ensure_child(p_pr, "w:pageBreakBefore");
    }

    // ========== Handle Run Content ==========
    // Find and remove all runs between bookmark start and end
    pugi::xml_node current = start_node_.next_sibling();
    while (current && current != end_node_) {
        const pugi::xml_node next = current.next_sibling();
        if (is_run_node(current.name())) {
            para.remove_child(current);
        }
        current = next;
    }

    // Create new run with character format
    pugi::xml_node new_run = para.insert_child_before("w:r", end_node_);

    // Apply character formatting if specified
    if (format.is_valid() || format.bold || format.italic || format.underline ||
        format.strikethrough) {
        pugi::xml_node r_pr = new_run.append_child("w:rPr");

        // Font settings
        if (!format.font_ascii.empty() || !format.font_far_east.empty() ||
            !format.font_hansi.empty() || !format.font_hint.empty()) {
            pugi::xml_node r_fonts = r_pr.append_child("w:rFonts");
            if (!format.font_ascii.empty()) {
                r_fonts.append_attribute("w:ascii").set_value(format.font_ascii.c_str());
            }
            if (!format.font_far_east.empty()) {
                r_fonts.append_attribute("w:eastAsia").set_value(format.font_far_east.c_str());
            }
            if (!format.font_hansi.empty()) {
                r_fonts.append_attribute("w:hAnsi").set_value(format.font_hansi.c_str());
            }
            if (!format.font_hint.empty()) {
                r_fonts.append_attribute("w:hint").set_value(format.font_hint.c_str());
            }
        }

        // Font size
        if (format.font_size > 0) {
            pugi::xml_node sz = r_pr.append_child("w:sz");
            sz.append_attribute("w:val").set_value(format.font_size);
            pugi::xml_node sz_cs = r_pr.append_child("w:szCs");
            sz_cs.append_attribute("w:val").set_value(format.font_size);
        }

        // Color
        if (!format.color.empty()) {
            pugi::xml_node color = r_pr.append_child("w:color");
            color.append_attribute("w:val").set_value(format.color.c_str());
        }

        // Bold
        if (format.bold) {
            r_pr.append_child("w:b");
        }

        // Italic
        if (format.italic) {
            r_pr.append_child("w:i");
        }

        // Underline
        if (format.underline) {
            pugi::xml_node u = r_pr.append_child("w:u");
            u.append_attribute("w:val").set_value("single");
        }

        // Strikethrough
        if (format.strikethrough) {
            r_pr.append_child("w:strike");
        }
    }

    // Add text content
    const pugi::xml_node t = new_run.append_child("w:t");
    t.text().set(text.c_str());

    return true;
}

bool Bookmark::is_cross_paragraph() const {
    if (!is_valid()) {
        return false;
    }

    return start_node_.parent() != end_node_.parent();
}

std::vector<pugi::xml_node> Bookmark::get_covered_paragraphs() const {
    std::vector<pugi::xml_node> paragraphs;

    if (!is_valid()) {
        return paragraphs;
    }

    const pugi::xml_node start_para = start_node_.parent();
    const pugi::xml_node end_para = end_node_.parent();

    // Same paragraph
    if (start_para == end_para) {
        paragraphs.push_back(start_para);
        return paragraphs;
    }

    // Cross-paragraph: collect all paragraphs
    paragraphs.push_back(start_para);

    pugi::xml_node current = start_para.next_sibling("w:p");
    while (current && current != end_para) {
        paragraphs.push_back(current);
        current = current.next_sibling("w:p");
    }

    if (end_para) {
        paragraphs.push_back(end_para);
    }

    return paragraphs;
}

bool Bookmark::set_text_cross_paragraph(const std::string& text) {
    if (!is_valid()) {
        return false;
    }

    auto paragraphs = get_covered_paragraphs();
    if (paragraphs.empty()) {
        return false;
    }

    // Single paragraph - use normal method
    if (paragraphs.size() == 1) {
        return set_text_keep_format(text);
    }

    // Multi-paragraph handling:
    // 1. Extract format from first paragraph
    BookmarkFormat fmt;
    const pugi::xml_node first_run = paragraphs[0].child("w:r");
    if (first_run) {
        const pugi::xml_node r_pr = first_run.child("w:rPr");
        if (r_pr) {
            const pugi::xml_node r_fonts = r_pr.child("w:rFonts");
            if (r_fonts) {
                fmt.font_ascii = r_fonts.attribute("w:ascii").value();
                fmt.font_far_east = r_fonts.attribute("w:eastAsia").value();
            }
            const pugi::xml_node sz = r_pr.child("w:sz");
            if (sz) {
                fmt.font_size = sz.attribute("w:val").as_int();
            }
        }
    }

    // 2. Remove intermediate paragraphs
    for (size_t i = 1; i < paragraphs.size() - 1; ++i) {
        paragraphs[i].parent().remove_child(paragraphs[i]);
    }

    // 3. Move bookmark_end to first paragraph
    pugi::xml_node last_para = paragraphs.back();
    const std::string bookmark_id = start_node_.attribute("w:id").value();

    for (pugi::xml_node node = last_para.first_child(); node; node = node.next_sibling()) {
        if (is_bookmark_end_node(node.name())) {
            if (node.attribute("w:id").value() == bookmark_id) {
                // Move to first paragraph
                paragraphs[0].append_copy(node);
                last_para.remove_child(node);
                break;
            }
        }
    }

    // 4. Remove last paragraph
    if (paragraphs.size() > 1) {
        last_para.parent().remove_child(last_para);
    }

    // 5. Update end_node_ reference
    end_node_ = paragraphs[0].last_child();

    // 6. Set text with preserved format
    return set_text_formatted(text, fmt);
}

// ============================================================================
// BookmarkCollection Implementation
// ============================================================================

BookmarkCollection::BookmarkCollection(Document* doc) : doc_(doc) {
}

void BookmarkCollection::collect_bookmarks() const {
    if (collected_) {
        return;
    }

    bookmarks_.clear();

    // Scan document.xml for bookmarks
    pugi::xml_document* doc_xml = doc_->get_document_xml();
    if (!doc_xml) {
        collected_ = true;
        return;
    }

    // Find all bookmark_start and bookmark_end elements recursively
    // Use ID-based matching for accurate pairing
    std::map<std::string, pugi::xml_node> starts;   // id -> node
    std::map<std::string, std::string> id_to_name;  // id -> name
    std::map<std::string, pugi::xml_node> ends;     // id -> node

    auto collect_from_node = [&](auto& self, pugi::xml_node node) -> void {
        for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
            const std::string name = child.name();
            if (name == "w:bookmarkStart") {
                const std::string id = child.attribute("w:id").value();
                const std::string bm_name = child.attribute("w:name").value();
                if (!id.empty()) {
                    starts[id] = child;
                    id_to_name[id] = bm_name;
                }
            } else if (name == "w:bookmarkEnd") {
                const std::string id = child.attribute("w:id").value();
                if (!id.empty()) {
                    ends[id] = child;
                }
            }
            self(self, child);
        }
    };

    const pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    collect_from_node(collect_from_node, body);

    // Create Bookmark objects by matching IDs
    for (const auto& pair : starts) {
        const std::string& id = pair.first;
        const pugi::xml_node& start_node = pair.second;

        // Find corresponding end by ID
        auto end_it = ends.find(id);
        if (end_it != ends.end()) {
            // Valid bookmark with matching start and end
            bookmarks_.emplace_back(doc_, id_to_name[id], start_node, end_it->second);
        }
        // Else: orphaned bookmark start (no matching end), skip it
    }

    // Note: orphaned bookmark ends (no matching start) are ignored

    collected_ = true;
}

size_t BookmarkCollection::count() const {
    collect_bookmarks();
    return bookmarks_.size();
}

Bookmark BookmarkCollection::get(size_t index) const {
    collect_bookmarks();
    if (index < bookmarks_.size()) {
        return bookmarks_[index];
    }
    return {};
}

std::optional<Bookmark> BookmarkCollection::get(const std::string& name) const {
    collect_bookmarks();

    for (const auto& bm : bookmarks_) {
        if (iequals(bm.get_name(), name)) {
            return bm;
        }
    }

    return std::nullopt;
}

bool BookmarkCollection::contains(const std::string& name) const {
    return get(name).has_value();
}

bool BookmarkCollection::remove(const std::string& name) {
    collect_bookmarks();

    for (auto it = bookmarks_.begin(); it != bookmarks_.end(); ++it) {
        if (iequals(it->get_name(), name)) {
            it->remove();
            bookmarks_.erase(it);
            return true;
        }
    }

    return false;
}

bool BookmarkCollection::remove_at(size_t index) {
    collect_bookmarks();

    if (index < bookmarks_.size()) {
        bookmarks_[index].remove();
        bookmarks_.erase(bookmarks_.begin() + static_cast<std::ptrdiff_t>(index));
        return true;
    }

    return false;
}

void BookmarkCollection::clear() {
    collect_bookmarks();
    for (auto& bm : bookmarks_) {
        bm.remove();
    }
    bookmarks_.clear();
}

Bookmark BookmarkCollection::add(const std::string& name, Paragraph& para) {
    if (!doc_ || name.empty()) {
        return {};
    }

    // If bookmark already exists, return it
    auto existing = get(name);
    if (existing) {
        return *existing;
    }

    const int id = doc_->generate_unique_bookmark_id();

    auto start = std::make_shared<BookmarkStart>(name, id);
    auto end = std::make_shared<BookmarkEnd>(id);

    para.append_child(start);
    para.append_child(end);

    // Sync to physical so collect_bookmarks() can find the new nodes
    doc_->sync_to_physical_tree();

    // Invalidate cache so next access picks up the new bookmark
    collected_ = false;

    auto result = get(name);
    if (result) {
        return *result;
    }
    return {};
}

std::vector<Bookmark>::iterator BookmarkCollection::begin() {
    collect_bookmarks();
    return bookmarks_.begin();
}

std::vector<Bookmark>::iterator BookmarkCollection::end() {
    collect_bookmarks();
    return bookmarks_.end();
}

std::vector<Bookmark>::const_iterator BookmarkCollection::begin() const {
    collect_bookmarks();
    return bookmarks_.begin();
}

std::vector<Bookmark>::const_iterator BookmarkCollection::end() const {
    collect_bookmarks();
    return bookmarks_.end();
}

std::vector<std::string> BookmarkCollection::get_names() const {
    collect_bookmarks();
    std::vector<std::string> names;
    names.reserve(bookmarks_.size());
    for (const auto& bm : bookmarks_) {
        names.push_back(bm.get_name());
    }
    return names;
}

// ============================================================================

}  // namespace cdocx
