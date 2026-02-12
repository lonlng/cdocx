/**
 * @file node.h
 * @brief Node base classes for CDocx document model
 * @details Defines the core node hierarchy with Composite pattern
 */

#pragma once

#include <cdocx/enums.h>
#include <memory>
#include <string>
#include <vector>
#include <functional>

namespace cdocx {

// Forward declarations
class Document;
class Node;
class CompositeNode;
class NodeCollection;
class DocumentVisitor;

// ============================================================================
// Node Class - Abstract base for all document nodes
// ============================================================================

class Node : public std::enable_shared_from_this<Node> {
protected:
    Document* document_ = nullptr;
    CompositeNode* parent_ = nullptr;
    std::shared_ptr<Node> next_sibling_;
    std::shared_ptr<Node> prev_sibling_;
    bool is_deleted_ = false;

public:
    virtual ~Node() = default;

    // ------------------------------------------------------------------------
    // Abstract interface
    // ------------------------------------------------------------------------
    virtual NodeType node_type() const = 0;
    virtual std::string get_text() const { return ""; }
    virtual std::shared_ptr<Node> clone(bool deep = true) const = 0;
    virtual void accept(DocumentVisitor* visitor) = 0;

    // ------------------------------------------------------------------------
    // Tree structure
    // ------------------------------------------------------------------------
    Document* get_document() const { return document_; }
    void set_document(Document* doc) { document_ = doc; }
    
    CompositeNode* get_parent() const { return parent_; }
    void set_parent(CompositeNode* parent) { parent_ = parent; }
    
    std::shared_ptr<Node> get_next_sibling() const { return next_sibling_; }
    std::shared_ptr<Node> get_previous_sibling() const { return prev_sibling_; }
    
    void set_next_sibling(std::shared_ptr<Node> node) { next_sibling_ = node; }
    void set_previous_sibling(std::shared_ptr<Node> node) { prev_sibling_ = node; }
    
    // ------------------------------------------------------------------------
    // Utility methods
    // ------------------------------------------------------------------------
    virtual bool is_composite() const { return false; }
    bool is_deleted() const { return is_deleted_; }
    void mark_deleted() { is_deleted_ = true; }
    
    // Remove this node from its parent
    void remove();
    
    // Get the index of this node in its parent's children
    int get_index() const;
    
    // Check if this node is a descendant of another node
    bool is_descendant_of(const Node* ancestor) const;
    
    // Get the previous node in the document (pre-order traversal)
    std::shared_ptr<Node> get_previous_node() const;
    
    // Get the next node in the document (pre-order traversal)
    std::shared_ptr<Node> get_next_node() const;
};

// ============================================================================
// CompositeNode Class - Node that can contain child nodes
// ============================================================================

class CompositeNode : public Node {
protected:
    std::vector<std::shared_ptr<Node>> children_;

public:
    // ------------------------------------------------------------------------
    // Child node operations
    // ------------------------------------------------------------------------
    const std::vector<std::shared_ptr<Node>>& get_children() const { return children_; }
    
    // Get first/last child
    std::shared_ptr<Node> get_first_child() const;
    std::shared_ptr<Node> get_last_child() const;
    
    // Get child count
    size_t get_child_count() const { return children_.size(); }
    
    // Get child at index
    std::shared_ptr<Node> get_child(int index) const;
    
    // Check if has children
    bool has_children() const { return !children_.empty(); }
    
    // ------------------------------------------------------------------------
    // Child manipulation
    // ------------------------------------------------------------------------
    // Append a child node
    std::shared_ptr<Node> append_child(std::shared_ptr<Node> child);
    
    // Insert a child at specific index
    std::shared_ptr<Node> insert_child(int index, std::shared_ptr<Node> child);
    
    // Insert before reference node
    std::shared_ptr<Node> insert_before(std::shared_ptr<Node> new_node, 
                                         std::shared_ptr<Node> ref_node);
    
    // Insert after reference node
    std::shared_ptr<Node> insert_after(std::shared_ptr<Node> new_node, 
                                        std::shared_ptr<Node> ref_node);
    
    // Remove a child
    void remove_child(std::shared_ptr<Node> child);
    
    // Remove child at index
    void remove_child(int index);
    
    // Remove all children
    void remove_all_children();
    
    // ------------------------------------------------------------------------
    // Typed access helpers
    // ------------------------------------------------------------------------
    template<typename T>
    std::shared_ptr<T> get_first_child() const {
        for (const auto& child : children_) {
            if (auto typed = std::dynamic_pointer_cast<T>(child)) {
                return typed;
            }
        }
        return nullptr;
    }
    
    template<typename T>
    std::shared_ptr<T> get_last_child() const {
        for (auto it = children_.rbegin(); it != children_.rend(); ++it) {
            if (auto typed = std::dynamic_pointer_cast<T>(*it)) {
                return typed;
            }
        }
        return nullptr;
    }
    
