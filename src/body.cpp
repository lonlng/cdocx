/**
 * @file body.cpp
 * @brief Body and Inline class implementations
 */

#include <cdocx/body.h>
#include <cdocx/paragraph.h>
#include <cdocx/table.h>
#include <cdocx/document.h>
#include <cdocx/section.h>

namespace cdocx {

// ============================================================================
// Body Implementation
// ============================================================================

Body::Body() = default;

Body::Body(Document* doc) {
    set_document(doc);
}

void Body::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    
    if (visitor->visit_body_start(*this) == VisitorAction::Continue) {
        for (const auto& child : children_) {
            child->accept(visitor);
        }
        visitor->visit_body_end(*this);
    }
}

std::shared_ptr<Node> Body::clone(bool deep) const {
    auto cloned = std::make_shared<Body>(get_document());
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->append_child(child->clone(true));
        }
    }
    
    return cloned;
}

std::shared_ptr<Section> Body::get_parent_section() const {
    return get_ancestor<Section>();
}

std::shared_ptr<Paragraph> Body::append_paragraph(const std::string& text) {
    auto para = std::make_shared<Paragraph>(get_document());
    if (!text.empty()) {
        para->append_run(text);
    }
    append_child(para);
    return para;
}

std::shared_ptr<Paragraph> Body::insert_paragraph(int index, const std::string& text) {
    auto para = std::make_shared<Paragraph>(get_document());
    if (!text.empty()) {
        para->append_run(text);
    }
    insert_child(index, para);
    return para;
}

std::shared_ptr<Paragraph> Body::get_first_paragraph() const {
    return get_first_child<Paragraph>();
}

std::shared_ptr<Paragraph> Body::get_last_paragraph() const {
    return get_last_child<Paragraph>();
}

std::vector<std::shared_ptr<Paragraph>> Body::get_paragraphs() const {
    return get_children_of_type<Paragraph>();
}

std::shared_ptr<Table> Body::append_table(int rows, int cols) {
    auto table = std::make_shared<Table>(get_document(), rows, cols);
    append_child(table);
    return table;
}

std::shared_ptr<Table> Body::insert_table(int index, int rows, int cols) {
    auto table = std::make_shared<Table>(get_document(), rows, cols);
    insert_child(index, table);
    return table;
}

std::shared_ptr<Table> Body::get_first_table() const {
    return get_first_child<Table>();
}

std::shared_ptr<Table> Body::get_last_table() const {
    return get_last_child<Table>();
}

std::vector<std::shared_ptr<Table>> Body::get_tables() const {
    return get_children_of_type<Table>();
}

void Body::ensure_minimum() {
    // Ensure at least one paragraph
    bool has_content = false;
    for (const auto& child : children_) {
        if (child->node_type() == NodeType::Paragraph || 
            child->node_type() == NodeType::Table) {
            has_content = true;
            break;
        }
    }
    
    if (!has_content) {
        append_paragraph();
    }
}

std::string Body::get_text() const {
    std::string result;
    for (const auto& child : children_) {
        result += child->get_text();
    }
    return result;
}

// ============================================================================
// Inline Implementation
// ============================================================================

Inline::Inline() = default;

Inline::Inline(Document* doc) {
    set_document(doc);
}

std::shared_ptr<Paragraph> Inline::get_parent_paragraph() const {
    return get_ancestor<Paragraph>();
}

Inline& Inline::set_bold(bool value) {
    font_.bold = value;
    return *this;
}

Inline& Inline::set_italic(bool value) {
    font_.italic = value;
    return *this;
}

Inline& Inline::set_underline(UnderlineType value) {
    font_.underline = value;
    return *this;
}

Inline& Inline::set_strikethrough(bool value) {
    font_.strikethrough = value;
    return *this;
}

Inline& Inline::set_font_size(double size) {
    font_.size = size;
    return *this;
}

Inline& Inline::set_font_name(const std::string& name) {
    font_.name = name;
    return *this;
}

Inline& Inline::set_color(const Color& color) {
    font_.color = color;
    return *this;
}

Inline& Inline::set_highlight(HighlightColor color) {
    font_.highlight = color;
    return *this;
}

Inline& Inline::set_superscript() {
    font_.script_type = ScriptType::Superscript;
    return *this;
}

Inline& Inline::set_subscript() {
    font_.script_type = ScriptType::Subscript;
    return *this;
}

} // namespace cdocx
