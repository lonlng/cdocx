/// @file net/file_web_request.h
#pragma once

#include <cstdint>
#include <system/async_callback.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>
#include <net/cookie_container.h>
#include <net/http/http_response_message.h>
#include <net/iweb_proxy.h>
#include <net/service_point.h>
#include <net/web_request.h>
#include "security/cryptography/x509_certificates/x509_certificate_collection.h"

namespace System { namespace Net {

class RequestStream;

/// Provides implementation of the WebRequest abstract class to work with the file system.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS FileWebRequest : public System::Net::WebRequest
{
    /// This type.
    typedef FileWebRequest ThisType;
    /// Parent type.
    typedef System::Net::WebRequest BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// @copydoc System::Net::WebRequest::set_Timeout
    ASPOSECPP_SHARED_API void set_Timeout(int timeout) override;

    /// @copydoc System::Net::WebRequest::get_ContentType
    ASPOSECPP_SHARED_API String get_ContentType() override;
    /// @copydoc System::Net::WebRequest::set_ContentType
    ASPOSECPP_SHARED_API void set_ContentType(String value) override;
    /// @copydoc System::Net::WebRequest::get_Headers
    ASPOSECPP_SHARED_API System::SharedPtr<WebHeaderCollection> get_Headers() override;
    /// @copydoc System::Net::WebRequest::set_Headers
    ASPOSECPP_SHARED_API void set_Headers(System::SharedPtr<WebHeaderCollection> value) override;
    /// @copydoc System::Net::WebRequest::get_Method
    ASPOSECPP_SHARED_API String get_Method() override;
    /// @copydoc System::Net::WebRequest::set_Method
    ASPOSECPP_SHARED_API void set_Method(String value) override;
    /// @copydoc System::Net::WebRequest::get_RequestUri
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_RequestUri() override;

    /// Constructs a new instance.
    /// @param uri The URI of the file system request.
    ASPOSECPP_SHARED_API FileWebRequest(System::SharedPtr<Uri> uri);
    /// @copydoc System::Net::WebRequest::GetResponse
    ASPOSECPP_SHARED_API System::SharedPtr<WebResponse> GetResponse() override;
    /// @copydoc System::Net::WebRequest::Abort
    ASPOSECPP_SHARED_API void Abort() override;
    /// @copydoc System::Net::WebRequest::BeginGetRequestStream
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetRequestStream(AsyncCallback callback,
                                                                               System::SharedPtr<Object> state) override;
    /// @copydoc System::Net::WebRequest::EndGetRequestStream
    ASPOSECPP_SHARED_API System::SharedPtr<IO::Stream>
        EndGetRequestStream(System::SharedPtr<IAsyncResult> asyncResult) override;
    /// @copydoc System::Net::WebRequest::BeginGetResponse
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetResponse(AsyncCallback callback,
                                                                          System::SharedPtr<Object> state) override;
    /// @copydoc System::Net::WebRequest::EndGetResponse
    ASPOSECPP_SHARED_API virtual System::SharedPtr<WebResponse>
        EndGetResponse(System::SharedPtr<IAsyncResult> asyncResult) override;

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
private:
    /// The URI of the file system request.
    System::SharedPtr<Uri> _requestUri;
    /// The port number.
    int32_t _timeout;
};

}} // namespace System::Net
