/**
 * @file base_content.cpp
 * @brief Implementation of base content classes (Run, SpecialChar, Field, etc.)
 * @version 0.7.0 - DOM Style
 */

#include <cdocx/base.h>
#include <cdocx/document.h>
#include <cdocx/paragraph.h>

namespace cdocx {

// ============================================================================
// Run DOM Implementation
// ============================================================================

Run::Run() = default;

Run::Run(Document* doc) {
    set_document(doc);
}

Run::Run(Document* doc, const std::string& text) : text_(text) {
    set_document(doc);
}

Run::Run(const Run& other)
    : Inline(other),
      text_(other.text_),
      parent_xml_(other.parent_xml_),
      current_xml_(other.current_xml_) {
    for (auto child = other.preserved_children_.first_child(); child; child = child.next_sibling()) {
        preserved_children_.append_copy(child);
    }
}

Run& Run::operator=(const Run& other) {
    if (this != &other) {
        Inline::operator=(other);
        text_ = other.text_;
        parent_xml_ = other.parent_xml_;
        current_xml_ = other.current_xml_;
        preserved_children_.reset();
        for (auto child = other.preserved_children_.first_child(); child; child = child.next_sibling()) {
            preserved_children_.append_copy(child);
        }
    }
    return *this;
}

Run& Run::set_properties(const TextProperties& props) {
    props.applyTo(*this);
    return *this;
}

Run& Run::set_underline_style(TextProperties::UnderlineStyle style, const std::string& color) {
    // Stub: map to basic underline for now
    switch (style) {
        case TextProperties::UnderlineStyle::None:
            set_underline(UnderlineType::None);
            break;
        case TextProperties::UnderlineStyle::Single:
        case TextProperties::UnderlineStyle::Words:
            set_underline(UnderlineType::Single);
            break;
        case TextProperties::UnderlineStyle::Double:
            set_underline(UnderlineType::Double);
            break;
        default:
            set_underline(UnderlineType::Single);
            break;
    }
    if (!color.empty() && color != "auto") {
        font_.color = Color(color);
    }
    return *this;
}

Run& Run::set_spacing(TextProperties::SpacingType type, int value) {
    // Stub implementation
    (void)type;
    (void)value;
    return *this;
}

Run& Run::set_position(TextProperties::PositionType type, int value) {
    (void)value;
    switch (type) {
        case TextProperties::PositionType::Raised:
            set_superscript();
            break;
        case TextProperties::PositionType::Lowered:
            set_subscript();
            break;
        default:
            font_.script_type = ScriptType::Normal;
            break;
    }
    return *this;
}

Run& Run::set_scale(int percent) {
    (void)percent;
    return *this;
}

Run& Run::set_strike(TextProperties::StrikeStyle style) {
    set_strikethrough(style != TextProperties::StrikeStyle::None);
    return *this;
}

Run& Run::set_highlight(TextProperties::Highlight color) {
    switch (color) {
        case TextProperties::Highlight::Yellow: font_.highlight = HighlightColor::Yellow; break;
        case TextProperties::Highlight::Green: font_.highlight = HighlightColor::Green; break;
        case TextProperties::Highlight::Cyan: font_.highlight = HighlightColor::Turquoise; break;
        case TextProperties::Highlight::Magenta: font_.highlight = HighlightColor::Pink; break;
        case TextProperties::Highlight::Blue: font_.highlight = HighlightColor::Blue; break;
        case TextProperties::Highlight::Red: font_.highlight = HighlightColor::Red; break;
        case TextProperties::Highlight::Black: font_.highlight = HighlightColor::Black; break;
        case TextProperties::Highlight::White: font_.highlight = HighlightColor::White; break;
        case TextProperties::Highlight::DarkRed: font_.highlight = HighlightColor::DarkRed; break;
        case TextProperties::Highlight::DarkGreen: font_.highlight = HighlightColor::BrightGreen; break;
        case TextProperties::Highlight::DarkBlue: font_.highlight = HighlightColor::DarkBlue; break;
        case TextProperties::Highlight::DarkYellow: font_.highlight = HighlightColor::DarkYellow; break;
        case TextProperties::Highlight::DarkCyan: font_.highlight = HighlightColor::Teal; break;
        case TextProperties::Highlight::DarkMagenta: font_.highlight = HighlightColor::Violet; break;
        case TextProperties::Highlight::DarkGray: font_.highlight = HighlightColor::Gray50; break;
        case TextProperties::Highlight::LightGray: font_.highlight = HighlightColor::Gray25; break;
        default: font_.highlight = HighlightColor::None; break;
    }
    return *this;
}

void Run::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_run(*this);
    }
}

