/// @file system/details/dereference.h
/// Contains implementation for Dereference utility function
#pragma once
#include <fwd.h>
#include <system/exceptions.h>

namespace System { namespace Details {

/// @brief Dereferences various pointer-like and reference types to obtain a reference to the underlying value
/// @tparam T The type of the underlying value
/// @{

/// @brief Returns the input reference unchanged (identity operation for references)
/// @param ref The const reference to dereference
/// @return const T& The input reference
/// @note This overload handles plain constant references
template <typename T>
const T& Dereference(const T& ref) {return ref;}

/// @param ref The reference to dereference
/// @return T& The input reference
/// @note This overload handles plain references
template <typename T>
T& Dereference(T& ref) {return ref;}

/// @brief Dereferences a raw pointer to obtain a reference to the pointed-to value
/// @param ptr The raw pointer to dereference
/// @return const T& A reference to the value pointed to by ptr
/// @warning The pointer must not be null and must point to a valid object
/// @note This overload handles raw pointers
template <typename T>
T& Dereference(T* ptr)
{
    if (!ptr)
    {
        throw NullReferenceException();
    }
    return *ptr;
}

/// @brief Dereferences a const raw pointer to obtain a const reference to the pointed-to value
/// @param ptr The raw pointer to dereference
/// @return const T& A const reference to the value pointed to by ptr
/// @warning The pointer must not be null and must point to a valid object
/// @note This overload handles constant raw pointers
template <typename T>
const T& Dereference(const T* ptr)
{
    if (!ptr)
    {
        throw NullReferenceException();
    }
    return *ptr;
}

/// @brief Dereferences a SharedPtr to obtain a reference to the managed object
/// @param ptr The SharedPtr to dereference
/// @return const T& A reference to the managed object
/// @pre The SharedPtr must not be null and must manage a valid object
/// @note This overload handles constant references to smart pointers
template <typename T>
T& Dereference(const SharedPtr<T>& ptr) {return *ptr;}

/// @brief Dereferences a SharedPtr to obtain a reference to the managed object
/// @param ptr The SharedPtr to dereference
/// @return T& A reference to the managed object
/// @pre The SharedPtr must not be null and must manage a valid object
/// @note This overload handles mutable references to smart pointers
template <typename T>
T& Dereference(SharedPtr<T>& ptr) {return *ptr;}

/// @brief Dereferences a WeakPtr to obtain a reference to the managed object
/// @param ptr The WeakPtr to dereference
/// @return const T& A const to the managed object
/// @pre The WeakPtr must be locked (not expired) and manage a valid object
/// @warning Using this with an expired WeakPtr results in undefined behavior
/// @note This overload handles WeakPtr smart pointers
template <typename T>
T& Dereference(const WeakPtr<T>& ptr) {return *ptr;}

/// @}

}} // namespace System::Details
