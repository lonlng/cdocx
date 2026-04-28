/// @file system/multicast_delegate.h
/// Contains the declaration of System::MulticastDelegate class.
#ifndef _aspose_system_multicast_delegate_h_
#define _aspose_system_multicast_delegate_h_

#include "delegate.h"
#include "shared_ptr.h"
#include "exceptions.h"
#include "system/details/delegate_holding_variables.h"
#include <list>
#include <functional>
#include <algorithm>
#include <type_traits>
#include <utility>

#define ASPOSE_REMOVE_EMPTY_CALLBACKS

#ifdef ASPOSE_THREADSAFE_DELEGATES
#include <mutex>
#endif

namespace System
{
    class IAsyncResult;

    /// @cond
    template<class Unused>
    class MulticastDelegate;
    /// @endcond
    
    using AsyncCallback = MulticastDelegate<void(SharedPtr<IAsyncResult>)>;

    /// Represents a pointer to TypeInfo object that contains information about MulticastDelegate class.
    struct MulticastDelegateTypeInfo : TypeInfoPtr
    {
        /// Constructs an instance of MulticastDelegateTypeInfo class.
        MulticastDelegateTypeInfo()
            : TypeInfoPtr(u"System::MulticastDelegate")
        {}
    };

    /// Represents a collection of delegates.
    /// This type should be allocated on stack and passed to functions by value or by reference.
    /// Never use System::SmartPtr class to manage objects of this type.
    /// @tparam ReturnType Return type of the invokable entities pointed to by each delegate in the collection
    /// @tparam ArgumentTypes Argument list of the invokable entities pointed to by each delegate in the collection
    /// @code
    /// #include "system/multicast_delegate.h"
    /// #include <iostream>
    ///
    /// int main()
    /// {
    ///   // Create an instance of MulticastDelegate.
    ///   System::MulticastDelegate<void(float, float)> operations;
    ///
    ///   // Print the sum of two numbers.
    ///   operations.connect(std::function<void(float, float)>([](float a, float b) -> void
    ///   {
    ///     std::cout << a << " + " << b << " = " << a + b << std::endl;
    ///   }));
    ///
    ///   // Print the sub of two numbers.
    ///   operations.connect(std::function<void(float, float)>([](float a, float b) -> void
    ///   {
    ///     std::cout << a << " - " << b << " = " << a - b << std::endl;
    ///   }));
    ///
    ///   // Print the mul of two numbers.
    ///   operations.connect(std::function<void(float, float)>([](float a, float b) -> void
    ///   {
    ///     std::cout << a << " * " << b << " = " << a * b << std::endl;
    ///   }));
    ///
    ///   // Print the div of two numbers.
    ///   operations.connect(std::function<void(float, float)>([](float a, float b) -> void
    ///   {
    ///     std::cout << a << " / " << b << " = " << a / b << std::endl;
    ///   }));
    ///
    ///   // Call all operations with two numbers.
    ///   operations(10.0f, 2.0f);
    ///
    ///   return 0;
    /// }
    /// /*
    /// This code example produces the following output:
    /// 10 + 2 = 12
    /// 10 - 2 = 8
    /// 10 * 2 = 20
    /// 10 / 2 = 5
    /// */
    /// @endcode
    template <class ReturnType, class... ArgumentTypes>
    class ASPOSECPP_SHARED_CLASS MulticastDelegate<ReturnType(ArgumentTypes...)> : public Details::DelegateHoldingVariables
    {
    private:
        typedef MulticastDelegateTypeInfo ThisTypeInfo;

    public:
        /// The type of the delegates represented by the MulticastDelegate class.
        using Callback = Delegate<ReturnType(ArgumentTypes...)>;

        /// Constructs an empty collection.
        MulticastDelegate()
        {
            m_callbacks = std::make_shared<const std::list<Callback>>();
        }

        /// Destructor.
        ~MulticastDelegate()
        {}

        /// Equivalent to defalt constructor.
        MulticastDelegate(std::nullptr_t) : MulticastDelegate()
        {}

        /// Performs a shallow copy of the delegate collection.
        /// @param o An instance of MulticastDelegate class to copy the collection of delegates from.
        MulticastDelegate(const MulticastDelegate& o)
            : Details::DelegateHoldingVariables(o)
            , m_callbacks(o.m_callbacks)
        {}

