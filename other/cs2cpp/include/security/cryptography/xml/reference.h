#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/io/stream.h>
#include <cstdint>

namespace System { namespace Xml { class XmlElement; } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedInfo; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class SignedXml; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Transform; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { enum class ReferenceTargetType; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class TransformChain; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class CanonicalXmlNodeList; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

namespace Details { struct SignedXmlImpl; }
namespace Details { struct ReferenceImpl; }

/// Facilitates creation of the XML signatures.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS Reference : public Object
{
    typedef Reference ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class SignedInfo;
    friend class SignedXml;
    friend class Transform;
    friend struct Details::SignedXmlImpl;

public:
    ASPOSECPP_SHARED_API String get_Id();
    ASPOSECPP_SHARED_API void set_Id(String value);
    ASPOSECPP_SHARED_API String get_Uri();
    ASPOSECPP_SHARED_API void set_Uri(String value);
    ASPOSECPP_SHARED_API String get_Type();
    ASPOSECPP_SHARED_API void set_Type(String value);
    ASPOSECPP_SHARED_API String get_DigestMethod();
    ASPOSECPP_SHARED_API void set_DigestMethod(String value);
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> get_DigestValue();
    ASPOSECPP_SHARED_API void set_DigestValue(ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API SharedPtr<TransformChain> get_TransformChain();
    ASPOSECPP_SHARED_API void set_TransformChain(SharedPtr<TransformChain> value);

    ASPOSECPP_SHARED_API Reference();
    ASPOSECPP_SHARED_API Reference(SharedPtr<IO::Stream> stream);
    ASPOSECPP_SHARED_API Reference(String uri);

    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml();
    ASPOSECPP_SHARED_API void LoadXml(SharedPtr<System::Xml::XmlElement> value);
    ASPOSECPP_SHARED_API void AddTransform(SharedPtr<Transform> transform);

protected:
    virtual ASPOSECPP_SHARED_API ~Reference();
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    const std::unique_ptr<Details::ReferenceImpl> m_impl;
};

}}}} // System::Security::Cryptography::Xml
