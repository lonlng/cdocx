/**
 * @file base_content.cpp
 * @brief Implementation of base content classes (Run, Paragraph, Table, etc.)
 * @details This file contains the implementation of the fundamental content
 *          classes that make up the document structure.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/base.h>
#include <cdocx/document.h>
#include <cdocx/format_context.h>
#include <cctype>
#include <cstring>

namespace cdocx {

// ============================================================================
// Run DOM Implementation
// ============================================================================

Run::Run(Document* doc) {
    set_document(doc);
}

Run::Run(Document* doc, const std::string& text) : text_(text) {
    set_document(doc);
}

void Run::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_run(*this);
    }
}

std::shared_ptr<Node> Run::clone(bool deep) const {
    // TODO: Implement proper cloning
    return nullptr;
}

// ============================================================================
// Run Legacy Implementation
// ============================================================================

Run::Run() = default;

Run::Run(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {}

void Run::set_parent(pugi::xml_node node) {
    parent_ = node;
    // Find first run child in the paragraph
    current_ = parent_.child("w:r");
}

void Run::set_current(pugi::xml_node node) {
    current_ = node;
}

pugi::xml_node Run::get_current() const {
    return current_;
}

pugi::xml_node Run::get_parent() const {
    return parent_;
}

std::string Run::get_text() const {
    if (!current_) {
        return "";
    }
    return current_.child("w:t").text().get();
}

bool Run::set_text(const std::string& text) const {
    if (!current_) {
        return false;
    }
    return current_.child("w:t").text().set(text.c_str());
}

bool Run::set_text(const char* text) const {
    if (!current_) {
        return false;
    }
    return current_.child("w:t").text().set(text);
}

Run& Run::next() {
    // Move to next w:r sibling (skip non-run elements)
    current_ = current_.next_sibling("w:r");
    return *this;
}

bool Run::has_next() const {
    return current_ != nullptr;
}

// ============================================================================
// Run Formatting Methods
// ============================================================================

bool Run::set_color(const std::string& color_hex) {
    return TextFormatContext::apply_color(current_, color_hex);
}

bool Run::set_font_size(int size) {
    return TextFormatContext::apply_font_size(current_, size);
}

bool Run::set_font_name(const std::string& font_name) {
    return TextFormatContext::apply_font_name(current_, font_name);
}

bool Run::set_bold(bool bold) {
    return TextFormatContext::apply_bold(current_, bold);
}

bool Run::set_italic(bool italic) {
    return TextFormatContext::apply_italic(current_, italic);
}

bool Run::set_underline(bool underline) {
    return TextFormatContext::apply_underline(current_, underline);
}

} // namespace cdocx
