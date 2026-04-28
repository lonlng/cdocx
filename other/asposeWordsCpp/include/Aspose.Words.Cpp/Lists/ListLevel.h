//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListLevel.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/NumberStyle.h>
#include <Aspose.Words.Cpp/Lists/ListTrailingCharacter.h>
#include <Aspose.Words.Cpp/Lists/ListLevelAlignment.h>
#include <Aspose.Words.Cpp/IRunAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Drawing
{
class ImageData;

}

class Font;

enum class RevisionsView;

class Style;

}
}

namespace Aspose {

namespace Words {

namespace Lists {

/// Defines formatting for a list level.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-lists/">Working with Lists</a> documentation article.
/// 
/// You do not create objects of this class. List level objects are created automatically
/// when a list is created. You access <see cref="Aspose::Words::Lists::ListLevel">ListLevel</see> objects via the
/// <see cref="Aspose::Words::Lists::ListLevelCollection">ListLevelCollection</see> collection.
/// 
/// Use the properties of <see cref="Aspose::Words::Lists::ListLevel">ListLevel</see> to specify list formatting
/// for individual list levels.
class ASPOSE_WORDS_SHARED_CLASS ListLevel : public Aspose::Words::IRunAttrSource
{
    typedef ListLevel ThisType;
    typedef Aspose::Words::IRunAttrSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using System::Object::Equals;

public:

    /// Returns the starting number for this list level.
    /// 
    /// Default value is 1.
    ASPOSE_WORDS_SHARED_API int32_t get_StartAt();
    /// Sets the starting number for this list level.
    /// 
    /// Default value is 1.
    ASPOSE_WORDS_SHARED_API void set_StartAt(int32_t value);
    /// Returns the number style for this list level.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NumberStyle get_NumberStyle() const;
    /// Sets the number style for this list level.
    ASPOSE_WORDS_SHARED_API void set_NumberStyle(Aspose::Words::NumberStyle value);
    /// Gets the custom number style format for this list level. For example: "a, ç, ĝ, ...".
    ASPOSE_WORDS_SHARED_API System::String get_CustomNumberStyleFormat();
    /// Sets the custom number style format for this list level. For example: "a, ç, ĝ, ...".
    ASPOSE_WORDS_SHARED_API void set_CustomNumberStyleFormat(const System::String& value);
    /// Returns or sets the number format for the list level.
    /// 
    /// Among normal text characters, the string can contain placeholder characters \\x0000 to \\x0008
    /// representing the numbers from the corresponding list levels.
    /// 
    /// For example, the string "\x0000.\x0001)" will generate a list label
    /// that looks something like "1.5)". The number "1" is the current number from
    /// the 1st list level, the number "5" is the current number from the 2nd list level.
    /// 
    /// Null is not allowed, but an empty string meaning no number is valid.
    ASPOSE_WORDS_SHARED_API System::String get_NumberFormat() const;
    /// Setter for Aspose::Words::Lists::ListLevel::get_NumberFormat
    ASPOSE_WORDS_SHARED_API void set_NumberFormat(const System::String& value);
    /// Gets the justification of the actual number of the list item.
    /// 
    /// The list label is justified relative to the <see cref="Aspose::Words::Lists::ListLevel::get_NumberPosition">NumberPosition</see> property.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Lists::ListLevelAlignment get_Alignment() const;
    /// Sets the justification of the actual number of the list item.
    /// 
    /// The list label is justified relative to the <see cref="Aspose::Words::Lists::ListLevel::get_NumberPosition">NumberPosition</see> property.
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::Lists::ListLevelAlignment value);
    /// True if the level turns all inherited numbers to Arabic, false if it preserves their number style.
    ASPOSE_WORDS_SHARED_API bool get_IsLegal() const;
    /// True if the level turns all inherited numbers to Arabic, false if it preserves their number style.
    ASPOSE_WORDS_SHARED_API void set_IsLegal(bool value);
    /// Sets or returns the list level that must appear before the specified list level restarts numbering.
    /// 
    /// The value of -1 means the numbering will continue.
    ASPOSE_WORDS_SHARED_API int32_t get_RestartAfterLevel() const;
    /// Sets or returns the list level that must appear before the specified list level restarts numbering.
    /// 
    /// The value of -1 means the numbering will continue.
    ASPOSE_WORDS_SHARED_API void set_RestartAfterLevel(int32_t value);
    /// Returns the character inserted after the number for the list level.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Lists::ListTrailingCharacter get_TrailingCharacter() const;
    /// Sets the character inserted after the number for the list level.
    ASPOSE_WORDS_SHARED_API void set_TrailingCharacter(Aspose::Words::Lists::ListTrailingCharacter value);
    /// Specifies character formatting used for the list label.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Returns or sets the tab position (in points) for the list level.
    /// 
    /// Has effect only when <see cref="Aspose::Words::Lists::ListLevel::get_TrailingCharacter">TrailingCharacter</see> is a tab.
    /// 
    /// @sa Aspose::Words::Lists::ListLevel::get_NumberPosition
    /// @sa Aspose::Words::Lists::ListLevel::get_TextPosition
    ASPOSE_WORDS_SHARED_API double get_TabPosition() const;
    /// Setter for Aspose::Words::Lists::ListLevel::get_TabPosition
    ASPOSE_WORDS_SHARED_API void set_TabPosition(double value);
    /// Returns or sets the position (in points) of the number or bullet for the list level.
    /// 
    /// <see cref="Aspose::Words::Lists::ListLevel::get_NumberPosition">NumberPosition</see> corresponds to LeftIndent plus FirstLineIndent of the paragraph.
    /// 
    /// @sa Aspose::Words::Lists::ListLevel::get_TextPosition
    /// @sa Aspose::Words::Lists::ListLevel::get_TabPosition
    ASPOSE_WORDS_SHARED_API double get_NumberPosition() const;
    /// Setter for Aspose::Words::Lists::ListLevel::get_NumberPosition
    ASPOSE_WORDS_SHARED_API void set_NumberPosition(double value);
    /// Returns or sets the position (in points) for the second line of wrapping text for the list level.
    /// 
    /// <see cref="Aspose::Words::Lists::ListLevel::get_TextPosition">TextPosition</see> corresponds to LeftIndent of the paragraph.
    /// 
    /// @sa Aspose::Words::Lists::ListLevel::get_NumberPosition
    /// @sa Aspose::Words::Lists::ListLevel::get_TabPosition
    ASPOSE_WORDS_SHARED_API double get_TextPosition() const;
    /// Setter for Aspose::Words::Lists::ListLevel::get_TextPosition
    ASPOSE_WORDS_SHARED_API void set_TextPosition(double value);
    /// Gets or sets the paragraph style that is linked to this list level.
    /// 
    /// This property is <c>%null</c> when the list level is not linked to a paragraph style.
    /// This property can be set to <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> get_LinkedStyle();
    /// Setter for Aspose::Words::Lists::ListLevel::get_LinkedStyle
    ASPOSE_WORDS_SHARED_API void set_LinkedStyle(const System::SharedPtr<Aspose::Words::Style>& value);
    /// Returns image data of the picture bullet shape for the current list level.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::ImageData> get_ImageData();

