//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/RunPrExpandFlags.h
#pragma once

#include <system/enum_helpers.h>
#include <cstdint>

namespace Aspose {

namespace Words {

/// RunPrExpandFlags enumeration.
enum class RunPrExpandFlags
{
    Normal = 0x0000,
    DocumentDefaults = 0x0001,
    IgnoreNormalFontSize = 0x0002,
    IgnoreHyperlinkCharStyle = 0x0004,
    Revised = 0x0008,
    AfterChanges = 0x0010,
    GlobalDefaults = 0x0020,
    NoTableStyle = 0x0040,
    NoDirectFormatting = 0x0080,
    NoParaStyle = 0x0100,
    NoChangeCommentSize = 0x0200,
    Layout = static_cast<int32_t>(DocumentDefaults)
};

DECLARE_ENUM_OPERATORS(Aspose::Words::RunPrExpandFlags);
DECLARE_USING_GLOBAL_OPERATORS

}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words);
