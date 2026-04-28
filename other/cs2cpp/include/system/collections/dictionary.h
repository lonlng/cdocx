/// @file system/collections/dictionary.h
#ifndef _aspose_system_collections_dictionary_h_
#define _aspose_system_collections_dictionary_h_

#include "system/object.h"
#include "system/collections/base_dictionary.h"
#include "system/collections/keyvalue_collection.h"
#include "system/collections/iequality_comparer.h"
#include "system/cycles_detection.h"
#include "system/iequatable.h"

#include <unordered_map>

namespace System {
namespace Collections {
namespace Generic {

/// Forward declaration of Dictionary class.
template<typename T, typename V> class Dictionary;

/// Dictionary pointer class with operator overloads.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
/// @tparam T Key type.
/// @tparam V Value type.
template<typename T, typename V>
class DictionaryPtr : public SharedPtr<Dictionary<T, V> >
{
public:
    /// Initializes null pointer.
    DictionaryPtr() {}
    /// Converts pointer type.
    /// @param obj Pointer to convert.
    DictionaryPtr(const SharedPtr<Dictionary<T, V> >& obj) : SharedPtr<Dictionary<T, V> >(obj) { }

    /// Access operator to work with key type conversion.
    /// @tparam X Source key type.
    /// @param key Dictionary key.
    /// @return Reference to value corresponding to the key passed, existing or newly created.
    template<class X>
    V& operator[] (const X& key) const
    {
        return (**this)[T(key)];
    }
    /// Access operator.
    /// @param key Dictionary key.
    /// @return Reference to value corresponding to the key passed, existing or newly created.
    V& operator[] (const T& key) const
    {
        return (**this)[key];
    }
};


/// Dictionary that maps values to keys.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include <system/collections/dictionary.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// int main()
/// {
///   // Create the Dictionary-class instance.
///   auto dictionary = MakeObject<Dictionary<int, String>>();
///
///   // Fill the dictionary.
///   dictionary->Add(0, u"Foo");
///   dictionary->Add(1, u"Bar");
///   dictionary->Add(2, u"Baz");
///
///   // Print the dictionary items.
///   for (const auto &pair: dictionary)
///   {
///     std::cout << pair.get_Key() << " - " << pair.get_Value() << std::endl;
///   }
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 0 - Foo
/// 1 - Bar
/// 2 - Baz
/// */
/// @endcode
/// @tparam TKey Key type.
/// @tparam TValue Value type.
template<typename TKey, typename TValue>
class ASPOSECPP_SHARED_CLASS Dictionary
    : public BaseDictionary<std::unordered_map<TKey, TValue, EqualityComparerHashAdapter<TKey>, EqualityComparerAdapter<TKey>, ASPOSE_MAP_ALLOCATOR_TYPE(TKey, TValue)> >
{
    /// Self type.
    typedef Dictionary<TKey, TValue> ThisType;
    /// Implementation type.
    typedef BaseDictionary<std::unordered_map<TKey, TValue, EqualityComparerHashAdapter<TKey>, EqualityComparerAdapter<TKey>, ASPOSE_MAP_ALLOCATOR_TYPE(TKey, TValue)> > BaseType;

    typedef IDictionary<TKey, TValue> BaseType_;

    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, System::BaseTypesInfo<BaseType_>);

public:
    /// Collection of keys to extract.
    typedef ICollection<TKey>   KeyCollection;
    /// Collection of values to extract.
    typedef ICollection<TValue> ValueCollection;
    /// Underlying data type.
    typedef std::unordered_map<TKey, TValue, EqualityComparerHashAdapter<TKey>, EqualityComparerAdapter<TKey>, ASPOSE_MAP_ALLOCATOR_TYPE(TKey, TValue)>  map_t;

    /// Pointer type.
    typedef SharedPtr< Dictionary<TKey, TValue> > Ptr;
    /// Key-value pair type.
    typedef KeyValuePair<TKey, TValue> KVPair;
    /// Pointer to enumerable interface.
    typedef SharedPtr< IEnumerable<KVPair> > IEnumerablePtr;
    /// Pointer to enumerator.
    typedef SharedPtr< IEnumerator<KVPair> > IEnumeratorPtr;

