//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/Chart.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartFormatSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/ChartStyle.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Drawing
{
namespace Charts
{
class ChartAxis;
class ChartAxisCollection;
class ChartDataTable;
class ChartFormat;
class ChartLegend;
class ChartSeriesCollection;
class ChartSeriesGroupCollection;
enum class ChartShapeType;
class ChartTitle;

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
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Provides access to the chart shape properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Chart : public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef Chart ThisType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Provides access to series collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeriesCollection> get_Series();
    /// Provides access to a series group collection of this chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeriesGroupCollection> get_SeriesGroups();
    /// Provides access to the chart title properties.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartTitle> get_Title();
    /// Provides access to the chart legend properties.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegend> get_Legend();
    /// Provides access to properties of a data table of this chart.
    /// The data table can be shown using the <see cref="Aspose::Words::Drawing::Charts::ChartDataTable::get_Show">Show</see> property.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataTable> get_DataTable();
    /// Provides access to properties of the primary X axis of the chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis> get_AxisX();
    /// Provides access to properties of the primary Y axis of the chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis> get_AxisY();
    /// Provides access to properties of the Z axis of the chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis> get_AxisZ();
    /// Gets a collection of all axes of this chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxisCollection> get_Axes();
    /// Gets the path and name of an xls/xlsx file this chart is linked to.
    ASPOSE_WORDS_SHARED_API System::String get_SourceFullName();
    /// Gets the path and name of an xls/xlsx file this chart is linked to.
    ASPOSE_WORDS_SHARED_API void set_SourceFullName(const System::String& value);
    /// Provides access to fill and line formatting of the chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();
    /// Gets the style of the chart.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartStyle get_Style();
    /// Sets the style of the chart.
    ASPOSE_WORDS_SHARED_API void set_Style(Aspose::Words::Drawing::Charts::ChartStyle value);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Chart();

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
    System::SharedPtr<System::Object> mField5;

    void MaterializeSpPr() override;

};

}
}
}
}
