//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/IResourceSavingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class ResourceSavingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// \interface IResourceSavingCallback
/// Implement this interface if you want to control how %Aspose.Words saves external resources (images, fonts and css) when
/// saving a document to fixed page HTML or SVG.
class ASPOSE_WORDS_SHARED_CLASS IResourceSavingCallback : public virtual System::Object
{
    typedef IResourceSavingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words saves an external resource to fixed page HTML or SVG formats.
    virtual void ResourceSaving(System::SharedPtr<Aspose::Words::Saving::ResourceSavingArgs> args) = 0;

};

}
}
}
