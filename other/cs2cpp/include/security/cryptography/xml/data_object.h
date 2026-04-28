#pragma once

#include <xml/xml_node_list.h>
#include <xml/xml_element.h>
#include <xml/xml_document.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class Signature; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedXml; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class CanonicalXmlNodeList; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

namespace Details { struct SignedXmlImpl; }

/// Defines a format-independent mechanism for data transfer.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS DataObject : public Object
{
    typedef DataObject ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class Signature;
    friend class SignedXml;
    friend struct Details::SignedXmlImpl;

public:

    ASPOSECPP_SHARED_API String get_Id();
    ASPOSECPP_SHARED_API void set_Id(String value);
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlNodeList> get_Data();
    ASPOSECPP_SHARED_API void set_Data(SharedPtr<System::Xml::XmlNodeList> value);

    ASPOSECPP_SHARED_API DataObject();

protected:

    SharedPtr<System::Xml::XmlElement> GetXml();
    SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> document);
    void LoadXml(SharedPtr<System::Xml::XmlElement> value);
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:

    String _id;
    String _mimeType;
    String _encoding;
    SharedPtr<CanonicalXmlNodeList> _elData;
    SharedPtr<System::Xml::XmlElement> _cachedXml;

    bool get_CacheValid();

};

}}}} // System::Security::Cryptography::Xml
