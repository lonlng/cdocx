/// @file net/http_version.h
#pragma once

#include <system/object.h>
#include <system/version.h>

namespace System { namespace Net {

/// Contains versions of HTTP.
class ASPOSECPP_SHARED_CLASS HttpVersion
{
public:
    /// Represents an unknown version of the HTTP.
    static ASPOSECPP_SHARED_API Version Unknown;
    /// Represents HTTP version 1.0.
    static ASPOSECPP_SHARED_API Version Version10;
    /// Represents HTTP version 1.1.
    static ASPOSECPP_SHARED_API Version Version11;
    /// Represents HTTP version 2.0.
    static ASPOSECPP_SHARED_API Version Version20;

    /// The deleted default constructor.
    HttpVersion() = delete;
};

}} // namespace System::Net
