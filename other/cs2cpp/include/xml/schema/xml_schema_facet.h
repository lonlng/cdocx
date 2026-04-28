/// @file xml/schema/xml_schema_facet.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class FacetsChecker;
enum class FacetType;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// A base class for all facets that are used when simple types are derived by restriction.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaFacet : public XmlSchemaAnnotated
{
    typedef XmlSchemaFacet ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaFacet>;

private:
    /// @cond
    friend class FacetsChecker;
    friend class FacetsChecker;
    /// @endcond

public:

    /// Returns the @c value attribute of the facet.
    /// @returns The value attribute.
    ASPOSECPP_SHARED_API String get_Value();
    /// Sets the @c value attribute of the facet.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Value(const String& value);
    /// Returns information that indicates that this facet is fixed.
    /// @returns If @c true, value is fixed; otherwise, @c false. The default is @c false. Optional.
    virtual ASPOSECPP_SHARED_API bool get_IsFixed();
    /// Sets information that indicates that this facet is fixed.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_IsFixed(bool value);

    /// Initializes a new instance of the XmlSchemaFacet class.
    ASPOSECPP_SHARED_API XmlSchemaFacet();

protected:

    /// @cond
    System::Xml::Schema::FacetType get_FacetType();
    void set_FacetType(System::Xml::Schema::FacetType value);

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
    const char* DBG_class_name() const override { return "XmlSchemaFacet"; }
#endif
    /// @endcond

private:

    String _value;
    bool _isFixed;
    System::Xml::Schema::FacetType _facetType;

};

/// A vase class for defining @c numeric facets.
/// This class is the base class for numeric facet classes such as XmlSchemaMinLengthFacet.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaNumericFacet : public XmlSchemaFacet
{
    typedef XmlSchemaNumericFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaNumericFacet>;

};

/// Represents the @c length facet from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the length of a @c simpleType element on the data type.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaLengthFacet : public XmlSchemaNumericFacet
{
    typedef XmlSchemaLengthFacet ThisType;
    typedef XmlSchemaNumericFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaLengthFacet>;

public:

    /// Initializes a new instance of the XmlSchemaLengthFacet class.
    ASPOSECPP_SHARED_API XmlSchemaLengthFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c minLength element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the minimum length of the data value of a @c simpleType element.
/// The length must be greater than the value of the @c minLength element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaMinLengthFacet : public XmlSchemaNumericFacet
{
    typedef XmlSchemaMinLengthFacet ThisType;
    typedef XmlSchemaNumericFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaMinLengthFacet>;

public:

    /// Initializes a new instance of the XmlSchemaMinLengthFacet class.
    ASPOSECPP_SHARED_API XmlSchemaMinLengthFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c maxLength element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the maximum length of the data value of a @c simpleType element.
/// The length must be less than the value of the @c maxLength element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaMaxLengthFacet : public XmlSchemaNumericFacet
{
    typedef XmlSchemaMaxLengthFacet ThisType;
    typedef XmlSchemaNumericFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaMaxLengthFacet>;

public:

    /// Initializes a new instance of the XmlSchemaMaxLengthFacet class.
    ASPOSECPP_SHARED_API XmlSchemaMaxLengthFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c pattern element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the value entered for a @c simpleType element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaPatternFacet : public XmlSchemaFacet
{
    typedef XmlSchemaPatternFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaPatternFacet>;

public:

    /// Initializes a new instance of the XmlSchemaPatternFacet class.
    ASPOSECPP_SHARED_API XmlSchemaPatternFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c enumeration facet from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class specifies a list of valid values for a simpleType element. Declaration is contained within a @c restriction declaration.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaEnumerationFacet : public XmlSchemaFacet
{
    typedef XmlSchemaEnumerationFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaEnumerationFacet>;

public:

    /// Initializes a new instance of the XmlSchemaEnumerationFacet class.
    ASPOSECPP_SHARED_API XmlSchemaEnumerationFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c minExclusive element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the minimum value of a @c simpleType element.
/// The element value must be greater than the value of the @c minExclusive element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaMinExclusiveFacet : public XmlSchemaFacet
{
    typedef XmlSchemaMinExclusiveFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaMinExclusiveFacet>;

public:

    /// Initializes a new instance of the XmlSchemaMinExclusiveFacet class.
    ASPOSECPP_SHARED_API XmlSchemaMinExclusiveFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c minInclusive element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the minimum value of a simpleType element.
/// The element value must be greater than or equal to the value of the @c minInclusive element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaMinInclusiveFacet : public XmlSchemaFacet
{
    typedef XmlSchemaMinInclusiveFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaMinInclusiveFacet>;

public:

    /// Initializes a new instance of the XmlSchemaMinInclusiveFacet class.
    ASPOSECPP_SHARED_API XmlSchemaMinInclusiveFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c maxExclusive element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the maximum value of a @c simpleType element.
/// The element value must be less than the value of the @c maxExclusive element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaMaxExclusiveFacet : public XmlSchemaFacet
{
    typedef XmlSchemaMaxExclusiveFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaMaxExclusiveFacet>;

public:

    /// Initializes a new instance of the XmlSchemaMaxExclusiveFacet class.
    ASPOSECPP_SHARED_API XmlSchemaMaxExclusiveFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c maxInclusive element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the maximum value of a @c simpleType element.
/// The element value must be less than or equal to the value of the @c maxInclusive element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaMaxInclusiveFacet : public XmlSchemaFacet
{
    typedef XmlSchemaMaxInclusiveFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaMaxInclusiveFacet>;

public:

    /// Initializes a new instance of the XmlSchemaMaxInclusiveFacet class.
    ASPOSECPP_SHARED_API XmlSchemaMaxInclusiveFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c totalDigits facet from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to specify a restriction on the number of digits that can be entered for the value of a @c simpleType element.
/// That value of @c totalDigits must be a positive integer.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaTotalDigitsFacet : public XmlSchemaNumericFacet
{
    typedef XmlSchemaTotalDigitsFacet ThisType;
    typedef XmlSchemaNumericFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaTotalDigitsFacet>;

public:

    /// Initializes a new instance of the XmlSchemaTotalDigitsFacet class.
    ASPOSECPP_SHARED_API XmlSchemaTotalDigitsFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Specifies a restriction on the number of digits that can be entered for the fraction value of a simpleType element.
/// The value of fractionDigits must be a positive integer. Represents the World Wide Web Consortium (W3C) @c fractionDigits facet.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaFractionDigitsFacet : public XmlSchemaNumericFacet
{
    typedef XmlSchemaFractionDigitsFacet ThisType;
    typedef XmlSchemaNumericFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaFractionDigitsFacet>;

public:

    /// Initializes a new instance of the XmlSchemaFractionDigitsFacet class.
    ASPOSECPP_SHARED_API XmlSchemaFractionDigitsFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the World Wide Web Consortium (W3C) @c whiteSpace facet.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaWhiteSpaceFacet : public XmlSchemaFacet
{
    typedef XmlSchemaWhiteSpaceFacet ThisType;
    typedef XmlSchemaFacet BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaWhiteSpaceFacet>;

public:

    /// Initializes a new instance of the XmlSchemaWhiteSpaceFacet class.
    ASPOSECPP_SHARED_API XmlSchemaWhiteSpaceFacet();

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


