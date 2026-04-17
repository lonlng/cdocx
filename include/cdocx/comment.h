/**
 * @file comment.h
 * @brief Comment support for CDocx
 * @details Provides document comment functionality including comment containers,
 *          comment ranges, and comment references.
 *
 * @since 0.7.0
 */

#pragma once

#include <cdocx/enums.h>
#include <cdocx/node.h>

#include <chrono>
#include <string>

namespace cdocx {

// ============================================================================
// CommentRangeStart - Marks the beginning of a commented region
// ============================================================================

class CommentRangeStart : public Node {
  public:
    CommentRangeStart();
    explicit CommentRangeStart(int id);
    explicit CommentRangeStart(Document* doc);
    CommentRangeStart(Document* doc, int id) : id_(id) { set_document(doc); }

    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    NodeType node_type() const override { return NodeType::CommentRangeStart; }
    std::string get_text() const override { return ""; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;

  private:
    int id_ = 0;
};

// ============================================================================
// CommentRangeEnd - Marks the end of a commented region
// ============================================================================

class CommentRangeEnd : public Node {
  public:
    CommentRangeEnd();
    explicit CommentRangeEnd(int id);
    explicit CommentRangeEnd(Document* doc);
    CommentRangeEnd(Document* doc, int id) : id_(id) { set_document(doc); }

    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    NodeType node_type() const override { return NodeType::CommentRangeEnd; }
    std::string get_text() const override { return ""; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;

  private:
    int id_ = 0;
};

// ============================================================================
// Comment - Container for comment text
// ============================================================================

class Comment : public CompositeNode {
  public:
    Comment();
    explicit Comment(Document* doc);
    Comment(Document* doc, const std::string& author, const std::string& text);

    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    std::string get_author() const { return author_; }
    void set_author(const std::string& author) { author_ = author; }

    std::string get_initial() const { return initial_; }
    void set_initial(const std::string& initial) { initial_ = initial; }

    std::string get_text() const override;
    void set_text(const std::string& text);

    std::chrono::system_clock::time_point get_date_time() const { return date_time_; }
    void set_date_time(std::chrono::system_clock::time_point dt) { date_time_ = dt; }

    bool is_done() const { return done_; }
    void set_done(bool done) { done_ = done; }

    int get_parent_comment_id() const { return parent_comment_id_; }
    void set_parent_comment_id(int id) { parent_comment_id_ = id; }

    NodeType node_type() const override { return NodeType::Comment; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;

    // Convenience: append paragraph with text
    std::shared_ptr<Paragraph> append_paragraph(const std::string& text = "");

  private:
    int id_ = 0;
    std::string author_;
    std::string initial_;
    std::chrono::system_clock::time_point date_time_;
    bool done_ = false;
    int parent_comment_id_ = -1;
};

// ============================================================================
// CommentCollection - Typed access to document comments
// ============================================================================

class CommentCollection {
  private:
    friend class Document;

    Document* doc_;
    mutable std::vector<std::shared_ptr<Comment>> comments_;
    mutable bool collected_ = false;

    void collect_comments() const;

  public:
    CommentCollection() : doc_(nullptr), collected_(true) {}
    explicit CommentCollection(Document* doc);

    size_t count() const;
    std::shared_ptr<Comment> get(size_t index) const;
    std::shared_ptr<Comment> get_by_id(int id) const;

    bool contains(int id) const;

    std::shared_ptr<Comment> add(const std::string& author, const std::string& text);
    bool remove_at(size_t index);
    bool remove(int id);
    void clear();

    std::vector<std::shared_ptr<Comment>>::iterator begin();
    std::vector<std::shared_ptr<Comment>>::iterator end();
    std::vector<std::shared_ptr<Comment>>::const_iterator begin() const;
    std::vector<std::shared_ptr<Comment>>::const_iterator end() const;
};

}  // namespace cdocx
