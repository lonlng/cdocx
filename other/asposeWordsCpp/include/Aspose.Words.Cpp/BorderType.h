//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BorderType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies sides of a border.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
enum class ASPOSE_WORDS_SHARED_CLASS BorderType
{
    /// Default value.
    None = -1,
    /// Specifies the bottom border of a paragraph or a table cell.
    Bottom = 0,
    /// Specifies the left border of a paragraph or a table cell.
    Left = 1,
    /// Specifies the right border of a paragraph or a table cell.
    Right = 2,
    /// Specifies the top border of a paragraph or a table cell.
    Top = 3,
    /// Specifies the horizontal border between cells in a table or between conforming paragraphs.
    Horizontal = 4,
    /// Specifies the vertical border between cells in a table.
    Vertical = 5,
    /// Specifies the diagonal border in a table cell.
    DiagonalDown = 6,
    /// Specifies the diagonal border in a table cell.
    DiagonalUp = 7
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::BorderType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::BorderType, const char_t*>, 9>& values();
};
