//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisTimeUnit.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the unit of time for axes.
enum class ASPOSE_WORDS_SHARED_CLASS AxisTimeUnit
{
    /// Specifies that unit was not set explicitly and default value should be used.
    Automatic,
    /// Specifies that the chart data shall be shown in days.
    Days,
    /// Specifies that the chart data shall be shown in months.
    Months,
    /// Specifies that the chart data shall be shown in years.
    Years
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::AxisTimeUnit>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::AxisTimeUnit, const char_t*>, 4>& values();
};
