//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldIncludePictureCode.h
#pragma once

#include <system/object.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldIncludePictureCode : public virtual System::Object
{
    typedef IFieldIncludePictureCode ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::String get_SourceFullName() = 0;
    virtual bool get_IsLinked() = 0;

};/// \endcond

}
}
}
