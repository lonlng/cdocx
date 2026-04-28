#pragma once

#include <system/object.h>
#include <system/object_ext.h>
#include <system/shared_ptr.h>
#include <defines.h>
#include <system/exceptions.h>
#include <system/idisposable.h>
#include <system/collections/ienumerator_ng.h>

namespace System { namespace Collections { namespace Generic {
    template <typename T>
    class IEnumerator;
}}}

namespace System {
namespace Collections {

/// Wrapper the creates non generic IEnumerator implementation over the generic Iterator
/// IEnumeratorImplRefType - wrapper for the Reference Types
/// @tparam T Element type.
template <typename T>
class ASPOSECPP_SHARED_CLASS IEnumeratorImplRefType : public System::Collections::IEnumerator
{
public:
    /// wrapper constructor
    IEnumeratorImplRefType(System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<T>>> enumerator) : m_enum(enumerator) {}

    // There no need to define an empty virtual dtor, virtual dtor for inheritance already defined in the Object class
    /// Gets current element.
    /// @return Currently referenced element copy.
    virtual const SharedPtr<System::Object>& get_Current() const override
    {
        return m_current;
    }
    /// Moves enumerator to the next element. If no element was referenced before, sets reference to the first element available.
    /// If container end was hit, does nothing.
    /// @return True if some element is available after call, false otherwise.
    virtual bool MoveNext() override
    {
        if (m_enum->MoveNext())
        {
            m_current = m_enum->get_Current();
            return true;
        }
        m_current = System::Default<System::SharedPtr<System::Object>>();
        return false;
    }

private:
    System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<T>>>  m_enum;
    System::SharedPtr<System::Object> m_current;
};

/// Wrapper the creates non generic IEnumerator implementation over the generic Iterator
/// IEnumeratorImplRefType - wrapper for the value Types
/// @tparam T Element type.
template <typename T>
class ASPOSECPP_SHARED_CLASS IEnumeratorImplValueType : public System::Collections::IEnumerator
{
public:
    /// wrapper constructor
    IEnumeratorImplValueType(System::SharedPtr<System::Collections::Generic::IEnumerator<T>> enumerator) : m_enum(enumerator) {}

    // There no need to define an empty virtual dtor, virtual dtor for inheritance already defined in the Object class
    /// Gets current element.
    /// @return Currently referenced element copy.
    virtual const SharedPtr<System::Object>& get_Current() const override
    {
        return m_current;
    }
    /// Moves enumerator to the next element. If no element was referenced before, sets reference to the first element available.
    /// If container end was hit, does nothing.
    /// @return True if some element is available after call, false otherwise.
    virtual bool MoveNext() override
    {
        if (m_enum->MoveNext())
        {
            m_current = ObjectExt::Box(m_enum->get_Current());
            return true;
        }
        m_current = System::Default<System::SharedPtr<System::Object>>();
        return false;
    }

private:
    System::SharedPtr<System::Collections::Generic::IEnumerator<T>>  m_enum;
    System::SharedPtr<System::Object> m_current;
};

} // namespace Collections
} // namespace System
