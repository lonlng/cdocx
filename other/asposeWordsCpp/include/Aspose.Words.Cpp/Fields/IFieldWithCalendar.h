//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldWithCalendar.h
#pragma once

#include <system/object.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldWithCalendar : public virtual System::Object
{
    typedef IFieldWithCalendar ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual bool get_UseLunarCalendar() = 0;
    virtual bool get_UseSakaEraCalendar() = 0;
    virtual bool get_UseUmAlQuraCalendar() = 0;

};/// \endcond

}
}
}
