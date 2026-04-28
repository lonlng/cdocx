//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DropCapPosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the position for a drop cap text.
enum class ASPOSE_WORDS_SHARED_CLASS DropCapPosition
{
    /// The paragraph does not have a drop cap.
    None = 0,
    /// The drop cap is positioned inside the text margin on the anchor paragraph.
    Normal = 1,
    /// The drop cap is positioned outside the text margin on the anchor paragraph.
    Margin = 2
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::DropCapPosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::DropCapPosition, const char_t*>, 3>& values();
};
