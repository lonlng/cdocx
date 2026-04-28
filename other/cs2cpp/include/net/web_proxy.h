/// @file net/web_proxy.h
#pragma once
#include <cstdint>
#include <system/array.h>
#include <system/collections/list.h>
#include <system/runtime/serialization/serialization_info.h>
#include <system/runtime/serialization/streaming_context.h>
#include <system/string.h>
#include <system/text/regularexpressions/regex.h>

#include <net/ip_address.h>
#include <net/iweb_proxy.h>

namespace System { namespace Net {

/// Represents an http web-proxy server.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class WebProxy : public System::Net::IWebProxy
{
public:
    /// Gets the address of the current proxy server.
    /// @returns The address of the current proxy server.
    System::SharedPtr<Uri> get_Address();
    /// Sets the address of the current proxy server.
    /// @param value The address to set.
    void set_Address(System::SharedPtr<Uri> value);
    /// Gets a value that indicates if the proxy server must be used for local addresses.
    /// @returns A value that indicates if the proxy server must be used for local addresses.
    bool get_BypassProxyOnLocal();
    /// Sets a value that indicates if the proxy server must be used for local addresses.
    /// @param value A value to set.
    void set_BypassProxyOnLocal(bool value);
    /// Gets the list of addresses that do not use the proxy server.
    /// @returns The list of addresses that do not use the proxy server.
    System::ArrayPtr<String> get_BypassList();
    /// Sets the list of addresses that do not use the proxy server.
    /// @param value The list to set.
    void set_BypassList(System::ArrayPtr<String> value);
    /// Gets the credentials that are sent to the proxy server for authentication.
    /// @returns The credentials that are sent to the proxy server for authentication.
    System::SharedPtr<ICredentials> get_Credentials();
    /// Sets the credentials that are sent to the proxy server for authentication.
    /// @param value The credentials to set.
    void set_Credentials(System::SharedPtr<ICredentials> value);
    /// Gets a value that indicates if the default credentials must be sent with requests.
    /// @returns A value that indicates if the default credentials must be sent with requests.
    bool get_UseDefaultCredentials();
    /// Sets a value that indicates if the default credentials must be sent with requests.
    /// @param value A vault to set.
    void set_UseDefaultCredentials(bool value);

    /// Constructs a new instance.
    WebProxy();
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    WebProxy(System::SharedPtr<Uri> Address);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    /// @param BypassOnLocal A value that indicates if the proxy server must be used for local addresses.
    WebProxy(System::SharedPtr<Uri> Address, bool BypassOnLocal);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    /// @param BypassOnLocal A value that indicates if the proxy server must be used for local addresses.
    /// @param BypassList The list of addresses that do not use the proxy server.
    WebProxy(System::SharedPtr<Uri> Address, bool BypassOnLocal, System::ArrayPtr<String> BypassList);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    /// @param BypassOnLocal A value that indicates if the proxy server must be used for local addresses.
    /// @param BypassList The list of addresses that do not use the proxy server.
    /// @param Credentials The credentials that are sent to the proxy server for authentication.
    WebProxy(System::SharedPtr<Uri> Address, bool BypassOnLocal, System::ArrayPtr<String> BypassList,
             System::SharedPtr<ICredentials> Credentials);
    /// Constructs a new instance.
    /// @param Host The host name.
    /// @param Port The port number.
    WebProxy(String Host, int32_t Port);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    WebProxy(String Address);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    /// @param BypassOnLocal A value that indicates if the proxy server must be used for local addresses.
    WebProxy(String Address, bool BypassOnLocal);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    /// @param BypassOnLocal A value that indicates if the proxy server must be used for local addresses.
    /// @param BypassList The list of addresses that do not use the proxy server.
    WebProxy(String Address, bool BypassOnLocal, System::ArrayPtr<String> BypassList);
    /// Constructs a new instance.
    /// @param Address The proxy server address.
    /// @param BypassOnLocal A value that indicates if the proxy server must be used for local addresses.
    /// @param BypassList The list of addresses that do not use the proxy server.
    /// @param Credentials The credentials that are sent to the proxy server for authentication.
    WebProxy(String Address, bool BypassOnLocal, System::ArrayPtr<String> BypassList,
             System::SharedPtr<ICredentials> Credentials);

    /// Returns the proxied URI for a web request.
    /// @param destination The resource's URI.
    /// @returns The proxied URI.
    System::SharedPtr<Uri> GetProxy(System::SharedPtr<Uri> destination);
    /// Checks if the proxy server is not used for the specified URI.
    /// @param host The URI to check.
    /// @returns True when the proxy server is not used for the specified URI, otherwise false.
    bool IsBypassed(System::SharedPtr<Uri> host);
    /// Returns the proxy that uses the non-dynamic settings of the Internet Explorer.
    /// @returns The proxy that uses the non-dynamic settings of the Internet Explorer.
    static System::SharedPtr<WebProxy> GetDefaultProxy();

private:
    /// The collection of addresses for which the proxy server is not used.
    System::SharedPtr<Collections::Generic::List<String>> _bypassList;
    /// The collection of regular expressions.
    System::ArrayPtr<System::SharedPtr<Text::RegularExpressions::Regex>> _regExBypassList;
    /// The address of the current proxy server.
    System::SharedPtr<Uri> pr_Address;
    /// A value that indicates if the proxy server must be used for local addresses.
    bool pr_BypassProxyOnLocal;
    /// The credentials that are sent to the proxy server for authentication.
    System::SharedPtr<ICredentials> pr_Credentials;

    /// Creates the URI for the specified address.
    /// @param address The address that is used to initialize the URI-class instance.
    /// @returns A newly created URI-class instance.
    static System::SharedPtr<Uri> CreateProxyUri(String address);
    /// Updates the list of internal regular expressions.
    /// @param canThrow A value that indicates if an exception will be thrown when an error occurs.
    void UpdateRegExList(bool canThrow);
    /// Checks if the specified URI is matched against the internal collection of regular expressions.
    /// @param input The URI to check.
    /// @returns True when the specified URI is matched against the internal collection of regular expressions,
    /// otherwise false.
    bool IsMatchInBypassList(System::SharedPtr<Uri> input);
    /// Checks if the specified URI is a local address.
    /// @param host The URI to check.
    /// @returns True when the specified URI is a local address, otherwise false.
    bool IsLocal(System::SharedPtr<Uri> host);
    /// Checks if the specified IP address is a local one.
    /// @param ipAddress The IP address.
    /// @returns True when the specified IP address is a local one, otherwise false.
    static bool IsAddressLocal(System::SharedPtr<IPAddress> ipAddress);
};

}} // namespace System::Net
