//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/EmfPlusDualRenderingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words should render EMF+ Dual metafiles.
enum class ASPOSE_WORDS_SHARED_CLASS EmfPlusDualRenderingMode
{
    /// %Aspose.Words tries to render EMF+ part of EMF+ Dual metafile. If some of the EMF+ records are not supported
    /// then %Aspose.Words renders EMF part of EMF+ Dual metafile.
    EmfPlusWithFallback = 0,
    /// %Aspose.Words renders EMF+ part of EMF+ Dual metafile.
    EmfPlus = 1,
    /// %Aspose.Words renders EMF part of EMF+ Dual metafile.
    Emf = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::EmfPlusDualRenderingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::EmfPlusDualRenderingMode, const char_t*>, 3>& values();
};
