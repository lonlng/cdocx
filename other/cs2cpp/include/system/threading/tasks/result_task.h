/// @file system/threading/tasks/result_task.h
#pragma once

#include <functional>
#include <system/object.h>
#include <system/func.h>
#include <system/threading/tasks/task.h>

namespace System { namespace Runtime { namespace CompilerServices {
template<typename T>
class ResultTaskAwaiter;
template<typename T>
class ConfiguredResultTaskAwaitable;
}}

namespace Threading { namespace Tasks {

/// @brief A Task specialization that returns a result value upon completion
/// @tparam T The type of the result value returned by the task
/// @details Represents an asynchronous operation that produces a result,
///          similar to System.Threading.Tasks.Task<TResult> in .NET
template<typename T>
class ResultTask final : public Task
{
    using ThisType = ResultTask<T>;
    using BaseType = Task;

public:
    /// @brief Constructs a ResultTask with a function that returns a value
    /// @param function The function to execute asynchronously that returns a result
    ResultTask(const Func<T>& function) : Task(MakeFunction(function))
    {
    }

    /// @brief Gets the result of the asynchronous operation
    /// @return T The result value produced by the task
    /// @throws If the task faulted, rethrows the captured exception
    /// @throws OperationCanceledException If the task was canceled
    /// @note This method blocks until the task completes if necessary
    T get_Result()
    {
        Wait();
        return m_result;
    }

    /// @brief Configures how awaits on this result task should behave regarding context capture
    /// @param continueOnCapturedContext Whether to continue on the captured context
    /// @return Runtime::CompilerServices::ConfiguredResultTaskAwaitable<T> A configured awaitable for the result
    /// @note This enables fine-grained control over context flow for async/await patterns
    Runtime::CompilerServices::ConfiguredResultTaskAwaitable<T> ConfigureAwait(bool continueOnCapturedContext) const
    {
        return {MakeSharedPtr(this), continueOnCapturedContext};
    }

    using Task::ContinueWith;

    /// @brief Creates a continuation that executes when the result task completes
    /// @param continuationAction Action to execute when this task completes, receiving this result task
    /// @return TaskPtr A new task representing the continuation
    /// @note The continuation action receives this ResultTask to access the result value
    TaskPtr ContinueWith(const Action<RTaskPtr<T>>& continuationAction)
    {
        auto result = MakeObject<Task>(
            std::function<void()>([continuationAction, task = MakeSharedPtr(this)] { continuationAction(task); }));
        ContinueWithCore(result);
        return result;
    }

    /// @brief Creates a continuation that executes when the result task completes
    /// @tparam TNewResult Result type of task continuation
    /// @param continuationFunction Function to get continuation result when this task completes, receiving this result task
    /// @return RTaskPtr A new task representing the continuation
    /// @note The continuation function receives this ResultTask to access the result value
    template<typename TNewResult>
    RTaskPtr<TNewResult> ContinueWith(const Func<RTaskPtr<T>, TNewResult>& continuationFunction)
    {
        auto result = MakeObject<ResultTask<TNewResult>>(std::function<TNewResult()>(
            [continuationFunction, task = MakeSharedPtr(this)] { return continuationFunction(task); }));
        ContinueWithCore(result);
        return result;
    }

    /// @brief Gets an awaiter for this result task for use with Await
    /// @return Runtime::CompilerServices::ResultTaskAwaiter<T> An awaiter instance that returns the result
    /// @note When awaited, the coroutine will resume with the result value available
    Runtime::CompilerServices::ResultTaskAwaiter<T> GetAwaiter() const
    {
        return {MakeSharedPtr(this)};
    }

/// Internal implementation. Not for user code

    /// Internal constructor for creating uninitialized result tasks
    ResultTask()
    {
    }

    /// Internal constructor for creating result tasks with specified result
    ResultTask(const T& result) : m_result(result)
    {
        set_Status(TaskStatus::RanToCompletion);
    }

    /// Sets the result value for the task
    void set_Result(const T& result)
    {
        m_result = result;
    }

    /// Sets the result value for the task and completes it
    void Complete(const T& result)
    {
        set_Result(result);
        BaseType::Complete();
    }

private:
    /// Creates a wrapper function that captures and stores the result
    FunctionT MakeFunction(const Func<T>& func)
    {
        return [func, this]
        {
            set_Result(func());
        };
    }

    /// The result value produced by the task
    T m_result;
};

}} // namespace Threading::Tasks

namespace Runtime { namespace CompilerServices {

template <typename T>
class ResultTaskAwaiter
{
public:
    ResultTaskAwaiter(const RTaskPtr<T>& task) : m_task(task)
    {}

    bool get_IsCompleted() const
    {
        return m_task->get_IsCompleted();
    }

    void OnCompleted(const Action<>& continuation)
    {
        m_task->AddCompletionAction(continuation);
    }

    T GetResult() const
    {
        return m_task->get_Result();
    }

    bool continueOnCapturedContext = false;

private:
    RTaskPtr<T> m_task;
};

template <typename T>
class ConfiguredResultTaskAwaitable
{
public:
    ConfiguredResultTaskAwaitable(const RTaskPtr<T>& task, bool continueOnCapturedContext)
        : m_task(task), m_continueOnCapturedContext(continueOnCapturedContext)
    {}

    Runtime::CompilerServices::ResultTaskAwaiter<T> GetAwaiter() const
    {
        auto result = m_task->GetAwaiter();
        result.continueOnCapturedContext = m_continueOnCapturedContext;
        return result;
    }

private:
    RTaskPtr<T> m_task;
    bool m_continueOnCapturedContext;
};

}} // namespace Runtime::CompilerServices

} // namespace System
