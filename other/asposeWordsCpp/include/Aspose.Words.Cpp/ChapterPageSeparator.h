//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ChapterPageSeparator.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Defines the separator character that appears between the chapter and page number.
/// 
/// @sa Aspose::Words::PageSetup
/// @sa Aspose::Words::PageSetup::get_ChapterPageSeparator
enum class ASPOSE_WORDS_SHARED_CLASS ChapterPageSeparator
{
    /// A colon.
    Hyphen = 0,
    /// A period.
    Period = 1,
    /// A colon.
    Colon = 2,
    /// An emphasized dash.
    EmDash = 3,
    /// A standard dash.
    EnDash = 4
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::ChapterPageSeparator>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::ChapterPageSeparator, const char_t*>, 5>& values();
};
