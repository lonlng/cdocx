//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BreakType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies type of a break inside a document.
enum class ASPOSE_WORDS_SHARED_CLASS BreakType
{
    /// Break between paragraphs.
    ParagraphBreak,
    /// Explicit page break.
    PageBreak,
    /// Explicit column break.
    ColumnBreak,
    /// Specifies start of new section on the same page as the previous section.
    SectionBreakContinuous,
    /// Specifies start of new section in the new column.
    SectionBreakNewColumn,
    /// Specifies start of new section on a new page.
    SectionBreakNewPage,
    /// Specifies start of new section on a new even page.
    SectionBreakEvenPage,
    /// Specifies start of new section on a odd page.
    SectionBreakOddPage,
    /// Explicit line break.
    LineBreak
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::BreakType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::BreakType, const char_t*>, 9>& values();
};
