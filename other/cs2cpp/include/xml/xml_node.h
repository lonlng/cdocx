/// @file xml/xml_node.h

#pragma once

#include <xml/xpath/ixpath_navigable.h>
#include <xml/xml_node_type.h>
#include <system/collections/ienumerable.h>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
} // namespace Generic
} // namespace Collections
class String;
namespace Text
{
class StringBuilder;
} // namespace Text
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
class XmlCDataSection;
class XmlCharacterData;
class XmlChildEnumerator;
class XmlChildNodes;
class XmlDocument;
class XmlElement;
class XmlElementList;
class XmlEntity;
class XmlEntityReference;
class XmlLinkedNode;
class XmlLoader;
class XmlNamedNodeMap;
class XmlNamespaceManager;
enum class XmlNodeChangedAction;
class XmlNodeChangedEventArgs;
class XmlNodeList;
class XmlNodeReaderNavigator;
class XmlNotation;
class XmlSignificantWhitespace;
enum class XmlSpace;
class XmlText;
class XmlWhitespace;
class XmlWriter;
namespace XPath
{
class XPathNavigator;
enum class XPathNodeType;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a single node in the XML document.
class ASPOSECPP_SHARED_CLASS XmlNode : public Collections::Generic::IEnumerable<SharedPtr<System::Xml::XmlNode>>, public XPath::IXPathNavigable
{
    typedef XmlNode ThisType;
    typedef Collections::Generic::IEnumerable<SharedPtr<System::Xml::XmlNode>> BaseType;
    typedef XPath::IXPathNavigable BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNode>;

private:
    /// @cond
    friend class DocumentSchemaValidator;
    friend class DocumentXmlWriter;
    friend class DocumentXPathNavigator;
    friend class XmlAttribute;
    friend class XmlAttributeCollection;
    friend class XmlNamedNodeMap;
    friend class XmlCDataSection;
    friend class XmlCharacterData;
    friend class XmlLinkedNode;
    friend class XmlChildEnumerator;
    friend class XmlChildNodes;
    friend class XmlNodeList;
    friend class XmlDocument;
    friend class XmlElement;
    friend class XmlElementList;
    friend class XmlEntity;
    friend class XmlEntityReference;
    friend class XmlLoader;
    friend class XmlNodeReaderNavigator;
    friend class XmlNotation;
    friend class XmlSignificantWhitespace;
    friend class XmlText;
    friend class XmlWhitespace;
    friend class Schema::Parser;
    /// @endcond

public:

