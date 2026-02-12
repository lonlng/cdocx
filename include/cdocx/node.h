/**
 * @file node.h
 * @brief Node base classes for CDocx document model - DOM Style
 * @details Defines the core node hierarchy with Composite pattern.
 *          This is the foundation of the DOM-style document API.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0
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
class CompositeNode;
class Section;
class Body;
class HeaderFooter;
class Paragraph;
class Run;
class Table;
class Row;
class Cell;
class SpecialChar;
class Field;
class BookmarkStart;
class BookmarkEnd;
class DocumentVisitor;
class NodeCollection;

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
    int custom_id_ = 0;  // For user-defined identification

public:
    virtual ~Node() = default;

    // Abstract interface
    virtual NodeType node_type() const = 0;
    virtual std::string get_text() const { return ""; }
    virtual std::shared_ptr<Node> clone(bool deep = true) const = 0;
    virtual void accept(DocumentVisitor* visitor) = 0;
    virtual bool is_composite() const { return false; }
    
    // Tree structure
    Document* get_document() const { return document_; }
    void set_document(Document* doc) { document_ = doc; }
    
    CompositeNode* get_parent() const { return parent_; }
    void set_parent(CompositeNode* parent) { parent_ = parent; }
    
    std::shared_ptr<Node> get_next_sibling() const { return next_sibling_; }
    std::shared_ptr<Node> get_previous_sibling() const { return prev_sibling_; }
    
    void set_next_sibling(std::shared_ptr<Node> node) { next_sibling_ = node; }
    void set_previous_sibling(std::shared_ptr<Node> node) { prev_sibling_ = node; }
    
    // Custom node ID (not saved to file)
    int get_custom_id() const { return custom_id_; }
    void set_custom_id(int id) { custom_id_ = id; }
    
    // Utility methods
    bool is_deleted() const { return is_deleted_; }
    void mark_deleted() { is_deleted_ = true; }
    
    // Remove this node from its parent
    void remove();
    
    // Get the index of this node in its parent's children
    int get_index() const;
    
    // Check if this node is a descendant of another node
    bool is_descendant_of(const Node* ancestor) const;
    
    // Get ancestor of specific type
    template<typename T>
    T* get_ancestor() const {
        Node* current = parent_;
        while (current) {
            if (auto typed = dynamic_cast<T*>(current)) {
                return typed;
            }
            current = current->get_parent();
        }
        return nullptr;
    }
    
    // Get previous node in document order (pre-order traversal)
    std::shared_ptr<Node> get_previous_node_in_document() const;
    
    // Get next node in document order (pre-order traversal)
    std::shared_ptr<Node> get_next_node_in_document() const;
    
    // Get the previous sibling or parent's previous sibling
    std::shared_ptr<Node> get_previous_logical() const;
    
    // Get the next sibling or parent's next sibling
    std::shared_ptr<Node> get_next_logical() const;
};

// ============================================================================
// CompositeNode Class - Node that can contain child nodes
// ============================================================================

class CompositeNode : public Node {
protected:
    std::vector<std::shared_ptr<Node>> children_;

public:
    // Child node operations
    const std::vector<std::shared_ptr<Node>>& get_children() const { return children_; }
    
    // Get first/last child
    std::shared_ptr<Node> get_first_child() const;
    std::shared_ptr<Node> get_last_child() const;
    
    // Get child count
    size_t get_child_count() const { return children_.size(); }
    bool has_children() const { return !children_.empty(); }
    
    // Get child at index
    std::shared_ptr<Node> get_child(int index) const;
    std::shared_ptr<Node> get_child(size_t index) const {
        return get_child(static_cast<int>(index));
    }
    
    // Child manipulation
    std::shared_ptr<Node> append_child(std::shared_ptr<Node> child);
    std::shared_ptr<Node> prepend_child(std::shared_ptr<Node> child);
    std::shared_ptr<Node> insert_child(int index, std::shared_ptr<Node> child);
    std::shared_ptr<Node> insert_before(std::shared_ptr<Node> new_node, 
                                         std::shared_ptr<Node> ref_node);
    std::shared_ptr<Node> insert_after(std::shared_ptr<Node> new_node, 
                                        std::shared_ptr<Node> ref_node);
    void remove_child(std::shared_ptr<Node> child);
    void remove_child(int index);
    void remove_all_children();
    
    // Find child index
    int index_of(const std::shared_ptr<Node>& child) const;
    
    // Typed access helpers
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
    
    // NodeCollection access
    NodeCollection get_child_nodes() const;
    NodeCollection get_child_nodes(NodeType type) const;
    
    // Node overrides
    bool is_composite() const override { return true; }
    std::string get_text() const override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
    // Accept visitor start/end (for nodes with children)
    virtual VisitorAction accept_start(DocumentVisitor* visitor) {
        return VisitorAction::Continue;
    }
    virtual VisitorAction accept_end(DocumentVisitor* visitor) {
        return VisitorAction::Continue;
    }
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
    
    // Collection properties
    size_t get_count() const { return nodes_.size(); }
    bool is_empty() const { return nodes_.empty(); }
    
    // Element access
    std::shared_ptr<Node> get_item(size_t index) const {
        if (index < nodes_.size()) {
            return nodes_[index];
        }
        return nullptr;
    }
    std::shared_ptr<Node> operator[](size_t index) const {
        return get_item(index);
    }
    std::shared_ptr<Node> first() const {
        return nodes_.empty() ? nullptr : nodes_.front();
    }
    std::shared_ptr<Node> last() const {
        return nodes_.empty() ? nullptr : nodes_.back();
    }
    
    // Iterators
    iterator begin() { return nodes_.begin(); }
    iterator end() { return nodes_.end(); }
    const_iterator begin() const { return nodes_.begin(); }
    const_iterator end() const { return nodes_.end(); }
    
    // Filtering
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
    
    // Searching
    std::shared_ptr<Node> find(const std::string& text) const;
    std::vector<std::shared_ptr<Node>> find_all(const std::string& text) const;
    std::shared_ptr<Node> find_if(std::function<bool(const Node&)> predicate) const;
    NodeCollection find_all_if(std::function<bool(const Node&)> predicate) const;
    
    // Modification
    void add(std::shared_ptr<Node> node);
    void remove(std::shared_ptr<Node> node);
    void remove_at(size_t index);
    void clear();
    void insert(size_t index, std::shared_ptr<Node> node);
    
    // Get text from all nodes
    std::string get_text() const;
};

// ============================================================================
// DocumentVisitor Class - Visitor pattern for traversing document
// ============================================================================

class DocumentVisitor {
public:
    virtual ~DocumentVisitor() = default;
    
    // Document
    virtual VisitorAction visit_document_start(Document& doc) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_document_end(Document& doc) { 
        return VisitorAction::Continue; 
    }
    
    // Section
    virtual VisitorAction visit_section_start(Section& section) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_section_end(Section& section) { 
        return VisitorAction::Continue; 
    }
    
    // Body
    virtual VisitorAction visit_body_start(Body& body) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_body_end(Body& body) { 
        return VisitorAction::Continue; 
    }
    
    // Header/Footer
    virtual VisitorAction visit_header_start(HeaderFooter& header) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_header_end(HeaderFooter& header) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_footer_start(HeaderFooter& footer) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_footer_end(HeaderFooter& footer) { 
        return VisitorAction::Continue; 
    }
    
    // Paragraph
    virtual VisitorAction visit_paragraph_start(Paragraph& para) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_paragraph_end(Paragraph& para) { 
        return VisitorAction::Continue; 
    }
    
    // Table
    virtual VisitorAction visit_table_start(Table& table) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_table_end(Table& table) { 
        return VisitorAction::Continue; 
    }
    
    // Row
    virtual VisitorAction visit_row_start(Row& row) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_row_end(Row& row) { 
        return VisitorAction::Continue; 
    }
    
    // Cell
    virtual VisitorAction visit_cell_start(Cell& cell) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_cell_end(Cell& cell) { 
        return VisitorAction::Continue; 
    }
    
    // Run (leaf node - no start/end)
    virtual VisitorAction visit_run(Run& run) { 
        return VisitorAction::Continue; 
    }
    
    // SpecialChar (leaf node)
    virtual VisitorAction visit_special_char(SpecialChar& ch) { 
        return VisitorAction::Continue; 
    }
    
    // Field
    virtual VisitorAction visit_field_start(Field& field) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_field_separator(Field& field) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_field_end(Field& field) { 
        return VisitorAction::Continue; 
    }
    
    // Bookmark
    virtual VisitorAction visit_bookmark_start(BookmarkStart& bookmark) { 
        return VisitorAction::Continue; 
    }
    virtual VisitorAction visit_bookmark_end(BookmarkEnd& bookmark) { 
        return VisitorAction::Continue; 
    }
};

} // namespace cdocx
