/// @file system/threading/tasks/result_value_task.h
#pragma once

#include <system/object.h>
#include <system/nullable.h>
#include <system/iequatable.h>
#include <system/threading/tasks/async.h>

namespace System { namespace Runtime { namespace CompilerServices {
template<typename T>
class ResultValueTaskAwaiter;
template<typename T>
class ConfiguredResultValueTaskAwaitable;
}}

namespace Threading { namespace Tasks {

/// @brief Represents a hybrid task-like type that can wrap either a direct result value or a ResultTask<T>.
/// @details ResultValueTask combines the benefits of ValueTask (reduced allocations for synchronous results)
/// with the ability to wrap existing ResultTask<T> objects.
/// It provides awaitable interface and various task status inspection methods.
/// @tparam T The type of the result produced by the task.
template<typename T>
class ResultValueTask final : public IEquatable<ResultValueTask<T>>, public System::Details::BoxableObjectBase
{
    using ThisType = ResultValueTask<T>;
    using BaseType = Object;

public:
    /// @brief Constructs an empty, uninitialized ResultValueTask.
    /// @remarks The task is not completed and contains no result.
    /// Attempting to get the result will throw an exception.
    ResultValueTask()
    {}
    /// @brief Constructs a completed ResultValueTask with the specified result.
    /// @param result The result value to wrap in a completed task.
    /// @remarks This creates a successfully completed task that immediately returns the value.
    ResultValueTask(const T& result) : m_result(result)
    {}
    /// @brief Constructs a ResultValueTask from a shared pointer to a ResultTask<T>.
    /// @param task The task to wrap. Can be null for an empty task.
    /// @remarks The ResultValueTask will represent the state and result of the provided task.
    ResultValueTask(const RTaskPtr<T>& task) : m_task(task)
    {}

    /// @brief Gets a value indicating whether the task completed due to an unhandled exception.
    /// @return bool True if the task is faulted; otherwise, false.
    /// @remarks Returns false if the task contains a direct result value.
    bool get_IsFaulted() const
    {
        return m_task && m_task->get_IsFaulted();
    }
    /// @brief Gets a value indicating whether the task completed successfully.
    /// @return bool True if the task ran to completion or contains a direct result; otherwise, false.
    bool get_IsCompletedSuccessfully() const
    {
        return (m_task && m_task->get_Status() == TaskStatus::RanToCompletion) || m_result.get_HasValue();
    }
    /// @brief Gets a value indicating whether the task has completed.
    /// @return bool True if the underlying task has completed or contains a direct result; otherwise, false.
    bool get_IsCompleted() const
    {
        return (m_task && m_task->get_IsCompleted()) || m_result.get_HasValue();
    }
    /// @brief Gets a value indicating whether the task completed due to being canceled.
    /// @return bool True if the task was canceled; otherwise, false.
    /// @remarks Returns false if the task contains a direct result value.
    bool get_IsCanceled() const
    {
        return m_task && m_task->get_IsCanceled();
    }
    /// @brief Gets the result of the completed task.
    /// @return T The result value.
    /// @remarks If the task is backed by a ResultTask<T>, this method will await the result and cache it.
    /// Subsequent calls will return the cached value without awaiting.
    T get_Result()
    {
        if (m_task)
        {
            m_result.set_Value(m_task->get_Result());
            m_task.reset();
        }

        return m_result.get_Value();
    }

