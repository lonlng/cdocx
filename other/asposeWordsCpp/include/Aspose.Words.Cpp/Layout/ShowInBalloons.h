//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/ShowInBalloons.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Specifies which revisions are rendered in balloons.
enum class ASPOSE_WORDS_SHARED_CLASS ShowInBalloons
{
    /// Renders insert, delete and format revisions inline.
    None = 0,
    /// Renders insert and delete revisions inline, format revisions in balloons.
    Format = 1,
    /// Renders insert revisions inline, delete and format revisions in balloons.
    FormatAndDelete = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Layout::ShowInBalloons>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::ShowInBalloons, const char_t*>, 3>& values();
};
