//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IDisplaceableByCustomXml.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Revisions/DisplacedByType.h>

namespace Aspose {

namespace Words {

/// \cond
class IDisplaceableByCustomXml : public virtual System::Object
{
    typedef IDisplaceableByCustomXml ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::Revisions::DisplacedByType get_DisplacedByCustomXml() = 0;
    virtual void set_DisplacedByCustomXml(Aspose::Words::Revisions::DisplacedByType value) = 0;

};/// \endcond

}
}
