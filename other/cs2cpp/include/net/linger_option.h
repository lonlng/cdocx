/// @file net/linger_option.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Specifies whether a socket will remain connected after a call to the Close() or Close() methods. It also specifies
/// the period the socket will remain connected if sending of the data continues.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS LingerOption : public System::Object
{
    /// This type.
    typedef LingerOption ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @returns A value that indicates if the socket will delay closing in an attempt to send all pending data.
    ASPOSECPP_SHARED_API bool get_Enabled();
    /// Sets a value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @param value A value that must be set.
    ASPOSECPP_SHARED_API void set_Enabled(bool value);
    /// Gets a delay timeout in seconds.
    /// @returns A delay timeout in seconds.
    ASPOSECPP_SHARED_API int32_t get_LingerTime();
    /// Sets a delay timeout in seconds.
    /// @param value A value that must be set.
    ASPOSECPP_SHARED_API void set_LingerTime(int32_t value);

    /// Constructs a new instance.
    /// @param enable A value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @param seconds A delay timeout in seconds.
    ASPOSECPP_SHARED_API LingerOption(bool enable, int32_t seconds);
};
} // namespace Sockets
} // namespace Net
} // namespace System
