#pragma once
#include <system/object.h>
#include <system/collections/ienumerable_ng.h>

namespace System {
namespace Collections {

/// Defines non generic collection interface
/// @tparam T Element type.
class ASPOSECPP_SHARED_CLASS ICollection : public System::Collections::IEnumerable
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::ICollection, System::BaseTypesInfo<System::Collections::IEnumerable>);
public:
    /// Gets number of elements in collection.
    /// @return Number of elements.
    virtual int get_Count() const = 0;
};

} // namespace Collections
} // namespace System
