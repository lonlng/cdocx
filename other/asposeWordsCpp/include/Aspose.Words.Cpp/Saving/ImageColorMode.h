//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ImageColorMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the color mode for the generated images of document pages.
enum class ASPOSE_WORDS_SHARED_CLASS ImageColorMode
{
    /// The pages of the document will be rendered as color images.
    None = 0,
    /// The pages of the document will be rendered as grayscale images.
    Grayscale = 1,
    /// The pages of the document will be rendered as black and white images.
    BlackAndWhite = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::ImageColorMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::ImageColorMode, const char_t*>, 3>& values();
};
