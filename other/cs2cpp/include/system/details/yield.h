/// @file system/details/yield.h
/// @brief Containis support routines for implementing yield code on C++ side
#pragma once

#include <system/object.h>
#include <system/collections/ienumerable.h>
#include <system/nullable.h>
#include <system/exceptions.h>

namespace System { namespace Details {

/// @brief Context for managing yield operations in async state machines
/// @tparam T The type of values to be yielded
template<typename T>
struct YieldContext
{
    /// @brief Yields a value and sets the execution stage
    /// @param val The value to yield
    /// @param step The next execution stage for the state machine
    void YieldReturn(const T& val, int32_t step)
    {
        stage = step;
        value = val;
    }

    /// @brief Current stage of the async state machine execution
    int32_t stage = 0;

    /// @brief Optional storage for the current yielded value (nullptr if no vaule is yelded yet or values are over)
    Nullable<T> value;
};


/// @brief Function type for yield operations
/// @tparam T The type of values the function yields
template <typename T>
using YieldFunction = std::function<void(YieldContext<T>&)>;

/// @brief IEnumerable implementation for yield-based sequences
/// @tparam T The type of elements in the sequence
template<typename T>
class YieldEnumerable : public Collections::Generic::IEnumerable<T>
{
public:
    /// @brief Type alias for the yield function
    using FunctionT = YieldFunction<T>;

    /// @brief Enumerator implementation for yield sequences
    class Enumerator : public Collections::Generic::IEnumerator<T>
    {
    public:
        /// @brief Constructs an enumerator with the given yield function
        /// @param function The yield function to execute
        Enumerator(const FunctionT& function) : m_function(function)
        {
        }

        /// @brief Gets the current element in the sequence
        /// @return Const reference to the current element
        /// @throws IndexOutOfRangeException if no current element exists
        MakeConstRef_t<T> get_Current() const override
        {
            if (m_context.value.get_HasValue())
            {
                return m_context.value;
            }
            else
            {
                throw IndexOutOfRangeException(u"index");
            }
        }

        /// @brief Advances the enumerator to the next element
        /// @return true if the enumerator was successfully advanced; false if the end has been reached
        bool MoveNext() override
        {
            m_context.value.reset();
            m_function(m_context);
            return m_context.value.get_HasValue();
        }

    private:
        /// The yield function to execute
        FunctionT m_function;

        /// Context for managing yield operations
        YieldContext<T>  m_context;
    };

public:
    /// @brief Constructs a yield enumerable with the given function
    /// @param function The yield function to execute
    YieldEnumerable(const FunctionT& function) : m_function(function)
    {
    }

    /// @brief Gets an enumerator for the sequence
    /// @return Shared pointer to the enumerator
    SharedPtr<Collections::Generic::IEnumerator<T>> GetEnumerator() override
    {
        return MakeObject<Enumerator>(m_function);
    }

private:
    /// The yield function to execute
    FunctionT m_function;
};

} // namespace Details

/// @brief Creates an IEnumerable from a yield function
/// @tparam T The type of elements in the sequence
/// @param fnc The yield function to execute
/// @return Shared pointer to the IEnumerable
template <typename T>
SharedPtr<Collections::Generic::IEnumerable<T>> MakeYieldEnumerable(const Details::YieldFunction<T>& fnc)
{
    return MakeObject<Details::YieldEnumerable<T>>(fnc);
}

/// @brief Creates an IEnumerator from a yield function
/// @tparam T The type of elements in the sequence
/// @param fnc The yield function to execute
/// @return Shared pointer to the IEnumerator
template <typename T>
SharedPtr<Collections::Generic::IEnumerator<T>> MakeYieldEnumerator(const Details::YieldFunction<T>& fnc)
{
    return MakeObject<typename Details::YieldEnumerable<T>::Enumerator>(fnc);
}

} // namespace System
