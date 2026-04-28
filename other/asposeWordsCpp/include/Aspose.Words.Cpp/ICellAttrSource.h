//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ICellAttrSource.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose {

namespace Words {

/// \cond
class ICellAttrSource : public virtual System::Object
{
    typedef ICellAttrSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<System::Object> GetDirectCellAttr(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> FetchCellAttr(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> FetchInheritedCellAttr(int32_t key) = 0;
    virtual void SetCellAttr(int32_t key, System::SharedPtr<System::Object> value) = 0;
    virtual void ClearCellAttrs() = 0;

};/// \endcond

}
}
