//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ImageType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the type (format) of an image in a %Microsoft Word document.
/// 
/// @sa Aspose::Words::Drawing::ImageData::get_ImageType
enum class ASPOSE_WORDS_SHARED_CLASS ImageType
{
    /// The is no image data.
    NoImage = 0,
    /// An unknown image type or image type that cannot be directly stored inside a %Microsoft Word document.
    Unknown = 1,
    /// Windows Enhanced Metafile.
    Emf = 2,
    /// Windows Metafile.
    Wmf = 3,
    /// Macintosh PICT. An existing image will be preserved in a document, but inserting new
    /// PICT images into a document is not supported.
    Pict = 4,
    /// JPEG JFIF.
    Jpeg = 5,
    /// Portable Network Graphics.
    Png = 6,
    /// Windows Bitmap.
    Bmp = 7,
    /// Encapsulated PostScript.
    Eps = 8,
    /// WebP.
    WebP = 9,
    /// GIF
    Gif = 10
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ImageType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ImageType, const char_t*>, 11>& values();
};
