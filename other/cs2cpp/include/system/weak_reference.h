/// @file system/weak_reference.h
#pragma once

#include "system/object.h"
#include "system/smart_ptr.h"
#include "system/weak_ptr.h"

namespace System
{
    /// Represents a weak reference, which references an object while still allowing that object to be deleted.
    /// @tparam Args Template arguments of a weak reference declaring a type of a referenced object, a number of arguments can be zero or one.
    template <typename... Args>
    class ASPOSECPP_SHARED_CLASS WeakReference;

    /// Represents a weak reference, which references an object while still allowing that object to be deleted.
    /// @tparam T Type of a referenced object.
    template <typename T>
    class ASPOSECPP_SHARED_CLASS WeakReference<T> : public System::Object
    {

        RTTI_INFO(System::WeakReference<T>, ::System::BaseTypesInfo<System::Object>)
    public:
        /// Default constructor
        WeakReference()
        {
        }

        /// Constructor from nullptr
        WeakReference(std::nullptr_t)
        {
        }

        /// Initializes a new instance of the WeakReference class, referencing the specified object.
        /// @param data Object to store.
        WeakReference(const SmartPtr<T>& data)
        {
            wptr = data;
        }

        /// Initializes a new instance of the WeakReference class, referencing the specified object.
        /// @param data Object to store.
        /// @param trackResurrection Ignored.
        WeakReference(const SmartPtr<T>& data, bool trackResurrection)
        {
            ASPOSE_UNUSED(trackResurrection);
            wptr = data;
        }

        /// Gets the object (the target) referenced by the current WeakReference object.
        /// @param data Object referenced by the current WeakReference object.
        /// @return True if an operation succeded, false otherwise.
        bool TryGetTarget(const SmartPtr<T>& data) const
        {
            data = wptr;
            return true;
        }

        /// Sets the object (the target) referenced by the current WeakReference object.
        /// @param data Object to set.
        void SetTarget(const SmartPtr<T>& data)
        {
            wptr = data;
        }

        void reset()
        {
            wptr.reset();
        }

        /// Checks if referenced object is null.
        /// @return True if referenced object is null, false otherwise.
        bool operator==(std::nullptr_t) const
        {
            return wptr == nullptr;
        }

        /// Checks if referenced object is not null.
        /// @return True if referenced object is not null, false otherwise.
        bool operator!=(std::nullptr_t) const
        {
            return !(*this == nullptr);
        }

        /// Compares referenced object to another instance WeakReference class.
        /// @param other Object compare to.
        /// @return True if compared objects reference the same object, false otherwise.
        bool operator==(const WeakReference<T>& other) const
        {
            return wptr == other.wptr;
        }

        /// Compares referenced object to another instance WeakReference class.
        /// @param other Object compare to.
        /// @return True if compared objects reference different objects, false if objects are same.
        bool operator!=(const WeakReference<T>& other) const
        {
            return wptr != other.wptr;
        }

    protected:
        WeakPtr<T> wptr;
    };

    /// Represents a weak reference, which references an object while still allowing that object to be deleted.
    template <>
    class ASPOSECPP_SHARED_CLASS WeakReference<> : public WeakReference<System::Object>
    {

        RTTI_INFO(System::WeakReference<>, ::System::BaseTypesInfo<System::Object>);
    public:
        /// Default constructor
        WeakReference() : WeakReference<Object>()
        {
        }

        /// Constructor from nullptr
        WeakReference(std::nullptr_t) : WeakReference<Object>(nullptr)
        {
        }

        /// Initializes a new instance of the WeakReference class, referencing the specified object.
        /// @param data Object to store.
        WeakReference(const SmartPtr<Object>& data) : WeakReference<Object>(data)
        {
        }

        /// Initializes a new instance of the WeakReference class, referencing the specified object.
        /// @param data Object to store.
        /// @param trackResurrection Ignored.
        WeakReference(const SmartPtr<Object>& data, bool trackResurrection) : WeakReference<Object>(data, trackResurrection)
        {
        }

        /// Gets the object (the target) referenced by the current WeakReference object.
        /// @return Object referenced by the current WeakReference object.
        const WeakPtr<Object>& get_Target() const
        {
            return wptr;
        }

        /// Sets the object (the target) referenced by the current WeakReference object.
        /// @param data Object to set.
        void set_Target(const SmartPtr<Object>& data)
        {
            wptr = data;
        }

        /// Gets an indication whether the object referenced by the current WeakReference object has been deleted.
        /// @return True if object is not expired, false otherwise.
        bool get_IsAlive() const
        {
            return !wptr.expired();
        }
    };
}
