/// @file xml/xml_text.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_character_data.h>
#include <cstdint>


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

/// Represents the text content of an element or attribute.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlText : public XmlCharacterData
{
    typedef XmlText ThisType;
    typedef XmlCharacterData BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlText>;

private:
    /// @cond
    friend class XmlDocument;
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns For text nodes, this method returns @c \#text.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For text nodes, this method returns @c \#text.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns For text nodes, this value is XmlNodeType::Text.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the value of the node.
    /// @returns The content of the text node.
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Sets the value of the node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Value(String value) override;
    /// Returns the text node that immediately precedes this node.
    /// @returns Returns XmlNode.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_PreviousText() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Splits the node into two nodes at the specified offset, keeping both in the tree as siblings.
    /// @param offset The offset at which to split the node.
    /// @returns The new node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlText> SplitText(int32_t offset);
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter.
    /// XmlText nodes do not have children, so this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_ParentNodeInternal() override;
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    ASPOSECPP_SHARED_API bool get_IsText() override;

    XmlText(const String& strData);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlText, CODEPORTING_ARGS(const String& strData));
    /// @endcond

    /// Initializes a new instance of the XmlText class.
    /// @param strData The content of the node; see the XmlText::get_Value method.
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlText(const String& strData, const SharedPtr<XmlDocument>& doc);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlText, CODEPORTING_ARGS(const String& strData, const SharedPtr<XmlDocument>& doc));

    virtual ASPOSECPP_SHARED_API ~XmlText();

};

} // namespace Xml
} // namespace System


