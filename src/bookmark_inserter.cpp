/**
 * @file bookmark_inserter.cpp
 * @brief BookmarkInserter implementation
 * @author Claude Code
 * @copyright MIT License
 * @date 2026
 * @version 0.7.0
 */

#include <cdocx/bookmark_inserter.h>

#include <algorithm>
#include <vector>

namespace cdocx {

namespace {

// Collect plain text from all <w:t> children of a <w:r> run.
// Skips nodes that have already been bookmarked by this inserter.
std::string get_run_text(pugi::xml_node run) {
    std::string result;
    for (pugi::xml_node t = run.child("w:t"); t; t = t.next_sibling("w:t")) {
        if (t.attribute("_cdocx_bmk")) {
            continue;
        }
        if (t.text()) {
            result += t.text().get();
        }
    }
    return result;
}

// Copy <w:rPr> from source run to destination run.
void copy_run_properties(pugi::xml_node dst_run, pugi::xml_node src_run) {
    pugi::xml_node rpr = src_run.child("w:rPr");
    if (!rpr) {
        return;
    }
    // Remove any existing rPr in dst.
    pugi::xml_node existing = dst_run.child("w:rPr");
    if (existing) {
        dst_run.remove_child(existing);
    }
    dst_run.prepend_copy(rpr);
}

}  // namespace

BookmarkInserter::BookmarkInserter(Document* doc) : doc_(doc) {
    if (doc_) {
        // Seed next_bookmark_id_ by scanning existing bookmarks.
        pugi::xml_document* xml = doc_->get_document_xml();
        if (xml) {
            int max_id = 0;
            for (const pugi::xpath_node& xn : xml->select_nodes("//w:bookmarkStart")) {
                pugi::xml_node bm = xn.node();
                pugi::xml_attribute id_attr = bm.attribute("w:id");
                if (id_attr) {
                    max_id = std::max(max_id, id_attr.as_int(0));
                }
            }
            next_bookmark_id_ = max_id + 1;
        }
    }
}

int BookmarkInserter::allocate_bookmark_id() {
    return next_bookmark_id_++;
}

bool BookmarkInserter::insert(const std::string& bookmark_name, const std::string& text) {
    if (!doc_ || text.empty()) {
        return false;
    }

    pugi::xml_document* xml = doc_->get_document_xml();
    if (!xml) {
        return false;
    }

    // Search all paragraphs in document.xml body (including inside tables).
    pugi::xml_node body = xml->child("w:document").child("w:body");
    if (!body) {
        return false;
    }

    std::function<bool(pugi::xml_node)> search = [&](pugi::xml_node node) -> bool {
        for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
            std::string tag = child.name();
            if (tag == "w:p") {
                if (insert_in_paragraph(child, bookmark_name, text)) {
                    return true;
                }
            }
            // Recurse into tables, cells, etc.
            if (search(child)) {
                return true;
            }
        }
        return false;
    };

    return search(body);
}

int BookmarkInserter::insert_all(const std::string& bookmark_name, const std::string& text) {
    if (!doc_ || text.empty()) {
        return 0;
    }

    pugi::xml_document* xml = doc_->get_document_xml();
    if (!xml) {
        return 0;
    }

    pugi::xml_node body = xml->child("w:document").child("w:body");
    if (!body) {
        return 0;
    }

    int count = 0;
    bool found = true;
    while (found) {
        found = false;
        std::function<bool(pugi::xml_node)> search = [&](pugi::xml_node node) -> bool {
            for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
                if (std::string(child.name()) == "w:p") {
                    if (insert_in_paragraph(child, bookmark_name, text)) {
                        found = true;
                        ++count;
                        return true;  // Restart search from top after each insertion
                    }
                }
                if (search(child)) {
                    return true;
                }
            }
            return false;
        };
        search(body);
    }
    return count;
}

int BookmarkInserter::insert_batch(const std::map<std::string, std::string>& mappings) {
    // Sort by text length descending so longer strings are bookmarked before
    // shorter substrings. This prevents a short value like "YK52+320" from
    // being hidden by the internal _cdocx_bmk marker of a longer value like
    // "YK52+320~YK52+470".
    std::vector<std::pair<std::string, std::string>> sorted(mappings.begin(), mappings.end());
    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        return a.second.size() > b.second.size();
    });

    int success = 0;
    for (const auto& pair : sorted) {
        if (insert(pair.first, pair.second)) {
            ++success;
        }
    }
    return success;
}

