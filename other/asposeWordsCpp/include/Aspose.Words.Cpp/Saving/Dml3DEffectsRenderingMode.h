//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/Dml3DEffectsRenderingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how 3D shape effects are rendered.
enum class ASPOSE_WORDS_SHARED_CLASS Dml3DEffectsRenderingMode
{
    /// A lightweight and stable rendering, based on the internal engine,
    /// but advanced effects such as lighting, materials and other additional effects
    /// are not displayed when using this mode.
    /// Please see documentation for details.
    Basic = 0,
    /// Rendering of an extended list of special effects including advanced 3D effects
    /// such as bevels, lighting and materials.
    Advanced = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::Dml3DEffectsRenderingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::Dml3DEffectsRenderingMode, const char_t*>, 2>& values();
};
