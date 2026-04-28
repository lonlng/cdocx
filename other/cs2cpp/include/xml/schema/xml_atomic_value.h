/// @file xml/schema/xml_atomic_value.h

#pragma once

#include <xml/xpath/xpath_item.h>
#include <xml/xml_namespace_scope.h>
#include <xml/ixml_namespace_resolver.h>
#include <system/string.h>
#include <system/date_time.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class IDictionary;
} // namespace Generic
} // namespace Collections
enum class TypeCode;
class TypeInfo;
namespace Xml
{
namespace Schema
{
class Datatype_List;
class XmlAnyConverter;
class XmlBooleanConverter;
class XmlDateTimeConverter;
class XmlMiscConverter;
class XmlNumeric10Converter;
class XmlNumeric2Converter;
class XmlSchemaType;
class XmlStringConverter;
class XmlUntypedConverter;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the typed value of a validated XML element or attribute. The XmlAtomicValue class cannot be inherited.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlAtomicValue final : public System::Xml::XPath::XPathItem
{
    typedef XmlAtomicValue ThisType;
    typedef System::Xml::XPath::XPathItem BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlAtomicValue>;

private:
    /// @cond
    friend class Datatype_List;
    friend class XmlNumeric10Converter;
    friend class XmlNumeric2Converter;
    friend class XmlDateTimeConverter;
    friend class XmlBooleanConverter;
    friend class XmlMiscConverter;
    friend class XmlStringConverter;
    friend class XmlUntypedConverter;
    friend class XmlAnyConverter;
    /// @endcond

private:

    class Union : public System::Object
    {
        typedef Union ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        bool boolVal;
        double dblVal;
        int64_t i64Val;
        int32_t i32Val;
        DateTime dtVal;

        Union();

    protected:

        #ifdef ASPOSE_GET_SHARED_MEMBERS
        void GetSharedMembers(System::Object::shared_members_type& result) const override;
        #endif

        #ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to members.
        /// @param visitor Visitor to apply.
        ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
        /// Gets class name.
        /// @return String literal pointer.
        const char* DBG_class_name() const override { return "Union"; }
        #endif


    };

    class NamespacePrefixForQName : public IXmlNamespaceResolver
    {
        typedef NamespacePrefixForQName ThisType;
        typedef IXmlNamespaceResolver BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        String prefix;
        String ns;

        NamespacePrefixForQName(const String& prefix, const String& ns);

        String LookupNamespace(const String& prefix) override;
        String LookupPrefix(const String& namespaceName) override;
        SharedPtr<Collections::Generic::IDictionary<String, String>> GetNamespacesInScope(XmlNamespaceScope scope) override;

    };


public:

