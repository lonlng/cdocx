//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MailMergeMainDocumentType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the possible types for a mail merge source document.
/// 
/// @sa Aspose::Words::Settings::MailMergeSettings::get_MainDocumentType
enum class ASPOSE_WORDS_SHARED_CLASS MailMergeMainDocumentType
{
    /// This document is not a mail merge document.
    NotAMergeDocument = 0x00,
    /// Specifies that the mail merge source document is of the form letter type.
    FormLetters = 0x01,
    /// Specifies that the mail merge source document is of the mailing label type.
    MailingLabels = 0x02,
    /// Specifies that the mail merge source document is of the envelope type.
    Envelopes = 0x04,
    /// Specifies that the mail merge source document is of the catalog type.
    Catalog = 0x08,
    /// Specifies that the mail merge source document is of the e-mail message type.
    Email = 0x10,
    /// Specifies that the mail merge source document is of the fax type.
    Fax = 0x20,
    /// Equals to <see cref="Aspose::Words::Settings::MailMergeMainDocumentType::NotAMergeDocument">NotAMergeDocument</see>
    Default = static_cast<int32_t>(NotAMergeDocument)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::MailMergeMainDocumentType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::MailMergeMainDocumentType, const char_t*>, 8>& values();
};
