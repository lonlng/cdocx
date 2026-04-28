//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IShadingAttrSource.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose {

namespace Words {

/// \cond
class IShadingAttrSource : public virtual System::Object
{
    typedef IShadingAttrSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<System::Object> FetchInheritedShadingAttr(int32_t key) = 0;

};/// \endcond

}
}
