//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldBuildingBlock.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
class DocumentBuilder;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldBuildingBlock : public System::Object
{
    typedef IFieldBuildingBlock ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual void BuildBlock(System::SharedPtr<Aspose::Words::DocumentBuilder> documentBuilder) = 0;

};/// \endcond

}
}
}
