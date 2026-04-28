//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/IMailMergeCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace MailMerging {

/// \interface IMailMergeCallback
/// Implement this interface if you want to receive notifications while mail merge is performed.
class ASPOSE_WORDS_SHARED_CLASS IMailMergeCallback : public virtual System::Object
{
    typedef IMailMergeCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when "mustache" text tags are replaced with MERGEFIELD fields.
    /// 
    /// @sa Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields
    virtual void TagsReplaced() = 0;

};

}
}
}
