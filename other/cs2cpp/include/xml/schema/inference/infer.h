/// @file xml/schema/inference/infer.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerable;
} // namespace Generic
} // namespace Collections
namespace Xml
{
class NameTable;
namespace Schema
{
class XmlSchema;
class XmlSchemaAttribute;
class XmlSchemaComplexType;
class XmlSchemaElement;
class XmlSchemaObject;
class XmlSchemaObjectCollection;
class XmlSchemaObjectTable;
class XmlSchemaSet;
class XmlSchemaSimpleContentExtension;
class XmlSchemaType;
} // namespace Schema
class XmlNamespaceManager;
class XmlQualifiedName;
class XmlReader;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Infers an XML Schema Definition Language (XSD) schema from an XML document.
/// The XmlSchemaInference class cannot be inherited.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaInference final : public System::Object
{
    typedef XmlSchemaInference ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaInference>;

public:

    /// Affects occurrence and type information inferred by the XmlSchemaInference class for elements and attributes in an XML document.
    enum class InferenceOption
    {
        /// Indicates that a more restrictive schema declaration should be inferred for a particular element or attribute.
        Restricted,
        /// Indicates that a less restrictive schema declaration should be inferred for a particular element or attribute.
        Relaxed
    };


public:

    /// Returns the XmlSchemaInference::InferenceOption value that affects schema occurrence declarations inferred from the XML document.
    /// @returns An XmlSchemaInference::InferenceOption object.
    ASPOSECPP_SHARED_API XmlSchemaInference::InferenceOption get_Occurrence();
    /// Sets the XmlSchemaInference::InferenceOption value that affects schema occurrence declarations inferred from the XML document.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Occurrence(XmlSchemaInference::InferenceOption value);
    /// Returns the XmlSchemaInference::InferenceOption value that affects types inferred from the XML document.
    /// @returns An XmlSchemaInference::InferenceOption object.
    ASPOSECPP_SHARED_API XmlSchemaInference::InferenceOption get_TypeInference();
    /// Sets the XmlSchemaInference::InferenceOption value that affects types inferred from the XML document.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_TypeInference(XmlSchemaInference::InferenceOption value);

    /// Initializes a new instance of the XmlSchemaInference class.
    ASPOSECPP_SHARED_API XmlSchemaInference();

    /// Infers an XML Schema Definition Language (XSD) schema from the XML document contained in the XmlReader object specified.
    /// @param instanceDocument An XmlReader object containing the XML document to infer a schema from.
    /// @returns An XmlSchemaSet object containing the inferred schemas.
    /// @throws XmlException The XML document is not well-formed.
    /// @throws XmlSchemaInferenceException The XmlReader object is not positioned on the root node or on an element.
    /// An error occurs during the schema inference process.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSet> InferSchema(const SharedPtr<XmlReader>& instanceDocument);
    /// Infers an XML Schema Definition Language (XSD) schema from the XML document contained in the XmlReader object specified,
    /// and refines the inferred schema using an existing schema in the XmlSchemaSet object specified with the same target namespace.
    /// @param instanceDocument An XmlReader object containing the XML document to infer a schema from.
    /// @param schemas An XmlSchemaSet object containing an existing schema used to refine the inferred schema.
    /// @returns An XmlSchemaSet object containing the inferred schemas.
    /// @throws XmlException The XML document is not well-formed.
    /// @throws XmlSchemaInferenceException The XmlReader object is not positioned on the root node or on an element.
    /// An error occurs during the schema inference process.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSet> InferSchema(const SharedPtr<XmlReader>& instanceDocument, SharedPtr<XmlSchemaSet> schemas);

protected:

    /// @cond
    static SharedPtr<XmlQualifiedName>& ST_boolean();
    static SharedPtr<XmlQualifiedName>& ST_byte();
    static SharedPtr<XmlQualifiedName>& ST_unsignedByte();
    static SharedPtr<XmlQualifiedName>& ST_short();
    static SharedPtr<XmlQualifiedName>& ST_unsignedShort();
    static SharedPtr<XmlQualifiedName>& ST_int();
    static SharedPtr<XmlQualifiedName>& ST_unsignedInt();
    static SharedPtr<XmlQualifiedName>& ST_long();
    static SharedPtr<XmlQualifiedName>& ST_unsignedLong();
    static SharedPtr<XmlQualifiedName>& ST_integer();
    static SharedPtr<XmlQualifiedName>& ST_decimal();
    static SharedPtr<XmlQualifiedName>& ST_float();
    static SharedPtr<XmlQualifiedName>& ST_double();
    static SharedPtr<XmlQualifiedName>& ST_duration();
    static SharedPtr<XmlQualifiedName>& ST_dateTime();
    static SharedPtr<XmlQualifiedName>& ST_time();
    static SharedPtr<XmlQualifiedName>& ST_date();
    static SharedPtr<XmlQualifiedName>& ST_gYearMonth();
    static SharedPtr<XmlQualifiedName>& ST_string();
    static SharedPtr<XmlQualifiedName>& ST_anySimpleType();
    static ArrayPtr<SharedPtr<XmlQualifiedName>>& SimpleTypes();

    static const int16_t HC_ST_boolean;
    static const int16_t HC_ST_byte;
    static const int16_t HC_ST_unsignedByte;
    static const int16_t HC_ST_short;
    static const int16_t HC_ST_unsignedShort;
    static const int16_t HC_ST_int;
    static const int16_t HC_ST_unsignedInt;
    static const int16_t HC_ST_long;
    static const int16_t HC_ST_unsignedLong;
    static const int16_t HC_ST_integer;
    static const int16_t HC_ST_decimal;
    static const int16_t HC_ST_float;
    static const int16_t HC_ST_double;
    static const int16_t HC_ST_duration;
    static const int16_t HC_ST_dateTime;
    static const int16_t HC_ST_time;
    static const int16_t HC_ST_date;
    static const int16_t HC_ST_gYearMonth;
    static const int16_t HC_ST_string;
    static const int16_t HC_ST_Count;
    static const int32_t TF_boolean;
    static const int32_t TF_byte;
    static const int32_t TF_unsignedByte;
    static const int32_t TF_short;
    static const int32_t TF_unsignedShort;
    static const int32_t TF_int;
    static const int32_t TF_unsignedInt;
    static const int32_t TF_long;
    static const int32_t TF_unsignedLong;
    static const int32_t TF_integer;
    static const int32_t TF_decimal;
    static const int32_t TF_float;
    static const int32_t TF_double;
    static const int32_t TF_duration;
    static const int32_t TF_dateTime;
    static const int32_t TF_time;
    static const int32_t TF_date;
    static const int32_t TF_gYearMonth;
    static const int32_t TF_string;

    SharedPtr<XmlSchemaSet> InferSchema1(const SharedPtr<XmlReader>& instanceDocument, const SharedPtr<XmlSchemaSet>& schemas);
    void InferElement(SharedPtr<XmlSchemaElement> xse, bool bCreatingNewType, const SharedPtr<XmlSchema>& parentSchema);
    SharedPtr<XmlSchemaElement> FindMatchingElement(bool bCreatingNewType, const SharedPtr<XmlReader>& xtr, const SharedPtr<XmlSchemaComplexType>& ct, int32_t& lastUsedSeqItem, bool& bParticleChanged, SharedPtr<XmlSchema> parentSchema, bool setMaxoccurs);
    void ProcessAttributes(SharedPtr<XmlSchemaElement>& xse, const SharedPtr<XmlSchemaType>& effectiveSchemaType, bool bCreatingNewType, const SharedPtr<XmlSchema>& parentSchema);
    SharedPtr<XmlSchemaAttribute> FindAttribute(const SharedPtr<Collections::Generic::IEnumerable<SharedPtr<XmlSchemaObject>>>& attributes, const String& attrName);
    SharedPtr<XmlSchemaElement> FindGlobalElement(const String& namespaceURI, const String& localName, SharedPtr<XmlSchema>& parentSchema);
    SharedPtr<XmlSchemaElement> FindElement(const SharedPtr<XmlSchemaObjectCollection>& elements, const String& elementName);
    SharedPtr<XmlSchemaAttribute> FindAttributeRef(const SharedPtr<Collections::Generic::IEnumerable<SharedPtr<XmlSchemaObject>>>& attributes, const String& attributeName, const String& nsURI);
    SharedPtr<XmlSchemaElement> FindElementRef(const SharedPtr<XmlSchemaObjectCollection>& elements, const String& elementName, const String& nsURI);
    void MakeExistingAttributesOptional(const SharedPtr<XmlSchemaComplexType>& ct, const SharedPtr<XmlSchemaObjectCollection>& attributesInInstance);
    SharedPtr<XmlQualifiedName> RefineSimpleType(String s, int32_t& iTypeFlags);
    static int32_t InferSimpleType(const String& s, bool& bNeedsRangeCheck);
    static int32_t DateTime(const String& s, bool bDate, bool bTime);
    void SetMinMaxOccurs(const SharedPtr<XmlSchemaElement>& el, bool setMaxOccurs);

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
    const char* DBG_class_name() const override { return "XmlSchemaInference"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlSchema> _rootSchema;
    SharedPtr<XmlSchemaSet> _schemaSet;
    SharedPtr<XmlReader> _xtr;
    SharedPtr<NameTable> _nametable;
    String _targetNamespace;
    SharedPtr<XmlNamespaceManager> _namespaceManager;
    XmlSchemaInference::InferenceOption _occurrence;
    XmlSchemaInference::InferenceOption _typeInference;

    SharedPtr<XmlSchemaAttribute> AddAttribute(const String& localName, const String& prefix, const String& childURI, const String& attrValue, bool bCreatingNewType, const SharedPtr<XmlSchema>& parentSchema, const SharedPtr<XmlSchemaObjectCollection>& addLocation, const SharedPtr<XmlSchemaObjectTable>& compiledAttributes);
    SharedPtr<XmlSchema> CreateXmlSchema(const String& targetNS);
    SharedPtr<XmlSchemaElement> AddElement(const String& localName, const String& prefix, String childURI, SharedPtr<XmlSchema> parentSchema, const SharedPtr<XmlSchemaObjectCollection>& addLocation, int32_t positionWithinCollection);
    SharedPtr<XmlSchemaSimpleContentExtension> CheckSimpleContentExtension(const SharedPtr<XmlSchemaComplexType>& ct);
    SharedPtr<XmlSchemaType> GetEffectiveSchemaType(const SharedPtr<XmlSchemaElement>& elem, bool bCreatingNewType);
    void MoveAttributes(const SharedPtr<XmlSchemaSimpleContentExtension>& scExtension, const SharedPtr<XmlSchemaComplexType>& ct);
    void MoveAttributes(const SharedPtr<XmlSchemaComplexType>& ct, const SharedPtr<XmlSchemaSimpleContentExtension>& simpleContentExtension, bool bCreatingNewType);
    void SwitchUseToOptional(const SharedPtr<XmlSchemaObjectCollection>& attributes, const SharedPtr<XmlSchemaObjectCollection>& attributesInInstance);
    SharedPtr<XmlSchemaElement> CreateNewElementforChoice(const SharedPtr<XmlSchemaElement>& copyElement);
    static int32_t GetSchemaType(const SharedPtr<XmlQualifiedName>& qname);

};

} // namespace Schema
} // namespace Xml
} // namespace System

template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaInference::InferenceOption>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaInference::InferenceOption, const char_t*>, 2>& values();
};



