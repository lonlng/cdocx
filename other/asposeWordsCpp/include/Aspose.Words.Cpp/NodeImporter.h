//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeImporter.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/ImportFormatMode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class DocumentBase;

class ImportFormatOptions;

class Node;

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

/// Allows to efficiently perform repeated import of nodes from one document to another.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// %Aspose.Words provides functionality for easy copying and moving fragments
/// between %Microsoft Word documents. This is known as "importing nodes".
/// Before you can insert a fragment from one document into another, you need to "import" it.
/// Importing creates a deep clone of the original node, ready to be inserted into the
/// destination document.
/// 
/// The simplest way to import a node is to use the <see cref="Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool)">ImportNode()</see> method
/// provided by the <see cref="Aspose::Words::DocumentBase">DocumentBase</see> object.
/// 
/// However, when you need to import nodes from one document to another multiple times,
/// it is better to use the <see cref="Aspose::Words::NodeImporter">NodeImporter</see> class. The <see cref="Aspose::Words::NodeImporter">NodeImporter</see>
/// class allows to minimize the number of styles and lists created in the destination document.
/// 
/// Copying or moving fragments from one %Microsoft Word document to another presents a number
/// of technical challenges for %Aspose.Words. In a Word document, styles and list formatting
/// are stored centrally, separately from the text of the document. The paragraphs
/// and runs of text merely reference the styles by internal unique identifiers.
/// 
/// The challenges arise from the fact that styles and lists are different in different documents.
/// For example, to copy a paragraph formatted with the Heading 1 style from one document to another,
/// a number of things must be taken into account: decide whether to copy the Heading 1 style from
/// the source document to the destination document, clone the paragraph, update the cloned
/// paragraph so it refers to the correct Heading 1 style in the destination document.
/// If the style had to be copied, all the styles that it references (based on style
/// and next paragraph style) should be analyzed and possibly copied too and so on.
/// Similar issues exist when copying bulleted or numbered paragraphs because %Microsoft Word
/// stores list definitions separately from text.
/// 
/// The <see cref="Aspose::Words::NodeImporter">NodeImporter</see> class is like a context, that holds the "translation tables"
/// during the import. It correctly translates between styles and lists in the source and
/// destination documents.
/// 
/// @sa Aspose::Words::Document
/// @sa Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool)
class ASPOSE_WORDS_SHARED_CLASS NodeImporter : public System::Object
{
    typedef NodeImporter ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Initializes a new instance of the <see cref="Aspose::Words::NodeImporter">NodeImporter</see> class.
    /// 
    /// @param srcDoc The source document.
    /// @param dstDoc The destination document that will be the owner of imported nodes.
    /// @param importFormatMode Specifies how to merge style formatting that clashes.
    ASPOSE_WORDS_SHARED_API NodeImporter(const System::SharedPtr<Aspose::Words::DocumentBase>& srcDoc, const System::SharedPtr<Aspose::Words::DocumentBase>& dstDoc, Aspose::Words::ImportFormatMode importFormatMode);
    /// Initializes a new instance of the <see cref="Aspose::Words::NodeImporter">NodeImporter</see> class.
    /// 
    /// @param srcDoc The source document.
    /// @param dstDoc The destination document that will be the owner of imported nodes.
    /// @param importFormatMode Specifies how to merge style formatting that clashes.
    /// @param importFormatOptions Specifies various options to format imported node.
    ASPOSE_WORDS_SHARED_API NodeImporter(const System::SharedPtr<Aspose::Words::DocumentBase>& srcDoc, const System::SharedPtr<Aspose::Words::DocumentBase>& dstDoc, Aspose::Words::ImportFormatMode importFormatMode, const System::SharedPtr<Aspose::Words::ImportFormatOptions>& importFormatOptions);

    /// Imports a node from one document into another.
    /// 
    /// Importing a node creates a copy of the source node belonging to the importing document.
    /// The returned node has no parent. The source node is not altered or removed from the original document.
    /// 
    /// Before a node from another document can be inserted into this document, it must be imported.
    /// During import, document-specific properties such as references to styles and lists are translated
    /// from the original to the importing document. After the node was imported, it can be inserted
    /// into the appropriate place in the document using <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see> or
    /// <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see>.
    /// 
    /// If the source node already belongs to the destination document, then simply a deep clone
    /// of the source node is created.
    /// 
    /// @param srcNode The node to import.
    /// @param isImportChildren <c>%true</c> to import all child nodes recursively; otherwise, <c>%false</c>.
    /// 
    /// @return The cloned, imported node. The node belongs to the destination document, but has no parent.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> ImportNode(const System::SharedPtr<Aspose::Words::Node>& srcNode, bool isImportChildren);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    __TypeStub<1,1,1,1>::type mField8;

    __TypeStub<1,1,1,1>::type mField9;
    System::SharedPtr<System::Object> mField10;
    __TypeStub<4,4,4,4>::type mField11;

};

}
}
