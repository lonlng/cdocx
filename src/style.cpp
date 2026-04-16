#include <cdocx/style.h>
#include <cdocx/document.h>
#include <algorithm>

namespace cdocx {

Style::Style() = default;

Style::Style(Document* doc, StyleType type)
    : document_(doc), type_(type) {}

void Style::remove() {
    if (document_) {
        document_->styles().remove(shared_from_this());
    }
}

// ---------------------------------------------------------------------------
// StyleCollection
// ---------------------------------------------------------------------------

std::shared_ptr<Style> StyleCollection::get_by_name(const std::string& name) const {
    for (const auto& s : styles_) {
        if (s->get_name() == name) return s;
    }
    return nullptr;
}

std::shared_ptr<Style> StyleCollection::get_by_style_id(const std::string& style_id) const {
    for (const auto& s : styles_) {
        if (s->get_style_id() == style_id) return s;
    }
    return nullptr;
}

std::shared_ptr<Style> StyleCollection::get_by_identifier(StyleIdentifier identifier) const {
    for (const auto& s : styles_) {
        if (s->get_style_identifier() == identifier) return s;
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
    if (!style) return;
    style->set_document(document_);
    styles_.push_back(style);
}

void StyleCollection::remove(const std::shared_ptr<Style>& style) {
    if (!style) return;
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

} // namespace cdocx
