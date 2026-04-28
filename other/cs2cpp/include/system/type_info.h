/// @file system/type_info.h
/// Contains the declaration System::TypeInfo class and supporting classes.
#ifndef _TypeInfo_h_
#define _TypeInfo_h_

#include <system/shared_ptr.h>
#include <system/reflection/binding_flags.h>
#include <system/reflection.h>

#include <memory>
#include <vector>
#include <functional>
#include <type_traits>
#include <cwchar>
#include <iosfwd>
#include <map>

#include <fwd.h>

namespace System { namespace Reflection { class Assembly; } }
namespace System { namespace Reflection { class MemberInfo; }}
namespace System { namespace Reflection { class MethodInfo; }}
namespace System { namespace Reflection { class PropertyInfo; } }
namespace System { namespace Reflection { class ConstructorInfo; }}
namespace System { namespace Reflection { class FieldInfo; } }

namespace System
{

class Object;
class String;

/// A helper class that generates a hash value from a c-string.
/// @tparam i The length of the string for which the hash value has to be generated.
template<unsigned i>
class StringHashCompiletime
{
public:
    /// Generates a hash value from the specified c-string of the specified length.
    /// @param input A pointer to the beginning of the c-string.
    /// @param strLen The length of the specified c-string
    /// @param hash The output parameter, which contains the resulting hash value on method return
    static void Hash(uint32_t &hash, int strLen, const char_t *input)
    {
        hash = input[strLen - i] + (hash << 6) + (hash << 16) - hash;
        StringHashCompiletime<i - 1>::Hash(hash, strLen, input);
    }
};

/// @cond
/// Specialization for the empty string.
template<>
class StringHashCompiletime<0>
{
public:
    /// Does nothing.
    static void Hash(uint32_t &hash, int strLen, const char_t* input)
    {
        ASPOSE_UNUSED(hash);
        ASPOSE_UNUSED(strLen);
        ASPOSE_UNUSED(input);
    }
};
/// @endcond

class TypeInfo;

/// Wrapper for a pointer to an instance of TypeInfo class.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
struct TypeInfoPtr
{
    /// Unique pointer to the TypeInfo object.
    std::unique_ptr<TypeInfo> ptr;
    /// Returns a raw pointer to the represented TypeInfo object.
    operator TypeInfo*()
    {
        return ptr.get();
    }

    /// Default constructor.
    TypeInfoPtr() = default;

    /// Constructor.
    /// @param info Information about a type.
    ASPOSECPP_SHARED_API TypeInfoPtr(const std::type_info& info);

    /// Constructor.
    /// @param name Type name.
    /// @param hash Type name hash.
    ASPOSECPP_SHARED_API TypeInfoPtr(const char_t* name, uint32_t hash);

    /// Constructor.
    /// @param name Type name.
    ASPOSECPP_SHARED_API TypeInfoPtr(const char_t* name);

    /// Constructor.
    /// @param name Type name.
    ASPOSECPP_SHARED_API TypeInfoPtr(const String& name);

    /// Destructor.
    ASPOSECPP_SHARED_API ~TypeInfoPtr();
};

class TypeInfoImpl;

/// Represents a particular type and provides information about it.
class ASPOSECPP_SHARED_CLASS TypeInfo
{
    friend class TypeInfoImpl;

    typedef SharedPtr<Object> ObjectPtr;
    typedef const TypeInfo& (*GetTypeInfoFunPtr)();

