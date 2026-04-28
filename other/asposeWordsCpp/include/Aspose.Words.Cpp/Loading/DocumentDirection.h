//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/DocumentDirection.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify the direction to flow the text in a document.
enum class ASPOSE_WORDS_SHARED_CLASS DocumentDirection
{
    /// Left to right direction.
    LeftToRight = 0,
    /// Right to left direction.
    RightToLeft = 1,
    /// Auto-detect direction.
    Auto = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::DocumentDirection>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::DocumentDirection, const char_t*>, 3>& values();
};
