/// @file system/threading/auto_reset_event.h
#if !defined(_auto_reset_event_h_)
#define _auto_reset_event_h_

#include "system/object.h"
#include "system/threading/event_wait_handle.h"

namespace System{ namespace Threading{

/// Event to notify waiting thread that resets automatically.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include "system/threading/auto_reset_event.h"
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
///
///   auto autoResetEvent = System::MakeObject<AutoResetEvent>(true);
///   int x = 0;
///
///   std::vector<System::SharedPtr<Thread>> threads;
///   threads.reserve(threadsCount);
///   for (auto i = 0; i < threadsCount; ++i)
///   {
///     threads.emplace_back(System::MakeObject<Thread>([&x, &autoResetEvent]() -> void {
///       autoResetEvent->WaitOne();
///       x = 1;
///       for (auto i = 0; i < 5; ++i)
///       {
///         std::cout << Thread::get_CurrentThread()->get_Name() << ": " << x++ << std::endl;
///         Thread::Sleep(100);
///       }
///       autoResetEvent->Set();
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
class ASPOSECPP_SHARED_CLASS AutoResetEvent final : public EventWaitHandle
{
    /// RTTI information.
    RTTI_INFO(System::Threading::AutoResetEvent, ::System::BaseTypesInfo<System::Threading::EventWaitHandle>);
public:
    /// Constructor.
    /// @param initialState True for signalled, false for not signalled.
    ASPOSECPP_SHARED_API AutoResetEvent(bool initialState);
};

}}

#endif
