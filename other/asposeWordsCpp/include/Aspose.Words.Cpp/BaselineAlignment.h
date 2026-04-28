//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BaselineAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies fonts vertical position on a line.
enum class ASPOSE_WORDS_SHARED_CLASS BaselineAlignment
{
    /// Aligns along the top of each font.
    Top = 0,
    /// Aligns the center points of each font.
    Center = 1,
    /// Aligns to the baseline of the paragraph.
    Baseline = 2,
    /// Aligns to the bottom of each font.
    Bottom = 3,
    /// Baseline is adjusted automatically.
    Auto = 4
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::BaselineAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::BaselineAlignment, const char_t*>, 5>& values();
};
