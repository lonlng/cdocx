//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/CompositeNode.h
#pragma once

#include <system/object_ext.h>
#include <system/exceptions.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/details/dispose_guard.h>
#include <system/constraints.h>
#include <system/collections/ienumerable.h>
#include <system/array.h>

#include <Aspose.Words.Cpp/Revisions/RevisionTrackingUtil.h>
#include <Aspose.Words.Cpp/NodeUtil.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/NodeChangingArgs.h>
#include <Aspose.Words.Cpp/NodeChangingAction.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/INodeCollection.h>
#include <Aspose.Words.Cpp/CompositeNodeHelper.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/SuspendTrackRevisionsDocument.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class DocumentBase;

class DocumentVisitor;

class INodeCloningListener;

class Node;
class NodeCollection;

class NodeList;

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
namespace Text
{
class StringBuilder;
}
}

namespace Aspose {

namespace Words {

/// Base class for nodes that can contain other nodes.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// A document is represented as a tree of nodes, similar to DOM or XmlDocument.
/// 
/// For more info see the Composite design pattern.
/// 
/// The <see cref="Aspose::Words::CompositeNode">CompositeNode</see> class:
/// 
/// - Provides access to the child nodes.
/// - Implements Composite operations such as insert and remove children.
/// - Provides methods for XPath navigation.
class ASPOSE_WORDS_SHARED_CLASS CompositeNode : public Aspose::Words::Node, public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>>, public Aspose::Words::INodeCollection
{
    typedef CompositeNode ThisType;
    typedef Aspose::Words::Node BaseType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>> BaseType1;
    typedef Aspose::Words::INodeCollection BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::Node::Clone;

public:

    /// Returns <c>%true</c> as this node can have child nodes.
    ASPOSE_WORDS_SHARED_API bool get_IsComposite() override;
    /// Returns <c>%true</c> if this node has any child nodes.
    ASPOSE_WORDS_SHARED_API bool get_HasChildNodes();
    /// Gets the first child of the node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_FirstChild() const;
    /// Gets the last child of the node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_LastChild() const;
    /// Gets the number of immediate children of this node.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets the text of this node and of all its children.
    /// 
    /// The returned string includes all control and special characters as described in <see cref="Aspose::Words::ControlChar">ControlChar</see>.
    ASPOSE_WORDS_SHARED_API System::String GetText() override;
    /// Returns a live collection of child nodes that match the specified type.
    /// 
    /// The collection of nodes returned by this method is always live.
    /// 
    /// A live collection is always in sync with the document. For example, if you
    /// selected all sections in a document and enumerate through the collection
    /// deleting the sections, the section is removed from the collection immediately
    /// when it is removed from the document.
    /// 
    /// @param nodeType Specifies the type of nodes to select.
    /// @param isDeep <c>%true</c> to select from all child nodes recursively;
    ///     <c>%false</c> to select only among immediate children.
    /// 
    /// @return A live collection of child nodes of the specified type.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeCollection> GetChildNodes(Aspose::Words::NodeType nodeType, bool isDeep);
    /// Returns an Nth child node that matches the specified type.
    /// 
    /// If index is out of range, a <c>%null</c> is returned.
    /// 
    /// @param nodeType Specifies the type of the child node.
    /// @param index Zero based index of the child node to select.
    ///     Negative indexes are also allowed and indicate access from the end,
    ///     that is -1 means the last node.
    /// @param isDeep <c>%true</c> to select from all child nodes recursively;
    ///     <c>%false</c> to select only among immediate children. See remarks for more info.
    /// 
    /// @return The child node that matches the criteria or <c>%null</c> if no matching node is found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> GetChild(Aspose::Words::NodeType nodeType, int32_t index, bool isDeep);
    /// Selects a list of nodes matching the XPath expression.
    /// 
    /// Only expressions with element names are supported at the moment. Expressions
    /// that use attribute names are not supported.
    /// 
    /// @param xpath The XPath expression.
    /// 
    /// @return A list of nodes matching the XPath query.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeList> SelectNodes(const System::String& xpath);
    /// Selects the first <see cref="Aspose::Words::Node">Node</see> that matches the XPath expression.
    /// 
    /// Only expressions with element names are supported at the moment. Expressions
    /// that use attribute names are not supported.
    /// 
    /// @param xpath The XPath expression.
    /// 
    /// @return The first <see cref="Aspose::Words::Node">Node</see> that matches the XPath query or <c>%null</c> if no matching node is found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> SelectSingleNode(const System::String& xpath);
    /// Provides support for the for each style iteration over the child nodes of this node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>>> GetEnumerator() override;
    template <typename T>
    T AppendChild(T newChild)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        return InsertAfter<T>(newChild, get_LastChild());
    }

