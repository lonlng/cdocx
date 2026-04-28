/// @file system/object.h
#pragma once

#include <defines.h>

#include <system/type_info.h>
#include <system/reflection.h>
#include <system/smart_ptr.h>
#include <system/weak_ptr.h>
#include <system/dynamic_weak_ptr.h>
#include <system/refcount.h>

#include <system/cycles_detection.h>
#include <system/details/dbg_tools.h>
#include <system/details/dbg_garbage_collection.h>
#include <system/details/leakage_detector.h>
#include <system/details/lock_context.h>

#include <type_traits>
#include <string>
#include <list>
#include <utility>
#include <map>
#include <memory>
#include <cmath>
#include <mutex>


#ifdef ASPOSECPPLIB_BEING_BUILT
#include <boost/thread/recursive_mutex.hpp>
#endif

namespace boost {
    /// Forward declaration of recursive_mutex class.
    ASPOSECPP_3RD_PARTY_CLASS(recursive_mutex);
}


namespace System
{

class String;
class Details_Exception;

/// @brief Base class that enables using methods available for System.Object class in C#. All non-trivial classes used with translated environment should inherit it.
/// 
/// Alongside with methods available in C# System.Object class, it also enables support for some concepts specific for translated code environment. This includes reference
/// counting used by smart pointer classes (System::SmartPtr, System::WeakPtr, System::DynamicWeakPtr) and other services related to memory management, debug, etc.
/// 
/// Each Object has two reference counters: shared reference counter and weak reference counter. Weak reference counter is always stored in detached data structure
/// rather than in Object itself which allows weak pointers overlive referenced object. Smart reference counter is stored either in object itself or in same detached
/// structure, depending on ENABLE_EXTERNAL_REFCOUNT macro state. By default, it is enabled in debug builds and disabled in release builds. If smart pointer counter
/// is stored in object itself, detached data structure is created only if weak pointers to object exist. Otherwise, it is created alongside with object itself.
/// 
/// All smart pointers use these two reference counters and contribute to same and only ownership group.
/// 
/// If Object subclass is created on stack, no smart pointers to it may be created, otherwise there is a stack deletion issue.
///
/// This type can be allocated either in stack as value type or in heap using System::MakeObject() function.
/// Once the object is allocated, never mix up these two usecases: having SmartPtr pointers onto stack-allocated objects is strictly prohibited.
class ASPOSECPP_SHARED_CLASS Object
{
public:
    /// @brief Alias for smart pointer type.
    typedef SmartPtr<Object> ptr;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @brief structure to keep list of shared pointers contained in object.
    typedef System::Details::SharedMembersType shared_members_type;
#endif
    /// @brief Creates object. Initializes all internal data structures.
    ASPOSECPP_SHARED_API Object();
    /// @brief Destroys object. Frees all internal data structures.
    virtual ASPOSECPP_SHARED_API ~Object();

