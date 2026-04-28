//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/FootnoteNumberingRule.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Notes {

/// Determines when automatic footnote or endnote numbering restarts.
/// 
/// @sa Aspose::Words::Notes::FootnoteOptions
/// @sa Aspose::Words::Notes::EndnoteOptions
enum class ASPOSE_WORDS_SHARED_CLASS FootnoteNumberingRule
{
    /// Numbering continuous throughout the document.
    Continuous = 0,
    /// Numbering restarts at each section.
    RestartSection = 1,
    /// Numbering restarts at each page. Valid for footnotes only.
    RestartPage = 2,
    /// Equals <see cref="Aspose::Words::Notes::FootnoteNumberingRule::Continuous">Continuous</see>.
    Default = static_cast<int32_t>(Continuous)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Notes::FootnoteNumberingRule>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Notes::FootnoteNumberingRule, const char_t*>, 4>& values();
};
