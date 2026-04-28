//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/RevisionColor.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Allows to specify color of document revisions.
enum class ASPOSE_WORDS_SHARED_CLASS RevisionColor
{
    /// Default.
    Auto = 0,
    /// Represents 000000 color.
    Black = 1,
    /// Represents 2e97d3 color.
    Blue = 2,
    /// Represents 84a35b color.
    BrightGreen = 3,
    /// Represents 0000ff color.
    ClassicBlue = 4,
    /// Represents ff0000 color.
    ClassicRed = 5,
    /// Represents 376e96 color.
    DarkBlue = 6,
    /// Represents 881824 color.
    DarkRed = 7,
    /// Represents e09a2b color.
    DarkYellow = 8,
    /// Represents a0a3a9 color.
    Gray25 = 9,
    /// Represents 50565e color.
    Gray50 = 10,
    /// Represents 2c6234 color.
    Green = 11,
    /// Represents ce338f color.
    Pink = 12,
    /// Represents b5082e color.
    Red = 13,
    /// Represents 1b9cab color.
    Teal = 14,
    /// Represents 3eafc2 color.
    Turquoise = 15,
    /// Represents 633277 color.
    Violet = 16,
    /// Represents ffffff color.
    White = 17,
    /// Represents fad272 color.
    Yellow = 18,
    /// Represents fce6f4 color.
    LightPink = 19,
    /// Represents e1f2fa color.
    LightBlue = 20,
    /// Represents fef4de color.
    LightYellow = 21,
    /// Represents eadfef color.
    LightPurple = 22,
    /// Represents fce3d0 color.
    LightOrange = 23,
    /// Represents e9f8ce color.
    LightGreen = 24,
    /// Represents efeded color.
    Gray = 25,
    /// No color is used to highlight revision changes.
    NoHighlight = 26,
    /// Revisions of each author receive their own color for highlighting from a predefined set of hi-contrast colors.
    ByAuthor = 27
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Layout::RevisionColor>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::RevisionColor, const char_t*>, 28>& values();
};
