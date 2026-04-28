//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PageBorderDistanceFrom.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the positioning of the page border relative to the page margin.
/// 
/// @sa Aspose::Words::PageSetup
/// @sa Aspose::Words::PageSetup::get_BorderDistanceFrom
enum class ASPOSE_WORDS_SHARED_CLASS PageBorderDistanceFrom
{
    /// Border position is measured from the page margin.
    Text = 0,
    /// Border position is measured from the page edge.
    PageEdge = 1
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::PageBorderDistanceFrom>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::PageBorderDistanceFrom, const char_t*>, 2>& values();
};
