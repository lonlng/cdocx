/// @file system/details/shared_members_t.h
#pragma once

#include "system/details/delegate_holding_variables.h"
#include <system/debug/chain_element.h>
#include <system/smart_ptr.h>

#include <list>
#include <memory>
#include <utility>
#include <vector>
#include <type_traits>


namespace System
{
    class Object;
}


namespace System { namespace Details {

struct SharedMembersType;

/// @cond
template<class T>
using PopulateSharedMembersMark = decltype((void)std::declval<T>().PopulateSharedMembers(std::declval<SharedMembersType&>()));

template<class T, class = void>
struct HasPopulateSharedMembersMethod : std::false_type {};

template<class T>
struct HasPopulateSharedMembersMethod<T, PopulateSharedMembersMark<T>> : std::true_type {};
/// @endcond

/// @brief structure to keep list of shared pointers contained in object.
struct SharedMembersType {
#if defined(ENABLE_CYCLES_DETECTION_EXT)
    std::vector<Debug::ChainElement> m_chainElements;
#endif
#if defined(__DBG_GARBAGE_COLLECTION)
    /// @brief List of non-null shared pointers contained in object, with member names.
    std::vector<std::pair<const char*, SmartPtrInfo>> m_sharedMembers;
    /// @brief List of value type Object subclasses contained in object, with member names.
    std::vector<std::pair<const char*, const System::Object*>> m_valueMembers;
#endif

    /// @brief Adds object to list. Non-specific version which ignores its arguments,
    /// @tparam T Random type of field.
    template <class T>
    typename std::enable_if<!IsSmartPtr<T>::value &&
                            !HasPopulateSharedMembersMethod<T>::value &&
                            !std::is_base_of<Object, T>::value &&
                            !std::is_base_of<DelegateHoldingVariables, T>::value, void>::type
    Add(const char*, const T&)
    {
        // Nothing to do.
    }
    /// @brief Adds Object subclass to list.
    /// @tparam T Value type Object subclass.
    /// @param name Field name.
    /// @param member Field reference.
    template <class T>
    typename std::enable_if<!IsSmartPtr<T>::value &&
                            HasPopulateSharedMembersMethod<T>::value &&
                            !std::is_base_of<Object, T>::value, void>::type
    Add(const char* name, const T &member)
    {
#if defined(ENABLE_CYCLES_DETECTION_EXT)
        Debug::ChainElement::ClassCallback callback = std::bind(&T::PopulateSharedMembers, &member, std::placeholders::_1);
        m_chainElements.emplace_back(name, typeid(member), &member, callback);
#endif
#if defined(__DBG_GARBAGE_COLLECTION)
        member.PopulateSharedMembers(*this);
#endif
    }
    /// @brief Adds Object subclass to list.
    /// @tparam T Value type Object subclass.
    /// @param name Field name.
    /// @param member Field reference.
    template <class T>
    typename std::enable_if<!IsSmartPtr<T>::value &&
                            std::is_base_of<Object, T>::value, void>::type
    Add(const char* name, const T &member)
    {
#if defined(ENABLE_CYCLES_DETECTION_EXT)
        m_chainElements.emplace_back(name, static_cast<const Object*>(&member));
#endif
#if defined(__DBG_GARBAGE_COLLECTION)
        m_valueMembers.emplace_back(name, static_cast<const Object*>(&member));
#endif
    }
    /// @brief Adds smart pointer to list.
    /// @tparam T Pointee type.
    /// @param name Field name.
    /// @param member Field reference.
    template <class T>
    void Add(const char* name, const SmartPtr<T> &member)
    {
        if (member.get_Mode() != SmartPtrMode::Weak)
            Add(name, SmartPtrInfo(member));
    }
    /// @brief Adds smart pointer info to list.
    /// @param name Field name.
    /// @param info Smart pointer info.
    void Add(const char* name, const SmartPtrInfo &info)
    {
        if (info)
        {
#if defined(ENABLE_CYCLES_DETECTION_EXT)
            m_chainElements.emplace_back(name, info);
#endif
#if defined(__DBG_GARBAGE_COLLECTION)
            m_sharedMembers.emplace_back(name, info);
#endif
        }
    }
    /// @brief Adds variables held by a delegate to the list.
    /// @param name A field name.
    /// @param member A field reference.
    template <typename T>
    typename std::enable_if<!IsSmartPtr<T>::value &&
                            !std::is_base_of<Object, T>::value &&
                            std::is_base_of<Details::DelegateHoldingVariables, T>::value, void>::type
    Add(const char* name, const T &member)
    {
#if defined(ENABLE_CYCLES_DETECTION_EXT)
        Debug::ChainElement::DelegateCallback callback = std::bind(&T::GetHeldVariables, &member);
        m_chainElements.emplace_back(name, typeid(member), &member, callback);
#endif
#if defined(__DBG_GARBAGE_COLLECTION)
        auto heldVariables = member.GetHeldVariables();

        if (heldVariables)
        {
            for (const auto& sharedPointer: heldVariables->sharedPointers)
            {
                Add(sharedPointer.first, sharedPointer.second);
            }

            for (const auto& value: heldVariables->values)
            {
                Add(value.first, value.second);
            }
        }
#endif
    }

#if defined(ENABLE_CYCLES_DETECTION_EXT)
    /// @brief Forms full list of contained references, both direct and indirect.
    /// @return Full list of smart pointers contained in collection.
    ASPOSECPP_SHARED_API std::vector<Debug::ChainElement> GetHolders() const;
#endif

    /// Populates contents of STL-style container to shared members data structure.
    /// This overload handles containers with no smart pointers in them.
    /// @tparam Container Container type
    /// @tparam Value Contained type
    template <class Container, typename Value = typename Container::value_type>
    typename std::enable_if<!System::IsSmartPtr<Value>::value &&
                            !System::detail::is_a<Value, std::pair>::value &&
                            !std::is_base_of<Object, Value>::value &&
                            !HasPopulateSharedMembersMethod<Value>::value, void>::type
    PopulateSharedMembers(const char* /*name*/, Container& /*container*/)
    {
        /* Nothing to do here, see specialization below */
    }

    /// Populates contents of STL-style container to shared members data structure.
    /// This overload handles containers with elements that can populate shared members.
    /// @tparam Container Container type
    /// @tparam Value Contained type
    template <class Container, typename Value = typename Container::value_type>
    typename std::enable_if<System::IsSmartPtr<Value>::value ||
                            std::is_base_of<Object, Value>::value ||
                            HasPopulateSharedMembersMethod<Value>::value, void>::type
    PopulateSharedMembers(const char* name, Container& container)
    {
        for (auto& item : container)
        {
            Add(name, item);
        }
    }

    /// Populates contents of STL-style container to shared members data structure. This overload handles containers of pairs.
    /// @tparam Container Container type
    /// @tparam Value Contained type
    /// @param name Member name
    /// @param container Container to get elements from
    template <class Container, typename Value = typename Container::value_type>
    typename std::enable_if<System::detail::is_a<Value, std::pair>::value, void>::type
    PopulateSharedMembers(const char* name, Container& container)
    {
        for (auto& item : container)
        {
            Add(name, item.first);
            Add(name, item.second);
        }
    }
};

} } // namespace System::Details

