/// @file xml/xml_attribute_collection.h

#pragma once

#include <xml/xml_named_node_map.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class DocumentXmlWriter;
class XmlAttribute;
class XmlElement;
class XmlLoader;
class XmlNamedNodeMap;
class XmlNode;
class XmlNodeReaderNavigator;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a collection of attributes that can be accessed by name or index.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlAttributeCollection final : public XmlNamedNodeMap
{
    typedef XmlAttributeCollection ThisType;
    typedef XmlNamedNodeMap BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlAttributeCollection>;

private:
    /// @cond
    friend class DocumentXmlWriter;
    friend class XmlAttribute;
    friend class XmlElement;
    friend class XmlLoader;
    friend class XmlNodeReaderNavigator;
    /// @endcond

public:

    /// Returns the attribute with the specified index.
    /// @param i The index of the attribute.
    /// @returns The attribute at the specified index.
    /// @throws IndexOutOfRangeException The index being passed in is out of range.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> idx_get(int32_t i);
    /// Returns the attribute with the specified name.
    /// @param name The qualified name of the attribute.
    /// @returns The attribute with the specified name. If the attribute does not exist, this method returns @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> idx_get(const String& name);
    /// Returns the attribute with the specified local name and namespace Uniform Resource Identifier (URI).
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The attribute with the specified local name and namespace URI.
    /// If the attribute does not exist, this method returns @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> idx_get(const String& localName, const String& namespaceURI);

    /// Adds an XmlNode using its XmlNode::get_Name result.
    /// @param node An attribute node to store in this collection. The node will later be accessible using the name of the node.
    /// If a node with that name is already present in the collection, it is replaced by the new one;
    /// otherwise, the node is appended to the end of the collection.
    /// @returns If the @p node replaces an existing node with the same name, the old node is returned;
    /// otherwise, the added node is returned.
    /// @throws ArgumentException @p node was created from a different XmlDocument than the one that created this collection.
    /// This XmlAttributeCollection is read-only.
    /// @throws InvalidOperationException @p node is an XmlAttribute that is already an attribute of another XmlElement object.
    /// To re-use attributes in other elements, you must clone the XmlAttribute objects you want to re-use.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> SetNamedItem(SharedPtr<XmlNode> node) override;
    /// Inserts the specified attribute as the first node in the collection.
    /// @param node The attribute to insert.
    /// @returns The XmlAttribute added to the collection.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> Prepend(const SharedPtr<XmlAttribute>& node);
    /// Inserts the specified attribute as the last node in the collection.
    /// @param node The attribute to insert.
    /// @returns The XmlAttribute to append to the collection.
    /// @throws ArgumentException @p node was created from a document different from the one that created this collection.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> Append(const SharedPtr<XmlAttribute>& node);
    /// Inserts the specified attribute immediately before the specified reference attribute.
    /// @param newNode The attribute to insert.
    /// @param refNode The reference attribute. @p newNode is placed before the @p refNode.
    /// @returns The XmlAttribute to insert into the collection.
    /// @throws ArgumentException The @p newNode was created from a document different from the one that created this collection.
    /// Or the @p refNode is not a member of this collection.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> InsertBefore(const SharedPtr<XmlAttribute>& newNode, const SharedPtr<XmlAttribute>& refNode);
    /// Inserts the specified attribute immediately after the specified reference attribute.
    /// @param newNode The attribute to insert.
    /// @param refNode The reference attribute. @p newNode is placed after the @p refNode.
    /// @returns The XmlAttribute to insert into the collection.
    /// @throws ArgumentException The @p newNode was created from a document different from the one that created this collection.
    /// Or the @p refNode is not a member of this collection.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> InsertAfter(const SharedPtr<XmlAttribute>& newNode, const SharedPtr<XmlAttribute>& refNode);
    /// Removes the specified attribute from the collection.
    /// @param node The attribute to remove.
    /// @returns The node removed or @c nullptr if it is not found in the collection.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> Remove(const SharedPtr<XmlAttribute>& node);
    /// Removes the attribute corresponding to the specified index from the collection.
    /// @param i The index of the node to remove. The first node has index 0.
    /// @returns Returns @c nullptr if there is no attribute at the specified index.
    ASPOSECPP_SHARED_API SharedPtr<XmlAttribute> RemoveAt(int32_t i);
    /// Removes all attributes from the collection.
    ASPOSECPP_SHARED_API void RemoveAll();
    /// Copies all the XmlAttribute objects from this collection into the given array.
    /// @param array The array that is the destination of the objects copied from this collection.
    /// @param index The index in the array where copying begins.
    ASPOSECPP_SHARED_API void CopyTo(const ArrayPtr<SharedPtr<XmlAttribute>>& array, int32_t index);

protected:

    /// @cond
    XmlAttributeCollection(const SharedPtr<XmlNode>& parent);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAttributeCollection, CODEPORTING_ARGS(SharedPtr<XmlNode> parent));

    int32_t FindNodeOffset(const SharedPtr<XmlAttribute>& node);
    int32_t FindNodeOffsetNS(const SharedPtr<XmlAttribute>& node);
    ASPOSECPP_SHARED_API const SharedPtr<XmlNode>& AddNode(const SharedPtr<XmlNode>& node) override;
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> InsertNodeAt(int32_t i, SharedPtr<XmlNode> node) override;
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveNodeAt(int32_t i) override;
    void Detach(const SharedPtr<XmlAttribute>& attr);
    void InsertParentIntoElementIdAttrMap(const SharedPtr<XmlAttribute>& attr);
    void RemoveParentFromElementIdAttrMap(const SharedPtr<XmlAttribute>& attr);
    int32_t RemoveDuplicateAttribute(const SharedPtr<XmlAttribute>& attr);
    bool PrepareParentInElementIdAttrMap(const String& attrPrefix, const String& attrLocalName);
    void ResetParentInElementIdAttrMap(const String& oldVal, const String& newVal);
    SharedPtr<XmlAttribute> InternalAppendAttribute(const SharedPtr<XmlAttribute>& node);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlAttributeCollection();

};

} // namespace Xml
} // namespace System


