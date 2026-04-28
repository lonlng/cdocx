//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/EndCap.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies line cap style.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_EndCap
enum class ASPOSE_WORDS_SHARED_CLASS EndCap
{
    /// Rounded ends.
    Round = 0,
    /// Square protrudes by half line width.
    Square = 1,
    /// Line ends at end point.
    Flat = 2,
    /// Default value is <see cref="Aspose::Words::Drawing::EndCap::Flat">Flat</see>.
    Default = static_cast<int32_t>(Flat)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::EndCap>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::EndCap, const char_t*>, 4>& values();
};
