//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Stroke.h
#pragma once

#include <Aspose.Words.Cpp/Themes/ThemeColor.h>
#include <Aspose.Words.Cpp/Drawing/ShapeLineStyle.h>
#include <Aspose.Words.Cpp/Drawing/JoinStyle.h>
#include <Aspose.Words.Cpp/Drawing/EndCap.h>
#include <Aspose.Words.Cpp/Drawing/DashStyle.h>
#include <Aspose.Words.Cpp/Drawing/Core/IFillable.h>
#include <Aspose.Words.Cpp/Drawing/ArrowWidth.h>
#include <Aspose.Words.Cpp/Drawing/ArrowType.h>
#include <Aspose.Words.Cpp/Drawing/ArrowLength.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Drawing
{

namespace Core
{
namespace Dml
{
namespace Colors
{
class DmlColor;
}

namespace Themes
{
class IThemeProvider;
}
}
enum class FillTypeCore;
class IFill;

}
class Fill;
class GradientStopCollection;
enum class GradientStyle;
enum class GradientVariant;
enum class PatternType;
enum class PresetTexture;

enum class TextureAlignment;
}

}
}
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

/// Defines a stroke for a shape.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-shapes/">Working with Shapes</a> documentation article.
/// 
/// Use the <see cref="Aspose::Words::Drawing::Shape::get_Stroke">Stroke</see> property to access stroke properties of a shape.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::Stroke">Stroke</see> class directly.
/// 
/// @sa Aspose::Words::Drawing::Shape::get_Stroke
class ASPOSE_WORDS_SHARED_CLASS Stroke : public Aspose::Words::Drawing::Core::IFillable
{
    typedef Stroke ThisType;
    typedef Aspose::Words::Drawing::Core::IFillable BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Defines whether the path will be stroked.
    /// 
    /// The default value for a <see cref="Aspose::Words::Drawing::Shape">Shape</see> is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_On();
    /// Defines whether the path will be stroked.
    /// 
    /// The default value for a <see cref="Aspose::Words::Drawing::Shape">Shape</see> is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_On(bool value);
    /// Defines the color of a stroke.
    /// 
    /// The default value for a <see cref="Aspose::Words::Drawing::Shape">Shape</see> is
    /// <see cref="System::Drawing::Color::get_Black">Black</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color();
    /// Setter for Aspose::Words::Drawing::Stroke::get_Color
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value);
    /// Defines a second color for a stroke.
    /// 
    /// The default value for a <see cref="Aspose::Words::Drawing::Shape">Shape</see> is
    /// <see cref="System::Drawing::Color::get_White">White</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color2();
    /// Setter for Aspose::Words::Drawing::Stroke::get_Color2
    ASPOSE_WORDS_SHARED_API void set_Color2(System::Drawing::Color value);
    /// Gets the foreground color of the stroke.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_ForeColor();
    /// Sets the foreground color of the stroke.
    ASPOSE_WORDS_SHARED_API void set_ForeColor(System::Drawing::Color value);
    /// Gets the base foreground color of the stroke without any modifiers.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BaseForeColor();
    /// Gets the background color of the stroke.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BackColor();
    /// Sets the background color of the stroke.
    ASPOSE_WORDS_SHARED_API void set_BackColor(System::Drawing::Color value);
    /// Gets a ThemeColor object that represents the stroke foreground color.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeColor get_ForeThemeColor();
    /// Sets a ThemeColor object that represents the stroke foreground color.
    ASPOSE_WORDS_SHARED_API void set_ForeThemeColor(Aspose::Words::Themes::ThemeColor value);
    /// Gets a ThemeColor object that represents the stroke background color.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Themes::ThemeColor get_BackThemeColor();
    /// Sets a ThemeColor object that represents the stroke background color.
    ASPOSE_WORDS_SHARED_API void set_BackThemeColor(Aspose::Words::Themes::ThemeColor value);
    /// Gets or sets a double value that lightens or darkens the stroke foreground color.
    /// 
    /// The allowed values are within the range from -1 (the darkest) to 1 (the lightest) for this property.
    /// Zero (0) is neutral. Attempting to set this property to a value less than -1 or more than 1
    /// results in <see cref="System::ArgumentOutOfRangeException">ArgumentOutOfRangeException</see>.
    ASPOSE_WORDS_SHARED_API double get_ForeTintAndShade();
    /// Setter for Aspose::Words::Drawing::Stroke::get_ForeTintAndShade
    ASPOSE_WORDS_SHARED_API void set_ForeTintAndShade(double value);
    /// Gets or sets a double value that lightens or darkens the stroke background color.
    /// 
    /// The allowed values are within the range from -1 (the darkest) to 1 (the lightest) for this property.
    /// Zero (0) is neutral. Attempting to set this property to a value less than -1 or more than 1
    /// results in <see cref="System::ArgumentOutOfRangeException">ArgumentOutOfRangeException</see>.
    ASPOSE_WORDS_SHARED_API double get_BackTintAndShade();
    /// Setter for Aspose::Words::Drawing::Stroke::get_BackTintAndShade
    ASPOSE_WORDS_SHARED_API void set_BackTintAndShade(double value);
    /// Gets a flag indicating whether the stroke is visible.
    ASPOSE_WORDS_SHARED_API bool get_Visible();
    /// Sets a flag indicating whether the stroke is visible.
    ASPOSE_WORDS_SHARED_API void set_Visible(bool value);
    /// Gets a value between 0.0 (opaque) and 1.0 (clear) representing the degree of transparency
    /// of the stroke.
    ASPOSE_WORDS_SHARED_API double get_Transparency();
    /// Sets a value between 0.0 (opaque) and 1.0 (clear) representing the degree of transparency
    /// of the stroke.
    ASPOSE_WORDS_SHARED_API void set_Transparency(double value);
    /// Defines the brush thickness that strokes the path of a shape in points.
    /// 
    /// The default value for a <see cref="Aspose::Words::Drawing::Shape">Shape</see> is 0.75.
    ASPOSE_WORDS_SHARED_API double get_Weight();
    /// Defines the brush thickness that strokes the path of a shape in points.
    /// 
    /// The default value for a <see cref="Aspose::Words::Drawing::Shape">Shape</see> is 0.75.
    ASPOSE_WORDS_SHARED_API void set_Weight(double value);
    /// Specifies the dot and dash pattern for a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::DashStyle::Solid">Solid</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::DashStyle get_DashStyle();
    /// Specifies the dot and dash pattern for a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::DashStyle::Solid">Solid</see>.
    ASPOSE_WORDS_SHARED_API void set_DashStyle(Aspose::Words::Drawing::DashStyle value);
    /// Defines the join style of a polyline.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::JoinStyle::Round">Round</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::JoinStyle get_JoinStyle();
    /// Defines the join style of a polyline.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::JoinStyle::Round">Round</see>.
    ASPOSE_WORDS_SHARED_API void set_JoinStyle(Aspose::Words::Drawing::JoinStyle value);
    /// Defines the cap style for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::EndCap::Flat">Flat</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::EndCap get_EndCap();
    /// Defines the cap style for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::EndCap::Flat">Flat</see>.
    ASPOSE_WORDS_SHARED_API void set_EndCap(Aspose::Words::Drawing::EndCap value);
    /// Defines the line style of the stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ShapeLineStyle::Single">Single</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ShapeLineStyle get_LineStyle();
    /// Defines the line style of the stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ShapeLineStyle::Single">Single</see>.
    ASPOSE_WORDS_SHARED_API void set_LineStyle(Aspose::Words::Drawing::ShapeLineStyle value);
    /// Defines the arrowhead for the start of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowType::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ArrowType get_StartArrowType();
    /// Defines the arrowhead for the start of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowType::None">None</see>.
    ASPOSE_WORDS_SHARED_API void set_StartArrowType(Aspose::Words::Drawing::ArrowType value);
    /// Defines the arrowhead for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowType::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ArrowType get_EndArrowType();
    /// Defines the arrowhead for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowType::None">None</see>.
    ASPOSE_WORDS_SHARED_API void set_EndArrowType(Aspose::Words::Drawing::ArrowType value);
    /// Defines the arrowhead width for the start of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowWidth::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ArrowWidth get_StartArrowWidth();
    /// Defines the arrowhead width for the start of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowWidth::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API void set_StartArrowWidth(Aspose::Words::Drawing::ArrowWidth value);
    /// Defines the arrowhead length for the start of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowLength::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ArrowLength get_StartArrowLength();
    /// Defines the arrowhead length for the start of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowLength::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API void set_StartArrowLength(Aspose::Words::Drawing::ArrowLength value);
    /// Defines the arrowhead width for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowWidth::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ArrowWidth get_EndArrowWidth();
    /// Defines the arrowhead width for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowWidth::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API void set_EndArrowWidth(Aspose::Words::Drawing::ArrowWidth value);
    /// Defines the arrowhead length for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowLength::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ArrowLength get_EndArrowLength();
    /// Defines the arrowhead length for the end of a stroke.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ArrowLength::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API void set_EndArrowLength(Aspose::Words::Drawing::ArrowLength value);
    /// Defines the amount of transparency of a stroke. Valid range is from 0 to 1.
    /// 
    /// The default value is 1.
    ASPOSE_WORDS_SHARED_API double get_Opacity();
    /// Defines the amount of transparency of a stroke. Valid range is from 0 to 1.
    /// 
    /// The default value is 1.
    ASPOSE_WORDS_SHARED_API void set_Opacity(double value);
    /// Defines the image for a stroke image or pattern fill.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_ImageBytes();
    /// Gets fill formatting for the <see cref="Aspose::Words::Drawing::Stroke">Stroke</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Fill> get_Fill();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Stroke();

