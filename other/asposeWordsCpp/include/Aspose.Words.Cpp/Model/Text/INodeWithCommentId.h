//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Model/Text/INodeWithCommentId.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose {

namespace Words {

/// \cond
class INodeWithAnnotationId : public virtual System::Object
{
    typedef INodeWithAnnotationId ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual int32_t get_IdInternal() = 0;
    virtual void set_IdInternal(int32_t value) = 0;
    virtual int32_t get_ParentIdInternal() = 0;
    virtual void set_ParentIdInternal(int32_t value) = 0;

};/// \endcond

}
}