    /// Creates picture bullet shape for the current list level.
    ASPOSE_WORDS_SHARED_API void CreatePictureBullet();
    /// Deletes picture bullet for the current list level.
    ASPOSE_WORDS_SHARED_API void DeletePictureBullet();
    /// Reports the string representation of the <see cref="Aspose::Words::Lists::ListLevel">ListLevel</see> object for the specified index
    /// of the list item. Parameters specify the <see cref="Aspose::Words::NumberStyle">NumberStyle</see> and an optional format string
    /// used when <see cref="Aspose::Words::NumberStyle::Custom">Custom</see> is specified.
    /// 
    /// @param index The index of the list item (must be in the range from 1 to 32767).
    /// @param numberStyle The <see cref="Aspose::Words::NumberStyle">NumberStyle</see> of the <see cref="Aspose::Words::Lists::ListLevel">ListLevel</see> object.
    /// @param customNumberStyleFormat The optional format string used when <see cref="Aspose::Words::NumberStyle::Custom">Custom</see> is specified (e.g. "a, ç, ĝ, ...").
    ///     In other cases, this parameter must be <c>%null</c> or empty.
    /// 
    /// @return The string representation of the <see cref="Aspose::Words::Lists::ListLevel">ListLevel</see> object, described by the @a numberStyle parameter and
    ///     the @a customNumberStyleFormat parameter, in the list item at the position determined by the @a index parameter.
    /// 
    /// @exception System::ArgumentException @a customNumberStyleFormat is <c>%null</c> or empty when the @a numberStyle is custom.-or-
    ///     @a customNumberStyleFormat is not <c>%null</c> or empty when the @a numberStyle is non-custom.-or-
    ///     @a customNumberStyleFormat is invalid.
    /// @exception System::ArgumentOutOfRangeException index is out of range.
    static ASPOSE_WORDS_SHARED_API System::String GetEffectiveValue(int32_t index, Aspose::Words::NumberStyle numberStyle, const System::String& customNumberStyleFormat);
    /// Compares with the specified ListLevel.
    ASPOSE_WORDS_SHARED_API bool Equals(const System::SharedPtr<Aspose::Words::Lists::ListLevel>& level);
    /// Calculates hash code for this object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;

protected:

    __TypeStub<1,1,1,1>::type mField0;

    virtual ASPOSE_WORDS_SHARED_API ~ListLevel();

private:

    System::WeakPtr<System::Object> mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::String mField5;
    System::String mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    __TypeStub<4,4,4,4>::type mField9;
    __TypeStub<4,4,4,4>::type mField10;
    System::SharedPtr<System::Object> mField11;
    System::SharedPtr<System::Object> mField12;
    __TypeStub<4,4,4,4>::type mField13;
    __TypeStub<1,1,1,1>::type mField14;
    __TypeStub<4,4,4,4>::type mField15;
    __TypeStub<4,4,4,4>::type mField16;
    __TypeStub<1,1,1,1>::type mField17;
    __TypeStub<1,1,1,1>::type mField18;
    __TypeStub<4,4,4,4>::type mField19;
    System::SharedPtr<System::Object> mField20;
    System::WeakPtr<System::Object> mField21;
    System::WeakPtr<System::Object> mField22;

    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedRunAttr(int32_t ) override;
    void SetRunAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveRunAttr(int32_t ) override;
    void ClearRunAttrs() override;

};

}
}
}
