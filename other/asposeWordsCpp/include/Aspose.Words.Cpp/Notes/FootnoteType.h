//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/FootnoteType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Notes {

/// Specifies whether this is a footnote or an endnote.
/// 
/// Both footnotes and endnotes are represented by objects by the <see cref="Aspose::Words::Notes::FootnoteType::Footnote">Footnote</see>
/// class. Use <see cref="Aspose::Words::Notes::Footnote::get_FootnoteType">FootnoteType</see> to distinguish between footnotes
/// and endnotes.
/// 
/// @sa Aspose::Words::Notes::FootnoteType::Footnote
enum class ASPOSE_WORDS_SHARED_CLASS FootnoteType
{
    /// The object is a footnote.
    Footnote = 0,
    /// The object is an endnote.
    Endnote = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Notes::FootnoteType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Notes::FootnoteType, const char_t*>, 2>& values();
};
