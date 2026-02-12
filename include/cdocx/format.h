/**
 * @file format.h
 * @brief Formatting properties for CDocx
 * @details Defines paragraph, font, table, and cell format classes
 */

#pragma once

#include <cdocx/enums.h>
#include <string>
#include <optional>

namespace cdocx {

// ============================================================================
// Color Class
// ============================================================================

class Color {
public:
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;  // Alpha, default opaque
    
    Color() = default;
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
    
    // Static factory methods
    static Color from_hex(const std::string& hex);
    static Color from_rgb(uint8_t r, uint8_t g, uint8_t b) { 
        return Color(r, g, b); 
    }
    
    // Predefined colors
    static Color transparent() { return Color(0, 0, 0, 0); }
    static Color black() { return Color(0, 0, 0); }
    static Color white() { return Color(255, 255, 255); }
    static Color red() { return Color(255, 0, 0); }
    static Color green() { return Color(0, 255, 0); }
    static Color blue() { return Color(0, 0, 255); }
    static Color yellow() { return Color(255, 255, 0); }
    static Color cyan() { return Color(0, 255, 255); }
    static Color magenta() { return Color(255, 0, 255); }
    static Color gray() { return Color(128, 128, 128); }
    static Color light_gray() { return Color(192, 192, 192); }
    static Color dark_gray() { return Color(64, 64, 64); }
    
    // Convert to hex string
    std::string to_hex() const;
    std::string to_hex_rgb() const;  // Without alpha
    
    // Check if automatic color
    bool is_auto() const { return a == 0; }
    void set_auto() { a = 0; }
    
    // Static method for auto color (used as default parameter)
    static Color auto_color() { 
        Color c;
        c.a = 0;
        return c;
    }
    
    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool operator!=(const Color& other) const { return !(*this == other); }
};

// ============================================================================
// Border Class
// ============================================================================

class Border {
public:
    BorderType type = BorderType::None;
    Color color = Color::black();
    double width = 0.5;  // points
    double space = 0;    // points
    bool shadow = false;
    
    Border() = default;
    Border(BorderType t, const Color& c, double w = 0.5) 
        : type(t), color(c), width(w) {}
    
    // Predefined borders
    static Border none() { return Border(BorderType::None, Color::black(), 0); }
    static Border single(const Color& c = Color::black(), double w = 0.5) {
        return Border(BorderType::Single, c, w);
    }
    static Border double_border(const Color& c = Color::black(), double w = 0.5) {
        return Border(BorderType::Double, c, w);
    }
    static Border dotted(const Color& c = Color::black(), double w = 0.5) {
        return Border(BorderType::Dotted, c, w);
    }
    static Border dashed(const Color& c = Color::black(), double w = 0.5) {
        return Border(BorderType::Dashed, c, w);
    }
    
    bool is_visible() const { return type != BorderType::None; }
    void clear() { type = BorderType::None; }
};

// ============================================================================
// Borders Collection
// ============================================================================

class Borders {
public:
    Border top;
    Border left;
    Border bottom;
    Border right;
    Border inside_horizontal;
    Border inside_vertical;
    
    // Set all borders to the same style
    void set_all(const Border& border) {
        top = left = bottom = right = inside_horizontal = inside_vertical = border;
    }
    
    // Set outside borders only
    void set_outside(const Border& border) {
        top = left = bottom = right = border;
    }
    
    // Set inside borders only
    void set_inside(const Border& border) {
        inside_horizontal = inside_vertical = border;
    }
    
    // Clear all borders
    void clear() {
        top.clear();
        left.clear();
        bottom.clear();
        right.clear();
        inside_horizontal.clear();
        inside_vertical.clear();
    }
    
    // Check if any border is visible
    bool has_visible() const {
        return top.is_visible() || left.is_visible() || 
               bottom.is_visible() || right.is_visible() ||
               inside_horizontal.is_visible() || inside_vertical.is_visible();
    }
};

// ============================================================================
// Shading Class
// ============================================================================

class Shading {
public:
    Color foreground = Color::auto_color();
    Color background = Color::auto_color();
    std::string texture = "clear";  // e.g., "clear", "solid", "pct5", etc.
    
    Shading() = default;
    
    // Quick set solid fill
    void set_solid_fill(const Color& color) {
        background = color;
        texture = "clear";
    }
    
    // Quick set pattern
    void set_pattern(const std::string& tex, const Color& fore, const Color& back) {
        texture = tex;
        foreground = fore;
        background = back;
    }
    
