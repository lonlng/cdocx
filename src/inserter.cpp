/**
 * @file inserter.cpp
 * @brief DocumentInserter class implementation
 * @details Implementation of document content insertion and merging functionality.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */

#include <cdocx/inserter.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>

namespace cdocx {

// ============================================================================
// Constructor
// ============================================================================

DocumentInserter::DocumentInserter(Document* target) : target_doc_(target) {}

// ============================================================================
// Clone Functions
// ============================================================================

/**
 * @internal
 * @brief Deep clone a paragraph from source to target
 * @param[in] source_para Source paragraph XML node
 * @param[in] target_parent Target parent node (body or cell)
 * @return The cloned paragraph node in target document
 */
pugi::xml_node DocumentInserter::clone_paragraph(const pugi::xml_node& source_para, 
                                                  pugi::xml_node target_parent) {
    // Append new paragraph to target
    pugi::xml_node new_para = target_parent.append_child("w:p");
    
    // Copy paragraph properties if present
    pugi::xml_node pPr = source_para.child("w:pPr");
    if (pPr) {
        new_para.append_copy(pPr);
    }
    
    // Copy all runs
    for (pugi::xml_node run = source_para.child("w:r"); run; run = run.next_sibling("w:r")) {
        new_para.append_copy(run);
    }
    
    return new_para;
}

/**
 * @internal
 * @brief Deep clone a table from source to target
 * @param[in] source_table Source table XML node
 * @param[in] target_parent Target parent node
 * @return The cloned table node in target document
 */
pugi::xml_node DocumentInserter::clone_table(const pugi::xml_node& source_table,
                                              pugi::xml_node target_parent) {
    // Append new table to target
    pugi::xml_node new_table = target_parent.append_child("w:tbl");
    
    // Copy table properties
    pugi::xml_node tblPr = source_table.child("w:tblPr");
    if (tblPr) {
        new_table.append_copy(tblPr);
    }
    
    // Copy table grid
    pugi::xml_node tblGrid = source_table.child("w:tblGrid");
    if (tblGrid) {
        new_table.append_copy(tblGrid);
    }
    
    // Copy all rows
    for (pugi::xml_node row = source_table.child("w:tr"); row; row = row.next_sibling("w:tr")) {
        pugi::xml_node new_row = new_table.append_child("w:tr");
        
        // Copy row properties
        pugi::xml_node trPr = row.child("w:trPr");
        if (trPr) {
            new_row.append_copy(trPr);
        }
        
        // Copy all cells
        for (pugi::xml_node cell = row.child("w:tc"); cell; cell = cell.next_sibling("w:tc")) {
            pugi::xml_node new_cell = new_row.append_child("w:tc");
            
            // Copy cell properties
            pugi::xml_node tcPr = cell.child("w:tcPr");
            if (tcPr) {
                new_cell.append_copy(tcPr);
            }
            
            // Copy all paragraphs in cell
            for (pugi::xml_node para = cell.child("w:p"); para; para = para.next_sibling("w:p")) {
                clone_paragraph(para, new_cell);
            }
        }
    }
    
    return new_table;
}

// ============================================================================
// Insertion Functions
// ============================================================================

void DocumentInserter::insert_document(Document* source) {
    if (!target_doc_ || !source || !target_doc_->is_open() || !source->is_open()) {
        return;
    }
    
    // Get target body
    pugi::xml_document* target_doc = target_doc_->get_document_xml();
    pugi::xml_document* source_doc = source->get_document_xml();
    
    if (!target_doc || !source_doc) {
        return;
    }
    
    pugi::xml_node target_body = target_doc->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc->child("w:document").child("w:body");
    
    if (!target_body || !source_body) {
        return;
    }
    
    // Clone all paragraphs and tables from source
    for (pugi::xml_node child = source_body.first_child(); child; child = child.next_sibling()) {
        std::string name = child.name();
        if (name == "w:p") {
            clone_paragraph(child, target_body);
        } else if (name == "w:tbl") {
            clone_table(child, target_body);
        }
    }
}

void DocumentInserter::insert_document_after(Document* source, Paragraph& after_para) {
    if (!target_doc_ || !source || !target_doc_->is_open() || !source->is_open()) {
        return;
    }
    
    // Get the insertion point
    pugi::xml_node insert_after = after_para.get_current_node();
    if (!insert_after) {
        return;
    }
    
    // Get source body
    pugi::xml_document* source_doc = source->get_document_xml();
    if (!source_doc) {
        return;
    }
    
    pugi::xml_node source_body = source_doc->child("w:document").child("w:body");
    if (!source_body) {
        return;
    }
    
    // Clone and insert after the reference paragraph
    pugi::xml_node last_inserted = insert_after;
    
    for (pugi::xml_node child = source_body.first_child(); child; child = child.next_sibling()) {
        std::string name = child.name();
        pugi::xml_node new_node;
        
        if (name == "w:p") {
            new_node = insert_after.parent().insert_child_after("w:p", last_inserted);
            // Copy content
            for (pugi::xml_node run = child.child("w:r"); run; run = run.next_sibling("w:r")) {
                new_node.append_copy(run);
            }
        } else if (name == "w:tbl") {
            new_node = insert_after.parent().insert_child_after("w:tbl", last_inserted);
            // Copy content
            for (pugi::xml_node row = child.child("w:tr"); row; row = row.next_sibling("w:tr")) {
                new_node.append_copy(row);
            }
        }
        
        if (new_node) {
            last_inserted = new_node;
        }
    }
}

void DocumentInserter::insert_document_at(Document* source, int position) {
    if (!target_doc_ || !source || !target_doc_->is_open() || !source->is_open()) {
        return;
    }
    
    // Get target body
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc) {
        return;
    }
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc->child("w:document").child("w:body");
    
