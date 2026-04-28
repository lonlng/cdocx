//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/IMailMergeDataSource.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// \interface IMailMergeDataSource
/// Implement this interface to allow mail merge from a custom data source, such as a list of objects. Master-detail data is also supported.
/// 
/// When a data source is created, it should be initialized to point to BOF (before the first record).
/// The %Aspose.Words mail merge engine will invoke <see cref="Aspose::Words::MailMerging::IMailMergeDataSource::MoveNext">MoveNext</see> to advance to next record and
/// then invoke <see cref="Aspose::Words::MailMerging::IMailMergeDataSource::GetValue(System::String, System::SharedPtr<System::Object>&)">GetValue()</see> for every merge field it encounters in the document or the current mail merge region.
/// 
/// @sa Aspose::Words::MailMerging::MailMerge
class ASPOSE_WORDS_SHARED_CLASS IMailMergeDataSource : public virtual System::Object
{
    typedef IMailMergeDataSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the name of the data source.
    /// 
    /// If you are implementing <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see>, return the name of the data
    /// source from this property.
    /// 
    /// %Aspose.Words uses this name to match against the mail merge region name specified
    /// in the template document. The comparison between the data source name and
    /// the mail merge region name is not case sensitive.
    /// 
    /// @return The name of the data source. Empty string if the data source has no name.
    virtual System::String get_TableName() = 0;

    /// Advances to the next record in the data source.
    /// 
    /// @return <c>%true</c> if moved to next record successfully; <c>%false</c> if reached end of the data source.
    virtual bool MoveNext() = 0;
    virtual bool GetValue(System::String fieldName, System::SharedPtr<System::Object>& fieldValue) = 0;
    /// The %Aspose.Words mail merge engine invokes this method when it encounters a beginning of a nested mail merge region.
    /// 
    /// When the %Aspose.Words mail merge engines populates a mail merge region with data and encounters the beginning of a nested
    /// mail merge region in the form of MERGEFIELD TableStart:TableName, it invokes <see cref="Aspose::Words::MailMerging::IMailMergeDataSource::GetChildDataSource(System::String)">GetChildDataSource()</see> on the current
    /// data source object. Your implementation needs to return a new data source object that will provide access to the child
    /// records of the current parent record. %Aspose.Words will use the returned data source to populate the nested mail merge region.
    /// 
    /// Below are the rules that the implementation of <see cref="Aspose::Words::MailMerging::IMailMergeDataSource::GetChildDataSource(System::String)">GetChildDataSource()</see> must follow.
    /// 
    /// If the table that is represented by this data source object has a related child (detail) table with the specified name,
    /// then your implementation needs to return a new <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see> object that will provide access
    /// to the child records of the current record.
    /// An example of this is Orders / OrderDetails relationship. Let's assume that the current <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see> object
    /// represents the Orders table and it has a current order record. Next, %Aspose.Words encounters "MERGEFIELD TableStart:OrderDetails"
    /// in the document and invokes <see cref="Aspose::Words::MailMerging::IMailMergeDataSource::GetChildDataSource(System::String)">GetChildDataSource()</see>. You need to create and return a <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see>
    /// object that will allow %Aspose.Words to access the OrderDetails record for the current order.
    /// 
    /// If this data source object does not have a relation to the table with the specified name, then you need to return
    /// a <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see> object that will provide access to all records of the specified table.
    /// 
    /// If a table with the specified name does not exist, your implementation should return <c>%null</c>.
    /// 
    /// @param tableName The name of the mail merge region as specified in the template document. Case-insensitive.
    /// 
    /// @return A data source object that will provide access to the data records of the specified table.
    virtual System::SharedPtr<Aspose::Words::MailMerging::IMailMergeDataSource> GetChildDataSource(System::String tableName) = 0;

};

}
}
}
