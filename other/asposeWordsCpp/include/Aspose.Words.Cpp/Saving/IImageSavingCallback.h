//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/IImageSavingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class ImageSavingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// \interface IImageSavingCallback
/// Implement this interface if you want to control how %Aspose.Words saves images when
/// saving a document to HTML. May be used by other formats.
class ASPOSE_WORDS_SHARED_CLASS IImageSavingCallback : public virtual System::Object
{
    typedef IImageSavingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words saves an image to HTML.
    virtual void ImageSaving(System::SharedPtr<Aspose::Words::Saving::ImageSavingArgs> args) = 0;

};

}
}
}
