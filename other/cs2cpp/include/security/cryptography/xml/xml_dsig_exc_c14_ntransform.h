#pragma once

#include <security/cryptography/xml/transform.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class ExcCanonicalXml; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the exclusive C14N XML canonicalization transform for a digital signature without comments.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlDsigExcC14NTransform : public Transform
{
    typedef XmlDsigExcC14NTransform ThisType;
    typedef Transform BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:
    ASPOSECPP_SHARED_API String get_InclusiveNamespacesPrefixList();
    ASPOSECPP_SHARED_API void set_InclusiveNamespacesPrefixList(String value);
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_InputTypes() override;
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_OutputTypes() override;

    ASPOSECPP_SHARED_API XmlDsigExcC14NTransform();
    ASPOSECPP_SHARED_API XmlDsigExcC14NTransform(bool includeComments);
    ASPOSECPP_SHARED_API XmlDsigExcC14NTransform(bool includeComments, String inclusiveNamespacesPrefixList);

    ASPOSECPP_SHARED_API void LoadInnerXml(SharedPtr<System::Xml::XmlNodeList> nodeList) override;
    ASPOSECPP_SHARED_API void LoadInput(SharedPtr<Object> obj) override;
    ASPOSECPP_SHARED_API SharedPtr<Object> GetOutput() override;
    ASPOSECPP_SHARED_API SharedPtr<Object> GetOutput(const TypeInfo& type) override;
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> GetDigestedOutput(SharedPtr<HashAlgorithm> hash) override;

protected:
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlNodeList> GetInnerXml() override;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    ArrayPtr<TypeInfo> m_input_types;
    ArrayPtr<TypeInfo> m_output_types;
    bool m_include_comments;
    String m_inclusive_namespaces_prefix_list;
    SharedPtr<ExcCanonicalXml> m_exc_canonical_xml;
};

}}}} // System::Security::Cryptography::Xml
