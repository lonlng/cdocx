//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/MergeFieldImageDimensionUnit.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies an unit of an image dimension (i.e. the width or the height) used across a mail merge process.
enum class ASPOSE_WORDS_SHARED_CLASS MergeFieldImageDimensionUnit
{
    /// The point (i.e. 1/72 inch).
    Point,
    /// The percent of the original image dimension value.
    Percent
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::MergeFieldImageDimensionUnit>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::MergeFieldImageDimensionUnit, const char_t*>, 2>& values();
};