    // the following 2 members needed for MemberwiseClone()
    /// @brief Copy constructor. Doesn't copy anything, really, just initializes new object and enables copy constructing subclasses.
    /// @param x Formal parameter.
    ASPOSECPP_SHARED_API Object(Object const& x);
    /// @brief Assignment operator. Doesn't copy anything, really, just initializes new object and enables copy constructing subclasses.
    /// @param x Formal parameter.
    Object& operator = (Object const& x){ ASPOSE_UNUSED(x); return *this; } // does nothing
    /// @brief Increments shared reference count. Shouldn't be called directly; instead, use smart pointers or ThisProtector.
    /// @return Raw pointer to current object.
    Object* SharedRefAdded();
    /// @brief Decrements and returns shared reference count. Shouldn't be called directly; instead, use smart pointers or ThisProtector.
    /// @return Decremented value of shared reference counter.
    int SharedRefRemovedSafe();
    /// @brief Decreases shared reference count by specified value.
    /// @param count Number of shared references to remove.
    /// @return Decreased value of shared reference counter.
    int RemovedSharedRefs(int count);
    /// @brief Increments weak reference count. Shouldn't be called directly; instead, use smart pointers or ThisProtector.
    /// @return Pointer to reference counting data structure associated with object.
    Detail::SmartPtrCounter* WeakRefAdded();
    /// @brief Decrements weak reference count. Shouldn't be called directly; instead, use smart pointers or ThisProtector.
    void WeakRefRemoved();
    /// @brief Gets reference counter data structure associated with the object.
    /// @return Pointer to reference counting data structure associated with object.
    inline Detail::SmartPtrCounter* GetCounter();
    /// @brief Gets current value of shared reference counter.
    /// @return Current value of shared reference counter.
    int SharedCount() const;
    /// @brief Implements C# lock() statement locking. Call directly or use LockContext sentry object.
    ASPOSECPP_SHARED_API void Lock();
    /// @brief Implements C# lock() statement unlocking. Call directly or use LockContext sentry object.
    ASPOSECPP_SHARED_API void Unlock();
    /// @brief Compares objects using C# Object.Equals semantics.
    /// @param obj Object to compare current one to.
    /// @return True if objects are considered equal and false otherwise.
    virtual ASPOSECPP_SHARED_API bool Equals(ptr obj);
    /// @brief Compares objects by reference.
    /// @param objA First pointer to compare.
    /// @param objB Second pointer to compare.
    /// @return True if pointers match and false otherwise.
    static bool ReferenceEquals(ptr const& objA, ptr const& objB)
    {
        return objA == objB;
    }
    /// @brief Compares objects by reference.
    /// @tparam T Type of objects to compare.
    /// @param objA First object to compare.
    /// @param objB Second object to compare.
    /// @return True if object addresses match and false otherwise.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value, bool>::type ReferenceEquals(T const& objA, T const& objB)
    {
        return &objA == &objB;
    }
    /// @brief Reference-compares value type object with nullptr.
    /// @tparam T Type of object to compare.
    /// @param objA First object to compare.
    /// @return Always returns false as value types cannot be nulled.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value, bool>::type ReferenceEquals(T const& objA, std::nullptr_t)
    {
        return false;
    }
    /// @brief Compares reference type objects in C# style.
    /// @tparam T1 Type of first object to compare.
    /// @tparam T2 Type of second object to compare.
    /// @param objA First object to compare.
    /// @param objB Second object to compare.
    /// @return True if objects match either by reference or semantically (by Object.Equals-alike comparison), false otherwise.
    template<typename T1, typename T2>
    static typename std::enable_if<IsSmartPtr<T1>::value && IsSmartPtr<T2>::value, bool>::type Equals(T1 const& objA, T2 const& objB)
    {
        return ReferenceEquals(objA, objB) || (objA != nullptr && objB != nullptr && objA->Equals(objB));
    }
    /// @brief Compares value type objects in C# style.
    /// @tparam T1 Type of first object to compare.
    /// @tparam T2 Type of second object to compare.
    /// @param objA First object to compare.
    /// @param objB Second object to compare.
    /// @return True if objects are considered equal by equality operator available, false otherwise.
    template<typename T1, typename T2>
    static typename std::enable_if<!IsSmartPtr<T1>::value && !IsSmartPtr<T2>::value, bool>::type Equals(T1 const& objA, T2 const& objB)
    {
        return objA == objB;
    }
    /// @brief Analog of C# Object.GetHashCode() method. Enables hashing of custom objects.
    /// @return Hash code value as calculated by corresponding class.
    virtual ASPOSECPP_SHARED_API int32_t GetHashCode() const;
    /// @brief Analog of C# Object.ToString() method. Enables converting custom objects to string.
    /// @return String representation as provided by final class.
    virtual ASPOSECPP_SHARED_API String ToString() const;
    /// @brief Analog of C# Object.MemberwiseClone() method. Enables cloning custom types.
    /// @return Pointer to object copy created.
    /// @throws NotImplemented exception is thrown by default. Implement manually or use polymorphic_memberwiseclone option to enable this method in translated code.
    virtual ASPOSECPP_SHARED_API ptr MemberwiseClone() const;
    /// @brief Implements C# typeof(System.Object) construct.
    /// @return TypeInfo object which describes System::Object type.
    static const TypeInfo& Type()
    {
        return *static_holder<ThisTypeInfo>();
    }
    /// @brief Gets actual type of object. Analog of C# System.Object.GetType() call.
    /// @return TypeInfo object which describes final type.
    virtual ASPOSECPP_SHARED_API const TypeInfo& GetType() const;
    /// @brief Check if object represents an instance of type described by targetType. Analog of C# 'is' operator.
    /// @param targetType TypeInfo structure describing the type to test current object against.
    /// @return True if object is of tagged type or its subclass, false otherwise.
    virtual ASPOSECPP_SHARED_API bool Is(const TypeInfo& targetType) const;
    /// @brief Set n'th template argument a weak pointer (rather than shared). Allows switching pointers in containers to weak mode.
    /// @param argument Index of template argument to treat as weak poiner.
    virtual ASPOSECPP_SHARED_API void SetTemplateWeakPtr(uint32_t argument);
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Gets list of non-null shared pointers 
    virtual ASPOSECPP_SHARED_API void GetSharedMembers(shared_members_type&) const;
#endif
    /// @brief For internal purposes only.
    /// @param helper FastRttiBase structure specialized with a desired type.
    /// @param out_ptr A pointer to a desired type if conversion is available.
    /// @return True if a class supports FastRTTI operations.
    virtual ASPOSECPP_SHARED_API bool FastCast(const Details::FastRttiBase& helper, void** out_ptr) const;

#ifdef __DBG_TOOLS
private:
    friend struct ::System::Details::DbgTools;

