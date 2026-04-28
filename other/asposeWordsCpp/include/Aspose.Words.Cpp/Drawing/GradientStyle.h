//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/GradientStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the style for a gradient fill.
enum class ASPOSE_WORDS_SHARED_CLASS GradientStyle
{
    /// No gradient.
    None = -1,
    /// Gradient running horizontally across an object.
    Horizontal = 1,
    /// Gradient running vertically down an object.
    Vertical = 2,
    /// Diagonal gradient moving from a bottom corner up to the opposite corner.
    DiagonalUp = 3,
    /// Diagonal gradient moving from a top corner down to the opposite corner.
    DiagonalDown = 4,
    /// Gradient running from a corner to the other three corners.
    FromCorner = 5,
    /// Gradient running from the center out to the corners.
    FromCenter = 6
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::GradientStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::GradientStyle, const char_t*>, 7>& values();
};
