/// @file net/secure_protocols/authentificated_stream.h
#pragma once
#include <system/io/stream.h>

namespace System {
namespace Net {
namespace Security {

/// Contains the methods for passing credentials across a stream.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT AuthenticatedStream : public System::IO::Stream
{
    /// This type.
    typedef AuthenticatedStream ThisType;
    /// Parent type.
    typedef System::IO::Stream BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the stream that is used by the current class instances for sending and receiving data.
    /// @returns The stream that is used by the current class instances for sending and receiving data.
    bool ASPOSECPP_SHARED_API get_LeaveInnerStreamOpen() const;
    /// Returns a value that indicates if authentication is successfully passed.
    /// @returns A value that indicates if authentication is successfully passed.
    virtual ASPOSECPP_SHARED_API bool get_IsAuthenticated() const = 0;
    /// Returns a value that indicates if a server and a client are authenticated.
    /// @returns A value that indicates if a server and a client are authenticated.
    virtual ASPOSECPP_SHARED_API bool get_IsMutuallyAuthenticated() const = 0;
    /// Returns a value that indicates if the data sent using this stream is encrypted.
    /// @returns A value that indicates if the data sent using this stream is encrypted.
    virtual ASPOSECPP_SHARED_API bool get_IsEncrypted() const = 0;
    /// Returns a value that indicates if the data sent using this stream is signed.
    /// @returns A value that indicates if the data sent using this stream is signed.
    virtual ASPOSECPP_SHARED_API bool get_IsSigned() const = 0;
    /// Returns a value that indicates if the local side of the connection is the server.
    /// @returns A value that indicates if the local side of the connection is the server.
    virtual ASPOSECPP_SHARED_API bool get_IsServer() const = 0;

protected:
    /// Constructs a new instance.
    /// @param innerStream The stream that is used for sending and receiving data.
    /// @param leaveInnerStreamOpen If true, closing the current instance has no effect on 'InnerStream'.
    ASPOSECPP_SHARED_API AuthenticatedStream(System::SharedPtr<IO::Stream> innerStream, bool leaveInnerStreamOpen);
    /// Returns the stream that is used for sending and receiving data.
    /// @returns The stream that is used for sending and receiving data.
    ASPOSECPP_SHARED_API System::SharedPtr<IO::Stream> get_InnerStream() const;

private:
    // The stream that is used for sending and receiving data.
    System::SharedPtr<IO::Stream> InnerStream;
    /// If true, closing the current instance has no effect on 'InnerStream'.
    bool    LeaveStreamOpen;
};
}}} // namespace System::Net::Security
