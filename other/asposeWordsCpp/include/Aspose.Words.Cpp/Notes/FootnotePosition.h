//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/FootnotePosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Notes {

/// Defines the footnote position.
/// 
/// @sa Aspose::Words::Notes::FootnoteOptions
enum class ASPOSE_WORDS_SHARED_CLASS FootnotePosition
{
    /// Footnotes are output at the bottom of each page.
    BottomOfPage = 1,
    /// Footnotes are output beneath text on each page.
    BeneathText = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Notes::FootnotePosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Notes::FootnotePosition, const char_t*>, 2>& values();
};
