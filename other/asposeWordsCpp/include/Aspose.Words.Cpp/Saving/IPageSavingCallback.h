//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/IPageSavingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class PageSavingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// \interface IPageSavingCallback
/// Implement this interface if you want to control how %Aspose.Words saves separate pages when
/// saving a document to fixed page formats.
class ASPOSE_WORDS_SHARED_CLASS IPageSavingCallback : public virtual System::Object
{
    typedef IPageSavingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words saves a separate page to fixed page formats.
    virtual void PageSaving(System::SharedPtr<Aspose::Words::Saving::PageSavingArgs> args) = 0;

};

}
}
}
