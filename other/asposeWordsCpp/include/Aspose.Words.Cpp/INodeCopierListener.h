//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/INodeCopierListener.h
#pragma once

#include <Aspose.Words.Cpp/INodeCloningListener.h>

namespace Aspose
{
namespace Words
{
class NodeRange;
}
}

namespace Aspose {

namespace Words {

/// \cond
class INodeCopierListener : public Aspose::Words::INodeCloningListener
{
    typedef INodeCopierListener ThisType;
    typedef Aspose::Words::INodeCloningListener BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual void NotifyNodeRangeCopied(System::SharedPtr<Aspose::Words::NodeRange> sourceRange, System::SharedPtr<Aspose::Words::NodeRange> insertedRange) = 0;

};/// \endcond

}
}
