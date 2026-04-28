//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisTickLabelPosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the possible positions for tick labels.
enum class ASPOSE_WORDS_SHARED_CLASS AxisTickLabelPosition
{
    /// Specifies the axis labels shall be at the high end of the perpendicular axis.
    High,
    /// Specifies the axis labels shall be at the low end of the perpendicular axis.
    Low,
    /// Specifies the axis labels shall be next to the axis.
    NextToAxis,
    /// Specifies the axis labels are not drawn.
    None,
    /// Specifies default value of tick labels position.
    Default = static_cast<int32_t>(NextToAxis)
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::AxisTickLabelPosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::AxisTickLabelPosition, const char_t*>, 5>& values();
};
