//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfFontEmbeddingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words should embed fonts.
enum class ASPOSE_WORDS_SHARED_CLASS PdfFontEmbeddingMode
{
    /// %Aspose.Words embeds all fonts.
    EmbedAll = 0,
    /// %Aspose.Words embeds all fonts excepting standard Windows fonts Arial and Times New Roman.
    /// Only Arial and Times New Roman fonts are affected in this mode because MS Word doesn't embed
    /// only these fonts when saving document to PDF.
    EmbedNonstandard = 1,
    /// %Aspose.Words do not embed any fonts.
    EmbedNone = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfFontEmbeddingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfFontEmbeddingMode, const char_t*>, 3>& values();
};
