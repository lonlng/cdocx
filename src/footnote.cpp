/**
 * @file footnote.cpp
 * @brief Footnote/Endnote implementation
 * @since 0.7.0
 */

#include <cdocx/document.h>
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
    if (!visitor) {
        return;
    }
    if (visitor->visit_footnote_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
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

// ============================================================================
// FootnoteCollection
// ============================================================================

FootnoteCollection::FootnoteCollection(Document* doc) : doc_(doc) {
}

void FootnoteCollection::collect_footnotes() const {
    if (collected_) {
        return;
    }
    footnotes_.clear();
    if (doc_) {
        footnotes_ = doc_->footnotes_cache_;
    }
    collected_ = true;
}

size_t FootnoteCollection::count() const {
    collect_footnotes();
    return footnotes_.size();
}

std::shared_ptr<Footnote> FootnoteCollection::get(size_t index) const {
    collect_footnotes();
    if (index < footnotes_.size()) {
        return footnotes_[index];
    }
    return nullptr;
}

std::shared_ptr<Footnote> FootnoteCollection::get_by_id(int id) const {
    collect_footnotes();
    for (const auto& fn : footnotes_) {
        if (fn->get_id() == id) {
            return fn;
        }
    }
    return nullptr;
}

bool FootnoteCollection::contains(int id) const {
    return get_by_id(id) != nullptr;
}

std::shared_ptr<Footnote> FootnoteCollection::add(const std::string& text) {
    return add(text, "");
}

std::shared_ptr<Footnote> FootnoteCollection::add(const std::string& text,
                                                  const std::string& reference_mark) {
    if (!doc_) {
        return nullptr;
    }
    auto footnote = doc_->add_footnote(text, reference_mark);
    if (footnote) {
        collected_ = false;
        collect_footnotes();
    }
    return footnote;
}

bool FootnoteCollection::remove_at(size_t index) {
    collect_footnotes();
    if (index >= footnotes_.size()) {
        return false;
    }
    const int id = footnotes_[index]->get_id();
    const bool result = doc_->remove_footnote(id);
    if (result) {
        collected_ = false;
    }
    return result;
}

bool FootnoteCollection::remove(int id) {
    const bool result = doc_->remove_footnote(id);
    if (result) {
        collected_ = false;
    }
    return result;
}

void FootnoteCollection::clear() {
    if (doc_) {
        doc_->clear_footnotes();
    }
    footnotes_.clear();
    collected_ = true;
}

std::vector<std::shared_ptr<Footnote>>::iterator FootnoteCollection::begin() {
    collect_footnotes();
    return footnotes_.begin();
}

std::vector<std::shared_ptr<Footnote>>::iterator FootnoteCollection::end() {
    collect_footnotes();
    return footnotes_.end();
}

std::vector<std::shared_ptr<Footnote>>::const_iterator FootnoteCollection::begin() const {
    collect_footnotes();
    return footnotes_.begin();
}

std::vector<std::shared_ptr<Footnote>>::const_iterator FootnoteCollection::end() const {
    collect_footnotes();
    return footnotes_.end();
}

// ============================================================================
// EndnoteCollection
// ============================================================================

EndnoteCollection::EndnoteCollection(Document* doc) : doc_(doc) {
}

void EndnoteCollection::collect_endnotes() const {
    if (collected_) {
        return;
    }
    endnotes_.clear();
    if (doc_) {
        endnotes_ = doc_->endnotes_cache_;
    }
    collected_ = true;
}

size_t EndnoteCollection::count() const {
    collect_endnotes();
    return endnotes_.size();
}

std::shared_ptr<Footnote> EndnoteCollection::get(size_t index) const {
    collect_endnotes();
    if (index < endnotes_.size()) {
        return endnotes_[index];
    }
    return nullptr;
}

std::shared_ptr<Footnote> EndnoteCollection::get_by_id(int id) const {
    collect_endnotes();
    for (const auto& en : endnotes_) {
        if (en->get_id() == id) {
            return en;
        }
    }
    return nullptr;
}

bool EndnoteCollection::contains(int id) const {
    return get_by_id(id) != nullptr;
}

std::shared_ptr<Footnote> EndnoteCollection::add(const std::string& text) {
    return add(text, "");
}

std::shared_ptr<Footnote> EndnoteCollection::add(const std::string& text,
                                                 const std::string& reference_mark) {
    if (!doc_) {
        return nullptr;
    }
    auto endnote = doc_->add_endnote(text, reference_mark);
    if (endnote) {
        collected_ = false;
        collect_endnotes();
    }
    return endnote;
}

bool EndnoteCollection::remove_at(size_t index) {
    collect_endnotes();
    if (index >= endnotes_.size()) {
        return false;
    }
    const int id = endnotes_[index]->get_id();
    const bool result = doc_->remove_endnote(id);
    if (result) {
        collected_ = false;
    }
    return result;
}

bool EndnoteCollection::remove(int id) {
    const bool result = doc_->remove_endnote(id);
    if (result) {
        collected_ = false;
    }
    return result;
}

void EndnoteCollection::clear() {
    if (doc_) {
        doc_->clear_endnotes();
    }
    endnotes_.clear();
    collected_ = true;
}

std::vector<std::shared_ptr<Footnote>>::iterator EndnoteCollection::begin() {
    collect_endnotes();
    return endnotes_.begin();
}

std::vector<std::shared_ptr<Footnote>>::iterator EndnoteCollection::end() {
    collect_endnotes();
    return endnotes_.end();
}

std::vector<std::shared_ptr<Footnote>>::const_iterator EndnoteCollection::begin() const {
    collect_endnotes();
    return endnotes_.begin();
}

std::vector<std::shared_ptr<Footnote>>::const_iterator EndnoteCollection::end() const {
    collect_endnotes();
    return endnotes_.end();
}

}  // namespace cdocx
