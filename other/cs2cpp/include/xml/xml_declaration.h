/// @file xml/xml_declaration.h

#pragma once

#include <xml/xml_node_type.h>
#include <xml/xml_linked_node.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlDocument;
class XmlNode;
class XmlNodeReaderNavigator;
class XmlWriter;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents the XML declaration node <tt><?xml version='1.0'...?></tt>.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDeclaration : public XmlLinkedNode
{
    typedef XmlDeclaration ThisType;
    typedef XmlLinkedNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlDeclaration>;

private:
    /// @cond
    friend class XmlDocument;
    friend class XmlNodeReaderNavigator;
    /// @endcond

public:

    /// Returns the XML version of the document.
    /// @returns The value is always @c 1.0.
    ASPOSECPP_SHARED_API String get_Version();
    /// Returns the encoding level of the XML document.
    /// @returns The valid character encoding name.
    ///
    /// The most commonly supported character encoding names for XML are the following:
    /// <list type="table"><listheader><term> Category
    /// </term><description> Encoding Names
    /// </description></listheader><item><term> Unicode
    /// </term><description> UTF-8, UTF-16
    /// </description></item><item><term> ISO 10646
    /// </term><description> ISO-10646-UCS-2, ISO-10646-UCS-4
    /// </description></item><item><term> ISO 8859
    /// </term><description> ISO-8859-n (where "n" is a digit from 1 to 9)
    /// </description></item><item><term> JIS X-0208-1997
    /// </term><description> ISO-2022-JP, Shift_JIS, EUC-JP
    /// </description></item></list>
    /// This value is optional. If a value is not set, this method returns String::Empty.
    /// If an encoding attribute is not included, UTF-8 encoding is assumed when the document is written or saved out.
    ASPOSECPP_SHARED_API String get_Encoding();
    /// Sets the encoding level of the XML document.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Encoding(const String& value);
    /// Returns the value of the standalone attribute.
    /// @returns Valid values are @c yes if all entity declarations required by the XML document are contained within the document
    /// or @c no if an external document type definition (DTD) is required.
    /// If a standalone attribute is not present in the XML declaration, this method returns String::Empty.
    ASPOSECPP_SHARED_API String get_Standalone();
    /// Sets the value of the standalone attribute.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Standalone(const String& value);
    /// Returns the value of the XmlDeclaration.
    /// @returns The contents of the XmlDeclaration (that is, everything between <tt><?xml</tt> and <tt>?></tt>).
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Sets the value of the XmlDeclaration.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Value(String value) override;
    /// Returns the concatenated values of the XmlDeclaration.
    /// @returns The concatenated values of the XmlDeclaration (that is, everything between <tt><?xml</tt> and <tt>?></tt>).
    ASPOSECPP_SHARED_API String get_InnerText() override;
    /// Sets the concatenated values of the XmlDeclaration.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;
    /// Returns the qualified name of the node.
    /// @returns For XmlDeclaration nodes, the name is @c xml.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For XmlDeclaration nodes, the local name is @c xml.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the type of the current node.
    /// @returns For XmlDeclaration nodes, this value is XmlNodeType::XmlDeclaration.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node; @c false to clone only the node itself.
    /// Because XmlDeclaration nodes do not have children, the cloned node always includes the data value, regardless of the parameter setting.
    /// @returns The cloned node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves the children of the node to the specified XmlWriter.
    /// Because XmlDeclaration nodes do not have children, this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API void set_Version(const String& value);
    /// @endcond

    /// Initializes a new instance of the XmlDeclaration class.
    /// @param version The XML version; see the XmlDeclaration::get_Version method.
    /// @param encoding The encoding scheme; see the XmlDeclaration::get_Encoding method.
    /// @param standalone Indicates whether the XML document depends on an external DTD; see the XmlDeclaration::get_Standalone method.
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlDeclaration(const String& version, const String& encoding, const String& standalone, const SharedPtr<XmlDocument>& doc);

    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlDeclaration, CODEPORTING_ARGS(String version, String encoding, String standalone, SharedPtr<XmlDocument> doc));

    virtual ASPOSECPP_SHARED_API ~XmlDeclaration();

private:

    static const String YES;
    static const String NO;
    String _version;
    String _encoding;
    String _standalone;

    bool IsValidXmlVersion(const String& ver);

};

} // namespace Xml
} // namespace System


