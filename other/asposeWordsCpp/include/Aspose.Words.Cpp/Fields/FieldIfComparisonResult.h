//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldIfComparisonResult.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies the result of the IF field condition evaluation.
enum class ASPOSE_WORDS_SHARED_CLASS FieldIfComparisonResult
{
    /// There is an error in the condition.
    Error,
    /// The condition is <c>%true</c>.
    True,
    /// The condition is <c>%false</c>.
    False
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::FieldIfComparisonResult>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::FieldIfComparisonResult, const char_t*>, 3>& values();
};
