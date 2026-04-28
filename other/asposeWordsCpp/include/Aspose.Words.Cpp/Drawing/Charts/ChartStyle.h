//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies predefined styles of a chart.
enum class ASPOSE_WORDS_SHARED_CLASS ChartStyle
{
    /// Represents the default chart style.
    Normal,
    /// A style with muted colors.
    Muted,
    /// A style with more saturated colors.
    Saturated,
    /// A style with shaded data points.
    Shaded,
    /// A style with flat data points without gradient.
    Flat,
    /// A style with data points having a shadow.
    Shadowed,
    /// A style with gradient fill of data points.
    Gradient,
    /// A style with an original appearance of a chart.
    Original,
    /// A style with transparent data points.
    Transparent1,
    /// A style with transparent data points.
    Transparent2,
    /// A style with data points having no fill, but only an outline.
    Outline,
    /// A style with black chart background, in which data points have no fill, but only an outline.
    OutlineBlack,
    /// A style with black chart background.
    Black,
    /// A style with gray gradient chart background.
    Grey,
    /// A style with blue chart background.
    Blue,
    /// A style, in which the plot area is shaded.
    ShadedPlot
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartStyle, const char_t*>, 16>& values();
};
