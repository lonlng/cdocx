/// @file net/file_web_response.h
#pragma once

#include <system/collections/ienumerable.h>
#include <system/io/stream.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/uri.h>

#include <net/cookie_collection.h>
#include <net/cookie_container.h>
#include <net/http/http_response_message.h>
#include <net/http_status_code.h>
#include <net/web_header_collection.h>
#include <net/web_response.h>

namespace System { namespace Net {

/// Provides implementation of the WebResponse abstract class to work with the file system.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS FileWebResponse : public System::Net::WebResponse
{
    /// This type.
    typedef FileWebResponse ThisType;
    /// Parent type.
    typedef System::Net::WebResponse BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// @copydoc System::Net::WebResponse::get_ContentLength
    ASPOSECPP_SHARED_API int64_t get_ContentLength() override;
    /// @copydoc System::Net::WebResponse::get_ContentType
    ASPOSECPP_SHARED_API String get_ContentType() override;
    /// @copydoc System::Net::WebResponse::get_Headers
    ASPOSECPP_SHARED_API System::SharedPtr<WebHeaderCollection> get_Headers() override;
    /// @copydoc System::Net::WebResponse::get_ResponseUri
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_ResponseUri() override;
    /// @copydoc System::Net::WebResponse::get_SupportsHeaders
    ASPOSECPP_SHARED_API bool get_SupportsHeaders() override;

    /// Constructs a new instance.
    /// @param uri The URI of the file system response.
    ASPOSECPP_SHARED_API FileWebResponse(System::SharedPtr<Uri> uri);

    /// @copydoc System::Net::WebResponse::GetResponseStream
    ASPOSECPP_SHARED_API System::SharedPtr<IO::Stream> GetResponseStream() override;
    /// @copydoc System::Net::WebResponse::Close
    ASPOSECPP_SHARED_API void Close() override;

protected:
    /// @copydoc System::Net::WebResponse::Dispose
    void Dispose(bool disposing) override;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
private:
    /// The URI of the file system response.
    System::SharedPtr<Uri> _requestUri;
};

}} // namespace System::Net
