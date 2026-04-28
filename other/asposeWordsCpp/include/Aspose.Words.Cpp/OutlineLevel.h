//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/OutlineLevel.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the outline level of a paragraph in the document.
enum class ASPOSE_WORDS_SHARED_CLASS OutlineLevel
{
    /// The paragraph is at the outline level 1 (topmost level).
    Level1 = 0,
    /// The paragraph is at the outline level 2.
    Level2 = 1,
    /// The paragraph is at the outline level 3.
    Level3 = 2,
    /// The paragraph is at the outline level 4.
    Level4 = 3,
    /// The paragraph is at the outline level 5.
    Level5 = 4,
    /// The paragraph is at the outline level 6.
    Level6 = 5,
    /// The paragraph is at the outline level 7.
    Level7 = 6,
    /// The paragraph is at the outline level 8.
    Level8 = 7,
    /// The paragraph is at the outline level 9.
    Level9 = 8,
    /// The paragraph is at the level of the main text.
    BodyText = 9
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::OutlineLevel>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::OutlineLevel, const char_t*>, 10>& values();
};
