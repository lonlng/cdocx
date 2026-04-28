//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartXValueType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Allows to specify type of an X value of a chart series.
enum class ASPOSE_WORDS_SHARED_CLASS ChartXValueType
{
    /// Specifies that an X value is a string category.
    String,
    /// Specifies that an X value is a double-precision floating-point number.
    Double,
    /// Specifies that an X value is a date and time of day.
    DateTime,
    /// Specifies that an X value is a time of day.
    Time,
    /// Specifies that an X value is a multilevel value.
    /// 
    /// @sa Aspose::Words::Drawing::Charts::ChartMultilevelValue
    Multilevel
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartXValueType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartXValueType, const char_t*>, 5>& values();
};