        /// Assigns the collection of delegates represented by the specified object to the current object. As a result both objects point to the same collection of delegates.
        /// @param o An instance of MulticastDelegate class containing the collection of delegates to be assigned to the current object.
        MulticastDelegate& operator=(const MulticastDelegate& o)
        {
            if ( this == &o )
                return *this;

#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock(m_guard, o.m_guard);
            std::lock_guard<std::recursive_mutex> l1( m_guard, std::adopt_lock );
            std::lock_guard<std::recursive_mutex> l2(o.m_guard, std::adopt_lock);
#endif
            m_callbacks = o.m_callbacks;
            Details::DelegateHoldingVariables::operator = (o);
            return *this;
        }

        // movable
        /// Moving constructor.
        /// @param o An instance of MulticastDelegate class to move the collection of delegates from.
        MulticastDelegate(MulticastDelegate&& o) noexcept
            : Details::DelegateHoldingVariables(o)
            , m_callbacks(std::move(o.m_callbacks))
        {}

        /// Moving assignment operator.
        /// @param o An instance of MulticastDelegate class to move the collection of delegates from.
        MulticastDelegate& operator=(MulticastDelegate&& o) noexcept
        {
            m_callbacks = std::move(o.m_callbacks);
            Details::DelegateHoldingVariables::operator = (std::move(o));
            return *this;
        }

        /// Constructs an instance and puts the specified delegate to the delegates collection.
        /// @param initial A delegate to put to the delegate collection
        MulticastDelegate(Callback&& initial) : MulticastDelegate()
        {
             mutable_list()->push_back(std::move(initial));
        }

        /// Constructs an instance and puts the specified value to the delegates collection.
        /// @param arg A value to put to the delegate collection
        /// @tparam T Type of the value to put to the delegate collection of the newly constructed instance; the type must be convertible to Callback type.
        template <class T, typename = decltype(Callback(std::declval<T>()))>
        MulticastDelegate(T arg) : MulticastDelegate(Callback(arg))
        {
        }

        /// Constructs an instance and puts the specified value to the delegates collection.
        /// @param arg A value to put to the delegate collection
        MulticastDelegate(std::function<ReturnType(ArgumentTypes...)> arg) : MulticastDelegate(Callback(arg))
        {
        }

        /// Determines whether the delegate collection is empty.
        /// @returns True if the delegate collection is empty, otherwise - false
        bool empty() const
        {
#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock_guard<std::recursive_mutex> lock(m_guard);
#endif

#ifdef ASPOSE_REMOVE_EMPTY_CALLBACKS
            bool res = true;
            if (m_callbacks)
            {
                for (auto it = m_callbacks->begin(); it != m_callbacks->end(); ++it)
                    res &= it->Empty();
            }
            return res;
#else
            return m_callbacks->empty();
#endif
        }

        /// Determines whether the delegate collection is empty.
        /// @returns True if the delegate collection is empty, otherwise - false
        bool IsNull() const { return empty(); }

        const TypeInfo& GetType() const
        {
            return Type();
        }

        String ToString() const
        {
            return GetType().ToString();
        }

        int GetHashCode() const
        {
#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock_guard<std::recursive_mutex> lock(m_guard);
#endif
            return System::GetHashCode(m_callbacks.get());
        }

        bool Equals(const MulticastDelegate& other)
        {
            return *this == other;
        }

        /// Determines whether the delegate collection is empty.
        /// @returns True if the delegate collection is empty, otherwise - false
        bool operator==(const std::nullptr_t&) const
        {
            return empty();
        }

        /// Determines whether the delegate collection is not empty.
        /// @returns True if the delegate collection is not empty, otherwise - false
        bool operator!=(const std::nullptr_t&) const
        {
            return !operator==(nullptr);
        }

        /// Adds the specified delegate to the collection.
        /// @param callback The delegate to add to the collection
        /// @returns A reference to the self
        MulticastDelegate& connect(Callback callback)
        {
#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock_guard<std::recursive_mutex> lock(m_guard);
#endif

            mutable_list()->push_back(std::move(callback));

            return *this;
        }

