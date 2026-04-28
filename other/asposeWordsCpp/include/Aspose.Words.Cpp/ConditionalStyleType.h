//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ConditionalStyleType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Represents possible table areas to which conditional formatting may be defined in a table style.
enum class ASPOSE_WORDS_SHARED_CLASS ConditionalStyleType
{
    /// Specifies formatting of the first row of a table.
    FirstRow,
    /// Specifies formatting of the first column of a table.
    FirstColumn,
    /// Specifies formatting of the last row of a table.
    LastRow,
    /// Specifies formatting of the last column of a table.
    LastColumn,
    /// Specifies formatting of odd-numbered row stripe.
    OddRowBanding,
    /// Specifies formatting of odd-numbered column stripe.
    OddColumnBanding,
    /// Specifies formatting of even-numbered row stripe.
    EvenRowBanding,
    /// Specifies formatting of even-numbered column stripe.
    EvenColumnBanding,
    /// Specifies formatting of the top left cell of a table.
    TopLeftCell,
    /// Specifies formatting of the top right cell of a table.
    TopRightCell,
    /// Specifies formatting of the bottom left cell of a table.
    BottomLeftCell,
    /// Specifies formatting of the bottom right cell of a table.
    BottomRightCell
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::ConditionalStyleType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::ConditionalStyleType, const char_t*>, 12>& values();
};
