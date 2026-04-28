//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/GlowFormat.h
#pragma once

#include <system/object.h>

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

/// Represents the glow formatting for an object.
/// 
/// Use the <see cref="Aspose::Words::Drawing::ShapeBase::get_Glow">Glow</see> property to access glow properties of an object.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::GlowFormat">GlowFormat</see> class directly.
class ASPOSE_WORDS_SHARED_CLASS GlowFormat : public System::Object
{
    typedef GlowFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a <see cref="System::Drawing::Color">Color</see> object that represents the color for a glow effect.
    /// The default value is <see cref="System::Drawing::Color::get_Black">Black</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Sets a <see cref="System::Drawing::Color">Color</see> object that represents the color for a glow effect.
    /// The default value is <see cref="System::Drawing::Color::get_Black">Black</see>.
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets the degree of transparency for the glow effect as a value between 0.0 (opaque) and 1.0 (clear).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Transparency();
    /// Sets the degree of transparency for the glow effect as a value between 0.0 (opaque) and 1.0 (clear).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Transparency(double value);
    /// Gets a double value that represents the length of the radius for a glow effect in points (pt).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API double get_Radius();
    /// Sets a double value that represents the length of the radius for a glow effect in points (pt).
    /// The default value is 0.0.
    ASPOSE_WORDS_SHARED_API void set_Radius(double value);

    /// Removes <see cref="Aspose::Words::Drawing::GlowFormat">GlowFormat</see> from the parent object.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