    /// Returns the qualified name of the node, when overridden in a derived class.
    /// @returns The qualified name of the node.
    ///
    /// The name returned is dependent on the XmlNode::get_NodeType of the node:
    /// <list type="table"><listheader><term> Type
    /// </term><description> Name
    /// </description></listheader><item><term> Attribute
    /// </term><description> The qualified name of the attribute.
    /// </description></item><item><term> CDATA
    /// </term><description> \#cdata-section
    /// </description></item><item><term> Comment
    /// </term><description> \#comment
    /// </description></item><item><term> Document
    /// </term><description> \#document
    /// </description></item><item><term> DocumentFragment
    /// </term><description> \#document-fragment
    /// </description></item><item><term> DocumentType
    /// </term><description> The document type name.
    /// </description></item><item><term> Element
    /// </term><description> The qualified name of the element.
    /// </description></item><item><term> Entity
    /// </term><description> The name of the entity.
    /// </description></item><item><term> EntityReference
    /// </term><description> The name of the entity referenced.
    /// </description></item><item><term> Notation
    /// </term><description> The notation name.
    /// </description></item><item><term> ProcessingInstruction
    /// </term><description> The target of the processing instruction.
    /// </description></item><item><term> Text
    /// </term><description> \#text
    /// </description></item><item><term> Whitespace
    /// </term><description> \#whitespace
    /// </description></item><item><term> SignificantWhitespace
    /// </term><description> \#significant-whitespace
    /// </description></item><item><term> XmlDeclaration
    /// </term><description> \#xml-declaration
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API String get_Name() = 0;
    /// Returns the value of the node.
    /// @returns The value returned depends on the XmlNode::get_NodeType of the node:
    /// <list type="table"><listheader><term> Type
    /// </term><description> Value
    /// </description></listheader><item><term> Attribute
    /// </term><description> The value of the attribute.
    /// </description></item><item><term> CDATASection
    /// </term><description> The content of the CDATA Section.
    /// </description></item><item><term> Comment
    /// </term><description> The content of the comment.
    /// </description></item><item><term> Document
    /// </term><description>@c nullptr.
    /// </description></item><item><term> DocumentFragment
    /// </term><description>@c nullptr.
    /// </description></item><item><term> DocumentType
    /// </term><description>@c nullptr.
    /// </description></item><item><term> Element
    /// </term><description>@c nullptr. You can use the XmlElement::InnerText or XmlElement::get_InnerXml values
    /// to access the value of the element node.
    /// </description></item><item><term> Entity
    /// </term><description>@c nullptr.
    /// </description></item><item><term> EntityReference
    /// </term><description>@c nullptr.
    /// </description></item><item><term> Notation
    /// </term><description>@c nullptr.
    /// </description></item><item><term> ProcessingInstruction
    /// </term><description> The entire content excluding the target.
    /// </description></item><item><term> Text
    /// </term><description> The content of the text node.
    /// </description></item><item><term> SignificantWhitespace
    /// </term><description> The white space characters. White space can consist of one or more space characters,
    /// carriage returns, line feeds, or tabs.
    /// </description></item><item><term> Whitespace
    /// </term><description> The white space characters. White space can consist of one or more space characters,
    /// carriage returns, line feeds, or tabs.
    /// </description></item><item><term> XmlDeclaration
    /// </term><description> The content of the declaration (that is, everything between <tt><?xml and ?></tt>).
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API String get_Value();
    /// Sets the value of the node.
    /// @param value The value to set.
    /// @throws ArgumentException Setting the value of a node that is read-only.
    /// @throws InvalidOperationException Setting the value of a node that is not supposed to have a value (for example, an Element node).
    virtual ASPOSECPP_SHARED_API void set_Value(String value);
    /// Returns the type of the current node, when overridden in a derived class.
    /// @returns One of the XmlNodeType values.
    virtual ASPOSECPP_SHARED_API XmlNodeType get_NodeType() = 0;
    /// Returns the parent of this node (for nodes that can have parents).
    /// @returns The XmlNode that is the parent of the current node.
    ///
    /// If a node has just been created and not yet added to the tree, or if it has been removed from the tree,
    /// the parent is @c nullptr. For all other nodes, the value returned depends on the XmlNode::get_NodeType of the node.
    /// The following table describes the possible return values for the @c get_NodeType method.
    /// <list type="table"><listheader><term> NodeType
    /// </term><description> Return Value of ParentNode
    /// </description></listheader><item><term> Attribute, Document, DocumentFragment, Entity, Notation
    /// </term><description> Returns @c nullptr; these nodes do not have parents.
    /// </description></item><item><term> CDATA
    /// </term><description> Returns the element or entity reference containing the CDATA section.
    /// </description></item><item><term> Comment
    /// </term><description> Returns the element, entity reference, document type, or document containing the comment.
    /// </description></item><item><term> DocumentType
    /// </term><description> Returns the document node.
    /// </description></item><item><term> Element
    /// </term><description> Returns the parent node of the element. If the element is the root node in the tree, the parent is the document node.
    /// </description></item><item><term> EntityReference
    /// </term><description> Returns the element, attribute, or entity reference containing the entity reference.
    /// </description></item><item><term> ProcessingInstruction
    /// </term><description> Returns the document, element, document type, or entity reference containing the processing instruction.
    /// </description></item><item><term> Text
    /// </term><description> Returns the parent element, attribute, or entity reference containing the text node.
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNode() final;
    /// Returns all the child nodes of the node.
    /// @returns An object that contains all the child nodes of the node.
    /// If there are no child nodes, this method returns an empty XmlNodeList.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> get_ChildNodes();
    /// Returns the node immediately preceding this node.
    /// @returns The preceding XmlNode. If there is no preceding node, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_PreviousSibling() final;
    /// Returns the node immediately following this node.
    /// @returns The next XmlNode. If there is no next node, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_NextSibling() final;
    /// Returns an XmlAttributeCollection containing the attributes of this node.
    /// @returns An XmlAttributeCollection containing the attributes of the node.
    /// If the node is of type XmlNodeType::Element, the attributes of the node are returned.
    /// Otherwise, this method returns @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttributeCollection> get_Attributes() final;
    /// Returns the XmlDocument to which this node belongs.
    /// @returns The XmlDocument to which this node belongs.
    /// If the node is an XmlDocument (NodeType equals XmlNodeType::Document), this method returns @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDocument> get_OwnerDocument();
    /// Returns the first child of the node.
    /// @returns The first child of the node. If there is no such node, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_FirstChild() final;
    /// Returns the last child of the node.
    /// @returns The last child of the node. If there is no such node, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_LastChild() final;
    /// Returns a value indicating whether this node has any child nodes.
    /// @returns @c true if the node has child nodes; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_HasChildNodes();
    /// Returns the namespace URI of this node.
    /// @returns The namespace URI of this node. If there is no namespace URI, this method returns String::Empty.
    virtual ASPOSECPP_SHARED_API String get_NamespaceURI();
    /// Returns the namespace prefix of this node.
    /// @returns The namespace prefix of this node. For example, @c Prefix is @c bk for the element <tt><bk:book></tt>.
    /// If there is no prefix, this method returns String::Empty.
    virtual ASPOSECPP_SHARED_API String get_Prefix();
    /// Sets the namespace prefix of this node.
    /// @param value The value to set.
    /// @throws ArgumentException This node is read-only.
    /// @throws XmlException The specified prefix contains an invalid character.
    /// The specified prefix is malformed.
    /// The specified prefix is "xml" and the namespaceURI of this node is different from "http://www.w3.org/XML/1998/namespace".
    /// This node is an attribute and the specified prefix is "xmlns" and the namespaceURI of this node is different from "http://www.w3.org/2000/xmlns/ ".
    /// This node is an attribute and the qualifiedName of this node is "xmlns".
    virtual ASPOSECPP_SHARED_API void set_Prefix(String value);
    /// Returns the local name of the node, when overridden in a derived class.
    /// @returns The name of the node with the prefix removed.
    /// For example, @c LocalName is @c book for the element <tt><bk:book></tt>.
    ///
    /// The name returned is dependent on the XmlNode::get_NodeType of the node:
    /// <list type="table"><listheader><term> Type
    /// </term><description> Name
    /// </description></listheader><item><term> Attribute
    /// </term><description> The local name of the attribute.
    /// </description></item><item><term> CDATA
    /// </term><description> \#cdata-section
    /// </description></item><item><term> Comment
    /// </term><description> \#comment
    /// </description></item><item><term> Document
    /// </term><description> \#document
    /// </description></item><item><term> DocumentFragment
    /// </term><description> \#document-fragment
    /// </description></item><item><term> DocumentType
    /// </term><description> The document type name.
    /// </description></item><item><term> Element
    /// </term><description> The local name of the element.
    /// </description></item><item><term> Entity
    /// </term><description> The name of the entity.
    /// </description></item><item><term> EntityReference
    /// </term><description> The name of the entity referenced.
    /// </description></item><item><term> Notation
    /// </term><description> The notation name.
    /// </description></item><item><term> ProcessingInstruction
    /// </term><description> The target of the processing instruction.
    /// </description></item><item><term> Text
    /// </term><description> \#text
    /// </description></item><item><term> Whitespace
    /// </term><description> \#whitespace
    /// </description></item><item><term> SignificantWhitespace
    /// </term><description> \#significant-whitespace
    /// </description></item><item><term> XmlDeclaration
    /// </term><description> \#xml-declaration
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API String get_LocalName() = 0;
    /// Returns a value indicating whether the node is read-only.
    /// @returns @c true if the node is read-only; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_IsReadOnly();
    /// Returns the concatenated values of the node and all its child nodes.
    /// @returns The concatenated values of the node and all its child nodes.
    virtual ASPOSECPP_SHARED_API String get_InnerText();
    /// Sets the concatenated values of the node and all its child nodes.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_InnerText(String value);
    /// Returns the markup containing this node and all its child nodes.
    /// @returns The markup containing this node and all its child nodes, not including default attributes.
    virtual ASPOSECPP_SHARED_API String get_OuterXml();
    /// Returns the markup representing only the child nodes of this node.
    /// @returns The markup of the child nodes of this node, not including default attributes.
    /// @throws InvalidOperationException Setting this value on a node that cannot have child nodes.
    /// @throws XmlException The XML specified when setting this value is not well-formed.
    virtual ASPOSECPP_SHARED_API String get_InnerXml();
    /// Sets the markup representing only the child nodes of this node.
    /// @param value The value to set.
    /// @throws InvalidOperationException Setting this value on a node that cannot have child nodes.
    /// @throws XmlException The XML specified when setting this value is not well-formed.
    virtual ASPOSECPP_SHARED_API void set_InnerXml(String value);
    /// Returns the post schema validation infoset that has been assigned to this node as a result of schema validation.
    /// @returns An IXmlSchemaInfo object containing the post schema validation infoset of this node.
    virtual ASPOSECPP_SHARED_API SharedPtr<Schema::IXmlSchemaInfo> get_SchemaInfo();
    /// Returns the base URI of the current node.
    /// @returns The location from which the node was loaded or String::Empty if the node has no base URI.
    virtual ASPOSECPP_SHARED_API String get_BaseURI();
    /// Returns the text node that immediately precedes this node.
    /// @returns Returns XmlNode.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_PreviousText();

