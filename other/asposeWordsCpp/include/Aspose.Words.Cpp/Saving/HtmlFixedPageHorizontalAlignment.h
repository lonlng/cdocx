//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlFixedPageHorizontalAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the horizontal alignment for pages in output HTML document.
enum class ASPOSE_WORDS_SHARED_CLASS HtmlFixedPageHorizontalAlignment
{
    /// Align pages to the left.
    Left = 0,
    /// Center pages. This is the default value.
    Center = 1,
    /// Align pages to the right.
    Right = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment, const char_t*>, 3>& values();
};
