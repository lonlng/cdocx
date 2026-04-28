/// @file system/threading/thread_pool.h
#ifndef _aspose_system_threading_thread_pool_h_
#define _aspose_system_threading_thread_pool_h_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <system/object.h>
#include <system/multicast_delegate.h>
#include <system/shared_ptr.h>

namespace System { namespace Threading {

/// Callback item to be executed once there is a spot.
using WaitCallback = System::MulticastDelegate<void(System::SharedPtr<System::Object>)>;

class ThreadPool;

/// Thread pool internal data.
/// This is a singleton type with memory management done by access function(s).
/// You should never create instances of it directly.
class ASPOSECPP_SHARED_CLASS ThreadPoolImpl
{
public:
    /// Adds work item to queue.
    /// @param callback Callback function to execute.
    /// @param state Callback function argument.
    /// @return Always returns true.
    ASPOSECPP_SHARED_API bool QueueUserWorkItem(WaitCallback callback, const System::SharedPtr<System::Object>& state);

    /// Gets number of available threads.
    /// @param wt Reference to variable to store number of awailable worker threads.
    /// @param cpt Reference to variable to store number of awailable IO threads.
    ASPOSECPP_SHARED_API void GetAvailableThreads(int &wt, int &cpt);
    /// Gets maximal number of concurrent threads.
    /// @param wt Reference to variable to store maximal number of awailable worker threads.
    /// @param cpt Reference to variable to store maximal number of awailable IO threads.
    ASPOSECPP_SHARED_API void GetMaxThreads(int &wt, int &cpt);
    /// Gets minimal number of threads being created by pool.
    /// @param wt Reference to variable to store minimal number of awailable worker threads.
    /// @param cpt Reference to variable to store minimal number of awailable IO threads.
    ASPOSECPP_SHARED_API void GetMinThreads(int &wt, int &cpt);
    /// Sets number of threads owned by pool.
    /// @param wt Maximal number of worker threads.
    /// @param cpt Maximal number of IO threads.
    /// @return True if parameters were accepted, false otherwise.
    ASPOSECPP_SHARED_API bool SetMaxThreads(int wt, int cpt);
    /// Sets minimal number of threads owned by pool.
    /// @param wt Minimal number of worker threads.
    /// @param cpt Minimal number of IO threads.
    /// @return True if parameters were accepted, false otherwise.
    ASPOSECPP_SHARED_API bool SetMinThreads(int wt, int cpt);

    /// Constructor.
    ASPOSECPP_SHARED_API ThreadPoolImpl();
    /// Destructor. Joins all threads if they were not terminated yet.
    ASPOSECPP_SHARED_API ~ThreadPoolImpl();

    /// Gets initialization state singleton.
    /// @return Reference to variable that holds true if initialization was done already and false otherwise.
    static ASPOSECPP_SHARED_API bool& GetInitialized();
    /// Joins all owned threads. Waits infinitely.
    ASPOSECPP_SHARED_API void JoinAll();

protected:
    /// Maximal allowed number of threads to exist simultaneously in the pool.
    std::uint32_t m_max_threads;
    /// Minimal allowed number of threads to be created on request.
    std::uint32_t m_min_threads;
    /// Mutex that blocks thread pool task queue.
    std::mutex m_mutex;
    /// Condition variable used to keep executor threads waiting.
    std::condition_variable m_cv;
    /// Structure that keeps job callback and parameter to be executed.
    typedef std::pair<WaitCallback, System::SharedPtr<System::Object>> Job;
    /// Jobs queue.
    std::queue<Job> m_queue;

