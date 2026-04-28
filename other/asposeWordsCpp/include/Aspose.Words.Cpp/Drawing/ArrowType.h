//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ArrowType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the type of an arrow at a line end.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_StartArrowType
/// @sa Aspose::Words::Drawing::Stroke::get_EndArrowType
enum class ASPOSE_WORDS_SHARED_CLASS ArrowType
{
    /// The line does not have an arrow at the end.
    None = 0,
    /// The arrow is a solid triangle.
    Arrow = 1,
    /// The arrow is a "stealth" arrow.
    Stealth = 2,
    /// The line end is a solid diamond.
    Diamond = 3,
    /// The line end is a solid oval.
    Oval = 4,
    /// The arrow is an open arrow.
    Open = 5,
    /// Same as <see cref="Aspose::Words::Drawing::ArrowType::None">None</see>.
    Default = static_cast<int32_t>(None)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ArrowType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ArrowType, const char_t*>, 7>& values();
};
