/**
 * @file footnote.h
 * @brief Footnote/Endnote support for CDocx
 * @details Provides document footnote and endnote functionality.
 *
 * @since 0.7.0
 */

#pragma once

#include <cdocx/enums.h>
#include <cdocx/node.h>

#include <string>

namespace cdocx {

// ============================================================================
// Footnote - Container for footnote/endnote text
// ============================================================================

class Footnote : public CompositeNode {
  public:
    Footnote();
    explicit Footnote(Document* doc);
    Footnote(Document* doc, FootnoteType type);

    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    FootnoteType get_footnote_type() const { return type_; }
    void set_footnote_type(FootnoteType type) { type_ = type; }

    bool is_auto() const { return is_auto_; }
    void set_auto(bool value) { is_auto_ = value; }

    std::string get_reference_mark() const { return reference_mark_; }
    void set_reference_mark(const std::string& mark) {
        reference_mark_ = mark;
        is_auto_ = mark.empty();
    }

    std::string get_text() const override;
    void set_text(const std::string& text);

    NodeType node_type() const override {
        return type_ == FootnoteType::Endnote ? NodeType::Endnote : NodeType::Footnote;
    }

    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;

    // Convenience: append paragraph with text
    std::shared_ptr<Paragraph> append_paragraph(const std::string& text = "");

  private:
    int id_ = 0;
    FootnoteType type_ = FootnoteType::Footnote;
    bool is_auto_ = true;
    std::string reference_mark_;
};

// ============================================================================
// FootnoteReference - Inline footnote reference marker
// ============================================================================

class FootnoteReference : public Node {
  public:
    FootnoteReference();
    explicit FootnoteReference(Document* doc);

    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    NodeType node_type() const override { return NodeType::FootnoteReference; }
    std::string get_text() const override { return ""; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;

  private:
    int id_ = 0;
};

// ============================================================================
// EndnoteReference - Inline endnote reference marker
// ============================================================================

class EndnoteReference : public Node {
  public:
    EndnoteReference();
    explicit EndnoteReference(Document* doc);

    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    NodeType node_type() const override { return NodeType::EndnoteReference; }
    std::string get_text() const override { return ""; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;

  private:
    int id_ = 0;
};

// ============================================================================
// FootnoteCollection - Typed access to document footnotes
// ============================================================================

class FootnoteCollection {
  private:
    friend class Document;

    Document* doc_;
    mutable std::vector<std::shared_ptr<Footnote>> footnotes_;
    mutable bool collected_ = false;

    void collect_footnotes() const;

  public:
    FootnoteCollection() : doc_(nullptr), collected_(true) {}
    explicit FootnoteCollection(Document* doc);

    size_t count() const;
    std::shared_ptr<Footnote> get(size_t index) const;
    std::shared_ptr<Footnote> get_by_id(int id) const;
    bool contains(int id) const;

    std::shared_ptr<Footnote> add(const std::string& text);
    std::shared_ptr<Footnote> add(const std::string& text, const std::string& reference_mark);
    bool remove_at(size_t index);
    bool remove(int id);
    void clear();

    std::vector<std::shared_ptr<Footnote>>::iterator begin();
    std::vector<std::shared_ptr<Footnote>>::iterator end();
    std::vector<std::shared_ptr<Footnote>>::const_iterator begin() const;
    std::vector<std::shared_ptr<Footnote>>::const_iterator end() const;
};

// ============================================================================
// EndnoteCollection - Typed access to document endnotes
// ============================================================================

class EndnoteCollection {
  private:
    friend class Document;

    Document* doc_;
    mutable std::vector<std::shared_ptr<Footnote>> endnotes_;
    mutable bool collected_ = false;

    void collect_endnotes() const;

  public:
    EndnoteCollection() : doc_(nullptr), collected_(true) {}
    explicit EndnoteCollection(Document* doc);

    size_t count() const;
    std::shared_ptr<Footnote> get(size_t index) const;
    std::shared_ptr<Footnote> get_by_id(int id) const;
    bool contains(int id) const;

    std::shared_ptr<Footnote> add(const std::string& text);
    std::shared_ptr<Footnote> add(const std::string& text, const std::string& reference_mark);
    bool remove_at(size_t index);
    bool remove(int id);
    void clear();

    std::vector<std::shared_ptr<Footnote>>::iterator begin();
    std::vector<std::shared_ptr<Footnote>>::iterator end();
    std::vector<std::shared_ptr<Footnote>>::const_iterator begin() const;
    std::vector<std::shared_ptr<Footnote>>::const_iterator end() const;
};

}  // namespace cdocx
