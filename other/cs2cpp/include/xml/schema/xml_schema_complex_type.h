/// @file xml/schema/xml_schema_complex_type.h

#pragma once

#include <xml/schema/xml_schema_type.h>
#include <xml/schema/xml_schema_derivation_method.h>
#include <xml/schema/xml_schema_content_type.h>
#include <system/shared_ptr.h>
#include <system/enum_helpers.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class DocumentSchemaValidator;
namespace Schema
{
class Compiler;
class ContentValidator;
class Datatype_List;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchema;
class XmlSchemaAnyAttribute;
class XmlSchemaAttributeGroup;
class XmlSchemaContentModel;
enum class XmlSchemaContentProcessing;
class XmlSchemaElement;
enum class XmlSchemaForm;
class XmlSchemaGroup;
class XmlSchemaInference;
class XmlSchemaObject;
class XmlSchemaObjectCollection;
class XmlSchemaObjectTable;
class XmlSchemaParticle;
class XmlSchemaValidator;
} // namespace Schema
class XmlQualifiedName;
namespace Xsl
{
class XmlQueryType;
class XmlQueryTypeFactory;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c complexType element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class defines a complex type that determines the set of attributes and content of an element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaComplexType : public XmlSchemaType
{
    typedef XmlSchemaComplexType ThisType;
    typedef XmlSchemaType BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaComplexType>;

private:
    /// @cond
    friend class System::Xml::DocumentSchemaValidator;
    friend class Datatype_List;
    friend class XmlSchemaInference;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchema;
    friend class XmlSchemaAttributeGroup;
    friend class XmlSchemaType;
    friend class XmlSchemaElement;
    friend class XmlSchemaGroup;
    friend class XmlSchemaValidator;
    friend class Xsl::XmlQueryType;
    friend class Xsl::XmlQueryTypeFactory;
    friend class Xsl::XmlQueryTypeFactory;
    /// @endcond

public:

    /// Returns the information that determines if the @c complexType element can be used in the instance document.
    /// @returns If @c true, an element cannot use this @c complexType element directly and
    /// must use a complex type that is derived from this @c complexType element.
    /// The default is @c false. Optional.
    ASPOSECPP_SHARED_API bool get_IsAbstract();
    /// Sets the information that determines if the @c complexType element can be used in the instance document.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsAbstract(bool value);
    /// Returns the @c block attribute.
    /// @returns The @c block attribute prevents a complex type from being used in the specified type of derivation.
    /// The default is XmlSchemaDerivationMethod::None. Optional.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_Block();
    /// Sets the @c block attribute.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Block(XmlSchemaDerivationMethod value);
    /// Returns information that determines if the complex type has a mixed content model (markup within the content).
    /// @returns @c true, if character data can appear between child elements of this complex type;
    /// otherwise, @c false.
    /// The default is @c false. Optional.
    ASPOSECPP_SHARED_API bool get_IsMixed() override;
    /// Sets information that determines if the complex type has a mixed content model (markup within the content).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsMixed(bool value) override;
    /// Returns the post-compilation XmlSchemaContentModel of this complex type.
    /// @returns The content model type that is one of the XmlSchemaSimpleContent or XmlSchemaComplexContent classes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaContentModel> get_ContentModel();
    /// Sets the post-compilation XmlSchemaContentModel of this complex type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ContentModel(const SharedPtr<XmlSchemaContentModel>& value);
    /// Returns the compositor type as one of the XmlSchemaGroupRef, XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    /// @returns The compositor type.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaParticle> get_Particle();
    /// Sets the compositor type as one of the XmlSchemaGroupRef, XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Particle(const SharedPtr<XmlSchemaParticle>& value);
    /// Returns the collection of attributes for the complex type.
    /// @returns Contains XmlSchemaAttribute and XmlSchemaAttributeGroupRef classes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Attributes();
    /// Returns the value for the XmlSchemaAnyAttribute component of the complex type.
    /// @returns The XmlSchemaAnyAttribute component of the complex type.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnyAttribute> get_AnyAttribute();
    /// Sets the value for the XmlSchemaAnyAttribute component of the complex type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_AnyAttribute(const SharedPtr<XmlSchemaAnyAttribute>& value);
    /// Returns the content model of the complex type which holds the post-compilation value.
    /// @returns The post-compilation value of the content model for the complex type.
    ASPOSECPP_SHARED_API XmlSchemaContentType get_ContentType();
    /// Returns the particle that holds the post-compilation value of the XmlSchemaComplexType::get_ContentType particle.
    /// @returns The particle for the content type.
    /// The post-compilation value of the XmlSchemaComplexType::get_ContentType particle.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaParticle> get_ContentTypeParticle();
    /// Returns the value after the type has been compiled to the post-schema-validation information set (infoset).
    /// This value indicates how the type is enforced when @c xsi:type is used in the instance document.
    /// @returns The post-schema-validated infoset value.
    /// The default is @c BlockDefault value on the @c schema element.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_BlockResolved();
    /// Returns the collection of all the complied attributes of this complex type and its base types.
    /// @returns The collection of all the attributes from this complex type and its base types.
    /// The post-compilation the @c AttributeUses value.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_AttributeUses();
    /// Returns the post-compilation value for @c anyAttribute for this complex type and its base type(s).
    /// @returns The post-compilation value of the @c anyAttribute element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnyAttribute> get_AttributeWildcard();

