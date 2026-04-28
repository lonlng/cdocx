/// @file net/dns.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/iasyncresult.h>
#include <system/async_callback.h>
#include <system/array.h>

#include <net/ip_host_entry.h>
#include <net/ip_address.h>

namespace System {
namespace Net {

/// Provides methods to work with DNS.
class ASPOSECPP_SHARED_CLASS Dns : public System::Object
{
    /// This type.
    typedef Dns ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Creates a new IPHostEntry-class instance using the specified host name.
    /// @param hostName The host name.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> GetHostByName(String hostName);
    /// Creates a new IPHostEntry-class instance using the specified string representation of an IP address.
    /// @param address The string representation of an IP address.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> GetHostByAddress(String address);
    /// Creates a new IPHostEntry-class instance using the specified IP address.
    /// @param address The IP address.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> GetHostByAddress(System::SharedPtr<IPAddress> address);
    /// Returns the host name of the local machine.
    /// @returns The host name of the local machine.
    static ASPOSECPP_SHARED_API String GetHostName();
    /// Creates a new IPHostEntry-class instance using the specified host name.
    /// @param hostName A host name that is used to create a new instance of the IPHostEntry class.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> Resolve(String hostName);
    /// Initiates an asynchronous operation to create a new IPHostEntry-class instance using the specified host name.
    /// @param hostName A host name.
    /// @param requestCallback A callback to be called when the operation completes.
    /// @param stateObject User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    static ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetHostByName(String hostName, AsyncCallback requestCallback, System::SharedPtr<Object> stateObject);
    /// Waits until the specified asynchronous operation to create a new IPHostEntry-class instance completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous operation.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> EndGetHostByName(System::SharedPtr<IAsyncResult> asyncResult);
    /// Creates a new IPHostEntry-class instance using the specified string that contains a host name or IP address.
    /// @param hostNameOrAddress A string that contains a hostname or IP address.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> GetHostEntry(String hostNameOrAddress);
    /// Creates a new IPHostEntry-class instance using the specified IP address.
    /// @param address The IP address.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> GetHostEntry(System::SharedPtr<IPAddress> address);
    /// Returns a collection of IP addresses of the specified host name or IP address.
    /// @param hostNameOrAddress The string that contains a hostname or IP address.
    /// @returns A collection of IP addresses.
    static ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<IPAddress>> GetHostAddresses(String hostNameOrAddress);
    /// Initiates an asynchronous operation to create a new IPHostEntry-class instance using the specified string that
    /// contains a host name or IP address.
    /// @param hostNameOrAddress The string that contains a hostname or IP address.
    /// @param requestCallback A callback to be called when the operation completes.
    /// @param stateObject User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    static ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetHostEntry(String hostNameOrAddress, AsyncCallback requestCallback, System::SharedPtr<Object> stateObject);
    /// Initiates an asynchronous operation to create a new IPHostEntry-class instance using the specified IP address.
    /// @param address The IP address.
    /// @param requestCallback A callback to be called when the operation completes.
    /// @param stateObject User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    static ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetHostEntry(System::SharedPtr<IPAddress> address, AsyncCallback requestCallback, System::SharedPtr<Object> stateObject);
    /// Waits until the specified asynchronous operation to create a new IPHostEntry-class instance completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous operation.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> EndGetHostEntry(System::SharedPtr<IAsyncResult> asyncResult);
    /// Initiates an asynchronous operation to create a new IPHostEntry-class instance using the specified string that
    /// contains a host name or IP address.
    /// @param hostNameOrAddress A string that contains a hostname or IP address.
    /// @param requestCallback A callback to be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    static ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetHostAddresses(String hostNameOrAddress, AsyncCallback requestCallback, System::SharedPtr<Object> state);
    /// Waits until the specified asynchronous operation to create a new IPHostEntry-class instance completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous operation.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<IPAddress>> EndGetHostAddresses(System::SharedPtr<IAsyncResult> asyncResult);
    /// Initiates an asynchronous operation to create a new IPHostEntry-class instance using the specified host name.
    /// @param hostName A host name that is used to create a new instance of the IPHostEntry class.
    /// @param requestCallback A callback to be called when the operation completes.
    /// @param stateObject User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    static ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginResolve(String hostName, AsyncCallback requestCallback, System::SharedPtr<Object> stateObject);
    /// Waits until the specified asynchronous operation to create a new IPHostEntry-class instance completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous operation.
    /// @returns A newly created IPHostEntry-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPHostEntry> EndResolve(System::SharedPtr<IAsyncResult> asyncResult);

    /// The deleted default constructor.
    Dns() = delete;
};
} // namespace Net
} // namespace System
