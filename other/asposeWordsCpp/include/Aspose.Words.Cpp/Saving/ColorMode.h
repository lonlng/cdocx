//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ColorMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how colors are rendered.
enum class ASPOSE_WORDS_SHARED_CLASS ColorMode
{
    /// Rendering with unmodified colors.
    Normal = 0,
    /// Rendering with colors in a range of gray shades from white to black.
    Grayscale = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::ColorMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::ColorMode, const char_t*>, 2>& values();
};
