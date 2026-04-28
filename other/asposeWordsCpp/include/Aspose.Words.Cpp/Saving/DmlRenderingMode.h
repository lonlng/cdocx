//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DmlRenderingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how DrawingML shapes are rendered to fixed page formats.
enum class ASPOSE_WORDS_SHARED_CLASS DmlRenderingMode
{
    /// If fall-back shape is available for DrawingML, %Aspose.Words renders fall-back shape instead of the DrawingML.
    Fallback = 0,
    /// %Aspose.Words ignores fall-back shape of DrawingML and renders DrawingML itself.
    /// This is the default mode.
    DrawingML = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::DmlRenderingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::DmlRenderingMode, const char_t*>, 2>& values();
};
