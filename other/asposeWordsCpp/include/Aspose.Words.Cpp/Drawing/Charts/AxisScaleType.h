//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisScaleType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the possible scale types for an axis.
enum class ASPOSE_WORDS_SHARED_CLASS AxisScaleType
{
    /// Linear scaling.
    Linear,
    /// Logarithmic scaling.
    Logarithmic
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::AxisScaleType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::AxisScaleType, const char_t*>, 2>& values();
};
