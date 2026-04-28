//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Fill.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Themes/ThemeColor.h>
#include <Aspose.Words.Cpp/Drawing/TextureAlignment.h>
#include <Aspose.Words.Cpp/Drawing/PresetTexture.h>
#include <Aspose.Words.Cpp/Drawing/PatternType.h>
#include <Aspose.Words.Cpp/Drawing/GradientVariant.h>
#include <Aspose.Words.Cpp/Drawing/GradientStyle.h>
#include <Aspose.Words.Cpp/Drawing/FillType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{

class GradientStopCollection;

}

}
}
namespace System
{
namespace Drawing
{
class Color;
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents fill formatting for an object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-graphic-elements/">Working with Graphic Elements</a> documentation article.
/// 
/// Use the <see cref="Aspose::Words::Drawing::ShapeBase::get_Fill">Fill</see> or <see cref="Aspose::Words::Font::get_Fill">Fill</see> property to access fill properties of an object.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::Fill">Fill</see> class directly.
class ASPOSE_WORDS_SHARED_CLASS Fill : public System::Object
{
    typedef Fill ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a <see cref="Aspose::Words::Drawing::PresetTexture">PresetTexture</see> for the fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::PresetTexture get_PresetTexture();
    /// Gets a <see cref="Aspose::Words::Drawing::PatternType">PatternType</see> for the fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::PatternType get_Pattern();
    /// Gets the alignment for tile texture fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::TextureAlignment get_TextureAlignment();
    /// Sets the alignment for tile texture fill.
    ASPOSE_WORDS_SHARED_API void set_TextureAlignment(Aspose::Words::Drawing::TextureAlignment value);
    /// @deprecated This property is obsolete. Please, use ForeColor property instead.
    /// Gets a Color object that represents the foreground color for the fill.
    [[deprecated("This property is obsolete. Please, use ForeColor property instead.")]]
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// @deprecated This property is obsolete. Please, use ForeColor property instead.
    /// Sets a Color object that represents the foreground color for the fill.
    [[deprecated("This property is obsolete. Please, use ForeColor property instead.")]]
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Gets the degree of opacity of the specified fill as a value between 0.0 (clear) and 1.0 (opaque).
    ASPOSE_WORDS_SHARED_API double get_Opacity();
    /// Sets the degree of opacity of the specified fill as a value between 0.0 (clear) and 1.0 (opaque).
    ASPOSE_WORDS_SHARED_API void set_Opacity(double value);
    /// Gets the raw bytes of the fill texture or pattern.
    /// 
    /// The default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_ImageBytes();
    /// Gets a Color object that represents the foreground color for the fill.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_ForeColor();
    /// Sets a Color object that represents the foreground color for the fill.
    ASPOSE_WORDS_SHARED_API void set_ForeColor(System::Drawing::Color value);
    /// Gets a Color object that represents the base foreground color for the fill
    /// without any modifiers.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BaseForeColor();
    /// Gets a Color object that represents the background color for the fill.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BackColor();
    /// Sets a Color object that represents the background color for the fill.
    ASPOSE_WORDS_SHARED_API void set_BackColor(System::Drawing::Color value);
    /// Gets a ThemeColor object that represents the foreground color for the fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeColor get_ForeThemeColor();
    /// Sets a ThemeColor object that represents the foreground color for the fill.
    ASPOSE_WORDS_SHARED_API void set_ForeThemeColor(Aspose::Words::Themes::ThemeColor value);
    /// Gets a ThemeColor object that represents the background color for the fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeColor get_BackThemeColor();
    /// Sets a ThemeColor object that represents the background color for the fill.
    ASPOSE_WORDS_SHARED_API void set_BackThemeColor(Aspose::Words::Themes::ThemeColor value);
    /// Gets or sets a double value that lightens or darkens the foreground color.
    /// 
    /// The allowed values are in the range from -1 (the darkest) to 1 (the lightest) for this property.
    /// 
    /// Zero (0) is neutral.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throw if set this property to a value less than -1 or more than 1.
    ASPOSE_WORDS_SHARED_API double get_ForeTintAndShade();
    /// Setter for Aspose::Words::Drawing::Fill::get_ForeTintAndShade
    ASPOSE_WORDS_SHARED_API void set_ForeTintAndShade(double value);
    /// Gets or sets a double value that lightens or darkens the background color.
    /// 
    /// The allowed values are in the range from -1 (the darkest) to 1 (the lightest) for this property.
    /// 
    /// Zero (0) is neutral.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throw if set this property to a value less than -1 or more than 1.
    ASPOSE_WORDS_SHARED_API double get_BackTintAndShade();
    /// Setter for Aspose::Words::Drawing::Fill::get_BackTintAndShade
    ASPOSE_WORDS_SHARED_API void set_BackTintAndShade(double value);
    /// Gets value that is <c>%true</c> if the formatting applied to this instance, is visible.
    ASPOSE_WORDS_SHARED_API bool get_Visible();
    /// Sets value that is <c>%true</c> if the formatting applied to this instance, is visible.
    ASPOSE_WORDS_SHARED_API void set_Visible(bool value);
    /// Gets the degree of transparency of the specified fill as a value between 0.0 (opaque) and 1.0 (clear).
    ASPOSE_WORDS_SHARED_API double get_Transparency();
    /// Sets the degree of transparency of the specified fill as a value between 0.0 (opaque) and 1.0 (clear).
    ASPOSE_WORDS_SHARED_API void set_Transparency(double value);
    /// Gets whether the fill rotates with the specified object.
    ASPOSE_WORDS_SHARED_API bool get_RotateWithObject();
    /// Sets whether the fill rotates with the specified object.
    ASPOSE_WORDS_SHARED_API void set_RotateWithObject(bool value);
    /// Gets a fill type.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::FillType get_FillType();
    /// Gets the angle of the gradient fill.
    ASPOSE_WORDS_SHARED_API double get_GradientAngle();
    /// Sets the angle of the gradient fill.
    ASPOSE_WORDS_SHARED_API void set_GradientAngle(double value);
    /// Gets the gradient variant <see cref="Aspose::Words::Drawing::GradientVariant">GradientVariant</see> for the fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::GradientVariant get_GradientVariant();
    /// Gets the gradient style <see cref="Aspose::Words::Drawing::GradientStyle">GradientStyle</see> for the fill.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::GradientStyle get_GradientStyle();
    /// Gets a collection of <see cref="Aspose::Words::Drawing::GradientStop">GradientStop</see> objects for the fill.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::GradientStopCollection> get_GradientStops();