std::shared_ptr<Node> Run::clone(bool deep) const {
    auto cloned = std::make_shared<Run>(get_document(), text_);
    cloned->font_ = font_;
    if (preserved_children_.first_child()) {
        for (auto child = preserved_children_.first_child(); child; child = child.next_sibling()) {
            cloned->preserved_children_.append_copy(child);
        }
    }
    return cloned;
}

void Run::preserve_child(pugi::xml_node child) {
    if (child) {
        preserved_children_.append_copy(child);
    }
}

void Run::serialize_preserved_children(pugi::xml_node run_xml) const {
    for (auto child = preserved_children_.first_child(); child; child = child.next_sibling()) {
        run_xml.append_copy(child);
    }
}

bool Run::has_preserved_children() const {
    return preserved_children_.first_child() != nullptr;
}

// ============================================================================
// Run Legacy Implementation (XML-based)
// ============================================================================

Run::Run(pugi::xml_node parent, pugi::xml_node current)
    : parent_xml_(parent), current_xml_(current) {}

void Run::set_parent_xml(pugi::xml_node node) {
    parent_xml_ = node;
    current_xml_ = parent_xml_.child("w:r");
}

void Run::set_current_xml(pugi::xml_node node) {
    current_xml_ = node;
}

Run& Run::next() {
    current_xml_ = current_xml_.next_sibling("w:r");
    return *this;
}

bool Run::has_next() const {
    return current_xml_ != nullptr;
}

std::string Run::get_text_xml() const {
    if (!current_xml_) return "";
    return current_xml_.child("w:t").text().get();
}

bool Run::set_text_xml(const std::string& text) const {
    if (!current_xml_) return false;
    return current_xml_.child("w:t").text().set(text.c_str());
}

namespace {
    pugi::xml_node EnsureRPr(pugi::xml_node current_xml) {
        auto rPr = current_xml.child("w:rPr");
        if (!rPr) {
            // Insert after any w:rPr element? Just prepend before w:t or other children
            rPr = current_xml.prepend_child("w:rPr");
        }
        return rPr;
    }
}  // namespace

bool Run::set_color_xml(const std::string& color_hex) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (color_hex.empty() || color_hex == "auto") {
        rPr.remove_child("w:color");
        return true;
    }
    auto color = rPr.child("w:color");
    if (!color) color = rPr.append_child("w:color");
    color.append_attribute("w:val").set_value(color_hex.c_str());
    return true;
}

bool Run::set_font_size_xml(int size) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (size <= 0) {
        rPr.remove_child("w:sz");
        rPr.remove_child("w:szCs");
        return true;
    }
    auto sz = rPr.child("w:sz");
    if (!sz) sz = rPr.append_child("w:sz");
    sz.append_attribute("w:val").set_value(size);
    auto szCs = rPr.child("w:szCs");
    if (!szCs) szCs = rPr.append_child("w:szCs");
    szCs.append_attribute("w:val").set_value(size);
    return true;
}

bool Run::set_font_name_xml(const std::string& font_name) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (font_name.empty()) {
        rPr.remove_child("w:rFonts");
        return true;
    }
    auto fonts = rPr.child("w:rFonts");
    if (!fonts) fonts = rPr.append_child("w:rFonts");
    fonts.append_attribute("w:ascii").set_value(font_name.c_str());
    fonts.append_attribute("w:hAnsi").set_value(font_name.c_str());
    fonts.append_attribute("w:cs").set_value(font_name.c_str());
    fonts.append_attribute("w:eastAsia").set_value(font_name.c_str());
    return true;
}

bool Run::set_bold_xml(bool bold) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (bold) {
        if (!rPr.child("w:b")) rPr.append_child("w:b");
    } else {
        rPr.remove_child("w:b");
    }
    return true;
}

bool Run::set_italic_xml(bool italic) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (italic) {
        if (!rPr.child("w:i")) rPr.append_child("w:i");
    } else {
        rPr.remove_child("w:i");
    }
    return true;
}

