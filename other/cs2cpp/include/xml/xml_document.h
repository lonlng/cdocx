/// @file xml/xml_document.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_node_changed_event_handler.h>
#include <xml/xml_node.h>
#include <xml/schema/validation_event_handler.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace IO
{
class Stream;
class TextReader;
class TextWriter;
} // namespace IO
namespace Text
{
class Encoding;
} // namespace Text
template <typename... Args> class WeakReference;
namespace Xml
{
class DocumentSchemaValidator;
class DocumentXmlWriter;
class DocumentXPathNavigator;
class DomNameTable;
class EmptyEnumerator;
namespace Schema
{
class IXmlSchemaInfo;
class SchemaAttDef;
class SchemaElementDecl;
class SchemaInfo;
class XmlSchemaSet;
} // namespace Schema
class XmlAttribute;
class XmlAttributeCollection;
class XmlCDataSection;
class XmlCharacterData;
class XmlChildNodes;
class XmlComment;
class XmlDeclaration;
class XmlDocumentFragment;
class XmlDocumentType;
class XmlElement;
class XmlEntity;
class XmlEntityReference;
class XmlImplementation;
class XmlLinkedNode;
class XmlLoader;
class XmlName;
class XmlNamedNodeMap;
class XmlNameEx;
class XmlNameTable;
enum class XmlNodeChangedAction;
class XmlNodeChangedEventArgs;
class XmlNodeList;
class XmlNodeReader;
class XmlNodeReaderNavigator;
class XmlProcessingInstruction;
class XmlReader;
class XmlResolver;
class XmlSignificantWhitespace;
class XmlText;
class XmlTextReader;
class XmlUnspecifiedAttribute;
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

/// Represents an XML document. You can use this class to load, validate, edit, add, and position XML in a document.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDocument : public XmlNode
{
    typedef XmlDocument ThisType;
    typedef XmlNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlDocument>;

private:
    /// @cond
    friend class DocumentSchemaValidator;
    friend class DocumentXmlWriter;
    friend class DocumentXPathNavigator;
    friend class XmlAttribute;
    friend class XmlNode;
    friend class XmlAttributeCollection;
    friend class XmlNamedNodeMap;
    friend class XmlCDataSection;
    friend class XmlCharacterData;
    friend class XmlChildNodes;
    friend class XmlComment;
    friend class XmlDocumentFragment;
    friend class XmlDocumentType;
    friend class XmlElement;
    friend class XmlEntityReference;
    friend class XmlImplementation;
    friend class XmlLoader;
    friend class XmlNameEx;
    friend class XmlNamedNodeMap;
    friend class XmlNodeReader;
    friend class XmlNodeReaderNavigator;
    friend class XmlSignificantWhitespace;
    friend class XmlText;
    friend class XmlUnspecifiedAttribute;
    friend class XmlWhitespace;
    /// @endcond

public:

    /// Occurs when a node belonging to this document is about to be inserted into another node.
    XmlNodeChangedEventHandler NodeInserting;
    /// Occurs when a node belonging to this document has been inserted into another node.
    XmlNodeChangedEventHandler NodeInserted;
    /// Occurs when a node belonging to this document is about to be removed from the document.
    XmlNodeChangedEventHandler NodeRemoving;
    /// Occurs when a node belonging to this document has been removed from its parent.
    XmlNodeChangedEventHandler NodeRemoved;
    /// Occurs when the XmlNode::get_Value of a node belonging to this document is about to be changed.
    XmlNodeChangedEventHandler NodeChanging;
    /// Occurs when the XmlNode::get_Value of a node belonging to this document has been changed.
    XmlNodeChangedEventHandler NodeChanged;

    /// Returns the type of the current node.
    /// @returns The node type. For XmlDocument nodes, this value is XmlNodeType::Document.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the node containing the DOCTYPE declaration.
    /// @returns The XmlNode containing the DocumentType (DOCTYPE declaration).
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDocumentType> get_DocumentType();
    /// Returns the XmlImplementation object for the current document.
    /// @returns The XmlImplementation object for the current document.
    ASPOSECPP_SHARED_API SharedPtr<XmlImplementation> get_Implementation();
    /// Returns the qualified name of the node.
    /// @returns For XmlDocument nodes, the name is \#document.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For XmlDocument nodes, the local name is \#document.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the root XmlElement for the document.
    /// @returns The XmlElement that represents the root of the XML document tree. If no root exists, @c nullptr is returned.
    ASPOSECPP_SHARED_API SharedPtr<XmlElement> get_DocumentElement();
    /// Returns the XmlDocument to which the current node belongs.
    /// @returns For XmlDocument nodes (XmlDocument::get_NodeType equals XmlNodeType::Document), this method always returns @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlDocument> get_OwnerDocument() override;
    /// Returns the XmlSchemaSet object associated with this XmlDocument.
    /// @returns An XmlSchemaSet object containing the XML Schema Definition Language (XSD) schemas associated with this XmlDocument;
    /// otherwise, an empty XmlSchemaSet object.
    ASPOSECPP_SHARED_API SharedPtr<Schema::XmlSchemaSet> get_Schemas();
    /// Sets the XmlSchemaSet object associated with this XmlDocument.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Schemas(const SharedPtr<Schema::XmlSchemaSet>& value);
    /// Sets the XmlResolver to use for resolving external resources.
    /// @param value The value to set.
    /// @throws XmlException This value is set to @c nullptr and an external DTD or entity is encountered.
    virtual ASPOSECPP_SHARED_API void set_XmlResolver(SharedPtr<System::Xml::XmlResolver> value);
    /// Returns the XmlNameTable associated with this implementation.
    /// @returns An XmlNameTable enabling you to get the atomized version of a string within the document.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable();
    /// Returns a value indicating whether to preserve white space in element content.
    /// @returns @c true to preserve white space; otherwise @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_PreserveWhitespace();
    /// Sets a value indicating whether to preserve white space in element content.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_PreserveWhitespace(bool value);
    /// Returns a value indicating whether the current node is read-only.
    /// @returns @c true if the current node is read-only; otherwise @c false. XmlDocument nodes always return @c false.
    ASPOSECPP_SHARED_API bool get_IsReadOnly() override;
    /// Throws an InvalidOperationException in all cases.
    /// @param value The value to set.
    /// @throws InvalidOperationException In all cases.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;
    /// Returns the markup representing the children of the current node.
    /// @returns The markup of the children of the current node.
    ASPOSECPP_SHARED_API String get_InnerXml() override;
    /// Sets the markup representing the children of the current node.
    /// @param value The value to set.
    /// @throws XmlException The XML specified when setting this value is not well-formed.
    ASPOSECPP_SHARED_API void set_InnerXml(String value) override;
    /// Returns the Post-Schema-Validation-Infoset (PSVI) of the node.
    /// @returns The IXmlSchemaInfo object representing the PSVI of the node.
    ASPOSECPP_SHARED_API SharedPtr<Schema::IXmlSchemaInfo> get_SchemaInfo() override;
    /// Returns the base URI of the current node.
    /// @returns The location from which the node was loaded.
    ASPOSECPP_SHARED_API String get_BaseURI() override;

    /// Initializes a new instance of the XmlDocument class.
    ASPOSECPP_SHARED_API XmlDocument();
    /// Initializes a new instance of the XmlDocument class with the specified XmlNameTable.
    /// @param nt The XmlNameTable to use.
    ASPOSECPP_SHARED_API XmlDocument(const SharedPtr<XmlNameTable>& nt);

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node; @c false to clone only the node itself.
    /// @returns The cloned XmlDocument node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Creates an XmlAttribute with the specified name.
    /// @param name The qualified name of the attribute. If the name contains a colon,
    /// the XmlNode::get_Prefix value reflects the part of the name preceding the first colon and
    /// the XmlDocument::get_LocalName value reflects the part of the name following the first colon.
    /// The XmlNode::get_NamespaceURI remains empty unless the prefix is a recognized built-in prefix such as @c xmlns.
    /// In this case get_NamespaceURI has a value of http://www.w3.org/2000/xmlns/.
    /// @returns The new XmlAttribute.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> CreateAttribute(const String& name);
    /// Creates an XmlCDataSection containing the specified data.
    /// @param data The content of the new XmlCDataSection.
    /// @returns The new XmlCDataSection.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlCDataSection> CreateCDataSection(const String& data);
    /// Creates an XmlComment containing the specified data.
    /// @param data The content of the new XmlComment.
    /// @returns The new XmlComment.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlComment> CreateComment(const String& data);
    /// Returns a new XmlDocumentType object.
    /// @param name Name of the document type.
    /// @param publicId The public identifier of the document type or @c nullptr.
    /// You can specify a public URI and also a system identifier to identify the location of the external DTD subset.
    /// @param systemId The system identifier of the document type or @c nullptr. Specifies the URL of the file location for the external DTD subset.
    /// @param internalSubset The DTD internal subset of the document type or @c nullptr.
    /// @returns The new XmlDocumentType.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDocumentType> CreateDocumentType(const String& name, const String& publicId, const String& systemId, const String& internalSubset);
    /// Creates an XmlDocumentFragment.
    /// @returns The new XmlDocumentFragment.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDocumentFragment> CreateDocumentFragment();
    /// Creates an element with the specified name.
    /// @param name The qualified name of the element. If the name contains a colon then
    /// the XmlNode::get_Prefix value reflects the part of the name preceding the colon and
    /// the XmlDocument::get_LocalName value reflects the part of the name after the colon.
    /// The qualified name cannot include a prefix of @c xmlns.
    /// @returns The new XmlElement.
    ASPOSECPP_SHARED_API SharedPtr<XmlElement> CreateElement(const String& name);
    /// Creates an XmlEntityReference with the specified name.
    /// @param name The name of the entity reference.
    /// @returns The new XmlEntityReference.
    /// @throws ArgumentException The name is invalid (for example, names starting with '#' are invalid.)
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlEntityReference> CreateEntityReference(const String& name);
    /// Creates an XmlProcessingInstruction with the specified name and data.
    /// @param target The name of the processing instruction.
    /// @param data The data for the processing instruction.
    /// @returns The new XmlProcessingInstruction.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlProcessingInstruction> CreateProcessingInstruction(const String& target, const String& data);
    /// Creates an XmlDeclaration node with the specified values.
    /// @param version The version must be "1.0".
    /// @param encoding The value of the encoding attribute.
    /// This is the encoding that is used when you save the XmlDocument to a file or a stream; therefore,
    /// it must be set to a string supported by the Text::Encoding class, otherwise "XmlDocument::Save(String)" fails.
    /// If this is @c nullptr or String::Empty, the XmlDocument::Save method does not write an encoding attribute on
    /// the XML declaration and therefore the default encoding, UTF-8, is used.
    ///
    /// Note: If the XmlDocument is saved to either a TextWriter or an XmlTextWriter, this encoding value is discarded.
    /// Instead, the encoding of the TextWriter or the XmlTextWriter is used.
    /// This ensures that the XML written out can be read back using the correct encoding.
    /// @param standalone The value must be either "yes" or "no". If this is @c nullptr or String::Empty,
    /// the XmlDocument::Save method does not write a standalone attribute on the XML declaration.
    /// @returns The new XmlDeclaration node.
    /// @throws ArgumentException The values of @p version or @p standalone are something other than the ones specified above.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDeclaration> CreateXmlDeclaration(const String& version, const String& encoding, const String& standalone);
    /// Creates an XmlText with the specified text.
    /// @param text The text for the Text node.
    /// @returns The new XmlText node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlText> CreateTextNode(const String& text);
    /// Creates an XmlSignificantWhitespace node.
    /// @param text The string must contain only the following characters @c '\\x20', @c '\\x0d', @c '\\x0a', @c '\\x09'.
    /// @returns A new XmlSignificantWhitespace node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlSignificantWhitespace> CreateSignificantWhitespace(const String& text);
    /// Creates a new XPathNavigator object for navigating this document.
    /// @returns An XPathNavigator object.
    ASPOSECPP_SHARED_API SharedPtr<XPath::XPathNavigator> CreateNavigator() override;
    /// Creates an XmlWhitespace node.
    /// @param text The string must contain only the following characters @c '\\x20', @c '\\x0d', @c '\\x0a', @c '\\x09'.
    /// @returns A new XmlWhitespace node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWhitespace> CreateWhitespace(const String& text);
    /// Returns an XmlNodeList containing a list of all descendant elements that match the specified name.
    /// @param name The qualified name to match. It is matched against the @c get_Name value of the matching node.
    /// The special value @c "*" matches all tags.
    /// @returns An XmlNodeList containing a list of all matching nodes.
    /// If no nodes match @p name, the returned collection will be empty.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> GetElementsByTagName(String name);
    /// Creates an XmlAttribute with the specified qualified name and XmlNode::get_NamespaceURI.
    /// @param qualifiedName The qualified name of the attribute. If the name contains a colon then
    /// the XmlNode::get_Prefix value will reflect the part of the name preceding the colon and
    /// the XmlDocument::get_LocalName value will reflect the part of the name after the colon.
    /// @param namespaceURI The namespaceURI of the attribute. If the qualified name includes a prefix of @c xmlns,
    /// then this parameter must be http://www.w3.org/2000/xmlns/.
    /// @returns The new XmlAttribute.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> CreateAttribute(const String& qualifiedName, const String& namespaceURI);
    /// Creates an XmlElement with the qualified name and XmlNode::get_NamespaceURI.
    /// @param qualifiedName The qualified name of the element. If the name contains a colon then
    /// the XmlNode::get_Prefix value will reflect the part of the name preceding the colon and
    /// the XmlDocument::get_LocalName value will reflect the part of the name after the colon.
    /// The qualified name cannot include a prefix of @c xmlns.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The new XmlElement.
    ASPOSECPP_SHARED_API SharedPtr<XmlElement> CreateElement(const String& qualifiedName, const String& namespaceURI);
    /// Returns an XmlNodeList containing a list of all descendant elements that match
    /// the specified XmlDocument::get_LocalName and XmlNode::get_NamespaceURI.
    /// @param localName The LocalName to match. The special value @c "*" matches all tags.
    /// @param namespaceURI NamespaceURI to match.
    /// @returns An XmlNodeList containing a list of all matching nodes.
    /// If no nodes match the specified @p localName and @p namespaceURI, the returned collection will be empty.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNodeList> GetElementsByTagName(String localName, String namespaceURI);
    /// Returns the XmlElement with the specified ID.
    /// @param elementId The attribute ID to match.
    /// @returns The XmlElement with the matching ID or @c nullptr if no matching element is found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlElement> GetElementById(String elementId);
    /// Imports a node from another document to the current document.
    /// @param node The node being imported.
    /// @param deep @c true to perform a deep clone; otherwise, @c false.
    /// @returns The imported XmlNode.
    /// @throws InvalidOperationException Calling this method on a node type which cannot be imported.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> ImportNode(SharedPtr<XmlNode> node, bool deep);
    /// Creates an XmlAttribute with the specified XmlNode::get_Prefix, XmlDocument::get_LocalName, and XmlNode::get_NamespaceURI.
    /// @param prefix The prefix of the attribute (if any). String::Empty and @c nullptr are equivalent.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute (if any). String::Empty and @c nullptr are equivalent.
    /// If @p prefix is @c xmlns, then this parameter must be http://www.w3.org/2000/xmlns/; otherwise an exception is thrown.
    /// @returns The new XmlAttribute.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> CreateAttribute(const String& prefix, const String& localName, const String& namespaceURI);
    /// Creates an element with the specified XmlNode::get_Prefix, XmlDocument::get_LocalName, and XmlNode::get_NamespaceURI.
    /// @param prefix The prefix of the new element (if any). String::Empty and @c nullptr are equivalent.
    /// @param localName The local name of the new element.
    /// @param namespaceURI The namespace URI of the new element (if any). String::Empty and @c nullptr are equivalent.
    /// @returns The new XmlElement.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlElement> CreateElement(const String& prefix, const String& localName, const String& namespaceURI);
    /// Creates a XmlNode with the specified XmlNodeType, XmlNode::get_Prefix, XmlDocument::get_Name, and XmlNode::get_NamespaceURI.
    /// @param type The XmlNodeType of the new node.
    /// @param prefix The prefix of the new node.
    /// @param name The local name of the new node.
    /// @param namespaceURI The namespace URI of the new node.
    /// @returns The new XmlNode.
    /// @throws ArgumentException The name was not provided and the XmlNodeType requires a name.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> CreateNode(XmlNodeType type, const String& prefix, const String& name, const String& namespaceURI);
    /// Creates an XmlNode with the specified node type, XmlDocument::get_Name, and XmlNode::get_NamespaceURI.
    /// @param nodeTypeString String version of the XmlNodeType of the new node.
    /// This parameter must be one of the values listed in the table below.
    /// @param name The qualified name of the new node. If the name contains a colon,
    /// it is parsed into XmlNode::get_Prefix and XmlDocument::get_LocalName components.
    /// @param namespaceURI The namespace URI of the new node.
    /// @returns The new XmlNode.
    /// @throws ArgumentException The name was not provided and the XmlNodeType requires a name;
    /// or @p nodeTypeString is not one of the strings listed below.
    ///
    /// The @p nodeTypeString parameter is case sensitive and must be one of the values in the following table:
    /// <list type="table"><listheader><term>nodeTypeString</term><description>XmlNodeType
    /// </description></listheader><item><term>attribute</term><description>Attribute
    /// </description></listheader><item><term>cdatasection</term><description>CDATA
    /// </description></listheader><item><term>comment</term><description>Comment
    /// </description></listheader><item><term>document</term><description>Document
    /// </description></listheader><item><term>documentfragment</term><description>DocumentFragment
    /// </description></listheader><item><term>documenttype</term><description>DocumentType
    /// </description></listheader><item><term>element</term><description>Element
    /// </description></listheader><item><term>entityreference</term><description>EntityReference
    /// </description></listheader><item><term>processinginstruction</term><description>ProcessingInstruction
    /// </description></listheader><item><term>significantwhitespace</term><description>SignificantWhitespace
    /// </description></listheader><item><term>text</term><description>Text
    /// </description></listheader><item><term>whitespace</term><description>Whitespace
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> CreateNode(const String& nodeTypeString, const String& name, const String& namespaceURI);
    /// Creates an XmlNode with the specified XmlNodeType, XmlDocument::get_Name, and XmlNode::get_NamespaceURI.
    /// @param type The XmlNodeType of the new node.
    /// @param name The qualified name of the new node. If the name contains a colon then it is parsed into
    /// XmlNode::get_Prefix and XmlDocument::get_LocalName components.
    /// @param namespaceURI The namespace URI of the new node.
    /// @returns The new XmlNode.
    /// @throws ArgumentException The name was not provided and the XmlNodeType requires a name.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> CreateNode(XmlNodeType type, const String& name, const String& namespaceURI);
    /// Creates an XmlNode object based on the information in the XmlReader. The reader must be positioned on a node or attribute.
    /// @param reader The XML source.
    /// @returns The new XmlNode or @c nullptr if no more nodes exist.
    /// @throws NullReferenceException The reader is positioned on a node type that does not translate to
    /// a valid DOM node (for example, EndElement or EndEntity).
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> ReadNode(SharedPtr<XmlReader> reader);
    /// Loads the XML document from the specified URL.
    /// @param filename URL for the file containing the XML document to load.
    /// The URL can be either a local file or an HTTP URL (a Web address).
    /// @throws XmlException There is a load or parse error in the XML. In this case, a FileNotFoundException is raised.
    /// @throws ArgumentException @p filename is a zero-length string, contains only white space,
    /// or contains one or more invalid characters as defined by System::IO::Path::GetInvalidPathChars.
    /// @throws ArgumentNullException @p filename is @c nullptr.
    /// @throws PathTooLongException The specified path, file name, or both exceed the system-defined maximum length.
    /// @throws DirectoryNotFoundException The specified path is invalid (for example, it is on an unmapped drive).
    /// @throws IOException An I/O error occurred while opening the file.
    /// @throws UnauthorizedAccessException @p filename specified a file that is read-only.
    /// This operation is not supported on the current platform.
    /// @p filename specified a directory.
    /// The caller does not have the required permission.
    /// @throws FileNotFoundException The file specified in @p filename was not found.
    /// @throws NotSupportedException @p filename is in an invalid format.
    /// @throws SecurityException The caller does not have the required permission.
    virtual ASPOSECPP_SHARED_API void Load(String filename);
    /// Loads the XML document from the specified stream.
    /// @param inStream The stream containing the XML document to load.
    /// @throws XmlException There is a load or parse error in the XML. In this case, a FileNotFoundException is raised.
    virtual ASPOSECPP_SHARED_API void Load(SharedPtr<IO::Stream> inStream);
    /// Loads the XML document from the specified TextReader.
    /// @param txtReader The TextReader used to feed the XML data into the document.
    /// @throws XmlException There is a load or parse error in the XML. In this case, the document remains empty.
    virtual ASPOSECPP_SHARED_API void Load(SharedPtr<IO::TextReader> txtReader);
    /// Loads the XML document from the specified XmlReader.
    /// @param reader The XmlReader used to feed the XML data into the document.
    /// @throws XmlException There is a load or parse error in the XML. In this case, the document remains empty.
    virtual ASPOSECPP_SHARED_API void Load(SharedPtr<XmlReader> reader);
    /// Loads the XML document from the specified string.
    /// @param xml String containing the XML document to load.
    /// @throws XmlException There is a load or parse error in the XML. In this case, the document remains empty.
    virtual ASPOSECPP_SHARED_API void LoadXml(String xml);
    /// Saves the XML document to the specified file. If the specified file exists, this method overwrites it.
    /// @param filename The location of the file where you want to save the document.
    /// @throws XmlException The operation would not result in a well formed XML document
    /// (for example, no document element or duplicate XML declarations).
    virtual ASPOSECPP_SHARED_API void Save(String filename);
    /// Saves the XML document to the specified stream.
    /// @param outStream The stream to which you want to save.
    /// @throws XmlException The operation would not result in a well formed XML document
    /// (for example, no document element or duplicate XML declarations).
    virtual ASPOSECPP_SHARED_API void Save(SharedPtr<IO::Stream> outStream);
    /// Saves the XML document to the specified TextWriter.
    /// @param writer The TextWriter to which you want to save.
    /// @throws XmlException The operation would not result in a well formed XML document
    /// (for example, no document element or duplicate XML declarations).
    virtual ASPOSECPP_SHARED_API void Save(SharedPtr<IO::TextWriter> writer);
    /// Saves the XML document to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    /// @throws XmlException The operation would not result in a well formed XML document
    /// (for example, no document element or duplicate XML declarations).
    virtual ASPOSECPP_SHARED_API void Save(SharedPtr<XmlWriter> w);
    /// Saves the XmlDocument node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the XmlDocument node to the specified XmlWriter.
    /// @param xw The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& xw) override;
    /// Validates the XmlDocument against the XML Schema Definition Language (XSD) schemas contained in the XmlDocument::get_Schemas list.
    /// @param validationEventHandler The Schema::ValidationEventHandler object that
    /// receives information about schema validation warnings and errors.
    /// @throws XmlSchemaValidationException A schema validation event occurred and no Schema::ValidationEventHandler object was specified.
    ASPOSECPP_SHARED_API void Validate(Schema::ValidationEventHandler validationEventHandler);
    /// Validates the XmlNode object specified against the XML Schema Definition Language (XSD) schemas in the XmlDocument::get_Schemas list.
    /// @param validationEventHandler The Schema::ValidationEventHandler object that
    /// receives information about schema validation warnings and errors.
    /// @param nodeToValidate The XmlNode object created from an XmlDocument to validate.
    /// @throws ArgumentException The XmlNode object parameter was not created from an XmlDocument.
    /// @throws InvalidOperationException The XmlNode object parameter is not an element, attribute, document fragment, or the root node.
    /// @throws XmlSchemaValidationException A schema validation event occurred and no Schema::ValidationEventHandler object was specified.
    ASPOSECPP_SHARED_API void Validate(Schema::ValidationEventHandler validationEventHandler, const SharedPtr<XmlNode>& nodeToValidate);

protected:

    /// @cond
    bool fEntRefNodesPresent;
    bool fCDataNodesPresent;
    String strDocumentName;
    String strDocumentFragmentName;
    String strCommentName;
    String strTextName;
    String strCDataSectionName;
    String strEntityName;
    String strID;
    String strXmlns;
    String strXml;
    String strSpace;
    String strLang;
    String strEmpty;
    String strNonSignificantWhitespaceName;
    String strSignificantWhitespaceName;
    String strReservedXmlns;
    String strReservedXml;
    String baseURI;
    bool bSetResolver;
    SharedPtr<Object> objLock;
    static SharedPtr<System::Xml::EmptyEnumerator> EmptyEnumerator;
    static SharedPtr<Schema::IXmlSchemaInfo> NotKnownSchemaInfo;
    static SharedPtr<Schema::IXmlSchemaInfo> ValidSchemaInfo;
    static SharedPtr<Schema::IXmlSchemaInfo> InvalidSchemaInfo;

    SharedPtr<System::Xml::Schema::SchemaInfo> get_DtdSchemaInfo();
    void set_DtdSchemaInfo(const SharedPtr<System::Xml::Schema::SchemaInfo>& value);
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal() override;
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDeclaration> get_Declaration();
    SharedPtr<XmlElement> get_DocumentElementInternal();
    ASPOSECPP_SHARED_API bool get_IsContainer() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlLinkedNode> get_LastNode() override;
    ASPOSECPP_SHARED_API void set_LastNode(SharedPtr<XmlLinkedNode> value) override;
    bool get_CanReportValidity();
    bool get_HasSetResolver();
    SharedPtr<XmlNamedNodeMap> get_Entities();
    void set_Entities(const SharedPtr<XmlNamedNodeMap>& value);
    bool get_IsLoading();
    void set_IsLoading(bool value);
    bool get_ActualLoadingStatus();
    void set_ActualLoadingStatus(bool value);
    SharedPtr<System::Text::Encoding> get_TextEncoding();
    String get_Version();
    String get_Encoding();
    String get_Standalone();
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    bool get_HasEntityReferences();
    SharedPtr<XmlAttribute> get_NamespaceXml();
    /// @endcond

    /// Initializes a new instance of the XmlDocument class with the specified XmlImplementation.
    /// @param imp The XmlImplementation to use.
    ASPOSECPP_SHARED_API XmlDocument(const SharedPtr<XmlImplementation>& imp);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlDocument, CODEPORTING_ARGS(SharedPtr<XmlImplementation> imp));

