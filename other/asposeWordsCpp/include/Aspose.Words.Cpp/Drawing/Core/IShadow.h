//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/IShadow.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Drawing/ShadowType.h>

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
class IShadow : public virtual System::Object
{
    typedef IShadow ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::Drawing::ShadowType get_ShadowType() = 0;
    virtual void set_ShadowType(Aspose::Words::Drawing::ShadowType value) = 0;
    virtual bool get_Visible() = 0;
    virtual System::Drawing::Color get_ShadowColors() = 0;
    virtual void set_ShadowColors(System::Drawing::Color value) = 0;
    virtual double get_ShadowTransparency() = 0;
    virtual void set_ShadowTransparency(double value) = 0;

    virtual void RemoveShadow() = 0;

};/// \endcond

}
}
}
}
