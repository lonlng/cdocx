//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/ISoftEdge.h
#pragma once

#include <system/object.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class ISoftEdge : public virtual System::Object
{
    typedef ISoftEdge ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual double get_EdgeRadius() = 0;
    virtual void set_EdgeRadius(double value) = 0;

    virtual void RemoveSoftEdge() = 0;

};/// \endcond

}
}
}
}
