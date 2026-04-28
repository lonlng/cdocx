//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/PreferredWidthType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Specifies the unit of measurement for the preferred width of a table or cell.
/// 
/// @sa Aspose::Words::Tables::PreferredWidth
enum class ASPOSE_WORDS_SHARED_CLASS PreferredWidthType
{
    /// The preferred width is not specified. The actual width of the table or cell is either specified using the explicit width or
    /// will be determined automatically by the table layout algorithm when the table is displayed, depending on the table auto fit setting.
    Auto = 1,
    /// Measure the current item width using a specified percentage.
    Percent = 2,
    /// Measure the current item width using a specified number of points (1/72 inch).
    Points = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Tables::PreferredWidthType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::PreferredWidthType, const char_t*>, 3>& values();
};
