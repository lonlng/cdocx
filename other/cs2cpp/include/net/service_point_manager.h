/// @file net/service_point_manager.h
#pragma once

#include <cstdint>
#include <system/enum_helpers.h>
#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/iweb_proxy.h>
#include <net/secure_protocols/ssl_enum_types.h>
#include <net/secure_protocols/ssl_stream.h>

namespace System { namespace Net {

/// Enumerates the security protocol types.
enum class SecurityProtocolType
{
    /// The default system value must be used.
    SystemDefault = 0,
    /// The SSL 3.0 protocol.
    Ssl3 = 48,
    /// The TLS 1.0 protocol.
    Tls = 192,
    /// The TLS 1.1 protocol.
    Tls11 = 768,
    /// The TLS 1.2 protocol.
    Tls12 = 3072
};

/// @cond
/// Declaration of template arithmetic operators for values of the DecompressionMethods enum type.
DECLARE_ENUM_OPERATORS(System::Net::SecurityProtocolType);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

class ICertificatePolicy;

/// Manages the lifecycle stages (creating, maintaining, and deleting) of the ServicePoint class instances.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ServicePointManager : public System::Object
{
    /// This type.
    typedef ServicePointManager ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The default number of non-persistent connections.
    static ASPOSECPP_SHARED_API const int32_t DefaultNonPersistentConnectionLimit;
    /// The default number of persistent connections.
    static ASPOSECPP_SHARED_API const int32_t DefaultPersistentConnectionLimit;

    /// Gets the security protocol type used by the ServicePoint-class instances that are managed by the current
    /// instance.
    /// @returns The security protocol type used by the ServicePoint-class instances that are managed by the current
    /// instance.
    static ASPOSECPP_SHARED_API SecurityProtocolType get_SecurityProtocol();
    /// Sets the security protocol type used by the ServicePoint-class instances that are managed by the current
    /// instance.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_SecurityProtocol(SecurityProtocolType value);
    /// Gets the maximum number of the ServicePoint-class instances that can be managed by the current instance.
    /// @returns The maximum number of the ServicePoint-class instances that can be managed by the current instance.
    static ASPOSECPP_SHARED_API int32_t get_MaxServicePoints();
    /// Sets the maximum number of the ServicePoint-class instances that can be managed by the current instance.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_MaxServicePoints(int32_t value);
    /// Gets the maximum number of concurrent connections that are allowed by the ServicePoint-class instances.
    /// @returns The maximum number of concurrent connections that are allowed by the ServicePoint-class instances.
    static ASPOSECPP_SHARED_API int32_t get_DefaultConnectionLimit();
    /// Sets the maximum number of concurrent connections that are allowed by the ServicePoint-class instances.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_DefaultConnectionLimit(int32_t value);
    /// Gets the maximum idle time of the ServicePoint-class instances.
    /// @returns The maximum idle time of the ServicePoint-class instances.
    static ASPOSECPP_SHARED_API int32_t get_MaxServicePointIdleTime();
    /// Sets the maximum idle time of the ServicePoint-class instances.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_MaxServicePointIdleTime(int32_t value);
    /// Gets a value that indicates if the ServicePoint-class instances use the Nagle algorithm.
    /// @returns A value that indicates if the ServicePoint-class instances use the Nagle algorithm.
    static ASPOSECPP_SHARED_API bool get_UseNagleAlgorithm();
    /// Sets a value that indicates if the ServicePoint-class instances use the Nagle algorithm.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_UseNagleAlgorithm(bool value);
    /// Gets a value that indicates if the ServicePoint-class instances use the 100-Continue behavior.
    /// @returns A value that indicates if the ServicePoint-class instances use the 100-Continue behavior.
    static ASPOSECPP_SHARED_API bool get_Expect100Continue();
    /// Sets a value that indicates if the ServicePoint-class instances use the 100-Continue behavior.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_Expect100Continue(bool value);
    /// Gets a value that indicates if a DNS resolution rotates among the applicable IP addresses.
    /// @returns A value that indicates if a DNS resolution rotates among the applicable IP addresses.
    static ASPOSECPP_SHARED_API bool get_EnableDnsRoundRobin();
    /// Sets a value that indicates if a DNS resolution rotates among the applicable IP addresses.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_EnableDnsRoundRobin(bool value);
    /// Gets a timeout in milliseconds during which a DNS resolution is considered valid.
    /// @returns A timeout in milliseconds during which a DNS resolution is considered valid.
    static ASPOSECPP_SHARED_API int32_t get_DnsRefreshTimeout();
    /// Sets a timeout in milliseconds during which a DNS resolution is considered valid.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_DnsRefreshTimeout(int32_t value);
    /// Gets a certificate policy.
    /// @returns A certificate policy.
    static ASPOSECPP_SHARED_API System::SharedPtr<ICertificatePolicy> get_CertificatePolicy();
    /// Sets a certificate policy.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_CertificatePolicy(System::SharedPtr<ICertificatePolicy> value);
    /// Gets the callback that is used to validate a server certificate.
    /// @returns The callback that is used to validate a server certificate.
    static ASPOSECPP_SHARED_API Security::RemoteCertificateValidationCallback get_ServerCertificateValidationCallback();
    /// Sets the callback that is used to validate a server certificate.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void
        set_ServerCertificateValidationCallback(Security::RemoteCertificateValidationCallback value);
    /// Gets a value that indicates if the output connections sockets use the 'SO_REUSE_UNICASTPORT' option.
    /// @returns A value that indicates if the output connections sockets use the 'SO_REUSE_UNICASTPORT' option.
    static ASPOSECPP_SHARED_API bool get_ReusePort();
    /// Sets a value that indicates if the output connections sockets use the 'SO_REUSE_UNICASTPORT' option.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_ReusePort(bool value);
    /// Gets a value that indicates if the certificate must be checked against the certificate authority revocation
    /// list.
    /// @returns A value that indicates if the certificate must be checked against the certificate authority revocation
    /// list.
    static ASPOSECPP_SHARED_API bool get_CheckCertificateRevocationList();
    /// Sets a value that indicates if the certificate must be checked against the certificate authority revocation
    /// list.
    /// @param value The value to set.
    static ASPOSECPP_SHARED_API void set_CheckCertificateRevocationList(bool value);
    /// Returns the encryption policy that is used by the current instance.
    /// @returns The encryption policy that is used by the current instance.
    static ASPOSECPP_SHARED_API System::Net::Security::EncryptionPolicy get_EncryptionPolicy();

    /// Sets the value that indicates if the 'Keep-Alive' option is enabled.
    /// @param enabled A value that indicates if the 'Keep-Alive' option is enabled.
    /// @param keepAliveTime A timeout in milliseconds after which the first 'Keep-Alive' packet will be sent.
    /// @param keepAliveInterval A timeout in milliseconds between sending 'Keep-Alive' packets.
    static ASPOSECPP_SHARED_API void SetTcpKeepAlive(bool enabled, int32_t keepAliveTime, int32_t keepAliveInterval);

private:
    /// The callback that is used to validate a server certificate.
    static ASPOSECPP_SHARED_API Security::RemoteCertificateValidationCallback s_ServerCertValidationCallback;
};
}} // namespace System::Net

DECLARE_USING_ENUM_OPERATORS(System::Net);
