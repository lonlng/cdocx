/// @file net/uri_scheme.h
#pragma once

#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net {

/// Represent the scheme for URI.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class UriScheme : public System::Object
{
    /// This type.
    typedef UriScheme ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The HTTP string representation.
    static const String Http;
    /// The HTTPS string representation.
    static const String Https;
    /// The WS string representation.
    static const String Ws;
    /// The WSS string representation.
    static const String Wss;
    /// The string that represents the scheme delimiter.
    static const String SchemeDelimiter;
};

}} // namespace System::Net
