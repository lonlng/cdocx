/// @file system/memory_management.h
#pragma once

#include <system/object.h>
#include <system/smart_ptr.h>
#include <system/exceptions.h>
#include <system/iobjects_holder.h>
#include <system/details/objects_bag.h>
#include <type_traits>

#include <map>
#include <list>

namespace CodePorting { namespace Translator { namespace Cs2Cpp {

namespace Details {

/// Used to hold multiple objects.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.

template <size_t ObjectCount>
class ObjectsHolder final : public IObjectsHolder
{
public:
    template <typename ...Args, typename = std::enable_if_t<sizeof...(Args) == ObjectCount>>
    ObjectsHolder(const System::SmartPtr<Args>& ...args)
        : m_objects{ args... }
    {
    }

    ObjectsHolder(const ObjectsHolder&) = delete;
    ObjectsHolder& operator=(const ObjectsHolder&) = delete;

    void setObjectsMode(System::SmartPtrMode mode) final
    {
        for (int n = 1; n < ObjectCount; ++n)
        {
            m_objects[n].set_Mode(mode);
        }
    }

#if defined(__DBG_TOOLS)
    std::vector<int> getHoldObjectIds() const final
    {
        std::vector<int> res;
        for (int n = 1; n < ObjectCount; ++n)
        {
            res.push_back(System::Details::DbgTools::DBG_InstanceNo(m_objects[n].GetObjectOrNull()));
        }

        return res;
    }
#endif

private:
    System::SmartPtr<System::Object> m_objects[ObjectCount];

#ifdef ASPOSE_GET_SHARED_MEMBERS
    void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        System::Object::GetSharedMembers(result);
        for (auto& object : m_objects)
            result.Add("m_objects[]", object);
    }
#endif

#ifdef __DBG_FOR_EACH_MEMBER
public:
    void DBG_for_each_member(System::DBG::for_each_member_visitor &visitor) const override
    {
        visitor.add_self(this);
        System::DBG::for_each_of_Object(this, m_objects, visitor);
    }
    /// Returns a c-string containing the name of the class the current object is instance of.
    const char* DBG_class_name() const override { return "ObjectsHolder<T>"; }
#endif

    RTTI_INFO_TEMPLATE_CLASS(CodePorting::Translator::Cs2Cpp::Details::ObjectsHolder<ObjectCount>, System::BaseTypesInfo<System::Object>);
};

} // namespace Details

/// @brief Defines a methods that changes the lifetime of objects.
class MemoryManagement
{
public:
    /// Highly optimized container designed to extend objects lifetime.
    using ObjectsBag = System::Details::ObjectsBag;

