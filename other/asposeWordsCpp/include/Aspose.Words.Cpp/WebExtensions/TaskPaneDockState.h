//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/TaskPaneDockState.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Enumerates available locations of task pane object.
enum class ASPOSE_WORDS_SHARED_CLASS TaskPaneDockState
{
    /// Dock the task pane on the right side of the document window.
    Right,
    /// Dock the task pane on the left side of the document window.
    Left
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::WebExtensions::TaskPaneDockState>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::WebExtensions::TaskPaneDockState, const char_t*>, 2>& values();
};
