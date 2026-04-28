//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/IStrokable.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Core/LineFillType.h>
#include <Aspose.Words.Cpp/Themes/ThemeColor.h>
#include <Aspose.Words.Cpp/Drawing/ShapeLineStyle.h>
#include <Aspose.Words.Cpp/Drawing/JoinStyle.h>
#include <Aspose.Words.Cpp/Drawing/EndCap.h>
#include <Aspose.Words.Cpp/Drawing/DashStyle.h>
#include <Aspose.Words.Cpp/Drawing/ArrowWidth.h>
#include <Aspose.Words.Cpp/Drawing/ArrowType.h>
#include <Aspose.Words.Cpp/Drawing/ArrowLength.h>

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
namespace Core
{
namespace Dml
{
namespace Fills
{
class DmlFill;
}
namespace Themes
{
class IThemeProvider;
}
}
}
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class IStrokable : public virtual System::Object
{
    typedef IStrokable ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeForeColor() = 0;
    virtual void set_StrokeForeColor(System::SharedPtr<Aspose::Drawing::DrColor> value) = 0;
    virtual System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeBaseForeColor() = 0;
    virtual System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeBackColor() = 0;
    virtual void set_StrokeBackColor(System::SharedPtr<Aspose::Drawing::DrColor> value) = 0;
    virtual Aspose::Words::Themes::ThemeColor get_StrokeForeThemeColor() = 0;
    virtual void set_StrokeForeThemeColor(Aspose::Words::Themes::ThemeColor value) = 0;
    virtual Aspose::Words::Themes::ThemeColor get_StrokeBackThemeColor() = 0;
    virtual void set_StrokeBackThemeColor(Aspose::Words::Themes::ThemeColor value) = 0;
    virtual double get_StrokeForeTintAndShade() = 0;
    virtual void set_StrokeForeTintAndShade(double value) = 0;
    virtual double get_StrokeBackTintAndShade() = 0;
    virtual void set_StrokeBackTintAndShade(double value) = 0;
    virtual bool get_StrokeVisible() = 0;
    virtual void set_StrokeVisible(bool value) = 0;
    virtual double get_StrokeTransparency() = 0;
    virtual void set_StrokeTransparency(double value) = 0;
    virtual double get_Weight() = 0;
    virtual void set_Weight(double value) = 0;
    virtual Aspose::Words::Drawing::DashStyle get_DashStyle() = 0;
    virtual void set_DashStyle(Aspose::Words::Drawing::DashStyle value) = 0;
    virtual Aspose::Words::Drawing::JoinStyle get_JoinStyle() = 0;
    virtual void set_JoinStyle(Aspose::Words::Drawing::JoinStyle value) = 0;
    virtual Aspose::Words::Drawing::EndCap get_EndCap() = 0;
    virtual void set_EndCap(Aspose::Words::Drawing::EndCap value) = 0;
    virtual Aspose::Words::Drawing::ShapeLineStyle get_LineStyle() = 0;
    virtual void set_LineStyle(Aspose::Words::Drawing::ShapeLineStyle value) = 0;
    virtual Aspose::Words::Drawing::ArrowType get_StartArrowType() = 0;
    virtual void set_StartArrowType(Aspose::Words::Drawing::ArrowType value) = 0;
    virtual Aspose::Words::Drawing::ArrowType get_EndArrowType() = 0;
    virtual void set_EndArrowType(Aspose::Words::Drawing::ArrowType value) = 0;
    virtual Aspose::Words::Drawing::ArrowWidth get_StartArrowWidth() = 0;
    virtual void set_StartArrowWidth(Aspose::Words::Drawing::ArrowWidth value) = 0;
    virtual Aspose::Words::Drawing::ArrowLength get_StartArrowLength() = 0;
    virtual void set_StartArrowLength(Aspose::Words::Drawing::ArrowLength value) = 0;
    virtual Aspose::Words::Drawing::ArrowWidth get_EndArrowWidth() = 0;
    virtual void set_EndArrowWidth(Aspose::Words::Drawing::ArrowWidth value) = 0;
    virtual Aspose::Words::Drawing::ArrowLength get_EndArrowLength() = 0;
    virtual void set_EndArrowLength(Aspose::Words::Drawing::ArrowLength value) = 0;
    virtual System::ArrayPtr<uint8_t> get_StrokeImageBytes() = 0;
    virtual Aspose::Words::Drawing::Core::LineFillType get_LineFillType() = 0;
    virtual void set_LineFillType(Aspose::Words::Drawing::Core::LineFillType value) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_StrokeThemeProvider() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_StrokeFill() = 0;
    virtual void set_StrokeFill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> value) = 0;

};/// \endcond

}
}
}
}
