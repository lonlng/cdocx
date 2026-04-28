//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Comparing/ComparisonTargetType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Comparing {

/// Allows to specify base document which will be used during comparison.  Default value is <see cref="Aspose::Words::Comparing::ComparisonTargetType::Current">Current</see>.
enum class ASPOSE_WORDS_SHARED_CLASS ComparisonTargetType
{
    /// This document is used as a base during comparison.
    Current,
    /// Other document is used as a base during comparison.
    New
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Comparing::ComparisonTargetType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Comparing::ComparisonTargetType, const char_t*>, 2>& values();
};