    /// Sets the fill to a uniform color.
    ASPOSE_WORDS_SHARED_API void Solid();
    /// Sets the fill to a specified uniform color.
    ASPOSE_WORDS_SHARED_API void Solid(System::Drawing::Color color);
    /// Sets the fill to a preset texture.
    /// 
    /// @param presetTexture <see cref="Aspose::Words::Drawing::PresetTexture">PresetTexture</see>
    ASPOSE_WORDS_SHARED_API void PresetTextured(Aspose::Words::Drawing::PresetTexture presetTexture);
    /// Sets the specified fill to a pattern.
    /// 
    /// @param patternType <see cref="Aspose::Words::Drawing::PatternType">PatternType</see>
    ASPOSE_WORDS_SHARED_API void Patterned(Aspose::Words::Drawing::PatternType patternType);
    /// Sets the specified fill to a pattern.
    /// 
    /// @param patternType <see cref="Aspose::Words::Drawing::PatternType">PatternType</see>
    /// @param foreColor The color of the foreground fill.
    /// @param backColor The color of the background fill.
    ASPOSE_WORDS_SHARED_API void Patterned(Aspose::Words::Drawing::PatternType patternType, System::Drawing::Color foreColor, System::Drawing::Color backColor);
    /// Sets the specified fill to a one-color gradient.
    /// 
    /// @param style The gradient style <see cref="Aspose::Words::Drawing::GradientStyle">GradientStyle</see>
    /// @param variant The gradient variant <see cref="Aspose::Words::Drawing::GradientVariant">GradientVariant</see>
    /// @param degree The gradient degree. Can be a value from 0.0 (dark) to 1.0 (light).
    ASPOSE_WORDS_SHARED_API void OneColorGradient(Aspose::Words::Drawing::GradientStyle style, Aspose::Words::Drawing::GradientVariant variant, double degree);
    /// Sets the specified fill to a one-color gradient using the specified color.
    /// 
    /// @param color The color to build the gradient.
    /// @param style The gradient style <see cref="Aspose::Words::Drawing::GradientStyle">GradientStyle</see>
    /// @param variant The gradient variant <see cref="Aspose::Words::Drawing::GradientVariant">GradientVariant</see>
    /// @param degree The gradient degree. Can be a value from 0.0 (dark) to 1.0 (light).
    ASPOSE_WORDS_SHARED_API void OneColorGradient(System::Drawing::Color color, Aspose::Words::Drawing::GradientStyle style, Aspose::Words::Drawing::GradientVariant variant, double degree);
    /// Sets the specified fill to a two-color gradient.
    /// 
    /// @param style The gradient style <see cref="Aspose::Words::Drawing::GradientStyle">GradientStyle</see>.
    /// @param variant The gradient variant <see cref="Aspose::Words::Drawing::GradientVariant">GradientVariant</see>
    ASPOSE_WORDS_SHARED_API void TwoColorGradient(Aspose::Words::Drawing::GradientStyle style, Aspose::Words::Drawing::GradientVariant variant);
    /// Sets the specified fill to a two-color gradient.
    /// 
    /// @param color1 The first color to build the gradient.
    /// @param color2 The second color to build the gradient.
    /// @param style The gradient style <see cref="Aspose::Words::Drawing::GradientStyle">GradientStyle</see>.
    /// @param variant The gradient variant <see cref="Aspose::Words::Drawing::GradientVariant">GradientVariant</see>
    ASPOSE_WORDS_SHARED_API void TwoColorGradient(System::Drawing::Color color1, System::Drawing::Color color2, Aspose::Words::Drawing::GradientStyle style, Aspose::Words::Drawing::GradientVariant variant);
    /// Changes the fill type to single image.
    /// 
    /// @param fileName The path to the image file.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::String& fileName);
    /// Changes the fill type to single image.
    /// 
    /// @param stream The stream that contains the image bytes.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& stream);
    /// Changes the fill type to single image.
    /// 
    /// @param imageBytes The image bytes array.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::ArrayPtr<uint8_t>& imageBytes);

protected:

private:

    System::WeakPtr<System::Object> mField0;

};

}
}
}
