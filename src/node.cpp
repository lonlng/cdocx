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
    if (!parent_) {
        return -1;
    }
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
        if (current == ancestor) {
            return true;
        }
        current = current->get_parent();
    }
    return false;
}

std::shared_ptr<Node> Node::get_previous_node_in_document() const {
    auto prev = prev_sibling_.lock();
    if (prev) {
        // Pre-order: previous sibling's deepest last descendant
        auto current = prev;
        while (current->is_composite()) {
            auto composite = std::dynamic_pointer_cast<CompositeNode>(current);
            if (!composite || !composite->has_children()) {
                break;
            }
            current = composite->get_last_child();
        }
        return current;
    }
    // No previous sibling: return parent
    if (parent_) {
        return static_cast<Node*>(parent_)->shared_from_this();
    }
    return nullptr;
}

std::shared_ptr<Node> Node::get_next_node_in_document() const {
    // Pre-order: first child, then next sibling, then ancestor's next sibling
    if (is_composite()) {
        const auto* composite = dynamic_cast<const CompositeNode*>(this);
        if (composite && composite->has_children()) {
            return composite->get_first_child();
        }
    }
    auto next = next_sibling_.lock();
    if (next) {
        return next;
    }
    auto* current = parent_;
    while (current) {
        if (current->get_next_sibling()) {
            return current->get_next_sibling();
        }
        current = current->get_parent();
    }
    return nullptr;
}

std::shared_ptr<Node> Node::get_previous_logical() const {
    return prev_sibling_.lock();
}

std::shared_ptr<Node> Node::get_next_logical() const {
    return next_sibling_.lock();
}

// ============================================================================
// CompositeNode Implementation
// ============================================================================

std::shared_ptr<Node> CompositeNode::get_first_child() const {
    if (children_.empty()) {
        return nullptr;
    }
    return children_.front();
}

std::shared_ptr<Node> CompositeNode::get_last_child() const {
    if (children_.empty()) {
        return nullptr;
    }
    return children_.back();
}

std::shared_ptr<Node> CompositeNode::get_child(int index) const {
    if (index < 0 || static_cast<size_t>(index) >= children_.size()) {
        return nullptr;
    }
    return children_[index];
}

int CompositeNode::index_of(const std::shared_ptr<Node>& child) const {
    if (!child) {
        return -1;
    }
    for (size_t i = 0; i < children_.size(); ++i) {
        if (children_[i] == child) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::shared_ptr<Node> CompositeNode::append_child(std::shared_ptr<Node> child) {
    if (!child) {
        return nullptr;
    }

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
    if (!child || index < 0 || static_cast<size_t>(index) > children_.size()) {
        return nullptr;
    }

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

std::shared_ptr<Node> CompositeNode::insert_before(const std::shared_ptr<Node>& new_node,
                                                   const std::shared_ptr<Node>& ref_node) {
    if (!new_node || !ref_node) {
        return nullptr;
    }

    for (size_t i = 0; i < children_.size(); ++i) {
        if (children_[i] == ref_node) {
            return insert_child(static_cast<int>(i), new_node);
        }
    }
    return nullptr;
}

std::shared_ptr<Node> CompositeNode::insert_after(const std::shared_ptr<Node>& new_node,
                                                  const std::shared_ptr<Node>& ref_node) {
    if (!new_node || !ref_node) {
        return nullptr;
    }

    for (size_t i = 0; i < children_.size(); ++i) {
        if (children_[i] == ref_node) {
            return insert_child(static_cast<int>(i + 1), new_node);
        }
    }
    return nullptr;
}

void CompositeNode::remove_child(const std::shared_ptr<Node>& child) {
    if (!child) {
        return;
    }

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

std::shared_ptr<Node> CompositeNode::clone(bool /*deep*/) const {
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

std::shared_ptr<Node> NodeCollection::find_if(
    const std::function<bool(const Node&)>& predicate) const {
    for (const auto& node : nodes_) {
        if (predicate(*node)) {
            return node;
        }
    }
    return nullptr;
}

NodeCollection NodeCollection::find_all_if(
    const std::function<bool(const Node&)>& predicate) const {
    std::vector<std::shared_ptr<Node>> result;
    for (const auto& node : nodes_) {
        if (predicate(*node)) {
            result.push_back(node);
        }
    }
    return NodeCollection(result);
}

void NodeCollection::add(const std::shared_ptr<Node>& node) {
    if (node) {
        nodes_.push_back(node);
    }
}

void NodeCollection::remove(const std::shared_ptr<Node>& node) {
    if (!node) {
        return;
    }
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

}  // namespace cdocx
