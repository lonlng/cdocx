//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/TextPath.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/TextPathAlignment.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Defines the text and formatting of the text path (of a WordArt object).
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-shapes/">Working with Shapes</a> documentation article.
/// 
/// Use the <see cref="Aspose::Words::Drawing::Shape::get_TextPath">TextPath</see> property to access WordArt properties of a shape.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::TextPath">TextPath</see> class directly.
/// 
/// @sa Aspose::Words::Drawing::Shape::get_TextPath
class ASPOSE_WORDS_SHARED_CLASS TextPath : public System::Object
{
    typedef TextPath ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Defines whether the text is displayed.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_On();
    /// Defines whether the text is displayed.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_On(bool value);
    /// Defines whether the text fits the path of a shape.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_FitPath();
    /// Defines whether the text fits the path of a shape.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_FitPath(bool value);
    /// Defines whether the text fits bounding box of a shape.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_FitShape();
    /// Defines whether the text fits bounding box of a shape.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_FitShape(bool value);
    /// Defines the family of the textpath font.
    /// 
    /// The default value is Arial.
    ASPOSE_WORDS_SHARED_API System::String get_FontFamily();
    /// Defines the family of the textpath font.
    /// 
    /// The default value is Arial.
    ASPOSE_WORDS_SHARED_API void set_FontFamily(const System::String& value);
    /// Defines the size of the font in points.
    /// 
    /// The default value is 36.
    ASPOSE_WORDS_SHARED_API double get_Size();
    /// Defines the size of the font in points.
    /// 
    /// The default value is 36.
    ASPOSE_WORDS_SHARED_API void set_Size(double value);
    /// True if the font is formatted as bold.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Bold();
    /// True if the font is formatted as bold.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Bold(bool value);
    /// True if the font is formatted as italic.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Italic();
    /// True if the font is formatted as italic.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Italic(bool value);
    /// True if the font is formatted as small capital letters.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_SmallCaps();
    /// True if the font is formatted as small capital letters.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_SmallCaps(bool value);
    /// Determines whether the letters of the text are rotated.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_RotateLetters();
    /// Determines whether the letters of the text are rotated.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_RotateLetters(bool value);
    /// Determines whether extra space is removed above and below the text.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Trim();
    /// Determines whether extra space is removed above and below the text.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Trim(bool value);
    /// Determines whether kerning is turned on.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Kerning();
    /// Determines whether kerning is turned on.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Kerning(bool value);
    /// Defines whether a shadow is applied to the text on a text path.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Shadow();
    /// Defines whether a shadow is applied to the text on a text path.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Shadow(bool value);
    /// True if the font is underlined.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Underline();
    /// True if the font is underlined.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Underline(bool value);
    /// True if the font is formatted as strikethrough text.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_StrikeThrough();
    /// True if the font is formatted as strikethrough text.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_StrikeThrough(bool value);
    /// Determines whether all letters will be the same height regardless of initial case.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_SameLetterHeights();
    /// Determines whether all letters will be the same height regardless of initial case.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_SameLetterHeights(bool value);
    /// Defines the text of the text path.
    /// 
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Defines the text of the text path.
    /// 
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);
    /// Defines the alignment of text.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::TextPathAlignment::Center">Center</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::TextPathAlignment get_TextPathAlignment();
    /// Defines the alignment of text.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::TextPathAlignment::Center">Center</see>.
    ASPOSE_WORDS_SHARED_API void set_TextPathAlignment(Aspose::Words::Drawing::TextPathAlignment value);
    /// Determines whether the layout order of rows is reversed.
    /// 
    /// The default value is <c>%false</c>.
    /// 
    /// If <c>%true</c>, the layout order of rows is reversed. This attribute is used for vertical text layout.
    ASPOSE_WORDS_SHARED_API bool get_ReverseRows();
    /// Setter for Aspose::Words::Drawing::TextPath::get_ReverseRows
    ASPOSE_WORDS_SHARED_API void set_ReverseRows(bool value);
    /// Defines the amount of spacing for text. 1 means 100\%.
    /// 
    /// The default value is 1.
    ASPOSE_WORDS_SHARED_API double get_Spacing();
    /// Defines the amount of spacing for text. 1 means 100\%.
    /// 
    /// The default value is 1.
    ASPOSE_WORDS_SHARED_API void set_Spacing(double value);
    /// Determines whether a straight textpath will be used instead of the shape path.
    /// 
    /// The default value is <c>%false</c>.
    /// 
    /// If <c>%true</c>, the text runs along a path from left to right along the x value of
    /// the lower boundary of the shape.
    ASPOSE_WORDS_SHARED_API bool get_XScale();
    /// Setter for Aspose::Words::Drawing::TextPath::get_XScale
    ASPOSE_WORDS_SHARED_API void set_XScale(bool value);

protected:

private:

    System::WeakPtr<System::Object> mField0;

};

}
}
}
