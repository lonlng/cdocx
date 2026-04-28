/// @file system/threading/tasks/parallel.h
/// @brief Contains support routines for implementing Parallel static class.
/// @details Provides parallel loop constructs similar to .NET's Parallel class.

#pragma once

#include <system/action.h>
#include <system/func.h>
#include <system/object.h>
#include <system/threading/tasks/task_utils.h>

namespace System { namespace Threading { namespace Tasks {

/// @class ParallelLoopResult
/// @brief Provides completion status of a Parallel loop.
/// @details Represents the result of a parallel loop operation, including whether it completed and information about breaks.
class ASPOSECPP_SHARED_CLASS ParallelLoopResult : public Object, public System::Details::BoxableObjectBase
{
    typedef ParallelLoopResult ThisType;
    typedef Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;

public:
    /// @brief Constructs a ParallelLoopResult.
    ParallelLoopResult() : _completed(false) {}

    /// @brief Gets whether the loop ran to completion.
    /// @return true if the loop completed all iterations; otherwise, false.
    bool get_IsCompleted() {return _completed;}
    
    /// @brief Gets the lowest iteration index at which a break occurred.
    /// @return The lowest iteration index where Break was called, or null if no break occurred.
    Nullable<int64_t> get_LowestBreakIteration() {return _lowestBreakIteration;}

protected:
    bool _completed;                            ///< @brief Indicates if the loop completed.
    Nullable<int64_t> _lowestBreakIteration;    ///< @brief Stores the lowest break iteration index.
};

/// @class ParallelOptions
/// @brief Stores options that configure the operation of methods on the Parallel class.
class ASPOSECPP_SHARED_CLASS ParallelOptions : public Object
{
    typedef ParallelOptions ThisType;
    typedef Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;

public:
    /// @brief Constructs a ParallelOptions instance with default values.
    /// @details Default values: TaskScheduler = Default, MaxDegreeOfParallelism = -1 (unlimited),
    /// CancellationToken = get_None().
    ASPOSECPP_SHARED_API ParallelOptions();

    /// @brief Gets the TaskScheduler associated with this ParallelOptions instance.
    /// @return The TaskScheduler used for scheduling tasks.
    const SharedPtr<TaskScheduler>& get_TaskScheduler() {return _scheduler;}
    
    /// @brief Sets the TaskScheduler associated with this ParallelOptions instance.
    /// @param value The TaskScheduler to use for scheduling tasks.
    void set_TaskScheduler(const SharedPtr<TaskScheduler>& value) {_scheduler = value;}
    
    /// @brief Gets the maximum degree of parallelism enabled by this ParallelOptions instance.
    /// @return The maximum number of concurrent tasks.
    int32_t get_MaxDegreeOfParallelism() {return _maxDegreeOfParallelism;}
    
    /// @brief Sets the maximum degree of parallelism enabled by this ParallelOptions instance.
    /// @param value The maximum number of concurrent tasks (must be positive).
    void set_MaxDegreeOfParallelism(int32_t value) {_maxDegreeOfParallelism = value;}
    
    /// @brief Gets the CancellationToken associated with this ParallelOptions instance.
    /// @return The CancellationToken that can be used to cancel parallel operations.
    const CancellationToken& get_CancellationToken() {return _cancellationToken;}
    
    /// @brief Sets the CancellationToken associated with this ParallelOptions instance.
    /// @param value The CancellationToken to use for cancellation.
    void set_CancellationToken(const CancellationToken& value) {_cancellationToken = value;}

protected:
    friend class Parallel;

    /// @brief Gets the effective TaskScheduler to use.
    /// @return The specified TaskScheduler or the default if none was specified.
    ASPOSECPP_SHARED_API SharedPtr<TaskScheduler> get_EffectiveTaskScheduler();
    
    /// @brief Gets the effective maximum concurrency level.
    /// @return The specified MaxDegreeOfParallelism or a computed default based on available processors.
    ASPOSECPP_SHARED_API int32_t get_EffectiveMaxConcurrencyLevel();

private:
    SharedPtr<TaskScheduler> _scheduler;    ///< @brief The task scheduler for parallel operations.
    int32_t _maxDegreeOfParallelism;        ///< @brief The maximum degree of parallelism.
    CancellationToken _cancellationToken;   ///< @brief The cancellation token.
};

/// @class Parallel
/// @brief Provides support for parallel loops and regions.
/// @details This class provides methods for parallel execution of loops and operations.
class ASPOSECPP_SHARED_CLASS Parallel
{
public:
    /// @brief Executes a foreach operation on an IEnumerable in which iterations may run in parallel.
    /// @tparam TSource The type of the data in the source.
    /// @param source An enumerable data source.
    /// @param parallelOptions An object that configures the behavior of this operation.
    /// @param body The delegate that is invoked once per iteration.
    /// @return A ParallelLoopResult structure that contains information on what portion of the loop completed.
    /// @throws System.OperationCanceledException if the CancellationToken in parallelOptions is set.
    /// @details This method partitions the source enumerable and executes the body delegate on multiple threads concurrently.
    template <typename TSource>
    static ParallelLoopResult ForEach(const SharedPtr<Collections::Generic::IEnumerable<TSource>>& source,
        const SharedPtr<ParallelOptions>& parallelOptions, const Action<TSource>& body)
    {
        parallelOptions->get_CancellationToken().ThrowIfCancellationRequested();

        auto enumerator = source->GetEnumerator();
        auto tasks = MakeArray<TaskPtr>(parallelOptions->get_EffectiveMaxConcurrencyLevel());
        auto lock = MakeObject<Object>();

        for (auto& task : tasks)
        {
            task = MakeAsync([=, &lock, &enumerator, &body](System::Details::AsyncContext& __) mutable
            {
                if (parallelOptions->get_CancellationToken().get_IsCancellationRequested())
                {
                    __.Return(); return;
                }

                TSource value;
                {
                    LockContext __guard((lock).GetPointer());
                    if (enumerator->MoveNext())
                    {
                        value = enumerator->get_Current();
                    }
                    else
                    {
                        __.Return(); return;
                    }
                }
                body(value);
            });
        }

        Tasks::WaitAll(tasks, parallelOptions->get_CancellationToken());

        return ParallelLoopResult();
    }

    /// @brief Executes a foreach operation on an IEnumerable in which iterations may run in parallel.
    /// @tparam TSource The type of the data in the source.
    /// @param source An enumerable data source.
    /// @param body The delegate that is invoked once per iteration.
    /// @return A ParallelLoopResult structure that contains information on what portion of the loop completed.
    /// @details Uses default ParallelOptions with unlimited parallelism and no cancellation.
    template<typename TSource>
    static ParallelLoopResult ForEach(const SharedPtr<Collections::Generic::IEnumerable<TSource>>& source, const Action<TSource>& body)
    {
        return ForEach(source, s_defaultParallelOptions, body);
    }

protected:
    /// @brief Default ParallelOptions instance used when no options are specified.
    /// @details Initialized with default values: unlimited parallelism, default task scheduler, no cancellation.
    ASPOSECPP_SHARED_API static SharedPtr<ParallelOptions> s_defaultParallelOptions;
};

}}} // namespace System::Threading::Tasks
