//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/IFillable.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Core/FillTypeCore.h>
#include <Aspose.Words.Cpp/Themes/ThemeColor.h>
#include <Aspose.Words.Cpp/Drawing/TextureAlignment.h>
#include <Aspose.Words.Cpp/Drawing/PresetTexture.h>
#include <Aspose.Words.Cpp/Drawing/PatternType.h>
#include <Aspose.Words.Cpp/Drawing/GradientVariant.h>
#include <Aspose.Words.Cpp/Drawing/GradientStyle.h>

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
class IFill;
}
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
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class IFillable : public virtual System::Object
{
    typedef IFillable ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::Drawing::Color get_FilledColor() = 0;
    virtual void set_FilledColor(System::Drawing::Color value) = 0;
    virtual bool get_OldOn() = 0;
    virtual void set_OldOn(bool value) = 0;
    virtual double get_OldOpacity() = 0;
    virtual void set_OldOpacity(double value) = 0;
    virtual System::ArrayPtr<uint8_t> get_FillableImageBytes() = 0;
    virtual System::Drawing::Color get_FillableForeColor() = 0;
    virtual void set_FillableForeColor(System::Drawing::Color value) = 0;
    virtual System::Drawing::Color get_FillableBaseForeColor() = 0;
    virtual System::Drawing::Color get_FillableBackColor() = 0;
    virtual void set_FillableBackColor(System::Drawing::Color value) = 0;
    virtual Aspose::Words::Themes::ThemeColor get_FillableForeThemeColor() = 0;
    virtual void set_FillableForeThemeColor(Aspose::Words::Themes::ThemeColor value) = 0;
    virtual Aspose::Words::Themes::ThemeColor get_FillableBackThemeColor() = 0;
    virtual void set_FillableBackThemeColor(Aspose::Words::Themes::ThemeColor value) = 0;
    virtual double get_FillableForeTintAndShade() = 0;
    virtual void set_FillableForeTintAndShade(double value) = 0;
    virtual double get_FillableBackTintAndShade() = 0;
    virtual void set_FillableBackTintAndShade(double value) = 0;
    virtual bool get_FillableVisible() = 0;
    virtual void set_FillableVisible(bool value) = 0;
    virtual double get_FillableTransparency() = 0;
    virtual void set_FillableTransparency(double value) = 0;
    virtual bool get_RotateWithObject() = 0;
    virtual void set_RotateWithObject(bool value) = 0;
    virtual Aspose::Words::Drawing::Core::FillTypeCore get_FillType() = 0;
    virtual Aspose::Words::Drawing::TextureAlignment get_TextureAlignment() = 0;
    virtual void set_TextureAlignment(Aspose::Words::Drawing::TextureAlignment value) = 0;
    virtual double get_GradientAngle() = 0;
    virtual void set_GradientAngle(double value) = 0;
    virtual Aspose::Words::Drawing::GradientVariant get_GradientVariant() = 0;
    virtual Aspose::Words::Drawing::GradientStyle get_GradientStyle() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::GradientStopCollection> get_GradientStops() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_FillableThemeProvider() = 0;

    virtual void Solid() = 0;
    virtual void PresetTextured(Aspose::Words::Drawing::PresetTexture presetTexture) = 0;
    virtual void Patterned(Aspose::Words::Drawing::PatternType patternType) = 0;
    virtual Aspose::Words::Drawing::PresetTexture GetPresetTexture() = 0;
    virtual Aspose::Words::Drawing::PatternType GetPatternType() = 0;
    virtual void TwoColorGradient(Aspose::Words::Drawing::GradientStyle style, Aspose::Words::Drawing::GradientVariant variant) = 0;
    virtual void OneColorGradient(Aspose::Words::Drawing::GradientStyle style, Aspose::Words::Drawing::GradientVariant variant, double degree) = 0;
    virtual void SetImage(System::ArrayPtr<uint8_t> imageBytes) = 0;
    virtual void SetFill(System::SharedPtr<Aspose::Words::Drawing::Core::IFill> fill) = 0;
    virtual double GetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> color) = 0;
    virtual void SetTransparency(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> color, double value) = 0;

};/// \endcond

}
}
}
}
