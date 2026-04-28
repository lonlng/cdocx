/// @file system/threading/monitor.h
#pragma once
#include <system/timespan.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/exceptions.h>
#include <cstdint>

namespace System { namespace Threading {

/// Class Monitor provides a mechanism that synchronizes access to objects
/// @code
/// #include "system/threading/monitor.h"
/// #include "system/threading/thread.h"
/// #include "system/smart_ptr.h"
/// #include "system/string.h"
/// #include <iostream>
/// #include <vector>
///
/// int main()
/// {
///   using namespace System::Threading;
///
///   const auto threadsCount = 3;
///   std::cout << "Threads count: " << threadsCount << std::endl;
///   auto locker = System::MakeObject<System::Object>();
///   int x = 0;
///
///   std::vector<System::SharedPtr<Thread>> threads;
///   threads.reserve(threadsCount);
///   for (auto i = 0; i < threadsCount; ++i)
///   {
///     threads.emplace_back(System::MakeObject<Thread>([&x, &locker]() -> void {
///       Monitor::Enter(locker);
///
///       x = 1;
///       for (auto i = 0; i < 5; ++i)
///       {
///         std::cout << Thread::get_CurrentThread()->get_Name() << ": " << x++ << std::endl;
///         Thread::Sleep(100);
///       }
///
///       Monitor::Exit(locker);
///     }));
///     threads.back()->set_Name(System::String("Thread " + std::to_string(i)));
///     threads.back()->Start();
///   }
///
///   Thread::Sleep(threadsCount * 100);
///
///   for (auto& thread : threads)
///   {
///     thread->Join();
///   }
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// Threads count: 3
/// Thread 0: 1
/// Thread 0: 2
/// Thread 0: 3
/// Thread 0: 4
/// Thread 0: 5
/// Thread 1: 1
/// Thread 1: 2
/// Thread 1: 3
/// Thread 1: 4
/// Thread 1: 5
/// Thread 2: 1
/// Thread 2: 2
/// Thread 2: 3
/// Thread 2: 4
/// Thread 2: 5
/// */
/// @endcode
class ASPOSECPP_SHARED_CLASS Monitor : public System::Object
{
    typedef Monitor ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:
    /// Acquires an exclusive lock on a specified object.
    /// @param obj The object on which to acquire the monitor lock.
    /// @throws ArgumentNullException The obj parameter is null.
    ASPOSECPP_SHARED_API static void Enter(const SharedPtr<Object>& obj);
    /// Acquires an exclusive lock on the specified object,
    /// and atomically sets a value that indicates whether the lock was taken
    static ASPOSECPP_SHARED_API void Enter(const System::SharedPtr<Object>& obj, bool& lockTaken);
    /// Releases an exclusive lock on the specified object.
    /// @param obj The object on which to release the lock.
    /// @throw ArgumentNullException The obj parameter is null.
    /// @throw SynchronizationLockException The current thread does not own the lock for the specified object.
    ASPOSECPP_SHARED_API static void Exit(const SharedPtr<Object>& obj);
    /// Attempts to acquire an exclusive lock on the specified object
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool TryEnter(const SharedPtr<Object>& obj);
    /// Attempts to acquire an exclusive lock on the specified object,
    /// and atomically sets a value that indicates whether the lock was taken
    static ASPOSECPP_SHARED_API void TryEnter(const System::SharedPtr<Object>& obj, bool& lockTaken);
    /// Attempts, for the specified number of milliseconds, to acquire an exclusive lock on the specified object
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool TryEnter(const SharedPtr<Object>& obj, int32_t millisecondsTimeout);
    /// Attempts, for the specified amount of time, to acquire an exclusive lock on the specified object
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool TryEnter(const SharedPtr<Object>& obj, TimeSpan timeout);
    /// Attempts, for the specified amount of time, to acquire an exclusive lock on the specified object,
    /// and atomically sets a value that indicates whether the lock was taken
    static ASPOSECPP_SHARED_API void TryEnter(const System::SharedPtr<Object>& obj, int32_t millisecondsTimeout,
                                              bool& lockTaken);
    /// Attempts, for the specified amount of time, to acquire an exclusive lock on the specified object,
    /// and atomically sets a value that indicates whether the lock was taken
    static ASPOSECPP_SHARED_API void TryEnter(const System::SharedPtr<Object>& obj, TimeSpan timeout, bool& lockTaken);
    /// Determines whether the current thread holds the lock on the specified object
    static ASPOSECPP_SHARED_API bool IsEntered(const System::SharedPtr<Object>& obj);
    /// Releases the lock on an object and blocks the current thread until it reacquires the lock.
    /// If the specified time-out interval elapses, the thread enters the ready queue.
    /// Optionally exits the synchronization domain for the synchronized context before the wait
    /// and reacquires the domain afterward.
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool Wait(const SharedPtr<Object>& obj, int32_t millisecondsTimeout, bool exitContext);
    /// Releases the lock on an object and blocks the current thread until it reacquires the lock.
    /// If the specified time-out interval elapses, the thread enters the ready queue.
    /// Optionally exits the synchronization domain for the synchronized context before the wait
    /// and reacquires the domain afterward.
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool Wait(const SharedPtr<Object>& obj, TimeSpan timeout, bool exitContext);
    /// Releases the lock on an object and blocks the current thread until it reacquires the lock.
    /// If the specified time-out interval elapses, the thread enters the ready queue.
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool Wait(const SharedPtr<Object>& obj, int32_t millisecondsTimeout);
    /// Releases the lock on an object and blocks the current thread until it reacquires the lock.
    /// If the specified time-out interval elapses, the thread enters the ready queue.
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool Wait(const SharedPtr<Object>& obj, TimeSpan timeout);
    /// Releases the lock on an object and blocks the current thread until it reacquires the lock
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static bool Wait(const SharedPtr<Object>& obj);
    /// Notifies a thread in the waiting queue of a change in the locked object's state
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static void Pulse(const SharedPtr<Object>& obj);
    /// Notifies all waiting threads of a change in the object's state
    /// Not implemented.
    /// @throw NotImplementedException Always.
    ASPOSECPP_SHARED_API static void PulseAll(const SharedPtr<Object>& obj);
    
private:
    static std::vector<SharedPtr<Object>> m_locked;
};

}} // namespace System::Threading
