/**
 * @file body.cpp
 * @brief Body and Inline class implementations
 */

#include <cdocx/body.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/table.h>

namespace cdocx {

// ============================================================================
// Body Implementation
// ============================================================================

Body::Body() = default;

Body::Body(Document* doc) {
    set_document(doc);
}

void Body::accept(DocumentVisitor* visitor) {
    if (!visitor)
        return;

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
    Section* sect = get_ancestor<Section>();
    if (sect) {
        return std::static_pointer_cast<Section>(sect->shared_from_this());
    }
    return nullptr;
}

std::shared_ptr<Paragraph> Body::append_paragraph(const std::string& text) {
    // Remove the placeholder empty paragraph created by create_empty()
    // when the body contains only that single unmodified placeholder.
    auto children = get_children();
    if (children.size() == 1 && children[0]->node_type() == NodeType::Paragraph) {
        auto placeholder = std::static_pointer_cast<Paragraph>(children[0]);
        auto para_children = placeholder->get_children();
        if (para_children.size() == 1 && para_children[0]->node_type() == NodeType::Run &&
            placeholder->get_text().empty()) {
            remove_child(placeholder);
        }
    }

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
        if (child->node_type() == NodeType::Paragraph || child->node_type() == NodeType::Table) {
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

Inline::Inline(const Inline& other) : Node(other), font_(other.font_) {
    if (other.preserved_rPr_.first_child()) {
        preserved_rPr_.append_copy(other.preserved_rPr_.first_child());
    }
}

Inline& Inline::operator=(const Inline& other) {
    if (this != &other) {
        Node::operator=(other);
        font_ = other.font_;
        preserved_rPr_.reset();
        if (other.preserved_rPr_.first_child()) {
            preserved_rPr_.append_copy(other.preserved_rPr_.first_child());
        }
    }
    return *this;
}

std::shared_ptr<Paragraph> Inline::get_parent_paragraph() const {
    Paragraph* para = get_ancestor<Paragraph>();
    if (para) {
        return std::static_pointer_cast<Paragraph>(para->shared_from_this());
    }
    return nullptr;
}

void Inline::preserve_rPr(pugi::xml_node rPr) {
    if (!rPr)
        return;
    preserved_rPr_.reset();
    preserved_rPr_.append_copy(rPr);
}

pugi::xml_node Inline::get_preserved_rPr() const {
    return preserved_rPr_.first_child();
}

bool Inline::has_preserved_rPr() const {
    return preserved_rPr_.first_child() != nullptr;
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

}  // namespace cdocx