        /// Adds the specified function object to the delegate collection. The function object is converted to the Callback delegate type before being added to the collection.
        /// @param f The function object to add to the collection
        /// @returns A reference to the self
        /// @tparam R The return type of the function object to add to the collection
        /// @tparam Args The argument list of the function object to add to the collection
        template <class R, class... Args>
        MulticastDelegate& connect(std::function<R(Args...)> f)
        {
            return connect(Callback(f));
        }

        /// Adds the specified MulticastDelegate object to the delegate collection.
        /// @param other An instance of the MulticastDelegate class to add to the delegate collection
        /// @returns A reference to the self
        MulticastDelegate& connect(MulticastDelegate& other)
        {
            if (other.m_callbacks)
                for (auto &callback : *other.m_callbacks)
                    connect(callback);
            return *this;
        }

        /// Adds the specified non-static method of the specified object to the delegate collection.
        /// @param member A pointer to the non-static method of the specified object
        /// @param obj A pointer to an object member method of which is to be added to the delegate collection
        /// @returns A reference to the self
        /// @tparam MemberType The type of the non-static method that is to be added to the delegate collection
        /// @tparam ClassType The type of the object method of which is to be added to the delegate
        template <class MemberType, class ClassType>
        MulticastDelegate& connect(MemberType ClassType::* member, ClassType * obj)
        {
            CODEPORTING_DEBUG_ASSERT( obj != nullptr );
            return connect(Callback(member, obj));
        }

        /// Adds the specified non-static method of the specified object to the delegate collection.
        /// @param member A pointer to the non-static method of the specified object
        /// @param obj A shared pointer to an object member method of which is to be added to the delegate collection
        /// @returns A reference to the self
        /// @tparam MemberType The type of the non-static method that is to be added to the delegate collection
        /// @tparam ClassType The type of the object method of which is to be added to the delegate collection
        template <class MemberType, class ClassType>
        MulticastDelegate& connect(MemberType ClassType::* member, const SharedPtr<ClassType> & obj)
        {
            CODEPORTING_DEBUG_ASSERT(obj != nullptr);
            return connect(Callback(member, obj));
        }

        /// Adds the specified delegate to the collection.
        /// @param callback The delegate to add to the collection
        /// @returns A reference to the self
        MulticastDelegate& operator +=(Callback callback)
        {
            return connect(std::move(callback));
        }

        /// Removes the specified delegate from the delegate collection.
        /// @param callback The delegate to remove from the collection
        /// @returns A reference to the self
        MulticastDelegate& disconnect(Callback callback)
        {
#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock_guard<std::recursive_mutex> lock(m_guard);
#endif
            auto callbacks = mutable_list();
            auto it = std::find_if(callbacks->rbegin(), callbacks->rend(), [&](const Callback& c){return callback == c;});
            if (it != callbacks->rend())
                callbacks->erase(std::next(it).base());
            return *this;
        }

        /// Removes the specified non-static method of the specified object from the delegate collection.
        /// @param member A pointer to the non-static method of the specified object
        /// @param obj A pointer to an object member method of which is to be removed from the delegate collection
        /// @returns A reference to the self
        /// @tparam MemberType The type of the non-static method that is to be removed from the delegate collection
        /// @tparam ClassType The type of the object method of which is to be removed from the delegate collection
        template <class MemberType, class ClassType>
        MulticastDelegate& disconnect(MemberType ClassType::* member, ClassType * obj)
        {
            CODEPORTING_DEBUG_ASSERT(obj != nullptr);
            return disconnect(Callback(member, obj));
        }

        /// Removes the specified non-static method of the specified object from the delegate collection.
        /// @param member A pointer to the non-static method of the specified object
        /// @param obj A shared pointer to an object member method of which is to be removed from the delegate collection
        /// @returns A reference to the self
        /// @tparam MemberType The type of the non-static method that is to be removed from the delegate collection
        /// @tparam ClassType The type of the object method of which is to be removed from the delegate collection
        template <class MemberType, class ClassType>
        MulticastDelegate& disconnect(MemberType ClassType::* member, const SharedPtr<ClassType> & obj)
        {
            CODEPORTING_DEBUG_ASSERT(obj != nullptr);
            return disconnect(Callback(member, obj));
        }

