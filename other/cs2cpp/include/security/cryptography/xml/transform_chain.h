#pragma once

#include <system/type_info.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/collections/ienumerator.h>
#include <cstdint>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class CipherReference; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class EncryptedReference; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Reference; } } } }
namespace System { namespace Security { namespace Cryptography { namespace Xml { class Transform; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

namespace Details { struct ReferenceImpl; }
namespace Details { struct TransformChainImpl; }

/// Represents an ordered chain of transforms.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS TransformChain : public Object
{
    typedef TransformChain ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class CipherReference;
    friend class EncryptedReference;
    friend class Reference;
    friend struct Details::ReferenceImpl;

public:
    ASPOSECPP_SHARED_API int32_t get_Count();

    ASPOSECPP_SHARED_API TransformChain();

    ASPOSECPP_SHARED_API void Add(SharedPtr<Transform> transform);
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<Transform>>> GetEnumerator();

    ASPOSECPP_SHARED_API SharedPtr<Transform> idx_get(int32_t index);

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    const std::unique_ptr<Details::TransformChainImpl> m_impl;
};

}}}} // System::Security::Cryptography::Xml
