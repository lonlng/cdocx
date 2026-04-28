//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/INodeCloningListener.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
class Node;
}
}

namespace Aspose {

namespace Words {

/// \cond
class INodeCloningListener : public System::Object
{
    typedef INodeCloningListener ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual void NotifyNodeCloned(System::SharedPtr<Aspose::Words::Node> source, System::SharedPtr<Aspose::Words::Node> clone) = 0;

};/// \endcond

}
}
