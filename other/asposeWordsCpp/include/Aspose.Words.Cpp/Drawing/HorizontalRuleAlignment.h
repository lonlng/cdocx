//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/HorizontalRuleAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents the alignment for the specified horizontal rule.
enum class ASPOSE_WORDS_SHARED_CLASS HorizontalRuleAlignment
{
    /// Aligned to the left.
    Left = 0,
    /// Aligned to the center.
    Center = 1,
    /// Aligned to the right.
    Right = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::HorizontalRuleAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::HorizontalRuleAlignment, const char_t*>, 3>& values();
};
