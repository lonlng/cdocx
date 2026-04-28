/// @file net/cache/request_cache_policy.h
#pragma once

#include <system/date_time.h>
#include <system/enum.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/timespan.h>

namespace System { namespace Net { namespace Cache {

/// The enum describes cache settings applicable for any WebRequest.
enum class RequestCacheLevel
{
    /// Satisfies a request for a resource either by using the cached copy of the resource or by sending a request for
    /// the resource to the server.
    Default = 0,
    /// Satisfies a request by using the server. No entries are taken from the cache.
    BypassCache = 1,
    /// Satisfies a request for a resource only from the cache. WebException will be thrown when a resource is not in
    /// the client cache.
    CacheOnly = 2,
    /// Satisfies a request for a resource from the cache if the resource is available, otherwise sends a request to the
    /// server.
    CacheIfAvailable = 3,
    /// Using a resource local copy if the client timestamp is the same as the timestamp of the resource on the server.
    /// Otherwise, a resource is downloaded from a server.
    Revalidate = 4,
    /// A resource is always downloaded from the server.
    Reload = 5,
    /// Never satisfies a request by using resources from the cache and does not cache resources.
    NoCacheNoStore = 6
};

/// Common request cache policy used for caching of Http, FTP, etc.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RequestCachePolicy : public System::Object
{
    /// This type.
    typedef RequestCachePolicy ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the specified RequestCacheLevel value.
    /// @returns The specified RequestCacheLevel value.
    ASPOSECPP_SHARED_API RequestCacheLevel get_Level();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API RequestCachePolicy();
    /// Construct a new instance with the specified RequestCacheLevel value.
    /// @param level The RequestCacheLevel value.
    ASPOSECPP_SHARED_API RequestCachePolicy(RequestCacheLevel level);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    /// The RequestCacheLevel value.
    RequestCacheLevel m_Level;
};

/// The enum describes cache settings for HTTP
enum class HttpRequestCacheLevel
{
    /// Satisfies a request for a resource either by using the cached copy of the resource or by sending a request for
    /// the resource to the server.
    Default = 0,
    /// Satisfies a request by using the server.
    BypassCache = 1,
    /// Always uses the client cache to get a resource.
    CacheOnly = 2,
    /// Satisfies a request for a resource from the cache if the resource is available, otherwise sends a request to the
    /// server.
    CacheIfAvailable = 3,
    /// Using a resource local copy if the client timestamp is the same as the timestamp of the resource on the server.
    /// Otherwise, a resource is downloaded from a server.
    Revalidate = 4,
    /// A resource is always downloaded from the server.
    Reload = 5,
    /// Never satisfies a request by using resources from the cache and does not cache resources.
    NoCacheNoStore = 6,
    /// Satisfies a request for a resource either from the local computer's cache or from a remote cache on the LAN.
    CacheOrNextCacheOnly = 7,
    /// Satisfies a request by using the server or a cache other than the local cache.
    Refresh = 8
};

/// CacheAgeControl is used to specify preferences with respect of cached item age and freshness.
enum class HttpCacheAgeControl
{
    /// For internal use only.
    None = 0x0,
    /// Content can be taken from the cache if the time remaining before expiration is greater than or equal to the
    /// time specified with this value.
    MinFresh = 0x1,
    /// Content can be taken from the cache until it is older than the age specified with this value.
    MaxAge = 0x2,
    /// Content can be taken from the cache after it has expired until the time specified with this value elapses.
    MaxStale = 0x4,
    /// MaxAge and MinFresh.
    MaxAgeAndMinFresh = 0x3,
    /// MaxAge and MaxStale.
    MaxAgeAndMaxStale = 0x6
};

/// HTTP cache policy that expresses RFC2616 HTTP caching semantic
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class HttpRequestCachePolicy : public System::Net::Cache::RequestCachePolicy
{
    /// This type.
    typedef HttpRequestCachePolicy ThisType;
    /// Parent type.
    typedef System::Net::Cache::RequestCachePolicy BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the specified HttpRequestCacheLevel value.
    /// @returns The specified HttpRequestCacheLevel value.
    ASPOSECPP_SHARED_API HttpRequestCacheLevel get_Level() const;
    /// Gets the time when resources stored in the cache must be revalidated.
    /// @returns The time when resources stored in the cache must be revalidated.
    ASPOSECPP_SHARED_API DateTime get_CacheSyncDate() const;
    /// Gets the time in the UTC format when resources stored in the cache must be revalidated. For internal use only.
    /// @returns The time in the UTC format when resources stored in the cache must be revalidated.
    ASPOSECPP_SHARED_API DateTime get_InternalCacheSyncDateUtc() const;
    /// Gets the max age permitted for a resource.
    /// @returns The max age permitted for a resource.
    ASPOSECPP_SHARED_API TimeSpan get_MaxAge() const;
    /// Gets the min age permitted for a resource.
    /// @returns The min age permitted for a resource.
    ASPOSECPP_SHARED_API TimeSpan get_MinFresh() const;
    /// Gets the maximum staleness value that is permitted for a resource.
    /// @returns The maximum staleness value that is permitted for a resource.
    ASPOSECPP_SHARED_API TimeSpan get_MaxStale() const;

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpRequestCachePolicy();
    /// Constructs a new instance.
    /// @param level The caching behavior for resources.
    ASPOSECPP_SHARED_API HttpRequestCachePolicy(HttpRequestCacheLevel level);
    /// Constructs a new instance.
    /// @param cacheAgeControl Controls the caching behavior for resources.
    /// @param ageOrFreshOrStale An amount of time.
    ASPOSECPP_SHARED_API HttpRequestCachePolicy(HttpCacheAgeControl cacheAgeControl, TimeSpan ageOrFreshOrStale);
    /// Constructs a new instance.
    /// @param cacheAgeControl Controls the caching behavior for resources.
    /// @param maxAge The max age permitted for resources.
    /// @param freshOrStale An amount of time.
    ASPOSECPP_SHARED_API HttpRequestCachePolicy(HttpCacheAgeControl cacheAgeControl, TimeSpan maxAge, TimeSpan freshOrStale);
    /// Constructs a new instance.
    /// @param cacheSyncDate The time when resources stored in the cache must be revalidated.
    ASPOSECPP_SHARED_API HttpRequestCachePolicy(DateTime cacheSyncDate);
    /// Constructs a new instance.
    /// @param cacheAgeControl Controls the caching behavior for resources.
    /// @param maxAge The max age permitted for resources.
    /// @param freshOrStale An amount of time.
    /// @param cacheSyncDate The time when resources stored in the cache must be revalidated.
    ASPOSECPP_SHARED_API HttpRequestCachePolicy(HttpCacheAgeControl cacheAgeControl, TimeSpan maxAge, TimeSpan freshOrStale,
                           DateTime cacheSyncDate);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    /// The resources cache.
    static System::SharedPtr<HttpRequestCachePolicy> BypassCache;
    /// The value that indicates the caching behavior for resources.
    HttpRequestCacheLevel m_Level;
    /// The last synchronization date and time in the UTC format.
    DateTime m_LastSyncDateUtc;
    /// The max age permitted for resources.
    TimeSpan m_MaxAge;
    /// The min age permitted for resources.
    TimeSpan m_MinFresh;
    /// The maximum staleness value that is permitted for a resource.
    TimeSpan m_MaxStale;

    /// Returns the corresponding RequestCacheLevel value for the specified HttpRequestCacheLevel value.
    /// @param level The value to map.
    /// @returns The corresponding RequestCacheLevel enumeration value.
    static RequestCacheLevel MapLevel(HttpRequestCacheLevel level);

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}}} // namespace System::Net::Cache

/// Specialization System::Net::Cache::RequestCacheLevel; contains mapping of enum constants to their string
/// representations.
template <>
struct EnumMetaInfo<System::Net::Cache::RequestCacheLevel>
{
    static const std::array<std::pair<System::Net::Cache::RequestCacheLevel, const char_t*>, 7>& values();
};
/// Specialization System::Net::Cache::HttpRequestCacheLevel; contains mapping of enum constants to their string
/// representations.
template <>
struct EnumMetaInfo<System::Net::Cache::HttpRequestCacheLevel>
{
    static const std::array<std::pair<System::Net::Cache::HttpRequestCacheLevel, const char_t*>, 9>& values();
};
