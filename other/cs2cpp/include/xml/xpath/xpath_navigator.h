/// @file xml/xpath/xpath_navigator.h

#pragma once

#include <xml/xpath/xpath_node_type.h>
#include <xml/xpath/xpath_namespace_scope.h>
#include <xml/xpath/xpath_item.h>
#include <xml/xpath/ixpath_navigable.h>
#include <xml/xml_node_order.h>
#include <xml/xml_namespace_scope.h>
#include <xml/schema/validation_event_handler.h>
#include <xml/ixml_namespace_resolver.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class IDictionary;
template <typename> class IEqualityComparer;
} // namespace Generic
} // namespace Collections
class DateTime;
namespace Internal
{
namespace Xml
{
namespace Cache
{
class XPathDocumentBuilder;
class XPathDocumentElementDescendantIterator;
class XPathDocumentKindDescendantIterator;
class XPathNode;
class XPathNodeHelper;
} // namespace Cache
namespace XPath
{
class XPathArrayIterator;
} // namespace XPath
} // namespace Xml
} // namespace Internal
class TypeInfo;
namespace Xml
{
namespace Schema
{
class IXmlSchemaInfo;
class ValidationEventArgs;
class XmlSchemaAttribute;
class XmlSchemaElement;
class XmlSchemaSet;
class XmlSchemaType;
} // namespace Schema
class XmlNamespaceManager;
class XmlNameTable;
class XmlReader;
class XmlWriter;
namespace XPath
{
class XPathExpression;
class XPathNavigatorKeyComparer;
class XPathNavigatorReader;
class XPathNodeIterator;
} // namespace XPath
namespace Xsl
{
namespace XsltOld
{
class XsltCompileContext;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

/// Provides a cursor model for navigating and editing XML data.
class ASPOSECPP_SHARED_CLASS XPathNavigator : public XPathItem, public IXPathNavigable, public IXmlNamespaceResolver
{
    typedef XPathNavigator ThisType;
    typedef XPathItem BaseType;
    typedef IXPathNavigable BaseType1;
    typedef IXmlNamespaceResolver BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XPathNavigator>;

private:
    /// @cond
    friend class Internal::Xml::Cache::XPathDocumentBuilder;
    friend class XPathNodeIterator;
    friend class Internal::Xml::Cache::XPathDocumentElementDescendantIterator;
    friend class Internal::Xml::Cache::XPathDocumentKindDescendantIterator;
    friend class Internal::Xml::Cache::XPathNode;
    friend class Internal::Xml::Cache::XPathNodeHelper;
    friend class Internal::Xml::XPath::XPathArrayIterator;
    friend class XPathNavigatorReader;
    friend class XPathNodeIterator;
    friend class Xsl::XsltOld::XsltCompileContext;
    /// @endcond

private:

    class CheckValidityHelper : public System::Object
    {
        typedef CheckValidityHelper ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        bool get_IsValid();

        CheckValidityHelper(System::Xml::Schema::ValidationEventHandler nextEventHandler, const SharedPtr<XPathNavigatorReader>& reader);

        void ValidationCallback(const SharedPtr<Object>& sender, const SharedPtr<System::Xml::Schema::ValidationEventArgs>& args);
        /// @endcond

    protected:

        #ifdef ASPOSE_GET_SHARED_MEMBERS
        void GetSharedMembers(System::Object::shared_members_type& result) const override;
        #endif

    #ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to members.
        /// @param visitor Visitor to apply.
        ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
        /// Gets class name.
        /// @return String literal pointer.
        const char* DBG_class_name() const override { return "CheckValidityHelper"; }
    #endif


    private:

        bool _isValid;
        System::Xml::Schema::ValidationEventHandler _nextEventHandler;
        SharedPtr<XPathNavigatorReader> _reader;

    };


public:

