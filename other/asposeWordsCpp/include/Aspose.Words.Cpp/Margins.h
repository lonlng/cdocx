//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Margins.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies preset margins.
enum class ASPOSE_WORDS_SHARED_CLASS Margins
{
    /// Normal margins.
    Normal,
    /// Narrow margins.
    Narrow,
    /// Moderate margins.
    Moderate,
    /// Wide margins.
    Wide,
    /// Mirrored margins.
    Mirrored,
    /// Custom margins.
    Custom
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::Margins>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Margins, const char_t*>, 6>& values();
};
