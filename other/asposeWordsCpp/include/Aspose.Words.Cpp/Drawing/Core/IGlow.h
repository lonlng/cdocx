//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/IGlow.h
#pragma once

#include <system/object.h>

namespace System
{
namespace Drawing
{
class Color;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class IGlow : public virtual System::Object
{
    typedef IGlow ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::Drawing::Color get_Color() = 0;
    virtual void set_Color(System::Drawing::Color value) = 0;
    virtual double get_Transparency() = 0;
    virtual void set_Transparency(double value) = 0;
    virtual double get_Radius() = 0;
    virtual void set_Radius(double value) = 0;

    virtual void RemoveGlow() = 0;

};/// \endcond

}
}
}
}
