#pragma once

#include "system/collections/base_set.h"

#include <set>

namespace System {
namespace Collections {
namespace Generic {

/// Forward declaration of SortedSet class.
template<typename T> class SortedSet;

/// Pointer to keep SortedSet references.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
/// @param T Hashed type.
template<typename T>
class ASPOSECPP_SHARED_CLASS SortedSetPtr : public SharedPtr<SortedSet<T>>
{
public:
    /// Null pointer constructor.
    SortedSetPtr() {}
    /// Copy constructor.
    /// @param obj Pointer to copy.
    SortedSetPtr(const SharedPtr<SortedSet<T>>& obj) : SharedPtr<SortedSet<T>>(obj) { }
};

/// Implementation a set of ordered objects.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @param T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS SortedSet : public BaseSet<T, std::set<T, ComparerAdapter<T>, typename System::Details::CollectionHelpers::ContainerPointerMode<T>::allocator_type>>
{
public:
    /// Self type.
    using ThisType = System::Collections::Generic::SortedSet<T>;
    /// Vase type.
    using BaseType = BaseSet<T, std::set<T, ComparerAdapter<T>, typename System::Details::CollectionHelpers::ContainerPointerMode<T>::allocator_type>>;
    /// Pointer type.
    using ThisPtr = SharedPtr<ThisType>;

private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, System::BaseTypesInfo<System::Object>);

public:
    /// Creates empty set.
    SortedSet() : BaseType() {}

    /// Creates empty set with specified capacity
    SortedSet(int capacity) : BaseType(capacity) {}

    /// Creates empty set that uses the specified equality comparer
    /// @param comparer Comparer object to associate with SortedSet.
    SortedSet(const SharedPtr<IComparer<T>>& comparer)
        : BaseType(ComparerAdapter<T>(comparer))
    {
    }

    /// Creates SortedSet based on enumerable values
    SortedSet(const SharedPtr<IEnumerable<T>>& items) : BaseType(items) {}

    /// Gets the maximum value in the SortedSet.
    /// @return The maximum value in the SortedSet.
    T get_Max() const
    {
        if (BaseType::m_data.empty())
            throw ArgumentOutOfRangeException(u"SortedSet is empty");
        return *BaseType::m_data.rbegin();
    }

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
    const char* DBG_class_name() const override { return "SortedSet<T>"; }
#endif

protected:
    /// Destructor.
    ~SortedSet() override {}
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Implements loop reference detection mechanism for container.
    DEFINE_GET_SHARED_MEMBERS(BaseType::m_data);
#endif
};

} // namespace Generic
} // namespace Collections
} // namespace System
