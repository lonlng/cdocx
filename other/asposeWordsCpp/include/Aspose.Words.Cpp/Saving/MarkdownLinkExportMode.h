//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MarkdownLinkExportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how links are exported into Markdown.
enum class ASPOSE_WORDS_SHARED_CLASS MarkdownLinkExportMode
{
    /// Automatically detect export mode for each link.
    Auto = 0,
    /// Export all links as inline blocks.
    Inline = 1,
    /// Export all links as reference blocks.
    Reference = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::MarkdownLinkExportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::MarkdownLinkExportMode, const char_t*>, 3>& values();
};
