//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/IResourceLoadingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Loading/ResourceLoadingAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Loading
{
class ResourceLoadingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Loading {

/// \interface IResourceLoadingCallback
/// Implement this interface if you want to control how %Aspose.Words loads external resource when
/// importing a document and inserting images using <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>.
class ASPOSE_WORDS_SHARED_CLASS IResourceLoadingCallback : public virtual System::Object
{
    typedef IResourceLoadingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words loads any external resource.
    virtual Aspose::Words::Loading::ResourceLoadingAction ResourceLoading(System::SharedPtr<Aspose::Words::Loading::ResourceLoadingArgs> args) = 0;

};

}
}
}
