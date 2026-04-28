//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ProtectionType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Protection type for a document.
enum class ASPOSE_WORDS_SHARED_CLASS ProtectionType
{
    /// User can only modify comments in the document.
    AllowOnlyComments = 1,
    /// User can only enter data in the form fields in the document.
    AllowOnlyFormFields = 2,
    /// User can only add revision marks to the document.
    AllowOnlyRevisions = 0,
    /// No changes are allowed to the document. Available since %Microsoft Word 2003.
    ReadOnly = 3,
    /// The document is not protected.
    NoProtection = -1
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::ProtectionType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::ProtectionType, const char_t*>, 5>& values();
};
