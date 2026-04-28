//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/Dml/Themes/IThemeProvider.h
#pragma once

#include <system/object.h>
#include <system/enum_helpers.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Core/Dml/Themes/ThemeFontCore.h>
#include <Aspose.Words.Cpp/Themes/ThemeColor.h>

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
namespace Fills
{
class DmlFill;
}
namespace Outlines
{
class DmlOutline;
}
}
}
}
namespace Themes
{
class EffectStyle;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

namespace Dml {

namespace Themes {

/// \cond
class IThemeProvider : public virtual System::Object
{
    typedef IThemeProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::String GetFontName(Aspose::Words::Drawing::Core::Dml::Themes::ThemeFontCore themeFont) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Colors::DmlColor> GetThemeColor(Aspose::Words::Themes::ThemeColor color) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> GetBackgroundFillStyle(int32_t index) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> GetFillStyle(int32_t index) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> GetLineStyle(int32_t index) = 0;
    virtual System::SharedPtr<Aspose::Words::Themes::EffectStyle> GetEffectStyle(int32_t index) = 0;
    virtual void OnChange() = 0;

};/// \endcond

}
}
}
}
}
}
