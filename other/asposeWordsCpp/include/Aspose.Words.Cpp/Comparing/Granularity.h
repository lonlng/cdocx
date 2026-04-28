//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Comparing/Granularity.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Comparing {

/// Specifies the granularity of changes to track when comparing two documents.
enum class ASPOSE_WORDS_SHARED_CLASS Granularity
{
    /// Specifies changes at the character level.
    CharLevel = 0,
    /// Specifies changes at the word level.
    WordLevel = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Comparing::Granularity>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Comparing::Granularity, const char_t*>, 2>& values();
};
