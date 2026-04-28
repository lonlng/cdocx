//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeList.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>

#include <Aspose.Words.Cpp/Node.h>

namespace Aspose { namespace Words { class NodeCollection; } }

namespace Aspose {

namespace Words {

/// Represents a collection of nodes matching an XPath query executed using the <see cref="Aspose::Words::CompositeNode::SelectNodes(System::String)">SelectNodes()</see> method.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// <see cref="Aspose::Words::NodeList">NodeList</see> is returned by <see cref="Aspose::Words::CompositeNode::SelectNodes(System::String)">SelectNodes()</see> and contains a collection
/// of nodes matching the XPath query.
/// 
/// <see cref="Aspose::Words::NodeList">NodeList</see> supports indexed access and iteration.
/// 
/// @note Treat the <see cref="Aspose::Words::NodeList">NodeList</see> collection as a "snapshot" collection. <see cref="Aspose::Words::NodeList">NodeList</see> starts
/// as a "live" collection because the nodes are not actually retrieved when the XPath query is run.
/// The nodes are only retrieved upon access and at this time the node and all nodes that precede
/// it are cached forming a "snapshot" collection.
class ASPOSE_WORDS_SHARED_CLASS NodeList : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>>
{
    typedef NodeList ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of nodes in the list.
    ASPOSE_WORDS_SHARED_API int32_t get_Count() const;

    ASPOSE_WORDS_SHARED_API NodeList(const System::SharedPtr<Aspose::Words::NodeCollection>& nodes);

    /// Provides a simple "foreach" style iteration over the collection of nodes.
    /// 
    /// @return An IEnumerator.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>>> GetEnumerator() override;

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
    /// @param index An index into the list of nodes.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> idx_get(int32_t index) const;

    /// Copies all nodes from the collection to a new array of nodes.
    /// 
    /// You should not be adding/removing nodes while iterating over a collection
    /// of nodes because it invalidates the iterator and requires refreshes for live collections.
    /// 
    /// To be able to add/remove nodes during iteration, use this method to copy
    /// nodes into a fixed-size array and then iterate over the array.
    /// 
    /// @return An array of nodes.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<Aspose::Words::Node>> ToArray() const;

#ifdef __DBG_FOR_EACH_MEMBER
public:
    ASPOSE_WORDS_SHARED_API void DBG_for_each_member(System::DBG::for_each_member_visitor &visitor) const override;
    ASPOSE_WORDS_SHARED_API const char* DBG_class_name() const override;
#endif

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
