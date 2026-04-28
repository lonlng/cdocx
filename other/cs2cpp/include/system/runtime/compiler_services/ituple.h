#pragma once
#include "system/object.h"

namespace System {
namespace Runtime {
namespace CompilerServices {

/// Defines a general-purpose Tuple implementation that allows access to
/// Tuple instance members without knowing the underlying Tuple type.
class ITuple : virtual public Object
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(Runtime::CompilerServices::ITuple, System::BaseTypesInfo<System::Object>);

public:
    /// Returns the element at position index
    /// @param index of the specified Tuple element.
    /// @returns The element at position index the Tuple
    virtual SharedPtr<Object> idx_get(int32_t index) const = 0;

    /// Returns the number of positions in this data structure.
    virtual int32_t get_Length() const = 0;
};

}}} // namespace System::Runtime::CompilerServices
