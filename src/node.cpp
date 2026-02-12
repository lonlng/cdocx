/**
 * @file node.cpp
 * @brief Node class implementations
 * @details Implementation of Node, CompositeNode and related classes
 */

#include <cdocx/node.h>
#include <cdocx/paragraph.h>
#include <cdocx/table.h>

namespace cdocx {

// ============================================================================
// Node Implementation
// ============================================================================

void Node::remove() {
    if (parent_) {
        parent_->remove_child(shared_from_this());
    }
}

int Node::get_index() const {
    if (!parent_) return -1;
    const auto& children = parent_->get_children();
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i].get() == this) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool Node::is_descendant_of(const Node* ancestor) const {
    Node* current = parent_;
    while (current) {
        if (current == ancestor) return true;
        current = current->get_parent();
    }
    return false;
}

std::shared_ptr<Node> Node::get_previous_node() const {
    if (prev_sibling_) {
        return prev_sibling_;
    }
    return nullptr;
}

std::shared_ptr<Node> Node::get_next_node() const {
    if (next_sibling_) {
        return next_sibling_;
    }
    return nullptr;
}

// ============================================================================
// CompositeNode Implementation
// ============================================================================

std::shared_ptr<Node> CompositeNode::get_first_child() const {
    if (children_.empty()) return nullptr;
    return children_.front();
}

std::shared_ptr<Node> CompositeNode::get_last_child() const {
    if (children_.empty()) return nullptr;
    return children_.back();
}

std::shared_ptr<Node> CompositeNode::get_child(int index) const {
    if (index < 0 || static_cast<size_t>(index) >= children_.size()) return nullptr;
    return children_[index];
}

std::shared_ptr<Node> CompositeNode::append_child(std::shared_ptr<Node> child) {
    if (!child) return nullptr;
    
    child->set_parent(this);
    child->set_document(document_);
    
    if (!children_.empty()) {
        child->set_previous_sibling(children_.back());
        children_.back()->set_next_sibling(child);
    }
    
    children_.push_back(child);
    return child;
}

std::shared_ptr<Node> CompositeNode::insert_child(int index, std::shared_ptr<Node> child) {
    if (!child || index < 0 || static_cast<size_t>(index) > children_.size()) return nullptr;
    
    child->set_parent(this);
    child->set_document(document_);
    
    if (index == 0) {
        if (!children_.empty()) {
            child->set_next_sibling(children_.front());
            children_.front()->set_previous_sibling(child);
        }
        children_.insert(children_.begin(), child);
    } else {
        auto it = children_.begin() + index;
        child->set_previous_sibling(*(it - 1));
        child->set_next_sibling(*it);
        (*(it - 1))->set_next_sibling(child);
        (*it)->set_previous_sibling(child);
        children_.insert(it, child);
    }
    
    return child;
}

std::shared_ptr<Node> CompositeNode::insert_before(std::shared_ptr<Node> new_node, 
                                                    std::shared_ptr<Node> ref_node) {
    if (!new_node || !ref_node) return nullptr;
    
    for (size_t i = 0; i < children_.size(); ++i) {
        if (children_[i] == ref_node) {
            return insert_child(static_cast<int>(i), new_node);
        }
    }
    return nullptr;
}

std::shared_ptr<Node> CompositeNode::insert_after(std::shared_ptr<Node> new_node, 
                                                   std::shared_ptr<Node> ref_node) {
    if (!new_node || !ref_node) return nullptr;
    
    for (size_t i = 0; i < children_.size(); ++i) {
        if (children_[i] == ref_node) {
            return insert_child(static_cast<int>(i + 1), new_node);
        }
    }
    return nullptr;
}

void CompositeNode::remove_child(std::shared_ptr<Node> child) {
    if (!child) return;
    
    for (auto it = children_.begin(); it != children_.end(); ++it) {
        if (*it == child) {
            // Update sibling links
            if (child->get_previous_sibling()) {
                child->get_previous_sibling()->set_next_sibling(child->get_next_sibling());
            }
            if (child->get_next_sibling()) {
                child->get_next_sibling()->set_previous_sibling(child->get_previous_sibling());
            }
            
            child->set_parent(nullptr);
            children_.erase(it);
            return;
        }
    }
}

void CompositeNode::remove_child(int index) {
    if (index >= 0 && static_cast<size_t>(index) < children_.size()) {
        remove_child(children_[index]);
    }
}

void CompositeNode::remove_all_children() {
    for (auto& child : children_) {
        child->set_parent(nullptr);
    }
    children_.clear();
}

std::string CompositeNode::get_text() const {
    std::string result;
    for (const auto& child : children_) {
        result += child->get_text();
    }
    return result;
}

std::shared_ptr<Node> CompositeNode::clone(bool deep) const {
    // Base implementation - derived classes should override
    return nullptr;
}

NodeCollection CompositeNode::get_child_nodes() const {
    return NodeCollection(children_);
}

NodeCollection CompositeNode::get_child_nodes(NodeType type) const {
    std::vector<std::shared_ptr<Node>> filtered;
    for (const auto& child : children_) {
        if (child->node_type() == type) {
            filtered.push_back(child);
        }
    }
    return NodeCollection(filtered);
}

// ============================================================================
// NodeCollection Implementation
// ============================================================================

NodeCollection NodeCollection::of_type(NodeType type) const {
    std::vector<std::shared_ptr<Node>> filtered;
    for (const auto& node : nodes_) {
        if (node->node_type() == type) {
            filtered.push_back(node);
        }
    }
    return NodeCollection(filtered);
}

std::shared_ptr<Node> NodeCollection::find(const std::string& text) const {
    for (const auto& node : nodes_) {
        if (node->get_text().find(text) != std::string::npos) {
            return node;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Node>> NodeCollection::find_all(const std::string& text) const {
    std::vector<std::shared_ptr<Node>> result;
    for (const auto& node : nodes_) {
        if (node->get_text().find(text) != std::string::npos) {
            result.push_back(node);
        }
    }
    return result;
}

std::shared_ptr<Node> NodeCollection::find_if(std::function<bool(const Node&)> predicate) const {
    for (const auto& node : nodes_) {
        if (predicate(*node)) {
            return node;
        }
    }
    return nullptr;
}

NodeCollection NodeCollection::find_all_if(std::function<bool(const Node&)> predicate) const {
    std::vector<std::shared_ptr<Node>> result;
    for (const auto& node : nodes_) {
        if (predicate(*node)) {
            result.push_back(node);
        }
    }
    return NodeCollection(result);
}

void NodeCollection::add(std::shared_ptr<Node> node) {
    if (node) {
        nodes_.push_back(node);
    }
}

void NodeCollection::remove(std::shared_ptr<Node> node) {
    if (!node) return;
    for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
        if (*it == node) {
            nodes_.erase(it);
            return;
        }
    }
}

void NodeCollection::clear() {
    nodes_.clear();
}

} // namespace cdocx
