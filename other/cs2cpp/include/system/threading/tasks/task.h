/// @file system/threading/tasks/task.h
#pragma once

#include <functional>
#include <atomic>
#include <mutex>
#include <system/idisposable.h>
#include <system/threading/tasks/task_status.h>
#include <system/threading/cancellation_token.h>
#include <system/action.h>
#include <system/aggregate_exception.h>

namespace System {
template<typename T>
class Nullable;
namespace Threading { namespace Tasks {
class TaskScheduler;
}} // namespace Threading
namespace Runtime { namespace CompilerServices {
class TaskAwaiter;
class ConfiguredTaskAwaitable;
}}

namespace Threading { namespace Tasks {

/// @brief Represents an asynchronous operation that can be awaited and composed with other tasks
/// @details Provides a C++ implementation similar to System.Threading.Tasks.Task in .NET,
///          supporting cancellation, continuations, and async/await patterns
class ASPOSECPP_SHARED_CLASS Task : public IDisposable
{
    using ThisType = Task;

public:
    /// @brief Constructs a Task with an action to execute
    /// @param action The action to execute asynchronously
    ASPOSECPP_SHARED_API Task(const Action<>& action);
    /// @brief Constructs a Task with an action and cancellation token
    /// @param action The action to execute asynchronously
    /// @param cancellationToken Token to monitor for cancellation requests
    ASPOSECPP_SHARED_API Task(const Action<>& action, const CancellationToken& cancellationToken);
    /// @brief Constructs a Task with a stateful action and state object
    /// @param action The action to execute (accepts state object)
    /// @param state User-defined state object passed to the action
    ASPOSECPP_SHARED_API Task(const Action<SharedPtr<Object>>& action, const SharedPtr<Object>& state);
    /// @brief Constructs a Task with stateful action, state, and cancellation token
    /// @param action The action to execute (accepts state object)
    /// @param state User-defined state object passed to the action
    /// @param cancellationToken Token to monitor for cancellation requests
    ASPOSECPP_SHARED_API Task(const Action<SharedPtr<Object>>& action, const SharedPtr<Object>& state,
                              const CancellationToken& cancellationToken);
    /// @brief Destructor
    ASPOSECPP_SHARED_API ~Task();

    static ASPOSECPP_SHARED_API Nullable<int32_t> get_CurrentId();
    /// @brief Gets a completed task (singleton)
    /// @return TaskPtr Shared pointer to a completed task instance
    static ASPOSECPP_SHARED_API const TaskPtr& get_CompletedTask();
    /// @brief Gets whether the task has completed
    /// @return bool True if the task has completed (successfully, faulted, or canceled)
    ASPOSECPP_SHARED_API bool get_IsCompleted() const;
    /// @brief Gets whether the task completed due to cancellation
    /// @return bool True if the task was canceled
    bool get_IsCanceled() const {return m_status == TaskStatus::Canceled;}
    /// @brief Gets the current status of the task
    /// @return TaskStatus The current execution status
    TaskStatus get_Status() const {return m_status;}
    /// @brief Gets the ID for task
    /// @return int32_t The unique ID for this task
    ASPOSECPP_SHARED_API AggregateException get_Exception() const;
    int32_t get_Id() const {return m_id;}
    /// @brief Gets the user-defined state object associated with the task
    /// @return SharedPtr<Object> The state object provided during construction
    const SharedPtr<Object>& get_AsyncState() const {return m_state;}
    /// @brief Gets whether the task completed due to an unhandled exception
    /// @return bool True if the task faulted
    bool get_IsFaulted() const {return m_status == TaskStatus::Faulted;}

    /// @brief Creates a continuation that executes when the task completes
    /// @param continuationAction Action to execute when this task completes
    /// @return TaskPtr A new task representing the continuation
    ASPOSECPP_SHARED_API TaskPtr ContinueWith(const Action<TaskPtr>& continuationAction);
    /// @brief Creates a continuation that executes when the task completes
    /// @tparam TResult A type of task result
    /// @param continuationFunction Function to get result when this task completes
    /// @return RTaskPtr A new task representing the continuation
    template<typename TResult>
    RTaskPtr<TResult> ContinueWith(const Func<TaskPtr, TResult>& continuationFunction);

    /// @brief Gets an awaiter for this task for use with Await
    /// @return Runtime::CompilerServices::TaskAwaiter An awaiter instance
    ASPOSECPP_SHARED_API Runtime::CompilerServices::TaskAwaiter GetAwaiter() const;
    /// @brief Configures how awaits on this task should behave regarding context capture
    /// @param continueOnCapturedContext Whether to continue on the captured context
    /// @return Runtime::CompilerServices::ConfiguredTaskAwaitable A configured awaitable
    ASPOSECPP_SHARED_API Runtime::CompilerServices::ConfiguredTaskAwaitable ConfigureAwait(bool continueOnCapturedContext) const;

