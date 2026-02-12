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
    Footnote,
    Endnote,
    SpecialChar,
    GroupShape
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
// Style
// ============================================================================

enum class StyleIdentifier {
    Normal,
    Heading1,
    Heading2,
    Heading3,
    Heading4,
    Heading5,
    Heading6,
    Heading7,
    Heading8,
    Heading9,
    Title,
    Subtitle,
    Quote,
    IntenseQuote,
    Caption,
    ListParagraph,
    NoList,
    TableNormal,
    TableGrid
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