    /// Worker thread function.
    ASPOSECPP_SHARED_API void Worker();
    /// Adds worker threads to the pool.
    /// @param amount Number of worker threads to create.
    ASPOSECPP_SHARED_API void AddWorkers(uint32_t amount);
    /// Deletes worker threads from the pool.
    /// @param amount Number of worker threads to delete.
    ASPOSECPP_SHARED_API void DelWorkers(uint32_t amount);
};


/// Thread pool API allowing it pushing jobs into queue to be read by pool of worker threads.
/// This is a static type with no instance services.
/// You should never create instances of it by any means.
/// @code
/// #include "system/threading/thread_pool.h"
/// #include "system/threading/thread.h"
/// #include "system/object.h"
/// #include "system/smart_ptr.h"
/// #include <iostream>
/// #include <mutex>
/// #include <string>
/// #include <thread>
///
/// const std::string &BooleanToString(bool value)
/// {
///   static const std::string True = "True";
///   static const std::string False = "False";
///
///   return value ? True : False;
/// }
///
/// int main()
/// {
///   using namespace System::Threading;
///   std::mutex m;
///
///   const auto threadsCount = std::thread::hardware_concurrency();
///
///   for (unsigned int i = 0; i < threadsCount; ++i)
///   {
///     ThreadPool::QueueUserWorkItem([&m](System::SharedPtr<System::Object> object) -> void {
///       auto thread = Thread::get_CurrentThread();
///       m.lock();
///       std::cout << "Background: " << BooleanToString(thread->get_IsBackground()) <<
///         ", Thread pool: " << BooleanToString(thread->get_IsThreadPoolThread()) <<
///         ", Thread ID: " << thread->get_ManagedThreadId() << std::endl;
///       m.unlock();
///     });
///   }
///
///   ThreadPool::JoinAllThreads();
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// Background: True, Thread pool: True, Thread ID: 1
/// Background: True, Thread pool: True, Thread ID: 3
/// Background: True, Thread pool: True, Thread ID: 5
/// Background: True, Thread pool: True, Thread ID: 6
/// Background: True, Thread pool: True, Thread ID: 9
/// Background: True, Thread pool: True, Thread ID: 1
/// Background: True, Thread pool: True, Thread ID: 7
/// Background: True, Thread pool: True, Thread ID: 2
/// Background: True, Thread pool: True, Thread ID: 4
/// Background: True, Thread pool: True, Thread ID: 3
/// Background: True, Thread pool: True, Thread ID: 12
/// Background: True, Thread pool: True, Thread ID: 8
/// Background: True, Thread pool: True, Thread ID: 5
/// Background: True, Thread pool: True, Thread ID: 6
/// Background: True, Thread pool: True, Thread ID: 16
/// Background: True, Thread pool: True, Thread ID: 11
/// */
/// @endcode
class ThreadPool: public System::Object
{
    /// RTTI information.
    RTTI_INFO(System::Threading::ThreadPool, ::System::BaseTypesInfo<System::Object>);
public:
    /// Implementation instance that holds list of jobs and other parameters.
    /// @return Pool implementation object refernce.
    static ASPOSECPP_SHARED_API ThreadPoolImpl& GetInstance();

    /// No copying.
    ThreadPool(const ThreadPool&) = delete;
    /// No copying.
    void operator = (const ThreadPool&) = delete;
    
    /// Puts work item into queue which is present with callback with no parameter.
    /// @param callback Callback function to be used as a job.
    /// @return Always returns true.
    static ASPOSECPP_SHARED_API bool QueueUserWorkItem(WaitCallback callback);
    /// Puts work item into queue which is present with callback with no parameter.
    /// @param callback Callback function to be used as a job.
    /// @param state Job function parameter.
    /// @return Always returns true.
    static ASPOSECPP_SHARED_API bool QueueUserWorkItem(WaitCallback callback, const System::SharedPtr<System::Object>& state);

    /// Gets number of available threads.
    /// @param wt Reference to variable to store number of awailable worker threads.
    /// @param cpt Reference to variable to store number of awailable IO threads.
    static ASPOSECPP_SHARED_API void GetAvailableThreads(int &wt, int &cpt);
    /// Gets maximal number of concurrent threads.
    /// @param wt Reference to variable to store maximal number of awailable worker threads.
    /// @param cpt Reference to variable to store maximal number of awailable IO threads.
    static ASPOSECPP_SHARED_API void GetMaxThreads(int &wt, int &cpt);
    /// Gets minimal number of threads being created by pool.
    /// @param wt Reference to variable to store minimal number of awailable worker threads.
    /// @param cpt Reference to variable to store minimal number of awailable IO threads.
    static ASPOSECPP_SHARED_API void GetMinThreads(int &wt, int &cpt);

    /// Sets number of threads owned by pool.
    /// @param wt Maximal number of worker threads.
    /// @param cpt Maximal number of IO threads.
    /// @return True if parameters were accepted, false otherwise.
    static ASPOSECPP_SHARED_API bool SetMaxThreads(int wt, int cpt);
    /// Sets minimal number of threads owned by pool.
    /// @param wt Minimal number of worker threads.
    /// @param cpt Minimal number of IO threads.
    /// @return True if parameters were accepted, false otherwise.
    static ASPOSECPP_SHARED_API bool SetMinThreads(int wt, int cpt);

    /// Joins all owned threads. Waits infinitely.
    static ASPOSECPP_SHARED_API void JoinAllThreads();
};

}} // System::Threading

#endif
