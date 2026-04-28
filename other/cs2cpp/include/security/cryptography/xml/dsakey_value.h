#pragma once

#include <xml/xml_element.h>
#include <xml/xml_document.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <security/cryptography/dsa.h>
#include <security/cryptography/xml/key_info_clause.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the DSA private key.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS DSAKeyValue : public KeyInfoClause
{
    typedef DSAKeyValue ThisType;
    typedef KeyInfoClause BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    ASPOSECPP_SHARED_API SharedPtr<DSA> get_Key();
    ASPOSECPP_SHARED_API void set_Key(SharedPtr<DSA> value);

    ASPOSECPP_SHARED_API DSAKeyValue();
    ASPOSECPP_SHARED_API DSAKeyValue(SharedPtr<DSA> key);

protected:

    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml() override;
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> xmlDocument) override;
    ASPOSECPP_SHARED_API void LoadXml(SharedPtr<System::Xml::XmlElement> value) override;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:

    SharedPtr<DSA> _key;
    static const String KeyValueElementName;
    static const String DSAKeyValueElementName;
    static const String PElementName;
    static const String QElementName;
    static const String GElementName;
    static const String JElementName;
    static const String YElementName;
    static const String SeedElementName;
    static const String PgenCounterElementName;

};

}}}} // System::Security::Cryptography::Xml
