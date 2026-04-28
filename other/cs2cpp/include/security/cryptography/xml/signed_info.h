#pragma once

#include <xml/xml_element.h>
#include <xml/xml_document.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/collections/ilist.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class Signature; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedXml; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedXmlDebugLog; } } } }
namespace Tests { class SignedXmlTest; }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Reference; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Transform; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

namespace Details { struct SignedXmlImpl; }

/// Represents the 'SignedInfo' element of the XML signature.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SignedInfo : public Object
{
    typedef SignedInfo ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class Signature;
    friend class SignedXml;
    friend class SignedXmlDebugLog;
    friend struct Details::SignedXmlImpl;
    friend class Tests::SignedXmlTest;

public:
    ASPOSECPP_SHARED_API String get_SignatureMethod();
    ASPOSECPP_SHARED_API void set_SignatureMethod(String value);
    ASPOSECPP_SHARED_API String get_CanonicalizationMethod();
    ASPOSECPP_SHARED_API void set_CanonicalizationMethod(String value);

protected:
    SharedPtr<SignedXml> get_SignedXml();
    void set_SignedXml(SharedPtr<SignedXml> value);
    String get_Id();
    void set_Id(String value);
    SharedPtr<Transform> get_CanonicalizationMethodObject();
    String get_SignatureLength();
    void set_SignatureLength(String value);
    SharedPtr<Collections::Generic::IList<SharedPtr<Reference>>> get_References();
    bool get_CacheValid();

    SignedInfo();
    MEMBER_FUNCTION_MAKE_OBJECT(SignedInfo, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    SharedPtr<System::Xml::XmlElement> GetXml();
    SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> document);
    void LoadXml(SharedPtr<System::Xml::XmlElement> value);
    void AddReference(SharedPtr<Reference> reference);
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    String _id;
    String _canonicalizationMethod;
    String _signatureMethod;
    String _signatureLength;
    SharedPtr<Collections::Generic::IList<SharedPtr<Reference>>> _references;
    SharedPtr<System::Xml::XmlElement> _cachedXml;
    WeakPtr<SignedXml> _signedXml;
    SharedPtr<Transform> _canonicalizationMethodTransform;
};

}}}} // System::Security::Cryptography::Xml
