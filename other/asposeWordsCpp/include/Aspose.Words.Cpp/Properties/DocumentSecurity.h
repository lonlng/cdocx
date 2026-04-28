//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Properties/DocumentSecurity.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Properties {

/// Used as a value for the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_Security">Security</see> property.
/// Specifies the security level of a document as a numeric value.
enum class ASPOSE_WORDS_SHARED_CLASS DocumentSecurity
{
    /// There are no security states specified by the property.
    None = 0x0000,
    /// The document is password protected. (Note has never been seen in a document so far).
    PasswordProtected = 0x0001,
    /// The document to be opened read-only if possible, but the setting can be overridden.
    ReadOnlyRecommended = 0x0002,
    /// The document to always be opened read-only.
    ReadOnlyEnforced = 0x0004,
    /// The document to always be opened read-only except for annotations.
    ReadOnlyExceptAnnotations = 0x0008
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Properties::DocumentSecurity);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Properties);
template<>
struct EnumMetaInfo<Aspose::Words::Properties::DocumentSecurity>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Properties::DocumentSecurity, const char_t*>, 5>& values();
};