    bool has_fill() const {
        return !background.is_auto();
    }
    
    void clear() {
        foreground = Color::auto_color();
        background = Color::auto_color();
        texture = "clear";
    }
};

// ============================================================================
// ParagraphFormat Class
// ============================================================================

class ParagraphFormat {
public:
    // Alignment
    ParagraphAlignment alignment = ParagraphAlignment::Left;
    
    // Indentation (in points)
    double left_indent = 0;
    double right_indent = 0;
    double first_line_indent = 0;  // Positive = indent, negative = hanging
    
    // Spacing (in points)
    double space_before = 0;
    double space_after = 0;
    
    // Line spacing
    LineSpacingRule line_spacing_rule = LineSpacingRule::Auto;
    double line_spacing = 1.15;  // Multiple or points depending on rule
    
    // Pagination control
    bool keep_together = false;
    bool keep_with_next = false;
    bool page_break_before = false;
    bool widow_control = true;
    
    // Outline level
    OutlineLevel outline_level = OutlineLevel::BodyText;
    
    // Style name
    std::string style_name;
    
    // Borders
    Borders borders;
    
    // Shading
    Shading shading;
    
    // ------------------------------------------------------------------------
    // Convenience methods
    // ------------------------------------------------------------------------
    void set_indent(double left, double right = 0, double first_line = 0) {
        left_indent = left;
        right_indent = right;
        first_line_indent = first_line;
    }
    
    void set_spacing(double before, double after) {
        space_before = before;
        space_after = after;
    }
    
    void set_line_spacing(double spacing, LineSpacingRule rule = LineSpacingRule::Auto) {
        line_spacing = spacing;
        line_spacing_rule = rule;
    }
    
    // Chinese-style first line indent (2 characters = ~24 points)
    void set_first_line_indent_chars(int chars, double char_width = 12) {
        first_line_indent = chars * char_width;
    }
    
    bool has_borders() const { return borders.has_visible(); }
    bool has_shading() const { return shading.has_fill(); }
};

// ============================================================================
// Font Class
// ============================================================================

class Font {
public:
    // Font names
    std::string name = "Times New Roman";
    std::string name_ascii;
    std::string name_far_east = "宋体";
    std::string name_other;
    
    // Size (in points)
    double size = 12;
    
    // Color
    Color color = Color::black();
    
    // Formatting flags
    bool bold = false;
    bool italic = false;
    bool hidden = false;
    
    // Underline
    UnderlineType underline = UnderlineType::None;
    Color underline_color;
    
    // Strikethrough
    StrikeType strike = StrikeType::None;
    bool double_strike = false;
    bool strikethrough = false;  // Convenience flag for single strikethrough
    
    // Script position
    ScriptType script_type = ScriptType::Normal;
    
    // Highlight
    HighlightColor highlight = HighlightColor::None;
    
    // Character spacing (in points, 0 = normal)
    double spacing = 0;
    
    // Character scaling (percentage, 100 = normal)
    int scale = 100;
    
    // Kerning (minimum font size for kerning)
    double kerning = 0;
    
    // Small caps / All caps
    bool small_caps = false;
    bool all_caps = false;
    
    // ------------------------------------------------------------------------
    // Convenience methods
    // ------------------------------------------------------------------------
    void set_names(const std::string& ascii, const std::string& far_east = "") {
        name = ascii;
        name_ascii = ascii;
        if (!far_east.empty()) {
            name_far_east = far_east;
        }
    }
    
    void set_underline(UnderlineType type, const Color& color = Color::auto_color()) {
        underline = type;
        underline_color = color;
    }
    
    void clear_formatting() {
        bold = false;
        italic = false;
        underline = UnderlineType::None;
        strike = StrikeType::None;
        double_strike = false;
        script_type = ScriptType::Normal;
        small_caps = false;
        all_caps = false;
        hidden = false;
    }
};

// ============================================================================
// TableFormat Class
// ============================================================================

class TableFormat {
public:
    // Alignment
    TableAlignment alignment = TableAlignment::Left;
    
    // Indentation (in points)
    double left_indent = 0;
    
    // Auto fit
    bool allow_auto_fit = true;
    AutoFitBehavior auto_fit_behavior = AutoFitBehavior::AutoFitToContents;
    
    // Cell spacing (in points)
    double cell_spacing = 0;
    bool allow_cell_spacing = false;
    
