/// @file xml/schema/xml_schema_validator.h

#pragma once

#include <xml/xml_char_type.h>
#include <xml/schema/xml_schema_validation_flags.h>
#include <xml/schema/validation_event_handler.h>
#include <system/multicast_delegate.h>
#include <system/exceptions.h>
#include <system/enum_helpers.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace Text
{
class StringBuilder;
} // namespace Text
class Uri;
namespace Xml
{
class DocumentSchemaValidator;
class HWStack;
class IDtdInfo;
class IXmlLineInfo;
class IXmlNamespaceResolver;
namespace Schema
{
class BaseValidator;
class DtdValidator;
class IdRefNode;
class SchemaAttDef;
class SchemaDeclBase;
class SchemaElementDecl;
class SchemaInfo;
class ValidationState;
enum class ValidatorState;
class XdrValidator;
class XmlSchema;
class XmlSchemaAttribute;
enum class XmlSchemaContentProcessing;
enum class XmlSchemaContentType;
class XmlSchemaDatatype;
class XmlSchemaElement;
class Details_XmlSchemaException; using XmlSchemaException = System::ExceptionWrapper<Details_XmlSchemaException>;
class XmlSchemaInfo;
class XmlSchemaObject;
class XmlSchemaParticle;
class XmlSchemaSet;
class XmlSchemaSimpleType;
class Details_XmlSchemaValidationException; using XmlSchemaValidationException = System::ExceptionWrapper<Details_XmlSchemaValidationException>;
enum class XmlSeverityType;
class XsdValidator;
} // namespace Schema
class XmlNameTable;
class XmlQualifiedName;
class XmlResolver;
enum class XmlTokenizedType;
class XsdValidatingReader;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// A callback used by the XmlSchemaValidator class to pass attribute, text,and white space values as a run-time type
/// compatible with the XML Schema Definition Language (XSD) type of the attribute, text, or white space.
/// @returns An object containing the attribute, text, or white space value.
/// The object is a type that corresponds to the XSD type of the attribute, text, or white space value.
using XmlValueGetter = System::MulticastDelegate<SharedPtr<Object>()>;

/// Represents an XML Schema Definition Language (XSD) Schema validation engine.
/// The XmlSchemaValidator class cannot be inherited.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaValidator final : public System::Object
{
    typedef XmlSchemaValidator ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaValidator>;

private:
    /// @cond
    friend class System::Xml::XsdValidatingReader;
    friend class System::Xml::DocumentSchemaValidator;
    friend class BaseValidator;
    friend class DtdValidator;
    friend class XdrValidator;
    friend class XsdValidator;
    /// @endcond

public:

    /// The ValidationEventHandler that receives schema validation warnings and errors encountered during schema validation.
    System::Xml::Schema::ValidationEventHandler ValidationEventHandler;

    /// Sets the XmlResolver object used to resolve @c xs:import and
    /// @c xs:include elements as well as @c xsi:schemaLocation and @c xsi:noNamespaceSchemaLocation attributes.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);
    /// Returns the line number information for the XML node being validated.
    /// @returns An IXmlLineInfo object.
    ASPOSECPP_SHARED_API SharedPtr<IXmlLineInfo> get_LineInfoProvider();
    /// Sets the line number information for the XML node being validated.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_LineInfoProvider(const SharedPtr<IXmlLineInfo>& value);
    /// Returns the source URI for the XML node being validated.
    /// @returns A Uri object representing the source URI for the XML node being validated; the default is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<Uri> get_SourceUri();
    /// Sets the source URI for the XML node being validated.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SourceUri(const SharedPtr<Uri>& value);
    /// Returns the object sent as the sender object of a validation event.
    /// @returns An Object; the default is this XmlSchemaValidator object.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_ValidationEventSender();
    /// Sets the object sent as the sender object of a validation event.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ValidationEventSender(const SharedPtr<Object>& value);

    /// Initializes a new instance of the XmlSchemaValidator class.
    /// @param nameTable An XmlNameTable object containing element and attribute names as atomized strings.
    /// @param schemas An XmlSchemaSet object containing the XML Schema Definition Language (XSD) schemas used for validation.
    /// @param namespaceResolver An IXmlNamespaceResolver object used for resolving namespaces encountered during validation.
    /// @param validationFlags An XmlSchemaValidationFlags value specifying schema validation options.
    /// @throws ArgumentNullException One or more of the parameters specified are @c nullptr.
    /// @throws XmlSchemaException An error occurred while compiling schemas in the XmlSchemaSet parameter.
    ASPOSECPP_SHARED_API XmlSchemaValidator(const SharedPtr<XmlNameTable>& nameTable, const SharedPtr<XmlSchemaSet>& schemas, const SharedPtr<IXmlNamespaceResolver>& namespaceResolver, XmlSchemaValidationFlags validationFlags);

    /// Adds an XML Schema Definition Language (XSD) schema to the set of schemas used for validation.
    /// @param schema An XmlSchema object to add to the set of schemas used for validation.
    /// @throws ArgumentNullException The XmlSchema parameter specified is @c nullptr.
    /// @throws XmlSchemaValidationException The target namespace of the XmlSchema parameter matches that of
    /// any element or attribute already encountered by the XmlSchemaValidator object.
    /// @throws XmlSchemaException The XmlSchema parameter is invalid.
    ASPOSECPP_SHARED_API void AddSchema(const SharedPtr<XmlSchema>& schema);
    /// Initializes the state of the XmlSchemaValidator object.
    /// @throws InvalidOperationException Calling the XmlSchemaValidator::Initialize method is valid immediately after
    /// the construction of an XmlSchemaValidator object or after a call to XmlSchemaValidator::EndValidation only.
    ASPOSECPP_SHARED_API void Initialize();
    /// Initializes the state of the XmlSchemaValidator object using the XmlSchemaObject specified for partial validation.
    /// @param partialValidationType An XmlSchemaElement, XmlSchemaAttribute, or XmlSchemaType object used to
    /// initialize the validation context of the XmlSchemaValidator object for partial validation.
    /// @throws InvalidOperationException Calling the XmlSchemaValidator::Initialize method is valid immediately after
    /// the construction of an XmlSchemaValidator object or after a call to XmlSchemaValidator::EndValidation only.
    /// @throws ArgumentException The XmlSchemaObject parameter is not an XmlSchemaElement,
    /// XmlSchemaAttribute, or XmlSchemaType object.
    /// @throws ArgumentNullException The XmlSchemaObject parameter cannot be @c nullptr.
    ASPOSECPP_SHARED_API void Initialize(const SharedPtr<XmlSchemaObject>& partialValidationType);
    /// Validates the element in the current context.
    /// @param localName The local name of the element to validate.
    /// @param namespaceUri The namespace URI of the element to validate.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful validation of the element's name.
    /// This parameter can be @c nullptr.
    /// @throws XmlSchemaValidationException The element's name is not valid in the current context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateElement method was not called in the correct sequence.
    /// For example, the XmlSchemaValidator::ValidateElement method is called after calling XmlSchemaValidator::ValidateAttribute.
    ASPOSECPP_SHARED_API void ValidateElement(const String& localName, const String& namespaceUri, const SharedPtr<XmlSchemaInfo>& schemaInfo);
    /// Validates the element in the current context with the @c xsi:Type, @c xsi:Nil, @c xsi:SchemaLocation,
    /// and @c xsi:NoNamespaceSchemaLocation attribute values specified.
    /// @param localName The local name of the element to validate.
    /// @param namespaceUri The namespace URI of the element to validate.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful validation of the element's name.
    /// This parameter can be @c nullptr.
    /// @param xsiType The @c xsi:Type attribute value of the element. This parameter can be @c nullptr.
    /// @param xsiNil The @c xsi:Nil attribute value of the element. This parameter can be @c nullptr.
    /// @param xsiSchemaLocation The @c xsi:SchemaLocation attribute value of the element. This parameter can be @c nullptr.
    /// @param xsiNoNamespaceSchemaLocation The @c xsi:NoNamespaceSchemaLocation attribute value of the element.
    /// This parameter can be @c nullptr.
    /// @throws XmlSchemaValidationException The element's name is not valid in the current context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateElement method was not called in the correct sequence.
    /// For example, the XmlSchemaValidator::ValidateElement method is called after calling XmlSchemaValidator::ValidateAttribute.
    ASPOSECPP_SHARED_API void ValidateElement(const String& localName, const String& namespaceUri, const SharedPtr<XmlSchemaInfo>& schemaInfo, const String& xsiType, const String& xsiNil, const String& xsiSchemaLocation, const String& xsiNoNamespaceSchemaLocation);
    /// Validates the attribute name, namespace URI, and value in the current element context.
    /// @param localName The local name of the attribute to validate.
    /// @param namespaceUri The namespace URI of the attribute to validate.
    /// @param attributeValue The value of the attribute to validate.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful validation of the attribute.
    /// This parameter can be @c nullptr.
    /// @returns The validated attribute's value.
    /// @throws XmlSchemaValidationException The attribute is not valid in the current element context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateAttribute method was not called in the correct sequence.
    /// For example, calling XmlSchemaValidator::ValidateAttribute after calling XmlSchemaValidator::ValidateEndOfAttributes.
    /// @throws ArgumentNullException One or more of the parameters specified are @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<Object> ValidateAttribute(const String& localName, const String& namespaceUri, const String& attributeValue, const SharedPtr<XmlSchemaInfo>& schemaInfo);
    /// Validates the attribute name, namespace URI, and value in the current element context.
    /// @param localName The local name of the attribute to validate.
    /// @param namespaceUri The namespace URI of the attribute to validate.
    /// @param attributeValue An XmlValueGetter callback used to pass the attribute's value as a type compatible with
    /// the XML Schema Definition Language (XSD) type of the attribute.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful validation of the attribute.
    /// This parameter and can be @c nullptr.
    /// @returns The validated attribute's value.
    /// @throws XmlSchemaValidationException The attribute is not valid in the current element context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateAttribute method was not called in the correct sequence.
    /// For example, calling XmlSchemaValidator::ValidateAttribute after calling XmlSchemaValidator::ValidateEndOfAttributes.
    /// @throws ArgumentNullException One or more of the parameters specified are @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<Object> ValidateAttribute(const String& localName, const String& namespaceUri, XmlValueGetter attributeValue, const SharedPtr<XmlSchemaInfo>& schemaInfo);
    /// Validates identity constraints on the default attributes and populates the List specified with
    /// XmlSchemaAttribute objects for any attributes with default values that have not been previously
    /// validated using the XmlSchemaValidator::ValidateAttribute method in the element context.
    /// @param defaultAttributes A List to populate with XmlSchemaAttribute objects for
    /// any attributes not yet encountered during validation in the element context.
    ASPOSECPP_SHARED_API void GetUnspecifiedDefaultAttributes(const SharedPtr<Collections::Generic::List<SharedPtr<Object>>>& defaultAttributes);
    /// Verifies whether all the required attributes in the element context are present and prepares
    /// the XmlSchemaValidator object to validate the child content of the element.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful verification that all
    /// the required attributes in the element context are present.
    /// This parameter can be @c nullptr.
    /// @throws XmlSchemaValidationException One or more of the required attributes in the current element context were not found.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateEndOfAttributes method was not called in the correct sequence.
    /// For example, calling XmlSchemaValidator::ValidateEndOfAttributes after calling XmlSchemaValidator::SkipToEndElement.
    /// @throws ArgumentNullException One or more of the parameters specified are @c nullptr.
    ASPOSECPP_SHARED_API void ValidateEndOfAttributes(const SharedPtr<XmlSchemaInfo>& schemaInfo);
    /// Validates whether the text @c string specified is allowed in the current element context,
    /// and accumulates the text for validation if the current element has simple content.
    /// @param elementValue A text @c string to validate in the current element context.
    /// @throws XmlSchemaValidationException The text @c string specified is not allowed in the current element context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateText method was not called in the correct sequence.
    /// For example, the XmlSchemaValidator::ValidateText method is called after calling XmlSchemaValidator::ValidateAttribute.
    /// @throws ArgumentNullException The text @c string parameter cannot be @c nullptr.
    ASPOSECPP_SHARED_API void ValidateText(const String& elementValue);
    /// Validates whether the text returned by the XmlValueGetter object specified is allowed in the current element context,
    /// and accumulates the text for validation if the current element has simple content.
    /// @param elementValue An XmlValueGetter callback used to pass the text value as a type compatible with
    /// the XML Schema Definition Language (XSD) type of the attribute.
    /// @throws XmlSchemaValidationException The text @c string specified is not allowed in the current element context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateText method was not called in the correct sequence.
    /// For example, the XmlSchemaValidator::ValidateText method is called after calling XmlSchemaValidator::ValidateAttribute.
    /// @throws ArgumentNullException The text @c string parameter cannot be @c nullptr.
    ASPOSECPP_SHARED_API void ValidateText(XmlValueGetter elementValue);
    /// Validates whether the white space in the @c string specified is allowed in the current element context,
    /// and accumulates the white space for validation if the current element has simple content.
    /// @param elementValue A white space @c string to validate in the current element context.
    /// @throws XmlSchemaValidationException White space is not allowed in the current element context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateWhitespace method was not called in the correct sequence.
    /// For example, if the XmlSchemaValidator::ValidateWhitespace method is called after calling XmlSchemaValidator::ValidateAttribute.
    ASPOSECPP_SHARED_API void ValidateWhitespace(const String& elementValue);
    /// Validates whether the white space returned by the XmlValueGetter object specified is allowed in the current element context,
    /// and accumulates the white space for validation if the current element has simple content.
    /// @param elementValue An XmlValueGetter callback used to pass the white space value as a type compatible with
    /// the XML Schema Definition Language (XSD) type of the attribute.
    /// @throws XmlSchemaValidationException White space is not allowed in the current element context.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateWhitespace method was not called in the correct sequence.
    /// For example, if the XmlSchemaValidator::ValidateWhitespace method is called after calling XmlSchemaValidator::ValidateAttribute.
    ASPOSECPP_SHARED_API void ValidateWhitespace(XmlValueGetter elementValue);
    /// Verifies if the text content of the element is valid according to its data type for elements with simple content,
    /// and verifies if the content of the current element is complete for elements with complex content.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful validation of the element.
    /// This parameter can be @c nullptr.
    /// @returns The parsed, typed text value of the element if the element has simple content.
    /// @throws XmlSchemaValidationException The element's content is not valid.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateEndElement method was not called in the correct sequence.
    /// For example, if the XmlSchemaValidator::ValidateEndElement method is called after calling XmlSchemaValidator::SkipToEndElement.
    ASPOSECPP_SHARED_API SharedPtr<Object> ValidateEndElement(const SharedPtr<XmlSchemaInfo>& schemaInfo);
    /// Verifies if the text content of the element specified is valid according to its data type.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set on successful validation of the text content of the element.
    /// This parameter can be @c nullptr.
    /// @param typedValue The typed text content of the element.
    /// @returns The parsed, typed simple content of the element.
    /// @throws XmlSchemaValidationException The element's text content is not valid.
    /// @throws InvalidOperationException The XmlSchemaValidator::ValidateEndElement method was not called in the correct sequence
    /// (for example, if the XmlSchemaValidator::ValidateEndElement method is called after calling XmlSchemaValidator::SkipToEndElement),
    /// calls to the XmlSchemaValidator::ValidateText method have been previously made, or the element has complex content.
    /// @throws ArgumentNullException The typed text content parameter cannot be @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<Object> ValidateEndElement(const SharedPtr<XmlSchemaInfo>& schemaInfo, const SharedPtr<Object>& typedValue);
    /// Skips validation of the current element content and prepares
    /// the XmlSchemaValidator object to validate content in the parent element's context.
    /// @param schemaInfo An XmlSchemaInfo object whose properties are set if
    /// the current element content is successfully skipped.
    /// This parameter can be @c nullptr.
    /// @throws InvalidOperationException The method was not called in the correct sequence.
    /// For example, calling XmlSchemaValidator::SkipToEndElement after calling XmlSchemaValidator::SkipToEndElement.
    ASPOSECPP_SHARED_API void SkipToEndElement(const SharedPtr<XmlSchemaInfo>& schemaInfo);
    /// Ends validation and checks identity constraints for the entire XML document.
    /// @throws XmlSchemaValidationException An identity constraint error was found in the XML document.
    ASPOSECPP_SHARED_API void EndValidation();
    /// Returns the expected particles in the current element context.
    /// @returns An array of XmlSchemaParticle objects or an empty array if there are no expected particles.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlSchemaParticle>> GetExpectedParticles();
    /// Returns the expected attributes for the current element context.
    /// @returns An array of XmlSchemaAttribute objects or an empty array if there are no expected attributes.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlSchemaAttribute>> GetExpectedAttributes();

protected:

    /// @cond
    static ArrayPtr<std::vector<bool>> ValidStates;

    SharedPtr<XmlSchemaSet> get_SchemaSet();
    XmlSchemaValidationFlags get_ValidationFlags();
    XmlSchemaContentType get_CurrentContentType();
    XmlSchemaContentProcessing get_CurrentProcessContents();
    bool get_ProcessIdentityConstraints();
    bool get_ReportValidationWarnings();
    bool get_ProcessSchemaHints();

    void GetUnspecifiedDefaultAttributes(const SharedPtr<Collections::Generic::List<SharedPtr<Object>>>& defaultAttributes, bool createNodeData);
    void SetDtdSchemaInfo(const SharedPtr<IDtdInfo>& dtdSchemaInfo);
    String GetConcatenatedValue();
    SharedPtr<Object> CheckMixedValueConstraint(const String& elementValue);
    void RecompileSchemaSet();
    String GetDefaultAttributePrefix(const String& attributeNS);
    static void ElementValidationError(const SharedPtr<XmlQualifiedName>& name, const SharedPtr<ValidationState>& context, System::Xml::Schema::ValidationEventHandler eventHandler, const SharedPtr<Object>& sender, const String& sourceUri, int32_t lineNo, int32_t linePos, const SharedPtr<XmlSchemaSet>& schemaSet);
    static void CompleteValidationError(const SharedPtr<ValidationState>& context, System::Xml::Schema::ValidationEventHandler eventHandler, const SharedPtr<Object>& sender, const String& sourceUri, int32_t lineNo, int32_t linePos, const SharedPtr<XmlSchemaSet>& schemaSet);
    static String PrintExpectedElements(const SharedPtr<Collections::Generic::List<SharedPtr<XmlSchemaParticle>>>& expected);
    static String PrintExpectedElements(const SharedPtr<Collections::Generic::List<String>>& expected);
    static String QNameString(const String& localName, const String& ns);
    static String BuildElementName(const SharedPtr<XmlQualifiedName>& qname);
    static String BuildElementName(const String& localName, const String& ns);
    static void SendValidationEvent(System::Xml::Schema::ValidationEventHandler eventHandler, const SharedPtr<Object>& sender, XmlSchemaValidationException e, XmlSeverityType severity);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaValidator();

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
    const char* DBG_class_name() const override { return "XmlSchemaValidator"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaSet> _schemaSet;
    XmlSchemaValidationFlags _validationFlags;
    int32_t _startIDConstraint;
    static const int32_t STACK_INCREMENT;
    bool _isRoot;
    bool _rootHasSchema;
    bool _attrValid;
    bool _checkEntity;
    SharedPtr<SchemaInfo> _compiledSchemaInfo;
    SharedPtr<IDtdInfo> _dtdSchemaInfo;
    SharedPtr<Collections::Generic::Dictionary<String, String>> _validatedNamespaces;
    SharedPtr<HWStack> _validationStack;
    SharedPtr<ValidationState> _context;
    ValidatorState _currentState;
    SharedPtr<Collections::Generic::Dictionary<SharedPtr<XmlQualifiedName>, SharedPtr<SchemaAttDef>>> _attPresence;
    SharedPtr<SchemaAttDef> _wildID;
    SharedPtr<Collections::Generic::Dictionary<String, String>> _IDs;
    SharedPtr<IdRefNode> _idRefListHead;
    SharedPtr<XmlQualifiedName> _contextQName;
    String _nsXs;
    String _nsXsi;
    String _nsXmlNs;
    String _nsXml;
    SharedPtr<XmlSchemaObject> _partialValidationType;
    SharedPtr<Text::StringBuilder> _textValue;
    WeakPtr<Object> _validationEventSender;
    SharedPtr<XmlNameTable> _nameTable;
    SharedPtr<IXmlLineInfo> _positionInfo;
    SharedPtr<IXmlLineInfo> _dummyPositionInfo;
    SharedPtr<System::Xml::XmlResolver> _xmlResolver;
    SharedPtr<Uri> _sourceUri;
    String _sourceUriString;
    WeakPtr<IXmlNamespaceResolver> _nsResolver;
    XmlSchemaContentProcessing _processContents;
    static SharedPtr<XmlSchemaAttribute> s_xsiTypeSO;
    static SharedPtr<XmlSchemaAttribute> s_xsiNilSO;
    static SharedPtr<XmlSchemaAttribute> s_xsiSLSO;
    static SharedPtr<XmlSchemaAttribute> s_xsiNoNsSLSO;
    String _xsiTypeString;
    String _xsiNilString;
    String _xsiSchemaLocationString;
    String _xsiNoNamespaceSchemaLocationString;
    static SharedPtr<XmlSchemaDatatype> s_dtQName;
    static SharedPtr<XmlSchemaDatatype> s_dtCDATA;
    static SharedPtr<XmlSchemaDatatype> s_dtStringArray;
    static const String Quote;
    static ArrayPtr<SharedPtr<XmlSchemaParticle>> s_emptyParticleArray;
    static ArrayPtr<SharedPtr<XmlSchemaAttribute>> s_emptyAttributeArray;
    XmlCharType _xmlCharType;
    static ArrayPtr<String> s_methodNames;

    bool get_StrictlyAssessed();
    bool get_HasSchema();
    bool get_HasIdentityConstraints();
    System::Xml::Schema::ValidationEventHandler get_EventHandler();

    void Init();
    void Reset();
    SharedPtr<Object> ValidateAttribute(String localName, String namespaceUri, XmlValueGetter attributeValueGetter, const String& attributeStringValue, const SharedPtr<XmlSchemaInfo>& schemaInfo);
    void ValidateText(const String& elementStringValue, XmlValueGetter elementValueGetter);
    void ValidateWhitespace(const String& elementStringValue, XmlValueGetter elementValueGetter);
    SharedPtr<Object> InternalValidateEndElement(const SharedPtr<XmlSchemaInfo>& schemaInfo, SharedPtr<Object> typedValue);
    void ProcessSchemaLocations(const String& xsiSchemaLocation, const String& xsiNoNamespaceSchemaLocation);
    SharedPtr<Object> ValidateElementContext(const SharedPtr<XmlQualifiedName>& elementName, bool& invalidElementInContext);
    SharedPtr<XmlSchemaElement> GetSubstitutionGroupHead(const SharedPtr<XmlQualifiedName>& member);
    SharedPtr<Object> ValidateAtomicValue(const String& stringValue, SharedPtr<XmlSchemaSimpleType>& memberType);
    SharedPtr<Object> ValidateAtomicValue(const SharedPtr<Object>& parsedValue, SharedPtr<XmlSchemaSimpleType>& memberType);
    String GetTypeName(const SharedPtr<SchemaDeclBase>& decl);
    void SaveTextValue(const SharedPtr<Object>& value);
    void Push(const SharedPtr<XmlQualifiedName>& elementName);
    void Pop();
    void AddXsiAttributes(const SharedPtr<Collections::Generic::List<SharedPtr<XmlSchemaAttribute>>>& attList);
    SharedPtr<SchemaElementDecl> FastGetElementDecl(const SharedPtr<XmlQualifiedName>& elementName, const SharedPtr<Object>& particle);
    SharedPtr<SchemaElementDecl> CheckXsiTypeAndNil(SharedPtr<SchemaElementDecl> elementDecl, const String& xsiType, const String& xsiNil, bool& declFound);
    void ThrowDeclNotFoundWarningOrError(bool declFound);
    void CheckElementProperties();
    void ValidateStartElementIdentityConstraints();
    SharedPtr<SchemaAttDef> CheckIsXmlAttribute(const SharedPtr<XmlQualifiedName>& attQName);
    void AddXmlNamespaceSchema();
    void LoadSchema(const String& uri, const String& url);
    void ProcessTokenizedType(XmlTokenizedType ttype, const String& name, bool attrValue);
    SharedPtr<Object> CheckAttributeValue(const SharedPtr<Object>& value, const SharedPtr<SchemaAttDef>& attdef);
    SharedPtr<Object> CheckElementValue(const String& stringValue);
    void CheckTokenizedTypes(const SharedPtr<XmlSchemaDatatype>& dtype, const SharedPtr<Object>& typedValue, bool attrValue);
    SharedPtr<Object> FindId(const String& name);
    void CheckForwardRefs();
    void CheckStateTransition(ValidatorState toState, const String& methodName);
    void ClearPSVI();
    void CheckRequiredAttributes(const SharedPtr<SchemaElementDecl>& currentElementDecl);
    SharedPtr<XmlSchemaElement> GetSchemaElement();
    void AddIdentityConstraints();
    void ElementIdentityConstraints();
    void AttributeIdentityConstraints(const String& name, const String& ns, const SharedPtr<Object>& obj, const String& sobj, const SharedPtr<XmlSchemaDatatype>& datatype);
    void EndElementIdentityConstraints(const SharedPtr<Object>& typedValue, const String& stringValue, const SharedPtr<XmlSchemaDatatype>& datatype);
    static void BuildXsiAttributes();
    static void PrintNamesWithNS(const SharedPtr<Collections::Generic::List<SharedPtr<XmlQualifiedName>>>& expected, const SharedPtr<Text::StringBuilder>& builder);
    static void EnumerateAny(const SharedPtr<Text::StringBuilder>& builder, const String& namespaces);
    void ProcessEntity(const String& name);
    void SendValidationEvent(const String& code);
    void SendValidationEvent(const String& code, const ArrayPtr<String>& args);
    void SendValidationEvent(const String& code, const String& arg);
    void SendValidationEvent(const String& code, const String& arg1, const String& arg2);
    void SendValidationEvent(const String& code, const ArrayPtr<String>& args, Exception innerException, XmlSeverityType severity);
    void SendValidationEvent(const String& code, const ArrayPtr<String>& args, Exception innerException);
    void SendValidationEvent(XmlSchemaValidationException e);
    void SendValidationEvent(XmlSchemaException e);
    void SendValidationEvent(const String& code, const String& msg, XmlSeverityType severity);
    void SendValidationEvent(XmlSchemaValidationException e, XmlSeverityType severity);

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

};

} // namespace Schema
} // namespace Xml
} // namespace System


