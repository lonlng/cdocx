//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartSeriesGroup.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Charts/ChartSeriesType.h>
#include <Aspose.Words.Cpp/Drawing/Charts/AxisGroup.h>
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

class ChartSeriesCollection;

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

/// Represents properties of a chart series group, that is, the properties of chart series of the same type
/// associated with the same axes.
/// 
/// Combo charts contains multiple chart series groups, with a separate group for each series type.
/// 
/// Also, you can create a chart series group to assign secondary axes to one or more chart series.
/// 
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartSeriesGroup : public System::Object
{
    typedef ChartSeriesGroup ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the type of chart series included in this group.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartSeriesType get_SeriesType();
    /// Gets the axis group to which this series group belongs.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::AxisGroup get_AxisGroup();
    /// Sets the axis group to which this series group belongs.
    ASPOSE_WORDS_SHARED_API void set_AxisGroup(Aspose::Words::Drawing::Charts::AxisGroup value);
    /// Provides access to properties of the X axis of this series group.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis> get_AxisX();
    /// Provides access to properties of the Y axis of this series group.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis> get_AxisY();
    /// Gets a collection of series that belong to this series group.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeriesCollection> get_Series();
    /// Gets or sets the percentage of how much the series bars or columns overlap.
    /// 
    /// Applies to series groups of all bar and column types.
    /// 
    /// The range of acceptable values is from -100 to 100 inclusive. A value of 0 indicates that there is no
    /// space between bars/columns. If the value is -100, the distance between bars/columns is equal to their width.
    /// A value of 100 means that the bars/columns overlap completely.
    ASPOSE_WORDS_SHARED_API int32_t get_Overlap();
    /// Setter for Aspose::Words::Drawing::Charts::ChartSeriesGroup::get_Overlap
    ASPOSE_WORDS_SHARED_API void set_Overlap(int32_t value);
    /// Gets or sets the percentage of gap width between chart elements.
    /// 
    /// Applies only to series groups of the bar, column, pie-of-bar, pie-of-pie, histogram, box\&whisker,
    /// waterfall and funnel types.
    /// 
    /// The range of acceptable values is from 0 to 500 inclusive. For bar/column-based series groups, the
    /// property represents the space between bar clusters as a percentage of their width. For pie-of-pie and
    /// bar-of-pie charts, this is the space between the primary and secondary sections of the chart.
    ASPOSE_WORDS_SHARED_API int32_t get_GapWidth();
    /// Setter for Aspose::Words::Drawing::Charts::ChartSeriesGroup::get_GapWidth
    ASPOSE_WORDS_SHARED_API void set_GapWidth(int32_t value);
    /// Gets or sets the size of the bubbles as a percentage of their default size.
    /// 
    /// Applies only to series groups of the <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Bubble">Bubble</see> and
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Bubble3D">Bubble3D</see> types.
    /// 
    /// The range of acceptable values is from 0 to 300 inclusive. The default value is 100.
    ASPOSE_WORDS_SHARED_API int32_t get_BubbleScale();
    /// Setter for Aspose::Words::Drawing::Charts::ChartSeriesGroup::get_BubbleScale
    ASPOSE_WORDS_SHARED_API void set_BubbleScale(int32_t value);
    /// Gets or sets the angle, in degrees, of the first slice of the parent pie chart.
    /// 
    /// Applies to series groups of the <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Pie">Pie</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Pie3D">Pie3D</see>
    /// and <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Doughnut">Doughnut</see> types.
    /// 
    /// The range of acceptable values is from 0 to 360 inclusive. The default value is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_FirstSliceAngle();
    /// Setter for Aspose::Words::Drawing::Charts::ChartSeriesGroup::get_FirstSliceAngle
    ASPOSE_WORDS_SHARED_API void set_FirstSliceAngle(int32_t value);
    /// Gets or sets the hole size of the parent doughnut chart as a percentage.
    /// 
    /// Applies only to series groups of the <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Doughnut">Doughnut</see> type.
    /// 
    /// The range of acceptable values is from 0 to 90 inclusive. The default value is 75.
    ASPOSE_WORDS_SHARED_API int32_t get_DoughnutHoleSize();
    /// Setter for Aspose::Words::Drawing::Charts::ChartSeriesGroup::get_DoughnutHoleSize
    ASPOSE_WORDS_SHARED_API void set_DoughnutHoleSize(int32_t value);
    /// Gets or sets the size of the pie chart secondary section as a percentage.
    /// 
    /// Applies to series groups of the <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::PieOfPie">PieOfPie</see> and
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::PieOfBar">PieOfBar</see> types.
    /// 
    /// The range of acceptable values is from 5 to 200 inclusive. The default value is 75.
    ASPOSE_WORDS_SHARED_API int32_t get_SecondSectionSize();
    /// Setter for Aspose::Words::Drawing::Charts::ChartSeriesGroup::get_SecondSectionSize
    ASPOSE_WORDS_SHARED_API void set_SecondSectionSize(int32_t value);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
}
