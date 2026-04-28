#pragma once

#include <xml/xml_namespace_manager.h>
#include <system/io/stream.h>

#include <security/cryptography/xml/transform.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class Reference; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the enveloped signature transform for the XML signature.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDsigEnvelopedSignatureTransform : public Transform
{
    typedef XmlDsigEnvelopedSignatureTransform ThisType;
    typedef Transform BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class Reference;

public:
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_InputTypes() override;
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_OutputTypes() override;

    ASPOSECPP_SHARED_API XmlDsigEnvelopedSignatureTransform();

    ASPOSECPP_SHARED_API void LoadInnerXml(SharedPtr<System::Xml::XmlNodeList> nodeList) override;
    ASPOSECPP_SHARED_API void LoadInput(SharedPtr<Object> obj) override;
    ASPOSECPP_SHARED_API SharedPtr<Object> GetOutput() override;
    ASPOSECPP_SHARED_API SharedPtr<Object> GetOutput(const TypeInfo& type) override;

protected:
    void set_SignaturePosition(int32_t value);

    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlNodeList> GetInnerXml() override;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    ArrayPtr<TypeInfo> m_input_types;
    ArrayPtr<TypeInfo> m_output_types;
    SharedPtr<System::Xml::XmlNodeList> m_input_node_list;
    SharedPtr<System::Xml::XmlNamespaceManager> m_ns_manager;
    SharedPtr<System::Xml::XmlDocument> m_containing_document;
    int32_t m_signature_position;

    void LoadStreamInput(SharedPtr<IO::Stream> stream);
    void LoadXmlNodeListInput(SharedPtr<System::Xml::XmlNodeList> nodeList);
    void LoadXmlDocumentInput(SharedPtr<System::Xml::XmlDocument> doc);
};

}}}} // System::Security::Cryptography::Xml
