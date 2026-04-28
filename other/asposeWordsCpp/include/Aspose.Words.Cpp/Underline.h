//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Underline.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Indicates type of the underline applied to a font.
enum class ASPOSE_WORDS_SHARED_CLASS Underline
{
    None = 0,
    Single = 1,
    Words = 2,
    Double = 3,
    Dotted = 4,
    Thick = 6,
    Dash = 7,
    DashLong = 39,
    DotDash = 9,
    DotDotDash = 10,
    Wavy = 11,
    DottedHeavy = 20,
    DashHeavy = 23,
    DashLongHeavy = 55,
    DotDashHeavy = 25,
    DotDotDashHeavy = 26,
    WavyHeavy = 27,
    WavyDouble = 43
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::Underline>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Underline, const char_t*>, 18>& values();
};
