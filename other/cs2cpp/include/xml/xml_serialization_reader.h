/// @file xml/xml_serialization_reader.h
#pragma once
#include <xml/xml_node.h>
#include <xml/xml_element.h>
#include <xml/xml_document.h>
#include <xml/xml_attribute.h>
#include <xml/i_xml_serializable.h>
#include <system/type_info.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/reflection/assembly.h>
#include <system/object.h>
#include <system/exceptions.h>
#include <system/date_time.h>
#include <system/array.h>
#include <cstdint>

#include "xml/xml_reader.h"
#include "xml/xml_qualified_name.h"
#include "xml/xml_serializer.h"

namespace System { namespace Xml { namespace Serialization {

class XmlSerializer;

/// Service class improving XmlReader experience.
class ASPOSECPP_SHARED_CLASS ABSTRACT XmlSerializationReader : public System::Object
{
    using BaseType = Object;

public:
    /// Initializes XmlSerializationReader class.
    /// @param reader Reader to use.
    /// @param eventSource Event source to use.
    ASPOSECPP_SHARED_API void Initialize(System::SharedPtr<XmlReader> reader,
                                         System::SharedPtr<XmlSerializer> eventSource);

protected:
    ASPOSECPP_SHARED_API System::SharedPtr<XmlDocument> get_Document();
    ASPOSECPP_SHARED_API System::SharedPtr<XmlReader> get_Reader();
    ASPOSECPP_SHARED_API bool get_IsReturnValue();
    ASPOSECPP_SHARED_API void set_IsReturnValue(bool value);
    ASPOSECPP_SHARED_API int32_t get_ReaderCount();
    ASPOSECPP_SHARED_API bool get_DecodeName();
    ASPOSECPP_SHARED_API void set_DecodeName(bool value);

    ASPOSECPP_SHARED_API XmlSerializationReader();

