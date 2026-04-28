//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/Core/ComplexTypes/DmlChartStyleItem.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

namespace Core {

namespace ComplexTypes {

/// DmlChartStyleItem enumeration.
enum class DmlChartStyleItem
{
    AxisTitle,
    CategoryAxis,
    ChartArea,
    DataLabel,
    DataLabelCallout,
    DataPoint,
    DataPoint3D,
    DataPointLine,
    DataPointMarker,
    DataPointWireframe,
    DataTable,
    DownBar,
    DropLine,
    ErrorBar,
    Floor,
    GridlineMajor,
    GridlineMinor,
    HighLowLine,
    LeaderLine,
    Legend,
    PlotArea,
    PlotArea3D,
    SeriesAxis,
    SeriesLine,
    Title,
    TrendLine,
    TrendlineLabel,
    UpBar,
    ValueAxis,
    Wall
};

}
}
}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartStyleItem>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartStyleItem, const char_t*>, 30>& values();
};
