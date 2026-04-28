/// @file net/cookie_container.h
#pragma once

#include <system/collections/dictionary.h>
#include <system/collections/icomparer.h>
#include <system/collections/keyvalue_pair.h>
#include <system/collections/sorted_list.h>
#include <system/object.h>

#include <net/cookie.h>
#include <net/cookie_collection.h>

namespace System { namespace Net {

/// Used to match the cookie name and specification.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HeaderVariantInfo : public System::Object
{
    /// This type.
    typedef HeaderVariantInfo ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the cookie's name.
    /// @returns The cookie's name.
    ASPOSECPP_SHARED_API String get_Name();
    /// Returns the cookie's specification.
    /// @returns The cookie's specification.
    ASPOSECPP_SHARED_API CookieVariant get_Variant();

    /// Constructs a new instance.
    /// @param name The cookie's name.
    /// @param variant The cookie's specification.
    ASPOSECPP_SHARED_API HeaderVariantInfo(String name, CookieVariant variant);
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HeaderVariantInfo();

private:
    /// The cookie's name.
    String _name;
    /// The cookie's specification.
    CookieVariant _variant;
};

/// Represents the list of the CookieCollection class instances.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS PathList : public System::Object
{
    /// This type.
    typedef PathList ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

private:
    /// Used to compare the PathList-class instances.
    class PathListComparer final : public System::Collections::Generic::IComparer<System::String>
    {
        /// This type.
        typedef PathListComparer ThisType;
        /// Parent type.
        typedef System::Collections::Generic::IComparer<System::String> BaseType;

        /// Base types.
        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        /// RTTI information.
        RTTI_INFO_DECL();

    public:
        /// The 'singleton' implementation. Always returns the same instance of this class.
        /// @returns The instance of this class.
        static System::SharedPtr<PathList::PathListComparer> StaticInstance;

    private:
        /// @copydoc System::Collections::Generic::IComparer::Compare
        int32_t Compare(args_type x, args_type y) const override;
    };

public:
    /// Returns the number of items.
    /// @returns The number of items.
    ASPOSECPP_SHARED_API int32_t get_Count() const;
    /// Returns the object through which the collection is being synchronized.
    /// @returns The object through which the collection is being synchronized.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> get_SyncRoot() const;

    /// Creates a new instance.
    /// @returns A newly created instance.
    ASPOSECPP_SHARED_API static System::SharedPtr<PathList> Create();
    /// Returns the number of cookies of all collection items.
    /// @returns The number of cookies of all collection items.
    ASPOSECPP_SHARED_API int32_t GetCookiesCount();

    /// Gets the cookie collection by specified path.
    /// @param s The path.
    /// @returns The cookie collection by specified path.
    ASPOSECPP_SHARED_API System::SharedPtr<CookieCollection> idx_get(String s);
    /// Sets the cookie collection by specified path.
    /// @param s The path.
    /// @param value The cookie collection to set.
    ASPOSECPP_SHARED_API void idx_set(String s, System::SharedPtr<CookieCollection> value);

    /// Returns the enumerator for the current collection.
    /// @returns The enumerator for the current collection.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::IEnumerator<
        Collections::Generic::KeyValuePair<String, System::SharedPtr<CookieCollection>>>>
        GetEnumerator();

private:
    /// An internal collection of paths and corresponding CookieCollection-class instances.
    System::SharedPtr<Collections::Generic::SortedList<String, System::SharedPtr<CookieCollection>>> _list;

    /// Constructs a new instance.
    /// @param list A collection that will be used to initialize a new instance.
    PathList(System::SharedPtr<Collections::Generic::SortedList<String, System::SharedPtr<CookieCollection>>> list);
    MEMBER_FUNCTION_MAKE_OBJECT(PathList, CODEPORTING_ARGS(System::SharedPtr<Collections::Generic::SortedList<String, System::SharedPtr<CookieCollection>>> list), CODEPORTING_ARGS(list));
};

/// Provides a container for the CookieCollection-class instances.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS CookieContainer : public System::Object
{
    /// This type.
    typedef CookieContainer ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The maximum number of collection items.
    ASPOSECPP_SHARED_API static const int32_t DefaultCookieLimit;
    /// The maximum number of collection items per domain.
    ASPOSECPP_SHARED_API static const int32_t DefaultPerDomainCookieLimit;
    /// The maximum cookie size.
    ASPOSECPP_SHARED_API static const int32_t DefaultCookieLengthLimit;

    /// Gets the collection capacity.
    /// @returns The collection capacity.
    ASPOSECPP_SHARED_API int32_t get_Capacity();
    /// Sets the collection capacity.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Capacity(int32_t value);
    /// Returns the number of the collection's items.
    /// @returns The number of the collection's items.
    ASPOSECPP_SHARED_API int32_t get_Count();
    /// Gets the maximum cookie size.
    /// @returns The maximum cookie size.
    /// @remarks A new cookie will be truncated when its size exceeds the maximum cookie size.
    ASPOSECPP_SHARED_API int32_t get_MaxCookieSize();
    /// Sets the maximum cookie size.
    /// @param value The value that must be set.
    /// @remarks A new cookie will be truncated when its size exceeds the maximum cookie size.
    ASPOSECPP_SHARED_API void set_MaxCookieSize(int32_t value);
    /// Gets the collection capacity per domain.
    /// @returns The collection capacity per domain.
    ASPOSECPP_SHARED_API int32_t get_PerDomainCapacity();
    /// Sets the collection capacity per domain.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_PerDomainCapacity(int32_t value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API CookieContainer();
    /// Constructs a new instance.
    /// @param capacity The collection capacity.
    ASPOSECPP_SHARED_API CookieContainer(int32_t capacity);
    /// Constructs a new instance.
    /// @param capacity The collection capacity.
    /// @param perDomainCapacity The collection capacity per domain.
    /// @param maxCookieSize The maximum cookie size.
    ASPOSECPP_SHARED_API CookieContainer(int32_t capacity, int32_t perDomainCapacity, int32_t maxCookieSize);

    /// Adds a cookie to the collection.
    /// @param cookie The cookie to add.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<Cookie> cookie);
    /// Adds a cookie to the collection.
    /// @param cookie The cookie to add.
    /// @param throwOnError A value that indicates if an exception will be thrown when an error occurs.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<Cookie> cookie, bool throwOnError);
    /// Copies cookies from the specified collection to the current one.
    /// @param cookies The collection from which cookies will be copied.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<CookieCollection> cookies);
    /// Checks if the specified domain is localhost.
    /// @param host The domain to check.
    /// @returns True when the specified domain is localhost, otherwise false.
    ASPOSECPP_SHARED_API bool IsLocalDomain(String host);
    /// Adds a cookie for the specified URI.
    /// @param uri An URI of the cookie.
    /// @param cookie The cookie to add.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<Uri> uri, System::SharedPtr<Cookie> cookie);
    /// Copies cookies from the specified collection for the specified URI to the current collection.
    /// @param uri An URI of the cookie.
    /// @param cookies A cookie collection from which cookies must be copied.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<Uri> uri, System::SharedPtr<CookieCollection> cookies);
    /// Copies cookies from the specified HTTP header for the specified URI.
    /// @internal
    ASPOSECPP_SHARED_API System::SharedPtr<CookieCollection> CookieCutter(System::SharedPtr<Uri> uri, String headerName,
                                                                          String setCookieHeader, bool isThrow);
    /// Returns a collection of cookies that are associated with the specified URI.
    /// @param uri The URI for which cookies will be searched.
    /// @returns A collection of cookies that are associated with the specified URI.
    ASPOSECPP_SHARED_API System::SharedPtr<CookieCollection> GetCookies(System::SharedPtr<Uri> uri);
    /// Returns a collection of cookies that are associated with the specified URI.
    /// @param uri An URI for which cookies will be searched.
    /// @returns A collection of cookies that are associated with the specified URI.
    /// @internal
    ASPOSECPP_SHARED_API System::SharedPtr<CookieCollection> InternalGetCookies(System::SharedPtr<Uri> uri);
    /// Return an HTTP header that contains cookies associated with the specified URI.
    /// @param uri An URI for which header name will be built.
    /// @returns An HTTP header that contains cookies associated with the specified URI.
    ASPOSECPP_SHARED_API String GetCookieHeader(System::SharedPtr<Uri> uri);
    /// Return an HTTP header that contains cookies associated with the specified URI.
    /// @param uri An URI for which header name will be built.
    /// @param optCookie2 The output parameter where a cookie with the maximum supported version will be assigned.
    /// @returns An HTTP header that contains cookies associated with the specified URI.
    ASPOSECPP_SHARED_API String GetCookieHeader(System::SharedPtr<Uri> uri, String& optCookie2);
    /// Copies cookies from the specified header to the collection and associates them with the specified URI.
    /// @param uri The URI.
    /// @param cookieHeader The header that contains cookies.
    ASPOSECPP_SHARED_API void SetCookies(System::SharedPtr<Uri> uri, String cookieHeader);

private:
    /// The collection of the HeaderVariantInfo-class instances.
    static System::ArrayPtr<HeaderVariantInfo> s_headerInfo;
    /// Contains domains and PathList-class instances associated with them.
    System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<PathList>>> _domainTable;
    /// The maximum cookie size.
    int32_t _maxCookieSize;
    /// The container capacity.
    int32_t _maxCookies;
    /// The capacity per domain.
    int32_t _maxCookiesPerDomain;
    /// The number of items.
    int32_t _count;
    /// The local domain name.
    String _fqdnMyDomain;

    /// Removes expired cookies by specified domain name.
    /// @param domain The domain name. All container items will be checked when @p domain equals to nullptr.
    /// @returns True when the operation is completed successfully, otherwise false.
    bool AgeCookies(String domain);
    /// Removes cookies from the collection and returns the number of removed cookies.
    /// @param cc The collection from which expired cookies must be removed.
    /// @returns The number of removed cookies.
    int32_t ExpireCollection(System::SharedPtr<CookieCollection> cc);
    /// Updated the specified cookie collection using the specified parameters.
    /// @param uri The URI.
    /// @param isSecure The value that indicates if cookies that can be sent only with https:// requests must be added.
    /// @param port The TCP port.
    /// @param cookies The collection that will be updated.
    /// @param domainAttribute The collection of domain attributes.
    /// @param matchOnlyPlainCookie Unused.
    void BuildCookieCollectionFromDomainMatches(System::SharedPtr<Uri> uri, bool isSecure, int32_t port,
                                                System::SharedPtr<CookieCollection> cookies,
                                                System::SharedPtr<Collections::Generic::List<String>> domainAttribute,
                                                bool matchOnlyPlainCookie);
    /// Merges the specified collections.
    /// @param destination The collection to which cookies will be added.
    /// @param source The collection from which cookies will be taken.
    /// @param port The TCP port.
    /// @param isSecure The value that indicates if cookies that can be sent only with https:// requests must be added.
    /// @param isPlainOnly The value that indicates if only cookies with the plain cookie specification must be added.
    void MergeUpdateCollections(System::SharedPtr<CookieCollection> destination,
                                System::SharedPtr<CookieCollection> source, int32_t port, bool isSecure,
                                bool isPlainOnly);

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}} // namespace System::Net
