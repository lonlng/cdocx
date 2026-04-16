/**
 * @file enums.h
 * @brief Enumerations for CDocx library
 * @details Defines all enum types used throughout the library
 */

#pragma once

#include <cstdint>

namespace cdocx {

// ============================================================================
// Node Types
// ============================================================================

enum class NodeType {
    Unknown,
    Document,
    Section,
    Body,
    HeaderFooter,
    Header,       ///< Header content
    Footer,       ///< Footer content
    Paragraph,
    Run,
    Table,
    Row,
    Cell,
    BookmarkStart,
    BookmarkEnd,
    FieldStart,
    FieldSeparator,
    FieldEnd,
    Picture,
    Shape,
    Comment,
    CommentRangeStart,
    CommentRangeEnd,
    Footnote,
    Endnote,
    FootnoteReference,
    EndnoteReference,
    FormField,
    SpecialChar,
    GroupShape,
    Hyperlink
};

// ============================================================================
// Paragraph Formatting
// ============================================================================

enum class ParagraphAlignment {
    Left,
    Center,
    Right,
    Justify,
    Distributed
};

enum class LineSpacingRule {
    Auto,       // Multiple line spacing
    Exact,      // Exact points
    AtLeast     // Minimum points
};

enum class OutlineLevel {
    Level1 = 0,
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

enum class DropCapPosition {
    None,
    Normal,
    Margin
};

// ============================================================================
// Font Formatting
// ============================================================================

enum class UnderlineType {
    None,
    Single,
    Words,
    Double,
    Dotted,
    Dash,
    DashDot,
    DashDotDot,
    Wave,
    Thick,
    DottedHeavy,
    DashHeavy,
    DashDotHeavy,
    DashDotDotHeavy,
    WaveHeavy
};

enum class StrikeType {
    None,
    Single,
    Double
};

enum class ScriptType {
    Normal,
    Superscript,
    Subscript
};

enum class HighlightColor {
    None,
    Black,
    Blue,
    BrightGreen,
    DarkBlue,
    DarkRed,
    DarkYellow,
    Gray25,
    Gray50,
    Green,
    Pink,
    Red,
    Teal,
    Turquoise,
    Violet,
    White,
    Yellow
};

// ============================================================================
// Table Formatting
// ============================================================================

enum class TableAlignment {
    Left,
    Center,
    Right
};

enum class AutoFitBehavior {
    AutoFitToContents,
    AutoFitToWindow,
    FixedColumnWidth
};

enum class TextWrapping {
    None,
    Around
};

enum class CellVerticalAlignment {
    Top,
    Center,
    Bottom
};

// ============================================================================
// Border
// ============================================================================

enum class BorderType {
    None,
    Single,
    Thick,
    Double,
    Dotted,
    Dashed,
    DotDash,
    DotDotDash,
    Triple,
    ThinThickSmall,
    ThickThinSmall,
    ThinThickThinSmall,
    ThinThickMedium,
    ThickThinMedium,
    ThinThickThinMedium,
    ThinThickLarge,
    ThickThinLarge,
    ThinThickThinLarge,
    Wave,
    DoubleWave,
    DashSmall,
    DashDotStroked,
    ThreeDEmboss,
    ThreeDEngrave,
    Outset,
    Inset,
    Clear
};

// ============================================================================
// Break Types
// ============================================================================

enum class BreakType {
    ParagraphBreak,
    PageBreak,
    ColumnBreak,
    LineBreak,
    SectionBreakNextPage,
    SectionBreakContinuous,
    SectionBreakEvenPage,
    SectionBreakOddPage
};

// ============================================================================
// Page Setup
// ============================================================================

enum class PageOrientation {
    Portrait,
    Landscape
};

enum class HeightRule {
    Auto,
    AtLeast,
    Exact
};

// ============================================================================
// Header/Footer Types
// ============================================================================

enum class HeaderFooterType {
    Primary,        // Default header/footer
    FirstPage,      // First page only
    EvenPages,       // Even pages only    
    Default,    ///< Default header/footer
    First,      ///< First page only
    Even        ///< Even pages only
};

// ============================================================================
// Footnote Types
// ============================================================================

enum class FootnoteType : std::uint8_t {
    Footnote = 0,
    Endnote = 1
};

// ============================================================================
// Field Types
// ============================================================================

enum class FieldType {
    Unknown,
    Page,
    NumPages,
    Date,
    Time,
    CreateDate,
    SaveDate,
    Author,
    Title,
    Subject,
    Keywords,
    FileName,
    FileSize,
    NumWords,
    NumChars,
    Hyperlink,
    Ref,
    PageRef,
    Formula,
    MergeField
};

// ============================================================================
// Form Field Types
// ============================================================================

enum class FormFieldType : std::uint8_t {
    TextInput,
    CheckBox,
    ComboBox
};

enum class TextFormFieldType : std::uint8_t {
    Regular,
    Number,
    Date,
    CurrentDate,
    CurrentTime,
    Calculated
};

// ============================================================================
// Style
// ============================================================================

enum class StyleType {
    Paragraph = 1,
    Character = 2,
    Table = 3,
    List = 4
};

enum class StyleIdentifier {
    Normal = 0,
    Heading1 = 1,
    Heading2 = 2,
    Heading3 = 3,
    Heading4 = 4,
    Heading5 = 5,
    Heading6 = 6,
    Heading7 = 7,
    Heading8 = 8,
    Heading9 = 9,
    Index1 = 10,
    Index2 = 11,
    Index3 = 12,
    Index4 = 13,
    Index5 = 14,
    Index6 = 15,
    Index7 = 16,
    Index8 = 17,
    Index9 = 18,
    Toc1 = 19,
    Toc2 = 20,
    Toc3 = 21,
    Toc4 = 22,
    Toc5 = 23,
    Toc6 = 24,
    Toc7 = 25,
    Toc8 = 26,
    Toc9 = 27,
    NormalIndent = 28,
    FootnoteText = 29,
    CommentText = 30,
    Header = 31,
    Footer = 32,
    IndexHeading = 33,
    Caption = 34,
    TableOfFigures = 35,
    EnvelopeAddress = 36,
    EnvelopeReturn = 37,
    FootnoteReference = 38,
    CommentReference = 39,
    LineNumber = 40,
    PageNumber = 41,
    EndnoteReference = 42,
    EndnoteText = 43,
    TableOfAuthorities = 44,
    Macro = 45,
    ToaHeading = 46,
    List = 47,
    ListBullet = 48,
    ListNumber = 49,
    List2 = 50,
    List3 = 51,
    List4 = 52,
    List5 = 53,
    ListBullet2 = 54,
    ListBullet3 = 55,
    ListBullet4 = 56,
    ListBullet5 = 57,
    ListNumber2 = 58,
    ListNumber3 = 59,
    ListNumber4 = 60,
    ListNumber5 = 61,
    Title = 62,
    Closing = 63,
    Signature = 64,
    DefaultParagraphFont = 65,
    BodyText = 66,
    BodyTextInd = 67,
    ListContinue = 68,
    ListContinue2 = 69,
    ListContinue3 = 70,
    ListContinue4 = 71,
    ListContinue5 = 72,
    MessageHeader = 73,
    Subtitle = 74,
    Salutation = 75,
    Date = 76,
    BodyText1I = 77,
    BodyText1I2 = 78,
    NoteHeading = 79,
    BodyText2 = 80,
    BodyText3 = 81,
    BodyTextInd2 = 82,
    BodyTextInd3 = 83,
    BlockText = 84,
    Hyperlink = 85,
    FollowedHyperlink = 86,
    Strong = 87,
    Emphasis = 88,
    DocumentMap = 89,
    PlainText = 90,
    EmailSignature = 91,
    HtmlTopOfForm = 92,
    HtmlBottomOfForm = 93,
    NormalWeb = 94,
    HtmlAcronym = 95,
    HtmlAddress = 96,
    HtmlCite = 97,
    HtmlCode = 98,
    HtmlDefinition = 99,
    HtmlKeyboard = 100,
    HtmlPreformatted = 101,
    HtmlSample = 102,
    HtmlTypewriter = 103,
    HtmlVariable = 104,
    TableNormal = 105,
    NoList = 107,
    OutlineList1 = 108,
    OutlineList2 = 109,
    OutlineList3 = 110,
    TableSimple1 = 111,
    TableSimple2 = 112,
    TableSimple3 = 113,
    TableClassic1 = 114,
    TableClassic2 = 115,
    TableClassic3 = 116,
    TableClassic4 = 117,
    TableColorful1 = 118,
    TableColorful2 = 119,
    TableColorful3 = 120,
    TableColumns1 = 121,
    TableColumns2 = 122,
    TableColumns3 = 123,
    TableColumns4 = 124,
    TableColumns5 = 125,
    TableGrid1 = 126,
    TableGrid2 = 127,
    TableGrid3 = 128,
    TableGrid4 = 129,
    TableGrid5 = 130,
    TableGrid6 = 131,
    TableGrid7 = 132,
    TableGrid8 = 133,
    TableList1 = 134,
    TableList2 = 135,
    TableList3 = 136,
    TableList4 = 137,
    TableList5 = 138,
    TableList6 = 139,
    TableList7 = 140,
    TableList8 = 141,
    Table3DEffects1 = 142,
    Table3DEffects2 = 143,
    Table3DEffects3 = 144,
    TableContemporary = 145,
    TableElegant = 146,
    TableProfessional = 147,
    TableSubtle1 = 148,
    TableSubtle2 = 149,
    TableWeb1 = 150,
    TableWeb2 = 151,
    TableWeb3 = 152,
    BalloonText = 153,
    TableGrid = 154,
    TableTheme = 155,
    PlaceholderText = 156,
    NoSpacing = 157,
    Revision = 178,
    ListParagraph = 179,
    Quote = 180,
    IntenseQuote = 181,
    SubtleEmphasis = 260,
    IntenseEmphasis = 261,
    SubtleReference = 262,
    IntenseReference = 263,
    BookTitle = 264,
    Bibliography = 265,
    TocHeading = 266,
    PlainTable1 = 267,
    PlainTable2 = 268,
    PlainTable3 = 269,
    PlainTable4 = 270,
    PlainTable5 = 271,
    TableGridLight = 272,
    GridTable1Light = 273,
    GridTable2 = 274,
    GridTable3 = 275,
    GridTable4 = 276,
    GridTable5Dark = 277,
    GridTable6Colorful = 278,
    GridTable7Colorful = 279,
    GridTable1LightAccent1 = 280,
    GridTable2Accent1 = 281,
    GridTable3Accent1 = 282,
    GridTable4Accent1 = 283,
    GridTable5DarkAccent1 = 284,
    GridTable6ColorfulAccent1 = 285,
    GridTable7ColorfulAccent1 = 286,
    GridTable1LightAccent2 = 287,
    GridTable2Accent2 = 288,
    GridTable3Accent2 = 289,
    GridTable4Accent2 = 290,
    GridTable5DarkAccent2 = 291,
    GridTable6ColorfulAccent2 = 292,
    GridTable7ColorfulAccent2 = 293,
    GridTable1LightAccent3 = 294,
    GridTable2Accent3 = 295,
    GridTable3Accent3 = 296,
    GridTable4Accent3 = 297,
    GridTable5DarkAccent3 = 298,
    GridTable6ColorfulAccent3 = 299,
    GridTable7ColorfulAccent3 = 300,
    GridTable1LightAccent4 = 301,
    GridTable2Accent4 = 302,
    GridTable3Accent4 = 303,
    GridTable4Accent4 = 304,
    GridTable5DarkAccent4 = 305,
    GridTable6ColorfulAccent4 = 306,
    GridTable7ColorfulAccent4 = 307,
    GridTable1LightAccent5 = 308,
    GridTable2Accent5 = 309,
    GridTable3Accent5 = 310,
    GridTable4Accent5 = 311,
    GridTable5DarkAccent5 = 312,
    GridTable6ColorfulAccent5 = 313,
    GridTable7ColorfulAccent5 = 314,
    GridTable1LightAccent6 = 315,
    GridTable2Accent6 = 316,
    GridTable3Accent6 = 317,
    GridTable4Accent6 = 318,
    GridTable5DarkAccent6 = 319,
    GridTable6ColorfulAccent6 = 320,
    GridTable7ColorfulAccent6 = 321,
    ListTable1Light = 322,
    ListTable2 = 323,
    ListTable3 = 324,
    ListTable4 = 325,
    ListTable5Dark = 326,
    ListTable6Colorful = 327,
    ListTable7Colorful = 328,
    ListTable1LightAccent1 = 329,
    ListTable2Accent1 = 330,
    ListTable3Accent1 = 331,
    ListTable4Accent1 = 332,
    ListTable5DarkAccent1 = 333,
    ListTable6ColorfulAccent1 = 334,
    ListTable7ColorfulAccent1 = 335,
    ListTable1LightAccent2 = 336,
    ListTable2Accent2 = 337,
    ListTable3Accent2 = 338,
    ListTable4Accent2 = 339,
    ListTable5DarkAccent2 = 340,
    ListTable6ColorfulAccent2 = 341,
    ListTable7ColorfulAccent2 = 342,
    ListTable1LightAccent3 = 343,
    ListTable2Accent3 = 344,
    ListTable3Accent3 = 345,
    ListTable4Accent3 = 346,
    ListTable5DarkAccent3 = 347,
    ListTable6ColorfulAccent3 = 348,
    ListTable7ColorfulAccent3 = 349,
    ListTable1LightAccent4 = 350,
    ListTable2Accent4 = 351,
    ListTable3Accent4 = 352,
    ListTable4Accent4 = 353,
    ListTable5DarkAccent4 = 354,
    ListTable6ColorfulAccent4 = 355,
    ListTable7ColorfulAccent4 = 356,
    ListTable1LightAccent5 = 357,
    ListTable2Accent5 = 358,
    ListTable3Accent5 = 359,
    ListTable4Accent5 = 360,
    ListTable5DarkAccent5 = 361,
    ListTable6ColorfulAccent5 = 362,
    ListTable7ColorfulAccent5 = 363,
    ListTable1LightAccent6 = 364,
    ListTable2Accent6 = 365,
    ListTable3Accent6 = 366,
    ListTable4Accent6 = 367,
    ListTable5DarkAccent6 = 368,
    ListTable6ColorfulAccent6 = 369,
    ListTable7ColorfulAccent6 = 370,
    Mention = 372,
    SmartHyperlink = 373,
    Hashtag = 374,
    UnresolvedMention = 375,
    User = 0x0FFE,
    Nil = 0x2FFF
};

// ============================================================================
// Tab Stops
// ============================================================================

enum class TabAlignment : std::uint8_t {
    Left,       // Left-aligns text after the tab stop
    Center,     // Centers text around the tab stop
    Right,      // Right-aligns text at the tab stop
    Decimal,    // Aligns text at the decimal dot
    Bar,        // Draws a vertical bar at the tab stop position
    List,       // Delimiter between number/bullet and text
    Clear       // Clears any tab stop in this position
};

enum class TabLeader : std::uint8_t {
    None,       // No leader line
    Dots,       // Dots
    Dashes,     // Dashes
    Line,       // Single line
    Heavy,      // Thick line
    MiddleDot   // Middle dots
};

// ============================================================================
// File Format
// ============================================================================

enum class LoadFormat : std::uint8_t {
    Auto = 0,
    Docx = 20,
    Docm = 21,
    Dotx = 22,
    Dotm = 23,
    FlatOpc = 24,
    Rtf = 30,
    Html = 50,
    Odt = 60,
    Text = 62,
    Markdown = 63,
    Xml = 65,
    Unknown = 255
};

enum class SaveFormat : std::uint8_t {
    Auto = 0,
    Docx = 20,
    Docm = 21,
    Dotx = 22,
    Dotm = 23,
    FlatOpc = 24,
    Rtf = 30,
    Html = 50,
    Odt = 60,
    Text = 62,
    Markdown = 63,
    Xml = 65,
    Unknown = 255
};

// ============================================================================
// Visitor Action
// ============================================================================

enum class VisitorAction {
    Continue,       // Continue visiting
    Skip,           // Skip this node's children
    Stop            // Stop visiting completely
};

} // namespace cdocx
