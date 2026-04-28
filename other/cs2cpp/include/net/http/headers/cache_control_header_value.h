/// @file net/http/headers/cache_control_header_value.h
#pragma once

#include <cstdint>
#include <system/action.h>
#include <system/collections/icollection.h>
#include <system/collections/list.h>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/text/string_builder.h>
#include <system/timespan.h>

#include <net/http/headers/object_collection.h>

namespace System { namespace Net { namespace Http { namespace Headers {

class NameValueHeaderValue;

/// Represents a value of the 'Cache-Control' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS CacheControlHeaderValue : public System::ICloneable
{
    /// This type.
    typedef CacheControlHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the value that determines if the client will accept a cached response.
    /// @returns The value that determines if the client will accept a cached response.
    ASPOSECPP_SHARED_API bool get_NoCache();
    /// Sets the value that determines if the client will accept a cached response.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_NoCache(bool value);
    /// Gets the collection of fieldnames in the 'no-cache' directive in the 'Cache-Control' header.
    /// @returns A collection of fieldnames in the 'no-cache' directive in the 'Cache-Control' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<String>> get_NoCacheHeaders();
    /// Gets the value that determines if a cache must not store any part of an HTTP request or response.
    /// @returns The value that determines if a cache must not store any part of an HTTP request or response.
    ASPOSECPP_SHARED_API bool get_NoStore();
    /// Sets the value that determines if a cache must not store any part of an HTTP request or response.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_NoStore(bool value);
    /// Gets the maximum age value in seconds that determines a time during which the client will accept a response.
    /// @returns The maximum age value in seconds that determines a time during which the client will accept a response.
    ASPOSECPP_SHARED_API Nullable<TimeSpan> get_MaxAge();
    /// Sets the maximum age value in seconds that determines a time during which the client will accept a response.
    /// @param value The maximum age that must be set.
    ASPOSECPP_SHARED_API void set_MaxAge(Nullable<TimeSpan> value);
    /// Gets the shared maximum age value in seconds that overrides the 'max-age' directive in the 'Cache-Control'.
    /// header or the 'Expires' header for a shared cache.
    /// @returns The shared maximum age value in seconds that overrides the 'max-age' directive in the 'Cache-Control'.
    /// header or the 'Expires' header for a shared cache.
    ASPOSECPP_SHARED_API Nullable<TimeSpan> get_SharedMaxAge();
    /// Sets the shared maximum age value in seconds that overrides the 'max-age' directive in the 'Cache-Control'.
    /// header or the 'Expires' header for a shared cache.
    /// @param value The shared maximum age that must be set.
    ASPOSECPP_SHARED_API void set_SharedMaxAge(Nullable<TimeSpan> value);
    /// Gets the value that determines if the client will accept the expired responses.
    /// @returns The value that determines if the client will accept the expired responses.
    ASPOSECPP_SHARED_API bool get_MaxStale();
    /// Sets the value that determines if the client will accept the expired responses.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MaxStale(bool value);
    /// Gets the value in seconds that determines the time during which the client will accept the expired responses.
    /// @returns The value in seconds that determines the time during which the client will accept the expired
    /// responses.
    ASPOSECPP_SHARED_API Nullable<TimeSpan> get_MaxStaleLimit();
    /// Sets the value in seconds that determines the time during which the client will accept the expired responses.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MaxStaleLimit(Nullable<TimeSpan> value);
    /// Gets the value that determines the freshness lifetime.
    /// @returns The value that determines the freshness lifetime.
    ASPOSECPP_SHARED_API Nullable<TimeSpan> get_MinFresh();
    /// Sets the value that determines the freshness lifetime.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MinFresh(Nullable<TimeSpan> value);
    /// Gets the value that determines if a cache or proxy must not change any part of the entity body.
    /// @returns The value that determines if a cache or proxy must not change any part of the entity body.
    ASPOSECPP_SHARED_API bool get_NoTransform();
    /// Sets the value that determines if a cache or proxy must not change any part of the entity body.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_NoTransform(bool value);
    /// Gets the value that determines if the client must use only cached entries.
    /// @returns The value that determines if the client must use only cached entries.
    ASPOSECPP_SHARED_API bool get_OnlyIfCached();
    /// Sets the value that determines if the client must use only cached entries.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_OnlyIfCached(bool value);
    /// Gets the value that determines if an HTTP response can be cached by any cache.
    /// @returns The value that determines if an HTTP response can be cached by any cache.
    ASPOSECPP_SHARED_API bool get_Public();
    /// Sets the value that determines if an HTTP response can be cached by any cache.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Public(bool value);
    /// Gets the value that determines if the HTTP response message or its part is intended for a single user and must
    /// not be cached by a shared cache.
    /// @returns The value that determines if the HTTP response message or its part is intended for a single user and
    /// must not be cached by a shared cache.
    ASPOSECPP_SHARED_API bool get_Private();
    /// Sets the value that determines if the HTTP response message or its part is intended for a single user and must
    /// not be cached by a shared cache.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Private(bool value);
    /// Gets the collection of fieldnames in the 'private' directive in the 'Cache-Control' header.
    /// @returns A collection of fieldnames in the 'private' directive in the 'Cache-Control' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<String>> get_PrivateHeaders();
    /// Gets the value that determines if the server requires revalidation of a cache entry when the it becomes stale.
    /// @returns The value that determines if the server requires revalidation of a cache entry when the it becomes
    /// stale.
    ASPOSECPP_SHARED_API bool get_MustRevalidate();
    /// Sets the value that determines if the server requires revalidation of a cache entry when the it becomes stale.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MustRevalidate(bool value);
    /// Gets the value that determines if the server requires revalidation of a cache entry when it becomes stale for
    /// the shared user agent caches.
    /// @returns The value that determines if the server requires revalidation of a cache entry when it becomes stale
    /// for the shared user agent caches.
    ASPOSECPP_SHARED_API bool get_ProxyRevalidate();
    /// Sets the value that determines if the server requires revalidation of a cache entry when it becomes stale for
    /// the shared user agent caches.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ProxyRevalidate(bool value);
    /// Returns the collection of the cache-extension tokens.
    /// @returns The collection of the cache-extension tokens.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<NameValueHeaderValue>>>
        get_Extensions();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API CacheControlHeaderValue();

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the CacheControlHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the CacheControlHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<CacheControlHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the CacheControlHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<CacheControlHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the CacheControlHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param storeValue A value that must be added to the parsed object.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetCacheControlLength(String input, int32_t startIndex,
                                         System::SharedPtr<CacheControlHeaderValue> storeValue,
                                         System::SharedPtr<CacheControlHeaderValue>& parsedValue);

private:
    /// The string representation of the 'max-age' directive in the 'Cache-Control' header.
    static const String maxAgeString;
    /// The string representation of the 'max-stale' directive in the 'Cache-Control' header.
    static const String maxStaleString;
    /// The string representation of the 'min-fresh' directive in the 'Cache-Control' header.
    static const String minFreshString;
    /// The string representation of the 'must-revalidate' directive in the 'Cache-Control' header.
    static const String mustRevalidateString;
    /// The string representation of the 'no-cache' directive in the 'Cache-Control' header.
    static const String noCacheString;
    /// The string representation of the 'no-store' directive in the 'Cache-Control' header.
    static const String noStoreString;
    /// The string representation of the 'no-transform' directive in the 'Cache-Control' header.
    static const String noTransformString;
    /// The string representation of the 'only-if-cached' directive in the 'Cache-Control' header.
    static const String onlyIfCachedString;
    /// The string representation of the 'private' directive in the 'Cache-Control' header.
    static const String privateString;
    /// The string representation of the 'proxy-revalidate' directive in the 'Cache-Control' header.
    static const String proxyRevalidateString;
    /// The string representation of the 'public' directive in the 'Cache-Control' header.
    static const String publicString;
    /// The string representation of the 's-maxage' directive in the 'Cache-Control' header.
    static const String sharedMaxAgeString;
    /// The delegate that is used to validate tokens.
    static Action<String> s_checkIsValidToken;
    /// Determines if the client will accept a cached response.
    bool _noCache;
    /// A collection of fieldnames in the 'no-cache' directive in the 'Cache-Control' header.
    System::SharedPtr<ObjectCollection<String>> _noCacheHeaders;
    /// Determines if a cache must not store any part of an HTTP request or response.
    bool _noStore;
    /// The maximum age value in seconds that determines a time during which the client will accept a response.
    Nullable<TimeSpan> _maxAge;
    /// The shared maximum age value in seconds that overrides the 'max-age' directive in the 'Cache-Control'.
    Nullable<TimeSpan> _sharedMaxAge;
    /// Determines if the client will accept the expired responses.
    bool _maxStale;
    /// The time in seconds during which the client will accept the expired responses.
    Nullable<TimeSpan> _maxStaleLimit;
    /// The freshness lifetime.
    Nullable<TimeSpan> _minFresh;
    /// Determines if a cache or proxy must not change any part of the entity body.
    bool _noTransform;
    /// Determines if the client must use only cached entries.
    bool _onlyIfCached;
    /// Determines if an HTTP response can be cached by any cache.
    bool _publicField;
    /// Determines if the HTTP response message or its part is intended for a single user and must not be cached by a
    /// shared cache.
    bool _privateField;
    /// A collection of fieldnames in the 'private' directive in the 'Cache-Control' header.
    System::SharedPtr<ObjectCollection<String>> _privateHeaders;
    /// Determines if the server requires revalidation of a cache entry when the it becomes stale.
    bool _mustRevalidate;
    /// Determines if the server requires revalidation of a cache entry when it becomes stale for the shared user agent
    /// caches.
    bool _proxyRevalidate;
    /// The collection of the cache-extension tokens.
    System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> _extensions;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    CacheControlHeaderValue(System::SharedPtr<CacheControlHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(CacheControlHeaderValue, CODEPORTING_ARGS(System::SharedPtr<CacheControlHeaderValue> source), CODEPORTING_ARGS(source));

    /// Tries to set the CacheControlHeaderValue values from the specified NameValueHeaderValue-class instance.
    /// @param cc The CacheControlHeaderValue class instance where values will be assigned.
    /// @param nameValueList The NameValueHeaderValue class instance from which values will be taken.
    /// @returns True when all values are successfully assigned, otherwise false.
    static bool TrySetCacheControlValues(
        System::SharedPtr<CacheControlHeaderValue> cc,
        System::SharedPtr<Collections::Generic::List<System::SharedPtr<NameValueHeaderValue>>> nameValueList);
    /// Tries to set a token value.
    /// @param nameValue A key-value pair that must be parsed.
    /// @param boolField The output parameter that stores the reference to the corresponding field of the current class
    /// instance.
    /// @returns True when the value is successfully assigned, otherwise false.
    static bool TrySetTokenOnlyValue(System::SharedPtr<NameValueHeaderValue> nameValue, bool& boolField);
    /// Tries to set a token value.
    /// @param nameValue A key-value pair that must be parsed.
    /// @param boolField The output parameter that stores the reference to the corresponding field of the current class
    /// instance.
    /// @param destination The output parameter where the value will be assigned.
    /// @returns True when the value is successfully assigned, otherwise false.
    static bool TrySetOptionalTokenList(System::SharedPtr<NameValueHeaderValue> nameValue, bool& boolField,
                                        System::SharedPtr<ObjectCollection<String>>& destination);
    /// Tries to parse and set a time span value.
    /// @param nameValue A key-value pair that must be parsed.
    /// @param timeSpan The output parameter where the value will be assigned.
    /// @returns True when the value is successfully assigned, otherwise false.
    static bool TrySetTimeSpan(System::SharedPtr<NameValueHeaderValue> nameValue, Nullable<TimeSpan>& timeSpan);
    /// Appends a value with a separator to the specified StringBuilder class instance.
    /// @param sb The StringBuilder class instance where the value must be appended.
    /// @param appendValue True when the value must be appended, otherwise false.
    /// @param value The value that must be appended.
    static void AppendValueIfRequired(System::SharedPtr<Text::StringBuilder> sb, bool appendValue, String value);
    /// Appends the specified value to the StringBuilder class instance.
    /// @param sb The StringBuilder class instance where the value must be appended.
    /// @param value The value that must be appended.
    static void AppendValueWithSeparatorIfRequired(System::SharedPtr<Text::StringBuilder> sb, String value);
    /// Appends multiple values to the StringBuilder class instance.
    /// @param sb The StringBuilder class instance where values must be appended.
    /// @param values The collection of values that must be appended.
    static void AppendValues(System::SharedPtr<Text::StringBuilder> sb,
                             System::SharedPtr<ObjectCollection<String>> values);
    /// Validates a string representation of a token.
    /// @param item A string representation of a token.
    /// @throws System::ArgumentException The exception is thrown when the specified string is empty.
    /// @throws System::FormatException The exception is thrown when the specified string contains not only a token
    /// value.
    static void CheckIsValidToken(String item);
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
