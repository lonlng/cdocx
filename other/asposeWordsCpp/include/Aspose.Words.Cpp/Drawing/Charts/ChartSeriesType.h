//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartSeriesType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies a type of a chart series.
enum class ASPOSE_WORDS_SHARED_CLASS ChartSeriesType
{
    /// Represents an Area chart series.
    Area,
    /// Represents a Stacked Area chart series.
    AreaStacked,
    /// Represents a 100\% Stacked Area chart series.
    AreaPercentStacked,
    /// Represents a 3D Area chart series.
    Area3D,
    /// Represents a 3D Stacked Area chart series.
    Area3DStacked,
    /// Represents a 3D 100\% Stacked Area chart series.
    Area3DPercentStacked,
    /// Represents a Bar chart series.
    Bar,
    /// Represents a Stacked Bar chart series.
    BarStacked,
    /// Represents a 100\% Stacked Bar chart series.
    BarPercentStacked,
    /// Represents a 3D Bar chart series.
    Bar3D,
    /// Represents a 3D Stacked Bar chart series.
    Bar3DStacked,
    /// Represents a 3D 100\% Stacked Bar chart series.
    Bar3DPercentStacked,
    /// Represents a Bubble chart series.
    Bubble,
    /// Represents a 3D Bubble chart series.
    Bubble3D,
    /// Represents a Column chart series.
    Column,
    /// Represents a Stacked Column chart series.
    ColumnStacked,
    /// Represents a 100\% Stacked Column chart series.
    ColumnPercentStacked,
    /// Represents a 3D Column chart series.
    Column3D,
    /// Represents a 3D Stacked Column chart series.
    Column3DStacked,
    /// Represents a 3D 100\% Stacked Column chart series.
    Column3DPercentStacked,
    /// Represents a 3D Clustered Column chart series.
    Column3DClustered,
    /// Represents a Doughnut chart series.
    Doughnut,
    /// Represents a Line chart series.
    Line,
    /// Represents a Stacked Line chart series.
    LineStacked,
    /// Represents a 100\% Stacked Line chart series.
    LinePercentStacked,
    /// Represents a 3D Line chart series.
    Line3D,
    /// Represents a Pie chart series.
    Pie,
    /// Represents a 3D Pie chart series.
    Pie3D,
    /// Represents a Pie of Bar chart series.
    PieOfBar,
    /// Represents a Pie of Pie chart series.
    PieOfPie,
    /// Represents a Radar chart series.
    Radar,
    /// Represents a Scatter chart series.
    Scatter,
    /// Represents a Stock chart series.
    Stock,
    /// Represents a Surface chart series.
    Surface,
    /// Represents a 3D Surface chart series.
    Surface3D,
    /// Represents a Treemap chart series.
    Treemap,
    /// Represents a Sunburst chart series.
    Sunburst,
    /// Represents a Histogram chart series.
    Histogram,
    /// Represents a Pareto chart series.
    Pareto,
    /// Represents a Pareto Line chart series.
    ParetoLine,
    /// Represents a Box and Whisker chart series.
    BoxAndWhisker,
    /// Represents a Waterfall chart series.
    Waterfall,
    /// Represents a Funnel chart series.
    Funnel,
    /// Represents a Region Map chart series.
    RegionMap
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartSeriesType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartSeriesType, const char_t*>, 44>& values();
};
