//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MetafileRenderingMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words should render WMF and EMF metafiles.
enum class ASPOSE_WORDS_SHARED_CLASS MetafileRenderingMode
{
    /// %Aspose.Words tries to render a metafile as vector graphics. If %Aspose.Words cannot correctly render some of
    /// the metafile records to vector graphics then %Aspose.Words renders this metafile to a bitmap.
    VectorWithFallback = 0,
    /// %Aspose.Words renders a metafile as vector graphics.
    Vector = 1,
    /// %Aspose.Words invokes GDI+ to render a metafile to a bitmap and then saves the bitmap to the output document.
    Bitmap = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::MetafileRenderingMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::MetafileRenderingMode, const char_t*>, 3>& values();
};
