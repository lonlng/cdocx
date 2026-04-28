//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ArrowLength.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Length of the arrow at the end of a line.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_StartArrowLength
/// @sa Aspose::Words::Drawing::Stroke::get_EndArrowLength
enum class ASPOSE_WORDS_SHARED_CLASS ArrowLength
{
    Short = 0,
    Medium = 1,
    Long = 2,
    /// Same as <see cref="Aspose::Words::Drawing::ArrowLength::Short">Short</see>.
    Default = static_cast<int32_t>(Short)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ArrowLength>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ArrowLength, const char_t*>, 4>& values();
};
