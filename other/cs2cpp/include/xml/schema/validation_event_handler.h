#pragma once

#include <system/shared_ptr.h>
#include <system/multicast_delegate.h>

/// @cond
namespace System
{
class Object;
namespace Xml
{
namespace Schema
{
class ValidationEventArgs;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the callback method that will handle XML schema validation events and the ValidationEventArgs.
/// @param sender The source of the event.
/// **Note** Determine the type of a sender before using it in your code.
/// You cannot assume that the sender is an instance of a particular type.
/// The sender is also not guaranteed to not be null.
/// Always surround your casts with failure handling logic.
/// @param e The event data.
using ValidationEventHandler = System::MulticastDelegate<void(SharedPtr<Object> /*sender*/, SharedPtr<ValidationEventArgs> /*e*/)>;

} // namespace Schema
} // namespace Xml
} // namespace System


