//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeReplacer.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/INodeCopierListener.h>

namespace Aspose
{
namespace Words
{

class Node;
class NodeRange;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
}

namespace Aspose {

namespace Words {

/// \cond
class NodeReplacer : public Aspose::Words::INodeCopierListener
{
    typedef NodeReplacer ThisType;
    typedef Aspose::Words::INodeCopierListener BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

protected:

    virtual void ReplaceCollectedNode(System::SharedPtr<Aspose::Words::Node> ) = 0;
    virtual void CollectClone(System::SharedPtr<Aspose::Words::Node> , System::SharedPtr<Aspose::Words::Node> );
    virtual void FinalizeReplace();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    void NotifyNodeCloned(System::SharedPtr<Aspose::Words::Node> , System::SharedPtr<Aspose::Words::Node> ) override;
    void NotifyNodeRangeCopied(System::SharedPtr<Aspose::Words::NodeRange> , System::SharedPtr<Aspose::Words::NodeRange> ) override;

};/// \endcond

}
}
