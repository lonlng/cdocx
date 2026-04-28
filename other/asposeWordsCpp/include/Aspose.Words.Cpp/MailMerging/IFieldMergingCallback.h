//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/IFieldMergingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace MailMerging
{
class FieldMergingArgs;
class ImageFieldMergingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// \interface IFieldMergingCallback
/// Implement this interface if you want to control how data is inserted into merge fields during a mail merge operation.
class ASPOSE_WORDS_SHARED_CLASS IFieldMergingCallback : public virtual System::Object
{
    typedef IFieldMergingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when the %Aspose.Words mail merge engine is about to insert data into a merge field in the document.
    virtual void FieldMerging(System::SharedPtr<Aspose::Words::MailMerging::FieldMergingArgs> args) = 0;
    /// Called when the %Aspose.Words mail merge engine is about to insert an image into a merge field.
    virtual void ImageFieldMerging(System::SharedPtr<Aspose::Words::MailMerging::ImageFieldMergingArgs> args) = 0;

};

}
}
}
