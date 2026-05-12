#include <cdocx/document.h>
#include <cdocx/format_context.h>
#include <cdocx/paragraph.h>
#include <cdocx/section.h>
#include <cdocx/table.h>

#include <cstring>

namespace cdocx {

namespace {

void apply_formatting_flags(pugi::xml_node r_pr, FormattingFlag f) {
    if (f & kBold) {
        r_pr.append_child("w:b");
    }
    if (f & kItalic) {
        r_pr.append_child("w:i");
    }
    if (f & kUnderline) {
        r_pr.append_child("w:u").append_attribute("w:val").set_value("single");
    }
    if (f & kStrikethrough) {
        r_pr.append_child("w:strike").append_attribute("w:val").set_value("true");
    }
    if (f & kSuperscript) {
        r_pr.append_child("w:vertAlign").append_attribute("w:val").set_value("superscript");
    } else if (f & kSubscript) {
        r_pr.append_child("w:vertAlign").append_attribute("w:val").set_value("subscript");
    }
    if (f & kSmallCaps) {
        r_pr.append_child("w:smallCaps").append_attribute("w:val").set_value("true");
    }
    if (f & kShadow) {
        r_pr.append_child("w:shadow").append_attribute("w:val").set_value("true");
    }
}

struct BreakCharMapping {
    BreakType type;
    char16_t char_code;
};

static const BreakCharMapping kBreakCharMappings[] = {
    {BreakType::PageBreak, 0x0C},
    {BreakType::LineBreak, 0x0B},
    {BreakType::ColumnBreak, 0x0E},
};

}  // namespace

// ============================================================================
// Paragraph DOM Implementation
// ============================================================================

Paragraph::Paragraph(Document* doc) {
    set_document(doc);
}

Paragraph::Paragraph(const Paragraph& other)
    : CompositeNode(other),
      format_(other.format_),
      list_format_(other.list_format_),
      parent_(other.parent_),
      current_(other.current_),
      run_(other.run_) {
    if (other.preserved_p_pr_.first_child()) {
        preserved_p_pr_.reset();
        preserved_p_pr_.append_copy(other.preserved_p_pr_.first_child());
    }
}

Paragraph& Paragraph::operator=(const Paragraph& other) {
    if (this != &other) {
        CompositeNode::operator=(other);
        format_ = other.format_;
        list_format_ = other.list_format_;
        parent_ = other.parent_;
        current_ = other.current_;
        run_ = other.run_;
        preserved_p_pr_.reset();
        if (other.preserved_p_pr_.first_child()) {
            preserved_p_pr_.append_copy(other.preserved_p_pr_.first_child());
        }
    }
    return *this;
}

std::string Paragraph::get_text() const {
    std::string result;
    // Legacy fallback: if bound to XML but has no DOM children, read from XML directly
    if (current_ && get_children().empty()) {
        for (auto run = current_.child("w:r"); run; run = run.next_sibling("w:r")) {
            auto t = run.child("w:t");
            if (t) {
                result += t.text().get();
            }
        }
        return result;
    }
    for (const auto& child : get_children()) {
        result += child->get_text();
    }
    return result;
}

void Paragraph::accept(DocumentVisitor* visitor) {
    if (!visitor) {
        return;
    }
    if (visitor->visit_paragraph_start(*this) == VisitorAction::Continue) {
        for (const auto& child : get_children()) {
            child->accept(visitor);
        }
        visitor->visit_paragraph_end(*this);
    }
}

std::shared_ptr<Node> Paragraph::clone(bool deep) const {
    auto cloned = std::make_shared<Paragraph>(get_document());
    cloned->set_paragraph_format(format_);
    cloned->get_list_format() = list_format_;
    if (has_preserved_p_pr()) {
        cloned->preserve_p_pr(get_preserved_p_pr());
    }
    if (deep) {
        for (const auto& child : get_children()) {
            if (auto child_clone = child->clone(deep)) {
                cloned->append_child(child_clone);
            }
        }
    }
    return cloned;
}

void Paragraph::preserve_p_pr(pugi::xml_node p_pr) {
    if (!p_pr) {
        preserved_p_pr_.reset();
        return;
    }
    preserved_p_pr_.reset();
    preserved_p_pr_.append_copy(p_pr);
}

pugi::xml_node Paragraph::get_preserved_p_pr() const {
    return preserved_p_pr_.first_child();
}

bool Paragraph::has_preserved_p_pr() const {
    return preserved_p_pr_.first_child();
}

// ============================================================================
// Bookmark Operations (DOM API)
// ============================================================================

static int generate_bookmark_id() {
    static int next_id = 1;
    return next_id++;
}

std::shared_ptr<BookmarkStart> Paragraph::append_bookmark_start(const std::string& name) {
    auto bookmark = std::make_shared<BookmarkStart>(get_document());
    bookmark->set_name(name);
    bookmark->set_id(generate_bookmark_id());
    append_child(bookmark);
    return bookmark;
}

std::shared_ptr<BookmarkEnd> Paragraph::append_bookmark_end(int id) {
    auto bookmark = std::make_shared<BookmarkEnd>(get_document());
    bookmark->set_id(id);
    append_child(bookmark);
    return bookmark;
}

std::shared_ptr<Field> Paragraph::append_field(FieldType type) {
    auto field = std::make_shared<Field>(get_document(), type);
    append_child(field);
    return field;
}

std::shared_ptr<Field> Paragraph::insert_field(int index, FieldType type) {
    auto field = std::make_shared<Field>(get_document(), type);
    insert_child(index, field);
    return field;
}

// ============================================================================
// Special Character Operations (DOM API)
// ============================================================================

std::shared_ptr<SpecialChar> Paragraph::append_special_char(char16_t char_code) {
    auto special = std::make_shared<SpecialChar>(char_code);
    append_child(special);
    return special;
}

std::shared_ptr<SpecialChar> Paragraph::append_break(BreakType break_type) {
    for (const auto& mapping : kBreakCharMappings) {
        if (mapping.type == break_type) {
            auto special = std::make_shared<SpecialChar>(mapping.char_code);
            append_child(special);
            return special;
        }
    }
    return append_special_char(0x0D);  // paragraph break
}

std::shared_ptr<SpecialChar> Paragraph::append_page_break() {
    auto special = std::make_shared<SpecialChar>(0x0C);
    append_child(special);
    return special;
}

std::shared_ptr<SpecialChar> Paragraph::append_line_break() {
    auto special = std::make_shared<SpecialChar>(0x0B);
    append_child(special);
    return special;
}

std::shared_ptr<SpecialChar> Paragraph::append_tab() {
    auto special = std::make_shared<SpecialChar>(0x09);
    append_child(special);
    return special;
}

// ============================================================================
// Convenience: Hyperlink and Field
// ============================================================================

std::shared_ptr<Hyperlink> Paragraph::append_hyperlink(const std::string& text,
                                                       const std::string& url) {
    auto link = std::make_shared<Hyperlink>(get_document());
    link->set_address(url);
    link->set_result(text);
    append_child(link);
    return link;
}

std::shared_ptr<Hyperlink> Paragraph::append_hyperlink(const std::string& text,
                                                       const std::string& bookmark_name,
                                                       bool /*is_bookmark*/) {
    auto link = std::make_shared<Hyperlink>(get_document());
    link->set_bookmark_name(bookmark_name);
    link->set_result(text);
    append_child(link);
    return link;
}

std::shared_ptr<Field> Paragraph::append_page_number(const std::string& switches) {
    auto field = std::make_shared<Field>(get_document(), FieldType::Page);
    field->set_field_code("PAGE");
    field->set_result("1");
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    append_child(field);
    return field;
}

std::shared_ptr<Field> Paragraph::append_date(const std::string& switches) {
    auto field = std::make_shared<Field>(get_document(), FieldType::Date);
    field->set_field_code("DATE");
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    append_child(field);
    return field;
}

std::shared_ptr<Field> Paragraph::append_time(const std::string& switches) {
    auto field = std::make_shared<Field>(get_document(), FieldType::Time);
    field->set_field_code("TIME");
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    append_child(field);
    return field;
}

std::shared_ptr<Field> Paragraph::append_merge_field(const std::string& field_name,
                                                     const std::string& switches) {
    auto field = std::make_shared<Field>(get_document(), FieldType::MergeField);
    field->set_field_code("MERGEFIELD " + field_name);
    if (!switches.empty()) {
        field->add_switch(switches);
    }
    append_child(field);
    return field;
}

// ============================================================================
// Run Operations (DOM API)
// ============================================================================

std::shared_ptr<Run> Paragraph::append_run(const std::string& text) {
    auto run = std::make_shared<Run>(get_document(), text);
    append_child(run);
    return run;
}

std::shared_ptr<Run> Paragraph::insert_run(int index, const std::string& text) {
    auto run = std::make_shared<Run>(get_document(), text);
    insert_child(index, run);
    return run;
}

std::shared_ptr<Run> Paragraph::get_first_run() const {
    return get_first_child<Run>();
}

std::shared_ptr<Run> Paragraph::get_last_run() const {
    return get_last_child<Run>();
}

RunCollection Paragraph::get_runs() const {
    auto runs = get_children_of_type<Run>();
    return RunCollection(runs);
}

std::vector<std::shared_ptr<Field>> Paragraph::get_fields() const {
    return get_children_of_type<Field>();
}

void Paragraph::set_text(const std::string& text) {
    remove_all_children();
    append_run(text);
}

void Paragraph::append_text(const std::string& text) {
    if (auto last_run = get_last_run()) {
        last_run->append_text(text);
    } else {
        append_run(text);
    }
}

void Paragraph::prepend_text(const std::string& text) {
    if (auto first_run = get_first_run()) {
        first_run->prepend_text(text);
    } else {
        append_run(text);
    }
}

// ============================================================================
// Utility Methods
// ============================================================================

int Paragraph::join_runs_with_same_formatting() {
    int merged_count = 0;
    auto children = get_children();

    for (size_t i = 0; i + 1 < children.size();) {
        auto run1 = std::dynamic_pointer_cast<Run>(children[i]);
        auto run2 = std::dynamic_pointer_cast<Run>(children[i + 1]);

        if (!run1 || !run2) {
            ++i;
            continue;
        }

        if (run1->get_font() == run2->get_font()) {
            run1->append_text(run2->get_text());
            remove_child(run2);
            children.erase(children.begin() + i + 1);
            ++merged_count;
        } else {
            ++i;
        }
    }

    return merged_count;
}

void Paragraph::ensure_minimum() {
    if (!get_first_run()) {
        append_run("");
    }
}

// ============================================================================
// Legacy Paragraph Implementation (iterator style)
// ============================================================================

Paragraph::Paragraph() = default;

Paragraph::Paragraph(pugi::xml_node parent_node, pugi::xml_node current_node)
    : parent_(parent_node), current_(current_node) {
    run_.set_parent_xml(current_);
}

void Paragraph::set_parent(pugi::xml_node node) {
    parent_ = node;
    // Find first paragraph child
    current_ = parent_.child("w:p");
    // Initialize run iterator for this paragraph
    if (current_) {
        run_.set_parent_xml(current_);
    }
}

void Paragraph::set_current(pugi::xml_node node) {
    current_ = node;
}

Paragraph& Paragraph::next() {
    // Move to next w:p sibling (skip non-paragraph elements like w:sect_pr)
    current_ = current_.next_sibling("w:p");
    // Update run iterator for new paragraph
    if (current_) {
        run_.set_parent_xml(current_);
    }
    return *this;
}

bool Paragraph::has_next() const {
    return current_ != nullptr;
}

Run& Paragraph::runs() {
    run_.set_parent_xml(current_);
    return run_;
}

Run& Paragraph::add_run(const std::string& text, FormattingFlag f) {
    return add_run(text.c_str(), f);
}

Run& Paragraph::add_run(const char* text, FormattingFlag f) {
    if (!current_) {
        return run_;
    }

    // Create new run element
    pugi::xml_node new_run = current_.append_child("w:r");

    // Create run properties element
    const pugi::xml_node meta = new_run.append_child("w:rPr");

    apply_formatting_flags(meta, f);

    // Create text element
    pugi::xml_node new_run_text = new_run.append_child("w:t");

    // Preserve spaces if text starts or ends with whitespace
    if (*text != 0 && (std::isspace(static_cast<unsigned char>(text[0])) ||
                       std::isspace(static_cast<unsigned char>(text[std::strlen(text) - 1])))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }

    // Set text content
    new_run_text.text().set(text);
    run_.set_current_xml(new_run);

    return run_;
}

Run& Paragraph::add_run_with_bookmark(Document& doc,
                                      const std::string& text,
                                      const std::string& bookmark_name,
                                      FormattingFlag f) {
    return add_run_with_bookmark(doc, text.c_str(), bookmark_name, f);
}

Run& Paragraph::add_run_with_bookmark(Document& doc,
                                      const char* text,
                                      const std::string& bookmark_name,
                                      FormattingFlag f) {
    if (!current_) {
        return run_;
    }

    // Generate unique bookmark ID
    const int bookmark_id = doc.generate_unique_bookmark_id();

    // Create bookmark_start element before the run
    pugi::xml_node bookmark_start = current_.append_child("w:bookmarkStart");
    bookmark_start.append_attribute("w:id").set_value(bookmark_id);
    bookmark_start.append_attribute("w:name").set_value(bookmark_name.c_str());

    // Create new run element (same as add_run)
    pugi::xml_node new_run = current_.append_child("w:r");

    // Create run properties element
    const pugi::xml_node meta = new_run.append_child("w:rPr");

    apply_formatting_flags(meta, f);

    // Create text element
    pugi::xml_node new_run_text = new_run.append_child("w:t");

    // Preserve spaces if text starts or ends with whitespace
    if (*text != 0 && (std::isspace(static_cast<unsigned char>(text[0])) ||
                       std::isspace(static_cast<unsigned char>(text[std::strlen(text) - 1])))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }

    // Set text content
    new_run_text.text().set(text);

    // Create bookmark_end element after the run
    pugi::xml_node bookmark_end = current_.append_child("w:bookmarkEnd");
    bookmark_end.append_attribute("w:id").set_value(bookmark_id);

    run_.set_current_xml(new_run);

    return run_;
}

void Paragraph::remove_run(const Run& r) {
    if (!current_) {
        return;
    }
    current_.remove_child(r.get_current_xml());
}

Paragraph& Paragraph::insert_paragraph_after(const std::string& text, FormattingFlag f) {
    // Insert new paragraph after current
    const pugi::xml_node new_para = parent_.insert_child_after("w:p", current_);

    // Create static pointer to avoid stack allocation issues
    // Note: This is a potential memory leak in the original code
    static Paragraph* p = nullptr;
    delete p;
    p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);

