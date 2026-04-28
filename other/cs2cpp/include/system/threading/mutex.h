/// @file system/threading/mutex.h
#pragma once
#include "system/object.h"
#include "system/threading/wait_handle.h"

namespace System { namespace Threading {
class MutexHandler;

/// Mutex implemnetation.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include "system/threading/mutex.h"
/// #include "system/threading/thread.h"
/// #include "system/console.h"
/// #include "system/convert.h"
/// #include "system/smart_ptr.h"
/// #include "system/string.h"
///
/// int main()
/// {
///   auto mutex = System::MakeObject<System::Threading::Mutex>();
///
///   System::String str;
///
///   const int THREADS_COUNT = 3;
///   std::vector<System::SharedPtr<System::Threading::Thread>> threads;
///   threads.reserve(THREADS_COUNT);
///
///   for (auto i = 0; i < THREADS_COUNT; ++i)
///   {
///     threads.push_back(System::MakeObject<System::Threading::Thread>([&mutex, &str]()
///     {
///       mutex->WaitOne();
///
///       str += u"Thread " + System::Convert::ToString(System::Threading::Thread::GetCurrentThreadId()) + u" started." + System::Environment::get_NewLine();
///
///       System::Threading::Thread::Sleep(200);
///
///       str += u"Thread " + System::Convert::ToString(System::Threading::Thread::GetCurrentThreadId()) + u" ended." + System::Environment::get_NewLine();
///
///       mutex->ReleaseMutex();
///     }));
///
///     threads[i]->Start();
///   }
///
///   System::Threading::Thread::Sleep(700);
///
///   System::Console::WriteLine(str);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// Thread 1 started.
/// Thread 1 ended.
/// Thread 2 started.
/// Thread 2 ended.
/// Thread 3 started.
/// Thread 3 ended.
/// */
/// @endcode
class ASPOSECPP_SHARED_CLASS Mutex : public WaitHandle
{
    /// RTTI information.
    RTTI_INFO(System::Threading::Mutex, ::System::BaseTypesInfo<System::Threading::WaitHandle>);

public:
    /// Constructs unowned mutex.
    ASPOSECPP_SHARED_API Mutex();
    /// Constructor.
    /// @param initiallyOwned If true, the mutex being constructed is owned initially.
    ASPOSECPP_SHARED_API Mutex(bool initiallyOwned);
    /// Constructor.
    /// @param initiallyOwned If true, the mutex being constructed is owned initially.
    /// @param name Name of the mutex.
    ASPOSECPP_SHARED_API Mutex(bool initiallyOwned, const String& name);

    /// Releases the mutex.
    ASPOSECPP_SHARED_API void ReleaseMutex();

    /// Resets mutex state. Not implemented.
    virtual ASPOSECPP_SHARED_API bool Reset();
    /// Set mutex to signalled state. Not implemented.
    virtual ASPOSECPP_SHARED_API bool Set();

    /// Locks mutex. Performs unlimited waiting if neccessary.
    /// @return Always returns true as it does not return until mutex is locked.
    virtual ASPOSECPP_SHARED_API bool WaitOne() override;
    /// Locks mutex. Performs waiting if neccessary.
    /// @param millisecondsTimeout Waiting timeout in milliseconds.
    /// @return Returns true if mutex was locked or false if timeout exceeded.
    virtual ASPOSECPP_SHARED_API bool WaitOne(int millisecondsTimeout) override;
    /// Locks mutex. Performs waiting if neccessary.
    /// @param timeout A System::TimeSpan that represents the number of milliseconds to wait, or a System::TimeSpan that represents -1 milliseconds to wait indefinitely.
    /// @return Returns true if mutex was locked or false if timeout exceeded.
    virtual ASPOSECPP_SHARED_API bool WaitOne(TimeSpan timeout) override;

    /// Erases a named mutex from the system.
    /// @return false on error
    static ASPOSECPP_SHARED_API bool Remove(const String& mutexName);

private:
    /// Mutex implemnetation.
    std::unique_ptr<MutexHandler> m_mutex_handler;

    /// Create mutex implementation.
    /// @param initiallyOwned If true, the mutex being constructed is owned initially.
    /// @param name Name of the mutex. If value is null or empty, the mutex is unnamed.
    static std::unique_ptr<MutexHandler> CreateMutexHandler(bool initiallyOwned, const String& name);
};

}} // namespace System{ namespace Threading{
