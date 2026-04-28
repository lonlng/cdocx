//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisBuiltInUnit.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the display units for an axis.
enum class ASPOSE_WORDS_SHARED_CLASS AxisBuiltInUnit
{
    /// Specifies the values on the chart shall displayed as is.
    None,
    /// Specifies the values on the chart shall be divided by a user-defined divisor. This value is not supported
    /// by the new chart types of MS Office 2016.
    Custom,
    /// Specifies the values on the chart shall be divided by 1,000,000,000.
    Billions,
    /// Specifies the values on the chart shall be divided by 100,000,000.
    HundredMillions,
    /// Specifies the values on the chart shall be divided by 100.
    Hundreds,
    /// Specifies the values on the chart shall be divided by 100,000.
    HundredThousands,
    /// Specifies the values on the chart shall be divided by 1,000,000.
    Millions,
    /// Specifies the values on the chart shall be divided by 10,000,000.
    TenMillions,
    /// Specifies the values on the chart shall be divided by 10,000.
    TenThousands,
    /// Specifies the values on the chart shall be divided by 1,000.
    Thousands,
    /// Specifies the values on the chart shall be divided by 1,000,000,000,0000.
    Trillions,
    /// Specifies the values on the chart shall be divided by 0.01. This value is supported only by the new chart
    /// types of MS Office 2016.
    Percentage
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::AxisBuiltInUnit>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::AxisBuiltInUnit, const char_t*>, 12>& values();
};
