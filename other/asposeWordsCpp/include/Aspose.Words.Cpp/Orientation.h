//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Orientation.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies page orientation.
enum class ASPOSE_WORDS_SHARED_CLASS Orientation
{
    /// Portrait page orientation (narrow and tall).
    Portrait = 1,
    /// Landscape page orientation (wide and short).
    Landscape = 2
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::Orientation>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Orientation, const char_t*>, 2>& values();
};
