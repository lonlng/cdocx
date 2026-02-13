/**
 * @file base_content.cpp
 * @brief Implementation of base content classes (Run, SpecialChar, Field, etc.)
 * @version 0.7.0 - DOM Style
 */

#include <cdocx/base.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>

namespace cdocx {

// ============================================================================
// Run DOM Implementation
// ============================================================================

Run::Run() = default;

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
    auto cloned = std::make_shared<Run>(get_document(), text_);
    cloned->font_ = font_;
    return cloned;
}

// ============================================================================
// Run Legacy Implementation (XML-based)
// ============================================================================

Run::Run(pugi::xml_node parent, pugi::xml_node current)
    : parent_xml_(parent), current_xml_(current) {}

void Run::set_parent_xml(pugi::xml_node node) {
    parent_xml_ = node;
    current_xml_ = parent_xml_.child("w:r");
}

void Run::set_current_xml(pugi::xml_node node) {
    current_xml_ = node;
}

Run& Run::next() {
    current_xml_ = current_xml_.next_sibling("w:r");
    return *this;
}

bool Run::has_next() const {
    return current_xml_ != nullptr;
}

std::string Run::get_text_xml() const {
    if (!current_xml_) return "";
    return current_xml_.child("w:t").text().get();
}

bool Run::set_text_xml(const std::string& text) const {
    if (!current_xml_) return false;
    return current_xml_.child("w:t").text().set(text.c_str());
}

bool Run::set_color_xml(const std::string& color_hex) {
    // TODO: Implement
    return false;
}

bool Run::set_font_size_xml(int size) {
    // TODO: Implement
    return false;
}

bool Run::set_font_name_xml(const std::string& font_name) {
    // TODO: Implement
    return false;
}

bool Run::set_bold_xml(bool bold) {
    // TODO: Implement
    return false;
}

bool Run::set_italic_xml(bool italic) {
    // TODO: Implement
    return false;
}

bool Run::set_underline_xml(bool underline) {
    // TODO: Implement
    return false;
}

void Run::set_properties_xml(const TextProperties& props) {
    // TODO: Implement
}

TextProperties Run::get_properties_xml() const {
    // TODO: Implement
    return TextProperties();
}

bool Run::set_highlight_xml(TextProperties::Highlight color) {
    // TODO: Implement
    return false;
}

bool Run::set_underline_style_xml(TextProperties::UnderlineStyle style, 
                                   const std::string& color) {
    // TODO: Implement
    return false;
}

bool Run::set_strike_xml(TextProperties::StrikeStyle style) {
    // TODO: Implement
    return false;
}

bool Run::set_scale_xml(int percent) {
    // TODO: Implement
    return false;
}

bool Run::set_spacing_xml(TextProperties::SpacingType type, int value) {
    // TODO: Implement
    return false;
}

bool Run::set_position_xml(TextProperties::PositionType type, int value) {
    // TODO: Implement
    return false;
}

// ============================================================================
// RunCollection Implementation
// ============================================================================

void RunCollection::add(std::shared_ptr<Run> run) {
    if (run) {
        runs_.push_back(run);
    }
}

void RunCollection::remove(std::shared_ptr<Run> run) {
    if (!run) return;
    for (auto it = runs_.begin(); it != runs_.end(); ++it) {
        if (*it == run) {
            runs_.erase(it);
            return;
        }
    }
}

void RunCollection::remove_at(int index) {
    if (index >= 0 && static_cast<size_t>(index) < runs_.size()) {
        runs_.erase(runs_.begin() + index);
    }
}

void RunCollection::clear() {
    runs_.clear();
}

// get_item, first, last are inline in base.h

std::string RunCollection::get_text() const {
    std::string result;
    for (const auto& run : runs_) {
        if (run) {
            result += run->get_text();
        }
    }
    return result;
}

// ============================================================================
// SpecialChar Implementation
// ============================================================================

SpecialChar::SpecialChar() = default;

SpecialChar::SpecialChar(char16_t char_code) : char_code_(char_code) {}

