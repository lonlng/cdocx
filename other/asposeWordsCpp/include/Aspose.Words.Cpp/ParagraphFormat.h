//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ParagraphFormat.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/ParagraphAlignment.h>
#include <Aspose.Words.Cpp/OutlineLevel.h>
#include <Aspose.Words.Cpp/LineSpacingRule.h>
#include <Aspose.Words.Cpp/DropCapPosition.h>
#include <Aspose.Words.Cpp/BaselineAlignment.h>
#include <Aspose.Words.Cpp/StyleIdentifier.h>
#include <Aspose.Words.Cpp/IShadingAttrSource.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class BorderCollection;
enum class BorderType;

class Shading;
class Style;

class TabStopCollection;

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
class String;
}

namespace Aspose {

namespace Words {

/// Represents all the formatting for a paragraph.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-paragraphs/">Working with Paragraphs</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ParagraphFormat : public Aspose::Words::IBorderAttrSource, public Aspose::Words::IShadingAttrSource
{
    typedef ParagraphFormat ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;
    typedef Aspose::Words::IShadingAttrSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets text alignment for the paragraph.
    ASPOSE_WORDS_SHARED_API Aspose::Words::ParagraphAlignment get_Alignment();
    /// Sets text alignment for the paragraph.
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::ParagraphAlignment value);
    /// Gets fonts vertical position on a line.
    ASPOSE_WORDS_SHARED_API Aspose::Words::BaselineAlignment get_BaselineAlignment();
    /// Sets fonts vertical position on a line.
    ASPOSE_WORDS_SHARED_API void set_BaselineAlignment(Aspose::Words::BaselineAlignment value);
    /// When <c>%true</c>, <see cref="Aspose::Words::ParagraphFormat::get_SpaceBefore">SpaceBefore</see> and <see cref="Aspose::Words::ParagraphFormat::get_SpaceAfter">SpaceAfter</see> will be ignored
    /// between the paragraphs of the same style.
    /// 
    /// This setting only takes affect when applied to a paragraph style. If applied to
    /// a paragraph directly, it has no effect.
    ASPOSE_WORDS_SHARED_API bool get_NoSpaceBetweenParagraphsOfSameStyle();
    /// Setter for Aspose::Words::ParagraphFormat::get_NoSpaceBetweenParagraphsOfSameStyle
    ASPOSE_WORDS_SHARED_API void set_NoSpaceBetweenParagraphsOfSameStyle(bool value);
    /// True if all lines in the paragraph are to remain on the same page.
    ASPOSE_WORDS_SHARED_API bool get_KeepTogether();
    /// True if all lines in the paragraph are to remain on the same page.
    ASPOSE_WORDS_SHARED_API void set_KeepTogether(bool value);
    /// True if the paragraph is to remains on the same page as the paragraph that follows it.
    ASPOSE_WORDS_SHARED_API bool get_KeepWithNext();
    /// True if the paragraph is to remains on the same page as the paragraph that follows it.
    ASPOSE_WORDS_SHARED_API void set_KeepWithNext(bool value);
    /// True if a page break is forced before the paragraph.
    ASPOSE_WORDS_SHARED_API bool get_PageBreakBefore();
    /// True if a page break is forced before the paragraph.
    ASPOSE_WORDS_SHARED_API void set_PageBreakBefore(bool value);
    /// Specifies whether the current paragraph's lines should be exempted from line numbering
    /// which is applied in the parent section.
    ASPOSE_WORDS_SHARED_API bool get_SuppressLineNumbers();
    /// Specifies whether the current paragraph's lines should be exempted from line numbering
    /// which is applied in the parent section.
    ASPOSE_WORDS_SHARED_API void set_SuppressLineNumbers(bool value);
    /// Specifies whether the current paragraph should be exempted from any hyphenation which
    /// is applied in the document settings.
    ASPOSE_WORDS_SHARED_API bool get_SuppressAutoHyphens();
    /// Specifies whether the current paragraph should be exempted from any hyphenation which
    /// is applied in the document settings.
    ASPOSE_WORDS_SHARED_API void set_SuppressAutoHyphens(bool value);
    /// True if the first and last lines in the paragraph are to remain on the same page as the rest of the paragraph.
    ASPOSE_WORDS_SHARED_API bool get_WidowControl();
    /// True if the first and last lines in the paragraph are to remain on the same page as the rest of the paragraph.
    ASPOSE_WORDS_SHARED_API void set_WidowControl(bool value);
    /// Gets a flag indicating whether inter-character spacing is automatically adjusted between regions
    /// of Latin text and regions of East Asian text in the current paragraph.
    ASPOSE_WORDS_SHARED_API bool get_AddSpaceBetweenFarEastAndAlpha();
    /// Sets a flag indicating whether inter-character spacing is automatically adjusted between regions
    /// of Latin text and regions of East Asian text in the current paragraph.
    ASPOSE_WORDS_SHARED_API void set_AddSpaceBetweenFarEastAndAlpha(bool value);
    /// Gets a flag indicating whether inter-character spacing is automatically adjusted between regions
    /// of numbers and regions of East Asian text in the current paragraph.
    ASPOSE_WORDS_SHARED_API bool get_AddSpaceBetweenFarEastAndDigit();
    /// Sets a flag indicating whether inter-character spacing is automatically adjusted between regions
    /// of numbers and regions of East Asian text in the current paragraph.
    ASPOSE_WORDS_SHARED_API void set_AddSpaceBetweenFarEastAndDigit(bool value);
    /// Gets a flag indicating whether East Asian line-breaking rules are applied to the current paragraph.
    ASPOSE_WORDS_SHARED_API bool get_FarEastLineBreakControl();
    /// Sets a flag indicating whether East Asian line-breaking rules are applied to the current paragraph.
    ASPOSE_WORDS_SHARED_API void set_FarEastLineBreakControl(bool value);
    /// If this property is <c>%false</c>, Latin text in the middle of a word can be wrapped for
    /// the current paragraph. Otherwise Latin text is wrapped by whole words.
    ASPOSE_WORDS_SHARED_API bool get_WordWrap();
    /// If this property is <c>%false</c>, Latin text in the middle of a word can be wrapped for
    /// the current paragraph. Otherwise Latin text is wrapped by whole words.
    ASPOSE_WORDS_SHARED_API void set_WordWrap(bool value);
    /// Gets a flag indicating whether hanging punctuation is enabled for the current paragraph.
    ASPOSE_WORDS_SHARED_API bool get_HangingPunctuation();
    /// Sets a flag indicating whether hanging punctuation is enabled for the current paragraph.
    ASPOSE_WORDS_SHARED_API void set_HangingPunctuation(bool value);
    /// Gets or sets whether this is a right-to-left paragraph.
    /// 
    /// When <c>%true</c>, the runs and other inline objects in this paragraph
    /// are laid out right to left.
    ASPOSE_WORDS_SHARED_API bool get_Bidi();
    /// Setter for Aspose::Words::ParagraphFormat::get_Bidi
    ASPOSE_WORDS_SHARED_API void set_Bidi(bool value);
    /// Gets the value (in points) that represents the left indent for paragraph.
    ASPOSE_WORDS_SHARED_API double get_LeftIndent();
    /// Sets the value (in points) that represents the left indent for paragraph.
    ASPOSE_WORDS_SHARED_API void set_LeftIndent(double value);
    /// Gets the left indent value (in characters) for the specified paragraphs.
    ASPOSE_WORDS_SHARED_API double get_CharacterUnitLeftIndent();
    /// Sets the left indent value (in characters) for the specified paragraphs.
    ASPOSE_WORDS_SHARED_API void set_CharacterUnitLeftIndent(double value);
    /// Gets the value (in points) that represents the right indent for paragraph.
    ASPOSE_WORDS_SHARED_API double get_RightIndent();
    /// Sets the value (in points) that represents the right indent for paragraph.
    ASPOSE_WORDS_SHARED_API void set_RightIndent(double value);
    /// Gets the right indent value (in characters) for the specified paragraphs.
    ASPOSE_WORDS_SHARED_API double get_CharacterUnitRightIndent();
    /// Sets the right indent value (in characters) for the specified paragraphs.
    ASPOSE_WORDS_SHARED_API void set_CharacterUnitRightIndent(double value);
    /// Gets the value (in points) for a first line or hanging indent.
    /// Use positive values to set the first-line indent, and negative values to set the hanging indent.
    ASPOSE_WORDS_SHARED_API double get_FirstLineIndent();
    /// Sets the value (in points) for a first line or hanging indent.
    /// Use positive values to set the first-line indent, and negative values to set the hanging indent.
    ASPOSE_WORDS_SHARED_API void set_FirstLineIndent(double value);
    /// Gets the value (in characters) for the first-line or hanging indent.
    /// Use positive values to set the first-line indent, and negative values to set the hanging indent.
    ASPOSE_WORDS_SHARED_API double get_CharacterUnitFirstLineIndent();
    /// Sets the value (in characters) for the first-line or hanging indent.
    /// Use positive values to set the first-line indent, and negative values to set the hanging indent.
    ASPOSE_WORDS_SHARED_API void set_CharacterUnitFirstLineIndent(double value);
    /// True if the amount of spacing before the paragraph is set automatically.
    /// 
    /// When set to <c>%true</c>, overrides the effect of <see cref="Aspose::Words::ParagraphFormat::get_SpaceBefore">SpaceBefore</see>.
    /// 
    /// When you set paragraph Space Before and Space After to Auto,
    /// Microsoft Word adds 14 points spacing between paragraphs automatically
    /// according to the following rules:
    /// 
    /// - Normally, spacing is added after all paragraphs.
    /// - In a bulleted or numbered list, spacing is added only after the last item in the list.
    ///   Spacing is not added between the list items.
    /// - In a nested bulleted or numbered list spacing is not added.
    /// - Spacing is normally added after a table.
    /// - Spacing is not added after a table if it is the last block in a table cell.
    /// - Spacing is not added after the last paragraph in a table cell.
    ASPOSE_WORDS_SHARED_API bool get_SpaceBeforeAuto();
    /// Setter for Aspose::Words::ParagraphFormat::get_SpaceBeforeAuto
    ASPOSE_WORDS_SHARED_API void set_SpaceBeforeAuto(bool value);
    /// True if the amount of spacing after the paragraph is set automatically.
    /// 
    /// When set to <c>%true</c>, overrides the effect of <see cref="Aspose::Words::ParagraphFormat::get_SpaceAfter">SpaceAfter</see>.
    /// 
    /// When you set paragraph Space Before and Space After to Auto,
    /// Microsoft Word adds 14 points spacing between paragraphs automatically
    /// according to the following rules:
    /// 
    /// - Normally, spacing is added after all paragraphs.
    /// - In a bulleted or numbered list, spacing is added only after the last item in the list.
    ///   Spacing is not added between the list items.
    /// - In a nested bulleted or numbered list spacing is not added.
    /// - Spacing is normally added after a table.
    /// - Spacing is not added after a table if it is the last block in a table cell.
    /// - Spacing is not added after the last paragraph in a table cell.
    ASPOSE_WORDS_SHARED_API bool get_SpaceAfterAuto();
    /// Setter for Aspose::Words::ParagraphFormat::get_SpaceAfterAuto
    ASPOSE_WORDS_SHARED_API void set_SpaceAfterAuto(bool value);
    /// Gets or sets the amount of spacing (in points) before the paragraph.
    /// 
    /// Has no effect when <see cref="Aspose::Words::ParagraphFormat::get_SpaceBeforeAuto">SpaceBeforeAuto</see> is <c>%true</c>.
    /// 
    /// Valid values range from 0 to 1584 inclusive.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when argument was out of the range of valid values.
    ASPOSE_WORDS_SHARED_API double get_SpaceBefore();
    /// Setter for Aspose::Words::ParagraphFormat::get_SpaceBefore
    ASPOSE_WORDS_SHARED_API void set_SpaceBefore(double value);
    /// Gets the amount of spacing (in gridlines) before the paragraphs.
    ASPOSE_WORDS_SHARED_API double get_LineUnitBefore();
    /// Sets the amount of spacing (in gridlines) before the paragraphs.
    ASPOSE_WORDS_SHARED_API void set_LineUnitBefore(double value);
    /// Gets or sets the amount of spacing (in points) after the paragraph.
    /// 
    /// Has no effect when <see cref="Aspose::Words::ParagraphFormat::get_SpaceAfterAuto">SpaceAfterAuto</see> is <c>%true</c>.
    /// 
    /// Valid values ​​range from 0 to 1584 inclusive.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when argument was out of the range of valid values.
    ASPOSE_WORDS_SHARED_API double get_SpaceAfter();
    /// Setter for Aspose::Words::ParagraphFormat::get_SpaceAfter
    ASPOSE_WORDS_SHARED_API void set_SpaceAfter(double value);
    /// Gets the amount of spacing (in gridlines) after the paragraphs.
    ASPOSE_WORDS_SHARED_API double get_LineUnitAfter();
    /// Sets the amount of spacing (in gridlines) after the paragraphs.
    ASPOSE_WORDS_SHARED_API void set_LineUnitAfter(double value);
    /// Gets the line spacing for the paragraph.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LineSpacingRule get_LineSpacingRule();
    /// Sets the line spacing for the paragraph.
    ASPOSE_WORDS_SHARED_API void set_LineSpacingRule(Aspose::Words::LineSpacingRule value);
    /// Gets or sets the line spacing (in points) for the paragraph.
    /// 
    /// When <see cref="Aspose::Words::ParagraphFormat::get_LineSpacingRule">LineSpacingRule</see> property is set to <see cref="Aspose::Words::LineSpacingRule::AtLeast">AtLeast</see>, the line spacing can be greater than or equal to,
    /// but never less than the specified <see cref="Aspose::Words::ParagraphFormat::get_LineSpacing">LineSpacing</see> value.
    /// 
    /// When <see cref="Aspose::Words::ParagraphFormat::get_LineSpacingRule">LineSpacingRule</see> property is set to <see cref="Aspose::Words::LineSpacingRule::Exactly">Exactly</see>, the line spacing never changes from
    /// the specified <see cref="Aspose::Words::ParagraphFormat::get_LineSpacing">LineSpacing</see> value, even if a larger font is used within the paragraph.
    ASPOSE_WORDS_SHARED_API double get_LineSpacing();
    /// Setter for Aspose::Words::ParagraphFormat::get_LineSpacing
    ASPOSE_WORDS_SHARED_API void set_LineSpacing(double value);
    /// Gets a flag indicating whether the left and right indents are of the same width.
    ASPOSE_WORDS_SHARED_API bool get_MirrorIndents();
    /// Sets a flag indicating whether the left and right indents are of the same width.
    ASPOSE_WORDS_SHARED_API void set_MirrorIndents(bool value);
    /// True when the paragraph style is one of the built-in Heading styles.
    ASPOSE_WORDS_SHARED_API bool get_IsHeading();
    /// True when the paragraph is an item in a bulleted or numbered list.
    ASPOSE_WORDS_SHARED_API bool get_IsListItem();
    /// Specifies the outline level of the paragraph in the document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::OutlineLevel get_OutlineLevel();
    /// Specifies the outline level of the paragraph in the document.
    ASPOSE_WORDS_SHARED_API void set_OutlineLevel(Aspose::Words::OutlineLevel value);
    /// Gets the number of lines of the paragraph text used to calculate the drop cap height.
    ASPOSE_WORDS_SHARED_API int32_t get_LinesToDrop();
    /// Sets the number of lines of the paragraph text used to calculate the drop cap height.
    ASPOSE_WORDS_SHARED_API void set_LinesToDrop(int32_t value);
    /// Gets the position for a drop cap text.
    ASPOSE_WORDS_SHARED_API Aspose::Words::DropCapPosition get_DropCapPosition();
    /// Sets the position for a drop cap text.
    ASPOSE_WORDS_SHARED_API void set_DropCapPosition(Aspose::Words::DropCapPosition value);
    /// Returns a <see cref="Aspose::Words::Shading">Shading</see> object that refers to the shading formatting for the paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Shading> get_Shading();
    /// Gets collection of borders of the paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Gets the paragraph style applied to this formatting.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> get_Style();
    /// Sets the paragraph style applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_Style(const System::SharedPtr<Aspose::Words::Style>& value);
    /// Gets the name of the paragraph style applied to this formatting.
    ASPOSE_WORDS_SHARED_API System::String get_StyleName();
    /// Sets the name of the paragraph style applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_StyleName(const System::String& value);
    /// Gets the locale independent style identifier of the paragraph style applied to this formatting.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StyleIdentifier get_StyleIdentifier();
    /// Sets the locale independent style identifier of the paragraph style applied to this formatting.
    ASPOSE_WORDS_SHARED_API void set_StyleIdentifier(Aspose::Words::StyleIdentifier value);
    /// Specifies whether the current paragraph should use the document grid lines per page settings
    /// when laying out the contents in the paragraph.
    ASPOSE_WORDS_SHARED_API bool get_SnapToGrid();
    /// Specifies whether the current paragraph should use the document grid lines per page settings
    /// when laying out the contents in the paragraph.
    ASPOSE_WORDS_SHARED_API void set_SnapToGrid(bool value);
    /// Gets the collection of custom tab stops defined for this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::TabStopCollection> get_TabStops();

    /// Resets to default paragraph formatting.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ParagraphFormat();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    System::WeakPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;
    System::SharedPtr<System::Object> FetchInheritedShadingAttr(int32_t ) override;

};

}
}
