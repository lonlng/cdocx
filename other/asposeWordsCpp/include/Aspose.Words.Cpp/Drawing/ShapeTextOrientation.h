//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ShapeTextOrientation.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies orientation of text in shapes.
enum class ASPOSE_WORDS_SHARED_CLASS ShapeTextOrientation
{
    /// Text is arranged horizontally (lr-tb).
    Horizontal,
    /// Text is rotated 90 degrees to the right to appear from top to bottom (tb-rl).
    Downward,
    /// Text is rotated 90 degrees to the left to appear from bottom to top (bt-lr).
    Upward,
    /// Far East characters appear vertical, other text is rotated 90 degrees
    /// to the right to appear from top to bottom (tb-rl-v).
    VerticalFarEast,
    /// Far East characters appear vertical, other text is rotated 90 degrees
    /// to the right to appear from top to bottom vertically, then left to right horizontally  (tb-lr-v).
    VerticalRotatedFarEast,
    /// Text is vertical, with one letter on top of the other.
    WordArtVertical,
    /// Text is vertical, with one letter on top of the other, then right to left horizontally.
    WordArtVerticalRightToLeft
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ShapeTextOrientation>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ShapeTextOrientation, const char_t*>, 7>& values();
};
