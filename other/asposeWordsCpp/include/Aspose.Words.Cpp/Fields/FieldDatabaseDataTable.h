//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldDatabaseDataTable.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class FieldDatabaseDataRow;
}
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IList;
}
}
namespace Data
{
class DataTable;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Provides data for the <see cref="Aspose::Words::Fields::FieldDatabase">FieldDatabase</see> field result. Please see <see cref="System::Data::DataTable">DataTable</see> instance.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldDatabaseDataTable : public System::Object
{
    typedef FieldDatabaseDataTable ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets columns that belong to this table.
    ASPOSE_WORDS_SHARED_API const System::ArrayPtr<System::String>& get_ColumnNames() const;
    /// Gets rows that belong to this table.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::Fields::FieldDatabaseDataRow>>>& get_Rows() const;

    /// Initializes a new instance of the <see cref="Aspose::Words::Fields::FieldDatabaseDataTable">FieldDatabaseDataTable</see> class.
    ASPOSE_WORDS_SHARED_API FieldDatabaseDataTable(const System::ArrayPtr<System::String>& columnNames);

    /// Initializes a new instance of the <see cref="Aspose::Words::Fields::FieldDatabaseDataTable">FieldDatabaseDataTable</see> class
    /// from the <see cref="System::Data::DataTable">DataTable</see> instance.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldDatabaseDataTable> CreateFrom(const System::SharedPtr<System::Data::DataTable>& dataTable);

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
