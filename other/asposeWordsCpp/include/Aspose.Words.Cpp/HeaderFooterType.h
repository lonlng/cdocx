//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/HeaderFooterType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Identifies the type of header or footer found in a Word file.
enum class ASPOSE_WORDS_SHARED_CLASS HeaderFooterType
{
    /// Header for even numbered pages.
    HeaderEven = 0,
    /// Primary header, also used for odd numbered pages.
    HeaderPrimary = 1,
    /// Footer for even numbered pages.
    FooterEven = 2,
    /// Primary footer, also used for odd numbered pages.
    FooterPrimary = 3,
    /// Header for the first page of the section.
    HeaderFirst = 4,
    /// Footer for the first page of the section.
    FooterFirst = 5
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::HeaderFooterType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::HeaderFooterType, const char_t*>, 6>& values();
};
