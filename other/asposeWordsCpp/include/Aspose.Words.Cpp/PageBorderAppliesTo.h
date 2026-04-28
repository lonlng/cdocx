//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PageBorderAppliesTo.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies which pages the page border is printed on.
/// 
/// @sa Aspose::Words::PageSetup
/// @sa Aspose::Words::PageSetup::get_BorderAppliesTo
enum class ASPOSE_WORDS_SHARED_CLASS PageBorderAppliesTo
{
    /// Page border is shown on all pages of the section.
    AllPages = 0,
    /// Page border is shown on the first page of the section only.
    FirstPage = 1,
    /// Page border is shown on all pages except the first page of the section.
    OtherPages = 2
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::PageBorderAppliesTo>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::PageBorderAppliesTo, const char_t*>, 3>& values();
};
