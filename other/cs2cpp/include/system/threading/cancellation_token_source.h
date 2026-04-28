/// @file system/threading/cancellation_token_source.h
/// @brief Implementation of a cancellation token source similar to System.Threading.CancellationTokenSource in .NET.
#pragma once

#include <system/idisposable.h>
#include <system/action.h>
#include <map>

namespace System { namespace Threading {

class CancellationToken;

/// @class CancellationTokenSource
/// @brief A cancellation token source that can be used to trigger cancellation notifications.
/// @details Provides mechanisms to create and control cancellation tokens for cooperative cancellation of operations.
class ASPOSECPP_SHARED_CLASS CancellationTokenSource : public IDisposable
{
public:
    /// @brief Constructs a new CancellationTokenSource.
    /// @post Creates a token source in non-canceled state.
    ASPOSECPP_SHARED_API CancellationTokenSource();

    /// @brief Gets whether cancellation has been requested.
    /// @return true if Cancel() has been called, false otherwise.
    bool get_IsCancellationRequested() const {return m_canceled;}
    /// @brief Gets the cancellation token associated with this source.
    /// @return A cancellation token that can be passed to cancelable operations.
    ASPOSECPP_SHARED_API CancellationToken get_Token() const;

    /// @brief Creates a linked token source that cancels when any of the provided tokens cancel.
    /// @param token1 First cancellation token to monitor.
    /// @param token2 Second cancellation token to monitor.
    /// @return New token source that will cancel when either input token cancels.
    /// @remarks The returned source will immediately cancel if either input token is already canceled.
    static ASPOSECPP_SHARED_API SharedPtr<CancellationTokenSource>
        CreateLinkedTokenSource(const CancellationToken& token1, const CancellationToken& token2);

    /// @brief Communicates a request for cancellation.
    /// @post All registered callbacks will be invoked.
    /// @post Subsequent calls to get_IsCancellationRequested() will return true.
    /// @note Callbacks are executed synchronously during this call.
    ASPOSECPP_SHARED_API void Cancel();

    /// @brief Releases all resources used by the CancellationTokenSource.
    /// @details Unregisters all callbacks and makes the token unusable.
    /// @note Multiple calls are safe and have no additional effect.
    ASPOSECPP_SHARED_API void Dispose() override;

private:
    friend CancellationToken;
    friend class CancellationTokenRegistration;

    /// Registers a callback to execute when cancellation is requested.
    ASPOSECPP_SHARED_API int32_t RegisterCallback(const Action<>&);
    /// Unregisters a previously registered callback.
    ASPOSECPP_SHARED_API void UnregisterCallback(int32_t);

    /// Flag indicating whether cancellation has been requested.
    bool m_canceled;
    /// Map of registered callbacks with their registration IDs.
    std::map<int32_t, Action<>> m_callbacks;
};

}} // System::Threading
