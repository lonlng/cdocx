//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MultiplePagesType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies how document is printed out.
enum class ASPOSE_WORDS_SHARED_CLASS MultiplePagesType
{
    /// Normal printing, no multiple pages specified.
    Normal,
    /// Swaps left and right margins on facing pages.
    MirrorMargins,
    /// Prints two pages per sheet.
    TwoPagesPerSheet,
    /// Specifies whether to print the document as a book fold.
    BookFoldPrinting,
    /// Specifies whether to print the document as a reverse book fold.
    BookFoldPrintingReverse,
    /// Default value is <see cref="Aspose::Words::Settings::MultiplePagesType::Normal">Normal</see>
    Default = static_cast<int32_t>(Normal)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::MultiplePagesType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::MultiplePagesType, const char_t*>, 6>& values();
};
