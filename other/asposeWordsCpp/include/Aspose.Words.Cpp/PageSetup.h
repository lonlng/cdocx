//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PageSetup.h
#pragma once

#include <system/shared_ptr.h>
#include <mutex>
#include <memory>

#include <Aspose.Words.Cpp/LocaleDefaults.h>
#include <Aspose.Words.Cpp/TextOrientation.h>
#include <Aspose.Words.Cpp/Settings/MultiplePagesType.h>
#include <Aspose.Words.Cpp/SectionStart.h>
#include <Aspose.Words.Cpp/SectionLayoutMode.h>
#include <Aspose.Words.Cpp/PaperSize.h>
#include <Aspose.Words.Cpp/PageVerticalAlignment.h>
#include <Aspose.Words.Cpp/PageBorderDistanceFrom.h>
#include <Aspose.Words.Cpp/PageBorderAppliesTo.h>
#include <Aspose.Words.Cpp/Orientation.h>
#include <Aspose.Words.Cpp/Margins.h>
#include <Aspose.Words.Cpp/LineNumberRestartMode.h>
#include <Aspose.Words.Cpp/ChapterPageSeparator.h>
#include <Aspose.Words.Cpp/NumberStyle.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class BorderCollection;
enum class BorderType;

namespace Notes
{
class EndnoteOptions;
class FootnoteOptions;
}

class TextColumnCollection;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename, typename> class SortedList;
}
}

}

