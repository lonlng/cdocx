/// @file net/http_status_description.h
#pragma once

#include <cstdint>
#include <net/http_status_code.h>
#include <system/array.h>
#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net {

/// Contains the utility methods to get the string representation of the HTTP status.
class HttpStatusDescription : public System::Object
{
    /// This type.
    typedef HttpStatusDescription ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a string description of the specified HTTP status code.
    /// @param code The status code.
    /// @returns A string description of the specified HTTP status code.
    static String Get(HttpStatusCode code);
    /// Returns a string description of the specified HTTP status code.
    /// @param code The status code.
    /// @returns A string description of the specified HTTP status code.
    static String Get(int32_t code);

    /// The deleted default constructor.
    HttpStatusDescription() = delete;

private:
    /// The internal array that stores string description of the status codes.
    static System::ArrayPtr<System::ArrayPtr<String>> s_httpStatusDescriptions;

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}} // namespace System::Net
