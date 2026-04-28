/// @file xml/xpath/xpath_node_type.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace XPath {

/// Defines the XPath node types that can be returned from the XPathNavigator class.
enum class XPathNodeType
{
    /// The root node of the XML document or node tree.
    Root,
    /// An element, such as <tt>\<element></tt>.
    Element,
    /// An attribute, such as @c id='123'.
    Attribute,
    /// A namespace, such as @c xmlns="namespace".
    Namespace,
    /// The text content of a node.
    /// Equivalent to the Document Object Model (DOM) Text and CDATA node types.
    /// Contains at least one character.
    Text,
    /// A node with white space characters and @c xml:space set to @c preserve.
    SignificantWhitespace,
    /// A node with only white space characters and no significant white space.
    /// White space characters are @c '\\x20', @c '\\x0d', @c '\\x0a', @c '\\x09'.
    Whitespace,
    /// A processing instruction, such as <tt><?pi test?></tt>.
    /// This does not include XML declarations, which are not visible to the XPathNavigator class.
    ProcessingInstruction,
    /// A comment, such as <tt><!-- my comment --></tt>.
    Comment,
    /// Any of the XPathNodeType node types.
    All
};

} // namespace XPath
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XPath::XPathNodeType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XPath::XPathNodeType, const char_t*>, 10>& values();
};
/// @endcond


