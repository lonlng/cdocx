/**
 * @file comment.cpp
 * @brief Comment implementation
 * @since 0.7.0
 */

#include <cdocx/comment.h>
#include <cdocx/paragraph.h>
#include <cdocx/document.h>

namespace cdocx {

// ============================================================================
// CommentRangeStart
// ============================================================================

CommentRangeStart::CommentRangeStart() = default;

CommentRangeStart::CommentRangeStart(int id) : id_(id) {}

CommentRangeStart::CommentRangeStart(Document* doc) {
    set_document(doc);
}

void CommentRangeStart::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_comment_range_start(*this);
    }
}

std::shared_ptr<Node> CommentRangeStart::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<CommentRangeStart>(id_);
    cloned->set_document(document_);
    return cloned;
}

// ============================================================================
// CommentRangeEnd
// ============================================================================

CommentRangeEnd::CommentRangeEnd() = default;

CommentRangeEnd::CommentRangeEnd(int id) : id_(id) {}

CommentRangeEnd::CommentRangeEnd(Document* doc) {
    set_document(doc);
}

void CommentRangeEnd::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_comment_range_end(*this);
    }
}

std::shared_ptr<Node> CommentRangeEnd::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<CommentRangeEnd>(id_);
    cloned->set_document(document_);
    return cloned;
}

// ============================================================================
// Comment
// ============================================================================

Comment::Comment() = default;

Comment::Comment(Document* doc) {
    set_document(doc);
    date_time_ = std::chrono::system_clock::now();
}

Comment::Comment(Document* doc, const std::string& author, const std::string& text)
    : author_(author) {
    set_document(doc);
    date_time_ = std::chrono::system_clock::now();
    if (!text.empty()) {
        set_text(text);
    }
}

std::string Comment::get_text() const {
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

void Comment::set_text(const std::string& text) {
    // Clear existing paragraphs
    remove_all_children();

    // Split by newlines and create paragraphs
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

void Comment::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_comment(*this) == VisitorAction::Continue) {
        for (auto& child : get_children()) {
            child->accept(visitor);
        }
    }
}

std::shared_ptr<Node> Comment::clone(bool deep) const {
    auto cloned = std::make_shared<Comment>();
    cloned->set_document(document_);
    cloned->set_id(id_);
    cloned->set_author(author_);
    cloned->set_initial(initial_);
    cloned->set_date_time(date_time_);
    cloned->set_done(done_);
    cloned->set_parent_comment_id(parent_comment_id_);
    if (deep) {
        for (const auto& child : get_children()) {
            cloned->append_child(child->clone(true));
        }
    }
    return cloned;
}

std::shared_ptr<Paragraph> Comment::append_paragraph(const std::string& text) {
    auto para = std::make_shared<Paragraph>();
    if (!text.empty()) {
        para->append_run(text);
    }
    append_child(para);
    return para;
}

// ============================================================================
// CommentCollection
// ============================================================================

CommentCollection::CommentCollection(Document* doc) : doc_(doc) {}

void CommentCollection::collect_comments() const {
    if (collected_) {
        return;
    }
    comments_.clear();
    if (doc_) {
        comments_ = doc_->comments_cache_;
    }
    collected_ = true;
}

size_t CommentCollection::count() const {
    collect_comments();
    return comments_.size();
}

std::shared_ptr<Comment> CommentCollection::get(size_t index) const {
    collect_comments();
    if (index < comments_.size()) {
        return comments_[index];
    }
    return nullptr;
}

std::shared_ptr<Comment> CommentCollection::get_by_id(int id) const {
    collect_comments();
    for (const auto& c : comments_) {
        if (c->get_id() == id) {
            return c;
        }
    }
    return nullptr;
}

bool CommentCollection::contains(int id) const {
    return get_by_id(id) != nullptr;
}

std::shared_ptr<Comment> CommentCollection::add(const std::string& author, const std::string& text) {
    if (!doc_) {
        return nullptr;
    }
    auto comment = doc_->add_comment(author, text);
    if (comment) {
        collected_ = false;
        collect_comments();
    }
    return comment;
}

bool CommentCollection::remove_at(size_t index) {
    collect_comments();
    if (index >= comments_.size()) {
        return false;
    }
    int id = comments_[index]->get_id();
    bool result = doc_->remove_comment(id);
    if (result) {
        collected_ = false;
    }
    return result;
}

bool CommentCollection::remove(int id) {
    bool result = doc_->remove_comment(id);
    if (result) {
        collected_ = false;
    }
    return result;
}

void CommentCollection::clear() {
    if (doc_) {
        doc_->clear_comments();
    }
    comments_.clear();
    collected_ = true;
}

std::vector<std::shared_ptr<Comment>>::iterator CommentCollection::begin() {
    collect_comments();
    return comments_.begin();
}

std::vector<std::shared_ptr<Comment>>::iterator CommentCollection::end() {
    collect_comments();
    return comments_.end();
}

std::vector<std::shared_ptr<Comment>>::const_iterator CommentCollection::begin() const {
    collect_comments();
    return comments_.begin();
}

std::vector<std::shared_ptr<Comment>>::const_iterator CommentCollection::end() const {
    collect_comments();
    return comments_.end();
}

} // namespace cdocx
