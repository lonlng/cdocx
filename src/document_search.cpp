/**
 * @file document_search.cpp
 * @brief DocumentSearch implementation
 * @since 0.3.0
 */

#include <cdocx/document_search.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>

#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace cdocx {

// DocumentSearch Implementation
// ============================================================================

static int count_occurrences(const std::string& text, const std::string& pattern) {
    if (pattern.empty() || text.empty() || pattern.size() > text.size()) {
        return 0;
    }
    int count = 0;
    size_t pos = 0;
    while ((pos = text.find(pattern, pos)) != std::string::npos) {
        ++count;
        pos += pattern.size();
    }
    return count;
}

static std::string replace_all_in_string(std::string text,
                                      const std::string& old_text,
                                      const std::string& new_text) {
    if (old_text.empty()) {
        return text;
    }
    size_t pos = 0;
    while ((pos = text.find(old_text, pos)) != std::string::npos) {
        text.replace(pos, old_text.size(), new_text);
        pos += new_text.size();
    }
    return text;
}

std::optional<Range> DocumentSearch::find(Document& doc, const std::string& text) {
    if (text.empty()) {
        return std::nullopt;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) {
            continue;
        }
        const std::string para_text = para->get_text();
        if (para_text.find(text) != std::string::npos) {
            return Range(&doc, para->get_current_node(), para->get_current_node());
        }
    }
    return std::nullopt;
}

std::vector<Range> DocumentSearch::find_all(Document& doc, const std::string& text) {
    std::vector<Range> results;
    if (text.empty()) {
        return results;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) {
            continue;
        }
        const std::string para_text = para->get_text();
        if (para_text.find(text) != std::string::npos) {
            results.emplace_back(&doc, para->get_current_node(), para->get_current_node());
        }
    }
    return results;
}

bool DocumentSearch::replace(Document& doc,
                             const std::string& old_text,
                             const std::string& new_text) {
    if (old_text.empty()) {
        return false;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) {
            continue;
        }
        std::string para_text = para->get_text();
        const size_t pos = para_text.find(old_text);
        if (pos != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);
            para->set_text(para_text);
            return true;
        }
    }
    return false;
}

int DocumentSearch::replace_all(Document& doc,
                                const std::string& old_text,
                                const std::string& new_text) {
    if (old_text.empty()) {
        return 0;
    }

    int total = 0;
    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) {
            continue;
        }
        const std::string para_text = para->get_text();
        const int count = count_occurrences(para_text, old_text);
        if (count > 0) {
            para->set_text(replace_all_in_string(para_text, old_text, new_text));
            total += count;
        }
    }
    return total;
}

bool DocumentSearch::replace_with_formatting(Document& doc,
                                             const std::string& old_text,
                                             const std::string& new_text,
                                             FormattingFlag flag) {
    if (old_text.empty()) {
        return false;
    }

    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) {
            continue;
        }
        std::string para_text = para->get_text();
        const size_t pos = para_text.find(old_text);
        if (pos != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);
            para->set_text(para_text);
            if (auto run = para->get_first_run()) {
                if (flag & kBold) {
                    run->set_bold(true);
                }
                if (flag & kItalic) {
                    run->set_italic(true);
                }
                if (flag & kUnderline) {
                    run->set_underline(UnderlineType::Single);
                }
            }
            return true;
        }
    }
    return false;
}

int DocumentSearch::find_and_process(Document& doc,
                                     const std::string& pattern,
                                     const SearchCallback& callback) {
    if (pattern.empty() || !callback) {
        return 0;
    }

    int count = 0;
    auto paragraphs = doc.get_paragraphs();
    for (auto& para : paragraphs) {
        if (!para) {
            continue;
        }
        const std::string para_text = para->get_text();
        if (para_text.find(pattern) != std::string::npos) {
            Range range(&doc, para->get_current_node(), para->get_current_node());
            ++count;
            if (!callback(para_text, range)) {
                break;
            }
        }
    }
    return count;
}

// ============================================================================

}  // namespace cdocx