namespace Aspose {

namespace Words {

/// Represents the page setup properties of a section.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-sections/">Working with Sections</a> documentation article.
/// 
/// <see cref="Aspose::Words::PageSetup">PageSetup</see> object contains all the page setup attributes of a section
/// (left margin, bottom margin, paper size, and so on) as properties.
class ASPOSE_WORDS_SHARED_CLASS PageSetup : public Aspose::Words::IBorderAttrSource
{
    typedef PageSetup ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// True if the document has different headers and footers for odd-numbered and even-numbered pages.
    ASPOSE_WORDS_SHARED_API bool get_OddAndEvenPagesHeaderFooter() const;
    /// True if the document has different headers and footers for odd-numbered and even-numbered pages.
    ASPOSE_WORDS_SHARED_API void set_OddAndEvenPagesHeaderFooter(bool value);
    /// True if a different header or footer is used on the first page.
    ASPOSE_WORDS_SHARED_API bool get_DifferentFirstPageHeaderFooter();
    /// True if a different header or footer is used on the first page.
    ASPOSE_WORDS_SHARED_API void set_DifferentFirstPageHeaderFooter(bool value);
    /// For multiple page documents, gets or sets how a document is printed or rendered so that it can be bound as a booklet.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::MultiplePagesType get_MultiplePages() const;
    /// For multiple page documents, gets or sets how a document is printed or rendered so that it can be bound as a booklet.
    ASPOSE_WORDS_SHARED_API void set_MultiplePages(Aspose::Words::Settings::MultiplePagesType value);
    /// Returns the number of pages to be included in each booklet.
    ASPOSE_WORDS_SHARED_API int32_t get_SheetsPerBooklet() const;
    /// Sets the number of pages to be included in each booklet.
    ASPOSE_WORDS_SHARED_API void set_SheetsPerBooklet(int32_t value);
    /// Returns the type of section break for the specified object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SectionStart get_SectionStart();
    /// Sets the type of section break for the specified object.
    ASPOSE_WORDS_SHARED_API void set_SectionStart(Aspose::Words::SectionStart value);
    /// True if endnotes are printed at the end of the next section that doesn't suppress endnotes.
    /// Suppressed endnotes are printed before the endnotes in that section.
    ASPOSE_WORDS_SHARED_API bool get_SuppressEndnotes();
    /// True if endnotes are printed at the end of the next section that doesn't suppress endnotes.
    /// Suppressed endnotes are printed before the endnotes in that section.
    ASPOSE_WORDS_SHARED_API void set_SuppressEndnotes(bool value);
    /// Returns the vertical alignment of text on each page in a document or section.
    ASPOSE_WORDS_SHARED_API Aspose::Words::PageVerticalAlignment get_VerticalAlignment();
    /// Sets the vertical alignment of text on each page in a document or section.
    ASPOSE_WORDS_SHARED_API void set_VerticalAlignment(Aspose::Words::PageVerticalAlignment value);
    /// Specifies that this section contains bidirectional (complex scripts) text.
    /// 
    /// When <c>%true</c>, the columns in this section are laid out from right to left.
    ASPOSE_WORDS_SHARED_API bool get_Bidi();
    /// Specifies that this section contains bidirectional (complex scripts) text.
    /// 
    /// When <c>%true</c>, the columns in this section are laid out from right to left.
    ASPOSE_WORDS_SHARED_API void set_Bidi(bool value);
    /// Gets the layout mode of this section.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SectionLayoutMode get_LayoutMode();
    /// Sets the layout mode of this section.
    ASPOSE_WORDS_SHARED_API void set_LayoutMode(Aspose::Words::SectionLayoutMode value);
    /// Gets or sets the number of characters per line in the document grid.
    /// 
    /// Minimum value of the property is 1. Maximum value depends on page width and font size of the Normal
    /// style. Minimum character pitch is 90 percent of the font size. For example, maximum number of characters
    /// per line of a Letter page with one-inch margins is 43.
    /// 
    /// By default, the property has a value, on which character pitch equals to font size of the Normal
    /// style.
    ASPOSE_WORDS_SHARED_API int32_t get_CharactersPerLine();
    /// Setter for Aspose::Words::PageSetup::get_CharactersPerLine
    ASPOSE_WORDS_SHARED_API void set_CharactersPerLine(int32_t value);
    /// Gets or sets the number of lines per page in the document grid.
    /// 
    /// Minimum value of the property is 1. Maximum value depends on page height and font size of the Normal
    /// style. Minimum line pitch is 136 percent of the font size. For example, maximum number of lines per page of
    /// a Letter page with one-inch margins is 39.
    /// 
    /// By default, the property has a value, on which line pitch is in 1.5 times greater than font size of
    /// the Normal style.
    ASPOSE_WORDS_SHARED_API int32_t get_LinesPerPage();
    /// Setter for Aspose::Words::PageSetup::get_LinesPerPage
    ASPOSE_WORDS_SHARED_API void set_LinesPerPage(int32_t value);
    /// Returns the width of the page in points.
    ASPOSE_WORDS_SHARED_API double get_PageWidth();
    /// Sets the width of the page in points.
    ASPOSE_WORDS_SHARED_API void set_PageWidth(double value);
    /// Returns the height of the page in points.
    ASPOSE_WORDS_SHARED_API double get_PageHeight();
    /// Sets the height of the page in points.
    ASPOSE_WORDS_SHARED_API void set_PageHeight(double value);
    /// Returns preset <see cref="Aspose::Words::Margins">Margins</see> of the page.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Margins get_Margins();
    /// Sets preset <see cref="Aspose::Words::Margins">Margins</see> of the page.
    ASPOSE_WORDS_SHARED_API void set_Margins(Aspose::Words::Margins value);
    /// Returns or sets the paper size.
    /// 
    /// Setting this property updates <see cref="Aspose::Words::PageSetup::get_PageWidth">PageWidth</see> and <see cref="Aspose::Words::PageSetup::get_PageHeight">PageHeight</see> values.
    /// Setting this value to <see cref="Aspose::Words::PaperSize::Custom">Custom</see> does not change existing values.
    ASPOSE_WORDS_SHARED_API Aspose::Words::PaperSize get_PaperSize();
    /// Setter for Aspose::Words::PageSetup::get_PaperSize
    ASPOSE_WORDS_SHARED_API void set_PaperSize(Aspose::Words::PaperSize value);
    /// Returns the orientation of the page.
    /// 
    /// Changing <see cref="Aspose::Words::PageSetup::get_Orientation">Orientation</see> swaps <see cref="Aspose::Words::PageSetup::get_PageWidth">PageWidth</see> and <see cref="Aspose::Words::PageSetup::get_PageHeight">PageHeight</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Orientation get_Orientation();
    /// Sets the orientation of the page.
    /// 
    /// Changing <see cref="Aspose::Words::PageSetup::get_Orientation">Orientation</see> swaps <see cref="Aspose::Words::PageSetup::get_PageWidth">PageWidth</see> and <see cref="Aspose::Words::PageSetup::get_PageHeight">PageHeight</see>.
    ASPOSE_WORDS_SHARED_API void set_Orientation(Aspose::Words::Orientation value);
    /// Returns the distance (in points) between the left edge of the page and the left boundary of the body text.
    ASPOSE_WORDS_SHARED_API double get_LeftMargin();
    /// Sets the distance (in points) between the left edge of the page and the left boundary of the body text.
    ASPOSE_WORDS_SHARED_API void set_LeftMargin(double value);
    /// Returns the distance (in points) between the right edge of the page and the right boundary of the body text.
    ASPOSE_WORDS_SHARED_API double get_RightMargin();
    /// Sets the distance (in points) between the right edge of the page and the right boundary of the body text.
    ASPOSE_WORDS_SHARED_API void set_RightMargin(double value);
    /// Returns the distance (in points) between the top edge of the page and the top boundary of the body text.
    ASPOSE_WORDS_SHARED_API double get_TopMargin();
    /// Sets the distance (in points) between the top edge of the page and the top boundary of the body text.
    ASPOSE_WORDS_SHARED_API void set_TopMargin(double value);
    /// Returns the distance (in points) between the bottom edge of the page and the bottom boundary of the body text.
    ASPOSE_WORDS_SHARED_API double get_BottomMargin();
    /// Sets the distance (in points) between the bottom edge of the page and the bottom boundary of the body text.
    ASPOSE_WORDS_SHARED_API void set_BottomMargin(double value);
    /// Returns the distance (in points) between the header and the top of the page.
    ASPOSE_WORDS_SHARED_API double get_HeaderDistance();
    /// Sets the distance (in points) between the header and the top of the page.
    ASPOSE_WORDS_SHARED_API void set_HeaderDistance(double value);
    /// Returns the distance (in points) between the footer and the bottom of the page.
    ASPOSE_WORDS_SHARED_API double get_FooterDistance();
    /// Sets the distance (in points) between the footer and the bottom of the page.
    ASPOSE_WORDS_SHARED_API void set_FooterDistance(double value);
    /// Gets the amount of extra space added to the margin for document binding.
    ASPOSE_WORDS_SHARED_API double get_Gutter();
    /// Sets the amount of extra space added to the margin for document binding.
    ASPOSE_WORDS_SHARED_API void set_Gutter(double value);
    /// Gets the paper tray (bin) to use for the first page of a section.
    /// The value is implementation (printer) specific.
    ASPOSE_WORDS_SHARED_API int32_t get_FirstPageTray();
    /// Sets the paper tray (bin) to use for the first page of a section.
    /// The value is implementation (printer) specific.
    ASPOSE_WORDS_SHARED_API void set_FirstPageTray(int32_t value);
    /// Gets the paper tray (bin) to be used for all but the first page of a section.
    /// The value is implementation (printer) specific.
    ASPOSE_WORDS_SHARED_API int32_t get_OtherPagesTray();
    /// Sets the paper tray (bin) to be used for all but the first page of a section.
    /// The value is implementation (printer) specific.
    ASPOSE_WORDS_SHARED_API void set_OtherPagesTray(int32_t value);
    /// Gets or sets the heading level style that is applied to the chapter titles in the document.
    /// 
    /// Can be a number from 0 through 9. 0 means no chapter number if applied to page number.
    /// 
    /// Before you can create page numbers that include chapter numbers, the document headings must have a numbered outline format applied.
    ASPOSE_WORDS_SHARED_API int32_t get_HeadingLevelForChapter();
    /// Setter for Aspose::Words::PageSetup::get_HeadingLevelForChapter
    ASPOSE_WORDS_SHARED_API void set_HeadingLevelForChapter(int32_t value);
    /// Gets the separator character that appears between the chapter number and the page number.
    /// 
    /// Before you can create page numbers that include chapter numbers, the document headings must have a numbered outline format applied.
    ASPOSE_WORDS_SHARED_API Aspose::Words::ChapterPageSeparator get_ChapterPageSeparator();
    /// Sets the separator character that appears between the chapter number and the page number.
    /// 
    /// Before you can create page numbers that include chapter numbers, the document headings must have a numbered outline format applied.
    ASPOSE_WORDS_SHARED_API void set_ChapterPageSeparator(Aspose::Words::ChapterPageSeparator value);
    /// Gets the page number format.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NumberStyle get_PageNumberStyle();
    /// Sets the page number format.
    ASPOSE_WORDS_SHARED_API void set_PageNumberStyle(Aspose::Words::NumberStyle value);
    /// True if page numbering restarts at the beginning of the section.
    ASPOSE_WORDS_SHARED_API bool get_RestartPageNumbering();
    /// True if page numbering restarts at the beginning of the section.
    ASPOSE_WORDS_SHARED_API void set_RestartPageNumbering(bool value);
    /// Gets the starting page number of the section.
    ASPOSE_WORDS_SHARED_API int32_t get_PageStartingNumber();
    /// Sets the starting page number of the section.
    ASPOSE_WORDS_SHARED_API void set_PageStartingNumber(int32_t value);
    /// Gets the way line numbering runs  that is, whether it starts over at the beginning of a new
    /// page or section or runs continuously.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LineNumberRestartMode get_LineNumberRestartMode();
    /// Sets the way line numbering runs  that is, whether it starts over at the beginning of a new
    /// page or section or runs continuously.
    ASPOSE_WORDS_SHARED_API void set_LineNumberRestartMode(Aspose::Words::LineNumberRestartMode value);
    /// Returns the numeric increment for line numbers.
    ASPOSE_WORDS_SHARED_API int32_t get_LineNumberCountBy();
    /// Sets the numeric increment for line numbers.
    ASPOSE_WORDS_SHARED_API void set_LineNumberCountBy(int32_t value);
    /// Gets distance between the right edge of line numbers and the left edge of the document.
    ASPOSE_WORDS_SHARED_API double get_LineNumberDistanceFromText();
    /// Sets distance between the right edge of line numbers and the left edge of the document.
    ASPOSE_WORDS_SHARED_API void set_LineNumberDistanceFromText(double value);
    /// Gets the starting line number.
    ASPOSE_WORDS_SHARED_API int32_t get_LineStartingNumber();
    /// Sets the starting line number.
    ASPOSE_WORDS_SHARED_API void set_LineStartingNumber(int32_t value);
    /// Returns a collection that represents the set of text columns.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TextColumnCollection> get_TextColumns();
    /// Gets whether %Microsoft Word uses gutters for the section based on a right-to-left language or a left-to-right language.
    ASPOSE_WORDS_SHARED_API bool get_RtlGutter();
    /// Sets whether %Microsoft Word uses gutters for the section based on a right-to-left language or a left-to-right language.
    ASPOSE_WORDS_SHARED_API void set_RtlGutter(bool value);
    /// Specifies where the page border is positioned relative to intersecting texts and objects.
    ASPOSE_WORDS_SHARED_API bool get_BorderAlwaysInFront();
    /// Specifies where the page border is positioned relative to intersecting texts and objects.
    ASPOSE_WORDS_SHARED_API void set_BorderAlwaysInFront(bool value);
    /// Gets a value that indicates whether the specified page border is measured from the edge of the page or from the text it surrounds.
    ASPOSE_WORDS_SHARED_API Aspose::Words::PageBorderDistanceFrom get_BorderDistanceFrom();
    /// Sets a value that indicates whether the specified page border is measured from the edge of the page or from the text it surrounds.
    ASPOSE_WORDS_SHARED_API void set_BorderDistanceFrom(Aspose::Words::PageBorderDistanceFrom value);
    /// Specifies which pages the page border is printed on.
    ASPOSE_WORDS_SHARED_API Aspose::Words::PageBorderAppliesTo get_BorderAppliesTo();
    /// Specifies which pages the page border is printed on.
    ASPOSE_WORDS_SHARED_API void set_BorderAppliesTo(Aspose::Words::PageBorderAppliesTo value);
    /// Specifies whether the page border includes or excludes the header.
    ASPOSE_WORDS_SHARED_API bool get_BorderSurroundsHeader();
    /// Specifies whether the page border includes or excludes the header.
    ASPOSE_WORDS_SHARED_API void set_BorderSurroundsHeader(bool value);
    /// Specifies whether the page border includes or excludes the footer.
    ASPOSE_WORDS_SHARED_API bool get_BorderSurroundsFooter();
    /// Specifies whether the page border includes or excludes the footer.
    ASPOSE_WORDS_SHARED_API void set_BorderSurroundsFooter(bool value);
    /// Gets a collection of the page borders.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Provides options that control numbering and positioning of footnotes in this section.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Notes::FootnoteOptions> get_FootnoteOptions();
    /// Provides options that control numbering and positioning of endnotes in this section.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Notes::EndnoteOptions> get_EndnoteOptions();
    /// Allows to specify <see cref="Aspose::Words::PageSetup::get_TextOrientation">TextOrientation</see> for the whole page.
    /// Default value is <see cref="Aspose::Words::TextOrientation::Horizontal">Horizontal</see>
    ASPOSE_WORDS_SHARED_API Aspose::Words::TextOrientation get_TextOrientation();
    /// Allows to specify <see cref="Aspose::Words::PageSetup::get_TextOrientation">TextOrientation</see> for the whole page.
    /// Default value is <see cref="Aspose::Words::TextOrientation::Horizontal">Horizontal</see>
    ASPOSE_WORDS_SHARED_API void set_TextOrientation(Aspose::Words::TextOrientation value);

    /// Resets page setup to default paper size, margins and orientation.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~PageSetup();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;

};

}
}