    std::shared_ptr<TypeInfoImpl> m_pimpl;
    TypeInfoImpl *getPipml() const;


public:
    /// Calculates hash for specified string.
    /// @param str String to calculate hash for.
    /// @return Hash value.
    static uint32_t StringHash(const char_t *str)
    {
        uint32_t hash = 0;

        while (char_t c = *str++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }
    
    /// Default constructor (no type is set).
    ASPOSECPP_SHARED_API TypeInfo();
    /// Null object constructor (no type is set).
    ASPOSECPP_SHARED_API TypeInfo(std::nullptr_t);
    /// Constructor.
    /// @param name Type name.
    ASPOSECPP_SHARED_API TypeInfo(const char_t* name);
    /// Constructor.
    /// @param name Type name.
    /// @param hash Type name hash.
    ASPOSECPP_SHARED_API TypeInfo(const char_t* name, uint32_t hash);
    /// Constructor.
    /// @param info Information about a type.
    ASPOSECPP_SHARED_API TypeInfo(const std::type_info& info);

    /// Returns the name of the type represented by the current object.
    ASPOSECPP_SHARED_API String get_Name() const;

    /// Gets the namespace of the Type.
    ASPOSECPP_SHARED_API String get_Namespace() const;

    /// Returns the fully qualified name (but without the assembly name) of the type represented by the current
    /// object.
    ASPOSECPP_SHARED_API String get_FullName() const;

    /// NOT IMPLEMENTED.
    /// Returns a pointer to the assembly in which the type represented by the current object is declared.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Reflection::Assembly> get_Assembly() const;

    /// NOT IMPLEMENTED.
    /// Returns the fully qualified name including the assembly name of the type represented by the current object.
    ASPOSECPP_SHARED_API String get_AssemblyQualifiedName() const;

    /// Determines whether the type represented by the current object is a subclass of the specified class.
    /// @param type the type to compare with the current type
    ASPOSECPP_SHARED_API bool IsSubclassOf(const TypeInfo& type) const;

    /// Determines whether the specified object is an instance of the current type.
    /// @param obj The object to compare with the current type
    /// @returns true if the current type is in the inheritance hierarchy of the object represented by obj
    ASPOSECPP_SHARED_API bool IsInstanceOfType(const SharedPtr<Object>& obj) const;

    /// Determines whether an instance of a specified type can be assigned to a variable of the current type
    /// @param type the type to compare with the current type
    ASPOSECPP_SHARED_API bool IsAssignableFrom(const TypeInfo& type) const;

    /// NOT IMPLEMENTED.
    /// Indicates whether one or more attributes of the specified type or of its derived types is applied to this member.
    /// @param attributeType The type of custom attribute to search for. The search includes derived types.
    /// @param inherit true to search this member's inheritance chain to find the attributes; otherwise,
    /// false. This parameter is ignored for properties and events.
    /// @return true if one or more instances of attributeType or any of its derived types is applied to this member; otherwise, false.
    ASPOSECPP_SHARED_API bool IsDefined(const TypeInfo& attributeType, bool inherit) const;

    /// Gets a value indicating whether the Type is declared sealed.
    ASPOSECPP_SHARED_API bool get_IsSealed() const;
    /// Gets a value indicating whether the Type is an interface; that is, not a class or a value type.
    ASPOSECPP_SHARED_API bool get_IsInterface() const;
    /// Gets a value indicating whether the Type is abstract and must be overridden.
    ASPOSECPP_SHARED_API bool get_IsAbstract() const;
    /// Gets a value indicating whether the current Type represents an enumeration.
    ASPOSECPP_SHARED_API bool get_IsEnum() const;
    /// Gets a value that indicates whether the type is an array.
    ASPOSECPP_SHARED_API bool get_IsArray() const;
    /// Gets a value indicating whether the Type is a class or a delegate; that is, not a value type or interface.
    ASPOSECPP_SHARED_API bool get_IsClass() const;
    /// Gets a value indicating whether the Type is a value type.
    ASPOSECPP_SHARED_API bool get_IsValueType() const;
    /// Gets a value indicating whether the Type can be accessed by code outside the assembly.
    ASPOSECPP_SHARED_API bool get_IsVisible() const;
    /// Gets a value indicating whether the current Type object has type parameters that have not been replaced by specific types
    ASPOSECPP_SHARED_API bool get_ContainsGenericParameters() const;
    // /Gets a value indicating whether the current type is a generic type
    ASPOSECPP_SHARED_API bool get_IsGenericType() const;
    /// Gets a value indicating whether the current Type represents a generic type definition, from which other generic types can be constructed
    ASPOSECPP_SHARED_API bool get_IsGenericTypeDefinition() const;
    /// Gets an array of the generic type arguments for this type.
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> get_GenericTypeArguments() const;
    /// Gets an array of the generic type arguments for this type.
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> GetGenericArguments() const;

    /// Gets all the interfaces implemented or inherited by the current Type.
    ASPOSECPP_SHARED_API ArrayPtr<TypeInfo> GetInterfaces() const;

    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API TypeInfo GetElementType() const;

    /// searches for the constructors defined for the current Type, using the specified BindingFlags.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::ConstructorInfo>> GetConstructors(System::Reflection::BindingFlags bindingAttr) const;
    /// Returns all the public constructors defined for the current Type
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::ConstructorInfo>> GetConstructors() const;
    /// Searches for a public instance constructor whose parameters match the types in the specified array.
    ASPOSECPP_SHARED_API SharedPtr<System::Reflection::ConstructorInfo> GetConstructor(const ArrayPtr<TypeInfo>& types) const;

    /// Returns a string containing the name of the type represented by the current object.
    ASPOSECPP_SHARED_API String ToString() const;

    /// Returns a hash value associated with the type represented by the current object.
    ASPOSECPP_SHARED_API uint32_t Hash() const;

    /// Returns a hash code associated with this instance.
    int GetHashCode() const
    {
        return Hash();
    }

    bool Equals(const TypeInfo& other) const
    {
        return *this == other;
    }

    /// Determines if the current and the specified TypeInfo objects are equal.
    /// @param info The TypeInfo object to compare with
    /// @returns True if the objects' hashes are equal, otherwise - false
    bool operator == (const TypeInfo& info) const
    {
        if (*this == nullptr && info == nullptr)
        {
            return true;
        }

        if (*this == nullptr || info == nullptr)
        {
            return false;
        }

        return Hash() == info.Hash();
    }

    /// Determines if the current and the specified TypeInfo objects are not equal.
    /// @param info The TypeInfo object to compare with
    /// @returns True if the objects' hashes are not equal, otherwise - false
    bool operator != (const TypeInfo& info) const
    {
        return !operator==(info);
    }
        
    /// Determines if the current TypeInfo object is a null-object, i.e. does not represent any type.
    /// @returns True if the current TypeInfo object is a null-object, otherwise - false
    bool operator == (std::nullptr_t) const
    {
        return !m_pimpl;
    }

    /// Determines if the current TypeInfo object is not a null-object, i.e. it represents some type.
    /// @returns True if the current TypeInfo object is not a null-object, otherwise - false
    bool operator != (std::nullptr_t) const
    {
        return !!m_pimpl;
    }

    /// Adds the specified attribute to the list of type's attributes.
    /// @param attribute A constant reference to an object that represents an attribute to be added
    ASPOSECPP_SHARED_API void AddAttribute(const ObjectPtr& attribute);
    /// Adds the specified member to the list of type's members.
    /// @param member Member to add.
    ASPOSECPP_SHARED_API void AddMember(const SharedPtr<System::Reflection::MemberInfo>& member);
    /// Gets list of the members with specified name.
    /// @param name Name of the member to get.
    /// @return Array of member descriptors (empty if no member is found).
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::MemberInfo>> GetMember(const String& name) const;
    /// Gets list of the members with specified name.
    /// @param name Name of the member to get.
    /// @return Array of member descriptors (empty if no member is found).
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::MemberInfo>> get_DeclaredMember(const String& name) const;
    /// Gets method with specified name.
    /// @param name Name of the method to get.
    /// @return Method descriptor (or null if not found).
    ASPOSECPP_SHARED_API SharedPtr<System::Reflection::MethodInfo> GetMethod(const String& name) const;

    /// Returns all the public properties of the current Type.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::PropertyInfo>> GetProperties() const;
    /// Searches for the properties of the current Type, using the specified binding constraints.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::PropertyInfo>> GetProperties(System::Reflection::BindingFlags bindingAttr) const;
    /// Searches for the fields defined for the current Type, using the specified binding constraints.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<System::Reflection::FieldInfo>> GetFields(System::Reflection::BindingFlags bindingAttr) const;
    /// Searches for the specified field, using the specified binding constraints.
    ASPOSECPP_SHARED_API SharedPtr<System::Reflection::FieldInfo> GetField(const System::String& name, System::Reflection::BindingFlags bindingAttr) const;

    /// Searches for the custom attribute applied having the specified type and applied to the type reprsented by
    /// the current object.
    /// @param attributeType The constant reference to the TypeInfo object representing the type of the attribute to
    /// search
    /// @returns A pointer to an object representing the found attribute, or null-pointer if no attribute was foud
    /// matching the search criteria
    ASPOSECPP_SHARED_API ObjectPtr GetCustomAttribute(const TypeInfo& attributeType) const;

    /// Returns an array containing objects that represent all custom attributes applied to the type.
    ASPOSECPP_SHARED_API ArrayPtr<ObjectPtr> GetCustomAttributes() const;
    /// Returns an array containing objects that represent specific attributes applied to the type.
    /// @param attributeType Type of the attribute to look for.
    /// @param inherit Whether to look for inherited attributes as well.
    ASPOSECPP_SHARED_API ArrayPtr<ObjectPtr> GetCustomAttributes(const TypeInfo& attributeType, bool inherit) const;

    /// Returns base type descritor.
    /// @return Pointer to base type descriptor or null if not found.
    ASPOSECPP_SHARED_API TypeInfo get_BaseType() const;
    /// Sets base type descritor.
    /// @param basetype Pointer to base type descriptor to set.
    ASPOSECPP_SHARED_API void SetBaseType(GetTypeInfoFunPtr basetype);
    /// Sets template parameter type descritor.
    /// @param templParam Pointer to template parameter type descriptor to set.
    ASPOSECPP_SHARED_API void SetTemplParamType(const TypeInfo& templParam);

    /// Gets template parameter type descritor.
    ASPOSECPP_SHARED_API TypeInfo GetTemplParamType() const;

    /// Sets TypeInfo to null
    ASPOSECPP_SHARED_API void reset();

    /// Sets default constructor for the type T
    template <class T> inline void AddDefaultConstructor();

    /// Function pointer to construct type
    typedef std::function<ObjectPtr()> DefaultConstructor;

    /// Sets default constructor by the functor that creates class instanse
    /// @param method functor that creates class instanse
    ASPOSECPP_SHARED_API void AddDefaultConstructor(DefaultConstructor method);

    /// Sets a value indicating whether the Type is a value type.
    ASPOSECPP_SHARED_API void set_IsValueType(bool value);

    /// Provides unique TypeInfo structure for BoxedValue type to be shared by multiple Boxed* classes.
    /// @tparam T Type to hold TypeInfo structure for.
    /// @return TypeInfo structure which is unique per class.
    template <class T> static inline const TypeInfo& BoxedValueType()
    {
        return *System::static_holder<TypeInfo::BoxedValue<T>>();
    }

    /// TypeInfo structure for BoxedValue class.
    template <class T> struct BoxedValue : TypeInfoPtr
    {
        /// Fills appropriate type name.
        BoxedValue()
            : TypeInfoPtr(typeid(BoxedValue<T>))
        {}
    };

    /// Constant representing empty list of TypeInfo
    ASPOSECPP_SHARED_API static ArrayPtr<TypeInfo> EmptyTypes;

    /// Constant representing empty list of TypeInfo
    ASPOSECPP_SHARED_API static TypeInfo EmptyType;

    /// Returns a TypeInfo object that represent TypeInfo class.
    static const TypeInfo& Type();

};

/// Insert data into the stream using UTF-8 encoding.
/// @param stream Output stream to insert data to.
/// @param type_info Data to insert.
/// @return \p stream.
ASPOSECPP_SHARED_API std::ostream& operator<<(std::ostream& stream, const TypeInfo& type_info);

/// Insert data into the stream.
/// @param stream Output stream to insert data to.
/// @param type_info Data to insert.
/// @return \p stream.
ASPOSECPP_SHARED_API std::wostream& operator<<(std::wostream& stream, const TypeInfo& type_info);

} // namespace System

namespace std
{
/// Template specification for TypeInfo type.
template<>
struct hash<System::TypeInfo> {
public:
    /// Generates hash for the specified value.
    /// @param ti An object for which to generate a hash
    /// @returns A hash for @p ti
    size_t operator()(const System::TypeInfo &ti) const
    {
        return ti.Hash();
    }
};
}

#endif // _TypeInfo_h_
