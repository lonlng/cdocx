//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TextEffect.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Animation effect for text runs.
enum class ASPOSE_WORDS_SHARED_CLASS TextEffect
{
    None = 0,
    LasVegasLights = 1,
    BlinkingBackground = 2,
    SparkleText = 3,
    MarchingBlackAnts = 4,
    MarchingRedAnts = 5,
    Shimmer = 6
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::TextEffect>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::TextEffect, const char_t*>, 7>& values();
};
