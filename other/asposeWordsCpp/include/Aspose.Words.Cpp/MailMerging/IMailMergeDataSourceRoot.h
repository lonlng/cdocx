//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/IMailMergeDataSourceRoot.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace MailMerging
{
class IMailMergeDataSource;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// \interface IMailMergeDataSourceRoot
/// Implement this interface to allow mail merge from a custom data source with master-detail data.
class ASPOSE_WORDS_SHARED_CLASS IMailMergeDataSourceRoot : public virtual System::Object
{
    typedef IMailMergeDataSourceRoot ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The %Aspose.Words mail merge engine invokes this method when it encounters a beginning of a top-level mail merge region.
    /// 
    /// When the %Aspose.Words mail merge engines populates a document with data and encounters MERGEFIELD TableStart:TableName,
    /// it invokes <see cref="Aspose::Words::MailMerging::IMailMergeDataSourceRoot::GetDataSource(System::String)">GetDataSource()</see> on this object. Your implementation needs to return a new data source object.
    /// %Aspose.Words will use the returned data source to populate the mail merge region.
    /// 
    /// If a data source (table) with the specified name does not exist, your implementation should return <c>%null</c>.
    /// 
    /// @param tableName The name of the mail merge region as specified in the template document. Case-insensitive.
    /// 
    /// @return A data source object that will provide access to the data records of the specified table.
    virtual System::SharedPtr<Aspose::Words::MailMerging::IMailMergeDataSource> GetDataSource(System::String tableName) = 0;

};

}
}
}
