/// @file net/iweb_request_create.h
#pragma once

#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/uri.h>

namespace System { namespace Net {

class WebRequest;

/// Provides the methods for creating the WebRequest class instances.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class IWebRequestCreate : public System::Object
{
    /// This type.
    typedef IWebRequestCreate ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Creates a WebRequest-class instance for the specified resource's URI.
    /// @param uri The resource's URI.
    /// @returns A newly created WebRequest-class instance.
    virtual System::SharedPtr<WebRequest> Create(System::SharedPtr<Uri> uri) = 0;
};

}} // namespace System::Net
