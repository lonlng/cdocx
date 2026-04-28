//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LineNumberRestartMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Determines when automatic line numbering restarts.
/// 
/// @sa Aspose::Words::PageSetup
/// @sa Aspose::Words::PageSetup::get_LineNumberRestartMode
enum class ASPOSE_WORDS_SHARED_CLASS LineNumberRestartMode
{
    /// Line numbering restarts at the start of every page.
    RestartPage = 0,
    /// Line numbering restarts at the section start.
    RestartSection = 1,
    /// Line numbering continuous from the previous section.
    Continuous = 2
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::LineNumberRestartMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LineNumberRestartMode, const char_t*>, 3>& values();
};