    template<typename T>
    std::vector<std::shared_ptr<T>> get_children_of_type() const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& child : children_) {
            if (auto typed = std::dynamic_pointer_cast<T>(child)) {
                result.push_back(typed);
            }
        }
        return result;
    }
    
    // ------------------------------------------------------------------------
    // NodeCollection access
    // ------------------------------------------------------------------------
    NodeCollection get_child_nodes() const;
    NodeCollection get_child_nodes(NodeType type) const;
    
    // ------------------------------------------------------------------------
    // Node overrides
    // ------------------------------------------------------------------------
    bool is_composite() const override { return true; }
    std::string get_text() const override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
};

// ============================================================================
// NodeCollection Class - Collection of nodes with filtering
// ============================================================================

class NodeCollection {
public:
    using NodeList = std::vector<std::shared_ptr<Node>>;
    using iterator = NodeList::iterator;
    using const_iterator = NodeList::const_iterator;

private:
    NodeList nodes_;

public:
    // Construction
    NodeCollection() = default;
    explicit NodeCollection(const NodeList& nodes) : nodes_(nodes) {}
    explicit NodeCollection(NodeList&& nodes) : nodes_(std::move(nodes)) {}
    
    // ------------------------------------------------------------------------
    // Collection properties
    // ------------------------------------------------------------------------
    size_t get_count() const { return nodes_.size(); }
    bool is_empty() const { return nodes_.empty(); }
    
    // ------------------------------------------------------------------------
    // Element access
    // ------------------------------------------------------------------------
    std::shared_ptr<Node> get_item(size_t index) const {
        if (index < nodes_.size()) {
            return nodes_[index];
        }
        return nullptr;
    }
    
    std::shared_ptr<Node> operator[](size_t index) const {
        return get_item(index);
    }
    
    // ------------------------------------------------------------------------
    // Iterators
    // ------------------------------------------------------------------------
    iterator begin() { return nodes_.begin(); }
    iterator end() { return nodes_.end(); }
    const_iterator begin() const { return nodes_.begin(); }
    const_iterator end() const { return nodes_.end(); }
    
    // ------------------------------------------------------------------------
    // Filtering
    // ------------------------------------------------------------------------
    NodeCollection of_type(NodeType type) const;
    
    template<typename T>
    std::vector<std::shared_ptr<T>> of_type() const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& node : nodes_) {
            if (auto typed = std::dynamic_pointer_cast<T>(node)) {
                result.push_back(typed);
            }
        }
        return result;
    }
    
    // ------------------------------------------------------------------------
    // Searching
    // ------------------------------------------------------------------------
    std::shared_ptr<Node> find(const std::string& text) const;
    std::vector<std::shared_ptr<Node>> find_all(const std::string& text) const;
    
    // Find by predicate
    std::shared_ptr<Node> find_if(std::function<bool(const Node&)> predicate) const;
    NodeCollection find_all_if(std::function<bool(const Node&)> predicate) const;
    
    // ------------------------------------------------------------------------
    // Modification
    // ------------------------------------------------------------------------
    void add(std::shared_ptr<Node> node);
    void remove(std::shared_ptr<Node> node);
    void clear();
    
    // ------------------------------------------------------------------------
    // Typed shortcuts
    // ------------------------------------------------------------------------
    std::shared_ptr<Node> first() const {
        return nodes_.empty() ? nullptr : nodes_.front();
    }
    
    std::shared_ptr<Node> last() const {
        return nodes_.empty() ? nullptr : nodes_.back();
    }
};

// ============================================================================
// DocumentVisitor Class - Visitor pattern for traversing document
// ============================================================================

class DocumentVisitor {
public:
    virtual ~DocumentVisitor() = default;
    
    // Called when visitor starts visiting a document
    virtual VisitorAction visit_document_start(Document& doc) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visitor finishes visiting a document
    virtual VisitorAction visit_document_end(Document& doc) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a section
    virtual VisitorAction visit_section_start(class Section& section) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_section_end(class Section& section) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a paragraph
    virtual VisitorAction visit_paragraph_start(class Paragraph& para) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_paragraph_end(class Paragraph& para) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a run
    virtual VisitorAction visit_run(class Run& run) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a table
    virtual VisitorAction visit_table_start(class Table& table) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_table_end(class Table& table) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a row
    virtual VisitorAction visit_row_start(class Row& row) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_row_end(class Row& row) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a cell
    virtual VisitorAction visit_cell_start(class Cell& cell) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_cell_end(class Cell& cell) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting special characters
    virtual VisitorAction visit_special_char(class SpecialChar& ch) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a field
    virtual VisitorAction visit_field_start(class Field& field) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_field_separator(class Field& field) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_field_end(class Field& field) { 
        return VisitorAction::Continue; 
    }
    
    // Called when visiting a bookmark
    virtual VisitorAction visit_bookmark_start(class BookmarkStart& bookmark) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_bookmark_end(class BookmarkEnd& bookmark) { 
        return VisitorAction::Continue; 
    }
};

} // namespace cdocx
