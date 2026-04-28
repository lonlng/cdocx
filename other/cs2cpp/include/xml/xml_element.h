/// @file xml/xml_element.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_linked_node.h>
#include <system/shared_ptr.h>
#include <cstdint>


/// @cond
namespace System
{
class String;
namespace Xml
{
class DocumentSchemaValidator;
class DocumentXmlWriter;
class DocumentXPathNavigator;
namespace Schema
{
class IXmlSchemaInfo;
class Parser;
} // namespace Schema
class XmlAttribute;
class XmlAttributeCollection;
class XmlDocument;
class XmlLoader;
class XmlName;
class XmlNode;
class XmlNodeList;
class XmlNodeReaderNavigator;
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

/// Represents an element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlElement : public XmlLinkedNode
{
    typedef XmlElement ThisType;
    typedef XmlLinkedNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlElement>;

private:
    /// @cond
    friend class DocumentSchemaValidator;
    friend class DocumentXmlWriter;
    friend class DocumentXPathNavigator;
    friend class XmlAttribute;
    friend class XmlNode;
    friend class XmlAttributeCollection;
    friend class XmlDocument;
    friend class XmlLoader;
    friend class XmlNodeReaderNavigator;
    friend class Schema::Parser;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns The qualified name of the node. For XmlElement nodes, this is the tag name of the element.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the current node.
    /// @returns The name of the current node with the prefix removed.
    /// For example, @c get_LocalName value is @c book for the element <tt><bk:book></tt>.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the namespace URI of this node.
    /// @returns The namespace URI of this node. If there is no namespace URI, this method returns String::Empty.
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
    /// The specified prefix is "xml" and the namespaceURI of this node is different from http://www.w3.org/XML/1998/namespace.
    ASPOSECPP_SHARED_API void set_Prefix(String value) override;
    /// Returns the type of the current node.
    /// @returns The node type. For XmlElement nodes, this value is XmlNodeType::Element.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the XmlDocument to which this node belongs.
    /// @returns The XmlDocument to which this element belongs.
    ASPOSECPP_SHARED_API SharedPtr<XmlDocument> get_OwnerDocument() override;
    /// Returns the tag format of the element.
    /// @returns @c true if the element is to be serialized in the short tag format "<tt><item/></tt>";
    /// @c false for the long format "<tt><item></item></tt>".
    ASPOSECPP_SHARED_API bool get_IsEmpty();
    /// Sets the tag format of the element.
    /// @param value The value to set.
    /// When setting this value, if set to @c true,
    /// the children of the element are removed and the element is serialized in the short tag format.
    /// If set to @c false, the value is changed (regardless of whether or not the element has content);
    /// if the element is empty, it is serialized in the long format.
    ASPOSECPP_SHARED_API void set_IsEmpty(bool value);
    /// Returns a @c bool value indicating whether the current node has any attributes.
    /// @returns @c true if the current node has attributes; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_HasAttributes();
    /// Returns the post schema validation infoset that has been assigned to this node as a result of schema validation.
    /// @returns An IXmlSchemaInfo object containing the post schema validation infoset of this node.
    ASPOSECPP_SHARED_API SharedPtr<Schema::IXmlSchemaInfo> get_SchemaInfo() override;
    /// Returns the markup representing just the children of this node.
    /// @returns The markup of the children of this node.
    ASPOSECPP_SHARED_API String get_InnerXml() override;
    /// Sets the markup representing just the children of this node.
    /// @param value The value to set.
    /// @throws XmlException The XML specified when setting this value is not well-formed.
    ASPOSECPP_SHARED_API void set_InnerXml(String value) override;
    /// Returns the concatenated values of the node and all its children.
    /// @returns The concatenated values of the node and all its children.
    ASPOSECPP_SHARED_API String get_InnerText() override;
    /// Sets the concatenated values of the node and all its children.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself (and its attributes if the node is an XmlElement).
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Returns the value for the attribute with the specified name.
    /// @param name The name of the attribute to retrieve. This is a qualified name.
    /// It is matched against the @c get_Name value of the matching node.
    /// @returns The value of the specified attribute.
    /// An empty string is returned if a matching attribute is not found or
    /// if the attribute does not have a specified or default value.
    virtual ASPOSECPP_SHARED_API String GetAttribute(String name);
    /// Sets the value of the attribute with the specified name.
    /// @param name The name of the attribute to create or alter. This is a qualified name.
    /// If the name contains a colon it is parsed into prefix and local name components.
    /// @param value The value to set for the attribute.
    /// @throws XmlException The specified name contains an invalid character.
    /// @throws ArgumentException The node is read-only.
    virtual ASPOSECPP_SHARED_API void SetAttribute(String name, String value);
    /// Removes an attribute by name.
    /// @param name The name of the attribute to remove. This is a qualified name.
    /// It is matched against the @c get_Name value of the matching node.
    /// @throws ArgumentException The node is read-only.
    virtual ASPOSECPP_SHARED_API void RemoveAttribute(String name);
    /// Returns the XmlAttribute with the specified name.
    /// @param name The name of the attribute to retrieve. This is a qualified name.
    /// It is matched against the @c get_Name value of the matching node.
    /// @returns The specified XmlAttribute or @c nullptr if a matching attribute was not found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> GetAttributeNode(String name);
    /// Adds the specified XmlAttribute.
    /// @param newAttr The XmlAttribute node to add to the attribute collection for this element.
    /// @returns If the attribute replaces an existing attribute with the same name, the old XmlAttribute is returned;
    /// otherwise, @c nullptr is returned.
    /// @throws ArgumentException The @p newAttr was created from a different document than the one that created this node.
    /// Or this node is read-only.
    /// @throws InvalidOperationException The @p newAttr is already an attribute of another XmlElement object.
    /// You must explicitly clone XmlAttribute nodes to re-use them in other XmlElement objects.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> SetAttributeNode(SharedPtr<XmlAttribute> newAttr);
    /// Removes the specified XmlAttribute.
    /// @param oldAttr The XmlAttribute node to remove. If the removed attribute has a default value, it is immediately replaced.
    /// @returns The removed XmlAttribute or @c nullptr if @p oldAttr is not an attribute node of the XmlElement.
    /// @throws ArgumentException This node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> RemoveAttributeNode(SharedPtr<XmlAttribute> oldAttr);
    /// Returns an XmlNodeList containing a list of all descendant elements that match the specified XmlElement::get_Name.
    /// @param name The name tag to match. This is a qualified name.
    /// It is matched against the @c get_Name value of the matching node.
    /// The asterisk (*) is a special value that matches all tags.
    /// @returns An XmlNodeList containing a list of all matching nodes. The list is empty if there are no matching nodes.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> GetElementsByTagName(String name);
    /// Returns the value for the attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute to retrieve.
    /// @param namespaceURI The namespace URI of the attribute to retrieve.
    /// @returns The value of the specified attribute.
    /// An empty string is returned if a matching attribute is not found or
    /// if the attribute does not have a specified or default value.
    virtual ASPOSECPP_SHARED_API String GetAttribute(String localName, String namespaceURI);
    /// Sets the value of the attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @param value The value to set for the attribute.
    /// @returns The attribute value.
    virtual ASPOSECPP_SHARED_API String SetAttribute(String localName, String namespaceURI, String value);
    /// Removes an attribute with the specified local name and namespace URI.
    /// (If the removed attribute has a default value, it is immediately replaced).
    /// @param localName The local name of the attribute to remove.
    /// @param namespaceURI The namespace URI of the attribute to remove.
    /// @throws ArgumentException The node is read-only.
    virtual ASPOSECPP_SHARED_API void RemoveAttribute(String localName, String namespaceURI);
    /// Returns the XmlAttribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The specified XmlAttribute or @c nullptr if a matching attribute was not found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> GetAttributeNode(String localName, String namespaceURI);
    /// Adds the specified XmlAttribute.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The XmlAttribute to add.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> SetAttributeNode(String localName, String namespaceURI);
    /// Removes the XmlAttribute specified by the local name and namespace URI.
    /// (If the removed attribute has a default value, it is immediately replaced).
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The removed XmlAttribute or @c nullptr if the XmlElement does not have a matching attribute node.
    /// @throws ArgumentException This node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> RemoveAttributeNode(String localName, String namespaceURI);
    /// Returns an XmlNodeList containing a list of all descendant elements that match the specified
    /// XmlElement::get_LocalName and XmlElement::get_NamespaceURI values.
    /// @param localName The local name to match. The asterisk (*) is a special value that matches all tags.
    /// @param namespaceURI The namespace URI to match.
    /// @returns An XmlNodeList containing a list of all matching nodes. The list is empty if there are no matching nodes.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> GetElementsByTagName(String localName, String namespaceURI);
    /// Determines whether the current node has an attribute with the specified name.
    /// @param name The name of the attribute to find. This is a qualified name.
    /// It is matched against the @c get_Name value of the matching node.
    /// @returns @c true if the current node has the specified attribute; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool HasAttribute(String name);
    /// Determines whether the current node has an attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute to find.
    /// @param namespaceURI The namespace URI of the attribute to find.
    /// @returns @c true if the current node has the specified attribute; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool HasAttribute(String localName, String namespaceURI);
    /// Saves the current node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;
    /// Removes the attribute node with the specified index from the element.
    /// (If the removed attribute has a default value, it is immediately replaced).
    /// @param i The index of the node to remove. The first node has index 0.
    /// @returns The attribute node removed or @c nullptr if there is no node at the given index.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveAttributeAt(int32_t i);
    /// Removes all specified attributes from the element. Default attributes are not removed.
    virtual ASPOSECPP_SHARED_API void RemoveAllAttributes();
    /// Removes all specified attributes and children of the current node. Default attributes are not removed.
    ASPOSECPP_SHARED_API void RemoveAll() override;

protected:

    /// @cond
    SharedPtr<System::Xml::XmlName> get_XmlName();
    void set_XmlName(const SharedPtr<System::Xml::XmlName>& value);
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal() override;
    ASPOSECPP_SHARED_API bool get_IsContainer() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode() override;
    ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value) override;
    ASPOSECPP_SHARED_API SharedPtr<XmlAttributeCollection> get_AttributesInternal() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_NextSiblingInternal() override;
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    ASPOSECPP_SHARED_API String get_XPLocalName() override;

