/**
 * @file properties.h
 * @brief Text and paragraph properties structures (inspired by minidocx)
 * @details Provides property structures for text formatting and paragraph formatting,
 *          allowing more flexible and comprehensive document styling.
 *
 * @since 0.4.0
 * @author CDocx Team
 * @copyright MIT License
 */

#pragma once

#include <cdocx/enums.h>
#include <cdocx/fwd.h>

#include <ctime>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace cdocx {

// ============================================================================
// Text Properties (RichText Properties)
// ============================================================================

/**
 * @struct TextProperties
 * @brief Comprehensive text formatting properties
 * @details Inspired by minidocx, provides detailed control over text appearance.
 *          All properties are optional - unset properties will not be applied.
 *
 * @par Usage Example:
 * @code
 * TextProperties props;
 * props.font = TextProperties::Font{"Arial", "SimHei"};
 * props.fontSize = 24;  // 12pt
 * props.color = "FF0000";
 * props.highlight = TextProperties::Highlight::Yellow;
 *
 * run.setProperties(props);
 * @endcode
 */
struct TextProperties {
    // ------------------------------------------------------------------------
    // Font Settings
    // ------------------------------------------------------------------------

    /**
     * @struct Font
     * @brief Font family settings for different character sets
     */
    struct Font {
        std::string ascii = "Times New Roman";  ///< Western font
        std::string eastAsia = "SimSun";        ///< CJK font (中文)
        std::string hAnsi = "Times New Roman";  ///< High ANSI font
        std::string cs = "Times New Roman";     ///< Complex script font

        /**
         * @enum Hint
         * @brief Font type hint for ambiguous characters
         */
        enum class Hint {
            Default,       ///< No hint
            EastAsia,      ///< Prefer East Asian font
            ComplexScript  ///< Prefer complex script font
        };
        Hint hint = Hint::Default;

        Font() = default;
        Font(const std::string& ascii_font, const std::string& east_asian_font)
            : ascii(ascii_font), eastAsia(east_asian_font), hAnsi(ascii_font), cs(ascii_font) {}
    };
    std::optional<Font> font;

    // ------------------------------------------------------------------------
    // Font Style (Bold, Italic)
    // ------------------------------------------------------------------------

    struct FontStyle {
        bool bold = false;
        bool italic = false;
    } fontStyle;

    // ------------------------------------------------------------------------
    // Font Size (in half-points: 24 = 12pt)
    // ------------------------------------------------------------------------
    int fontSize = 0;  ///< 0 = not set

    // ------------------------------------------------------------------------
    // Font Color (RRGGBB or "auto")
    // ------------------------------------------------------------------------
    std::string color;

    // ------------------------------------------------------------------------
    // Underline Styles
    // ------------------------------------------------------------------------

    /**
     * @enum UnderlineStyle
     * @brief Comprehensive underline style options
     */
    enum class UnderlineStyle {
        None,
        Words,            ///< Underline words only
        Single,           ///< 单实线
        Double,           ///< 双实线
        Thick,            ///< 粗单实线
        Dotted,           ///< 点虚线
        DottedHeavy,      ///< 粗点虚线
        Dash,             ///< 短划线
        DashedHeavy,      ///< 粗短划线
        DashLong,         ///< 长划线
        DashLongHeavy,    ///< 粗长划线
        DotDash,          ///< 点划线
        DashDotHeavy,     ///< 粗点划线
        DotDotDash,       ///< 点点划线
        DashDotDotHeavy,  ///< 粗点点划线
        Wave,             ///< 波浪线
        WavyDouble,       ///< 双波浪线
        WavyHeavy         ///< 粗波浪线
    };

    struct Underline {
        UnderlineStyle style = UnderlineStyle::None;
        std::string color = "auto";  ///< RRGGBB or "auto"
    } underline;

    // ------------------------------------------------------------------------
    // Strikethrough Styles
    // ------------------------------------------------------------------------

    enum class StrikeStyle {
        None,
        Single,  ///< 删除线
        Double   ///< 双删除线
    } strike = StrikeStyle::None;

    // ------------------------------------------------------------------------
    // Vertical Alignment (Superscript/Subscript)
    // ------------------------------------------------------------------------

    enum class VertAlign {
        None,
        Superscript,  ///< 上标
        Subscript     ///< 下标
    } vertAlign = VertAlign::None;

    // ------------------------------------------------------------------------
    // Highlight Colors
    // ------------------------------------------------------------------------

    /**
     * @enum Highlight
     * @brief Text highlighting color options
     */
    enum class Highlight {
        None,
        Black,
        White,
        Red,
        Green,
        Blue,
        Yellow,
        Cyan,
        Magenta,
        DarkRed,
        DarkGreen,
        DarkBlue,
        DarkYellow,
        DarkCyan,
        DarkMagenta,
        DarkGray,
        LightGray
    } highlight = Highlight::None;

