/// @file system/async_callback.h
/// Contains declaration of AsyncCallback typedef.
#ifndef _async_callback_h_
#define _async_callback_h_

#include <system/multicast_delegate.h>
#include <system/shared_ptr.h>

namespace System
{
    class IAsyncResult;
    /// A delegate type that represents a method to be called when asynchronous operation completes.
    using AsyncCallback = System::MulticastDelegate<void(SharedPtr<IAsyncResult>)>;
}
#endif
