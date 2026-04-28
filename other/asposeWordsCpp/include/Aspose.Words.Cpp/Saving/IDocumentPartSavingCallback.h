//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/IDocumentPartSavingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class DocumentPartSavingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// \interface IDocumentPartSavingCallback
/// Implement this interface if you want to receive notifications and control how
/// %Aspose.Words saves document parts when exporting a document to <see cref="Aspose::Words::SaveFormat::Html">Html</see>
/// or <see cref="Aspose::Words::SaveFormat::Epub">Epub</see> format.
class ASPOSE_WORDS_SHARED_CLASS IDocumentPartSavingCallback : public virtual System::Object
{
    typedef IDocumentPartSavingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words is about to save a document part.
    virtual void DocumentPartSaving(System::SharedPtr<Aspose::Words::Saving::DocumentPartSavingArgs> args) = 0;

};

}
}
}
