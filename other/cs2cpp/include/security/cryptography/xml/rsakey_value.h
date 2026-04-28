#pragma once

#include <system/string.h>
#include <security/cryptography/rsa.h>
#include <security/cryptography/xml/key_info_clause.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the 'RSAKeyValue' element of the XML signature.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RSAKeyValue : public KeyInfoClause
{
    typedef RSAKeyValue ThisType;
    typedef KeyInfoClause BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    ASPOSECPP_SHARED_API SharedPtr<RSA> get_Key();
    ASPOSECPP_SHARED_API void set_Key(SharedPtr<RSA> value);

    ASPOSECPP_SHARED_API RSAKeyValue();
    ASPOSECPP_SHARED_API RSAKeyValue(SharedPtr<RSA> key);

protected:
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml() override;
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> xmlDocument) override;
    ASPOSECPP_SHARED_API void LoadXml(SharedPtr<System::Xml::XmlElement> value) override;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    SharedPtr<RSA> _key;
    static const String KeyValueElementName;
    static const String RSAKeyValueElementName;
    static const String ModulusElementName;
    static const String ExponentElementName;
};

}}}} // System::Security::Cryptography::Xml
