//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/MailMergerContext.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace LowCode
{

class MailMergeOptions;
}
}
}
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

/// Mail merge context.
class ASPOSE_WORDS_SHARED_CLASS MailMergerContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef MailMergerContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Mail merge options.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::LowCode::MailMergeOptions>& get_MailMergeOptions() const;

    ASPOSE_WORDS_SHARED_API MailMergerContext();

    /// Sets data source used to execute simple mail merge.
    ASPOSE_WORDS_SHARED_API void SetSimpleDataSource(const System::ArrayPtr<System::String>& fieldNames, const System::ArrayPtr<System::SharedPtr<System::Object>>& fieldValues);
    /// Sets data source used to execute simple mail merge.
    ASPOSE_WORDS_SHARED_API void SetSimpleDataSource(const System::SharedPtr<System::Data::DataRow>& dataRow);
    /// Sets data source used to execute simple mail merge.
    ASPOSE_WORDS_SHARED_API void SetSimpleDataSource(const System::SharedPtr<System::Data::DataTable>& dataTable);
    /// Sets data source used to execute mail merge with regions.
    ASPOSE_WORDS_SHARED_API void SetRegionsDataSource(const System::SharedPtr<System::Data::DataTable>& dataTable);
    /// Sets data source used to execute mail merge with regions.
    ASPOSE_WORDS_SHARED_API void SetRegionsDataSource(const System::SharedPtr<System::Data::DataSet>& dataSet);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<System::Object> mField2;

};

}
}
}
