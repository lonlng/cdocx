/// @file xml/xml_linked_node.h

#pragma once

#include <xml/xml_node.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlAttribute;
class XmlCharacterData;
class XmlDeclaration;
class XmlDocument;
class XmlDocumentType;
class XmlElement;
class XmlEntityReference;
class XmlProcessingInstruction;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Returns the node immediately preceding or following this node.
class ASPOSECPP_SHARED_CLASS XmlLinkedNode : public XmlNode
{
    typedef XmlLinkedNode ThisType;
    typedef XmlNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlLinkedNode>;

private:
    /// @cond
    friend class XmlAttribute;
    friend class XmlNode;
    friend class XmlCharacterData;
    friend class XmlDeclaration;
    friend class XmlDocument;
    friend class XmlDocumentType;
    friend class XmlElement;
    friend class XmlEntityReference;
    friend class XmlProcessingInstruction;
    /// @endcond

protected:

    /// @cond
    XmlLinkedNode* _prev;
    SharedPtr<XmlLinkedNode> _next;

    const SharedPtr<XmlLinkedNode>& get_next()
    {
        return _next;
    }

    void set_next(const SharedPtr<XmlLinkedNode>& value);
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_PreviousSiblingInternal() override;
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_NextSiblingInternal() override;

    XmlLinkedNode();
    XmlLinkedNode(const SharedPtr<XmlDocument>& doc);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlLinkedNode();

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
    const char* DBG_class_name() const override { return "XmlLinkedNode"; }
    #endif
    /// @endcond

};

} // namespace Xml
} // namespace System


