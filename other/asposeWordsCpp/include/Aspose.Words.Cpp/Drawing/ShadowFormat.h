//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ShadowFormat.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Drawing/ShadowType.h>
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

/// Represents shadow formatting for an object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-graphic-elements/">Working with Graphic Elements</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ShadowFormat : public System::Object
{
    typedef ShadowFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the specified <see cref="Aspose::Words::Drawing::ShadowType">ShadowType</see> for ShadowFormat.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ShadowType get_Type();
    /// Sets the specified <see cref="Aspose::Words::Drawing::ShadowType">ShadowType</see> for ShadowFormat.
    ASPOSE_WORDS_SHARED_API void set_Type(Aspose::Words::Drawing::ShadowType value);
    /// Returns <c>%true</c> if the formatting applied to this instance is visible.
    ASPOSE_WORDS_SHARED_API bool get_Visible();
    /// Gets a <see cref="System::Drawing::Color">Color</see> object that represents the color for the shadow.
    /// The default value is <see cref="System::Drawing::Color::get_Black">Black</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Sets a <see cref="System::Drawing::Color">Color</see> object that represents the color for the shadow.
    /// The default value is <see cref="System::Drawing::Color::get_Black">Black</see>.
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets the degree of transparency for the shadow effect as a value between 0.0 (opaque) and 1.0 (clear).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Transparency();
    /// Sets the degree of transparency for the shadow effect as a value between 0.0 (opaque) and 1.0 (clear).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Transparency(double value);

    /// Clears shadow format.
    ASPOSE_WORDS_SHARED_API void Clear();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
