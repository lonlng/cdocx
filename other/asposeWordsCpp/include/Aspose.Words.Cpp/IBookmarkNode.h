//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IBookmarkNode.h
#pragma once

#include <system/object.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// \cond
class IBookmarkNode : public virtual System::Object
{
    typedef IBookmarkNode ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::String get_Name() = 0;
    virtual void set_Name(System::String value) = 0;

};/// \endcond

}
}
