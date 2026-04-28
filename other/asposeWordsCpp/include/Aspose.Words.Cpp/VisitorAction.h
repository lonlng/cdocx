//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/VisitorAction.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Allows the visitor to control the enumeration of nodes.
enum class ASPOSE_WORDS_SHARED_CLASS VisitorAction
{
    /// The visitor requests the enumeration to continue.
    Continue,
    /// The visitor requests to skip the current node and continue enumeration.
    SkipThisNode,
    /// The visitor requests the enumeration of nodes to stop.
    Stop
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::VisitorAction>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::VisitorAction, const char_t*>, 3>& values();
};
