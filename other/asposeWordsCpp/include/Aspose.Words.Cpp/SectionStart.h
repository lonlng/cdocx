//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SectionStart.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// The type of break at the beginning of the section.
enum class ASPOSE_WORDS_SHARED_CLASS SectionStart
{
    /// The new section starts on the same page as the previous section.
    Continuous = 0,
    /// The section starts from a new column.
    NewColumn = 1,
    /// The section starts from a new page.
    NewPage = 2,
    /// The section starts on a new even page.
    EvenPage = 3,
    /// The section starts on a new odd page.
    OddPage = 4
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::SectionStart>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::SectionStart, const char_t*>, 5>& values();
};
