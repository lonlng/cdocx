//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TextOrientation.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies orientation of text on a page, in a table cell or a text frame.
enum class ASPOSE_WORDS_SHARED_CLASS TextOrientation
{
    /// Text is arranged horizontally (lr-tb).
    Horizontal = 0,
    /// Text is rotated 90 degrees to the right to appear from top to bottom (tb-rl).
    Downward = 1,
    /// Text is rotated 90 degrees to the left to appear from bottom to top (bt-lr).
    Upward = 3,
    /// Text is arranged horizontally, but Far East characters are rotated 90 degrees to the left (lr-tb-v).
    HorizontalRotatedFarEast = 4,
    /// Far East characters appear vertical, other text is rotated 90 degrees
    /// to the right to appear from top to bottom (tb-rl-v).
    VerticalFarEast = 5,
    /// Far East characters appear vertical, other text is rotated 90 degrees
    /// to the right to appear from top to bottom vertically, then left to right horizontally  (tb-lr-v).
    VerticalRotatedFarEast = 7
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::TextOrientation>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::TextOrientation, const char_t*>, 6>& values();
};
