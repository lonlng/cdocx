/// @file xml/xpath/xpath_item.h

#pragma once

#include <system/object.h>
#include <cstdint>


/// @cond
namespace System
{
class DateTime;
class String;
class TypeInfo;
namespace Xml
{
class IXmlNamespaceResolver;
namespace Schema
{
class XmlSchemaType;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

/// Represents an item in the XQuery 1.0 and XPath 2.0 Data Model.
class ASPOSECPP_SHARED_CLASS XPathItem : public virtual System::Object
{
    typedef XPathItem ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XPathItem>;

public:

    /// When overridden in a derived class, gets a value indicating whether the item represents
    /// an XPath node or an atomic value.
    /// @returns @c true if the item represents an XPath node; @c false if the item represents an atomic value.
    virtual ASPOSECPP_SHARED_API bool get_IsNode() = 0;
    /// When overridden in a derived class, gets the XmlSchemaType for the item.
    /// @returns The XmlSchemaType for the item.
    virtual ASPOSECPP_SHARED_API SharedPtr<System::Xml::Schema::XmlSchemaType> get_XmlType() = 0;
    /// When overridden in a derived class, gets the @c string value of the item.
    /// @returns The @c string value of the item.
    virtual ASPOSECPP_SHARED_API String get_Value() = 0;
    /// When overridden in a derived class, gets the current item as a boxed object of
    /// the most appropriate type according to its schema type.
    /// @returns The current item as a boxed object of the most appropriate type.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> get_TypedValue() = 0;
    /// When overridden in a derived class, gets the type of the item.
    /// @returns The type of the item. The default value is String.
    virtual ASPOSECPP_SHARED_API TypeInfo get_ValueType() = 0;
    /// When overridden in a derived class, gets the item's value as a Boolean.
    /// @returns The item's value as a Boolean.
    /// @throws FormatException The item's value is not in the correct format for the Boolean type.
    /// @throws InvalidCastException The attempted cast to Boolean is not valid.
    virtual ASPOSECPP_SHARED_API bool get_ValueAsBoolean() = 0;
    /// When overridden in a derived class, gets the item's value as a DateTime.
    /// @returns The item's value as a DateTime.
    /// @throws FormatException The item's value is not in the correct format for the DateTime type.
    /// @throws InvalidCastException The attempted cast to DateTime is not valid.
    virtual ASPOSECPP_SHARED_API DateTime get_ValueAsDateTime() = 0;
    /// When overridden in a derived class, gets the item's value as a Double.
    /// @returns The item's value as a Double.
    /// @throws FormatException The item's value is not in the correct format for the Double type.
    /// @throws InvalidCastException The attempted cast to Double is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    virtual ASPOSECPP_SHARED_API double get_ValueAsDouble() = 0;
    /// When overridden in a derived class, gets the item's value as an Int32.
    /// @returns The item's value as an Int32.
    /// @throws FormatException The item's value is not in the correct format for the Int32 type.
    /// @throws InvalidCastException The attempted cast to Int32 is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    virtual ASPOSECPP_SHARED_API int32_t get_ValueAsInt() = 0;
    /// When overridden in a derived class, gets the item's value as an Int64.
    /// @returns The item's value as an Int64.
    /// @throws FormatException The item's value is not in the correct format for the Int64 type.
    /// @throws InvalidCastException The attempted cast to Int64 is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    virtual ASPOSECPP_SHARED_API int64_t get_ValueAsLong() = 0;

    /// Returns the item's value as the specified type.
    /// @param returnType The type to return the item value as.
    /// @returns The value of the item as the type requested.
    /// @throws FormatException The item's value is not in the correct format for the target type.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ValueAs(const TypeInfo& returnType);
    /// When overridden in a derived class, returns the item's value as the type specified using
    /// the IXmlNamespaceResolver object specified to resolve namespace prefixes.
    /// @param returnType The type to return the item's value as.
    /// @param nsResolver The IXmlNamespaceResolver object used to resolve namespace prefixes.
    /// @returns The value of the item as the type requested.
    /// @throws FormatException The item's value is not in the correct format for the target type.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws OverflowException The attempted cast resulted in an overflow.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ValueAs(const TypeInfo& returnType, SharedPtr<IXmlNamespaceResolver> nsResolver) = 0;

};

} // namespace XPath
} // namespace Xml
} // namespace System


