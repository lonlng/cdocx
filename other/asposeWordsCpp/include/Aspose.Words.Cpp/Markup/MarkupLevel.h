//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/MarkupLevel.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Specifies the level in the document tree where a particular <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see> can occur.
enum class ASPOSE_WORDS_SHARED_CLASS MarkupLevel
{
    /// Specifies the unknown or invalid value.
    Unknown,
    /// The element occurs at the inline level (e.g. among as runs of text).
    Inline,
    /// The element occurs at the block level (e.g. among tables and paragraphs).
    Block,
    /// The element occurs among rows in a table.
    Row,
    /// The element occurs among cells in a row.
    Cell
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Markup::MarkupLevel>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Markup::MarkupLevel, const char_t*>, 5>& values();
};
