//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IRunAttrSource.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/RevisionsView.h>

namespace Aspose {

namespace Words {

/// \cond
class IRunAttrSource : public virtual System::Object
{
    typedef IRunAttrSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<System::Object> GetDirectRunAttr(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> GetDirectRunAttr(int32_t key, Aspose::Words::RevisionsView revisionsView) = 0;
    virtual System::SharedPtr<System::Object> FetchInheritedRunAttr(int32_t key) = 0;
    virtual void SetRunAttr(int32_t key, System::SharedPtr<System::Object> value) = 0;
    virtual void RemoveRunAttr(int32_t key) = 0;
    virtual void ClearRunAttrs() = 0;

};/// \endcond

}
}
