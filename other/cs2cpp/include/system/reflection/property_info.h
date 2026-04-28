/// @file system/reflection/property_info.h
#pragma once
#include <functional>
#include <system/object_ext.h>
#include <system/delegate.h>
#include <system/object.h>
#include <system/string.h>
#include <system/reflection/member_info.h>
#include <system/collections/list.h>

namespace System { namespace Reflection {

/// Represents property information.
class ASPOSECPP_SHARED_CLASS PropertyInfo : public MemberInfo
{
public:
    /// Gets property value from specific object.
    /// @param obj Object to read property from.
    /// @return Value of specified property for specified object.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Object> GetValue(System::SharedPtr<System::Object> obj);
    /// Gets property value from specific object.
    /// @param obj Object to read property from.
    /// @param indexer These are optional index values for indexed properties. For non-indexed properties, this value should be null.
    /// @return Value of specified property for specified object.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Object> GetValue(System::SharedPtr<System::Object> obj, System::ArrayPtr<System::SharedPtr<System::Object>> indexer);
    /// Sets property value to specific object.
    /// @param obj Object to write property to.
    /// @param value Value of property to set.
    ASPOSECPP_SHARED_API void SetValue (System::SharedPtr<System::Object> obj, System::SharedPtr<System::Object> value);
    /// Sets property value to specific object.
    /// @param obj Object to write property to.
    /// @param indexer These are optional index values for indexed properties. For non-indexed properties, this value should be null.
    /// @param value Value of property to set.
    ASPOSECPP_SHARED_API void SetValue (System::SharedPtr<System::Object> obj, System::SharedPtr<System::Object> value, System::ArrayPtr<System::SharedPtr<System::Object>> indexer);

    /// Gets property type.
    /// @return Type of the property.
    ASPOSECPP_SHARED_API TypeInfo get_PropertyType();

    /// Gets a MemberTypes value indicating that this member is a property.
    ASPOSECPP_SHARED_API virtual MemberTypes get_MemberType() const override;

    /// Sets the type of this property.
    /// @param type property type
    void set_PropertyType(const TypeInfo& type)
    {
        m_property_type = type;
    }

    /// Constructor. Property with only const getter
    /// @tparam PropertyType Type of the property.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param get_prop_method Getter method.
    template <class PropertyType, typename ClassType>
    PropertyInfo(
        String name,
        System::SharedPtr<PropertyType>(ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<System::SharedPtr<PropertyType>(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            throw NotImplementedException();
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            return get_function((ClassType *)obj.get());
        };

    }

    /// Constructor. Property with only non-const getter
    /// @tparam PropertyType Type of the property.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param get_prop_method Getter method.
    template <class PropertyType, typename ClassType>
    PropertyInfo(
        String name,
        System::SharedPtr<PropertyType>(ClassType::*get_prop_method)() ) :
        MemberInfo(name)
    {
        std::function<System::SharedPtr<PropertyType>(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            throw NotImplementedException();
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            return get_function((ClassType *)obj.get());
        };

    }

    /// Constructor.
    /// @tparam PropertyType Type of the property.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <class PropertyType, typename ClassType>
    PropertyInfo(
        String name, 
        void (ClassType::*set_prop_method)(System::SharedPtr<PropertyType>), 
        System::SharedPtr<PropertyType> (ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, System::SharedPtr<PropertyType>)> set_function = set_prop_method;
        std::function<System::SharedPtr<PropertyType>(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, System::Object::ptr value) -> void {
            set_function((ClassType *)obj.get(), ExplicitCast<PropertyType>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr  {
            return get_function((ClassType *)obj.get());
        };

    }

    /// Constructor. Nullable property with setter and getter
    /// @tparam PropertyType Type of the property.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <class NullableType, typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::Nullable<NullableType>),
        System::Nullable<NullableType>(ClassType::*get_prop_method)()) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, System::Nullable<NullableType>)> set_function = set_prop_method;
        std::function<System::Nullable<NullableType>(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, System::Object::ptr value) -> void {
            set_function((ClassType *)obj.get(), System::ObjectExt::UnboxToNullable<NullableType>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            System::Nullable<NullableType> value = get_function((ClassType *)obj.get());
            return System::ObjectExt::Box<System::Nullable<NullableType>>(value);
        };

    }

    /// Constructor. Nullable property with const getter only
    /// @tparam PropertyType Type of the property.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <class NullableType, typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::Nullable<NullableType>),
        System::Nullable<NullableType>(ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, System::Nullable<NullableType>)> set_function = set_prop_method;
        std::function<System::Nullable<NullableType>(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, System::Object::ptr value) -> void {
            set_function((ClassType *)obj.get(), System::ObjectExt::UnboxToNullable<NullableType>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            System::Nullable<NullableType> value = get_function((ClassType *)obj.get());
            return System::ObjectExt::Box<System::Nullable<NullableType>>(value);
        };

    }

    /// Constructor. Object property with getter only
    /// @tparam PropertyType Type of the property.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <class PropertyType, typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::SharedPtr<PropertyType>),
        System::SharedPtr<PropertyType>(ClassType::*get_prop_method)()) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, System::SharedPtr<PropertyType>)> set_function = set_prop_method;
        std::function<System::SharedPtr<PropertyType>(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, System::Object::ptr value) -> void {
            set_function(dynamic_cast<ClassType*>(obj.get()), ExplicitCast<PropertyType>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            return get_function(dynamic_cast<ClassType *>(obj.get()));
        };

    }

