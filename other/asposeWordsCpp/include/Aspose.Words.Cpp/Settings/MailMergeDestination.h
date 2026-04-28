//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MailMergeDestination.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the possible results which may be generated when a mail merge is carried out on a document.
/// 
/// @sa Aspose::Words::Settings::MailMergeSettings::get_Destination
enum class ASPOSE_WORDS_SHARED_CLASS MailMergeDestination
{
    /// Specifies that conforming hosting applications shall generate new documents by populating the fields
    /// within a given document with data from the specified external data source.
    NewDocument = 0,
    /// Specifies that conforming hosting applications shall print the documents that result from populating the
    /// fields within a given document with external data from the specified external data source.
    Printer = 1,
    /// Specifies that conforming hosting applications shall generate emails using the documents that result from
    /// populating the fields within a given document with data from the specified external data source.
    Email = 2,
    /// Specifies that conforming hosting applications shall generate faxes using the documents that result from
    /// populating the fields within a given document with data from the specified external data source.
    Fax = 4,
    /// Equals to the <see cref="Aspose::Words::Settings::MailMergeDestination::NewDocument">NewDocument</see> value.
    Default = static_cast<int32_t>(NewDocument)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::MailMergeDestination>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::MailMergeDestination, const char_t*>, 5>& values();
};
