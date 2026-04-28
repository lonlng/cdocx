/// @file xml/xml_entity_reference.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_linked_node.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlDocument;
class XmlLoader;
class XmlNode;
class XmlWriter;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents an entity reference node.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlEntityReference : public XmlLinkedNode
{
    typedef XmlEntityReference ThisType;
    typedef XmlLinkedNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlEntityReference>;

private:
    /// @cond
    friend class XmlNode;
    friend class XmlDocument;
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the name of the node.
    /// @returns The name of the entity referenced.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For XmlEntityReference nodes, this method returns the name of the entity referenced.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the value of the node.
    /// @returns The value of the node. For XmlEntityReference nodes, this method returns @c nullptr.
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Sets the value of the node.
    /// @param value The value to set.
    /// @throws ArgumentException Node is read-only.
    /// @throws InvalidOperationException Setting the value.
    ASPOSECPP_SHARED_API void set_Value(String value) override;
    /// Returns the type of the node.
    /// @returns The node type. For XmlEntityReference nodes, the value is XmlNodeType::EntityReference.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns a value indicating whether the node is read-only.
    /// @returns @c true if the node is read-only; otherwise @c false.
    /// Because XmlEntityReference nodes are read-only, this method always returns @c true.
    ASPOSECPP_SHARED_API bool get_IsReadOnly() override;
    /// Returns the base Uniform Resource Identifier (URI) of the current node.
    /// @returns The location from which the node was loaded.
    ASPOSECPP_SHARED_API String get_BaseURI() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// For XmlEntityReference nodes, this method always returns an entity reference node with no children.
    /// The replacement text is set when the node is inserted into a parent.
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
    ASPOSECPP_SHARED_API bool get_IsContainer() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode() override;
    ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value) override;
    String get_ChildBaseURI();
    /// @endcond

    /// Initializes a new instance of the XmlEntityReference class.
    /// @param name The name of the entity reference; see the XmlEntityReference::get_Name method.
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlEntityReference(const String& name, const SharedPtr<XmlDocument>& doc);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlEntityReference, CODEPORTING_ARGS(String name, SharedPtr<XmlDocument> doc));

    /// @cond
    ASPOSECPP_SHARED_API void SetParent(SharedPtr<XmlNode> node) override;
    ASPOSECPP_SHARED_API void SetParentForLoad(SharedPtr<XmlNode> node) override;
    ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type) override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlEntityReference();

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
    const char* DBG_class_name() const override { return "XmlEntityReference"; }
    #endif
    /// @endcond

private:

    String _name;
    SharedPtr<XmlLinkedNode> _lastChild;

    String ConstructBaseURI(const String& baseURI, const String& systemId);

};

} // namespace Xml
} // namespace System


