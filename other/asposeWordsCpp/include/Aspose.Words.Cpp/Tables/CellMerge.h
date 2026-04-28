//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/CellMerge.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Specifies how a cell in a table is merged with other cells.
enum class ASPOSE_WORDS_SHARED_CLASS CellMerge
{
    /// The cell is not merged.
    None = 0,
    /// The cell is the first cell in a range of merged cells.
    First = 1,
    /// The cell is merged to the previous cell horizontally or vertically.
    Previous = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Tables::CellMerge>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::CellMerge, const char_t*>, 3>& values();
};
