//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/PresetTexture.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies texture to be used to fill a shape.
enum class ASPOSE_WORDS_SHARED_CLASS PresetTexture
{
    /// No Texture.
    None = -1,
    /// Blue tissue paper texture.
    BlueTissuePaper = 1,
    /// Bouquet texture.
    Bouquet = 2,
    /// Brown marble texture.
    BrownMarble = 3,
    /// Canvas texture.
    Canvas = 4,
    /// Cork texture.
    Cork = 5,
    /// Denim texture.
    Denim = 6,
    /// Fish fossil texture.
    FishFossil = 7,
    /// Granite texture.
    Granite = 8,
    /// Green marble texture.
    GreenMarble = 9,
    /// Medium wood texture.
    MediumWood = 10,
    /// Newsprint texture.
    Newsprint = 11,
    /// Oak texture.
    Oak = 12,
    /// Paper bag texture.
    PaperBag = 13,
    /// Papyrus texture.
    Papyrus = 14,
    /// Parchment texture.
    Parchment = 15,
    /// Pink tissue paper texture.
    PinkTissuePaper = 16,
    /// Purple mesh texture.
    PurpleMesh = 17,
    /// Recycled paper texture.
    RecycledPaper = 18,
    /// Sand texture.
    Sand = 19,
    /// Stationery texture.
    Stationery = 20,
    /// Walnut texture.
    Walnut = 21,
    /// Water droplets texture.
    WaterDroplets = 22,
    /// White marble texture.
    WhiteMarble = 23,
    /// Woven mat texture.
    WovenMat = 24
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::PresetTexture>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::PresetTexture, const char_t*>, 25>& values();
};
