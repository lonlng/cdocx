//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartMarker.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Charts/MarkerSymbol.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartFormatSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Drawing
{
namespace Charts
{

class ChartFormat;

enum class ChartShapeType;

}
namespace Core
{
namespace Dml
{
namespace Fills
{
class DmlFill;
}
namespace Outlines
{
class DmlOutline;
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

namespace Charts {

/// Represents a chart data marker.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartMarker : public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef ChartMarker ThisType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets chart marker symbol.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::MarkerSymbol get_Symbol();
    /// Sets chart marker symbol.
    ASPOSE_WORDS_SHARED_API void set_Symbol(Aspose::Words::Drawing::Charts::MarkerSymbol value);
    /// Gets chart marker size.
    /// Default value is 7.
    ASPOSE_WORDS_SHARED_API int32_t get_Size();
    /// Sets chart marker size.
    /// Default value is 7.
    ASPOSE_WORDS_SHARED_API void set_Size(int32_t value);
    /// Provides access to fill and line formatting of this marker.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartMarker();

private:

    bool get_IsFillSupported() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_Fill() override;
    void set_Fill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> get_Outline() override;
    void set_Outline(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> ) override;
    Aspose::Words::Drawing::Charts::ChartShapeType get_ShapeType() override;
    void set_ShapeType(Aspose::Words::Drawing::Charts::ChartShapeType ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_ThemeProvider() override;
    bool get_IsFormatDefined() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;

    void MaterializeSpPr() override;

protected:

};

}
}
}
}
