//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TextDmlEffect.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Dml text effect for text runs.
enum class ASPOSE_WORDS_SHARED_CLASS TextDmlEffect
{
    /// Glow effect, in which a color blurred outline is added outside the edges of the object.
    Glow,
    /// Fill overlay effect.
    Fill,
    /// Shadow effect.
    Shadow,
    /// Outline effect.
    Outline,
    /// 3D effect.
    Effect3D,
    /// Reflection effect.
    Reflection
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::TextDmlEffect>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::TextDmlEffect, const char_t*>, 6>& values();
};
