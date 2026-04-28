/// @file system/collections/specialized/name_value_collection.h
#pragma once
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/collections/list.h>
#include <system/collections/ienumerator.h>
#include <system/collections/icollection.h>
#include <system/collections/dictionary.h>
#include <system/array.h>
#include <cstdint>

namespace System { namespace Collections { namespace Specialized {

///  Collection of associated String keys and String values that can be accessed either with the key or with the index.
class ASPOSECPP_SHARED_CLASS NameValueCollection : public System::Collections::Generic::ICollection<System::String>
{
    typedef NameValueCollection ThisType;
    typedef System::Collections::Generic::ICollection<System::String> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:
    /// Gets all the keys 
    ASPOSECPP_SHARED_API virtual System::ArrayPtr<String> get_AllKeys();
    /// Gets all the keys 
    ASPOSECPP_SHARED_API virtual System::SharedPtr<System::Collections::Generic::IList<String>> get_Keys();
    /// Gets the number of key/value pairs
    ASPOSECPP_SHARED_API virtual int get_Count() const override;
    /// Override ICollection method - not implemented
    ASPOSECPP_SHARED_API virtual void Add(const String& item) override;
    /// Checks if item is present in collection.
    /// @param item to look for.
    /// @return True if item is present, false otherwise.
    ASPOSECPP_SHARED_API virtual bool Contains(const String& item) const override;
    /// Removes specific item.
    /// @param item Item to remove.
    /// @return True if item was found and removed, false otherwise.
    ASPOSECPP_SHARED_API virtual bool Remove(const String& item) override;
    /// Deletes all elements.
    ASPOSECPP_SHARED_API void Clear() override;
    /// Copies collection elements into existing array elements.
    /// @param array Destination array.
    /// @param arrayIndex Destination array start index.
    ASPOSECPP_SHARED_API void CopyTo(System::ArrayPtr<String> array, int32_t arrayIndex) override;
    /// Gets enumerator to iterate through collection.
    /// @return Created enumerator iterating through current collection.
    ASPOSECPP_SHARED_API System::SharedPtr<Generic::IEnumerator<String>> GetEnumerator() override;
    /// Initializes a new instance of the NameValueCollection class that is empty
    ASPOSECPP_SHARED_API NameValueCollection();
    /// Copies the entries from the specified NameValueCollection to a new NameValueCollection 
    ASPOSECPP_SHARED_API NameValueCollection(const System::SharedPtr<NameValueCollection>& col);
    /// Copies the entries in the specified NameValueCollection to the current 
    ASPOSECPP_SHARED_API void Add(const System::SharedPtr<NameValueCollection>& c);
    /// Adds an entry with the specified name and value 
    ASPOSECPP_SHARED_API virtual void Add(const String& name, const String& value);
    /// Gets the values associated with the specified key
    ASPOSECPP_SHARED_API virtual String Get(const String& name);
    /// Gets the values associated with the specified key
    ASPOSECPP_SHARED_API virtual System::ArrayPtr<String> GetValues(const String& name);
    /// Sets the value of an entry
    ASPOSECPP_SHARED_API virtual void Set(const String& name, const String& value);
    /// Gets value at specified index.
    /// @param name entry name.
    /// @return Copy of value at specified index.
    ASPOSECPP_SHARED_API String idx_get(const String& name);
    /// Sets value of an entry.
    /// @param name entry name.
    /// @param value Value to set at name.
    ASPOSECPP_SHARED_API void idx_set(const String& name, const String& value);
    /// Gets a value indicating whether the NameValueCollection contains keys that are not null
    ASPOSECPP_SHARED_API bool HasKeys();

    /// @copydoc System::Collections::Generic::IEnumerable<System::String>::virtualizeBeginIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeBeginIterator() override;
    /// @copydoc System::Collections::Generic::IEnumerable<System::String>::virtualizeEndIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeEndIterator() override;
    /// @copydoc System::Collections::Generic::IEnumerable<System::String>::virtualizeBeginConstIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeBeginConstIterator() const override;
    /// @copydoc System::Collections::Generic::IEnumerable<System::String>::virtualizeEndConstIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeEndConstIterator() const override;

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
private:
    System::SharedPtr<Generic::Dictionary<String, System::SharedPtr<Generic::List<String>>>> _entries;

    bool get_IsReadOnly();

    static String GetAsOneString(const System::SharedPtr<Generic::List<String>>& list);
    static System::ArrayPtr<String> GetAsStringArray(const System::SharedPtr<Generic::List<String>>& list);
};

}}} // namespace System::Collections::Specialized
