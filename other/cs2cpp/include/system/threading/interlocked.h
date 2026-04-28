/// @file system/threading/interlocked.h
#pragma once
#include <atomic>
#include <type_traits>
#include "system/threading/thread.h"

namespace System { namespace Threading {

/// Provides API for thread-safe operations.
/// This is a static type with no instance services.
/// You should never create instances of it by any means.
class Interlocked
{
    /// Checks if a passed type is supported by a template function.
    template <typename T>
    static constexpr bool IsSupportedInt = std::is_same<T, int32_t>::value || std::is_same<T, uint32_t>::value ||
                                           std::is_same<T, int64_t>::value || std::is_same<T, uint64_t>::value;

public:
    /// Increments value atomically.
    /// @param location Variable reference to increment.
    /// @return Value of variable right after it was incremented.
    static ASPOSECPP_SHARED_API int32_t Increment(int32_t& location);
    /// Increments value atomically.
    /// @param location Variable reference to increment.
    /// @return Value of variable right after it was incremented.
    static ASPOSECPP_SHARED_API int64_t Increment(int64_t& location);
    /// Decrements value atomically.
    /// @param location Variable reference to decrement.
    /// @return Value of variable right after it was decremented.
    static ASPOSECPP_SHARED_API int32_t Decrement(int32_t& location);
    /// Decrements value atomically.
    /// @param location Variable reference to decrement.
    /// @return Value of variable right after it was decremented.
    static ASPOSECPP_SHARED_API int64_t Decrement(int64_t& location);

    /// Increases value atomically.
    /// @param location1 Variable reference to increase.
    /// @param value Value to add to @p location1.
    /// @return Value of variable right after it was increased.
    static ASPOSECPP_SHARED_API int32_t Add(int32_t& location1, int32_t value);
    /// Increases value atomically.
    /// @param location1 Variable reference to increase.
    /// @param value Value to add to @p location1.
    /// @return Value of variable right after it was increased.
    static ASPOSECPP_SHARED_API int64_t Add(int64_t& location1, int64_t value);

    /// Returns a 64-bit value, loaded as an atomic operation.
    /// @param location1 The 64-bit value to be loaded.
    /// @return The loaded value.
    static ASPOSECPP_SHARED_API int64_t Read(int64_t& location1);

    /// Increases value atomically via exchange-add procedure.
    /// @param location1 Variable reference to increase.
    /// @param value Value to add to @p location1.
    /// @return Value of variable right after it was increased.
    static ASPOSECPP_SHARED_API int32_t ExchangeAdd(int32_t& location1, int32_t value);
    /// Increases value atomically via exchange-add procedure.
    /// @param location1 Variable reference to increase.
    /// @param value Value to add to @p location1.
    /// @return Value of variable right after it was increased.
    static ASPOSECPP_SHARED_API int64_t ExchangeAdd(int64_t& location1, int64_t value);

    /// Exchanges value on variable: stores new value and returns the value variable had immediately before storing.
    /// @tparam T Variable type.
    /// @param location1 Variable reference to change.
    /// @param value Value to store.
    /// @return Value of variable right before it was changed.
    template <typename T>
    static typename std::enable_if<IsSupportedInt<T>, T>::type Exchange(T& location1, T value)
    {
        return std::atomic_exchange((std::atomic<T>*)&location1, value);
    }
    /// Exchanges value on variable: stores new value and returns the value variable had immediately before storing. Not
    /// implemented.
    /// @tparam T Variable type.
    /// @param location1 Variable reference to change.
    /// @param value Value to store.
    /// @return Value of variable right before it was changed.
    template <typename T>
    static typename std::enable_if<!IsSupportedInt<T>, T>::type Exchange(T& location1, T value)
    {
        throw NotImplementedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// Compare-exchanges value on variable: checks if variable is equal to specific value and stores the new value only
    /// if stored value matches expected.
    /// @tparam T Variable type.
    /// @param location1 Variable reference to change.
    /// @param value Value to store.
    /// @param comparand Value to compare variable's value to before exchanging.
    /// @return Value of variable on operation start regardless whether it was changed or not.
    template <typename T>
    static typename std::enable_if<IsSupportedInt<T>, T>::type CompareExchange(T& location1, T value, T comparand)
    {
        auto orig = location1;
        std::atomic_compare_exchange_strong((std::atomic<T>*)&location1, &comparand, value);
        return orig;
    }
    /// Compare-exchanges value on variable: checks if variable is equal to specific value and stores the new value only
    /// if stored value matches expected. Not implemented.
    /// @tparam T Variable type.
    /// @param location1 Variable reference to change.
    /// @param value Value to store.
    /// @param comparand Value to compare variable's value to before exchanging.
    /// @return Value of variable on operation start regardless whether it was changed or not.
    template <typename T>
    static typename std::enable_if<!IsSupportedInt<T>, T>::type CompareExchange(T& location1, T value, T comparand)
    {
        throw NotImplementedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// Compare-exchanges value on variable: checks if variable is equal to specific value and stores the new value only
    /// if stored value matches expected.
    /// @param location1 Variable reference to change.
    /// @param value Value to store.
    /// @param comparand Value to compare variable's value to before exchanging.
    /// @param succeeded Reference to variable which is set to true if exchange took place and to false otherwise.
    /// @return Value of variable on operation start regardless whether it was changed or not.
    static ASPOSECPP_SHARED_API int32_t CompareExchange(int32_t& location1, int32_t value, int32_t comparand,
                                                        bool& succeeded);
};

}} // namespace System::Threading
