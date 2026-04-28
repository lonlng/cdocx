//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/FieldMergingArgs.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/MailMerging/FieldMergingArgsBase.h>
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

/// Provides data for the <b>%MergeField</b> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// The <b>%MergeField</b> event occurs during mail merge when a simple mail merge
/// field is encountered in the document. You can respond to this event to return
/// text for the mail merge engine to insert into the document.
/// 
/// @sa Aspose::Words::MailMerging::IFieldMergingCallback
class ASPOSE_WORDS_SHARED_CLASS FieldMergingArgs : public Aspose::Words::MailMerging::FieldMergingArgsBase
{
    typedef FieldMergingArgs ThisType;
    typedef Aspose::Words::MailMerging::FieldMergingArgsBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the text that will be inserted into the document for the current merge field.
    /// 
    /// When your event handler is called, this property is set to <c>%null</c>.
    /// 
    /// If you leave Text as <c>%null</c>, the mail merge engine will insert <see cref="Aspose::Words::MailMerging::FieldMergingArgsBase::get_FieldValue">FieldValue</see> in place of the merge field.
    /// 
    /// If you set Text to any string (including empty), the string will be inserted into the document in place of the merge field.
    ASPOSE_WORDS_SHARED_API System::String get_Text() const;
    /// Setter for Aspose::Words::MailMerging::FieldMergingArgs::get_Text
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);

protected:

private:

    System::String mField0;

};

}
}
}
