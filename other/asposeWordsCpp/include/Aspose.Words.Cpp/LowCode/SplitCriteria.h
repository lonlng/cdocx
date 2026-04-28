//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/SplitCriteria.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace LowCode {

/// Specifies how the document is split into parts.
enum class ASPOSE_WORDS_SHARED_CLASS SplitCriteria
{
    /// Specifies that the document is split into pages.
    Page = 0,
    /// Specifies that the document is split into parts at a section break of any type.
    SectionBreak = 1,
    /// Specifies that the document is split into parts at a paragraph formatted using the style specified in <see cref="Aspose::Words::LowCode::SplitOptions::get_SplitStyle">SplitStyle</see>.
    Style = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::LowCode::SplitCriteria>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LowCode::SplitCriteria, const char_t*>, 3>& values();
};
