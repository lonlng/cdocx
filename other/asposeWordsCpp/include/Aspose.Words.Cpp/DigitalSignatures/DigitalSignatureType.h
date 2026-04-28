//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DigitalSignatures/DigitalSignatureType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace DigitalSignatures {

/// Specifies the type of a digital signature.
enum class ASPOSE_WORDS_SHARED_CLASS DigitalSignatureType
{
    /// Indicates an error, unknown digital signature type.
    Unknown,
    /// The Crypto API signature method used in %Microsoft Word 97-2003 .DOC binary documents.
    CryptoApi,
    /// The XmlDsig signature method used in OOXML and OpenDocument documents.
    XmlDsig
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::DigitalSignatures::DigitalSignatureType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::DigitalSignatures::DigitalSignatureType, const char_t*>, 3>& values();
};
