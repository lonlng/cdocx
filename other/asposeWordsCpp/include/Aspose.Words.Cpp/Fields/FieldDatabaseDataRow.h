//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldDatabaseDataRow.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Data
{
class DataRow;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Provides data for the <see cref="Aspose::Words::Fields::FieldDatabase">FieldDatabase</see> field result. Please see <see cref="System::Data::DataRow">DataRow</see> instance.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldDatabaseDataRow : public System::Object
{
    typedef FieldDatabaseDataRow ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets values that belong to this row.
    ASPOSE_WORDS_SHARED_API const System::ArrayPtr<System::String>& get_Values() const;

    /// Initializes a new instance of the <see cref="Aspose::Words::Fields::FieldDatabaseDataRow">FieldDatabaseDataRow</see> class.
    ASPOSE_WORDS_SHARED_API FieldDatabaseDataRow(const System::ArrayPtr<System::String>& values);

    /// Initializes a new instance of the <see cref="Aspose::Words::Fields::FieldDatabaseDataRow">FieldDatabaseDataRow</see> class
    /// from the <see cref="System::Data::DataRow">DataRow</see> instance.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldDatabaseDataRow> CreateFrom(const System::SharedPtr<System::Data::DataRow>& dataRow);

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
