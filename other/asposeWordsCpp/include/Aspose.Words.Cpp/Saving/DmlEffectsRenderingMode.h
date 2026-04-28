//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DmlEffectsRenderingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how DrawingML effects are rendered to fixed page formats.
enum class ASPOSE_WORDS_SHARED_CLASS DmlEffectsRenderingMode
{
    /// Rendering of DrawingML effects are simplified.
    Simplified = 0,
    /// No DrawingML effects are rendered.
    None = 1,
    /// DrawingML effects are rendered in fine mode which involves advanced processing.
    /// In this mode rendering of effects gives better results but at a higher performance cost than <see cref="Aspose::Words::Saving::DmlEffectsRenderingMode::Simplified">Simplified</see> mode.
    Fine = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::DmlEffectsRenderingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::DmlEffectsRenderingMode, const char_t*>, 3>& values();
};
