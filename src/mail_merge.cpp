/**
 * @file mail_merge.cpp
 * @brief Mail merge implementation for CDocx
 * @since 0.7.0
 */

#include <cdocx/mail_merge.h>
#include <cdocx/node.h>
#include <cdocx/paragraph.h>
#include <iostream>  // DEBUG

#include <algorithm>
#include <cctype>
#include <sstream>

namespace cdocx {

namespace {

// Trim leading and trailing whitespace
std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }
    return s.substr(start, end - start);
}

// Case-insensitive string comparison
bool iequals(const std::string& a, const std::string& b) {
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(a[i])) !=
            std::tolower(static_cast<unsigned char>(b[i]))) {
            return false;
        }
    }
    return true;
}

// Extract merge field name from field code like "MERGEFIELD Name \\* MERGEFORMAT"
std::string parse_merge_field_name(const std::string& field_code) {
    std::string code = trim(field_code);
    std::istringstream iss(code);
    std::string keyword;
    if (!(iss >> keyword))
        return "";

    // Check keyword (case-insensitive)
    std::string kw_lower;
    for (char c : keyword) {
        kw_lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    if (kw_lower != "mergefield")
        return "";

    // The rest is the field name and optional switches
    std::string rest;
    std::getline(iss, rest);
    rest = trim(rest);

    // Remove switches (anything starting with \\)
    size_t switch_pos = rest.find("\\\\");
    if (switch_pos != std::string::npos) {
        rest = trim(rest.substr(0, switch_pos));
    }

    return rest;
}

// Check if a paragraph contains only whitespace/empty runs
bool is_empty_paragraph(const Paragraph* para) {
    if (!para)
        return true;
    for (const auto& child : para->get_children()) {
        if (child->node_type() == NodeType::Run) {
            auto* run = dynamic_cast<Run*>(child.get());
            if (run && !trim(run->get_text()).empty()) {
                return false;
            }
        } else if (child->node_type() != NodeType::FieldStart &&
                   child->node_type() != NodeType::BookmarkStart &&
                   child->node_type() != NodeType::BookmarkEnd &&
                   child->node_type() != NodeType::CommentRangeStart &&
                   child->node_type() != NodeType::CommentRangeEnd &&
                   child->node_type() != NodeType::FootnoteReference &&
                   child->node_type() != NodeType::EndnoteReference) {
            return false;
        }
    }
    return true;
}

}  // anonymous namespace

// ============================================================================
// MailMerge Implementation
// ============================================================================

MailMerge::MailMerge(Document* doc) : doc_(doc) {
}

void MailMerge::execute(const std::map<std::string, std::string>& data) {
    execute_impl(data);
}

void MailMerge::execute(const std::vector<std::pair<std::string, std::string>>& data) {
    std::map<std::string, std::string> map_data;
    for (const auto& p : data) {
        map_data[p.first] = p.second;
    }
    execute_impl(map_data);
}

void MailMerge::execute_impl(const std::map<std::string, std::string>& data) {
    if (!doc_)
        return;

    // Round-trip sync to unify DOM and physical XML state.
    // This ensures MERGEFIELDs created via DOM or DocumentBuilder are visible.
    doc_->sync_to_physical_tree();
    doc_->sync_from_physical_tree();

    bool removed_any_field = false;

    auto sections = doc_->get_sections();
    for (auto& section : sections) {
        if (auto body = section->get_body()) {
            for (const auto& child : body->get_children()) {
                if (child->node_type() != NodeType::Paragraph)
                    continue;
                auto* para = dynamic_cast<Paragraph*>(child.get());
                if (!para)
                    continue;

                auto children = para->get_children();
                for (size_t i = 0; i < children.size(); ++i) {
                    auto& node = children[i];
                    if (node->node_type() != NodeType::FieldStart)
                        continue;
                    auto* field = dynamic_cast<Field*>(node.get());
                    if (!field)
                        continue;

                    std::string field_name = parse_merge_field_name(field->get_field_code());
                    if (field_name.empty())
                        continue;

                    removed_any_field = true;

                    auto it = std::find_if(data.begin(), data.end(), [&field_name](const auto& kv) {
                        return iequals(kv.first, field_name);
                    });

                    if (it != data.end()) {
                        // Replace field with a Run containing the value
                        auto run = std::make_shared<Run>(doc_, it->second);
                        para->insert_child(static_cast<int>(i), run);
                        para->remove_child(node);
                    } else {
                        // No value found: remove field entirely
                        para->remove_child(node);
                    }
                }
            }
        }
    }

    if (removed_any_field) {
        apply_cleanup();
        doc_->sync_to_physical_tree();
    }
}

std::vector<std::string> MailMerge::get_field_names() const {
    auto names = collect_field_names();
    // Sort and deduplicate
    std::sort(names.begin(), names.end());
    names.erase(std::unique(names.begin(), names.end()), names.end());
    return names;
}

std::vector<std::string> MailMerge::collect_field_names() const {
    std::vector<std::string> result;
    if (!doc_)
        return result;

    // Round-trip sync to unify DOM and physical XML state.
    doc_->sync_to_physical_tree();
    doc_->sync_from_physical_tree();

    auto sections = doc_->get_sections();
    for (auto& section : sections) {
        if (auto body = section->get_body()) {
            for (const auto& child : body->get_children()) {
                if (child->node_type() != NodeType::Paragraph)
                    continue;
                auto* para = dynamic_cast<Paragraph*>(child.get());
                if (!para)
                    continue;

                for (const auto& node : para->get_children()) {
                    if (node->node_type() != NodeType::FieldStart)
                        continue;
                    auto* field = dynamic_cast<Field*>(node.get());
                    if (!field)
                        continue;

                    std::string name = parse_merge_field_name(field->get_field_code());
                    if (!name.empty()) {
                        result.push_back(name);
                    }
                }
            }
        }
    }
    return result;
}

void MailMerge::delete_fields() {
    if (!doc_)
        return;

    // Round-trip sync to unify DOM and physical XML state.
    doc_->sync_to_physical_tree();
    doc_->sync_from_physical_tree();

    bool removed_any = false;
    auto sections = doc_->get_sections();
    for (auto& section : sections) {
        if (auto body = section->get_body()) {
            for (const auto& child : body->get_children()) {
                if (child->node_type() != NodeType::Paragraph)
                    continue;
                auto* para = dynamic_cast<Paragraph*>(child.get());
                if (!para)
                    continue;

                auto children = para->get_children();
                for (auto& node : children) {
                    if (node->node_type() != NodeType::FieldStart)
                        continue;
                    auto* field = dynamic_cast<Field*>(node.get());
                    if (!field)
                        continue;

                    std::string name = parse_merge_field_name(field->get_field_code());
                    if (!name.empty()) {
                        para->remove_child(node);
                        removed_any = true;
                    }
                }
            }
        }
    }

    if (removed_any) {
        apply_cleanup();
        doc_->sync_to_physical_tree();
    }
}

void MailMerge::apply_cleanup() {
    if (static_cast<std::uint8_t>(cleanup_options_ &
                                  MailMergeCleanupOptions::RemoveEmptyParagraphs) == 0) {
        return;
    }

    auto sections = doc_->get_sections();
    for (auto& section : sections) {
        if (auto body = section->get_body()) {
            auto children = body->get_children();
            for (auto& child : children) {
                if (child->node_type() != NodeType::Paragraph)
                    continue;
                auto* para = dynamic_cast<Paragraph*>(child.get());
                if (para && is_empty_paragraph(para)) {
                    body->remove_child(child);
                }
            }
        }
    }
}

}  // namespace cdocx
