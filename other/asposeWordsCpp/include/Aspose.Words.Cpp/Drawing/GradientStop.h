//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/GradientStop.h
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

/// Represents one gradient stop.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-graphic-elements/">Working with Graphic Elements</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS GradientStop : public System::Object
{
    typedef GradientStop ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a value representing the color of the gradient stop.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Sets a value representing the color of the gradient stop.
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets a value representing the color of the gradient stop without any modifiers.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BaseColor();
    /// Gets a value representing the position of a stop within the gradient
    /// expressed as a percent in range 0.0 to 1.0.
    ASPOSE_WORDS_SHARED_API double get_Position() const;
    /// Sets a value representing the position of a stop within the gradient
    /// expressed as a percent in range 0.0 to 1.0.
    ASPOSE_WORDS_SHARED_API void set_Position(double value);
    /// Gets a value representing the transparency of the gradient fill
    /// expressed as a percent in range 0.0 to 1.0.
    ASPOSE_WORDS_SHARED_API double get_Transparency() const;
    /// Sets a value representing the transparency of the gradient fill
    /// expressed as a percent in range 0.0 to 1.0.
    ASPOSE_WORDS_SHARED_API void set_Transparency(double value);

    /// Initializes a new instance of the <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> class.
    /// 
    /// @param color Represents the color of the gradient stop.
    /// @param position Represents the position of a stop within
    ///     the gradient expressed as a percent in range 0.0 to 1.0.
    ASPOSE_WORDS_SHARED_API GradientStop(System::Drawing::Color color, double position);
    /// Initializes a new instance of the <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> class.
    /// 
    /// @param color Represents the color of the gradient stop.
    /// @param position Represents the position of a stop within
    ///     the gradient expressed as a percent in range 0.0 to 1.0.
    /// @param transparency Represents the transparency of a stop within
    ///     the gradient expressed as a percent in range 0.0 to 1.0.
    ASPOSE_WORDS_SHARED_API GradientStop(System::Drawing::Color color, double position, double transparency);

    /// Removes the gradient stop from the parent <see cref="Aspose::Words::Drawing::GradientStopCollection">GradientStopCollection</see>.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~GradientStop();

private:

    System::SharedPtr<System::Object> mField0;

    System::WeakPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
}
