/// @file net/web/services/protocol/soap_exception.h
#pragma once

#include <system/exceptions.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <xml/xml_node.h>
#include <xml/xml_qualified_name.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

class SoapFaultSubCode;

class Details_SoapException;
using SoapException = System::ExceptionWrapper<Details_SoapException>;

/// Represents the exception thrown when method is called over SOAP and an error occurs.
/// Never create instances of this class manually. Use the SoapException class instead.
/// Never wrap the SoapException class instances into System::SmartPtr.
class Details_SoapException : public System::Details_SystemException
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    using BaseType = System::Details_SystemException;

public:
    /// A SOAP fault code that represents a client call that is formatted incorrectly or doesn't contain required
    /// information.
    static System::SharedPtr<Xml::XmlQualifiedName> ClientFaultCode;
    /// A namespace qualified local name in format 'namespace:localname'.
    static System::SharedPtr<Xml::XmlQualifiedName> DetailElementName;
    /// A SOAP fault code that indicates if the SOAP element marked by the 'MustUnderstand' attribute is not processed.
    static System::SharedPtr<Xml::XmlQualifiedName> MustUnderstandFaultCode;
    /// A SOAP fault code that represents an error occurred on the server.
    static System::SharedPtr<Xml::XmlQualifiedName> ServerFaultCode;
    /// A SOAP fault code that represents an invalid namespace.
    static System::SharedPtr<Xml::XmlQualifiedName> VersionMismatchFaultCode;

    /// Returns the code piece where the exception is thrown when SOAP version 1.1 is used.
    /// @returns The code piece where the exception is thrown.
    String get_Actor();
    /// Returns a namespace qualified local name in format 'namespace:localname' that specifies the SOAP fault code.
    /// @returns A namespace qualified local name in format 'namespace:localname' that specifies the SOAP fault code.
    System::SharedPtr<Xml::XmlQualifiedName> get_Code();
    /// Returns details about the thrown exception.
    /// @returns Details about the thrown exception.
    System::SharedPtr<Xml::XmlNode> get_Detail();
    /// Returns the language, which is used to localize exception properties.
    /// @returns The language, which is used to localize exception properties.
    String get_Lang();
    /// Returns the role of the XML web service that throws the exception.
    /// @returns The role of the XML web service that throws the exception.
    String get_Role();
    /// Returns optional information from the 'subcode' XML element.
    /// @returns Optional information from the 'subcode' XML element.
    System::SharedPtr<SoapFaultSubCode> get_SubCode();
    /// Returns the code piece where the exception is thrown when SOAP version 1.2 is used.
    /// @returns The code piece where the exception is thrown.
    String get_Node();

    /// Constructs a new instance.
    Details_SoapException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException, CODEPORTING_ARGS(String message, System::SharedPtr<Xml::XmlQualifiedName> code), CODEPORTING_ARGS(message, code));
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param innerException The inner exception.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, Exception innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            Exception innerException
        ),
        CODEPORTING_ARGS(message, code, innerException)
    );
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param actor The code piece where the exception is thrown.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException, CODEPORTING_ARGS(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor), CODEPORTING_ARGS(message, code, actor));
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param actor The code piece where the exception is thrown.
    /// @param innerException The inner exception.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor,
                          Exception innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            String actor,
            Exception innerException
        ),
        CODEPORTING_ARGS(message, code, actor, innerException)
    );
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param actor The code piece where the exception is thrown.
    /// @param detail Details about the thrown exception.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor,
                          System::SharedPtr<Xml::XmlNode> detail);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            String actor,
            System::SharedPtr<Xml::XmlNode> detail
        ),
        CODEPORTING_ARGS(message, code, actor, detail)
    );
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param actor The code piece where the exception is thrown.
    /// @param detail Details about the thrown exception.
    /// @param innerException The inner exception.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor,
                          System::SharedPtr<Xml::XmlNode> detail, Exception innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            String actor,
            System::SharedPtr<Xml::XmlNode> detail, Exception innerException
        ),
        CODEPORTING_ARGS(message, code, actor, detail, innerException)
    );
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param subcode Optional information from the 'subcode' XML element.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code,
                          System::SharedPtr<SoapFaultSubCode> subcode);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            System::SharedPtr<SoapFaultSubCode> subcode
        ),
        CODEPORTING_ARGS(message, code, subcode)
    );
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param actor The code piece where the exception is thrown.
    /// @param role The role of the XML web service that throws the exception.
    /// @param detail Details about the thrown exception.
    /// @param subcode Optional information from the 'subcode' XML element.
    /// @param innerException The inner exception.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor, String role,
                          System::SharedPtr<Xml::XmlNode> detail, System::SharedPtr<SoapFaultSubCode> subcode,
                          Exception innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            String actor,
            String role,
            System::SharedPtr<Xml::XmlNode> detail,
            System::SharedPtr<SoapFaultSubCode> subcode,
            Exception innerException
        ), CODEPORTING_ARGS(message, code, actor, role, detail, subcode, innerException)
    );
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param code The exception code.
    /// @param actor The code piece where the exception is thrown.
    /// @param role The role of the XML web service that throws the exception.
    /// @param lang The language, which is used to localize exception properties.
    /// @param detail Details about the thrown exception.
    /// @param subcode Optional information from the 'subcode' XML element.
    /// @param innerException The inner exception.
    Details_SoapException(String message, System::SharedPtr<Xml::XmlQualifiedName> code, String actor, String role,
                          String lang, System::SharedPtr<Xml::XmlNode> detail,
                          System::SharedPtr<SoapFaultSubCode> subcode, Exception innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SoapException,
        CODEPORTING_ARGS(
            String message,
            System::SharedPtr<Xml::XmlQualifiedName> code,
            String actor,
            String role,
            String lang,
            System::SharedPtr<Xml::XmlNode> detail,
            System::SharedPtr<SoapFaultSubCode> subcode,
            Exception innerException
        ), CODEPORTING_ARGS(message, code, actor, role, lang, detail, subcode, innerException)
    );

    /// Checks if the specified code is equal to the 'Client' SOAP fault code.
    /// @param code The SOAP fault code to check.
    /// @returns True when the specified code is equal to the 'Client' SOAP fault code, otherwise false.
    static bool IsClientFaultCode(System::SharedPtr<Xml::XmlQualifiedName> code);
    /// Checks if the specified code is equal to the 'MustUnderstand' SOAP fault code.
    /// @param code The SOAP fault code to check.
    /// @returns True when the specified code is equal to the 'MustUnderstand' SOAP fault code, otherwise false.
    static bool IsMustUnderstandFaultCode(System::SharedPtr<Xml::XmlQualifiedName> code);
    /// Checks if the specified code is equal to the 'Server' SOAP fault code.
    /// @param code The SOAP fault code to check.
    /// @returns True when the specified code is equal to the 'Server' SOAP fault code, otherwise false.
    static bool IsServerFaultCode(System::SharedPtr<Xml::XmlQualifiedName> code);
    /// Checks if the specified code is equal to the 'VersionMismatch' SOAP fault code.
    /// @param code The SOAP fault code to check.
    /// @returns True when the specified code is equal to the 'VersionMismatch' SOAP fault code, otherwise false.
    static bool IsVersionMismatchFaultCode(System::SharedPtr<Xml::XmlQualifiedName> code);

protected:
    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_SoapException>(self); }

private:
    /// The code piece where the exception is thrown.
    String actor;
    /// A namespace qualified local name in format 'namespace:localname' that specifies the SOAP fault code.
    System::SharedPtr<Xml::XmlQualifiedName> code;
    /// Details about the thrown exception.
    System::SharedPtr<Xml::XmlNode> detail;
    /// The language, which is used to localize exception properties.
    String lang;
    /// The role of the XML web service that throws the exception.
    String role;
    /// Optional information from the 'subcode' XML element.
    System::SharedPtr<SoapFaultSubCode> subcode;
};

}}}} // namespace System::Web::Services::Protocols
