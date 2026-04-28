//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfTextCompression.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies a type of compression applied to all content in the PDF file except images.
enum class ASPOSE_WORDS_SHARED_CLASS PdfTextCompression
{
    /// No compression.
    None = 0,
    /// Flate (ZIP) compression.
    Flate = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfTextCompression>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfTextCompression, const char_t*>, 2>& values();
};
