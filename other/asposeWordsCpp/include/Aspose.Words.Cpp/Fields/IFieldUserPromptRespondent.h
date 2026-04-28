//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldUserPromptRespondent.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IFieldUserPromptRespondent
/// Represents the respondent to user prompts during field update.
class ASPOSE_WORDS_SHARED_CLASS IFieldUserPromptRespondent : public virtual System::Object
{
    typedef IFieldUserPromptRespondent ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// When implemented, returns a response from the user on prompting.
    /// Your implementation should return <c>%null</c> to indicate that the user has not responded to the prompt
    /// (i.e. the user has pressed the Cancel button in the prompt window).
    /// 
    /// @param promptText Prompt text (i.e. title of the prompt window).
    /// @param defaultResponse Default user response (i.e. initial value contained in the prompt window).
    /// 
    /// @return User response (i.e. confirmed value contained in the prompt window).
    virtual System::String Respond(System::String promptText, System::String defaultResponse) = 0;

};

}
}
}
