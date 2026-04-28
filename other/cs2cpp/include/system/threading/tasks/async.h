/// @file system/threading/tasks/async.h
/// @brief Containis support routines for implementing await-async code on C++ side
#pragma once

#include <functional>
#include <system/object_ext.h>
#include <system/action.h>
#include <system/threading/tasks/result_task.h>
#include <system/threading/tasks/task_status.h>
#include <system/details/dereference.h>

namespace System { namespace Details {

/// @brief Base context for managing asynchronous operations and state machines
/// @details Provides facilities for awaiting asynchronous operations, managing execution stages,
/// and controlling flow continuation in async state machines
struct ASPOSECPP_SHARED_CLASS AsyncContextBase
{
    /// @brief Sets the current execution stage of the async state machine
    /// @param s The stage identifier to set
    void Step(int32_t s) {stage = s;}
    /// @brief Continues execution of the async state machine after return from Await call
    ASPOSECPP_SHARED_API void Continue();
    /// @brief Awaits an asynchronous operation without capturing the result
    /// @tparam T Type of the awaitable object
    /// @param awaitee The awaitable object to wait for
    /// @param step The stage to set when awaiting complete
    /// @return bool True if the operation was not completed and awaiting is necessary,
    ///              false if the operation was already completed
    /// @note The async state machine will resume at the specified stage after completion
    template<typename T>
    bool Await(const T& awaitee, int32_t step)
    {
        return AwaitImpl(awaitee, step, [](const auto& awaiter) { awaiter.GetResult(); });
    }
    /// @brief Awaits an asynchronous operation and captures the result
    /// @tparam T Type of the awaitable object
    /// @tparam V Type of the value to capture
    /// @param awaitee The awaitable object to wait for
    /// @param value Reference to store the result of the awaitable operation
    /// @param step The stage to set when awaiting complete
    /// @return bool True if the operation was not completed and awaiting is necessary,
    ///              false if the operation was already completed
    /// @note The result will be assigned to 'value' when the operation completes
    template <typename T, typename V>
    bool Await(const T& awaitee, V& value, int32_t step)
    {
        return AwaitImpl(awaitee, step, [&value](const auto& awaiter) { value = ExplicitCast<V>(awaiter.GetResult()); });
    }

    /// @brief The call operator needed to make the state machine behave like a function
    ASPOSECPP_SHARED_API void operator()();

    /// @brief Current stage of the async state machine execution
    int32_t stage = 0;

protected:
    /// @brief Alias for functor being called when awaited operation completes
    using Continuer = std::function<void()>;

    /// @brief Abstract getter for task related to this state machine
    virtual Threading::Tasks::Task* get_Task() const = 0;
    /// @brief Abstract executer of function related to this state machine
    virtual void Execute() = 0;
    /// @brief Internal implementation for awaiting asynchronous operations
    /// @tparam AwaiteeT Type of the awaitable object
    /// @tparam ContinuerT Type of the continuation function
    /// @param awaitee The awaitable object to wait for
    /// @param step The stage to set when awaiting
    /// @param continuer Function to handle the result when the operation completes
    /// @return bool True if awaiting was necessary, false if operation was already complete
    /// @details Sets up continuation callbacks and manages task state transitions
    template <typename AwaiteeT, typename ContinuerT>
    bool AwaitImpl(const AwaiteeT& awaitee, int32_t step, const ContinuerT& continuer)
    {
        stage = step;

        // Getting awaiter instance
        auto awaiter = Dereference(awaitee).GetAwaiter();

        // Trying to avoid sleeping if awaiter completed already
        if (awaiter.get_IsCompleted())
        {
            continuer(awaiter);
            return false;
        }

        // Going to suspend
        Suspend([awaiter, continuer]() { continuer(awaiter); });

        // Setting up resume context (we need to get it here because resuming should be executed in other context)
        auto continuationContext = GetResumeScheduler(awaiter.continueOnCapturedContext);

        // Setting up resume action
        awaiter.OnCompleted(Action<>([this, continuationContext] { Resume(continuationContext); }));

        return true;
    }
    /// @Internal method called to suspend async task until awaiting task completes
    ASPOSECPP_SHARED_API void Suspend(Continuer&& continuer);
    /// @Internal method called to compute scheduler where task should be resumed after await
    ASPOSECPP_SHARED_API SharedPtr<Threading::Tasks::TaskScheduler> GetResumeScheduler(bool continueOnCapturedContext) const;
    /// @Internal method called to wake async task after awaited task completes
    ASPOSECPP_SHARED_API void Resume(const SharedPtr<Threading::Tasks::TaskScheduler>& context);

