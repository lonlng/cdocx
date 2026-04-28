//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/AutoFitBehavior.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Determines how %Aspose.Words resizes the table when you invoke the <see cref="Aspose::Words::Tables::Table::AutoFit(Aspose::Words::Tables::AutoFitBehavior)">AutoFit()</see> method.
enum class ASPOSE_WORDS_SHARED_CLASS AutoFitBehavior
{
    /// %Aspose.Words enables the AutoFit option, removes the preferred width from the table and all cells and then updates the table layout.
    /// In the resulting table, cell widths are updated to fit the table contents. Most likely, the table will shrink.
    AutoFitToContents,
    /// When you use this value, %Aspose.Words enables the AutoFit option, sets the preferred width for the table to 100\%,
    /// removes preferred widths from all cells and then updates the table layout.
    /// As a result, the table occupies all available width and the cell widths are updated to fit table contents.
    AutoFitToWindow,
    /// %Aspose.Words disables the AutoFit option and removes the preferred with from the table.
    /// The widths of the cells remain as they are specified by their <see cref="Aspose::Words::Tables::CellFormat::get_Width">Width</see> properties.
    FixedColumnWidths
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Tables::AutoFitBehavior>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::AutoFitBehavior, const char_t*>, 3>& values();
};
