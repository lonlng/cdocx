//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/TextFormFieldType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies the type of a text form field.
enum class ASPOSE_WORDS_SHARED_CLASS TextFormFieldType
{
    /// The text form field can contain any text.
    Regular = 0,
    /// The text form field can contain only numbers.
    Number = 1,
    /// The text form field can contain only a valid date value.
    Date = 2,
    /// The text form field value is the current date when the field is updated.
    CurrentDate = 3,
    /// The text form field value is the current time when the field is updated.
    CurrentTime = 4,
    /// The text form field value is calculated from the expression specified in
    /// the <see cref="Aspose::Words::Fields::FormField::get_TextInputDefault">TextInputDefault</see> property.
    Calculated = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::TextFormFieldType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::TextFormFieldType, const char_t*>, 6>& values();
};