    /// @cond
    static void CheckName(const String& name);
    SharedPtr<XmlName> AddXmlName(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<Schema::IXmlSchemaInfo>& schemaInfo);
    SharedPtr<XmlName> GetXmlName(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<Schema::IXmlSchemaInfo>& schemaInfo);
    SharedPtr<XmlName> AddAttrXmlName(const String& prefix, const String& localName, const String& namespaceURI, const SharedPtr<Schema::IXmlSchemaInfo>& schemaInfo);
    bool AddIdInfo(const SharedPtr<XmlName>& eleName, const SharedPtr<XmlName>& attrName);
    SharedPtr<XmlName> GetIDInfoByElement(const SharedPtr<XmlName>& eleName);
    void AddElementWithId(const String& id, const SharedPtr<XmlElement>& elem);
    void RemoveElementWithId(const String& id, const SharedPtr<XmlElement>& elem);
    SharedPtr<System::Xml::XmlResolver> GetResolver();
    ASPOSECPP_SHARED_API bool IsValidChildType(XmlNodeType type) override;
    ASPOSECPP_SHARED_API bool CanInsertBefore(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild) override;
    ASPOSECPP_SHARED_API bool CanInsertAfter(SharedPtr<XmlNode> newChild, SharedPtr<XmlNode> refChild) override;
    void SetDefaultNamespace(const String& prefix, const String& localName, String& namespaceURI);
    void AddDefaultAttributes(const SharedPtr<XmlElement>& elem);
    /// @endcond

