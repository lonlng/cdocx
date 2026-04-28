/// @file system/threading/thread.h
#ifndef _aspose_system_threading_thread_h_
#define _aspose_system_threading_thread_h_

#include <thread>
#include <mutex>
#include <condition_variable>

#include <system/multicast_delegate.h>
#include <system/globalization/culture_info.h>
#include <system/threading/thread_state.h>



namespace System { 
    
    namespace ComponentModel {
        class BackgroundWorker;
    }

    namespace Threading {

/// Thread function with single parameter.
using ParameterizedThreadStart = System::MulticastDelegate<void(System::SharedPtr<System::Object>)>;
/// Thread function with no parameters.
using ThreadStart = System::MulticastDelegate<void()>;

/// Thread implementation.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include "system/threading/thread.h"
/// #include "system/smart_ptr.h"
///
/// int main()
/// {
///   auto thread = System::MakeObject<System::Threading::Thread>([]()
///   {
///     std::cout << "Child thread ID: " << System::Threading::Thread::GetCurrentThreadId() << std::endl;
///     System::Threading::Thread::Sleep(200);
///   });
///
///   std::cout << "Main thread ID: " << System::Threading::Thread::GetCurrentThreadId() << std::endl;
///
///   thread->Start();
///   thread->Join();
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// Main thread ID: 2
/// Child thread ID: 1
/// */
/// @endcode
class ASPOSECPP_SHARED_CLASS Thread final: public System::Object
{
    /// Friendship declaration for optimization.
    friend class ThreadPoolImpl;
    friend class System::ComponentModel::BackgroundWorker;

public:
    /// Constructor.
    ASPOSECPP_SHARED_API Thread();
    /// Constructor.
    /// @param thread_function Function to be executed by thread.
    ASPOSECPP_SHARED_API Thread(ThreadStart thread_function);
    /// Constructor.
    /// @param thread_function Function to be executed by thread.
    ASPOSECPP_SHARED_API Thread(ParameterizedThreadStart thread_function);

    /// Copies TLS data from different thread.
    /// @param t Thread to copy data from.
    /// @return Self reference.
    ASPOSECPP_SHARED_API Thread & operator = (const Thread &t);
    /// Copy constructor.
    /// @param t Thread to copy data from.
    ASPOSECPP_SHARED_API Thread(Thread &t);
    /// Destructor.
    virtual ASPOSECPP_SHARED_API ~Thread();

    /// Gets thread culture.
    /// @return Culture used by thread.
    ASPOSECPP_SHARED_API SharedPtr<Globalization::CultureInfo> get_CurrentCulture();
    /// Sets thread culture.
    /// @param ci Culture to be used by thread.
    ASPOSECPP_SHARED_API void set_CurrentCulture(const SharedPtr<Globalization::CultureInfo>& ci);

    /// Gets object which describes current thread.
    /// @return Thread object.
    static ASPOSECPP_SHARED_API System::SharedPtr<Thread> get_CurrentThread();

    /// Gets user interface culture used by thread.
    /// @return Culture used by thread UI.
    ASPOSECPP_SHARED_API SharedPtr<Globalization::CultureInfo> get_CurrentUICulture();
    /// Sets user interface culture used by thread.
    ASPOSECPP_SHARED_API void set_CurrentUICulture(const SharedPtr<Globalization::CultureInfo>& ci);

    /// Checks whether thread is alive.
    /// @return True if thread is executing or joining, false otherwise.
    ASPOSECPP_SHARED_API bool get_IsAlive();
    /// Checks whether thread is background.
    /// @return True is thread is background, false otherwise.
    ASPOSECPP_SHARED_API bool get_IsBackground();
    /// Sets thread to background or foreground.
    /// @param is_background If true, set thread to background, otherwise to foreground.
    ASPOSECPP_SHARED_API void set_IsBackground(bool is_background);
    /// Checks if thread is owned by a thread pool.
    /// @return True if thread is part of ThreadPool, false otherwise.
    ASPOSECPP_SHARED_API bool get_IsThreadPoolThread();
    /// Gets identifier of thread. Can be got from OS, but if OS thread identifier exceeds int limits, ids of threads can intersect.
    /// @return Pseudo-unique thread identifier.
    ASPOSECPP_SHARED_API int get_ManagedThreadId() const;
    /// Gets thread name.
    /// @return Thread name.
    ASPOSECPP_SHARED_API System::String get_Name();
    /// Sets thread name.
    /// @param name Thread name.
    ASPOSECPP_SHARED_API void set_Name(const System::String& name);

