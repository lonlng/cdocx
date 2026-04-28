//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisCrosses.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies the possible crossing points for an axis.
enum class ASPOSE_WORDS_SHARED_CLASS AxisCrosses
{
    /// The category axis crosses at the zero point of the value axis (if possible), or at the minimum value
    /// if the minimum is greater than zero, or at the maximum if the maximum is less than zero.
    Automatic,
    /// A perpendicular axis crosses at the maximum value of the axis.
    Maximum,
    /// A perpendicular axis crosses at the minimum value of the axis.
    Minimum,
    /// A perpendicular axis crosses at the specified value of the axis.
    Custom
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::AxisCrosses>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::AxisCrosses, const char_t*>, 4>& values();
};
