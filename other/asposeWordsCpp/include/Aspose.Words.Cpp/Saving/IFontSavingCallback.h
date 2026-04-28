//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/IFontSavingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class FontSavingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// \interface IFontSavingCallback
/// Implement this interface if you want to receive notifications and control how
/// %Aspose.Words saves fonts when exporting a document to HTML format.
class ASPOSE_WORDS_SHARED_CLASS IFontSavingCallback : public virtual System::Object
{
    typedef IFontSavingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words is about to save a font resource.
    virtual void FontSaving(System::SharedPtr<Aspose::Words::Saving::FontSavingArgs> args) = 0;

};

}
}
}
