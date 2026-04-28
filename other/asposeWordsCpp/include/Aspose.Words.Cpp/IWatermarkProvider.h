//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IWatermarkProvider.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
class Shape;
}
}
}

namespace Aspose {

namespace Words {

/// \cond
class IWatermarkProvider : public virtual System::Object
{
    typedef IWatermarkProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual void Add(System::SharedPtr<Aspose::Words::Drawing::Shape> watermark) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Shape> Get() = 0;
    virtual void Remove() = 0;

};/// \endcond

}
}
