#include "cdocx.h"

#include <cctype>
#include <filesystem>

// Hack on pugixml
// We need to write xml to std string (or char *)
// So overload the write function
struct xml_string_writer : pugi::xml_writer {
    std::string result;

    virtual void write(const void *data, size_t size) {
        result.append(static_cast<const char *>(data), size);
    }
};

cdocx::Run::Run() {}

cdocx::Run::Run(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void cdocx::Run::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:r");
}

void cdocx::Run::set_current(pugi::xml_node node) { this->current = node; }

pugi::xml_node cdocx::Run::get_current() const {
    return this->current;
}

pugi::xml_node cdocx::Run::get_parent() const
{
    return this->parent;
}

std::string cdocx::Run::get_text() const {
    return this->current.child("w:t").text().get();
}

bool cdocx::Run::set_text(const std::string &text) const {
    return this->current.child("w:t").text().set(text.c_str());
}

bool cdocx::Run::set_text(const char *text) const {
    return this->current.child("w:t").text().set(text);
}

cdocx::Run &cdocx::Run::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool cdocx::Run::has_next() const { return this->current != 0; }

// Table cells
cdocx::TableCell::TableCell() {}

cdocx::TableCell::TableCell(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void cdocx::TableCell::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tc");

    this->paragraph.set_parent(this->current);
}

void cdocx::TableCell::set_current(pugi::xml_node node) {
    this->current = node;
}

bool cdocx::TableCell::has_next() const { return this->current != 0; }

cdocx::TableCell &cdocx::TableCell::next() {
    this->current = this->current.next_sibling();
    return *this;
}

cdocx::Paragraph &cdocx::TableCell::paragraphs() {
    this->paragraph.set_parent(this->current);
    return this->paragraph;
}

// Table rows
cdocx::TableRow::TableRow() {}

cdocx::TableRow::TableRow(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void cdocx::TableRow::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tr");

    this->cell.set_parent(this->current);
}

void cdocx::TableRow::set_current(pugi::xml_node node) { this->current = node; }

cdocx::TableRow &cdocx::TableRow::next() {
    this->current = this->current.next_sibling();
    return *this;
}

cdocx::TableCell &cdocx::TableRow::cells() {
    this->cell.set_parent(this->current);
    return this->cell;
}

bool cdocx::TableRow::has_next() const { return this->current != 0; }

// Tables
cdocx::Table::Table() {}

cdocx::Table::Table(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void cdocx::Table::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tbl");

    this->row.set_parent(this->current);
}

bool cdocx::Table::has_next() const { return this->current != 0; }

cdocx::Table &cdocx::Table::next() {
    this->current = this->current.next_sibling();
    this->row.set_parent(this->current);
    return *this;
}

void cdocx::Table::set_current(pugi::xml_node node) { this->current = node; }

cdocx::TableRow &cdocx::Table::rows() {
    this->row.set_parent(this->current);
    return this->row;
}

cdocx::Paragraph::Paragraph() {}

cdocx::Paragraph::Paragraph(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void cdocx::Paragraph::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:p");

    this->run.set_parent(this->current);
}

void cdocx::Paragraph::set_current(pugi::xml_node node) {
    this->current = node;
}

cdocx::Paragraph &cdocx::Paragraph::next() {
    this->current = this->current.next_sibling();
    this->run.set_parent(this->current);
    return *this;
}

bool cdocx::Paragraph::has_next() const { return this->current != 0; }

cdocx::Run &cdocx::Paragraph::runs() {
    this->run.set_parent(this->current);
    return this->run;
}

cdocx::Run &cdocx::Paragraph::add_run(const std::string &text,
                                      cdocx::formatting_flag f) {
    return this->add_run(text.c_str(), f);
}

