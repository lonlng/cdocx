//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MailMergeDataType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the type of an external mail merge data source.
/// 
/// @sa Aspose::Words::Settings::MailMergeSettings::get_DataType
enum class ASPOSE_WORDS_SHARED_CLASS MailMergeDataType
{
    /// No mail merge data source is specified.
    None = -1,
    /// Specifies that a given document has been connected to a text file via the Dynamic Data Exchange (DDE) system.
    TextFile = 0,
    /// Specifies that a given document has been connected to an Access database via the Dynamic Data Exchange (DDE) system.
    Database = 1,
    /// Specifies that a given document has been connected to an Excel spreadsheet via the Dynamic Data Exchange (DDE) system.
    Spreadsheet = 2,
    /// Specifies that a given document has been connected to an external data source using an external query tool.
    Query = 3,
    /// Specifies that a given document has been connected to an external data source via the Open Database Connectivity interface.
    Odbc = 4,
    /// Specifies that a given document has been connected to an external data source via the Office Data Source Object (ODSO) interface.
    Native = 5,
    /// Equals to <see cref="Aspose::Words::Settings::MailMergeDataType::None">None</see>.
    Default = static_cast<int32_t>(None)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::MailMergeDataType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::MailMergeDataType, const char_t*>, 8>& values();
};
