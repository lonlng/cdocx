//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/IReflection.h
#pragma once

#include <system/object.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class IReflection : public virtual System::Object
{
    typedef IReflection ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual double get_Blur() = 0;
    virtual void set_Blur(double value) = 0;
    virtual double get_Distance() = 0;
    virtual void set_Distance(double value) = 0;
    virtual double get_ReflectionSize() = 0;
    virtual void set_ReflectionSize(double value) = 0;
    virtual double get_ReflectionTransparency() = 0;
    virtual void set_ReflectionTransparency(double value) = 0;

    virtual void RemoveReflection() = 0;

};/// \endcond

}
}
}
}
