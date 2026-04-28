//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Replacing/ReplaceAction.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Replacing {

/// Allows the user to specify what happens to the current match during a replace operation.
/// 
/// @sa Aspose::Words::Replacing::IReplacingCallback
/// @sa Aspose::Words::Range
/// @sa Aspose::Words::Range::Replace(System::String, System::String, System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>)
enum class ASPOSE_WORDS_SHARED_CLASS ReplaceAction
{
    /// Replace the current match.
    Replace,
    /// Skip the current match.
    Skip,
    /// Terminate the replace operation.
    Stop
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Replacing::ReplaceAction>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Replacing::ReplaceAction, const char_t*>, 3>& values();
};
