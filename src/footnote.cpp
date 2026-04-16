/**
 * @file footnote.cpp
 * @brief Footnote/Endnote implementation
 * @since 0.7.0
 */

#include <cdocx/footnote.h>
#include <cdocx/paragraph.h>

namespace cdocx {

// ============================================================================
// Footnote
// ============================================================================

Footnote::Footnote() = default;

Footnote::Footnote(Document* doc) {
    set_document(doc);
}

Footnote::Footnote(Document* doc, FootnoteType type) : type_(type) {
    set_document(doc);
}

std::string Footnote::get_text() const {
    std::string result;
    for (const auto& child : get_children()) {
        if (child->node_type() == NodeType::Paragraph) {
            if (!result.empty()) {
                result += "\n";
            }
            result += child->get_text();
        }
    }
    return result;
}

void Footnote::set_text(const std::string& text) {
    remove_all_children();

    size_t start = 0;
    while (start <= text.size()) {
        size_t end = text.find('\n', start);
        if (end == std::string::npos) {
            end = text.size();
        }
        auto para = std::make_shared<Paragraph>();
        if (start < end) {
            para->append_run(text.substr(start, end - start));
        }
        append_child(para);
        start = end + 1;
    }
}

void Footnote::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_footnote_start(*this) == VisitorAction::Continue) {
        for (auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_footnote_end(*this);
    }
}

std::shared_ptr<Node> Footnote::clone(bool deep) const {
    auto cloned = std::make_shared<Footnote>();
    cloned->set_document(document_);
    cloned->set_id(id_);
    cloned->set_footnote_type(type_);
    cloned->set_auto(is_auto_);
    cloned->set_reference_mark(reference_mark_);
    if (deep) {
        for (const auto& child : get_children()) {
            cloned->append_child(child->clone(true));
        }
    }
    return cloned;
}

std::shared_ptr<Paragraph> Footnote::append_paragraph(const std::string& text) {
    auto para = std::make_shared<Paragraph>();
    if (!text.empty()) {
        para->append_run(text);
    }
    append_child(para);
    return para;
}

// ============================================================================
// FootnoteReference
// ============================================================================

FootnoteReference::FootnoteReference() = default;
FootnoteReference::FootnoteReference(Document* doc) {
    set_document(doc);
}

void FootnoteReference::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_footnote_reference(*this);
    }
}

std::shared_ptr<Node> FootnoteReference::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<FootnoteReference>();
    cloned->set_document(document_);
    cloned->set_id(id_);
    return cloned;
}

// ============================================================================
// EndnoteReference
// ============================================================================

EndnoteReference::EndnoteReference() = default;
EndnoteReference::EndnoteReference(Document* doc) {
    set_document(doc);
}

void EndnoteReference::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_endnote_reference(*this);
    }
}

std::shared_ptr<Node> EndnoteReference::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<EndnoteReference>();
    cloned->set_document(document_);
    cloned->set_id(id_);
    return cloned;
}

} // namespace cdocx
