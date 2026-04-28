#pragma once

#include <system/object.h>
#include <system/shared_ptr.h>
#include <defines.h>
#include <system/exceptions.h>
#include <system/idisposable.h>

namespace System {
namespace Collections {

/// Interface of enumerator which can be used to iterate through some elements.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam T Element type.
class ASPOSECPP_SHARED_CLASS IEnumerator: virtual public IDisposable, virtual public Object
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::IEnumerator, System::BaseTypesInfo<System::Object>);
public:
    /// Value type.
    using ValueType = SharedPtr<System::Object>;

    // There no need to define an empty virtual dtor, virtual dtor for inheritance already defined in the Object class
    /// Gets current element.
    /// @return Currently referenced element copy.
    virtual const SharedPtr<System::Object>& Current() const { return get_Current(); }
    /// Gets current element.
    /// @return Currently referenced element copy.
    virtual const SharedPtr<System::Object>& get_Current() const = 0;
    /// Moves enumerator to the next element. If no element was referenced before, sets reference to the first element available.
    /// If container end was hit, does nothing.
    /// @return True if some element is available after call, false otherwise.
    virtual bool MoveNext() = 0;
    /// Resets enumerator to position before first element.
    virtual void Reset() { throw System::NotImplementedException(); }
};

} // namespace Collections
} // namespace System
