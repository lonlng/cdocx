//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MarkdownListExportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how lists are exported into Markdown.
enum class ASPOSE_WORDS_SHARED_CLASS MarkdownListExportMode
{
    /// Export list items compatible with Markdown syntax.
    MarkdownSyntax = 0,
    /// Export list items as plain text.
    PlainText = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::MarkdownListExportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::MarkdownListExportMode, const char_t*>, 2>& values();
};
