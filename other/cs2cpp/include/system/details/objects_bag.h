/// @file system/details/objects_bag.h
#pragma once

#include <system/object.h>
#include <vector>

namespace System { namespace Details {

/// Objects container based on the hash table with open addressing and linear probing.
/// Up to 10 times faster than System::Collections::Generic::HashSet.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ObjectsBag final : public Object
{
    RTTI_INFO(System::Details::ObjectsBag, ::System::BaseTypesInfo<System::Object>)

public:
    ASPOSECPP_SHARED_API ObjectsBag();
    ASPOSECPP_SHARED_API ~ObjectsBag();

    ObjectsBag(const ObjectsBag&) = delete;
    ObjectsBag operator=(const ObjectsBag&) = delete;

    /// Adds object into container.
    /// @param object Object to add.
    template <typename T>
    void Add(const SharedPtr<T>& object)
    {
        TryAdd(object);
    }

    /// Adds object into container.
    /// @param object Object to add.
    /// @return True if object was added, false if already exists.
    template <typename T>
    bool TryAdd(const SharedPtr<T>& object)
    {
        return TryAdd(object.GetObjectOrNull());
    }

    /// Removes object from container.
    /// @param object Object to remove.
    /// @return True if object was found and deleted, false otherwise.
    template <typename T>
    bool Remove(const SharedPtr<T>& object)
    {
        return Remove(object.GetObjectOrNull());
    }

    /// Checks if object is present in the container.
    /// @param object Object to look for.
    /// @return True if object is present in the container, false otherwise.
    template <typename T>
    bool Contains(const SharedPtr<T>& object) const
    {
        return Contains(object.GetObjectOrNull());
    }

    /// Adds object into container.
    /// @param object Object to add.
    /// @return True if object was added, false if already exists.
    ASPOSECPP_SHARED_API bool TryAdd(Object* object);

    /// Removes object from container.
    /// @param object Object to remove.
    /// @return True if object was found and deleted, false otherwise.
    ASPOSECPP_SHARED_API bool Remove(Object* object);

    /// Checks if object is present in the container.
    /// @param object Object to look for.
    /// @return True if object is present in the container, false otherwise.
    ASPOSECPP_SHARED_API bool Contains(Object* object) const;

    /// Deletes all objects in the container.
    ASPOSECPP_SHARED_API void Clear();

    /// Gets number of objects.
    /// @return Objects count.
    int get_Count() const
    {
        return ASPOSECPP_CHECKED_CAST(int, m_count);
    }

    bool TryAdd(std::nullptr_t) = delete;
    bool Remove(std::nullptr_t) = delete;
    bool Contains(std::nullptr_t) const = delete;

private:
    static constexpr uintptr_t null_object = 0;

    std::vector<uintptr_t> m_table;
    size_t m_count = 0;

    static size_t Hash(uintptr_t object_ptr);
    static void ReleaseObject(uintptr_t object_ptr);

    void ResizeTableIfNeeded();
    void ShiftObjects(size_t index);

    template <typename It>
    static It Find(const It begin, const It end, const It start, uintptr_t object_ptr)
    {
        for (auto it = start; it != end; ++it)
            if (*it == null_object || *it == object_ptr)
                return it;

        for (auto it = begin; it != start; ++it)
            if (*it == null_object || *it == object_ptr)
                return it;

        return end;
    }

#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
    
#ifdef __DBG_FOR_EACH_MEMBER
public:
    void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override;
    const char* DBG_class_name() const override { return "ObjectsBag"; }
#endif
};

}} // namespace System::Details
