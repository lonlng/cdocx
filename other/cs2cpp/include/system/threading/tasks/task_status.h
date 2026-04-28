/// @file system/threading/tasks/task_status.h
#pragma once

namespace System { namespace Threading { namespace Tasks {

// Represents the current stage in the lifecycle of a System.Threading.Tasks.Task.
enum class TaskStatus
{
    // The task has been initialized but has not yet been scheduled.
    Created = 0,
    // The task is waiting to be activated and scheduled internally by the .NET Framework
    // infrastructure.
    WaitingForActivation = 1,
    // The task has been scheduled for execution but has not yet begun executing.
    WaitingToRun = 2,
    // The task is running but has not yet completed.
    Running = 3,
    // The task has finished executing and is implicitly waiting for attached child
    // tasks to complete.
    WaitingForChildrenToComplete = 4,
    // The task completed execution successfully.
    RanToCompletion = 5,
    // The task acknowledged cancellation by throwing an OperationCanceledException
    // with its own CancellationToken while the token was in signaled state, or the
    // task's CancellationToken was already signaled before the task started executing.
    // For more information, see Task Cancellation.
    Canceled = 6,
    // The task completed due to an unhandled exception.
    Faulted = 7
};

}}} // namespace System::Threading::Tasks
