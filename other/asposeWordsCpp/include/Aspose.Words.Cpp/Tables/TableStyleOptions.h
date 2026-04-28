//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/TableStyleOptions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Specifies how table style is applied to a table.
/// 
/// @sa Aspose::Words::Tables::Table::get_StyleOptions
enum class ASPOSE_WORDS_SHARED_CLASS TableStyleOptions
{
    /// No table style formatting is applied.
    None = 0x0000,
    /// Apply first row conditional formatting.
    FirstRow = 0x0020,
    /// Apply last row conditional formatting.
    LastRow = 0x0040,
    /// Apply 1 first column conditional formatting.
    FirstColumn = 0x0080,
    /// Apply last column conditional formatting.
    LastColumn = 0x0100,
    /// Apply row banding conditional formatting.
    RowBands = 0x0200,
    /// Apply column banding conditional formatting.
    ColumnBands = 0x0400,
    /// Row and column banding is applied. This is %Microsoft Word default for old formats such as DOC, WML and RTF.
    Default2003 = static_cast<int32_t>(RowBands | ColumnBands),
    /// This is %Microsoft Word defaults.
    Default = static_cast<int32_t>(FirstRow | FirstColumn | RowBands)
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Tables::TableStyleOptions);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Tables);
template<>
struct EnumMetaInfo<Aspose::Words::Tables::TableStyleOptions>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::TableStyleOptions, const char_t*>, 9>& values();
};
