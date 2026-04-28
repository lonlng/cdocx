#pragma once

#include <system/string.h>

#include <security/cryptography/xml/key_info_clause.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the XMLDSIG 'KeyName' subelement or the XML encryption 'KeyInfo' element.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS KeyInfoName : public KeyInfoClause
{
    typedef KeyInfoName ThisType;
    typedef KeyInfoClause BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    ASPOSECPP_SHARED_API KeyInfoName();

protected:

    String get_Value();
    void set_Value(String value);

    KeyInfoName(String keyName);

    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml() override;
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> xmlDocument) override;
    ASPOSECPP_SHARED_API void LoadXml(SharedPtr<System::Xml::XmlElement> value) override;

private:

    String _keyName;

};

}}}} // System::Security::Cryptography::Xml
