//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SubDocument.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class DocumentVisitor;
class Node;

}
}

namespace Aspose {

namespace Words {

/// Represents a <b>%SubDocument</b> - which is a reference to an externally stored document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// In this version of %Aspose.Words, <see cref="Aspose::Words::SubDocument">SubDocument</see> nodes do not provide public methods
/// and properties to create or modify a subdocument. In this version you are not able to instantiate
/// <see cref="Aspose::Words::SubDocument">SubDocument</see> nodes or modify existing except deleting them.
/// 
/// <see cref="Aspose::Words::SubDocument">SubDocument</see> can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
class ASPOSE_WORDS_SHARED_CLASS SubDocument : public Aspose::Words::Node
{
    typedef SubDocument ThisType;
    typedef Aspose::Words::Node BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::SubDocument">SubDocument</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;

    /// Accepts a visitor.
    /// 
    /// Enumerates over this node and all of its children. Each node calls a corresponding method on <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the nodes.
    /// 
    /// @return True if all nodes were visited; false if <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> stopped the operation before visiting all nodes.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~SubDocument();

private:

    System::String mField0;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