bool Run::set_underline_xml(bool underline) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (underline) {
        auto u = rPr.child("w:u");
        if (!u) u = rPr.append_child("w:u");
        u.append_attribute("w:val").set_value("single");
    } else {
        rPr.remove_child("w:u");
    }
    return true;
}

void Run::set_properties_xml(const TextProperties& props) {
    // TODO: Implement
}

TextProperties Run::get_properties_xml() const {
    // TODO: Implement
    return TextProperties();
}

bool Run::set_highlight_xml(TextProperties::Highlight color) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (color == TextProperties::Highlight::None) {
        rPr.remove_child("w:highlight");
        return true;
    }
    const char* val = "yellow";
    switch (color) {
        case TextProperties::Highlight::Black:       val = "black"; break;
        case TextProperties::Highlight::Blue:        val = "blue"; break;
        case TextProperties::Highlight::Cyan:        val = "cyan"; break;
        case TextProperties::Highlight::Green:       val = "green"; break;
        case TextProperties::Highlight::Magenta:     val = "magenta"; break;
        case TextProperties::Highlight::Red:         val = "red"; break;
        case TextProperties::Highlight::Yellow:      val = "yellow"; break;
        case TextProperties::Highlight::White:       val = "white"; break;
        case TextProperties::Highlight::DarkBlue:    val = "darkBlue"; break;
        case TextProperties::Highlight::DarkCyan:    val = "darkCyan"; break;
        case TextProperties::Highlight::DarkGreen:   val = "darkGreen"; break;
        case TextProperties::Highlight::DarkMagenta: val = "darkMagenta"; break;
        case TextProperties::Highlight::DarkRed:     val = "darkRed"; break;
        case TextProperties::Highlight::DarkYellow:  val = "darkYellow"; break;
        case TextProperties::Highlight::DarkGray:    val = "darkGray"; break;
        case TextProperties::Highlight::LightGray:   val = "lightGray"; break;
        default: break;
    }
    auto hl = rPr.child("w:highlight");
    if (!hl) hl = rPr.append_child("w:highlight");
    hl.append_attribute("w:val").set_value(val);
    return true;
}

bool Run::set_underline_style_xml(TextProperties::UnderlineStyle style,
                                   const std::string& color) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (style == TextProperties::UnderlineStyle::None) {
        rPr.remove_child("w:u");
        return true;
    }
    const char* val = "single";
    switch (style) {
        case TextProperties::UnderlineStyle::Words:       val = "words"; break;
        case TextProperties::UnderlineStyle::Single:      val = "single"; break;
        case TextProperties::UnderlineStyle::Double:      val = "double"; break;
        case TextProperties::UnderlineStyle::Thick:       val = "thick"; break;
        case TextProperties::UnderlineStyle::Dotted:      val = "dotted"; break;
        case TextProperties::UnderlineStyle::DottedHeavy: val = "dottedHeavy"; break;
        case TextProperties::UnderlineStyle::Dash:        val = "dash"; break;
        case TextProperties::UnderlineStyle::DashedHeavy: val = "dashedHeavy"; break;
        case TextProperties::UnderlineStyle::DashLong:    val = "dashLong"; break;
        case TextProperties::UnderlineStyle::DashLongHeavy: val = "dashLongHeavy"; break;
        case TextProperties::UnderlineStyle::DotDash:     val = "dotDash"; break;
        case TextProperties::UnderlineStyle::DashDotHeavy: val = "dashDotHeavy"; break;
        case TextProperties::UnderlineStyle::DotDotDash:  val = "dotDotDash"; break;
        case TextProperties::UnderlineStyle::DashDotDotHeavy: val = "dashDotDotHeavy"; break;
        case TextProperties::UnderlineStyle::Wave:        val = "wave"; break;
        case TextProperties::UnderlineStyle::WavyDouble:  val = "wavyDouble"; break;
        case TextProperties::UnderlineStyle::WavyHeavy:   val = "wavyHeavy"; break;
        default: break;
    }
    auto u = rPr.child("w:u");
    if (!u) u = rPr.append_child("w:u");
    u.append_attribute("w:val").set_value(val);
    if (!color.empty() && color != "auto") {
        u.append_attribute("w:color").set_value(color.c_str());
    }
    return true;
}

