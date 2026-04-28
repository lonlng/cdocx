#pragma once

#include <system/shared_ptr.h>
#include <system/multicast_delegate.h>

/// @cond
namespace System
{
class Object;
namespace Xml
{
class XmlNodeChangedEventArgs;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents the method that handles XmlDocument::NodeChanged, XmlDocument::NodeChanging, XmlDocument::NodeInserted,
/// XmlDocument::NodeInserting, XmlDocument::NodeRemoved and XmlDocument::NodeRemoving events.
/// @param sender The source of the event.
/// @param e An XmlNodeChangedEventArgs containing the event data.
using XmlNodeChangedEventHandler = System::MulticastDelegate<void(SharedPtr<Object> /*sender*/, SharedPtr<XmlNodeChangedEventArgs> /*e*/)>;
} // namespace Xml
} // namespace System


