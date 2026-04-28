//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeChangingArgs.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/NodeChangingAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class Node;
}
}

namespace Aspose {

namespace Words {

/// Provides data for methods of the <see cref="Aspose::Words::INodeChangingCallback">INodeChangingCallback</see> interface.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// @sa Aspose::Words::DocumentBase
/// @sa Aspose::Words::INodeChangingCallback
/// @sa Aspose::Words::NodeChangingAction
class ASPOSE_WORDS_SHARED_CLASS NodeChangingArgs : public System::Object
{
    typedef NodeChangingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the <see cref="Aspose::Words::NodeChangingArgs::get_Node">Node</see> that is being added or removed.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_Node() const;
    /// Gets the node's parent before the operation began.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_OldParent() const;
    /// Gets the node's parent that will be set after the operation completes.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_NewParent() const;
    /// Gets a value indicating what type of node change event is occurring.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeChangingAction get_Action() const;

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    __TypeStub<4,4,4,4>::type mField3;

};

}
}
