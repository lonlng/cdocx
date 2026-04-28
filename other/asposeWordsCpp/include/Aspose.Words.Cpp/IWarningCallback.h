//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IWarningCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class WarningInfo;
}
}

namespace Aspose {

namespace Words {

/// \interface IWarningCallback
/// Implement this interface if you want to have your own custom method called to
/// capture loss of fidelity warnings that can occur during document loading or saving.
class ASPOSE_WORDS_SHARED_CLASS IWarningCallback : public virtual System::Object
{
    typedef IWarningCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// %Aspose.Words invokes this method when it encounters some issue during document loading
    /// or saving that might result in loss of formatting or data fidelity.
    virtual void Warning(System::SharedPtr<Aspose::Words::WarningInfo> info) = 0;

};

}
}
