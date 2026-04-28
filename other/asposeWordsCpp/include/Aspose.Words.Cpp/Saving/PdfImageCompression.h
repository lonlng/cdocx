//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfImageCompression.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the type of compression applied to images in the PDF file.
enum class ASPOSE_WORDS_SHARED_CLASS PdfImageCompression
{
    /// Automatically selects the most appropriate compression for each image.
    Auto = 0,
    /// Jpeg compression.
    /// Does not support transparency.
    Jpeg = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfImageCompression>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfImageCompression, const char_t*>, 2>& values();
};
