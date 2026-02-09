/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * CDocx is a free library to work with docx files.
 */

#pragma once

#include <cstdio>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

#include "constants.h"
#include "cdocxIterator.h"

// Include third-party headers
#include <pugixml.hpp>
#include <zip.h>

// Forward declarations
struct zip_t;

namespace cdocx {

// Forward declarations
class Document;

// Run contains runs in a paragraph
class Run {
  private:
    friend class IteratorHelper;
    // Store the parent node (a paragraph)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;

  public:
    Run();
    Run(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);
    pugi::xml_node get_current() const;
    pugi::xml_node get_parent() const;
    std::string get_text() const;
    bool set_text(const std::string &) const;
    bool set_text(const char *) const;

    Run &next();
    bool has_next() const;
};

// Paragraph contains a paragraph
// and stores runs
class Paragraph {
  private:
    friend class IteratorHelper;
    // Store parent node (usually the body node)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;
    // A paragraph consists of runs
    Run run;

  public:
    Paragraph();
    Paragraph(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Paragraph &next();
    bool has_next() const;

    Run &runs();
    Run &add_run(const std::string &, cdocx::formatting_flag = cdocx::none);
    Run &add_run(const char *, cdocx::formatting_flag = cdocx::none);
    void remove_run(const Run &);
    Paragraph &insert_paragraph_after(const std::string &,
                                      cdocx::formatting_flag = cdocx::none);
};

// TableCell contains one or more paragraphs
class TableCell {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    Paragraph paragraph;

  public:
    TableCell();
    TableCell(pugi::xml_node, pugi::xml_node);

    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Paragraph &paragraphs();

    TableCell &next();
    bool has_next() const;
};

// TableRow consists of one or more TableCells
class TableRow {
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableCell cell;

  public:
    TableRow();
    TableRow(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    TableCell &cells();

    bool has_next() const;
    TableRow &next();
};

// Table consists of one or more TableRow objects
class Table {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableRow row;

  public:
    Table();
    Table(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Table &next();
    bool has_next() const;

    TableRow &rows();
};

// Document contains whole the docx file
// and stores paragraphs
class Document {
  private:
    friend class IteratorHelper;
    std::string directory;
    Paragraph paragraph;
    Table table;
    pugi::xml_document document;
    bool flag_is_open;
    zip_t *zipfile;

  public:
    Document();
    Document(std::string);
    ~Document();
    
    void file(std::string);
    void open();
    void save();
    void save(const std::string&);
    bool is_open() const;

    Paragraph &paragraphs();
    Table &tables();
};

// Template class for replacing placeholder strings in docx documents
class Template {
  private:
    Document *doc;
    std::map<std::string, std::string> placeholders;
    std::string pattern_prefix = "{{";
    std::string pattern_suffix = "}}";

    // FSM-based placeholder context
    struct PlaceholderContext {
        Run* first_run = nullptr;
        std::vector<Run*> runs_to_delete;
        std::string collected_text;
        size_t prefix_pos = 0;
        void clear();
    };

    bool replace_in_string(std::string &text) const;
    void replace_in_paragraphs();
    void replace_in_tables();
    
    // Helper functions for FSM-based replacement
    bool try_replace_single_run(Run& r);
    void transition_to_collecting_state(PlaceholderContext& ctx, Run& r, const std::string& text, size_t prefix_pos);
    bool try_replace_placeholder(const PlaceholderContext& ctx, Paragraph& p);
    void delete_collected_runs(const PlaceholderContext& ctx, Paragraph& p);
    void process_paragraph(Paragraph& p);

  public:
    Template(Document *document);
    Template(Document *document, const std::string &prefix, const std::string &suffix);

    // Set placeholder value
    void set(const std::string &key, const std::string &value);
    void set(const std::string &key, const char *value);

    // Set custom pattern (default is "{{" and "}}")
    void set_pattern(const std::string &prefix, const std::string &suffix);

    // Replace all placeholders in the document
    void replace_all();

    // Clear all placeholder values
    void clear();

    // Get number of placeholders
    size_t size() const;
};

} // namespace cdocx
