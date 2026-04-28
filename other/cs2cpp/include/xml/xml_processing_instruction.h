/// @file xml/xml_processing_instruction.h

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

/// Represents a processing instruction, which XML defines to keep processor-specific information in the text of the document.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlProcessingInstruction : public XmlLinkedNode
{
    typedef XmlProcessingInstruction ThisType;
    typedef XmlLinkedNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlProcessingInstruction>;

private:
    /// @cond
    friend class XmlDocument;
    friend class XmlLoader;
    /// @endcond

public:

    /// Returns the qualified name of the node.
    /// @returns For processing instruction nodes, this method returns the target of the processing instruction.
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the node.
    /// @returns For processing instruction nodes, this method returns the target of the processing instruction.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the value of the node.
    /// @returns The entire content of the processing instruction, excluding the target.
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Sets the value of the node.
    /// @param value The value to set.
    /// @throws ArgumentException Node is read-only.
    ASPOSECPP_SHARED_API void set_Value(String value) override;
    /// Returns the target of the processing instruction.
    /// @returns The target of the processing instruction.
    ASPOSECPP_SHARED_API String get_Target();
    /// Returns the content of the processing instruction, excluding the target.
    /// @returns The content of the processing instruction, excluding the target.
    ASPOSECPP_SHARED_API String get_Data();
    /// Sets the content of the processing instruction, excluding the target.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Data(const String& value);
    /// Returns the concatenated values of the node and all its children.
    /// @returns The concatenated values of the node and all its children.
    ASPOSECPP_SHARED_API String get_InnerText() override;
    /// Sets the concatenated values of the node and all its children.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;
    /// Returns the type of the current node.
    /// @returns For XmlProcessingInstruction nodes, this value is XmlNodeType::ProcessingInstruction.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;

    /// Creates a duplicate of this node.
    /// @param deep @c true to recursively clone the subtree under the specified node;
    /// @c false to clone only the node itself.
    /// @returns The duplicate node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> CloneNode(bool deep) override;
    /// Saves the node to the specified XmlWriter.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteTo(const SharedPtr<XmlWriter>& w) override;
    /// Saves all the children of the node to the specified XmlWriter.
    /// Because ProcessingInstruction nodes do not have children, this method has no effect.
    /// @param w The XmlWriter to which you want to save.
    ASPOSECPP_SHARED_API void WriteContentTo(const SharedPtr<XmlWriter>& w) override;

protected:

    /// @cond
    ASPOSECPP_SHARED_API String get_XPLocalName() override;
    ASPOSECPP_SHARED_API XPath::XPathNodeType get_XPNodeType() override;
    /// @endcond

    /// Initializes a new instance of the XmlProcessingInstruction class.
    /// @param target The target of the processing instruction; see the XmlProcessingInstruction::get_Target method.
    /// @param data The content of the instruction; see the XmlProcessingInstruction::get_Data method.
    /// @param doc The parent XML document.
    ASPOSECPP_SHARED_API XmlProcessingInstruction(const String& target, const String& data, const SharedPtr<XmlDocument>& doc);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlProcessingInstruction, CODEPORTING_ARGS(String target, String data, SharedPtr<XmlDocument> doc));

    virtual ASPOSECPP_SHARED_API ~XmlProcessingInstruction();

private:

    String _target;
    String _data;

};

} // namespace Xml
} // namespace System


