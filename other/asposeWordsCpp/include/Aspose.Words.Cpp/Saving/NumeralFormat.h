//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/NumeralFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Indicates the symbol set that is used to represent numbers
/// while rendering to fixed page formats.
enum class ASPOSE_WORDS_SHARED_CLASS NumeralFormat
{
    /// European numerals: 0123456789.
    European = 0,
    /// Numerals used in Arabic: ٠١٢٣٤٥٦٧٨٩.
    /// Unicode range U+0660 - u+0669.
    ArabicIndic = 1,
    /// Numerals used in Persian and Urdu: ۰۱۲۳۴۵۶۷۸۹.
    /// Unicode range U+06F0 - u+06F9.
    EasternArabicIndic = 2,
    /// Symbol set is decided from context(locale and RTL property).
    Context = 3,
    /// THIS OPTION IS NOT SUPPORTED.
    /// Symbol set is decided from regional settings.
    System = 4
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::NumeralFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::NumeralFormat, const char_t*>, 5>& values();
};
