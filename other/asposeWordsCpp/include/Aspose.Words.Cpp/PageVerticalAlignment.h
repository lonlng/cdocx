//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PageVerticalAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies vertical justification of text on each page.
/// 
/// @sa Aspose::Words::PageSetup
/// @sa Aspose::Words::PageSetup::get_VerticalAlignment
enum class ASPOSE_WORDS_SHARED_CLASS PageVerticalAlignment
{
    /// Text is aligned at the bottom of the page.
    Bottom = 3,
    /// Text is aligned in the middle of the page.
    Center = 1,
    /// Text is spread to fill the page.
    Justify = 2,
    /// Text is aligned at the top of the page.
    Top = 0
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::PageVerticalAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::PageVerticalAlignment, const char_t*>, 4>& values();
};
