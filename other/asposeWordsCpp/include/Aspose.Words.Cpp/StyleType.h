//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/StyleType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Represents type of the style.
enum class ASPOSE_WORDS_SHARED_CLASS StyleType
{
    /// The style is a paragraph style.
    Paragraph = 1,
    /// The style is a character style.
    Character = 2,
    /// The style is a table style.
    Table = 3,
    /// The style is a list style.
    List = 4
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::StyleType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::StyleType, const char_t*>, 4>& values();
};
