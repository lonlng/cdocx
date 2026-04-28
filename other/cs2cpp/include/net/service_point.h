/// @file net/service_point.h
#pragma once

#include <security/cryptography/x509_certificates/x509_certificate.h>
#include <system/date_time.h>
#include <system/multicast_delegate.h>
#include <system/shared_ptr.h>
#include <system/uri.h>
#include <system/version.h>

#include <net/ip_end_point.h>

namespace System { namespace Net {

class ServicePoint;
using BindIPEndPoint = System::MulticastDelegate<System::SharedPtr<IPEndPoint>(System::SharedPtr<ServicePoint>,
                                                                               System::SharedPtr<IPEndPoint>, int32_t)>;

/// Provides HTTP connection management.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ServicePoint : public System::Object
{
    /// This type.
    typedef ServicePoint ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the delegate that is used to associate local IPEndPoint with the current instance.
    /// @returns The delegate that is used to associate local IPEndPoint with the current instance.
    ASPOSECPP_SHARED_API BindIPEndPoint get_BindIPEndPointDelegate();
    /// Sets the delegate that is used to associate local IPEndPoint with the current instance.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BindIPEndPointDelegate(BindIPEndPoint value);
    /// Gets a timeout in milliseconds after which active ServicePoint will be closed.
    /// @returns A timeout in milliseconds after which active ServicePoint will be closed.
    ASPOSECPP_SHARED_API int32_t get_ConnectionLeaseTimeout();
    /// Sets a timeout in milliseconds after which active ServicePoint will be closed.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ConnectionLeaseTimeout(int32_t value);
    /// Returns the server URI to which the current instance connects.
    /// @returns The server URI to which the current instance connects.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_Address();
    /// Gets an amount of time in milliseconds after which an idle connection will be closed.
    /// @returns A n amount of time in milliseconds after which an idle connection will be closed.
    ASPOSECPP_SHARED_API int32_t get_MaxIdleTime();
    /// Sets an amount of time in milliseconds after which an idle connection will be closed.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MaxIdleTime(int32_t value);
    /// Gets a value that indicates if the Nagle algorithm is used by connections managed by the current instance.
    /// @returns A value that indicates if the Nagle algorithm is used by connections managed by the current instance.
    ASPOSECPP_SHARED_API bool get_UseNagleAlgorithm();
    /// Sets a value that indicates if the Nagle algorithm is used by connections managed by the current instance.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_UseNagleAlgorithm(bool value);
    /// Gets the size of the receive buffer.
    /// @returns The size of the receive buffer.
    ASPOSECPP_SHARED_API int32_t get_ReceiveBufferSize();
    /// Sets the size of the receive buffer.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ReceiveBufferSize(int32_t value);
    /// Gets a value that indicates if the 100-Continue behavior is used.
    /// @returns A value that indicates if the 100-Continue behavior is used.
    ASPOSECPP_SHARED_API bool get_Expect100Continue();
    /// Sets a value that indicates if the 100-Continue behavior is used.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Expect100Continue(bool value);
    /// Returns a date and time of the latest connection to a host.
    /// @returns A date and time of the latest connection to a host.
    ASPOSECPP_SHARED_API DateTime get_IdleSince();
    /// Returns the HTTP version.
    /// @returns The HTTP version.
    virtual ASPOSECPP_SHARED_API Version get_ProtocolVersion();
    /// Returns the connection name.
    /// @returns The connection name.
    ASPOSECPP_SHARED_API String get_ConnectionName();
    /// Gets the maximum number of connections that are allowed by the current instance.
    /// @returns The maximum number of connections that are allowed by the current instance.
    ASPOSECPP_SHARED_API int32_t get_ConnectionLimit();
    /// Sets the maximum number of connections that are allowed by the current instance.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ConnectionLimit(int32_t value);
    /// Returns a number of opened connections.
    /// @returns A number of opened connections.
    ASPOSECPP_SHARED_API int32_t get_CurrentConnections();
    /// Returns a certificate that is used by the current instance.
    /// @returns A certificate that is used by the current instance.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>
        get_Certificate();
    /// Returns the last client certificate.
    /// @returns The last client certificate.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>
        get_ClientCertificate();
    /// Returns a value that indicates if the current instance supports the pipeline connections.
    /// @returns A value that indicates if the current instance supports the pipeline connections.
    ASPOSECPP_SHARED_API bool get_SupportsPipelining();
    /// Closes and removes connections that belong to the specified connection group.
    /// @param connectionGroupName The name of the connection group.
    /// @returns True when connections are closed successfully, otherwise false.
    ASPOSECPP_SHARED_API bool CloseConnectionGroup(String connectionGroupName);
    /// Sets the value that indicates if the 'Keep-Alive' option is enabled.
    /// @param enabled A value that indicates if the 'Keep-Alive' option is enabled.
    /// @param keepAliveTime A timeout in milliseconds after which the first 'Keep-Alive' packet will be sent.
    /// @param keepAliveInterval A timeout in milliseconds between sending 'Keep-Alive' packets.
    ASPOSECPP_SHARED_API void SetTcpKeepAlive(bool enabled, int32_t keepAliveTime, int32_t keepAliveInterval);

private:
    /// A value that indicates if the 100-Continue behavior is used.
    bool m_Expect100Continue;
};
}} // namespace System::Net
