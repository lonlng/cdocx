//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LineSpacingRule.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies line spacing values for a paragraph.
enum class ASPOSE_WORDS_SHARED_CLASS LineSpacingRule
{
    /// The line spacing can be greater than or equal to, but never less than,
    /// the value specified in the <see cref="Aspose::Words::ParagraphFormat::get_LineSpacing">LineSpacing</see> property.
    AtLeast,
    /// The line spacing never changes from the value specified in the
    /// <see cref="Aspose::Words::ParagraphFormat::get_LineSpacing">LineSpacing</see> property,
    /// even if a larger font is used within the paragraph.
    Exactly,
    /// The line spacing is specified in the <see cref="Aspose::Words::ParagraphFormat::get_LineSpacing">LineSpacing</see>
    /// property as the number of lines. One line equals 12 points.
    Multiple
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::LineSpacingRule>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LineSpacingRule, const char_t*>, 3>& values();
};
