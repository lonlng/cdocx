//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SdtDateStorageFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Specifies how the date for a date SDT is stored/retrieved when the SDT is bound to an XML node in the document's data store.
enum class ASPOSE_WORDS_SHARED_CLASS SdtDateStorageFormat
{
    /// The date value for a date SDT is stored as a date in the standard XML Schema Date format.
    Date,
    /// The date value for a date SDT is stored as a date in the standard XML Schema DateTime format.
    DateTime,
    /// The date value for a date SDT is stored as text.
    Text,
    /// Defaults to <see cref="Aspose::Words::Markup::SdtDateStorageFormat::DateTime">DateTime</see>
    Default = static_cast<int32_t>(DateTime)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Markup::SdtDateStorageFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Markup::SdtDateStorageFormat, const char_t*>, 4>& values();
};
