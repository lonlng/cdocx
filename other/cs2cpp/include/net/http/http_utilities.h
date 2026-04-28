/// @file net/http/http_utilities.h
#pragma once

#include <system/action.h>
#include <system/diagnostics/debug.h>
#include <system/enum_helpers.h>
#include <system/exceptions.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/uri.h>
#include <system/version.h>

namespace System { namespace Net { namespace Http {

/// Contains the utility methods.
class HttpUtilities : public System::Object
{
    /// This type.
    typedef HttpUtilities ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The default HTTP version for sending requests.
    static Version DefaultRequestVersion;
    /// The default HTTP version for receiving responses.
    static Version DefaultResponseVersion;

    /// Checks if the specified URI is the HTTP URI.
    /// @param uri The URI to check.
    /// @returns True when the specified URI is the HTTP URI, otherwise false.
    static bool IsHttpUri(System::SharedPtr<Uri> uri);
};

}}} // namespace System::Net::Http