    /// Returns a value that indicates if the current node represents an XPath node.
    /// @returns Always returns @c true.
    ASPOSECPP_SHARED_API bool get_IsNode() override;
    /// Returns the XmlSchemaType information for the current node.
    /// @returns An XmlSchemaType object; default is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::Schema::XmlSchemaType> get_XmlType() override;
    /// Returns the current node as a boxed object of the most appropriate type.
    /// @returns The current node as a boxed object of the most appropriate type.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_TypedValue() override;
    /// Returns the type of the current node.
    /// @returns The type of the current node. The default value is String.
    ASPOSECPP_SHARED_API TypeInfo get_ValueType() override;
    /// Returns the current node's value as a Boolean.
    /// @returns The current node's value as a Boolean.
    /// @throws FormatException The current node's string value cannot be converted to a Boolean.
    /// @throws InvalidCastException The attempted cast to Boolean is not valid.
    ASPOSECPP_SHARED_API bool get_ValueAsBoolean() override;
    /// Returns the current node's value as a DateTime.
    /// @returns The current node's value as a DateTime.
    /// @throws FormatException The current node's string value cannot be converted to a DateTime.
    /// @throws InvalidCastException The attempted cast to DateTime is not valid.
    ASPOSECPP_SHARED_API DateTime get_ValueAsDateTime() override;
    /// Returns the current node's value as a Double.
    /// @returns The current node's value as a Double.
    /// @throws FormatException The current node's string value cannot be converted to a Double.
    /// @throws InvalidCastException The attempted cast to Double is not valid.
    ASPOSECPP_SHARED_API double get_ValueAsDouble() override;
    /// Returns the current node's value as an Int32.
    /// @returns The current node's value as an Int32.
    /// @throws FormatException The current node's string value cannot be converted to a Int32.
    /// @throws InvalidCastException The attempted cast to Int32 is not valid.
    ASPOSECPP_SHARED_API int32_t get_ValueAsInt() override;
    /// Returns the current node's value as an Int64.
    /// @returns The current node's value as an Int64.
    /// @throws FormatException The current node's string value cannot be converted to a Int64.
    /// @throws InvalidCastException The attempted cast to Int64 is not valid.
    ASPOSECPP_SHARED_API int64_t get_ValueAsLong() override;
    /// When overridden in a derived class, gets the XmlNameTable of the XPathNavigator.
    /// @returns An XmlNameTable object enabling you to get the atomized version of a String within the XML document.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable() = 0;
    /// Returns an Collections::IEqualityComparer used for equality comparison of XPathNavigator objects.
    /// @returns An Collections::IEqualityComparer used for equality comparison of XPathNavigator objects.
    static ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEqualityComparer<SharedPtr<XPathNavigator>>> get_NavigatorComparer();
    /// When overridden in a derived class, gets the XPathNodeType of the current node.
    /// @returns One of the XPathNodeType values representing the current node.
    virtual ASPOSECPP_SHARED_API XPathNodeType get_NodeType() = 0;
    /// When overridden in a derived class, gets the XPathNavigator::get_Name of the current node without any namespace prefix.
    /// @returns A String that contains the local name of the current node,
    /// or String::Empty if the current node does not have a name (for example, text or comment nodes).
    virtual ASPOSECPP_SHARED_API String get_LocalName() = 0;
    /// When overridden in a derived class, gets the qualified name of the current node.
    /// @returns A String that contains the qualified XPathNavigator::get_Name of the current node,
    /// or String::Empty if the current node does not have a name (for example, text or comment nodes).
    virtual ASPOSECPP_SHARED_API String get_Name() = 0;
    /// When overridden in a derived class, gets the namespace URI of the current node.
    /// @returns A String that contains the namespace URI of the current node,
    /// or String::Empty if the current node has no namespace URI.
    virtual ASPOSECPP_SHARED_API String get_NamespaceURI() = 0;
    /// When overridden in a derived class, gets the namespace prefix associated with the current node.
    /// @returns A String that contains the namespace prefix associated with the current node.
    virtual ASPOSECPP_SHARED_API String get_Prefix() = 0;
    /// When overridden in a derived class, gets the base URI for the current node.
    /// @returns The location from which the node was loaded, or String::Empty if there is no value.
    virtual ASPOSECPP_SHARED_API String get_BaseURI() = 0;
    /// When overridden in a derived class, gets a value that indicates whether the current node is
    /// an empty element without an end element tag.
    /// @returns @c true if the current node is an empty element; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_IsEmptyElement() = 0;
    /// Returns the @c xml:lang scope for the current node.
    /// @returns A String that contains the value of the @c xml:lang scope,
    /// or String::Empty if the current node has no @c xml:lang scope value to return.
    virtual ASPOSECPP_SHARED_API String get_XmlLang();
    /// Used by XPathNavigator implementations which provide a "virtualized" XML view over a store,
    /// to provide access to underlying objects.
    /// @returns The default is @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> get_UnderlyingObject();
    /// Returns a value that indicates whether the current node has any attributes.
    /// @returns @c true if the current node has attributes;
    /// returns @c false if the current node has no attributes,
    /// or if the XPathNavigator is not positioned on an element node.
    virtual ASPOSECPP_SHARED_API bool get_HasAttributes();
    /// Returns a value that indicates whether the current node has any child nodes.
    /// @returns @c true if the current node has any child nodes; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_HasChildren();
    /// Returns the schema information that has been assigned to the current node as a result of schema validation.
    /// @returns An IXmlSchemaInfo object that contains the schema information for the current node.
    virtual ASPOSECPP_SHARED_API SharedPtr<System::Xml::Schema::IXmlSchemaInfo> get_SchemaInfo();
    /// Returns a value that indicates whether the XPathNavigator can edit the underlying XML data.
    /// @returns @c true if the XPathNavigator can edit the underlying XML data; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_CanEdit();
    /// Returns the markup representing the opening and closing tags of the current node and its child nodes.
    /// @returns A String that contains the markup representing the opening and closing tags of the current node and its child nodes.
    virtual ASPOSECPP_SHARED_API String get_OuterXml();
    /// Sets the markup representing the opening and closing tags of the current node and its child nodes.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_OuterXml(String value);
    /// Returns the markup representing the child nodes of the current node.
    /// @returns A String that contains the markup of the child nodes of the current node.
    virtual ASPOSECPP_SHARED_API String get_InnerXml();
    /// Sets the markup representing the child nodes of the current node.
    /// @param value The value to set.
    /// @throws InvalidOperationException The value cannot be set.
    virtual ASPOSECPP_SHARED_API void set_InnerXml(String value);