    /// @brief Converts this ResultValueTask to a shared pointer to ResultTask<T>.
    /// @return RTaskPtr<T> A shared pointer to a ResultTask<T> that represents this operation.
    /// @remarks If the ResultValueTask contains a direct result, creates a completed task with that result.
    /// If it contains a task, returns a shared pointer to that task.
    RTaskPtr<T> AsTask() const
    {
        return m_task ? m_task : MakeObject<ResultTask<T>>(m_result.get_Value());
    }
    /// @brief Configures an awaiter for this task.
    /// @param continueOnCapturedContext true to attempt to marshal the continuation back to the original context
    /// captured; otherwise, false.
    /// @return ConfiguredResultValueTaskAwaitable<T> An object that configures how awaiters behave for this task.
    Runtime::CompilerServices::ConfiguredResultValueTaskAwaitable<T> ConfigureAwait(bool continueOnCapturedContext) const
    {
        return {*this, continueOnCapturedContext};
    }
    /// @brief Determines whether this instance equals another ResultValueTask instance.
    /// @param other The other ResultValueTask to compare with this instance.
    /// @return bool True if the instances are equal; otherwise, false.
    bool Equals(ResultValueTask other) override 
    {
        return *this == other;
    }
    /// @brief Determines whether this instance equals another object.
    /// @param obj The object to compare with this instance.
    /// @return bool True if the object is a ResultValueTask and equal to this instance; otherwise, false.
    bool Equals(System::SharedPtr<System::Object> obj) override
    {
        return System::ObjectExt::Is<ResultValueTask>(obj) && Equals(System::ExplicitCast<ResultValueTask>(obj));
    }
    /// @brief Gets an awaiter for this task to support await expressions.
    /// @return ResultValueTaskAwaiter<T> An awaiter instance for this task.
    /// @remarks This method enables the use of the Await method with ResultValueTask.
    Runtime::CompilerServices::ResultValueTaskAwaiter<T> GetAwaiter() const
    {
        return {*this};
    }

    /// @brief Equality operator for ResultValueTask.
    /// @param other The other ResultValueTask to compare with this instance.
    /// @return bool True if both tasks have the same result value or reference the same underlying task; otherwise,
    /// false.
    /// @details If either instance contains a direct result value, compares the results directly.
    /// Otherwise, compares the underlying task pointers.
    bool operator==(const ResultValueTask& other) const
    {
        if (m_result.get_HasValue() || other.m_result.get_HasValue())
        {
            return m_result == other.m_result;
        }

        return m_task == other.m_task;
    }
    /// @brief Inequality operator for ResultValueTask.
    /// @param other The other ResultValueTask to compare with this instance.
    /// @return bool True if the instances are not equal; otherwise, false.
    bool operator!=(const ResultValueTask& other) const {return !(*this == other);}

private:
    /// @brief Friend declaration to allow the awaiter access to private members.
    friend class Runtime::CompilerServices::ResultValueTaskAwaiter<T>;

    /// @brief The cached result value, if available.
    Nullable<T> m_result;
    /// @brief The underlying task, if this ResultValueTask wraps a ResultTask<T>.
    RTaskPtr<T> m_task;
};

}} // namespace Threading::Tasks

namespace Runtime { namespace CompilerServices {

template <typename T>
class ResultValueTaskAwaiter
{
public:
    ResultValueTaskAwaiter(Threading::Tasks::ResultValueTask<T> task) : m_task(task)
    {}

    bool get_IsCompleted() const
    {
        return m_task.get_IsCompleted();
    }

    void OnCompleted(const Action<>& continuation)
    {
        if (m_task.m_task)
        {
            m_task.m_task->AddCompletionAction(continuation);
        }
    }

    T GetResult() const
    {
        return m_task.get_Result();
    }

    bool continueOnCapturedContext = false;

private:
    // Here, it's 'mutable' because the GetResult() function is const (it doesn't change the state of the awaiter),
    // while the get_Result() function for tasks isn't (it does change their state).
    // The fact that m_task is a value member of the waiter is merely a syntactic coincidence,
    // due to the fact that ValueTask is a value type. Essentially, the waiter merely references it.
    mutable Threading::Tasks::ResultValueTask<T> m_task;
};

template <typename T>
class ConfiguredResultValueTaskAwaitable
{
public:
    ConfiguredResultValueTaskAwaitable(const Threading::Tasks::ResultValueTask<T>& task, bool continueOnCapturedContext)
        : m_task(task), m_continueOnCapturedContext(continueOnCapturedContext)
    {}

    Runtime::CompilerServices::ResultTaskAwaiter<T> GetAwaiter() const
    {
        auto result = m_task.GetAwaiter();
        result.continueOnCapturedContext = m_continueOnCapturedContext;
        return result;
    }

private:
    Threading::Tasks::ResultValueTask<T> m_task;
    bool m_continueOnCapturedContext;
};

}} // namespace Runtime::CompilerServices

template <typename T>
Threading::Tasks::ResultValueTask<T> MakeValueAsync(const Details::ResultAsyncFunction<T>& fnc)
{
    return Threading::Tasks::ResultValueTask<T>(MakeAsync<T>(fnc));
}

} // namespace System