    /// Gets thread state.
    /// @return State of controlled thread.
    ASPOSECPP_SHARED_API ThreadState get_ThreadState();

    /// Joins managed thread. Performs unlimited waiting if required.
    ASPOSECPP_SHARED_API void Join();
    /// Joins managed thread. Performs limited waiting.
    /// @param millisecondsTimeout Waiting timeout in milliseconds.
    /// @return True if thread was successfully joined, false if timeout exceeded.
    ASPOSECPP_SHARED_API bool Join(int millisecondsTimeout);
    /// Joins managed thread. Performs limited waiting.
    /// @param timeout A TimeSpan set to the amount of time to wait for the thread to terminate.
    /// @return True if thread was successfully joined, false if timeout exceeded.
    ASPOSECPP_SHARED_API bool Join(TimeSpan timeout);
    /// Stops current thread for specified timeout.
    /// @param millisecondsTimeout Timeout to sleep in milliseconds.
    static ASPOSECPP_SHARED_API void Sleep(int millisecondsTimeout);
    /// Stops current thread for specified timeout.
    /// @param timeout Timeout to sleep.
    static ASPOSECPP_SHARED_API void Sleep(TimeSpan timeout);
    /// Waits for specific number of loop iterations.
    /// @param iterations How many loops to wait for.
    static ASPOSECPP_SHARED_API void SpinWait(int iterations);

    /// Starts thread using null argument object.
    ASPOSECPP_SHARED_API void Start();
    /// Starts thread.
    /// @param o Object to pass to thread function as argument.
    ASPOSECPP_SHARED_API void Start(const System::SharedPtr<System::Object>& o);
    /// Aborts thread. Not implemented.
    ASPOSECPP_SHARED_API void Abort();
    /// Interrupt thread. Not implemented.
    ASPOSECPP_SHARED_API void Interrupt();
    /// Yields thread.
    static ASPOSECPP_SHARED_API bool Yield();

    /// Gets identifier of current thread.
    /// @return Pseudo-unique identifier of current thread.
    static ASPOSECPP_SHARED_API int GetCurrentThreadId();

    /// @see Object::GetHashCode
    virtual ASPOSECPP_SHARED_API int GetHashCode() const override;

    /// Synchronizes memory access 
    static ASPOSECPP_SHARED_API void MemoryBarrier();

private:
    /// Data describing the thread.
    struct TlsData
    {
        /// Thread name.
        System::String name;
        /// Thread state.
        ThreadState state = Unstarted;
        /// Whether the thread is background.
        bool is_backgroung = false;
        /// Whether the thread is owned by ThreadPool.
        bool is_thread_pool_thread = false;
        // Whether the thread is ready
        bool is_ready = false;
        /// Timed mutex
        std::timed_mutex m_timed_mutex;
        /// Sleep condition variable
        std::condition_variable m_cv_sleep;
        /// Mutex for sleep condition variable
        std::mutex m_mtx_cv_sleep;
        ///Thread id
        int m_thread_id;
        ///Default ctor
        TlsData();
    };

    /// Whether thread function awaits argument.
    bool m_is_pts;
    /// Thread function with object argument.
    ParameterizedThreadStart m_pts;
    /// Thread function without arguments.
    ThreadStart m_ts;
    /// Controlled thread.
    std::thread m_thread;
    /// Gets data associated with a thread.
    static std::shared_ptr<TlsData>& GetTlsData();
    /// Thread data.
    std::shared_ptr<TlsData> m_data;

    /// Thread execution wrapper which calls worker function and sets thread state and other data.
    static void StartHelper(const SharedPtr<Thread>& thread, const ThreadStart& worker);

    /// Checks that the timeout parameter is not greater than the INT32_MAX value.
    /// @param timeout A TimeSpan class instance to check.
    /// @throws ArgumentOutOfRangeException If a passed value is greater than the INT32_MAX value.
    static ASPOSECPP_SHARED_API void CheckIsValidTimeout(TimeSpan timeout);

    /// Initializes TlsData object
    static ASPOSECPP_SHARED_API void InitTlsData();
};

}} // namespace System::Threading

#endif // _aspose_system_threading_thread_h_
