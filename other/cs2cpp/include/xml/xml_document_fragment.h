/// @file xml/xml_document_fragment.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_node.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
class String;
namespace Xml
{
class XmlDocument;
class XmlLinkedNode;
class XmlWriter;
namespace XPath
{
enum class XPathNodeType;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a lightweight object that is useful for tree insert operations.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDocumentFragment : public XmlNode
{
    typedef XmlDocumentFragment ThisType;
    typedef XmlNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlDocumentFragment>;

private:
    /// @cond
    friend class XmlDocument;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns For XmlDocumentFragment, the name is @c \#document-fragment.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For XmlDocumentFragment nodes, the local name is @c \#document-fragment.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns For XmlDocumentFragment nodes, this value is XmlNodeType::DocumentFragment.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the XmlDocument to which this node belongs.
    /// @returns The XmlDocument to which this node belongs.
    ASPOSECPP_SHARED_API SharedPtr<XmlDocument> get_OwnerDocument() override;
    /// Returns the markup representing the children of this node.
    /// @returns The markup of the children of this node.
    ASPOSECPP_SHARED_API String get_InnerXml() override;
    /// Sets the markup representing the children of this node.
    /// @param value The value to set.
    /// @throws XmlException The XML specified when setting this value is not well-formed.
    ASPOSECPP_SHARED_API void set_InnerXml(String value) override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal() override;
    ASPOSECPP_SHARED_API bool get_IsContainer() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode() override;
    ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value) override;
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    /// @endcond

    /// Initializes a new instance of the XmlDocumentFragment class.
    /// @param ownerDocument The XML document that is the source of the fragment.
    ASPOSECPP_SHARED_API XmlDocumentFragment(const SharedPtr<XmlDocument>& ownerDocument);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlDocumentFragment, CODEPORTING_ARGS(SharedPtr<XmlDocument> ownerDocument));

    /// @cond
    ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type) override;
    ASPOSECPP_SHARED_API bool CanInsertAfter(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild) override;
    ASPOSECPP_SHARED_API bool CanInsertBefore(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild) override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlDocumentFragment();

    /// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlDocumentFragment"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlLinkedNode> _lastChild;

};

} // namespace Xml
} // namespace System


