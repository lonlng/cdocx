//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies type of a chart.
enum class ASPOSE_WORDS_SHARED_CLASS ChartType
{
    /// Area chart.
    Area,
    /// Stacked Area chart.
    AreaStacked,
    /// 100\% Stacked Area chart.
    AreaPercentStacked,
    /// 3D Area chart.
    Area3D,
    /// 3D Stacked Area chart.
    Area3DStacked,
    /// 3D 100\% Stacked Area chart.
    Area3DPercentStacked,
    /// Bar chart.
    Bar,
    /// Stacked Bar chart.
    BarStacked,
    /// 100\% Stacked Bar chart.
    BarPercentStacked,
    /// 3D Bar chart.
    Bar3D,
    /// 3D Stacked Bar chart.
    Bar3DStacked,
    /// 3D 100\% Stacked Bar chart.
    Bar3DPercentStacked,
    /// Bubble chart.
    Bubble,
    /// 3D Bubble chart.
    Bubble3D,
    /// Column chart.
    Column,
    /// Stacked Column chart.
    ColumnStacked,
    /// 100\% Stacked Column chart.
    ColumnPercentStacked,
    /// 3D Column chart.
    Column3D,
    /// 3D Stacked Column chart.
    Column3DStacked,
    /// 3D 100\% Stacked Column chart.
    Column3DPercentStacked,
    /// 3D Clustered Column chart.
    Column3DClustered,
    /// Doughnut chart.
    Doughnut,
    /// Line chart.
    Line,
    /// Stacked Line chart.
    LineStacked,
    /// 100\% Stacked Line chart.
    LinePercentStacked,
    /// 3D Line chart.
    Line3D,
    /// Pie chart.
    Pie,
    /// 3D Pie chart.
    Pie3D,
    /// Pie of Bar chart.
    PieOfBar,
    /// Pie of Pie chart.
    PieOfPie,
    /// Radar chart.
    Radar,
    /// Scatter chart.
    Scatter,
    /// Stock chart.
    Stock,
    /// Surface chart.
    Surface,
    /// 3D Surface chart.
    Surface3D,
    /// Treemap chart.
    Treemap,
    /// Sunburst chart.
    Sunburst,
    /// Histogram chart.
    Histogram,
    /// Pareto chart.
    Pareto,
    /// Box and Whisker chart.
    BoxAndWhisker,
    /// Waterfall chart.
    Waterfall,
    /// Funnel chart.
    Funnel
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartType, const char_t*>, 42>& values();
};
