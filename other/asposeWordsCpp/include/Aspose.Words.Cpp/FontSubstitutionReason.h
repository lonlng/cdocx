//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/FontSubstitutionReason.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the reason of font substitution.
enum class ASPOSE_WORDS_SHARED_CLASS FontSubstitutionReason
{
    /// Font substitution by alternative name from the document.
    AlternativeName,
    /// Font substitution by font name rule.
    FontNameSubstitutionRule,
    /// Font substitution by font config rule.
    FontConfigSubstitutionRule,
    /// Font substitution by table rule.
    TableSubstitutionRule,
    /// Font substitution by font info rule.
    FontInfoSubstitutionRule,
    /// Font substitution by default font rule.
    DefaultFontSubstitutionRule,
    /// Font substitution with the first available font.
    FirstAvailableFont
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::FontSubstitutionReason>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::FontSubstitutionReason, const char_t*>, 7>& values();
};
