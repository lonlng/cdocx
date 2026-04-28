//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/MailMergeDataSource.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Data
{
class DataRow;
class DataSet;
class DataTable;
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Mail merge data source used for using in <see cref="Aspose::Words::LowCode::MailMergerContext">MailMergerContext</see>.
class ASPOSE_WORDS_SHARED_CLASS MailMergeDataSource : public System::Object
{
    typedef MailMergeDataSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates Mail Merge Data Source from field names and values arrays.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::MailMergeDataSource> Create(const System::ArrayPtr<System::String>& fieldNames, const System::ArrayPtr<System::SharedPtr<System::Object>>& fieldValues);
    /// Creates Mail Merge Data Source from DataRow.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::MailMergeDataSource> Create(const System::SharedPtr<System::Data::DataRow>& dataRow);
    /// Creates Mail Merge Data Source from DataTable.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::MailMergeDataSource> Create(const System::SharedPtr<System::Data::DataTable>& dataTable);
    /// Creates Mail Merge Data Source from DataSet.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::MailMergeDataSource> Create(const System::SharedPtr<System::Data::DataSet>& dataSet);

protected:

private:

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<System::Object> mField2;

    System::SharedPtr<System::Object> mField3;

    System::SharedPtr<System::Object> mField4;

    __TypeStub<4,4,4,4>::type mField5;

};

}
}
}
