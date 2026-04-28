//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MarkdownOfficeMathExportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words exports OfficeMath to Markdown.
enum class ASPOSE_WORDS_SHARED_CLASS MarkdownOfficeMathExportMode
{
    /// Export OfficeMath as plain text.
    Text = 0,
    /// Export OfficeMath as image.
    Image = 1,
    /// Export OfficeMath as MathML.
    MathML = 2,
    /// Export OfficeMath as LaTeX.
    Latex = 3,
    /// Export OfficeMath as LaTeX that is compatible with MarkItDown.
    MarkItDown = 4
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::MarkdownOfficeMathExportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::MarkdownOfficeMathExportMode, const char_t*>, 5>& values();
};
