//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfPermissions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>
#include <Aspose.Words.Cpp/Rendering/Pdf/Encryption/PdfUserAccessPermissions.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the operations that are allowed to a user on an encrypted PDF document.
enum class ASPOSE_WORDS_SHARED_CLASS PdfPermissions
{
    /// Disallows all operations on the PDF document.
    /// This is the default value.
    DisallowAll = 0,
    /// Allows all operations on the PDF document.
    AllowAll = 0xffff,
    /// Copy or otherwise extract text and graphics from the document by operations other than that controlled
    /// by <see cref="Aspose::Words::Saving::PdfPermissions::ContentCopyForAccessibility">ContentCopyForAccessibility</see>.
    ContentCopy = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::Copy),
    /// Extract text and graphics (in support of accessibility to users with disabilities or for other purposes).
    ContentCopyForAccessibility = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::CopyForAccessibility),
    /// Modify the contents of the document by operations other than those controlled by
    /// <see cref="Aspose::Words::Saving::PdfPermissions::ModifyAnnotations">ModifyAnnotations</see>, <see cref="Aspose::Words::Saving::PdfPermissions::FillIn">FillIn</see>, and <see cref="Aspose::Words::Saving::PdfPermissions::DocumentAssembly">DocumentAssembly</see>.
    ModifyContents = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::Modify),
    /// Add or modify text annotations, fill in interactive form fields, and, if <see cref="Aspose::Words::Saving::PdfPermissions::ModifyContents">ModifyContents</see> is
    /// also set, create or modify interactive form fields (including signature fields).
    ModifyAnnotations = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::ModifyAnnotations),
    /// Fill in existing interactive form fields (including signature fields), even if <see cref="Aspose::Words::Saving::PdfPermissions::ModifyContents">ModifyContents</see>
    /// is clear.
    FillIn = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::FillForms),
    /// Assemble the document (insert, rotate, or delete pages and create document outline items or thumbnail
    /// images), even if <see cref="Aspose::Words::Saving::PdfPermissions::ModifyContents">ModifyContents</see> is clear.
    DocumentAssembly = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::Assemble),
    /// Print the document (possibly not at the highest quality level, depending on whether
    /// <see cref="Aspose::Words::Saving::PdfPermissions::HighResolutionPrinting">HighResolutionPrinting</see> is also set).
    Printing = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::Print),
    /// Print the document to a representation from which a faithful digital copy of the PDF content could be
    /// generated, based on an implementation-dependent algorithm. When this flag is clear (and
    /// <see cref="Aspose::Words::Saving::PdfPermissions::Printing">Printing</see> is set), printing shall be limited to a low-level representation of the appearance,
    /// possibly of degraded quality.
    HighResolutionPrinting = static_cast<int32_t>(Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::HighQualityPrint | Aspose::Rendering::Pdf::Encryption::PdfUserAccessPermissions::Print)
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Saving::PdfPermissions);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Saving);
template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfPermissions>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfPermissions, const char_t*>, 10>& values();
};