cdocx::Run &cdocx::Paragraph::add_run(const char *text,
                                      cdocx::formatting_flag f) {
    // Add new run
    pugi::xml_node new_run = this->current.append_child("w:r");
    // Insert meta to new run
    pugi::xml_node meta = new_run.append_child("w:rPr");

    if (f & cdocx::bold)
        meta.append_child("w:b");

    if (f & cdocx::italic)
        meta.append_child("w:i");

    if (f & cdocx::underline)
        meta.append_child("w:u").append_attribute("w:val").set_value("single");

    if (f & cdocx::strikethrough)
        meta.append_child("w:strike")
            .append_attribute("w:val")
            .set_value("true");

    if (f & cdocx::superscript)
        meta.append_child("w:vertAlign")
            .append_attribute("w:val")
            .set_value("superscript");
    else if (f & cdocx::subscript)
        meta.append_child("w:vertAlign")
            .append_attribute("w:val")
            .set_value("subscript");

    if (f & cdocx::smallcaps)
        meta.append_child("w:smallCaps")
            .append_attribute("w:val")
            .set_value("true");

    if (f & cdocx::shadow)
        meta.append_child("w:shadow")
            .append_attribute("w:val")
            .set_value("true");

    pugi::xml_node new_run_text = new_run.append_child("w:t");
    // If the run starts or ends with whitespace characters, preserve them using
    // the xml:space attribute
    if (*text != 0 && (isspace(text[0]) || isspace(text[strlen(text) - 1])))
        new_run_text.append_attribute("xml:space").set_value("preserve");
    new_run_text.text().set(text);

    this->run.set_current(new_run);
    return this->run;
}

void cdocx::Paragraph::remove_run(const Run &r) 
{
    this->current.remove_child(r.get_current());
}

cdocx::Paragraph &
cdocx::Paragraph::insert_paragraph_after(const std::string &text,
                                         cdocx::formatting_flag f) {
    pugi::xml_node new_para =
        this->parent.insert_child_after("w:p", this->current);

    Paragraph *p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);

    return *p;
}

cdocx::Document::Document() {
    // TODO: this function must be removed!
    this->directory = "";
    this->flag_is_open = false;
    this->zipfile = nullptr;
}

cdocx::Document::Document(std::string directory) {
    this->directory = directory;
    this->flag_is_open = false;
    this->zipfile = nullptr;
}

void cdocx::Document::file(std::string directory) {
    this->directory = directory;
}

