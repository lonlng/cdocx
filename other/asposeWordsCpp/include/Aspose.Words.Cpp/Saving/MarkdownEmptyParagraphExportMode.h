//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MarkdownEmptyParagraphExportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words exports empty paragraphs to Markdown.
enum class ASPOSE_WORDS_SHARED_CLASS MarkdownEmptyParagraphExportMode
{
    /// Export as empty lines.
    EmptyLine,
    /// Export as Markdown HardLineBreak character '\\'.
    MarkdownHardLineBreak,
    /// Don't export empty paragraphs.
    None
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::MarkdownEmptyParagraphExportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::MarkdownEmptyParagraphExportMode, const char_t*>, 3>& values();
};
