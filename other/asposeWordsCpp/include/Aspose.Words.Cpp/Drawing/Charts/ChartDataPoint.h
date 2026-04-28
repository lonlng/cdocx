//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataPoint.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/Drawing/Charts/IChartDataPoint.h>
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
class ChartMarker;

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

/// Allows to specify formatting of a single data point on the chart.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartDataPoint : public Aspose::Words::Drawing::Charts::IChartDataPoint, public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef ChartDataPoint ThisType;
    typedef Aspose::Words::Drawing::Charts::IChartDataPoint BaseType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Index of the data point this object applies formatting to.
    ASPOSE_WORDS_SHARED_API int32_t get_Index();
    /// Specifies the amount the data point shall be moved from the center of the pie.
    /// Can be negative, negative means that property is not set and no explosion should be applied.
    /// Applies only to Pie charts.
    ASPOSE_WORDS_SHARED_API int32_t get_Explosion() override;
    /// Specifies the amount the data point shall be moved from the center of the pie.
    /// Can be negative, negative means that property is not set and no explosion should be applied.
    /// Applies only to Pie charts.
    ASPOSE_WORDS_SHARED_API void set_Explosion(int32_t value) override;
    /// Specifies whether the parent element shall inverts its colors if the value is negative.
    ASPOSE_WORDS_SHARED_API bool get_InvertIfNegative() override;
    /// Specifies whether the parent element shall inverts its colors if the value is negative.
    ASPOSE_WORDS_SHARED_API void set_InvertIfNegative(bool value) override;
    /// Specifies whether the bubbles in Bubble chart should have a 3-D effect applied to them.
    ASPOSE_WORDS_SHARED_API bool get_Bubble3D() override;
    /// Specifies whether the bubbles in Bubble chart should have a 3-D effect applied to them.
    ASPOSE_WORDS_SHARED_API void set_Bubble3D(bool value) override;
    /// Provides access to fill and line formatting of this data point.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();
    /// Specifies chart data marker.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartMarker> get_Marker() override;

    /// Clears format of this data point. The properties are set to the default values defined in the parent series.
    ASPOSE_WORDS_SHARED_API void ClearFormat();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartDataPoint();

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
    System::WeakPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

    void MaterializeSpPr() override;

};

}
}
}
}
