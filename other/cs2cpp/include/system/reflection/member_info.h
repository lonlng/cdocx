/// @file system/reflection/member_info.h
#ifndef _aspose_system_reflection_member_info_h_
#define _aspose_system_reflection_member_info_h_

#include <system/object.h>
#include <system/string.h>
#include <system/reflection/member_types.h>

namespace System { namespace Reflection {

/// Provides reflection information on members.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS MemberInfo : public System::Object
{
public:
    /// Alias for a shared pointer to Object.
    typedef SharedPtr<Object> ObjectPtr;

    /// Declaring type desription.
    /// This type should be allocated on stack and passed to functions by value or by reference.
    /// Never use System::SmartPtr class to manage objects of this type.
    class TypeInternal
    {
    public:
        /// Friend declaration.
        friend MemberInfo;
        /// Gets type short name.
        /// @return short name of type.
        const String& get_Name() const { return m_name; }
        /// Gets type full name.
        /// @return Type full name.
        const String& get_FullName() const { return m_full_name; }

    private:
        /// Type short name.
        String m_name;
        /// Type full name.
        String m_full_name;
    };

    /// Gets member name.
    /// @return Member name.
    ASPOSECPP_SHARED_API const String& get_Name() const;
    /// Gets declaring type.
    /// @return Declaring type information.
    ASPOSECPP_SHARED_API TypeInfo get_DeclaringType() const;
    /// Gets reflected type type.
    /// @return Reflected type information.
    ASPOSECPP_SHARED_API TypeInfo get_ReflectedType() const;
    /// Gets member full name. Can be different in manually implemented parts.
    /// @return Member full name.
    ASPOSECPP_SHARED_API const String& get_FullName() const;

    /// Gets a System::Reflection::MemberTypes value
    /// indicating the type of the member - method, constructor, event, and so on.
    /// @return System::Reflection::MemberTypes value indicating the type of member.
    ASPOSECPP_SHARED_API virtual MemberTypes get_MemberType() const = 0;

    /// Returns an array containing objects that represent all custom attributes applied to the type represented by the current object.
    /// @param attributeType Type of attribute to look for.
    /// @param inherit Whether to check inherited attributes, too.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<Object>> GetCustomAttributes(const TypeInfo& attributeType, bool inherit = false) const;

    /// Returns an array containing objects that represent all custom attributes applied to the type represented by the current object.
    /// @param inherit Whether to check inherited attributes, too.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<Object>> GetCustomAttributes(bool inherit = false) const;

    /// Adds attribute to collection.
    /// @param attribute Attribute to add to current member.
    ASPOSECPP_SHARED_API void AddAttribute(const ObjectPtr& attribute);


protected:
    /// Constructor.
    /// @param full_name Member full name.
    ASPOSECPP_SHARED_API MemberInfo(const String& full_name);

    /// Member full name.
    String m_full_name;
    /// Member name
    String m_name;
    /// Declaring type description.
    TypeInternal m_type_internal;

    /// Alias for a vector of shared pointers to Object.
    typedef std::vector<ObjectPtr> ObjectVector;
    /// Type's attributes.
    ObjectVector m_attributes;
};

}}

#endif
