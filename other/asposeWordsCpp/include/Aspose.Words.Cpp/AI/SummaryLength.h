//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/SummaryLength.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace AI {

/// Enumerates possible lengths of summary.
enum class ASPOSE_WORDS_SHARED_CLASS SummaryLength
{
    /// Try to generate 1-2 sentences.
    VeryShort = 0,
    /// Try to generate 3-4 sentences.
    Short = 1,
    /// Try to generate 5-6 sentences.
    Medium = 2,
    /// Try to generate 7-10 sentences.
    Long = 3,
    /// Try to generate 11-20 sentences.
    VeryLong = 4
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::AI::SummaryLength>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::AI::SummaryLength, const char_t*>, 5>& values();
};