    if (!target_body || !source_body) {
        return;
    }
    
    // Find insertion point
    pugi::xml_node insert_before;
    if (position <= 0) {
        // Insert at beginning
        insert_before = target_body.first_child();
    } else {
        // Count to position
        int count = 0;
        for (pugi::xml_node child = target_body.first_child(); child; child = child.next_sibling()) {
            std::string name = child.name();
            if (name == "w:p" || name == "w:tbl") {
                count++;
                if (count == position) {
                    insert_before = child.next_sibling();
                    break;
                }
            }
        }
    }
    
    // Clone source content in reverse order (to insert before same point)
    std::vector<pugi::xml_node> nodes_to_clone;
    for (pugi::xml_node child = source_body.first_child(); child; child = child.next_sibling()) {
        std::string name = child.name();
        if (name == "w:p" || name == "w:tbl") {
            nodes_to_clone.push_back(child);
        }
    }
    
    // Insert in reverse order
    for (auto it = nodes_to_clone.rbegin(); it != nodes_to_clone.rend(); ++it) {
        std::string name = it->name();
        pugi::xml_node new_node;
        
        if (insert_before) {
            new_node = target_body.insert_child_before(name.c_str(), insert_before);
        } else {
            new_node = target_body.append_child(name.c_str());
        }
        
        // Copy content
        for (pugi::xml_node attr = it->first_child(); attr; attr = attr.next_sibling()) {
            new_node.append_copy(attr);
        }
    }
}

void DocumentInserter::insert_paragraphs(Document* source, int position) {
    if (!target_doc_ || !source || !target_doc_->is_open() || !source->is_open()) {
        return;
    }
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc) {
        return;
    }
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc->child("w:document").child("w:body");
    
    if (!target_body || !source_body) {
        return;
    }
    
    // Find insertion point (similar to insert_document_at)
    pugi::xml_node insert_before;
    if (position <= 0) {
        insert_before = target_body.first_child();
    } else {
        int count = 0;
        for (pugi::xml_node child = target_body.first_child(); child; child = child.next_sibling()) {
            if (std::string(child.name()) == "w:p" || std::string(child.name()) == "w:tbl") {
                count++;
                if (count == position) {
                    insert_before = child.next_sibling();
                    break;
                }
            }
        }
    }
    
    // Collect and clone only paragraphs
    std::vector<pugi::xml_node> paras_to_clone;
    for (pugi::xml_node child = source_body.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "w:p") {
            paras_to_clone.push_back(child);
        }
    }
    
    // Insert in reverse order
    for (auto it = paras_to_clone.rbegin(); it != paras_to_clone.rend(); ++it) {
        pugi::xml_node new_para;
        if (insert_before) {
            new_para = target_body.insert_child_before("w:p", insert_before);
        } else {
            new_para = target_body.append_child("w:p");
        }
        
        // Copy all content
        for (pugi::xml_node attr = it->first_child(); attr; attr = attr.next_sibling()) {
            new_para.append_copy(attr);
        }
    }
}

void DocumentInserter::insert_tables(Document* source, int position) {
    if (!target_doc_ || !source || !target_doc_->is_open() || !source->is_open()) {
        return;
    }
    
    pugi::xml_document* target_doc_xml = target_doc_->get_document_xml();
    pugi::xml_document* source_doc = source->get_document_xml();
    
    if (!target_doc_xml || !source_doc) {
        return;
    }
    
    pugi::xml_node target_body = target_doc_xml->child("w:document").child("w:body");
    pugi::xml_node source_body = source_doc->child("w:document").child("w:body");
    
    if (!target_body || !source_body) {
        return;
    }
    
    // Find insertion point
    pugi::xml_node insert_before;
    if (position <= 0) {
        insert_before = target_body.first_child();
    } else {
        int count = 0;
        for (pugi::xml_node child = target_body.first_child(); child; child = child.next_sibling()) {
            if (std::string(child.name()) == "w:p" || std::string(child.name()) == "w:tbl") {
                count++;
                if (count == position) {
                    insert_before = child.next_sibling();
                    break;
                }
            }
        }
    }
    
    // Collect and clone only tables
    std::vector<pugi::xml_node> tables_to_clone;
    for (pugi::xml_node child = source_body.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "w:tbl") {
            tables_to_clone.push_back(child);
        }
    }
    
    // Insert in reverse order
    for (auto it = tables_to_clone.rbegin(); it != tables_to_clone.rend(); ++it) {
        pugi::xml_node new_table;
        if (insert_before) {
            new_table = target_body.insert_child_before("w:tbl", insert_before);
        } else {
            new_table = target_body.append_child("w:tbl");
        }
        
        // Copy all content
        for (pugi::xml_node attr = it->first_child(); attr; attr = attr.next_sibling()) {
            new_table.append_copy(attr);
        }
    }
}

} // namespace cdocx