    // ------------------------------------------------------------------------
    // Character Scale (1-600, 100 = normal)
    // ------------------------------------------------------------------------
    int scale = 100;

    // ------------------------------------------------------------------------
    // Character Spacing
    // ------------------------------------------------------------------------

    enum class SpacingType {
        Normal,    ///< No adjustment
        Expanded,  ///< 加宽
        Condensed  ///< 紧缩
    };

    struct Spacing {
        SpacingType type = SpacingType::Normal;
        int value = 20;  ///< 20 = 1pt
    } spacing;

    // ------------------------------------------------------------------------
    // Position (Raised/Lowered)
    // ------------------------------------------------------------------------

    enum class PositionType {
        Normal,  ///< Standard position
        Raised,  ///< 上升
        Lowered  ///< 下降
    };

    struct Position {
        PositionType type = PositionType::Normal;
        int value = 2;  ///< 2 = 1pt
    } position;

    // ------------------------------------------------------------------------
    // Methods
    // ------------------------------------------------------------------------

    /**
     * @brief Apply these properties to a Run
     * @param[in,out] run The run to apply properties to
     */
    void applyTo(Run& run) const;

    /**
     * @brief Apply these properties directly to an XML node
     * @param[in,out] run_node The w:r XML node
     */
    void applyTo(pugi::xml_node run_node) const;

    /**
     * @brief Extract properties from a Run
     * @param[in] run The run to extract from
     * @return TextProperties containing the extracted values
     */
    static TextProperties extractFrom(const Run& run);

    /**
     * @brief Extract properties from an XML node
     * @param[in] run_node The w:r XML node
     * @return TextProperties containing the extracted values
     */
    static TextProperties extractFrom(pugi::xml_node run_node);
};

// ============================================================================
// Tab Stop
// ============================================================================

/**
 * @struct TabStop
 * @brief Represents a single custom tab stop
 * @details A tab stop specifies a position where a tab stop exists.
 *          Can also be used to clear inherited tab stops by setting
 *          alignment to TabAlignment::Clear.
 */
struct TabStop {
    double position = 0;  ///< Position in points
    TabAlignment alignment = TabAlignment::Left;
    TabLeader leader = TabLeader::None;

    TabStop() = default;
    explicit TabStop(double pos) : position(pos) {}
    TabStop(double pos, TabAlignment align, TabLeader lead = TabLeader::None)
        : position(pos), alignment(align), leader(lead) {}

    bool operator==(const TabStop& other) const {
        return position == other.position && alignment == other.alignment && leader == other.leader;
    }
    bool operator!=(const TabStop& other) const { return !(*this == other); }
};

/**
 * @class TabStopCollection
 * @brief Collection of TabStop objects
 * @details Represents custom tabs for a paragraph or style.
 */
class TabStopCollection {
  public:
    TabStopCollection() = default;

    void add(const TabStop& tab_stop);
    void add(double position, TabAlignment alignment, TabLeader leader = TabLeader::None);

    void remove(double position);
    void remove_at(size_t index);
    void clear();

    size_t count() const { return tab_stops_.size(); }
    bool empty() const { return tab_stops_.empty(); }

    const TabStop& at(size_t index) const { return tab_stops_.at(index); }
    TabStop& at(size_t index) { return tab_stops_.at(index); }

    const TabStop* get(double position) const;
    bool contains(double position) const;

    std::vector<TabStop>::const_iterator begin() const { return tab_stops_.begin(); }
    std::vector<TabStop>::const_iterator end() const { return tab_stops_.end(); }
    std::vector<TabStop>::iterator begin() { return tab_stops_.begin(); }
    std::vector<TabStop>::iterator end() { return tab_stops_.end(); }

    void applyTo(pugi::xml_node para_node) const;
    static TabStopCollection extractFrom(pugi::xml_node para_node);

  private:
    std::vector<TabStop> tab_stops_;
};

// ============================================================================
// Paragraph Properties
// ============================================================================

/**
 * @struct ParagraphProperties
 * @brief Comprehensive paragraph formatting properties
 * @details Provides detailed control over paragraph layout and appearance.
 *
 * @par Usage Example:
 * @code
 * ParagraphProperties props;
 * props.align = ParagraphProperties::Alignment::Centered;
 * props.outlineLevel = ParagraphProperties::OutlineLevel::Level1;
 *
 * ParagraphProperties::Indentation indent;
 * indent.special.kind = ParagraphProperties::Indentation::Special::Kind::FirstLine;
 * indent.special.value = 200;  // 2 characters
 * props.indent = indent;
 *
 * para.setProperties(props);
 * @endcode
 */
