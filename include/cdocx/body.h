/**
 * @file body.h
 * @brief Body class for CDocx
 * @details The Body class represents the main content container of a section.
 *          It can contain paragraphs, tables, and other block-level elements.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0
 */

#pragma once

#include <cdocx/node.h>
#include <cdocx/format.h>

#include <memory>
#include <vector>
#include <string>

namespace cdocx {

// Forward declarations
class Section;
class Document;
class Paragraph;
class Table;

// ============================================================================
// Body Class - Main content container of a section
// ============================================================================

class Body : public CompositeNode {
public:
    Body();
    explicit Body(Document* doc);
    
    // Node overrides
    NodeType node_type() const override { return NodeType::Body; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep = true) const override;
    
    // Parent section
    std::shared_ptr<Section> get_parent_section() const;
    
    // Paragraph operations
    std::shared_ptr<Paragraph> append_paragraph(const std::string& text = "");
    std::shared_ptr<Paragraph> insert_paragraph(int index, const std::string& text = "");
    std::shared_ptr<Paragraph> get_first_paragraph() const;
    std::shared_ptr<Paragraph> get_last_paragraph() const;
    
    // Get paragraphs collection
    std::vector<std::shared_ptr<Paragraph>> get_paragraphs() const;
    
    // Table operations
    std::shared_ptr<Table> append_table(int rows = 1, int cols = 1);
    std::shared_ptr<Table> insert_table(int index, int rows = 1, int cols = 1);
    std::shared_ptr<Table> get_first_table() const;
    std::shared_ptr<Table> get_last_table() const;
    
    // Get tables collection
    std::vector<std::shared_ptr<Table>> get_tables() const;
    
    // Typed child access
    template<typename T>
    std::vector<std::shared_ptr<T>> get_children_of_type() const;
    
    // Ensure minimum content (at least one paragraph)
    void ensure_minimum();
    
    // Get all text content
    std::string get_text() const override;
    
private:
    // Helper to rebuild typed caches
    void rebuild_caches() const;
    
    mutable std::vector<std::weak_ptr<Paragraph>> paragraph_cache_;
    mutable std::vector<std::weak_ptr<Table>> table_cache_;
    mutable bool caches_dirty_ = true;
};

} // namespace cdocx
