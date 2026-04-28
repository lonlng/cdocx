/// @file system/dummy_classes.h
#ifndef __dummy_classes_h__
#define __dummy_classes_h__

#include "system/event.h"
#include "system/eventargs.h"
#include "system/eventhandler.h"
#include "system/uri.h"
#include "system/io/text_writer.h"
#include "system/collections/dictionary.h"
#include <system/component_model/component.h>
#include <system/runtime/serialization/iserializable.h>
#include <net/http_status_code.h>
#include <net/web_response.h>
#include <net/http_web_response.h>
#include <net/http_web_request.h>
#include <net/file_web_response.h>
#include <net/file_web_request.h>

#include "fwd.h"

namespace System {
    namespace Web {

        /// Forward declaration.
        class HttpRequest;
        /// Forward declaration.
        class HttpResponse;

        /// Dummy class making it possible linking translated code with HttpContext references, but not executing it.
        /// Contains no properly implemented members.
        /// Objects of this class should only be allocated using System::MakeObject() function.
        /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
        /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
        class ASPOSECPP_SHARED_CLASS HttpContext : public Object
        {
        public:
            /// Not implemented.
            static System::SharedPtr<HttpContext> get_Current(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            static void set_Current(const System::SharedPtr<HttpContext>& context){ ASPOSE_UNUSED(context); throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            System::SharedPtr<HttpRequest> get_Request(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
        };

        /// Dummy class making it possible linking translated code with HttpResponse references, but not executing it.
        /// Contains no properly implemented members.
        /// Objects of this class should only be allocated using System::MakeObject() function.
        /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
        /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
        class ASPOSECPP_SHARED_CLASS HttpResponse : public Object
        {
        public:
            /// Not implemented.
            HttpResponse(const System::SharedPtr<System::IO::TextWriter>& writer) : Object() { ASPOSE_UNUSED(writer); }
            /// Not implemented.
            void AddHeader(const String& name, const String& value){ ASPOSE_UNUSED(name); ASPOSE_UNUSED(value); throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            void BinaryWrite(const System::ArrayPtr<uint8_t>& buffer){ ASPOSE_UNUSED(buffer); throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            void Clear(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            void ClearContent(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            void ClearHeaders(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            void End(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            SharedPtr<System::IO::Stream> get_OutputStream(){ throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            void set_ContentType(const String& value){ ASPOSE_UNUSED(value); throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
        };

        namespace UI {
            namespace WebControls {

                /// Dummy class making it possible linking translated code with DataGrid references, but not executing it.
                /// Contains no properly implemented members.
                /// Objects of this class should only be allocated using System::MakeObject() function.
                /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
                /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
                class ASPOSECPP_SHARED_CLASS DataGrid : public Object
                {
                public:
                    /// Self pointer type.
                    typedef SharedPtr<DataGrid> ptr;
                };
            }
        }

    }

    namespace Net {

        class WebHeaderCollection;
        class HttpWebResponse;
        class FileWebResponse;

        /// Dummy class making it possible linking translated code with FtpWebResponse references, but not executing it.
        /// Contains no properly implemented members.
        /// Objects of this class should only be allocated using System::MakeObject() function.
        /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
        /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
        class ASPOSECPP_SHARED_CLASS FtpWebResponse : public WebResponse
        {
            /// ThisType alias
            typedef FtpWebResponse ThisType;
            /// BaseType alias
            typedef System::Net::WebResponse BaseType;

            /// ThisTypeBaseTypesInfo alias
            typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;

            /// RTTI info
            RTTI_INFO(System::Net::FtpWebResponse, ThisTypeBaseTypesInfo)

        public:
        
            /// Not implemented.
            int64_t get_ContentLength() override { throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            System::String get_ContentType() override { throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            System::SharedPtr<WebHeaderCollection> get_Headers() override { throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            System::SharedPtr<System::Uri> get_ResponseUri() override { throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
        
            /// Not implemented.
            void Close() override { throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
            /// Not implemented.
            System::SharedPtr<System::IO::Stream> GetResponseStream() override { throw NotImplementedException(ASPOSE_CURRENT_FUNCTION); }
        };
        
        class ICredentials;
        class WebRequest;
        class HttpWebRequest;
        class FileWebRequest;

        /// Implements a File Transfer Protocol (FTP) client.
        /// Dummy class making it possible linking translated code with FtpWebRequest references, but not executing it.
        /// Contains no properly implemented members.
        class ASPOSECPP_SHARED_CLASS FtpWebRequest : public System::Net::WebRequest
        {
            /// ThisType alias
            typedef FtpWebRequest ThisType;
            /// BaseType alias
            typedef System::Net::WebRequest BaseType;


            /// ThisTypeBaseTypesInfo alias
            typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;

            /// RTTI info
            RTTI_INFO(System::Net::FtpWebRequest, ThisTypeBaseTypesInfo);
        };

        /// Dummy class making it possible linking translated code with ServicePoint references, but not executing it.
        /// Contains no properly implemented members.
        /// Objects of this class should only be allocated using System::MakeObject() function.
        /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
        /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
        class ServicePoint;

    } // namespace Net
} // namespace System

#endif
