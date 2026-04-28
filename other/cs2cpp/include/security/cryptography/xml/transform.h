#pragma once

#include <xml/xml_document.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/collections/idictionary.h>
#include <security/cryptography/hash_algorithm.h>
#include <cstdint>

namespace System { namespace Xml { class XmlElement; } }
namespace System { namespace Xml { class XmlNodeList; } }
namespace System { namespace Xml { class XmlResolver; } }

namespace System { namespace Security { namespace Cryptography { namespace Xml { class Reference; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedInfo; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedXml; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedXmlDebugLog; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class TransformChain; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

namespace Details { struct SignedXmlImpl; }
namespace Details { struct TransformChainImpl; }

/// Provides information about transforming the data by the signer.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS Transform : public Object
{
    typedef Transform ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class Reference;
    friend class SignedInfo;
    friend class SignedXml;
    friend class SignedXmlDebugLog;
    friend class TransformChain;
    friend struct Details::SignedXmlImpl;
    friend struct Details::TransformChainImpl;

public:
    ASPOSECPP_SHARED_API String get_Algorithm();
    ASPOSECPP_SHARED_API void set_Algorithm(String value);
    virtual ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_InputTypes() = 0;
    virtual ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_OutputTypes() = 0;
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> get_Context();
    ASPOSECPP_SHARED_API void set_Context(SharedPtr<System::Xml::XmlElement> value);
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IDictionary<String, String>> get_PropagatedNamespaces();

    virtual ASPOSECPP_SHARED_API void LoadInnerXml(SharedPtr<System::Xml::XmlNodeList> nodeList) = 0;
    virtual ASPOSECPP_SHARED_API void LoadInput(SharedPtr<Object> obj) = 0;
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> GetOutput() = 0;
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> GetOutput(const TypeInfo& type) = 0;
    virtual ASPOSECPP_SHARED_API ArrayPtr<uint8_t> GetDigestedOutput(SharedPtr<HashAlgorithm> hash);
    ASPOSECPP_SHARED_API void set_Resolver(SharedPtr<System::Xml::XmlResolver> value);

protected:
    String get_BaseURI() const;
    void set_BaseURI(String value);
    SharedPtr<SignedXml> get_SignedXml() const;
    void set_SignedXml(SharedPtr<SignedXml> value);
    SharedPtr<Reference> get_Reference() const;
    void set_Reference(SharedPtr<Reference> value);
    SharedPtr<System::Xml::XmlResolver> get_Resolver() const;
    bool get_ResolverSet();

    ASPOSECPP_SHARED_API Transform();

    bool AcceptsType(const TypeInfo& inputType);
    SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> document);
    SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> document, String name);
    virtual ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlNodeList> GetInnerXml() = 0;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    String m_algorithm;
    String m_base_uri;
    bool m_resolver_set;
    WeakPtr<SignedXml> m_signed_xml;
    WeakPtr<Reference> m_reference;
    SharedPtr<System::Xml::XmlResolver> m_xml_resolver;
    SharedPtr<Collections::Generic::IDictionary<String, String>> m_propagated_namespaces;
    SharedPtr<System::Xml::XmlElement> m_context;
};

}}}} // System::Security::Cryptography::Xml