    /// @brief Runs the task synchronously on the current thread
    /// @throws If the task has already been started or completed
    ASPOSECPP_SHARED_API void RunSynchronously();
    /// @brief Runs the task synchronously using the specified scheduler
    /// @param scheduler The scheduler to use for execution
    /// @throws If the task has already been started or completed
    ASPOSECPP_SHARED_API void RunSynchronously(const SharedPtr<TaskScheduler>& scheduler);
    /// @brief Starts the task execution using the default scheduler
    /// @throws If the task has already been started
    ASPOSECPP_SHARED_API void Start();
    /// @brief Starts the task execution using the specified scheduler
    /// @param scheduler The scheduler to use for execution
    /// @throws If the task has already been started
    ASPOSECPP_SHARED_API void Start(const SharedPtr<TaskScheduler>& scheduler);
    /// @brief Waits for the task to complete with cancellation support
    /// @param cancellationToken Token to monitor for cancellation while waiting
    /// @throws OperationCanceledException If the wait is canceled
    /// @throws Exception If the task faults
    ASPOSECPP_SHARED_API void Wait(const CancellationToken& cancellationToken);
    /// @brief Waits for the task to complete
    /// @throws Exception If the task faults
    ASPOSECPP_SHARED_API void Wait();

    /// @brief Releases resources associated with the task
    ASPOSECPP_SHARED_API void Dispose() override;

/// Internal implementation. Not for user code

    /// Function type for internal task execution
    using FunctionT = std::function<void()>;

    /// Internal constructor for creating uninitialized tasks
    ASPOSECPP_SHARED_API Task();
    /// Sets the internal function to execute
    void set_Function(const FunctionT& fnc) {m_function = fnc;}
    /// Sets the task status
    ASPOSECPP_SHARED_API void set_Status(TaskStatus status);
    /// Gets the scheduler associated with this task
    ASPOSECPP_SHARED_API const SharedPtr<TaskScheduler>& get_Scheduler() const {return m_scheduler;}
    /// Sets the scheduler associated with this task
    ASPOSECPP_SHARED_API void set_Scheduler(const SharedPtr<TaskScheduler>& scheduler) {m_scheduler = scheduler;}

    /// Activates the task for execution on a scheduler
    ASPOSECPP_SHARED_API void Activate(const SharedPtr<TaskScheduler>& scheduler = nullptr);
    /// Executes the task's function
    ASPOSECPP_SHARED_API void Execute();
    /// Adds a continuation action to be executed upon completion
    ASPOSECPP_SHARED_API void AddCompletionAction(const Action<>& continuation);
    /// Marks the task as completed and finishes task
    ASPOSECPP_SHARED_API void Complete();
    /// Marks the task as cancelled and finishes task
    ASPOSECPP_SHARED_API void Cancel();

protected:
    /// Internal implementation for adding continuations
    ASPOSECPP_SHARED_API void ContinueWithCore(const TaskPtr& continuationTask);
    /// Executes all registered continuations
    ASPOSECPP_SHARED_API void ExecuteContinuations();

    /// Finalizes task completion and executes continuations
    ASPOSECPP_SHARED_API virtual void Finish();

protected:
    // Task ID
    int32_t             m_id;
    /// The function to execute
    FunctionT           m_function;
    /// Current execution status
    TaskStatus          m_status;
    /// Captured exception if the task faulted
    std::exception_ptr  m_exception;
    /// Cancellation token for the task
    CancellationToken   m_cancellation_token;
    /// Scheduler responsible for executing the task
    SharedPtr<TaskScheduler> m_scheduler;
    /// User-defined state object
    SharedPtr<Object>   m_state;
    /// List of continuation tasks to execute after completion
    std::list<Action<>> m_completions;
    /// Mutex protecting continuations operations
    std::mutex          m_completions_mutex;

    /// ID of next task will be created
    static std::atomic<int32_t> m_next_id;
};

}} // namespace Threading::Tasks

namespace Runtime { namespace CompilerServices {

class ASPOSECPP_SHARED_CLASS TaskAwaiter
{
public:
    TaskAwaiter(const TaskPtr& task) : m_task(task) {}

    ASPOSECPP_SHARED_API bool get_IsCompleted() const;
    ASPOSECPP_SHARED_API void OnCompleted(const Action<>& continuation);
    ASPOSECPP_SHARED_API void GetResult() const;

    bool continueOnCapturedContext = false;

private:
    TaskPtr m_task;
};

class ASPOSECPP_SHARED_CLASS ConfiguredTaskAwaitable
{
public:
    ASPOSECPP_SHARED_CLASS ConfiguredTaskAwaitable(const TaskPtr& task, bool continueOnCapturedContext);
    ASPOSECPP_SHARED_API Runtime::CompilerServices::TaskAwaiter GetAwaiter() const;

private:
    TaskPtr m_task;
    bool m_continueOnCapturedContext;
};

}}} // namespace System::Runtime::CompilerServices

#include <system/func.h>
#include <system/threading/tasks/result_task.h>

namespace System { namespace Threading { namespace Tasks {

template <typename TResult>
RTaskPtr<TResult> Task::ContinueWith(const Func<TaskPtr, TResult>& continuationFunction)
{
    auto result = MakeObject<Threading::Tasks::ResultTask<TResult>>(
        Func<TResult>([continuationFunction, task = MakeSharedPtr(this)] { return continuationFunction(task); }));
    ContinueWithCore(result);
    return result;
}

}}} // namespace System::Threading::Tasks
