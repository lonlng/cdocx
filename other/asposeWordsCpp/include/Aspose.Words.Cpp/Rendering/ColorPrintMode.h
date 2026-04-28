//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Rendering/ColorPrintMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Rendering {

/// Specifies how non-colored pages are printed if the device supports color printing.
enum class ASPOSE_WORDS_SHARED_CLASS ColorPrintMode
{
    /// All pages are printed according to the printer's capabilities and settings.
    Normal,
    /// Non-colored pages if detected are printed in grayscale.
    GrayscaleAuto
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Rendering::ColorPrintMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Rendering::ColorPrintMode, const char_t*>, 2>& values();
};