    /// Sets the value of the current node.
    /// @param value The new value of the node.
    /// @throws ArgumentNullException The value parameter is @c nullptr.
    /// @throws InvalidOperationException The XPathNavigator is positioned on the root node, a namespace node,
    /// or the specified value is invalid.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void SetValue(String value);
    /// Sets the typed value of the current node.
    /// @param typedValue The new typed value of the node.
    /// @throws ArgumentException The XPathNavigator does not support the type of the object specified.
    /// @throws ArgumentNullException The value specified cannot be @c nullptr.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element or attribute node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void SetTypedValue(SharedPtr<Object> typedValue);
    /// Returns the current node's value as the Type specified, using the IXmlNamespaceResolver object specified to resolve namespace prefixes.
    /// @param returnType The Type to return the current node's value as.
    /// @param nsResolver The IXmlNamespaceResolver object used to resolve namespace prefixes.
    /// @returns The value of the current node as the Type requested.
    /// @throws FormatException The current node's value is not in the correct format for the target type.
    /// @throws InvalidCastException The attempted cast is not valid.
    ASPOSECPP_SHARED_API SharedPtr<Object> ValueAs(const TypeInfo& returnType, SharedPtr<IXmlNamespaceResolver> nsResolver) override;
    /// Returns a copy of the XPathNavigator.
    /// @returns An XPathNavigator copy of this XPathNavigator.
    ASPOSECPP_SHARED_API SharedPtr<XPathNavigator> CreateNavigator() override;
    /// Returns the namespace URI for the specified prefix.
    /// @param prefix The prefix whose namespace URI you want to resolve.
    /// To match the default namespace, pass String::Empty.
    /// @returns A String that contains the namespace URI assigned to the namespace prefix specified;
    /// @c nullptr if no namespace URI is assigned to the prefix specified.
    /// The String returned is atomized.
    ASPOSECPP_SHARED_API String LookupNamespace(const String& prefix) override;
    /// Returns the prefix declared for the specified namespace URI.
    /// @param namespaceURI The namespace URI to resolve for the prefix.
    /// @returns A String that contains the namespace prefix assigned to the namespace URI specified;
    /// otherwise, String::Empty if no prefix is assigned to the namespace URI specified.
    /// The String returned is atomized.
    ASPOSECPP_SHARED_API String LookupPrefix(const String& namespaceURI) override;
    /// Returns the in-scope namespaces of the current node.
    /// @param scope An XmlNamespaceScope value specifying the namespaces to return.
    /// @returns An IDictionary collection of namespace names keyed by prefix.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IDictionary<String, String>> GetNamespacesInScope(XmlNamespaceScope scope) override;
    /// When overridden in a derived class, creates a new XPathNavigator positioned at the same node as this XPathNavigator.
    /// @returns A new XPathNavigator positioned at the same node as this XPathNavigator.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNavigator> Clone() = 0;
    /// Returns an XmlReader object that contains the current node and its child nodes.
    /// @returns An XmlReader object that contains the current node and its child nodes.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element node or the root node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlReader> ReadSubtree();
    /// Streams the current node and its child nodes to the XmlWriter object specified.
    /// @param writer The XmlWriter object to stream to.
    virtual ASPOSECPP_SHARED_API void WriteSubtree(SharedPtr<XmlWriter> writer);
    /// Returns the value of the attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute. @p localName is case-sensitive.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns A String that contains the value of the specified attribute;
    /// String::Empty if a matching attribute is not found, or if the XPathNavigator is not positioned on an element node.
    virtual ASPOSECPP_SHARED_API String GetAttribute(String localName, String namespaceURI);
    /// Moves the XPathNavigator to the attribute with the matching local name and namespace URI.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute; @c nullptr for an empty namespace.
    /// @returns @c true if the XPathNavigator is successful moving to the attribute; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToAttribute(String localName, String namespaceURI);
    /// When overridden in a derived class, moves the XPathNavigator to the first attribute of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the first attribute of the current node;
    /// otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToFirstAttribute() = 0;
    /// When overridden in a derived class, moves the XPathNavigator to the next attribute.
    /// @returns @c true if the XPathNavigator is successful moving to the next attribute;
    /// @c false if there are no more attributes.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToNextAttribute() = 0;
    /// Returns the value of the namespace node corresponding to the specified local name.
    /// @param name The local name of the namespace node.
    /// @returns A String that contains the value of the namespace node;
    /// String::Empty if a matching namespace node is not found, or if the XPathNavigator is not positioned on an element node.
    virtual ASPOSECPP_SHARED_API String GetNamespace(String name);
    /// Moves the XPathNavigator to the namespace node with the specified namespace prefix.
    /// @param name The namespace prefix of the namespace node.
    /// @returns @c true if the XPathNavigator is successful moving to the specified namespace;
    /// @c false if a matching namespace node was not found, or if the XPathNavigator is not positioned on an element node.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToNamespace(String name);
    /// When overridden in a derived class, moves the XPathNavigator to the first namespace node that matches the XPathNamespaceScope specified.
    /// @param namespaceScope An XPathNamespaceScope value describing the namespace scope.
    /// @returns @c true if the XPathNavigator is successful moving to the first namespace node; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToFirstNamespace(XPathNamespaceScope namespaceScope) = 0;
    /// When overridden in a derived class, moves the XPathNavigator to the next namespace node matching the XPathNamespaceScope specified.
    /// @param namespaceScope An XPathNamespaceScope value describing the namespace scope.
    /// @returns @c true if the XPathNavigator is successful moving to the next namespace node; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToNextNamespace(XPathNamespaceScope namespaceScope) = 0;
    /// Moves the XPathNavigator to first namespace node of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the first namespace node; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    ASPOSECPP_SHARED_API bool MoveToFirstNamespace();
    /// Moves the XPathNavigator to the next namespace node.
    /// @returns @c true if the XPathNavigator is successful moving to the next namespace node; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    ASPOSECPP_SHARED_API bool MoveToNextNamespace();
    /// When overridden in a derived class, moves the XPathNavigator to the next sibling node of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the next sibling node; otherwise
    /// @c false if there are no more siblings or if the XPathNavigator is currently positioned on an attribute node.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToNext() = 0;
    /// When overridden in a derived class, moves the XPathNavigator to the previous sibling node of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the previous sibling node; otherwise,
    /// @c false if there is no previous sibling node or if the XPathNavigator is currently positioned on an attribute node.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToPrevious() = 0;
    /// Moves the XPathNavigator to the first sibling node of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the first sibling node of the current node;
    /// @c false if there is no first sibling, or if the XPathNavigator is currently positioned on an attribute node.
    /// If the XPathNavigator is already positioned on the first sibling,
    /// XPathNavigator will return @c true and will not move its position.
    /// If XPathNavigator::MoveToFirst returns @c false because there is no first sibling,
    /// or if XPathNavigator is currently positioned on an attribute, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToFirst();
    /// When overridden in a derived class, moves the XPathNavigator to the first child node of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the first child node of the current node;
    /// otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToFirstChild() = 0;
    /// When overridden in a derived class, moves the XPathNavigator to the parent node of the current node.
    /// @returns @c true if the XPathNavigator is successful moving to the parent node of the current node;
    /// otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToParent() = 0;
    /// Moves the XPathNavigator to the root node that the current node belongs to.
    virtual ASPOSECPP_SHARED_API void MoveToRoot();
    /// When overridden in a derived class, moves the XPathNavigator to the same position as the specified XPathNavigator.
    /// @param other The XPathNavigator positioned on the node that you want to move to.
    /// @returns @c true if the XPathNavigator is successful moving to the same position as the specified XPathNavigator;
    /// otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveTo(SharedPtr<XPathNavigator> other) = 0;
    /// When overridden in a derived class, moves to the node that has an attribute of type @c ID whose value matches the specified String.
    /// @param id A String representing the @c ID value of the node to which you want to move.
    /// @returns @c true if the XPathNavigator is successful moving; otherwise, @c false.
    /// If @c false, the position of the navigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToId(String id) = 0;
    /// Moves the XPathNavigator to the child node with the local name and namespace URI specified.
    /// @param localName The local name of the child node to move to.
    /// @param namespaceURI The namespace URI of the child node to move to.
    /// @returns @c true if the XPathNavigator is successful moving to the child node; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToChild(String localName, String namespaceURI);
    /// Moves the XPathNavigator to the child node of the XPathNodeType specified.
    /// @param type The XPathNodeType of the child node to move to.
    /// @returns @c true if the XPathNavigator is successful moving to the child node; otherwise, @c false.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToChild(XPathNodeType type);
    /// Moves the XPathNavigator to the element with the local name and namespace URI specified in document order.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns @c true if the XPathNavigator moved successfully; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool MoveToFollowing(String localName, String namespaceURI);
    /// Moves the XPathNavigator to the element with the local name and namespace URI specified,
    /// to the boundary specified, in document order.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @param end The XPathNavigator object positioned on the element boundary which the current XPathNavigator
    /// will not move past while searching for the following element.
    /// @returns @c true if the XPathNavigator moved successfully; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool MoveToFollowing(String localName, String namespaceURI, SharedPtr<XPathNavigator> end);
    /// Moves the XPathNavigator to the following element of the XPathNodeType specified in document order.
    /// @param type The XPathNodeType of the element. The XPathNodeType cannot be
    /// XPathNodeType::Attribute or XPathNodeType::Namespace.
    /// @returns @c true if the XPathNavigator moved successfully; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool MoveToFollowing(XPathNodeType type);
    /// Moves the XPathNavigator to the following element of the XPathNodeType specified,
    /// to the boundary specified, in document order.
    /// @param type The XPathNodeType of the element. The XPathNodeType cannot be
    /// XPathNodeType::Attribute or XPathNodeType::Namespace.
    /// @param end The XPathNavigator object positioned on the element boundary which the current XPathNavigator
    /// will not move past while searching for the following element.
    /// @returns @c true if the XPathNavigator moved successfully; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool MoveToFollowing(XPathNodeType type, SharedPtr<XPathNavigator> end);
    /// Moves the XPathNavigator to the next sibling node with the local name and namespace URI specified.
    /// @param localName The local name of the next sibling node to move to.
    /// @param namespaceURI The namespace URI of the next sibling node to move to.
    /// @returns @c true if the XPathNavigator is successful moving to the next sibling node;
    /// @c false if there are no more siblings, or if the XPathNavigator is currently positioned on an attribute node.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToNext(String localName, String namespaceURI);
    /// Moves the XPathNavigator to the next sibling node of the current node that matches the XPathNodeType specified.
    /// @param type The XPathNodeType of the sibling node to move to.
    /// @returns @c true if the XPathNavigator is successful moving to the next sibling node;
    /// otherwise, @c false if there are no more siblings or if the XPathNavigator is currently positioned on an attribute node.
    /// If @c false, the position of the XPathNavigator is unchanged.
    virtual ASPOSECPP_SHARED_API bool MoveToNext(XPathNodeType type);
    /// When overridden in a derived class, determines whether the current XPathNavigator is
    /// at the same position as the specified XPathNavigator.
    /// @param other The XPathNavigator to compare to this XPathNavigator.
    /// @returns @c true if the two XPathNavigator objects have the same position; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool IsSamePosition(SharedPtr<XPathNavigator> other) = 0;
    /// Determines whether the specified XPathNavigator is a descendant of the current XPathNavigator.
    /// @param nav The XPathNavigator to compare to this XPathNavigator.
    /// @returns @c true if the specified XPathNavigator is a descendant of the current XPathNavigator; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool IsDescendant(SharedPtr<XPathNavigator> nav);
    /// Compares the position of the current XPathNavigator with the position of the XPathNavigator specified.
    /// @param nav The XPathNavigator to compare against.
    /// @returns An XmlNodeOrder value representing the comparative position of the two XPathNavigator objects.
    virtual ASPOSECPP_SHARED_API XmlNodeOrder ComparePosition(SharedPtr<XPathNavigator> nav);
    /// Verifies that the XML data in the XPathNavigator conforms to the XML Schema definition language (XSD) schema provided.
    /// @param schemas The XmlSchemaSet containing the schemas used to validate the XML data contained in the XPathNavigator.
    /// @param validationEventHandler The ValidationEventHandler that receives information about schema validation warnings and errors.
    /// @returns @c true if no schema validation errors occurred; otherwise, @c false.
    /// @throws XmlSchemaValidationException A schema validation error occurred,
    /// and no ValidationEventHandler was specified to handle validation errors.
    /// @throws InvalidOperationException The XPathNavigator is positioned on a node that is not an element, attribute,
    /// or the root node or there is not type information to perform validation.
    /// @throws ArgumentException The method was called with an XmlSchemaSet parameter when the XPathNavigator was
    /// not positioned on the root node of the XML data.
    virtual ASPOSECPP_SHARED_API bool CheckValidity(SharedPtr<System::Xml::Schema::XmlSchemaSet> schemas, System::Xml::Schema::ValidationEventHandler validationEventHandler);
    /// Compiles a string representing an XPath expression and returns an XPathExpression object.
    /// @param xpath A string representing an XPath expression.
    /// @returns An XPathExpression object representing the XPath expression.
    /// @throws ArgumentException The @p xpath parameter contains an XPath expression that is not valid.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathExpression> Compile(String xpath);
    /// Selects a single node in the XPathNavigator using the specified XPath query.
    /// @param xpath A String representing an XPath expression.
    /// @returns An XPathNavigator object that contains the first matching node for the XPath query specified;
    /// otherwise, @c nullptr if there are no query results.
    /// @throws ArgumentException An error was encountered in the XPath query or the return type of
    /// the XPath expression is not a node.
    /// @throws XPathException The XPath query is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNavigator> SelectSingleNode(String xpath);
    /// Selects a single node in the XPathNavigator object using the specified XPath query with
    /// the IXmlNamespaceResolver object specified to resolve namespace prefixes.
    /// @param xpath A String representing an XPath expression.
    /// @param resolver The IXmlNamespaceResolver object used to resolve namespace prefixes in the XPath query.
    /// @returns An XPathNavigator object that contains the first matching node for the XPath query specified;
    /// otherwise @c nullptr if there are no query results.
    /// @throws ArgumentException An error was encountered in the XPath query or the return type of
    /// the XPath expression is not a node.
    /// @throws XPathException The XPath query is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNavigator> SelectSingleNode(String xpath, SharedPtr<IXmlNamespaceResolver> resolver);
    /// Selects a single node in the XPathNavigator using the specified XPathExpression object.
    /// @param expression An XPathExpression object containing the compiled XPath query.
    /// @returns An XPathNavigator object that contains the first matching node for the XPath query specified;
    /// otherwise @c nullptr if there are no query results.
    /// @throws ArgumentException An error was encountered in the XPath query or the return type of
    /// the XPath expression is not a node.
    /// @throws XPathException The XPath query is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNavigator> SelectSingleNode(SharedPtr<XPathExpression> expression);
    /// Selects a node set, using the specified XPath expression.
    /// @param xpath A String representing an XPath expression.
    /// @returns An XPathNodeIterator pointing to the selected node set.
    /// @throws ArgumentException The XPath expression contains an error or its return type is not a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> Select(String xpath);
    /// Selects a node set using the specified XPath expression with the IXmlNamespaceResolver object specified
    /// to resolve namespace prefixes.
    /// @param xpath A String representing an XPath expression.
    /// @param resolver The IXmlNamespaceResolver object used to resolve namespace prefixes.
    /// @returns An XPathNodeIterator that points to the selected node set.
    /// @throws ArgumentException The XPath expression contains an error or its return type is not a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> Select(String xpath, SharedPtr<IXmlNamespaceResolver> resolver);
    /// Selects a node set using the specified XPathExpression.
    /// @param expr An XPathExpression object containing the compiled XPath query.
    /// @returns An XPathNodeIterator that points to the selected node set.
    /// @throws ArgumentException The XPath expression contains an error or its return type is not a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> Select(SharedPtr<XPathExpression> expr);
    /// Evaluates the specified XPath expression and returns the typed result.
    /// @param xpath A string representing an XPath expression that can be evaluated.
    /// @returns The result of the expression (Boolean, number, string, or node set).
    /// This maps to Boolean, Double, String, or XPathNodeIterator objects respectively.
    /// @throws ArgumentException The return type of the XPath expression is a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> Evaluate(String xpath);
    /// Evaluates the specified XPath expression and returns the typed result,
    /// using the IXmlNamespaceResolver object specified to resolve namespace prefixes in the XPath expression.
    /// @param xpath A string representing an XPath expression that can be evaluated.
    /// @param resolver The IXmlNamespaceResolver object used to resolve namespace prefixes in the XPath expression.
    /// @returns The result of the expression (Boolean, number, string, or node set).
    /// This maps to Boolean, Double, String, or XPathNodeIterator objects respectively.
    /// @throws ArgumentException The return type of the XPath expression is a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> Evaluate(String xpath, SharedPtr<IXmlNamespaceResolver> resolver);
    /// Evaluates the XPathExpression and returns the typed result.
    /// @param expr An XPathExpression that can be evaluated.
    /// @returns The result of the expression (Boolean, number, string, or node set).
    /// This maps to Boolean, Double, String, or XPathNodeIterator objects respectively.
    /// @throws ArgumentException The return type of the XPath expression is a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> Evaluate(SharedPtr<XPathExpression> expr);
    /// Uses the supplied context to evaluate the XPathExpression, and returns the typed result.
    /// @param expr An XPathExpression that can be evaluated.
    /// @param context An XPathNodeIterator that points to the selected node set that the evaluation is to be performed on.
    /// @returns The result of the expression (Boolean, number, string, or node set).
    /// This maps to Boolean, Double, String, or XPathNodeIterator objects respectively.
    /// @throws ArgumentException The return type of the XPath expression is a node set.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> Evaluate(SharedPtr<XPathExpression> expr, SharedPtr<XPathNodeIterator> context);
    /// Determines whether the current node matches the specified XPathExpression.
    /// @param expr An XPathExpression object containing the compiled XPath expression.
    /// @returns @c true if the current node matches the XPathExpression; otherwise, @c false.
    /// @throws ArgumentException The XPath expression cannot be evaluated.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API bool Matches(SharedPtr<XPathExpression> expr);
    /// Determines whether the current node matches the specified XPath expression.
    /// @param xpath The XPath expression.
    /// @returns @c true if the current node matches the specified XPath expression; otherwise, @c false.
    /// @throws ArgumentException The XPath expression cannot be evaluated.
    /// @throws XPathException The XPath expression is not valid.
    virtual ASPOSECPP_SHARED_API bool Matches(String xpath);
    /// Selects all the child nodes of the current node that have the matching XPathNodeType.
    /// @param type The XPathNodeType of the child nodes.
    /// @returns An XPathNodeIterator that contains the selected nodes.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> SelectChildren(XPathNodeType type);
    /// Selects all the child nodes of the current node that have the local name and namespace URI specified.
    /// @param name The local name of the child nodes.
    /// @param namespaceURI The namespace URI of the child nodes.
    /// @returns An XPathNodeIterator that contains the selected nodes.
    /// @throws ArgumentNullException @c nullptr cannot be passed as a parameter.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> SelectChildren(String name, String namespaceURI);
    /// Selects all the ancestor nodes of the current node that have a matching XPathNodeType.
    /// @param type The XPathNodeType of the ancestor nodes.
    /// @param matchSelf To include the context node in the selection, @c true; otherwise, @c false.
    /// @returns An XPathNodeIterator that contains the selected nodes.
    /// The returned nodes are in reverse document order.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> SelectAncestors(XPathNodeType type, bool matchSelf);
    /// Selects all the ancestor nodes of the current node that have the specified local name and namespace URI.
    /// @param name The local name of the ancestor nodes.
    /// @param namespaceURI The namespace URI of the ancestor nodes.
    /// @param matchSelf To include the context node in the selection, @c true; otherwise, @c false.
    /// @returns An XPathNodeIterator that contains the selected nodes.
    /// The returned nodes are in reverse document order.
    /// @throws ArgumentNullException @c nullptr cannot be passed as a parameter.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> SelectAncestors(String name, String namespaceURI, bool matchSelf);
    /// Selects all the descendant nodes of the current node that have a matching XPathNodeType.
    /// @param type The XPathNodeType of the descendant nodes.
    /// @param matchSelf @c true to include the context node in the selection; otherwise, @c false.
    /// @returns An XPathNodeIterator that contains the selected nodes.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> SelectDescendants(XPathNodeType type, bool matchSelf);
    /// Selects all the descendant nodes of the current node with the local name and namespace URI specified.
    /// @param name The local name of the descendant nodes.
    /// @param namespaceURI The namespace URI of the descendant nodes.
    /// @param matchSelf @c true to include the context node in the selection; otherwise, @c false.
    /// @returns An XPathNodeIterator that contains the selected nodes.
    /// @throws ArgumentNullException @c nullptr cannot be passed as a parameter.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> SelectDescendants(String name, String namespaceURI, bool matchSelf);
    /// Returns an XmlWriter object used to create a new child node at the beginning of
    /// the list of child nodes of the current node.
    /// @returns An XmlWriter object used to create a new child node at the beginning of
    /// the list of child nodes of the current node.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on does not allow
    /// a new child node to be prepended.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriter> PrependChild();
    /// Returns an XmlWriter object used to create one or more new child nodes at the end of
    /// the list of child nodes of the current node.
    /// @returns An XmlWriter object used to create new child nodes at the end of the list of
    /// child nodes of the current node.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on is not
    /// the root node or an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriter> AppendChild();
    /// Returns an XmlWriter object used to create a new sibling node after the currently selected node.
    /// @returns An XmlWriter object used to create a new sibling node after the currently selected node.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow
    /// a new sibling node to be inserted after the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriter> InsertAfter();
    /// Returns an XmlWriter object used to create a new sibling node before the currently selected node.
    /// @returns An XmlWriter object used to create a new sibling node before the currently selected node.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow
    /// a new sibling node to be inserted before the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriter> InsertBefore();
    /// Returns an XmlWriter object used to create new attributes on the current element.
    /// @returns An XmlWriter object used to create new attributes on the current element.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriter> CreateAttributes();
    /// Replaces a range of sibling nodes from the current node to the node specified.
    /// @param lastSiblingToReplace An XPathNavigator positioned on the last sibling node in the range to replace.
    /// @returns An XmlWriter object used to specify the replacement range.
    /// @throws ArgumentNullException The XPathNavigator specified is @c nullptr.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws InvalidOperationException The last node to replace specified is not
    /// a valid sibling node of the current node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriter> ReplaceRange(SharedPtr<XPathNavigator> lastSiblingToReplace);
    /// Replaces the current node with the content of the string specified.
    /// @param newNode The XML data string for the new node.
    /// @throws ArgumentNullException The XML string parameter is @c nullptr.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element, text,
    /// processing instruction, or comment node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML string parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void ReplaceSelf(String newNode);
    /// Replaces the current node with the contents of the XmlReader object specified.
    /// @param newNode An XmlReader object positioned on the XML data for the new node.
    /// @throws ArgumentException The XmlReader object is in an error state or closed.
    /// @throws ArgumentNullException The XmlReader object parameter is @c nullptr.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element, text,
    /// processing instruction, or comment node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML contents of the XmlReader object parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void ReplaceSelf(SharedPtr<XmlReader> newNode);
    /// Replaces the current node with the contents of the XPathNavigator object specified.
    /// @param newNode An XPathNavigator object positioned on the new node.
    /// @throws ArgumentNullException The XPathNavigator object parameter is @c nullptr.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element,
    /// text, processing instruction, or comment node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML contents of the XPathNavigator object parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void ReplaceSelf(SharedPtr<XPathNavigator> newNode);
    /// Creates a new child node at the end of the list of child nodes of the current node using the XML data string specified.
    /// @param newChild The XML data string for the new child node.
    /// @throws ArgumentNullException The XML data string parameter is @c nullptr.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on is not
    /// the root node or an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML data string parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void AppendChild(String newChild);
    /// Creates a new child node at the end of the list of child nodes of the current node using the XML contents
    /// of the XmlReader object specified.
    /// @param newChild An XmlReader object positioned on the XML data for the new child node.
    /// @throws ArgumentException The XmlReader object is in an error state or closed.
    /// @throws ArgumentNullException The XmlReader object parameter is @c nullptr.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on is not
    /// the root node or an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML contents of the XmlReader object parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void AppendChild(SharedPtr<XmlReader> newChild);
    /// Creates a new child node at the end of the list of child nodes of the current node using the nodes
    /// in the XPathNavigator specified.
    /// @param newChild An XPathNavigator object positioned on the node to add as the new child node.
    /// @throws ArgumentNullException The XPathNavigator object parameter is @c nullptr.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on is not
    /// the root node or an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void AppendChild(SharedPtr<XPathNavigator> newChild);
    /// Creates a new child node at the beginning of the list of child nodes of the current node using the XML string specified.
    /// @param newChild The XML data string for the new child node.
    /// @throws ArgumentNullException The XML string parameter is @c nullptr.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on does not allow
    /// a new child node to be prepended.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML string parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void PrependChild(String newChild);
    /// Creates a new child node at the beginning of the list of child nodes of the current node using
    /// the XML contents of the XmlReader object specified.
    /// @param newChild An XmlReader object positioned on the XML data for the new child node.
    /// @throws ArgumentException The XmlReader object is in an error state or closed.
    /// @throws ArgumentNullException The XmlReader object parameter is @c nullptr.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on does not allow
    /// a new child node to be prepended.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML contents of the XmlReader object parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void PrependChild(SharedPtr<XmlReader> newChild);
    /// Creates a new child node at the beginning of the list of child nodes of the current node using the nodes
    /// in the XPathNavigator object specified.
    /// @param newChild An XPathNavigator object positioned on the node to add as the new child node.
    /// @throws ArgumentNullException The XPathNavigator object parameter is @c nullptr.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on does not allow
    /// a new child node to be prepended.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void PrependChild(SharedPtr<XPathNavigator> newChild);
    /// Creates a new sibling node before the currently selected node using the XML string specified.
    /// @param newSibling The XML data string for the new sibling node.
    /// @throws ArgumentNullException The XML string parameter is @c nullptr.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted before the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML string parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void InsertBefore(String newSibling);
    /// Creates a new sibling node before the currently selected node using the XML contents of the XmlReader object specified.
    /// @param newSibling An XmlReader object positioned on the XML data for the new sibling node.
    /// @throws ArgumentException The XmlReader object is in an error state or closed.
    /// @throws ArgumentNullException The XmlReader object parameter is @c nullptr.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted before the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML contents of the XmlReader object parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void InsertBefore(SharedPtr<XmlReader> newSibling);
    /// Creates a new sibling node before the currently selected node using the nodes in the XPathNavigator specified.
    /// @param newSibling An XPathNavigator object positioned on the node to add as the new sibling node.
    /// @throws ArgumentNullException The XPathNavigator object parameter is @c nullptr.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted before the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void InsertBefore(SharedPtr<XPathNavigator> newSibling);
    /// Creates a new sibling node after the currently selected node using the XML string specified.
    /// @param newSibling The XML data string for the new sibling node.
    /// @throws ArgumentNullException The XML string parameter is @c nullptr.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted after the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML string parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void InsertAfter(String newSibling);
    /// Creates a new sibling node after the currently selected node using the XML contents of the XmlReader object specified.
    /// @param newSibling An XmlReader object positioned on the XML data for the new sibling node.
    /// @throws ArgumentException The XmlReader object is in an error state or closed.
    /// @throws ArgumentNullException The XmlReader object parameter is @c nullptr.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted after the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws XmlException The XML contents of the XmlReader object parameter is not well-formed.
    virtual ASPOSECPP_SHARED_API void InsertAfter(SharedPtr<XmlReader> newSibling);
    /// Creates a new sibling node after the currently selected node using the nodes in the XPathNavigator object specified.
    /// @param newSibling An XPathNavigator object positioned on the node to add as the new sibling node.
    /// @throws ArgumentNullException The XPathNavigator object parameter is @c nullptr.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted after the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void InsertAfter(SharedPtr<XPathNavigator> newSibling);
    /// Deletes a range of sibling nodes from the current node to the node specified.
    /// @param lastSiblingToDelete An XPathNavigator positioned on the last sibling node in the range to delete.
    /// @throws ArgumentNullException The XPathNavigator specified is @c nullptr.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    /// @throws InvalidOperationException The last node to delete specified is not a valid sibling node of the current node.
    virtual ASPOSECPP_SHARED_API void DeleteRange(SharedPtr<XPathNavigator> lastSiblingToDelete);
    /// Deletes the current node and its child nodes.
    /// @throws InvalidOperationException The XPathNavigator is positioned on a node that cannot be deleted such as
    /// the root node or a namespace node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void DeleteSelf();
    /// Creates a new child element at the beginning of the list of child nodes of the current node using
    /// the namespace prefix, local name, and namespace URI specified with the value specified.
    /// @param prefix The namespace prefix of the new child element (if any).
    /// @param localName The local name of the new child element (if any).
    /// @param namespaceURI The namespace URI of the new child element (if any).
    /// String::Empty and @c nullptr are equivalent.
    /// @param value The value of the new child element.
    /// If String::Empty or @c nullptr are passed, an empty element is created.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on does not
    /// allow a new child node to be prepended.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void PrependChildElement(String prefix, String localName, String namespaceURI, String value);
    /// Creates a new child element node at the end of the list of child nodes of the current node using
    /// the namespace prefix, local name and namespace URI specified with the value specified.
    /// @param prefix The namespace prefix of the new child element node (if any).
    /// @param localName The local name of the new child element node (if any).
    /// @param namespaceURI The namespace URI of the new child element node (if any).
    /// String::Empty and @c nullptr are equivalent.
    /// @param value The value of the new child element node.
    /// If String::Empty or @c nullptr are passed, an empty element is created.
    /// @throws InvalidOperationException The current node the XPathNavigator is positioned on is not the root node or an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void AppendChildElement(String prefix, String localName, String namespaceURI, String value);
    /// Creates a new sibling element before the current node using the namespace prefix,
    /// local name, and namespace URI specified, with the value specified.
    /// @param prefix The namespace prefix of the new child element (if any).
    /// @param localName The local name of the new child element (if any).
    /// @param namespaceURI The namespace URI of the new child element (if any).
    /// String::Empty and @c nullptr are equivalent.
    /// @param value The value of the new child element.
    /// If String::Empty or @c nullptr are passed, an empty element is created.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted before the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void InsertElementBefore(String prefix, String localName, String namespaceURI, String value);
    /// Creates a new sibling element after the current node using the namespace prefix,
    /// local name and namespace URI specified, with the value specified.
    /// @param prefix The namespace prefix of the new child element (if any).
    /// @param localName The local name of the new child element (if any).
    /// @param namespaceURI The namespace URI of the new child element (if any).
    /// String::Empty and @c nullptr are equivalent.
    /// @param value The value of the new child element.
    /// If String::Empty or @c nullptr are passed, an empty element is created.
    /// @throws InvalidOperationException The position of the XPathNavigator does not allow a new sibling node
    /// to be inserted after the current node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void InsertElementAfter(String prefix, String localName, String namespaceURI, String value);
    /// Creates an attribute node on the current element node using the namespace prefix,
    /// local name and namespace URI specified with the value specified.
    /// @param prefix The namespace prefix of the new attribute node (if any).
    /// @param localName The local name of the new attribute node which cannot String::Empty or @c nullptr.
    /// @param namespaceURI The namespace URI for the new attribute node (if any).
    /// @param value The value of the new attribute node.
    /// If String::Empty or @c nullptr are passed, an empty attribute node is created.
    /// @throws InvalidOperationException The XPathNavigator is not positioned on an element node.
    /// @throws NotSupportedException The XPathNavigator does not support editing.
    virtual ASPOSECPP_SHARED_API void CreateAttribute(String prefix, String localName, String namespaceURI, String value);
    /// Returns the text value of the current node.
    /// @returns A @c string that contains the text value of the current node.
    ASPOSECPP_SHARED_API String ToString() const override;

protected:

