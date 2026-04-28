//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LineStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies line style of a <see cref="Aspose::Words::Border">Border</see>.
enum class ASPOSE_WORDS_SHARED_CLASS LineStyle
{
    None = 0,
    Single = 1,
    Thick = 2,
    Double = 3,
    Hairline = 5,
    Dot = 6,
    DashLargeGap = 7,
    DotDash = 8,
    DotDotDash = 9,
    Triple = 10,
    ThinThickSmallGap = 11,
    ThickThinSmallGap = 12,
    ThinThickThinSmallGap = 13,
    ThinThickMediumGap = 14,
    ThickThinMediumGap = 15,
    ThinThickThinMediumGap = 16,
    ThinThickLargeGap = 17,
    ThickThinLargeGap = 18,
    ThinThickThinLargeGap = 19,
    Wave = 20,
    DoubleWave = 21,
    DashSmallGap = 22,
    DashDotStroker = 23,
    Emboss3D = 24,
    Engrave3D = 25,
    Outset = 26,
    Inset = 27
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::LineStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LineStyle, const char_t*>, 27>& values();
};
