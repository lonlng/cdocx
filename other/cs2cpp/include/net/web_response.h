/// @file net/web_response.h
#pragma once

#include <cstdint>
#include <net/web_header_collection.h>
#include <system/idisposable.h>
#include <system/io/stream.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>

namespace System { namespace Net {

/// Represents a web response.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT WebResponse : public System::IDisposable
{
    /// This type.
    typedef WebResponse ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the number of bytes of the resource.
    /// @returns The number of bytes of the resource.
    virtual int64_t get_ContentLength() = 0;
    /// Returns the MIME type of the resource.
    /// @returns The MIME type of the resource.
    virtual String get_ContentType() = 0;
    /// Returns the resource's URI.
    /// @returns The resource's URI.
    virtual System::SharedPtr<Uri> get_ResponseUri() = 0;
    /// Returns the collection of the headers that are associated with the current response.
    /// @returns The collection of the headers that are associated with the current response.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<WebHeaderCollection> get_Headers();
    /// Returns a value that indicates if the current response supports headers.
    /// @returns A value that indicates if the current response supports headers.
    ASPOSECPP_SHARED_API virtual bool get_SupportsHeaders();

    /// Closes the response stream.
    ASPOSECPP_SHARED_API virtual void Close();
    /// @copydoc System::IDisposable::Dispose
    void Dispose() override;

    /// Returns the response stream.
    /// @returns The response stream.
    virtual System::SharedPtr<IO::Stream> GetResponseStream() = 0;

protected:
    /// Constructs a new instance.
    WebResponse();
    /// Disposes the current instance.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    virtual void Dispose(bool disposing);
};

}} // namespace System::Net
