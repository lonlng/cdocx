/// @file xml/xml_document_type.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_linked_node.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class SchemaInfo;
} // namespace Schema
class XmlDocument;
class XmlLoader;
class XmlNamedNodeMap;
class XmlNode;
class XmlWriter;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents the document type declaration.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDocumentType : public XmlLinkedNode
{
    typedef XmlDocumentType ThisType;
    typedef XmlLinkedNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlDocumentType>;

private:
    /// @cond
    friend class XmlDocument;
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns For DocumentType nodes, this method returns the name of the document type.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For DocumentType nodes, this method returns the name of the document type.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns For DocumentType nodes, this value is XmlNodeType::DocumentType.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns a value indicating whether the node is read-only.
    /// @returns @c true if the node is read-only; otherwise, @c false.
    /// Because DocumentType nodes are read-only, this method always returns @c true.
    ASPOSECPP_SHARED_API bool get_IsReadOnly() override;
    /// Returns the collection of XmlEntity nodes declared in the document type declaration.
    /// @returns An XmlNamedNodeMap containing the XmlEntity nodes. The returned XmlNamedNodeMap is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNamedNodeMap> get_Entities();
    /// Returns the collection of XmlNotation nodes present in the document type declaration.
    /// @returns An XmlNamedNodeMap containing the XmlNotation nodes. The returned XmlNamedNodeMap is read-only.
    ASPOSECPP_SHARED_API SharedPtr<XmlNamedNodeMap> get_Notations();
    /// Returns the value of the public identifier on the DOCTYPE declaration.
    /// @returns The public identifier on the DOCTYPE. If there is no public identifier, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_PublicId();
    /// Returns the value of the system identifier on the DOCTYPE declaration.
    /// @returns The system identifier on the DOCTYPE. If there is no system identifier, @c nullptr is returned.
    ASPOSECPP_SHARED_API String get_SystemId();
    /// Returns the value of the document type definition (DTD) internal subset on the DOCTYPE declaration.
    /// @returns The DTD internal subset on the DOCTYPE. If there is no DTD internal subset, String::Empty is returned.
    ASPOSECPP_SHARED_API String get_InternalSubset();

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself. For document type nodes, the cloned node always includes the subtree,
    /// regardless of the parameter setting.
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter. For XmlDocumentType nodes, this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    bool get_ParseWithNamespaces();
    void set_ParseWithNamespaces(bool value);
    SharedPtr<System::Xml::Schema::SchemaInfo> get_DtdSchemaInfo();
    void set_DtdSchemaInfo(const SharedPtr<System::Xml::Schema::SchemaInfo>& value);
    /// @endcond

    /// Initializes a new instance of the XmlDocumentType class.
    /// @param name The qualified name; see the XmlDocumentType::get_Name method.
    /// @param publicId The public identifier; see the XmlDocumentType::get_PublicId method.
    /// @param systemId The system identifier; see the XmlDocumentType::get_SystemId method.
    /// @param internalSubset The DTD internal subset; see the XmlDocumentType::get_InternalSubset method.
    /// @param doc The parent document.
    ASPOSECPP_SHARED_API XmlDocumentType(const String& name, const String& publicId, const String& systemId, const String& internalSubset, const SharedPtr<XmlDocument>& doc);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlDocumentType, CODEPORTING_ARGS(String name, String publicId, String systemId, String internalSubset, SharedPtr<XmlDocument> doc));

    virtual ASPOSECPP_SHARED_API ~XmlDocumentType();

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
    const char* DBG_class_name() const override { return "XmlDocumentType"; }
    #endif
    /// @endcond

private:

    String _name;
    String _publicId;
    String _systemId;
    String _internalSubset;
    bool _namespaces;
    SharedPtr<XmlNamedNodeMap> _entities;
    SharedPtr<XmlNamedNodeMap> _notations;
    SharedPtr<System::Xml::Schema::SchemaInfo> _schemaInfo;

};

} // namespace Xml
} // namespace System


