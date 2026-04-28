//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IRowAttrSource.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose {

namespace Words {

/// \cond
class IRowAttrSource : public virtual System::Object
{
    typedef IRowAttrSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<System::Object> GetDirectRowAttr(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> FetchRowAttr(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> FetchInheritedRowAttr(int32_t key) = 0;
    virtual void SetRowAttr(int32_t key, System::SharedPtr<System::Object> value) = 0;
    virtual void ClearRowAttrs() = 0;
    virtual void ResetToDefaultAttrs() = 0;

};/// \endcond

}
}
