//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TextureIndex.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies shading texture.
enum class ASPOSE_WORDS_SHARED_CLASS TextureIndex
{
    Texture10Percent = 3,
    Texture12Pt5Percent = 37,
    Texture15Percent = 38,
    Texture17Pt5Percent = 39,
    Texture20Percent = 4,
    Texture22Pt5Percent = 40,
    Texture25Percent = 5,
    Texture27Pt5Percent = 41,
    Texture2Pt5Percent = 35,
    Texture30Percent = 6,
    Texture32Pt5Percent = 42,
    Texture35Percent = 43,
    Texture37Pt5Percent = 44,
    Texture40Percent = 7,
    Texture42Pt5Percent = 45,
    Texture45Percent = 46,
    Texture47Pt5Percent = 47,
    Texture50Percent = 8,
    Texture52Pt5Percent = 48,
    Texture55Percent = 49,
    Texture57Pt5Percent = 50,
    Texture5Percent = 2,
    Texture60Percent = 9,
    Texture62Pt5Percent = 51,
    Texture65Percent = 52,
    Texture67Pt5Percent = 53,
    Texture70Percent = 10,
    Texture72Pt5Percent = 54,
    Texture75Percent = 11,
    Texture77Pt5Percent = 55,
    Texture7Pt5Percent = 36,
    Texture80Percent = 12,
    Texture82Pt5Percent = 56,
    Texture85Percent = 57,
    Texture87Pt5Percent = 58,
    Texture90Percent = 13,
    Texture92Pt5Percent = 59,
    Texture95Percent = 60,
    Texture97Pt5Percent = 61,
    TextureCross = 24,
    TextureDarkCross = 18,
    TextureDarkDiagonalCross = 19,
    TextureDarkDiagonalDown = 16,
    TextureDarkDiagonalUp = 17,
    TextureDarkHorizontal = 14,
    TextureDarkVertical = 15,
    TextureDiagonalCross = 25,
    TextureDiagonalDown = 22,
    TextureDiagonalUp = 23,
    TextureHorizontal = 20,
    TextureNone = 0,
    TextureSolid = 1,
    TextureVertical = 21,
    /// Specifies that there shall be no pattern used on the current shaded region
    /// (i.e. the pattern shall be a complete fill with the background color).
    TextureNil = 65535
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::TextureIndex>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::TextureIndex, const char_t*>, 54>& values();
};
