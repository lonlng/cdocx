/// @file system/component_model/do_work_event_handler.h
#pragma once

#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/eventhandler.h>
#include <system/component_model/do_work_event_args.h>

namespace System {
namespace ComponentModel {

/// Handler type to handle DoWork event.
using DoWorkEventHandler = System::EventHandler<System::SharedPtr<DoWorkEventArgs>>;

} // namespace ComponentModel
} // namespace System


