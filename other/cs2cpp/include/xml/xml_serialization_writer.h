/// @file xml/xml_serialization_writer.h
#pragma once
#include <xml/xml_writer.h>
#include <xml/xml_node.h>
#include <xml/i_xml_serializable.h>
#include <xml/xml_qualified_name.h>
#include <xml/serialization/xml_serializer_namespaces.h>
#include <system/type_info.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/reflection/assembly.h>
#include <system/object.h>
#include <system/exceptions.h>
#include <system/date_time.h>
#include <system/array.h>
#include <system/collections/hashset.h>
#include <system/collections/queue.h>
#include <cstdint>

namespace System {

namespace Xml {

namespace Serialization {

/// Service class improving XmlWriter experience.
class ASPOSECPP_SHARED_CLASS ABSTRACT XmlSerializationWriter : public System::Object
{
    using BaseType = System::Object;

public:
    /// Initializes XmlSerializationReader class.
    /// @param writer Writer to use.
    /// @param nss Namespace storage.
    ASPOSECPP_SHARED_API void Initialize(System::SharedPtr<XmlWriter> writer, System::SharedPtr<XmlSerializerNamespaces> nss);
    
protected:

    ASPOSECPP_SHARED_API System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Xml::XmlQualifiedName>>> get_Namespaces();
    ASPOSECPP_SHARED_API void set_Namespaces(System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Xml::XmlQualifiedName>>> value);
    ASPOSECPP_SHARED_API System::SharedPtr<XmlWriter> get_Writer();
    ASPOSECPP_SHARED_API void set_Writer(System::SharedPtr<XmlWriter> value);
    ASPOSECPP_SHARED_API bool get_EscapeName();
    ASPOSECPP_SHARED_API void set_EscapeName(bool value);
    
    ASPOSECPP_SHARED_API XmlSerializationWriter();
    
