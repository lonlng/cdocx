//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MailMergeCheckErrors.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies how %Microsoft Word will report errors detected during mail merge.
/// 
/// @sa Aspose::Words::Settings::MailMergeSettings::get_CheckErrors
enum class ASPOSE_WORDS_SHARED_CLASS MailMergeCheckErrors
{
    /// Simulate the merge and report errors in a new document.
    Simulate = 1,
    /// Complete the merge and pause to report errors.
    PauseOnError = 2,
    /// Complete the merge and report errors in a new document.
    CollectErrors = 3,
    /// Equals to the <see cref="Aspose::Words::Settings::MailMergeCheckErrors::PauseOnError">PauseOnError</see> value.
    Default = static_cast<int32_t>(PauseOnError)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::MailMergeCheckErrors>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::MailMergeCheckErrors, const char_t*>, 4>& values();
};