    XmlElement(const SharedPtr<System::Xml::XmlName>& name, bool empty, const SharedPtr<XmlDocument>& doc);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlElement, CODEPORTING_ARGS(const SharedPtr<System::Xml::XmlName>& name, bool empty, const SharedPtr<XmlDocument>& doc));
    /// @endcond

    /// Initializes a new instance of the XmlElement class.
    /// @param prefix The namespace prefix; see the XmlElement::get_Prefix method.
    /// @param localName The local name; see the XmlElement::get_LocalName method.
    /// @param namespaceURI The namespace URI; see the XmlElement::get_NamespaceURI method.
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlElement(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<XmlDocument>& doc);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlElement, CODEPORTING_ARGS(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<XmlDocument>& doc));

    /// @cond
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> AppendChildForLoad(const SharedPtr<XmlNode>& newChild, const SharedPtr<XmlDocument>& doc) override;
    ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type) override;
    void RemoveAllChildren();
    ASPOSECPP_SHARED_API void SetParent(SharedPtr<XmlNode> node) override;
    ASPOSECPP_SHARED_API String GetXPAttribute(String localName, String ns) override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlElement();

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
    const char* DBG_class_name() const override { return "XmlElement"; }
    #endif
    /// @endcond

private:

    SharedPtr<System::Xml::XmlName> _name;
    SharedPtr<XmlAttributeCollection> _attributes;
    SharedPtr<XmlLinkedNode> _lastChild;

    static void WriteElementTo(const SharedPtr<XmlWriter>& writer, SharedPtr<XmlElement> e);
    void WriteStartElement(const SharedPtr<XmlWriter>& w);

};

} // namespace Xml
} // namespace System