bool Run::set_strike_xml(TextProperties::StrikeStyle style) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    rPr.remove_child("w:strike");
    rPr.remove_child("w:dstrike");
    if (style == TextProperties::StrikeStyle::Single) {
        rPr.append_child("w:strike");
    } else if (style == TextProperties::StrikeStyle::Double) {
        rPr.append_child("w:dstrike");
    }
    return true;
}

bool Run::set_scale_xml(int percent) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (percent <= 0 || percent == 100) {
        rPr.remove_child("w:w");
        return true;
    }
    auto w = rPr.child("w:w");
    if (!w) w = rPr.append_child("w:w");
    w.append_attribute("w:val").set_value(percent);
    return true;
}

bool Run::set_spacing_xml(TextProperties::SpacingType type, int value) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (type == TextProperties::SpacingType::Normal || value == 0) {
        rPr.remove_child("w:spacing");
        return true;
    }
    auto sp = rPr.child("w:spacing");
    if (!sp) sp = rPr.append_child("w:spacing");
    int val = (type == TextProperties::SpacingType::Expanded) ? value : -value;
    sp.append_attribute("w:val").set_value(val);
    return true;
}

bool Run::set_position_xml(TextProperties::PositionType type, int value) {
    if (!current_xml_) return false;
    auto rPr = EnsureRPr(current_xml_);
    if (type == TextProperties::PositionType::Normal) {
        rPr.remove_child("w:vertAlign");
        rPr.remove_child("w:position");
        return true;
    }
    const char* valign = (type == TextProperties::PositionType::Raised)
                             ? "superscript"
                             : "subscript";
    auto va = rPr.child("w:vertAlign");
    if (!va) va = rPr.append_child("w:vertAlign");
    va.append_attribute("w:val").set_value(valign);
    if (value != 0) {
        auto pos = rPr.child("w:position");
        if (!pos) pos = rPr.append_child("w:position");
        int val = (type == TextProperties::PositionType::Raised) ? value : -value;
        pos.append_attribute("w:val").set_value(val);
    } else {
        rPr.remove_child("w:position");
    }
    return true;
}

// ============================================================================
// RunCollection Implementation
// ============================================================================

void RunCollection::add(const std::shared_ptr<Run>& run) {
    if (run) {
        runs_.push_back(run);
    }
}

void RunCollection::remove(const std::shared_ptr<Run>& run) {
    if (!run) return;
    for (auto it = runs_.begin(); it != runs_.end(); ++it) {
        if (*it == run) {
            runs_.erase(it);
            return;
        }
    }
}

void RunCollection::remove_at(int index) {
    if (index >= 0 && static_cast<size_t>(index) < runs_.size()) {
        runs_.erase(runs_.begin() + index);
    }
}

void RunCollection::clear() {
    runs_.clear();
}

// get_item, first, last are inline in base.h

std::string RunCollection::get_text() const {
    std::string result;
    for (const auto& run : runs_) {
        if (run) {
            result += run->get_text();
        }
    }
    return result;
}

// ============================================================================
// SpecialChar Implementation
// ============================================================================

SpecialChar::SpecialChar() = default;

SpecialChar::SpecialChar(char16_t char_code) : char_code_(char_code) {}

std::string SpecialChar::get_text() const {
    // Convert char16_t to UTF-8 string
    std::string result;
    if (char_code_ <= 0x7F) {
        result += static_cast<char>(char_code_);
    } else if (char_code_ <= 0x7FF) {
        result += static_cast<char>(0xC0 | ((char_code_ >> 6) & 0x1F));
        result += static_cast<char>(0x80 | (char_code_ & 0x3F));
    } else {
        result += static_cast<char>(0xE0 | ((char_code_ >> 12) & 0x0F));
        result += static_cast<char>(0x80 | ((char_code_ >> 6) & 0x3F));
        result += static_cast<char>(0x80 | (char_code_ & 0x3F));
    }
    return result;
}

void SpecialChar::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_special_char(*this);
    }
}

std::shared_ptr<Node> SpecialChar::clone(bool deep) const {
    return std::make_shared<SpecialChar>(char_code_);
}

std::shared_ptr<SpecialChar> SpecialChar::paragraph_break() {
    return std::make_shared<SpecialChar>(0x000D);  // CR
}