void cdocx::Document::open() {
    void *buf = NULL;
    size_t bufsize;

    // Open file and load "xml" content to the document variable
    zip_t *zip =
        zip_open(this->directory.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    if (!zip) {
        this->flag_is_open = false;
        return;
    }
    this->flag_is_open = true;

    if (zip_entry_open(zip, "word/document.xml") != 0) {
        zip_close(zip);
        this->flag_is_open = false;
        return;
    }

    zip_entry_read(zip, &buf, &bufsize);

    zip_entry_close(zip);
    zip_close(zip);

    if (!buf || bufsize == 0) {
        this->flag_is_open = false;
        return;
    }

    this->document.load_buffer(buf, bufsize);

    free(buf);

    // Check if the document was loaded properly
    pugi::xml_node doc_node = document.child("w:document");
    if (!doc_node) {
        this->flag_is_open = false;
        return;
    }

    pugi::xml_node body_node = doc_node.child("w:body");
    if (!body_node) {
        this->flag_is_open = false;
        return;
    }

    this->paragraph.set_parent(body_node);
}

void cdocx::Document::save() {
    save(this->directory);
    return;
    // minizip only supports appending or writing to new files
    // so we must
    // - make a new file
    // - write any new files
    // - copy the old files
    // - delete old docx
    // - rename new file to old file
    
    if(!this->is_open()) {
        // if file is not existing, save() will make no sense
        return;
    }

    // Read document buffer
    xml_string_writer writer;
    this->document.print(writer);

    // Open file and replace "xml" content

    std::string original_file = this->directory;
    std::string temp_file = this->directory + ".tmp";

    // Create the new file
    zip_t *new_zip =
        zip_open(temp_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    // Write out document.xml
    zip_entry_open(new_zip, "word/document.xml");

    const char *buf = writer.result.c_str();

    zip_entry_write(new_zip, buf, strlen(buf));
    zip_entry_close(new_zip);

    // Open the original zip and copy all files which are not replaced by CDocx
    zip_t *orig_zip =
        zip_open(original_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    // Loop & copy each relevant entry in the original zip
    int orig_zip_entry_ct = zip_total_entries(orig_zip);
    for (int i = 0; i < orig_zip_entry_ct; i++) {
        zip_entry_openbyindex(orig_zip, i);
        const char *name = zip_entry_name(orig_zip);

        // Skip copying the original file
        if (std::string(name) != std::string("word/document.xml")) {
            // Read the old content
            void *entry_buf;
            size_t entry_buf_size;
            zip_entry_read(orig_zip, &entry_buf, &entry_buf_size);

            // Write into new zip
            zip_entry_open(new_zip, name);
            zip_entry_write(new_zip, entry_buf, entry_buf_size);
            zip_entry_close(new_zip);

            free(entry_buf);
        }

        zip_entry_close(orig_zip);
    }

    // Close both zips
    zip_close(orig_zip);
    zip_close(new_zip);

    // Remove original zip, rename new to correct name
    remove(original_file.c_str());
    rename(temp_file.c_str(), original_file.c_str());
}

void cdocx::Document::save(const std::string& file) 
{
        // minizip only supports appending or writing to new files
    // so we must
    // - make a new file
    // - write any new files
    // - copy the old files
    // - delete old docx
    // - rename new file to old file
    
    if(!this->is_open()) {
        // if file is not existing, save() will make no sense
        return;
    }

    // Read document buffer
    xml_string_writer writer;
    this->document.print(writer);

    // Open file and replace "xml" content

    std::string temp_file = this->directory + ".tmp";

    // Create the new file
    zip_t *new_zip =
        zip_open(temp_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    // Write out document.xml
    zip_entry_open(new_zip, "word/document.xml");

    const char *buf = writer.result.c_str();

    zip_entry_write(new_zip, buf, strlen(buf));
    zip_entry_close(new_zip);

    // Open the original zip and copy all files which are not replaced by CDocx
    zip_t *orig_zip =
        zip_open(this->directory.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    // Loop & copy each relevant entry in the original zip
    int orig_zip_entry_ct = zip_total_entries(orig_zip);
    for (int i = 0; i < orig_zip_entry_ct; i++) {
        zip_entry_openbyindex(orig_zip, i);
        const char *name = zip_entry_name(orig_zip);
        auto nameStr = std::string(name);
        // Skip copying the original file
        if (nameStr != std::string("word/document.xml") &&
            nameStr[nameStr.size() -1] != '/') {
            // Read the old content
            void *entry_buf;
            size_t entry_buf_size;
            zip_entry_read(orig_zip, &entry_buf, &entry_buf_size);

            // Write into new zip
            zip_entry_open(new_zip, name);
            zip_entry_write(new_zip, entry_buf, entry_buf_size);
            zip_entry_close(new_zip);

            free(entry_buf);
        }

        zip_entry_close(orig_zip);
    }

    // Close both zips
    zip_close(orig_zip);
    zip_close(new_zip);

    // Remove original zip, rename new to correct name
    // Check if file exists before attempting to remove it
    if (std::filesystem::exists(file)) {
        remove(file.c_str());
    }
    rename(temp_file.c_str(), file.c_str());
}

bool cdocx::Document::is_open() const {
    return this->flag_is_open;
}

cdocx::Paragraph &cdocx::Document::paragraphs() {
    if (!this->is_open()) {
        // Return a default-constructed paragraph that won't crash
        static Paragraph empty_paragraph;
        return empty_paragraph;
    }
    
    pugi::xml_node body_node = document.child("w:document").child("w:body");
    if (!body_node) {
        static Paragraph empty_paragraph;
        return empty_paragraph;
    }
    
    this->paragraph.set_parent(body_node);
    return this->paragraph;
}

cdocx::Table &cdocx::Document::tables() {
    if (!this->is_open()) {
        // Return a default-constructed table that won't crash
        static Table empty_table;
        return empty_table;
    }
    
    pugi::xml_node body_node = document.child("w:document").child("w:body");
    if (!body_node) {
        static Table empty_table;
        return empty_table;
    }
    
    this->table.set_parent(body_node);
    return this->table;
}

// Template implementation
cdocx::Template::Template(Document *document) : doc(document) {}

cdocx::Template::Template(Document *document, const std::string &prefix,
                         const std::string &suffix)
    : doc(document), pattern_prefix(prefix), pattern_suffix(suffix) {}

void cdocx::Template::set(const std::string &key, const std::string &value) {
    placeholders[key] = value;
}

void cdocx::Template::set(const std::string &key, const char *value) {
    placeholders[key] = std::string(value);
}

void cdocx::Template::set_pattern(const std::string &prefix,
                                  const std::string &suffix) {
    pattern_prefix = prefix;
    pattern_suffix = suffix;
}

bool cdocx::Template::replace_in_string(std::string &text) const {
    bool replaced = false;
    std::string result = text;

    for (const auto &ph : placeholders) {
        std::string pattern = pattern_prefix + ph.first + pattern_suffix;
        size_t pos = result.find(pattern);
        while (pos != std::string::npos) {
            result.replace(pos, pattern.length(), ph.second);
            replaced = true;
            pos = result.find(pattern, pos + ph.second.length());
        }
    }

    if (replaced) {
        text = result;
    }

    return replaced;
}
#include <iostream>
void cdocx::Template::replace_in_paragraphs() {
    auto &paragraphs = doc->paragraphs();
    std::vector<cdocx::Run> runss;
    cdocx::Run prefix_run;
    bool first = true;
    cdocx::Run first_run;
    cdocx::Run suffix_run;
    std::vector<std::string> strs;
    std::string sstr;
    bool begin = false;
    int pos = 0;
    for (auto p = paragraphs; p.has_next(); p.next()) {
        auto &runs = p.runs();
        for (auto r = runs; r.has_next(); r.next()) {
            std::string text = r.get_text();
            if (text.empty()) {
                continue;
            }
            // if (replace_in_string(text)) {
            //     r.set_text(text);
            //     continue;
            // }

            if (text == pattern_prefix) {
                begin = true;
                sstr = "";
                prefix_run = r;
                continue;
            }
            if (begin) {
                if (first) {
                    first_run = r;
                    first = false;
                } else {
                    runss.push_back(r);
                }
                if (text == pattern_suffix) {
                    suffix_run = r;
                    for (const auto &ph : placeholders) {
                        if (sstr == ph.first) {
                            // replace
                            first_run.set_text(ph.second);
                            p.remove_run(prefix_run);
                            p.remove_run(suffix_run);
                            for (auto rr : runss) {
                                p.remove_run(rr);
                            }
                            begin = false;
                            sstr = "";
                            runss.clear();
                            break;
                        }
                    }
                }
                sstr += text;
            }
        }
    }
}


void cdocx::Template::replace_in_tables() {
    auto &tables = doc->tables();
    for (auto t = tables; t.has_next(); t.next()) {
        auto &rows = t.rows();
        for (auto row = rows; row.has_next(); row.next()) {
            auto &cells = row.cells();
            for (auto cell = cells; cell.has_next(); cell.next()) {
                auto &paragraphs = cell.paragraphs();
                for (auto p = paragraphs; p.has_next(); p.next()) {
                    auto &runs = p.runs();
                    for (auto r = runs; r.has_next(); r.next()) {
                        std::string text = r.get_text();
                        if (replace_in_string(text)) {
                            r.set_text(text);
                        }
                    }
                }
            }
        }
    }
}

void cdocx::Template::replace_all() {
    if (!doc->is_open()) {
        return;
    }

    replace_in_paragraphs();
    replace_in_tables();
}

void cdocx::Template::clear() { placeholders.clear(); }

size_t cdocx::Template::size() const { return placeholders.size(); }

cdocx::Document::~Document() {
    if (flag_is_open) {
        zip_close(zipfile);
    }
}

