//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/ContinuousSectionRestart.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Represents different behaviors when computing page numbers in a continuous section that restarts page numbering.
enum class ASPOSE_WORDS_SHARED_CLASS ContinuousSectionRestart
{
    /// Page numbering always restarts regardless of content flow.
    Always = 0,
    /// Page numbering restarts only if there is no other content before the section on the page where the section starts.
    FromNewPageOnly = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Layout::ContinuousSectionRestart>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::ContinuousSectionRestart, const char_t*>, 2>& values();
};
