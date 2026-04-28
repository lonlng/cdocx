/**
 * @file range.cpp
 * @brief Range and TableOperations implementation
 * @since 0.3.0
 */

#include <cdocx/advanced.h>
#include <cdocx/range.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>
#include <cdocx/table.h>

#include <string>
#include <vector>

namespace cdocx {

namespace {

std::string collect_text_from_runs(pugi::xml_node para) {
    std::string result;
    for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
        const pugi::xml_node t = run.child("w:t");
        if (t) {
            result += t.text().get();
        }
    }
    return result;
}

}  // namespace

// Range Implementation
// ============================================================================

Range::Range() = default;

Range::Range(Document* doc, pugi::xml_node start, pugi::xml_node end)
    : doc_(doc), start_para_(start), end_para_(end) {
}

std::string Range::get_text() const {
    std::string result;

    pugi::xml_node current = start_para_;
    while (current) {
        result += collect_text_from_runs(current);
        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }

    return result;
}

bool Range::replace(const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return false;
    }

    // Fallback for DOM paragraphs without XML node binding
    if (!is_valid() && doc_) {
        auto paragraphs = doc_->get_paragraphs();
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

    pugi::xml_node current = start_para_;
    while (current) {
        std::string para_text = collect_text_from_runs(current);

        const size_t pos = para_text.find(old_text);
        if (pos != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);

            // Clear all runs and set first run to new text
            pugi::xml_node first_run;
            pugi::xml_node run = current.child("w:r");
            while (run) {
                const pugi::xml_node next = run.next_sibling("w:r");
                if (!first_run) {
                    first_run = run;
                    // Clear existing text nodes
                    for (pugi::xml_node t = run.child("w:t"); t; t = t.next_sibling("w:t")) {
                        run.remove_child(t);
                    }
                    pugi::xml_node new_t = run.append_child("w:t");
                    if (!para_text.empty() &&
                        (std::isspace(static_cast<unsigned char>(para_text.front())) ||
                         std::isspace(static_cast<unsigned char>(para_text.back())))) {
                        new_t.append_attribute("xml:space").set_value("preserve");
                    }
                    new_t.text().set(para_text.c_str());
                } else {
                    current.remove_child(run);
                }
                run = next;
            }

            // If no run existed, create one
            if (!first_run) {
                pugi::xml_node new_run = current.append_child("w:r");
                pugi::xml_node new_t = new_run.append_child("w:t");
                if (!para_text.empty() &&
                    (std::isspace(static_cast<unsigned char>(para_text.front())) ||
                     std::isspace(static_cast<unsigned char>(para_text.back())))) {
                    new_t.append_attribute("xml:space").set_value("preserve");
                }
                new_t.text().set(para_text.c_str());
            }

            return true;
        }

        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    return false;
}

int Range::replace_all(const std::string& old_text, const std::string& new_text) {
    if (old_text.empty()) {
        return 0;
    }

    // Fallback for DOM paragraphs without XML node binding
    if (!is_valid() && doc_) {
        int total = 0;
        auto paragraphs = doc_->get_paragraphs();
        for (auto& para : paragraphs) {
            if (!para) {
                continue;
            }
            std::string para_text = para->get_text();
            int count = 0;
            size_t pos = 0;
            while ((pos = para_text.find(old_text, pos)) != std::string::npos) {
                para_text.replace(pos, old_text.size(), new_text);
                pos += new_text.size();
                ++count;
            }
            if (count > 0) {
                para->set_text(para_text);
                total += count;
            }
        }
        return total;
    }

    int total = 0;
    pugi::xml_node current = start_para_;
    while (current) {
        std::string para_text = collect_text_from_runs(current);

        int count = 0;
        size_t pos = 0;
        while ((pos = para_text.find(old_text, pos)) != std::string::npos) {
            para_text.replace(pos, old_text.size(), new_text);
            pos += new_text.size();
            ++count;
        }

        if (count > 0) {
            ++total;
            // Clear all runs and set first run to new text
            pugi::xml_node first_run;
            pugi::xml_node run = current.child("w:r");
            while (run) {
                const pugi::xml_node next = run.next_sibling("w:r");
                if (!first_run) {
                    first_run = run;
                    for (pugi::xml_node t = run.child("w:t"); t; t = t.next_sibling("w:t")) {
                        run.remove_child(t);
                    }
                    pugi::xml_node new_t = run.append_child("w:t");
                    if (!para_text.empty() &&
                        (std::isspace(static_cast<unsigned char>(para_text.front())) ||
                         std::isspace(static_cast<unsigned char>(para_text.back())))) {
                        new_t.append_attribute("xml:space").set_value("preserve");
                    }
                    new_t.text().set(para_text.c_str());
                } else {
                    current.remove_child(run);
                }
                run = next;
            }

            if (!first_run) {
                pugi::xml_node new_run = current.append_child("w:r");
                pugi::xml_node new_t = new_run.append_child("w:t");
                if (!para_text.empty() &&
                    (std::isspace(static_cast<unsigned char>(para_text.front())) ||
                     std::isspace(static_cast<unsigned char>(para_text.back())))) {
                    new_t.append_attribute("xml:space").set_value("preserve");
                }
                new_t.text().set(para_text.c_str());
            }
        }

        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    return total;
}

bool Range::delete_content() {
    if (!is_valid()) {
        return false;
    }

    pugi::xml_node current = start_para_;
    while (current) {
        // Remove all run elements
        pugi::xml_node run = current.child("w:r");
        while (run) {
            const pugi::xml_node next = run.next_sibling("w:r");
            current.remove_child(run);
            run = next;
        }

        if (current == end_para_) {
            break;
        }
        current = current.next_sibling();
    }
    return true;
}

bool Range::is_valid() const {
    return start_para_ && end_para_;
}

void Range::collapse(bool to_start) {
    if (to_start) {
        end_para_ = start_para_;
    } else {
        start_para_ = end_para_;
    }
}

// ============================================================================
// TableOperations Implementation
// ============================================================================

bool TableOperations::insert_row(Table& table, size_t index) {
    return table.insert_row(static_cast<int>(index)) != nullptr;
}

bool TableOperations::append_row(Table& table) {
    return table.append_row() != nullptr;
}

bool TableOperations::delete_row(Table& table, size_t index) {
    table.remove_row(static_cast<int>(index));
    return true;
}

bool TableOperations::insert_cell(Row& row, size_t index) {
    return row.insert_cell(static_cast<int>(index)) != nullptr;
}

bool TableOperations::delete_cell(Row& row, size_t index) {
    auto cell = row.get_cell(static_cast<int>(index));
    if (cell) {
        row.remove_child(cell);
        return true;
    }
    return false;
}

size_t TableOperations::get_row_count(const Table& table) {
    return static_cast<size_t>(table.get_row_count());
}

size_t TableOperations::get_column_count(const Table& table) {
    return static_cast<size_t>(table.get_column_count());
}

bool TableOperations::merge_cells_horizontal(Row& row, size_t start, size_t end) {
    auto table = row.get_parent_table();
    if (!table) {
        return false;
    }
    const int row_index = row.get_row_index();
    if (row_index < 0) {
        return false;
    }
    auto result =
        table->merge_cells(row_index, static_cast<int>(start), row_index, static_cast<int>(end));
    return result != nullptr;
}

bool TableOperations::set_cell_text(Cell& cell, const std::string& text) {
    cell.set_text(text);
    return true;
}

std::string TableOperations::get_cell_text(const Cell& cell) {
    return cell.get_text();
}

// ============================================================================

}  // namespace cdocx
