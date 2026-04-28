/// @file xml/xml_comment.h

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

/// Represents the content of an XML comment.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlComment : public XmlCharacterData
{
    typedef XmlComment ThisType;
    typedef XmlCharacterData BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlComment>;

private:
    /// @cond
    friend class XmlDocument;
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns For comment nodes, the value is @c \#comment.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For comment nodes, the value is @c \#comment.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns For comment nodes, the value is XmlNodeType::Comment.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// Because comment nodes do not have children, the cloned node always includes the text content,
    /// regardless of the parameter setting.
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter.
    /// Because comment nodes do not have children, this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    /// @endcond

    /// Initializes a new instance of the XmlComment class.
    /// @param comment The content of the comment element.
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlComment(const String& comment, const SharedPtr<XmlDocument>& doc);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlComment, CODEPORTING_ARGS(const String& comment, const SharedPtr<XmlDocument>& doc));

    virtual ASPOSECPP_SHARED_API ~XmlComment();

};

} // namespace Xml
} // namespace System


