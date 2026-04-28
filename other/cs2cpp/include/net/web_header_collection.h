/// @file net/web_header_collection.h
#pragma once

#include <cstdint>
#include <system/array.h>
#include <system/collections/dictionary.h>
#include <system/collections/list.h>
#include <system/string.h>

#include <net/http_request_header.h>
#include <net/http_response_header.h>

namespace System { namespace Net {

/// Enumerates the types of the protocol headers collection.
enum class WebHeaderCollectionType : uint8_t
{
    /// A collection contains an unknown type elements.
    Unknown,
    /// A collection contains the headers of web requests.
    WebRequest,
    /// A collection contains the headers of web response.
    WebResponse
};

/// Represents the collection of the protocol headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS WebHeaderCollection : public Object
{
public:
    /// Adds the specified pair of the header name and the header value to the collection.
    /// @param header The header name.
    /// @param value The header value.
    ASPOSECPP_SHARED_API void Add(String header, String value);
    /// Adds the specified pair of the header and the header value to the collection.
    /// @param header The header.
    /// @param value The header value.
    ASPOSECPP_SHARED_API void Add(HttpResponseHeader header, String value);
    /// Adds the specified pair of the header and the header value to the collection.
    /// @param header The header.
    /// @param value The header value.
    ASPOSECPP_SHARED_API void Add(HttpRequestHeader header, String value);
    /// Gets the header value using the specified request's header.
    /// @param header The header.
    /// @returns The header value using the specified header.
    ASPOSECPP_SHARED_API String idx_get(HttpRequestHeader header);
    /// Sets the header value of the specified header.
    /// @param header The header.
    /// @param value The header value to set.
    ASPOSECPP_SHARED_API void idx_set(HttpRequestHeader header, String value);
    /// Gets the header value using the specified response's header.
    /// @param header The header.
    /// @returns The header value using the specified header.
    ASPOSECPP_SHARED_API String idx_get(HttpResponseHeader header);
    /// Sets the header value using the specified response's header.
    /// @param header The header.
    /// @param value The header value to set.
    ASPOSECPP_SHARED_API void idx_set(HttpResponseHeader header, String value);
    /// Gets the header value using the specified header name.
    /// @param name The header name.
    /// @returns The header value using the specified header name.
    ASPOSECPP_SHARED_API String idx_get(String name);
    /// Sets the header value using the specified header name.
    /// @param name The header name.
    /// @param value The header value to set.
    ASPOSECPP_SHARED_API void idx_set(String name, String value);
    /// Removes the header by the specified header name.
    /// @param name The header name.
    ASPOSECPP_SHARED_API void Remove(String name);
    /// Removes the specified response's header.
    /// @param header The header to remove.
    ASPOSECPP_SHARED_API void Remove(HttpResponseHeader header);
    /// Removes the specified request's header.
    /// @param header The header to remove.
    ASPOSECPP_SHARED_API void Remove(HttpRequestHeader header);
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API WebHeaderCollection();

    /// Returns a number of elements in the collection.
    /// @returns A number of elements in the collection.
    ASPOSECPP_SHARED_API int32_t get_Count() const;
    /// Returns a collection of header names that are stored in the collection.
    /// @returns A collection of header names that are stored in the collection.
    ASPOSECPP_SHARED_API System::ArrayPtr<String> AllKeys();
    /// Returns a collection of header names that are stored in the collection.
    /// @returns A collection of header names that are stored in the collection.
    ASPOSECPP_SHARED_API System::ArrayPtr<String> get_Keys();

    /// Returns a key at the specified index.
    /// @param index The index.
    /// @returns A key at the specified index.
    ASPOSECPP_SHARED_API String GetKey(int index);
    /// Returns the collection of the header values.
    /// @param header The header for which values must be returned.
    /// @returns The collection of the header values.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::String> GetValues(String header);

    /// Sets the value of the specified header.
    /// @param name The header name.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void Set(String name, String value);

    /// Tests whether the specified HTTP header can be set for the request.
    /// @param headerName The header name to test.
    /// @returns true if the header is restricted; otherwise false.
    ASPOSECPP_SHARED_API static bool IsRestricted(const String& headerName);

protected:
    /// Destructs the current instance.
    ASPOSECPP_SHARED_API ~WebHeaderCollection() override;

private:
    /// The approximate header line size.
    static const int32_t ApproxAveHeaderLineSize;
    /// The approximate quantity of the headers.
    static const int32_t ApproxHighAvgNumHeaders;
    /// The list that contains only headers' names.
    System::SharedPtr<Collections::Generic::List<String>> _entriesList;
    /// The dictionary that contains headers' names and values.
    System::SharedPtr<Collections::Generic::Dictionary<String, String>> _entriesDictionary;
    /// The array that contains headers' names that are stored in the collection.
    System::ArrayPtr<String> _allKeys;
    /// The collection type.
    WebHeaderCollectionType _type;

    /// Returns a value that indicates if the collection can store the request headers.
    /// @returns A value that indicates if the collection can store the request headers.
    bool get_AllowHttpRequestHeader();
    /// Returns a value that indicates if the collection can store the response headers.
    /// @returns A value that indicates if the collection can store the response headers.
    bool get_AllowHttpResponseHeader();

    /// Contains the characters used to trim a header value.
    static System::ArrayPtr<char16_t> s_httpTrimCharacters;

    /// Checks if the specified value contains invalid characters.
    /// @param value The value to check.
    /// @returns The trimmed value.
    /// @throws ArgumentException When the specified value contains invalid characters.
    static String CheckBadHeaderValueChars(String value);
    /// Checks if the specified name contains invalid characters.
    /// @param name The name to check.
    /// @returns The trimmed name.
    /// @throws ArgumentException When the specified name contains invalid characters.
    static String CheckBadHeaderNameChars(String name);
    /// Checks if the specified string contains non-ASCII characters.
    /// @param token The string to check.
    /// @returns True when the specified string contains non-ASCII characters, otherwise false.
    static bool ContainsNonAsciiChars(String token);
    /// Checks if internal fields are initialized.
    /// @returns True when internal fields are initialized, otherwise false.
    bool IsInitialized();
    /// Initializes internal fields if they weren't initialized before.
    void EnsureInitialized();
    /// Invalidates the internal cache.
    void InvalidateCachedArray();
    /// Converts the specified list to an array.
    /// @param list The list to convert.
    /// @returns The corresponding array.
    static System::ArrayPtr<String> ToArray(System::SharedPtr<Collections::Generic::List<String>> list);

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}} // namespace System::Net
