//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisTickMark.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the possible positions for tick marks.
enum class ASPOSE_WORDS_SHARED_CLASS AxisTickMark
{
    /// Specifies that the tick marks shall cross the axis.
    Cross,
    /// Specifies that the tick marks shall be inside the plot area.
    Inside,
    /// Specifies that the tick marks shall be outside the plot area.
    Outside,
    /// Specifies that there shall be no tick marks.
    None
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::AxisTickMark>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::AxisTickMark, const char_t*>, 4>& values();
};
