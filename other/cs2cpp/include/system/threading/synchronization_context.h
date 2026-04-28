/// @file system/threading/synchronization_context.h
#pragma once
#include <system/object.h>
#include <system/threading/send_or_post_callback.h>

namespace System { namespace Threading {

/// @brief Provides the basic functionality for propagating a synchronization context across various synchronization
/// operations.
/// @details This class enables the propagation of synchronization context between threads and is used to marshal
/// callbacks or invocations to the appropriate thread or synchronization context.
/// @note Dummy implementation.
class ASPOSECPP_SHARED_CLASS SynchronizationContext : public Object
{
    /// RTTI information.
    RTTI_INFO(System::Threading::SynchronizationContext, ::System::BaseTypesInfo<System::Object>);

public:
    /// @brief Constructs a new instance of SynchronizationContext.
    /// @remarks Creates a default synchronization context. The specific behavior depends on the platform
    /// implementation.
    ASPOSECPP_SHARED_API SynchronizationContext();

    /// @brief Gets the synchronization context for the current thread.
    /// @return SharedPtr<SynchronizationContext> A shared pointer to the current thread's synchronization context.
    /// @remarks Returns null if no synchronization context has been set for the current thread.
    static ASPOSECPP_SHARED_API const SharedPtr<SynchronizationContext>& get_Current();

    /// @brief Sets the synchronization context for the current thread.
    /// @param syncContext The synchronization context to set for the current thread.
    /// @remarks Passing nullptr will clear the synchronization context for the current thread.
    static ASPOSECPP_SHARED_API void SetSynchronizationContext(const SharedPtr<SynchronizationContext>& syncContext);

    /// @brief Runs callback asynchronously.
    /// @param d Callback to execute.
    /// @param state Object to pass as callback argument.
    virtual ASPOSECPP_SHARED_API void Post(SendOrPostCallback d, SharedPtr<Object> state);

    /// @brief Runs callback synchronously.
    /// @param d Callback to execute.
    /// @param state Object to pass as callback argument.
    /// @note Unimplemented.
    virtual ASPOSECPP_SHARED_API void Send(SendOrPostCallback d, SharedPtr<Object> state);

private:
    /// @brief Thread-local storage for the current synchronization context.
    /// @details Each thread maintains its own instance of the synchronization context.
    static thread_local SharedPtr<SynchronizationContext> m_current;
};

}} // System::Threading