    return *p;
}

bool Paragraph::clear() {
    if (!current_) {
        return false;
    }

    // Remove all run elements
    pugi::xml_node run = current_.child("w:r");
    while (run) {
        const pugi::xml_node next = run.next_sibling("w:r");
        current_.remove_child(run);
        run = next;
    }
    return true;
}

bool Paragraph::remove() {
    if (!parent_ || !current_) {
        return false;
    }
    return parent_.remove_child(current_);
}

Paragraph* Paragraph::insert_before(const std::string& text, FormattingFlag f) {
    if (!parent_ || !current_) {
        return nullptr;
    }

    // Insert new paragraph before current
    const pugi::xml_node new_para = parent_.insert_child_before("w:p", current_);

    // Note: This returns a pointer to a heap-allocated object
    // Caller is responsible for deletion (but API design suggests this is managed)
    auto* p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);

    return p;
}

// ============================================================================
// Paragraph Formatting Methods
// ============================================================================

/**
 * @internal
 * @brief Get or create paragraph properties element
 * @param para The w:p element
 * @return The w:p_pr element
 */
static pugi::xml_node get_or_create_p_pr(pugi::xml_node para) {
    pugi::xml_node p_pr = para.child("w:p_pr");
    if (!p_pr) {
        p_pr = para.prepend_child("w:p_pr");
    }
    return p_pr;
}

