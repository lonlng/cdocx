//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Properties/PropertyType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Properties {

/// Specifies data type of a document property.
/// 
/// @sa Aspose::Words::Properties::DocumentProperty
/// @sa Aspose::Words::Properties::DocumentProperty::get_Type
enum class ASPOSE_WORDS_SHARED_CLASS PropertyType
{
    /// The property is a boolean value.
    Boolean,
    /// The property is a date time value.
    DateTime,
    /// The property is a floating number.
    Double,
    /// The property is an integer number.
    Number,
    /// The property is a string value.
    String,
    /// The property is an array of strings.
    StringArray,
    /// The property is an array of objects.
    ObjectArray,
    /// The property is an array of bytes.
    ByteArray,
    /// The property is some other type.
    Other
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Properties::PropertyType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Properties::PropertyType, const char_t*>, 9>& values();
};