    /// @brief Continuation function to execute when awaiting operation completes
    Continuer m_continuer;
    /// @brief Flag "function is executing now" to prevent re-entrance activation problem
    bool m_executing = false;
    /// @brief Context on which function will be re-activated when execution completes
    SharedPtr<Threading::Tasks::TaskScheduler> m_activator;
};

/// @brief Alias for async function signature that operates on an AsyncContext
/// @param ctx Reference to the AsyncContext for managing async state
using AsyncFunction = std::function<void(struct AsyncContext&)>;

/// @brief BaseAsyncContext inheritor for operations that do not return a result value
/// @details Provides result storage and handling capabilities in addition to base async functionality
struct AsyncContext : AsyncContextBase
{
    /// @brief Constructs an AsyncContext associated with a Task
    /// @param task Pointer to the Task that this context manages
    AsyncContext(Threading::Tasks::Task* task, const AsyncFunction& fnc) : m_task(task), m_function(fnc)
    {}

    /// @brief Returns from the async operation, completing the task
    ASPOSECPP_SHARED_API void Return();

protected:
    /// @brief Getter for task related to this state machine
    Threading::Tasks::Task* get_Task() const override {return m_task;}
    /// @brief Executer of function related to this state machine
    void Execute() override {m_function(*this);}

    /// @brief Pointer to the associated Task
    Threading::Tasks::Task* m_task;
    /// @brief Associated function
    AsyncFunction m_function;
};

template<typename T>
struct ResultAsyncContext;

/// @brief Alias for async function signature that operates on a ResultAsyncContext and returns a value
/// @tparam T The type of the result value returned by the function
/// @param ctx Reference to the ResultAsyncContext for managing async state and result storage
/// @note Functions of this type are expected to call ctx.Return with a result value
template <typename T>
using ResultAsyncFunction = std::function<void(ResultAsyncContext<T>&)>;

/// @brief BaseAsyncContext inheritor for operations that return a result value
/// @tparam T The type of the result value returned by the asynchronous operation
/// @details Provides result storage and handling capabilities in addition to base async functionality
template<typename T>
struct ResultAsyncContext : AsyncContextBase
{
    /// @brief Constructs a ResultAsyncContext associated with a ResultTask
    /// @param task Pointer to the ResultTask that this context manages
    ResultAsyncContext(Threading::Tasks::ResultTask<T>* task, const ResultAsyncFunction<T>& fnc) : m_result_task(task), m_function(fnc)
    {}

    /// @brief Returns from the async operation with a result value, completing the task
    /// @param result The result value to return from the asynchronous operation
    /// @post The result is stored in the associated ResultTask and the task is marked as completed
    /// @note This will trigger continuation of any awaiting operations with the provided result
    void Return(const T& result)
    {
        m_result_task->set_Result(result);
        m_result_task->set_Status(Threading::Tasks::TaskStatus::RanToCompletion);
    }

protected:
    /// @brief Getter for result task related to this state machine
    Threading::Tasks::Task* get_Task() const override {return m_result_task;}
    /// @brief Executer of function related to this state machine
    void Execute() override {m_function(*this);}

    /// @brief Pointer to the associated ResultTask (specialized Task with result storage)
    Threading::Tasks::ResultTask<T>* m_result_task;
    /// @brief Associated function
    ResultAsyncFunction<T> m_function;
};

} // namespace Details

ASPOSECPP_SHARED_API TaskPtr MakeAsync(const Details::AsyncFunction& fnc);

template<typename T>
RTaskPtr<T> MakeAsync(const Details::ResultAsyncFunction<T>& fnc)
{
    auto result = System::MakeObject<Threading::Tasks::ResultTask<T>>();
    result->set_Function(Details::ResultAsyncContext<T>(result.GetPointer(), fnc));
    result->RunSynchronously();
    return result;
}

} // namespace System
