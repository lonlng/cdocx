//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NumSpacing.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies possible values in which numeral spacing can be displayed.
enum class ASPOSE_WORDS_SHARED_CLASS NumSpacing
{
    /// Specifies that numerals are displayed in the font’s default form.
    Default,
    /// Specifies that the forms of the numerals designed as proportionally spaced are displayed if supported by the font.
    Proportional,
    /// Specifies that the forms of the numerals designed as tabular are displayed if supported by the font.
    Tabular
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::NumSpacing>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::NumSpacing, const char_t*>, 3>& values();
};
