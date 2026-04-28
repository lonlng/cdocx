/// @file system/threading/send_or_post_callback.h
#pragma once

#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/multicast_delegate.h>

namespace System {

namespace Threading {

using SendOrPostCallback = System::MulticastDelegate<void(System::SharedPtr<Object>)>;
} // namespace Threading
} // namespace System

