//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/RevisionTextEffect.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Allows to specify decoration effect for revisions of document text.
enum class ASPOSE_WORDS_SHARED_CLASS RevisionTextEffect
{
    /// Revised content has no special effects applied.
    /// This corresponds to <see cref="Aspose::Words::Layout::RevisionColor::NoHighlight">NoHighlight</see>.
    None = 0,
    /// Revised content is highlighted with color only.
    Color = 1,
    /// Revised content is made bold and colored.
    Bold = 2,
    /// Revised content is made italic and colored.
    Italic = 3,
    /// Revised content is underlined and colored.
    Underline = 4,
    /// Revised content is double underlined and colored.
    DoubleUnderline = 5,
    /// Revised content is stroked through and colored.
    StrikeThrough = 6,
    /// Revised content is double stroked through and colored.
    DoubleStrikeThrough = 7,
    /// Revised content is hidden.
    Hidden = 8
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Layout::RevisionTextEffect>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::RevisionTextEffect, const char_t*>, 9>& values();
};
