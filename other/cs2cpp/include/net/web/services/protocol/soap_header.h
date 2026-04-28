/// @file net/web/services/protocol/soap_header.h
#pragma once

#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <xml/xml_element.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Represents content of the SOAP header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ABSTRACT SoapHeader : public System::Object
{
public:
    /// Gets the URI of the SOAP header recipient when SOAP version 1.1 is used.
    /// @returns The URI of the SOAP header recipient when SOAP version 1.1 is used.
    ASPOSECPP_SHARED_API String get_Actor();
    /// Sets the URI of the SOAP header recipient when SOAP version 1.1 is used.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Actor(String value);
    /// Gets a value that indicates if the SOAP header is properly processed.
    /// @returns A value that indicates if the SOAP header is properly processed.
    ASPOSECPP_SHARED_API bool get_DidUnderstand();
    /// Sets a value that indicates if the SOAP header is properly processed.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_DidUnderstand(bool value);
    /// Gets a value of the 'mustUnderstand' attribute when SOAP version 1.1 is used.
    /// @returns A value of the 'mustUnderstand' attribute when SOAP version 1.1 is used.
    ASPOSECPP_SHARED_API String get_EncodedMustUnderstand();
    /// Sets a value of the 'mustUnderstand' attribute when SOAP version 1.1 is used.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_EncodedMustUnderstand(String value);
    /// Gets a value that indicates if the SOAP header must be understood.
    /// @returns A value that indicates if the SOAP header must be understood.
    ASPOSECPP_SHARED_API bool get_MustUnderstand();
    /// Sets a value that indicates if the SOAP header must be understood.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MustUnderstand(bool value);
    /// Gets a value of the 'mustUnderstand' attribute when SOAP version 1.2 is used.
    /// @returns A value of the 'mustUnderstand' attribute when SOAP version 1.2 is used.
    ASPOSECPP_SHARED_API String get_EncodedMustUnderstand12();
    /// Sets a value of the 'mustUnderstand' attribute when SOAP version 1.2 is used.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_EncodedMustUnderstand12(String value);
    /// Gets a string representation of the 'relay' attribute value.
    /// @returns A string representation of the 'relay' attribute value.
    ASPOSECPP_SHARED_API String get_EncodedRelay();
    /// Sets a string representation of the 'relay' attribute value.
    /// @param value The value that must be set.
    /// @remarks Possible values: '0', 'false', '1' and 'true'.
    ASPOSECPP_SHARED_API void set_EncodedRelay(String value);
    /// Gets a value of the 'relay' attribute.
    /// @returns A value of the 'relay' attribute.
    ASPOSECPP_SHARED_API bool get_Relay();
    /// Sets a value of the 'relay' attribute.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Relay(bool value);
    /// Gets the URI of the SOAP header recipient when SOAP version 1.2 is used.
    /// @returns The URI of the SOAP header recipient when SOAP version 1.2 is used.
    ASPOSECPP_SHARED_API String get_Role();
    /// Sets the URI of the SOAP header recipient when SOAP version 1.2 is used.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Role(String value);

    /// Constructs a new instance.
    /// @param elem An XML element used to initialize a new instance.
    ASPOSECPP_SHARED_API SoapHeader(System::SharedPtr<Xml::XmlElement> elem);

protected:
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API SoapHeader();

private:
    /// The URI of the SOAP header recipient when SOAP version 1.1 is used.
    String actor;
    /// A value that indicates if the SOAP header is properly proceed.
    bool didUnderstand;
    /// A value that indicates if the SOAP header must be understood.
    bool mustUnderstand;
    /// The URI of the SOAP header recipient when SOAP version 1.2 is used.
    String role;
    /// A value of the 'relay' attribute.
    bool relay;
};

}}}} // namespace System::Web::Services::Protocols
