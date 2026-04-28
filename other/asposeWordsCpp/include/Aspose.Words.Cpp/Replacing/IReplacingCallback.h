//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Replacing/IReplacingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Replacing/ReplaceAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Replacing
{
class ReplacingArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Replacing {

/// \interface IReplacingCallback
/// Implement this interface if you want to have your own custom method called during a find and replace operation.
class ASPOSE_WORDS_SHARED_CLASS IReplacingCallback : public virtual System::Object
{
    typedef IReplacingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// A user defined method that is called during a replace operation for each match found just before a replace is made.
    /// 
    /// @return A <see cref="Aspose::Words::Replacing::ReplaceAction">ReplaceAction</see> value that specifies the action to be taken for the current match.
    virtual Aspose::Words::Replacing::ReplaceAction Replacing(System::SharedPtr<Aspose::Words::Replacing::ReplacingArgs> args) = 0;

};

}
}
}
