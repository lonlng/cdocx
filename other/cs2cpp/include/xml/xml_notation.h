/// @file xml/xml_notation.h

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
class XmlLoader;
class XmlWriter;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a notation declaration, such as <tt><!NOTATION... ></tt>.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlNotation : public XmlNode
{
    typedef XmlNotation ThisType;
    typedef XmlNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNotation>;

private:
    /// @cond
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the name of the current node.
    /// @returns The name of the notation.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the name of the current node without the namespace prefix.
    /// @returns For XmlNotation nodes, this method returns the name of the notation.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns The node type. For XmlNotation nodes, the value is XmlNodeType::Notation.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns a value indicating whether the node is read-only.
    /// @returns @c true if the node is read-only; otherwise, @c false.
    /// Because XmlNotation nodes are read-only, this method always returns @c true.
    ASPOSECPP_SHARED_API bool get_IsReadOnly() override;
    /// Returns the value of the public identifier on the notation declaration.
    /// @returns The public identifier on the notation. If there is no public identifier, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_PublicId();
    /// Returns the value of the system identifier on the notation declaration.
    /// @returns The system identifier on the notation. If there is no system identifier, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_SystemId();
    /// Returns the markup representing this node and all its children.
    /// @returns For XmlNotation nodes, String::Empty is returned.
    ASPOSECPP_SHARED_API String get_OuterXml() override;
    /// Returns the markup representing the children of this node.
    /// @returns For XmlNotation nodes, String::Empty is returned.
    ASPOSECPP_SHARED_API String get_InnerXml() override;
    /// Sets the markup representing the children of this node.
    /// @param value The value to set.
    /// @throws InvalidOperationException Attempting to set the value.
    ASPOSECPP_SHARED_API void set_InnerXml(String value) override;

    /// Creates a duplicate of this node. Notation nodes cannot be cloned.
    /// Calling this method on an XmlNotation object throws an exception.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// @returns A XmlNode copy of the node from which the method is called.
    /// @throws InvalidOperationException Notation nodes cannot be cloned.
    /// Calling this method on an XmlNotation object throws an exception.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter. This method has no effect on XmlNotation nodes.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves the children of the node to the specified XmlWriter. This method has no effect on XmlNotation nodes.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    XmlNotation(const String& name, const String& publicId, const String& systemId, const SharedPtr<XmlDocument>& doc);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlNotation, CODEPORTING_ARGS(String name, String publicId, String systemId, SharedPtr<XmlDocument> doc));
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlNotation();

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
    const char* DBG_class_name() const override { return "XmlNotation"; }
    #endif
    /// @endcond

private:

    String _publicId;
    String _systemId;
    String _name;

};

} // namespace Xml
} // namespace System