    template <typename T>
    T PrependChild(T newChild)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        return InsertBefore<T>(newChild, get_FirstChild());
    }

    template <typename T>
    T InsertAfter(T newChild, const System::SharedPtr<Aspose::Words::Node>& refChild)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        return Insert<T>(newChild, refChild, true);
    }

    template <typename T>
    T InsertBefore(T newChild, const System::SharedPtr<Aspose::Words::Node>& refChild)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        return Insert<T>(newChild, refChild, false);
    }

    template <typename T>
    T RemoveChild(T oldChild)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        return RemoveChildCore<T>(oldChild, false);
    }

    /// Removes all the child nodes of the current node.
    ASPOSE_WORDS_SHARED_API void RemoveAllChildren();
    /// Removes all <see cref="Aspose::Words::Markup::SmartTag">SmartTag</see> descendant nodes of the current node.
    ASPOSE_WORDS_SHARED_API void RemoveSmartTags();
    /// Returns the index of the specified child node in the child node array.
    ASPOSE_WORDS_SHARED_API int32_t IndexOf(const System::SharedPtr<Aspose::Words::Node>& child);
    /// When implemented in a derived class, calls the VisitXXXStart method of the specified document visitor.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) = 0;
    /// When implemented in a derived class, calls the VisitXXXEnd method of the specified document visitor.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) = 0;
    ASPOSE_WORDS_SHARED_API void SetTemplateWeakPtr(uint32_t argument) override;

protected:

    ASPOSE_WORDS_SHARED_API CompositeNode();

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;
    ASPOSE_WORDS_SHARED_API void GetTextToBuilder(System::SharedPtr<System::Text::StringBuilder> ) override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> GetNodeFromPos(int32_t ) override;
    ASPOSE_WORDS_SHARED_API int32_t GetTextLength() override;
    virtual ASPOSE_WORDS_SHARED_API System::String GetEndText();

    virtual ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> );

    #if defined(__MSVC__)
    #pragma warning( push )
    #pragma warning(disable : 4715)
    #pragma warning(disable : 4700)
    #pragma warning(disable : 4701)
    #elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wreturn-type"
    #endif
    template <typename T>
    T Insert(T newChild, const System::SharedPtr<Aspose::Words::Node>& refChild, bool isAfter)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        if ((refChild != nullptr) && (refChild->get_ParentNode() != this))
        {
            throw System::ArgumentException(u"The reference node is not a child of this node.");
        }

        if (System::ObjectExt::UnknownIsNull(newChild))
        {
            throw System::ArgumentException(u"Cannot insert a null node.");
        }

        if (newChild == this)
        {
            throw System::ArgumentException(u"Cannot add a node to self.");
        }

        if (IsAncestorNode(newChild))
        {
            throw System::ArgumentException(u"The newChild is an ancestor of this node.");
        }

        if (newChild == refChild)
        {
            throw System::ArgumentException(u"Cannot add a node before/after itself.");
        }

        System::SharedPtr<Aspose::Words::DocumentBase> thisDoc = get_Document();
        System::SharedPtr<Aspose::Words::DocumentBase> childDoc = newChild->get_Document();
        Aspose::Words::CompositeNodeHelper::DocumentBaseCompareException(thisDoc, childDoc);

        if ((newChild->get_NodeType() != Aspose::Words::NodeType::System) && !CanInsert(newChild))
        {
            throw System::ArgumentException(u"Cannot insert a node of this type at this location.");
        }

        System::SharedPtr<Aspose::Words::CompositeNode> oldParent = newChild->get_ParentNode();
        System::SharedPtr<Aspose::Words::Node> oldNextSibling = newChild->get_NextSibling();

        if (oldParent != nullptr)
        {

            {
                System::SharedPtr<Aspose::Words::SuspendTrackRevisionsDocument> __using_resource_0 = System::MakeObject<Aspose::Words::SuspendTrackRevisionsDocument>(thisDoc);

                System::Details::DisposeGuard<1> __dispose_guard_1({ __using_resource_0});

                try
                {
                    oldParent->template RemoveChildCore<T>(newChild, true);
                }
                catch(...)
                {
                    __dispose_guard_1.SetCurrentException(std::current_exception());
                }
            }
        }

        System::SharedPtr<Aspose::Words::NodeChangingArgs> args = Aspose::Words::CompositeNodeHelper::DocumentBaseInternalEvent(thisDoc, newChild, nullptr, System::MakeSharedPtr(this), Aspose::Words::NodeChangingAction::Insert);
        Aspose::Words::CompositeNodeHelper::DocumentBaseBeforeEvent(thisDoc, args);

        if (mLastChild == nullptr)
        {

            newChild->set_PrevNode(nullptr);
            newChild->set_NextNode(nullptr);
            mFirstChild = newChild;
            mLastChild = newChild;
        }
        else
        {
            if (isAfter)
            {
                if (refChild != nullptr)
                {

                    InsertAfterCore(newChild, refChild);
                }
                else
                {

                    InsertBeforeCore(newChild, mFirstChild);
                }
            }
            else
            {
                if (refChild != nullptr)
                {
                    InsertBeforeCore(newChild, refChild);
                }
                else
                {

                    InsertAfterCore(newChild, mLastChild);
                }
            }
        }

        newChild->SetParent(System::MakeSharedPtr(this));

        Aspose::Words::CompositeNodeHelper::DocumentBaseAfterEvent(thisDoc, args);

        if (Aspose::Words::CompositeNodeHelper::DocumentBaseIsTrackRevisionsEnabled(thisDoc))
        {
            Aspose::Words::Revisions::RevisionTrackingUtil::TrackInsertion(newChild, oldParent, oldNextSibling);
        }

        return newChild;
    }
    #if defined(__MSVC__)
    #pragma warning( pop )
    #elif defined(__GNUC__)
    #pragma GCC diagnostic pop
    #endif

    virtual ASPOSE_WORDS_SHARED_API ~CompositeNode();

private:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::CompositeNode> get_Container() override;

    System::SharedPtr<Aspose::Words::Node> mFirstChild;
    System::SharedPtr<Aspose::Words::Node> mLastChild;
    System::SharedPtr<System::Object> mField2;

    template <typename T>
    T RemoveChildCore(T oldChild, bool skipUpdatingRelatedNodes)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        if (System::ObjectExt::UnknownIsNull(oldChild))
        {
            throw System::ArgumentNullException(u"oldChild");
        }

        if (oldChild->get_ParentNode() != this)
        {
            throw System::ArgumentException(u"This node is not a parent of the oldChild node.");
        }

        System::SharedPtr<Aspose::Words::DocumentBase> doc = get_Document();

        System::SharedPtr<Aspose::Words::NodeChangingArgs> args = Aspose::Words::CompositeNodeHelper::DocumentBaseInternalEvent(doc, oldChild, System::MakeSharedPtr(this), nullptr, Aspose::Words::NodeChangingAction::Remove);

        if (Aspose::Words::CompositeNodeHelper::DocumentBaseIsTrackRevisionsEnabled(doc))
        {
            if (Aspose::Words::Revisions::RevisionTrackingUtil::TrackDeletion(oldChild))
            {
                return oldChild;
            }
        }

        Aspose::Words::CompositeNodeHelper::DocumentBaseBeforeEvent(doc, args);

        if (!skipUpdatingRelatedNodes && Aspose::Words::NodeUtil::IsStructuredDocumentTagNode(oldChild))
        {
            Aspose::Words::NodeUtil::ResetDisplacedAnnotationReferences(oldChild, false);
        }

        T removedNode = RemoveNode<T>(oldChild);

        Aspose::Words::CompositeNodeHelper::DocumentBaseAfterEvent(doc, args);

        return removedNode;
    }

    ASPOSE_WORDS_SHARED_API void InsertAfterCore(const System::SharedPtr<Aspose::Words::Node>& newChild, const System::SharedPtr<Aspose::Words::Node>& prevChild);
    ASPOSE_WORDS_SHARED_API void InsertBeforeCore(const System::SharedPtr<Aspose::Words::Node>& newChild, const System::SharedPtr<Aspose::Words::Node>& nextChild);

    template <typename T>
    T RemoveNode(T oldChild)
    {
        typedef Aspose::Words::Node BaseT_Node;
        assert_is_base_of(BaseT_Node, T);

        if (oldChild == mFirstChild)
        {
            if (mFirstChild == mLastChild)
            {

                mFirstChild.reset();
                mLastChild.reset();
            }
            else
            {

                mFirstChild = oldChild->get_NextNode();
                mFirstChild->set_PrevNode(nullptr);
            }
        }
        else
        {

            System::SharedPtr<Aspose::Words::Node> prevNode = oldChild->get_PrevNode();
            System::SharedPtr<Aspose::Words::Node> nextNode = oldChild->get_NextNode();
            prevNode->set_NextNode(nextNode);

            if (nextNode == nullptr)
            {
                mLastChild = prevNode;
            }
            else
            {
                nextNode->set_PrevNode(prevNode);
            }
        }

        oldChild->set_NextNode(nullptr);
        oldChild->set_PrevNode(nullptr);
        oldChild->SetParent(nullptr);

        return oldChild;
    }

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> GetNextMatchingNode(System::SharedPtr<Aspose::Words::Node> ) override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> GetCurrentNode() override;

};

}
}
