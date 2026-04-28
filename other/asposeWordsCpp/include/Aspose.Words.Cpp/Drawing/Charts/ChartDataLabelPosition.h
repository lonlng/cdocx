//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataLabelPosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the position for a chart data label.
enum class ASPOSE_WORDS_SHARED_CLASS ChartDataLabelPosition
{
    /// Specifies that a data label should be displayed centered on a data marker.
    Center,
    /// Specifies that a data label should be displayed to the left of a data marker.
    Left,
    /// Specifies that a data label should be displayed to the right of a data marker.
    Right,
    /// Specifies that a data label should be displayed above a data marker.
    Above,
    /// Specifies that a data label should be displayed below a data marker.
    Below,
    /// Specifies that a data label should be displayed inside the base of a data marker.
    InsideBase,
    /// Specifies that a data label should be displayed inside the end of a data marker.
    InsideEnd,
    /// Specifies that a data label should be displayed outside the end of a data marker.
    OutsideEnd,
    /// Specifies that a data label should be displayed in the most appropriate position.
    BestFit
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartDataLabelPosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartDataLabelPosition, const char_t*>, 9>& values();
};
