//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeCollection.h
#pragma once

#include <system/enumerator_adapter.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>

#include <Aspose.Words.Cpp/NodeCollectionEnumerator.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/INodeCollection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class CompositeNode;

class DocumentBase;

class Node;

enum class NodeType;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
}
}
}

namespace Aspose {

namespace Words {

/// Represents a collection of nodes of a specific type.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// <see cref="Aspose::Words::NodeCollection">NodeCollection</see> does not own the nodes it contains, rather, is just a selection of nodes
/// of the specified type, but the nodes are stored in the tree under their respective parent nodes.
/// 
/// <see cref="Aspose::Words::NodeCollection">NodeCollection</see> supports indexed access, iteration and provides add and remove methods.
/// 
/// The <see cref="Aspose::Words::NodeCollection">NodeCollection</see> collection is "live", i.e. changes to the children of the node object
/// that it was created from are immediately reflected in the nodes returned by the <see cref="Aspose::Words::NodeCollection">NodeCollection</see>
/// properties and methods.
/// 
/// <see cref="Aspose::Words::NodeCollection">NodeCollection</see> is returned by <see cref="Aspose::Words::CompositeNode::GetChildNodes(Aspose::Words::NodeType, bool)">GetChildNodes()</see>
/// and also serves as a base class for typed node collections such as <see cref="Aspose::Words::SectionCollection">SectionCollection</see>,
/// <see cref="Aspose::Words::ParagraphCollection">ParagraphCollection</see> etc.
/// 
/// <see cref="Aspose::Words::NodeCollection">NodeCollection</see> can be "flat" and contain only immediate children of the node it was created
/// from, or it can be "deep" and contain all descendant children.
class ASPOSE_WORDS_SHARED_CLASS NodeCollection : public Aspose::Words::INodeCollection, public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>>
{
    typedef NodeCollection ThisType;
    typedef Aspose::Words::INodeCollection BaseType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>> BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of nodes in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Retrieves a node at the given index.
    /// 
    /// The index is zero-based.
    /// 
    /// Negative indexes are allowed and indicate access from the back of the collection.
    /// For example -1 means the last item, -2 means the second before last and so on.
    /// 
    /// If index is greater than or equal to the number of items in the list, this returns a null reference.
    /// 
    /// If index is negative and its absolute value is greater than the number of items in the list, this returns a null reference.
    /// 
    /// @param index An index into the collection of nodes.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> idx_get(int32_t index);

    /// Adds a node to the end of the collection.
    /// 
    /// The node is inserted as a child into the node object from which the collection was created.
    /// 
    /// If the node being inserted was created from another document, you should use
    /// <see cref="Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool, Aspose::Words::ImportFormatMode)">ImportNode()</see> to import the node to the current document.
    /// The imported node can then be inserted into the current document.
    /// 
    /// @param node The node to be added to the end of the collection.
    /// 
    /// @exception System::NotSupportedException The <see cref="Aspose::Words::NodeCollection">NodeCollection</see> is a "deep" collection.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Inserts a node into the collection at the specified index.
    /// 
    /// The node is inserted as a child into the node object from which the collection was created.
    /// 
    /// If the index is equal to or greater than <see cref="Aspose::Words::NodeCollection::get_Count">Count</see>, the node is added at the end of the collection.
    /// 
    /// If the index is negative and its absolute value is greater than <see cref="Aspose::Words::NodeCollection::get_Count">Count</see>, the node is added at the end of the collection.
    /// 
    /// If the node being inserted was created from another document, you should use
    /// <see cref="Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool, Aspose::Words::ImportFormatMode)">ImportNode()</see> to import the node to the current document.
    /// The imported node can then be inserted into the current document.
    /// 
    /// @param index The zero-based index of the node.
    ///     Negative indexes are allowed and indicate access from the back of the list.
    ///     For example -1 means the last node, -2 means the second before last and so on.
    /// @param node The node to insert.
    /// 
    /// @exception System::NotSupportedException The <see cref="Aspose::Words::NodeCollection">NodeCollection</see> is a "deep" collection.
    ASPOSE_WORDS_SHARED_API void Insert(int32_t index, const System::SharedPtr<Aspose::Words::Node>& node);
    /// Removes the node from the collection and from the document.
    /// 
    /// @param node The node to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Removes the node at the specified index from the collection and from the document.
    /// 
    /// @param index The zero-based index of the node.
    ///     Negative indexes are allowed and indicate access from the back of the list.
    ///     For example -1 means the last node, -2 means the second before last and so on.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all nodes from this collection and from the document.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Determines whether a node is in the collection.
    /// 
    /// This method performs a linear search; therefore, the average execution time is proportional to <see cref="Aspose::Words::NodeCollection::get_Count">Count</see>.
    /// 
    /// @param node The node to locate.
    /// 
    /// @return <c>%true</c> if item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Returns the zero-based index of the specified node.
    /// 
    /// This method performs a linear search; therefore, the average execution time is proportional to <see cref="Aspose::Words::NodeCollection::get_Count">Count</see>.
    /// 
    /// @param node The node to locate.
    /// 
    /// @return The zero-based index of the node within the collection, if found; otherwise, -1.
    ASPOSE_WORDS_SHARED_API int32_t IndexOf(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Copies all nodes from the collection to a new array of nodes.
    /// 
    /// You should not be adding/removing nodes while iterating over a collection
    /// of nodes because it invalidates the iterator and requires refreshes for live collections.
    /// 
    /// To be able to add/remove nodes during iteration, use this method to copy
    /// nodes into a fixed-size array and then iterate over the array.
    /// 
    /// @return An array of nodes.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<Aspose::Words::Node>> ToArray();
    /// Provides a simple "foreach" style iteration over the collection of nodes.
    /// 
    /// @return An IEnumerator.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~NodeCollection();

private:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::CompositeNode> get_Container() override;

    System::SharedPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;
    System::WeakPtr<System::Object> mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    System::WeakPtr<System::Object> mField6;
    __TypeStub<4,4,4,4>::type mField7;
    System::SharedPtr<System::Object> mField8;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> GetNextMatchingNode(System::SharedPtr<Aspose::Words::Node> ) override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> GetCurrentNode() override;

};

}
}
