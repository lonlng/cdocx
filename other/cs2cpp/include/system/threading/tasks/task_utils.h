/// @file system/threading/tasks/task_utils.h
/// @brief Contains utility functions for working with tasks in asynchronous programming.

#pragma once

#include <functional>
#include <system/object.h>
#include <system/collections/ienumerable.h>
#include <system/linq/enumerable.h>
#include <system/threading/tasks/task.h>
#include <system/threading/tasks/result_task.h>
#include <system/threading/tasks/async.h>
#include <system/array.h>

#undef Yield

namespace System {

namespace Runtime { namespace CompilerServices {

/// @class YieldAwaitable
/// @brief An awaitable type that is returned from TaskUtils::Yield().
/// @details This type enables yielding control back to the calling context in asynchronous methods.
class ASPOSECPP_SHARED_CLASS YieldAwaitable
{
public:
    /// @class YieldAwaiter
    /// @brief The awaiter type for YieldAwaitable.
    class ASPOSECPP_SHARED_CLASS YieldAwaiter
    {
    public:
        /// @brief Gets whether the yield operation has completed.
        /// @return Always returns false, indicating the operation is not yet complete.
        bool get_IsCompleted() const {return false;}
        
        /// @brief Schedules the continuation action for when the yield operation completes.
        /// @param continuation The action to invoke when the yield completes.
        ASPOSECPP_SHARED_API void OnCompleted(const Action<>& continuation);
        
        /// @brief Ends the await operation.
        void GetResult() const {}

        /// @brief Specifies whether to continue on the captured synchronization context.
        static constexpr bool continueOnCapturedContext = false;
    };

