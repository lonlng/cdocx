//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/IFontSource.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose
{
namespace Fonts
{
class IFontData;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerable;
}
}
}

namespace Aspose {

namespace Fonts {

/// \cond
class IFontSource : public virtual System::Object
{
    typedef IFontSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO(ThisType, ThisTypeBaseTypesInfo);

public:

    virtual int32_t get_PriorityInternal() = 0;

    virtual System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Fonts::IFontData>>> GetFontDataInternal() = 0;

};/// \endcond

}
}
