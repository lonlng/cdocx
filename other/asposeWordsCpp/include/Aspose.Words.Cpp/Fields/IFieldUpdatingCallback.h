//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldUpdatingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class Field;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IFieldUpdatingCallback
/// Implement this interface if you want to have your own custom methods called during a field update.
class ASPOSE_WORDS_SHARED_CLASS IFieldUpdatingCallback : public virtual System::Object
{
    typedef IFieldUpdatingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// A user defined method that is called just before a field is updated.
    virtual void FieldUpdating(System::SharedPtr<Aspose::Words::Fields::Field> field) = 0;
    /// A user defined method that is called just after a field is updated.
    virtual void FieldUpdated(System::SharedPtr<Aspose::Words::Fields::Field> field) = 0;

};

}
}
}
