/// @file system/details/signal_awaiter.h
/// @brief Containis signal awaiter for implementing await-async code on C++ side
#pragma once

#include <functional>
#include <system/object.h>
#include <system/action.h>

namespace System { namespace Details {

/// @brief Signal function type that accepts a result provider callback
/// @tparam T The type of the result value
/// @param resultGetter Callback function that provides the result when invoked
/// @details Used to signal completion and provide a mechanism to retrieve the result
template <typename T>
using ResultSignal = std::function<void(std::function<T()>)>;

/// @brief Acceptor function type that receives a ResultSignal
/// @tparam T The type of the result value
/// @param signal The ResultSignal to be accepted and stored for later invocation
/// @details Used to accept and store a signal callback for deferred completion signaling
template <typename T>
using ResultSignalAcceptor = std::function<void(ResultSignal<T>)>;

/// @brief Awaiter class for ResultSignal-based asynchronous operations
/// @tparam T The type of the result value
/// @details Implements the awaiter interface for implementation of async tasks using direct C++. Should not be used in C# code translation.
template <typename T>
class SignalAwaiter
{
public:
    /// @brief Constructs a SignalAwaiter with a ResultSignal acceptor
    /// @param acceptor The acceptor function that will receive the ResultSignal
    /// @details The acceptor is invoked immediately to establish the signal channel
    SignalAwaiter(ResultSignalAcceptor<T> acceptor) : m_data(std::make_shared<Data>())
    {
        ResultSignal<T> signal = [data = m_data](std::function<T()> resultGetter)
        {
            data->result_getter = resultGetter;

            if (!data->continuation.IsNull())
            {
                data->continuation();
            }
        };

        acceptor(signal);
    }

    /// @brief Checks if the asynchronous operation has completed
    /// @return bool True if the result is available, false otherwise
    /// @note Completion means the ResultSignal has been invoked with a result provider
    bool get_IsCompleted() const
    {
        return m_data->result_getter != nullptr;
    }
    /// @brief Sets the continuation to be executed when the operation completes
    /// @param continuation The action to execute upon completion
    void OnCompleted(const Action<>& continuation)
    {
        m_data->continuation = continuation;
    }
    /// @brief Retrieves the result of the completed asynchronous operation
    /// @return T The result value
    /// @pre The operation must be completed (get_IsCompleted() returns true)
    /// @throws May propagate exceptions thrown by the result provider function
    T GetResult() const
    {
        return m_data->result_getter();
    }

    /// @brief Indicates that continuation should not capture the execution context
    /// @value Always false - continuations run on the context that signals completion
    static const bool continueOnCapturedContext = false;

private:
    /// @brief Internal data structure shared between awaiter and awaitable
    struct Data
    {
        /// @brief Continuation action to invoke upon completion
        Action<> continuation;
        /// @brief Function to retrieve the result when available
        std::function<T()> result_getter;
    };

    /// @brief Shared state data between the awaiter and awaitable
    std::shared_ptr<Data> m_data;
};

/// @brief Source for awaiter for ResultSignal-based asynchronous operations
/// @tparam T The type of the result value
/// @details Provides the GetAwaiter() method required for Await support,
///          wrapping a ResultSignalAcceptor for use in C++ async functions
template <typename T>
class SignalAwaitable
{
public:
    /// @brief Constructs a SignalAwaitable with a ResultSignal acceptor
    /// @param acceptor The acceptor function that will receive the ResultSignal
    SignalAwaitable(ResultSignalAcceptor<T> acceptor) : m_acceptor(acceptor) {}

    /// @brief Creates an awaiter for this awaitable operation
    /// @return SignalAwaiter<T> An awaiter instance ready for Await call
    /// @note This method is automatically called by Await calls
    SignalAwaiter<T> GetAwaiter() const {return SignalAwaiter<T>(m_acceptor);}

private:
    /// @brief The acceptor function that establishes the signal channel
    ResultSignalAcceptor<T> m_acceptor;
};

}} // namespace System::Details
