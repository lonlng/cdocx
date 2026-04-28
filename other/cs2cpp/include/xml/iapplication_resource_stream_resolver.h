/// @file xml/iapplication_resource_stream_resolver.h

#pragma once

#include <system/object.h>


/// @cond
namespace System
{
namespace IO
{
class Stream;
} // namespace IO
class Uri;
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents an application resource stream resolver.
class ASPOSECPP_SHARED_CLASS IApplicationResourceStreamResolver : public System::Object
{
    typedef IApplicationResourceStreamResolver ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns an application resource stream from the specified URI.
    /// @param relativeUri The relative URI.
    /// @returns An application resource stream.
    virtual SharedPtr<IO::Stream> GetApplicationResourceStream(SharedPtr<Uri> relativeUri) = 0;

};

} // namespace Xml
} // namespace System