    /// Initializes a new instance of the XmlSchemaComplexType class.
    ASPOSECPP_SHARED_API XmlSchemaComplexType();

protected:

    /// @cond
    static SharedPtr<XmlSchemaComplexType> get_AnyType();
    static SharedPtr<XmlSchemaComplexType> get_UntypedAnyType();
    static SharedPtr<XmlSchemaComplexType> get_AnyTypeSkip();
    static SharedPtr<ContentValidator> get_AnyTypeContentValidator();
    SharedPtr<XmlSchemaObjectTable> get_LocalElements();
    bool get_HasWildCard();
    void set_HasWildCard(bool value);
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_DerivedFrom() override;

    void SetContentTypeParticle(const SharedPtr<XmlSchemaParticle>& value);
    void SetBlockResolved(XmlSchemaDerivationMethod value);
    void SetAttributeWildcard(const SharedPtr<XmlSchemaAnyAttribute>& value);
    void SetAttributes(const SharedPtr<XmlSchemaObjectCollection>& newAttributes);
    bool ContainsIdAttribute(bool findAll);
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;
    SharedPtr<XmlSchemaObject> Clone(const SharedPtr<XmlSchema>& parentSchema);
    static SharedPtr<XmlSchemaObjectCollection> CloneAttributes(const SharedPtr<XmlSchemaObjectCollection>& attributes);
    static SharedPtr<XmlSchemaParticle> CloneParticle(const SharedPtr<XmlSchemaParticle>& particle, const SharedPtr<XmlSchema>& parentSchema);
    static bool HasParticleRef(const SharedPtr<XmlSchemaParticle>& particle, const SharedPtr<XmlSchema>& parentSchema);
    static bool HasAttributeQNameRef(const SharedPtr<XmlSchemaObjectCollection>& attributes);

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
    const char* DBG_class_name() const override { return "XmlSchemaComplexType"; }
#endif
    /// @endcond

private:

    XmlSchemaDerivationMethod _block;
    SharedPtr<XmlSchemaContentModel> _contentModel;
    SharedPtr<XmlSchemaParticle> _particle;
    SharedPtr<XmlSchemaObjectCollection> _attributes;
    SharedPtr<XmlSchemaAnyAttribute> _anyAttribute;
    SharedPtr<XmlSchemaParticle> _contentTypeParticle;
    XmlSchemaDerivationMethod _blockResolved;
    SharedPtr<XmlSchemaObjectTable> _localElements;
    SharedPtr<XmlSchemaObjectTable> _attributeUses;
    SharedPtr<XmlSchemaAnyAttribute> _attributeWildcard;

    uint8_t _pvFlags;
    static const uint8_t wildCardMask;
    static const uint8_t isMixedMask;
    static const uint8_t isAbstractMask;

    static SharedPtr<XmlSchemaComplexType> CreateAnyType(XmlSchemaContentProcessing processContents);
    void ClearCompiledState();
    static SharedPtr<XmlSchemaObjectCollection> CloneGroupBaseParticles(const SharedPtr<XmlSchemaObjectCollection>& groupBaseParticles, const SharedPtr<XmlSchema>& parentSchema);
    static XmlSchemaForm GetResolvedElementForm(const SharedPtr<XmlSchema>& parentSchema, const SharedPtr<XmlSchemaElement>& element);
    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