    /// @brief Gets the awaiter for this awaitable.
    /// @return A YieldAwaiter instance.
    YieldAwaiter GetAwaiter() const
    {
        return YieldAwaiter();
    }
};

}} // namespace Runtime::CompilerServices

namespace Threading {

class CancellationToken;

namespace Tasks {

/// @brief Creates a task that completes after a time delay.
/// @param millisecondsDelay The number of milliseconds to wait before completing the returned task, or -1 to wait indefinitely.
/// @return A task that represents the time delay.
/// @throws System.ArgumentOutOfRangeException if the millisecondsDelay argument is less than -1.
ASPOSECPP_SHARED_API TaskPtr Delay(int32_t millisecondsDelay);

/// @brief Creates a task that completes after a time delay and can be cancelled.
/// @param millisecondsDelay The number of milliseconds to wait before completing the returned task, or -1 to wait indefinitely.
/// @param cancellationToken The cancellation token that can be used to cancel the delay.
/// @return A task that represents the time delay.
/// @throws System.ArgumentOutOfRangeException if the millisecondsDelay argument is less than -1.
ASPOSECPP_SHARED_API TaskPtr Delay(int32_t millisecondsDelay, const CancellationToken& cancellationToken);

/// @brief Creates a task that has completed due to cancellation with the specified token.
/// @param cancellationToken The cancellation token that caused the task to be cancelled.
/// @return A cancelled task.
ASPOSECPP_SHARED_API TaskPtr FromCanceled(const CancellationToken& cancellationToken);

/// @brief Creates a task that has completed with a specified exception.
/// @param exception The exception with which to complete the task.
/// @return A faulted task.
ASPOSECPP_SHARED_API TaskPtr FromException(const Exception& exception);

/// @brief Creates a task that has completed with a specified exception and result type.
/// @tparam TResult The type of the task's result.
/// @param exception The exception with which to complete the task.
/// @return A faulted task with the specified result type.
template<typename TResult>
RTaskPtr<TResult> FromException(const Exception& exception)
{
    return MakeAsync<TResult>([=](System::Details::ResultAsyncContext<TResult>& __context) { exception.Throw(); });
}

/// @brief Creates a task that has successfully completed with the specified result.
/// @tparam TResult The type of the task's result.
/// @param result The result value with which to complete the task.
/// @return A successfully completed task.
template <typename TResult>
RTaskPtr<TResult> FromResult(TResult result)
{
    return MakeObject<ResultTask<TResult>>(result);
}

/// @brief Queues the specified work to run on the thread pool and returns a Task handle for that work.
/// @param action The work to execute asynchronously.
/// @return A Task that represents the work queued to execute in the thread pool.
ASPOSECPP_SHARED_API TaskPtr Run(const Action<>& action);

/// @brief Queues the specified work to run on the thread pool and returns a Task handle for that work.
/// @param action The work to execute asynchronously.
/// @param cancellationToken A cancellation token that can be used to cancel the work if it has not yet started.
/// @return A Task that represents the work queued to execute in the thread pool.
ASPOSECPP_SHARED_API TaskPtr Run(const Action<>& action, const CancellationToken& cancellationToken);

/// @brief Queues the specified work to run on the thread pool and returns a proxy for the Task returned by the function.
/// @param function The work to execute asynchronously, which returns a Task.
/// @return A Task that represents a proxy for the Task returned by the function.
ASPOSECPP_SHARED_API TaskPtr Run(const Func<TaskPtr>& function);

/// @brief Queues the specified work to run on the thread pool and returns a Task<TResult> handle for that work.
/// @tparam TResult The type of the result returned by the task.
/// @param function The work to execute asynchronously.
/// @return A Task<TResult> that represents the work queued to execute in the thread pool.
template <typename TResult>
RTaskPtr<TResult> Run(const Func<TResult>& function)
{
    auto result = MakeObject<ResultTask<TResult>>(function);
    result->Start();
    return result;
}

/// @brief Waits for all of the provided Task objects to complete execution.
/// @param tasks An array of Task instances on which to wait.
/// @param cancellationToken A CancellationToken to observe while waiting for the tasks to complete.
/// @throws System.OperationCanceledException if the cancellationToken is cancelled.
ASPOSECPP_SHARED_API void WaitAll(const ArrayPtr<TaskPtr>& tasks, const CancellationToken& cancellationToken);

/// @brief Waits for all of the provided Task objects to complete execution.
/// @param tasks An array of Task instances on which to wait.
ASPOSECPP_SHARED_API void WaitAll(const ArrayPtr<TaskPtr>& tasks);

/// @brief Waits for any of the provided Task objects to complete execution.
/// @param tasks An array of Task instances on which to wait.
/// @param cancellationToken A CancellationToken to observe while waiting for the tasks to complete.
/// @return The index of the completed task in the tasks array.
/// @throws System.OperationCanceledException if the cancellationToken is cancelled.
ASPOSECPP_SHARED_API int32_t WaitAny(const ArrayPtr<TaskPtr>& tasks, const CancellationToken& cancellationToken);

/// @brief Waits for any of the provided Task objects to complete execution.
/// @param tasks An array of Task instances on which to wait.
/// @return The index of the completed task in the tasks array.
ASPOSECPP_SHARED_API int32_t WaitAny(const ArrayPtr<TaskPtr>& tasks);

/// @brief Creates a task that will complete when all of the supplied tasks have completed.
/// @param tasks The tasks to wait on for completion.
/// @return A task that represents the completion of all of the supplied tasks.
ASPOSECPP_SHARED_API TaskPtr WhenAll(const ArrayPtr<TaskPtr>& tasks);

/// @brief Creates a task that will complete when all of the supplied tasks have completed.
/// @param tasks The tasks to wait on for completion.
/// @return A task that represents the completion of all of the supplied tasks.
ASPOSECPP_SHARED_API TaskPtr WhenAll(const SharedPtr<Collections::Generic::IEnumerable<TaskPtr>>& tasks);

/// @brief Creates a task that will complete when all of the supplied tasks have completed.
/// @tparam TResult The type of the completed tasks' results.
/// @param tasks The tasks to wait on for completion.
/// @return A task that returns an array of all the results when all tasks complete.
template <typename TResult>
RTaskPtr<ArrayPtr<TResult>> WhenAll(const SharedPtr<Collections::Generic::IEnumerable<RTaskPtr<TResult>>>& tasks)
{
    return WhenAll(tasks->LINQ_ToArray());
}

/// @brief Creates a task that will complete when all of the supplied tasks have completed.
/// @tparam TResult The type of the completed tasks' results.
/// @param tasks The tasks to wait on for completion.
/// @return A task that returns an array of all the results when all tasks complete.
template <typename TResult>
RTaskPtr<ArrayPtr<TResult>> WhenAll(const ArrayPtr<RTaskPtr<TResult>>& tasks)
{
    auto size = tasks->get_Length();
    if (size == 0)
    {
        return FromResult(MakeArray<TResult>(0));
    }
    else if (size == 1)
    {
        return tasks[0]->ContinueWith(Func<TaskPtr, ArrayPtr<TResult>>([task = tasks[0]](const TaskPtr&) mutable
        {
            auto result = task->get_Result();
            task = nullptr;
            return MakeArray<TResult>({result});
        }));
    }
    else return WhenAll(tasks->template LINQ_Cast<TaskPtr>())->ContinueWith(Func<TaskPtr, ArrayPtr<TResult>>([tasks_copy = tasks, size](const TaskPtr&) mutable
    {
        auto result = MakeArray<TResult>(size);
        for (auto i = 0; i < size; ++i)
        {
            result[i] = tasks_copy[i]->get_Result();
        }
        tasks_copy = nullptr;
        return result;
    }));
}

/// @brief Creates a task that will complete when any of the supplied tasks have completed.
/// @param tasks The tasks to wait on for completion.
/// @return A task that represents the completion of one of the supplied tasks.
ASPOSECPP_SHARED_API RTaskPtr<TaskPtr> WhenAny(const SharedPtr<Collections::Generic::IEnumerable<TaskPtr>>& tasks);

/// @brief Creates a task that will complete when any of the supplied tasks have completed.
/// @param tasks The tasks to wait on for completion.
/// @return A task that represents the completion of one of the supplied tasks.
ASPOSECPP_SHARED_API RTaskPtr<TaskPtr> WhenAny(const ArrayPtr<TaskPtr>& tasks);

/// @brief Creates a task that will complete when any of the supplied tasks have completed.
/// @tparam TResult The type of the completed task's result.
/// @param tasks The tasks to wait on for completion.
/// @return A task that returns the first completed task when any task completes.
template <typename TResult>
RTaskPtr<RTaskPtr<TResult>> WhenAny(const ArrayPtr<RTaskPtr<TResult>>& tasks)
{
    return WhenAny(tasks->template LINQ_Cast<TaskPtr>())->ContinueWith(Func<RTaskPtr<TaskPtr>, RTaskPtr<TResult>>([](const RTaskPtr<TaskPtr>& task)
    {
        return ExplicitCast<ResultTask<TResult>>(task->get_Result());
    }));
}

/// @brief Creates a task that will complete when any of the supplied tasks have completed.
/// @tparam TResult The type of the completed task's result.
/// @param tasks The tasks to wait on for completion.
/// @return A task that returns the first completed task when any task completes.
template <typename TResult>
RTaskPtr<RTaskPtr<TResult>> WhenAny(const SharedPtr<Collections::Generic::IEnumerable<RTaskPtr<TResult>>>& tasks)
{
    return WhenAny(tasks->LINQ_ToArray());
}

/// @brief Creates an awaitable task that asynchronously yields back to the current context when awaited.
/// @return A YieldAwaitable that can be awaited to yield control.
/// @details This method is useful for forcing an asynchronous method to yield control,
/// allowing other pending work to be processed before continuing.
ASPOSECPP_SHARED_API Runtime::CompilerServices::YieldAwaitable Yield();

}}} // namespace System::Threading::Tasks
