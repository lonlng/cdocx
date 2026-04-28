//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/OdsoDataSourceType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the type of the external data source to be connected to as part of the ODSO connection information.
/// 
/// The OOXML specification is very vague for this enum. I guess it might correspond to the WdMergeSubType
/// enumeration http://msdn.microsoft.com/en-us/library/bb237801.aspx.
/// 
/// @sa Aspose::Words::Settings::Odso::get_DataSourceType
enum class ASPOSE_WORDS_SHARED_CLASS OdsoDataSourceType
{
    /// Specifies that a given document has been connected to a text file.
    /// Possibly wdMergeSubTypeOther.
    Text = 0,
    /// Specifies that a given document has been connected to a database.
    /// Possibly wdMergeSubTypeAccess.
    Database = 1,
    /// Specifies that a given document has been connected to an address book of contacts.
    /// Possibly wdMergeSubTypeOAL.
    AddressBook = 2,
    /// Specifies that a given document has been connected to another document format supported by the producing application.
    /// Possibly wdMergeSubTypeOLEDBWord.
    Document1 = 3,
    /// Specifies that a given document has been connected to another document format supported by the producing application.
    /// Possibly wdMergeSubTypeWorks.
    Document2 = 4,
    /// Specifies that a given document has been connected to another document format native to the producing application.
    /// Possibly wdMergeSubTypeOLEDBText
    Native = 5,
    /// Specifies that a given document has been connected to an e-mail application.
    /// Possibly wdMergeSubTypeOutlook.
    Email = 6,
    /// The type of the external data source is not specified.
    /// Possibly wdMergeSubTypeWord.
    None = 7,
    /// Specifies that a given document has been connected to a legacy document format supported by the producing application
    /// Possibly wdMergeSubTypeWord2000.
    Legacy = 8,
    /// Specifies that a given document has been connected to a data source which aggregates other data sources.
    Master,
    /// Equals to <see cref="Aspose::Words::Settings::OdsoDataSourceType::None">None</see>.
    Default = static_cast<int32_t>(None)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::OdsoDataSourceType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::OdsoDataSourceType, const char_t*>, 11>& values();
};
