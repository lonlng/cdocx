//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ArrowWidth.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Width of the arrow at the end of a line.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_StartArrowWidth
/// @sa Aspose::Words::Drawing::Stroke::get_EndArrowWidth
enum class ASPOSE_WORDS_SHARED_CLASS ArrowWidth
{
    Narrow = 0,
    Medium = 1,
    Wide = 2,
    /// Same as <see cref="Aspose::Words::Drawing::ArrowWidth::Narrow">Narrow</see>.
    Default = static_cast<int32_t>(Narrow)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ArrowWidth>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ArrowWidth, const char_t*>, 4>& values();
};
