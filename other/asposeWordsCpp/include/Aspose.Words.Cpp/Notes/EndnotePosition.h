//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/EndnotePosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Notes {

/// Defines the endnote position.
/// 
/// @sa Aspose::Words::Notes::EndnoteOptions
enum class ASPOSE_WORDS_SHARED_CLASS EndnotePosition
{
    /// Endnotes are output at the end of the section.
    EndOfSection = 0,
    /// Endnotes are output at the end of the document.
    EndOfDocument = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Notes::EndnotePosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Notes::EndnotePosition, const char_t*>, 2>& values();
};