std::shared_ptr<SpecialChar> SpecialChar::line_break() {
    return std::make_shared<SpecialChar>(0x000A);  // LF
}

std::shared_ptr<SpecialChar> SpecialChar::page_break() {
    return std::make_shared<SpecialChar>(0x000C);  // Form feed
}

std::shared_ptr<SpecialChar> SpecialChar::column_break() {
    return std::make_shared<SpecialChar>(0x000E);  // SO
}

std::shared_ptr<SpecialChar> SpecialChar::tab() {
    return std::make_shared<SpecialChar>(0x0009);  // Tab
}

// ============================================================================
// Field Implementation
// ============================================================================

Field::Field() = default;

Field::Field(FieldType type) : type_(type) {}

Field::Field(Document* doc, FieldType type) : type_(type) {
    set_document(doc);
}

void Field::update() {
    // Subclasses implement
}

void Field::unlink() {
    // Replace field with its result
    result_ = get_text();
}

void Field::accept(DocumentVisitor* visitor) {
    if (!visitor) return;
    if (visitor->visit_field_start(*this) == VisitorAction::Continue) {
        visitor->visit_field_end(*this);
    }
}

std::shared_ptr<Node> Field::clone(bool deep) const {
    auto cloned = std::make_shared<Field>(get_document(), type_);
    cloned->field_code_ = field_code_;
    cloned->result_ = result_;
    cloned->is_locked_ = is_locked_;
    cloned->is_dirty_ = is_dirty_;
    return cloned;
}

// ============================================================================
// BookmarkStart Implementation
// ============================================================================

BookmarkStart::BookmarkStart() = default;

BookmarkStart::BookmarkStart(const std::string& name, int id) 
    : name_(name), id_(id) {}

BookmarkStart::BookmarkStart(Document* doc) {
    set_document(doc);
}

void BookmarkStart::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_bookmark_start(*this);
    }
}

std::shared_ptr<Node> BookmarkStart::clone(bool deep) const {
    return std::make_shared<BookmarkStart>(name_, id_);
}

// ============================================================================
// BookmarkEnd Implementation
// ============================================================================

BookmarkEnd::BookmarkEnd() = default;

BookmarkEnd::BookmarkEnd(int id) : id_(id) {}

BookmarkEnd::BookmarkEnd(Document* doc) {
    set_document(doc);
}

void BookmarkEnd::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_bookmark_end(*this);
    }
}

std::shared_ptr<Node> BookmarkEnd::clone(bool deep) const {
    return std::make_shared<BookmarkEnd>(id_);
}

// ============================================================================
// Hyperlink Implementation
// ============================================================================

Hyperlink::Hyperlink() = default;

Hyperlink::Hyperlink(Document* doc) {
    set_document(doc);
}

void Hyperlink::set_address(const std::string& url) {
    address_ = url;
    bookmark_name_.clear();
}

void Hyperlink::set_bookmark_name(const std::string& name) {
    bookmark_name_ = name;
    address_.clear();
}

void Hyperlink::set_tooltip(const std::string& tooltip) {
    tooltip_ = tooltip;
}

void Hyperlink::set_screen_tip(const std::string& tip) {
    screen_tip_ = tip;
}

std::string Hyperlink::get_address() const {
    return address_;
}

std::string Hyperlink::get_bookmark_name() const {
    return bookmark_name_;
}

std::string Hyperlink::get_tooltip() const {
    return tooltip_;
}

std::string Hyperlink::get_screen_tip() const {
    return screen_tip_;
}

std::shared_ptr<Node> Hyperlink::clone(bool deep) const {
    auto cloned = std::make_shared<Hyperlink>(get_document());
    cloned->set_field_code(get_field_code());
    cloned->set_result(get_result());
    cloned->set_locked(is_locked());
    cloned->set_dirty(is_dirty());
    cloned->address_ = address_;
    cloned->bookmark_name_ = bookmark_name_;
    cloned->tooltip_ = tooltip_;
    cloned->screen_tip_ = screen_tip_;
    cloned->get_font() = get_font();
    return cloned;
}

void Hyperlink::accept(DocumentVisitor* visitor) {
    if (visitor) {
        visitor->visit_field_start(*this);
    }
}

void Hyperlink::update() {
    // Subclasses can override for dynamic updates
}

} // namespace cdocx
