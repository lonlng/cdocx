//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/LegendPosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the possible positions for a chart legend.
enum class ASPOSE_WORDS_SHARED_CLASS LegendPosition
{
    /// No legend will be shown for the chart.
    None,
    /// Specifies that the legend shall be drawn at the bottom of the chart.
    Bottom,
    /// Specifies that the legend shall be drawn at the left of the chart.
    Left,
    /// Specifies that the legend shall be drawn at the right of the chart.
    Right,
    /// Specifies that the legend shall be drawn at the top of the chart.
    Top,
    /// Specifies that the legend shall be drawn at the top right of the chart.
    TopRight
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::LegendPosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::LegendPosition, const char_t*>, 6>& values();
};