    // Default cell padding (in points)
    double top_padding = 0;
    double bottom_padding = 0;
    double left_padding = 5.4;   // Default ~0.1 inch
    double right_padding = 5.4;
    
    // Borders
    Borders borders;
    
    // Shading
    Shading shading;
    
    // Text wrapping
    TextWrapping text_wrapping = TextWrapping::None;
    
    // BiDi (right-to-left)
    bool bidi = false;
    
    // Style
    std::string style_name;
    
    // ------------------------------------------------------------------------
    // Convenience methods
    // ------------------------------------------------------------------------
    void set_padding(double all) {
        top_padding = bottom_padding = left_padding = right_padding = all;
    }
    
    void set_padding(double top_bottom, double left_right) {
        top_padding = bottom_padding = top_bottom;
        left_padding = right_padding = left_right;
    }
    
    void set_padding(double top, double right, double bottom, double left) {
        top_padding = top;
        right_padding = right;
        bottom_padding = bottom;
        left_padding = left;
    }
};

// ============================================================================
// RowFormat Class
// ============================================================================

class RowFormat {
public:
    // Height (in points)
    double height = 0;
    bool height_rule_exact = false;  // true = exact, false = at least
    
    // Allow break across pages
    bool allow_break_across_pages = true;
    
    // Heading row (repeats on new page)
    bool heading = false;
    
    // Alignment (can override cell alignment)
    CellVerticalAlignment vertical_alignment = CellVerticalAlignment::Top;
};

// ============================================================================
// CellFormat Class
// ============================================================================

class CellFormat {
public:
    // Width (in points)
    double width = 0;
    bool preferred_width = false;
    
    // Vertical merge
    bool vertical_merge = false;
    bool vertical_merge_start = false;  // true = restart, false = continue
    
    // Horizontal merge (grid span)
    int horizontal_merge = 1;  // Number of cells spanned
    
    // Margins (in points, -1 = use table default)
    double top_margin = -1;
    double bottom_margin = -1;
    double left_margin = -1;
    double right_margin = -1;
    
    // Vertical alignment
    CellVerticalAlignment vertical_alignment = CellVerticalAlignment::Top;
    
    // Fit text
    bool fit_text = false;
    
    // Borders
    Borders borders;
    
    // Shading
    Shading shading;
    
    // ------------------------------------------------------------------------
    // Convenience methods
    // ------------------------------------------------------------------------
    void set_margins(double all) {
        top_margin = bottom_margin = left_margin = right_margin = all;
    }
    
    bool is_merged() const {
        return vertical_merge || horizontal_merge > 1;
    }
    
    bool is_vertical_merge_start() const {
        return vertical_merge && vertical_merge_start;
    }
    
    bool is_vertical_merge_continue() const {
        return vertical_merge && !vertical_merge_start;
    }
};

// ============================================================================
// PageSetup Class
// ============================================================================

class PageSetup {
public:
    // Page size (in points, 1 inch = 72 points)
    double page_width = 595.35;   // A4 width ~8.27 inch
    double page_height = 841.95;  // A4 height ~11.69 inch
    
    // Orientation
    enum class Orientation { Portrait, Landscape };
    Orientation orientation = Orientation::Portrait;
    
    // Margins (in points)
    double top_margin = 72;     // 1 inch
    double bottom_margin = 72;
    double left_margin = 72;
    double right_margin = 72;
    
    // Header/footer distance
    double header_distance = 36;  // 0.5 inch
    double footer_distance = 36;
    
    // Gutter
    double gutter = 0;
    
    // Multiple pages
    bool mirror_margins = false;
    bool two_pages_on_one = false;
    
    // Page borders
    Borders borders;
    
    // ------------------------------------------------------------------------
    // Convenience methods
    // ------------------------------------------------------------------------
    void set_margins(double all) {
        top_margin = bottom_margin = left_margin = right_margin = all;
    }
    
    void set_margins(double top_bottom, double left_right) {
        top_margin = bottom_margin = top_bottom;
        left_margin = right_margin = left_right;
    }
    
    void set_page_size(double width, double height) {
        page_width = width;
        page_height = height;
    }
    
    // Common page sizes
    void set_a4() {
        page_width = 595.35;
        page_height = 841.95;
    }
    
    void set_letter() {
        page_width = 612;   // 8.5 inch
        page_height = 792;  // 11 inch
    }
    
    void set_a3() {
        page_width = 841.95;
        page_height = 1190.55;
    }
};

} // namespace cdocx
