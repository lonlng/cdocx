/// @file system/threading/cancellation_token.h
#pragma once

#include <system/object.h>
#include <system/action.h>

namespace System { namespace Threading {

class CancellationTokenSource;
class CancellationToken;

/// @class CancellationTokenRegistration
/// @brief Represents a registration for a cancellation token callback.
///
/// This class allows for the deregistration of a callback from a cancellation token.
/// When disposed, it removes the callback from the associated CancellationTokenSource.
/// @note This class should not be created directly - it is returned by CancellationToken registration methods.
class ASPOSECPP_SHARED_CLASS CancellationTokenRegistration
{
public:
    /// @brief Disposes the registration and removes the callback from the associated CancellationTokenSource.
    /// After calling this method, the registered callback will no longer be invoked
    /// when the associated CancellationTokenSource is canceled.
    /// @note It is safe to call this method multiple times - subsequent calls will have no effect.
    ASPOSECPP_SHARED_API void Dispose();

private:
    friend class CancellationToken;

    /// Weak reference to the CancellationTokenSource this registration is associated with.
    WeakPtr<CancellationTokenSource> m_source;
    /// The registration ID used to identify this callback in the CancellationTokenSource.
    /// A value of -1 indicates an invalid/unregistered state.
    int32_t m_registration = -1;
};

/// @class CancellationToken
/// @brief Propagates notification that operations should be canceled.
/// This class provides a mechanism for cooperative cancellation between threads,
/// allowing one thread to notify others that an operation should be canceled.
/// @note A CancellationToken can only be canceled through its associated CancellationTokenSource.
class ASPOSECPP_SHARED_CLASS CancellationToken : public ::System::Details::BoxableObjectBase
{
public:
    /// @brief Default constructor.
    /// @details Creates a token that will never be canceled (equivalent to None).
    ASPOSECPP_SHARED_API CancellationToken();

    /// @brief Returns an empty System::Threading::CancellationToken value.
    /// @return An empty cancellation token that cannot be canceled.
    /// @note The returned token will never transition to a canceled state.
    static ASPOSECPP_SHARED_API CancellationToken get_None();

    /// @brief Gets whether cancellation has been requested for this token.
    /// @return true if cancellation has been requested for this token; otherwise, false.
    ASPOSECPP_SHARED_API bool get_IsCancellationRequested() const;
    /// @brief Gets whether this token is capable of being in the canceled state.
    /// @return true if this token is capable of being in the canceled state; otherwise, false.
    /// @note Tokens created from CancellationTokenSource will return true,
    /// while the None token will always return false.
    ASPOSECPP_SHARED_API bool get_CanBeCanceled() const;

    /// @brief Registers a callback that will be invoked when cancellation is requested.
    /// @param callback The Action<> to execute when cancellation is requested.
    /// @return A CancellationTokenRegistration object that can be used to deregister the callback.
    /// @note If cancellation has already been requested, the callback will be invoked immediately.
    /// @warning The callback should be short-lived and non-blocking as it will be executed
    /// on the thread that calls Cancel() on the CancellationTokenSource.
    ASPOSECPP_SHARED_API CancellationTokenRegistration Register(const Action<>& callback) const;

    /// @brief Throws a OperationCanceledException if cancellation has been requested.
    /// @throws OperationCanceledException if get_IsCancellationRequested is true.
    /// @note This method provides a convenient way to check for cancellation at specific
    /// points in your code where it's safe to throw an exception.
    ASPOSECPP_SHARED_API void ThrowIfCancellationRequested() const;

private:
    friend CancellationTokenSource;

    /// Shared pointer to the CancellationTokenSource associated with this token.
    /// This is null for tokens created with get_None() or the default constructor.
    SharedPtr<CancellationTokenSource> m_source;
};

}} // System::Threading
