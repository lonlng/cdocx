//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldDatabaseProvider.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class FieldDatabase;
class FieldDatabaseDataTable;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IFieldDatabaseProvider
/// Implement this interface to provide data for the <see cref="Aspose::Words::Fields::FieldDatabase">FieldDatabase</see> field when it's updated.
class ASPOSE_WORDS_SHARED_CLASS IFieldDatabaseProvider : public virtual System::Object
{
    typedef IFieldDatabaseProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns query result.
    /// 
    /// @param fileName The complete path and file name of the database specified in the \\d field switch.
    /// @param connection The connection to the data specified in the \\c field switch.
    /// @param query The set of SQL instructions that query the database specified in the \\s field switch.
    /// @param field The field being updated.
    /// 
    /// @return The <see cref="Aspose::Words::Fields::FieldDatabaseDataTable">FieldDatabaseDataTable</see> instance that should be used for the field's update.
    virtual System::SharedPtr<Aspose::Words::Fields::FieldDatabaseDataTable> GetQueryResult(System::String fileName, System::String connection, System::String query, System::SharedPtr<Aspose::Words::Fields::FieldDatabase> field) = 0;

};

}
}
}