    ASPOSECPP_SHARED_API void AddTarget(String id, System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API Exception CreateCtorHasSecurityException(String typeName);
    ASPOSECPP_SHARED_API Exception CreateInaccessibleConstructorException(String typeName);
    ASPOSECPP_SHARED_API Exception CreateAbstractTypeException(String name, String ns);
    ASPOSECPP_SHARED_API Exception CreateInvalidCastException(const TypeInfo& type, System::SharedPtr<Object> value);
    ASPOSECPP_SHARED_API Exception CreateReadOnlyCollectionException(String name);
    ASPOSECPP_SHARED_API Exception CreateUnknownConstantException(String value, const TypeInfo& enumType);
    ASPOSECPP_SHARED_API Exception CreateUnknownNodeException();
    ASPOSECPP_SHARED_API Exception CreateUnknownTypeException(System::SharedPtr<XmlQualifiedName> type);
    ASPOSECPP_SHARED_API void CheckReaderCount(int32_t& whileIterations, int32_t& readerCount);

    template <typename T>
    System::ArrayPtr<T> EnsureArrayIndex(System::ArrayPtr<T> a, int index, System::TypeInfo elementType)
    {
        if (a != nullptr && index < a->get_Length())
        {
            return a;
        }

        int32_t size;
        if (a == nullptr)
        {
            size = 32;
        }
        else
        {
            size = a->get_Length() * 2;
        }

        System::ArrayPtr<T> result = System::MakeArray<T>(size);
        if (a != nullptr)
        {
            Array<T>::Copy(a, result, index);
        }

        return result;
    }

    template <typename T>
    System::ArrayPtr<T> ShrinkArray(System::ArrayPtr<T> a, int length, TypeInfo elementType, bool isNullable)
    {
        if (length == 0 && isNullable)
        {
            return nullptr;
        }
        if (a == nullptr)
        {
            // return Array::CreateInstance(elementType, length);
            return System::MakeArray<T>(length);
        }
        if (a->get_Length() == length)
        {
            return a;
        }

        System::ArrayPtr<T> result = System::MakeArray<T>(length);
        Array<T>::Copy(a, result, length);
        return result;
    }

    ASPOSECPP_SHARED_API void FixupArrayRefs(System::SharedPtr<Object> fixup);
    ASPOSECPP_SHARED_API int32_t GetArrayLength(String name, String ns);
    ASPOSECPP_SHARED_API bool GetNullAttr();
    ASPOSECPP_SHARED_API System::SharedPtr<Object> GetTarget(String id);
    ASPOSECPP_SHARED_API System::SharedPtr<XmlQualifiedName> GetXsiType();
    ASPOSECPP_SHARED_API virtual void InitCallbacks() = 0;
    ASPOSECPP_SHARED_API virtual void InitIDs() = 0;
    ASPOSECPP_SHARED_API bool IsXmlnsAttribute(String name);
    ASPOSECPP_SHARED_API void ParseWsdlArrayType(System::SharedPtr<XmlAttribute> attr);
    ASPOSECPP_SHARED_API System::SharedPtr<XmlQualifiedName> ReadElementQualifiedName();
    ASPOSECPP_SHARED_API void ReadEndElement();
    ASPOSECPP_SHARED_API bool ReadNull();
    ASPOSECPP_SHARED_API System::SharedPtr<XmlQualifiedName> ReadNullableQualifiedName();
    ASPOSECPP_SHARED_API String ReadNullableString();
    ASPOSECPP_SHARED_API bool ReadReference(String& fixupReference);
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadReferencedElement();
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadReferencedElement(String name, String ns);
    ASPOSECPP_SHARED_API void ReadReferencedElements();
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadReferencingElement(String& fixupReference);
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadReferencingElement(String name, String ns,
                                                                          String& fixupReference);
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadReferencingElement(String name, String ns, bool elementCanBeType,
                                                                          String& fixupReference);
    ASPOSECPP_SHARED_API System::SharedPtr<IXmlSerializable>
        ReadSerializable(System::SharedPtr<IXmlSerializable> serializable);
    ASPOSECPP_SHARED_API System::SharedPtr<IXmlSerializable>
        ReadSerializable(System::SharedPtr<IXmlSerializable> serializable, bool wrappedAny);
    ASPOSECPP_SHARED_API String ReadString(String value);
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadTypedPrimitive(System::SharedPtr<XmlQualifiedName> type);
    ASPOSECPP_SHARED_API System::SharedPtr<XmlNode> ReadXmlNode(bool wrapped);
    ASPOSECPP_SHARED_API System::SharedPtr<XmlDocument> ReadXmlDocument(bool wrapped);
    ASPOSECPP_SHARED_API void Referenced(System::SharedPtr<Object> o);

    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> ToByteArrayBase64(bool isNull);
    ASPOSECPP_SHARED_API static System::ArrayPtr<uint8_t> ToByteArrayBase64(String value);
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> ToByteArrayHex(bool isNull);
    ASPOSECPP_SHARED_API static System::ArrayPtr<uint8_t> ToByteArrayHex(String value);
    ASPOSECPP_SHARED_API static char16_t ToChar(String value);
    ASPOSECPP_SHARED_API static DateTime ToDate(String value);
    ASPOSECPP_SHARED_API static DateTime ToDateTime(String value);
    ASPOSECPP_SHARED_API static DateTime ToTime(String value);
    ASPOSECPP_SHARED_API static String ToXmlName(String value);
    ASPOSECPP_SHARED_API static String ToXmlNCName(String value);
    ASPOSECPP_SHARED_API static String ToXmlNmToken(String value);
    ASPOSECPP_SHARED_API static String ToXmlNmTokens(String value);
    ASPOSECPP_SHARED_API System::SharedPtr<XmlQualifiedName> ToXmlQualifiedName(String value);
    ASPOSECPP_SHARED_API void UnknownAttribute(System::SharedPtr<Object> o, System::SharedPtr<XmlAttribute> attr);
    ASPOSECPP_SHARED_API void UnknownAttribute(System::SharedPtr<Object> o, System::SharedPtr<XmlAttribute> attr,
                                               String qnames);
    ASPOSECPP_SHARED_API void UnknownElement(System::SharedPtr<Object> o, System::SharedPtr<XmlElement> elem);
    ASPOSECPP_SHARED_API void UnknownElement(System::SharedPtr<Object> o, System::SharedPtr<XmlElement> elem,
                                             String qnames);
    ASPOSECPP_SHARED_API void UnknownNode(System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API void UnknownNode(System::SharedPtr<Object> o, String qnames);
    ASPOSECPP_SHARED_API void UnreferencedObject(String id, System::SharedPtr<Object> o);
    ASPOSECPP_SHARED_API String CollapseWhitespace(String value);
    ASPOSECPP_SHARED_API Exception CreateBadDerivationException(String xsdDerived, String nsDerived, String xsdBase,
                                                                String nsBase, String clrDerived, String clrBase);
    ASPOSECPP_SHARED_API Exception CreateInvalidCastException(const TypeInfo& type, System::SharedPtr<Object> value,
                                                              String id);
    ASPOSECPP_SHARED_API Exception CreateMissingIXmlSerializableType(String name, String ns, String clrType);
    ASPOSECPP_SHARED_API String ReadString(String value, bool trim);
    ASPOSECPP_SHARED_API System::SharedPtr<Object> ReadTypedNull(System::SharedPtr<XmlQualifiedName> type);
    ASPOSECPP_SHARED_API static System::SharedPtr<Reflection::Assembly> ResolveDynamicAssembly(String assemblyFullName);
    ASPOSECPP_SHARED_API int64_t
        ToEnum(String value, System::SharedPtr<System::Collections::Generic::Dictionary<System::String, int64_t>> h,
               String typeName);

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
    const char* DBG_class_name() const override { return "XmlSerializationReader"; }
#endif

private:
    System::SharedPtr<XmlDocument> m_document;
    System::SharedPtr<XmlReader> m_reader;
    System::SharedPtr<XmlSerializer> m_event_source;
    int32_t delayedFixupId;
    int32_t readCount, whileIterationCount;
    String w3SchemaNS;
    String w3InstanceNS;
    String w3InstanceNS2000;
    String w3InstanceNS1999;
    String soapNS;
    String wsdlNS;
    String nullX;
    String nil;
    String typeX;
    String arrayType;
    System::SharedPtr<XmlQualifiedName> m_array_qname;

    String CurrentTag();
    bool TargetReady(String id);
    bool ReadList(System::SharedPtr<Object>& resultList);
    System::SharedPtr<Object> ReadTypedPrimitive(System::SharedPtr<XmlQualifiedName> qname, bool reportUnknown);
    void OnUnknownNode(System::SharedPtr<XmlNode> node, System::SharedPtr<Object> o, String qnames);
};

}}} // namespace System::Xml::Serialization