    /// Local stack trace information for debug purposes.
    System::Details::DbgTools::stack_s_int_string_t m_personal_st;
    /// When set from debugger, enables collecting stack trace information for this object.
    bool m_rec_personal_st;
    /// Current object's id.
    mutable int m_instanceNo;
#endif

#if defined(ENABLE_CYCLES_DETECTION_EXT)
private:
    friend class System::Debug::ExternalObjectCollector;
    unsigned m_instance_id;
#endif

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Calls visitor on all shared pointers owned by the object.
    /// @param visitor Visitor to invoke.
    virtual ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const;
    /// Provides human-readable class name.
    /// @return Human-readable hardcoded class name.
    virtual const char* DBG_class_name() const { return "Object"; }
#endif

private:
    friend class ::System::Detail::SmartPtrCounter;
    friend class ::System::Details::LeakageDetector;

#ifdef ENABLE_EXTERNAL_REFCOUNT
    /// Data structure that counts shared and weak references to related object.
    std::unique_ptr<Detail::SmartPtrCounter> m_external_count;
#else
    /// Data structure that counts weak references to related object.
    std::atomic<Detail::SmartPtrCounter*> m_external_count;
    /// Shared references count used by SmartPtr class.
    Detail::RefCount m_shared_count;
#endif

    /// Service class to hold TypeInfo structure describing System::Object class. Used by Object::Type().
    struct ThisTypeInfo : TypeInfoPtr
    {
        /// Creates Object private TypeInfo structure.
        ThisTypeInfo()
            : TypeInfoPtr(u"System::Object")
        {}

        // Explicitly deleting several members to avoid warnings
        ThisTypeInfo(const ThisTypeInfo&) = delete;
        ThisTypeInfo(ThisTypeInfo&&) = delete;
        ThisTypeInfo& operator = (const ThisTypeInfo&) = delete;
        ThisTypeInfo& operator = (ThisTypeInfo&&) = delete;
    };

    /// Mutex type to use for lock() statement translation.
    typedef boost::recursive_mutex mutex;
    /// Wrapper class to create global mutex. Some implementations can require this mutex is never deleted as it is being accessed on globals destruction stage.
    class GlobalMutexHolder;
    /// Global mutex shared by all objects not having their private mutexes yet.
    static GlobalMutexHolder s_globalMutex;

