//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeMatcher.h
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
class NodeMatcher : public System::Object
{
    typedef NodeMatcher ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual bool get_IsSkipMarkupNodes() = 0;

    virtual bool IsMatch(System::SharedPtr<Aspose::Words::Node> node) = 0;

};/// \endcond

}
}