bool BookmarkInserter::insert_in_paragraph(pugi::xml_node paragraph,
                                           const std::string& bookmark_name,
                                           const std::string& text) {
    // Gather all <w:r> runs and their concatenated text.
    struct RunInfo {
        pugi::xml_node run;
        std::string text;
    };

    std::vector<RunInfo> runs;
    std::string paragraph_text;
    for (pugi::xml_node run = paragraph.child("w:r"); run; run = run.next_sibling("w:r")) {
        std::string t = get_run_text(run);
        runs.push_back({run, t});
        paragraph_text += t;
    }

    std::size_t pos = paragraph_text.find(text);
    if (pos == std::string::npos) {
        return false;
    }

    std::size_t end_pos = pos + text.length();

    // Determine which runs cover [pos, end_pos).
    std::size_t current_pos = 0;
    std::size_t start_run_idx = runs.size();
    std::size_t end_run_idx = runs.size();

    for (std::size_t i = 0; i < runs.size(); ++i) {
        std::size_t run_start = current_pos;
        std::size_t run_end = current_pos + runs[i].text.length();

        if (run_start <= pos && pos < run_end) {
            start_run_idx = i;
        }
        if (run_start < end_pos && end_pos <= run_end) {
            end_run_idx = i;
            break;
        }
        current_pos = run_end;
    }

    if (start_run_idx >= runs.size() || end_run_idx >= runs.size()) {
        return false;
    }

    // We now know the text spans runs [start_run_idx, end_run_idx].
    // We may need to split the first and/or last run if the match does not
    // consume the entire run text.

    std::size_t current = 0;
    for (std::size_t i = 0; i < start_run_idx; ++i) {
        current += runs[i].text.length();
    }
    std::size_t match_start_in_first = pos - current;
    std::size_t match_end_in_last = 0;
    {
        std::size_t tmp = current;
        for (std::size_t i = start_run_idx; i <= end_run_idx; ++i) {
            tmp += runs[i].text.length();
        }
        match_end_in_last = runs[end_run_idx].text.length() - (tmp - end_pos);
    }

    pugi::xml_node first_marked_run;
    pugi::xml_node last_marked_run;

    auto clear_run_text_nodes = [](pugi::xml_node run) {
        pugi::xml_node t = run.child("w:t");
        while (t) {
            pugi::xml_node next = t.next_sibling("w:t");
            run.remove_child(t);
            t = next;
        }
    };

    if (start_run_idx == end_run_idx) {
        // Match is entirely within a single run.
        pugi::xml_node original_run = runs[start_run_idx].run;
        if (match_start_in_first > 0) {
            pugi::xml_node prefix_run = paragraph.insert_child_before("w:r", original_run);
            copy_run_properties(prefix_run, original_run);
            prefix_run.append_child("w:t").text().set(
                runs[start_run_idx].text.substr(0, match_start_in_first).c_str());
        }
        if (match_end_in_last < runs[start_run_idx].text.length()) {
            pugi::xml_node suffix_run = paragraph.insert_child_after("w:r", original_run);
            copy_run_properties(suffix_run, original_run);
            suffix_run.append_child("w:t").text().set(
                runs[start_run_idx].text.substr(match_end_in_last).c_str());
        }
        clear_run_text_nodes(original_run);
        pugi::xml_node t_node = original_run.append_child("w:t");
        t_node.text().set(
            runs[start_run_idx].text.substr(match_start_in_first, text.length()).c_str());
        t_node.append_attribute("_cdocx_bmk").set_value("1");
        first_marked_run = original_run;
        last_marked_run = original_run;
    } else {
        // Match spans multiple runs: preserve all original runs and their
        // formatting. Only split the first and/or last run if necessary.
        pugi::xml_node start_run = runs[start_run_idx].run;
        if (match_start_in_first > 0) {
            pugi::xml_node prefix_run = paragraph.insert_child_before("w:r", start_run);
            copy_run_properties(prefix_run, start_run);
            prefix_run.append_child("w:t").text().set(
                runs[start_run_idx].text.substr(0, match_start_in_first).c_str());
            clear_run_text_nodes(start_run);
            pugi::xml_node t_node = start_run.append_child("w:t");
            t_node.text().set(runs[start_run_idx].text.substr(match_start_in_first).c_str());
            t_node.append_attribute("_cdocx_bmk").set_value("1");
        } else {
            // Entire start run is consumed by the match: mark its text nodes.
            for (pugi::xml_node t = start_run.child("w:t"); t; t = t.next_sibling("w:t")) {
                t.append_attribute("_cdocx_bmk").set_value("1");
            }
        }
        first_marked_run = start_run;

        pugi::xml_node end_run = runs[end_run_idx].run;
        if (match_end_in_last < runs[end_run_idx].text.length()) {
            pugi::xml_node suffix_run = paragraph.insert_child_after("w:r", end_run);
            copy_run_properties(suffix_run, end_run);
            suffix_run.append_child("w:t").text().set(
                runs[end_run_idx].text.substr(match_end_in_last).c_str());
            clear_run_text_nodes(end_run);
            pugi::xml_node t_node = end_run.append_child("w:t");
            t_node.text().set(runs[end_run_idx].text.substr(0, match_end_in_last).c_str());
            t_node.append_attribute("_cdocx_bmk").set_value("1");
        } else {
            // Entire end run is consumed by the match: mark its text nodes.
            for (pugi::xml_node t = end_run.child("w:t"); t; t = t.next_sibling("w:t")) {
                t.append_attribute("_cdocx_bmk").set_value("1");
            }
        }
        last_marked_run = end_run;

        // Mark intermediate runs so they are skipped by future scans.
        for (std::size_t i = start_run_idx + 1; i < end_run_idx; ++i) {
            for (pugi::xml_node t = runs[i].run.child("w:t"); t; t = t.next_sibling("w:t")) {
                t.append_attribute("_cdocx_bmk").set_value("1");
            }
        }
    }

    int bm_id = allocate_bookmark_id();

    pugi::xml_node bm_start = paragraph.insert_child_before("w:bookmarkStart", first_marked_run);
    bm_start.append_attribute("w:id").set_value(bm_id);
    bm_start.append_attribute("w:name").set_value(bookmark_name.c_str());

    pugi::xml_node bm_end = paragraph.insert_child_after("w:bookmarkEnd", last_marked_run);
    bm_end.append_attribute("w:id").set_value(bm_id);

    return true;
}

}  // namespace cdocx