    mutex* volatile m_objectMutex;

#ifdef ASPOSECPP_DEBUG
    /// Information on currently executing constructor used by some debug features.
    mutable const std::string* m_currentConstructor;
#endif

#ifdef __DBG_GARBAGE_COLLECTION
    /// GC generation object falls into.
    int m_generation;
    friend bool ASPOSECPP_SHARED_API System::Details::__buildIsolationIsland(Object *&last, std::map<const Object*, shared_members_type> &island, int generation);
#endif
};

/// Emulates C#-style floating point comparison where two NaNs are considered equal even though according to IEC 60559:1989 NaN is not equal to any value,
/// including NaN.
/// @param objA LHS floating point value.
/// @param objB RHS floating point value.
/// @return True if @p objA and @p objB are both NaN or equal, false otherwise.
template<>
inline bool Object::Equals<float, float>(float const& objA, float const& objB)
{
    return (std::isnan(objA) && std::isnan(objB)) ? true : objA == objB;
}

/// Emulates C#-style floating point comparison where two NaNs are considered equal even though according to IEC 60559:1989 NaN is not equal to any value,
/// including NaN.
/// @param objA LHS floating point value.
/// @param objB RHS floating point value.
/// @return True if @p objA and @p objB are both NaN or equal, false otherwise.
template<>
inline bool Object::Equals<double, double>(double const& objA, double const& objB)
{
    return (std::isnan(objA) && std::isnan(objB)) ? true : objA == objB;
}

/// Implementation
inline Object* Object::SharedRefAdded()
{
#ifdef ENABLE_EXTERNAL_REFCOUNT
    return GetCounter()->SharedRefAdded();
#else
    ++m_shared_count;
    return this;
#endif
}

/// Implementation
inline int Object::SharedRefRemovedSafe()
{
#ifdef ENABLE_EXTERNAL_REFCOUNT
    return GetCounter()->SharedRefRemovedSafe();
#else
    return --m_shared_count;
#endif
}

/// Implementation
inline int Object::RemovedSharedRefs(int count)
{
#ifdef ENABLE_EXTERNAL_REFCOUNT
    return m_external_count->DecreaseSharedRef(count);
#else
    return (m_shared_count -= count);
#endif
}

/// Implementation
inline Detail::SmartPtrCounter* Object::WeakRefAdded()
{
    return GetCounter()->WeakRefAdded();
}

/// Implementation
inline void Object::WeakRefRemoved()
{
    GetCounter()->WeakRefRemoved();
}

/// Implementation
inline Detail::SmartPtrCounter* Object::GetCounter()
{
#ifdef ENABLE_EXTERNAL_REFCOUNT
    return m_external_count.get();
#else
    Detail::SmartPtrCounter *counter = m_external_count.load();
    if (counter == nullptr)
    {
        std::unique_ptr<Detail::SmartPtrCounter> new_counter(new Detail::SmartPtrCounter(this));
        if (m_external_count.compare_exchange_strong(counter, new_counter.get()))
            return new_counter.release();
    }
    return counter;
#endif
}

/// Implementation
inline int Object::SharedCount() const
{
#ifdef ENABLE_EXTERNAL_REFCOUNT
    return m_external_count->SharedCount();
#else
    return m_shared_count;
#endif
}

// ------------------------ casting implemetation --------------------------------
namespace Details {
    /// Throws InvalidCastException.
    /// @throw InvalidCastException unconditionally.
    [[noreturn]] ASPOSECPP_SHARED_API void ThrowInvalidCastException();
    /// Helper function to allow throwing InvalidCastException from expressions.
    /// @tparam T Expression type.
    /// @return Never actually returns as function throws.
    template <typename T>
    T ThrowInvalidCastException_helper()
    {
        ThrowInvalidCastException();
        return T();
    }
}

/// Template magic to deduce cast results.
template <typename TTo>
struct CastResult
{
    /// An alias for a pointer to an instance of @p TTo.
    typedef SmartPtr<TTo> type;
};

/// @cond
template <typename TTo>
struct CastResult<SmartPtr<TTo>>
{
    /// An alias for the SmartPointer type
    typedef SmartPtr<TTo> type;
};
/// @endcond

/// @cond
struct ExceptionWrapperType {};
/// @endcond

/// A template predicate that determines if the specified type is a Exception class or its descendant.
/// @tparam T The type to check
template <typename T> struct IsExceptionWrapper : std::is_base_of<System::ExceptionWrapperType, T> {};

/// Performs cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed or nullptr otherwise.
template<typename TTo, typename TFrom>
typename std::enable_if<!IsExceptionWrapper<TTo>::value, typename CastResult<TTo>::type>::type 
Cast_noexcept(SmartPtr<TFrom> const& obj) // throw()
{
    return obj.template dynamic_pointer_cast<TTo>();    
}

/// Performs cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
template<typename TTo, typename TFrom>
typename std::enable_if<!IsExceptionWrapper<TTo>::value, typename CastResult<TTo>::type>::type
Cast(SmartPtr<TFrom> const& obj) // throw(System::InvalidCastException)
{
    auto casted = dynamic_cast<TTo*>(obj.get());
    return obj && !casted
        ? Details::ThrowInvalidCastException_helper<typename CastResult<TTo>::type>()
        : SmartPtr<TTo>(obj, casted, obj.get_Mode());
}

//////////////////////////////////////////////////////////////////////////
/// Old obsolete casts. Will be removed in future versions

/// Performs dynamic cast on Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Source Exception type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<IsExceptionWrapper<TFrom>::value && IsExceptionWrapper<TTo>::value && (std::is_convertible<TTo, TFrom>::value || std::is_base_of<TTo, TFrom>::value), TTo>::type
DynamicCast_noexcept(const TFrom& obj) noexcept
{
    return
        (DynamicCast_noexcept<typename TTo::ExceptionType>(obj.Get()) != nullptr)
        ? TTo(obj.Get())
        : TTo(nullptr)
    ;
}

/// Performs dynamic cast on Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Source Exception type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<IsExceptionWrapper<TFrom>::value && IsExceptionWrapper<TTo>::value && (std::is_convertible<TTo, TFrom>::value || std::is_base_of<TTo, TFrom>::value), TTo>::type
DynamicCast(const TFrom& obj) // throw(System::InvalidCastException)
{
    return
        obj != nullptr
        ? ((DynamicCast_noexcept<typename TTo::ExceptionType>(obj.Get()) != nullptr)
            ? TTo(obj.Get())
            : Details::ThrowInvalidCastException_helper<TTo>())
        : TTo(nullptr)
    ;
}

// static cast

/// Performs static cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<!IsExceptionWrapper<TTo>::value, typename CastResult<TTo>::type>::type 
StaticCast_noexcept(SmartPtr<TFrom> const& obj) // throw()
{
    return Cast_noexcept<TTo, TFrom>(obj);
}

/// Performs static cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<!IsExceptionWrapper<TTo>::value, typename CastResult<TTo>::type>::type
StaticCast(SmartPtr<TFrom> const& obj) // throw(System::InvalidCastException)
{
    return Cast<TTo, TFrom>(obj);
}

/// Performs static cast on WeakPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename CastResult<TTo>::type StaticCast_noexcept(WeakPtr<TFrom> const& obj) // throw()
{
    return Cast_noexcept<TTo, TFrom>(obj);
}

/// Performs static cast on WeakPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename CastResult<TTo>::type StaticCast(WeakPtr<TFrom> const& obj) // throw(System::InvalidCastException)
{
    return obj != nullptr ? Cast<TTo, TFrom>(obj) : typename CastResult<TTo>::type();
}

/// Performs static cast of null objects.
/// @tparam TTo Target pointee type.
/// @return nullptr.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo>
[[deprecated]] typename CastResult<TTo>::type StaticCast(std::nullptr_t) // throw()
{
    // to process code like System::ExplicitCast<System::Object>(nullptr)
    return typename CastResult<TTo>::type(nullptr);
}

/// Specialization for arithmetic types.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_arithmetic<TFrom>::value, TTo>::type StaticCast(TFrom value)
{
    return TTo(value);
}

/// Process cast from String to String 
template<typename TTo>
[[deprecated]] typename std::enable_if<std::is_same<TTo, System::String>::value, TTo>::type StaticCast(TTo value)
{
    return value;
};

/// Specialization for arithmetic types.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_arithmetic<TFrom>::value, TTo>::type StaticCast(const TFrom* value)
{
    return TTo(value);
}

/// Performs static cast on non-pointer objects.
/// @tparam TTo Target type.
/// @tparam TFrom Source type.
/// @param obj Source object.
/// @return Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<!std::is_same<TFrom, System::String>::value && !IsExceptionWrapper<TFrom>::value && !IsSmartPtr<TFrom>::value && !std::is_arithmetic<TFrom>::value, TTo>::type StaticCast(const TFrom& obj)
{
    //it is for special cases, like exception classes
    if (!obj.Is(TTo::Type()))
        Details::ThrowInvalidCastException();
    return static_cast<TTo&>(obj);
}

// dynamic cast

/// Performs dynamic cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<!IsExceptionWrapper<TTo>::value, typename CastResult<TTo>::type>::type
DynamicCast_noexcept(SmartPtr<TFrom> const& obj) noexcept
{
    return Cast_noexcept<TTo, TFrom>(obj);
}

/// Performs static cast on Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Source Exception type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<IsExceptionWrapper<TFrom>::value && IsExceptionWrapper<TTo>::value && (std::is_convertible<TTo, TFrom>::value || std::is_base_of<TTo, TFrom>::value), TTo>::type
StaticCast_noexcept(const TFrom& obj) // throw()
{
    return
        (DynamicCast_noexcept<typename TTo::ExceptionType>(obj.Get()) != nullptr)
        ? TTo(obj.Get())
        : TTo(nullptr)
    ;
}

/// Performs static cast on Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Source Exception type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<IsExceptionWrapper<TFrom>::value && IsExceptionWrapper<TTo>::value && (std::is_convertible<TTo, TFrom>::value || std::is_base_of<TTo, TFrom>::value), TTo>::type
StaticCast(const TFrom& obj) // throw(System::InvalidCastException)
{
    return
        obj != nullptr
        ? ((DynamicCast_noexcept<typename TTo::ExceptionType>(obj.Get()) != nullptr)
            ? TTo(obj.Get())
            : Details::ThrowInvalidCastException_helper<TTo>())
        : TTo(nullptr)
    ;
}


/// Performs dynamic cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<!std::is_enum<TTo>::value && !IsExceptionWrapper<TTo>::value, typename CastResult<TTo>::type>::type
DynamicCast(SmartPtr<TFrom> const& obj) // throw(System::InvalidCastException)
{
    return Cast<TTo, TFrom>(obj);
}

namespace Detail {
    /// Converts boxed enum value to integral type
    /// @param obj Boxed enum object.
    /// @return Integral represenattion of boxed enum value.
    /// @throw InvalidCastException if obj is not a boxed enum.
    ASPOSECPP_SHARED_API uint64_t GetIEnumUnsignedLongLongValue(const SmartPtr<Object>& obj);
}

/// Unboxes boxed enum via cast.
/// @tparam TTo Target enum type.
/// @tparam TFrom Source pointee type.
/// @param obj Pointer to the object to unbox data from.
/// @return Unboxed enum value.
/// @throw InvalidCastException if obj is not a boxed enum.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_enum<TTo>::value, TTo>::type DynamicCast(SmartPtr<TFrom> obj)
{
    return static_cast<TTo>(Detail::GetIEnumUnsignedLongLongValue(obj));
}

/// Performs dynamic cast of null objects.
/// @tparam TTo Target pointee type.
/// @return nullptr.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo>
[[deprecated]] typename CastResult<TTo>::type DynamicCast(std::nullptr_t) noexcept
{
    // to process code like System::ExplicitCast<System::Object>(nullptr)
    return SmartPtr<TTo>();
}

/// Performs dynamic cast on non-pointer objects.
/// @tparam TTo Target type.
/// @tparam TFrom Source type.
/// @param obj Source object.
/// @return Cast result.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<
    !IsExceptionWrapper<TFrom>::value && !IsSmartPtr<TFrom>::value && std::is_convertible<TTo, TFrom>::value /* check if TFrom is base for TTo */
    , TTo>::type DynamicCast(TFrom &obj)
{
    return *dynamic_cast<TTo*>(&obj);
}

/// Performs static cast on Objects to Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Object type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_same<System::Object, TFrom>::value && IsExceptionWrapper<TTo>::value, TTo>::type
StaticCast_noexcept(SmartPtr<TFrom> obj) noexcept
{
    auto exception_ptr = DynamicCast_noexcept<typename TTo::ExceptionType>(obj);
    return exception_ptr != nullptr ? TTo(StaticCast_noexcept<System::Details_Exception>(exception_ptr)) : TTo(nullptr);
}

/// Performs static cast on Objects to Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Object type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_same<System::Object, TFrom>::value && IsExceptionWrapper<TTo>::value, TTo>::type
StaticCast(SmartPtr<TFrom> obj) noexcept
{
    if (obj == nullptr)
        return TTo(nullptr);

    auto exception_ptr = DynamicCast_noexcept<typename TTo::ExceptionType>(obj);
    return exception_ptr != nullptr ? TTo(StaticCast_noexcept<System::Details_Exception>(exception_ptr)) : Details::ThrowInvalidCastException_helper<TTo>();
}

/// Performs dynamic cast on Objects to Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Object type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed or nullptr otherwise.
/// @deprecated Left for backwards compatibility. Use AsCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_same<System::Object, TFrom>::value && IsExceptionWrapper<TTo>::value, TTo>::type
DynamicCast_noexcept(SmartPtr<TFrom> obj) noexcept
{
    auto exception_ptr = DynamicCast_noexcept<typename TTo::ExceptionType>(obj);
    return exception_ptr != nullptr ? TTo(StaticCast_noexcept<System::Details_Exception>(exception_ptr)) : TTo(nullptr);
}

/// Performs dynamic cast on Objects to Exception objects.
/// @tparam TTo Target Exception type.
/// @tparam TFrom Object type.
/// @param obj Source pointer.
/// @returns Cast result if cast is allowed.
/// @throw InvalidCastException if cast is not allowed.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template <typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_same<System::Object, TFrom>::value && IsExceptionWrapper<TTo>::value, TTo>::type
DynamicCast(SmartPtr<TFrom> obj) // throw(System::InvalidCastException)
{
    if (obj == nullptr)
        return TTo(nullptr);

    auto exception_ptr = DynamicCast_noexcept<typename TTo::ExceptionType>(obj);
    return exception_ptr != nullptr ? TTo(StaticCast_noexcept<System::Details_Exception>(exception_ptr)) : Details::ThrowInvalidCastException_helper<TTo>();
}

/// Performs dynamic cast from IntPtr to pointer.
/// @tparam TTo Target type.
/// @tparam TFrom Source type.
/// @param value Source IntPtr value.
/// @return Cast result.
/// @deprecated Left for backwards compatibility. Use ExplicitCast instead.
template<typename TTo, typename TFrom>
[[deprecated]] typename std::enable_if<std::is_pointer<TTo>::value && std::is_same<IntPtr, TFrom>::value, TTo>::type DynamicCast(TFrom value) noexcept
{
    return reinterpret_cast<TTo>(value);
}

/// End of deprecated casts
//////////////////////////////////////////////////////////////////////////

/// Performs const cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed or nullptr otherwise.
template<typename TTo, typename TFrom>
typename CastResult<TTo>::type ConstCast(const SmartPtr<TFrom>& obj) // throw()
{
    return obj->Is(TTo::Type()) ? System::const_pointer_cast<TTo>(obj) : SmartPtr<TTo>();
}

/// Performs real static cast on SmartPtr objects.
/// @tparam TTo Target pointee type.
/// @tparam TFrom Source pointee type.
/// @param obj Source pointer.
/// @return Cast result if cast is allowed, otherwise the behavior is undefined.
template <typename TTo, typename TFrom>
typename CastResult<TTo>::type ForceStaticCast(SmartPtr<TFrom> const& obj) // throw(System::InvalidCastException)
{
    return SmartPtr<TTo>(obj, static_cast<TTo*>(obj.get()));
}

/// Performs memberwise cloning using copy constructor.
/// @tparam T Class to be copy-constructed. Subclass information is being lost.
/// @param ptr Pointer to the object to clone.
/// @return Pointer to cloned object.
template<typename T>
SmartPtr<Object> MemberwiseClone(T* ptr)
{
    return MakeObject<T>(*ptr);
}

/// Clones reference record and applies initializer functor to it.
/// @tparam T Record type to clone.
/// @tparam A Initialization functor type.
/// @param record Shared pointer to the object to clone and initialize.
/// @param initializer Initialization functor being applied to record clone.
/// @return Shared pointer to cloned record.
template<typename T, typename A>
SharedPtr<T> With(const SharedPtr<T>& record, const A& initializer)
{
    auto result = MakeSharedPtr<T>(static_cast<T*>(record->_Clone_()));
    initializer(*result);
    return result;
}

/// Copies struct record and applies initializer functor to it.
/// @tparam T Record type to copy.
/// @tparam A Initialization functor type.
/// @param record Record to copy and initialize.
/// @param initializer Initialization functor being applied to record copy.
/// @return Copied record.
template <typename T, typename A>
T With(const T& record, const A& initializer)
{
    auto result = record;
    initializer(result);
    return result;
}

namespace Runtime {
    namespace CompilerServices {
        /// Helper class to get some object information in runtime
        class RuntimeHelpers
        {
        public:
            /// Gets hash code on arbitrary type. Calls Object::GetHashCode() to do so.
            /// @tparam T Type to get hash code for.
            /// @param obj Object to get information from.
            /// @return Hash code value as calcualted by target implementation.
            template<typename T>
            static int GetHashCode(SmartPtr<T> const& obj)
            {
                return obj->Object::GetHashCode();
            }
        };
    }
}

/// Implementation
inline System::Object* System::Detail::SmartPtrCounter::Lock()
{
#ifdef ENABLE_EXTERNAL_REFCOUNT
    return SharedRefAdded();
#else
    return m_object->SharedRefAdded();
#endif
}

/// Implementation
template <typename T>
SmartPtr<Object> SmartPtr<T>::ToObjectPtr() const
{
    return SmartPtr<Object>(GetObjectOrNull());
}

/// Implementation
template <typename T>
void SmartPtr<T>::SetContainedTemplateWeakPtr(uint32_t argument) const
{
    if (Object *const object = GetObjectOrNull())
        object->SetTemplateWeakPtr(argument);
}

/// Implementation
template <typename T>
bool SmartPtr<T>::Is(const System::TypeInfo &target) const
{
    if (m_data.IsNull())
        return false;
    else if (m_data.GetMode() == SmartPtrMode::Shared)
        return m_data.SharedGetObject()->Is(target);
    else
        return m_data.WeakGetCounter()->GetObject()->Is(target);
}

/// Implementation
template <typename T>
Object* SmartPtr<T>::ReleaseSharedAndGetObjectToDelete(SharedRefReleaser *releaser)
{
    const int count = releaser->SharedRefRemovedSafe();

    System::Details::MakeObjectLeakageDetector::ReportLeakCycle(count);

#ifdef ENABLE_EXTERNAL_REFCOUNT
    if (releaser->GetOwnershipState() != System::Detail::SmartPtrCounter::ObjectOwnershipState::OwnedByPointers)
        return nullptr;

    Object *const object = releaser->GetObject();
#else
    Object *const& object = releaser;
#endif

    if (count == 0)
        return object;

    return nullptr;
}


namespace Details {

    /// Implementation
    template <unsigned int leaf, unsigned int ...leafs>
    void WeakLeafMaker<leaf, leafs...>::Apply(System::Object *ptr)
    {
        ptr->SetTemplateWeakPtr(leaf);
        WeakLeafMaker<leafs...>::Apply(ptr);
    }
}

/// Prints value to ostream. Mostly used for debug.
ASPOSECPP_SHARED_API void PrintTo(const System::Object& value, std::ostream* stream);

/// Insert data into the stream using UTF-8 encoding.
/// @param stream Output stream to insert data to.
/// @param object Data to insert.
/// @return \p stream.
ASPOSECPP_SHARED_API std::ostream& operator<<(std::ostream& stream, const System::Object& object);

/// Insert data into the stream.
/// @param stream Output stream to insert data to.
/// @param object Data to insert.
/// @return \p stream.
ASPOSECPP_SHARED_API std::wostream& operator<<(std::wostream& stream, const System::Object& object);

} // namespace System

  /// An alias for System::Object class.
typedef System::Object object;

#include <system/details/this_protector.h>
#include <system/details/for_each_member_visitor.h>
