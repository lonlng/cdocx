//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldUpdateCultureSource.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Indicates what culture to use during field update.
enum class ASPOSE_WORDS_SHARED_CLASS FieldUpdateCultureSource
{
    /// The culture of the current execution thread is used to update fields.
    CurrentThread,
    /// The culture specified in the field formatting properties via language setting is used.
    /// 
    /// @sa Aspose::Words::Fields::Field::get_LocaleId
    FieldCode
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::FieldUpdateCultureSource>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::FieldUpdateCultureSource, const char_t*>, 2>& values();
};
