#pragma once

#include <system/smart_ptr.h>
#include <system/string.h>

namespace System
{

/// This class used to get persistent reference to the object instance, whatever it is lvalue or 
/// rvalue. To ubtain such reference, use 'HoldIfTemporary' method, that has there overloads. Two 
/// of them take rvalue as a parameter, and just return the reference to it. The third one, in 
/// opposite, takes lvalue as a parameter, makes a pointer copy, then return reference to that copy.
/// Also, class has 'Hold' method to hold passed value unconditionally (used to copy values of 
/// a local on-stack variables or it's child references)
/// @tparam T The type of the object to hold to.
/// @tparam R True, if T is a reference type (SmartPtr specialization or System::String type), 
/// and temporary references holding is actually required, false - otherwise.
template <typename T, bool R = System::IsSmartPtr<T>::value || std::is_same<System::String, T>::value>
struct HolderInitializer
{
private:
    /// The variable reference to hold temporary value
    T& m_holder;
public:
    /// Initializes holder reference with passed one.
    inline HolderInitializer(T& holder) : m_holder(holder) {}

    /// Returns reference to rvalue (const)
    inline const T& HoldIfTemporary(const T& value)
    {
        return value;
    }

    /// Returns reference to rvalue (non-const)
    inline const T& HoldIfTemporary(T& value)
    {
        return value;
    }

    /// Copies passed lvalue to holder, then return the holder reference
    inline const T& HoldIfTemporary(T&& value)
    {
        m_holder = value;
        return m_holder;
    }

    /// Copies passed lvalue to holder, then return the holder reference
    /// Caller should use this method to hold passed value unconditionally.
    inline const T& Hold(const T& value)
    {
        m_holder = value;
        return m_holder;
    }
};

/// HolderInitializer specialization for the case when T is a value type., The usage context allow 
/// to return reference to temporary objects, as it is guaranteed, that the instance will be copied
/// by caller. So, this specialization is used just as a stub, and do nothing.
template <typename T>
struct HolderInitializer<T, false>
{
public:
    inline HolderInitializer(T& holder) {}

    inline const T& HoldIfTemporary(const T& value)
    {
        return value;
    }

    inline const T& Hold(const T& value)
    {
        return value;
    }
};

}