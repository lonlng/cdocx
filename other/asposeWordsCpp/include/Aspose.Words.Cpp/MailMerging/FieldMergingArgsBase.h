//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/FieldMergingArgsBase.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
namespace Fields
{
class FieldMergeField;
}

}
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// Base class for <see cref="Aspose::Words::MailMerging::FieldMergingArgs">FieldMergingArgs</see> and <see cref="Aspose::Words::MailMerging::ImageFieldMergingArgs">ImageFieldMergingArgs</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// @sa Aspose::Words::MailMerging::FieldMergingArgs
/// @sa Aspose::Words::MailMerging::ImageFieldMergingArgs
class ASPOSE_WORDS_SHARED_CLASS FieldMergingArgsBase : public System::Object
{
    typedef FieldMergingArgsBase ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the <see cref="Aspose::Words::MailMerging::FieldMergingArgsBase::get_Document">Document</see> object for which the mail merge is performed.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Document>& get_Document() const;
    /// Gets the name of the data table for the current merge operation or empty string if the name is not available.
    ASPOSE_WORDS_SHARED_API System::String get_TableName() const;
    /// Gets the zero based index of the record that is being merged.
    ASPOSE_WORDS_SHARED_API int32_t get_RecordIndex() const;
    /// Gets the name of the merge field in the data source.
    /// 
    /// If you have a mapping from a document field name to a different data source field name,
    /// then this is the mapped field name.
    /// 
    /// If you specified a field name prefix, for example "Image:MyFieldName" in the document,
    /// then <see cref="Aspose::Words::MailMerging::FieldMergingArgsBase::get_FieldName">FieldName</see> returns field name without the prefix, that is "MyFieldName".
    ASPOSE_WORDS_SHARED_API System::String get_FieldName() const;
    /// Gets the name of the merge field as specified in the document.
    /// 
    /// If you have a mapping from a document field name to a different data source field name,
    /// then this is the original field name as specified in the document.
    /// 
    /// If you specified a field name prefix, for example "Image:MyFieldName" in the document,
    /// then <see cref="Aspose::Words::MailMerging::FieldMergingArgsBase::get_DocumentFieldName">DocumentFieldName</see> returns field name without the prefix, that is "MyFieldName".
    ASPOSE_WORDS_SHARED_API System::String get_DocumentFieldName() const;
    /// Gets the value of the field from the data source.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Object>& get_FieldValue() const;
    /// Sets the value of the field from the data source.
    ASPOSE_WORDS_SHARED_API void set_FieldValue(const System::SharedPtr<System::Object>& value);
    /// Gets the object that represents the current merge field.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::FieldMergeField>& get_Field() const;

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    __TypeStub<4,4,4,4>::type mField2;
    System::String mField3;
    System::String mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;

};

}
}
}