    /// @brief Creates a smart pointer using the aliasing constructor.
    /// Creates a pointer to the @p target object which controls lifetime of the @p owner object.
    /// This pointer's expiration is bound to expiration of the @p owner object,
    /// just like this of any other pointer that owns @p owner object.
    /// If converted to weak type, it is still consistent with other pointers to @p owner and
    /// does not expire while there is at least one shared pointer to @p owner object.
    /// Also, the returned pointer does not ensure that @p target object is alive, so some other
    /// means (e. g. shared pointer stored in the @p owner object) should do so.
    /// Should be used in the situations where @p owner owns the @p target, which effectively means that
    /// the @p target will be kept alive by @p owner even if the returned aliasing pointer no longer exists.
    /// Otherwise, doesn't guarantee that the resulting pointer will remain valid, because if @p owner
    /// doesn't actually hold shared reference to @p target, @p target can be deleted any time as the
    /// resulting pointer only owns @p owner but not the @p target.
    /// @tparam T1 Type of smart pointer to the object that the new smart pointer will refer to.
    /// @tparam T2 Type of smart pointer to an object whose ownership is shared with a new smart pointer.
    /// @param target Smart pointer to the object that the new smart pointer will refer to.
    /// @param owner Smart pointer to an object whose ownership is shared with a new smart pointer.
    /// @return New smart pointer.
    /// @code
    /// #include "system/memory_management.h"
    /// #include "system/object.h"
    /// #include <iostream>
    /// // The ChildNode-class forward declaration.
    /// class ChildNode;
    ///
    /// // Stores a SharedPtr to an instance of the ChildNode class.
    /// class ParentNode: public System::Object
    /// {
    /// public:
    ///   System::SharedPtr<ChildNode> child;
    /// };
    ///
    /// // Stores a WeakPtr to an instance of the ParentNode-class.
    /// class ChildNode: public System::Object
    /// {
    /// public:
    ///   System::WeakPtr<ParentNode> parent;
    /// };
    ///
    /// // The lifetime of the ChildNode- and ParentNode-class instances will be bound when true is passed as a param value.
    /// System::SharedPtr<ChildNode> GetChildNode(bool bindLifetime)
    /// {
    ///   auto parent = System::MakeObject<ParentNode>();
    ///   auto child = System::MakeObject<ChildNode>();
    ///
    ///   parent->child = child;
    ///   child->parent = parent;
    ///
    ///   return bindLifetime ? CodePorting::Translator::Cs2Cpp::MemoryManagement::BindLifetime(child, parent) : child;
    /// }
    ///
    /// // This function prints information about WeakPtr to a ParentNode-class instance.
    /// void PrintInfo(System::WeakPtr<ParentNode> &parent)
    /// {
    ///   std::cout << "The pointer to an instance of the ParentNode class has expired: " << (parent.expired() ? "True" : "False") << std::endl;
    /// }
    ///
    /// int main()
    /// {
    ///   auto child = GetChildNode(false);
    ///   PrintInfo(child->parent);
    ///   child = GetChildNode(true);
    ///   PrintInfo(child->parent);
    ///
    ///   return 0;
    /// }
    /// /*
    /// This code example produces the following output:
    /// The pointer to an instance of the ParentNode class has expired: True
    /// The pointer to an instance of the ParentNode class has expired: False
    /// */
    /// @endcode
    template<typename T1, typename T2>
    static System::SmartPtr<typename T1::Pointee_> BindLifetime(const T1& target, const T2& owner)
    {
        static_assert(System::IsSmartPtr<T1>::value && System::IsSmartPtr<T2>::value, "Trying to bind lifetime for non-pointers");
        return System::SmartPtr<typename T1::Pointee_>(owner, target.get());
    }

    /// @brief Creates a smart pointer using the aliasing constructor.
    /// Creates a pointer to the @p target object which controls lifetime of the @p owner object.
    /// This pointer's expiration is bound to expiration of the @p owner object,
    /// just like this of any other pointer that owns @p owner object.
    /// If converted to weak type, it is still consistent with other pointers to @p owner and
    /// does not expire while there is at least one shared pointer to @p owner object.
    /// Also, the returned pointer does not ensure that @p target object is alive, so some other
    /// means (e. g. shared pointer stored in the @p owner object) should do so.
    /// Should be used in the situations where @p owner owns the @p target, which effectively means that
    /// the @p target will be kept alive by @p owner even if the returned aliasing pointer no longer exists.
    /// Otherwise, doesn't guarantee that the returned pointer will remain valid, because if @p owner
    /// doesn't actually hold shared reference to @p target, @p target can be deleted any time as the
    /// returned pointer only owns @p owner but not the @p target.
    /// @tparam T1 Type of smart pointer to the object that the new smart pointer will refer to.
    /// @tparam T2 Type of smart pointer to an object whose ownership is shared with a new smart pointer.
    /// @param target Smart pointer to the object that the new smart pointer will refer to.
    /// @param owner Smart pointer to an object whose ownership is shared with a new smart pointer.
    /// @return New smart pointer.
    template<typename T1, typename T2>
    static typename std::enable_if<!std::is_reference<T1>::value, System::SmartPtr<typename T1::Pointee_>>::type BindLifetime(T1&& target, const T2& owner)
    {
        static_assert(System::IsSmartPtr<T1>::value && System::IsSmartPtr<T2>::value, "Trying to bind lifetime for non-pointers");

        if (target != nullptr && target->SharedCount() == 1)
            throw System::InvalidOperationException(u"Can not bind lifetime for a temporary target object");

        return System::SmartPtr<typename T1::Pointee_>(owner, target.get());
    }

