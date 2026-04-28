//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfAttachmentsEmbeddingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how attachments are embedded to PDF document.
enum class ASPOSE_WORDS_SHARED_CLASS PdfAttachmentsEmbeddingMode
{
    /// Attachments are not embedded.
    None = 0,
    /// Attachments are embedded as annotations with location on page.
    Annotations = 1,
    /// Attachments are embedded as the document embedded files without annotations.
    DocumentEmbeddedFiles = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfAttachmentsEmbeddingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfAttachmentsEmbeddingMode, const char_t*>, 3>& values();
};
