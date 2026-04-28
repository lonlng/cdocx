/// @file net/icredentials.h
#pragma once

#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>

namespace System { namespace Net {

class NetworkCredential;

/// Provides the authentication interface.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ICredentials : public virtual System::Object
{
    /// This type.
    typedef ICredentials ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns credentials for the specified URI and authentication type.
    /// @param uri The URI for which the authentication type is provided by a client.
    /// @param authType The authentication type.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> GetCredential(System::SharedPtr<Uri> uri,
                                                                                    String authType) = 0;
};
}} // namespace System::Net
