//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/HorizontalRuleFormat.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Drawing/HorizontalRuleAlignment.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Drawing
{
class Color;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents horizontal rule formatting.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-shapes/">Working with Shapes</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS HorizontalRuleFormat : public System::Object
{
    typedef HorizontalRuleFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the length of the specified horizontal rule expressed as a percentage of the window width.
    /// 
    /// Valid values ​​range from 1 to 100 inclusive.
    /// 
    /// The default value is 100.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when argument was out of the range of valid values.
    ASPOSE_WORDS_SHARED_API double get_WidthPercent();
    /// Setter for Aspose::Words::Drawing::HorizontalRuleFormat::get_WidthPercent
    ASPOSE_WORDS_SHARED_API void set_WidthPercent(double value);
    /// Gets or sets the height of the horizontal rule.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::ShapeBase::get_Height">Height</see> property.
    /// 
    /// Valid values ​​range from 0 to 1584 inclusive.
    /// 
    /// The default value is 1.5.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when argument was out of the range of valid values.
    ASPOSE_WORDS_SHARED_API double get_Height();
    /// Setter for Aspose::Words::Drawing::HorizontalRuleFormat::get_Height
    ASPOSE_WORDS_SHARED_API void set_Height(double value);
    /// Indicates the presence of 3D shading for the horizontal rule.
    /// If <c>%true</c>, then the horizontal rule is without 3D shading and solid color is used.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_NoShade();
    /// Setter for Aspose::Words::Drawing::HorizontalRuleFormat::get_NoShade
    ASPOSE_WORDS_SHARED_API void set_NoShade(bool value);
    /// Gets or sets the brush color that fills the horizontal rule.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::Fill::get_Color">Color</see> property.
    /// 
    /// The default value is
    /// <see cref="System::Drawing::Color::get_Gray">Gray</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Setter for Aspose::Words::Drawing::HorizontalRuleFormat::get_Color
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets the alignment of the horizontal rule.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::HorizontalRuleAlignment::Left">Left</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::HorizontalRuleAlignment get_Alignment();
    /// Sets the alignment of the horizontal rule.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::HorizontalRuleAlignment::Left">Left</see>.
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::Drawing::HorizontalRuleAlignment value);

protected:

private:

    System::WeakPtr<System::Object> mField0;

};

}
}
}