        /// Removes the specified MulticastDelegate object from the delegate collection.
        /// @param other An instance of the MulticastDelegate class to remove from the delegate collection
        /// @returns A reference to the self
        MulticastDelegate& disconnect(MulticastDelegate& other)
        {
            if (other.m_callbacks)
            {
#ifdef ASPOSE_THREADSAFE_DELEGATES
                std::lock(m_guard, o.m_guard);
                std::lock_guard<std::recursive_mutex> l1(m_guard, std::adopt_lock);
                std::lock_guard<std::recursive_mutex> l2(o.m_guard, std::adopt_lock);
#endif
                for (auto &callback : *other.m_callbacks)
                    disconnect(callback);
            }
            return *this;
        }

        /// Removes the specified delegate from the delegate collection.
        /// @param callback The delegate to remove from the collection
        /// @returns A reference to the self
        MulticastDelegate& operator -=(Callback callback)
        {
            return disconnect(std::move(callback));
        }

        /// Determines whether two instances of MulticastDelegate - the current object and the specified object - are equal.
        /// @param other The MulticastDelegate object to compare with
        /// @returns True if both objects represent the same delegates collection, otherwise - false
        bool operator == (const MulticastDelegate& other) const
        {
            CODEPORTING_DEBUG_ASSERT(m_callbacks != nullptr && other.m_callbacks != nullptr);

            // If both delegates point to same callback list - they are equal for sure
            if (m_callbacks == other.m_callbacks)
                return true;

            // Then compare all callbacks one for another
            return *m_callbacks == *other.m_callbacks;
        }

        /// Determines whether two instances of MulticastDelegate - the current object and the specified object - are inequal.
        /// @param other The MulticastDelegate object to compare with
        /// @returns True if both objects represent the same delegates collection, otherwise - false
        bool operator != (const MulticastDelegate& other) const
        {
            return !operator == (other);
        }

        /// Removes all delegates from the delegate collection.
        /// @returns A reference to the self
        MulticastDelegate& disconnect_all_slots()
        {
#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock_guard<std::recursive_mutex> lock(m_guard);
#endif
            mutable_list()->clear();

            return *this;
        }

        /// Cleans out contained callbacks that are empty (not actually calling anything).
        void remove_empty_callbacks() const
        {
            if (m_callbacks && !m_callbacks->empty())
            {
                // We don't need to get unique callbacks here, because even shared callbacks, if empty, are subject to cleanup.
                auto* mutable_callbacks = const_cast<std::list<Callback>*>(m_callbacks.get());

                for (auto it = mutable_callbacks->begin(); it != mutable_callbacks->end();)
                {
                    if (it->Empty())
                        it = mutable_callbacks->erase(it);
                    else
                        ++it;
                }
            }
        }

        /// Invokes all delegates currently present in the delegates collection. Delegates are invoked in the same order as they were added to the collection. The method blocks while the delegates are executed.
        /// @param args Arguments to pass to the delegates to be invoked
        /// @returns Return value of the last invoked delegate
        ReturnType invoke(ArgumentTypes... args) const
        {
#ifdef ASPOSE_THREADSAFE_DELEGATES
            std::lock_guard<std::recursive_mutex> lock(m_guard);
#endif

#ifdef ASPOSE_REMOVE_EMPTY_CALLBACKS
            remove_empty_callbacks();
#endif
            if (m_callbacks && !m_callbacks->empty())
            {
                auto callbacks_copy = m_callbacks; // we must save the current callbacks list in case it will be changed during the call
                auto last = std::prev(callbacks_copy->end()); // always valid, m_callbacks is not empty
                for (auto it = callbacks_copy->begin(); it != last; ++it)
                    (*it)(args...); // ignore result!

                return (*last)(args...);
            }

            throw NullReferenceException(u"MulticastDelegate: Object reference not set to an instance of an object.");
        }

        /// Invokes all delegates currently present in the delegates collection. Delegates are invoked in the same order as they were added to the collection. The operator blocks while the delegates are executed.
        /// @param args Arguments to pass to the delegates to be invoked
        /// @returns Return value of the last invoked delegate
        ReturnType operator()(ArgumentTypes... args) const
        {
            return invoke(args...);
        }

