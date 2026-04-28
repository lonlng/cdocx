/// @file xml/xml_serializer.h
#pragma once
#include <xml/xml_writer.h>
#include <xml/serialization/xml_serializer_namespaces.h>
#include <xml/xml_serialization_writer.h>
#include <xml/xml_serialization_reader.h>
#include <xml/xml_root_attribute.h>
#include <xml/xml_attribute_overrides.h>
#include <system/type_info.h>
#include <system/text/encoding.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/io/text_writer.h>
#include <system/io/text_reader.h>
#include <system/io/stream.h>
#include <system/array.h>
#include <cstdint>
#include <xml/xml_reader.h>

namespace System { namespace Xml { namespace Serialization {

class XmlSerializationReader;
class XmlSerializationWriter;

/// Performs serialization and deserialization of objects into and from XML documents.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSerializer : public System::Object
{
    /// This type.
    typedef XmlSerializer ThisType;
    /// Base type.
    typedef System::Object BaseType;

    /// RTTI internals.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// WSDL namespace name.
    ASPOSECPP_SHARED_API static const String WsdlNamespace;
    /// Encoding namespace name.
    ASPOSECPP_SHARED_API static const String EncodingNamespace;
    /// WSDL types namespace name.
    ASPOSECPP_SHARED_API static const String WsdlTypesNamespace;

    /// Checks if specific reader is in deserializable state.
    /// @param xmlReader Reader to check.
    /// @return true if xmlReader can be deserialized, false otherwise.
    ASPOSECPP_SHARED_API virtual bool CanDeserialize(System::SharedPtr<XmlReader> xmlReader);
    /// Deserializes XML document into object.
    /// @param stream Stream to read document from.
    /// @return Object that was previously serialized into the document given.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> Deserialize(System::SharedPtr<IO::Stream> stream);
    /// Deserializes XML document into object.
    /// @param textReader Reader to read document from.
    /// @return Object that was previously serialized into the document given.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> Deserialize(System::SharedPtr<IO::TextReader> textReader);
    /// Deserializes XML document into object.
    /// @param xmlReader Reader to read document from.
    /// @return Object that was previously serialized into the document given.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> Deserialize(System::SharedPtr<XmlReader> xmlReader);
    /// Serializes document into XML.
    /// @param stream Destination stream.
    /// @param o Object to serialize.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<IO::Stream> stream, System::SharedPtr<Object> o);
    /// Serializes document into XML.
    /// @param textWriter Destination stream.
    /// @param o Object to serialize.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<IO::TextWriter> textWriter, System::SharedPtr<Object> o);
    /// Serializes document into XML.
    /// @param xmlWriter Destination stream.
    /// @param o Object to serialize.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<XmlWriter> xmlWriter, System::SharedPtr<Object> o);
    /// Serializes document into XML.
    /// @param stream Destination stream.
    /// @param o Object to serialize.
    /// @param namespaces Namespace storage.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<IO::Stream> stream, System::SharedPtr<Object> o,
                                        System::SharedPtr<XmlSerializerNamespaces> namespaces);
    /// Serializes document into XML.
    /// @param textWriter Destination stream.
    /// @param o Object to serialize.
    /// @param namespaces Namespace storage.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<IO::TextWriter> textWriter, System::SharedPtr<Object> o,
                                        System::SharedPtr<XmlSerializerNamespaces> namespaces);
    /// Serializes document into XML.
    /// @param xmlWriter Destination stream.
    /// @param o Object to serialize.
    /// @param namespaces Namespace storage.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<XmlWriter> xmlWriter, System::SharedPtr<Object> o,
                                        System::SharedPtr<XmlSerializerNamespaces> namespaces);
    /// Deserializes XML document into object.
    /// @param xmlReader Reader to read document from.
    /// @param encodingStyle Style used to serialize object.
    /// @return Object that was previously serialized into the document given.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> Deserialize(System::SharedPtr<XmlReader> xmlReader,
                                                               String encodingStyle);
    /// Serializes document into XML.
    /// @param xmlWriter Destination stream.
    /// @param o Object to serialize.
    /// @param namespaces Namespace storage.
    /// @param encodingStyle Style to use while serializing object.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<XmlWriter> xmlWriter, System::SharedPtr<Object> o,
                                        System::SharedPtr<XmlSerializerNamespaces> namespaces, String encodingStyle);
    /// Serializes document into XML.
    /// @param xmlWriter Destination stream.
    /// @param o Object to serialize.
    /// @param namespaces Namespace storage.
    /// @param encodingStyle Style to use while serializing object.
    /// @param id Object id to use while serializing it.
    ASPOSECPP_SHARED_API void Serialize(System::SharedPtr<XmlWriter> xmlWriter, System::SharedPtr<Object> o,
                                        System::SharedPtr<XmlSerializerNamespaces> namespaces, String encodingStyle,
                                        String id);

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API XmlSerializer();

    /// Creates reader object.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<XmlSerializationReader> CreateReader();
    /// Creates writer object.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<XmlSerializationWriter> CreateWriter();
    /// Deeserializes document read from specific reader.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<Object> Deserialize(System::SharedPtr<XmlSerializationReader> reader);
    /// Serializes object.
    ASPOSECPP_SHARED_API virtual void Serialize(System::SharedPtr<Object> o, System::SharedPtr<XmlSerializationWriter> writer);

    /// Gets encoding used by default.
    ASPOSECPP_SHARED_API static System::SharedPtr<Text::Encoding> get_DefaultEncoding();

private:
    /// Default encoding.
    static System::SharedPtr<Text::Encoding> defaultEncoding;
    /// Whether custom serializer should be used.
    bool customSerializer = false;
};

}}} // namespace System::Xml::Serialization
