//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/TiffCompression.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies what type of compression to apply when saving page images into a TIFF file.
enum class ASPOSE_WORDS_SHARED_CLASS TiffCompression
{
    /// Specifies no compression.
    None = 0,
    /// Specifies the RLE compression scheme.
    Rle = 1,
    /// Specifies the LZW compression scheme.
    /// In Java emulated by Deflate (Zip) compression.
    Lzw = 2,
    /// Specifies the CCITT3 compression scheme.
    Ccitt3 = 3,
    /// Specifies the CCITT4 compression scheme.
    Ccitt4 = 4
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::TiffCompression>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::TiffCompression, const char_t*>, 5>& values();
};