    /// Creates an XPathNavigator for navigating this object.
    /// @returns An XPathNavigator object used to navigate the node.
    /// The XPathNavigator is positioned on the node from which the method was called.
    /// It is not positioned on the root of the document.
    ASPOSECPP_SHARED_API SharedPtr<XPath::XPathNavigator> CreateNavigator() override;
    /// Selects the first XmlNode that matches the XPath expression.
    /// @param xpath The XPath expression.
    /// @returns The first XmlNode that matches the XPath query or @c nullptr if no matching node is found.
    /// @throws XPathException The XPath expression contains a prefix.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> SelectSingleNode(const String& xpath);
    /// Selects the first XmlNode that matches the XPath expression.
    /// Any prefixes found in the XPath expression are resolved using the supplied XmlNamespaceManager.
    /// @param xpath The XPath expression.
    /// @param nsmgr An XmlNamespaceManager to use for resolving namespaces for prefixes in the XPath expression.
    /// @returns The first XmlNode that matches the XPath query or @c nullptr if no matching node is found.
    /// @throws XPathException The XPath expression contains a prefix which is not defined in the XmlNamespaceManager.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> SelectSingleNode(const String& xpath, const SharedPtr<XmlNamespaceManager>& nsmgr);
    /// Selects a list of nodes matching the XPath expression.
    /// @param xpath The XPath expression.
    /// @returns An XmlNodeList containing a collection of nodes matching the XPath query.
    /// @throws XPathException The XPath expression contains a prefix.
    ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> SelectNodes(const String& xpath);
    /// Selects a list of nodes matching the XPath expression.
    /// Any prefixes found in the XPath expression are resolved using the supplied XmlNamespaceManager.
    /// @param xpath The XPath expression.
    /// @param nsmgr An XmlNamespaceManager to use for resolving namespaces for prefixes in the XPath expression.
    /// @returns An XmlNodeList containing a collection of nodes matching the XPath query.
    /// @throws XPathException The XPath expression contains a prefix which is not defined in the XmlNamespaceManager.
    ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> SelectNodes(const String& xpath, const SharedPtr<XmlNamespaceManager>& nsmgr);
    /// Inserts the specified node immediately before the specified reference node.
    /// @param newChild The node to insert.
    /// @param refChild The reference node. @p newChild is placed before this node.
    /// @returns The node being inserted.
    /// @throws InvalidOperationException The current node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// The @p refChild is not a child of this node.
    /// This node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> InsertBefore(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild);
    /// Inserts the specified node immediately after the specified reference node.
    /// @param newChild The node to insert.
    /// @param refChild The reference node. @p newChild is placed after @p refChild.
    /// @returns The node being inserted.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// The @p refChild is not a child of this node.
    /// This node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> InsertAfter(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild);
    /// Replaces the child node @p oldChild with @p newChild node.
    /// @param newChild The new node to put in the child list.
    /// @param oldChild The node being replaced in the list.
    /// @returns The node replaced.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// This node is read-only.
    /// The @p oldChild is not a child of this node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> ReplaceChild(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> oldChild);
    /// Removes specified child node.
    /// @param oldChild The node being removed.
    /// @returns The node removed.
    /// @throws ArgumentException The @p oldChild is not a child of this node. Or this node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveChild(SharedPtr<XmlNode> oldChild);
    /// Adds the specified node to the beginning of the list of child nodes for this node.
    /// @param newChild The node to add. All the contents of the node to be added are moved into the specified location.
    /// @returns The node added.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// This node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> PrependChild(SharedPtr<XmlNode> newChild);
    /// Adds the specified node to the end of the list of child nodes, of this node.
    /// @param newChild The node to add. All the contents of the node to be added are moved into the specified location.
    /// @returns The node added.
    /// @throws InvalidOperationException This node is of a type that does not allow child nodes of the type of the @p newChild node.
    /// The @p newChild is an ancestor of this node.
    /// @throws ArgumentException The @p newChild was created from a different document than the one that created this node.
    /// This node is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> AppendChild(SharedPtr<XmlNode> newChild);
    /// Creates a duplicate of the node, when overridden in a derived class.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// @returns The cloned node.
    /// @throws InvalidOperationException Calling this method on a node type that cannot be cloned.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) = 0;
    /// Puts all XmlText nodes in the full depth of the sub-tree underneath this XmlNode into a "normal" form
    /// where only markup (that is, tags, comments, processing instructions, CDATA sections, and entity references)
    /// separates XmlText nodes, that is, there are no adjacent XmlText nodes.
    virtual ASPOSECPP_SHARED_API void Normalize();
    /// Tests if the DOM implementation implements a specific feature.
    /// @param feature The package name of the feature to test. This name is not case-sensitive.
    /// @param version The version number of the package name to test.
    /// If the version is not specified (null), supporting any version of the feature causes the method to return true.
    /// @returns @c true if the feature is implemented in the specified version; otherwise, @c false.
    ///
    /// The following table describes the combinations that return @c true.
    /// <list type="table"><listheader><term> Feature
    /// </term><description> Version
    /// </description></listheader><item><term> XML
    /// </term><description> 1.0
    /// </description></item><item><term> XML
    /// </term><description> 2.0
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API bool Supports(String feature, String version);
    /// Creates a duplicate of this node.
    /// @returns The cloned node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> Clone();
    /// Returns an enumerator that iterates through the child nodes in the current node.
    /// @returns An Collections::IEnumerator object that can be used to iterate through the child nodes in the current node.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlNode>>> GetEnumerator() override;
    /// Saves the current node to the specified XmlWriter, when overridden in a derived class.
    /// @param w The XmlWriter to which you want to save.
    virtual ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) = 0;
    /// Saves all the child nodes of the node to the specified XmlWriter, when overridden in a derived class.
    /// @param w The XmlWriter to which you want to save.
    virtual ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) = 0;
    /// Removes all the child nodes and/or attributes of the current node.
    virtual ASPOSECPP_SHARED_API void RemoveAll();
    /// Looks up the closest **xmlns** declaration for the given prefix that is in scope for the current node and
    /// returns the namespace URI in the declaration.
    /// @param prefix The prefix whose namespace URI you want to find.
    /// @returns The namespace URI of the specified prefix.
    virtual ASPOSECPP_SHARED_API String GetNamespaceOfPrefix(String prefix);
    /// Looks up the closest **xmlns** declaration for the given namespace URI that is in scope for the current node and
    /// returns the prefix defined in that declaration.
    /// @param namespaceURI The namespace URI whose prefix you want to find.
    /// @returns The prefix for the specified namespace URI.
    virtual ASPOSECPP_SHARED_API String GetPrefixOfNamespace(String namespaceURI);

    /// Returns the first child element with the specified XmlNode::get_Name.
    /// @param name The qualified name of the element to retrieve.
    /// @returns The first XmlElement that matches the specified name.
    /// It returns @c nullptr if there is no match.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlElement> idx_get(String name);
    /// Returns the first child element with the specified XmlNode::get_LocalName and XmlNode::get_NamespaceURI values.
    /// @param localname The local name of the element.
    /// @param ns The namespace URI of the element.
    /// @returns The first XmlElement with the matching @p localname and @p ns.
    /// It returns @c nullptr if there is no match.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlElement> idx_get(String localname, String ns);

