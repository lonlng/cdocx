//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PaperSize.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies paper size.
enum class ASPOSE_WORDS_SHARED_CLASS PaperSize
{
    /// 297 x 420 mm.
    A3,
    /// 210 x 297 mm.
    A4,
    /// 148 x 210 mm.
    A5,
    /// 250 x 353 mm.
    B4,
    /// 176 x 250 mm.
    B5,
    /// 7.25 x 10.5 inches.
    Executive,
    /// 8.5 x 13 inches.
    Folio,
    /// 17 x 11 inches.
    Ledger,
    /// 8.5 x 14 inches.
    Legal,
    /// 8.5 x 11 inches.
    Letter,
    /// 110 x 220 mm.
    EnvelopeDL,
    /// 8.47 x 10.83 inches.
    Quarto,
    /// 8.5 x 5.5 inches.
    Statement,
    /// 11 x 17 inches.
    Tabloid,
    /// 10 x 14 inches.
    Paper10x14,
    /// 11 x 17 inches.
    Paper11x17,
    /// 4.125 x 9.5 inches.
    Number10Envelope,
    /// 257 x 364 mm.
    JisB4,
    /// 182 x 257 mm.
    JisB5,
    /// Custom paper size.
    Custom
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::PaperSize>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::PaperSize, const char_t*>, 20>& values();
};