private:

    System::Drawing::Color get_FilledColor() override;
    void set_FilledColor(System::Drawing::Color ) override;
    bool get_OldOn() override;
    void set_OldOn(bool ) override;
    double get_OldOpacity() override;
    void set_OldOpacity(double ) override;
    System::ArrayPtr<uint8_t> get_FillableImageBytes() override;
    Aspose::Words::Drawing::TextureAlignment get_TextureAlignment() override;
    void set_TextureAlignment(Aspose::Words::Drawing::TextureAlignment ) override;
    double get_GradientAngle() override;
    void set_GradientAngle(double ) override;
    Aspose::Words::Drawing::GradientVariant get_GradientVariant() override;
    Aspose::Words::Drawing::GradientStyle get_GradientStyle() override;
    System::SharedPtr<Aspose::Words::Drawing::GradientStopCollection> get_GradientStops() override;
    System::Drawing::Color get_FillableForeColor() override;
    void set_FillableForeColor(System::Drawing::Color ) override;
    System::Drawing::Color get_FillableBaseForeColor() override;
    System::Drawing::Color get_FillableBackColor() override;
    void set_FillableBackColor(System::Drawing::Color ) override;
    Aspose::Words::Themes::ThemeColor get_FillableForeThemeColor() override;
    void set_FillableForeThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    Aspose::Words::Themes::ThemeColor get_FillableBackThemeColor() override;
    void set_FillableBackThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    double get_FillableForeTintAndShade() override;
    void set_FillableForeTintAndShade(double ) override;
    double get_FillableBackTintAndShade() override;
    void set_FillableBackTintAndShade(double ) override;
    bool get_FillableVisible() override;
    void set_FillableVisible(bool ) override;
    double get_FillableTransparency() override;
    void set_FillableTransparency(double ) override;
    bool get_RotateWithObject() override;
    void set_RotateWithObject(bool ) override;
    Aspose::Words::Drawing::Core::FillTypeCore get_FillType() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_FillableThemeProvider() override;

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

    void Solid() override;
    Aspose::Words::Drawing::PresetTexture GetPresetTexture() override;
    Aspose::Words::Drawing::PatternType GetPatternType() override;
    void PresetTextured(Aspose::Words::Drawing::PresetTexture ) override;
    void Patterned(Aspose::Words::Drawing::PatternType ) override;
    void TwoColorGradient(Aspose::Words::Drawing::GradientStyle , Aspose::Words::Drawing::GradientVariant ) override;
    void OneColorGradient(Aspose::Words::Drawing::GradientStyle , Aspose::Words::Drawing::GradientVariant , double ) override;
    void SetImage(System::ArrayPtr<uint8_t> ) override;
    void SetFill(System::SharedPtr<Aspose::Words::Drawing::Core::IFill> ) override;
    double GetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> ) override;
    void SetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> , double ) override;

};

}
}
}
