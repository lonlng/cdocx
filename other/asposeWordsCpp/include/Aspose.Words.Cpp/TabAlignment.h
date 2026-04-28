//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TabAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the alignment/type of a tab stop.
enum class ASPOSE_WORDS_SHARED_CLASS TabAlignment
{
    /// Left-aligns the text after the tab stop.
    Left = 0,
    /// Centers the text around the tab stop.
    Center = 1,
    /// Right-aligns the text at the tab stop.
    Right = 2,
    /// Aligns the text at the decimal dot.
    Decimal = 3,
    /// Draws a vertical bar at the tab stop position.
    Bar = 4,
    /// The tab is a delimiter between the number/bullet and text in a list item.
    List = 6,
    /// Clears any tab stop in this position.
    Clear = 7
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::TabAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::TabAlignment, const char_t*>, 7>& values();
};
