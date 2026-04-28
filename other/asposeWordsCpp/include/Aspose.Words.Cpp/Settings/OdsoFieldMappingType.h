//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/OdsoFieldMappingType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the possible types used to indicate if a given mail merge field has been mapped to a column in the given external data source.
/// 
/// @sa Aspose::Words::Settings::OdsoFieldMapData::get_Type
enum class ASPOSE_WORDS_SHARED_CLASS OdsoFieldMappingType
{
    /// Specifies that the mail merge field has been mapped to a column in the given external data source.
    Column,
    /// Specifies that the mail merge field has not been mapped to a column in the given external data source.
    Null,
    /// Equals to <see cref="Aspose::Words::Settings::OdsoFieldMappingType::Null">Null</see>.
    Default = static_cast<int32_t>(Null)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::OdsoFieldMappingType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::OdsoFieldMappingType, const char_t*>, 3>& values();
};
