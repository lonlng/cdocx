//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldDatabaseFormatAttributes.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// FieldDatabaseFormatAttributes enumeration.
enum class FieldDatabaseFormatAttributes
{
    None = 0,
    Borders = 1,
    Shading = 2,
    Font = 4,
    Color = 8,
    AutoFit = 16,
    FirstRow = 32,
    LastRow = 64,
    FirstColumn = 128,
    LastColumn = 256
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Fields::FieldDatabaseFormatAttributes);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Fields);
template<>
struct EnumMetaInfo<Aspose::Words::Fields::FieldDatabaseFormatAttributes>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::FieldDatabaseFormatAttributes, const char_t*>, 10>& values();
};