struct ParagraphProperties {
    // ------------------------------------------------------------------------
    // Style ID
    // ------------------------------------------------------------------------
    std::string styleId;

    // ------------------------------------------------------------------------
    // Alignment
    // ------------------------------------------------------------------------

    enum class Alignment {
        Left,
        Centered,
        Right,
        Justified,
        Distributed
    };
    std::optional<Alignment> align;

    // ------------------------------------------------------------------------
    // Outline Level (for table of contents)
    // ------------------------------------------------------------------------

    enum class OutlineLevel {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5,
        Level6,
        Level7,
        Level8,
        Level9,
        BodyText
    };
    OutlineLevel outlineLevel = OutlineLevel::BodyText;

    // ------------------------------------------------------------------------
    // Indentation
    // ------------------------------------------------------------------------

    struct Indentation {
        enum class Type {
            Character,  ///< 100 = 1 character
            Absolute    ///< 1440 = 1 inch = 72 points
        };

        struct Indent {
            Type type = Type::Absolute;
            int value = 0;
        };
        Indent left;
        Indent right;

        struct Special {
            enum class Kind {
                None,
                FirstLine,  ///< 首行缩进
                Hanging     ///< 悬挂缩进
            };
            Kind kind = Kind::None;
            Type type = Type::Character;
            int value = 0;
        } special;
    };
    std::optional<Indentation> indent;

    // ------------------------------------------------------------------------
    // Spacing
    // ------------------------------------------------------------------------

    struct Spacing {
        enum class Type {
            Auto,     ///< Automatically determined
            Lines,    ///< 100 = 1 line
            Absolute  ///< 1440 = 1 inch
        };

        struct ParaSpacing {
            Type type = Type::Auto;
            int value = 0;
        };
        ParaSpacing before;  ///< Space before paragraph
        ParaSpacing after;   ///< Space after paragraph

        enum class LineSpacingType {
            Lines,    ///< 240 = 1 line
            AtLeast,  ///< Minimum line spacing
            Exactly   ///< Exact line spacing
        };

        struct LineSpacing {
            LineSpacingType type = LineSpacingType::Lines;
            int value = 240;  ///< 240 = 1 line (single spacing)
        } lineSpacing;
    };
    std::optional<Spacing> spacing;

    // ------------------------------------------------------------------------
    // Page Break Control
    // ------------------------------------------------------------------------

    bool keepNext = false;         ///< Keep with next paragraph (与下段同页)
    bool keepLines = false;        ///< Keep lines together (段中不分页)
    bool pageBreakBefore = false;  ///< Page break before (段前分页)
    bool pageBreakAfter = false;   ///< Page break after (段后分页)

    // ------------------------------------------------------------------------
    // Paragraph Borders
    // ------------------------------------------------------------------------

    struct Border {
        enum class Style {
            None,
            Single,
            Double,
            Thick,
            Dotted,
            Dash,
            DotDash,
            Wave
        };
        Style style = Style::None;
        int size = 4;  ///< 1/8 point, 4 = 1/2 point
        std::string color = "auto";
        int space = 1;  ///< Space between border and content (points)
    };

    struct Borders {
        std::optional<Border> top;
        std::optional<Border> left;
        std::optional<Border> bottom;
        std::optional<Border> right;
    };
    std::optional<Borders> borders;

    // ------------------------------------------------------------------------
    // Tab Stops
    // ------------------------------------------------------------------------
    std::optional<TabStopCollection> tab_stops;

    // ------------------------------------------------------------------------
    // Methods
    // ------------------------------------------------------------------------

    /**
     * @brief Apply these properties to a Paragraph
     * @param[in,out] para The paragraph to apply properties to
     */
    void applyTo(Paragraph& para) const;

    /**
     * @brief Apply these properties directly to an XML node
     * @param[in,out] para_node The w:p XML node
     */
    void applyTo(pugi::xml_node para_node) const;

    /**
     * @brief Extract properties from a Paragraph
     * @param[in] para The paragraph to extract from
     * @return ParagraphProperties containing the extracted values
     */
    static ParagraphProperties extractFrom(const Paragraph& para);

    /**
     * @brief Extract properties from an XML node
     * @param[in] para_node The w:p XML node
     * @return ParagraphProperties containing the extracted values
     */
    static ParagraphProperties extractFrom(pugi::xml_node para_node);
};

// ============================================================================
// Table Properties
// ============================================================================

/**
 * @struct TableProperties
 * @brief Table formatting properties
 * @since 0.4.0
 */
struct TableProperties {
    // ------------------------------------------------------------------------
    // Table Width
    // ------------------------------------------------------------------------

