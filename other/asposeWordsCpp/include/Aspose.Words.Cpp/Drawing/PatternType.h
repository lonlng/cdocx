//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/PatternType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the fill pattern to be used to fill a shape.
enum class ASPOSE_WORDS_SHARED_CLASS PatternType
{
    /// No pattern.
    None = -1,
    /// 10\% of the foreground color.
    Percent10 = 1,
    /// 20\% of the foreground color.
    Percent20 = 2,
    /// 25\% of the foreground color.
    Percent25 = 3,
    /// 30\% of the foreground color.
    Percent30 = 4,
    /// 40\% of the foreground color
    Percent40 = 5,
    /// 50\% of the foreground color
    Percent50 = 6,
    /// 5\% of the foreground color.
    Percent5 = 7,
    /// 60\% of the foreground color.
    Percent60 = 8,
    /// 70\% of the foreground color.
    Percent70 = 9,
    /// 75\% of the foreground color.
    Percent75 = 10,
    /// 80\% of the foreground color.
    Percent80 = 11,
    /// 90\% of the foreground color.
    Percent90 = 12,
    /// Cross.
    Cross = 13,
    /// Dark downward diagonal.
    DarkDownwardDiagonal = 14,
    /// Dark horizontal.
    DarkHorizontal = 15,
    /// Dark upward diagonal.
    DarkUpwardDiagonal = 16,
    /// Dark vertical.
    DarkVertical = 17,
    /// Dashed downward diagonal.
    DashedDownwardDiagonal = 18,
    /// Dashed horizontal.
    DashedHorizontal = 19,
    /// Dashed upward diagonal.
    DashedUpwardDiagonal = 20,
    /// Dashed vertical.
    DashedVertical = 21,
    /// Diagonal brick.
    DiagonalBrick = 22,
    /// Diagonal cross.
    DiagonalCross = 23,
    /// Pattern divot.
    Divot = 24,
    /// Dotted diamond.
    DottedDiamond = 25,
    /// Dotted grid.
    DottedGrid = 26,
    /// Downward diagonal.
    DownwardDiagonal = 27,
    /// Horizontal.
    Horizontal = 28,
    /// Horizontal brick.
    HorizontalBrick = 29,
    /// Large checker board.
    LargeCheckerBoard = 30,
    /// Large confetti.
    LargeConfetti = 31,
    /// Large grid.
    LargeGrid = 32,
    /// Light downward diagonal.
    LightDownwardDiagonal = 33,
    /// Light horizontal.
    LightHorizontal = 34,
    /// Light upward diagonal.
    LightUpwardDiagonal = 36,
    /// Light vertical.
    LightVertical = 37,
    /// Narrow horizontal.
    NarrowHorizontal = 38,
    /// Narrow vertical.
    NarrowVertical = 39,
    /// Outlined diamond.
    OutlinedDiamond = 40,
    /// Plaid.
    Plaid = 41,
    /// Shingle.
    Shingle = 42,
    /// Small checker board.
    SmallCheckerBoard = 43,
    /// Small confetti.
    SmallConfetti = 44,
    /// Small grid.
    SmallGrid = 45,
    /// Solid diamond.
    SolidDiamond = 46,
    /// Sphere.
    Sphere = 47,
    /// Trellis.
    Trellis = 48,
    /// Upward diagonal.
    UpwardDiagonal = 49,
    /// Vertical.
    Vertical = 50,
    /// Wave.
    Wave = 51,
    /// Weave.
    Weave = 52,
    /// Wide downward diagonal.
    WideDownwardDiagonal = 53,
    /// Wide upward diagonal.
    WideUpwardDiagonal = 54,
    /// Zig zag.
    ZigZag = 55
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::PatternType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::PatternType, const char_t*>, 55>& values();
};
