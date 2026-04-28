/// @file xml/xml_node_type.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the type of node.
enum class XmlNodeType
{
    /// This is returned by the XmlReader if a @c Read method has not been called.
    None,
    /// An element (for example, <tt>\<item></tt>).
    Element,
    /// An attribute (for example, <tt>id='123'</tt>).
    Attribute,
    /// The text content of a node. A XmlNodeType::Text node cannot have any child nodes.
    /// It can appear as the child node of the XmlNodeType::Attribute, XmlNodeType::DocumentFragment,
    /// XmlNodeType::Element, and XmlNodeType::EntityReference nodes.
    Text,
    /// A CDATA section (for example, <tt><![CDATA[my escaped text]]></tt>).
    CDATA,
    /// A reference to an entity (for example, <tt>&amp;num;</tt>).
    EntityReference,
    /// An entity declaration (for example, <tt><!ENTITY...></tt>).
    Entity,
    /// A processing instruction (for example, <tt><?pi test?></tt>).
    ProcessingInstruction,
    /// A comment (for example, <tt><!-- my comment --></tt>).
    Comment,
    /// A document object that, as the root of the document tree, provides access to the entire XML document.
    Document,
    /// The document type declaration, indicated by the following tag (for example, <tt><!DOCTYPE...></tt>).
    DocumentType,
    /// A document fragment.
    DocumentFragment,
    /// A notation in the document type declaration (for example, <tt><!NOTATION...></tt>).
    Notation,
    /// White space between markup.
    Whitespace,
    /// White space between markup in a mixed content model or white space within the <tt>xml:space="preserve"</tt> scope.
    SignificantWhitespace,
    /// An end element tag (for example, <tt></item></tt>).
    EndElement,
    /// Returned when XmlReader gets to the end of the entity replacement as a result of a call to XmlReader::ResolveEntity.
    EndEntity,
    /// The XML declaration (for example, <tt><?xml version='1.0'?></tt>).
    /// The XmlNodeType::XmlDeclaration node must be the first node in the document.
    /// It cannot have children.
    /// It is a child of the XmlNodeType::Document node.
    /// It can have attributes that provide version and encoding information.
    XmlDeclaration
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlNodeType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlNodeType, const char_t*>, 18>& values();
};
/// @endcond


