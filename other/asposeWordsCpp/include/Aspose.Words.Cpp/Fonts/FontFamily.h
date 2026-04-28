//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontFamily.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Represents the font family.
/// 
/// A font family is a set of fonts having common stroke width and serif characteristics.
enum class ASPOSE_WORDS_SHARED_CLASS FontFamily
{
    /// Specifies a generic family name. This name is used when information about a font
    /// does not exist or does not matter. The default font is used.
    Auto = 0,
    /// Specifies a proportional font with serifs. An example is Times New Roman.
    Roman = 1,
    /// Specifies a proportional font without serifs. An example is Arial.
    Swiss = 2,
    /// Specifies a monospace font with or without serifs. Monospace fonts are
    /// usually modern; examples include Pica, Elite, and Courier New.
    Modern = 3,
    /// Specifies a font that is designed to look like handwriting; examples include Script and Cursive.
    Script = 4,
    /// Specifies a novelty font. An example is Old English.
    Decorative = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fonts::FontFamily>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fonts::FontFamily, const char_t*>, 6>& values();
};