    /// Constructs string property information.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::String),
        System::String (ClassType::*get_prop_method)()) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, String)> set_function = set_prop_method;
        std::function<String(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<String>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            String value = get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<String>(value);
        };
    }

    /// Constructs string property information from class with const getter.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::String),
        System::String(ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, String)> set_function = set_prop_method;
        std::function<String(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<String>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            String value = get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<String>(value);
        };
    }

    /// Constructs Decimal property information.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::Decimal),
        System::Decimal (ClassType::*get_prop_method)()) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, Decimal)> set_function = set_prop_method;
        std::function<Decimal(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<Decimal>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            Decimal value = get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<Decimal>(value);
        };
    }

    /// Constructs Decimal property information from class with const getter.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(System::Decimal),
        System::Decimal(ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, Decimal)> set_function = set_prop_method;
        std::function<Decimal(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<Decimal>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            Decimal value = get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<Decimal>(value);
        };
    }


    /// Constructs boolean property information.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(bool),
        bool (ClassType::*get_prop_method)()) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, bool)> set_function = set_prop_method;
        std::function<bool(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<bool>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            bool value = get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<bool>(value);
        };
    }

    /// Constructs boolean property information from class with const getter
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(bool),
        bool (ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, bool)> set_function = set_prop_method;
        std::function<bool(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<bool>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            bool value =  get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<bool>(value);
        };
    }

    /// Constructs int64_t property information.
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(int64_t),
        int64_t (ClassType::*get_prop_method)()) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, int64_t)> set_function = set_prop_method;
        std::function<int64_t(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<int64_t>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            int64_t value = get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<int64_t>(value);
        };
    }

    /// Constructs int64_t property information from class with const getter
    /// @tparam ClassType Type of the class the property belongs to.
    /// @param name Property name.
    /// @param set_prop_method Setter method.
    /// @param get_prop_method Getter method.
    template <typename ClassType>
    PropertyInfo(
        String name,
        void (ClassType::*set_prop_method)(int64_t),
        int64_t (ClassType::*get_prop_method)() const) :
        MemberInfo(name)
    {
        std::function<void(ClassType *, int64_t)> set_function = set_prop_method;
        std::function<int64_t(ClassType *)> get_function = get_prop_method;

        set_method = [=](const System::Object::ptr& obj, const System::Object::ptr& value) -> void {
            set_function(dynamic_cast<ClassType *>(obj.get()), System::ObjectExt::Unbox<int64_t>(value));
        };
        get_method = [=](const System::Object::ptr& obj) -> System::Object::ptr {
            int64_t value =  get_function(dynamic_cast<ClassType *>(obj.get()));
            return System::ObjectExt::Box<int64_t>(value);
        };
    }

protected:
    std::function<void(System::Object::ptr, System::Object::ptr)> set_method;
    std::function<System::Object::ptr(System::Object::ptr)> get_method;
    TypeInfo m_property_type;
};

}}
