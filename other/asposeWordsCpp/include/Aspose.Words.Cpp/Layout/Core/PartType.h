//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/Core/PartType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

namespace Core {

/// PartType enumeration.
enum class PartType
{
    None = 0x0,
    Page = 0x1,
    Column = 0x2,
    Table = 0x4,
    Row = 0x8,
    Cell = 0x10,
    Line = 0x20,
    Span = 0x40,
    Warp = 0x80,
    Footnote = 0x100,
    Endnote = 0x200,
    HeaderFooter = 0x400,
    TextBox = 0x800,
    Comment = 0x1000,
    NoteSeparator = 0x2000,
    Note = 0x4000,
    Group = 0x8000
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Layout::Core::PartType);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Layout::Core);
template<>
struct EnumMetaInfo<Aspose::Words::Layout::Core::PartType>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::Core::PartType, const char_t*>, 17>& values();
};
