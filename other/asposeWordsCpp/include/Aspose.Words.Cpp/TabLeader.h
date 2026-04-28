//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TabLeader.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the type of the leader line displayed under the tab character.
enum class ASPOSE_WORDS_SHARED_CLASS TabLeader
{
    /// No leader line is displayed.
    None = 0,
    /// The leader line is made up from dots.
    Dots = 1,
    /// The leader line is made up from dashes.
    Dashes = 2,
    /// The leader line is a single line.
    Line = 3,
    /// The leader line is a single thick line.
    Heavy = 4,
    /// The leader line is made up from middle-dots.
    MiddleDot = 5
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::TabLeader>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::TabLeader, const char_t*>, 6>& values();
};