    /// Returns a value indicating whether the validated XML element or attribute is an XPath node or an atomic value.
    /// @returns @c true if the validated XML element or attribute is an XPath node;
    /// @c false if the validated XML element or attribute is an atomic value.
    ASPOSECPP_SHARED_API bool get_IsNode() override;
    /// Returns the XmlSchemaType for the validated XML element or attribute.
    /// @returns The XmlSchemaType for the validated XML element or attribute.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaType> get_XmlType() override;
    /// Returns the type of the validated XML element or attribute.
    /// @returns The type of the validated XML element or attribute. The default value is String.
    ASPOSECPP_SHARED_API TypeInfo get_ValueType() override;
    /// Returns the current validated XML element or attribute as a boxed object of the most appropriate type according to its schema type.
    /// @returns The current validated XML element or attribute as a boxed object of the most appropriate type.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_TypedValue() override;
    /// Returns the validated XML element or attribute's value as a Boolean.
    /// @returns The validated XML element or attribute's value as a Boolean.
    /// @throws FormatException The validated XML element or attribute's value is not in the correct format for the Boolean type.
    /// @throws InvalidCastException The attempted cast to Boolean is not valid.
    ASPOSECPP_SHARED_API bool get_ValueAsBoolean() override;
    /// Returns the validated XML element or attribute's value as a DateTime.
    /// @returns The validated XML element or attribute's value as a DateTime.
    /// @throws FormatException The validated XML element or attribute's value is not in the correct format for the DateTime type.
    /// @throws InvalidCastException The attempted cast to DateTime is not valid.
    ASPOSECPP_SHARED_API DateTime get_ValueAsDateTime() override;
    /// Returns the validated XML element or attribute's value as a Double.
    /// @returns The validated XML element or attribute's value as a Double.
    /// @throws FormatException The validated XML element or attribute's value is not in the correct format for the Double type.
    /// @throws InvalidCastException The attempted cast to Double is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    ASPOSECPP_SHARED_API double get_ValueAsDouble() override;
    /// Returns the validated XML element or attribute's value as an Int32.
    /// @returns The validated XML element or attribute's value as an Int32.
    /// @throws FormatException The validated XML element or attribute's value is not in the correct format for the Int32 type.
    /// @throws InvalidCastException The attempted cast to Int32 is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    ASPOSECPP_SHARED_API int32_t get_ValueAsInt() override;
    /// Returns the validated XML element or attribute's value as an Int64.
    /// @returns The validated XML element or attribute's value as an Int64.
    /// @throws FormatException The validated XML element or attribute's value is not in the correct format for the Int64 type.
    /// @throws InvalidCastException The attempted cast to Int64 is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    ASPOSECPP_SHARED_API int64_t get_ValueAsLong() override;
    /// Returns the String value of the validated XML element or attribute.
    /// @returns The String value of the validated XML element or attribute.
    ASPOSECPP_SHARED_API String get_Value() override;

    /// Returns a copy of this XmlAtomicValue object.
    /// @returns An XmlAtomicValue object copy of this XmlAtomicValue object.
    ASPOSECPP_SHARED_API SharedPtr<XmlAtomicValue> Clone();
    /// Returns the validated XML element or attribute's value as the type specified using
    /// the IXmlNamespaceResolver object specified to resolve namespace prefixes.
    /// @param type The type to return the validated XML element or attribute's value as.
    /// @param nsResolver The IXmlNamespaceResolver object used to resolve namespace prefixes.
    /// @returns The value of the validated XML element or attribute as the type requested.
    /// @throws FormatException The validated XML element or attribute's value is not in the correct format for the target type.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    ASPOSECPP_SHARED_API SharedPtr<Object> ValueAs(const TypeInfo& type, SharedPtr<IXmlNamespaceResolver> nsResolver) override;
    /// Returns the String value of the validated XML element or attribute.
    /// @returns The String value of the validated XML element or attribute.
    ASPOSECPP_SHARED_API String ToString() const override;

protected:

    /// @cond
    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, bool value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, bool value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, DateTime value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, DateTime value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, double value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, double value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, int32_t value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, int32_t value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, int64_t value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, int64_t value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, const String& value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, String value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, const String& value, const SharedPtr<IXmlNamespaceResolver>& nsResolver);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, String value, SharedPtr<IXmlNamespaceResolver> nsResolver));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, const SharedPtr<Object>& value);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, SharedPtr<Object> value));

    XmlAtomicValue(const SharedPtr<XmlSchemaType>& xmlType, const SharedPtr<Object>& value, const SharedPtr<IXmlNamespaceResolver>& nsResolver);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlAtomicValue, CODEPORTING_ARGS(SharedPtr<XmlSchemaType> xmlType, SharedPtr<Object> value, SharedPtr<IXmlNamespaceResolver> nsResolver));
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlAtomicValue();

    /// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlAtomicValue"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaType> _xmlType;
    SharedPtr<Object> _objVal;
    TypeCode _clrType;
    XmlAtomicValue::Union _unionVal;
    SharedPtr<XmlAtomicValue::NamespacePrefixForQName> _nsPrefix;

    String ToString_NonConst();
    String GetPrefixFromQName(const String& value);

};

} // namespace Schema
} // namespace Xml
} // namespace System