std::string SpecialChar::get_text() const {
    // Convert char16_t to UTF-8 string
    std::string result;
    if (char_code_ <= 0x7F) {
        result += static_cast<char>(char_code_);
    } else if (char_code_ <= 0x7FF) {
        result += static_cast<char>(0xC0 | ((char_code_ >> 6) & 0x1F));
        result += static_cast<char>(0x80 | (char_code_ & 0x3F));
    } else {
        result += static_cast<char>(0xE0 | ((char_code_ >> 12) & 0x0F));
        result += static_cast<char>(0x80 | ((char_code_ >> 6) & 0x3F));
        result += static_cast<char>(0x80 | (char_code_ & 0x3F));
    }
    return result;
}

void SpecialChar::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_special_char(*this);
    }
}

std::shared_ptr<Node> SpecialChar::clone(bool deep) const {
    return std::make_shared<SpecialChar>(char_code_);
}

std::shared_ptr<SpecialChar> SpecialChar::paragraph_break() {
    return std::make_shared<SpecialChar>(0x000D);  // CR
}

std::shared_ptr<SpecialChar> SpecialChar::line_break() {
    return std::make_shared<SpecialChar>(0x000A);  // LF
}

std::shared_ptr<SpecialChar> SpecialChar::page_break() {
    return std::make_shared<SpecialChar>(0x000C);  // Form feed
}

std::shared_ptr<SpecialChar> SpecialChar::column_break() {
    return std::make_shared<SpecialChar>(0x000E);  // SO
}

std::shared_ptr<SpecialChar> SpecialChar::tab() {
    return std::make_shared<SpecialChar>(0x0009);  // Tab
}

// ============================================================================
// Field Implementation
// ============================================================================

Field::Field() = default;

Field::Field(FieldType type) : type_(type) {}

Field::Field(Document* doc, FieldType type) : type_(type) {
    set_document(doc);
}

void Field::update() {
    // Subclasses implement
}

void Field::unlink() {
    // Replace field with its result
    result_ = get_text();
}

void Field::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_field_start(*this) == VisitorAction::Continue) {
        visitor->visit_field_end(*this);
    }
}

std::shared_ptr<Node> Field::clone(bool deep) const {
    auto cloned = std::make_shared<Field>(get_document(), type_);
    cloned->field_code_ = field_code_;
    cloned->result_ = result_;
    cloned->is_locked_ = is_locked_;
    cloned->is_dirty_ = is_dirty_;
    return cloned;
}

// ============================================================================
// BookmarkStart Implementation
// ============================================================================

BookmarkStart::BookmarkStart() = default;

BookmarkStart::BookmarkStart(const std::string& name, int id) 
    : name_(name), id_(id) {}

BookmarkStart::BookmarkStart(Document* doc) {
    set_document(doc);
}

void BookmarkStart::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_bookmark_start(*this);
    }
}

std::shared_ptr<Node> BookmarkStart::clone(bool deep) const {
    return std::make_shared<BookmarkStart>(name_, id_);
}

// ============================================================================
// BookmarkEnd Implementation
// ============================================================================

BookmarkEnd::BookmarkEnd() = default;

BookmarkEnd::BookmarkEnd(int id) : id_(id) {}

BookmarkEnd::BookmarkEnd(Document* doc) {
    set_document(doc);
}

void BookmarkEnd::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_bookmark_end(*this);
    }
}

std::shared_ptr<Node> BookmarkEnd::clone(bool deep) const {
    return std::make_shared<BookmarkEnd>(id_);
}

// ============================================================================
// Hyperlink Implementation
// ============================================================================

Hyperlink::Hyperlink() = default;

Hyperlink::Hyperlink(Document* doc) {
    set_document(doc);
}

void Hyperlink::set_address(const std::string& url) {
    // TODO: Implement
}

void Hyperlink::set_bookmark_name(const std::string& name) {
    // TODO: Implement
}

void Hyperlink::set_tooltip(const std::string& tooltip) {
    // TODO: Implement
}

void Hyperlink::set_screen_tip(const std::string& tip) {
    // TODO: Implement
}

std::string Hyperlink::get_address() const {
    // TODO: Implement
    return "";
}

std::string Hyperlink::get_bookmark_name() const {
    // TODO: Implement
    return "";
}

void Hyperlink::update() {
    // TODO: Implement
}

} // namespace cdocx
