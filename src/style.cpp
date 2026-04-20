#include <cdocx/document.h>
#include <cdocx/style.h>

#include <algorithm>

namespace cdocx {

Style::Style() = default;

Style::Style(Document* doc, StyleType type) : document_(doc), type_(type) {
}

void Style::remove() {
    if (document_) {
        document_->styles().remove(shared_from_this());
    }
}

void Style::preserve_style_xml(pugi::xml_node style_node) {
    if (!style_node)
        return;
    preserved_style_xml_.reset();
    preserved_style_xml_.append_copy(style_node);
}

pugi::xml_node Style::get_preserved_style_xml() const {
    return preserved_style_xml_.first_child();
}

bool Style::has_preserved_style_xml() const {
    return preserved_style_xml_.first_child();
}

// ---------------------------------------------------------------------------
// StyleCollection
// ---------------------------------------------------------------------------

std::shared_ptr<Style> StyleCollection::get_by_name(const std::string& name) const {
    for (const auto& s : styles_) {
        if (s->get_name() == name)
            return s;
    }
    return nullptr;
}

std::shared_ptr<Style> StyleCollection::get_by_style_id(const std::string& style_id) const {
    for (const auto& s : styles_) {
        if (s->get_style_id() == style_id)
            return s;
    }
    return nullptr;
}

std::shared_ptr<Style> StyleCollection::get_by_identifier(StyleIdentifier identifier) const {
    for (const auto& s : styles_) {
        if (s->get_style_identifier() == identifier)
            return s;
    }
    return nullptr;
}

std::shared_ptr<Style> StyleCollection::add(StyleType type, const std::string& name) {
    auto style = std::make_shared<Style>(document_, type);
    style->set_name(name);
    style->set_style_id(name);
    styles_.push_back(style);
    return style;
}

void StyleCollection::add(const std::shared_ptr<Style>& style) {
    if (!style)
        return;
    style->set_document(document_);
    styles_.push_back(style);
}

void StyleCollection::remove(const std::shared_ptr<Style>& style) {
    if (!style)
        return;
    styles_.erase(std::remove(styles_.begin(), styles_.end(), style), styles_.end());
}

void StyleCollection::remove_at(int index) {
    if (index >= 0 && static_cast<size_t>(index) < styles_.size()) {
        styles_.erase(styles_.begin() + index);
    }
}

void StyleCollection::clear() {
    styles_.clear();
}

void StyleCollection::load_from_document() {
    // Placeholder - actual loading is done by Document::sync_styles_from_physical()
}

}  // namespace cdocx