    /// Creates a smart pointer using the aliasing constructor and copies @p target and @p objects pointers to the
    /// "proxy" objects holder.
    /// Creates a pointer to the @p target and extends the lifetime of all objects to the lifetime of this pointer.
    /// The resulting pointer guarantees all parameters to remain alive, even if it is the only pointer that
    /// keeps track of them.
    /// The resulting pointer effectively owns all objects passed to this method, however, it has its own
    /// expiration track. This means, that converting its own copy to weak type will expire it, even if all objects
    /// it tracks are still alive.
    /// Should be used in the situations when there are several unrelated (not holding shared references to each
    /// other) objects that should be guaranteed to remain alive together. The returned pointer will own a
    /// temporary objects that keeps all of them alive, and this lifetime extension stops working once the returned
    /// pointer no longer exists (or all of its copies become weak).
    /// @tparam T Type of the object that the new smart pointer will refer to.
    /// @tparam Objects Types of the objects whose ownership is shared with a new smart pointer.
    /// @param target Smart pointer to the object that the new smart pointer will refer to.
    /// @param objects Smart pointers to the objects whose ownership is shared with a new smart pointer.
    /// @return New smart pointer.
    /// @code
    /// #include "system/memory_management.h"
    /// #include "system/object.h"
    /// #include <iostream>
    ///
    /// // Create a class that stores links to the previous node and to the next one.
    /// class Node: public System::Object
    /// {
    ///   using NodePtr = System::WeakPtr<Node>;
    ///
    ///   int32_t m_value;
    ///
    /// public:
    ///   NodePtr previous;
    ///   NodePtr next;
    ///
    ///   explicit Node(int32_t value): m_value(value) {}
    ///
    ///   int32_t GetValue() const
    ///   {
    ///     return m_value;
    ///   }
    /// };
    ///
    /// // This function prints a value that is stored by the specified node.
    /// void PrintValue(System::SmartPtr<Node> &node)
    /// {
    ///   std::cout << (node == nullptr ? "nullptr" : std::to_string(node->GetValue())) << ' ';
    /// }
    ///
    /// int main()
    /// {
    ///   System::SharedPtr<Node> node;
    ///
    ///   {
    ///     auto first = System::MakeObject<Node>(1);
    ///     node = System::MakeObject<Node>(2);
    ///     auto last = System::MakeObject<Node>(3);
    ///
    ///     first->next = node;
    ///     node->previous = first;
    ///     node->next = last;
    ///     last->previous = node;
    ///   }
    ///
    ///   PrintValue(node->previous);
    ///   PrintValue(node);
    ///   PrintValue(node->next);
    ///   std::cout << std::endl;
    ///
    ///   {
    ///     auto first = System::MakeObject<Node>(4);
    ///     auto middle = System::MakeObject<Node>(5);
    ///     auto last = System::MakeObject<Node>(6);
    ///
    ///     first->next = middle;
    ///     middle->previous = first;
    ///     middle->next = last;
    ///     last->previous = middle;
    ///
    ///     node = CodePorting::Translator::Cs2Cpp::MemoryManagement::ExtendLifetime(middle, first, last);
    ///   }
    ///
    ///   PrintValue(node->previous);
    ///   PrintValue(node);
    ///   PrintValue(node->next);
    ///   std::cout << std::endl;
    ///
    ///   return 0;
    /// }
    /// /*
    /// This code example produces the following output:
    /// nullptr 2 nullptr
    /// 4 5 6
    /// */
    /// @endcode
    template <typename T, typename... Objects>
    static System::SmartPtr<typename T::Pointee_> ExtendLifetime(const T& target, const Objects&... objects)
    {
        static_assert(System::IsSmartPtr<T>::value, "Trying to bind lifetime for non-pointers");

        System::SmartPtr<System::Object> holder(new Details::ObjectsHolder<1 + sizeof...(objects)>(target, objects...));
        return System::SmartPtr<typename T::Pointee_>(holder, target.get());
    }

public:
    class PostponedHolders;
private:
    class PostponedHoldersRegistrar;

public:
    /// Creates a smart pointer using the aliasing constructor and copies @p target and @p objects pointers to the
    /// "proxy" objects holder.
    /// Creates a pointer to the @p target and extends the lifetime of all objects to the lifetime of this pointer.
    /// The resulting pointer guarantees all parameters to remain alive, even if it is the only pointer that
    /// keeps track of them.
    /// key - PostponedHolders key.
    /// In the case of PostponedHolders declared above the stack with the same key, all ObjectHolders will be switched
    /// to weak mode. This will be useful when need to control the destruction of objects in the holder. For example to
    /// avoid destructor calling if an exception happens in the constructor body but "this" pointer needs to keep in the
    /// ObjectHolders. The resulting pointer effectively owns all objects passed to this method, however, it has its own
    /// expiration track. This means, that converting its own copy to weak type will expire it, even if all objects
    /// it tracks are still alive.
    /// Should be used in the situations when there are several unrelated (not holding shared references to each
    /// other) objects that should be guaranteed to remain alive together. The returned pointer will own a
    /// temporary objects that keeps all of them alive, and this lifetime extension stops working once the returned
    /// pointer no longer exists (or all of its copies become weak).
    template <typename T, typename TObject>
    static System::SmartPtr<typename T::Pointee_>
        ExtendLifetimeAsWeakPostponed(const System::SharedPtr<System::Object>& key, const T& target, const TObject& object)
    {
        static_assert(System::IsSmartPtr<T>::value, "Trying to bind lifetime for non-pointers");

        System::SmartPtr<Details::IObjectsHolder> holder(
            new Details::ObjectsHolder<2>(target, object));

        auto* postpone_holder = PostponedHoldersRegistrar::inst().get(key);
        if (postpone_holder)
        {
            postpone_holder->addHolder(holder);
        }

        return System::SmartPtr<typename T::Pointee_>(holder, target.get());
    }

private:
    /// @brief PostponedHolders registrar singleton. Need to register and extract PostponedHolders objects by key.
    class PostponedHoldersRegistrar
    {
        friend class PostponedHolders;

