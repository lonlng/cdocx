/// @file xml/xml_attribute.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_node.h>
#include <system/shared_ptr.h>
#include <cstdint>


/// @cond
namespace System
{
class String;
namespace Xml
{
class DocumentSchemaValidator;
class DocumentXPathNavigator;
namespace Schema
{
class IXmlSchemaInfo;
class XsdBuilder;
} // namespace Schema
class XmlAttributeCollection;
class XmlDocument;
class XmlElement;
class XmlLinkedNode;
class XmlLoader;
class XmlName;
enum class XmlSpace;
class XmlUnspecifiedAttribute;
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

/// Represents an attribute. Valid and default values for the attribute are defined in a document type definition (DTD) or schema.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlAttribute : public XmlNode
{
    typedef XmlAttribute ThisType;
    typedef XmlNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlAttribute>;

private:
    /// @cond
    friend class DocumentSchemaValidator;
    friend class DocumentXPathNavigator;
    friend class XmlAttributeCollection;
    friend class XmlDocument;
    friend class XmlLoader;
    friend class XmlUnspecifiedAttribute;
    friend class Schema::XsdBuilder;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns The qualified name of the attribute node.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns The name of the attribute node with the prefix removed.
    /// In the following example <tt>\<book bk:genre= 'novel'></tt>, the @c LocalName of the attribute is @c genre.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the namespace URI of this node.
    /// @returns The namespace URI of this node.
    /// If the attribute is not explicitly given a namespace, this method returns String::Empty.
    ASPOSECPP_SHARED_API String get_NamespaceURI() override;
    /// Returns the namespace prefix of this node.
    /// @returns The namespace prefix of this node. If there is no prefix, this method returns String::Empty.
    ASPOSECPP_SHARED_API String get_Prefix() override;
    /// Sets the namespace prefix of this node.
    /// @param value The value to set.
    /// @throws ArgumentException This node is read-only.
    /// @throws XmlException The specified prefix contains an invalid character.
    /// The specified prefix is malformed.
    /// The namespaceURI of this node is @c nullptr.
    /// The specified prefix is "xml", and the namespaceURI of this node is different from "http://www.w3.org/XML/1998/namespace".
    /// This node is an attribute, the specified prefix is "xmlns", and the namespaceURI of this node is different from "http://www.w3.org/2000/xmlns/".
    /// This node is an attribute, and the qualifiedName of this node is "xmlns" [Namespaces].
    ASPOSECPP_SHARED_API void set_Prefix(String value) override;
    /// Returns the type of the current node.
    /// @returns The node type for XmlAttribute nodes is XmlNodeType::Attribute.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the XmlDocument to which this node belongs.
    /// @returns An XML document to which this node belongs.
    ASPOSECPP_SHARED_API SharedPtr<XmlDocument> get_OwnerDocument() override;
    /// Returns the value of the node.
    /// @returns The value returned depends on the XmlNode::get_NodeType of the node.
    /// For XmlAttribute nodes, the value of attribute is returned.
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Sets the value of the node.
    /// @param value The value to set.
    /// @throws ArgumentException The node is read-only and a set operation is called.
    ASPOSECPP_SHARED_API void set_Value(String value) override;
    /// Returns the post-schema-validation-infoset that has been assigned to this node as a result of schema validation.
    /// @returns An IXmlSchemaInfo containing the post-schema-validation-infoset of this node.
    ASPOSECPP_SHARED_API SharedPtr<Schema::IXmlSchemaInfo> get_SchemaInfo() override;
    /// Sets the concatenated values of the node and all its children.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;
    /// Returns a value indicating whether the attribute value was explicitly set.
    /// @returns @c true if this attribute was explicitly given a value in the original instance document; otherwise, @c false.
    /// A value of @c false indicates that the value of the attribute came from the DTD.
    virtual ASPOSECPP_SHARED_API bool get_Specified();
    /// Returns the XmlElement to which the attribute belongs.
    /// @returns The XmlElement that the attribute belongs to or @c nullptr if this attribute is not part of an XmlElement.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlElement> get_OwnerElement();
    /// Sets the value of the attribute.
    /// @param value The value to set.
    /// @throws XmlException The XML specified when setting this value is not well-formed.
    ASPOSECPP_SHARED_API void set_InnerXml(String value) override;
    /// Returns the base Uniform Resource Identifier (URI) of the node.
    /// @returns The location from which the node was loaded or String::Empty if the node has no base URI.
    /// Attribute nodes have the same base URI as their owner element.
    /// If an attribute node does not have an owner element, get_BaseURI returns String::Empty.
    ASPOSECPP_SHARED_API String get_BaseURI() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node; @c false to clone only the node itself.
    /// @returns The duplicate node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Inserts the specified node immediately before the specified reference node.
    /// @param newChild The XmlNode to insert.
    /// @param refChild The XmlNode that is the reference node. The @p newChild is placed before this node.
    /// @returns The XmlNode inserted.
    /// @throws InvalidOperationException The current node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// The @p refChild is not a child of this node.
    /// This node is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> InsertBefore(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild) override;
    /// Inserts the specified node immediately after the specified reference node.
    /// @param newChild The XmlNode to insert.
    /// @param refChild The XmlNode that is the reference node. The @p newChild is placed after the @p refChild.
    /// @returns The XmlNode inserted.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// The @p refChild is not a child of this node.
    /// This node is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> InsertAfter(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild) override;
    /// Replaces the child node specified with the new child node specified.
    /// @param newChild The new child XmlNode.
    /// @param oldChild The XmlNode to replace.
    /// @returns The XmlNode replaced.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// This node is read-only.
    /// The @p oldChild is not a child of this node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> ReplaceChild(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> oldChild) override;
    /// Removes the specified child node.
    /// @param oldChild The XmlNode to remove.
    /// @returns The XmlNode removed.
    /// @throws ArgumentException The @p oldChild is not a child of this node. Or this node is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveChild(SharedPtr<XmlNode> oldChild) override;
    /// Adds the specified node to the beginning of the list of child nodes for this node.
    /// @param newChild The XmlNode to add. If it is an XmlDocumentFragment, the entire contents of the document fragment
    /// are moved into the child list of this node.
    /// @returns The XmlNode added.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// This node is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> PrependChild(SharedPtr<XmlNode> newChild) override;
    /// Adds the specified node to the end of the list of child nodes, of this node.
    /// @param newChild The XmlNode to add.
    /// @returns The XmlNode added.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// This node is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> AppendChild(SharedPtr<XmlNode> newChild) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    int32_t get_LocalNameHash();
    SharedPtr<System::Xml::XmlName> get_XmlName();
    void set_XmlName(const SharedPtr<System::Xml::XmlName>& value);
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal() override;
    ASPOSECPP_SHARED_API bool get_IsContainer() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode() override;
    ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value) override;
    ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace() override;
    ASPOSECPP_SHARED_API String get_XmlLang() override;
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    ASPOSECPP_SHARED_API String get_XPLocalName() override;
    bool get_IsNamespace();

    XmlAttribute(const SharedPtr<System::Xml::XmlName>& name, const SharedPtr<XmlDocument>& doc);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAttribute, CODEPORTING_ARGS(const SharedPtr<System::Xml::XmlName>& name, const SharedPtr<XmlDocument>& doc));
    /// @endcond

    /// Initializes a new instance of the XmlAttribute class.
    /// @param prefix The namespace prefix.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace uniform resource identifier (URI).
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlAttribute(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<XmlDocument>& doc);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAttribute, CODEPORTING_ARGS(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<XmlDocument>& doc));

    /// @cond
    bool PrepareOwnerElementInElementIdAttrMap();
    void ResetOwnerElementInElementIdAttrMap(const String& oldInnerText);
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> AppendChildForLoad(const SharedPtr<XmlNode>& newChild, const SharedPtr<XmlDocument>& doc) override;
    ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type) override;
    ASPOSECPP_SHARED_API void SetParent(SharedPtr<XmlNode> node) override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlAttribute();

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
    const char* DBG_class_name() const override { return "XmlAttribute"; }
#endif
    /// @endcond

private:

    SharedPtr<System::Xml::XmlName> _name;
    SharedPtr<XmlLinkedNode> _lastChild;

};

} // namespace Xml
} // namespace System


