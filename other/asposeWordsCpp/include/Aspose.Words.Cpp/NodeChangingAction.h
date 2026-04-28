//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeChangingAction.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the type of node change.
/// 
/// @sa Aspose::Words::NodeChangingArgs
/// @sa Aspose::Words::NodeChangingArgs::get_Action
enum class ASPOSE_WORDS_SHARED_CLASS NodeChangingAction
{
    /// A node is being inserted in the tree.
    Insert,
    /// A node is being removed from the tree.
    Remove
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::NodeChangingAction>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::NodeChangingAction, const char_t*>, 2>& values();
};