        template <typename T, typename TObject>
        friend System::SmartPtr<typename T::Pointee_> MemoryManagement::ExtendLifetimeAsWeakPostponed(const System::SharedPtr<System::Object>&, const T&, const TObject&);

    private:
        static PostponedHoldersRegistrar & inst()
        {
            static PostponedHoldersRegistrar instance;
            return instance;
        }

        /// @brief Register PostponedHolders object by key.
        void reg(void *key, PostponedHolders *holder)
        {
            if (m_map_holders.end() != m_map_holders.find(key))
            {
                return;
            }
            
            m_map_holders.insert({key, holder});
        }

        /// @brief De register PostponedHolders object by key.
        void unreg(void *key)
        {
            m_map_holders.erase(key);
        }

        /// @brief Return PostponedHolders object by key.
        /// @param Key object.
        /// @return PostponedHolders raw pointer or nullptr.
        PostponedHolders * get(const System::SharedPtr<System::Object> &key)
        {
            auto it = m_map_holders.find(key.get());
            if (m_map_holders.end() == it)
            {
                return nullptr;
            }
            
            return it->second;
        }

    private:
        using map_holders = std::map<void*, PostponedHolders*>;
        map_holders m_map_holders;
    };

public:
    /// @brief Keeps ObjectHolder's in Weak state and after the switch, it to Shared remove it from a local collection.
    class PostponedHolders
    {
        template <typename T, typename TObject>
        friend System::SmartPtr<typename T::Pointee_> MemoryManagement::ExtendLifetimeAsWeakPostponed(const System::SharedPtr<System::Object>&, const T&, const TObject&);

    public:
        PostponedHolders(const System::SharedPtr<System::Object> & key)
            : m_key(key.get())
        {
            PostponedHoldersRegistrar::inst().reg(m_key, this);
        }

        ~PostponedHolders()
        {
            PostponedHoldersRegistrar::inst().unreg(m_key);
        }

    public:
        /// @brief Switch ObjectsHolder pointer's collection to Shared mode and clean postponed holders list.
        void switchToShared()
        {
            for (auto& holder : posponed_weak_holders)
            {
                holder->setObjectsMode(System::SmartPtrMode::Shared);
            }
            posponed_weak_holders.clear();
        }

    private:
        /// @brief Add ObjectsHolder and switch pointer's collection to Weak mode.
        void addHolder(System::SharedPtr<Details::IObjectsHolder> &holder)
        {
            holder->setObjectsMode(System::SmartPtrMode::Weak);
            posponed_weak_holders.push_back(holder);
        }

    private:
        std::list<System::SharedPtr<Details::IObjectsHolder>> posponed_weak_holders;
        void* m_key;
    };
};

}}} // namespace CodePorting::Translator::Cs2Cpp
