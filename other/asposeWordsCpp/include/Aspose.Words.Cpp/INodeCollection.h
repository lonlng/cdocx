//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/INodeCollection.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class CompositeNode;
class Node;
}
}

namespace Aspose {

namespace Words {

/// \cond
class ASPOSE_WORDS_SHARED_CLASS INodeCollection : public virtual System::Object
{
    typedef INodeCollection ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::CompositeNode> get_Container() = 0;

    virtual System::SharedPtr<Aspose::Words::Node> GetNextMatchingNode(System::SharedPtr<Aspose::Words::Node> curNode) = 0;
    virtual System::SharedPtr<Aspose::Words::Node> GetCurrentNode() = 0;

};/// \endcond

}
}
