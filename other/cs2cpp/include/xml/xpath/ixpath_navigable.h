/// @file xml/xpath/ixpath_navigable.h

#pragma once

#include <system/object.h>


/// @cond
namespace System
{
namespace Xml
{
namespace XPath
{
class XPathNavigator;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

/// Provides an accessor to the XPathNavigator class.
class ASPOSECPP_SHARED_CLASS IXPathNavigable : public virtual System::Object
{
    typedef IXPathNavigable ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns a new XPathNavigator object.
    /// @returns An XPathNavigator object.
    virtual SharedPtr<XPathNavigator> CreateNavigator() = 0;

};

} // namespace XPath
} // namespace Xml
} // namespace System


