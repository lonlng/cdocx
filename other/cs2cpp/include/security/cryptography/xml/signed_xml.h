#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/collections/object_model/collection.h>
#include <security/cryptography/hash_algorithm.h>
#include <cstdint>

namespace System { namespace Xml { class XmlDocument; } }
namespace System { namespace Xml { class XmlElement; } }
namespace System { namespace Security { namespace Cryptography { class AsymmetricAlgorithm; } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Transform; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Reference; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedInfo; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class KeyInfo; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class DataObject; } } } }
namespace System { namespace Security { namespace Cryptography { namespace X509Certificates { class X509Certificate2; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

namespace Details { struct ReferenceImpl; }
namespace Details { struct SignedXmlImpl; }

/// Used for XML signing and verification.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SignedXml : public Object
{
    typedef SignedXml ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class Reference;
    friend class Transform;
    friend struct Details::ReferenceImpl;
    friend struct Details::SignedXmlImpl;

public:
    static const ASPOSECPP_SHARED_API String XmlDsigNamespaceUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigMinimalCanonicalizationUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigCanonicalizationUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigCanonicalizationWithCommentsUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigSHA1Url;
    static const ASPOSECPP_SHARED_API String XmlDsigDSAUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigRSASHA1Url;
    static const ASPOSECPP_SHARED_API String XmlDsigHMACSHA1Url;
    static const ASPOSECPP_SHARED_API String XmlDsigSHA256Url;
    static const ASPOSECPP_SHARED_API String XmlDsigRSASHA256Url;
    static const ASPOSECPP_SHARED_API String XmlDsigSHA384Url;
    static const ASPOSECPP_SHARED_API String XmlDsigRSASHA384Url;
    static const ASPOSECPP_SHARED_API String XmlDsigSHA512Url;
    static const ASPOSECPP_SHARED_API String XmlDsigRSASHA512Url;
    static const ASPOSECPP_SHARED_API String XmlDsigC14NTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigC14NWithCommentsTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigExcC14NTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigExcC14NWithCommentsTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigBase64TransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigXPathTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigXsltTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDsigEnvelopedSignatureTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlDecryptionTransformUrl;
    static const ASPOSECPP_SHARED_API String XmlLicenseTransformUrl;

    ASPOSECPP_SHARED_API String get_SigningKeyName();
    ASPOSECPP_SHARED_API void set_SigningKeyName(String value);
    ASPOSECPP_SHARED_API SharedPtr<AsymmetricAlgorithm> get_SigningKey();
    ASPOSECPP_SHARED_API void set_SigningKey(SharedPtr<AsymmetricAlgorithm> value);
    ASPOSECPP_SHARED_API SharedPtr<SignedInfo> get_SignedInfo();
    ASPOSECPP_SHARED_API String get_SignatureMethod();
    ASPOSECPP_SHARED_API String get_SignatureLength();
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> get_SignatureValue();
    ASPOSECPP_SHARED_API SharedPtr<KeyInfo> get_KeyInfo();
    ASPOSECPP_SHARED_API void set_KeyInfo(SharedPtr<KeyInfo> value);

    ASPOSECPP_SHARED_API SignedXml();
    ASPOSECPP_SHARED_API SignedXml(SharedPtr<System::Xml::XmlDocument> document);
    ASPOSECPP_SHARED_API SignedXml(SharedPtr<System::Xml::XmlElement> elem);

    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml();
    ASPOSECPP_SHARED_API void LoadXml(SharedPtr<System::Xml::XmlElement> value);
    ASPOSECPP_SHARED_API void AddReference(SharedPtr<Reference> reference);
    ASPOSECPP_SHARED_API void AddObject(SharedPtr<DataObject> dataObject);
    ASPOSECPP_SHARED_API bool CheckSignature();
    ASPOSECPP_SHARED_API bool CheckSignatureReturningKey(SharedPtr<AsymmetricAlgorithm>& signingKey);
    ASPOSECPP_SHARED_API bool CheckSignature(SharedPtr<AsymmetricAlgorithm> key);
    ASPOSECPP_SHARED_API bool CheckSignature(SharedPtr<X509Certificates::X509Certificate2> certificate, bool verifySignatureOnly);
    ASPOSECPP_SHARED_API void ComputeSignature();
    virtual ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetIdElement(SharedPtr<System::Xml::XmlDocument> document, String idValue);

protected:
    SharedPtr<Collections::ObjectModel::Collection<String>> get_SafeCanonicalizationMethods();

    virtual ASPOSECPP_SHARED_API SharedPtr<AsymmetricAlgorithm> GetPublicKey();

    virtual ASPOSECPP_SHARED_API ~SignedXml();

#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    const std::unique_ptr<Details::SignedXmlImpl> m_impl;
};

}}}} // System::Security::Cryptography::Xml
