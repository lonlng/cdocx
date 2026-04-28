//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldDatabase.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>
#include <mutex>
#include <memory>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/FieldDatabaseTableFormat.h>
#include <Aspose.Words.Cpp/Fields/FieldDatabaseFormatAttributes.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Fields
{

enum class FieldSwitchType;
class FieldUpdateAction;
}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class IEnumerable;
template <typename> class IList;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the DATABASE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldDatabase : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldDatabase ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets which attributes of the format are to be applied to the table.
    ASPOSE_WORDS_SHARED_API System::String get_FormatAttributes();
    /// Sets which attributes of the format are to be applied to the table.
    ASPOSE_WORDS_SHARED_API void set_FormatAttributes(const System::String& value);
    /// Gets a connection to the data.
    ASPOSE_WORDS_SHARED_API System::String get_Connection();
    /// Sets a connection to the data.
    ASPOSE_WORDS_SHARED_API void set_Connection(const System::String& value);
    /// Gets the complete path and file name of the database
    ASPOSE_WORDS_SHARED_API System::String get_FileName();
    /// Sets the complete path and file name of the database
    ASPOSE_WORDS_SHARED_API void set_FileName(const System::String& value);
    /// Gets the integral record number of the first data record to insert.
    ASPOSE_WORDS_SHARED_API System::String get_FirstRecord();
    /// Sets the integral record number of the first data record to insert.
    ASPOSE_WORDS_SHARED_API void set_FirstRecord(const System::String& value);
    /// Gets whether to insert the field names from the database as column headings in
    /// the resulting table.
    ASPOSE_WORDS_SHARED_API bool get_InsertHeadings();
    /// Sets whether to insert the field names from the database as column headings in
    /// the resulting table.
    ASPOSE_WORDS_SHARED_API void set_InsertHeadings(bool value);
    /// Gets the format that is to be applied to the result of the database query.
    ASPOSE_WORDS_SHARED_API System::String get_TableFormat();
    /// Sets the format that is to be applied to the result of the database query.
    ASPOSE_WORDS_SHARED_API void set_TableFormat(const System::String& value);
    /// Gets whether to insert data at the beginning of a merge.
    ASPOSE_WORDS_SHARED_API bool get_InsertOnceOnMailMerge();
    /// Sets whether to insert data at the beginning of a merge.
    ASPOSE_WORDS_SHARED_API void set_InsertOnceOnMailMerge(bool value);
    /// Gets a set of SQL instructions that query the database.
    ASPOSE_WORDS_SHARED_API System::String get_Query();
    /// Sets a set of SQL instructions that query the database.
    ASPOSE_WORDS_SHARED_API void set_Query(const System::String& value);
    /// Gets the integral record number of the last data record to insert.
    ASPOSE_WORDS_SHARED_API System::String get_LastRecord();
    /// Sets the integral record number of the last data record to insert.
    ASPOSE_WORDS_SHARED_API void set_LastRecord(const System::String& value);

    ASPOSE_WORDS_SHARED_API FieldDatabase();

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldDatabase();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
