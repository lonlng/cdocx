//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/IDocumentLoadingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Loading
{
class DocumentLoadingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Loading {

/// \interface IDocumentLoadingCallback
/// Implement this interface if you want to have your own custom method called during loading a document.
class ASPOSE_WORDS_SHARED_CLASS IDocumentLoadingCallback : public virtual System::Object
{
    typedef IDocumentLoadingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// This is called to notify of document loading progress.
    /// 
    /// The primary uses for this interface is to allow application code to obtain progress status and abort loading process.
    /// 
    /// An exception should be threw from the progress callback for abortion and it should be caught in the consumer code.
    /// 
    /// @param args An argument of the event.
    /// 
    /// @sa Aspose::Words::Loading::LoadOptions::get_ProgressCallback
    virtual void Notify(System::SharedPtr<Aspose::Words::Loading::DocumentLoadingArgs> args) = 0;

};

}
}
}
