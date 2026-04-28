//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/INodeChangingCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class NodeChangingArgs;
}
}

namespace Aspose {

namespace Words {

/// \interface INodeChangingCallback
/// Implement this interface if you want to receive notifications when nodes are inserted or removed in the document.
class ASPOSE_WORDS_SHARED_CLASS INodeChangingCallback : public virtual System::Object
{
    typedef INodeChangingCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called just before a node belonging to this document is about to be inserted into another node.
    virtual void NodeInserting(System::SharedPtr<Aspose::Words::NodeChangingArgs> args) = 0;
    /// Called when a node belonging to this document has been inserted into another node.
    virtual void NodeInserted(System::SharedPtr<Aspose::Words::NodeChangingArgs> args) = 0;
    /// Called just before a node belonging to this document is about to be removed from the document.
    virtual void NodeRemoving(System::SharedPtr<Aspose::Words::NodeChangingArgs> args) = 0;
    /// Called when a node belonging to this document has been removed from its parent.
    virtual void NodeRemoved(System::SharedPtr<Aspose::Words::NodeChangingArgs> args) = 0;

};

}
}
