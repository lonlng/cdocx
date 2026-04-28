//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldUpdatingProgressCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class FieldUpdatingProgressArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IFieldUpdatingProgressCallback
/// Implement this interface if you want to track field updating progress.
class ASPOSE_WORDS_SHARED_CLASS IFieldUpdatingProgressCallback : public virtual System::Object
{
    typedef IFieldUpdatingProgressCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// A user defined method that is called when updating progress is changed.
    virtual void Notify(System::SharedPtr<Aspose::Words::Fields::FieldUpdatingProgressArgs> args) = 0;

};

}
}
}
