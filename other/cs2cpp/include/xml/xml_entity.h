/// @file xml/xml_entity.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_node.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlDocument;
class XmlLinkedNode;
class XmlLoader;
class XmlWriter;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents an entity declaration, such as <tt><!ENTITY... ></tt>.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlEntity : public XmlNode
{
    typedef XmlEntity ThisType;
    typedef XmlNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlEntity>;

private:
    /// @cond
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns a value indicating whether the node is read-only.
    /// @returns @c true if the node is read-only; otherwise, @c false.
    /// Because XmlEntity nodes are read-only, this method always returns @c true.
    ASPOSECPP_SHARED_API bool get_IsReadOnly() override;
    /// Returns the name of the node.
    /// @returns The name of the entity.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the name of the node without the namespace prefix.
    /// @returns For XmlEntity nodes, this method returns the name of the entity.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the concatenated values of the entity node and all its children.
    /// @returns The concatenated values of the node and all its children.
    ASPOSECPP_SHARED_API String get_InnerText() override;
    /// Sets the concatenated values of the entity node and all its children.
    /// @param value The value to set.
    /// @throws InvalidOperationException Attempting to set the value.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;
    /// Returns the type of the node.
    /// @returns The node type. For XmlEntity nodes, the value is XmlNodeType::Entity.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the value of the public identifier on the entity declaration.
    /// @returns The public identifier on the entity. If there is no public identifier, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_PublicId();
    /// Returns the value of the system identifier on the entity declaration.
    /// @returns The system identifier on the entity. If there is no system identifier, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_SystemId();
    /// Returns the name of the optional NDATA attribute on the entity declaration.
    /// @returns The name of the NDATA attribute. If there is no NDATA, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_NotationName();
    /// Returns the markup representing this node and all its children.
    /// @returns For XmlEntity nodes, String::Empty is returned.
    ASPOSECPP_SHARED_API String get_OuterXml() override;
    /// Returns the markup representing the children of this node.
    /// @returns For XmlEntity nodes, String::Empty is returned.
    ASPOSECPP_SHARED_API String get_InnerXml() override;
    /// Sets the markup representing the children of this node.
    /// @param value The value to set.
    /// @throws InvalidOperationException Attempting to set the value.
    ASPOSECPP_SHARED_API void set_InnerXml(String value) override;
    /// Returns the base Uniform Resource Identifier (URI) of the current node.
    /// @returns The location from which the node was loaded.
    ASPOSECPP_SHARED_API String get_BaseURI() override;

    /// Creates a duplicate of this node. Entity nodes cannot be cloned.
    /// Calling this method on an XmlEntity object throws an exception.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// @returns A copy of the XmlNode from which the method is called.
    /// @throws InvalidOperationException Entity nodes cannot be cloned.
    /// Calling this method on an XmlEntity object throws an exception.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter. For XmlEntity nodes, this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter. For XmlEntity nodes, this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API bool get_IsContainer() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode() override;
    ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value) override;

    XmlEntity(const String& name, const String& strdata, const String& publicId, const String& systemId, const String& notationName, const SharedPtr<XmlDocument>& doc);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlEntity, CODEPORTING_ARGS(String name, String strdata, String publicId, String systemId, String notationName, SharedPtr<XmlDocument> doc));

    ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type) override;
    void SetBaseURI(const String& inBaseURI);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlEntity();

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
    const char* DBG_class_name() const override { return "XmlEntity"; }
    #endif
    /// @endcond

private:

    String _publicId;
    String _systemId;
    String _notationName;
    String _name;
    String _unparsedReplacementStr;
    String _baseURI;
    SharedPtr<XmlLinkedNode> _lastChild;
    bool _childrenFoliating;

};

} // namespace Xml
} // namespace System


