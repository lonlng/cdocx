#pragma once
#include <system/collections/icollection_ng.h>

namespace System {
namespace Collections {

/// IList Represents a non-generic collection of objects that can be individually accessed by index.
class ASPOSECPP_SHARED_CLASS IList : virtual public System::Collections::ICollection
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::IList, System::BaseTypesInfo<System::Collections::ICollection>);
public:
    /// Gets the item at the specified index.
    /// @param index The item index.
    /// @param dummy The fake param that is used to disambiguate.
    /// @returns The item at the specified index.
    virtual SharedPtr<System::Object> idx_get(int index, int dummy = 0) const = 0;

    /// Adds item to the end of list.
    /// @param item The item to add.
    /// @returns The index of the added item.
    virtual int Add(SharedPtr<System::Object> item) = 0;

    /// Removes the first instance of the specified item from the list.
    /// @param item The item to remove.
    virtual void Remove(SharedPtr<System::Object> item) = 0;

    /// Removes all items from the list.
    virtual void Clear() = 0;

    /// Checks if the item is in the list.
    /// @param item The item to look for.
    /// @return True if item is found, false otherwise.
    virtual bool Contains(SharedPtr<System::Object> item) const = 0;

    /// Gets the first index of the specified item.
    /// @param item The item to look for.
    /// @return The index of the first occurrence of the specified item, otherwise -1.
    virtual int IndexOf(SharedPtr<System::Object> item)  const = 0;

    /// Inserts the item to the list at the specified index.
    /// @param index The index to insert the item into.
    /// @param item The item to insert.
    virtual void Insert(int index, SharedPtr<System::Object> item) = 0;

    /// Removes the item from the list at the specified index.
    /// @param index The index to remove the item at.
    virtual void RemoveAt(int index) = 0;

    /// Gets a value indicating whether the list has a fixed size.
    /// @returns True when the list has a fixed size, otherwise false.
    virtual bool get_IsFixedSize() const { return false; }
};

} // namespace Collection
} // namespace System


