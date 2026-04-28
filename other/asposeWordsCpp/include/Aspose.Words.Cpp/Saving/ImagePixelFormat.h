//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ImagePixelFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the pixel format for the generated images of document pages.
enum class ASPOSE_WORDS_SHARED_CLASS ImagePixelFormat
{
    /// 16 bits per pixel, RGB.
    Format16BppRgb555 = 0,
    /// 16 bits per pixel, RGB.
    Format16BppRgb565 = 1,
    /// 16 bits per pixel, ARGB.
    Format16BppArgb1555 = 2,
    /// 24 bits per pixel, RGB.
    Format24BppRgb = 3,
    /// 32 bits per pixel, RGB.
    Format32BppRgb = 4,
    /// 32 bits per pixel, ARGB.
    Format32BppArgb = 5,
    /// 32 bits per pixel, ARGB, premultiplied alpha.
    Format32BppPArgb = 6,
    /// 48 bits per pixel, RGB.
    Format48BppRgb = 7,
    /// 64 bits per pixel, ARGB.
    Format64BppArgb = 8,
    /// 64 bits per pixel, ARGB, premultiplied alpha.
    Format64BppPArgb = 9,
    /// 1 bit per pixel, Indexed.
    Format1bppIndexed = 10
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::ImagePixelFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::ImagePixelFormat, const char_t*>, 11>& values();
};
