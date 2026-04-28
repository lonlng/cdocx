//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/XlsxDateTimeParsingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how document text is parsed to identify date and time values.
enum class ASPOSE_WORDS_SHARED_CLASS XlsxDateTimeParsingMode
{
    /// The datetime format set for the current thread is used first to parse string values. If the parsing fails,
    /// other common datetime formats are tried.
    UseCurrentLocale = 0,
    /// The datetime format used in a document is determined automatically. This may take additional time.
    Auto = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::XlsxDateTimeParsingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::XlsxDateTimeParsingMode, const char_t*>, 2>& values();
};
