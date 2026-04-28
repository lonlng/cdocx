//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartAxisType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies type of chart axis.
enum class ASPOSE_WORDS_SHARED_CLASS ChartAxisType
{
    /// Category axis of a chart.
    Category,
    /// Series axis of a chart.
    Series,
    /// Value axis of a chart.
    Value
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartAxisType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartAxisType, const char_t*>, 3>& values();
};
