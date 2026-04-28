//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DigitalSignatures/XmlDsigLevel.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace DigitalSignatures {

/// Specifies the level of a digital signature based on XML-DSig standard.
enum class ASPOSE_WORDS_SHARED_CLASS XmlDsigLevel
{
    /// Specifies XML-DSig signature level.
    XmlDSig = 0,
    /// Specifies XAdES-EPES signature level.
    XAdEsEpes = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::DigitalSignatures::XmlDsigLevel>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::DigitalSignatures::XmlDsigLevel, const char_t*>, 2>& values();
};
