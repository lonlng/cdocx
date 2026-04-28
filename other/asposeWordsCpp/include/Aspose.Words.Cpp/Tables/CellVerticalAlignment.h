//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/CellVerticalAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Specifies vertical justification of text inside a table cell.
enum class ASPOSE_WORDS_SHARED_CLASS CellVerticalAlignment
{
    /// Text is aligned at the top of a cell.
    Top = 0,
    /// Text is aligned in the middle of a cell.
    Center = 1,
    /// Text is aligned at the bottom of the cell.
    Bottom = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Tables::CellVerticalAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::CellVerticalAlignment, const char_t*>, 3>& values();
};
