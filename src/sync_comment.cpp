/**
 * @file sync_comment.cpp
 * @brief Comment sync
 */

#include "sync_common.h"

#include <cdocx/comment.h>
#include <cdocx/document.h>

#include <chrono>
#include <cstring>

namespace cdocx {

// ============================================================================
// Comment Sync
// ============================================================================

void Document::sync_comments_to_physical() {
    if (comments_cache_.empty()) {
        return;
    }

    auto *comments_xml = get_xml_part("word/comments.xml");
    if (!comments_xml) {
        comments_xml = &create_xml_part("word/comments.xml");
    }

    auto root = comments_xml->child("w:comments");
    if (!root) {
        root = comments_xml->prepend_child("w:comments");
        root.append_attribute("xmlns:w").set_value(
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        root.append_attribute("xmlns:w14")
            .set_value("http://schemas.microsoft.com/office/word/2010/wordml");
        root.append_attribute("xmlns:w15")
            .set_value("http://schemas.microsoft.com/office/word/2012/wordml");
    }

    // Remove existing comment nodes
    for (auto child = root.first_child(); child;) {
        auto next = child.next_sibling();
        if (std::strcmp(child.name(), "w:comment") == 0) {
            root.remove_child(child);
        }
        child = next;
    }

    for (const auto& comment : comments_cache_) {
        auto cxml = root.append_child("w:comment");
        cxml.append_attribute("w:id").set_value(comment->get_id());
        cxml.append_attribute("w:author").set_value(comment->get_author().c_str());
        cxml.append_attribute("w:initials").set_value(comment->get_initial().c_str());

        auto time_val = std::chrono::system_clock::to_time_t(comment->get_date_time());
        cxml.append_attribute("w:date").set_value(time_to_w3cdtf(time_val).c_str());

        // Serialize comment paragraphs
        for (const auto& child : comment->get_children()) {
            if (child->node_type() == NodeType::Paragraph) {
                serialize_paragraph_to_xml(cxml, dynamic_cast<Paragraph*>(child.get()));
            }
        }
    }

    mark_modified("word/comments.xml");
}

void Document::sync_comments_from_physical() {
    auto *comments_xml = get_xml_part("word/comments.xml");
    if (!comments_xml) {
        return;
    }

    comments_cache_.clear();

    auto root = comments_xml->child("w:comments");
    if (!root) {
        return;
    }

    for (auto cxml = root.child("w:comment"); cxml; cxml = cxml.next_sibling("w:comment")) {
        auto comment = std::make_shared<Comment>(this);
        comment->set_id(cxml.attribute("w:id").as_int());
        comment->set_author(cxml.attribute("w:author").value());
        comment->set_initial(cxml.attribute("w:initials").value());

        const char* date_str = cxml.attribute("w:date").value();
        if (date_str && *date_str) {
            auto time = w3cdtf_to_time(date_str);
            comment->set_date_time(std::chrono::system_clock::from_time_t(time));
        }

        for (auto para_node = cxml.child("w:p"); para_node;
             para_node = para_node.next_sibling("w:p")) {
            auto para = parse_paragraph_from_xml(para_node);
            if (para) {
                comment->append_child(para);
            }
        }

        comments_cache_.push_back(comment);
    }

    for (const auto& comment : comments_cache_) {
        if (comment->get_id() >= next_comment_id_) {
            next_comment_id_ = comment->get_id() + 1;
        }
    }
}


}  // namespace cdocx