    /// @cond
    static SharedPtr<XPathNavigatorKeyComparer> comparer;

    uint32_t get_IndexInParent();

    static ArrayPtr<char16_t> NodeTypeLetter;
    static ArrayPtr<char16_t> UniqueIdTbl;

    virtual ASPOSECPP_SHARED_API String get_UniqueId();

    static const int32_t AllMask;
    static const int32_t NoAttrNmspMask;
    static const int32_t TextMask;
    static ArrayPtr<int32_t> ContentKindMasks;

    bool MoveToPrevious(String localName, const String& namespaceURI);
    bool MoveToPrevious(XPathNodeType type);
    bool MoveToNonDescendant();
    static SharedPtr<XmlNamespaceManager> GetNamespaces(const SharedPtr<IXmlNamespaceResolver>& resolver);
    static int32_t GetContentKindMask(XPathNodeType type);
    static int32_t GetKindMask(XPathNodeType type);
    static bool IsText(XPathNodeType type);
    void BuildSubtree(const SharedPtr<XmlReader>& reader, const SharedPtr<XmlWriter>& writer);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XPathNavigator();

private:

    String ToString_NonConst();
    SharedPtr<XmlReader> GetValidatingReader(const SharedPtr<XmlReader>& reader, const SharedPtr<System::Xml::Schema::XmlSchemaSet>& schemas, System::Xml::Schema::ValidationEventHandler validationEvent, const SharedPtr<System::Xml::Schema::XmlSchemaType>& schemaType, const SharedPtr<System::Xml::Schema::XmlSchemaElement>& schemaElement, const SharedPtr<System::Xml::Schema::XmlSchemaAttribute>& schemaAttribute);
    static SharedPtr<XPathExpression> CompileMatchPattern(const String& xpath);
    static int32_t GetDepth(const SharedPtr<XPathNavigator>& nav);
    XmlNodeOrder CompareSiblings(const SharedPtr<XPathNavigator>& n1, const SharedPtr<XPathNavigator>& n2);
    bool IsValidChildType(XPathNodeType type);
    bool IsValidSiblingType(XPathNodeType type);
    SharedPtr<XmlReader> CreateReader();
    SharedPtr<XmlReader> CreateContextReader(const String& xml, bool fromCurrentNode);

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

};

} // namespace XPath
} // namespace Xml
} // namespace System


