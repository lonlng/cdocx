//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Fields/FieldSwitchType.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldCodeTokenInfoProvider : public virtual System::Object
{
    typedef IFieldCodeTokenInfoProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String switchName) = 0;

};/// \endcond

}
}
}
