#pragma once
#include <system/collections/ienumerator_ng.h>
#include <system/collections/iequality_comparer.h>

namespace System {
namespace Collections {

/// IEnumerable is the base interface for all non-generic collections that can be enumerated
class ASPOSECPP_SHARED_CLASS IEnumerable: virtual public Object
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::IEnumerable, System::BaseTypesInfo<System::Object>);
public:
    /// Returns an enumerator that iterates through a collection.
    virtual SharedPtr<System::Collections::IEnumerator> GetEnumerator() = 0;
};

} // namespace Collections
} // namespace System
