//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ICssSavingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class CssSavingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// \interface ICssSavingCallback
/// Implement this interface if you want to control how %Aspose.Words saves CSS (Cascading Style Sheet) when
/// saving a document to HTML.
class ASPOSE_WORDS_SHARED_CLASS ICssSavingCallback : public virtual System::Object
{
    typedef ICssSavingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words saves an CSS (Cascading Style Sheet).
    virtual void CssSaving(System::SharedPtr<Aspose::Words::Saving::CssSavingArgs> args) = 0;

};

}
}
}