        /// Returns a reference to the TypeInfo object representing the MulticastDelegate class type information.
        static const TypeInfo& Type()
        {
            return *static_holder<ThisTypeInfo>();
        }


        /// NOT IMPLEMENTED
        /// @throws NotImplementedException Always
        template <typename CallbackArgumentType>
        SharedPtr<IAsyncResult> BeginInvoke(ArgumentTypes... args, const AsyncCallback& member, const CallbackArgumentType& obj)
        {
            throw System::NotImplementedException(ASPOSE_CURRENT_FUNCTION);
        }

        /// NOT IMPLEMENTED
        /// @throws NotImplementedException Always
        ReturnType EndInvoke(const SharedPtr<IAsyncResult>&)
        {
            throw System::NotImplementedException(ASPOSE_CURRENT_FUNCTION);
        }

#if defined(ASPOSE_GET_SHARED_MEMBERS) || defined(__DBG_FOR_EACH_MEMBER)
        /// Returns shared pointers and values held by a delegate.
        std::shared_ptr<Details::HeldVariables> GetHeldVariables() const
        {
            auto heldVariables = std::make_shared<Details::HeldVariables>();

            heldVariables->CopyFrom(m_heldVariables);

            if (m_callbacks && !m_callbacks->empty())
            {
                for (auto it = m_callbacks->cbegin(); it != m_callbacks->cend(); ++it)
                {
                    heldVariables->CopyFrom(it->GetHeldVariables());
                }
            }

            return heldVariables;
        }
#endif

    private:
        /// Gets mutable unique copy to callback list.
        /// Creates new copy if it's needed.
        std::list<Callback>* mutable_list()
        {
            CODEPORTING_DEBUG_ASSERT(m_callbacks != nullptr);

            if (m_callbacks.use_count() > 1)
                m_callbacks = std::make_shared<std::list<Callback>>(*m_callbacks);

            return const_cast<std::list<Callback>*>(m_callbacks.get());
        }

        /// The collection of delegates represented by the current object.
        mutable std::shared_ptr<const std::list<Callback>> m_callbacks;

#ifdef ASPOSE_THREADSAFE_DELEGATES
        /// The mutex must be recursive to avoid reentry problem during recursive calls
        mutable std::recursive_mutex m_guard;
#endif
    };

    /// Connects all callbacks from right hand delegate to the end of left hand delegate callback list.
    /// @param lhv The delegate to which callbacks are added.
    /// @param rhv The delegate whose callbacks are being added.
    /// @returns Returns a delegate that contains the callbacks of the left hand value and then the right hand ones.
    template <typename T>
    MulticastDelegate<T> operator+(MulticastDelegate<T> lhv, MulticastDelegate<T> rhv)
    {
        return lhv.connect(rhv);
    }

    /// Disconnects all callbacks in right hand delegate from the end of left hand delegate callback list.
    /// @param lhv The delegate from which callbacks will be removed.
    /// @param rhv The delegate whose callbacks will be removed.
    /// @returns Returns a delegate that contains the callbacks of the left hand value, but without the right hand value ones.
    template <typename T>
    MulticastDelegate<T> operator-(MulticastDelegate<T> lhv, MulticastDelegate<T> rhv)
    {
        return lhv.disconnect(rhv);
    }

    /// @cond
    /// Forward declatation of CastResult used by System::ExplicitCast, System::AsCast and alike functions.
    template <typename TTo> struct CastResult;

    /// Specialization of CastResult structure making sure MulticastResult remains value type instead of wrapping it into SmartPtr.
    /// @tparam T MulticastDelegate argument.
    template <typename T>
    struct ASPOSECPP_SHARED_CLASS CastResult<MulticastDelegate<T>>
    {
        /// An alias for a MusticastDelegate\<T\> type.
        typedef MulticastDelegate<T> type;
    };

    template <class T>
    struct IsBoxable<MulticastDelegate<T>> : std::true_type
    {
    };
    /// @endcond

} // namespace System
#endif // _aspose_system_multicast_delegate_h_
