/// @file xml/xml_cdata_section.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_character_data.h>


/// @cond
namespace System
{
class String;
namespace Xml
{
class XmlDocument;
class XmlLoader;
class XmlNode;
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

/// Represents a CDATA section.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlCDataSection : public XmlCharacterData
{
    typedef XmlCDataSection ThisType;
    typedef XmlCharacterData BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlCDataSection>;

private:
    /// @cond
    friend class XmlDocument;
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns For CDATA nodes, the name is @c \#cdata-section.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For CDATA nodes, the local name is @c \#cdata-section.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns The node type. For CDATA nodes, the value is XmlNodeType::CDATA.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the text node that immediately precedes this node.
    /// @returns Returns XmlNode.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_PreviousText() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// Because CDATA nodes do not have children, regardless of the parameter setting,
    /// the cloned node will always include the data content.
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves the children of the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal() override;
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    ASPOSECPP_SHARED_API bool get_IsText() override;
    /// @endcond

    /// Initializes a new instance of the XmlCDataSection class.
    /// @param data String that contains character data.
    /// @param doc XmlDocument object.
    ASPOSECPP_SHARED_API XmlCDataSection(const String& data, const SharedPtr<XmlDocument>& doc);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlCDataSection, CODEPORTING_ARGS(const String& data, const SharedPtr<XmlDocument>& doc));

    virtual ASPOSECPP_SHARED_API ~XmlCDataSection();

};

} // namespace Xml
} // namespace System


