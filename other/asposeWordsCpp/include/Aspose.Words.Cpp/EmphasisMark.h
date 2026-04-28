//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/EmphasisMark.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies possible types of emphasis mark.
enum class ASPOSE_WORDS_SHARED_CLASS EmphasisMark
{
    /// No emphasis mark.
    None = 0x00,
    /// Emphasis mark is a solid black circle displayed above text.
    OverSolidCircle = 0x01,
    /// Emphasis mark is a comma character displayed above text.
    OverComma = 0x02,
    /// Emphasis mark is an empty white circle displayed above text.
    OverWhiteCircle = 0x03,
    /// Emphasis mark is a solid black circle displayed below text.
    UnderSolidCircle = 0x04
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::EmphasisMark>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::EmphasisMark, const char_t*>, 5>& values();
};
