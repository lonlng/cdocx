//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WarningType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the type of a warning that is issued by %Aspose.Words during document loading or saving.
enum class ASPOSE_WORDS_SHARED_CLASS WarningType
{
    /// Some text/char/image or other data will be missing from either the document tree following load,
    /// or from the created document following save.
    DataLossCategory = 0x000000FF,
    /// Generic data loss, no specific code.
    DataLoss = 0x00000001,
    /// The resulting document or a particular location in it might look substantially different
    /// compared to the original document.
    MajorFormattingLossCategory = 0x0000FF00,
    /// Generic major formatting loss, no specific code.
    MajorFormattingLoss = 0x00000100,
    /// The resulting document or a particular location in it might look somewhat different compared
    /// to the original document.
    MinorFormattingLossCategory = 0x00FF0000,
    /// Generic minor formatting loss, no specific code.
    MinorFormattingLoss = 0x00010000,
    /// Font has been substituted.
    FontSubstitution = 0x00020000,
    /// Loss of embedded font information during document saving.
    FontEmbedding = 0x00040000,
    /// Some content in the source document could not be recognized (i.e. is unsupported), this may or may not
    /// cause issues or result in data/formatting loss.
    UnexpectedContentCategory = 0x0F000000,
    /// Generic unexpected content, no specific code.
    UnexpectedContent = 0x01000000,
    /// Advises of a potential problem or suggests an improvement.
    Hint = 0x10000000
};

DECLARE_ENUM_OPERATORS(Aspose::Words::WarningType);
DECLARE_USING_GLOBAL_OPERATORS

}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words);
template<>
struct EnumMetaInfo<Aspose::Words::WarningType>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::WarningType, const char_t*>, 11>& values();
};
