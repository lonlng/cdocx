//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/Core/INumberFormatProvider.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
namespace Charts
{
namespace Core
{
namespace ComplexTypes
{
class DmlChartNumFormat;
}
}
}
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

namespace Core {

/// \cond
class INumberFormatProvider : public virtual System::Object
{
    typedef INumberFormatProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartNumFormat> get_NumFmt_INumberFormatProvider() = 0;
    virtual void set_NumFmt_INumberFormatProvider(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartNumFormat> value) = 0;
    virtual bool get_IsInherited() = 0;

};/// \endcond

}
}
}
}
}
