#pragma once

#include <security/cryptography/xml/xml_dsig_c14_ntransform.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the C14N XML canonicalization transform for a digital signature with comments.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDsigC14NWithCommentsTransform : public XmlDsigC14NTransform
{
    typedef XmlDsigC14NWithCommentsTransform ThisType;
    typedef XmlDsigC14NTransform BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    ASPOSECPP_SHARED_API XmlDsigC14NWithCommentsTransform();
};

}}}} // System::Security::Cryptography::Xml
