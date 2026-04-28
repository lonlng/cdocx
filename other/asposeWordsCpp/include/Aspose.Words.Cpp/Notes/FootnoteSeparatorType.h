//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/FootnoteSeparatorType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Notes {

/// Specifies the type of the footnote/endnote separator.
enum class ASPOSE_WORDS_SHARED_CLASS FootnoteSeparatorType
{
    /// Separator between main text and footnote text.
    FootnoteSeparator = 0,
    /// Printed above footnote text on a page when the text must be continued from a previous page.
    FootnoteContinuationSeparator,
    /// Printed below footnote text on a page when footnote text must be continued on a succeeding page.
    FootnoteContinuationNotice,
    /// Separator between main text and endnote text.
    EndnoteSeparator,
    /// Printed above endnote text on a page when the text must be continued from a previous page.
    EndnoteContinuationSeparator,
    /// Printed below endnote text on a page when endnote text must be continued on a succeeding page.
    EndnoteContinuationNotice
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Notes::FootnoteSeparatorType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Notes::FootnoteSeparatorType, const char_t*>, 6>& values();
};
