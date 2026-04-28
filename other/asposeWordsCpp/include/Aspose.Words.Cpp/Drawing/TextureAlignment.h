//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/TextureAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the alignment for the tiling of the texture fill.
enum class ASPOSE_WORDS_SHARED_CLASS TextureAlignment
{
    /// Top left texture alignment.
    TopLeft,
    /// Top texture alignment.
    Top,
    /// Top right texture alignment.
    TopRight,
    /// Left texture alignment.
    Left,
    /// Center texture alignment.
    Center,
    /// Right texture alignment.
    Right,
    /// Bottom left texture alignment.
    BottomLeft,
    /// Bottom texture alignment.
    Bottom,
    /// Bottom right texture alignment.
    BottomRight,
    /// None texture alignment.
    None
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::TextureAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::TextureAlignment, const char_t*>, 10>& values();
};
