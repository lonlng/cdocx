//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Math/OfficeMathJustification.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Math {

/// Specifies the justification of the equation.
enum class ASPOSE_WORDS_SHARED_CLASS OfficeMathJustification
{
    /// Justifies instances of mathematical text to the left with respect to each other, and centers the group of mathematical
    /// text (the Math Paragraph) with respect to the page.
    CenterGroup = 1,
    /// Centers each instance of mathematical text individually with respect to margins.
    Center = 2,
    /// Left justification of Math Paragraph.
    Left = 3,
    /// Right Justification of Math Paragraph.
    Right = 4,
    /// Inline position of Math.
    Inline = 7,
    /// Default value <see cref="Aspose::Words::Math::OfficeMathJustification::CenterGroup">CenterGroup</see>.
    Default = static_cast<int32_t>(CenterGroup)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Math::OfficeMathJustification>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Math::OfficeMathJustification, const char_t*>, 6>& values();
};
