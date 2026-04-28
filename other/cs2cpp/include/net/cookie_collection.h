/// @file net/cookie_collection.h
#pragma once

#include <system/collections/icollection.h>
#include <system/collections/ienumerator.h>
#include <system/collections/list.h>
#include <system/shared_ptr.h>

#include <net/cookie.h>

namespace System { namespace Net {

/// Represents a list of sorted cookies.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS CookieCollection : public System::Collections::Generic::ICollection<System::SharedPtr<System::Net::Cookie>>
{
    /// This type.
    typedef CookieCollection ThisType;
    /// Parent type.
    typedef System::Collections::Generic::ICollection<System::SharedPtr<System::Net::Cookie>> BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Enumerates the timestamp set operations.
    enum class Stamp
    {
        /// Do nothing.
        Check = 0,
        /// Set the current datetime.
        Set = 1,
        /// Set the minimal value.
        SetToUnused = 2,
        /// Set the maximum value.
        SetToMaxUsed = 3
    };

public:
    /// @copydoc System::Collections::Generic::ICollection::get_Count
    ASPOSECPP_SHARED_API int32_t get_Count() const override;
    /// Returns a value that indicates if the collection contains a cookie with a version that is not equal to
    /// Cookie::MaxSupportedVersion.
    /// @returns True when the collection contains a cookie with a version that is not equal to
    /// Cookie::MaxSupportedVersion, otherwise false.
    /// @internal
    ASPOSECPP_SHARED_API bool get_IsOtherVersionSeen();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API CookieCollection();

    /// Returns a cookie from the cookie collection at the specified index.
    /// @param index The index of a cookie that must be returned.
    /// @returns A cookie at the specified index.
    ASPOSECPP_SHARED_API System::SharedPtr<Cookie> idx_get(int32_t index);
    /// Returns a cookie from the cookie collection by specified name.
    /// @param name The name of a cookie that must be returned.
    /// @returns A cookie from the cookie collection by specified name when it is found, otherwise nullptr.
    ASPOSECPP_SHARED_API System::SharedPtr<Cookie> idx_get(String name);

    /// Adds a cookie to the collection.
    /// @param cookie The cookie to add.
    ASPOSECPP_SHARED_API void Add(const System::SharedPtr<Cookie>& cookie) override;
    /// Removes the specified cookie from the collection.
    /// @param cookie The cookie to remove.
    /// @returns True when the specified cookie is removed successfully, otherwise false.
    /// @throws System::NotImplementedException
    ASPOSECPP_SHARED_API bool Remove(const System::SharedPtr<Cookie>& cookie) override;
    /// Checks if the collection contains the specified cookie.
    /// @param cookie The cookie to check.
    /// @returns True when the collection contains the specified cookie, otherwise false.
    ASPOSECPP_SHARED_API bool Contains(const System::SharedPtr<Cookie>& cookie) const override;
    /// Removes all cookies from the collection.
    ASPOSECPP_SHARED_API void Clear() override;

    /// Adds cookies from the specified collection to the current one.
    /// @param cookies The collection from which cookies will be copied to the current one.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<CookieCollection> cookies);
    /// Updates the timestamp by specified scenario and returns a new value.
    /// @param how The update scenario.
    /// @returns A new timestamp value.
    ASPOSECPP_SHARED_API DateTime TimeStamp(CookieCollection::Stamp how);
    /// Adds the specified cookie to the collection.
    /// @param cookie The cookie to add.
    /// @param isStrict True when the specified cookie must replace the old one, otherwise false.
    /// @returns 0 when the specified cookie replaced the old one, otherwise 1.
    ASPOSECPP_SHARED_API int32_t InternalAdd(System::SharedPtr<Cookie> cookie, bool isStrict);
    /// Returns an index of the specified cookie.
    /// @param cookie The cookie to search for.
    /// @returns An index of the specified cookie if it's found, otherwise -1.
    ASPOSECPP_SHARED_API int32_t IndexOf(System::SharedPtr<Cookie> cookie);
    /// Removes a cookie at the specified index.
    /// @param idx An index of a cookie that must be removed.
    ASPOSECPP_SHARED_API void RemoveAt(int32_t idx);
    /// @copydoc System::Collections::Generic::ICollection::GetEnumerator
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::IEnumerator<System::SharedPtr<Cookie>>> GetEnumerator() override;

    /// @copydoc System::Collections::Generic::IEnumerable<System::SharedPtr<Cookie>>::virtualizeBeginIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::SharedPtr<Cookie>>* virtualizeBeginIterator() override;
    /// @copydoc System::Collections::Generic::IEnumerable<System::SharedPtr<Cookie>>::virtualizeEndIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::SharedPtr<Cookie>>* virtualizeEndIterator() override;
    /// @copydoc System::Collections::Generic::IEnumerable<System::SharedPtr<Cookie>>::virtualizeBeginConstIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::SharedPtr<Cookie>>* virtualizeBeginConstIterator() const override;
    /// @copydoc System::Collections::Generic::IEnumerable<System::SharedPtr<Cookie>>::virtualizeEndConstIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::SharedPtr<Cookie>>* virtualizeEndConstIterator() const override;

private:
    /// The cookie collection.
    System::SharedPtr<Collections::Generic::List<System::SharedPtr<Cookie>>> _list;
    /// The timestamp.
    DateTime _timeStamp;
    /// A value that indicates if the collection contains a cookie with a version that is not equal to
    /// Cookie::MaxSupportedVersion.
    bool _hasOtherVersions;

    /// Gets a value that indicates if access to the collection is thread-safe.
    /// @returns True when access to the collection is thread-safe, otherwise false.
    bool get_IsSynchronized();
    /// @copydoc System::Collections::Generic::ICollection::get_SyncRoot
    System::SharedPtr<Object> get_SyncRoot() const;

    /// @copydoc System::Collections::Generic::ICollection::CopyTo
    void CopyTo(System::ArrayPtr<System::SharedPtr<Cookie>> array, int32_t arrayIndex) override;
};

}} // namespace System::Net
