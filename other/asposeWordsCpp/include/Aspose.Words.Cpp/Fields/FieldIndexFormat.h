//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldIndexFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies the formatting for the <see cref="Aspose::Words::Fields::FieldIndex">FieldIndex</see> fields in a document.
enum class ASPOSE_WORDS_SHARED_CLASS FieldIndexFormat
{
    /// From template.
    Template = 0,
    /// Classic.
    Classic = 1,
    /// Fancy.
    Fancy = 2,
    /// Modern.
    Modern = 3,
    /// Bulleted.
    Bulleted = 4,
    /// Formal.
    Formal = 5,
    /// Simple.
    Simple = 6
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::FieldIndexFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::FieldIndexFormat, const char_t*>, 7>& values();
};