bool Paragraph::set_alignment(const std::string& alignment) {
    if (!current_) {
        return false;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    // Get or create justification element
    pugi::xml_node jc = p_pr.child("w:jc");
    if (!jc) {
        jc = p_pr.append_child("w:jc");
    }

    jc.append_attribute("w:val").set_value(alignment.c_str());
    return true;
}

bool Paragraph::set_style(const std::string& style_id) {
    if (!current_) {
        return false;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    // Get or create paragraph style element
    pugi::xml_node p_style = p_pr.child("w:pStyle");
    if (!p_style) {
        p_style = p_pr.prepend_child("w:pStyle");
    }

    p_style.append_attribute("w:val").set_value(style_id.c_str());
    return true;
}

bool Paragraph::set_line_spacing(int line_spacing, bool is_exact) {
    if (!current_) {
        return false;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    // Get or create spacing element
    pugi::xml_node spacing = p_pr.child("w:spacing");
    if (!spacing) {
        spacing = p_pr.append_child("w:spacing");
    }

    // Set line rule
    spacing.append_attribute("w:lineRule").set_value(is_exact ? "exact" : "auto");
    spacing.append_attribute("w:line").set_value(line_spacing);

    return true;
}

bool Paragraph::set_spacing_before(int spacing) {
    if (!current_) {
        return false;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    pugi::xml_node sp = p_pr.child("w:spacing");
    if (!sp) {
        sp = p_pr.append_child("w:spacing");
    }

    sp.append_attribute("w:before").set_value(spacing);
    return true;
}

bool Paragraph::set_spacing_after(int spacing) {
    if (!current_) {
        return false;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    pugi::xml_node sp = p_pr.child("w:spacing");
    if (!sp) {
        sp = p_pr.append_child("w:spacing");
    }

    sp.append_attribute("w:after").set_value(spacing);
    return true;
}

bool Paragraph::set_indent(int left, int right, int first_line) {
    if (!current_) {
        return false;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    // Get or create indentation element
    pugi::xml_node ind = p_pr.child("w:ind");
    if (!ind) {
        ind = p_pr.append_child("w:ind");
    }

    // Set indentation values (-1 means ignore)
    if (left >= 0) {
        ind.append_attribute("w:left").set_value(left);
    }
    if (right >= 0) {
        ind.append_attribute("w:right").set_value(right);
    }
    if (first_line != 0) {
        ind.append_attribute("w:firstLine").set_value(first_line);
    }

    return true;
}

// ============================================================================
// Paragraph Text Formatting Methods
// ============================================================================

/**
 * @internal
 * @brief Get or create the first run in a paragraph for formatting
 * @param para The w:p element
 * @return The w:r element (created if didn't exist)
 */
static pugi::xml_node get_or_create_first_run(pugi::xml_node para) {
    pugi::xml_node run = para.child("w:r");
    if (!run) {
        // Create new run element
        run = para.append_child("w:r");
        // Create run properties
        run.append_child("w:rPr");
        // Create empty text element
        const pugi::xml_node t = run.append_child("w:t");
        t.text().set("");
    }
    return run;
}

bool Paragraph::set_color(const std::string& color_hex) {
    if (!current_) {
        return false;
    }
    const pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_color(run, color_hex);
}

bool Paragraph::set_font_size(int size) {
    if (!current_) {
        return false;
    }
    const pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_font_size(run, size);
}

bool Paragraph::set_font_name(const std::string& font_name) {
    if (!current_) {
        return false;
    }
    const pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_font_name(run, font_name);
}

bool Paragraph::set_bold(bool bold) {
    if (!current_) {
        return false;
    }
    const pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_bold(run, bold);
}

bool Paragraph::set_italic(bool italic) {
    if (!current_) {
        return false;
    }
    const pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_italic(run, italic);
}

bool Paragraph::set_underline(bool underline) {
    if (!current_) {
        return false;
    }
    const pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_underline(run, underline);
}

// ============================================================================
// List/Numbering Support (v0.5.0)
// ============================================================================

bool Paragraph::set_numbering(NumberingId num_id, NumberingLevel level) {
    // Always update the DOM list_format_ so sync_to_physical_tree() preserves it.
    list_format_.list_id = num_id;
    list_format_.level = level;

    // If this paragraph is backed by physical XML, update it as well.
    if (!current_) {
        return true;
    }

    pugi::xml_node p_pr = get_or_create_p_pr(current_);

    // Remove existing num_pr if any
    const pugi::xml_node existing_num_pr = p_pr.child("w:numPr");
    if (existing_num_pr) {
        p_pr.remove_child(existing_num_pr);
    }

    // Create num_pr element
    pugi::xml_node num_pr = p_pr.append_child("w:numPr");

    // Add ilvl (level)
    pugi::xml_node ilvl = num_pr.append_child("w:ilvl");
    ilvl.append_attribute("w:val").set_value(numbering_level_to_int(level));

    // Add num_id
    pugi::xml_node num_id_node = num_pr.append_child("w:numId");
    num_id_node.append_attribute("w:val").set_value(static_cast<unsigned int>(num_id));

    return true;
}

bool Paragraph::remove_numbering() {
    // Always clear the DOM list_format_.
    const bool had_dom_numbering = list_format_.is_list_item();
    list_format_.remove_list_format();

    if (!current_) {
        return had_dom_numbering;
    }

    pugi::xml_node p_pr = current_.child("w:p_pr");
    if (!p_pr) {
        return had_dom_numbering;
    }

    const pugi::xml_node num_pr = p_pr.child("w:numPr");
    if (!num_pr) {
        return had_dom_numbering;
    }

    return p_pr.remove_child(num_pr);
}

bool Paragraph::has_numbering() const {
    // Prefer DOM state over physical XML.
    if (list_format_.is_list_item()) {
        return true;
    }

    if (!current_) {
        return false;
    }

    const pugi::xml_node p_pr = current_.child("w:p_pr");
    if (!p_pr) {
        return false;
    }

    return p_pr.child("w:numPr") != nullptr;
}

NumberingId Paragraph::get_numbering_id() const {
    // Prefer DOM state over physical XML.
    if (list_format_.is_list_item()) {
        return list_format_.list_id;
    }

    if (!current_) {
        return 0;
    }

    const pugi::xml_node p_pr = current_.child("w:p_pr");
    if (!p_pr) {
        return 0;
    }

    const pugi::xml_node num_pr = p_pr.child("w:numPr");
    if (!num_pr) {
        return 0;
    }

    const pugi::xml_node num_id = num_pr.child("w:numId");
    if (!num_id) {
        return 0;
    }

    return num_id.attribute("w:val").as_uint();
}

NumberingLevel Paragraph::get_numbering_level() const {
    // Prefer DOM state over physical XML.
    if (list_format_.is_list_item()) {
        return list_format_.level;
    }

    if (!current_) {
        return NumberingLevel::Level1;
    }

    const pugi::xml_node p_pr = current_.child("w:p_pr");
    if (!p_pr) {
        return NumberingLevel::Level1;
    }

    const pugi::xml_node num_pr = p_pr.child("w:numPr");
    if (!num_pr) {
        return NumberingLevel::Level1;
    }

    const pugi::xml_node ilvl = num_pr.child("w:ilvl");
    if (!ilvl) {
        return NumberingLevel::Level1;
    }

    const int level = ilvl.attribute("w:val").as_int();
    if (level < 0 || level > 8) {
        return NumberingLevel::Level1;
    }

    return static_cast<NumberingLevel>(level);
}

bool Paragraph::set_list_level(NumberingLevel level) {
    // Always update the DOM list_format_.
    list_format_.level = level;

    if (!current_) {
        return list_format_.is_list_item();
    }

    const pugi::xml_node p_pr = current_.child("w:p_pr");
    if (!p_pr) {
        return list_format_.is_list_item();
    }

    pugi::xml_node num_pr = p_pr.child("w:numPr");
    if (!num_pr) {
        return list_format_.is_list_item();
    }

    pugi::xml_node ilvl = num_pr.child("w:ilvl");
    if (!ilvl) {
        ilvl = num_pr.prepend_child("w:ilvl");
    }

    ilvl.attribute("w:val").set_value(numbering_level_to_int(level));
    return true;
}

bool Paragraph::increase_list_level() {
    const int current_level = numbering_level_to_int(get_numbering_level());
    if (current_level < 8) {
        return set_list_level(static_cast<NumberingLevel>(current_level + 1));
    }
    return false;
}

bool Paragraph::decrease_list_level() {
    const int current_level = numbering_level_to_int(get_numbering_level());
    if (current_level > 0) {
        return set_list_level(static_cast<NumberingLevel>(current_level - 1));
    }
    return false;
}

Paragraph& Paragraph::set_properties(const ParagraphProperties& props) {
    props.apply_to(*this);
    return *this;
}

Paragraph& Paragraph::set_outline_level(cdocx::ParagraphProperties::OutlineLevel level) {
    format_.outline_level = static_cast<OutlineLevel>(level);
    return *this;
}

Paragraph& Paragraph::set_keep_next(bool value) {
    format_.keep_with_next = value;
    return *this;
}

Paragraph& Paragraph::set_keep_lines(bool value) {
    format_.keep_together = value;
    return *this;
}

Paragraph& Paragraph::set_page_break_before(bool value) {
    format_.page_break_before = value;
    return *this;
}

std::string ParagraphCollection::get_text() const {
    std::string result;
    for (const auto& para : paragraphs_) {
        if (para) {
            if (!result.empty()) {
                result += "\n";
            }
            result += para->get_text();
        }
    }
    return result;
}

// ============================================================================
// Parent Access
// ============================================================================

std::shared_ptr<Body> Paragraph::get_parent_body() const {
    for (CompositeNode* current = Node::parent_; current; current = current->get_parent()) {
        if (current->node_type() == NodeType::Body) {
            return std::static_pointer_cast<Body>(current->shared_from_this());
        }
    }
    return nullptr;
}

std::shared_ptr<Cell> Paragraph::get_parent_cell() const {
    for (CompositeNode* current = Node::parent_; current; current = current->get_parent()) {
        if (current->node_type() == NodeType::Cell) {
            return std::static_pointer_cast<Cell>(current->shared_from_this());
        }
    }
    return nullptr;
}

std::shared_ptr<Section> Paragraph::get_parent_section() const {
    for (CompositeNode* current = Node::parent_; current; current = current->get_parent()) {
        if (current->node_type() == NodeType::Section) {
            return std::static_pointer_cast<Section>(current->shared_from_this());
        }
    }
    return nullptr;
}

// ============================================================================
// Position Checks
// ============================================================================

bool Paragraph::is_in_cell() const {
    return get_parent_cell() != nullptr;
}

bool Paragraph::is_end_of_cell() const {
    auto cell = get_parent_cell();
    if (!cell) {
        return false;
    }
    auto last = cell->get_last_child();
    return last && last.get() == this;
}

bool Paragraph::is_end_of_section() const {
    auto section = get_parent_section();
    if (!section) {
        return false;
    }
    auto body = section->get_body();
    if (!body) {
        return false;
    }
    auto last = body->get_last_child();
    return last && last.get() == this;
}

bool Paragraph::is_list_item() const {
    return list_format_.is_list_item();
}

}  // namespace cdocx
