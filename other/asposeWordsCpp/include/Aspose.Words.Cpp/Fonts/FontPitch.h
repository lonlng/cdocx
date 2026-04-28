//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontPitch.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Represents the font pitch.
enum class ASPOSE_WORDS_SHARED_CLASS FontPitch
{
    /// Specifies that no information is available about the pitch of a font.
    Default = 0,
    /// Specifies that this is a fixed width font.
    Fixed = 1,
    /// Specifies that this is a proportional width font.
    Variable = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fonts::FontPitch>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fonts::FontPitch, const char_t*>, 3>& values();
};