protected:

    /// @cond
    WeakPtr<XmlNode> parentNode;

    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_PreviousSiblingInternal();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_NextSiblingInternal();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttributeCollection> get_AttributesInternal();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_FirstChildInternal();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_LastChildInternal();
    virtual ASPOSECPP_SHARED_API bool get_IsContainer();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode();
    virtual ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value);
    SharedPtr<XmlDocument> get_Document();
    virtual ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace();
    virtual ASPOSECPP_SHARED_API String get_XmlLang();
    virtual ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType();
    virtual ASPOSECPP_SHARED_API String get_XPLocalName();
    virtual ASPOSECPP_SHARED_API bool get_IsText();

    XmlNode();
    XmlNode(const SharedPtr<XmlDocument>& doc);

    bool AncestorNode(const SharedPtr<XmlNode>& node);
    bool IsConnected();
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> AppendChildForLoad(const SharedPtr<XmlNode>& newChild, const SharedPtr<XmlDocument>& doc);
    virtual ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type);
    virtual ASPOSECPP_SHARED_API bool CanInsertBefore(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild);
    virtual ASPOSECPP_SHARED_API bool CanInsertAfter(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild);
    virtual ASPOSECPP_SHARED_API void CopyChildren(SharedPtr<XmlDocument> doc, SharedPtr<XmlNode> container, bool deep);
    static bool HasReadOnlyParent(SharedPtr<XmlNode> n);
    String GetNamespaceOfPrefixStrict(String prefix);
    String GetPrefixOfNamespaceStrict(String namespaceURI);
    virtual ASPOSECPP_SHARED_API void SetParent(SharedPtr<XmlNode> node);
    virtual ASPOSECPP_SHARED_API void SetParentForLoad(SharedPtr<XmlNode> node);
    static void SplitName(const String& name, String& prefix, String& localName);
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> FindChild(XmlNodeType type);
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNodeChangedEventArgs> GetEventArgs(SharedPtr<XmlNode> node, SharedPtr<XmlNode> oldParent, SharedPtr<XmlNode> newParent, String oldValue, String newValue, XmlNodeChangedAction action);
    virtual ASPOSECPP_SHARED_API void BeforeEvent(SharedPtr<XmlNodeChangedEventArgs> args);
    virtual ASPOSECPP_SHARED_API void AfterEvent(SharedPtr<XmlNodeChangedEventArgs> args);
    virtual ASPOSECPP_SHARED_API String GetXPAttribute(String localName, String namespaceURI);
    static void NestTextNodes(const SharedPtr<XmlNode>& prevNode, const SharedPtr<XmlNode>& nextNode);
    static void UnnestTextNodes(const SharedPtr<XmlNode>& prevNode, const SharedPtr<XmlNode>& nextNode);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlNode();

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
    const char* DBG_class_name() const override { return "XmlNode"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlNode> NormalizeWinner(const SharedPtr<XmlNode>& firstNode, const SharedPtr<XmlNode>& secondNode);
    void AppendChildText(const SharedPtr<Text::StringBuilder>& builder);

};

} // namespace Xml
} // namespace System


