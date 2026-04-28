/// @file system/details/delegate_holding_variables.h
#pragma once

#include "defines.h"
#if defined(ASPOSE_GET_SHARED_MEMBERS) || defined(__DBG_FOR_EACH_MEMBER)
#include <memory>
#include "system/details/held_variables.h"
#endif
#include <string>
#include <type_traits>
#include "system/smart_ptr.h"

namespace System { namespace Details {
/// Contains variables held by a delegate.
class ASPOSECPP_SHARED_CLASS DelegateHoldingVariables
{
protected:
#if defined(ASPOSE_GET_SHARED_MEMBERS) || defined(__DBG_FOR_EACH_MEMBER)
    /// Contains shared pointers and values held by a delegate.
    std::shared_ptr<HeldVariables> m_heldVariables;

    DelegateHoldingVariables() = default;
#endif

public:
    // Adds a variable held by a delegate.
    /// @tparam DelegateType A type of the current class instance.
    /// @tparam T Random type of field.
    /// @param name A name of a held variable.
    /// @param variable A value of a held variable.
    template <typename DelegateType, typename T>
    typename std::enable_if_t<!IsSmartPtr<T>::value && !std::is_base_of<Object, T>::value, DelegateType&>
        AddHeldVariable(const char* name, const T&)
    {
        return *static_cast<DelegateType*>(this);
    }

    /// Adds a variable held by a delegate.
    /// @tparam DelegateType A type of the current class instance.
    /// @tparam T Value type Object subclass.
    /// @param name A name of a held variable.
    /// @param variable A value of a held variable.
    template <typename DelegateType, typename T>
    typename std::enable_if_t<!IsSmartPtr<T>::value && std::is_base_of<Object, T>::value, DelegateType&>
        AddHeldVariable(const char* name, T& variable)
    {
#if defined(ASPOSE_GET_SHARED_MEMBERS) || defined(__DBG_FOR_EACH_MEMBER)
        if (m_heldVariables == nullptr)
        {
            m_heldVariables = std::make_shared<HeldVariables>();
        }
        m_heldVariables->values.push_front(std::make_pair(name, static_cast<Object*>(&variable)));
#endif
        return *static_cast<DelegateType*>(this);
    }

    /// Adds a variable held by a delegate.
    /// @tparam DelegateType A type of the current class instance.
    /// @tparam T Pointee type.
    /// @param name A name of a held variable.
    /// @param variable A value of a held variable.
    template <typename DelegateType, typename T>
    DelegateType& AddHeldVariable(const char* name, const SmartPtr<T>& variable)
    {
#if defined(ASPOSE_GET_SHARED_MEMBERS) || defined(__DBG_FOR_EACH_MEMBER)
        if (variable.get_Mode() == SmartPtrMode::Shared)
        {
            SmartPtrInfo variableInfo(const_cast<SmartPtr<T>&>(variable));
            if (variableInfo)
            {
                if (m_heldVariables == nullptr)
                {
                    m_heldVariables = std::make_shared<HeldVariables>();
                }
                m_heldVariables->sharedPointers.push_front(std::make_pair(name, variableInfo));
            }
        }
#endif
        return *static_cast<DelegateType*>(this);
    }
};

}} // namespace System::Details