    /// Creates empty dictionary.
    Dictionary()
        : Dictionary(GetDefaultComparer<TKey>())
    {}
    /// Copies data from map.
    /// @param map Map to copy data from.
    Dictionary(const map_t& map)
        : BaseType(0, map) // 0 - use forwarding ctor
    {}
    /// Overload which corresponds to creating pre-allocated dictionary; does no allocation, actually.
    /// @param capacity Capacity to allocate; ignored.
    Dictionary(int capacity)
        : BaseType(0) // 0 - use forwarding ctor
    {}
    /// Copy constructor.
    /// @param src Dictionary to copy data from.
    Dictionary(const SharedPtr<IDictionary<TKey, TValue> >& src)
        : BaseType(src.get())
    {}
    /// Copy constructor.
    /// @param src Source dictionary.
    /// @param comparer Comparer object to use.
    Dictionary(const SharedPtr<IDictionary<TKey, TValue> >& src, const SharedPtr<IEqualityComparer<TKey> >& comparer)
        : BaseType(src.get(), 8, EqualityComparerHashAdapter<TKey>(comparer), EqualityComparerAdapter<TKey>(comparer)) // 8 is a bucket count
    {}
    /// Creates empty dictionary.
    /// @param comparer Comparer to use.
    Dictionary(const SharedPtr<IEqualityComparer<TKey> >& comparer)
        : BaseType(0, 8, EqualityComparerHashAdapter<TKey>(comparer), EqualityComparerAdapter<TKey>(comparer)) // 0 - use forwarding ctor
    {}
    /// Creates empty dictionary.
    /// @param capacity Dictionary capacity after creation; ignored.
    /// @param comparer Comparer to use.
    Dictionary(int capacity, const SharedPtr<IEqualityComparer<TKey> >& comparer)
        : Dictionary(comparer)
    {}

    /// Enumerator that allows iterating through the dictionary.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class Enumerator : public SimpleEnumerator<map_t, KVPair>
    {
        /// Self type.
        typedef typename Dictionary<TKey, TValue>::Enumerator EnumeratorType;
    public:
        /// Creates enumerator.
        /// @param dict Dictionary to iterate through.
        Enumerator(Ptr dict) : SimpleEnumerator<map_t, KVPair>(dict, dict->m_map) { }
        /// RTTI information.
        RTTI_INFO_TEMPLATE_CLASS(EnumeratorType, System::BaseTypesInfo<System::Object>);
        /// Clones current iterator.
        /// @return Copy of the current iterator.
        System::Details::VirtualizedIteratorBase<KVPair>* CloneIterator() const override
        {
            return new Enumerator(*this);
        }
    };

    /// Creates enumerator object.
    /// @return Newly created enumerator object.
    virtual IEnumeratorPtr GetEnumerator() override
    {
        return MakeObject<Enumerator>(MakeSharedPtr(this));
    }

protected:
    /// Destructor.
    ~Dictionary() override {}

    /// Implementation of internal keys collection accessor.
    /// @return Collection of dictionary keys.
    SharedPtr<KeyCollection> get_KeysInternal() const override
    {
        return MakeObject<_KeyCollection<Dictionary<TKey, TValue>>>(MakeSharedPtr(this));
    }
    /// Implementation of internal value collection accessor.
    /// @return Collection of dictionary values.
    SharedPtr<ValueCollection> get_ValuesInternal() const override
    {
        return MakeObject<_ValueCollection<Dictionary<TKey, TValue>>>(MakeSharedPtr(this));
    }

#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Loop references detection implementation.
    DEFINE_GET_SHARED_MEMBERS(BaseType::m_map)
#endif

    private:
        template<typename T>
        class DefaultComparer : public IEqualityComparer<T>
        {
        public:

            virtual bool Equals(T x, T y) const override
            {
                return x->Equals(y);
            }

            virtual int GetHashCode(T obj) const override
            {
                return obj->GetHashCode();
            }
        };

        template<typename T>
        typename std::enable_if<IsSmartPtr<T>::value && std::is_base_of<IEquatable<T>, typename T::Pointee_>::value, SharedPtr<IEqualityComparer<T>> >::type GetDefaultComparer()
        {
            return MakeObject<DefaultComparer<T>>();
        }

        template<typename T>
        typename std::enable_if<IsSmartPtr<T>::value && !std::is_base_of<IEquatable<T>, typename T::Pointee_>::value, SharedPtr<IEqualityComparer<T>> >::type GetDefaultComparer()
        {
            return SharedPtr<IEqualityComparer<T> >();
        }

        template<typename T>
        typename std::enable_if<!IsSmartPtr<T>::value, SharedPtr<IEqualityComparer<T>> >::type GetDefaultComparer()
        {
            return SharedPtr<IEqualityComparer<T> >();
        }

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Debug visitor iteration implementattion.
    /// @param visitor Visitor to access container and elements.
    void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
    {
        BaseType::DBG_for_each_member(visitor);

        visitor.add_self(this);
    }

    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "Dictionary<T>"; }
#endif
};

} // namespace Generic
} // namespace Collections
} // namespace System

#endif // _aspose_system_collections_dictionary_h_
