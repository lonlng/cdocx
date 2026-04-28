/// @file system/action.h
/// Contains definition of System::Action<T> delegate.
#ifndef _aspose_system_action_h_
#define _aspose_system_action_h_

#include "system/multicast_delegate.h"

namespace System
{
    /// Delegate type that references methods that have no return value. 
    /// @code
    /// #include <system/action.h>
    ///
    /// using namespace System;
    ///
    /// // The function that prints the passed string.
    /// void PrintString(const String &string)
    /// {
    ///   using namespace std;
    ///   cout << string << endl;
    /// }
    ///
    /// int main()
    /// {
    ///   // Create an instance of Action.
    ///   auto action = Action<String>(std::bind(&PrintString, std::placeholders::_1));
    ///
    ///   // Call the action.
    ///   action(u"Hello, world!");
    ///
    ///   return 0;
    /// }
    /// /*
    /// This code example produces the following output:
    /// Hello, world!
    /// */
    /// @endcode
    /// @tparam Args Argument list of the methods the delegate references.
    template<class... Args>
    using Action = MulticastDelegate<void(Args...)>;

} // namespace System
#endif // _action_h_