    /// Creates an XPathNavigator object for navigating this document positioned on the XmlNode specified.
    /// @param node The XmlNode you want the navigator initially positioned on.
    /// @returns An XPathNavigator object.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPath::XPathNavigator> CreateNavigator(SharedPtr<XmlNode> node);

    /// @cond
    static bool IsTextNode(XmlNodeType nt);
    /// @endcond

    /// Creates a default attribute with the specified prefix, local name and namespace URI.
    /// @param prefix The prefix of the attribute (if any).
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute (if any).
    /// @returns The new XmlAttribute.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> CreateDefaultAttribute(const String& prefix, const String& localName, const String& namespaceURI);

    /// @cond
    XmlNodeType ConvertToNodeType(const String& nodeTypeString);
    ASPOSECPP_SHARED_API SharedPtr<XmlNodeChangedEventArgs> GetEventArgs(SharedPtr<XmlNode> node, SharedPtr<XmlNode> oldParent, SharedPtr<XmlNode> newParent, String oldValue, String newValue, XmlNodeChangedAction action) override;
    SharedPtr<XmlNodeChangedEventArgs> GetInsertEventArgsForLoad(const SharedPtr<XmlNode>& node, const SharedPtr<XmlNode>& newParent);
    ASPOSECPP_SHARED_API void BeforeEvent(SharedPtr<XmlNodeChangedEventArgs> args) override;
    ASPOSECPP_SHARED_API void AfterEvent(SharedPtr<XmlNodeChangedEventArgs> args) override;
    SharedPtr<XmlAttribute> GetDefaultAttribute(const SharedPtr<XmlElement>& elem, const String& attrPrefix, const String& attrLocalname, const String& attrNamespaceURI);
    SharedPtr<XmlEntity> GetEntityNode(const String& name);
    void SetBaseURI(const String& inBaseURI);
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> AppendChildForLoad(const SharedPtr<XmlNode>& newChild, const SharedPtr<XmlDocument>& doc) override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlDocument();

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
    const char* DBG_class_name() const override { return "XmlDocument"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlImplementation> _implementation;
    SharedPtr<DomNameTable> _domNameTable;
    SharedPtr<XmlLinkedNode> _lastChild;
    SharedPtr<XmlNamedNodeMap> _entities;
    SharedPtr<Collections::Generic::Dictionary<String, SharedPtr<Collections::Generic::List<WeakReference<>>>>> _htElementIdMap;
    SharedPtr<Collections::Generic::Dictionary<SharedPtr<XmlName>, SharedPtr<XmlName>>> _htElementIDAttrDecl;
    SharedPtr<System::Xml::Schema::SchemaInfo> _schemaInfo;
    SharedPtr<Schema::XmlSchemaSet> _schemas;
    bool _reportValidity;
    bool _actualLoadingStatus;
    bool _preserveWhitespace;
    bool _isLoading;
    SharedPtr<System::Xml::XmlResolver> _resolver;
    SharedPtr<XmlAttribute> _namespaceXml;

    SharedPtr<XmlName> GetIDInfoByElement_(const SharedPtr<XmlName>& eleName);
    WeakReference<> GetElement(const SharedPtr<Collections::Generic::List<WeakReference<>>>& elementList, const SharedPtr<XmlElement>& elem);
    bool HasNodeTypeInPrevSiblings(XmlNodeType nt, const SharedPtr<XmlNode>& refNode);
    bool HasNodeTypeInNextSiblings(XmlNodeType nt, const SharedPtr<XmlNode>& refNode);
    SharedPtr<Schema::SchemaElementDecl> GetSchemaElementDecl(const SharedPtr<XmlElement>& elem);
    SharedPtr<XmlAttribute> PrepareDefaultAttribute(const SharedPtr<Schema::SchemaAttDef>& attdef, const String& attrPrefix, const String& attrLocalname, String attrNamespaceURI);
    SharedPtr<XmlNode> NormalizeText(SharedPtr<XmlNode> n);
    SharedPtr<XmlNode> ImportNodeInternal(const SharedPtr<XmlNode>& node, bool deep);
    void ImportAttributes(const SharedPtr<XmlNode>& fromElem, const SharedPtr<XmlNode>& toElem);
    void ImportChildren(const SharedPtr<XmlNode>& fromNode, const SharedPtr<XmlNode>& toNode, bool deep);
    SharedPtr<XmlTextReader> SetupReader(const SharedPtr<XmlTextReader>& tr);

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

};

} // namespace Xml
} // namespace System


