//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldResultFormatApplier.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
class NodeRange;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldResultFormatApplier : public System::Object
{
    typedef IFieldResultFormatApplier ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual void ApplyFormat(System::SharedPtr<Aspose::Words::NodeRange> result) = 0;

};/// \endcond

}
}
}
