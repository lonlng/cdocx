#pragma once

#include "system/collections/iequality_comparer.h"
#include "system/collections/base_set.h"

#include <unordered_set>

namespace System {
namespace Collections {
namespace Generic {

/// Forward declaration of HashSet class.
template<typename T> class HashSet;

/// Pointer to keep HashSet references.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
/// @param T Hashed type.
template<typename T>
class ASPOSECPP_SHARED_CLASS HashSetPtr : public SharedPtr<HashSet<T> >
{
public:
    /// Null pointer constructor.
    HashSetPtr() {}
    /// Copy constructor.
    /// @param obj Pointer to copy.
    HashSetPtr(const SharedPtr<HashSet<T> >& obj) : SharedPtr<HashSet<T> >(obj) { }
};

/// Set implementation based on hashing.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @param T Element type.
/// @code
/// #include "system/array.h"
/// #include "system/collections/hashset.h"
/// #include "system/smart_ptr.h"
///
/// void PrintValues(const System::SharedPtr<const System::Collections::Generic::IEnumerable<int>> & collection)
/// {
///   for (auto item: collection)
///   {
///     std::cout << item << ' ';
///   }
///   std::cout << std::endl;
/// }
///
/// int main()
/// {
///   // Create and fill instances of the HashSet<int> type.
///   auto set1 = System::MakeObject<System::Collections::Generic::HashSet<int>>();
///   auto set2 = System::MakeObject<System::Collections::Generic::HashSet<int>>();
///
///   for (auto i = 0; i < 10; i++)
///   {
///     set1->Add(i);
///     set2->Add(i * 3);
///   }
///
///   // Print items of the sets.
///   PrintValues(set1);
///   PrintValues(set2);
///
///   // Copy values of the sets to the array and print values.
///   auto arr = System::MakeArray<int>(set1->get_Count() + set2->get_Count());
///   set1->CopyTo(arr, 0);
///   set2->CopyTo(arr, set1->get_Count());
///   PrintValues(arr);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 8 0 1 2 3 4 5 6 7 9
/// 24 0 3 6 9 12 15 18 21 27
/// 8 0 1 2 3 4 5 6 7 9 24 0 3 6 9 12 15 18 21 27
/// */
/// @endcode
template<typename T>
class ASPOSECPP_SHARED_CLASS HashSet : public BaseSet<T, std::unordered_set<T, EqualityComparerHashAdapter<T>, EqualityComparerAdapter<T>, typename System::Details::CollectionHelpers::ContainerPointerMode<T>::allocator_type>>
{
public:
    /// Self type.
    using ThisType = System::Collections::Generic::HashSet<T>;
    /// Base type.
    using BaseType = BaseSet<T, std::unordered_set<T, EqualityComparerHashAdapter<T>, EqualityComparerAdapter<T>, typename System::Details::CollectionHelpers::ContainerPointerMode<T>::allocator_type>>;
    /// Pointer type.
    using ThisPtr = SharedPtr<ThisType>;

private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, System::BaseTypesInfo<System::Object>)

public:
    /// Creates empty set.
    HashSet() : BaseType() {}

    /// Creates empty set with specified capacity
    HashSet(int capacity) : BaseType(capacity) {}

    /// Creates empty set that uses the specified equality comparer
    /// @param comparer Comparer object to associate with hashset.
    HashSet(const SharedPtr<IEqualityComparer<T>>& comparer)
        : BaseType(EqualityComparerHashAdapter<T>(comparer), EqualityComparerAdapter<T>(comparer))
    {
    }

    /// Creates hashset based on enumerable values
    HashSet(const SharedPtr<IEnumerable<T>>& items) : BaseType(items) {}

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Makes container and elements accept visitor.
    /// @param visitor Visitor to accept.
    void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
    {
        BaseType::DBG_for_each_member(visitor);
        visitor.add_self(this);
    }
    /// Returns class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "HashSet<T>"; }
#endif

protected:
    /// Destructor.
    ~HashSet() override {}
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Implements loop reference detection mechanism for container.
    DEFINE_GET_SHARED_MEMBERS(BaseType::m_data);
#endif
};

} // namespace Generic
} // namespace Collections
} // namespace System
