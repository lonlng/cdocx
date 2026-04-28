//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ParagraphAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies text alignment in a paragraph.
enum class ASPOSE_WORDS_SHARED_CLASS ParagraphAlignment
{
    /// Text is aligned to the left.
    Left = 0,
    /// Text is centered horizontally.
    Center = 1,
    /// Text is aligned to the right.
    Right = 2,
    /// Text is aligned to both left and right.
    Justify = 3,
    /// Text is evenly distributed.
    Distributed = 4,
    /// Arabic only. Kashida length for text is extended to a medium length determined by the consumer.
    ArabicMediumKashida = 5,
    /// Arabic only. Kashida length for text is extended to its widest possible length.
    ArabicHighKashida = 7,
    /// Arabic only. Kashida length for text is extended to a slightly longer length.
    ArabicLowKashida = 8,
    /// Thai only. Text is justified with an optimization for Thai.
    ThaiDistributed = 9,
    /// The only Math element in a line, aligned as 'Centered As Group'.
    MathElementCenterAsGroup = 10
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::ParagraphAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::ParagraphAlignment, const char_t*>, 10>& values();
};