    ASPOSECPP_SHARED_API Exception CreateChoiceIdentifierValueException(String value, String identifier, String name, String ns);
    ASPOSECPP_SHARED_API Exception CreateInvalidChoiceIdentifierValueException(String type, String identifier);
    ASPOSECPP_SHARED_API Exception CreateMismatchChoiceException(String value, String elementName, String enumValue);
    ASPOSECPP_SHARED_API Exception CreateUnknownAnyElementException(String name, String ns);
    ASPOSECPP_SHARED_API Exception CreateUnknownTypeException(System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API Exception CreateUnknownTypeException(const TypeInfo& type);
    ASPOSECPP_SHARED_API static System::ArrayPtr<uint8_t> FromByteArrayBase64(System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API static String FromByteArrayHex(System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API static String FromChar(char16_t value);
    ASPOSECPP_SHARED_API static String FromDate(DateTime value);
    ASPOSECPP_SHARED_API static String FromDateTime(DateTime value);
    ASPOSECPP_SHARED_API static String FromEnum(int64_t value, System::ArrayPtr<String> values, System::ArrayPtr<int64_t> ids);
    ASPOSECPP_SHARED_API static String FromTime(DateTime value);
    ASPOSECPP_SHARED_API static String FromXmlName(String name);
    ASPOSECPP_SHARED_API static String FromXmlNCName(String ncName);
    ASPOSECPP_SHARED_API static String FromXmlNmToken(String nmToken);
    ASPOSECPP_SHARED_API static String FromXmlNmTokens(String nmTokens);
    ASPOSECPP_SHARED_API String FromXmlQualifiedName(System::SharedPtr<XmlQualifiedName> xmlQualifiedName);
    ASPOSECPP_SHARED_API virtual void InitCallbacks() = 0;
    ASPOSECPP_SHARED_API void TopLevelElement();
    ASPOSECPP_SHARED_API void WriteAttribute(String localName, System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API void WriteAttribute(String localName, String value);
    ASPOSECPP_SHARED_API void WriteAttribute(String localName, String ns, System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API void WriteAttribute(String localName, String ns, String value);
    ASPOSECPP_SHARED_API void WriteAttribute(String prefix, String localName, String ns, String value);
    ASPOSECPP_SHARED_API void WriteElementEncoded(System::SharedPtr<XmlNode> node, String name, String ns, bool isNullable, bool any);
    ASPOSECPP_SHARED_API void WriteElementLiteral(System::SharedPtr<XmlNode> node, String name, String ns, bool isNullable, bool any);
    ASPOSECPP_SHARED_API void WriteElementQualifiedName(String localName, System::SharedPtr<XmlQualifiedName> value);
    ASPOSECPP_SHARED_API void WriteElementQualifiedName(String localName, String ns, System::SharedPtr<XmlQualifiedName> value);
    ASPOSECPP_SHARED_API void WriteElementQualifiedName(String localName, System::SharedPtr<XmlQualifiedName> value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementQualifiedName(String localName, String ns, System::SharedPtr<XmlQualifiedName> value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementString(String localName, String value);
    ASPOSECPP_SHARED_API void WriteElementString(String localName, String ns, String value);
    ASPOSECPP_SHARED_API void WriteElementString(String localName, String value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementString(String localName, String ns, String value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, String value);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, System::ArrayPtr<uint8_t> value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, String ns, System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, String ns, String value);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, String value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, String ns, System::ArrayPtr<uint8_t> value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteElementStringRaw(String localName, String ns, String value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteEmptyTag(String name);
    ASPOSECPP_SHARED_API void WriteEmptyTag(String name, String ns);
    ASPOSECPP_SHARED_API void WriteEndElement();
    ASPOSECPP_SHARED_API void WriteEndElement(System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API void WriteId(System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API void WriteNamespaceDeclarations(System::SharedPtr<XmlSerializerNamespaces> xmlns);
    ASPOSECPP_SHARED_API void WriteNullableQualifiedNameEncoded(String name, String ns, System::SharedPtr<XmlQualifiedName> value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteNullableQualifiedNameLiteral(String name, String ns, System::SharedPtr<XmlQualifiedName> value);
    ASPOSECPP_SHARED_API void WriteNullableStringEncoded(String name, String ns, String value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteNullableStringEncodedRaw(String name, String ns, System::ArrayPtr<uint8_t> value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteNullableStringEncodedRaw(String name, String ns, String value, System::SharedPtr<XmlQualifiedName> xsiType);
    ASPOSECPP_SHARED_API void WriteNullableStringLiteral(String name, String ns, String value);
    ASPOSECPP_SHARED_API void WriteNullableStringLiteralRaw(String name, String ns, System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API void WriteNullableStringLiteralRaw(String name, String ns, String value);
    ASPOSECPP_SHARED_API void WriteNullTagEncoded(String name);
    ASPOSECPP_SHARED_API void WriteNullTagEncoded(String name, String ns);
    ASPOSECPP_SHARED_API void WriteNullTagLiteral(String name);
    ASPOSECPP_SHARED_API void WriteNullTagLiteral(String name, String ns);
    ASPOSECPP_SHARED_API void WritePotentiallyReferencingElement(String n, String ns, System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API void WritePotentiallyReferencingElement(String n, String ns, System::SharedPtr<Object> o, const TypeInfo& ambientType);
    ASPOSECPP_SHARED_API void WritePotentiallyReferencingElement(String n, String ns, System::SharedPtr<Object> o, const TypeInfo& ambientType, bool suppressReference);
    ASPOSECPP_SHARED_API void WritePotentiallyReferencingElement(String n, String ns, System::SharedPtr<Object> o, const TypeInfo& ambientType, bool suppressReference, bool isNullable);
    ASPOSECPP_SHARED_API void WriteReferencedElements();
    ASPOSECPP_SHARED_API void WriteReferencingElement(String n, String ns, System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API void WriteReferencingElement(String n, String ns, System::SharedPtr<Object> o, bool isNullable);
    ASPOSECPP_SHARED_API void WriteRpcResult(String name, String ns);
    ASPOSECPP_SHARED_API void WriteSerializable(System::SharedPtr<IXmlSerializable> serializable, String name, String ns, bool isNullable);
    ASPOSECPP_SHARED_API void WriteSerializable(System::SharedPtr<IXmlSerializable> serializable, String name, String ns, bool isNullable, bool wrapped);
    ASPOSECPP_SHARED_API void WriteStartDocument();
    ASPOSECPP_SHARED_API void WriteStartElement(String name);
    ASPOSECPP_SHARED_API void WriteStartElement(String name, String ns);
    ASPOSECPP_SHARED_API void WriteStartElement(String name, String ns, bool writePrefixed);
    ASPOSECPP_SHARED_API void WriteStartElement(String name, String ns, System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API void WriteStartElement(String name, String ns, System::SharedPtr<Object> o, bool writePrefixed);
    ASPOSECPP_SHARED_API void WriteStartElement(String name, String ns, System::SharedPtr<Object> o, bool writePrefixed, System::SharedPtr<XmlSerializerNamespaces> xmlns);
    ASPOSECPP_SHARED_API void WriteTypedPrimitive(String name, String ns, System::SharedPtr<Object> o, bool xsiType);
    ASPOSECPP_SHARED_API void WriteValue(System::ArrayPtr<uint8_t> value);
    ASPOSECPP_SHARED_API void WriteValue(String value);
    ASPOSECPP_SHARED_API void WriteXmlAttribute(System::SharedPtr<XmlNode> node);
    ASPOSECPP_SHARED_API void WriteXmlAttribute(System::SharedPtr<XmlNode> node, System::SharedPtr<Object> container);
    ASPOSECPP_SHARED_API void WriteXsiType(String name, String ns);
    ASPOSECPP_SHARED_API Exception CreateInvalidAnyTypeException(System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API Exception CreateInvalidAnyTypeException(const TypeInfo& type);
    ASPOSECPP_SHARED_API Exception CreateInvalidEnumValueException(System::SharedPtr<Object> value, String typeName);
    ASPOSECPP_SHARED_API static String FromEnum(int64_t value, System::ArrayPtr<String> values, System::ArrayPtr<int64_t> ids, String typeName);
    ASPOSECPP_SHARED_API String FromXmlQualifiedName(System::SharedPtr<XmlQualifiedName> xmlQualifiedName, bool ignoreEmpty);
    ASPOSECPP_SHARED_API static System::SharedPtr<Reflection::Assembly> ResolveDynamicAssembly(String assemblyFullName);

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Pointer leakage lookup.
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlSerializationWriter"; }
#endif

private:
    int32_t qnameCount;
    bool topLevelElement;
    System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Xml::XmlQualifiedName>>> m_namespaces;
    System::SharedPtr<XmlWriter> m_writer;
    System::SharedPtr<Collections::Generic::Queue<System::SharedPtr<System::Object>>> m_referenced_elements;
    System::SharedPtr<Collections::Generic::Dictionary<System::SharedPtr<System::Object>, System::SharedPtr<System::Object>>> m_serialized_objects;
    static const String xmlNamespace;
    static const String unexpectedTypeError;
    
    String GetId(System::SharedPtr<Object> o, bool addToReferencesList);
    bool AlreadyQueued(System::SharedPtr<Object> ob);
    String GetNamespacePrefix(String ns);
    String GetQualifiedName(String name, String ns);
    void WriteXmlNode(System::SharedPtr<XmlNode> node);
    void CheckReferenceQueue();
    void WriteStartElementInternal(String name, String ns, System::SharedPtr<Object> o, bool writePrefixed,
        System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Xml::XmlQualifiedName>>> namespaces);
};

} // namespace Serialization
} // namespace Xml
} // namespace System

