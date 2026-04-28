//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/CompatibilityOptions.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/Settings/MsWordVersion.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Contains compatibility options (that is, the user preferences entered on the <b>%Compatibility</b>
/// tab of the <b>%Options</b> dialog in %Microsoft Word).
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/detect-file-format-and-check-format-compatibility/">Detect File Format and Check Format Compatibility</a> documentation article.
/// 
/// @sa Aspose::Words::Document
/// @sa Aspose::Words::Document::get_CompatibilityOptions
class ASPOSE_WORDS_SHARED_CLASS CompatibilityOptions : public System::Object
{
    typedef CompatibilityOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Do Not Create Custom Tab Stop for Hanging Indent.
    ASPOSE_WORDS_SHARED_API bool get_NoTabHangInd();
    /// Do Not Create Custom Tab Stop for Hanging Indent.
    ASPOSE_WORDS_SHARED_API void set_NoTabHangInd(bool value);
    /// Do Not Increase Line Height for Raised/Lowered Text.
    ASPOSE_WORDS_SHARED_API bool get_NoSpaceRaiseLower();
    /// Do Not Increase Line Height for Raised/Lowered Text.
    ASPOSE_WORDS_SHARED_API void set_NoSpaceRaiseLower(bool value);
    /// Do Not Use Space Before On First Line After a Page Break.
    ASPOSE_WORDS_SHARED_API bool get_SuppressSpBfAfterPgBrk();
    /// Do Not Use Space Before On First Line After a Page Break.
    ASPOSE_WORDS_SHARED_API void set_SuppressSpBfAfterPgBrk(bool value);
    /// Line Wrap Trailing Spaces.
    ASPOSE_WORDS_SHARED_API bool get_WrapTrailSpaces();
    /// Line Wrap Trailing Spaces.
    ASPOSE_WORDS_SHARED_API void set_WrapTrailSpaces(bool value);
    /// Print Colors as Black And White without Dithering.
    ASPOSE_WORDS_SHARED_API bool get_PrintColBlack();
    /// Print Colors as Black And White without Dithering.
    ASPOSE_WORDS_SHARED_API void set_PrintColBlack(bool value);
    /// Do Not Balance Text Columns within a Section.
    ASPOSE_WORDS_SHARED_API bool get_NoColumnBalance();
    /// Do Not Balance Text Columns within a Section.
    ASPOSE_WORDS_SHARED_API void set_NoColumnBalance(bool value);
    /// Treat Backslash Quotation Delimiter as Two Quotation Marks.
    ASPOSE_WORDS_SHARED_API bool get_ConvMailMergeEsc();
    /// Treat Backslash Quotation Delimiter as Two Quotation Marks.
    ASPOSE_WORDS_SHARED_API void set_ConvMailMergeEsc(bool value);
    /// Ignore Minimum and Exact Line Height for First Line on Page.
    ASPOSE_WORDS_SHARED_API bool get_SuppressTopSpacing();
    /// Ignore Minimum and Exact Line Height for First Line on Page.
    ASPOSE_WORDS_SHARED_API void set_SuppressTopSpacing(bool value);
    /// Use Simplified Rules For Table Border Conflicts.
    ASPOSE_WORDS_SHARED_API bool get_UseSingleBorderforContiguousCells();
    /// Use Simplified Rules For Table Border Conflicts.
    ASPOSE_WORDS_SHARED_API void set_UseSingleBorderforContiguousCells(bool value);
    /// Specifies not to blank the area behind metafile pictures.
    ASPOSE_WORDS_SHARED_API bool get_TransparentMetafiles();
    /// Specifies not to blank the area behind metafile pictures.
    ASPOSE_WORDS_SHARED_API void set_TransparentMetafiles(bool value);
    /// Display Page/Column Breaks Present in Frames.
    ASPOSE_WORDS_SHARED_API bool get_ShowBreaksInFrames();
    /// Display Page/Column Breaks Present in Frames.
    ASPOSE_WORDS_SHARED_API void set_ShowBreaksInFrames(bool value);
    /// Swap Paragraph Borders on Odd Numbered Pages.
    ASPOSE_WORDS_SHARED_API bool get_SwapBordersFacingPgs();
    /// Swap Paragraph Borders on Odd Numbered Pages.
    ASPOSE_WORDS_SHARED_API void set_SwapBordersFacingPgs(bool value);
    /// Convert Backslash To Yen Sign When Entered.
    ASPOSE_WORDS_SHARED_API bool get_DoNotLeaveBackslashAlone();
    /// Convert Backslash To Yen Sign When Entered.
    ASPOSE_WORDS_SHARED_API void set_DoNotLeaveBackslashAlone(bool value);
    /// Don't Justify Lines Ending in Soft Line Break.
    ASPOSE_WORDS_SHARED_API bool get_DoNotExpandShiftReturn();
    /// Don't Justify Lines Ending in Soft Line Break.
    ASPOSE_WORDS_SHARED_API void set_DoNotExpandShiftReturn(bool value);
    /// Underline All Trailing Spaces.
    ASPOSE_WORDS_SHARED_API bool get_UlTrailSpace();
    /// Underline All Trailing Spaces.
    ASPOSE_WORDS_SHARED_API void set_UlTrailSpace(bool value);
    /// Balance Single Byte and Double Byte Characters.
    ASPOSE_WORDS_SHARED_API bool get_BalanceSingleByteDoubleByteWidth();
    /// Balance Single Byte and Double Byte Characters.
    ASPOSE_WORDS_SHARED_API void set_BalanceSingleByteDoubleByteWidth(bool value);
    /// Ignore Minimum Line Height for First Line on Page.
    ASPOSE_WORDS_SHARED_API bool get_SuppressSpacingAtTopOfPage();
    /// Ignore Minimum Line Height for First Line on Page.
    ASPOSE_WORDS_SHARED_API void set_SuppressSpacingAtTopOfPage(bool value);
    /// Only Expand/Condense Text By Whole Points.
    ASPOSE_WORDS_SHARED_API bool get_SpacingInWholePoints();
    /// Only Expand/Condense Text By Whole Points.
    ASPOSE_WORDS_SHARED_API void set_SpacingInWholePoints(bool value);
    /// Print Body Text before Header/Footer Contents.
    ASPOSE_WORDS_SHARED_API bool get_PrintBodyTextBeforeHeader();
    /// Print Body Text before Header/Footer Contents.
    ASPOSE_WORDS_SHARED_API void set_PrintBodyTextBeforeHeader(bool value);
    /// Do Not Add Leading Between Lines of Text.
    ASPOSE_WORDS_SHARED_API bool get_NoLeading();
    /// Do Not Add Leading Between Lines of Text.
    ASPOSE_WORDS_SHARED_API void set_NoLeading(bool value);
    /// Add Additional Space Below Baseline For Underlined East Asian Text.
    ASPOSE_WORDS_SHARED_API bool get_SpaceForUL();
    /// Add Additional Space Below Baseline For Underlined East Asian Text.
    ASPOSE_WORDS_SHARED_API void set_SpaceForUL(bool value);
    /// Emulate Word 5.x for the Macintosh Small Caps Formatting.
    ASPOSE_WORDS_SHARED_API bool get_MWSmallCaps();
    /// Emulate Word 5.x for the Macintosh Small Caps Formatting.
    ASPOSE_WORDS_SHARED_API void set_MWSmallCaps(bool value);
    /// Emulate WordPerfect 5.x Line Spacing.
    ASPOSE_WORDS_SHARED_API bool get_SuppressTopSpacingWP();
    /// Emulate WordPerfect 5.x Line Spacing.
    ASPOSE_WORDS_SHARED_API void set_SuppressTopSpacingWP(bool value);
    /// Emulate WordPerfect 6.x Font Height Calculation.
    ASPOSE_WORDS_SHARED_API bool get_TruncateFontHeightsLikeWP6();
    /// Emulate WordPerfect 6.x Font Height Calculation.
    ASPOSE_WORDS_SHARED_API void set_TruncateFontHeightsLikeWP6(bool value);
    /// Increase Priority Of Font Size During Font Substitution.
    ASPOSE_WORDS_SHARED_API bool get_SubFontBySize();
    /// Increase Priority Of Font Size During Font Substitution.
    ASPOSE_WORDS_SHARED_API void set_SubFontBySize(bool value);
    /// Emulate Word 6.0 Line Wrapping for East Asian Text.
    ASPOSE_WORDS_SHARED_API bool get_LineWrapLikeWord6();
    /// Emulate Word 6.0 Line Wrapping for East Asian Text.
    ASPOSE_WORDS_SHARED_API void set_LineWrapLikeWord6(bool value);
    /// Do Not Suppress Paragraph Borders Next To Frames.
    ASPOSE_WORDS_SHARED_API bool get_DoNotSuppressParagraphBorders();
    /// Do Not Suppress Paragraph Borders Next To Frames.
    ASPOSE_WORDS_SHARED_API void set_DoNotSuppressParagraphBorders(bool value);
    /// Do Not Center Content on Lines With Exact Line Height.
    ASPOSE_WORDS_SHARED_API bool get_NoExtraLineSpacing();
    /// Do Not Center Content on Lines With Exact Line Height.
    ASPOSE_WORDS_SHARED_API void set_NoExtraLineSpacing(bool value);
    /// Ignore Exact Line Height for Last Line on Page.
    ASPOSE_WORDS_SHARED_API bool get_SuppressBottomSpacing();
    /// Ignore Exact Line Height for Last Line on Page.
    ASPOSE_WORDS_SHARED_API void set_SuppressBottomSpacing(bool value);
    /// Specifies whether to set the width of a space as is done in WordPerfect 5.x.
    ASPOSE_WORDS_SHARED_API bool get_WPSpaceWidth();
    /// Specifies whether to set the width of a space as is done in WordPerfect 5.x.
    ASPOSE_WORDS_SHARED_API void set_WPSpaceWidth(bool value);
    /// Emulate WordPerfect 6.x Paragraph Justification.
    ASPOSE_WORDS_SHARED_API bool get_WPJustification();
    /// Emulate WordPerfect 6.x Paragraph Justification.
    ASPOSE_WORDS_SHARED_API void set_WPJustification(bool value);
    /// Use Printer Metrics To Display Documents.
    ASPOSE_WORDS_SHARED_API bool get_UsePrinterMetrics();
    /// Use Printer Metrics To Display Documents.
    ASPOSE_WORDS_SHARED_API void set_UsePrinterMetrics(bool value);
    /// Emulate Word 97 Text Wrapping Around Floating Objects.
    ASPOSE_WORDS_SHARED_API bool get_ShapeLayoutLikeWW8();
    /// Emulate Word 97 Text Wrapping Around Floating Objects.
    ASPOSE_WORDS_SHARED_API void set_ShapeLayoutLikeWW8(bool value);
    /// Emulate Word 6.x/95/97 Footnote Placement.
    ASPOSE_WORDS_SHARED_API bool get_FootnoteLayoutLikeWW8();
    /// Emulate Word 6.x/95/97 Footnote Placement.
    ASPOSE_WORDS_SHARED_API void set_FootnoteLayoutLikeWW8(bool value);
    /// Use Fixed Paragraph Spacing for HTML Auto Setting.
    ASPOSE_WORDS_SHARED_API bool get_DoNotUseHTMLParagraphAutoSpacing();
    /// Use Fixed Paragraph Spacing for HTML Auto Setting.
    ASPOSE_WORDS_SHARED_API void set_DoNotUseHTMLParagraphAutoSpacing(bool value);
    /// Add Document Grid Line Pitch To Lines in Table Cells.
    ASPOSE_WORDS_SHARED_API bool get_AdjustLineHeightInTable();
    /// Add Document Grid Line Pitch To Lines in Table Cells.
    ASPOSE_WORDS_SHARED_API void set_AdjustLineHeightInTable(bool value);
    /// Ignore Width of Last Tab Stop When Aligning Paragraph If It Is Not Left Aligned.
    ASPOSE_WORDS_SHARED_API bool get_ForgetLastTabAlignment();
    /// Ignore Width of Last Tab Stop When Aligning Paragraph If It Is Not Left Aligned.
    ASPOSE_WORDS_SHARED_API void set_ForgetLastTabAlignment(bool value);
    /// Emulate Word 95 Full-Width Character Spacing.
    ASPOSE_WORDS_SHARED_API bool get_AutoSpaceLikeWord95();
    /// Emulate Word 95 Full-Width Character Spacing.
    ASPOSE_WORDS_SHARED_API void set_AutoSpaceLikeWord95(bool value);
    /// Align Table Rows Independently.
    ASPOSE_WORDS_SHARED_API bool get_AlignTablesRowByRow();
    /// Align Table Rows Independently.
    ASPOSE_WORDS_SHARED_API void set_AlignTablesRowByRow(bool value);
    /// Ignore Space Before Table When Deciding If Table Should Wrap Floating Object.
    ASPOSE_WORDS_SHARED_API bool get_LayoutRawTableWidth();
    /// Ignore Space Before Table When Deciding If Table Should Wrap Floating Object.
    ASPOSE_WORDS_SHARED_API void set_LayoutRawTableWidth(bool value);
    /// Allow Table Rows to Wrap Inline Objects Independently.
    ASPOSE_WORDS_SHARED_API bool get_LayoutTableRowsApart();
    /// Allow Table Rows to Wrap Inline Objects Independently.
    ASPOSE_WORDS_SHARED_API void set_LayoutTableRowsApart(bool value);
    /// Emulate Word 97 East Asian Line Breaking.
    ASPOSE_WORDS_SHARED_API bool get_UseWord97LineBreakRules();
    /// Emulate Word 97 East Asian Line Breaking.
    ASPOSE_WORDS_SHARED_API void set_UseWord97LineBreakRules(bool value);
    /// Do Not Allow Floating Tables To Break Across Pages.
    ASPOSE_WORDS_SHARED_API bool get_DoNotBreakWrappedTables();
    /// Do Not Allow Floating Tables To Break Across Pages.
    ASPOSE_WORDS_SHARED_API void set_DoNotBreakWrappedTables(bool value);
    /// Do Not Snap to Document Grid in Table Cells with Objects.
    ASPOSE_WORDS_SHARED_API bool get_DoNotSnapToGridInCell();
    /// Do Not Snap to Document Grid in Table Cells with Objects.
    ASPOSE_WORDS_SHARED_API void set_DoNotSnapToGridInCell(bool value);
    /// Select Field When First or Last Character Is Selected.
    ASPOSE_WORDS_SHARED_API bool get_SelectFldWithFirstOrLastChar();
    /// Select Field When First or Last Character Is Selected.
    ASPOSE_WORDS_SHARED_API void set_SelectFldWithFirstOrLastChar(bool value);
    /// Use Legacy Ethiopic and Amharic Line Breaking Rules.
    ASPOSE_WORDS_SHARED_API bool get_ApplyBreakingRules();
    /// Use Legacy Ethiopic and Amharic Line Breaking Rules.
    ASPOSE_WORDS_SHARED_API void set_ApplyBreakingRules(bool value);
    /// Do Not Allow Hanging Punctuation With Character Grid.
    ASPOSE_WORDS_SHARED_API bool get_DoNotWrapTextWithPunct();
    /// Do Not Allow Hanging Punctuation With Character Grid.
    ASPOSE_WORDS_SHARED_API void set_DoNotWrapTextWithPunct(bool value);
    /// Do Not Compress Compressible Characters When Using Document Grid.
    ASPOSE_WORDS_SHARED_API bool get_DoNotUseEastAsianBreakRules();
    /// Do Not Compress Compressible Characters When Using Document Grid.
    ASPOSE_WORDS_SHARED_API void set_DoNotUseEastAsianBreakRules(bool value);
    /// Emulate Word 2002 Table Style Rules.
    ASPOSE_WORDS_SHARED_API bool get_UseWord2002TableStyleRules();
    /// Emulate Word 2002 Table Style Rules.
    ASPOSE_WORDS_SHARED_API void set_UseWord2002TableStyleRules(bool value);
    /// Allow Tables to AutoFit Into Page Margins.
    ASPOSE_WORDS_SHARED_API bool get_GrowAutofit();
    /// Allow Tables to AutoFit Into Page Margins.
    ASPOSE_WORDS_SHARED_API void set_GrowAutofit(bool value);
    /// Do Not Automatically Apply List Paragraph Style To Bulleted/Numbered Text.
    ASPOSE_WORDS_SHARED_API bool get_UseNormalStyleForList();
    /// Do Not Automatically Apply List Paragraph Style To Bulleted/Numbered Text.
    ASPOSE_WORDS_SHARED_API void set_UseNormalStyleForList(bool value);
    /// Ignore Hanging Indent When Creating Tab Stop After Numbering.
    ASPOSE_WORDS_SHARED_API bool get_DoNotUseIndentAsNumberingTabStop();
    /// Ignore Hanging Indent When Creating Tab Stop After Numbering.
    ASPOSE_WORDS_SHARED_API void set_DoNotUseIndentAsNumberingTabStop(bool value);
    /// Use Alternate Set of East Asian Line Breaking Rules.
    ASPOSE_WORDS_SHARED_API bool get_UseAltKinsokuLineBreakRules();
    /// Use Alternate Set of East Asian Line Breaking Rules.
    ASPOSE_WORDS_SHARED_API void set_UseAltKinsokuLineBreakRules(bool value);
    /// Allow Contextual Spacing of Paragraphs in Tables.
    ASPOSE_WORDS_SHARED_API bool get_AllowSpaceOfSameStyleInTable();
    /// Allow Contextual Spacing of Paragraphs in Tables.
    ASPOSE_WORDS_SHARED_API void set_AllowSpaceOfSameStyleInTable(bool value);
    /// Do Not Ignore Floating Objects When Calculating Paragraph Indentation.
    ASPOSE_WORDS_SHARED_API bool get_DoNotSuppressIndentation();
    /// Do Not Ignore Floating Objects When Calculating Paragraph Indentation.
    ASPOSE_WORDS_SHARED_API void set_DoNotSuppressIndentation(bool value);
    /// Do Not AutoFit Tables To Fit Next To Wrapped Objects.
    ASPOSE_WORDS_SHARED_API bool get_DoNotAutofitConstrainedTables();
    /// Do Not AutoFit Tables To Fit Next To Wrapped Objects.
    ASPOSE_WORDS_SHARED_API void set_DoNotAutofitConstrainedTables(bool value);
    /// Allow Table Columns To Exceed Preferred Widths of Constituent Cells.
    ASPOSE_WORDS_SHARED_API bool get_AutofitToFirstFixedWidthCell();
    /// Allow Table Columns To Exceed Preferred Widths of Constituent Cells.
    ASPOSE_WORDS_SHARED_API void set_AutofitToFirstFixedWidthCell(bool value);
    /// Underline Following Character Following Numbering.
    ASPOSE_WORDS_SHARED_API bool get_UnderlineTabInNumList();
    /// Underline Following Character Following Numbering.
    ASPOSE_WORDS_SHARED_API void set_UnderlineTabInNumList(bool value);
    /// Always Use Fixed Width for Hangul Characters.
    ASPOSE_WORDS_SHARED_API bool get_DisplayHangulFixedWidth();
    /// Always Use Fixed Width for Hangul Characters.
    ASPOSE_WORDS_SHARED_API void set_DisplayHangulFixedWidth(bool value);
    /// Always Move Paragraph Mark to Page after a Page Break.
    ASPOSE_WORDS_SHARED_API bool get_SplitPgBreakAndParaMark();
    /// Always Move Paragraph Mark to Page after a Page Break.
    ASPOSE_WORDS_SHARED_API void set_SplitPgBreakAndParaMark(bool value);
    /// Don't Vertically Align Cells Containing Floating Objects.
    ASPOSE_WORDS_SHARED_API bool get_DoNotVertAlignCellWithSp();
    /// Don't Vertically Align Cells Containing Floating Objects.
    ASPOSE_WORDS_SHARED_API void set_DoNotVertAlignCellWithSp(bool value);
    /// Don't Break Table Rows Around Floating Tables.
    ASPOSE_WORDS_SHARED_API bool get_DoNotBreakConstrainedForcedTable();
    /// Don't Break Table Rows Around Floating Tables.
    ASPOSE_WORDS_SHARED_API void set_DoNotBreakConstrainedForcedTable(bool value);
    /// Ignore Vertical Alignment in Textboxes.
    ASPOSE_WORDS_SHARED_API bool get_DoNotVertAlignInTxbx();
    /// Ignore Vertical Alignment in Textboxes.
    ASPOSE_WORDS_SHARED_API void set_DoNotVertAlignInTxbx(bool value);
    /// Use ANSI Kerning Pairs from Fonts.
    ASPOSE_WORDS_SHARED_API bool get_UseAnsiKerningPairs();
    /// Use ANSI Kerning Pairs from Fonts.
    ASPOSE_WORDS_SHARED_API void set_UseAnsiKerningPairs(bool value);
    /// Use Cached Paragraph Information for Column Balancing.
    ASPOSE_WORDS_SHARED_API bool get_CachedColBalance();
    /// Use Cached Paragraph Information for Column Balancing.
    ASPOSE_WORDS_SHARED_API void set_CachedColBalance(bool value);
    /// Do Not Bypass East Asian/Complex Script Layout Code.
    ASPOSE_WORDS_SHARED_API bool get_UseFELayout();
    /// Do Not Bypass East Asian/Complex Script Layout Code.
    ASPOSE_WORDS_SHARED_API void set_UseFELayout(bool value);
    /// Specifies how the style hierarchy of the document is evaluated.
    ASPOSE_WORDS_SHARED_API bool get_OverrideTableStyleFontSizeAndJustification();
    /// Specifies how the style hierarchy of the document is evaluated.
    ASPOSE_WORDS_SHARED_API void set_OverrideTableStyleFontSizeAndJustification(bool value);
    /// Specifies to disable OpenType font formatting features.
    ASPOSE_WORDS_SHARED_API bool get_DisableOpenTypeFontFormattingFeatures();
    /// Specifies to disable OpenType font formatting features.
    ASPOSE_WORDS_SHARED_API void set_DisableOpenTypeFontFormattingFeatures(bool value);
    /// Specifies to swap inside and outside for mirror indents and relative positioning.
    ASPOSE_WORDS_SHARED_API bool get_SwapInsideAndOutsideForMirrorIndentsAndRelativePositioning();
    /// Specifies to swap inside and outside for mirror indents and relative positioning.
    ASPOSE_WORDS_SHARED_API void set_SwapInsideAndOutsideForMirrorIndentsAndRelativePositioning(bool value);
    /// Specifies to use Word2010 table style rules.
    ASPOSE_WORDS_SHARED_API bool get_UseWord2010TableStyleRules();
    /// Specifies to use Word2010 table style rules.
    ASPOSE_WORDS_SHARED_API void set_UseWord2010TableStyleRules(bool value);
    /// True to disable UI functionality which is not compatible with Word97-2003.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UICompat97To2003();
    /// True to disable UI functionality which is not compatible with Word97-2003.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_UICompat97To2003(bool value);

    /// Allows to optimize the document contents as well as default %Aspose.Words behavior to a particular versions of MS Word.
    /// Use this method to prevent MS Word from displaying "Compatibility mode" ribbon upon document loading.
    /// (Note that you may also need to set the <see cref="Aspose::Words::Saving::OoxmlSaveOptions::get_Compliance">Compliance</see> property to
    /// <see cref="Aspose::Words::Saving::OoxmlCompliance::Iso29500_2008_Transitional">Iso29500_2008_Transitional</see> or higher.)
    ASPOSE_WORDS_SHARED_API void OptimizeFor(Aspose::Words::Settings::MsWordVersion version);

protected:

    CompatibilityOptions();

    virtual ASPOSE_WORDS_SHARED_API ~CompatibilityOptions();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;

    __TypeStub<1,1,1,1>::type mField4;

};

}
}
}
