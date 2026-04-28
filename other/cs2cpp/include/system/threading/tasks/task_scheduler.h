/// @file system/threading/tasks/task_scheduler.h
#pragma once

#include <system/object.h>
#include <system/collections/list.h>
#include <functional>

namespace System { namespace Threading { namespace Tasks {

/// Represents an object that handles the low-level work of queuing tasks onto threads.
class ASPOSECPP_SHARED_CLASS TaskScheduler : public Object
{
    using ThisType = TaskScheduler;

public:
    /// Gets the default TaskScheduler instance that is provided by the framework.
    /// @returns The default TaskScheduler instance.
    static ASPOSECPP_SHARED_API const SharedPtr<TaskScheduler>& get_Default();
    /// Gets the TaskScheduler associated with the currently executing task.
    /// @returns The TaskScheduler associated with the currently executing task.
    static ASPOSECPP_SHARED_API SharedPtr<TaskScheduler> get_Current();
    /// Indicates the maximum concurrency level this TaskScheduler is able to support.
    /// @returns An integer that represents the maximum concurrency level.
    virtual ASPOSECPP_SHARED_API int32_t get_MaximumConcurrencyLevel() const;
    /// Gets the unique ID for this TaskScheduler.
    /// @returns The unique ID for this TaskScheduler.
    int32_t get_Id() const {return m_id;}

    /// Creates a TaskScheduler associated with the current thread
    /// @returns A TaskScheduler associated with the current thread.
    static ASPOSECPP_SHARED_API SharedPtr<TaskScheduler> FromCurrentSynchronizationContext();

protected:
    TaskScheduler();

    friend Task;

    ASPOSECPP_SHARED_API bool TryExecuteTask(const SharedPtr<Task>&);
    virtual ASPOSECPP_SHARED_API bool TryExecuteTaskInline(const SharedPtr<Task>&, bool taskWasPreviouslyQueued) = 0;
    virtual ASPOSECPP_SHARED_API void QueueTask(const SharedPtr<Task>&);
    virtual ASPOSECPP_SHARED_API bool TryDequeue(const SharedPtr<Task>&);

    int32_t m_id;

    static int32_t m_next_id;
    static thread_local Task* m_current_task;
};

}}} // namespace System::Threading::Tasks
