//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/DocumentRecoveryMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Specifies the available recovery options when a document encounters errors during loading.
enum class ASPOSE_WORDS_SHARED_CLASS DocumentRecoveryMode
{
    /// No recovery is attempted.
    /// If the document is invalid, loading will fail with an error.
    None = 0,
    /// Attempts to recover the document while preserving as much data as possible.
    TryRecover = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::DocumentRecoveryMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::DocumentRecoveryMode, const char_t*>, 2>& values();
};
