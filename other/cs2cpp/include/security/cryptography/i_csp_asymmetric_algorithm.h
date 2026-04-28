/// @file security/cryptography/i_csp_asymmetric_algorithm.h
#pragma once

#include <system/array.h>
#include <security/cryptography/csp_key_container_info.h>

namespace System { namespace Security { namespace Cryptography {

/// Asymmetric algorithm base class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ICspAsymmetricAlgorithm : public virtual System::Object
{
    /// This type.
    typedef ICspAsymmetricAlgorithm ThisType;
    /// Base class.
    typedef System::Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a CspKeyContainerInfo object.
    virtual ASPOSECPP_SHARED_API SharedPtr<CspKeyContainerInfo> get_CspKeyContainerInfo() = 0;

    /// Exports blob with key information.
    /// @param include_private_parameters True to include private key, false otherwise.
    /// @return Exported data blob.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr ExportCspBlob(bool include_private_parameters) = 0;

    /// Imports key information from data blob.
    /// @param raw_data Previously imported CSP data.
    virtual ASPOSECPP_SHARED_API void ImportCspBlob(ByteArrayPtr raw_data) = 0;
};

}}} // namespace System::Security::Cryptography
