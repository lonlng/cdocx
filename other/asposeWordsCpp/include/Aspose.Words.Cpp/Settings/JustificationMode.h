//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/JustificationMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the character spacing adjustment for a document.
/// The default value is <c>%Expand</c>.
enum class ASPOSE_WORDS_SHARED_CLASS JustificationMode
{
    /// Do not compress character spacing.
    Expand = 0,
    /// Compress character spacing.
    Compress = 1,
    /// Compress, using rules of the kana syllabaries, Hiragana and Katakana.
    CompressKana = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::JustificationMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::JustificationMode, const char_t*>, 3>& values();
};
