//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/CommentDisplayMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Specifies the rendering mode for document comments.
enum class ASPOSE_WORDS_SHARED_CLASS CommentDisplayMode
{
    /// No document comments are rendered.
    Hide = 0,
    /// Renders document comments in balloons in the margin. This is the default value.
    ShowInBalloons = 1,
    /// Renders document comments in annotations. This is only available for Pdf format.
    ShowInAnnotations = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Layout::CommentDisplayMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::CommentDisplayMode, const char_t*>, 3>& values();
};
