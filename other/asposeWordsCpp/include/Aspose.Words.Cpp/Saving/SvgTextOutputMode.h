//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/SvgTextOutputMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify how text inside a document should be rendered
/// when saving in SVG format.
enum class ASPOSE_WORDS_SHARED_CLASS SvgTextOutputMode
{
    /// SVG fonts are used to render text. Note, not all browsers support SVG fonts.
    UseSvgFonts = 0,
    /// Fonts installed on the target machine are used to render text.
    /// Note, if some of fonts used in the document are not available on the target machine, document can look differently.
    UseTargetMachineFonts = 1,
    /// Text is rendered using curves. Note, text selection will not work if you use this option.
    UsePlacedGlyphs = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::SvgTextOutputMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::SvgTextOutputMode, const char_t*>, 3>& values();
};
