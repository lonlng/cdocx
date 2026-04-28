/// @file net/http/http_method.h
#pragma once

#include <cstdint>
#include <system/iequatable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http {

/// Represents an HTTP method.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpMethod : public System::IEquatable<System::SharedPtr<System::Net::Http::HttpMethod>>
{
    /// This type.
    typedef HttpMethod ThisType;
    /// Parent type.
    typedef System::IEquatable<System::SharedPtr<System::Net::Http::HttpMethod>> BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend bool operator==(System::SharedPtr<HttpMethod> left, System::SharedPtr<HttpMethod> right);
    friend bool operator!=(System::SharedPtr<HttpMethod> left, System::SharedPtr<HttpMethod> right);

public:
    /// Returns the 'GET' HTTP method.
    /// @returns The 'GET' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Get();
    /// Returns the 'PUT' HTTP method.
    /// @returns The 'PUT' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Put();
    /// Returns the 'POST' HTTP method.
    /// @returns The 'POST' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Post();
    /// Returns the 'DELETE' HTTP method.
    /// @returns The 'DELETE' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Delete();
    /// Returns the 'HEAD' HTTP method.
    /// @returns The 'HEAD' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Head();
    /// Returns the 'OPTIONS' HTTP method.
    /// @returns The 'OPTIONS' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Options();
    /// Returns the 'TRACE' HTTP method.
    /// @returns The 'TRACE' HTTP method.
    ASPOSECPP_SHARED_API static System::SharedPtr<HttpMethod> get_Trace();
    /// Returns a string representation of the HTTP method.
    /// @returns A string representation of the HTTP method.
    ASPOSECPP_SHARED_API String get_Method();

    /// Constructs a new instance.
    /// @param method A string representation of the HTTP method.
    ASPOSECPP_SHARED_API HttpMethod(String method);

    /// @copydoc System::IEquatable::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<HttpMethod> other) override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    /// A string representation of the HTTP method.
    String _method;
    /// The hash code.
    mutable int32_t _hashcode;
    /// The 'GET' HTTP method.
    static System::SharedPtr<HttpMethod> s_getMethod;
    /// The 'PUT' HTTP method.
    static System::SharedPtr<HttpMethod> s_putMethod;
    /// The 'POST' HTTP method.
    static System::SharedPtr<HttpMethod> s_postMethod;
    /// The 'DELETE' HTTP method.
    static System::SharedPtr<HttpMethod> s_deleteMethod;
    /// The 'HEAD' HTTP method.
    static System::SharedPtr<HttpMethod> s_headMethod;
    /// The 'OPTIONS' HTTP method.
    static System::SharedPtr<HttpMethod> s_optionsMethod;
    /// The 'TRACE' HTTP method.
    static System::SharedPtr<HttpMethod> s_traceMethod;

    /// Checks if the specified string contains only uppercase letters.
    /// @param value The string to check.
    /// @returns True when all characters of the specified string are uppercase letters, otherwise false.
    static bool IsUpperAscii(String value);
};

bool operator==(System::SharedPtr<HttpMethod> left, System::SharedPtr<HttpMethod> right);
bool operator!=(System::SharedPtr<HttpMethod> left, System::SharedPtr<HttpMethod> right);

}}} // namespace System::Net::Http
