#include <cdocx/document.h>
#include <cdocx/format_context.h>
#include <cdocx/paragraph.h>

#include <cstring>

namespace cdocx {

namespace {

void apply_formatting_flags(pugi::xml_node rPr, formatting_flag f) {
    if (f & bold) {
        rPr.append_child("w:b");
    }
    if (f & italic) {
        rPr.append_child("w:i");
    }
    if (f & underline) {
        rPr.append_child("w:u").append_attribute("w:val").set_value("single");
    }
    if (f & strikethrough) {
        rPr.append_child("w:strike").append_attribute("w:val").set_value("true");
    }
    if (f & superscript) {
        rPr.append_child("w:vertAlign").append_attribute("w:val").set_value("superscript");
    } else if (f & subscript) {
        rPr.append_child("w:vertAlign").append_attribute("w:val").set_value("subscript");
    }
    if (f & smallcaps) {
        rPr.append_child("w:smallCaps").append_attribute("w:val").set_value("true");
    }
    if (f & shadow) {
        rPr.append_child("w:shadow").append_attribute("w:val").set_value("true");
    }
}

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
    if (other.preserved_pPr_.first_child()) {
        preserved_pPr_.reset();
        preserved_pPr_.append_copy(other.preserved_pPr_.first_child());
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
        preserved_pPr_.reset();
        if (other.preserved_pPr_.first_child()) {
            preserved_pPr_.append_copy(other.preserved_pPr_.first_child());
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
    if (!visitor)
        return;
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
    if (has_preserved_pPr()) {
        cloned->preserve_pPr(get_preserved_pPr());
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

void Paragraph::preserve_pPr(pugi::xml_node pPr) {
    if (!pPr) {
        preserved_pPr_.reset();
        return;
    }
    preserved_pPr_.reset();
    preserved_pPr_.append_copy(pPr);
}

pugi::xml_node Paragraph::get_preserved_pPr() const {
    return preserved_pPr_.first_child();
}

bool Paragraph::has_preserved_pPr() const {
    return preserved_pPr_.first_child();
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
    // Move to next w:p sibling (skip non-paragraph elements like w:sectPr)
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

Run& Paragraph::add_run(const std::string& text, formatting_flag f) {
    return add_run(text.c_str(), f);
}

Run& Paragraph::add_run(const char* text, formatting_flag f) {
    if (!current_) {
        return run_;
    }

    // Create new run element
    pugi::xml_node new_run = current_.append_child("w:r");

    // Create run properties element
    pugi::xml_node meta = new_run.append_child("w:rPr");

    apply_formatting_flags(meta, f);

    // Create text element
    pugi::xml_node new_run_text = new_run.append_child("w:t");

    // Preserve spaces if text starts or ends with whitespace
    if (*text != 0 && (std::isspace(text[0]) || std::isspace(text[std::strlen(text) - 1]))) {
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
                                      formatting_flag f) {
    return add_run_with_bookmark(doc, text.c_str(), bookmark_name, f);
}

Run& Paragraph::add_run_with_bookmark(Document& doc,
                                      const char* text,
                                      const std::string& bookmark_name,
                                      formatting_flag f) {
    if (!current_) {
        return run_;
    }

    // Generate unique bookmark ID
    int bookmark_id = doc.generate_unique_bookmark_id();

    // Create bookmarkStart element before the run
    pugi::xml_node bookmark_start = current_.append_child("w:bookmarkStart");
    bookmark_start.append_attribute("w:id").set_value(bookmark_id);
    bookmark_start.append_attribute("w:name").set_value(bookmark_name.c_str());

    // Create new run element (same as add_run)
    pugi::xml_node new_run = current_.append_child("w:r");

    // Create run properties element
    pugi::xml_node meta = new_run.append_child("w:rPr");

    apply_formatting_flags(meta, f);

    // Create text element
    pugi::xml_node new_run_text = new_run.append_child("w:t");

    // Preserve spaces if text starts or ends with whitespace
    if (*text != 0 && (std::isspace(text[0]) || std::isspace(text[std::strlen(text) - 1]))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }

    // Set text content
    new_run_text.text().set(text);

    // Create bookmarkEnd element after the run
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

Paragraph& Paragraph::insert_paragraph_after(const std::string& text, formatting_flag f) {
    // Insert new paragraph after current
    pugi::xml_node new_para = parent_.insert_child_after("w:p", current_);

    // Create static pointer to avoid stack allocation issues
    // Note: This is a potential memory leak in the original code
    static Paragraph* p = nullptr;
    if (p) {
        delete p;
    }
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
        pugi::xml_node next = run.next_sibling("w:r");
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

Paragraph* Paragraph::insert_before(const std::string& text, formatting_flag f) {
    if (!parent_ || !current_) {
        return nullptr;
    }

    // Insert new paragraph before current
    pugi::xml_node new_para = parent_.insert_child_before("w:p", current_);

    // Note: This returns a pointer to a heap-allocated object
    // Caller is responsible for deletion (but API design suggests this is managed)
    Paragraph* p = new Paragraph();
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
 * @return The w:pPr element
 */
static pugi::xml_node get_or_create_pPr(pugi::xml_node para) {
    pugi::xml_node pPr = para.child("w:pPr");
    if (!pPr) {
        pPr = para.prepend_child("w:pPr");
    }
    return pPr;
}

bool Paragraph::set_alignment(const std::string& alignment) {
    if (!current_) {
        return false;
    }

    pugi::xml_node pPr = get_or_create_pPr(current_);

    // Get or create justification element
    pugi::xml_node jc = pPr.child("w:jc");
    if (!jc) {
        jc = pPr.append_child("w:jc");
    }

    jc.append_attribute("w:val").set_value(alignment.c_str());
    return true;
}

bool Paragraph::set_style(const std::string& style_id) {
    if (!current_) {
        return false;
    }

    pugi::xml_node pPr = get_or_create_pPr(current_);

    // Get or create paragraph style element
    pugi::xml_node pStyle = pPr.child("w:pStyle");
    if (!pStyle) {
        pStyle = pPr.prepend_child("w:pStyle");
    }

    pStyle.append_attribute("w:val").set_value(style_id.c_str());
    return true;
}

bool Paragraph::set_line_spacing(int line_spacing, bool is_exact) {
    if (!current_) {
        return false;
    }

    pugi::xml_node pPr = get_or_create_pPr(current_);

    // Get or create spacing element
    pugi::xml_node spacing = pPr.child("w:spacing");
    if (!spacing) {
        spacing = pPr.append_child("w:spacing");
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

    pugi::xml_node pPr = get_or_create_pPr(current_);

    pugi::xml_node sp = pPr.child("w:spacing");
    if (!sp) {
        sp = pPr.append_child("w:spacing");
    }

    sp.append_attribute("w:before").set_value(spacing);
    return true;
}

bool Paragraph::set_spacing_after(int spacing) {
    if (!current_) {
        return false;
    }

    pugi::xml_node pPr = get_or_create_pPr(current_);

    pugi::xml_node sp = pPr.child("w:spacing");
    if (!sp) {
        sp = pPr.append_child("w:spacing");
    }

    sp.append_attribute("w:after").set_value(spacing);
    return true;
}

bool Paragraph::set_indent(int left, int right, int first_line) {
    if (!current_) {
        return false;
    }

    pugi::xml_node pPr = get_or_create_pPr(current_);

    // Get or create indentation element
    pugi::xml_node ind = pPr.child("w:ind");
    if (!ind) {
        ind = pPr.append_child("w:ind");
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
        pugi::xml_node t = run.append_child("w:t");
        t.text().set("");
    }
    return run;
}

bool Paragraph::set_color(const std::string& color_hex) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_color(run, color_hex);
}

bool Paragraph::set_font_size(int size) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_font_size(run, size);
}

bool Paragraph::set_font_name(const std::string& font_name) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_font_name(run, font_name);
}

bool Paragraph::set_bold(bool bold) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_bold(run, bold);
}

bool Paragraph::set_italic(bool italic) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_italic(run, italic);
}

bool Paragraph::set_underline(bool underline) {
    if (!current_) {
        return false;
    }
    pugi::xml_node run = get_or_create_first_run(current_);
    return TextFormatContext::apply_underline(run, underline);
}

// ============================================================================
// List/Numbering Support (v0.5.0)
// ============================================================================

bool Paragraph::set_numbering(NumberingId numId, NumberingLevel level) {
    // Always update the DOM list_format_ so sync_to_physical_tree() preserves it.
    list_format_.list_id = numId;
    list_format_.level = level;

    // If this paragraph is backed by physical XML, update it as well.
    if (!current_) {
        return true;
    }

    pugi::xml_node pPr = get_or_create_pPr(current_);

    // Remove existing numPr if any
    pugi::xml_node existing_numPr = pPr.child("w:numPr");
    if (existing_numPr) {
        pPr.remove_child(existing_numPr);
    }

    // Create numPr element
    pugi::xml_node numPr = pPr.append_child("w:numPr");

    // Add ilvl (level)
    pugi::xml_node ilvl = numPr.append_child("w:ilvl");
    ilvl.append_attribute("w:val").set_value(numbering_level_to_int(level));

    // Add numId
    pugi::xml_node numId_node = numPr.append_child("w:numId");
    numId_node.append_attribute("w:val").set_value(static_cast<unsigned int>(numId));

    return true;
}

bool Paragraph::remove_numbering() {
    // Always clear the DOM list_format_.
    bool had_dom_numbering = list_format_.is_list_item();
    list_format_.remove_list_format();

    if (!current_) {
        return had_dom_numbering;
    }

    pugi::xml_node pPr = current_.child("w:pPr");
    if (!pPr) {
        return had_dom_numbering;
    }

    pugi::xml_node numPr = pPr.child("w:numPr");
    if (!numPr) {
        return had_dom_numbering;
    }

    return pPr.remove_child(numPr);
}

bool Paragraph::has_numbering() const {
    // Prefer DOM state over physical XML.
    if (list_format_.is_list_item()) {
        return true;
    }

    if (!current_) {
        return false;
    }

    pugi::xml_node pPr = current_.child("w:pPr");
    if (!pPr) {
        return false;
    }

    return pPr.child("w:numPr") != nullptr;
}

NumberingId Paragraph::get_numbering_id() const {
    // Prefer DOM state over physical XML.
    if (list_format_.is_list_item()) {
        return list_format_.list_id;
    }

    if (!current_) {
        return 0;
    }

    pugi::xml_node pPr = current_.child("w:pPr");
    if (!pPr) {
        return 0;
    }

    pugi::xml_node numPr = pPr.child("w:numPr");
    if (!numPr) {
        return 0;
    }

    pugi::xml_node numId = numPr.child("w:numId");
    if (!numId) {
        return 0;
    }

    return numId.attribute("w:val").as_uint();
}

NumberingLevel Paragraph::get_numbering_level() const {
    // Prefer DOM state over physical XML.
    if (list_format_.is_list_item()) {
        return list_format_.level;
    }

    if (!current_) {
        return NumberingLevel::Level1;
    }

    pugi::xml_node pPr = current_.child("w:pPr");
    if (!pPr) {
        return NumberingLevel::Level1;
    }

    pugi::xml_node numPr = pPr.child("w:numPr");
    if (!numPr) {
        return NumberingLevel::Level1;
    }

    pugi::xml_node ilvl = numPr.child("w:ilvl");
    if (!ilvl) {
        return NumberingLevel::Level1;
    }

    int level = ilvl.attribute("w:val").as_int();
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

    pugi::xml_node pPr = current_.child("w:pPr");
    if (!pPr) {
        return list_format_.is_list_item();
    }

    pugi::xml_node numPr = pPr.child("w:numPr");
    if (!numPr) {
        return list_format_.is_list_item();
    }

    pugi::xml_node ilvl = numPr.child("w:ilvl");
    if (!ilvl) {
        ilvl = numPr.prepend_child("w:ilvl");
    }

    ilvl.attribute("w:val").set_value(numbering_level_to_int(level));
    return true;
}

bool Paragraph::increase_list_level() {
    int current_level = numbering_level_to_int(get_numbering_level());
    if (current_level < 8) {
        return set_list_level(static_cast<NumberingLevel>(current_level + 1));
    }
    return false;
}

bool Paragraph::decrease_list_level() {
    int current_level = numbering_level_to_int(get_numbering_level());
    if (current_level > 0) {
        return set_list_level(static_cast<NumberingLevel>(current_level - 1));
    }
    return false;
}

Paragraph& Paragraph::set_properties(const ParagraphProperties& props) {
    props.applyTo(*this);
    return *this;
}

Paragraph& Paragraph::set_outline_level(cdocx::ParagraphProperties::OutlineLevel level) {
    using OL = cdocx::ParagraphProperties::OutlineLevel;
    switch (level) {
        case OL::Level1:
            format_.outline_level = OutlineLevel::Level1;
            break;
        case OL::Level2:
            format_.outline_level = OutlineLevel::Level2;
            break;
        case OL::Level3:
            format_.outline_level = OutlineLevel::Level3;
            break;
        case OL::Level4:
            format_.outline_level = OutlineLevel::Level4;
            break;
        case OL::Level5:
            format_.outline_level = OutlineLevel::Level5;
            break;
        case OL::Level6:
            format_.outline_level = OutlineLevel::Level6;
            break;
        case OL::Level7:
            format_.outline_level = OutlineLevel::Level7;
            break;
        case OL::Level8:
            format_.outline_level = OutlineLevel::Level8;
            break;
        case OL::Level9:
            format_.outline_level = OutlineLevel::Level9;
            break;
        default:
            format_.outline_level = OutlineLevel::BodyText;
            break;
    }
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

}  // namespace cdocx
