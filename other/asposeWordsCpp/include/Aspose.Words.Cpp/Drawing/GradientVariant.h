//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/GradientVariant.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the variant for a gradient fill.
enum class ASPOSE_WORDS_SHARED_CLASS GradientVariant
{
    /// Gradient variant 'None'.
    None,
    /// Gradient variant 1.
    Variant1,
    /// Gradient variant 2.
    Variant2,
    /// Gradient variant 3.
    Variant3,
    /// Gradient variant 4.
    Variant4
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::GradientVariant>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::GradientVariant, const char_t*>, 5>& values();
};
