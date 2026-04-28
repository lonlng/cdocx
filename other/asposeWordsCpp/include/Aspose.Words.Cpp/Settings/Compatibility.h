//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/Compatibility.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies names of compatibility options.
enum class ASPOSE_WORDS_SHARED_CLASS Compatibility
{
    /// No Tab Hang Indent
    NoTabHangInd,
    /// No Space Raise Lower
    NoSpaceRaiseLower,
    /// Suppress Space Before Paragraph Break
    SuppressSpBfAfterPgBrk,
    /// Wrap Trailing Spaces
    WrapTrailSpaces,
    /// Print Column Background
    PrintColBlack,
    /// No Column Balancing
    NoColumnBalance,
    /// Convert Mail Merge Escapes
    ConvMailMergeEsc,
    /// Suppress Top Spacing
    SuppressTopSpacing,
    /// Use Single Border for Contiguous Cells
    UseSingleBorderforContiguousCells,
    /// Transparent Metafiles
    TransparentMetafiles,
    /// Show Breaks in Frames
    ShowBreaksInFrames,
    /// Swap Borders on Odd-Facing Pages
    SwapBordersOddFacingPgs,
    /// Do Not Leave Backslash Alone
    DoNotLeaveBackslashAlone,
    /// Do Not Expand on Shift Return
    DoNotExpandOnShiftReturn,
    /// Underline Trailing Space
    UlTrailSpace,
    /// Balance Single-Byte and Double-Byte Widths
    BalanceSingleByteDoubleByteWidth,
    /// Suppress Top Line Spacing in WordPerfect
    SuppressTopSpacingAtTopOfPage,
    /// Spacing in Whole Points
    SpacingInWholePoints,
    /// Print Body Text Before Header
    PrintBodyTextBeforeHeader,
    /// No Leading
    NoLeading,
    /// Space for Underline
    SpaceForUL,
    /// MW Small Caps
    MWSmallCaps,
    /// Suppress Top Line Spacing in WordPerfect
    SuppressTopLineSpacingWP,
    /// Truncate Font Height Like WordPerfect 6
    TruncateFontHeightLikeWP6,
    /// Substitute Font by Size
    SubFontBySize,
    /// Line Wrap Like Word 6
    LineWrapLikeWord6,
    /// Do Not Suppress Paragraph Border
    DoNotSuppressParagraphBorder,
    /// No Extra Line Spacing
    NoExtraLineSpacing,
    /// Suppress Bottom Spacing
    SuppressBottomSpacing,
    /// WordPerfect Space Width
    WPSpaceWidth,
    /// WordPerfect Justification
    WPJustification,
    /// Use Printer Metrics
    UsePrinterMetrics,
    /// Shape Layout Like Word 2000
    ShapeLayoutLikeWW8,
    /// Footnote Layout Like Word 2000
    FootnoteLayoutLikeWW8,
    /// Do Not Use HTML Paragraph Auto Spacing
    DoNotUseHtmlParagraphAutoSpacing,
    /// Adjust Line Height in Table
    AdjustLineHeightInTable,
    /// Forget Last Tab Alignment
    ForgetLastTabAlignment,
    /// Auto Space Like Word 95
    AutoSpaceLikeWord95,
    /// Align Table Rows by Rule
    AlignTableRowByRow,
    /// Layout Raw Table Width
    LayoutRawTableWidth,
    /// Layout Table Rows Apart
    LayoutTableRowsApart,
    /// Use Word 97 Line Break Rules
    UseWord97LineBreakRules,
    /// Do Not Break Wrapped Tables
    DoNotBreakWrappedTables,
    /// Do Not Snap to Grid in Cells
    doNotSnapToGridInCell,
    /// Select Field with First or Last Character
    SelectFldWithFirstOrLastChar,
    /// Apply Breaking Rules
    ApplyBreakingRules,
    /// Do Not Wrap Text with Punctuation
    DoNotWrapTextWithPunct,
    /// Do Not Use East Asian Break Rules
    DoNotUseEastAsianBreakRules,
    /// Use Word 2002 Table Style Rules
    UseWord2002TableStyleRules,
    /// Grow AutoFit
    GrowAutofit,
    /// Use Normal Style for List
    UseNormalStyleForList,
    /// Do Not Use Indent as Numbering Tab Stop
    DoNotUseIndentAsNumberingTabStop,
    /// Use Alt Kinsoku Line Break Rules
    UseAltKinsokuLineBreakRules,
    /// Allow Space of Same Style in Table
    AllowSpaceOfSameStyleInTable,
    /// Do Not Suppress Indentation
    DoNotSuppressIndentation,
    /// Do Not AutoFit Constrained Tables
    DoNotAutofitConstrainedTables,
    /// AutoFit to First Fixed-Width Cell
    AutofitToFirstFixedWidthCell,
    /// Underline Tab in Numbered List
    UnderlineTabInNumList,
    /// Display Hangul Fixed Width
    DisplayHangulFixedWidth,
    /// Split Page Break and Paragraph Mark
    SplitPgBreakAndParaMark,
    /// Do Not Vertically Align Cell with Spacing
    DoNotVertAlignCellWithSp,
    /// Do Not Break Constrained Forced Tables
    DoNotBreakConstrainedForcedTable,
    /// Do Not Vertically Align in Textboxes
    DoNotVertAlignInTxbx,
    /// Use ANSI Kerning Pairs
    UseAnsiKerningPairs,
    /// Cached Column Balancing
    CachedColBalance,
    /// Use Far East Layout
    UseFELayout,
    /// User Interface Compatibility Mode from Word 97 to Word 2003
    UICompat97To2003,
    /// Override Table Style Font Size and Justification
    OverrideTableStyleFontSizeAndJustification,
    /// Disable OpenType Font Formatting Features
    DisableOpenTypeFontFormattingFeatures,
    /// Swap Inside and Outside for Mirror Indents and Relative Positioning
    SwapInsideAndOutsideForMirrorIndentsAndRelativePositioning,
    /// Use Word 2010 Table Style Rules
    UseWord2010TableStyleRules
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::Compatibility>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::Compatibility, const char_t*>, 71>& values();
};
