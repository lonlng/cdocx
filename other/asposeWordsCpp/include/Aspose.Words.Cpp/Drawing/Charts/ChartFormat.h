//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartFormat.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Core/IStrokable.h>
#include <Aspose.Words.Cpp/Drawing/Core/IFillable.h>
#include <Aspose.Words.Cpp/Drawing/Charts/ChartShapeType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Drawing
{
class DrColor;
}
namespace Words
{
namespace Drawing
{
enum class ArrowLength;
enum class ArrowType;
enum class ArrowWidth;

namespace Core
{
namespace Dml
{
namespace Colors
{
class DmlColor;
}
namespace Fills
{
class DmlFill;
}

namespace Themes
{
class IThemeProvider;
}
}
enum class FillTypeCore;
class IFill;
enum class LineFillType;
}
enum class DashStyle;
enum class EndCap;
class Fill;
class GradientStopCollection;
enum class GradientStyle;
enum class GradientVariant;
enum class JoinStyle;
enum class PatternType;
enum class PresetTexture;
enum class ShapeLineStyle;
class Stroke;
enum class TextureAlignment;
}
namespace Themes
{
enum class ThemeColor;
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

namespace Charts {

/// Represents the formatting of a chart element.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartFormat : public Aspose::Words::Drawing::Core::IFillable, public Aspose::Words::Drawing::Core::IStrokable
{
    typedef ChartFormat ThisType;
    typedef Aspose::Words::Drawing::Core::IFillable BaseType;
    typedef Aspose::Words::Drawing::Core::IStrokable BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets fill formatting for the parent chart element.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Fill> get_Fill();
    /// Gets line formatting for the parent chart element.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Stroke> get_Stroke();
    /// Gets the shape type of the parent chart element.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartShapeType get_ShapeType();
    /// Sets the shape type of the parent chart element.
    ASPOSE_WORDS_SHARED_API void set_ShapeType(Aspose::Words::Drawing::Charts::ChartShapeType value);
    /// Gets a flag indicating whether any format is defined.
    ASPOSE_WORDS_SHARED_API bool get_IsDefined();

    /// Resets the fill of the chart element to have the default value.
    ASPOSE_WORDS_SHARED_API void SetDefaultFill();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartFormat();

private:

    System::Drawing::Color get_FilledColor() override;
    void set_FilledColor(System::Drawing::Color ) override;
    bool get_OldOn() override;
    void set_OldOn(bool ) override;
    double get_OldOpacity() override;
    void set_OldOpacity(double ) override;
    System::ArrayPtr<uint8_t> get_FillableImageBytes() override;
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
    Aspose::Words::Drawing::TextureAlignment get_TextureAlignment() override;
    void set_TextureAlignment(Aspose::Words::Drawing::TextureAlignment ) override;
    double get_GradientAngle() override;
    void set_GradientAngle(double ) override;
    Aspose::Words::Drawing::GradientVariant get_GradientVariant() override;
    Aspose::Words::Drawing::GradientStyle get_GradientStyle() override;
    System::SharedPtr<Aspose::Words::Drawing::GradientStopCollection> get_GradientStops() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_FillableThemeProvider() override;
    System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeForeColor() override;
    void set_StrokeForeColor(System::SharedPtr<Aspose::Drawing::DrColor> ) override;
    System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeBaseForeColor() override;
    System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeBackColor() override;
    void set_StrokeBackColor(System::SharedPtr<Aspose::Drawing::DrColor> ) override;
    Aspose::Words::Themes::ThemeColor get_StrokeForeThemeColor() override;
    void set_StrokeForeThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    Aspose::Words::Themes::ThemeColor get_StrokeBackThemeColor() override;
    void set_StrokeBackThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    double get_StrokeForeTintAndShade() override;
    void set_StrokeForeTintAndShade(double ) override;
    double get_StrokeBackTintAndShade() override;
    void set_StrokeBackTintAndShade(double ) override;
    bool get_StrokeVisible() override;
    void set_StrokeVisible(bool ) override;
    double get_StrokeTransparency() override;
    void set_StrokeTransparency(double ) override;
    double get_Weight() override;
    void set_Weight(double ) override;
    Aspose::Words::Drawing::DashStyle get_DashStyle() override;
    void set_DashStyle(Aspose::Words::Drawing::DashStyle ) override;
    Aspose::Words::Drawing::JoinStyle get_JoinStyle() override;
    void set_JoinStyle(Aspose::Words::Drawing::JoinStyle ) override;
    Aspose::Words::Drawing::EndCap get_EndCap() override;
    void set_EndCap(Aspose::Words::Drawing::EndCap ) override;
    Aspose::Words::Drawing::ShapeLineStyle get_LineStyle() override;
    void set_LineStyle(Aspose::Words::Drawing::ShapeLineStyle ) override;
    Aspose::Words::Drawing::ArrowType get_StartArrowType() override;
    void set_StartArrowType(Aspose::Words::Drawing::ArrowType ) override;
    Aspose::Words::Drawing::ArrowType get_EndArrowType() override;
    void set_EndArrowType(Aspose::Words::Drawing::ArrowType ) override;
    Aspose::Words::Drawing::ArrowWidth get_StartArrowWidth() override;
    void set_StartArrowWidth(Aspose::Words::Drawing::ArrowWidth ) override;
    Aspose::Words::Drawing::ArrowLength get_StartArrowLength() override;
    void set_StartArrowLength(Aspose::Words::Drawing::ArrowLength ) override;
    Aspose::Words::Drawing::ArrowWidth get_EndArrowWidth() override;
    void set_EndArrowWidth(Aspose::Words::Drawing::ArrowWidth ) override;
    Aspose::Words::Drawing::ArrowLength get_EndArrowLength() override;
    void set_EndArrowLength(Aspose::Words::Drawing::ArrowLength ) override;
    Aspose::Words::Drawing::Core::LineFillType get_LineFillType() override;
    void set_LineFillType(Aspose::Words::Drawing::Core::LineFillType ) override;
    System::ArrayPtr<uint8_t> get_StrokeImageBytes() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_StrokeThemeProvider() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_StrokeFill() override;
    void set_StrokeFill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> ) override;

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

    void Solid() override;
    void PresetTextured(Aspose::Words::Drawing::PresetTexture ) override;
    void Patterned(Aspose::Words::Drawing::PatternType ) override;
    Aspose::Words::Drawing::PresetTexture GetPresetTexture() override;
    Aspose::Words::Drawing::PatternType GetPatternType() override;
    void OneColorGradient(Aspose::Words::Drawing::GradientStyle , Aspose::Words::Drawing::GradientVariant , double ) override;
    void TwoColorGradient(Aspose::Words::Drawing::GradientStyle , Aspose::Words::Drawing::GradientVariant ) override;
    void SetImage(System::ArrayPtr<uint8_t> ) override;
    void SetFill(System::SharedPtr<Aspose::Words::Drawing::Core::IFill> ) override;
    double GetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> ) override;
    void SetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> , double ) override;

};

}
}
}
}
