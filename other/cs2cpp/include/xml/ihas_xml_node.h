/// @file xml/ihas_xml_node.h

#pragma once

#include <system/object.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlNode;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Enables a class to return an XmlNode from the current context or position.
class ASPOSECPP_SHARED_CLASS IHasXmlNode : public virtual System::Object
{
    typedef IHasXmlNode ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the XmlNode for the current position.
    /// @returns The XmlNode for the current position.
    virtual SharedPtr<XmlNode> GetNode() = 0;

};

} // namespace Xml
} // namespace System


