#pragma once

#include <xml/xml_element.h>
#include <xml/xml_document.h>
#include <system/shared_ptr.h>
#include <system/object.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class KeyInfo; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// All implementations of KeyInfo subelements must inherit this abstract class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class KeyInfoClause : public Object
{
    typedef KeyInfoClause ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class KeyInfo;

protected:

    ASPOSECPP_SHARED_API KeyInfoClause();

    virtual SharedPtr<System::Xml::XmlElement> GetXml() = 0;
    virtual ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> xmlDocument);
    virtual void LoadXml(SharedPtr<System::Xml::XmlElement> element) = 0;

};

}}}} // System::Security::Cryptography::Xml