    enum class WidthType {
        Auto,     ///< Auto width
        Percent,  ///< Percentage (5000 = 100%)
        Absolute  ///< Absolute width (twips, 1440 = 1 inch)
    };

    struct Width {
        WidthType type = WidthType::Auto;
        int value = 0;
    } width;

    // ------------------------------------------------------------------------
    // Table Alignment
    // ------------------------------------------------------------------------
    ParagraphProperties::Alignment alignment = ParagraphProperties::Alignment::Left;

    // ------------------------------------------------------------------------
    // Table Borders
    // ------------------------------------------------------------------------
    ParagraphProperties::Borders borders;

    // ------------------------------------------------------------------------
    // Cell Margins (internal cell padding)
    // ------------------------------------------------------------------------
    struct CellMargin {
        int top = 0;     ///< twips
        int left = 0;    ///< twips
        int bottom = 0;  ///< twips
        int right = 0;   ///< twips
    } cellMargin;

    // ------------------------------------------------------------------------
    // Methods
    // ------------------------------------------------------------------------

    /**
     * @brief Apply these properties to a Table
     * @param[in,out] table The table to apply properties to
     */
    void applyTo(Table& table) const;

    /**
     * @brief Apply these properties directly to an XML node
     * @param[in,out] tbl_node The w:tbl XML node
     */
    void applyTo(pugi::xml_node tbl_node) const;
};

// ============================================================================
// Section Properties
// ============================================================================

/**
 * @struct SectionProperties
 * @brief Section (page) formatting properties
 * @since 0.4.0
 */
struct SectionProperties {
    // ------------------------------------------------------------------------
    // Page Size
    // ------------------------------------------------------------------------

    struct PageSize {
        int width = 12240;   ///< A4 width in twips (8.5 inch)
        int height = 15840;  ///< A4 height in twips (11 inch)
    } pageSize;

    // ------------------------------------------------------------------------
    // Page Orientation
    // ------------------------------------------------------------------------

    enum class Orientation {
        Portrait,
        Landscape
    } orientation = Orientation::Portrait;

    // ------------------------------------------------------------------------
    // Page Margins
    // ------------------------------------------------------------------------

    struct PageMargins {
        int top = 1440;     ///< 1 inch
        int right = 1440;   ///< 1 inch
        int bottom = 1440;  ///< 1 inch
        int left = 1440;    ///< 1 inch
        int header = 720;   ///< 0.5 inch
        int footer = 720;   ///< 0.5 inch
    } pageMargins;

    // ------------------------------------------------------------------------
    // Columns (for multi-column layout)
    // ------------------------------------------------------------------------

    struct Columns {
        int count = 1;           ///< Number of columns
        int space = 720;         ///< Space between columns (twips, 720 = 0.5 inch)
        bool separator = false;  ///< Show separator line
    } columns;

    // ------------------------------------------------------------------------
    // Methods
    // ------------------------------------------------------------------------

    /**
     * @brief Apply these properties to a section XML node
     * @param[in,out] sectPr_node The w:sectPr XML node
     */
    void applyTo(pugi::xml_node sectPr_node) const;
};

// ============================================================================
// Document Properties
// ============================================================================

/**
 * @class DocumentProperties
 * @brief Document properties (builtin and custom)
 * @details Manages document metadata properties like title, author, etc.
 */
class DocumentProperties {
  public:
    // Standard builtin properties
    std::string title;
    std::string subject;
    std::string author;
    std::string manager;
    std::string company;
    std::string category;
    std::string keywords;
    std::string comments;
    std::string template_name;
    std::string revision;
    std::string content_type;
    std::string content_status;

    // Date/time properties
    std::time_t created = 0;
    std::time_t modified = 0;
    std::time_t last_printed = 0;

    // Statistics (read-only from file)
    int total_pages = 0;
    int total_words = 0;
    int total_chars = 0;
    int total_chars_with_spaces = 0;
    int total_lines = 0;
    int total_paragraphs = 0;

    // Custom properties storage (string only for simplicity)
    std::map<std::string, std::string> custom_properties;

    // Methods
    DocumentProperties() = default;

    // Custom property access
    void set_custom(const std::string& name, const std::string& value) {
        custom_properties[name] = value;
    }

    bool has_custom(const std::string& name) const {
        return custom_properties.find(name) != custom_properties.end();
    }

    std::string get_custom(const std::string& name) const {
        auto it = custom_properties.find(name);
        if (it != custom_properties.end()) {
            return it->second;
        }
        return "";
    }

    void remove_custom(const std::string& name) { custom_properties.erase(name); }

    void clear_custom() { custom_properties.clear(); }
};

}  // namespace cdocx
