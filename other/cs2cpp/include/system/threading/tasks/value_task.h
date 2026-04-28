/// @file system/threading/tasks/result_value_task.h
#pragma once

#include <system/object.h>
#include <system/iequatable.h>
#include <system/threading/tasks/async.h>
#include <system/threading/tasks/task.h>

namespace System { namespace Runtime { namespace CompilerServices {
class ValueTaskAwaiter;
class ConfiguredValueTaskAwaitable;
}}

namespace Threading { namespace Tasks {

/// @brief Provides an awaitable result of an asynchronous operation.
class ASPOSECPP_SHARED_CLASS ValueTask final : public IEquatable<ValueTask>, public System::Details::BoxableObjectBase
{
    using ThisType = ValueTask;
    using BaseType = Object;

public:
    /// @brief Constructs an empty, uninitialized ValueTask.
    /// @remarks The task is not completed and contains no result.
    /// Attempting to get the result will throw an exception.
    ASPOSECPP_SHARED_API ValueTask();
    /// @brief Constructs a ValueTask from a shared pointer to a Task.
    /// @param task The task to wrap. Can be null for an empty task.
    /// @remarks The ValueTask will represent the state of the provided task.
    ASPOSECPP_SHARED_API ValueTask(const TaskPtr& task);

    /// @brief Gets a value indicating whether the task completed due to an unhandled exception.
    /// @return bool True if the task is faulted; otherwise, false.
    ASPOSECPP_SHARED_API bool get_IsFaulted() const;
    /// @brief Gets a value indicating whether the task completed successfully.
    /// @return bool True if the task ran to completion.
    ASPOSECPP_SHARED_API bool get_IsCompletedSuccessfully() const;
    /// @brief Gets a value indicating whether the task has completed.
    /// @return bool True if the underlying task has completed; otherwise, false.
    ASPOSECPP_SHARED_API bool get_IsCompleted() const;
    /// @brief Gets a value indicating whether the task completed due to being canceled.
    /// @return bool True if the task was canceled; otherwise, false.
    ASPOSECPP_SHARED_API bool get_IsCanceled() const;

    /// @brief Converts this ValueTask to a shared pointer to Task.
    /// @return TaskPtr A shared pointer to a Task that represents this operation.
    ASPOSECPP_SHARED_API TaskPtr AsTask() const;
    /// @brief Configures an awaiter for this task.
    /// @param continueOnCapturedContext true to attempt to marshal the continuation back to the original context
    /// captured; otherwise, false.
    /// @return ConfiguredValueTaskAwaitable An object that configures how awaiters behave for this task.
    ASPOSECPP_SHARED_API Runtime::CompilerServices::ConfiguredValueTaskAwaitable
        ConfigureAwait(bool continueOnCapturedContext) const;
    /// @brief Determines whether this instance equals another ValueTask instance.
    /// @param other The other ValueTask to compare with this instance.
    /// @return bool True if the instances are equal; otherwise, false.
    ASPOSECPP_SHARED_API bool Equals(ValueTask other) override;
    /// @brief Determines whether this instance equals another object.
    /// @param obj The object to compare with this instance.
    /// @return bool True if the object is a ValueTask and equal to this instance; otherwise, false.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    /// @brief Gets an awaiter for this task to support await expressions.
    /// @return ValueTaskAwaiter An awaiter instance for this task.
    /// @remarks This method enables the use of the Await method with ValueTask.
    ASPOSECPP_SHARED_API Runtime::CompilerServices::ValueTaskAwaiter GetAwaiter() const;

    /// @brief Equality operator for ValueTask.
    /// @param other The other ValueTask to compare with this instance.
    /// @return bool True if both tasks have the same underlying task; otherwise, false.
    ASPOSECPP_SHARED_API bool operator==(const ValueTask& other) const;
    /// @brief Inequality operator for ValueTask.
    /// @param other The other ValueTask to compare with this instance.
    /// @return bool True if the instances are not equal; otherwise, false.
    ASPOSECPP_SHARED_API bool operator!=(const ValueTask& other) const;

private:
    /// @brief Friend declaration to allow the awaiter access to private members.
    friend class Runtime::CompilerServices::ValueTaskAwaiter;

    /// @brief The underlying task, if this ValueTask wraps a Task.
    TaskPtr m_task;
};

}} // namespace Threading::Tasks

namespace Runtime { namespace CompilerServices {

class ASPOSECPP_SHARED_CLASS ValueTaskAwaiter
{
public:
    ASPOSECPP_SHARED_API ValueTaskAwaiter(Threading::Tasks::ValueTask task);

    ASPOSECPP_SHARED_API bool get_IsCompleted() const;

    ASPOSECPP_SHARED_API void OnCompleted(const Action<>& continuation);
    ASPOSECPP_SHARED_API void GetResult() const;

    bool continueOnCapturedContext = false;

private:
    Threading::Tasks::ValueTask m_task;
};

class ASPOSECPP_SHARED_CLASS ConfiguredValueTaskAwaitable
{
public:
    ASPOSECPP_SHARED_API ConfiguredValueTaskAwaitable(const Threading::Tasks::ValueTask& task, bool continueOnCapturedContext);

    ASPOSECPP_SHARED_API Runtime::CompilerServices::ValueTaskAwaiter GetAwaiter() const;

private:
    Threading::Tasks::ValueTask m_task;
    bool m_continueOnCapturedContext;
};

}} // namespace Runtime::CompilerServices

ASPOSECPP_SHARED_API Threading::Tasks::ValueTask MakeValueAsync(const Details::AsyncFunction& fnc);

} // namespace System
