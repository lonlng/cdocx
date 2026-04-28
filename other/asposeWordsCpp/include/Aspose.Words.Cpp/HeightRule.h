//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/HeightRule.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the rule for determining the height of an object.
enum class ASPOSE_WORDS_SHARED_CLASS HeightRule
{
    /// The height will be at least the specified height in points. It will grow, if needed,
    /// to accommodate all text inside an object.
    AtLeast,
    /// The height is specified exactly in points. Please note that if the text cannot
    /// fit inside the object of this height, it will appear truncated.
    Exactly,
    /// The height will grow automatically to accommodate all text inside an object.
    Auto
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::HeightRule>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::HeightRule, const char_t*>, 3>& values();
};
