/// @file net/web/services/soap.h
#pragma once
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Web { namespace Services {

/// Contains the string constants of SOAP.
class Soap
{
public:
    /// Contains the names of the SOAP attributes.
    class Attribute
    {
    public:
        /// The string representation of the 'mustUnderstand' attribute name.
        static const String MustUnderstand;
        /// The string representation of the 'actor' attribute name.
        static const String Actor;
        /// The string representation of the 'encodingStyle' attribute name.
        static const String EncodingStyle;
        /// The string representation of the 'lang' attribute name.
        static const String Lang;
        /// The string representation of the 'conformsTo' attribute name.
        static const String ConformsTo;

        /// The default constructor is deleted.
        Attribute() = delete;
    };

    /// Contains the names of the SOAP elements.
    class Element
    {
    public:
        /// The string representation of the 'Envelope' element name.
        static const String Envelope;
        /// The string representation of the 'Header' element name.
        static const String Header;
        /// The string representation of the 'Body' element name.
        static const String Body;
        /// The string representation of the 'Fault' element name.
        static const String Fault;
        /// The string representation of the 'faultactor' element name.
        static const String FaultActor;
        /// The string representation of the 'faultcode' element name.
        static const String FaultCode;
        /// The string representation of the 'detail' element name.
        static const String FaultDetail;
        /// The string representation of the 'faultstring' element name.
        static const String FaultString;
        /// The string representation of the 'StackTrace' element name.
        static const String StackTrace;
        /// The string representation of the 'Message' element name.
        static const String Message;
        /// The string representation of the 'Claim' element name.
        static const String Claim;

        /// The default constructor is deleted.
        Element() = delete;
    };

    /// Contains the names of the SOAP codes.
    class Code
    {
    public:
        /// The string representation of the 'Server' SOAP code.
        static const String Server;
        /// The string representation of the 'VersionMismatch' SOAP code.
        static const String VersionMismatch;
        /// The string representation of the 'MustUnderstand' SOAP code.
        static const String MustUnderstand;
        /// The string representation of the 'Client' SOAP code.
        static const String Client;

        /// The default constructor is deleted.
        Code() = delete;
    };

public:
    /// The value of the 'namespace' attribute.
    static const String XmlNamespace;
    /// The value of the 'xmlns:soapenc' attribute.
    static const String Encoding;
    /// The value of the 'xmlns:soap' attribute.
    static const String Namespace;
    /// The value of the 'xmlns:wsi' attribute.
    static const String ConformanceClaim;
    /// The conformance claim URI.
    static const String BasicProfile1_1;
    /// The string representation of the 'SOAPAction' attribute name.
    static const String Action;
    /// The string representation of the 'Array' suffix.
    static const String ArrayType;
    /// The SOAP prefix.
    static const String Prefix;
    /// The WS-I prefix.
    static const String ClaimPrefix;
    /// The string representation of the 'application/dime' MIME type.
    static const String DimeContentType;
    /// The string representation of the SOAP content type.
    static const String SoapContentType;

    /// The default constructor is deleted.
    Soap() = delete;
};

/// Contains the string constants of SOAP version 1.2.
class Soap12 final
{
public:
    /// Contains the names of the attributes of SOAP version 1.2.
    class Attribute
    {
    public:
        /// The string representation of the 'qname' attribute name.
        static const String UpgradeEnvelopeQname;
        /// The string representation of the 'role' attribute name.
        static const String Role;
        /// The string representation of the 'relay' attribute name.
        static const String Relay;

        /// The default constructor is deleted.
        Attribute() = delete;
    };

    /// Contains the names of the elements of SOAP version 1.2.
    class Element final
    {
    public:
        /// The string representation of the 'Upgrade' element name.
        static const String Upgrade;
        /// The string representation of the 'SupportedEnvelope' element name.
        static const String UpgradeEnvelope;
        /// The string representation of the 'Role' element name.
        static const String FaultRole;
        /// The string representation of the 'Reason' element name.
        static const String FaultReason;
        /// The string representation of the 'Text' element name.
        static const String FaultReasonText;
        /// The string representation of the 'Code' element name.
        static const String FaultCode;
        /// The string representation of the 'Node' element name.
        static const String FaultNode;
        /// The string representation of the 'Value' element name.
        static const String FaultCodeValue;
        /// The string representation of the 'Subcode' element name.
        static const String FaultSubcode;
        /// The string representation of the 'Detail' element name.
        static const String FaultDetail;

        /// The default constructor is deleted.
        Element() = delete;
    };

    /// Contains the names of the codes of SOAP version 1.2.
    class Code final
    {
    public:
        /// The string representation of the 'VersionMismatch' SOAP version 1.2 code.
        static const String VersionMismatch;
        /// The string representation of the 'MustUnderstand' SOAP version 1.2 code.
        static const String MustUnderstand;
        /// The string representation of the 'DataEncodingUnknown' SOAP version 1.2 code.
        static const String DataEncodingUnknown;
        /// The string representation of the 'Sender' SOAP version 1.2 code.
        static const String Sender;
        /// The string representation of the 'Receiver' SOAP version 1.2 code.
        static const String Receiver;
        /// The string representation of the 'ProcedureNotPresent' SOAP version 1.2 code.
        static const String RpcProcedureNotPresentSubcode;
        /// The string representation of the 'BadArguments' SOAP version 1.2 code.
        static const String RpcBadArgumentsSubcode;
        /// The string representation of the 'MissingID' SOAP version 1.2 code.
        static const String EncodingMissingIDFaultSubcode;
        /// The string representation of the 'UntypedValue' SOAP version 1.2 code.
        static const String EncodingUntypedValueFaultSubcode;

        /// The default constructor is deleted.
        Code() = delete;
    };

public:
    /// The value of the 'xmlns:soapenv' attribute.
    static const String Namespace;
    /// The value of the 'xmlns:SOAP-ENC' attribute.
    static const String Encoding;
    /// The value of the 'xmlns:rpc' attribute.
    static const String RpcNamespace;
    /// The SOAP version 1.2 prefix.
    static const String Prefix;

    /// The default constructor is deleted.
    Soap12() = delete;
};

}}} // namespace System::Web::Services
