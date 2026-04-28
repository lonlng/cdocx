//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/RevisionType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the type of change being tracked in <see cref="Aspose::Words::Revision">Revision</see>.
enum class ASPOSE_WORDS_SHARED_CLASS RevisionType
{
    /// New content was inserted in the document.
    Insertion,
    /// Content was removed from the document.
    Deletion,
    /// Change of formatting was applied to the parent node.
    FormatChange,
    /// Change of formatting was applied to the parent style.
    StyleDefinitionChange,
    /// Content was moved in the document.
    Moving
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::RevisionType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::RevisionType, const char_t*>, 5>& values();
};
