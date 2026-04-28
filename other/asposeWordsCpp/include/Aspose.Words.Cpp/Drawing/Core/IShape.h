//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/IShape.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class IShape : public virtual System::Object
{
    typedef IShape ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual int32_t get_ZOrder_IShape() = 0;
    virtual void set_ZOrder_IShape(int32_t value) = 0;

};/// \endcond

}
}
}
}
